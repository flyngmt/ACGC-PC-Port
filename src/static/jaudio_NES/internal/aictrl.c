#include "jaudio_NES/aictrl.h"

#include "jaudio_NES/dummyprobe.h"
#include "jaudio_NES/memory.h"
#include "jaudio_NES/sample.h"
#include "jaudio_NES/dspbuf.h"
#include "jaudio_NES/streamctrl.h"
#include "jaudio_NES/rate.h"
#include "dolphin/os.h"
#include "dolphin/ai.h"

typedef void (*DACCallback)(s16*, s32);

u32 UNIVERSAL_DACCOUNTER = 0;

static s16* dac[3];
static ALHeap audio_hp;
static BOOL audio_hp_exist = FALSE;
static s16* last_rsp_madep = nullptr;
static s16* use_rsp_madep = nullptr;
static BOOL vframe_work_running = FALSE;
static DACCallback DAC_CALLBACK_FUNC = nullptr;
u32 JAC_VFRAME_COUNTER = 0;
static MixCallback ext_mixcallback = nullptr;
static u8 ext_mixmode = MixMode_Mono;

extern void Jac_HeapSetup(void* pHeap, s32 size) {
    if (pHeap != nullptr) {
        Nas_HeapInit(&audio_hp, (u8*)pHeap, size);
        audio_hp_exist = TRUE;
    } else {
        audio_hp_exist = FALSE;
    }
}

extern void* OSAlloc2(u32 size) {
    void* alloc;
    BOOL enable = OSDisableInterrupts();

    switch (audio_hp_exist) {
        case FALSE:
            alloc = OSAlloc(size);
            break;
        case TRUE:
            alloc = Nas_HeapAlloc(&audio_hp, size);
            break;
    }

    OSRestoreInterrupts(enable);
    return alloc;
}

extern void Jac_Init(void) {
    for (int i = 0; i < 3; i++) {
        dac[i] = (s16*)OSAlloc2(DAC_SIZE * 2);
        Jac_bzero(dac[i], DAC_SIZE * 2);
#ifndef TARGET_PC
        DCStoreRange(dac[i], DAC_SIZE * 2);
#endif
    }

    AIInit(nullptr);
    AIInitDMA((uintptr_t)dac[2], DAC_SIZE * 2);
}

static void MixMonoTrack(s16* track, s32 nSamples, MixCallback callback) {
    Probe_Start(5, "MONO-MIX");

    s16* monoTrack = (*callback)(nSamples);
    int mix;

    if (monoTrack != nullptr) {
        Probe_Finish(5);

        s16* dst_p = track;
        s16* src_p = monoTrack;

        for (s32 i = 0; i < nSamples; i++) {
            mix = dst_p[0] + src_p[0];
            if (mix < S16_MIN) {
                mix = S16_MIN + 1;
            }

            if (mix > S16_MAX) {
                mix = S16_MAX;
            }

            dst_p[0] = (s16)mix;

            mix = dst_p[1] + src_p[0];
            if (mix < S16_MIN) {
                mix = S16_MIN + 1;
            }

            if (mix > S16_MAX) {
                mix = S16_MAX;
            }

            dst_p[1] = (s16)mix;

            dst_p += 2;
            src_p++;
        }
    }
}

static void MixMonoTrackWide(s16* track, s32 nSamples, MixCallback callback) {
    Probe_Start(5, "MONO(W)-MIX");

    s16* monoTrack = (*callback)(nSamples);
    int mix;

    if (monoTrack != nullptr) {
        Probe_Finish(5);

        s16* dst_p = track;
        s16* src_p = monoTrack;

        for (s32 i = 0; i < nSamples; i++) {
            mix = dst_p[0] + src_p[0];
            if (mix < S16_MIN) {
                mix = S16_MIN + 1;
            }

            if (mix > S16_MAX) {
                mix = S16_MAX;
            }

            dst_p[0] = (s16)mix;

            mix = dst_p[1] - src_p[0];
            if (mix < S16_MIN) {
                mix = S16_MIN + 1;
            }

            if (mix > S16_MAX) {
                mix = S16_MAX;
            }

            dst_p[1] = (s16)mix;

            dst_p += 2;
            src_p++;
        }
    }
}

static void MixExtraTrack(s16* track, s32 nSamples, MixCallback callback) {
    Probe_Start(5, "DSPMIX");

    s16* extraTrack = (*callback)(nSamples);
    int mix;

    if (extraTrack != nullptr) {
        Probe_Finish(5);
        Probe_Start(6, "MIXING");

        s16* dst_p = track;
        s16* src0_p = extraTrack + JAC_FRAMESAMPLES;
        s16* src1_p = extraTrack;

        for (s32 i = 0; i < nSamples; i++) {
            mix = dst_p[0] + src0_p[0];
            if (mix < S16_MIN) {
                mix = S16_MIN + 1;
            }

            if (mix > S16_MAX) {
                mix = S16_MAX;
            }

            dst_p[0] = (s16)mix;

            mix = dst_p[1] + src1_p[0];
            if (mix < S16_MIN) {
                mix = S16_MIN + 1;
            }

            if (mix > S16_MAX) {
                mix = S16_MAX;
            }

            dst_p[1] = (s16)mix;

            dst_p += 2;
            src0_p++;
            src1_p++;
        }

        Probe_Finish(6);
    }
}

static void MixInterleaveTrack(s16* track, s32 nSamples, MixCallback callback) {
    s16* interleaveTrack = (*callback)(nSamples);
    int mix;

    if (interleaveTrack != nullptr) {
        s16* track_p = track;
        s32 max = nSamples * 2;

        for (s32 i = 0; i < max; i++) {
            mix = track_p[0] + interleaveTrack[0];
            if (mix < S16_MIN) {
                mix = S16_MIN + 1;
            }

            if (mix > S16_MAX) {
                mix = S16_MAX;
            }

            track_p[0] = (s16)mix;

            track_p++;
            interleaveTrack++;
        }
    }
}

extern MixCallback Jac_GetMixcallback(u8* mixmode) {
    *mixmode = ext_mixmode;
    return ext_mixcallback;
}

extern void Jac_RegisterMixcallback(MixCallback mixcallback, u8 mixmode) {
    ext_mixcallback = mixcallback;
    ext_mixmode = mixmode;
}

extern void Jac_VframeWork(void) {
    static u32 dacp = 0;

    JAC_VFRAME_COUNTER++;

    s16* mixedTrack = MixDsp(DAC_SIZE / 2);
#ifdef TARGET_PC
    /* On PC, rspsim's INTERLEAVE command already produces interleaved stereo
     * in tmp_buf/dsp_buf. The original Jac_imixcopy assumes split-channel
     * layout (first half = R, second half = L) which is the GC DSP hardware
     * output format. Using it on already-interleaved data scrambles channels,
     * causing R ≈ 2×L gain asymmetry and audible pops. */
    Jac_bcopy(mixedTrack, dac[dacp], DAC_SIZE * 2);
#else
    Jac_imixcopy(&mixedTrack[JAC_FRAMESAMPLES], &mixedTrack[0], dac[dacp], DAC_SIZE / 2);
#endif

    if (ext_mixcallback != nullptr) {
        switch (ext_mixmode) {
            case MixMode_Mono:
                MixMonoTrack(dac[dacp], DAC_SIZE / 2, ext_mixcallback);
                break;
            case MixMode_MonoWide:
                MixMonoTrackWide(dac[dacp], DAC_SIZE / 2, ext_mixcallback);
                break;
            case MixMode_Extra:
                MixExtraTrack(dac[dacp], DAC_SIZE / 2, ext_mixcallback);
                break;
            case MixMode_Interleave:
                MixInterleaveTrack(dac[dacp], DAC_SIZE / 2, ext_mixcallback);
                break;
        }
    }

#ifndef TARGET_PC
    BOOL enable = OSDisableInterrupts();
    DCStoreRange(dac[dacp], DAC_SIZE * 2);
    OSRestoreInterrupts(enable);
#endif

    last_rsp_madep = dac[dacp];
    dacp++;
    if (dacp == 3) {
        dacp = 0;
    }
    vframe_work_running = FALSE;
}

extern void Jac_UpdateDAC(void) {
    if (use_rsp_madep == nullptr) {
        use_rsp_madep = last_rsp_madep;
        last_rsp_madep = nullptr;
    }

    if (use_rsp_madep != nullptr) {
        AIInitDMA((uintptr_t)use_rsp_madep, DAC_SIZE * 2);
        use_rsp_madep = nullptr;
    } else {
        UNIVERSAL_DACCOUNTER++;
    }

    if (last_rsp_madep == nullptr && vframe_work_running == FALSE) {
        Jac_VframeWork();
    }

    StreamMain();

    if (DAC_CALLBACK_FUNC != nullptr) {
        (*DAC_CALLBACK_FUNC)(last_rsp_madep, DAC_SIZE / 2);
    }
}
