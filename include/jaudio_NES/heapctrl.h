#ifndef _JAUDIO_HEAPCTRL_H
#define _JAUDIO_HEAPCTRL_H

#include "types.h"

typedef struct jaheap_ jaheap_;
typedef struct jaheap_ jaheap;

struct jaheap_ {
	u8 isRootHeap;             // _00, is this a 'mother' heap?
	u8 memoryType;             // _01, 0 = ARAM, 1 = DRAM
	u16 childCount;            // _02
	u32 heapId;                // _04
	u32 startAddress;          // _08
	u32 usedSize;              // _0C
	u32 size;                  // _10
	jaheap_* firstChild;       // _14
	jaheap_* parent;           // _18
	jaheap_* nextSibling;      // _1C
	jaheap_* groupOwner;       // _20
	jaheap_* firstGroupedHeap; // _24
	jaheap_* nextGroupedHeap;  // _28
};

#ifdef __cplusplus
extern "C" {
#endif

void Jac_GetUnlockHeap(jaheap_*);
void Jac_CheckAlloc(jaheap_*);
void Jac_InitHeap(jaheap_*);
void Jac_SelfInitHeap(jaheap_*, u32, u32, u32);
BOOL Jac_SelfAllocHeap(jaheap_*, jaheap_*, u32, u32);
BOOL Jac_SetGroupHeap(jaheap_*, jaheap_*);
void Jac_CutdownHeap(jaheap_*);
#ifdef TARGET_PC
void Jac_InitMotherHeap(jaheap_*, uintptr_t, u32, u8);
#else
void Jac_InitMotherHeap(jaheap_*, u32, u32, u8);
#endif
BOOL Jac_AllocHeap(jaheap_*, jaheap_*, u32);
BOOL Jac_DeleteHeap(jaheap_*);
void Jac_GarbageCollection_St(jaheap_*);
void Jac_CheckFreeHeap_Total(jaheap_*);
void Jac_CheckFreeHeap_Linear(jaheap_*);
void Jac_ShowHeap(jaheap_*, u32);

#ifdef __cplusplus
}
#endif

#endif
