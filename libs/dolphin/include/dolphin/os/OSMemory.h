#ifndef OS_MEMORY_H
#define OS_MEMORY_H
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SIM_MEM *(u32 *)0x800000f0 
static void Config24MB();
static void Config48MB();
u32 OSGetConsoleSimulatedMemSize(void);

void OSProtectRange(u32 chan, void* addr, u32 nBytes, u32 control);

#ifdef __cplusplus
}
#endif
#endif