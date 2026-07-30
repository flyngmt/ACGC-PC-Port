#include "jaudio_NES/sample.h"

#include "dolphin/os/OSCache.h"

#ifdef TARGET_PC
/* reinterpret_cast -> C cast so sample.c compiles as C on PC */
#define CAST_PTR_U32(p) ((u32)(uintptr_t)(p))
#include <string.h> /* memmove */
#endif

extern void Jac_imixcopy(s16* ta, s16* tb, s16* td, s32 s) {
    for (s; s > 0; s--) {
        *td++ = *ta++;
        *td++ = *tb++;
    }
}

extern void Jac_bcopyfast(u32* src, u32* dest, u32 size) {
    u32 copy1, copy2, copy3, copy4;
    for (size = size / (4 * sizeof(u32)); size != 0; size--) {
        copy1 = *src++;
        copy2 = *src++;
        copy3 = *src++;
        copy4 = *src++;
        *dest++ = copy1;
        *dest++ = copy2;
        *dest++ = copy3;
        *dest++ = copy4;
    }
}

extern void Jac_bcopy(void* src, void* dest, size_t size) {
#ifdef TARGET_PC
    /* N64 RSP bcopy must be overlap-safe (delay lines, ring buffers, DMEM slides).
       The original forward-only copy corrupts overlapping regions (dst > src),
       causing audible pops on one channel at frame boundaries. */
    if (size > 0) {
        memmove(dest, src, size);
    }
#else
    u8 alignedSrc, alignedDst;
    u32* usrc;
    u32* udest;

    u8* bsrc = (u8*)src;
    u8* bdest = (u8*)dest;

    alignedSrc = (reinterpret_cast<u32>(bsrc) & 0x03);
    alignedDst = (reinterpret_cast<u32>(bdest) & 0x03);
    if ((alignedSrc) == (alignedDst) && (size & 0x0f) == 0) {
        Jac_bcopyfast((u32*)src, (u32*)dest, (u32)size);
    } else if ((alignedSrc) == (alignedDst) && (size >= 16)) {
        if ((alignedSrc) != 0) {
            for (alignedSrc = 4 - alignedSrc; (alignedSrc) != 0; alignedSrc--) {
                *bdest++ = (u32) * (bsrc)++;
                size--;
            }
        }

        udest = (u32*)bdest;
        usrc = (u32*)bsrc;

        for (; size >= 4; size -= 4) {
            *udest++ = *usrc++;
        }

        if (size != 0) {
            bdest = (u8*)udest;
            bsrc = (u8*)usrc;

            for (; size > 0; size--) {
                *bdest++ = (u32)*bsrc++;
            }
        }
    } else {
        for (; size > 0; size--) {
            *bdest++ = (u32)*bsrc++;
        }
    }
#endif
}

extern void Jac_bzerofast(u32* dest, u32 size) {
    for (size = size / (4 * sizeof(u32)); size != 0; size--) {
        *dest++ = 0;
        *dest++ = 0;
        *dest++ = 0;
        *dest++ = 0;
    }
}

extern void Jac_bzero(void* dest, s32 size) {
    u32* udest;
    u8* bdest = (u8*)dest;
#ifdef TARGET_PC
    u8 alignedbitsDst = CAST_PTR_U32(bdest) & 0x3;
#else
    u8 alignedbitsDst = reinterpret_cast<u32>(bdest) & 0x3;
#endif
    if (alignedbitsDst == 0) {
        if ((size & 0x1f) == 0) {
            DCZeroRange(dest, size);
            return;
        }
        if ((size & 0xf) == 0) {
            Jac_bzerofast((u32*)dest, size);
            return;
        }
    }

    if (size >= 16) {
        if (alignedbitsDst != 0) {
            for (alignedbitsDst = 4 - alignedbitsDst; alignedbitsDst != 0; alignedbitsDst--) {
                *bdest++ = 0;
                size--;
            }
        }

        udest = (u32*)bdest;
        for (; size >= 4; size -= 4) {
            *udest++ = 0;
        }

        if (size != 0) {
            bdest = (u8*)udest;
            for (; size > 0; size--) {
                *bdest++ = 0;
            }
        }
    } else {
        for (; size > 0; size--) {
            *bdest++ = 0;
        }
    }
}
