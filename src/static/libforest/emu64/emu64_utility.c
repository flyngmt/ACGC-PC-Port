#include "libforest/emu64/emu64.hpp"

#include "boot.h"
#include "terminal.h"
#include "MSL_C/w_math.h"

#ifdef TARGET_PC
/* Executable image range from pc_main.c — BSS/data can collide with N64 segments */
extern "C" uintptr_t pc_image_base;
extern "C" uintptr_t pc_image_end;

/* Arena range from pc_os.c — heap pointers in arena also bypass segment resolution */
extern "C" unsigned char* pc_arena_base;
extern "C" unsigned char* pc_arena_end;

#if UINTPTR_MAX > 0xFFFFFFFFu
#include "pc_gbi_ptr.h"

/* === 64-bit seg2k0 ===
 * On 64-bit, real PC pointers are always above 0x0FFFFFFF. N64 segment
 * addresses are always 0x03XXXXXX-0x0FXXXXXX. However, truncated 64-bit
 * pointers (low 32 bits of a real pointer stored in a u32 Gfx field) can
 * fall ANYWHERE in the 32-bit range, including the segment address range.
 *
 * Strategy: first try segment resolution. If the segment base is 0 (unused
 * segment), try recovering the full pointer from the truncated value using
 * the known image/arena base addresses. */
uintptr_t emu64::seg2k0(uintptr_t segadr) {
    /* Full 64-bit pointer — already resolved */
    if (segadr > 0xFFFFFFFFu) return segadr;
    /* Zero — can't recover */
    if (segadr == 0) return 0;

    /* If the address is within the executable image, it's a native pointer */
    if (segadr >= pc_image_base && segadr < pc_image_end) {
        return segadr;
    }

    /* Check if address falls within the main memory arena (JKRHeap, Object_Exchange
       banks, cloth data, etc.).*/
    if (pc_arena_base && segadr >= (uintptr_t)pc_arena_base &&
        segadr < (uintptr_t)pc_arena_end) {
        return segadr;
    }

    /* Try N64 segment resolution first (0x03-0x0F range) */
    if (segadr >= 0x03000000u && segadr <= 0x0FFFFFFFu) {
        uintptr_t seg = (segadr >> 24) & 0xF;
        uintptr_t offset = segadr & 0xFFFFFF;
        if (this->segments[seg] != 0) {
            this->resolved_addresses++;
            return this->segments[seg] + offset;
        }
        /* Segment base is 0 — this might be a truncated PC pointer,
         * not a real segment address. Fall through to recovery. */
    }

    /* Try to recover a full 64-bit pointer from the truncated 32-bit value */
    uintptr_t recovered = pc_gbi_recover_ptr((unsigned int)segadr);
    if (recovered != segadr) {
        /* Successfully recovered — this was a truncated pointer */
        return recovered;
    }

    /* Unrecoverable — return as-is (may crash, handled by VEH/signal) */
    return segadr;
}
#else
/* === 32-bit seg2k0 ===
 * On 32-bit, PC pointers can collide with N64 segment addresses (both in
 * 0x03-0x0F range). On Windows/Linux, use VirtualQuery/mincore + page cache to
 * disambiguate. On other platforms, rely on segment table and image range. */

#if defined(_WIN32) || defined(__linux__)
#ifndef _WIN32
#include <sys/mman.h>
#include <errno.h>
#include <unistd.h>
#endif

/* Page-granularity cache for VirtualQuery/mincore results.
 * Avoids repeated syscalls for addresses in the same page. */
#define SEG2K0_PAGE_CACHE_SIZE 32
static struct { u32 page; u8 committed; } seg2k0_page_cache[SEG2K0_PAGE_CACHE_SIZE];
static int seg2k0_cache_next = 0;

static int seg2k0_is_committed(u32 addr) {
    static long page_size = 0;
    if (page_size == 0) {
#ifdef _WIN32
        page_size = 4096;
#else
        page_size = sysconf(_SC_PAGESIZE);
        if (page_size <= 0) page_size = 4096;
#endif
    }
    u32 page = addr & ~(u32)(page_size - 1);
    for (int i = 0; i < SEG2K0_PAGE_CACHE_SIZE; i++) {
        if (seg2k0_page_cache[i].page == page) {
            return seg2k0_page_cache[i].committed;
        }
    }
    int committed = 0;
#ifdef _WIN32
    MEMORY_BASIC_INFORMATION mbi;
    if (VirtualQuery((void*)(uintptr_t)addr, &mbi, sizeof(mbi)) > 0 && mbi.State == MEM_COMMIT) {
        committed = 1;
    }
#else
    /* Linux: use mincore to check if the page is mapped.
     * mincore(2) returns 0 on success, and sets vec[0] to indicate if the page is resident.
     * If the address is not mapped, it returns -1 with errno=ENOMEM. */
    unsigned char vec[1];
    if (mincore((void*)(uintptr_t)page, (size_t)page_size, vec) == 0) {
        committed = 1;
    } else if (errno != ENOMEM) {
        /* Other error (e.g. invalid pointer) — assume not committed */
        committed = 0;
    }
#endif
    seg2k0_page_cache[seg2k0_cache_next].page = page;
    seg2k0_page_cache[seg2k0_cache_next].committed = (u8)committed;
    seg2k0_cache_next = (seg2k0_cache_next + 1) % SEG2K0_PAGE_CACHE_SIZE;
    return (int)committed;
}
#endif /* _WIN32 || __linux__ */

uintptr_t emu64::seg2k0(uintptr_t segadr) {
    if ((segadr >> 28) != 0 || segadr < 0x03000000) {
        return segadr;
    }

    if (segadr >= pc_image_base && segadr < pc_image_end) {
        return segadr;
    }

    /* Check if address falls within the main memory arena (JKRHeap, Object_Exchange
       banks, cloth data, etc.).*/
    if (pc_arena_base && segadr >= (u32)(uintptr_t)pc_arena_base &&
        segadr < (u32)(uintptr_t)pc_arena_end) {
        return segadr;
    }

    u32 seg = (segadr >> 24) & 0xF;
    u32 offset = segadr & 0xFFFFFF;

    if (this->segments[seg] == 0) {
        return segadr;
    }

    uintptr_t resolved = this->segments[seg] + offset;

#if defined(_WIN32) || defined(__linux__)
    /* Real N64 segment addresses come from GBI macros like SEGMENT_ADDR(seg, offset)
       and always have small offsets (textures, matrices that are never > 512KB).
       PC heap pointers that collide with the segment range have large "offsets"
       (the low 24 bits of an arbitrary address). Use this to discriminate:
       large offset + committed raw address = heap pointer, not segment ref.

       This might be the last memory fix needed.
       */

    /* Large offset (> 512KB) with committed raw address = definitely a heap pointer,
       not a real segment reference. N64 segments never have offsets this large. */
    if (offset > 0x80000 && seg2k0_is_committed(segadr)) {
        return segadr;
    }

    /* Normal segment resolution path */
    if (seg2k0_is_committed((u32)resolved)) {
        /* Segment resolution gave a valid address — use it (normal path) */
        this->resolved_addresses++;
        return resolved;
    }

    if (seg2k0_is_committed((u32)segadr)) {
        return segadr;
    }
#endif /* _WIN32 || __linux__ */

    this->resolved_addresses++;
    return resolved;
}
#endif /* UINTPTR_MAX */
#else
u32 emu64::seg2k0(u32 segadr) {
    u32 k0;

    if ((segadr >> 28) == 0) {
        if (segadr < 0x03000000) {
            this->Printf0(VT_COL(RED, WHITE) "segadr=%08x" VT_RST "\n", segadr);
            this->panic("segadr is over 0x03000000.", __FILE__, 20);
            k0 = segadr + 0x80000000;
        } else {
            k0 = (u32)this->segments[(segadr >> 24) & 0xF] + (segadr & 0xFFFFFF);
        }
        this->resolved_addresses++;
    } else {
        k0 = segadr;
    }

    if ((k0 >> 31) == 0 || k0 < 0x80000000 || k0 >= 0x83000000) {
        this->Printf0("異常なアドレスです。%08x -> %08x\n", segadr, k0);
        this->panic("異常なアドレスです。", __FILE__, 77);
        this->abnormal_addresses++;
    }

    return k0;
}
#endif

/* @unused void guMtxXFMWF(MtxP, float, float, float, float, float, float*, float*, float*, float*) */

/* @unused void guMtxXFM1F(MtxP, float, float, float, float, float*, float*, float*) */

void guMtxXFM1F_dol(MtxP mtx, float x, float y, float z, float* ox, float* oy, float* oz) {
    *ox = mtx[0][0] * x + mtx[0][1] * y + mtx[0][2] * z + mtx[0][3];
    *oy = mtx[1][0] * x + mtx[1][1] * y + mtx[1][2] * z + mtx[1][3];
    *oz = mtx[2][0] * x + mtx[2][1] * y + mtx[2][2] * z + mtx[2][3];
}

void guMtxXFM1F_dol7(MtxP mtx, float x, float y, float z, float* ox, float* oy, float* oz) {
    GC_Mtx inv;

    PSMTXInverse(mtx, inv);
    *ox = inv[0][0] * x + inv[0][1] * y + inv[0][2] * z + inv[0][3];
    *oy = inv[1][0] * x + inv[1][1] * y + inv[1][2] * z + inv[1][3];
    *oz = inv[2][0] * x + inv[2][1] * y + inv[2][2] * z + inv[2][3];
}

void guMtxXFM1F_dol2(MtxP mtx, GXProjectionType type, float x, float y, float z, float* ox, float* oy, float* oz) {
    if (type == GX_PERSPECTIVE) {
        f32 s = -1.0f / z;

        *ox = mtx[0][0] * x * s - mtx[0][2];
        *oy = mtx[1][1] * y * s - mtx[1][2];
        *oz = mtx[2][3] * s - mtx[2][2];
    } else {
        *ox = mtx[0][0] * x + mtx[0][3];
        *oy = mtx[1][1] * y + mtx[1][3];
        *oz = mtx[2][2] * z + mtx[2][3];
    }
}

void guMtxXFM1F_dol2w(MtxP mtx, GXProjectionType type, float x, float y, float z, float* ox, float* oy, float* oz,
                      float* ow) {
    if (type == GX_PERSPECTIVE) {
        *ox = mtx[0][0] * x + mtx[0][2] * z;
        *oy = mtx[1][1] * y + mtx[1][2] * z;
        *oz = mtx[2][3] + mtx[2][2] * z;
        *ow = -z;
    } else {
        *ox = mtx[0][0] * x + mtx[0][3];
        *oy = mtx[1][1] * y + mtx[1][3];
        *oz = mtx[2][2] * z + mtx[2][3];
        *ow = 1.0f;
    }
}

float guMtxXFM1F_dol3(MtxP mtx, GXProjectionType type, float z) {
    if (type == GX_PERSPECTIVE) {
        return -mtx[2][3] / (z + mtx[2][2]);
    } else {
        return (z - mtx[2][3]) / mtx[2][2];
    }
}

void guMtxXFM1F_dol6w(MtxP mtx, GXProjectionType type, float x, float y, float z, float w, float* ox, float* oy,
                      float* oz, float* ow) {
    if (type == GX_PERSPECTIVE) {
        float xScale = mtx[0][0];
        float yScale = mtx[1][1];
        float zScale = mtx[2][2];

        float xRatioScaling = mtx[0][2];
        float yRatioScaling = mtx[1][2];
        float zSkew = mtx[2][3];

        *ox = (yScale * zSkew * (x + xRatioScaling * w)) / (xScale * (yScale * zSkew));
        *oy = (xScale * zSkew * (y + yRatioScaling * w)) / (xScale * (yScale * zSkew));
        *oz = -w;
        *ow = (xScale * yScale * (z + zScale * w)) / (xScale * (yScale * zSkew));
    } else {
        float xScale = mtx[0][0];
        float xSkew = mtx[0][3];

        float yScale = mtx[1][1];
        float ySkew = mtx[1][3];

        float zScale = mtx[2][2];
        float zSkew = mtx[2][3];

        float n = 1.0f / (xScale * yScale * zScale);

        *ox = n * (yScale * zScale * (x - xSkew));
        *oy = n * (zScale * xScale * (y - ySkew));
        *oz = n * (xScale * yScale * (z - zSkew));
        *ow = 1.0f;
    }
}

void guMtxXFM1F_dol6w1(MtxP mtx, GXProjectionType type, float x, float y, float z, float w, float* ox, float* oy,
                       float* oz) {
    if (type == GX_PERSPECTIVE) {
        float xScale = mtx[0][0];
        float yScale = mtx[1][1];
        float zScale = mtx[2][2];

        float xRatioScaling = mtx[0][2];
        float yRatioScaling = mtx[1][2];
        float zSkew = mtx[2][3];

        float temp_f7 = 1.0f / (xScale * yScale * (z + (zScale * w)));

        *ox = temp_f7 * (yScale * zSkew * (x + (xRatioScaling * w)));
        *oy = temp_f7 * (xScale * zSkew * (y + (yRatioScaling * w)));
        *oz = temp_f7 * (yScale * zSkew * xScale * -w);
    } else {
        float translateX = mtx[0][3];
        float translateY = mtx[1][3];
        float translateZ = mtx[2][3];

        float scaleX = mtx[0][0];
        float scaleY = mtx[1][1];
        float scaleZ = mtx[2][2];

        *ox = (x - translateX) / scaleX;
        *oy = (y - translateY) / scaleY;
        *oz = (z - translateZ) / scaleZ;
    }
}

/* @unused void guMtxXFMWL(N64Mtx*, float, float, float, float, float*, float*, float*, float*) */

void guMtxNormalize(GC_Mtx mtx) {
    for (int i = 0; i < 3; i++) {
        float magnitude = sqrtf(mtx[i][0] * mtx[i][0] + mtx[i][1] * mtx[i][1] + mtx[i][2] * mtx[i][2]);

        mtx[i][0] *= 1.0f / magnitude;
        mtx[i][1] *= 1.0f / magnitude;
        mtx[i][2] *= 1.0f / magnitude;
    }
}

/* TODO: Mtx -> N64Mtx, GC_Mtx -> Mtx */
void N64Mtx_to_DOLMtx(const Mtx* n64, MtxP gc) {
    s16* fixed = ((s16*)n64) + 0;
    u16* frac = ((u16*)n64) + 16;
    int i;

    /* N64Mtx_to_DOLMtx conversion verified correct for LE - no diagnostic needed */

    for (i = 0; i < 4; i++) {
#ifdef TARGET_PC
        /* On little-endian, s16 pairs within each int32 are swapped.
           guMtxF2L packs first value in high 16 bits of each int32.
           s16[0] on BE reads high bits (correct), but on LE reads low bits (wrong).
           So swap indices 0<->1 and 2<->3 within each group of 4. */
        gc[0][i] = fastcast_float(&fixed[1]) + fastcast_float(&frac[1]) * (1.0f / 65536.0f);
        gc[1][i] = fastcast_float(&fixed[0]) + fastcast_float(&frac[0]) * (1.0f / 65536.0f);
        gc[2][i] = fastcast_float(&fixed[3]) + fastcast_float(&frac[3]) * (1.0f / 65536.0f);
#else
        gc[0][i] = fastcast_float(&fixed[0]) + fastcast_float(&frac[0]) * (1.0f / 65536.0f);
        gc[1][i] = fastcast_float(&fixed[1]) + fastcast_float(&frac[1]) * (1.0f / 65536.0f);
        gc[2][i] = fastcast_float(&fixed[2]) + fastcast_float(&frac[2]) * (1.0f / 65536.0f);
#endif

        fixed += 4;
        frac += 4;
    }

}

/* @unused my_guMtxL2F(MtxP, const N64Mtx*) */
