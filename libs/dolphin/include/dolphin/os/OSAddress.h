#ifndef OS_ADDRESS_H
#define OS_ADDRESS_H

// maybe put this in OSUtil instead
#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Defines for cached and uncached memory.
// #define OS_BASE_CACHED (0x80000000)
// #define OS_BASE_UNCACHED (0xC0000000)

// // Address conversions.
// #define OSPhysicalToCached(paddr) ((void *)((u32)(paddr) + OS_BASE_CACHED))
// #define OSPhysicalToUncached(paddr) ((void *)((u32)(paddr) + OS_BASE_UNCACHED))
// #define OSCachedToPhysical(caddr) ((u32)((u8 *)(caddr)-OS_BASE_CACHED))
// #define OSUncachedToPhysical(ucaddr) ((u32)((u8 *)(ucaddr)-OS_BASE_UNCACHED))
// #define OSCachedToUncached(caddr) ((void *)((u8 *)(caddr) + (OS_BASE_UNCACHED - OS_BASE_CACHED)))
// #define OSUncachedToCached(ucaddr) ((void *)((u8 *)(ucaddr) - (OS_BASE_UNCACHED - OS_BASE_CACHED)))

// #define OS_CACHED_REGION_PREFIX 0x8000
// #define OS_UNCACHED_REGION_PREFIX 0xC000
// #define OS_PHYSICAL_MASK 0x3FFF

#ifdef __cplusplus
};
#endif

#endif
