#ifndef SAMPLE_H
#define SAMPLE_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void Jac_imixcopy(s16* ta, s16* tb, s16* td, s32 s);
extern void Jac_bcopyfast(u32* src, u32* dest, u32 size);
extern void Jac_bcopy(void* src, void* dest, size_t size);
extern void Jac_bzerofast(u32* dest, u32 size);
extern void Jac_bzero(void* dest, s32 size);

#ifdef __cplusplus
}
#endif

#endif
