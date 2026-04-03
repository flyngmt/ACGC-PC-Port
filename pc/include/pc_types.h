#ifndef PC_TYPES_H
#define PC_TYPES_H

/**
 * pc_types.h - Common type definitions for the PC port layer.
 * Included automatically via pc_platform.h.
 */

#include <stdint.h>

#ifndef ATTRIBUTE_ALIGN
#if defined(__MWERKS__) || defined(__GNUC__) || defined(__clang__)
#define ATTRIBUTE_ALIGN(num) __attribute__((aligned(num)))
#elif defined(_MSC_VER)
#define ATTRIBUTE_ALIGN(num) __declspec(align(num))
#else
#define ATTRIBUTE_ALIGN(num)
#endif
#endif

typedef uint8_t            u8;
typedef uint16_t           u16;
typedef uint32_t           u32;
typedef uint64_t           u64 ATTRIBUTE_ALIGN(8);
typedef int8_t             s8;
typedef int16_t            s16;
typedef int32_t            s32;
typedef int64_t            s64 ATTRIBUTE_ALIGN(8);
typedef float              f32;
typedef double             f64 ATTRIBUTE_ALIGN(8);
typedef int                BOOL;

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#endif /* PC_TYPES_H */
