#include "jaudio_NES/audiothread.h"

#include "dolphin/ai.h"
#include "dolphin/os.h"
#include "dolphin/os/OSFastCast.h"
#include "jaudio_NES/dspproc.h"
#include "jaudio_NES/cpubuf.h"
#include "jaudio_NES/dummyprobe.h"
#include "jaudio_NES/rate.h"
#include "jaudio_NES/aictrl.h"
#include "jaudio_NES/dummyrom.h"
#include "jaudio_NES/neosthread.h"
#include "jaudio_NES/dvdthread.h"
#include "jaudio_NES/dspboot.h"
#include "jaudio_NES/ja_calc.h"
#include "jaudio_NES/dspinterface.h"
#include "jaudio_NES/playercall.h"
#include "jaudio_NES/dspbuf.h"

#ifdef TARGET_PC
/*==========================================================================
 * PC: Synchronous audio — no threads, no message queues, no DSP interrupts.
 * StartAudioThread does all init inline. pc_audio_process_frame() is called
 * each game frame to drive audio processing.
 *==========================================================================*/

volatile int intcount = 0;
static BOOL pc_audio_initialized = FALSE;

extern void DspSyncCountClear(int count) {
    intcount = count;
}

extern int DspSyncCountCheck(void) {
    return intcount;
}

/* NeosSync on PC: no-op. On GC this signals the CPU that the NEOS
 * thread finished processing. On PC (synchronous), the buffer ring
 * is driven by Jac_VframeWork → MixCpu → CpubufProcess(MIX) path.
 * Calling CpuFrameEnd here would stall the ring buffer because read
 * hasn't advanced yet. */
extern void NeosSync(void) {
    /* no-op on PC */
}

/* Defined in os.c — must be called before audio thread starts */
extern void pc_audio_mq_init(void);
/* Defined in pc_audio.c — starts the audio producer thread */
extern void pc_audio_start_producer_thread(void);

extern void StartAudioThread(void* pHeap, s32 heapSize, u32 aramSize, u32 flags) {
    u32 neos_flag;

    /* Init thread-safe message queues before any audio processing */
    pc_audio_mq_init();

    Jac_HeapSetup(pHeap, heapSize);
    Jac_SetAudioARAMSize(aramSize);

    neos_flag = flags & AUDIO_THREAD_FLAG_NEOS;
    Jac_InitARAM(neos_flag);

    /* Init audio subsystem inline (replaces audioproc thread) */
    OSInitFastCast();
    Jac_Init();
    Jac_InitSinTable();
    ResetPlayerCallback();
    DspbufProcess(DSPBUF_EVENT_INIT);
    CpubufProcess(DSPBUF_EVENT_INIT);
    /* Skip DspBoot() — no DSP microcode on PC */
    DSP_InitBuffer();
    AISetDSPSampleRate(JAC_AI_SETTING);
    AIStartDMA();

    /* Init DVD task system (synchronous) */
    if ((flags & AUDIO_THREAD_FLAG_DVD)) {
        jac_dvdproc_init();
    }

    /* Init NEOS (synchronous) */
    if (neos_flag) {
        pc_neos_init_sync();
    }

    pc_audio_initialized = TRUE;

    /* Start dedicated audio producer thread — decouples audio from game frame */
    pc_audio_start_producer_thread();
}

/* Called by the audio producer thread to generate samples */
void pc_audio_process_frame(void) {
    if (!pc_audio_initialized) return;

    /* Process DSP subframes from previous frame's setup */
    if (intcount > 0) {
        while (intcount > 0) {
            intcount--;
            if (intcount == 0) {
                DspFrameEnd();
            } else {
                UpdateDSP();
            }
        }
    }

    /* Update DAC — mixes DSP + NEOS output into dac[] buffers */
    Jac_UpdateDAC();
}

#else /* !TARGET_PC — original GC code */

#include "dolphin/hw_regs.h"
#include "dolphin/ai.h"

#define AUDIO_STACK_SIZE 0x1000
#define AUDIOPROC_MQ_BUF_COUNT 16

#define AUDIOPROC_MESSAGE_UPDATE_DAC ((OSMessage)0)
#define AUDIOPROC_MESSAGE_DSP_SYNC ((OSMessage)1)
#define AUDIOPROC_MESSAGE_NEOS_SYNC ((OSMessage)2)
#define AUDIOPROC_MESSAGE_3 ((OSMessage)3)

OSThread jac_audioThread;
OSThread jac_neosThread;
OSThread jac_dvdThread;

static u8 audioStack[AUDIO_STACK_SIZE] ATTRIBUTE_ALIGN(32);
static u8 neosStack[AUDIO_STACK_SIZE] ATTRIBUTE_ALIGN(32);
static u8 dvdStack[AUDIO_STACK_SIZE] ATTRIBUTE_ALIGN(32);
static OSMessageQueue audioproc_mq;
static OSMessage msgbuf[AUDIOPROC_MQ_BUF_COUNT];
static u32 audioproc_mq_init = FALSE;
volatile int intcount = 0;

extern void DspSyncCountClear(int count) {
    intcount = count;
}

extern int DspSyncCountCheck(void) {
    return intcount;
}

static void DspSync(void) {
    if (audioproc_mq_init) {
        OSSendMessage(&audioproc_mq, AUDIOPROC_MESSAGE_DSP_SYNC, OS_MESSAGE_NOBLOCK);
    } else {
        DSPReleaseHalt();
    }
}

static void AudioSync(void) {
    static BOOL first = TRUE;

    if (first == FALSE) {
        Probe_Finish(4);
    }

    first = FALSE;
    Probe_Start(4, "UPDATE-DAC");
    if (audioproc_mq_init) {
        OSSendMessage(&audioproc_mq, AUDIOPROC_MESSAGE_UPDATE_DAC, OS_MESSAGE_NOBLOCK);
    }
}

extern void NeosSync(void) {
    if (audioproc_mq_init) {
        OSSendMessage(&audioproc_mq, AUDIOPROC_MESSAGE_NEOS_SYNC, OS_MESSAGE_BLOCK);
    }
}

static void __DspSync(__OSInterrupt interrupt, OSContext* context) {
    u16 reg = __DSPRegs[DSP_CONTROL_STATUS];
    reg &= ~(1 << 3); /* clear AI interrupt */
    reg &= ~(1 << 5); /* clear AR interrupt */
    reg |= (1 << 7);  /* set DSP interrupt */
    __DSPRegs[DSP_CONTROL_STATUS] = reg;

    OSContext tmp_context;
    OSClearContext(&tmp_context);
    OSSetCurrentContext(&tmp_context);
    DspSync();
    OSClearContext(&tmp_context);
    OSSetCurrentContext(context);
}

static void __DspReg(void) {
    BOOL enable = OSDisableInterrupts();
    __OSSetInterruptHandler(OS_INTR_DSP_DSP, &__DspSync);
    OSRestoreInterrupts(enable);
}

static void* audioproc(void* param) {
    OSInitFastCast();
    OSInitMessageQueue(&audioproc_mq, msgbuf, AUDIOPROC_MQ_BUF_COUNT);
    audioproc_mq_init = TRUE;
    Jac_Init();
    Jac_InitSinTable();
    ResetPlayerCallback();
    DspbufProcess(DSPBUF_EVENT_INIT);
    CpubufProcess(DSPBUF_EVENT_INIT);
    DspBoot();
    DSP_InitBuffer();
    __DspReg();
    AISetDSPSampleRate(JAC_AI_SETTING);
    AIRegisterDMACallback(&AudioSync);
    AIStartDMA();

    while (TRUE) {
        OSMessage msg;

        OSReceiveMessage(&audioproc_mq, &msg, OS_MESSAGE_BLOCK);
        switch ((int)msg) {
            case (int)AUDIOPROC_MESSAGE_UPDATE_DAC:
                Jac_UpdateDAC();
                break;
            case (int)AUDIOPROC_MESSAGE_DSP_SYNC:
                if (intcount == 0) {
                    return;
                }

                intcount--;
                if (intcount == 0) {
                    Probe_Finish(7);
                    DspFrameEnd();
                } else {
                    Probe_Start(2, "SFR_DSP");
                    UpdateDSP();
                    Probe_Finish(2);
                }

                break;
            case (int)AUDIOPROC_MESSAGE_NEOS_SYNC:
                CpuFrameEnd();
                break;
            case (int)AUDIOPROC_MESSAGE_3:
                OSExitThread(NULL);
                break;
        }
    }
}

static BOOL priority_set = FALSE;
static OSPriority pri = 0;
static OSPriority pri2 = 0;
static OSPriority pri3 = 0;

extern void StartAudioThread(void* pHeap, s32 heapSize, u32 aramSize, u32 flags) {
    if (priority_set == FALSE) {
        OSPriority base_prio = OSGetThreadPriority(OSGetCurrentThread()) - 3;

        pri = base_prio;
        pri3 = base_prio + 1;
        pri2 = base_prio + 2;
    }

    u32 neos_flag;

    Jac_HeapSetup(pHeap, heapSize);
    Jac_SetAudioARAMSize(aramSize);

    neos_flag = flags & AUDIO_THREAD_FLAG_NEOS;
    Jac_InitARAM(neos_flag);

    if ((flags & AUDIO_THREAD_FLAG_AUDIO)) {
        // point to top of audioStack
        u8* stack_p = audioStack;
        OSCreateThread(&jac_audioThread, &audioproc, NULL, &stack_p[AUDIO_STACK_SIZE], AUDIO_STACK_SIZE, pri, 0);
        OSResumeThread(&jac_audioThread);
    }

    if ((flags & AUDIO_THREAD_FLAG_DVD)) {
        jac_dvdproc_init();
        // point to top of dvdStack
        u8* stack_p = dvdStack;
        OSCreateThread(&jac_dvdThread, &jac_dvdproc, NULL, &stack_p[AUDIO_STACK_SIZE], AUDIO_STACK_SIZE, pri3, 0);
        OSResumeThread(&jac_dvdThread);
    }

    if (neos_flag) {
        // point to top of neosStack
        u8* stack_p = neosStack;
        OSCreateThread(&jac_neosThread, &neosproc, NULL, &stack_p[AUDIO_STACK_SIZE], AUDIO_STACK_SIZE, pri2, 0);
        OSResumeThread(&jac_neosThread);
    }
}

#endif /* TARGET_PC */
