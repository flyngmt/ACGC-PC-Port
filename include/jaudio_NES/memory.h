#ifndef _JAUDIO_MEMORY_H
#define _JAUDIO_MEMORY_H

#include "types.h"
#include "jaudio_NES/audiostruct.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void Nas_HeapInit(ALHeap* heap, u8* base, s32 len);
extern void* Nas_HeapAlloc(ALHeap* heap, s32 size);
extern void* Nas_HeapAlloc_CL(ALHeap* heap, s32 size);
extern void* Nas_NcHeapAlloc(ALHeap* heap, s32 size);
extern void* Nas_2ndHeapAlloc(ALHeap* heap, s32 size);
extern void* Nas_Alloc_Single(s32 size, s32 bank_id, u8* wave_addr, s8 medium, s32 cache);

extern void* Nas_CacheOff(u8* addr, s32 size);

extern void* Nas_SzHeapAlloc(s32 table_type, s32 size, s32 cache_type, s32 id);
extern void* Nas_SzCacheCheck(s32 type, s32 cache_type, s32 id);
extern void Nas_SzStayDelete(s32 type);
extern void Nas_SzHeapReset(u32 fix_size);

extern void Nas_SetDelayLineParam(s32 delayIdx, s32 param_type, intptr_t param_value, s32 init);

extern void Nas_SetBPFilter(s16* filter, s32 lowpass_cutoff, s32 highpass_cutoff);

extern s32 Nas_SpecChange(void);

extern void EntryWave(s32 id);
extern void* EmemOnCheck(s32 table_type, s32 id);
extern void* EmemAlloc(s32 table_type, s32 id, s32 size);

extern void Nas_ForceStopChannel(s32 bank_id);

#ifdef __cplusplus
}
#endif

#endif
