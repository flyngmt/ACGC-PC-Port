#ifndef DSPPROC_H
#define DSPPROC_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern s32 DSPSendCommands(u32* commands, u32 count);
extern u32 DSPReleaseHalt();
extern void DSPWaitFinish();
#ifdef TARGET_PC
extern void DsetupTable(uintptr_t arg0, uintptr_t arg1, uintptr_t arg2, uintptr_t arg3, uintptr_t arg4);
#else
extern void DsetupTable(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4);
#endif
#ifdef TARGET_PC
extern void DsyncFrame(u32 subframes, uintptr_t dspbuf_start, uintptr_t dspbuf_end);
#else
extern void DsyncFrame(u32 subframes, u32 dspbuf_start, u32 dspbuf_end);
#endif
extern void DwaitFrame();
#ifdef TARGET_PC
extern void DiplSec(uintptr_t arg0);
extern void DagbSec(uintptr_t arg0);
#else
extern void DiplSec(u32 arg0);
extern void DagbSec(u32 arg0);
#endif

#ifdef __cplusplus
}
#endif

#endif
