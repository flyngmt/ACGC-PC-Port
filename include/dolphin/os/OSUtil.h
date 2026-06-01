#ifndef OS_UTIL_H
#define OS_UTIL_H

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef TARGET_PC
#define OSRoundUp32B(x) (((uintptr_t)(x) + 0x1F) & ~((uintptr_t)0x1F))
#define OSRoundDown32B(x) (((uintptr_t)(x)) & ~((uintptr_t)0x1F))
#else
#define OSRoundUp32B(x) (((u32)(x) + 0x1F) & ~(0x1F))
#define OSRoundDown32B(x) (((u32)(x)) & ~(0x1F))
#endif

#ifdef __cplusplus
};
#endif

#endif