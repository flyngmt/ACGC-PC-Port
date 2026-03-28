#include "jaudio_NES/dspbuf.h"

#include "jaudio_NES/aictrl.h"
#include "jaudio_NES/ipldec.h"
#include "jaudio_NES/audiothread.h"
#include "jaudio_NES/dspproc.h"
#include "jaudio_NES/dspdriver.h"
#include "jaudio_NES/dspinterface.h"
#include "jaudio_NES/playercall.h"
#include "jaudio_NES/dummyprobe.h"

#define DSPBUF_NUM 3

static u8 write_buffer = 0;
static u8 read_buffer = 0;
static u8 dspstatus = 0;
static s16* dsp_buf[DSPBUF_NUM];
static u32 dac_sync_counter = 0;

extern s16* DspbufProcess(DSPBUF_EVENTS event) {
    u32 i;
    u32 j;

    switch (event) {
        case DSPBUF_EVENT_INIT:
            write_buffer = 2;
            read_buffer = 0;
            for (i = 0; i < DSPBUF_NUM; i++) {
                dsp_buf[i] = (s16*)OSAlloc2(JAC_FRAMESAMPLES << 2);
                for (j = 0; j < (JAC_FRAMESAMPLES << 1); j++) {
                    dsp_buf[i][j] = 0;
                }

#ifndef TARGET_PC
                DCStoreRange(dsp_buf[i], JAC_FRAMESAMPLES << 2);
#endif
            }

            dspstatus = 0;
            break;
        case DSPBUF_EVENT_FRAME_END: {
            DspExtraTaskCheck();
            u8 write = write_buffer + 1;

            if (write == DSPBUF_NUM) {
                write = 0;
            }

            if (write == read_buffer) {
                dspstatus = 0;
            } else {
                write_buffer = write;
                DspSyncCountClear(JAC_SUBFRAMES);
                Probe_Start(7, "DSP-MAIN");
                DsyncFrame(JAC_SUBFRAMES, (uintptr_t)dsp_buf[write_buffer], (uintptr_t)&dsp_buf[write_buffer][JAC_FRAMESAMPLES]);
                dspstatus = 1;
                UpdateDSP();
            }
            break;
        }
        case DSPBUF_EVENT_MIX: {
#ifdef TARGET_PC
            /* DSP hardware doesn't run on PC — just return a zeroed buffer.
             * The original code fills with the last sample when buffers haven't
             * advanced, creating a per-frame DC offset that causes audible pops
             * when mixed with the CPU pipeline output. */
            for (i = 0; i < (JAC_FRAMESAMPLES << 1); i++) {
                dsp_buf[read_buffer][i] = 0;
            }
            return dsp_buf[read_buffer];
#else
            u8 read = read_buffer + 1;
            if (read == DSPBUF_NUM) {
                read = 0;
            }

            if (read == write_buffer) {
                s16 left = dsp_buf[read_buffer][(JAC_FRAMESAMPLES / 2) - 1];
                s16 right = dsp_buf[read_buffer][JAC_FRAMESAMPLES - 1];

                for (i = 0; i < JAC_FRAMESAMPLES; i++) {
                    dsp_buf[read_buffer][i] = left;
                }

                for (i = JAC_FRAMESAMPLES; i < (JAC_FRAMESAMPLES << 1); i++) {
                    dsp_buf[read_buffer][i] = right;
                }

                if (dspstatus == 0) {
                    DspbufProcess(DSPBUF_EVENT_FRAME_END);
                }
            } else {
                read_buffer = read;
                DCInvalidateRange(dsp_buf[read_buffer], JAC_FRAMESAMPLES << 2);
                if (dspstatus == 0) {
                    DspbufProcess(DSPBUF_EVENT_FRAME_END);
                }
            }

            return dsp_buf[read_buffer];
#endif
        }
    }

    return nullptr;
}

extern void UpdateDSP(void) {
    dac_sync_counter++;
    Probe_Start(3, "SFR-UPDATE");
    DSP_InvalChannelAll();
    DspPlayerCallback();
    UpdateDSPchannelAll();
    DSPReleaseHalt();
    PlayerCallback();
    Probe_Finish(3);
}

extern s16* MixDsp(s32 n_samples) {
    static s32 cur = 0;
    return DspbufProcess(DSPBUF_EVENT_MIX);
}

extern void DspFrameEnd(void) {
    DspbufProcess(DSPBUF_EVENT_FRAME_END);
}
