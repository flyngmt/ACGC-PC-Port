#ifndef _JAUDIO_DSPDRIVER_H
#define _JAUDIO_DSPDRIVER_H

#include "types.h"
#include "jaudio_NES/audiostruct.h"

/////////// JAUDIO DSP DRIVER DEFINITIONS ///////////
// Global functions (all C++, so no extern C wrap).

#ifdef __cplusplus
extern "C" {
#endif

typedef uintptr_t JacDspOwner;

dspch_* GetDSPchannelHandle(u32 idx);
void InitDSPchannel();
dspch_* AllocDSPchannel(u32, JacDspOwner);
int DeAllocDSPchannel(dspch_*, JacDspOwner);
dspch_* GetLowerDSPchannel();
dspch_* GetLowerActiveDSPchannel();
BOOL ForceStopDSPchannel(dspch_*);
BOOL BreakLowerDSPchannel(u8);
BOOL BreakLowerActiveDSPchannel(u8);
void UpdateDSPchannelAll();

/////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif
