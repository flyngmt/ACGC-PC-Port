#include "jaudio_NES/neosthread.h"

#include "dolphin/os.h"
#include "jaudio_NES/dummyrom.h"
#include "jaudio_NES/dvdthread.h"
#include "jaudio_NES/aictrl.h"
#include "jaudio_NES/rate.h"
#include "jaudio_NES/audioconst.h"
#include "jaudio_NES/system.h"
#include "jaudio_NES/audiothread.h"
#include "jaudio_NES/cpubuf.h"
#include "jaudio_NES/dummyprobe.h"
#include "jaudio_NES/sub_sys.h"
#include "jaudio_NES/rspsim.h"
#include "jaudio_NES/sample.h"

#define NEOSTHREAD_IMAGE_LOADED_MSG (0x12345678)
#define NEOSTHREAD_ACMD_BUF_NUM 1600

#ifdef TARGET_PC
/*==========================================================================
 * PC: Synchronous NEOS — no thread, DVD loads complete synchronously.
 *==========================================================================*/
static s16* tmp_buf = nullptr;
static BOOL neos_ready = FALSE;
static Acmd pc_task_buf[2][NEOSTHREAD_ACMD_BUF_NUM];
static u32 pc_tasks[2] = { 0, 0 };
static u32 pc_neos_cur = 0;

extern u32 Neos_Update(s16* dst) {
    if (!neos_ready) return FALSE;

    /* Synchronous: generate audio task commands and run rspsim immediately */
    u32 cur = pc_neos_cur;
    pc_tasks[cur] = CreateAudioTask(pc_task_buf[cur], tmp_buf, JAC_FRAMESAMPLES, 0);

    u32 prev = (cur + 1) & 1;
    if (pc_tasks[prev]) {
        RspStart2(pc_task_buf[prev], pc_tasks[prev], 0);
        pc_tasks[prev] = 0;
        Jac_bcopy(tmp_buf, dst, DAC_SIZE * 2);
    } else {
        Jac_bzero(dst, DAC_SIZE * 2);
    }

    /* Diagnostic: check NEOS output amplitude every 60 frames */
    {
        static u32 neos_diag_ctr = 0;
        if ((neos_diag_ctr++ % 60) == 0) {
            s32 peak = 0;
            for (u32 i = 0; i < DAC_SIZE; i++) {
                s32 v = dst[i];
                if (v < 0) v = -v;
                if (v > peak) peak = v;
            }
            printf("[NEOS_OUT] frame=%u tasks=%u peak=%d\n", neos_diag_ctr, pc_tasks[cur], peak);
        }
    }

    NeosSync();
    pc_neos_cur = prev;
    return TRUE;
}

extern void ImageLoaded(u32 param) {
    /* On PC, DVD load is synchronous — this is called as the completion callback */
    (void)param;
}

extern BOOL Neos_CheckBoot(void) {
    return neos_ready;
}

/* Called from StartAudioThread on PC to do synchronous NEOS init */
void pc_neos_init_sync(void) {
    neos_ready = FALSE;

    u32 neos_rom_top = GetNeosRomTop();
    u32 neos_rom_preloaded = GetNeosRom_PreLoaded();
    u32 neos_file_top = GetNeos_FileTop();

    /* Synchronous DVD load — dvdthread processes this inline on PC */
    DVDT_LoadtoARAM(0, "/audiorom.img", neos_rom_top + neos_rom_preloaded, neos_file_top, 0, nullptr, &ImageLoaded);

    /* Process the DVD task synchronously */
    pc_dvd_process_all_tasks();

    tmp_buf = (s16*)OSAlloc2(DAC_SIZE * 2);

    /* Initialize NEOS audio */
    s32 buf_size = AGC.acmdBufSize;
    u64* acmdBuf = (u64*)OSAlloc2(buf_size);
    Nas_InitAudio(acmdBuf, buf_size);
    NeosSync();
    neos_ready = TRUE;

    Jac_RegisterMixcallback(&MixCpu, MixMode_Interleave);
}

extern void* neosproc(void* param) {
    /* Not used on PC — synchronous model */
    (void)param;
    return nullptr;
}

#else /* !TARGET_PC — original GC code */

static OSMessageQueue neosproc_mq;
static u32 neosproc_mq_init = FALSE;
static s16* tmp_buf = nullptr;
static BOOL neos_ready = FALSE;

extern u32 Neos_Update(s16* dst) {
    if (neosproc_mq_init) {
        if (OSSendMessage(&neosproc_mq, (OSMessage)dst, OS_MESSAGE_NOBLOCK) == TRUE) {
            return TRUE;
        } else {
            return FALSE;
        }
    }

    return FALSE;
}

extern void ImageLoaded(u32 param) {
    OSSendMessage(&neosproc_mq, (OSMessage)NEOSTHREAD_IMAGE_LOADED_MSG, OS_MESSAGE_BLOCK);
}

extern BOOL Neos_CheckBoot(void) {
    return neos_ready;
}

extern void* neosproc(void* param) {
    static OSMessage msgbuf[1];
    static u32 cur = 0;

    neos_ready = FALSE;
    OSInitMessageQueue(&neosproc_mq, msgbuf, 1);
    neosproc_mq_init = TRUE;
    u32 neos_rom_top = GetNeosRomTop();
    u32 neos_rom_preloaded = GetNeosRom_PreLoaded();
    u32 neos_file_top = GetNeos_FileTop();

    DVDT_LoadtoARAM(0, "/audiorom.img", neos_rom_top + neos_rom_preloaded, neos_file_top, 0, nullptr, &ImageLoaded);

    OSMessage msg;
    do {
        OSReceiveMessage(&neosproc_mq, &msg, 1);
    } while (msg != (OSMessage)NEOSTHREAD_IMAGE_LOADED_MSG);

    tmp_buf = (s16*)OSAlloc2(DAC_SIZE * 2);

    /* Initialize neos */
    s32 tmp = AGC.acmdBufSize;
    u64* acmdBuf = (u64*)OSAlloc2(tmp);
    Nas_InitAudio(acmdBuf, tmp);
    NeosSync();
    neos_ready = TRUE;

    Jac_RegisterMixcallback(&MixCpu, MixMode_Interleave);

    do {
        static Acmd task_buf[2][NEOSTHREAD_ACMD_BUF_NUM];
        static u32 tasks[2] = { 0, 0 };

        OSReceiveMessage(&neosproc_mq, &msg, OS_MESSAGE_BLOCK);
        Probe_Start(8, "NEOS THREAD");
        s16* samples_dst = (s16*)msg;
        tasks[cur] = CreateAudioTask(task_buf[cur], tmp_buf, JAC_FRAMESAMPLES, 0);

        tmp = (cur + 1) & 1;
        if (tasks[tmp]) {
            RspStart2((u32*)task_buf[tmp], tasks[tmp], 0);
            tasks[tmp] = 0;
            Jac_bcopy(tmp_buf, samples_dst, DAC_SIZE * 2);
        } else {
            Jac_bzero(samples_dst, DAC_SIZE * 2);
        }

        Probe_Finish(8);
        NeosSync();
        cur = tmp;
    } while (TRUE);
}

#endif /* TARGET_PC */
