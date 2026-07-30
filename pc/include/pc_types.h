#ifndef PC_TYPES_H
#define PC_TYPES_H

/**
 * pc_types.h - Common type definitions for the PC port layer.
 * Included automatically via pc_platform.h.
 */

#ifdef TARGET_PC
#include <dolphin/types.h>
#else
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned long      u32;
typedef unsigned long long u64;
typedef signed char        s8;
typedef signed short       s16;
typedef signed long        s32;
typedef signed long long   s64;
typedef float              f32;
typedef double             f64;
typedef int                BOOL;
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#endif /* PC_TYPES_H */
