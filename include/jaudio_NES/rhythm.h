#ifndef RHYTHM_H
#define RHYTHM_H

#include "types.h"
#include "audio.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void Na_RhythmInit();
extern s8 Na_GetRhythmSubTrack(uintptr_t idx);
extern void Na_RhythmStart(uintptr_t idx, s8 arg1, s8 arg2);
extern void Na_RhythmStop(uintptr_t idx);
extern void Na_RhythmAllStop();
extern f32 Na_GetRhythmAnimCounter(uintptr_t idx);
extern s8 Na_GetRhythmDelay(uintptr_t idx);
extern void Na_GetRhythmInfo(TempoBeat_c* tempo);
extern void Na_SetRhythmInfo(TempoBeat_c* tempo);

#ifdef __cplusplus
}
#endif

#endif
