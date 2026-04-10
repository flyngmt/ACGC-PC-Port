/* pc_audio_ptr.h - 64-bit pointer recovery for audio DMA commands.
 * Audio Acmd commands pack pointers into u32 w1 fields, truncating on 64-bit.
 * Since all audio pointers come from a single contiguous region (the audio heap
 * or related allocations), they share the same upper 32 bits. We store that
 * prefix once and reconstruct full pointers in rspsim. */
#ifndef PC_AUDIO_PTR_H
#define PC_AUDIO_PTR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if UINTPTR_MAX > 0xFFFFFFFFu

extern uintptr_t pc_audio_ptr_base;

/* Call once with any audio heap pointer to capture the upper 32 bits */
static inline void pc_audio_ptr_init(void* any_audio_ptr) {
    pc_audio_ptr_base = (uintptr_t)any_audio_ptr & ~(uintptr_t)0xFFFFFFFF;
}

/* Recover full pointer from truncated u32 in audio command */
static inline void* pc_audio_recover_ptr(unsigned int truncated) {
    if (truncated == 0) return (void*)0;
    return (void*)(pc_audio_ptr_base | (uintptr_t)truncated);
}

#else
/* 32-bit: no recovery needed */
#define pc_audio_ptr_init(p) ((void)0)
#define pc_audio_recover_ptr(t) ((void*)(uintptr_t)(t))
#endif

#ifdef __cplusplus
}
#endif

#endif /* PC_AUDIO_PTR_H */
