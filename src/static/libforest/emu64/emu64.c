#include "libforest/emu64/emu64.hpp"
#include "libforest/emu64.h"

// #include "MSL_C/w_math.h"
#include "libultra/libultra.h"
#include "terminal.h"
#include "boot.h"
#include "libc64/sprintf.h"
#include "dolphin/mtx.h"
#include "dolphin/os/OSFastCast.h"
#include "dolphin/os.h"
// #include "va_args.h"
#include "jsyswrap.h"
#include "dolphin/PPCArch.h"

#ifdef TARGET_PC
#include "pc_platform.h"
extern "C" void pc_gx_flush_if_begin_complete(void);

static jmp_buf pc_dl_crash_jmpbuf;

/* On 64-bit, Gwords.w1 is uintptr_t (at offset 8) while union member structs
 * have their second u32 field at offset 4 (in the padding). So union views
 * can't access w1 data. Use GFX_W1_U32 for reading w1 as u32, and
 * GFX_COMPACT / GFX_COMPACT_P for building a temporary 8-byte buffer that
 * can be cast to union view types (Gsettile, Gsetcolor, etc.). */
#if UINTPTR_MAX > 0xFFFFFFFFu
#define GFX_W1_U32(gfx_ref) ((u32)(gfx_ref).words.w1)
/* Build a packed 8-byte {w0,w1} buffer from a widened Gfx, suitable for
 * casting to any of the original 8-byte union member structs. */
#define GFX_COMPACT(varname, gfx_ptr) \
    u32 varname[2]; \
    varname[0] = (gfx_ptr)->words.w0; \
    varname[1] = (u32)(gfx_ptr)->words.w1
/* Same but from the this->gfx copy */
#define GFX_COMPACT_SELF(varname) \
    u32 varname[2]; \
    varname[0] = this->gfx.words.w0; \
    varname[1] = (u32)this->gfx.words.w1
#else
#define GFX_W1_U32(gfx_ref) ((gfx_ref).words.w1)
#define GFX_COMPACT(varname, gfx_ptr) \
    u32* varname = (u32*)(gfx_ptr)
#define GFX_COMPACT_SELF(varname) \
    u32* varname = (u32*)&this->gfx
#endif
#else
#define GFX_W1_U32(gfx_ref) ((gfx_ref).words.w1)
#define GFX_COMPACT(varname, gfx_ptr) \
    u32* varname = (u32*)(gfx_ptr)
#define GFX_COMPACT_SELF(varname) \
    u32* varname = (u32*)&this->gfx
#endif

// this pragma may be unnecessary
#pragma inline_depth(1024)

// this one is absolutely necessary for a ton of function calls to be inlined
#pragma inline_max_size(10000)

static void guMtxXFM1F_dol(MtxP mtx, float x, float y, float z, float* ox, float* oy, float* oz);
static void guMtxXFM1F_dol7(MtxP mtx, float x, float y, float z, float* ox, float* oy, float* oz);
static void guMtxXFM1F_dol2(MtxP mtx, GXProjectionType type, float x, float y, float z, float* ox, float* oy, float* oz);
static void guMtxXFM1F_dol2w(MtxP mtx, GXProjectionType type, float x, float y, float z, float* ox, float* oy, float* oz,
                      float* ow);
static float guMtxXFM1F_dol3(MtxP mtx, GXProjectionType type, float z);
static void guMtxXFM1F_dol6w(MtxP mtx, GXProjectionType type, float x, float y, float z, float w, float* ox, float* oy,
                      float* oz, float* ow);
void guMtxXFM1F_dol6w1(MtxP mtx, GXProjectionType type, float x, float y, float z, float w, float* ox, float* oy,
                       float* oz);

static aflags_c aflags;
u8 emu64::nChans = 0;
static u8 texture_buffer_data[TEX_BUFFER_DATA_SIZE] ATTRIBUTE_ALIGN(32);
static u8 texture_buffer_bss[TEX_BUFFER_BSS_SIZE] ATTRIBUTE_ALIGN(32);

static tmem_t tmem_map[TMEM_ENTRIES];

static u32 texture_cache_num = 0;
static texture_cache_entry_t texture_cache_list[TEXTURE_CACHE_LIST_SIZE];

static void* texture_cache_alloc(texture_cache_t* cache, u32 size);
static void* texture_cache_data_search(void* addr);
static int texture_cache_data_entry(void* original, void* converted);
static texture_cache_t* texture_cache_select(void* address);

static texture_cache_funcs texture_cache_data_func = {
    &texture_cache_data_search,
    &texture_cache_data_entry,
    &texture_cache_alloc,
};

/* .bss cache functions */
static void* texture_cache_bss_search(void* addr);
static int texture_cache_bss_entry(void* original, void* converted);

static texture_cache_funcs texture_cache_bss_func = {
    &texture_cache_bss_search,
    &texture_cache_bss_entry,
    &texture_cache_alloc,
};

static texture_cache_t texture_cache_data = {
    &texture_cache_data_func,
    &texture_buffer_data[0],
    &texture_buffer_data[sizeof(texture_buffer_data)],
    &texture_buffer_data[0],
    nullptr,
    nullptr,
    FALSE,
    0,
};

static texture_cache_t texture_cache_bss = {
    &texture_cache_bss_func,
    &texture_buffer_bss[0],
    &texture_buffer_bss[sizeof(texture_buffer_bss)],
    &texture_buffer_bss[0],
    nullptr,
    nullptr,
    FALSE,
    0,
};

#include "../src/static/libforest/emu64/emu64_utility.c"

static GXColor black_color = { 0, 0, 0, 0 };
static GXColor white_color = { 255, 255, 255, 255 };

static char* doltexwrapmode[] = { "CLAMP", "REPEAT", "MIRROR", "?" };

static char* dolfmttbl2[4][5] = {
    { "CMPR", "Z", "CI", "IA", "I" },
    { "RGBA?", "Z", "CI", "IA", "I" },
    { "RGB4A3", "YUV", "CI", "IA", "RGB565" },
    { "RGBA8888", "Z", "CI?", "IA?", "RGB?" },
};

static char* dolfmttbl[] = { "I4", "I8", "IA4", "IA8", "RGB565", "RGB5A3", "RGBA8", "CMPR" };

typedef struct {
    u32 value;
    char* name;
    u32 mask;
} GeometryModeParameterInfo;


#define NUM_GEOMETRYMODE_FLAGS 16
static const GeometryModeParameterInfo geomtbl[NUM_GEOMETRYMODE_FLAGS] = {
    { G_ZBUFFER, "G_ZBUFFER", G_ZBUFFER },
    { G_TEXTURE_ENABLE, "G_TEXTURE_ENABLE", G_TEXTURE_ENABLE },
    { G_SHADE, "G_SHADE", G_SHADE },
    { G_SHADING_SMOOTH, "G_SHADING_SMOOTH", G_SHADING_SMOOTH },
    { G_CULL_FRONT, "G_CULL_FRONT", G_CULL_FRONT },
    { G_CULL_BACK, "G_CULL_BACK", G_CULL_BACK },
    { G_FOG, "G_FOG", G_FOG },
    { G_LIGHTING, "G_LIGHTING", G_LIGHTING },
    { G_TEXTURE_GEN, "G_TEXTURE_GEN", G_TEXTURE_GEN },
    { G_TEXTURE_GEN_LINEAR, "G_TEXTURE_GEN_LINEAR", G_TEXTURE_GEN_LINEAR },
    { G_LOD, "G_LOD", G_LOD },
    { G_LIGHTING_POSITIONAL, "G_LIGHTING_POSITIONAL", G_LIGHTING_POSITIONAL },
    { G_DECAL_EQUAL, "G_DECAL_EQUAL", G_DECAL_ALWAYS },
    { G_DECAL_GEQUAL, "G_DECAL_GEQUAL", G_DECAL_ALWAYS },
    { G_DECAL_ALWAYS, "G_DECAL_ALWAYS", G_DECAL_ALWAYS },
    { G_DECAL_SPECIAL, "G_DECAL_SPECIAL", G_DECAL_SPECIAL }
};

typedef struct {
    u32 mask;
    char* enabled;
    char* disabled;
} MatrixInfo;

static const MatrixInfo gmtxtbl[] = {
    { (1 << 2), "G_MTX_PROJECTION", "G_MTX_MODELVIEW" },
    { (1 << 1), "G_MTX_LOAD", "G_MTX_MUL" },
    { (1 << 0), "G_MTX_PUSH", "G_MTX_NOPUSH" },
};

typedef struct {
    const char* name;
    int val;
} OtherModeOpt;

typedef struct {
    char* name;
    int shift;
    int len;
    OtherModeOpt opts[4];
} OthermodeParameterInfo;

static const OthermodeParameterInfo h_tbl[] = {
    {
        "SetAlphaDither",
        4,
        2,
        {
            { "G_AD_PATTERN", 0 << 4 },
            { "G_AD_NOTPATTERN", 1 << 4 },
            { "G_AD_NOISE", 2 << 4 },
            { "G_AD_DISABLE", 3 << 4 },
        },
    },
    {
        "SetColorDither",
        6,
        2,
        {
            { "G_CD_MAGICSQ", 0 << 6 },
            { "G_CD_BAYER", 1 << 6 },
            { "G_CD_NOISE", 2 << 6 },
            { "G_CD_DISABLE", 3 << 6 },
        },
    },
    {
        "SetCombineKey",
        8,
        1,
        {
            { "G_CK_NONE", 0 << 8 },
            { "G_CK_KEY", 1 << 8 },
            { "-1", -1 },
            { "-1", -1 },
        },
    },
    {
        "SetTextureConvert",
        9,
        3,
        {
            { "G_TC_CONV", 0 << 9 },
            { "G_TC_FILTCONV", 5 << 9 },
            { "G_TC_FILT", 6 << 9 },
            { "-1", -1 },
        },
    },
    {
        "SetTextureFilter",
        12,
        2,
        {
            { "G_TF_POINT", 0 << 12 },
            { "G_TF_AVERAGE", 3 << 12 },
            { "G_TF_BILERP", 2 << 12 },
            { "-1", -1 },
        },
    },
    {
        "SetTextureLUT",
        14,
        2,
        {
            { "G_TT_NONE", 0 << 14 },
            { "G_TT_RGBA16", 2 << 14 },
            { "G_TT_IA16", 3 << 14 },
            { "-1", -1 },
        },
    },
    {
        "SetTextureLOD",
        16,
        1,
        {
            { "G_TL_TILE", 0 << 16 },
            { "G_TL_LOD", 1 << 16 },
            { "-1", -1 },
            { "-1", -1 },
        },
    },
    {
        "SetTextureDetail",
        17,
        2,
        {
            { "G_TD_CLAMP", 0 << 17 },
            { "G_TD_SHARPEN", 1 << 17 },
            { "G_TD_DETAIL", 2 << 17 },
            { "-1", -1 },
        },
    },
    {
        "SetTexturePersp",
        19,
        1,
        {
            { "G_TP_PERSP", 1 << 19 },
            { "G_TP_NONE", 0 << 19 },
            { "-1", -1 },
            { "-1", -1 },
        },
    },
    {
        "SetCycleType",
        20,
        2,
        {
            { "G_CYC_1CYCLE", 0 << 20 },
            { "G_CYC_2CYCLE", 1 << 20 },
            { "G_CYC_COPY", 2 << 20 },
            { "G_CYC_FILL", 3 << 20 },
        },
    },
    {
        "PipelineMode",
        23,
        1,
        {
            { "G_PM_1PRIMITIVE", 1 << 23 },
            { "G_PM_NPRIMITIVE", 0 << 23 },
            { "-1", -1 },
            { "-1", -1 },
        },
    },
};

static const OthermodeParameterInfo l_tbl[] = {
    {
        "gsDPSetAlphaCompare",
        0,
        2,
        {
            { "G_AC_NONE", 0 << 0 },
            { "G_AC_THRESHOLD", 1 << 0 },
            { "G_AC_DITHER", 3 << 0 },
            { "-1", -1 },
        },
    },
    {
        "gsDPSetDepthSource",
        2,
        1,
        {
            { "G_ZS_PIXEL", 0 << 2 },
            { "G_ZS_PRIM", 1 << 2 },
            { "-1", -1 },
            { "-1", -1 },
        },
    },
};

#include "../src/static/libforest/emu64/emu64_print.cpp"

/* Helper function to convert N64 texture format to Dolphin format */
__declspec(section ".rodata") const u16 emu64::fmtxtbl[8][4] = {
    { GX_TF_CMPR, -1, GX_TF_RGB5A3, GX_TF_RGBA8 }, /* G_IM_FMT_RGBA */
    { -1, -1, -1, -1 },                            /* G_IM_FMT_YUV */
    { GX_TF_C4, GX_TF_C8, 0xA, -1 },               /* G_IM_FMT_CI */
    { -1, GX_TF_IA4, GX_TF_IA8, -1 },              /* G_IM_FMT_IA */
    { GX_TF_I4, GX_TF_I8, GX_TF_RGB565, -1 },      /* G_IM_FMT_I */
    { GX_TF_CMPR, GX_CTF_A8, GX_TF_RGB5A3, -1 },   /* ?? */
    { -1, GX_TF_Z8, GX_TF_Z16, GX_TF_Z24X8 },      /* ?? */
    { -1, -1, -1, -1 }                             /* ?? */
};

static const u8 tbla[8][2] = {
    { GX_CA_APREV, GX_CA_KONST }, { GX_CA_TEXA, GX_CA_TEXA }, { GX_CA_TEXA, GX_CA_TEXA }, { GX_CA_A1, GX_CA_A1 },
    { GX_CA_RASA, GX_CA_RASA },   { GX_CA_A2, GX_CA_A2 },     { GX_CA_KONST, GX_CA_A0 },  { GX_CA_ZERO, GX_CA_ZERO },
};

static const u8 tblc[32][4] = {
    { GX_CC_CPREV, GX_CC_CPREV, GX_CC_CPREV, GX_CC_CPREV }, { GX_CC_TEXC, GX_CC_TEXC, GX_CC_TEXC, GX_CC_TEXC },
    { GX_CC_TEXC, GX_CC_TEXC, GX_CC_TEXC, GX_CC_TEXC },     { GX_CC_C1, GX_CC_C1, GX_CC_C1, GX_CC_C1 },
    { GX_CC_RASC, GX_CC_RASC, GX_CC_RASC, GX_CC_RASC },     { GX_CC_C2, GX_CC_C2, GX_CC_C2, GX_CC_C2 },
    { GX_CC_ONE, GX_CC_HALF, GX_CC_HALF, GX_CC_ONE },       { GX_CC_HALF, GX_CC_HALF, GX_CC_APREV, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXA, GX_CC_ZERO },     { GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXA, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_A1, GX_CC_ZERO },       { GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASA, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_A2, GX_CC_ZERO },       { GX_CC_ZERO, GX_CC_ZERO, GX_CC_HALF, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_A0, GX_CC_ZERO },       { GX_CC_ZERO, GX_CC_ZERO, GX_CC_HALF, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },     { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },     { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },     { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },     { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },     { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },     { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },     { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },     { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },
};

/* These are set externally during emu64 initialization */
static texture_cache_data_entry_t texture_cache_data_entry_tbl[NUM_TEXTURE_CACHE_DATA];
static int texture_cache_data_entry_num = 0;

extern void emu64_texture_cache_data_entry_set(void* begin, void* end) {
    texture_cache_data_entry_tbl[texture_cache_data_entry_num].start = begin;
    texture_cache_data_entry_tbl[texture_cache_data_entry_num].end = end;
    texture_cache_data_entry_num++;
}

static texture_cache_t* texture_cache_select(void* addr) {
#ifdef TARGET_PC
    /* On PC, always use the main data cache (no GC .data/.bss section distinction) */
    return &texture_cache_data;
#else
    int i;

    if (aflags[AFLAGS_SKIP_TEXTURE_CONV] >= 1 || (addr >= _f_rodata && addr <= _e_data)) {
        return &texture_cache_data;
    }

    for (i = 0; i < texture_cache_data_entry_num; i++) {
        if (addr >= texture_cache_data_entry_tbl[i].start && addr < texture_cache_data_entry_tbl[i].end) {
            return &texture_cache_data;
        }
    }

    return &texture_cache_bss;
#endif
}

static bool texture_cache_is_overflow(texture_cache_t* cache) {
    return cache->is_overflow;
}

static void texture_cache_clear(texture_cache_t* cache) {
    cache->is_overflow = false;
    cache->buffer_current = cache->buffer_start;
}

/* @fabricated */
static u32 texture_cache_get_max_alloc_size(texture_cache_t* cache) {
    return cache->buffer_current - cache->buffer_start;
}

/* @fabricated */
static u32 texture_cache_get_alloc_size(texture_cache_t* cache) {
    return cache->buffer_current - cache->last_alloc_start;
}

/* @fabricated */
static u32 texture_cache_get_free_size(texture_cache_t* cache) {
    return cache->buffer_end - cache->buffer_current;
}

/* @fabricated */
static u32 texture_cache_get_heap_size(texture_cache_t* cache) {
    return cache->buffer_end - cache->buffer_start;
}

static void* texture_cache_alloc(texture_cache_t* cache, u32 size) {
    cache->last_alloc_start = cache->buffer_current;
    cache->last_alloc_end = (u8*)ALIGN_NEXT((uintptr_t)cache->buffer_current + size, 32);

    if (cache->buffer_pos < cache->last_alloc_end - cache->buffer_start) {
        cache->buffer_pos = cache->last_alloc_end - cache->buffer_start;
    }

    if (cache->last_alloc_end > cache->buffer_end) {
        cache->is_overflow = true;
        return nullptr;
    }

    cache->buffer_current = cache->last_alloc_end;
    return cache->last_alloc_start;
}

static void* texture_cache_data_search(void* original_addr) {
    int i;

    for (i = 0; i < texture_cache_num; i++) {
        if (original_addr == texture_cache_list[i].original) {
            return texture_cache_list[i].converted;
        }
    }

    return nullptr;
}

static int texture_cache_data_entry(void* original_addr, void* converted_addr) {
    if (texture_cache_num < TEXTURE_CACHE_LIST_SIZE && original_addr != nullptr && converted_addr != nullptr) {
        texture_cache_list[texture_cache_num].original = original_addr;
        texture_cache_list[texture_cache_num].converted = converted_addr;
        texture_cache_num++;
        return 0;
    }

    texture_cache_data.is_overflow = true;
    return -1;
}

static void* texture_cache_bss_search(void* original_addr) {
    return nullptr;
}

static int texture_cache_bss_entry(void* original_addr, void* converted_addr) {
    return -1;
}

static void texture_cache_list_clear() {
    texture_cache_clear(&texture_cache_data);
    texture_cache_num = 0;
}

extern void emu64_refresh() {
    texture_cache_list_clear();
}

static u16 cvtN64ToDol(int n64_fmt, int n64_bpp) {
    u16 dol = emu64::fmtxtbl[n64_fmt][n64_bpp];
    if (dol == 0xFFFF) {
        dol = GX_TF_I4;
    }

    return dol;
}

// @FAKE - necessary for matching
f32 PsendoArcSinConvert(f32 arcsin) {
    return 2.0f * (int)(0.5f * arcsin);
}

// MATCH_FORCESTRIP static f32 PsendoArcSinConvert(f32 arcsin) {
//     f32 g = 2.0f * (arcsin - 0.5f);
//     g = g * 0.4623f * g * g + g * 0.5377f;

//     return 0.5f + g * 0.5f;
// }

// MATCH_FORCESTRIP static void TextureLinearConvert1(Texture* src, Texture* dst) {
//     int y;
//     int x;

//     for (y = 0; y < dst->height; y++) {
//         for (x = 0; x < dst->width; x++) {
//             f32 arcsin_x = (f32)x / (f32)(dst->width - 1);
//             f32 arcsin_y = (f32)y / (f32)(dst->height - 1);

//             f32 sin_x = PsendoArcSinConvert(arcsin_x);
//             f32 sin_y = PsendoArcSinConvert(arcsin_y);

//             dst->putTexel(x, y, src->getTexel(sin_x * (src->width - 1), sin_y * (src->height - 1)));
//         }
//     }
// }

// MATCH_FORCESTRIP static void* TextureLinearConvert(void* img_p, unsigned int width, unsigned int height,
//                                                    unsigned int fmt, unsigned int bpp) {
//     texture_cache_t* tex_cache = texture_cache_select(NULL);
//     void* conv_img_p = tex_cache->funcs->alloc(tex_cache, 0x1000);
//     Texture src(img_p, width, height, fmt, bpp);
//     Texture dst(conv_img_p, width, height, fmt, bpp);

//     TextureLinearConvert1(&src, &dst);

//     return conv_img_p;
// }



static void emu64_init2(GXRenderModeObj* render_mode) {
    GC_Mtx m;
    int i;

    // __GXSetIndirectMask(0);

    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX2, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD3, GX_TG_MTX2x4, GX_TG_TEX3, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD4, GX_TG_MTX2x4, GX_TG_TEX4, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD5, GX_TG_MTX2x4, GX_TG_TEX5, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD6, GX_TG_MTX2x4, GX_TG_TEX6, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD7, GX_TG_MTX2x4, GX_TG_TEX7, GX_IDENTITY);

    GXSetNumTexGens(1);
    GXClearVtxDesc();
    GXInvalidateVtxCache();
    GXSetLineWidth(6, GX_TO_ZERO);
    GXSetPointSize(6, GX_TO_ZERO);

    GXEnableTexOffsets(GX_TEXCOORD0, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD1, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD2, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD3, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD4, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD5, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD6, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD7, GX_FALSE, GX_FALSE);

    PSMTXIdentity(m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXLoadNrmMtxImm(m, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXLoadTexMtxImm(m, GX_IDENTITY, GX_MTX3x4);

    GXSetViewport(0.0f, 0.0f, render_mode->fbWidth, render_mode->xfbHeight, 0.0f, 1.0f);
    GXSetCoPlanar(GX_FALSE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetClipMode(GX_CLIP_ENABLE);
    GXSetScissor(0, 0, render_mode->fbWidth, render_mode->efbHeight);
    GXSetScissorBoxOffset(0, 0);
    GXSetNumChans(0);

    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR0A0, black_color);
    GXSetChanMatColor(GX_COLOR0A0, white_color);

    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR1A1, black_color);
    GXSetChanMatColor(GX_COLOR1A1, white_color);

    GXInvalidateTexAll();

    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD2, GX_TEXMAP2, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD3, GX_TEXMAP3, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE4, GX_TEXCOORD4, GX_TEXMAP4, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE5, GX_TEXCOORD5, GX_TEXMAP5, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE6, GX_TEXCOORD6, GX_TEXMAP6, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE7, GX_TEXCOORD7, GX_TEXMAP7, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE8, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE9, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE10, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE11, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE12, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE13, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE14, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE15, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);

    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z8, 0);

    for (i = 0; i < GX_MAX_TEVSTAGE; i++) {
        GXSetTevKColorSel((GXTevStageID)i, GX_TEV_KCSEL_1_4);
        GXSetTevKAlphaSel((GXTevStageID)i, GX_TEV_KASEL_1);
        GXSetTevSwapMode((GXTevStageID)i, GX_TEV_SWAP0, GX_TEV_SWAP0);
    }

    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_GREEN, GX_CH_GREEN, GX_CH_GREEN, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);

    for (i = 0; i < GX_MAX_TEVSTAGE; i++) {
        GXSetTevDirect((GXTevStageID)i);
    }

    GXSetNumIndStages(0);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE1, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE2, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE3, GX_ITS_1, GX_ITS_1);

    GXSetFog(GX_FOG_NONE, 0.0f, 1.0f, 0.1f, 1.0f, black_color);
    GXSetFogRangeAdj(GX_FALSE, 0, 0);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetZCompLoc(GX_TRUE);
    GXSetDither(GX_FALSE);
    GXSetDstAlpha(GX_FALSE, 0);
    GXSetFieldMask(GX_TRUE, GX_TRUE);
    GXSetFieldMode(render_mode->field_rendering, (render_mode->xfbHeight * 2 - render_mode->viHeight) == 0 ? GX_TRUE : GX_FALSE);
}

void emu64::emu64_init() {
    bzero(this, sizeof(emu64));
    GXSetCurrentGXThread();
    emu64_init2(&GXNtsc480IntDf);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetPixelFmt(GX_PF_RGBA6_Z24, GX_ZC_LINEAR);
    GXSetDither(GX_TRUE);
    GXInvalidateTexAll();
    GXInvalidateVtxCache();

    static f32 AAnear = -1.0f;
    static f32 AAfar = 1.0f;

    C_MTXOrtho(this->ortho_mtx, 1.0f, -1.0f, -1.0f, 1.0f, AAnear, AAfar);
    PSMTXIdentity(this->perspective_mtx);
    PSMTXIdentity(this->projection_mtx);
    PSMTXIdentity(this->original_projection_mtx);
    PSMTXIdentity(this->position_mtx);
    PSMTXIdentity(this->model_view_mtx_stack[0]);
    PSMTXIdentity(this->position_mtx_stack[0]);
    GXSetProjection(this->ortho_mtx, GX_ORTHOGRAPHIC);
    GXLoadPosMtxImm(this->perspective_mtx, GX_VA_PNMTXIDX);
    GXLoadNrmMtxImm(this->perspective_mtx, GX_VA_PNMTXIDX);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(2);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(2);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

    for (int i = GX_TEVSTAGE2; i < GX_TEVSTAGE8; i++) {
        GXSetTevColorIn((GXTevStageID)i, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
        GXSetTevAlphaIn((GXTevStageID)i, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        GXSetTevOrder((GXTevStageID)i, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevColorOp((GXTevStageID)i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp((GXTevStageID)i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    }

    GXSetCurrentMtx(GX_PNMTX0);

    static u8 line_width = 6;
    static GXTexOffset tex_offsets = GX_TO_ZERO;

    GXSetLineWidth(line_width - 1, tex_offsets);

    static u8 black_texture[] ATTRIBUTE_ALIGN(32) = { 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
                                  0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
                                  0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88 };

    for (u32 i = GX_TEXMAP0; i < GX_MAX_TEXMAP; i++) {
        GXInitTexObj(&this->tex_objs[i], black_texture, 8, 4, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXLoadTexObj(&this->tex_objs[i], (GXTexMapID)i);
    }

    texture_cache_bss.is_overflow = false;
    texture_cache_bss.buffer_current = texture_cache_bss.buffer_start;

    int overflow = texture_cache_data.is_overflow;
    if (overflow) {
        texture_cache_data.is_overflow = false;
        texture_cache_data.buffer_current = texture_cache_data.buffer_start;
        texture_cache_num = 0;
    }

    bzero(tmem_map, sizeof(tmem_map));

    this->dirty_flags[EMU64_DIRTY_FLAG_PRIM_COLOR] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_ENV_COLOR] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_BLEND_COLOR] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_FOG] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_FILL_COLOR] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_FILL_TEV_COLOR] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_TEX] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_POSITION_MTX] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_COMBINE] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_OTHERMODE_HIGH] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_OTHERMODE_LOW] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_GEOMETRYMODE] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_PROJECTION_MTX] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_LIGHTS] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_LIGHTING] = true;

    this->tex_edge_alpha = 144;
    this->texture_scale_s = 32.0f;
    this->texture_scale_t = 32.0f;
}

void emu64::emu64_cleanup() {
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
}

__declspec(weak) inline void get_blk_wd_ht(unsigned int siz, unsigned int* blk_wd, unsigned int* blk_ht) {
    static const u8 blk_tbl[4][2] = {
        { 8, 8 }, // G_IM_SIZ_4b
        { 8, 4 }, // G_IM_SIZ_8b
        { 4, 4 }, // G_IM_SIZ_16b
        { 4, 4 }  // G_IM_SIZ_32b
    };

    *blk_wd = blk_tbl[siz][0];
    *blk_ht = blk_tbl[siz][1];
}

void emu64::printInfo() {
    int i;

    // Display DL stack %d level.
    this->Printf0("DLスタック表示 %d level\n", this->DL_stack_level);
    for (i = 0; i < this->DL_stack_level; i++) {
        this->Printf0("%d %08x %08x\n", i, this->DL_stack[i], convert_partial_address(this->DL_stack[i]));
    }

    // Display last 16 DLs.
    this->Printf0("最終16DL表示\n");
    for (i = 0; i < DL_HISTORY_COUNT; i++) {
        Gfx* gfx = this->dl_history[(i + this->dl_history_start) % DL_HISTORY_COUNT];

        // Print out the raw Gfx command
        this->Printf0("%016llx ", gfx->force_structure_alignment);
        // Convert the second word to resolve the RAM address if it's a segment
        this->Printf0(" %08x\n", convert_partial_address(gfx->words.w1));
    }

    // Display segment table.
    this->Printf0("セグメントテーブル表示\n");
    for (i = 0; i < EMU64_NUM_SEGMENTS; i++) {
        this->Printf0("%2d %08x %08x\n", i, this->segments[i], convert_partial_address(this->segments[i]));
    }
}

// @HACK
// #pragma dont_inline on
void emu64::panic(char* msg, char* file, int line) {
    if (file) {
        this->Printf0(VT_COL(RED, WHITE) "emu64 PANIC!! in %s line %d" VT_RST "\n", file, line);
    } else {
        this->Printf0(VT_COL(RED, WHITE) "emu64 PANIC!!" VT_RST "\n", file, line);
    }

    if (msg) {
        this->Printf0("%s", msg);
    }
    this->printInfo();
}
// #pragma dont_inline reset

void emu64::emu64_change_ucode(void* ucode_p) {
    if (this->ucode_len != 0) {
        for (int i = 0; i < this->ucode_len; i++) {
            if (ucode_p == this->ucode_info_p[i].ucode_p) {
                this->ucode_type = this->ucode_info_p[i].type;
                return;
            }
        }

        // ### Microcode did not match.
        this->Printf0("### マイクロコードが一致しなかった\n");
        this->err_count++;
        this->num_unknown_ucodes++;
        this->ucode_type = UCODE_TYPE_NONE;
    }
}

extern void get_dol_wd_ht(unsigned int siz, unsigned int in_wd, unsigned int in_ht, unsigned int* wd,
                          unsigned int* ht) {
    unsigned int blk_wd;
    unsigned int blk_ht;

    get_blk_wd_ht(siz, &blk_wd, &blk_ht);

    unsigned int w = blk_wd - 1;
    unsigned int h = blk_ht - 1;

    *wd = in_wd + w & ~w;
    *ht = in_ht + h & ~h;
}

void emu64::texconv_tile(u8* addr, u8* converted_addr, unsigned int wd, unsigned int fmt, unsigned int siz,
    unsigned int start_wd, unsigned int start_ht, unsigned int end_wd, unsigned int end_ht,
    unsigned int line_siz) {
    unsigned int blk_ht;
    unsigned int blk_wd;
    unsigned int blk_y;
    unsigned int blk_x;
    unsigned int y;
    unsigned int y_ofs;

    get_blk_wd_ht(siz, &blk_wd, &blk_ht);

    for (blk_y = start_ht; blk_y < end_ht; blk_y += blk_ht) {
        for (blk_x = start_wd; blk_x < end_wd; blk_x += blk_wd) {
            for (y = 0; y < blk_ht; y++) {
                y_ofs = blk_y + y;

                if (siz == G_IM_SIZ_16b) {
                    if (fmt == G_IM_FMT_RGBA) {
                        unsigned int x_ofs = (blk_x + y_ofs * wd) * sizeof(u16);
                        unsigned int ofs = this->tmem_swap(x_ofs, line_siz);
                        u8* src = (u8*)(addr + ofs);

#ifdef TARGET_PC
                        /* Source N64 RGBA5551 data is BE; read as BE u16.
                         * Write output as BE too so decode_RGB5A3 (which reads
                         * bytes as BE) handles it consistently with ROM data. */
                        {
                            u16 v0 = rgba5551_to_rgb5a3((src[0] << 8) | src[1]);
                            u16 v1 = rgba5551_to_rgb5a3((src[2] << 8) | src[3]);
                            converted_addr[0] = (u8)(v0 >> 8); converted_addr[1] = (u8)v0;
                            converted_addr[2] = (u8)(v1 >> 8); converted_addr[3] = (u8)v1;
                        }
#else
                        *(u16*)(converted_addr + 0) = rgba5551_to_rgb5a3(((u16*)src)[0]);
                        *(u16*)(converted_addr + 2) = rgba5551_to_rgb5a3(((u16*)src)[1]);
#endif

                        ofs = this->tmem_swap(x_ofs + 4, line_siz);
                        src = (u8*)(addr + ofs);
#ifdef TARGET_PC
                        {
                            u16 v0 = rgba5551_to_rgb5a3((src[0] << 8) | src[1]);
                            u16 v1 = rgba5551_to_rgb5a3((src[2] << 8) | src[3]);
                            converted_addr[4] = (u8)(v0 >> 8); converted_addr[5] = (u8)v0;
                            converted_addr[6] = (u8)(v1 >> 8); converted_addr[7] = (u8)v1;
                        }
#else
                        *(u16*)(converted_addr + 4) = rgba5551_to_rgb5a3(((u16*)src)[0]);
                        *(u16*)(converted_addr + 6) = rgba5551_to_rgb5a3(((u16*)src)[1]);
#endif
                    } else if (fmt == G_IM_FMT_IA) {
                        unsigned int x_ofs = (blk_x + y_ofs * wd) * sizeof(u16);
                        unsigned int ofs = this->tmem_swap(x_ofs, line_siz);
                        u8* src = addr + ofs;

                        converted_addr[0] = src[1];
                        converted_addr[1] = src[0];
                        converted_addr[2] = src[3];
                        converted_addr[3] = src[2];

                        x_ofs += 4;
                        ofs = this->tmem_swap(x_ofs, line_siz);
                        src = addr + ofs;

                        converted_addr[4] = src[1];
                        converted_addr[5] = src[0];
                        converted_addr[6] = src[3];
                        converted_addr[7] = src[2];
                    }

                    converted_addr += 8;
                } else if (siz == G_IM_SIZ_8b) {
                    if (fmt == G_IM_FMT_IA) {
                        unsigned int x_ofs = blk_x + y_ofs * wd;
                        unsigned int ofs = this->tmem_swap(x_ofs, line_siz);
                        u32* dst = (u32*)converted_addr;
                        u32* src = (u32*)(addr + ofs);
                        u32 part0 = (src[0] << 4) & 0xF0F0F0F0;
                        u32 part1 = (src[0] >> 4) & 0x0F0F0F0F;

                        dst[0] = part0 + part1;

                        ofs = this->tmem_swap(x_ofs + 4, line_siz);
                        src = (u32*)(addr + ofs);
                        u32 part12 = (src[0] >> 4) & 0x0F0F0F0F;
                        u32 part02 = (src[0] << 4) & 0xF0F0F0F0;
                        dst[1] = part02 + part12;
                    } else {
                        unsigned int x_ofs = blk_x + y_ofs * wd;
                        unsigned int ofs = this->tmem_swap(x_ofs, line_siz);

                        *(u32*)(converted_addr + 0) = *(u32*)(addr + ofs);
                        ofs = this->tmem_swap(x_ofs + 4, line_siz);
                        *(u32*)(converted_addr + 4) = *(u32*)(addr + ofs);
                    }

                    converted_addr += 8;
                } else if (siz == G_IM_SIZ_4b) {
                    unsigned int x_ofs = (blk_x + y_ofs * wd) / 2;
                    unsigned int ofs = this->tmem_swap(x_ofs, line_siz);

                    *(u32*)(converted_addr + 0) = *(u32*)(addr + ofs);
                    converted_addr += 4;
                } else {
                    // G_IM_SIZ_32b is not supported.
                    this->Printf0("G_IM_SIZ_32bはサポートしてません");
                }
            }
        }
    }

    this->texconv_cnt++;
}

void emu64::tlutconv_rgba5551(u16* rgba5551_p, u16* rgb5a3_p, unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {
        *rgb5a3_p++ = rgba5551_to_rgb5a3(*rgba5551_p++);
    }
}

void emu64::tlutconv_ia16(u16* src_ia16_p, u16* dst_ia16_p, unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {
        *(((u8*)dst_ia16_p) + 0) = *(((u8*)src_ia16_p) + 1);
        *(((u8*)dst_ia16_p) + 1) = *(((u8*)src_ia16_p) + 0);
        src_ia16_p++;
        dst_ia16_p++;
    }
}

u8* emu64::texconv_tile_new(u8* addr, unsigned int wd, unsigned int fmt, unsigned int siz, unsigned int start_wd,
                            unsigned int start_ht, unsigned int end_wd, unsigned int end_ht, unsigned int line_siz) {
    if (addr == nullptr) {
        return nullptr;
    }

    texture_cache_t* texture_cache = texture_cache_select(addr);
    u8* converted_addr = (u8*)(*texture_cache->funcs->search)(addr);

    /* Check if we already converted this texture */
    if (converted_addr != nullptr) {
        return converted_addr;
    }

    u32 len = get_dol_tex_siz(siz, (end_wd - start_wd) + 1, (end_ht - start_ht) + 1);

    converted_addr = (u8*)(*texture_cache->funcs->alloc)(texture_cache, len);
    if (converted_addr != nullptr) {
        /* Convert from N64 -> GC */
        this->texconv_tile(addr, converted_addr, wd, fmt, siz, start_wd, start_ht, end_wd, end_ht, line_siz);
        /* Update cache & store entry */
        DCStoreRange(converted_addr, len);
        (*texture_cache->funcs->entry)(addr, converted_addr);
    }

    return converted_addr;
}

u16* emu64::tlutconv_new(u16* tlut, unsigned int tlut_fmt, unsigned int count) {
    u16* converted_tlut;
    u32 len;
    texture_cache_t* texture_cache;

    if (tlut == nullptr) {
        return nullptr;
    }

    if (tlut_fmt == EMU64_TLUT_IA16) {
        this->err_count++;
        return nullptr;
    }

    EMU64_TIMED_SEGMENT_BEGIN();

    texture_cache = texture_cache_select(tlut);
    converted_tlut = (u16*)(*texture_cache->funcs->search)(tlut);

    /* Check if we already converted this texture */
    if (converted_tlut != nullptr) {
        return converted_tlut;
    }

    EMU64_TIMED_SEGMENT_END(texture_cache_select_time);

    len = get_dol_tlut_siz(count);
    converted_tlut = (u16*)(*texture_cache->funcs->alloc)(texture_cache, len);
    if (converted_tlut != nullptr) {
        /* Convert from N64 -> GC */
        this->tlutconv(tlut, converted_tlut, count, tlut_fmt);
        /* Update cache & store entry */
        DCStoreRange(converted_tlut, len);
        (*texture_cache->funcs->entry)(tlut, converted_tlut);
    }

    return converted_tlut;
}

void emu64::tlutconv(u16* src_tlut, u16* dst_tlut, unsigned int count, unsigned int tlut_fmt) {
    if (tlut_fmt == EMU64_TLUT_RGBA5551) {
        this->tlutconv_rgba5551(src_tlut, dst_tlut, count);
    } else {
        this->tlutconv_ia16(src_tlut, dst_tlut, count);
    }
}

/* TODO: @nonmatching */
int emu64::replace_combine_to_tev(Gfx* g) {
    Gsetcombine_new* setcombine = (Gsetcombine_new*)g;
    Gsetcombine_tev sc_tev;
    GXTevColorArg a_color;
    GXTevColorArg b_color;
    GXTevColorArg c_color;
    GXTevColorArg d_color;
    GXTevAlphaArg a_alpha;
    GXTevAlphaArg b_alpha;
    GXTevAlphaArg c_alpha;
    GXTevAlphaArg d_alpha;
    int a;
    int b;
    int c;
    int d;
    int Aa;
    int Ab;
    int Ac;
    int Ad;

    /* TARGET_PC: TEXEL1 substitution disabled — combine_manual() handles multi-texture cases
       (spotlight, fog, inventory oval) with per-stage texture binding instead. */
    if ((setcombine->a0 == G_CCMUX_TEXEL1 || setcombine->b0 == G_CCMUX_TEXEL1 || setcombine->c0 == G_CCMUX_TEXEL1 ||
         setcombine->d0 == G_CCMUX_TEXEL1 || setcombine->c0 == G_CCMUX_TEXEL1_ALPHA) ||
        (setcombine->Aa0 == G_ACMUX_TEXEL1 || setcombine->Ab0 == G_ACMUX_TEXEL1 || setcombine->Ac0 == G_ACMUX_TEXEL1 ||
         setcombine->Ad0 == G_ACMUX_TEXEL1) ||
        (setcombine->a1 == G_CCMUX_TEXEL1 || setcombine->b1 == G_CCMUX_TEXEL1 || setcombine->c1 == G_CCMUX_TEXEL1 ||
         setcombine->d1 == G_CCMUX_TEXEL1 || setcombine->c1 == G_CCMUX_TEXEL1_ALPHA) ||
        (setcombine->Aa1 == G_ACMUX_TEXEL1 || setcombine->Ab1 == G_ACMUX_TEXEL1 || setcombine->Ac1 == G_ACMUX_TEXEL1 ||
         setcombine->Ad1 == G_ACMUX_TEXEL1)) {
        g->setcombine.cmd = G_SETCOMBINE_NOTEV;
        return -1;
    }

    a = setcombine->a0;
    b = setcombine->b0;
    c = setcombine->c0;
    d = setcombine->d0;

    Aa = setcombine->Aa0;
    Ab = setcombine->Ab0;
    Ac = setcombine->Ac0;
    Ad = setcombine->Ad0;

    a_color = (GXTevColorArg)tblc[a][0];
    b_color = (GXTevColorArg)tblc[b][1];
    c_color = (GXTevColorArg)tblc[c][2];
    d_color = (GXTevColorArg)tblc[d][3];

    a_alpha = (GXTevAlphaArg)tbla[Aa][0];
    b_alpha = (GXTevAlphaArg)tbla[Ab][0];
    c_alpha = (GXTevAlphaArg)tbla[Ac][1];
    d_alpha = (GXTevAlphaArg)tbla[Ad][0];

    /* Set TEV color 0 */
    if (b_color == GX_CC_ZERO) {
        sc_tev.a0 = GX_CC_ZERO;
        sc_tev.b0 = a_color;
        sc_tev.c0 = c_color;
        sc_tev.d0 = d_color;
    } else if (b_color == d_color) {
        sc_tev.a0 = b_color;
        sc_tev.b0 = a_color;
        sc_tev.c0 = c_color;
        sc_tev.d0 = GX_CC_ZERO;

    } else {
        g->setcombine.cmd = G_SETCOMBINE_NOTEV;
        return -1;
    }

    /* Set TEV alpha 0 */
    if (b_alpha == TEV_ALPHA_ZERO) {
        sc_tev.Aa0 = TEV_ALPHA_ZERO;
        sc_tev.Ab0 = a_alpha;
        sc_tev.Ac0 = c_alpha;
        sc_tev.Ad0 = d_alpha;
    } else if (b_alpha == d_alpha) {
        sc_tev.Aa0 = b_alpha;
        sc_tev.Ab0 = a_alpha;
        sc_tev.Ac0 = c_alpha;
        sc_tev.Ad0 = TEV_ALPHA_ZERO;
    } else {
        g->setcombine.cmd = G_SETCOMBINE_NOTEV;
        return -1;
    }

    a = setcombine->a1;
    b = setcombine->b1;
    c = setcombine->c1;
    d = setcombine->d1;

    Aa = setcombine->Aa1;
    Ab = setcombine->Ab1;
    Ac = setcombine->Ac1;
    Ad = setcombine->Ad1;

    {
    GXTevColorArg a_color = (GXTevColorArg)tblc[a][0];
    GXTevColorArg b_color = (GXTevColorArg)tblc[b][1];
    GXTevColorArg c_color = (GXTevColorArg)tblc[c][2];
    GXTevColorArg d_color = (GXTevColorArg)tblc[d][3];

    GXTevAlphaArg a_alpha = (GXTevAlphaArg)tbla[Aa][0];
    GXTevAlphaArg b_alpha = (GXTevAlphaArg)tbla[Ab][0];
    GXTevAlphaArg c_alpha = (GXTevAlphaArg)tbla[Ac][1];
    GXTevAlphaArg d_alpha = (GXTevAlphaArg)tbla[Ad][0];

    /* Set TEV color 1 */
    if (b_color == GX_CC_ZERO) {
        sc_tev.a1 = GX_CC_ZERO;
        sc_tev.b1 = a_color;
        sc_tev.c1 = c_color;
        sc_tev.d1 = d_color;
    } else if (b_color == d_color) {
        sc_tev.a1 = b_color;
        sc_tev.b1 = a_color;
        sc_tev.c1 = c_color;
        sc_tev.d1 = GX_CC_ZERO;
    } else {
        g->setcombine.cmd = G_SETCOMBINE_NOTEV;
        return -1;
    }

    /* Set TEV alpha 1 */
    if (b_alpha == TEV_ALPHA_ZERO) {
        sc_tev.Aa1 = TEV_ALPHA_ZERO;
        sc_tev.Ab1 = a_alpha;
        sc_tev.Ac1 = c_alpha;
        sc_tev.Ad1 = d_alpha;
    } else if (b_alpha == d_alpha) {
        sc_tev.Aa1 = b_alpha;
        sc_tev.Ab1 = a_alpha;
        sc_tev.Ac1 = c_alpha;
        sc_tev.Ad1 = TEV_ALPHA_ZERO;
    } else {
        g->setcombine.cmd = G_SETCOMBINE_NOTEV;
        return -1;
    }

    sc_tev.cmd = G_SETCOMBINE_TEV;
    g->words.w0 = ((Gwords*)&sc_tev)->w0;
    g->words.w1 = ((Gwords*)&sc_tev)->w1;
    return 0;
    }
}

int emu64::combine_auto() {
    const Gsetcombine_new* const setcombine = (Gsetcombine_new*)&this->combine_gfx;
    GXTevColorArg color_a;
    GXTevColorArg color_b;
    GXTevColorArg color_c;
    GXTevColorArg color_d;
    GXTevAlphaArg alpha_b;
    GXTevAlphaArg alpha_a;
    GXTevAlphaArg alpha_c;
    GXTevAlphaArg alpha_d;
    int a;
    int b;
    int c;
    int d;
    int Aa;
    int Ab;
    int Ac;
    int Ad;

    int stage;
    int tevstages;
    GXTevStageID color_stages;
    GXTevStageID alpha_stages;

    int two_cycle = (this->othermode_high & G_CYC_2CYCLE) != 0;

    /* TEXEL1 combines have dedicated multi-texture handlers in combine_manual().
       Reject them here so they fall through to combine_manual's switch cases.
       (PC used to substitute TEXEL1→TEXEL0 here, but that destroyed the alpha
       mask information needed for inventory oval, spotlight, etc.) */
    if ((setcombine->a0 == G_CCMUX_TEXEL1 || setcombine->b0 == G_CCMUX_TEXEL1 || setcombine->c0 == G_CCMUX_TEXEL1 ||
         setcombine->d0 == G_CCMUX_TEXEL1 || setcombine->c0 == G_CCMUX_TEXEL1_ALPHA ||
         setcombine->Aa0 == G_ACMUX_TEXEL1 || setcombine->Ab0 == G_ACMUX_TEXEL1 || setcombine->Ac0 == G_ACMUX_TEXEL1 ||
         setcombine->Ad0 == G_ACMUX_TEXEL1) ||
        (two_cycle && (setcombine->a1 == G_CCMUX_TEXEL1 || setcombine->b1 == G_CCMUX_TEXEL1 ||
                       setcombine->c1 == G_CCMUX_TEXEL1 || setcombine->d1 == G_CCMUX_TEXEL1 ||
                       setcombine->c1 == G_CCMUX_TEXEL1_ALPHA) ||
         setcombine->Aa1 == G_ACMUX_TEXEL1 || setcombine->Ab1 == G_ACMUX_TEXEL1 || setcombine->Ac1 == G_ACMUX_TEXEL1 ||
         setcombine->Ad1 == G_ACMUX_TEXEL1)) {
        return -1;
    }

    stage = GX_TEVSTAGE0;

    a = setcombine->a0;
    b = setcombine->b0;
    c = setcombine->c0;
    d = setcombine->d0;

    Aa = setcombine->Aa0;
    Ab = setcombine->Ab0;
    Ac = setcombine->Ac0;
    Ad = setcombine->Ad0;

    color_b = (GXTevColorArg)tblc[a][0]; /* a0 */
    color_a = (GXTevColorArg)tblc[b][1]; /* b0 */
    color_c = (GXTevColorArg)tblc[c][2]; /* c0 */
    color_d = (GXTevColorArg)tblc[d][3]; /* d0 */

    alpha_b = (GXTevAlphaArg)tbla[Aa][0]; /* Aa0 */
    alpha_a = (GXTevAlphaArg)tbla[Ab][0]; /* Ab0 */
    alpha_c = (GXTevAlphaArg)tbla[Ac][1]; /* Ac0 */
    alpha_d = (GXTevAlphaArg)tbla[Ad][0]; /* Ad0 */

    if (color_a == GX_CC_ZERO) {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, color_b, color_c, color_d);
        color_stages = (GXTevStageID)1;
    } else if (color_a == color_d) {
        GXSetTevColorIn(GX_TEVSTAGE0, color_a, color_b, color_c, GX_CC_ZERO);
        color_stages = (GXTevStageID)1;
    } else {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, color_b, color_c, color_d);
        color_stages = (GXTevStageID)1;
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, color_a, color_c, GX_CC_CPREV);
        color_stages = (GXTevStageID)((int)color_stages + 1);
    }

    if (alpha_a == GX_CA_ZERO) {
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, alpha_b, alpha_c, alpha_d);
        alpha_stages = (GXTevStageID)1;
    } else if (alpha_a == alpha_d) {
        GXSetTevAlphaIn(GX_TEVSTAGE0, alpha_a, alpha_b, alpha_c, GX_CA_ZERO);
        alpha_stages = (GXTevStageID)1;
    } else {
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, alpha_b, alpha_c, alpha_d);
        alpha_stages = (GXTevStageID)1;
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, alpha_a, alpha_c, GX_CA_APREV);
        alpha_stages = (GXTevStageID)(alpha_stages + 1);
    }

    if (color_stages > alpha_stages) {
        alpha_stages = color_stages;
    }

    tevstages = alpha_stages;
    for (stage; stage < alpha_stages; stage++) {
        GXSetTevOrder((GXTevStageID)stage, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    }

    if (two_cycle) {
        a = setcombine->a1;
        b = setcombine->b1;
        c = setcombine->c1;
        d = setcombine->d1;

        Aa = setcombine->Aa1;
        Ab = setcombine->Ab1;
        Ac = setcombine->Ac1;
        Ad = setcombine->Ad1;

        GXTevColorArg color_b = (GXTevColorArg)tblc[a][0]; /* a1 */
        GXTevColorArg color_a = (GXTevColorArg)tblc[b][1]; /* b1 */
        GXTevColorArg color_c = (GXTevColorArg)tblc[c][2]; /* c1 */
        GXTevColorArg color_d = (GXTevColorArg)tblc[d][3]; /* d1 */

        GXTevAlphaArg alpha_b = (GXTevAlphaArg)tbla[Aa][0]; /* Aa1 */
        GXTevAlphaArg alpha_a = (GXTevAlphaArg)tbla[Ab][0]; /* Ab1 */
        GXTevAlphaArg alpha_c = (GXTevAlphaArg)tbla[Ac][1]; /* Ac1 */
        GXTevAlphaArg alpha_d = (GXTevAlphaArg)tbla[Ad][0]; /* Ad1 */

        /* @BUG - Is this alpha_c != GX_CC_ZERO check supposed to be alpha_c != GX_CA_ZERO? */
        if (color_c != GX_CC_ZERO || color_d != GX_CC_CPREV || alpha_c != GX_CC_ZERO || alpha_d != GX_CA_APREV) {
            if (color_a == GX_CC_ZERO) {
                GXSetTevColorIn((GXTevStageID)stage, GX_CC_ZERO, color_b, color_c, color_d);
                color_stages = (GXTevStageID)(stage + 1);
            } else if (color_a == color_d) {
                GXSetTevColorIn((GXTevStageID)stage, color_a, color_b, color_c, GX_CC_ZERO);
                color_stages = (GXTevStageID)(stage + 1);
            } else {
                GXSetTevColorIn((GXTevStageID)stage, GX_CC_ZERO, color_b, color_c, color_d);
                color_stages = (GXTevStageID)(stage + 1);
                GXSetTevColorOp(color_stages, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevColorIn(color_stages, GX_CC_ZERO, color_a, color_c, GX_CC_CPREV);
                color_stages = (GXTevStageID)((int)color_stages + 1);
            }

            if (alpha_a == GX_CA_ZERO) {
                GXSetTevAlphaIn((GXTevStageID)stage, GX_CA_ZERO, alpha_b, alpha_c, alpha_d);
                alpha_stages = (GXTevStageID)(stage + 1);
            } else if (alpha_a == alpha_d) {
                GXSetTevAlphaIn((GXTevStageID)stage, alpha_a, alpha_b, alpha_c, GX_CA_ZERO);
                alpha_stages = (GXTevStageID)(stage + 1);
            } else {
                GXSetTevAlphaIn((GXTevStageID)stage, GX_CA_ZERO, alpha_b, alpha_c, alpha_d);
                alpha_stages = (GXTevStageID)(stage + 1);
                GXSetTevAlphaOp(alpha_stages, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(alpha_stages, GX_CA_ZERO, alpha_a, alpha_c, GX_CA_APREV);
                alpha_stages = (GXTevStageID)((int)alpha_stages + 1);
            }

            if (color_stages > alpha_stages) {
                alpha_stages = color_stages;
            }

            tevstages = alpha_stages;
            for (stage; stage < alpha_stages; stage++) {
                GXSetTevOrder((GXTevStageID)stage, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            }
        }
    }

    EMU64_ASSERTLINE(tevstages <= 4, 1934);
    GXSetNumTevStages(tevstages);
    this->combine_auto_cnt[tevstages]++;
    return 0;
}

int emu64::combine_tev() {
    
    if ((u8)this->combine_gfx.setcombine.cmd == G_SETCOMBINE_TEV) {
        int two_cycle = (this->othermode_high & G_CYC_2CYCLE) >> G_MDSFT_CYCLETYPE;
        Gsetcombine_tev combine_tev = *((Gsetcombine_tev*)&this->combine_gfx);

        if (aflags[AFLAGS_FORCE_TEV_COMBINE_MODE] != 0) {
            if (aflags[AFLAGS_FORCE_TEV_COMBINE_MODE] == 1) {
                static u32 c = TEV_SHADE;
                static u32 c1 = TEV_SHADE;
                static u32 a = TEV_ALPHA_SHADE;
                static u32 a1 = TEV_ALPHA_SHADE;

                if (combine_tev.a0 == c) {
                    combine_tev.a0 = c1;
                }

                if (combine_tev.b0 == c) {
                    combine_tev.b0 = c1;
                }

                if (combine_tev.c0 == c) {
                    combine_tev.c0 = c1;
                }

                if (combine_tev.d0 == c) {
                    combine_tev.d0 = c1;
                }

                if (combine_tev.a1 == c) {
                    combine_tev.a1 = c1;
                }

                if (combine_tev.b1 == c) {
                    combine_tev.b1 = c1;
                }

                if (combine_tev.c1 == c) {
                    combine_tev.c1 = c1;
                }

                if (combine_tev.d1 == c) {
                    combine_tev.d1 = c1;
                }

                if (combine_tev.Aa0 == a) {
                    combine_tev.Aa0 = a1;
                }

                if (combine_tev.Ab0 == a) {
                    combine_tev.Ab0 = a1;
                }

                if (combine_tev.Ac0 == a) {
                    combine_tev.Ac0 = a1;
                }

                if (combine_tev.Ad0 == a) {
                    combine_tev.Ad0 = a1;
                }

                if (combine_tev.Aa1 == a) {
                    combine_tev.Aa1 = a1;
                }

                if (combine_tev.Ab1 == a) {
                    combine_tev.Ab1 = a1;
                }

                if (combine_tev.Ac1 == a) {
                    combine_tev.Ac1 = a1;
                }

                if (combine_tev.Ad1 == a) {
                    combine_tev.Ad1 = a1;
                }
            }

            if (aflags[AFLAGS_FORCE_TEV_COMBINE_MODE] == 2) {
                combine_tev.d1 = TEV_ENVIRONMENT;
                combine_tev.Ad1 = TEV_ALPHA_ONE;
            }
        }

        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

        GXSetTevColorIn(GX_TEVSTAGE0, (GXTevColorArg)combine_tev.a0, (GXTevColorArg)combine_tev.b0,
                        (GXTevColorArg)combine_tev.c0, (GXTevColorArg)combine_tev.d0);
        GXSetTevAlphaIn(GX_TEVSTAGE0, (GXTevAlphaArg)combine_tev.Aa0, (GXTevAlphaArg)combine_tev.Ab0,
                        (GXTevAlphaArg)combine_tev.Ac0, (GXTevAlphaArg)combine_tev.Ad0);

        if (two_cycle && ((((Gsetcombine_raw*)&combine_tev)->lower1) != 0xFFF0 || ((((Gsetcombine_raw*)&combine_tev)->lower0) & 0xFFF) != 0x0FF8)) {
            GXSetNumTexGens(2);
            GXSetNumTevStages(2);

            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn(GX_TEVSTAGE1, (GXTevColorArg)combine_tev.a1, (GXTevColorArg)combine_tev.b1,
                            (GXTevColorArg)combine_tev.c1, (GXTevColorArg)combine_tev.d1);
            GXSetTevAlphaIn(GX_TEVSTAGE1, (GXTevAlphaArg)combine_tev.Aa1, (GXTevAlphaArg)combine_tev.Ab1,
                            (GXTevAlphaArg)combine_tev.Ac1, (GXTevAlphaArg)combine_tev.Ad1);

            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
            GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
        } else {
            GXSetNumTexGens(1);
            GXSetNumTevStages(1);

            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
            GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);

            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
            GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
        }

        if (aflags[ALFAGS_TEV_ALPHA_KONST] != 0 || aflags[AFLAGS_WIREFRAME] != 0) {
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
        }
    }
    return 0;
}

#define NUM_COMBINER_HIGHLOW_ERRS 10

/* Combine Manual Macros */

#define gsDPSetCombineLERPInline(a0, b0, c0, d0, Aa0, Ab0, Ac0, Ad0, a1, b1, c1, d1, Aa1, Ab1, Ac1, Ad1)               \
    (((u64)_SHIFTL(G_SETCOMBINE, 24, 8) |                                                                              \
      _SHIFTL(GCCc0w0(G_CCMUX_##a0, G_CCMUX_##c0, G_ACMUX_##Aa0, G_ACMUX_##Ac0) | GCCc1w0(G_CCMUX_##a1, G_CCMUX_##c1), \
              0, 24))                                                                                                  \
     << 32) |                                                                                                          \
        ((u64)(GCCc0w1(G_CCMUX_##b0, G_CCMUX_##d0, G_ACMUX_##Ab0, G_ACMUX_##Ad0) |                                     \
               GCCc1w1(G_CCMUX_##b1, G_ACMUX_##Aa1, G_ACMUX_##Ac1, G_CCMUX_##d1, G_ACMUX_##Ab1, G_ACMUX_##Ad1)))
#define COMBINE_CONSTEXPR(mode0, mode1) (gsDPSetCombineLERPInline(mode0, mode1))

void emu64::combine_manual() {
    static u64 highlow_errs[NUM_COMBINER_HIGHLOW_ERRS];
    static u32 last_highlow;
    u8 orig_combine_cmd = ((Gsetcombine_new*)&this->combine_gfx)->cmd;
    Gsetcombine_new combine_mode_cmd_fixed = *(Gsetcombine_new*)&this->combine_gfx;

    /* replace_combine_to_tev() marks TEXEL1 paths as G_SETCOMBINE_NOTEV.
       Manual combine cases are keyed with G_SETCOMBINE opcode, so normalize
       the command byte before matching the mode payload. */
    if (combine_mode_cmd_fixed.cmd == G_SETCOMBINE_NOTEV) {
        combine_mode_cmd_fixed.cmd = G_SETCOMBINE;
    }

    u64 combine_mode = *(u64*)&combine_mode_cmd_fixed;
#ifdef TARGET_PC
    /* On LE, the struct's two 32-bit words are in opposite order from the
       gsDPSetCombineLERPInline macro (which uses BE word order: w0<<32|w1).
       Swap words so the switch cases match. */
    combine_mode = (combine_mode >> 32) | (combine_mode << 32);
#endif
    switch (combine_mode) {
        case gsDPSetCombineLERPInline(TEXEL0, 0, SHADE, TEXEL0, 0, 0, 0, TEXEL0, SHADE, ENVIRONMENT, PRIMITIVE,
                                      COMBINED, 0, 0, 0, COMBINED): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_RASC, GX_CC_C1, GX_CC_CPREV);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_C2, GX_CC_C1, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            break;
        }
        case gsDPSetCombineLERPInline(NOISE, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0,
                                      SHADE, 0, 0, 0, 0, COMBINED): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_HALF);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_C1, GX_CC_C2);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A1, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            break;
        }
        case gsDPSetCombineLERPInline(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, TEXEL1, PRIMITIVE, 0, 0, 0,
                                      0, COMBINED, 0, 0, 0, COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C2, GX_CC_C1, GX_CC_TEXC, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A1, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A1, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL1, TEXEL0, PRIMITIVE_ALPHA, TEXEL0, SHADE, 0, PRIM_LOD_FRAC, 0, COMBINED, 0,
                                      SHADE, 0, 0, 0, 0, COMBINED): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A1, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE,
                                      ENVIRONMENT, COMBINED, ENVIRONMENT, 0, 0, 0, COMBINED): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A0, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C2, GX_CC_C1, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL0, 0, TEXEL1, 0, TEXEL0, 0, TEXEL1, 0, PRIMITIVE, ENVIRONMENT, COMBINED,
                                      ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C2, GX_CC_C1, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A1, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0,
                                      PRIMITIVE, ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A0, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C2, GX_CC_C1, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A1, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, ENVIRONMENT, TEXEL0,
                                      PRIMITIVE, ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A0, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C2, GX_CC_C1, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_TEXA, GX_CA_A2, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A1, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL0, 0, TEXEL1_ALPHA, 0, TEXEL0, 0, TEXEL1, 0, PRIMITIVE, ENVIRONMENT,
                                      COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXA, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C2, GX_CC_C1, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A1, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(0, 0, 0, PRIMITIVE, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, 0, 0, 0, COMBINED,
                                      COMBINED, 0, PRIMITIVE, 0): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C1);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A1, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL1, TEXEL0, PRIM_LOD_FRAC,
                                      TEXEL0, COMBINED, 0, SHADE, 0, COMBINED, 0, PRIMITIVE, 0): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_C1, GX_CC_C2, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A1, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(0, 0, 0, PRIMITIVE, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, SHADE, 0, COMBINED, 0,
                                      COMBINED, 0, PRIMITIVE, 0): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_C1, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A1, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL1, 0, TEXEL0, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE, 0, SHADE, COMBINED, 0,
                                      0, 0, COMBINED): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_CPREV);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_RASC, GX_CC_C1, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE,
                                      ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A0, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C2, GX_CC_C1, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A1, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL0, 0, TEXEL1_ALPHA, 0, TEXEL0, 0, TEXEL1, 0, PRIMITIVE, 0, SHADE, COMBINED,
                                      COMBINED, 0, PRIM_LOD_FRAC, PRIMITIVE): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXA, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_C1, GX_CC_RASC, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_A1);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL0, 0, TEXEL1_ALPHA, 0, TEXEL0, 0, TEXEL1, 0, PRIMITIVE, 0, SHADE, COMBINED,
                                      COMBINED, 0, PRIM_LOD_FRAC, 0): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXA, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_C1, GX_CC_RASC, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_A1);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0,
                                      0, 0, COMBINED): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A0, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(1, 0, TEXEL0, TEXEL0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, TEXEL1, 0, 0, 0,
                                      COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(PRIMITIVE, 0, PRIM_LOD_FRAC, ENVIRONMENT, 0, 0, 0, TEXEL0, TEXEL1, 0, COMBINED, 0,
                                      0, 0, 0, COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_C1, GX_CC_A0, GX_CC_C2);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(PRIMITIVE, SHADE, PRIM_LOD_FRAC, SHADE, 0, 0, 0, TEXEL0, TEXEL1, 0, COMBINED, 0,
                                      0, 0, 0, COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_C1, GX_CC_A0, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(0, 0, 0, PRIMITIVE, TEXEL0, 0, TEXEL1, 0, 0, 0, 0, COMBINED, COMBINED, 0,
                                      PRIM_LOD_FRAC, 0): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(PRIMITIVE, TEXEL1, TEXEL0, TEXEL1, TEXEL0, 0, TEXEL1, 0, 0, 0, 0, COMBINED, 0, 0,
                                      0, COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_TEXC, GX_CC_C1, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(PRIMITIVE, 0, SHADE, ENVIRONMENT, TEXEL0, 0, TEXEL1, 0, TEXEL0, 0, PRIM_LOD_FRAC,
                                      COMBINED, 0, 0, 0, COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_C1, GX_CC_C2);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A0, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(PRIMITIVE, 0, SHADE, ENVIRONMENT, TEXEL0, 0, TEXEL1, TEXEL1, TEXEL1, 0,
                                      PRIM_LOD_FRAC, COMBINED, 0, 0, 0, COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A0, GX_CC_C2);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_RASC, GX_CC_C1, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_TEXA);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(1, 0, PRIMITIVE, TEXEL0, TEXEL0, 0, TEXEL1, 0, COMBINED, 0, SHADE, TEXEL1, 0, 0,
                                      0, COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_RASC, GX_CC_C1, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL0, 0, ENV_ALPHA, 0, TEXEL0, 0, TEXEL1, 0, PRIMITIVE, 0, PRIMITIVE_ALPHA,
                                      COMBINED, COMBINED, 0, PRIM_LOD_FRAC, 0): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A2, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_C1, GX_CC_A1, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(1, 0, PRIMITIVE, TEXEL0, TEXEL1, 0, TEXEL0, 0, COMBINED, 0, SHADE, TEXEL0,
                                      COMBINED, 0, PRIM_LOD_FRAC, 0): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C1);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_TEXC);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, TEXEL1, TEXEL1, 0, 0, 0,
                                      COMBINED, COMBINED, 0, PRIM_LOD_FRAC, 0): {
            /* Scene 19 spotlight: PRIM/ENV blend by TEX0, alpha = TEX1*(1+TEX0)
             * Stage 0: color = PRIM*TEX0 + ENV*(1-TEX0), alpha = tex0.a
             * Stage 1: color = passthrough, alpha = tex1.a * (1 + prev) */
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C2, GX_CC_C1, GX_CC_TEXC, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_TEXA);
            GXSetCullMode(GX_CULL_NONE);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(1, 0, PRIMITIVE, TEXEL0, TEXEL1, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, TEXEL1, 0,
                                      0, 0, COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_C1, GX_CC_RASC, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A1);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(0, 0, 0, PRIMITIVE, TEXEL0, 0, TEXEL1, 0, 0, 0, 0, COMBINED, COMBINED, 0,
                                      PRIMITIVE, 0): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C1);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A1, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(0, 0, 0, PRIMITIVE, 1, 0, TEXEL0, TEXEL1, 0, 0, 0, COMBINED, COMBINED, 0,
                                      PRIMITIVE, 0): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A1, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A1, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 1, 0, TEXEL0, TEXEL1, COMBINED, 0,
                                      SHADE, TEXEL0, COMBINED, 0, PRIM_LOD_FRAC, PRIMITIVE): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C2, GX_CC_C1, GX_CC_TEXC, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_RASC, GX_CC_CPREV, GX_CC_TEXC);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_A1);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        default: {
            if (aflags[AFLAGS_COMBINE_AUTO] != 0 || this->combine_auto() != 0) {
                if (aflags[AFLAGS_SKIP_COMBINE_TEV] == 2) {
                    last_highlow = 0;
                }

                if (last_highlow < NUM_COMBINER_HIGHLOW_ERRS) {
                    int i;
                    for (i = 0; i < (int)last_highlow; i++) {
                        if (combine_mode == highlow_errs[i]) {
                            goto default_continue;
                        }
                    }

                    highlow_errs[i] = combine_mode;
                    last_highlow++;
                    this->err_count++;
                    /* ### Unsupported combine mode ###\ncase 0x%16llx: // */
                    this->Printf0(VT_COL(YELLOW, BLACK) "### 未対応のコンバインモードです ###\ncase 0x%16llx: // ",
                                    combine_mode);
                    this->print_combine(combine_mode);
                    this->Printf0(VT_RST "\n");
                }
            default_continue:
                /* Default case */
                GXSetNumTevStages(1);
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE);
                GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
                GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            }
            break;
        }
    }
}

void emu64::combine() {
    if ((u8)this->combine_gfx.setcombine.cmd == G_SETCOMBINE_TEV) {
        this->combine_tev();
    } else {
        GXSetNumTexGens(2);
        GXSetNumTevStages(1);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
        GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

        int manual = TRUE;

        /* Try combine_auto first. It will reject TEXEL1 combines (return -1)
           so they fall through to combine_manual's dedicated handlers. */
        if (aflags[AFLAGS_COMBINE_AUTO] && this->combine_auto() == 0) {
            manual = FALSE;
        }

        if (manual) {
            this->combine_manual();
        }

        if (aflags[ALFAGS_TEV_ALPHA_KONST] || aflags[AFLAGS_WIREFRAME]) {
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
        }
    }
}

void emu64::setup_texture_tile(int tile) {
    u16 stride0;
    unsigned int stride;
    unsigned int sizes;
    u32 sizet;
    u16 sizet0;
    unsigned int width;
    unsigned int height;
    unsigned int twd0;
    unsigned int tht0;
    
    void* orig_addr;
    void* converted_addr;
    const Gsettile* settile;
    Gloadblock* loadblock;
    u8* tmem_addr;
    const Gloadtile* loadtile;
    const Gsetimg_new* setimg_new;
    unsigned int w;
    unsigned int h;
    GXTexFmts dol_fmt;
    
    EMU64_TIMED_SEGMENT_BEGIN();
    settile = &this->settile_cmds[tile];
    if (settile->line == 0) {
        return;
    }
    
    u32 tmem = settile->tmem;
    EMU64_ASSERTLINE(tmem / 4 < number(tmem_map), 2756);

    tmem_addr = (u8*)tmem_map[tmem / 4].addr;
    loadblock = &tmem_map[tmem / 4].loadblock;
    loadtile = &tmem_map[tmem / 4].loadtile;
    setimg_new = (Gsetimg_new*)&tmem_map[tmem / 4].setimg2;
    
    if (tmem_addr == nullptr) {
        this->err_count++;
        return;
    }

    int shift = (4 - settile->siz);
    stride0 = settile->line << shift;
    stride = stride0;
    sizes = (u16)(settile->masks != 0 ? (u16)(1 << settile->masks) : (1 << 10));
    sizet = (u16)(settile->maskt != 0 ? (1 << settile->maskt) : (1 << 10));
    
    // sizet = sizet0;
    
    if (setimg_new->setimg2.isDolphin) {
        width = EXPAND_WIDTH(setimg_new->setimg2.wd);
        height = EXPAND_HEIGHT(setimg_new->setimg2.ht);
    } else {
        int wd = setimg_new->setimg2.wd;
        if (wd == 0) {
            wd = loadblock->th;
            if (wd == 0) {
                width = stride;
                height = (u16)((((loadblock->sh) + 1) << (2 - settile->siz)) / stride);
            }
            else {
                width = (u16)(((1 << (15 - settile->siz)) - 1) / wd + 1);
                height = (u16)((((loadblock->sh) + 1) << (2 - settile->siz)) / width);
            }
        }
        else {
            width = (u16)(((wd + 1) << setimg_new->setimg.siz) >> settile->siz);
            height = 0;
        }
    }

    dol_fmt.raw = cvtN64ToDol(settile->fmt, settile->siz);

    if (setimg_new->setimg2.isDolphin) {
        twd0 = width;
        tht0 = height;
        orig_addr = tmem_addr;
        converted_addr = tmem_addr;
    } else {
        if (setimg_new->setimg2.wd == 0) {
            twd0 = width;
            orig_addr = tmem_addr;
            tht0 = height;
            
            if (settile->ct) {
                u32 tlen = this->settilesize_dolphin_cmds[tile].tlen + 1;
                if (tht0 > tlen) {
                    tht0 = tlen;
                }
            }

            if (tht0 > sizet) {
                tht0 = sizet;
            }

            if (tmem_addr == this->texture_info[tile].img_addr) {
                /* Translation: ### This tile is already loaded: %08x\n */
                EMU64_INFOF("### このタイルはすでにロードされています %08x\n", tmem_addr);

                if ((settile->fmt != G_IM_FMT_CI || this->texture_info[tile].tlut_name == settile->palette) &&
                    aflags[AFLAGS_SKIP_TILE_SETUP] != 0) {
                    /* Translation: ### Skip tile setup\n */
                    EMU64_INFO("### タイルの設定はスキップします\n");
                    return;
                }
            }
            
            converted_addr = this->texconv_block_new(tmem_addr, width, tht0, settile->fmt, settile->siz, loadblock->th > 0 ? 0 : settile->line);
        }
        else {
            unsigned int w0;
            unsigned int w1;
            unsigned int h0;
            unsigned int h1;
            unsigned int ofs0;
            
            w0 = ((loadtile->sl << setimg_new->setimg.siz) >> settile->siz) / 4;
            w1 = ((loadtile->sh << setimg_new->setimg.siz) >> settile->siz) / 4;
            h0 = loadtile->tl / 4;
            h1 = loadtile->th / 4;
            
            twd0 = (w1 - w0) + 1;
            tht0 = (h1 - h0) + 1;

            ofs0 = w0 + width * h0;
            orig_addr = tmem_addr + (ofs0 << settile->siz) / 2;
            
            if (orig_addr == this->texture_info[tile].img_addr) {
                /* Translation: ### This tile is already loaded: %08x\n */
                EMU64_INFOF("### このタイルはすでにロードされています %08x\n", tmem_addr);

                if ((settile->fmt != G_IM_FMT_CI || this->texture_info[tile].tlut_name == settile->palette) &&
                    aflags[AFLAGS_SKIP_TILE_SETUP] != 0) {
                    /* Translation: ### Skip tile setup\n */
                    EMU64_INFO("### タイルの設定はスキップします\n");
                    return;
                }
            }

            // issue may be in this inlined function
            converted_addr = this->texconv_tile_new(
                tmem_addr,
                width,
                settile->fmt, settile->siz,
                0, 0,
                w1 - w0, h1 - h0,
                0
            );
        }
    }

    if ((this->geometry_mode & G_TEXTURE_GEN_LINEAR) != 0 && aflags[AFLAGS_DO_TEXTURE_LINEAR_CONVERT] != 0) {
        // converted_addr = TextureLinearConvert(converted_addr, twd0, tht0, settile->fmt, settile->siz);
    }

    /* TODO: Go back and rename a lot of these variables */
    EMU64_INFOF(
        "\n : setup_texture_tile %s %s SIZE0=%dx? SIZE0X=%dx%d SIZE7=%dx%d TILE=%dx%d\n",
        get_fmt_str(settile->fmt),
        get_siz_str(settile->siz),
        stride,
        sizes, sizet,
        width, height,
        twd0, tht0
    );

    if (converted_addr == nullptr) {
        this->Printf0("TEXTURE OVER!!\n");
        this->err_count++;
        return;
    }

    if (setimg_new->setimg2.isDolphin == FALSE) {
        /* Translation: Texture conversion %08x %s %s %dx%d .data %d .bss %d\n */
        EMU64_WARNF(
            "テクスチャ変換 %08x %s %s %dx%d .data %d .bss %d\n",
            tmem_addr,
            get_fmt_str(settile->fmt),
            get_siz_str(settile->siz),
            twd0, tht0,
            (s32)texture_cache_data.buffer_current - (s32)texture_cache_data.buffer_start,
            (s32)texture_cache_bss.buffer_current - (s32)texture_cache_bss.buffer_start
        );
    }

    /* Convert to GC width & height */
    if (setimg_new->setimg2.isDolphin == FALSE) {
        get_dol_wd_ht(settile->siz, twd0, tht0, &w, &h);
    } else {
        w = twd0;
        h = tht0;
    }

    GXTexWrapMode wrap_s = GX_CLAMP;
    GXTexWrapMode wrap_t = GX_CLAMP;

    /* X wrapmode */
    switch (w) {
        case 4:
        case 8:
        case 16:
        case 32:
        case 64:
        case 128:
        case 256:
        case 512:
            if (settile->cs != 0) {
                int tw = EXPAND_WIDTH(this->settilesize_dolphin_cmds[tile].slen);
                if (settile->ms && w < tw) {
                    wrap_s = GX_MIRROR;
                } else {
                    wrap_s = GX_CLAMP;
                }
            }
            else {
                if (settile->ms != 0) {
                    wrap_s = GX_MIRROR;
                } else {
                    wrap_s = GX_REPEAT;
                }
            }
            break;
        default:
            wrap_s = GX_CLAMP;
            break;
    }
    
    /* Y wrapmode */
    switch (h) {
        case 4:
        case 8:
        case 16:
        case 32:
        case 64:
        case 128:
        case 256:
        case 512:
            if (settile->ct != 0) {
                int th = EXPAND_WIDTH(this->settilesize_dolphin_cmds[tile].tlen);
                if (settile->mt && h < th) {
                    wrap_t = GX_MIRROR;
                } else {
                    wrap_t = GX_CLAMP;
                }
            }
            else {
                if (settile->mt != 0) {
                    wrap_t = GX_MIRROR;
                } else {
                    wrap_t = GX_REPEAT;
                }
            }
            break;
        default:
            wrap_t = GX_CLAMP;
            break;
    }

    this->texture_info[tile].img_addr = orig_addr;
    this->texture_info[tile].format = settile->fmt;
    this->texture_info[tile].size = settile->siz;
    this->texture_info[tile].width = w;
    this->texture_info[tile].height = h;

    if (settile->fmt == G_IM_FMT_CI) {
        int pal = settile->palette;
        this->texture_info[tile].tlut_name = pal;
        GXInitTexObjCI(&this->tex_objs[tile], converted_addr, w, h, dol_fmt.citexfmt, wrap_s, wrap_t, GX_FALSE, pal);
        EMU64_INFOF("GXInitTexObjCI tile_no=%d %dx%d pal_no=%d\n", tile, w, h, settile->palette);
    }
    else {
        this->texture_info[tile].tlut_name = 0xFF;
        GXInitTexObj(&this->tex_objs[tile], converted_addr, w, h, dol_fmt.texfmt, wrap_s, wrap_t, GX_FALSE);
        EMU64_INFOF("GXInitTexObj tile_no=%d %dx%d\n", tile, w, h);
    }

    if (((this->othermode_high & G_TF_BILERP) == 0 || (this->othermode_high & G_CYC_COPY) != 0 || (aflags[AFLAGS_TEX_GEN_LOD_MODE] == 1)) && aflags[AFLAGS_TEX_GEN_LOD_MODE] != 2) {
        GXInitTexObjLOD(&this->tex_objs[tile], GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    }
    else if (aflags[AFLAGS_TEX_GEN_LOD_MODE] == 3) {
        GXInitTexObjLOD(&this->tex_objs[tile], GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_TRUE, GX_ANISO_1);
    }

    GXLoadTexObj(&this->tex_objs[tile], (GXTexMapID)tile);
    EMU64_TIMED_SEGMENT_END(setuptex_time);
}

void emu64::blend_mode() {
    if ((this->othermode_low & ZMODE_DEC) == ZMODE_DEC &&
        (this->geometry_mode & G_DECAL_ALL) == (G_DECAL_GEQUAL | G_DECAL_SPECIAL)) {
        GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    } else if ((this->othermode_low & ZMODE_DEC) == ZMODE_DEC &&
               (this->geometry_mode & G_DECAL_ALL) == G_DECAL_SPECIAL) {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_DSTALPHA, GX_BL_INVDSTALPHA, GX_LO_NOOP);
    } else if ((this->othermode_low & (IM_RD | FORCE_BL)) == (IM_RD | FORCE_BL)) {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    } else {
        GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    }
}

void emu64::alpha_compare() {
    u32 gequal =
        ((this->othermode_low & (AA_EN | CVG_X_ALPHA | ALPHA_CVG_SEL)) == (AA_EN | CVG_X_ALPHA | ALPHA_CVG_SEL) &&
         (this->othermode_low & (CVG_DST_SAVE | ZMODE_XLU)) == 0);

    u32 ac_threshold = (this->othermode_low & G_AC_DITHER) == G_AC_THRESHOLD;
    u8 tex_edge_alpha = this->tex_edge_alpha;
    if (aflags[AFLAGS_OVERRIDE_TEXEDGEALPHA] != 0) {
        tex_edge_alpha = (u8)aflags[AFLAGS_OVERRIDE_TEXEDGEALPHA];
    }

    GXCompare comp1 = gequal ? GX_GEQUAL : GX_ALWAYS;
    GXCompare comp0 = ac_threshold ? GX_GEQUAL : GX_ALWAYS;
#ifdef TARGET_PC
    /* On LE, EmuColor.raw is shift-packed (R<<24|G<<16|B<<8|A) but the
       union's rgba struct has byte-swapped fields. Extract alpha via mask. */
    u8 blend_alpha = this->blend_color.raw & 0xFF;
#else
    u8 blend_alpha = this->blend_color.rgba.a;
#endif
    GXSetAlphaCompare(comp0, blend_alpha, GX_AOP_AND, comp1, tex_edge_alpha);
    GXSetZCompLoc(ac_threshold == 0 && !gequal);
}

void emu64::zmode() {
    static u8 compare_enable = GX_FALSE;
    static GXCompare compare_func = GX_NEVER;
    static u8 update_enable = GX_FALSE;
    static u8 zcomp = GX_FALSE;

    if ((this->othermode_low & Z_CMP) != 0) {
        compare_enable = GX_TRUE;
        if ((this->othermode_low & ZMODE_DEC) == ZMODE_DEC) {
            u32 decal_mode = this->geometry_mode & G_DECAL_ALWAYS;

            compare_func =
                (decal_mode == G_DECAL_LEQUAL)
                    ? GX_LEQUAL
                    : ((decal_mode == G_DECAL_GEQUAL) ? GX_GEQUAL
                                                      : ((decal_mode == G_DECAL_EQUAL) ? GX_EQUAL : GX_ALWAYS));
            if (aflags[AFLAGS_DECAL_OFFSET_MODE] != 0) {
                compare_func = (aflags[AFLAGS_DECAL_OFFSET_MODE] == 1)
                                   ? GX_LEQUAL
                                   : ((aflags[AFLAGS_DECAL_OFFSET_MODE] == 2)
                                          ? GX_GEQUAL
                                          : ((aflags[AFLAGS_DECAL_OFFSET_MODE] == 3) ? GX_EQUAL : GX_ALWAYS));
            }

            if ((this->geometry_mode & G_DECAL_SPECIAL) != 0) {
                if (decal_mode == G_DECAL_GEQUAL) {
                    GXSetColorUpdate(GX_FALSE);
                    GXSetAlphaUpdate(GX_TRUE);
                } else if (decal_mode == G_DECAL_LEQUAL) {
                    GXSetColorUpdate(GX_TRUE);
                    GXSetAlphaUpdate(GX_FALSE);
                } else {
                    GXSetColorUpdate(GX_TRUE);
                    GXSetAlphaUpdate(GX_FALSE);
                }
            } else {
                GXSetColorUpdate(GX_TRUE);
                GXSetAlphaUpdate(GX_FALSE);
            }
        } else {
            compare_func = GX_LESS;
        }

        update_enable = (this->othermode_low & Z_UPD) != 0;
        zcomp = false;
    } else {
        if ((this->othermode_low & Z_UPD) != 0) {
            compare_enable = GX_TRUE;
            compare_func = GX_ALWAYS;
            update_enable = GX_TRUE;
            zcomp = false;
        } else {

            compare_enable = GX_FALSE;
            compare_func = GX_ALWAYS;
            update_enable = GX_FALSE;
            zcomp = true;
        }
    }

    if (aflags[AFLAGS_WIREFRAME] != 0) {
        compare_enable = GX_FALSE;
    }

    GXSetZMode(compare_enable, compare_func, update_enable);
}

void emu64::cullmode() {
    GXCullMode cullmode;
    if (aflags[AFLAGS_SET_CULLMODE] == 0) {
        /* Default mapping:
           - GC path keeps historical inverted mapping.
           - PC path uses direct mapping to match OpenGL front/back winding. */
#ifdef TARGET_PC
        switch (this->geometry_mode & G_CULL_BOTH) {
            case G_CULL_BACK:
                cullmode = GX_CULL_BACK;
                break;
            case G_CULL_FRONT:
                cullmode = GX_CULL_FRONT;
                break;
            case G_CULL_BOTH:
                cullmode = GX_CULL_ALL;
                break;
            default:
                cullmode = GX_CULL_NONE;
                break;
        }
#else
        /* Cull modes seem to be inverted between N64 and GC */
        cullmode = (GXCullMode)(((this->geometry_mode >> 8) & (G_CULL_FRONT >> 8)) |
                                ((this->geometry_mode >> 10) & (G_CULL_BACK >> 10)));
#endif
    } else if (aflags[AFLAGS_SET_CULLMODE] == 1) { /* Inverse mapping mode */
        switch (this->geometry_mode & G_CULL_BOTH) {
            case G_CULL_FRONT:
                cullmode = GX_CULL_BACK;
                break;
            case G_CULL_BACK:
                cullmode = GX_CULL_FRONT;
                break;
            case G_CULL_BOTH:
                cullmode = GX_CULL_ALL;
                break;
            default:
                cullmode = GX_CULL_NONE;
                break;
        }
    } else if (aflags[AFLAGS_SET_CULLMODE] == 2) { /* Direct mapping mode */
        switch (this->geometry_mode & G_CULL_BOTH) {
            case G_CULL_BACK:
                cullmode = GX_CULL_BACK;
                break;
            case G_CULL_FRONT:
                cullmode = GX_CULL_FRONT;
                break;
            case G_CULL_BOTH:
                cullmode = GX_CULL_ALL;
                break;
            default:
                cullmode = GX_CULL_NONE;
                break;
        }
    } else { /* Directly set cull mode. 3 = GX_CULL_FRONT, 4 = GX_CULL_BACK, 5 = GX_CULL_ALL */
        cullmode = (GXCullMode)(aflags[AFLAGS_SET_CULLMODE] - 2);
    }

    /* Culling is disabled when 2 tris mode is active */
    if (aflags[AFLAGS_WIREFRAME] != 0) {
        cullmode = GX_CULL_NONE;
    }

    GXSetCullMode(cullmode);
}

void emu64::texture_gen(int tex) {
    // clang-format off
    static const float shift_tbl[] = {
        1.0f,
        2.0f,
        4.0f,
        8.0f,
        16.0f,
        32.0f,
        64.0f,
        128.0f,
        256.0f,
        512.0f,
        1024.0f,
        1.0f / 32.0f, /* 0.03125f */
        1.0f / 16.0f, /* 0.0625f */
        1.0f / 8.0f,  /* 0.125f */
        1.0f / 4.0f,  /* 0.25f */
        1.0f / 2.0f   /* 0.5f */
    };
    // clang-format on

    GC_Mtx mm; /* Model-view matrix */
    GC_Mtx ml; /* Look-at matrix */
    GC_Mtx mf; /* Finalized texture matrix */
    GC_Mtx ms; /* Scale matrix */
    GC_Mtx mt; /* Translation matrix */
    GC_Mtx mn; /* Scale-Translation normalization matrix */

    /* Setup lookat matrix */

    /* LookAt X */
    ml[0][0] = (f32)this->lookAt.x.x / 128.0f; /* 0.0078125f */
    ml[0][1] = (f32)this->lookAt.x.y / 128.0f;
    ml[0][2] = (f32)this->lookAt.x.z / 128.0f;
    ml[0][3] = 0.0f;

    /* LookAt Y */
    ml[1][0] = (f32)this->lookAt.y.x / 128.0f;
    ml[1][1] = (f32)this->lookAt.y.y / 128.0f;
    ml[1][2] = (f32)this->lookAt.y.z / 128.0f;
    ml[1][3] = 0.0f;

    /* LookAt Z */
    ml[2][0] = 0.0f;
    ml[2][1] = 0.0f;
    ml[2][2] = 1.0f;
    ml[2][3] = 0.0f;

    MTXIdentity(mf);

    /* This is dead code, as the aflag to utilize it is only present in DnM+ */
    MTXCopy(this->model_view_mtx_stack[this->mtx_stack_size], mm);
    guMtxNormalize(mm);
    mm[0][3] = 0.0f;
    mm[1][3] = 0.0f;
    mm[2][3] = 0.0f;

    /* Apply look-at and default translation & scale */
    MTXScale(ms, 0.5f, 0.5f, 0.0f);
    MTXTrans(mt, 0.5f, 0.5f, 1.0f);
    MTXConcat(mt, ms, mn);
    MTXConcat(mn, ml, mf);

    /* Apply texture scaling */
    float x = ((64.0f * 32768.0f) / this->texture_scale_s) / 64.0f;
    float y = ((64.0f * 32768.0f) / this->texture_scale_t) / 64.0f;

    MTXScale(ms, x, y, 1.0f); /* 2,097,152 = 2^21, 1/64 = 0.015625 */
    MTXConcat(ms, mf, mf);

    /* Apply texture shift */
    MTXScale(ms, 1.0f / shift_tbl[this->settile_cmds[tex].shifts], 1.0f / shift_tbl[this->settile_cmds[tex].shiftt],
             1.0f);
    MTXConcat(ms, mf, mf);

    /* Apply texture position */
    u16 sl = this->settilesize_dolphin_cmds[tex].sl;
    u16 tl = this->settilesize_dolphin_cmds[tex].tl;
    float x0 = fastcast_float(&sl) / 16.0f;
    float y0 = fastcast_float(&tl) / 16.0f;

    MTXTrans(mt, -x0, -y0, 0.0f);
    MTXConcat(mt, mf, mf);

    /* Convert size to be in units of texture width & height */
    float x1 = 1.0f / fastcast_float(&this->texture_info[tex].width);
    float y1 = 1.0f / fastcast_float(&this->texture_info[tex].height);
    MTXScale(ms, x1, y1, 1.0f);
    MTXConcat(ms, mf, mf);

    /* Load texture */
    GXTexMtx id = (GXTexMtx)(GX_TEXMTX0 + tex * 3);
    GXLoadTexMtxImm(mf, id, GX_MTX3x4);
    GXSetTexCoordGen((GXTexCoordID)tex, GX_TG_MTX3x4, GX_TG_NRM, id);
}

void emu64::texture_matrix() {
    // clang-format off
    static const float shift_tbl[] = {
        1.0f,
        2.0f,
        4.0f,
        8.0f,
        16.0f,
        32.0f,
        64.0f,
        128.0f,
        256.0f,
        512.0f,
        1024.0f,
        1.0f / 32.0f, /* 0.03125f */
        1.0f / 16.0f, /* 0.0625f */
        1.0f / 8.0f,  /* 0.125f */
        1.0f / 4.0f,  /* 0.25f */
        1.0f / 2.0f   /* 0.5f */
    };
    // clang-format on

    EMU64_ASSERTLINE_DEBUG(this, 4036);
    if (this->texture_gfx.on != 0) {
        GC_Mtx m;
        u16 uls0;
        u16 ult0;

        f32 bilerp_adjust; /* bilerp center adjust */
        float uls;
        float ult;
        float lrs;
        float lrt;

        float x32;
        float y32;

        if ((this->texture_adjust_mode == 1 || (this->othermode_high & G_TF_BILERP) == 0 ||
             (this->othermode_high & G_CYC_COPY) != 0 || aflags[AFLAGS_TEX_GEN_LOD_MODE] == 1) &&
            aflags[AFLAGS_TEX_GEN_LOD_MODE] != 2) {
            bilerp_adjust = 0.0f;
        } else {
            bilerp_adjust = 8.0f;
        }

        static float scaleS = 0.5f;
        static float scaleT = -0.5f;
        static float transS = 0.5f;
        static float transT = 0.5f;

        x32 = this->texture_scale_s;
        y32 = this->texture_scale_t;

        if (this->use_dolphin_settile[0] == true) {
            this->settile_cmds[0].shifts = this->settile_dolphin_cmds[0].shift_s;
            this->settile_cmds[0].shiftt = this->settile_dolphin_cmds[0].shift_t;
        }

        if (this->use_dolphin_settile[1] == true) {
            this->settile_cmds[1].shifts = this->settile_dolphin_cmds[1].shift_s;
            this->settile_cmds[1].shiftt = this->settile_dolphin_cmds[1].shift_t;
        }

        EMU64_ASSERTLINE_DEBUG(this, 4092);
        if (this->texture_info[0].width != 0 && this->texture_info[0].height != 0) {
            float t_uls = x32 * shift_tbl[this->settile_cmds[0].shifts];
            float t_ult = y32 * shift_tbl[this->settile_cmds[0].shiftt];

            uls0 = this->settilesize_dolphin_cmds[0].sl;
            ult0 = this->settilesize_dolphin_cmds[0].tl;

            uls = t_uls * ((fastcast_float(&uls0) - bilerp_adjust) * (1.0f / 16.0f)); /* 0.0625f */
            ult = t_ult * ((fastcast_float(&ult0) - bilerp_adjust) * (1.0f / 16.0f)); /* 0.0625f */
            lrs = uls + (t_uls * fastcast_float(&this->texture_info[0].width));
            lrt = ult + (t_ult * fastcast_float(&this->texture_info[0].height));

            if (ult == lrt) {
                OSReport(VT_COL(RED, WHITE) "ult = %8.3f lrt = %8.3f ult0 = %d y32 = %8.3f texobj[0].ht = %d\n" VT_RST,
                         ult, lrt, ult0, y32, this->texture_info[0].height);
            }

            if (uls == lrs) {
                OSReport(VT_COL(RED, WHITE) "uls = %8.3f lrs = %8.3f uls0 = %d x32 = %8.3f texobj[0].wd = %d\n" VT_RST,
                         uls, lrs, uls0, x32, this->texture_info[0].width);
            }

            C_MTXLightOrtho(m, ult, lrt, uls, lrs, scaleS, scaleT, transS, transT);
            GXLoadTexMtxImm(m, GX_TEXMTX0, GX_MTX2x4);
            GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0);

            if ((this->geometry_mode & G_TEXTURE_GEN) != 0) {
                this->texture_gen(0);
            }
        }

        /* Setup texture tile 1 */
        if (this->texture_info[1].width != 0 && this->texture_info[1].height != 0) {
            float t_uls = x32 * shift_tbl[this->settile_cmds[1].shifts];
            float t_ult = y32 * shift_tbl[this->settile_cmds[1].shiftt];

            uls0 = this->settilesize_dolphin_cmds[1].sl;
            ult0 = this->settilesize_dolphin_cmds[1].tl;

            uls = t_uls * ((fastcast_float(&uls0) - bilerp_adjust) * (1.0f / 16.0f)); /* 0.0625f */
            ult = t_ult * ((fastcast_float(&ult0) - bilerp_adjust) * (1.0f / 16.0f)); /* 0.0625f */
            lrs = uls + (t_uls * fastcast_float(&this->texture_info[1].width));
            lrt = ult + (t_ult * fastcast_float(&this->texture_info[1].height));

            if (ult == lrt) {
                OSReport(VT_COL(RED, WHITE) "ult = %8.3f lrt = %8.3f ult0 = %d y32 = %8.3f texobj[1].ht = %d\n" VT_RST,
                         ult, lrt, ult0, y32, this->texture_info[1].height);
            }

            if (uls == lrs) {
                OSReport(VT_COL(RED, WHITE) "uls = %8.3f lrs = %8.3f uls0 = %d x32 = %8.3f texobj[1].wd = %d\n" VT_RST,
                         uls, lrs, uls0, x32, this->texture_info[1].width);
            }

            C_MTXLightOrtho(m, ult, lrt, uls, lrs, scaleS, scaleT, transS, transT);
            GXLoadTexMtxImm(m, GX_TEXMTX1, GX_MTX2x4);
            GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1);

            if ((this->geometry_mode & G_TEXTURE_GEN) != 0) {
                this->texture_gen(1);
            }
        }
    }
}

void emu64::set_position(unsigned int vtx) {
    Vertex* emu_vtx = &this->vertices[vtx];

    if (this->using_nonshared_mtx && (emu_vtx->flag & MTX_NONSHARED) == MTX_SHARED) {
        /* Translation: The nonshared triangle group is broken because a shared vertex is mixed in with the nonshared
         * triangle group! */
        this->Printf0("非シェアードの三角形群にシェアードの頂点が混ざっているので破綻しました!\n");
    }

    if ((emu_vtx->flag & MTX_NONSHARED) != MTX_SHARED) {
        if (!this->using_nonshared_mtx) {
            GC_Mtx& m = this->position_mtx_stack[this->mtx_stack_size];

            if (aflags[AFLAGS_USE_GUVECMULT]) {
                guMtxXFM1F_dol(m, emu_vtx->position.x, emu_vtx->position.y, emu_vtx->position.z, &emu_vtx->position.x,
                               &emu_vtx->position.y, &emu_vtx->position.z);
                guMtxXFM1F_dol(this->model_view_mtx, emu_vtx->normal.x, emu_vtx->normal.y, emu_vtx->normal.z,
                               &emu_vtx->normal.x, &emu_vtx->normal.y, &emu_vtx->normal.z);
            } else {
                MTXMultVec(m, &emu_vtx->position, &emu_vtx->position);
                MTXMultVec(this->model_view_mtx, &emu_vtx->normal, &emu_vtx->normal);
            }

            emu_vtx->flag |= MTX_NONSHARED;
            /* Translation: Nonshared vertices are mixed with the shared triangle group */
            EMU64_LOG("シェアードの三角形群に非シェアードの頂点が混ざっている\n");
        } else if ((this->geometry_mode & G_TEXTURE_GEN) != 0) {

            if (aflags[AFLAGS_USE_GUVECMULT]) {
                guMtxXFM1F_dol(this->model_view_mtx, emu_vtx->normal.x, emu_vtx->normal.y, emu_vtx->normal.z,
                               &emu_vtx->normal.x, &emu_vtx->normal.y, &emu_vtx->normal.z);
            } else {
                MTXMultVec(this->model_view_mtx, &emu_vtx->normal, &emu_vtx->normal);
            }

            /* Translation: Reflection mapping applied to nonshared vertex */
            EMU64_LOG("シェアードじゃない反射マッピングの頂点\n");
        }
    }

    if ((this->othermode_low & ZMODE_DEC) == ZMODE_DEC && (this->geometry_mode & G_ZBUFFER) != 0 &&
        (this->geometry_mode & G_DECAL_EQUAL) == 0) {
        Vec tmp;
        float ox, oy, oz;
        float ow;
        float x, y, z, w;
        u32 decal_mode = (this->geometry_mode & G_DECAL_ALWAYS);

        if ((emu_vtx->flag & MTX_NONSHARED) != MTX_SHARED) {

            if (aflags[AFLAGS_USE_GUVECMULT]) {
                guMtxXFM1F_dol(this->position_mtx_stack[this->mtx_stack_size], emu_vtx->position.x, emu_vtx->position.y,
                               emu_vtx->position.z, &ox, &oy, &oz);
            } else {
                MTXMultVec(this->position_mtx_stack[this->mtx_stack_size], &emu_vtx->position, &tmp);
                ox = tmp.x;
                oy = tmp.y;
                oz = tmp.z;
            }
        } else {
            ox = emu_vtx->position.x;
            oy = emu_vtx->position.y;
            oz = emu_vtx->position.z;
        }

        if (aflags[AFLAGS_SKIP_W_CALCULATION] == 0) {
            guMtxXFM1F_dol2w(this->projection_mtx, this->projection_type, ox, oy, oz, &x, &y, &z, &w);
            z /= w;
        } else {
            guMtxXFM1F_dol2(this->projection_mtx, this->projection_type, ox, oy, oz, &x, &y, &z);
            w = 1.0f;
        }

        if (decal_mode == 0) {
            z -= 0.0001f;
        } else if (decal_mode == G_DECAL_GEQUAL) {
            z += 0.0001f;
        }

        z *= w;
        if (aflags[AFLAGS_PROJECTION_CALC_W]) {
            guMtxXFM1F_dol6w(this->projection_mtx, this->projection_type, x, y, z, w, &ox, &oy, &oz, &ow);

            ox /= ow;
            oy /= ow;
            oz /= ow;
        } else {
            guMtxXFM1F_dol6w1(this->projection_mtx, this->projection_type, x, y, z, w, &ox, &oy, &oz);
        }

        if ((emu_vtx->flag & MTX_NONSHARED) != MTX_SHARED) {
            f32 fx, fy, fz;
            guMtxXFM1F_dol7(this->position_mtx_stack[this->mtx_stack_size], ox, oy, oz, &fx, &fy, &fz);
            GXPosition3f32(fx, fy, fz);
        } else {
            GXPosition3f32(ox, oy, oz);
        }
    } else {
        GXPosition3f32(emu_vtx->position.x, emu_vtx->position.y, emu_vtx->position.z);
    }

    /* If geometry mode lighting is enabled, write vertex normals */
    if ((this->geometry_mode & G_LIGHTING) != 0) {
        GXNormal3f32(emu_vtx->normal.x, emu_vtx->normal.y, emu_vtx->normal.z);
    }

    /* Vertex color */
#ifdef TARGET_PC
    /* On little-endian, color.raw has reversed byte order vs GXColor1u32's
       big-endian bit extraction. Use individual bytes instead. */
    GXColor4u8(emu_vtx->color.rgba.r, emu_vtx->color.rgba.g,
               emu_vtx->color.rgba.b, emu_vtx->color.rgba.a);
#else
    GXColor1u32(emu_vtx->color.raw);
#endif

    /* If texture is on, write texture coordinates */
    if (this->texture_gfx.on != G_OFF) {
        GXTexCoord2s16((s16)emu_vtx->tex_coords.s, (s16)emu_vtx->tex_coords.t);
    }
}

void emu64::set_position3(unsigned int v0, unsigned int v1, unsigned int v2) {
    int wireframe = aflags[AFLAGS_WIREFRAME];

    if (wireframe) {
        GXBegin(GX_LINESTRIP, GX_VTXFMT0, 4);
    }

    if (EMU64_CAN_DRAW_POLYGON()) {
        this->set_position(v0);
        this->set_position(v1);
        this->set_position(v2);
    } else {
        this->set_position(v0);
        this->set_position(v0);
        this->set_position(v0);
    }

    if (wireframe) {
        this->set_position(v0);
        GXEnd();
    }
}

void emu64::set_position4(unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3) {
    int wireframe = aflags[AFLAGS_WIREFRAME];

    if (wireframe) {
        GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);
    }

    if (EMU64_CAN_DRAW_POLYGON()) {
        this->set_position(v0);
        this->set_position(v1);
        this->set_position(v2);
        this->set_position(v3);
    } else {
        this->set_position(v0);
        this->set_position(v0);
        this->set_position(v0);
        this->set_position(v0);
    }

    if (wireframe) {
        this->set_position(v0);
        GXEnd();
    }
}

void emu64::setup_1tri_2tri_1quad(unsigned int vtx_idx) {
    EMU64_TIMED_SEGMENT_BEGIN();

    Vertex* vtx_p = &this->vertices[vtx_idx];

    if ((vtx_p->flag & MTX_NONSHARED) == MTX_SHARED) {
        EMU64_LOG("setup_1tri_2tri_1quad シェアード\n"); /* Translation: setup_1tri_2tri_1quad shared */
        GXSetCurrentMtx(SHARED_MTX);
        this->using_nonshared_mtx = false;
    } else {
        EMU64_LOG("setup_1tri_2tri_1quad ノンシェアード\n"); /* Translation: setup_1tri_2tri_1quad nonshared */
        GXSetCurrentMtx(NONSHARED_MTX);
        this->using_nonshared_mtx = true;
    }
#ifdef PC_GX_VERBOSE
    {
        extern int diag_frame;
        static int flag_diag_count = 0;
        if (diag_frame == 6 && flag_diag_count < 10 && this->projection_type == GX_ORTHOGRAPHIC) {
            flag_diag_count++;
            printf("[VTX FLAG] ortho draw #%d: vtx_idx=%d flag=%d (raw flag word=0x%X)\n",
                   flag_diag_count, vtx_idx, vtx_p->flag, vtx_p->flag);
        }
    }
#endif

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_F32, 0);
    if ((this->geometry_mode & G_LIGHTING) != 0) {
        GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_CLR_RGB, GX_F32, 0);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    } else {
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    }

    if (this->texture_gfx.on != G_OFF) {
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_RGBA4, 0);
    }

    EMU64_TIMED_SEGMENT_END(setup_time);
}

void emu64::draw_1tri_2tri_1quad(unsigned int n_verts, ...) {
    va_list list;
    unsigned int v0;
    unsigned int v1;
    unsigned int v2;
    unsigned int v3;

    va_start(list, n_verts);

    /* 1 Quad */
    if (n_verts == 4) {
        if ((aflags[2] & 3) == 0) {
            if (aflags[22] == 0) {
                GXBegin(GX_QUADS, GX_VTXFMT0, n_verts);
            }

            v0 = va_arg(list, unsigned int);
            v1 = va_arg(list, unsigned int);
            v2 = va_arg(list, unsigned int);
            v3 = va_arg(list, unsigned int);
            this->set_position4(v0, v1, v2, v3);

            if (aflags[22] == 0) {
                GXEnd();
            }

            goto exit;
        }
    }

    /* 1 Triangle */
    if (n_verts == 3) {
        if ((aflags[2] & 1) == 0) {
            if (aflags[22] == 0) {
                GXBegin(GX_TRIANGLES, GX_VTXFMT0, n_verts);
            }

            v0 = va_arg(list, unsigned int);
            v1 = va_arg(list, unsigned int);
            v2 = va_arg(list, unsigned int);
            this->set_position3(v0, v1, v2);

            if (aflags[22] == 0) {
                GXEnd();
            }

            goto exit;
        }
    }

    /* 2 Triangles */
    if (n_verts == 6) {
        if ((aflags[2] & 2) == 0) {
            if (aflags[22] == 0) {
                GXBegin(GX_TRIANGLES, GX_VTXFMT0, n_verts);
            }

            v0 = va_arg(list, unsigned int);
            v1 = va_arg(list, unsigned int);
            v2 = va_arg(list, unsigned int);
            this->set_position3(v0, v1, v2);

            v0 = va_arg(list, unsigned int);
            v1 = va_arg(list, unsigned int);
            v2 = va_arg(list, unsigned int);
            this->set_position3(v0, v1, v2);

            if (aflags[22] == 0) {
                GXEnd();
            }

            goto exit;
        }
    }

exit:
    this->rdp_pipe_sync_needed = TRUE;
}

/* aflag dirty settings */
#define DIRTY_SET_ALL -1
#define DIRTY_SET_NONE 0
#define DIRTY_SET_TILE 1

/* Dirty flag macros */
#define IS_DIRTY(flag) (this->dirty_flags[flag] != false)
#define CLEAR_DIRTY(flag) (this->dirty_flags[flag] = false)
#define SET_DIRTY(flag) (this->dirty_flags[flag] = true)

void emu64::fill_rectangle(float x0, float y0, float x1, float y1) {
    if ((this->othermode_high & G_CYC_COPY) != 0) {
        x1 += 1.0f;
        y1 += 1.0f;

        GXSetNumTevStages(1);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        GXSetZMode(GX_FALSE, GX_NEVER, GX_FALSE);
        this->dirty_flags[EMU64_DIRTY_FLAG_COMBINE] = true;
        this->dirty_flags[EMU64_DIRTY_FLAG_OTHERMODE_HIGH] = true;
        this->dirty_flags[EMU64_DIRTY_FLAG_OTHERMODE_LOW] = true;
    } else {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    }

    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    this->dirty_flags[EMU64_DIRTY_FLAG_LIGHTING] = true;
    GXSetNumTexGens(0);
    GXSetProjection(this->ortho_mtx, GX_ORTHOGRAPHIC);
    GXSetCurrentMtx(GX_PNMTX0);

    this->using_nonshared_mtx = false;
    this->dirty_flags[EMU64_DIRTY_FLAG_PROJECTION_MTX] = true;

    x0 = x0 * (1.0f / 320.0f) - 1.0f;
    y0 = y0 * -(1.0f / 240.0f) - -1.0f;
    x1 = x1 * (1.0f / 320.0f) - 1.0f;
    y1 = y1 * -(1.0f / 240.0f) - -1.0f;

    GXSetCullMode(GX_CULL_NONE);
    this->dirty_flags[EMU64_DIRTY_FLAG_GEOMETRYMODE] = true;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGB, GX_F32, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition2f32(x0, y0);
    GXPosition2f32(x1, y0);
    GXPosition2f32(x1, y1);
    GXPosition2f32(x0, y1);
    GXEnd();

    this->rdp_pipe_sync_needed = true;
}

void emu64::draw_rectangle(Gtexrect2* texrect) {
    float x0;
    float y0;
    float x1;
    float y1;
    float s0;
    float t0;
    float s1;
    float t1;

    float xh = texrect->xh / 4.0f;
    float yh = texrect->yh / 4.0f;
    float xl = texrect->xl / 4.0f;
    float yl = texrect->yl / 4.0f;
    float s = texrect->s / 32.0f;
    float t = texrect->t / 32.0f;
    int tile = texrect->tile;
    float dsdx = texrect->dsdx / 1024.0f;
    float dtdy = texrect->dtdy / 1024.0f;

    if (((this->othermode_high & G_CYC_COPY) != 0 && aflags[AFLAGS_FORCE_G_CYC_COPY] == FALSE) ||
        aflags[AFLAGS_FORCE_G_CYC_COPY] == TRUE) {
        xl += 1.0f;
        yl += 1.0f;
        GXSetNumTevStages(1);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetZMode(GX_FALSE, GX_NEVER, GX_FALSE);
        this->dirty_flags[EMU64_DIRTY_FLAG_COMBINE] = true;
        this->dirty_flags[EMU64_DIRTY_FLAG_OTHERMODE_HIGH] = true;
        this->dirty_flags[EMU64_DIRTY_FLAG_OTHERMODE_LOW] = true;
    }

    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    this->dirty_flags[EMU64_DIRTY_FLAG_LIGHTING] = true;

    float s_end = s + dsdx * (xl - xh);
    float t_end = t + dtdy * (yl - yh);

    float center;
    if ((this->texture_adjust_mode == G_TA_DOLPHIN || (this->othermode_high & G_TF_BILERP) == 0 ||
         (this->othermode_high & G_CYC_COPY) != 0 || aflags[AFLAGS_TEX_GEN_LOD_MODE] == 1) &&
        aflags[AFLAGS_TEX_GEN_LOD_MODE] != 2) {
        center = 0.0f;
    } else {
        center = 0.5f;
    }

    s0 = (center + (s - this->settilesize_dolphin_cmds[tile].sl / 16.0f)) / (int)this->texture_info[tile].width;
    t0 = (center + (t - this->settilesize_dolphin_cmds[tile].tl / 16.0f)) / (int)this->texture_info[tile].height;
    s1 = (center + (s_end - this->settilesize_dolphin_cmds[tile].sl / 16.0f)) / (int)this->texture_info[tile].width;
    t1 = (center + (t_end - this->settilesize_dolphin_cmds[tile].tl / 16.0f)) / (int)this->texture_info[tile].height;

    /* Save current projection — draw_rectangle overwrites it with its own
       ortho, but subsequent polygon rendering (e.g. mFont text on the FONT
       display list) needs the original projection to be restored. */
    Mtx44 saved_proj;
    int saved_proj_type = this->projection_type;
    bcopy(this->projection_mtx, saved_proj, sizeof(Mtx44));

    GXSetProjection(this->ortho_mtx, GX_ORTHOGRAPHIC);
    GXSetCurrentMtx(GX_PNMTX0);

    this->using_nonshared_mtx = false;
    this->dirty_flags[EMU64_DIRTY_FLAG_PROJECTION_MTX] = true;

    x0 = xh * (1.0f / 320.0f) - 1.0f;
    y0 = yh * -(1.0f / 240.0f) - -1.0f;
    x1 = xl * (1.0f / 320.0f) - 1.0f;
    y1 = yl * -(1.0f / 240.0f) - -1.0f;

    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, (GXTexMapID)tile, GX_COLOR_NULL);

    if (((this->othermode_high & G_CYC_COPY) == 0 || aflags[AFLAGS_FORCE_G_CYC_COPY] != FALSE) &&
        aflags[AFLAGS_FORCE_G_CYC_COPY] != TRUE) {
        GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, (GXTexMapID)((tile + 1) & 7), GX_COLOR_NULL);
    }

    GXSetCullMode(GX_CULL_NONE);
    this->dirty_flags[EMU64_DIRTY_FLAG_GEOMETRYMODE] = true;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGB, GX_F32, GX_FALSE);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_F32, GX_FALSE);

    if (aflags[AFLAGS_WIREFRAME]) {
        GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);
        GXPosition2f32(x0, y0);
        GXTexCoord2f32(s0, t0);
        GXPosition2f32(x1, y0);
        GXTexCoord2f32(s1, t0);
        GXPosition2f32(x1, y1);
        GXTexCoord2f32(s1, t1);
        GXPosition2f32(x0, y1);
        GXTexCoord2f32(s0, t1);
        GXPosition2f32(x0, y0);
        GXTexCoord2f32(s0, t0);
        GXEnd();
    } else {
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition2f32(x0, y0);
        GXTexCoord2f32(s0, t0);
        GXPosition2f32(x1, y0);
        GXTexCoord2f32(s1, t0);
        GXPosition2f32(x1, y1);
        GXTexCoord2f32(s1, t1);
        GXPosition2f32(x0, y1);
        GXTexCoord2f32(s0, t1);
        GXEnd();
    }

    /* Restore projection so subsequent polygon rendering uses the correct matrix */
    bcopy(saved_proj, this->projection_mtx, sizeof(Mtx44));
    this->projection_type = saved_proj_type;
    GXSetProjection(this->projection_mtx, (GXProjectionType)this->projection_type);
    this->dirty_flags[EMU64_DIRTY_FLAG_PROJECTION_MTX] = true;

    this->rdp_pipe_sync_needed = true;
}

void emu64::dirty_check(int tile, int n_tiles, int do_texture_matrix) {
    if (aflags[AFLAGS_SET_DIRTY_FLAGS] != DIRTY_SET_NONE) {
        if ((int)aflags[AFLAGS_SET_DIRTY_FLAGS] == DIRTY_SET_ALL) {
            // memset(this->dirty_flags, TRUE, NUM_DIRTY_FLAGS);
        }

        if (aflags[AFLAGS_SET_DIRTY_FLAGS] <= (NUM_DIRTY_FLAGS + DIRTY_SET_TILE - 1)) {
            SET_DIRTY(aflags[AFLAGS_SET_DIRTY_FLAGS] - 1);
        }
    }

    EMU64_TIMED_SEGMENT_BEGIN();
    EMU64_ASSERTLINE_DEBUG(this, 4826);

#ifdef TARGET_PC
    /* Flush any pending GX batch BEFORE changing state.
     * Without this, a pending batch (from the previous draw) gets flushed
     * mid-dirty_check when the first GX state call triggers
     * pc_gx_flush_if_begin_complete(). At that point, texture/combine/etc.
     * may already be partially updated for the NEW draw, causing the previous
     * batch to render with wrong textures. */
    pc_gx_flush_if_begin_complete();
#endif

    if (IS_DIRTY(EMU64_DIRTY_FLAG_PRIM_COLOR)) {
        EMU64_TIMED_SEGMENT_BEGIN();
        CLEAR_DIRTY(EMU64_DIRTY_FLAG_PRIM_COLOR);
        GXSetTevColor(GX_TEVREG1, this->primitive_color.color);
        EMU64_TIMED_SEGMENT_END(dirty_primcolor_time);
    }

    EMU64_ASSERTLINE_DEBUG(this, 4833);

    if (IS_DIRTY(EMU64_DIRTY_FLAG_ENV_COLOR)) {
        EMU64_TIMED_SEGMENT_BEGIN();
        CLEAR_DIRTY(EMU64_DIRTY_FLAG_ENV_COLOR);
        GXSetTevColor(GX_TEVREG2, this->environment_color.color);
        EMU64_TIMED_SEGMENT_END(dirty_envcolor_time);
    }

    EMU64_ASSERTLINE_DEBUG(this, 4840);

    if (IS_DIRTY(EMU64_DIRTY_FLAG_FOG)) {
        /**
         * Othermode lower's upper 16 bits are the cycle dependent "blender" register.
         * The calculation can have two phases over two cycles, and the params are as such:
         * P0P0|P1P1|A0A0|A1A1|M0M0|M1M1|B0B0|B1B1
         *
         * The emulator is checking if the first cycle's P0 value (upper most two bits) is G_BL_CLR_FOG.
         * This is equivalent to the standard GLB_c1 macro's m1a parameter.
         */
        if ((this->othermode_low >> 30) == G_BL_CLR_FOG && (this->geometry_mode & G_FOG) != 0 && this->fog_zmult != 0 &&
            this->fog_zmult != 0 && aflags[4] == 0) {
            /* The developers checked fog_zmult twice in all versions. Maybe it should've been fog_zoffset? */
            /* N64 fog position min-max calculations */
            int min = 500 - (this->fog_zoffset * 500) / this->fog_zmult;
            int max = 128000 / this->fog_zmult + min;

            CLEAR_DIRTY(EMU64_DIRTY_FLAG_FOG);

            /* Calculate startz & endz fog parameters */
            f32 startz =
                -guMtxXFM1F_dol3(this->projection_mtx, this->projection_type, ((f32)(u32)min - 1000.0f) / 1064.0f);
            f32 endz =
                -guMtxXFM1F_dol3(this->projection_mtx, this->projection_type, ((f32)(u32)max - 1000.0f) / 1016.0f);

#ifdef TARGET_PC
            /* On LE, EmuColor.raw is shift-packed (R<<24|G<<16|B<<8|A) but the
               union's GXColor member has byte-swapped fields. Extract via shifts. */
            {
                GXColor fc;
                fc.r = (this->fog_color.raw >> 24) & 0xFF;
                fc.g = (this->fog_color.raw >> 16) & 0xFF;
                fc.b = (this->fog_color.raw >> 8) & 0xFF;
                fc.a = this->fog_color.raw & 0xFF;
                GXSetFog(GX_FOG_PERSP_LIN, startz, endz, this->near, this->far, fc);
            }
        } else {
            GXColor fc = {0, 0, 0, 0};
            GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, fc);
#else
            GXSetFog(GX_FOG_PERSP_LIN, startz, endz, this->near, this->far, this->fog_color.color);
        } else {
            GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, this->fog_color.color);
#endif
        }
    }

    EMU64_ASSERTLINE_DEBUG(this, 4864);

    if (IS_DIRTY(EMU64_DIRTY_FLAG_FILL_TEV_COLOR) || IS_DIRTY(EMU64_DIRTY_FLAG_FILL_COLOR)) {
        EMU64_TIMED_SEGMENT_BEGIN();
        CLEAR_DIRTY(EMU64_DIRTY_FLAG_FILL_COLOR);
        CLEAR_DIRTY(EMU64_DIRTY_FLAG_FILL_TEV_COLOR);
        GXSetTevColor(GX_TEVREG0, this->fill_tev_color.color);
        EMU64_TIMED_SEGMENT_END(dirty_fillcolor_time);
    }

    EMU64_ASSERTLINE_DEBUG(this, 4872);
    if (IS_DIRTY(EMU64_DIRTY_FLAG_COMBINE) || IS_DIRTY(EMU64_DIRTY_FLAG_OTHERMODE_HIGH)) {
        EMU64_TIMED_SEGMENT_BEGIN();
        CLEAR_DIRTY(EMU64_DIRTY_FLAG_COMBINE);
        this->combine();
        EMU64_TIMED_SEGMENT_END(dirty_combine_mode_time);
    }

    EMU64_ASSERTLINE_DEBUG(this, 4826); // TODO: check DnM+ line number
    if (IS_DIRTY(EMU64_DIRTY_FLAG_OTHERMODE_HIGH)) {
        EMU64_TIMED_SEGMENT_BEGIN();
        CLEAR_DIRTY(EMU64_DIRTY_FLAG_OTHERMODE_HIGH);
        EMU64_TIMED_SEGMENT_END(dirty_othermodeh_time);
    }

    EMU64_ASSERTLINE_DEBUG(this, 4826); // TODO: check DnM+ line number
    if (IS_DIRTY(EMU64_DIRTY_FLAG_OTHERMODE_LOW) || IS_DIRTY(EMU64_DIRTY_FLAG_GEOMETRYMODE)) {
        this->zmode();
        this->blend_mode();

        if (IS_DIRTY(EMU64_DIRTY_FLAG_OTHERMODE_LOW)) {
            EMU64_TIMED_SEGMENT_BEGIN();
            CLEAR_DIRTY(EMU64_DIRTY_FLAG_OTHERMODE_LOW);
            this->alpha_compare();
            EMU64_TIMED_SEGMENT_END(dirty_othermodel_time);
        }

        if (IS_DIRTY(EMU64_DIRTY_FLAG_GEOMETRYMODE)) {
            EMU64_TIMED_SEGMENT_BEGIN();
            CLEAR_DIRTY(EMU64_DIRTY_FLAG_GEOMETRYMODE);
            this->cullmode();
            EMU64_TIMED_SEGMENT_END(dirty_geometory_time);
        }
    }

    EMU64_ASSERTLINE_DEBUG(this, 4826); // TODO: Check DnM+ line number

    /* Lights block */
    if (IS_DIRTY(EMU64_DIRTY_FLAG_LIGHTS)) {
        EMU64_TIMED_SEGMENT_BEGIN();
        CLEAR_DIRTY(EMU64_DIRTY_FLAG_LIGHTS);
        SET_DIRTY(EMU64_DIRTY_FLAG_LIGHTING);
        int i;
        for (i = 0; i < this->num_lights; i++) {
            EmuLight* l = &this->lights[i];
            GXLightObj light_obj;
            GXInitLightPos(&light_obj, l->position.x, l->position.y, l->position.z);
            GXInitLightDir(&light_obj, 0.0f, 0.0f, 0.0f);
            GXInitLightAttn(&light_obj, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);

            if (l->attenuation.kc) {
                GXInitLightDir(&light_obj, 1.0f, 0.0f, 0.0f);
                GXInitLightAttn(&light_obj, 0.0f, 0.0f, 0.0f,                           /* a */
                                l->attenuation.kc, l->attenuation.k1, l->attenuation.kq /* k */
                );
            }

            GXInitLightColor(&light_obj, l->color.color);
            GXLoadLightObjImm(&light_obj, (GXLightID)(1 << i));
        }

        GXSetChanAmbColor(GX_COLOR0A0, this->lights[i].color.color);
        EMU64_TIMED_SEGMENT_END(dirty_lightX_time);
        this->dirty_lightX_cnt++;
    }

    /* Lighting block */
    if (IS_DIRTY(EMU64_DIRTY_FLAG_LIGHTING)) {
        EMU64_TIMED_SEGMENT_BEGIN();
        CLEAR_DIRTY(EMU64_DIRTY_FLAG_LIGHTING);
        if ((this->geometry_mode & G_LIGHTING) != 0) {
            if (aflags[AFLAGS_LIGHT_DISABLE_DIFFUSION] != 0) {
                GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
            } else {
                if ((this->geometry_mode & G_LIGHTING_POSITIONAL) != 0) {
                    GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, (1 << num_lights) - 1, GX_DF_CLAMP,
                                  GX_AF_SPOT);
                } else {
                    GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, (1 << num_lights) - 1, GX_DF_CLAMP,
                                  GX_AF_NONE);
                }

                GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
            }
        } else {
            /* When G_SHADE is off, N64 ignores vertex colors (shade defaults to white).
             * Use GX_SRC_REG so the channel doesn't pull black vertex colors. */
            int mat_src = (this->geometry_mode & G_SHADE) ? GX_SRC_VTX : GX_SRC_REG;
            GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, mat_src, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        }

        EMU64_TIMED_SEGMENT_END(dirty_light_time);
        this->dirty_light_cnt++;
    }

    /* Texture block */
    EMU64_ASSERTLINE_DEBUG(this, 4957);
    if (tile >= 0) {
        EMU64_TIMED_SEGMENT_BEGIN();
        /* Flags TEXTURE0/1 are checked but not set in any version of the emulator. Not sure on the names. */
        if (IS_DIRTY(EMU64_DIRTY_FLAG_TEX_TILE0) || IS_DIRTY(EMU64_DIRTY_FLAG_21) ||
            IS_DIRTY(EMU64_DIRTY_FLAG_TEX_TILE1) || IS_DIRTY(EMU64_DIRTY_FLAG_22)) {
            SET_DIRTY(EMU64_DIRTY_FLAG_TEX_MTX);
        }

        int end_tile = tile + n_tiles + 1;
        for (int i = tile; i <= end_tile; i++) {
            int t = i & 7;
            if (IS_DIRTY(EMU64_DIRTY_FLAG_TEX_TILE0 + t) || IS_DIRTY(EMU64_DIRTY_FLAG_21 + t)) {
                EMU64_TIMED_SEGMENT_BEGIN();
                CLEAR_DIRTY(EMU64_DIRTY_FLAG_TEX_TILE0 + t);
                CLEAR_DIRTY(EMU64_DIRTY_FLAG_21 + t);

                if (this->use_dolphin_settile[t] == true) {
                    Gsettile_dolphin* settile_dol_cmd;
                    emu64_texture_info* tex_info_p;
                    u16 height;
                    u16 width;
                    u32 wrap_s;
                    u32 wrap_t;
                    void* img_addr;
                    GXTexFmts dol_fmt;

                    settile_dol_cmd = &this->settile_dolphin_cmds[t];
                    tex_info_p = &this->texture_info[t];
                    wrap_s = settile_dol_cmd->wrap_s;
                    wrap_t = settile_dol_cmd->wrap_t;
                    height = tex_info_p->height;
                    width = tex_info_p->width;
                    img_addr = tex_info_p->img_addr;

                    dol_fmt.raw = cvtN64ToDol(tex_info_p->format, tex_info_p->size);
                    if (((u32)img_addr & 0x1F) != 0) {
#ifndef TARGET_PC
                        /* Translation: Texture (%08x) alignment isn't 32 bytes */
                        this->Printf0("テクスチャ(%08x)のアライメントが３２バイトになっていません\n", img_addr);
                        /* GC hardware DMA requires 32-byte alignment; truncate.
                         * On PC we decode in software so the raw address is correct. */
                        img_addr = (void*)((u32)img_addr & ~0x1F);
#endif
                    }

                    if ((this->geometry_mode & G_TEXTURE_GEN_LINEAR) != 0 &&
                        aflags[AFLAGS_DO_TEXTURE_LINEAR_CONVERT] != 0) {
                        // img_addr = TextureLinearConvert(img_addr, width, height, tex_info_p->format, tex_info_p->size);
                    }

                    if (tex_info_p->format == G_IM_FMT_CI) {
                        GXInitTexObjCI(&this->tex_objs[t], img_addr, width, height, dol_fmt.citexfmt,
                                       (GXTexWrapMode)wrap_s, (GXTexWrapMode)wrap_t, GX_FALSE,
                                       settile_dol_cmd->tlut_name);
                    } else {
                        GXInitTexObj(&this->tex_objs[t], img_addr, width, height, dol_fmt.texfmt, (GXTexWrapMode)wrap_s,
                                     (GXTexWrapMode)wrap_t, GX_FALSE);
                    }

                    if (((this->othermode_high & G_TF_BILERP) == 0 || (this->othermode_high & G_CYC_COPY) != 0 ||
                         aflags[AFLAGS_TEX_GEN_LOD_MODE] == 1) &&
                        aflags[AFLAGS_TEX_GEN_LOD_MODE] != 2) {
                        GXInitTexObjLOD(&this->tex_objs[t], GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE,
                                        GX_ANISO_1);
                    } else if (aflags[AFLAGS_TEX_GEN_LOD_MODE] == 3) {
                        GXInitTexObjLOD(&this->tex_objs[t], GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_TRUE,
                                        GX_ANISO_1);
                    }

                    GXLoadTexObj(&this->tex_objs[t], (GXTexMapID)t);
                    EMU64_TIMED_SEGMENT_END(dirty_tex1_time);
                    this->dirty_tex1_cnt++;
                } else {
                    /* N64 texture tile */
                    this->setup_texture_tile(t);
                    EMU64_TIMED_SEGMENT_END(dirty_tex2_time);
                    this->dirty_tex2_cnt++;
                }

                this->dirty_tex_cnt++;
            }
        }

        EMU64_ASSERTLINE_DEBUG(this, 5026);
        if (IS_DIRTY(EMU64_DIRTY_FLAG_TEX_MTX) && do_texture_matrix != FALSE) {
            CLEAR_DIRTY(EMU64_DIRTY_FLAG_TEX_MTX);
            EMU64_TIMED_SEGMENT_BEGIN();
            this->texture_matrix();
            this->dirty_texmtx_cnt++;
            EMU64_TIMED_SEGMENT_END(dirty_texmtx_time);
        }

        EMU64_TIMED_SEGMENT_END(dirty_tex_time);
    }

    EMU64_ASSERTLINE_DEBUG(this, 5040);
    if (IS_DIRTY(EMU64_DIRTY_FLAG_PROJECTION_MTX)) {
        EMU64_TIMED_SEGMENT_BEGIN();
        CLEAR_DIRTY(EMU64_DIRTY_FLAG_PROJECTION_MTX);
        GXSetProjection(this->projection_mtx, this->projection_type);
        EMU64_TIMED_SEGMENT_END(dirty_proj_time);
    }

    EMU64_ASSERTLINE_DEBUG(this, 5047);
    EMU64_TIMED_SEGMENT_END(dirty_check_time);
    EMU64_ASSERTLINE_DEBUG(this, 5049);
}

/* Commands */
void emu64::dl_G_SPNOOP() {
#ifdef EMU64_DEBUG
    if (this->print_commands != false) {
        this->Printf2("gsSPNoOp(),");
    }
#endif
}

void emu64::dl_G_DL(void) {
    static char s[256];
    Gfx* gfx = this->gfx_p;

    this->work_ptr = (void*)this->seg2k0(gfx->words.w1);
#ifdef TARGET_PC
    if (this->work_ptr == NULL) {
        return;
    }
    {
        /* Validate only regular F3DEX display lists.
         * G_DL_GXDL payload is a GX binary command stream, not a Gfx list. */
        if (gfx->dma.par != G_DL_GXDL) {
            Gfx* target = (Gfx*)this->work_ptr;
            u8 first_opcode = (u8)((target->words.w0 >> 24) & 0xFF);
            u8 first_idx = first_opcode - G_FIRST_CMD;
            if (first_idx >= NUM_COMMANDS) {
                return;
            }
        }
    }
#endif

    switch (gfx->dma.par) {
        case G_DL_PUSH:
            if (this->segment_set != false) {
                this->segment_set = false;
                sprintf(s, "%s", this->segchk(gfx->words.w1));
                this->Printf0(VT_COL(RED, WHITE) "gsSPDisplayList(%s),\n" VT_RST, s);
                emu64::warningString[EMU64_WARN_IDX_DL] = s;
                emu64::warningTime[EMU64_WARN_IDX_DL] = EMU64_WARN_TIME;
                emu64::displayWarning = true;
            }

            if (this->DL_stack_level < DL_MAX_STACK_LEVEL) {
                this->DL_stack[this->DL_stack_level++] = (uintptr_t)(this->gfx_p + 1);
            } else {
                this->err_count++;
                this->Printf0("*** DL stack overflow ***\n");
            }

            this->gfx_p = (Gfx*)((uintptr_t)this->work_ptr - sizeof(Gfx));
            break;
        case G_DL_NOPUSH:
            this->gfx_p = (Gfx*)((uintptr_t)this->work_ptr - sizeof(Gfx));
            break;
        default:
            if (this->disable_polygons == false) {
                GXCallDisplayList(this->work_ptr, gfx->dma.len);
            }
            break;
    }
}

void emu64::dl_G_RDPHALF_1(void) {
    this->rdpHalf_1 = this->gfx.words.w1;
}

void emu64::dl_G_TEXRECT() {
#if UINTPTR_MAX > 0xFFFFFFFFu
    /* Gtexrect2 spans 3 Gfx commands (24 bytes in original 8-byte format).
     * Build a compact buffer from the widened Gfx entries. */
    u32 _texrect_buf[6] = {
        this->gfx_p[0].words.w0, (u32)this->gfx_p[0].words.w1,
        this->gfx_p[1].words.w0, (u32)this->gfx_p[1].words.w1,
        this->gfx_p[2].words.w0, (u32)this->gfx_p[2].words.w1
    };
    Gtexrect2* texrect_p = (Gtexrect2*)_texrect_buf;
#else
    Gtexrect2* texrect_p = (Gtexrect2*)this->gfx_p;
#endif

#ifdef EMU64_DEBUG
    if (this->print_commands != false) {
        this->Printf2("gsSPTextureRectangle(%d,%d,%d,%d,%d,%d,%d,%d,%d),",
                      texrect_p->xh, /* TODO: check if this is just wrong, or Gtexrect2 flips xh/yh with xl/yl */
                      texrect_p->yh, texrect_p->xl, texrect_p->yl, texrect_p->tile, texrect_p->s, texrect_p->t,
                      texrect_p->dsdx, texrect_p->dtdy);
    }
#endif

    if (this->disable_polygons == false) {
        this->dirty_check(texrect_p->tile, 0, 0);

#ifdef EMU64_DEBUG
        if (aflags[AFLAGS_SKIP_DRAW_RECTANGLE] == 0) {
#endif
            this->draw_rectangle(texrect_p);
#ifdef EMU64_DEBUG
        }
#endif
    }

    this->gfx_p += 2; /* Increment by two here, the emulator will increment by another for the full Gtexrect2 size */
}

void emu64::dl_G_LOAD_UCODE() {
#ifdef EMU64_DEBUG
    u16 uc_dsize = this->gfx.words.w0 & 0xFFFF;
    if (uc_dsize == 0x7FF) {
        if (this->print_commands != false) {
            this->Printf1("gsSPLoadUcode(%s, 0x%08x),", segchk(this->gfx.words.w1), this->rdpHalf_1);
        }
    } else if (this->print_commands != false) {
        this->Printf1("gsSPLoadUcodeEx(%s, 0x%08x, 0x%05x),", this->segchk(this->gfx.words.w1), this->rdpHalf_1,
                      uc_dsize + 1);
    }
#endif

    void* k0 = (void*)this->seg2k0(this->gfx.words.w1);
    this->emu64_change_ucode(k0);
    this->load_ucode_calls++;
}

void emu64::dl_G_ENDDL() {
#ifdef EMU64_DEBUG

    if (this->print_commands) {
        this->Printf1("gsSPEndDisplayList(),");
    }

#endif

    if (this->DL_stack_level <= 0) {
        this->end_dl = TRUE;
    } else {
        /* subtract one because emulator will add one after processing */
        this->gfx_p = (Gfx*)this->DL_stack[--this->DL_stack_level] - 1;
    }
}

void emu64::dl_G_SETTILE() {
    Gsettile* settile = (Gsettile*)EMU64_GFX_COMPACT_PTR;

#ifdef EMU64_DEBUG
    if (this->print_commands != false) {
        const char* s_wrapmode;
        int s_wrap = settile->ms + (settile->cs << 1);
        if (s_wrap == G_TX_WRAP) {
            s_wrapmode = "G_TX_WRAP";
        } else if (s_wrap == G_TX_MIRROR) {
            s_wrapmode = "G_TX_MIRROR";
        } else if (s_wrap == G_TX_CLAMP) {
            s_wrapmode = "G_TX_CLAMP";
        } else { /* s_wrap == G_TX_MIRROR|G_TX_CLAMP */
            s_wrapmode = "G_TX_MIRROR|G_TX_CLAMP";
        }

        const char* t_wrapmode;
        int t_wrap = settile->mt + (settile->ct << 1);
        if (t_wrap == G_TX_WRAP) {
            t_wrapmode = "G_TX_WRAP";
        } else if (t_wrap == G_TX_MIRROR) {
            t_wrapmode = "G_TX_MIRROR";
        } else if (t_wrap == G_TX_CLAMP) {
            t_wrapmode = "G_TX_CLAMP";
        } else { /* t_wrap == G_TX_MIRROR|G_TX_CLAMP */
            t_wrapmode = "G_TX_MIRROR|G_TX_CLAMP";
        }

        const char* s_siz;
        int siz = settile->siz;
        if (siz == G_IM_SIZ_4b) {
            s_siz = "4b";
        } else if (siz == G_IM_SIZ_8b) {
            s_siz = "8b";
        } else if (siz == G_IM_SIZ_16b) {
            s_siz = "16b";
        } else { /* siz == G_IM_SIZ_32b */
            s_siz = "32b";
        }

        const char* s_fmt;
        int fmt = settile->fmt;
        if (fmt == G_IM_FMT_RGBA) {
            s_fmt = "RGBA";
        } else if (fmt == G_IM_FMT_YUV) {
            s_fmt = "YUV";
        } else if (fmt == G_IM_FMT_CI) {
            s_fmt = "CI";
        } else if (fmt == G_IM_FMT_IA) {
            s_fmt = "IA";
        } else { /* fmt == G_IM_FMT_I */
            s_fmt = "I";
        }

        this->Printf2("gsDPSetTile(G_IM_FMT_%s, G_IM_SIZ_%s,%d,%d,%d,%d,%s,%d,%d,%s,%d,%d),", s_fmt, s_siz,
                      settile->line, settile->tmem, settile->tile, settile->palette, t_wrapmode, settile->maskt,
                      settile->shiftt, s_wrapmode, settile->masks, settile->shifts);
    }
#endif

    this->use_dolphin_settile[settile->tile] = false;
    bzero(&this->settile_dolphin_cmds[settile->tile], sizeof(Gsettile_dolphin));
    this->settile_cmds[settile->tile] = *settile;
    this->dirty_flags[EMU64_DIRTY_FLAG_TEX_TILE0 + settile->tile] = true;
}

void emu64::dl_G_SETTILE_DOLPHIN() {
    u32 w0 = this->gfx.words.w0;
    int dol_fmt = (w0 >> 20) & 0xF;
    int tile = (w0 >> 16) & 0x7;
    int tlut_name = (w0 >> 12) & 0xF;
    int wrap_s = (w0 >> 10) & 0x3;
    int wrap_t = (w0 >> 8) & 0x3;
    int shift_s = (w0 >> 4) & 0xF;
    int shift_t = w0 & 0xF;
    Gsettile_dolphin decoded = {};
    decoded.cmd = G_SETTILE_DOLPHIN;
    decoded.dol_fmt = dol_fmt;
    decoded.tile = tile;
    decoded.tlut_name = tlut_name;
    decoded.wrap_s = wrap_s;
    decoded.wrap_t = wrap_t;
    decoded.shift_s = shift_s;
    decoded.shift_t = shift_t;

#ifdef EMU64_DEBUG
    if (this->print_commands != false) {
        this->Printf2("gsDPSetTile_Dolphin(G_TF_%s,%d,%d,GX_%s,GX_%s,%d,%d),", dolfmttbl[dol_fmt], tile, tlut_name,
                      doltexwrapmode[wrap_s], doltexwrapmode[wrap_t], shift_s, shift_t);
    }
#endif

    this->use_dolphin_settile[tile] = true;
    this->settile_dolphin_cmds[tile] = decoded;
    bzero(&this->settile_cmds[tile], sizeof(Gsettile));
    this->setimg2_cmds[tile] = this->now_setimg.setimg2;

    /* Setup tile size using S (X): [0, width - 1], T (Y): [0, height - 1] */
    this->settilesize_dolphin_cmds[tile].sl = 0;
    this->settilesize_dolphin_cmds[tile].tl = 0;
    this->settilesize_dolphin_cmds[tile].slen = this->now_setimg.setimg2.wd;
    this->settilesize_dolphin_cmds[tile].tlen = EXPAND_HEIGHT(this->now_setimg.setimg2.ht) - 1;
    this->settilesize_dolphin_cmds[tile].tile = tile;
    this->settilesize_dolphin_cmds[tile].isDolphin = 1;

    /* Set texture info for use in GC texture object initialization */
#ifdef TARGET_PC
    this->texture_info[tile].img_addr = (void*)this->resolved_imgaddr;
#else
    this->texture_info[tile].img_addr = (void*)this->now_setimg.setimg2.imgaddr;
#endif
    this->texture_info[tile].format = this->now_setimg.setimg2.fmt;
    this->texture_info[tile].size = this->now_setimg.setimg2.siz;
    this->texture_info[tile].width = EXPAND_WIDTH(this->now_setimg.setimg2.wd);
    this->texture_info[tile].height = EXPAND_HEIGHT(this->now_setimg.setimg2.ht);

    /* Mark texture tile as dirty */
    this->dirty_flags[EMU64_DIRTY_FLAG_TEX_TILE0 + tile] = true;
}

void emu64::dl_G_LOADTILE() {
    Gloadtile& loadtile = *(Gloadtile*)EMU64_GFX_COMPACT_PTR;

#ifdef EMU64_DEBUG
    if (this->print_commands) {
        this->Printf2("gsDPLoadTile(%d,%d,%d,%d,%d),", loadtile->tile, loadtile->sl, loadtile->tl, loadtile->sh,
                      loadtile->th);
    }
#endif

    /* Check if this image does not support gsDPLoadTile() */
    if (this->now_setimg.setimg2.isDolphin != false)
        return;

    /* Determine tmem base address */
#ifdef TARGET_PC
    uintptr_t dram = this->resolved_imgaddr;
#else
    u32 dram = this->now_setimg.setimg2.imgaddr;
#endif
    dram += ((loadtile.tl / 4) * EXPAND_WIDTH(this->now_setimg.setimg2.wd) + (loadtile.sl / 4)
             << this->now_setimg.setimg2.siz) /
            2;

#ifdef EMU64_DEBUG
    if (this->print_commands) {
        this->Printf2("\n [%d %d]-[%d %d] tmem=%d dram=%08x\n", sl, tl, loadtile.sh / 4, loadtile.tl / 4, tmem, dram);
    }
#endif

    int tmem_idx = this->settile_cmds[loadtile.tile].tmem / 4;

    /* Copy setup values to tmem */
    tmem_map[tmem_idx].addr = (void*)dram;
    tmem_map[tmem_idx].loadtile = loadtile;
    tmem_map[tmem_idx].setimg2 = this->now_setimg.setimg2;

#ifdef EMU64_DEBUG
    if (this->print_commands) {
        this->Printf3("tmem_map[%d]=%08x\n", tmem_idx, addr);
    }
#endif
}

void emu64::dl_G_LOADBLOCK() {
    int tmem_idx;
    Gloadblock* loadblock = (Gloadblock*)EMU64_GFX_COMPACT_PTR;
#ifdef TARGET_PC
    uintptr_t addr;
#else
    u32 addr;
#endif
    int i;

#ifdef EMU64_DEBUG
    u32 start = osGetCount();

    if (this->print_commands) {
        this->Printf2("gsDPLoadBlock(%d,%d,%d,%d,%d),", loadblock->tile, loadblock->sl, loadblock->tl, loadblock->sh,
                      loadblock->th);
    }
#endif

    if (this->now_setimg.setimg2.isDolphin != false)
        return; /* Does not support LOAD commands */

    tmem_idx = this->settile_cmds[loadblock->tile].tmem / 4;
#ifdef TARGET_PC
    addr = this->resolved_imgaddr;
#else
    addr = this->now_setimg.setimg2.imgaddr;
#endif
    for (i = tmem_idx; i < tmem_idx + (loadblock->sh + 1) / 16; i++) {
        tmem_map[i].addr = (void*)addr;
        tmem_map[i].loadblock = *loadblock;
        tmem_map[i].setimg2 = this->now_setimg.setimg2;
        addr += 16 * sizeof(u16);
    }

#ifdef EMU64_DEBUG
    this->loadblock_time += (osGetCount() - start);
#endif
}

void emu64::dl_G_SETTILESIZE() {
    Gsettilesize* settilesize = (Gsettilesize*)EMU64_GFX_COMPACT_PTR;
    u32 w0 = this->gfx.words.w0;
    u32 w1 = this->gfx.words.w1;
    int tile;

    if (((w1 >> 31) & 1) != 0) {
        int sl = (w0 >> 10) & 0x3FFF;
        int slen = w0 & 0x3FF;
        int tl = (w1 >> 10) & 0x3FFF;
        int tlen = w1 & 0x3FF;
        tile = (w1 >> 24) & 0x7;
#ifdef EMU64_DEBUG
        /* Seems they checked it twice in source code... */
        if (this->print_commands != false && this->print_commands != false) {
            this->Printf2("gsDPSetTileSize_Dolphin(%d,%d,%d,%d,%d),", tile, sl, tl, slen, tlen);
        }
#endif
        this->settilesize_dolphin_cmds[tile].cmd = G_SETTILESIZE;
        this->settilesize_dolphin_cmds[tile].sl = sl;
        this->settilesize_dolphin_cmds[tile].tl = tl;
        this->settilesize_dolphin_cmds[tile].slen = slen;
        this->settilesize_dolphin_cmds[tile].tlen = tlen;
        this->settilesize_dolphin_cmds[tile].tile = tile;
        this->settilesize_dolphin_cmds[tile].isDolphin = 1;
    } else { /* Gsettilesize */
        u16 s_len = (((settilesize->sh) - (settilesize->sl)) >> 2) + 1;
        u16 t_len = ((settilesize->th - (settilesize->tl)) >> 2) + 1;
        tile = settilesize->tile;

#ifdef EMU64_DEBUG
        if (this->print_commands != false) {
            if (this->print_commands != false) {
                this->Printf2("gsDPSetTileSize(%d,%d,%d,%d,%d),", tile, settilesize->sl, settilesize->tl,
                              settilesize->sh, settilesize->th);
            }

            if (this->print_commands != false) {
                this->Printf2(" /* %dx%d */", s_len, t_len + 1);
            }
        }
#endif

        /* Convert from N64 Gsettilesize to Gsettilesize_dolphin */
        this->settilesize_dolphin_cmds[tile].sl = settilesize->sl * 4;
        this->settilesize_dolphin_cmds[tile].tl = settilesize->tl * 4;
        this->settilesize_dolphin_cmds[tile].slen = s_len - 1;
        this->settilesize_dolphin_cmds[tile].tlen = t_len - 1;
        this->settilesize_dolphin_cmds[tile].tile = tile;
        this->settilesize_dolphin_cmds[tile].isDolphin = 0;
    }

    /* Mark texture tile as dirty */
    this->dirty_flags[EMU64_DIRTY_FLAG_TEX_TILE0 + tile] = true;
}

#ifdef TARGET_PC
extern "C" void pc_gx_tlut_set_native_le(unsigned int idx);
extern "C" u16 s_tlut_first_word[16];
#endif

void emu64::dl_G_LOADTLUT() {
    Gloadtlut_dolphin* loadtlut_dol = (Gloadtlut_dolphin*)EMU64_GFX_COMPACT_PTR;
    u16 count;
    void* tlut_addr;
    u32 tlut_name;
    void* aligned_addr;

    EMU64_TIMED_SEGMENT_BEGIN();

    if (loadtlut_dol->type == 2) {
        uintptr_t tlut_w1 = this->gfx_p->words.w1; /* Full pointer from w1 */
        EMU64_LOGF("gsDPLoadTLUT_Dolphin(%d, %d, %s),", loadtlut_dol->tlut_name, loadtlut_dol->count,
                   this->segchk(tlut_w1));

        if (this->disable_polygons == false) {
            count = loadtlut_dol->count & 0x3FFF;
            tlut_name = loadtlut_dol->tlut_name;
            tlut_addr = (void*)this->seg2k0(tlut_w1);

            if (tlut_addr == this->tlut_addresses[tlut_name]) {
                /* Translation: ### Same TLUT address */
                EMU64_INFO("### 同じTLUTアドレスです\n");
#ifdef TARGET_PC
                /* On PC, the game reuses memory buffers — same address can hold
                 * different TLUT data (e.g., different NPC clothing palettes).
                 * GC hardware always re-DMA'd, so the skip was harmless there.
                 * On PC we must detect content changes and force a reload. */
                if (tlut_addr != nullptr) {
                    u16 first = *(u16*)tlut_addr;
                    if (s_tlut_first_word[tlut_name] != first) {
                        s_tlut_first_word[tlut_name] = first;
                        this->tlut_addresses[tlut_name] = nullptr;
                    }
                }
#endif
            } else { /* tlut_addr != this->tlut_addresses[tlut_name] */
                aligned_addr = tlut_addr;

                this->tlut_addresses[tlut_name] = tlut_addr;
                if (tlut_addr != nullptr) {
                    if (((u32)tlut_addr & (0x1F)) != 0) {
#ifndef TARGET_PC
                        /* The alignment of the palette (%08x) is not 32 bytes. */
                        EMU64_PRINTF(
                            VT_COL(RED, WHITE) "パレット(%08x)のアライメントが３２バイトになっていません\n" VT_RST,
                            tlut_addr)

                        /* GC hardware DMA requires 32-byte alignment; truncate.
                         * On PC we decode in software so the raw address is correct. */
                        aligned_addr = (void*)((u32)tlut_addr & (~0x1F));
#endif
                    }

                    GXInitTlutObj(&this->tlut_objs[tlut_name], aligned_addr, GX_TL_RGB5A3, count);
                    GXLoadTlut(&this->tlut_objs[tlut_name], tlut_name);
#ifdef TARGET_PC
                    pc_gx_tlut_set_native_le(tlut_name);
                    s_tlut_first_word[tlut_name] = *(u16*)aligned_addr;
#endif

                    EMU64_INFOF("GXInitTlutObj %08x %d pal_no=%d\n", tlut_addr, count, tlut_name);
                }
            }
        }
    } else {
        Gfx* loadtlut = this->gfx_p;
        Gloadtlut* loadtlut_v = (Gloadtlut*)EMU64_GFX_COMPACT_PTR;

        EMU64_LOGF("gsDPLoadTLUTCmd(%d,%d),", loadtlut_v->tile, (loadtlut->words.w1 >> 14) & 0x3FF);

        Gsettile* settile_p = &this->settile_cmds[loadtlut_v->tile];

        if (this->disable_polygons == false) {
            u16 count = ((loadtlut->words.w1 >> 14) & 0x3FF) + 1;
            void* tlut;
#ifdef TARGET_PC
            uintptr_t addr = this->resolved_imgaddr;
#else
            u32 addr = this->now_setimg.setimg2.imgaddr;
#endif
            u32 tlut_name = (settile_p->tmem / 16) & 0xF;

            if (addr == (uintptr_t)this->tlut_addresses[tlut_name]) {
                /* Translation: ### Same TLUT address %08x %d */
                EMU64_INFOF("### 同じTLUTアドレスです %08x %d\n", addr, tlut_name);
#ifdef TARGET_PC
                /* Same fix as type-2 path: detect content change at reused address.
                 * Note: addr here is already a direct pointer (not a segment address),
                 * so do NOT call seg2k0() — just cast directly. */
                if (addr != 0) {
                    u16 first = *(u16*)(uintptr_t)addr;
                    if (s_tlut_first_word[tlut_name] != first) {
                        s_tlut_first_word[tlut_name] = first;
                        this->tlut_addresses[tlut_name] = nullptr;
                    }
                }
#endif
            } else {
                /* Convert TLUT */
                if (this->now_setimg.setimg2.isDolphin) {
                    tlut = (void*)addr;
                } else {
                    tlut = this->tlutconv_new((u16*)addr, EMU64_TLUT_RGBA5551, count);
                }

                if (tlut != nullptr) {
                    while (count != 0) {
                        tlut_addresses[tlut_name] = (void*)addr;
                        GXInitTlutObj(&this->tlut_objs[tlut_name], tlut, GX_TL_RGB5A3, count);
                        GXLoadTlut(&this->tlut_objs[tlut_name], tlut_name);
#ifdef TARGET_PC
                        pc_gx_tlut_set_native_le(tlut_name);
#endif

                        EMU64_INFOF("GXInitTlutObj %08x %d pal_no=%d\n", addr, (u16)count, tlut_name);

                        tlut_name++;
                        count -= 16;
                        addr += 16 * sizeof(u16);
                        tlut = ((u16*)tlut) + 16;
                    }
                }
            }
        }
    }

    EMU64_TIMED_SEGMENT_END(loadtlut_time);
}

void emu64::dl_G_SETCOMBINE_NOTEV() {
#if defined(TARGET_PC) && UINTPTR_MAX > 0xFFFFFFFFu
    /* On 64-bit, reconstruct the packed 64-bit combine value from w0 and w1 */
    u64 combine_val = ((u64)this->gfx.words.w0) | ((u64)(u32)this->gfx.words.w1 << 32);
    /* Fix cmd to G_SETCOMBINE */
    combine_val = (combine_val & ~((u64)0xFF << 24)) | ((u64)G_SETCOMBINE << 24);
#else
    u64* combine = (u64*)&this->gfx;
#endif
    s8 print_commands = this->print_commands;

    if (print_commands) {
#if defined(TARGET_PC) && UINTPTR_MAX > 0xFFFFFFFFu
        this->print_combine(combine_val);
#else
        this->print_combine(*combine);
#endif
    }

    /* Update combiner settings only if it changed */
#if defined(TARGET_PC) && UINTPTR_MAX > 0xFFFFFFFFu
    if (*(u64*)&this->combine_gfx != combine_val) {
        *(u64*)&this->combine_gfx = combine_val;
        this->dirty_flags[EMU64_DIRTY_FLAG_COMBINE] = true;
    }
#else
    ((Gsetcombine_new*)combine)->cmd = G_SETCOMBINE;
    if (*(u64*)&this->combine_gfx != *combine) {
        *(u64*)&this->combine_gfx = *combine;
        this->dirty_flags[EMU64_DIRTY_FLAG_COMBINE] = true;
    }
#endif
}

void emu64::dl_G_SETCOMBINE() {
#if defined(TARGET_PC) && UINTPTR_MAX > 0xFFFFFFFFu
    u64 combine_val = ((u64)this->gfx.words.w0) | ((u64)(u32)this->gfx.words.w1 << 32);
#else
    u64* combine = (u64*)&this->gfx;
#endif
    s8 print_commands = this->print_commands;

    if (print_commands) {
#if defined(TARGET_PC) && UINTPTR_MAX > 0xFFFFFFFFu
        this->print_combine(combine_val);
#else
        this->print_combine(*combine);
#endif
    }

    /* Update combiner settings only if it changed */
#if defined(TARGET_PC) && UINTPTR_MAX > 0xFFFFFFFFu
    if (*(u64*)&this->combine_gfx != combine_val) {
        *(u64*)&this->combine_gfx = combine_val;
        this->dirty_flags[EMU64_DIRTY_FLAG_COMBINE] = true;
    }
#else
    if (*(u64*)&this->combine_gfx != *combine) {
        *(u64*)&this->combine_gfx = *combine;
        this->dirty_flags[EMU64_DIRTY_FLAG_COMBINE] = true;
    }
#endif

    /* N64 Combiner -> GC TEV */
#ifdef TARGET_PC
    /* On PC, skip replace_combine_to_tev — the Gsetcombine_tev bitfield
       layout is endian-dependent and produces garbled TEV inputs on LE.
       Instead, combine() will use combine_auto/combine_manual which
       translate N64 combine modes to GX TEV calls directly. */
#else
    if (this->gfx_cmd != G_SETCOMBINE_NOTEV && aflags[AFLAGS_SKIP_COMBINE_TEV] == 0) {
        this->replace_combine_to_tev(this->gfx_p);
    }
#endif
}

void emu64::dl_G_SETCOMBINE_TEV() {
#if defined(TARGET_PC) && UINTPTR_MAX > 0xFFFFFFFFu
    u64 combine_tev_val = ((u64)this->gfx.words.w0) | ((u64)(u32)this->gfx.words.w1 << 32);
#else
    u64* combine_tev = (u64*)&this->gfx;
#endif
    s8 print_commands = this->print_commands;

    if (print_commands) {
#if defined(TARGET_PC) && UINTPTR_MAX > 0xFFFFFFFFu
        this->print_combine_tev(combine_tev_val);
#else
        this->print_combine_tev(*combine_tev);
#endif
    }

    /* Update combiner settings only if it changed */
#if defined(TARGET_PC) && UINTPTR_MAX > 0xFFFFFFFFu
    if (*(u64*)&this->combine_gfx != combine_tev_val) {
        *(u64*)&this->combine_gfx = combine_tev_val;
        this->dirty_flags[EMU64_DIRTY_FLAG_COMBINE] = true;
    }
#else
    if (*(u64*)&this->combine_gfx != *combine_tev) {
        *(u64*)&this->combine_gfx = *combine_tev;
        this->dirty_flags[EMU64_DIRTY_FLAG_COMBINE] = true;
    }
#endif
}

void emu64::dl_G_SETOTHERMODE_H() {
    Gsetothermode_dolphin* othermodeH = (Gsetothermode_dolphin*)EMU64_GFX_COMPACT_PTR;
    u32 sft;
    u32 len;
    u32 data;

    len = othermodeH->len + 1;
    sft = (32 - othermodeH->sft) - len;
    data = GFX_W1_U32(this->gfx);

    if ((this->print_commands & EMU64_PRINTF2_FLAG) != 0) {
        for (int i = 0; i < ARRAY_COUNT(h_tbl); i++) {
            const OthermodeParameterInfo* info = &h_tbl[i];

            if (sft == info->shift) {
                for (int opt = 0; opt < 4; opt++) {
                    if (data == info->opts[opt].val) {
                        EMU64_LOGF("gsDP%s(%s),", info->name, info->opts[i].name);
                        goto exit;
                    }
                }
            }

            info++;
        }

        /* We didn't find the param */
        EMU64_LOGF("gsSPSetOtherModeH(%d, %d, 0x%08x),", sft, len, data);
    }

exit:
    if (this->othermode_high != (data | (this->othermode_high & (1 - (1 << len) << sft) - 1u))) {
        this->othermode_high = (data | (this->othermode_high & (1 - (1 << len) << sft) - 1u));
        this->dirty_flags[EMU64_DIRTY_FLAG_OTHERMODE_HIGH] = true;
    }
}

void emu64::dl_G_SETOTHERMODE_L() {
    u32 sft;
    u32 len;
    u32 data;

    len = ((Gsetothermode_dolphin*)EMU64_GFX_COMPACT_PTR)->len + 1;
    sft = (32 - ((Gsetothermode_dolphin*)EMU64_GFX_COMPACT_PTR)->sft) - len;
    data = GFX_W1_U32(this->gfx);

    if ((this->print_commands & EMU64_PRINTF2_FLAG) != 0) {
        if ((int)sft == G_MDSFT_RENDERMODE) {
            this->show_render(data);
        } else {
            for (int i = 0; i < ARRAY_COUNT(l_tbl); i++) {
                const OthermodeParameterInfo* info = &l_tbl[i];
                if (sft == info->shift) {
                    for (int opt = 0; opt < 4; opt++) {
                        if (data == info->opts[opt].val) {
                            EMU64_LOGF("gsDP%s(%s),", info->name, info->opts[i].name);
                            goto exit;
                        }
                    }
                }
            }
        }

        /* We didn't find the param */
        EMU64_LOGF("gsSPSetOtherModeL(%d, %d, 0x%08x),", sft, len, data);
    }

exit:
    u32 othermode = data | (this->othermode_low & (1 - (1 << len) << sft) - 1u);
    if (this->othermode_low != othermode) {
        this->dirty_flags[EMU64_DIRTY_FLAG_FOG] = true;
        this->othermode_low = othermode;
        this->dirty_flags[EMU64_DIRTY_FLAG_OTHERMODE_LOW] = true;
    }
}

void emu64::dl_G_RDPSETOTHERMODE() {
    /* Debug output */
    if ((this->print_commands & EMU64_PRINTF_ENABLED_FLAG) != 0) {
        EMU64_LOG("gsDPSetOtherMode(");

        /* Process high commands first */
        u32 h = this->gfx.words.w0 & 0xFFFFFF;
        for (int i = 0; i < ARRAY_COUNT(h_tbl); i++) {
            const OthermodeParameterInfo* info = &h_tbl[i];
            u32 mask = (0xFFFFFFFF >> (32 - info->len)) << info->shift;
            u32 param = h & mask;

            for (int opt = 0; opt < 4; opt++) {
                if (param == info->opts[opt].val) {
                    EMU64_LOGF("%s%s", info->opts[opt].name, i < NUM_OTHERMODE_HIGH_CMDS - 1 ? "|" : "");
                    goto h_found;
                }
            }

            EMU64_LOGF("%08x(%08x:%08x)%s", param, h, mask, i < NUM_OTHERMODE_HIGH_CMDS - 1 ? "|" : "");
        h_found:
            continue;
        }

        EMU64_LOG(", ");

        /* Process low commands */
        u32 l = this->gfx.words.w1;
        for (int i = 0; i < ARRAY_COUNT(l_tbl); i++) {
            const OthermodeParameterInfo* info = &l_tbl[i];
            u32 mask = (0xFFFFFFFF >> (32 - info->len)) << info->shift;
            u32 param = l & mask;

            for (int opt = 0; opt < 4; opt++) {
                if (param == info->opts[opt].val) {
                    EMU64_LOGF("%s%s", info->opts[opt].name, i < NUM_OTHERMODE_LOW_CMDS - 1 ? "|" : "");
                    goto l_found;
                }
            }

            EMU64_LOGF("%08x(%08x:%08x)%s", param, h, mask, i < NUM_OTHERMODE_LOW_CMDS - 1 ? "|" : "");
        l_found:
            continue;
        }

        EMU64_LOG("),");
    }

    /* Actual command processing */
    u32 othermode_h = this->gfx.words.w0 & 0xFFFFFF;
    if (this->othermode_high != othermode_h) {
        this->othermode_high = othermode_h;
        this->dirty_flags[EMU64_DIRTY_FLAG_OTHERMODE_HIGH] = true;
    }

    if (this->othermode_low != this->gfx.words.w1) {
        this->dirty_flags[EMU64_DIRTY_FLAG_FOG] = true;
        this->othermode_low = this->gfx.words.w1;
        this->dirty_flags[EMU64_DIRTY_FLAG_OTHERMODE_LOW] = true;
    }
}

void emu64::dl_G_SETSCISSOR() {
    u8 print_commands = this->print_commands;
    Gscissor* scissor = (Gscissor*)EMU64_GFX_COMPACT_PTR;

#ifdef EMU64_DEBUG

    if (print_commands & EMU64_PRINT_FLAG_ENABLE != 0) {
        const char* mode;
        if (scissor->pad == G_SC_NON_INTERLACE) {
            mode = "G_SC_NON_INTERLACE";
        } else if (scissor->pad == G_SC_ODD_INTERLACE) {
            mode = "G_SC_ODD_INTERLACE";
        } else if (scissor->pad == G_SC_EVEN_INTERLACE) {
            mode = "G_SC_EVEN_INTERLACE";
        } else {
            mode = "???";
        }

        int x0frac = scissor->x0frac;
        int y0frac = scissor->y0frac;
        int x1frac = scissor->x1frac;
        int y1frac = scissor->y1frac;

        if ((x0frac | y0frac | x1frac | y1frac) == 0) {
            if (print_commands != false) {
                this->Printf2("gsDPSetScissor(%s, %d, %d, %d, %d),", mode, scissor->x0, scissor->y0, scissor->x1,
                              scissor->y1);
            }
        } else if (print_commands != false) {
            this->Printf2("gsDPSetScissorFrac(%s, %d, %d, %d, %d),", mode, scissor->x0 * 4 + x0frac,
                          scissor->y0 * 4 + y0frac, scissor->x1 * 4 + x1frac, scissor->y1 * 4 + y1frac);
        }
    }

#endif

    /* NOTE: fractional scissor components are ignored */
    if (this->disable_polygons == false) {
        GXSetScissor(scissor->x0, scissor->y0, scissor->x1, scissor->y1);
    }
}

void emu64::dl_G_FILLRECT() {
    Gfillrect2* fillrect = (Gfillrect2*)EMU64_GFX_COMPACT_PTR;

    EMU64_LOGF("gsDPFillRectangle(%d, %d, %d, %d),", fillrect->x1, fillrect->y1, fillrect->x0, fillrect->y0);

    if (this->disable_polygons == false) {
        this->dirty_check(-1, -1, 0);
        this->fill_rectangle(fillrect->x1, fillrect->y1, fillrect->x0, fillrect->y0);
    }
}

void emu64::dl_G_SETCIMG() {
#ifdef EMU64_DEBUG
    if (this->print_commands & EMU64_PRINT_FLAG_ENABLE != 0) {
        u32 fmt = this->gfx.setimg.fmt;
        u32 siz = this->gfx.setimg.siz;

        if (this->print_commands != false) {
            const char* s_siz;
            const char* s_fmt;

            if (siz == G_IM_SIZ_4b) {
                s_siz = "4b";
            } else if (siz == G_IM_SIZ_8b) {
                s_siz = "8b";
            } else if (siz == G_IM_SIZ_16b) {
                s_siz = "16b";
            } else {
                s_siz = "32b";
            }

            if (fmt == G_IM_FMT_RGBA) {
                s_fmt = "RBGA";
            } else if (fmt == G_IM_FMT_YUV) {
                s_fmt = "YUV";
            } else if (fmt == G_IM_FMT_CI) {
                s_fmt = "CI";
            } else if (fmt == G_IM_FMT_IA) {
                s_fmt = "IA";
            } else {
                s_fmt = "I";
            }

            this->Printf1("gsDPSetColorImage(G_IM_FMT_%s, G_IM_SIZ_%s, %d, %s),", s_fmt, s_siz,
                          EXPAND_WIDTH(this->gfx.setimg.wd), this->segchk(this->gfx.words.w1));
        }
    }
#endif
}

void emu64::dl_G_SETZIMG() {
    EMU64_WARNF("gsDPSetDepthImage(%s),", this->segchk(this->gfx.words.w1));
}

void emu64::dl_G_SETTIMG() {
    Gsetimg2* setimg2 = (Gsetimg2*)EMU64_GFX_COMPACT_PTR;

#ifdef EMU64_DEBUG
    if (this->print_commands & EMU64_PRINT_FLAG_ENABLE) {
        if (setimg2->isDolphin == FALSE) {
            Gsetimg* setimg = (Gsetimg*)setimg2;
            if (this->print_commands != false) {
                const char* s_siz;
                const char* s_fmt;

                u32 siz = setimg->siz;
                u32 fmt = setimg->fmt;

                if (siz == G_IM_SIZ_4b) {
                    s_siz = "4b";
                } else if (siz == G_IM_SIZ_8b) {
                    s_siz = "8b";
                } else if (siz == G_IM_SIZ_16b) {
                    s_siz = "16b";
                } else {
                    s_siz = "32b";
                }

                if (fmt == G_IM_FMT_RGBA) {
                    s_fmt = "RBGA";
                } else if (fmt == G_IM_FMT_YUV) {
                    s_fmt = "YUV";
                } else if (fmt == G_IM_FMT_CI) {
                    s_fmt = "CI";
                } else if (fmt == G_IM_FMT_IA) {
                    s_fmt = "IA";
                } else {
                    s_fmt = "I";
                }

                this->Printf2("gsDPSetTextureImage(G_IM_FMT_%s, G_IM_SIZ_%s, %d, %s),", s_fmt, s_siz,
                              EXPAND_WIDTH(setimg->wd), this->segchk(this->gfx_p->words.w1));
            }
        } else if (this->print_commands) {
            const char* s_siz;
            u32 siz = setimg2->siz;

            if (siz == G_IM_SIZ_4b) {
                s_siz = "4b";
            } else if (siz == G_IM_SIZ_8b) {
                s_siz = "8b";
            } else if (siz == G_IM_SIZ_16b) {
                s_siz = "16b";
            } else {
                s_siz = "32b";
            }

            this->Printf2("gsDPSetTextureImage_Dolphin(G_IM_FMT_%s, G_IM_SIZ_%s, %d, %d, %s),",
                          dolfmttbl2[setimg2->siz][setimg2->fmt], s_siz, EXPAND_WIDTH(setimg2->wd),
                          EXPAND_HEIGHT(setimg2->ht), this->segchk(this->gfx_p->words.w1));
        }
    }
#endif

    this->now_setimg.setimg2 = *setimg2;
#ifdef TARGET_PC
    /* On 64-bit, the full pointer is in gfx_p->words.w1 (uintptr_t).
     * The 32-bit imgaddr bitfield in Gsetimg2 would truncate it. */
    this->resolved_imgaddr = this->seg2k0(this->gfx_p->words.w1);
    this->now_setimg.setimg2.imgaddr = (u32)this->resolved_imgaddr;
#else
    this->now_setimg.setimg2.imgaddr = (u32)this->seg2k0(setimg2->imgaddr);
#endif
}

void emu64::dl_G_SETENVCOLOR() {
    EMU64_LOGF("gsDPSetEnvColor(%d, %d, %d, %d),", (GFX_W1_U32(this->gfx) >> 24) & 0xFF,
               (GFX_W1_U32(this->gfx) >> 16) & 0xFF, (GFX_W1_U32(this->gfx) >> 8) & 0xFF,
               (GFX_W1_U32(this->gfx) >> 0) & 0xFF);

    if (this->environment_color.raw != GFX_W1_U32(this->gfx)) {
        this->environment_color.raw = GFX_W1_U32(this->gfx);
        this->dirty_flags[EMU64_DIRTY_FLAG_ENV_COLOR] = true;
    }
}

void emu64::dl_G_SETBLENDCOLOR() {
    EMU64_LOGF("gsDPSetBlendColor(%d, %d, %d, %d),", (GFX_W1_U32(this->gfx) >> 24) & 0xFF,
               (GFX_W1_U32(this->gfx) >> 16) & 0xFF, (GFX_W1_U32(this->gfx) >> 8) & 0xFF,
               (GFX_W1_U32(this->gfx) >> 0) & 0xFF);

    if (this->blend_color.raw != GFX_W1_U32(this->gfx)) {
        this->blend_color.raw = GFX_W1_U32(this->gfx);
        this->dirty_flags[EMU64_DIRTY_FLAG_BLEND_COLOR] = true;
    }
}

void emu64::dl_G_SETFOGCOLOR() {
    EMU64_LOGF("gsDPSetFogColor(%d, %d, %d, %d),", (GFX_W1_U32(this->gfx) >> 24) & 0xFF,
               (GFX_W1_U32(this->gfx) >> 16) & 0xFF, (GFX_W1_U32(this->gfx) >> 8) & 0xFF,
               (GFX_W1_U32(this->gfx) >> 0) & 0xFF);

    if (this->fog_color.raw != GFX_W1_U32(this->gfx)) {
        this->fog_color.raw = GFX_W1_U32(this->gfx);
        this->dirty_flags[EMU64_DIRTY_FLAG_FOG] = true;
    }
}

void emu64::dl_G_SETFILLCOLOR() {
    EMU64_LOGF("gsDPSetFillColor(0x%08x),", GFX_W1_U32(this->gfx));

    if (this->fill_color.raw != GFX_W1_U32(this->gfx)) {
        this->fill_color.raw = GFX_W1_U32(this->gfx);

        u32 fill_w1 = GFX_W1_U32(this->gfx);
        u16 fill_col = (u16)fill_w1; /* Low 16 bits on little-endian (same as *(u16*)&color) */
        this->fill_tev_color.color.r = (fill_col >> 8) & 0xF8;
        this->fill_tev_color.color.g = (fill_col >> 3) & 0xF8;
        this->fill_tev_color.color.b = (fill_col << 2) & 0xF8;

        this->dirty_flags[EMU64_DIRTY_FLAG_FILL_COLOR] = true;
        this->dirty_flags[EMU64_DIRTY_FLAG_FILL_TEV_COLOR] = true;
    }
}

void emu64::dl_G_SETTEXEDGEALPHA(void) {
    this->tex_edge_alpha = (u8)(GFX_W1_U32(this->gfx) & 0xFF);
    this->dirty_flags[EMU64_DIRTY_FLAG_OTHERMODE_LOW] = TRUE;
}

void emu64::dl_G_SETPRIMDEPTH() {
    EMU64_LOGF("gsDPSetPrimDepth(%d, %d),", (u16)(this->gfx.words.w1 >> 16), (u16)this->gfx.words.w1);

    this->primdepth = this->gfx.words.w1;
}

void emu64::dl_G_SETPRIMCOLOR() {
    EMU64_LOGF("gsDPSetPrimColor(%d, %d, %d, %d, %d, %d),", this->gfx.setcolor.prim_min_level,
               this->gfx.setcolor.prim_level, (GFX_W1_U32(this->gfx) >> 24) & 0xFF,
               (GFX_W1_U32(this->gfx) >> 16) & 0xFF, (GFX_W1_U32(this->gfx) >> 8) & 0xFF,
               (GFX_W1_U32(this->gfx) >> 0) & 0xFF);

    if (this->primitive_color.raw != GFX_W1_U32(this->gfx)) {
        this->primitive_color.raw = GFX_W1_U32(this->gfx);
        this->dirty_flags[EMU64_DIRTY_FLAG_PRIM_COLOR] = true;
    }

    if (this->fill_tev_color.color.a != this->gfx.setcolor.prim_level) {
        this->fill_tev_color.color.a = this->gfx.setcolor.prim_level;
        this->dirty_flags[EMU64_DIRTY_FLAG_FILL_TEV_COLOR] = true;
    }
}

void emu64::dl_G_RDPFULLSYNC() {
    EMU64_WARN("gsDPFullSync(),");
}

void emu64::dl_G_RDPPIPESYNC() {
    EMU64_LOG("gsDPPipeSync(),");

    if (aflags[AFLAGS_FORCE_PIPE_SYNC] == 1 || (aflags[AFLAGS_FORCE_PIPE_SYNC] == 0 && this->rdp_pipe_sync_needed)) {
        this->rdp_pipe_sync_needed = false;
    }
}

void emu64::dl_G_RDPTILESYNC() {
    EMU64_LOG("gsDPTileSync(),");
}

void emu64::dl_G_RDPLOADSYNC() {
    EMU64_LOG("gsDPLoadSync(),");
}

void emu64::dl_G_NOOP() {
    Gnoop* noop = (Gnoop*)EMU64_GFX_COMPACT_PTR;

    switch (noop->tag) {
        case G_TAG_NONE:
#ifdef TARGET_PC
            /* PC widescreen: skip aspect correction for transitions / bg blits.
             * See pc_platform.h for how the marker/flag mechanism works. */
            if (this->gfx.words.w1 == PC_NOOP_WIDESCREEN_STRETCH) {
                g_pc_widescreen_stretch = 1;
                break;
            }
            if (this->gfx.words.w1 == PC_NOOP_WIDESCREEN_STRETCH_OFF) {
                g_pc_widescreen_stretch = 2; /* pillarbox mode for UI */
                break;
            }
#endif
            if (this->gfx.words.w1 == 0) {
                EMU64_LOG("gsDPNoOp(),");
            } else {
                EMU64_LOGF("gsDPNoOpTag(%08x),", (u32)this->gfx.words.w1);
            }
            break;
        case G_TAG_HERE:
            EMU64_WARNF("gsDPNoOpHere([%s:%d]),", (char*)(uintptr_t)this->gfx.words.w1, noop->param0);
            break;
        case G_TAG_STRING:
            EMU64_WARNF("gsDPNoOpString(%c%s%c, %d),", '"', (char*)(uintptr_t)this->gfx.words.w1, '"', noop->param0);
            break;
        case G_TAG_WORD:
            EMU64_WARNF("gsDPNoOpWord(0x%08x, %d),", (u32)this->gfx.words.w1, noop->param0);
            break;
        case G_TAG_FLOAT: {
            u32 float_bits = (u32)this->gfx.words.w1;
            EMU64_WARNF("gsDPNoOpFloat(%8.3f, %d),", *(f32*)&float_bits, noop->param0);
        } break;
        case G_TAG_INFO:
            if (noop->param0 == 0) {
                EMU64_WARN("gsDPNoOpQuiet(),");
            } else {
                EMU64_WARN("gsDPNoOpVerbose(),");
            }

            this->print_commands = noop->param0;
            break;
        case G_TAG_CALLBACK:
/* They forgot to pass arguments here */
#ifdef EMU64_FIX_NOOP_CALLBACK_LOG
            EMU64_WARNF("gsDPNoOpCallBack(%08x,%d),", (u32)this->gfx.words.w1, noop->param0);
#else
            EMU64_WARN("gsDPNoOpCallBack(%08x,%d),");
#endif
            break;
        case G_TAG_OPENDISP:
            EMU64_WARNF("gsDPNoOpOpenDisp([%s:%d]),", (char*)(uintptr_t)this->gfx.words.w1, noop->param0);
            break;
        case G_TAG_CLOSEDISP:
            EMU64_WARNF("gsDPNoOpCloseDisp([%s:%d]),", (char*)(uintptr_t)this->gfx.words.w1, noop->param0);
            break;
        case G_TAG_FILL:
            EMU64_WARN("gsDPNoOpFill(), /* ### 何じゃコリャ */"); /* Rough translation: ### What the hell */
            this->num_unknown_cmds++;
            break;
        default:
            EMU64_WARNF("gsDPNoOpTag3(%02x, %08x, %04x),", tag, (u32)this->gfx.words.w1, noop->param0);
            break;
    }
}

void emu64::dl_G_MTX() {
    if (this->print_commands & EMU64_PRINTF_ENABLED_FLAG) {
        uintptr_t mtx_w1 = this->gfx_p->words.w1;
        EMU64_LOGF("gsSPMatrix(%s, 0", this->segchk(mtx_w1));

        for (int i = 0; i < ARRAY_COUNT(gmtxtbl); i++) {
            EMU64_LOGF("|%s", ((((Gmtx*)EMU64_GFX_COMPACT_PTR)->type ^ G_MTX_PUSH) & gmtxtbl[i].mask) == 0 ? gmtxtbl[i].disabled
                                                                                                 : gmtxtbl[i].enabled);
        }

        EMU64_LOG("),");

        if ((this->print_commands & EMU64_PRINTF3_FLAG) != 0) {
            EMU64_LOGF("%08x %08x %08x\n", (u32)mtx_w1, this->seg2k0(mtx_w1), this->seg2k0(mtx_w1));
            this->disp_matrix((MtxP)this->seg2k0(mtx_w1));
        }
    }

    if (this->disable_polygons == false) {
        EMU64_TIMED_SEGMENT_BEGIN();

        Gmtx* mtx_gfx = (Gmtx*)EMU64_GFX_COMPACT_PTR;
        Mtx_t* mtx =
            (Mtx_t*)this->seg2k0(this->gfx_p->words.w1); /* Matrix is in N64 s16.16 format. (First 8 elements are s16 integer
                                                    components, second 8 elements are s16 fractional components) */
#ifdef TARGET_PC
        if (mtx == NULL) {
            EMU64_TIMED_SEGMENT_END(matrix_time);
            return;
        }
#endif
#ifdef PC_GX_VERBOSE
        {
            extern int diag_frame;
            static int mtx_cmd_frame = -1, mtx_cmd_count = 0;
            if (diag_frame != mtx_cmd_frame) { mtx_cmd_frame = diag_frame; mtx_cmd_count = 0; }
            if (diag_frame == 6) {
                mtx_cmd_count++;
                printf("[MTX CMD #%d] %s %s %s type=0x%02X\n", mtx_cmd_count,
                       (mtx_gfx->type & G_MTX_PROJECTION) != G_MTX_MODELVIEW ? "PROJ" : "MV",
                       (mtx_gfx->type & G_MTX_LOAD) != G_MTX_MUL ? "LOAD" : "MUL",
                       (mtx_gfx->type & G_MTX_PUSH) == G_MTX_NOPUSH ? "PUSH" : "NOPUSH",
                       mtx_gfx->type);
            }
        }
#endif
        GC_Mtx mtx34;
        Mtx44 mtx44; /* float-based matrix */

        /* Convert our s16.u16 matrix into a f32 matrix. */
        N64Mtx_to_DOLMtx((Mtx*)mtx, mtx34);

        if ((mtx_gfx->type & G_MTX_PROJECTION) != G_MTX_MODELVIEW) { /* Projection */
            N64Mtx_to_DOLMtx((Mtx*)mtx, mtx44);
            if ((mtx_gfx->type & G_MTX_LOAD) != G_MTX_MUL) {
                {
#ifdef TARGET_PC
                /* Detect perspective vs orthographic from the converted float matrix.
                   For perspective: mtx44[2][3] is large (near*far term, typically hundreds).
                   For orthographic: mtx44[2][3] is 0 or very small (-(f+n)/(f-n), often 0
                   for symmetric near/far).
                   The original (*mtx)[1][3] check fails on 64-bit because Mtx_t uses
                   `long` (8 bytes) so array indexing reads wrong offsets.
                   Also, N64Mtx_to_DOLMtx only converts 3 rows, so mtx44[3][3] is
                   uninitialized and can't be used. */
                int is_perspective = (fabsf(mtx44[2][3]) > 1.0f);
#else
                int is_perspective = ((u16)(*mtx)[1][3] == 0);
#endif
                if (is_perspective) { /* If the last entry is 0, this should be a perspective projection.
                                                 Otherwise, it's likely an orthographic projection. */
                    this->near = mtx44[2][3] * ((mtx44[2][2] + 1.0f) / (mtx44[2][2] - 1.0f) - 1.0f) / 2.0f;
                    this->far = this->near * ((mtx44[2][2] - 1.0f) / (mtx44[2][2] + 1.0f) + 1.0f);
                    mtx44[2][2] = this->near / (this->near - this->far);
                    mtx44[2][3] = (this->near * this->far) / (this->near - this->far);
                    bcopy(mtx34, this->original_projection_mtx, sizeof(this->original_projection_mtx));
                    bcopy(mtx44, this->projection_mtx, sizeof(Mtx44));
                    this->projection_type = GX_PERSPECTIVE;
                } else { /* Orthographic projection */
#ifdef PC_GX_VERBOSE
                    {
                        extern int diag_frame;
                        if (diag_frame == 6) {
                            printf("[ORTHO PROJ] mtx44: [%.6f %.6f %.6f %.6f] [%.6f %.6f %.6f %.6f] [%.6f %.6f %.6f %.6f]\n",
                                   mtx44[0][0], mtx44[0][1], mtx44[0][2], mtx44[0][3],
                                   mtx44[1][0], mtx44[1][1], mtx44[1][2], mtx44[1][3],
                                   mtx44[2][0], mtx44[2][1], mtx44[2][2], mtx44[2][3]);
                        }
                    }
#endif
                    this->near = (mtx44[2][3] + 1.0f) / mtx44[2][2];
                    this->far = (mtx44[2][3] - 1.0f) / mtx44[2][2];
                    mtx44[2][2] = 1.0f / (this->near - this->far);
                    mtx44[2][3] = this->far / (this->near - this->far);
                    bcopy(mtx34, this->original_projection_mtx, sizeof(this->original_projection_mtx));
                    /* @BUG - this overwrites part of the first entry in model_view_mtx_stack */
                    bcopy(mtx44, this->projection_mtx, sizeof(Mtx44));
                    this->projection_type = GX_ORTHOGRAPHIC;
                }

                MTXIdentity(this->position_mtx);
                this->dirty_flags[EMU64_DIRTY_FLAG_PROJECTION_MTX] = true;
                this->dirty_flags[EMU64_DIRTY_FLAG_FOG] = true;
                } /* end perspective/ortho block */
            } else {
                bcopy(mtx44, &this->position_mtx, sizeof(GC_Mtx)); /* Last row of Mtx44 is ignored */
            }
        } else { /* Modelview */
            GC_Mtx& concat_src = this->model_view_mtx_stack[this->mtx_stack_size];

            if ((mtx_gfx->type & G_MTX_PUSH) == G_MTX_NOPUSH) {
                if (this->mtx_stack_size < MTX_STACK_SIZE - 1) {
                    this->mtx_stack_size++;
                } else {
                    this->Printf0("gsSPMatrix StackOverflow.\n");
                    this->err_count++;
                }
            }

            GC_Mtx& model_view_src = this->model_view_mtx_stack[this->mtx_stack_size];
            if ((mtx_gfx->type & G_MTX_LOAD) != G_MTX_MUL) {
                bcopy(mtx34, model_view_src, sizeof(GC_Mtx));
            } else {
                MTXConcat(concat_src, mtx34, model_view_src);
            }

            if (aflags[AFLAGS_COPY_POSITION_MTX] == 0) {
                GC_Mtx& src = this->model_view_mtx_stack[mtx_stack_size];

                for (int i = 0; i < 3; i++) {
                    this->model_view_mtx[i][0] = src[i][0];
                    this->model_view_mtx[i][1] = src[i][1];
                    this->model_view_mtx[i][2] = src[i][2];
                    this->model_view_mtx[i][3] = 0.0f;
                }
            } else {
                MTXCopy(this->model_view_mtx_stack[this->mtx_stack_size], this->model_view_mtx);
                this->model_view_mtx[0][3] = 0.0f;
                this->model_view_mtx[1][3] = 0.0f;
                this->model_view_mtx[2][3] = 0.0f;
            }

            if (aflags[AFLAGS_SKIP_MTX_NORMALIZATION] == 0 || this->geometry_mode & G_TEXTURE_GEN != 0) {
                /* Normalize matrix */
                guMtxNormalize(this->model_view_mtx);
            }

            GXLoadNrmMtxImm(this->model_view_mtx, NONSHARED_MTX);
        }

        this->dirty_flags[EMU64_DIRTY_FLAG_POSITION_MTX] = true;
        if (this->dirty_flags[EMU64_DIRTY_FLAG_POSITION_MTX] != false) {
            this->dirty_flags[EMU64_DIRTY_FLAG_POSITION_MTX] = false;
            MTXConcat(position_mtx, this->model_view_mtx_stack[mtx_stack_size],
                      this->position_mtx_stack[mtx_stack_size]);
            GXLoadPosMtxImm(this->position_mtx_stack[this->mtx_stack_size], NONSHARED_MTX);
        }

        EMU64_TIMED_SEGMENT_END(matrix_time);
    }
}

void emu64::dl_G_VTX() {
    EMU64_TIMED_SEGMENT_BEGIN();

    Gvtx* vtx_gfx = (Gvtx*)EMU64_GFX_COMPACT_PTR;
    u32 n = vtx_gfx->n; /* number of vertices */
    int vn = vtx_gfx->vn;
    u32 v0 = (vn >> 1) - n; /* first vertex to load */

    this->total_vertices += n;

    this->vtx_load_calls++;

    if ((this->print_commands & EMU64_PRINTF_ENABLED_FLAG)) {
        EMU64_LOGF("gsSPVertex(%s, %d, %d),", this->segchk(this->gfx.words.w1), n, v0);
        if ((this->print_commands & EMU64_PRINTF3_FLAG) != 0) {
            this->work_ptr = (void*)this->seg2k0(this->gfx.words.w1);
            this->show_vtx((Vtx*)work_ptr, n, v0);
        }
    }

    if (this->disable_polygons == false) {
        Vtx* vtx_p = (Vtx*)this->seg2k0(this->gfx.words.w1);
#ifdef TARGET_PC
        if (vtx_p == NULL) {
            EMU64_TIMED_SEGMENT_END(spvertex_time);
            return;
        }
#endif
#ifdef PC_GX_VERBOSE
        {
            static int vtx_diag_done = 0;
            if (vtx_diag_done < 2) {
                int has_nonzero = 0;
                for (u32 di = 0; di < n && !has_nonzero; di++) {
                    if (vtx_p[di].n.ob[0] != 0 || vtx_p[di].n.ob[1] != 0 || vtx_p[di].n.ob[2] != 0)
                        has_nonzero = 1;
                }
                if (vtx_diag_done == 0 || has_nonzero) {
                    printf("[VTX DIAG] %s: n=%d v0=%d\n",
                           vtx_diag_done == 0 ? "First SPVertex" : "First non-zero SPVertex", n, v0);
                    if (vtx_diag_done == 0 && !has_nonzero) vtx_diag_done = 1;
                    else vtx_diag_done = 2;
                }
            }
        }
#endif
        Vertex* emu_vtx_p = &this->vertices[v0];

        GC_Mtx& position_mtx = this->position_mtx_stack[this->mtx_stack_size];
        if ((this->print_commands & (1 << 5)) != 0) {
            /* NOTE: They print a 4x4 matrix, but position matrix is only 3x4. */
            this->disp_matrix(position_mtx);
        }

        while (n != 0) {
            /* Convert position */
            OSs16tof32(&vtx_p->n.ob[0], &emu_vtx_p->position.x);
            OSs16tof32(&vtx_p->n.ob[1], &emu_vtx_p->position.y);
            OSs16tof32(&vtx_p->n.ob[2], &emu_vtx_p->position.z);

            /* Flag */
            if (aflags[AFLAGS_FORCE_VTX_FLAG_COPY] == 0 && (this->geometry_mode & G_TEXTURE_GEN) != 0) {
                emu_vtx_p->flag = MTX_SHARED;
            } else {
                emu_vtx_p->flag = vtx_p->n.flag & MTX_NONSHARED;
            }

            /* Texture Coordinates */
            emu_vtx_p->tex_coords.s = vtx_p->n.tc[0];
            emu_vtx_p->tex_coords.t = vtx_p->n.tc[1];

            /* Normal */
            emu_vtx_p->normal.x = fastcast_float(&vtx_p->n.n[0]);
            emu_vtx_p->normal.y = fastcast_float(&vtx_p->n.n[1]);
            emu_vtx_p->normal.z = fastcast_float(&vtx_p->n.n[2]);

            /* Check vertex normal modification type. In AC/e+ only VECNormalize is utilized. */
            if (aflags[AFLAGS_VTX_NORMAL_MODIFY_TYPE] == 0 && (this->geometry_mode & G_TEXTURE_GEN) != 0) {
                PSVECNormalize(&emu_vtx_p->normal, &emu_vtx_p->normal);
            } else if (aflags[AFLAGS_VTX_NORMAL_MODIFY_TYPE] == 2) {
                emu_vtx_p->normal.x *= (1.0f / 120.0f);
                emu_vtx_p->normal.y *= (1.0f / 120.0f);
                emu_vtx_p->normal.z *= (1.0f / 120.0f);
            } else if (aflags[AFLAGS_VTX_NORMAL_MODIFY_TYPE] == 3) {
                emu_vtx_p->normal.x *= (1.0f / 128.0f);
                emu_vtx_p->normal.y *= (1.0f / 128.0f);
                emu_vtx_p->normal.z *= (1.0f / 128.0f);
            }

            /* Convert vectors to correct space */
            if ((emu_vtx_p->flag & MTX_NONSHARED) == MTX_SHARED) {
                PSMTXMultVec(position_mtx, &emu_vtx_p->position,
                             &emu_vtx_p->position); /* Position -> Projection Matrix */
                PSMTXMultVec(this->model_view_mtx, &emu_vtx_p->normal, &emu_vtx_p->normal); /* Normal -> View Matrix */
            }

            /* Color */
            emu_vtx_p->color.raw = *(u32*)(&vtx_p->v.cn[0]);

            vtx_p++;
            emu_vtx_p++;
            n--;
        }
    }

    EMU64_TIMED_SEGMENT_END(spvertex_time);
}

void emu64::dl_G_MODIFYVTX() {
#ifdef EMU64_DEBUG
    if (this->print_commands != false) {
        u8 where = this->gfx.dma.par;
        const char* s_where;
        if (where == G_MWO_POINT_RGBA) {
            s_where = "RGBA";
        } else if (where == G_MWO_POINT_ST) {
            s_where = "ST";
        } else if (where == G_MWO_POINT_XYSCREEN) {
            s_where = "XYSCREEN";
        } else if (where == G_MWO_POINT_ZSCREEN) {
            s_where = "ZSCREEN";
        } else {
            s_where = "???";
        }

        this->Printf2("gsSPModifyVertex(%d, G_MWO_POINT_%s, %08x),", (u16)(this->gfx.words.w0), s_where,
                      this->gfx.words.w1);
    }
#endif

/* This is broken. G_MODIFYVTX modifies a single vertex. They use the "where" component instead of adding one. */
#ifdef EMU64_FIX_MODIFYVTX_LOADED_COUNT
    this->total_vertices++;
#else
    this->total_vertices += this->gfx.dma.par;
#endif

    this->vtx_load_calls++;
    this->Printf0("gsSPModifyVertexはサポートされていません\n"); /* Translation: gsSPModifyVertex is unsupported */
}

void emu64::dl_G_LINE3D() {
    Gline3D_new* line = (Gline3D_new*)EMU64_GFX_COMPACT_PTR;

    if (line->wd == 0) {
        EMU64_LOGF("gsSPLine3D(%d, %d),", line->v0, line->v1);
    } else {
        EMU64_LOGF("gsSPLineW3D(%d, %d, %d),", line->v0, line->v1, line->wd);
    }

    this->lines++;
    this->Printf0("gsSPLine3Dはサポートされていません"); /* Translation: gsSPLine3D is unsupported */
}

void emu64::dl_G_TRI1() {
    Gtri1 tri_gfx = *(Gtri1*)EMU64_GFX_COMPACT_PTR;
    u32 v0 = tri_gfx.v0 / 2;
    u32 v1 = tri_gfx.v1 / 2;
    u32 v2 = tri_gfx.v2 / 2;

    EMU64_TIMED_SEGMENT_BEGIN();

    EMU64_LOGF("gsSP1Triangle(%d, %d, %d, 0),", v0, v1, v2);

    if (aflags[AFLAGS_MAX_POLYGONS] != 0) {
        EMU64_LOGF(" [%d] @@@", this->polygons);
    }

    if (this->disable_polygons == false && EMU64_CAN_DRAW_POLYGON()) {
        this->dirty_check(this->texture_gfx.tile, this->texture_gfx.level, TRUE);
        this->setup_1tri_2tri_1quad(v0);
        this->draw_1tri_2tri_1quad(3, v0, v1, v2);
    }

    this->triangles++;
    this->polygons++;

    EMU64_TIMED_SEGMENT_END(polygons_time);
}

void emu64::dl_G_TRIN_INDEPEND() {
    this->dl_G_TRIN();
}

void emu64::dl_G_TRIN() {
    Gtrin* g;
    int n_faces;
    int first_pass = TRUE;
    Gfx* first_cmd = this->gfx_p;
    int is_7bit = (first_cmd->words.w1 & POLY_BITMASK) == POLY_7b;
    int first_vtx = is_7bit ? POLY_GET_V0_7b(first_cmd) : POLY_GET_V0_5b(first_cmd);

    EMU64_TIMED_SEGMENT_BEGIN();

    this->dirty_check(this->texture_gfx.tile, this->texture_gfx.level, TRUE);

    this->setup_1tri_2tri_1quad(first_vtx);
    n_faces = ((first_cmd->words.w0 >> 17) & 0x7F) + 1;
    int n_verts = n_faces * 3;


    EMU64_LOGF("gsSPNTriangles(%d),\n", n_faces);
    if (aflags[AFLAGS_WIREFRAME] == 0) {
        GXBegin(GX_TRIANGLES, GX_VTXFMT0, n_verts);
    }

    while (n_faces > 0) {
        g = (Gtrin*)this->gfx_p;
        Gfx* gcmd = (Gfx*)g;

        if ((gcmd->words.w1 & POLY_BITMASK) == POLY_5b) {
            this->gfx_p++;
            /* 5 bits per vertex index, first pass = 3 faces, consecutive passes = 4 faces */
            int v0 = POLY_GET_V0_5b(gcmd);
            int v1 = POLY_GET_V1_5b(gcmd);
            int v2 = POLY_GET_V2_5b(gcmd);
            this->set_position3(v0, v1, v2);
            this->polygons++;
            EMU64_LOGF("gsSPNTriangleData1(%d, %d, %d, 0),\n", v0, v1, v2);

            n_faces--;
            if (n_faces == 0)
                break;

            int v3 = POLY_GET_V3_5b(gcmd);
            int v4 = POLY_GET_V4_5b(gcmd);
            int v5 = POLY_GET_V5_5b(gcmd);
            this->set_position3(v3, v4, v5);
            this->polygons++;
            EMU64_LOGF("gsSPNTriangleData1(%d, %d, %d, 0),\n", v3, v4, v5);

            n_faces--;
            if (n_faces == 0)
                break;

            int v6 = POLY_GET_V6_5b(gcmd);
            int v7 = POLY_GET_V7_5b(gcmd);
            int v8 = POLY_GET_V8_5b(gcmd);
            this->set_position3(v6, v7, v8);
            this->polygons++;
            EMU64_LOGF("gsSPNTriangleData1(%d, %d, %d, 0),\n", v6, v7, v8);

            n_faces--;
            if (n_faces == 0)
                break;

            /* Only 3 faces on the first pass */
            if (first_pass) {
                first_pass = FALSE;
            } else {
                int v9 = POLY_GET_V9_5b(gcmd);
                int v10 = POLY_GET_V10_5b(gcmd);
                int v11 = POLY_GET_V11_5b(gcmd);
                this->set_position3(v9, v10, v11);
                this->polygons++;
                EMU64_LOGF("gsSPNTriangleData1(%d, %d, %d, 0),\n", v9, v10, v11);

                n_faces--;
                if (n_faces == 0)
                    break;
            }
        } else {
            this->gfx_p++;

            /* 7 bits per vertex index, max 3 faces per Gfx */
            int v0 = POLY_GET_V0_7b(gcmd);
            int v1 = POLY_GET_V1_7b(gcmd);
            int v2 = POLY_GET_V2_7b(gcmd);
            this->set_position3(v0, v1, v2);
#ifdef EMU64_FIXES
            this->polygons++;
#endif
            EMU64_LOGF("gsSPNTriangleData1(%d, %d, %d, 0),\n", v0, v1, v2);

            n_faces--;
            if (n_faces == 0)
                break;

            int v3 = POLY_GET_V3_7b(gcmd);
            int v4 = POLY_GET_V4_7b(gcmd);
            int v5 = POLY_GET_V5_7b(gcmd);
            this->set_position3(v3, v4, v5);

#ifdef EMU64_FIXES
            this->polygons++;
#endif
            EMU64_LOGF("gsSPNTriangleData1(%d, %d, %d, 0),\n", v3, v4, v5);

            n_faces--;
            if (n_faces == 0)
                break;

            /* Only 2 faces on the first pass */
            if (first_pass) {
                first_pass = FALSE;
            } else {
                int v6 = POLY_GET_V6_7b(gcmd);
                int v7 = POLY_GET_V7_7b(gcmd);
                int v8 = POLY_GET_V8_7b(gcmd);
                this->set_position3(v6, v7, v8);
#ifdef EMU64_FIXES
                this->polygons++;
#endif
                EMU64_LOGF("gsSPNTriangleData1(%d, %d, %d, 0),\n", v6, v7, v8);

                n_faces--;
                if (n_faces == 0)
                    break;
            }
        }
    }

    this->gfx_p += (int)n_faces - 1; /* Should equate to gfx_p--, as the emulator will increment it once. */

#ifdef TARGET_PC
    /* Flush triangle batch immediately. On real HW the GXEnd is implicit,
       but our deferred vertex model needs an explicit flush so that state
       changes (viewport, projection) between batches don't affect this draw. */
    GXEnd();
#endif

    EMU64_TIMED_SEGMENT_END(polygons_time);
    this->rdp_pipe_sync_needed = true;
}

void emu64::dl_G_QUADN() {
    Gquad* g;
    int n_faces;
    int first_pass = TRUE;
    Gfx* first_cmd = this->gfx_p;
    int is_7bit = (first_cmd->words.w1 & POLY_BITMASK) == POLY_7b;
    int first_vtx = is_7bit ? ((first_cmd->words.w1 >> 4) & 0x7F) : ((first_cmd->words.w1 >> 4) & 0x1F);

    EMU64_TIMED_SEGMENT_BEGIN();

    this->dirty_check(this->texture_gfx.tile, this->texture_gfx.level, TRUE);
    this->setup_1tri_2tri_1quad(first_vtx);
    n_faces = ((first_cmd->words.w0 >> 17) & 0x7F) + 1;
    int n_verts = n_faces * 4;

    EMU64_LOGF("gsSPNQuadrangles(%d),\n", n_faces);
    if (aflags[AFLAGS_WIREFRAME] == 0) {
        GXBegin(GX_QUADS, GX_VTXFMT0, n_verts);
    }

    while (n_faces > 0) {
        g = (Gquad*)this->gfx_p;
        Gfx* gcmd = (Gfx*)g;
        if ((gcmd->words.w1 & POLY_BITMASK) == POLY_5b) {
            this->gfx_p++;
            /* 5 bits per vertex index, first pass = 2 faces, consecutive passes = 3 faces */
            int v0 = POLY_GET_V0_5b(gcmd);
            int v1 = POLY_GET_V1_5b(gcmd);
            int v2 = POLY_GET_V2_5b(gcmd);
            int v3 = POLY_GET_V3_5b(gcmd);
            this->set_position4(v0, v1, v2, v3);
            this->polygons++;
            EMU64_LOGF("gsSPNQuadrangleData1(%d, %d, %d, %d, 0),\n", v0, v1, v2, v3);

            n_faces--;
            if (n_faces == 0)
                break;

            int v4 = POLY_GET_V4_5b(gcmd);
            int v5 = POLY_GET_V5_5b(gcmd);
            int v6 = POLY_GET_V6_5b(gcmd);
            int v7 = POLY_GET_V7_5b(gcmd);
            this->set_position4(v4, v5, v6, v7);
            this->polygons++;
            EMU64_LOGF("gsSPNQuadrangleData1(%d, %d, %d, %d, 0),\n", v4, v5, v6, v7);

            n_faces--;
            if (n_faces == 0)
                break;

            /* Only 2 faces on the first pass */
            if (first_pass) {
                first_pass = FALSE;
            } else {
                int v8 = POLY_GET_V8_5b(gcmd);
                int v9 = POLY_GET_V9_5b(gcmd);
                int v10 = POLY_GET_V10_5b(gcmd);
                int v11 = POLY_GET_V11_5b(gcmd);
                this->set_position4(v8, v9, v10, v11);
                this->polygons++;
                EMU64_LOGF("gsSPNQuadrangleData1(%d, %d, %d, %d, 0),\n", v8, v9, v10, v11);

                n_faces--;
                if (n_faces == 0)
                    break;
            }
        } else {
            this->gfx_p++;
            /* 7 bits per vertex index, max 2 faces per Gfx */
            int v0 = (gcmd->words.w1 >> 4) & 0x7F;
            int v1 = (gcmd->words.w1 >> 11) & 0x7F;
            int v2 = (gcmd->words.w1 >> 18) & 0x7F;
            int v3 = (gcmd->words.w1 >> 25) & 0x7F;

            this->set_position4(v0, v1, v2, v3);
#ifdef EMU64_FIXES
            this->polygons++;
#endif
            EMU64_LOGF("gsSPNQuadrangleData1(%d, %d, %d, %d, 0),\n", v0, v1, v2, v3);

            n_faces--;
            if (n_faces == 0)
                break;

            /* Only 1 face on the first pass */
            if (first_pass) {
                first_pass = FALSE;
            } else {
                int q0 = (gcmd->words.w0 >> 4) & 0x7F;
                int q1 = (gcmd->words.w0 >> 11) & 0x7F;
                int q2 = (gcmd->words.w0 >> 18) & 0x7F;
                int q3 = (gcmd->words.w0 >> 25) & 0x7F;
                this->set_position4(q0, q1, q2, q3);
#ifdef EMU64_FIXES
                this->polygons++;
#endif
                EMU64_LOGF("gsSPNQuadrangleData1(%d, %d, %d, %d, 0),\n", q0, q1, q2, q3);

                n_faces--;
                if (n_faces == 0)
                    break;
            }
        }
    }

    this->gfx_p += (int)n_faces - 1; /* Should equate to gfx_p--, as the emulator will increment it once. */

#ifdef TARGET_PC
    GXEnd();
#endif

    EMU64_TIMED_SEGMENT_END(polygons_time);
    this->rdp_pipe_sync_needed = true;
}

void emu64::dl_G_TRI2() {
    int unused[2];
    u32 commands;
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    u32 v4;
    u32 v5;

    /**
     * NOTE: Looks like the devs made an optimization by counting up all TRI2 & TRI1
     * calls in sequence and executing them in one call. Probably an early version of
     * TRIN/TRIN_INDEPEND which seem to dominate AC's display list polygon calls.
     */

    if (this->disable_polygons || aflags[AFLAGS_MAX_POLYGONS] || aflags[AFLAGS_WIREFRAME]) {
        Gtri2 tris = *((Gtri2*)EMU64_GFX_COMPACT_PTR);

        v0 = tris.t0v0 / 2;
        v1 = tris.t0v1 / 2;
        v2 = tris.t0v2 / 2;
        v3 = tris.t1v0 / 2;
        v4 = tris.t1v1 / 2;
        v5 = tris.t1v2 / 2;

        EMU64_TIMED_SEGMENT_BEGIN();

        EMU64_LOGF("gsSP2Triangles(%d, %d, %d, 0, %d, %d, %d, 0),", v0, v1, v2, v3, v4, v5);

        if (aflags[AFLAGS_MAX_POLYGONS] != 0) {
            EMU64_LOGF(" [%d] @@@", this->polygons);
        }

        if (!this->disable_polygons && EMU64_CAN_DRAW_POLYGON()) {
            this->dirty_check(this->texture_gfx.tile, this->texture_gfx.level, TRUE);
            this->setup_1tri_2tri_1quad(v0);
            this->draw_1tri_2tri_1quad(6, v0, v1, v2, v3, v4, v5);
        }

        this->double_triangles++;
        this->polygons++;
#ifdef EMU64_DEBUG
        this->polygons_time += (osGetCount() - start);
#endif
    } else {
        /* Count up all the vertices */
        commands = 0;
        int n_verts = 0;

        int i = 0;
        while (TRUE) {
            if (this->gfx_p[i].tri.cmd == G_TRI2) {
                n_verts += 6;
            } else if (this->gfx_p[i].tri.cmd == G_TRI1) {
                n_verts += 3;
            } else {
                break;
            }
            i++;
            commands++;
        }

        this->dirty_check(this->texture_gfx.tile, this->texture_gfx.level, TRUE);
        u64 t_g;
        t_g = *(u64*)&this->gfx_p->words;
        Gtri2* tri2 = (Gtri2*)&t_g;
        this->setup_1tri_2tri_1quad(tri2->t0v0 / 2);

#ifdef EMU64_DEBUG
        u32 start = osGetCount();
#endif

        if (aflags[AFLAGS_WIREFRAME] == 0) {
            GXBegin(GX_TRIANGLES, GX_VTXFMT0, n_verts);
        }

        for (u32 i = 0; i < commands; i++) {
#if UINTPTR_MAX > 0xFFFFFFFFu
            u32 _tri2_buf[2] = { this->gfx_p[i].words.w0, (u32)this->gfx_p[i].words.w1 };
            Gtri2 g = *(Gtri2*)_tri2_buf;
#else
            Gtri2 g = *(Gtri2*)&this->gfx_p[i].words;
#endif
            u32 v0 = g.t0v0 / 2;
            u32 v1 = g.t0v1 / 2;
            u32 v2 = g.t0v2 / 2;
            this->set_position3(v0, v1, v2);
            if (this->gfx_p[i].tri.cmd == G_TRI2) {
                u32 v3 = g.t1v0 / 2;
                u32 v4 = g.t1v1 / 2;
                u32 v5 = g.t1v2 / 2;

                EMU64_LOGF("gsSP2Triangles(%d, %d, %d, 0, %d, %d, %d, 0),", v0, v1, v2, v3, v4, v5);

                this->set_position3(v3, v4, v5);
            } else {
                EMU64_LOGF("gsSP1Triangle(%d, %d, %d, 0),", v0, v1, v2);
            }
        }

        this->gfx_p += (commands - 1);
        EMU64_TIMED_SEGMENT_END(polygons_time);
    }

#ifdef TARGET_PC
    GXEnd();
#endif

    this->rdp_pipe_sync_needed = true;
}

void emu64::dl_G_QUAD() {
    Gquad0 q = *(Gquad0*)EMU64_GFX_COMPACT_PTR;
    u32 v0 = q.v0 / 2;
    u32 v1 = q.v1 / 2;
    u32 v2 = q.v2 / 2;
    u32 v3 = q.v3 / 2;

    EMU64_TIMED_SEGMENT_BEGIN();

    EMU64_LOGF("gsSP1Quadrangle(%d, %d, %d, %d, 0),", v0, v1, v2, v3);

    if (aflags[AFLAGS_MAX_POLYGONS]) {
        EMU64_LOGF(" [%d] @@@", this->polygons);
    }

    if (this->disable_polygons == false && EMU64_CAN_DRAW_POLYGON()) {
        this->setup_1tri_2tri_1quad(v0);
        this->draw_1tri_2tri_1quad(4, v0, v1, v2, v3);
    }

    this->polygons++;
    this->quads++;
    EMU64_TIMED_SEGMENT_END(polygons_time);
}

void emu64::dl_G_CULLDL() {
    f32 ox;
    f32 oy;
    f32 oz;
    u32 vstart = ((Gculldl*)EMU64_GFX_COMPACT_PTR)->vstart / 2;
    u32 vend = ((Gculldl*)EMU64_GFX_COMPACT_PTR)->vend / 2;
    u32 mask;
    u32 i;
    Vertex* vtx;

    EMU64_WARNF("gsSPCullDisplayList(%d, %d),", vstart, vend);

    EMU64_LOG("vn mask   x     y    z  \n");
    mask = G_CULL_Z_GREATERTHAN | G_CULL_Z_LESSTHAN | G_CULL_Y_GREATERTHAN | G_CULL_Y_LESSTHAN | G_CULL_X_GREATERTHAN |
           G_CULL_X_LESSTHAN; /* 0x3F00 */

    for (i = vstart; i <= vend; i++) {
        vtx = &this->vertices[i];
        /* Recompute cull classification fresh each call; keep only non-cull flag bits. */
        vtx->flag &= ~(G_CULL_Z_GREATERTHAN | G_CULL_Z_LESSTHAN |
                       G_CULL_Y_GREATERTHAN | G_CULL_Y_LESSTHAN |
                       G_CULL_X_GREATERTHAN | G_CULL_X_LESSTHAN);

        /* Vertex position -> camera space calculations */
        if ((vtx->flag & MTX_NONSHARED) == MTX_SHARED) {
#ifdef EMU64_DEBUG
            if (this->print_commands != false) {
                this->print_guMtxXFM1F_dol2(this->projection_mtx, this->projection_type, vtx->position.x,
                                            vtx->position.y, vtx->position.z);
            }
#endif

            guMtxXFM1F_dol2(this->projection_mtx, this->projection_type, vtx->position.x, vtx->position.y,
                            vtx->position.z, &ox, &oy, &oz);
        } else {
            /* MTX_NONSHARED */
            Vec oVec;
            if (aflags[AFLAGS_USE_GUVECMULT] == 0) {
                PSMTXMultVec(this->position_mtx_stack[this->mtx_stack_size], &vtx->position, &oVec);
            } else {
                guMtxXFM1F_dol(this->position_mtx_stack[this->mtx_stack_size], vtx->position.x, vtx->position.y,
                               vtx->position.z, &oVec.x, &oVec.y, &oVec.z);
            }

#ifdef EMU64_DEBUG
            if (this->print_commands != false) {
                this->print_guMtxXFM1F_dol2(this->projection_mtx, this->projection_type, oVec.x, oVec.y, oVec.z);
            }
#endif

            f32 x = oVec.x;
            f32 y = oVec.y;
            f32 z = oVec.z;

            guMtxXFM1F_dol2(this->projection_mtx, this->projection_type, x, y, z, &ox, &oy, &oz);
        }

        /* Assign culling flags to vertex */
#ifdef PC_ENHANCEMENTS
        /* Widescreen hor+ widens the rendered frustum but culling uses the
         * original 4:3 projection matrix.  Extend X cull bounds to match. */
        {
            float cull_x = (float)g_pc_window_w / (float)g_pc_window_h
                         / ((float)PC_GC_WIDTH / (float)PC_GC_HEIGHT);
            if (cull_x < 1.0f) cull_x = 1.0f;
            if (ox < -cull_x) {
                vtx->flag |= G_CULL_X_LESSTHAN;
            } else if (ox > cull_x) {
                vtx->flag |= G_CULL_X_GREATERTHAN;
            }
        }
#else
        if (ox < -1.0f) {
            vtx->flag |= G_CULL_X_LESSTHAN;
        } else if (ox > 1.0f) {
            vtx->flag |= G_CULL_X_GREATERTHAN;
        }
#endif

        if (oy < -1.0f) {
            vtx->flag |= G_CULL_Y_LESSTHAN;
        } else if (oy > 1.0f) {
            vtx->flag |= G_CULL_Y_GREATERTHAN;
        }

        if (oz > 0.0f) {
            vtx->flag |= G_CULL_Z_LESSTHAN;
        } else if (oz < -1.0f) {
            vtx->flag |= G_CULL_Z_GREATERTHAN;
        }

        EMU64_LOGF("%2d %04x %1d%1d%1d%1d%1d%1d %1d %6.3f %6.3f %6.3f  %8.2f %8.2f %8.2f \n", vstart, vtx->flag,
                   vtx->cull_z_greater, vtx->cull_z_lesser, vtx->cull_y_greater, vtx->cull_y_lesser,
                   vtx->cull_x_greater, vtx->cull_x_lesser, vtx->nonshared, ox, oy, oz
/* The devs seem to have forgotten to add the last three float values */
#ifdef EMU64_FIX_CULL_INFO_LOG
                   ,
                   vtx->position.x, vtx->position.y, vtx->position.z /* Not sure if this is correct. */
#endif
        );

        /* Update culled state */
        mask &= vtx->flag;

        /* TODO: An optimization here would be to break immediately if culling occurs? */
        /* I'm not sure if these flags are checked anywhere else. */
    }

    this->cullDL_calls++;
    if (mask != 0) {
        EMU64_LOGF("カリングされました mask=%02x\n", mask); /* Translation: Was culled mask=%02x */

        if (this->DL_stack_level <= 0) {
            this->end_dl = true;
        } else {
            this->gfx_p = (Gfx*)this->DL_stack[--DL_stack_level] - 1;
        }

        this->cullDL_outside_obj_count++;
#ifdef TARGET_PC
        pc_emu64_frame_cull_rejected++;
#endif
    } else {
        EMU64_LOG("カリングされませんでした\n"); /* Translation: Wasn't culled */
        this->cullDL_visible_obj_count++;
#ifdef TARGET_PC
        pc_emu64_frame_cull_visible++;
#endif
    }
}

void emu64::dl_G_BRANCH_Z() {
    this->work_ptr = (void*)this->seg2k0(this->rdpHalf_1);
    EMU64_WARNF("gsSPBranchLessZraw(%s, %d, 0x%08x),", this->segchk(this->rdpHalf_1), (this->gfx.words.w0 / 2) & 0x7FF,
                this->gfx.words.w1);

    this->gfx_p = (Gfx*)((uintptr_t)this->work_ptr - sizeof(Gfx));
    /* Translation: gsSPBranchLessZraw isn't implemented yet */
    this->Printf0("gsSPBranchLessZrawはまだインプリメントされていません\n");
}

#define TEXTURE_SCALE 32.0f
#define TEXTURE_SCALE_CONV TEXTURE_SCALE * 65536.0f

void emu64::dl_G_TEXTURE() {
    Gtexture_internal* texture = (Gtexture_internal*)EMU64_GFX_COMPACT_PTR;

#ifdef EMU64_DEBUG
    if (this->print_commands != false) {
        if (texture->xparam == 0) {
            EMU64_LOGF("gsSPTexture(%d, %d, %d, %d, %s),", texture->s, texture->t, texture->level, texture->tile,
                       texture->on ? "G_ON" : "G_OFF");
        } else {
            EMU64_LOGF("gsSPTextureL(%d, %d, %d, %d, %d, %s),", texture->s, texture->t, texture->level, texture->xparam,
                       texture->tile, texture->on ? "G_ON" : "G_OFF");
        }
    }
#endif

    Gfx* t = (Gfx*)&this->texture_gfx;
    if ((*(u64*)t) != (*(u64*)texture)) {
        *(u64*)&this->texture_gfx = *(u64*)texture;
        this->dirty_flags[EMU64_DIRTY_FLAG_TEX] = true;

        if (this->texture_gfx.s == 0) {
            this->texture_scale_s = TEXTURE_SCALE;
        } else {
            this->texture_scale_s = TEXTURE_SCALE_CONV / fastcast_float(&this->texture_gfx.s);
        }

        if (this->texture_gfx.t == 0) {
            this->texture_scale_t = TEXTURE_SCALE;
        } else {
            this->texture_scale_t = TEXTURE_SCALE_CONV / fastcast_float(&this->texture_gfx.t);
        }
    }
}

void emu64::dl_G_POPMTX() {
    u32 n = this->gfx_p->words.w1 >> 6;

#ifdef EMU64_DEBUG
    if (this->print_commands != false) {
        if (n == 1) {
            EMU64_LOG("gsSPPopMatrix(G_MTX_MODELVIEW),");
        } else {
            EMU64_LOGF("gsSPPopMatrix(G_MTX_MODELVIEW, %d),", n);
        }
    }
#endif

    this->mtx_stack_size -= n;
    this->dirty_flags[EMU64_DIRTY_FLAG_POSITION_MTX] = true;
}

void emu64::dl_G_GEOMETRYMODE() {
    u32 clear = this->gfx.words.w0 & 0x00FFFFFF;
    u32 set = this->gfx.words.w1 & 0x00FFFFFF;

    if (this->print_commands) {
        if (clear == 0) {
            EMU64_LOG("gsSPLoadGeometryMode(");
            this->print_geomflags(set);
            EMU64_LOG("),");
        } else if (set == 0) {
            EMU64_LOG("gsSPClearGeometryMode(");
            this->print_geomflags(~clear);
            EMU64_LOG("),");
        } else if (clear == 0xFFFFFF) {
            EMU64_LOG("gsSPSetGeometryMode(");
            this->print_geomflags(set);
            EMU64_LOG("),");
        } else {
            EMU64_LOG("gsSPGeometryMode(");
            this->print_geomflags(~clear);
            EMU64_LOG(", ");
            this->print_geomflags(set);
            EMU64_LOG("),");
        }
    }

    u32 flags = set | (this->geometry_mode & clear);
    if (this->geometry_mode != flags) {
        if ((this->geometry_mode ^ flags) & (G_LIGHTING | G_LIGHTING_POSITIONAL)) {
            this->dirty_flags[EMU64_DIRTY_FLAG_LIGHTING] = true;
        }

        if ((this->geometry_mode ^ flags) & G_FOG) {
            this->dirty_flags[EMU64_DIRTY_FLAG_FOG] = true;
        }

        if ((this->geometry_mode ^ flags) & G_TEXTURE_GEN) {
            this->dirty_flags[EMU64_DIRTY_FLAG_TEX_TILE0] = true;
            this->dirty_flags[EMU64_DIRTY_FLAG_TEX_TILE1] = true;
            this->dirty_flags[EMU64_DIRTY_FLAG_TEX_TILE2] = true;
            this->dirty_flags[EMU64_DIRTY_FLAG_TEX_TILE3] = true;
            this->dirty_flags[EMU64_DIRTY_FLAG_TEX_TILE4] = true;
            this->dirty_flags[EMU64_DIRTY_FLAG_TEX_TILE5] = true;
            this->dirty_flags[EMU64_DIRTY_FLAG_TEX_TILE6] = true;
            this->dirty_flags[EMU64_DIRTY_FLAG_TEX_TILE7] = true;
        }

        this->geometry_mode = flags;
        this->dirty_flags[EMU64_DIRTY_FLAG_GEOMETRYMODE] = true;
    }
}

/* TODO: where should these go? s1, s2, and s3 are after but these are after s */
static emu64 emu64_class;
char* emu64::warningString[EMU64_WARNING_COUNT];
u32 emu64::warningTime[EMU64_WARNING_COUNT];

void emu64::dl_G_MOVEWORD() {
    static char s1[20];
    static char s2[64];
    static char s3[64];
    Gmoveword* moveword = (Gmoveword*)EMU64_GFX_COMPACT_PTR;
    u32 mw_data = (u32)this->gfx_p->words.w1; /* Read data word from w1, not union view */

    switch (moveword->index) {
        case G_MW_SEGMENT: {
            u32 segment = moveword->offset / 4;
#ifdef TARGET_PC
            /* On 64-bit, w1 is uintptr_t and stores the full pointer directly.
             * No need for pc_gbi_recover_ptr anymore. */
            {
                uintptr_t seg_addr = this->gfx_p->words.w1;
                EMU64_WARNF("gsSPSegmentA(%d, 0x%08x),", segment, (u32)seg_addr);
                this->segments[segment] = seg_addr;
            }
#else
            EMU64_WARNF("gsSPSegmentA(%d, 0x%08x),", segment, moveword->data);
            this->segments[segment] = (0x80000000 + (moveword->data & 0x0FFFFFFF));
            if (segment >= EMU64_NUM_SEGMENTS ||
                (moveword->data != 0 && (moveword->data < 0x80000000 || moveword->data > 0x83000000))) {
                sprintf(s1, "gsSPSegmentA no=%d", segment);
                sprintf(s2, "base=%s", this->segchk(moveword->data));
                sprintf(s3, "gfxp=%s", this->segchk((u32)this->gfx_p));
                emu64::warningString[0] = "SPSegment found Illigal Address.";
                emu64::warningString[1] = s1;
                emu64::warningString[2] = s2;
                emu64::warningString[3] = s3;
                emu64::warningTime[0] = EMU64_WARN_TIME;
                emu64::warningTime[1] = EMU64_WARN_TIME;
                emu64::warningTime[2] = EMU64_WARN_TIME;
                emu64::warningTime[3] = EMU64_WARN_TIME;

                this->segment_set = true;
                OSReport(VT_COL(RED, WHITE) "%s\n%s\n%s\n" VT_RST, s1, s2, s3);
            }
#endif
        } break;

        case G_MW_CLIP: {
            EMU64_LOGF("gsSPClipRatio(FRUSTRATIO_%d), ", mw_data == 0 ? 0 : mw_data);
            this->gfx_p +=
                3; /* gsSPClipRatio generates four moveword instructions, so skip three. Emulator will skip last one. */
        } break;

        case G_MW_NUMLIGHT: {
            u32 num_lights = mw_data / 24;
            EMU64_LOGF("gsSPNumLights(%d), ", num_lights);
            if (this->num_lights != num_lights) {
                this->num_lights = num_lights;
                this->dirty_flags[EMU64_DIRTY_FLAG_LIGHTS] = true;
            }
        } break;

        case G_MW_LIGHTCOL: {
            int light = (moveword->offset & 0xF0) / 32;

/* Seems like the devs used the light table index as the enum number */
/* TODO: This could be correct. Investigate if they changed the light definitions. */
#ifdef EMU64_FIX_MOVEWORD_LIGHT_NUM_LOG
            EMU64_LOGF("gsSPLightColor(LIGHT_%d, %08x), ", (moveword->offset / 0x18) + 1, mw_data);
#else
            EMU64_LOGF("gsSPLightColor(LIGHT_%d, %08x), ", light + 1, mw_data);
#endif

            this->gfx_p++; /* gsSPLightColor generates two commands */

            {
                u32 color_val = GFX_W1_U32(this->gfx);
                GXColor color_tmp;
                color_tmp.r = (color_val >> 24) & 0xFF;
                color_tmp.g = (color_val >> 16) & 0xFF;
                color_tmp.b = (color_val >> 8) & 0xFF;
                this->lights[light].color.rgba.r = color_tmp.r;
                this->lights[light].color.rgba.g = color_tmp.g;
                this->lights[light].color.rgba.b = color_tmp.b;
            }

            this->dirty_flags[EMU64_DIRTY_FLAG_LIGHTS] = true;
        } break;

        case G_MW_FOG: {
            s16 fm = (s16)(mw_data >> 16); /* z multiplier */
            s16 fo = (s16)mw_data;         /* z offset */
            if (fm != 0) {
                int min = 500 - (fo * 500) / fm;
                EMU64_LOGF("gsSPFogFactor(%d, %d),", fm, fo);
                EMU64_LOGF("gsSPFogPosition(%d, %d),", min, 128000 / fm + min);
            } else {
                EMU64_LOGF("gsSPFogFactor(%d, %d), /* fm=0, no fog */", fm, fo);
            }

            this->fog_zmult = fm;
            this->fog_zoffset = fo;
            this->dirty_flags[EMU64_DIRTY_FLAG_FOG] = true;
        } break;

        case G_MW_PERSPNORM: {
            EMU64_LOGF("gsSPPerspNormalize(%d),", mw_data);
        } break;

        default: {
            EMU64_LOGF("gsMoveWd(%d, %d, %d), /* ### what */", moveword->index, moveword->offset, mw_data);

            this->num_unknown_cmds++;
            this->Printf0("未知の命令に出くわした\n"); /* Translation: Came across an unknown command */
        } break;
    }
}

void emu64::dl_G_MOVEMEM() {
    Gmovemem* movemem = (Gmovemem*)EMU64_GFX_COMPACT_PTR;
    uintptr_t movemem_addr = this->gfx_p->words.w1; /* Full pointer from w1 */
    u8 param = movemem->index;
    switch (movemem->index) {
        case G_MV_VIEWPORT: {
            this->work_ptr = (void*)this->seg2k0(movemem_addr);
            Vp_t* vp = (Vp_t*)this->work_ptr;

#ifdef EMU64_DEBUG
            if (this->print_commands != false) {
                EMU64_LOGF("gsSPViewport(%s),", this->segchk(movemem_addr));
                EMU64_INFOF("\t# vscale=[%d %d %d %d], ", vp->vscale[0], vp->vscale[1], vp->vscale[2], vp->vscale[3]);
                EMU64_INFOF("vtrans=[%d %d %d %d] ", vp->vtrans[0], vp->vtrans[1], vp->vtrans[2], vp->vtrans[3]);
            }
#endif

            if (!this->disable_polygons) {
                f32 left = ((f32)(vp->vtrans[0] - vp->vscale[0]) / 2.0f);
                f32 top = ((f32)(vp->vtrans[1] - vp->vscale[1]) / 2.0f);
                f32 wd = (f32)vp->vscale[0] / 2.0f;
                f32 ht = (f32)vp->vscale[1] / 2.0f;
                f32 nearz = ((f32)(vp->vscale[2] - vp->vtrans[2]) * 2.0f) / 1023.0f;
                f32 farz = ((f32)vp->vscale[2] * 2.0f) / 1023.0f;

#ifdef PC_GX_VERBOSE
                {
                    extern int diag_frame;
                    if (diag_frame == 6) {
                        printf("[VIEWPORT] left=%.1f top=%.1f wd=%.1f ht=%.1f near=%.3f far=%.3f\n",
                               left, top, wd, ht, nearz, farz);
                    }
                }
#endif

                EMU64_INFOF("GXSetViewport %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f\n", left, top, wd, ht, nearz, farz);

                GXSetViewport(left, top, wd, ht, nearz, farz);
            }
            break;
        }

        case G_MV_MATRIX: {
            EMU64_LOGF("gsSPForceMatrix(%s),", this->segchk(movemem_addr));
            this->gfx_p++;                                          /* Generates two commands */
            this->Printf0("gsSPForceMatrixはサポートしてません\n"); /* Translation: gsSPForceMatrix isn't supported */
            break;
        }

        case G_MV_LIGHT: {
            switch (movemem->offset * 8) {
                case G_MVO_LOOKATX: {
                    EMU64_LOGF("gsSPLookAtX(%s),", this->segchk(movemem_addr));
                    LookAt* la = (LookAt*)this->seg2k0(movemem_addr);
                    EMU64_INFOF(" /* {%3d,%3d,%3d} */", la->l->l.dir[0], la->l->l.dir[1], la->l->l.dir[2]);
                    this->lookAt.x.x = la->l->l.dir[0];
                    this->lookAt.x.y = la->l->l.dir[1];
                    this->lookAt.x.z = la->l->l.dir[2];
                    this->lookatx_cnt++;
                    break;
                }

                case G_MVO_LOOKATY: {
                    EMU64_LOGF("gsSPLookAtY(%s),", this->segchk(movemem_addr));
                    LookAt* la = (LookAt*)this->seg2k0(movemem_addr);
                    EMU64_INFOF(" /* {%3d,%3d,%3d} */", la->l->l.dir[0], la->l->l.dir[1], la->l->l.dir[2]);
                    this->lookAt.y.x = la->l->l.dir[0];
                    this->lookAt.y.y = la->l->l.dir[1];
                    this->lookAt.y.z = la->l->l.dir[2];
                    this->lookaty_cnt++;
                    break;
                }

                default: {
                    Light_new* light = (Light_new*)this->seg2k0(movemem_addr);
                    int idx = movemem->offset * 8 - 24;
                    idx /= 24; /* Idx should be 1 - 8. There's more bithacks going on here, but I think it's compiler
                                  generated */
                    EMU64_LOGF("gsSPLight(%s, %d),", this->segchk(movemem_addr), idx);
                    EMU64_INFOF("no = %d color=[%3d %3d %3d],", idx, light->l.col[0], light->l.col[1], light->l.col[2]);

                    /* Convert index to 0 based */
                    int l_idx = (idx - 1);
                    l_idx &= (NUM_LIGHTS - 1);

                    this->dirty_flags[EMU64_DIRTY_FLAG_LIGHTS] = true;

                    this->lights[l_idx].color.rgba.r = light->l.col[0];
                    this->lights[l_idx].color.rgba.g = light->l.col[1];
                    this->lights[l_idx].color.rgba.b = light->l.col[2];

                    if (light->l.pad1 != 0) {
                        EMU64_INFOF(" position=[%+6d %+6d %+6d],", light->p.pos[0], light->p.pos[1], light->p.pos[2]);
                        EMU64_INFOF(" kc=%3d kl=%3d kq=%3d", light->p.kc, light->p.kl, light->p.kq);

                        this->lights[l_idx].position.x = fastcast_float(&light->p.pos[0]);
                        this->lights[l_idx].position.y = fastcast_float(&light->p.pos[1]);
                        this->lights[l_idx].position.z = fastcast_float(&light->p.pos[2]);
                        this->lights[l_idx].attenuation.kc = fastcast_float(&light->p.kc) / 256.0f * 16.0f + 0.5f;
                        this->lights[l_idx].attenuation.k1 = fastcast_float(&light->p.kl) / 256.0f * 0.5f;
                        this->lights[l_idx].attenuation.kq = fastcast_float(&light->p.kq) / 256.0f * 0.000488f;

                        if (aflags[AFLAGS_LIGHT_MOVE_TO_MODEL_SPACE] != 0) {
                            PSMTXMultVec(this->position_mtx_stack[this->mtx_stack_size], &this->lights[l_idx].position,
                                         &this->lights[l_idx].position);
                        }
                    } else {
                        f32 position_mult = 10000.0f;
                        if (aflags[AFLAGS_LIGHT_POSITION_MULTIPLIER] != 0) {
                            position_mult = (f32)(aflags[AFLAGS_LIGHT_POSITION_MULTIPLIER]) / 100.0f;
                        }

                        EMU64_INFOF(" normal=[%+4d %+4d %+4d] pad1=%d", light->l.dir[0], light->l.dir[1],
                                    light->l.dir[2], light->l.pad1);

                        this->lights[l_idx].position.x = fastcast_float(&light->l.dir[0]) * position_mult;
                        this->lights[l_idx].position.y = fastcast_float(&light->l.dir[1]) * position_mult;
                        this->lights[l_idx].position.z = fastcast_float(&light->l.dir[2]) * position_mult;
                        this->lights[l_idx].attenuation.kc = 0.0f;
                        this->lights[l_idx].attenuation.k1 = 0.0f;
                        this->lights[l_idx].attenuation.kq = 0.0;
                    }
                    EMU64_INFO("\n");
                    break;
                }
            }

            break;
        }

        default: {
            /* Invalid/Unknown MOVEMEM command */
            EMU64_WARNF("gsMoveMem(%s, %d, %d, %d), /* ### what? */", this->segchk(movemem_addr),
                        ((movemem->length >> 3) + 1) * 8, movemem->index, movemem->offset);

            this->num_unknown_cmds++;
            this->Printf0("未知の命令に出くわした\n"); /* Came across an unknown command */
            break;
        }
    }
}

void emu64::dl_G_S2DEX() {
    this->Printf0("未知のディスプレイリストがありました\n");
}

void emu64::dl_G_SPECIAL_1() {
    Gspecial1* special = (Gspecial1*)EMU64_GFX_COMPACT_PTR;

    if (special->mode == G_SPECIAL_TA_MODE) {
        EMU64_LOGF("gsDPSetTextureAdjustMode(%s),", special->param0 == 0 ? "G_TA_N64" : "G_TA_DOLPHIN");
        this->texture_adjust_mode = special->param0;
    } else {
        EMU64_LOGF("gsDPSpecial_1(0x%02x, 0x%04x, 0x%08x),", special->mode, special->param0, special->param1);
    }
}

bool emu64::displayWarning = false;
u8 FrameCansel = false;

static dl_func dl_func_tbl[NUM_COMMANDS] = {
    &emu64::dl_G_SETTEXEDGEALPHA,
    &emu64::dl_G_SETCOMBINE_NOTEV,
    &emu64::dl_G_SETCOMBINE_TEV,
    &emu64::dl_G_NOOP,
    &emu64::dl_G_SETTILE_DOLPHIN,
    &emu64::dl_G_NOOP,
    &emu64::dl_G_NOOP,
    &emu64::dl_G_SPECIAL_1,
    &emu64::dl_G_NOOP,
    &emu64::dl_G_TEXTURE,
    &emu64::dl_G_POPMTX,
    &emu64::dl_G_GEOMETRYMODE,
    &emu64::dl_G_MTX,
    &emu64::dl_G_MOVEWORD,
    &emu64::dl_G_MOVEMEM,
    &emu64::dl_G_LOAD_UCODE,
    &emu64::dl_G_DL,
    &emu64::dl_G_ENDDL,
    &emu64::dl_G_SPNOOP,
    &emu64::dl_G_RDPHALF_1,
    &emu64::dl_G_SETOTHERMODE_L,
    &emu64::dl_G_SETOTHERMODE_H,
    &emu64::dl_G_TEXRECT,
    &emu64::dl_G_NOOP,
    &emu64::dl_G_RDPLOADSYNC,
    &emu64::dl_G_RDPPIPESYNC,
    &emu64::dl_G_RDPTILESYNC,
    &emu64::dl_G_RDPFULLSYNC,
    &emu64::dl_G_NOOP,
    &emu64::dl_G_NOOP,
    &emu64::dl_G_NOOP,
    &emu64::dl_G_SETSCISSOR,
    &emu64::dl_G_SETPRIMDEPTH,
    &emu64::dl_G_RDPSETOTHERMODE,
    &emu64::dl_G_LOADTLUT,
    &emu64::dl_G_NOOP,
    &emu64::dl_G_SETTILESIZE,
    &emu64::dl_G_LOADBLOCK,
    &emu64::dl_G_LOADTILE,
    &emu64::dl_G_SETTILE,
    &emu64::dl_G_FILLRECT,
    &emu64::dl_G_SETFILLCOLOR,
    &emu64::dl_G_SETFOGCOLOR,
    &emu64::dl_G_SETBLENDCOLOR,
    &emu64::dl_G_SETPRIMCOLOR,
    &emu64::dl_G_SETENVCOLOR,
    &emu64::dl_G_SETCOMBINE,
    &emu64::dl_G_SETTIMG,
    &emu64::dl_G_SETZIMG,
    &emu64::dl_G_SETCIMG,
    &emu64::dl_G_NOOP,
    &emu64::dl_G_VTX,
    &emu64::dl_G_MODIFYVTX,
    &emu64::dl_G_CULLDL,
    &emu64::dl_G_BRANCH_Z,
    &emu64::dl_G_TRI1,
    &emu64::dl_G_TRI2,
    &emu64::dl_G_QUAD,
    &emu64::dl_G_LINE3D,
    &emu64::dl_G_TRIN,
    &emu64::dl_G_TRIN_INDEPEND,
    &emu64::dl_G_NOOP,
    &emu64::dl_G_NOOP,
    &emu64::dl_G_QUADN,
};

u32 emu64::emu64_taskstart_r(Gfx* dl_p) {
#ifdef TARGET_PC
    pc_crash_protection_init();
#endif
    this->gfx_p = dl_p;
    EMU64_INFO("*** emu64taskstart ***\n");
    OSInitFastCast();
    this->end_dl = false;

#ifdef TARGET_PC
    pc_crash_set_jmpbuf(&pc_dl_crash_jmpbuf);
    volatile int pc_dl_recovery_point = 0; /* 0=normal, 1=from crash */
    if (setjmp(pc_dl_crash_jmpbuf) != 0) {
        pc_dl_recovery_point = 1;
    }
    if (pc_dl_recovery_point) {
        pc_emu64_frame_crashes++;
        pc_dl_recovery_point = 0;
        /* Re-arm the crash protection for the next iteration */
        pc_crash_set_jmpbuf(&pc_dl_crash_jmpbuf);
        /* Pop DL stack to return to parent display list instead of terminating */
        if (this->DL_stack_level > 0) {
            this->gfx_p = (Gfx*)(this->DL_stack[--this->DL_stack_level]);
            /* gfx_p now points to the command AFTER the bad gsSPDisplayList.
               The while loop will read *gfx_p, process it, then gfx_p++ at the bottom.
               No adjustment needed - we want to process the next command. */
            /* Continue the main loop */
        } else {
            /* No parent DL to return to - skip the bad command and continue.
               Previously we terminated here, but that cuts off ALL remaining
               DL commands (including 2D sprites, inventory icons, etc.) */
            this->gfx_p++;
            /* Continue the main loop - gfx_p now points past the crashed command */
        }
    }
#endif

    while (!this->end_dl && !FrameCansel) {
        this->cmds_processed++;
        EMU64_INFOF("%08x:", this->gfx_p);
        this->gfx = *this->gfx_p;
#if UINTPTR_MAX > 0xFFFFFFFFu
        this->gfx_c.words_compact.w0 = this->gfx.words.w0;
        this->gfx_c.words_compact.w1 = (u32)this->gfx.words.w1;
#endif
        this->gfx_cmd = this->gfx.dma.cmd;
        this->dl_history[this->dl_history_start++] = this->gfx_p;
        if (this->dl_history_start >= DL_HISTORY_COUNT) {
            this->dl_history_start = 0;
        }

        this->work_ptr = nullptr;

        if (this->print_commands) {
            EMU64_INFOF("%08x-%08x:", this->gfx.words.w0, this->gfx.words.w1);
            for (u32 i = 0; i < this->DL_stack_level; i++) {
                EMU64_WARN(" ");
            }
        }

        u8 cmd_index = this->gfx_cmd - G_FIRST_CMD;
#ifdef TARGET_PC
        {
            pc_emu64_frame_cmds++;
            /* Track specific command types by opcode */
            switch (this->gfx_cmd) {
                case 0x00: pc_emu64_frame_noop_cmds++; break; /* G_SPNOOP */
                case 0x01: pc_emu64_frame_vtx_cmds++; break;  /* G_VTX */
                case 0x05: case 0x06: case 0x07: case 0x09: case 0x0A: case 0x0D:
                    pc_emu64_frame_tri_cmds++; break; /* G_TRI1/TRI2/QUAD/TRIN/etc */
                case 0xDE: pc_emu64_frame_dl_cmds++; break;  /* G_DL */
            }
        }
#endif
#ifdef PC_GX_VERBOSE
        {
            static int cmd_diag = 0;
            if (cmd_diag < 500) {
                printf("[PC] emu64 cmd[%d]: op=0x%02X w0=0x%08X w1=0x%08X\n",
                       this->cmds_processed, this->gfx_cmd, this->gfx.words.w0, this->gfx.words.w1);
                cmd_diag++;
            }
        }
#endif
        if (cmd_index < NUM_COMMANDS) {
            if (dl_func_tbl[cmd_index] != nullptr) {
                EMU64_TIMED_SEGMENT_BEGIN();
                (this->*dl_func_tbl[cmd_index])();
                EMU64_TIMED_SEGMENT_END(command_info[cmd_index].time);
                // likely fakematch
                u32* p = (u32*)&this->command_info;
                p[(u32)cmd_index * 2 + 1]++;
            }
        } else {
#ifdef TARGET_PC
            static int unexpected_cmd_count = 0;
            if (unexpected_cmd_count < 5) {
                this->Printf0(
                    "予期しないコマンドがありました。中断します。(cmd=%02x)\n", this->gfx_cmd);
                unexpected_cmd_count++;
                if (unexpected_cmd_count == 5)
                    this->Printf0("[PC] (suppressing further unexpected command messages)\n");
            }
#else
            this->Printf0(
                "予期しないコマンドがありました。中断します。\n"); /* There was an unexpected command. Aborting. */
#endif
            break;
        }

        EMU64_INFO("\n");
        this->gfx_p++;
    }

#ifdef TARGET_PC
    pc_crash_set_jmpbuf(NULL);
#endif

#ifdef PC_GX_VERBOSE
    printf("[PC] emu64: loop done, cmds=%d end_dl=%d\n", this->cmds_processed, this->end_dl);
#endif

    if (FrameCansel != FALSE) {
        this->Printf0("フレームキャンセル\n"); /* Translation: Frame cancel. */
    }

#ifdef PC_GX_VERBOSE
    {
        static int task_diag = 0;
        if (task_diag < 10) {
            this->Printf0("[PC] emu64_taskstart_r[%d]: cmds=%d err=%d\n",
                           task_diag, this->cmds_processed, this->err_count);
            task_diag++;
        }
    }
#endif

    return this->err_count;
}

#define EMU64_RUN_MODE_SKIP -1
#define EMU64_RUN_MODE_NORMAL 0
#define EMU64_RUN_MODE_VERBOSE                                                                              \
    EMU64_PRINT_LEVEL0_FLAG | EMU64_PRINT_LEVEL1_FLAG | EMU64_PRINT_LEVEL2_FLAG | EMU64_PRINT_LEVEL3_FLAG | \
        EMU64_PRINT_LEVEL4_FLAG

void emu64::emu64_taskstart(Gfx* dl_p) {
    static int flag = 0;

    PPCSync();
    if ((int)aflags[AFLAGS_RUN_MODE] != EMU64_RUN_MODE_SKIP) {
        if (aflags[AFLAGS_RUN_MODE] != EMU64_RUN_MODE_NORMAL) {
            this->emu64_set_verbose(aflags[AFLAGS_RUN_MODE]);
            aflags.set(AFLAGS_RUN_MODE, EMU64_RUN_MODE_NORMAL);
        }

        EMU64_TIMED_SEGMENT_BEGIN();
        this->emu64_taskstart_r(dl_p);
        EMU64_TIMED_SEGMENT_END(rsprdp_time);

        if (aflags[AFLAGS_JUTREPORT_SEGMENT_STATS] == TRUE) {
            JW_JUTReport(40, 100, 1, "%d/%d/%d/%d/%d", this->resolved_addresses, this->_2024, this->_2028, this->_202C,
                         this->abnormal_addresses);
        }

        if (aflags[AFLAGS_PRINT_COMMAND_INFO] != 0) {
            aflags.set(AFLAGS_PRINT_COMMAND_INFO, 0);

#ifdef EMU64_DEBUG_PRINTINFO
            this->Printf0("CMD TIMES CALLS TIMES/CALLS\n");
#endif

            for (int i = 0; i < NUM_COMMANDS; i++) {
                if (this->command_info[i].calls != 0) {
                    this->Printf0("%02X %6d %4d %6d\n", (u8)(i + G_FIRST_CMD),            /* Command */
                                  this->command_info[i].time,                             /* Total time */
                                  this->command_info[i].calls,                            /* Total calls */
                                  this->command_info[i].time / this->command_info[i].time /* Average command time */
                    );
                }
            }

#ifdef EMU64_DEBUG_PRINTINFO
            EMU64_PRINT_MEMBER(lookatx_cnt);
            EMU64_PRINT_MEMBER(lookaty_cnt);
            EMU64_PRINT_MEMBER(texconv_cnt);
            EMU64_PRINT_MEMBER(vertex_cnt);
            EMU64_PRINT_MEMBER(texconv_time);
            EMU64_PRINT_MEMBER(rsprdp_time);
            EMU64_PRINT_MEMBER(combine_time);
            EMU64_PRINT_MEMBER(spvertex_time);
            EMU64_PRINT_MEMBER(setup_time);
            EMU64_PRINT_MEMBER(loadblock_time);
            EMU64_PRINT_MEMBER(loadtlut_time);
            EMU64_PRINT_MEMBER(matrix_time);
            this->Printf0("polygons = %u/%u/%u/%u\n", this->polygons, this->double_triangles, this->triangles,
                          this->quads);
            EMU64_PRINT_MEMBER(polygons_time);
            EMU64_PRINT_MEMBER(dirty_check_time);
#ifndef ANIMAL_FOREST_PLUS
            EMU64_PRINT_MEMBER(dirty_lightX_time);
            EMU64_PRINT_MEMBER(dirty_lightX_cnt);
#endif
            EMU64_PRINT_MEMBER(dirty_light_time);
            EMU64_PRINT_MEMBER(dirty_light_cnt);
            EMU64_PRINT_MEMBER(dirty_tex_time);
            EMU64_PRINT_MEMBER(dirty_tex_cnt);
            EMU64_PRINT_MEMBER(dirty_tex1_time);
            EMU64_PRINT_MEMBER(dirty_tex1_cnt);
            EMU64_PRINT_MEMBER(dirty_tex2_time);
            EMU64_PRINT_MEMBER(dirty_tex2_cnt);
            EMU64_PRINT_MEMBER(dirty_texmtx_time);
            EMU64_PRINT_MEMBER(dirty_texmtx_cnt);
            EMU64_PRINT_MEMBER(dirty_proj_time);
            EMU64_PRINT_MEMBER(dirty_primcolor_time);
            EMU64_PRINT_MEMBER(dirty_envcolor_time);
            EMU64_PRINT_MEMBER(dirty_fillcolor_time);
            EMU64_PRINT_MEMBER(dirty_combine_mode_time);
            EMU64_PRINT_MEMBER(dirty_othermodeh_time);
            EMU64_PRINT_MEMBER(dirty_othermodel_time);
            EMU64_PRINT_MEMBER(dirty_geometory_time);
            EMU64_PRINT_MEMBER(setuptex_time);
            EMU64_PRINT_MEMBER(texture_cache_select_time);
            EMU64_PRINT_MEMBER(guMtxL2F_time);
            EMU64_PRINT_MEMBER(guMtxL2F_cnt);
            EMU64_PRINT_MEMBER(combine_auto_cnt[0]);
            EMU64_PRINT_MEMBER(combine_auto_cnt[1]);
            EMU64_PRINT_MEMBER(combine_auto_cnt[2]);
            EMU64_PRINT_MEMBER(combine_auto_cnt[3]);
            EMU64_PRINT_MEMBER(combine_auto_cnt[4]);
#endif
        }

        if (emu64::displayWarning != false) {
            for (u32 i = 0; i < EMU64_WARNING_COUNT; i++) {
                if (emu64::warningString[i] != nullptr) {
                    JW_JUTReport(40, i * 16 + 80, 1, "%s", emu64::warningString[i]);
                    if (emu64::warningTime[i] == 0) {
                        emu64::warningString[i] = nullptr;
                    }
                }
            }
        }
    }
}

void emu64::emu64_set_ucode_info(int len, ucode_info* info) {
    this->ucode_len = len;
    this->ucode_info_p = info;
}

void emu64::emu64_set_first_ucode(void* ucode_p) {
    this->emu64_change_ucode(ucode_p);
}

void emu64::emu64_set_verbose(int verbose) {
    this->print_commands = verbose;
    this->print_flags = verbose;
}

/* C wrapper methods */

extern void emu64_init(void) {
    emu64_class.emu64_init();
}

extern void emu64_cleanup(void) {
    emu64_class.emu64_cleanup();
}

// hack - inlines in emu64_taskstart C wrapper otherwise
#pragma dont_inline on
extern void emu64_taskstart(Gfx* gfx) {
    emu64_class.emu64_taskstart(gfx);
}
#pragma dont_inline reset

extern void emu64_set_ucode_info(int len, ucode_info* info) {
    emu64_class.emu64_set_ucode_info(len, info);
}

extern void emu64_set_first_ucode(void* ucode_p) {
    emu64_class.emu64_set_first_ucode(ucode_p);
}

extern void emu64_set_aflags(int idx, int value) {
    if (idx > 0 && idx < aflags_c::getMaxArray()) {
        aflags.set(idx, value);
    }
}

extern int emu64_get_aflags(int idx) {
    if (idx > 0 && idx < aflags_c::getMaxArray()) {
        return aflags[idx];
    }

    return 0;
}
