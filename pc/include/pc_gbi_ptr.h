/* pc_gbi_ptr.h - 64-bit pointer recovery for GBI display list commands.
 * GBI commands store addresses in 32-bit w1 fields. On 64-bit, pointers
 * are truncated. This module recovers the full address from the truncated
 * value using the executable/arena base addresses. */
#ifndef PC_GBI_PTR_H
#define PC_GBI_PTR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(TARGET_PC) && UINTPTR_MAX > 0xFFFFFFFFu

/* Recover a full 64-bit pointer from a truncated 32-bit GBI w1 value.
 * Strategy: all game pointers come from one of two regions:
 *   1. Static data in the executable (__DATA segment) — share pc_image_base upper bits
 *   2. Arena memory (mmap'd heap) — share arena_memory upper bits
 * We check which region the low 32 bits fall into and reconstruct accordingly. */
extern uintptr_t pc_image_base;
extern u8* arena_memory;

static inline uintptr_t pc_gbi_recover_ptr(unsigned int truncated) {
    if (truncated == 0) return 0;

    /* Check if it's an arena pointer (game heap allocations) */
    uintptr_t arena_base = (uintptr_t)arena_memory;
    uintptr_t arena_lo32 = arena_base & 0xFFFFFFFF;
    uintptr_t arena_hi32 = arena_base & ~(uintptr_t)0xFFFFFFFF;
    uintptr_t arena_end_lo32 = (arena_base + 48u * 1024u * 1024u) & 0xFFFFFFFF;

    if (arena_lo32 <= arena_end_lo32) {
        /* Arena doesn't wrap in low 32 bits */
        if (truncated >= arena_lo32 && truncated < arena_end_lo32) {
            return arena_hi32 | (uintptr_t)truncated;
        }
    }

    /* Check if it's a static data pointer (executable image) */
    uintptr_t img_hi32 = pc_image_base & ~(uintptr_t)0xFFFFFFFF;
    uintptr_t img_lo32 = pc_image_base & 0xFFFFFFFF;
    if (truncated >= img_lo32) {
        return img_hi32 | (uintptr_t)truncated;
    }

    /* Unknown region — return as-is (may be a segment address or small offset) */
    return (uintptr_t)truncated;
}

/* Truncate a pointer for storage in a GBI w1 field */
#define GBI_PTR_TRUNC(p) ((unsigned int)(uintptr_t)(p))

#else
/* 32-bit: no recovery needed */
#define pc_gbi_recover_ptr(t) ((uintptr_t)(t))
#define GBI_PTR_TRUNC(p) ((unsigned int)(uintptr_t)(p))
#endif

#ifdef __cplusplus
}
#endif

#endif /* PC_GBI_PTR_H */
