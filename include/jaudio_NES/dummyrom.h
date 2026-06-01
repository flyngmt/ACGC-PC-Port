#ifndef DUMMYROM_H
#define DUMMYROM_H

#include "types.h"
#include "jaudio_NES/audiostruct.h"
#include "libultra/libultra.h"

#define DUMMYROM_DRAM_TO_ARAM 0
#define DUMMYROM_ARAM_TO_DRAM 1

#ifdef __cplusplus
extern "C" {
#endif

extern u8* JAC_ARAM_DMA_BUFFER_TOP;
extern ALHeap aram_hp; /* placed in common bss */

extern u32 GetNeos_FileTop(void);
extern u32 GetNeosRomTop(void);
extern u32 GetNeosRom_PreLoaded(void);
extern u32 SetPreCopy_NeosRom(u8* load_addr, u32 load_size, BOOL cut_flag);
extern BOOL ARAMStartDMAmesg(u32 dir, uintptr_t dramAddr, u32 aramAddr, u32 size, s32 unused, OSMesgQueue* mq);
extern void Jac_SetAudioARAMSize(u32 size);
extern void* ARAllocFull(u32* outSize);
extern void Jac_InitARAM(u32 loadAudiorom);

#ifdef __cplusplus
}
#endif

#endif
