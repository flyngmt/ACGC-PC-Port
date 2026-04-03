/* pc_gx_texture.c - GC texture format decoders + 2048-entry texture cache */
#include "pc_gx_internal.h"
#include "pc_texture_pack.h"
#include <dolphin/gx/GXEnum.h>
#include <stdlib.h>

static int pc_gx_tlut_force_be(void);
static void decode_rgb5a3_entry(u16 val, u8* r, u8* g, u8* b, u8* a);
static u32 tlut_content_hash(const void* data, int tlut_fmt, int n_entries, int is_be);

/* --- TLUT stale-data detection ---
 * On GC, gsDPLoadTLUT_Dolphin always re-DMA'd palette data from memory.
 * emu64 optimizes by skipping reload when the TLUT address hasn't changed.
 * On PC, the game reuses memory buffers — same address can hold different
 * palette data (e.g., different NPC clothing). We track the first u16 of
 * each TLUT slot to detect content changes and force reloads. */
u16 s_tlut_first_word[16];

/* --- texture cache --- */
#define TEX_CACHE_SIZE 2048

typedef struct {
    uintptr_t data_ptr;
    u16 width;
    u16 height;
    u32 format;
    u32 tlut_name;   /* TLUT slot for CI4/CI8, 0xFFFFFFFF for non-indexed */
    uintptr_t tlut_ptr;
    u32 tlut_hash;   /* FNV-1a of TLUT data + metadata */
    u32 data_hash;   /* FNV-1a of first N bytes */
    GLuint gl_tex;
    u32 wrap_s;
    u32 wrap_t;
    u32 min_filter;
    u8 external;     /* owned by texture pack, don't delete on eviction */
} TexCacheEntry;

/* Bits-per-pixel for each GC texture format (8 for unknown as safe default) */
static int gc_format_bpp(u32 format) {
    switch (format) {
        case GX_TF_I4: case GX_TF_C4: case GX_TF_CMPR: return 4;
        case GX_TF_I8: case GX_TF_IA4: case GX_TF_C8: return 8;
        case GX_TF_IA8: case GX_TF_RGB565: case GX_TF_RGB5A3: return 16;
        case GX_TF_RGBA8: return 32;
        default: return 8;
    }
}

/* FNV-1a hash of texture data to detect buffer reuse with different content.
 * Hashes first 256 + last 256 bytes (or all if <= 512). */
static u32 tex_content_hash(const void* data, int width, int height, u32 format) {
    if (!data) return 0;
    int bpp = gc_format_bpp(format);
    int data_size = (width * height * bpp) / 8;
    const u8* p = (const u8*)data;
    u32 h = 0x811c9dc5u;
    if (data_size <= 512) {
        /* small texture: hash everything */
        for (int i = 0; i < data_size; i++) {
            h ^= p[i];
            h *= 0x01000193u;
        }
    } else {
        /* large texture: sample head + tail */
        for (int i = 0; i < 256; i++) {
            h ^= p[i];
            h *= 0x01000193u;
        }
        for (int i = data_size - 256; i < data_size; i++) {
            h ^= p[i];
            h *= 0x01000193u;
        }
    }
    return h;
}

/* FNV-1a hash of TLUT data + metadata. CI textures need palette identity
 * in the cache key since the same image is often reused with different TLUTs. */
static u32 tlut_content_hash(const void* data, int tlut_fmt, int n_entries, int is_be) {
    if (!data || n_entries <= 0) return 0;
    int bytes = n_entries * 2;
    if (bytes > 512) bytes = 512;
    const u8* p = (const u8*)data;
    u32 h = 0x811c9dc5u;
    for (int i = 0; i < bytes; i++) {
        h ^= p[i];
        h *= 0x01000193u;
    }
    /* mix in metadata to distinguish different TLUT modes */
    h ^= (u32)(tlut_fmt & 0xFF); h *= 0x01000193u;
    h ^= (u32)(n_entries & 0xFFFF); h *= 0x01000193u;
    h ^= (u32)(is_be & 1); h *= 0x01000193u;
    return h;
}

static TexCacheEntry tex_cache[TEX_CACHE_SIZE];
static int tex_cache_count = 0;
static int tex_cache_hits = 0;
static int tex_cache_misses = 0;

/* Linear scan. Fine for <=2048 entries at ~100% hit rate. */
static TexCacheEntry* tex_cache_find(uintptr_t data_ptr, int w, int h, u32 fmt, u32 tlut_name,
                                     uintptr_t tlut_ptr, u32 tlut_hash, u32 data_hash) {
    for (int i = 0; i < tex_cache_count; i++) {
        TexCacheEntry* e = &tex_cache[i];
        if (e->data_ptr == data_ptr && e->width == w && e->height == h &&
            e->format == fmt && e->tlut_name == tlut_name && e->tlut_ptr == tlut_ptr &&
            e->tlut_hash == tlut_hash && e->data_hash == data_hash) {
            return e;
        }
    }
    return NULL;
}

static TexCacheEntry* tex_cache_insert(uintptr_t data_ptr, int w, int h, u32 fmt, u32 tlut_name,
                                       uintptr_t tlut_ptr, u32 tlut_hash, u32 data_hash, GLuint gl_tex) {
    if (tex_cache_count >= TEX_CACHE_SIZE) {
        /* evict oldest half */
        int half = TEX_CACHE_SIZE / 2;
        for (int i = 0; i < half; i++) {
            if (tex_cache[i].gl_tex) {
                for (int s = 0; s < 8; s++) {
                    if (g_gx.gl_textures[s] == tex_cache[i].gl_tex)
                        g_gx.gl_textures[s] = 0;
                }
                if (!tex_cache[i].external)
                    glDeleteTextures(1, &tex_cache[i].gl_tex);
            }
        }
        memmove(&tex_cache[0], &tex_cache[half], (tex_cache_count - half) * sizeof(TexCacheEntry));
        tex_cache_count -= half;
    }
    TexCacheEntry* e = &tex_cache[tex_cache_count++];
    e->data_ptr = data_ptr;
    e->width = (u16)w;
    e->height = (u16)h;
    e->format = fmt;
    e->tlut_name = tlut_name;
    e->tlut_ptr = tlut_ptr;
    e->tlut_hash = tlut_hash;
    e->data_hash = data_hash;
    e->gl_tex = gl_tex;
    e->wrap_s = 0xFFFFFFFF;
    e->wrap_t = 0xFFFFFFFF;
    e->min_filter = 0xFFFFFFFF;
    e->external = 0;
    return e;
}

void pc_gx_texture_cache_invalidate(void) {
    for (int i = 0; i < tex_cache_count; i++) {
        if (tex_cache[i].gl_tex && !tex_cache[i].external) {
            glDeleteTextures(1, &tex_cache[i].gl_tex);
        }
    }
    tex_cache_count = 0;
}

void pc_gx_texture_init(void) {
    tex_cache_count = 0;
    tex_cache_hits = 0;
    tex_cache_misses = 0;
    (void)pc_gx_tlut_force_be();
}

void pc_gx_texture_shutdown(void) {
    pc_gx_texture_cache_invalidate();
    memset(g_gx.gl_textures, 0, sizeof(g_gx.gl_textures));
}

/* --- texture object API --- */

/* PC-side texture object — replaces the u32[] array approach so pointers
 * survive on both 32-bit and 64-bit platforms. */
typedef struct {
    void*  image_ptr;
    u32    width;
    u32    height;
    u32    format;
    u32    wrap_s;
    u32    wrap_t;
    u32    mipmap;
    u32    min_filter;
    u32    mag_filter;
    f32    min_lod;
    f32    max_lod;
    f32    lod_bias;
    u32    bias_clamp;
    u32    edge_lod;
    u32    max_aniso;
    GLuint gl_tex;
    u32    ci_format;
    u32    tlut_name;
} PCTexObj;

typedef struct {
    void*  data;
    u32    format;
    u32    n_entries;
} PCTlutObj;

void GXInitTexObj(void* obj, void* image_ptr, u16 width, u16 height, u32 format,
                  u32 wrap_s, u32 wrap_t, u8 mipmap) {
    PCTexObj* o = (PCTexObj*)obj;
    memset(o, 0, sizeof(PCTexObj));
    o->image_ptr = image_ptr;
    o->width = width;
    o->height = height;
    o->format = format;
    o->wrap_s = wrap_s;
    o->wrap_t = wrap_t;
    o->mipmap = mipmap;
    o->min_filter = 1; /* GX_LINEAR */
    o->mag_filter = 1; /* GX_LINEAR */
}

void GXInitTexObjCI(void* obj, void* image_ptr, u16 width, u16 height, u32 format,
                    u32 wrap_s, u32 wrap_t, u8 mipmap, u32 tlut_name) {
    GXInitTexObj(obj, image_ptr, width, height, format, wrap_s, wrap_t, mipmap);
    PCTexObj* o = (PCTexObj*)obj;
    o->ci_format = format;
    o->tlut_name = tlut_name;
}

void GXInitTexObjData(void* obj, void* image_ptr) {
    PCTexObj* o = (PCTexObj*)obj;
    o->image_ptr = image_ptr;
}

void GXInitTexObjLOD(void* obj, u32 min_filt, u32 mag_filt, f32 min_lod, f32 max_lod,
                     f32 lod_bias, GXBool bias_clamp, GXBool edge_lod, u32 max_aniso) {
    PCTexObj* o = (PCTexObj*)obj;
    o->min_filter = min_filt;
    o->mag_filter = mag_filt;
    o->min_lod = min_lod;
    o->max_lod = max_lod;
    o->lod_bias = lod_bias;
    o->bias_clamp = bias_clamp;
    o->edge_lod = edge_lod;
    o->max_aniso = max_aniso;
}

void GXInitTexObjWrapMode(void* obj, u32 s, u32 t) {
    PCTexObj* o = (PCTexObj*)obj;
    o->wrap_s = s;
    o->wrap_t = t;
}

/* --- GC texture format decoders (tile layout -> linear RGBA8) --- */

/* Read a big-endian u16 (GC textures store 16-bit pixels in BE order) */
static inline u16 read_be16(const u8* p) {
    return (u16)((p[0] << 8) | p[1]);
}

/* I4: 8x8 blocks, 4bpp, each byte = 2 pixels */
static void decode_I4(const u8* src, u8* dst, int w, int h) {
    int bw = (w + 7) / 8, bh = (h + 7) / 8;
    for (int by = 0; by < bh; by++) {
        for (int bx = 0; bx < bw; bx++) {
            for (int y = 0; y < 8; y++) {
                for (int x = 0; x < 8; x += 2) {
                    u8 val = *src++;
                    int px0 = bx * 8 + x, py = by * 8 + y;
                    int px1 = px0 + 1;
                    u8 i0 = (val >> 4) | (val & 0xF0);
                    u8 i1 = (val & 0x0F) | ((val & 0x0F) << 4);
                    if (px0 < w && py < h) {
                        int idx = (py * w + px0) * 4;
                        dst[idx] = dst[idx+1] = dst[idx+2] = i0;
                        dst[idx+3] = i0;
                    }
                    if (px1 < w && py < h) {
                        int idx = (py * w + px1) * 4;
                        dst[idx] = dst[idx+1] = dst[idx+2] = i1;
                        dst[idx+3] = i1;
                    }
                }
            }
        }
    }
}

/* I8: 8x4 blocks, 8bpp */
static void decode_I8(const u8* src, u8* dst, int w, int h) {
    int bw = (w + 7) / 8, bh = (h + 3) / 4;
    for (int by = 0; by < bh; by++) {
        for (int bx = 0; bx < bw; bx++) {
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 8; x++) {
                    u8 val = *src++;
                    int px = bx * 8 + x, py = by * 4 + y;
                    if (px < w && py < h) {
                        int idx = (py * w + px) * 4;
                        dst[idx] = dst[idx+1] = dst[idx+2] = val;
                        dst[idx+3] = val;
                    }
                }
            }
        }
    }
}

/* IA4: 8x4 blocks, high nibble = alpha, low nibble = intensity */
static void decode_IA4(const u8* src, u8* dst, int w, int h) {
    int bw = (w + 7) / 8, bh = (h + 3) / 4;
    for (int by = 0; by < bh; by++) {
        for (int bx = 0; bx < bw; bx++) {
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 8; x++) {
                    u8 val = *src++;
                    int px = bx * 8 + x, py = by * 4 + y;
                    if (px < w && py < h) {
                        u8 a = (val >> 4) | (val & 0xF0);
                        u8 i = (val & 0x0F) | ((val & 0x0F) << 4);
                        int idx = (py * w + px) * 4;
                        dst[idx] = dst[idx+1] = dst[idx+2] = i; dst[idx+3] = a;
                    }
                }
            }
        }
    }
}

/* IA8: 4x4 blocks, 16bpp, alpha byte + intensity byte per pixel */
static void decode_IA8(const u8* src, u8* dst, int w, int h) {
    int bw = (w + 3) / 4, bh = (h + 3) / 4;
    for (int by = 0; by < bh; by++) {
        for (int bx = 0; bx < bw; bx++) {
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    u8 a = *src++;
                    u8 i = *src++;
                    int px = bx * 4 + x, py = by * 4 + y;
                    if (px < w && py < h) {
                        int idx = (py * w + px) * 4;
                        dst[idx] = dst[idx+1] = dst[idx+2] = i; dst[idx+3] = a;
                    }
                }
            }
        }
    }
}

/* RGB565: 4x4 blocks, 16bpp */
static void decode_RGB565(const u8* src, u8* dst, int w, int h) {
    int bw = (w + 3) / 4, bh = (h + 3) / 4;
    for (int by = 0; by < bh; by++) {
        for (int bx = 0; bx < bw; bx++) {
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    u16 val = (src[0] << 8) | src[1]; src += 2;
                    int px = bx * 4 + x, py = by * 4 + y;
                    if (px < w && py < h) {
                        u8 r = ((val >> 11) & 0x1F) * 255 / 31;
                        u8 g = ((val >> 5) & 0x3F) * 255 / 63;
                        u8 b = (val & 0x1F) * 255 / 31;
                        int idx = (py * w + px) * 4;
                        dst[idx] = r; dst[idx+1] = g; dst[idx+2] = b; dst[idx+3] = 255;
                    }
                }
            }
        }
    }
}

/* RGB5A3: 4x4 blocks, 16bpp. Bit 15=1: RGB555 opaque, bit 15=0: ARGB3444 */
static void decode_RGB5A3(const u8* src, u8* dst, int w, int h) {
    int bw = (w + 3) / 4, bh = (h + 3) / 4;
    for (int by = 0; by < bh; by++) {
        for (int bx = 0; bx < bw; bx++) {
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                    u16 val = (src[0] << 8) | src[1]; src += 2;
                    int px = bx * 4 + x, py = by * 4 + y;
                    if (px < w && py < h) {
                        int idx = (py * w + px) * 4;
                        decode_rgb5a3_entry(val, &dst[idx], &dst[idx+1], &dst[idx+2], &dst[idx+3]);
                    }
                }
            }
        }
    }
}

/* RGBA8: 4x4 blocks, 32bpp. Two passes per block: AR then GB (64 bytes total) */
static void decode_RGBA8(const u8* src, u8* dst, int w, int h) {
    int bw = (w + 3) / 4, bh = (h + 3) / 4;
    for (int by = 0; by < bh; by++) {
        for (int bx = 0; bx < bw; bx++) {
            u8 ar[16][2]; /* AR pass */
            for (int i = 0; i < 16; i++) {
                ar[i][0] = *src++;
                ar[i][1] = *src++;
            }
            for (int i = 0; i < 16; i++) { /* GB pass */
                int x = i % 4, y = i / 4;
                int px = bx * 4 + x, py = by * 4 + y;
                u8 g = *src++;
                u8 b = *src++;
                if (px < w && py < h) {
                    int idx = (py * w + px) * 4;
                    dst[idx] = ar[i][1];
                    dst[idx+1] = g;
                    dst[idx+2] = b;
                    dst[idx+3] = ar[i][0];
                }
            }
        }
    }
}

/* CMPR (S3TC/DXT1): 8x8 super-blocks of 2x2 sub-blocks, each sub is 4x4 DXT1 */
static void decode_CMPR(const u8* src, u8* dst, int w, int h) {
    int bw = (w + 7) / 8, bh = (h + 7) / 8;
    for (int by = 0; by < bh; by++) {
        for (int bx = 0; bx < bw; bx++) {
            for (int sub = 0; sub < 4; sub++) {
                int sx = (sub & 1) * 4, sy = (sub >> 1) * 4;
                u16 c0 = (src[0] << 8) | src[1]; /* DXT1 block (BE) */
                u16 c1 = (src[2] << 8) | src[3];
                src += 4;
                u8 palette[4][4];
                palette[0][0] = ((c0 >> 11) & 0x1F) * 255 / 31;
                palette[0][1] = ((c0 >> 5) & 0x3F) * 255 / 63;
                palette[0][2] = (c0 & 0x1F) * 255 / 31;
                palette[0][3] = 255;
                palette[1][0] = ((c1 >> 11) & 0x1F) * 255 / 31;
                palette[1][1] = ((c1 >> 5) & 0x3F) * 255 / 63;
                palette[1][2] = (c1 & 0x1F) * 255 / 31;
                palette[1][3] = 255;
                /* interpolated colors */
                if (c0 > c1) {
                    for (int c = 0; c < 3; c++) {
                        palette[2][c] = (2 * palette[0][c] + palette[1][c]) / 3;
                        palette[3][c] = (palette[0][c] + 2 * palette[1][c]) / 3;
                    }
                    palette[2][3] = palette[3][3] = 255;
                } else {
                    for (int c = 0; c < 3; c++)
                        palette[2][c] = (palette[0][c] + palette[1][c]) / 2;
                    palette[2][3] = 255;
                    palette[3][0] = palette[3][1] = palette[3][2] = 0;
                    palette[3][3] = 0;
                }
                for (int y = 0; y < 4; y++) {
                    u8 row = *src++;
                    for (int x = 0; x < 4; x++) {
                        int ci = (row >> (6 - x * 2)) & 3;
                        int px = bx * 8 + sx + x, py = by * 8 + sy + y;
                        if (px < w && py < h) {
                            int idx = (py * w + px) * 4;
                            dst[idx] = palette[ci][0];
                            dst[idx+1] = palette[ci][1];
                            dst[idx+2] = palette[ci][2];
                            dst[idx+3] = palette[ci][3];
                        }
                    }
                }
            }
        }
    }
}

/* Decode a single RGB5A3 value to RGBA8 */
static void decode_rgb5a3_entry(u16 val, u8* r, u8* g, u8* b, u8* a) {
    if (val & 0x8000) { /* RGB555 opaque */
        *r = ((val >> 10) & 0x1F) * 255 / 31;
        *g = ((val >> 5) & 0x1F) * 255 / 31;
        *b = (val & 0x1F) * 255 / 31;
        *a = 255;
    } else { /* ARGB3444 */
        *a = ((val >> 12) & 0x07) * 255 / 7;
        *r = ((val >> 8) & 0x0F) * 255 / 15;
        *g = ((val >> 4) & 0x0F) * 255 / 15;
        *b = (val & 0x0F) * 255 / 15;
    }
}

/* Decode a single RGB565 value to RGBA8 (always opaque) */
static void decode_rgb565_entry(u16 val, u8* r, u8* g, u8* b, u8* a) {
    *r = (u8)(((val >> 11) & 0x1F) * 255 / 31);
    *g = (u8)(((val >> 5) & 0x3F) * 255 / 63);
    *b = (u8)((val & 0x1F) * 255 / 31);
    *a = 255;
}

/* Build a 256-entry RGBA8 palette from TLUT data.
 * is_be=1 for ROM/JSystem data (BE), 0 for emu64 tlutconv output (native LE). */
static void build_palette(const void* tlut_data, int tlut_fmt, int n_entries,
                          u8 palette[256][4], int is_be) {
    /* default: grayscale ramp for missing palette */
    for (int i = 0; i < 256; i++) {
        palette[i][0] = palette[i][1] = palette[i][2] = (u8)i;
        palette[i][3] = 255;
    }
    if (!tlut_data || n_entries <= 0) return;
    if (n_entries > 256) n_entries = 256;

    const u16* pal16 = (const u16*)tlut_data;
    const u8* pal_bytes = (const u8*)tlut_data;
    for (int i = 0; i < n_entries; i++) {
        u16 val;
        if (is_be) {
            val = read_be16(pal_bytes + i * 2);
        } else {
            val = pal16[i];
        }
        if (tlut_fmt == GX_TL_RGB5A3) {
            decode_rgb5a3_entry(val, &palette[i][0], &palette[i][1],
                               &palette[i][2], &palette[i][3]);
        } else if (tlut_fmt == GX_TL_RGB565) {
            decode_rgb565_entry(val, &palette[i][0], &palette[i][1],
                                &palette[i][2], &palette[i][3]);
        } else { /* GX_TL_IA8: high byte = intensity, low byte = alpha */
            if (is_be) {
                palette[i][0] = palette[i][1] = palette[i][2] = (u8)(val >> 8);
                palette[i][3] = (u8)(val & 0xFF);
            } else {
                /* LE read of BE bytes [I,A] swaps them */
                palette[i][0] = palette[i][1] = palette[i][2] = (u8)(val & 0xFF);
                palette[i][3] = (u8)(val >> 8);
            }
        }
    }
}

/* CI4: 8x8 blocks, 4bpp indexed */
static void decode_CI4(const u8* src, u8* dst, int w, int h, const u8 palette[256][4]) {
    int bw = (w + 7) / 8, bh = (h + 7) / 8;
    for (int by = 0; by < bh; by++) {
        for (int bx = 0; bx < bw; bx++) {
            for (int y = 0; y < 8; y++) {
                for (int x = 0; x < 8; x += 2) {
                    u8 val = *src++;
                    int px0 = bx * 8 + x, py = by * 8 + y;
                    int px1 = px0 + 1;
                    int ci0 = (val >> 4) & 0xF;
                    int ci1 = val & 0xF;
                    if (px0 < w && py < h) {
                        int idx = (py * w + px0) * 4;
                        dst[idx] = palette[ci0][0]; dst[idx+1] = palette[ci0][1];
                        dst[idx+2] = palette[ci0][2]; dst[idx+3] = palette[ci0][3];
                    }
                    if (px1 < w && py < h) {
                        int idx = (py * w + px1) * 4;
                        dst[idx] = palette[ci1][0]; dst[idx+1] = palette[ci1][1];
                        dst[idx+2] = palette[ci1][2]; dst[idx+3] = palette[ci1][3];
                    }
                }
            }
        }
    }
}

/* CI8: 8x4 blocks, 8bpp indexed */
static void decode_CI8(const u8* src, u8* dst, int w, int h, const u8 palette[256][4]) {
    int bw = (w + 7) / 8, bh = (h + 3) / 4;
    for (int by = 0; by < bh; by++) {
        for (int bx = 0; bx < bw; bx++) {
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 8; x++) {
                    u8 val = *src++;
                    int px = bx * 8 + x, py = by * 4 + y;
                    if (px < w && py < h) {
                        int idx = (py * w + px) * 4;
                        dst[idx] = palette[val][0]; dst[idx+1] = palette[val][1];
                        dst[idx+2] = palette[val][2]; dst[idx+3] = palette[val][3];
                    }
                }
            }
        }
    }
}

static void decode_gc_texture(const void* src, u8* dst_rgba, int w, int h, u32 fmt,
                              const u8 palette[256][4]) {
    /* transparent fallback for unhandled formats */
    memset(dst_rgba, 0, w * h * 4);

    switch (fmt) {
        case GX_TF_I4:     decode_I4((const u8*)src, dst_rgba, w, h); break;
        case GX_TF_I8:     decode_I8((const u8*)src, dst_rgba, w, h); break;
        case GX_TF_IA4:    decode_IA4((const u8*)src, dst_rgba, w, h); break;
        case GX_TF_IA8:    decode_IA8((const u8*)src, dst_rgba, w, h); break;
        case GX_TF_RGB565: decode_RGB565((const u8*)src, dst_rgba, w, h); break;
        case GX_TF_RGB5A3: decode_RGB5A3((const u8*)src, dst_rgba, w, h); break;
        case GX_TF_RGBA8:  decode_RGBA8((const u8*)src, dst_rgba, w, h); break;
        case GX_TF_C4:     decode_CI4((const u8*)src, dst_rgba, w, h, palette); break;
        case GX_TF_C8:     decode_CI8((const u8*)src, dst_rgba, w, h, palette); break;
        case GX_TF_CMPR:   decode_CMPR((const u8*)src, dst_rgba, w, h); break;
        default:
            break;
    }
}

void GXLoadTexObj(void* obj, u32 id) {
    pc_gx_flush_if_begin_complete();

    if (id >= 8 && id != 0xFF && id < 0x100) return;
    if (id >= 8) return;

    PCTexObj* o = (PCTexObj*)obj;

#ifdef TARGET_PC
    {
        static int tex_diag_frame = 0;
        static int tex_diag_count = 0;
        tex_diag_count++;
        if (0 && tex_diag_frame < 3 && tex_diag_count <= 30) { /* disabled */
            fprintf(stderr, "[TEX] id=%d fmt=0x%x %dx%d ptr=%p tlut=%d",
                    id, o->format, o->width, o->height, o->image_ptr, o->tlut_name);
            if (o->image_ptr) {
                u8* d = (u8*)o->image_ptr;
                fprintf(stderr, " data=[%02x%02x%02x%02x]", d[0], d[1], d[2], d[3]);
            }
            if ((o->format == 8 || o->format == 9) && o->tlut_name < 16) {
                fprintf(stderr, " tlut_data=%p entries=%d is_be=%d",
                        g_gx.tlut[o->tlut_name].data,
                        g_gx.tlut[o->tlut_name].n_entries,
                        g_gx.tlut[o->tlut_name].is_be);
                if (g_gx.tlut[o->tlut_name].data) {
                    u16* pal = (u16*)g_gx.tlut[o->tlut_name].data;
                    fprintf(stderr, " pal=[%04x %04x %04x %04x]", pal[0], pal[1], pal[2], pal[3]);
                }
            }
            fprintf(stderr, "\n");
        }
        if (tex_diag_count > 100) { tex_diag_count = 0; tex_diag_frame++; }
    }
#endif
    void* image_ptr = o->image_ptr;
    int width = (int)o->width;
    int height = (int)o->height;
    u32 format = o->format;
    u32 wrap_s = o->wrap_s, wrap_t = o->wrap_t;
    u32 tlut_key = (format == GX_TF_C4 || format == GX_TF_C8) ? o->tlut_name : 0xFFFFFFFF;
    uintptr_t tlut_ptr_key = 0;
    u32 tlut_hash_key = 0;
    u32 filter_mode = o->min_filter;

    if (format == GX_TF_C4 || format == GX_TF_C8) {
        int tlut_name = (int)o->tlut_name;
        if (tlut_name >= 0 && tlut_name < 16 && g_gx.tlut[tlut_name].data) {
            tlut_ptr_key = (uintptr_t)g_gx.tlut[tlut_name].data;
            tlut_hash_key = tlut_content_hash(g_gx.tlut[tlut_name].data,
                                              g_gx.tlut[tlut_name].format,
                                              g_gx.tlut[tlut_name].n_entries,
                                              g_gx.tlut[tlut_name].is_be);
        }
    }

#ifdef PC_ENHANCEMENTS
    /* EFB capture bypass: use full-res FBO texture instead of re-decoding */
    {
        GLuint efb_tex = pc_gx_efb_capture_find((uintptr_t)image_ptr);
        if (efb_tex) {
            glBindTexture(GL_TEXTURE_2D, efb_tex);
            GLenum gl_filter = filter_mode ? GL_LINEAR : GL_NEAREST;
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_filter);
            o->gl_tex = efb_tex;
            g_gx.gl_textures[id] = efb_tex;
            g_gx.tex_obj_w[id] = width;
            g_gx.tex_obj_h[id] = height;
            g_gx.tex_obj_fmt[id] = (int)format;
            DIRTY(PC_GX_DIRTY_TEXTURES);
            return;
        }
    }
#endif

    /* detect when emu64 reuses the same buffer with different data */
    u32 hash = tex_content_hash(image_ptr, width, height, format);

    /* cache lookup */
    uintptr_t data_ptr_key = (uintptr_t)image_ptr;
    TexCacheEntry* cached = tex_cache_find(data_ptr_key, width, height, format, tlut_key,
                                           tlut_ptr_key, tlut_hash_key, hash);
    if (cached) {
        tex_cache_hits++;
        GLuint tex = cached->gl_tex;
        glBindTexture(GL_TEXTURE_2D, tex);

        /* update wrap/filter if changed */
        if (cached->wrap_s != wrap_s || cached->wrap_t != wrap_t) {
            GLenum gl_ws = (wrap_s == 2) ? GL_MIRRORED_REPEAT :
                           (wrap_s == 0) ? GL_CLAMP_TO_EDGE : GL_REPEAT;
            GLenum gl_wt = (wrap_t == 2) ? GL_MIRRORED_REPEAT :
                           (wrap_t == 0) ? GL_CLAMP_TO_EDGE : GL_REPEAT;
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gl_ws);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gl_wt);
            cached->wrap_s = wrap_s;
            cached->wrap_t = wrap_t;
        }
        if (cached->min_filter != filter_mode) {
            GLenum gl_filter = filter_mode ? GL_LINEAR : GL_NEAREST;
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_filter);
            cached->min_filter = filter_mode;
        }

        o->gl_tex = tex;
        g_gx.gl_textures[id] = tex;
        g_gx.tex_obj_w[id] = width;
        g_gx.tex_obj_h[id] = height;
        g_gx.tex_obj_fmt[id] = (int)format;
        DIRTY(PC_GX_DIRTY_TEXTURES);
        return;
    }

    /* cache miss */
    tex_cache_misses++;

    /* try texture pack replacement before decoding */
    if (pc_texture_pack_active()) {
        const void* tp_tlut = NULL;
        int tp_tlut_entries = 0;
        int tp_tlut_is_be = 1;
        if ((format == GX_TF_C4 || format == GX_TF_C8)) {
            int tlut_name = (int)o->tlut_name;
            if (tlut_name >= 0 && tlut_name < 16 && g_gx.tlut[tlut_name].data) {
                tp_tlut = g_gx.tlut[tlut_name].data;
                tp_tlut_entries = g_gx.tlut[tlut_name].n_entries;
                tp_tlut_is_be = g_gx.tlut[tlut_name].is_be;
            }
        }
        int data_size = (width * height * gc_format_bpp(format)) / 8;
        int hd_w = 0, hd_h = 0;
        GLuint hd_tex = pc_texture_pack_lookup(image_ptr, data_size,
                                               width, height, format,
                                               tp_tlut, tp_tlut_entries, tp_tlut_is_be,
                                               &hd_w, &hd_h);
        if (hd_tex) {
            glBindTexture(GL_TEXTURE_2D, hd_tex);
            GLenum gl_ws = (wrap_s == 2) ? GL_MIRRORED_REPEAT :
                           (wrap_s == 0) ? GL_CLAMP_TO_EDGE : GL_REPEAT;
            GLenum gl_wt = (wrap_t == 2) ? GL_MIRRORED_REPEAT :
                           (wrap_t == 0) ? GL_CLAMP_TO_EDGE : GL_REPEAT;
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gl_ws);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gl_wt);

            TexCacheEntry* entry = tex_cache_insert(data_ptr_key, width, height, format,
                                                    tlut_key, tlut_ptr_key, tlut_hash_key, hash, hd_tex);
            entry->wrap_s = wrap_s;
            entry->wrap_t = wrap_t;
            entry->min_filter = filter_mode;
            entry->external = 1;

            o->gl_tex = hd_tex;
            g_gx.gl_textures[id] = hd_tex;
            g_gx.tex_obj_w[id] = width;
            g_gx.tex_obj_h[id] = height;
            g_gx.tex_obj_fmt[id] = (int)format;
            DIRTY(PC_GX_DIRTY_TEXTURES);
            return;
        }
    }

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    if (image_ptr && width > 0 && height > 0 && width <= 1024 && height <= 1024) {
        u8* rgba = (u8*)malloc(width * height * 4);
        if (rgba) {
            u8 palette[256][4];
            if (format == GX_TF_C4 || format == GX_TF_C8) {
                int tlut_name = (int)o->tlut_name;
                if (tlut_name >= 0 && tlut_name < 16 && g_gx.tlut[tlut_name].data) {
                    build_palette(g_gx.tlut[tlut_name].data,
                                  g_gx.tlut[tlut_name].format,
                                  g_gx.tlut[tlut_name].n_entries,
                                  palette,
                                  g_gx.tlut[tlut_name].is_be);
                } else {
                    build_palette(NULL, 0, 0, palette, 0);
                }
            } else {
                build_palette(NULL, 0, 0, palette, 0);
            }

            decode_gc_texture(image_ptr, rgba, width, height, format, palette);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                         GL_RGBA, GL_UNSIGNED_BYTE, rgba);
            PC_GL_CHECK("glTexImage2D");
            free(rgba);
        } else {
            u8 white[4] = {255, 255, 255, 255};
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, white);
        }
    } else {
        u8 white[4] = {255, 255, 255, 255};
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, white);
    }

    {
        GLenum gl_filter = filter_mode ? GL_LINEAR : GL_NEAREST;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_filter);
    }

    {
        GLenum gl_ws = (wrap_s == 2) ? GL_MIRRORED_REPEAT :
                       (wrap_s == 0) ? GL_CLAMP_TO_EDGE : GL_REPEAT;
        GLenum gl_wt = (wrap_t == 2) ? GL_MIRRORED_REPEAT :
                       (wrap_t == 0) ? GL_CLAMP_TO_EDGE : GL_REPEAT;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gl_ws);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gl_wt);
    }

    /* insert into cache */
    TexCacheEntry* entry = tex_cache_insert(data_ptr_key, width, height, format, tlut_key,
                                            tlut_ptr_key, tlut_hash_key, hash, tex);
    entry->wrap_s = wrap_s;
    entry->wrap_t = wrap_t;
    entry->min_filter = filter_mode;

    o->gl_tex = tex;
    g_gx.gl_textures[id] = tex;
    g_gx.tex_obj_w[id] = width;
    g_gx.tex_obj_h[id] = height;
    g_gx.tex_obj_fmt[id] = (int)format;
    DIRTY(PC_GX_DIRTY_TEXTURES);
}

u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, GXBool mipmap, u8 max_lod) {
    u32 bpp = (u32)gc_format_bpp(format);
    u32 total = (width * height * bpp) / 8;
    if (mipmap) {
        u32 w = width, h = height;
        for (u8 lod = 1; lod <= max_lod && (w > 1 || h > 1); lod++) {
            if (w > 1) w >>= 1;
            if (h > 1) h >>= 1;
            total += (w * h * bpp) / 8;
        }
    }
    return total;
}

void GXInvalidateTexAll(void) {
    /* no-op: PC cache keys on pointer+format, no TMEM to flush */
}
void GXInvalidateTexRegion(void* region) { (void)region; }

/* --- TLUT --- */

void GXInitTlutObj(void* obj, void* lut, u32 fmt, u16 n_entries) {
    PCTlutObj* o = (PCTlutObj*)obj;
    memset(o, 0, sizeof(PCTlutObj));
    o->data = lut;
    o->format = fmt;
    o->n_entries = n_entries;
}

void GXLoadTlut(void* obj, u32 idx) {
    pc_gx_flush_if_begin_complete();
    if (idx >= 16) return;
    PCTlutObj* o = (PCTlutObj*)obj;
    g_gx.tlut[idx].data = (const void*)o->data;
    g_gx.tlut[idx].format = (int)o->format;
    g_gx.tlut[idx].n_entries = (int)o->n_entries;

    /* Detect if the TLUT is in the executable (native) or ROM (BE) */
    uintptr_t addr = (uintptr_t)o->data;
    if (addr >= pc_image_base && addr < pc_image_end) {
        g_gx.tlut[idx].is_be = 0;
    } else {
        g_gx.tlut[idx].is_be = 1;
    }
}

/* PC_GX_TLUT_MODE env var: "be" forces BE decode for diagnostics */
static int pc_gx_tlut_force_be(void) {
    static int init = 0;
    static int force_be = 0;
    if (!init) {
        const char* mode = getenv("PC_GX_TLUT_MODE");
        if (mode != NULL) {
            if (mode[0] == 'b' || mode[0] == 'B') {
                force_be = 1;
            }
        }
        init = 1;
    }
    return force_be;
}

/* Mark a TLUT slot as native-LE (from emu64 tlutconv) */
void pc_gx_tlut_set_native_le(unsigned int idx) {
    if (idx < 16) {
        if (pc_gx_tlut_force_be()) {
            g_gx.tlut[idx].is_be = 1;
        } else {
            g_gx.tlut[idx].is_be = 0;
        }
    }
}

void GXInitTexCacheRegion(void* region, GXBool is_32b, u32 tmem_even, u32 size_even,
                          u32 tmem_odd, u32 size_odd) {
    (void)region; (void)is_32b; (void)tmem_even; (void)size_even; (void)tmem_odd; (void)size_odd;
}

void* GXSetTexRegionCallback(void* callback) { return NULL; }
void GXInitTlutRegion(void* region, u32 tmem_addr, u32 tlut_size) {
    (void)region; (void)tmem_addr; (void)tlut_size;
}

/* --- accessors --- */
GXBool GXGetTexObjMipMap(const void* obj) { return ((const PCTexObj*)obj)->mipmap != 0; }
u32    GXGetTexObjFmt(const void* obj)    { return ((const PCTexObj*)obj)->format; }
u16    GXGetTexObjHeight(const void* obj) { return (u16)((const PCTexObj*)obj)->height; }
u16    GXGetTexObjWidth(const void* obj)  { return (u16)((const PCTexObj*)obj)->width; }
u32    GXGetTexObjWrapS(const void* obj)  { return ((const PCTexObj*)obj)->wrap_s; }
u32    GXGetTexObjWrapT(const void* obj)  { return ((const PCTexObj*)obj)->wrap_t; }
void*  GXGetTexObjData(const void* obj)   { return ((const PCTexObj*)obj)->image_ptr; }

void GXDestroyTexObj(void* obj) {
    PCTexObj* o = (PCTexObj*)obj;
    /* don't delete GL texture here; cache eviction handles that */
    o->gl_tex = 0;
}

void GXDestroyTlutObj(void* obj) { (void)obj; }
