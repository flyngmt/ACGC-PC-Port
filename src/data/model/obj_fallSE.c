#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 obj_fall_rainbow_1_tex_rgb_rgba16[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 obj_fall_rainbow_1_tex_rgb_rgba16[] = {
#include "assets/obj_fallSE/obj_fall_rainbow_1_tex_rgb_rgba16.inc"
};
#endif

#ifdef TARGET_PC
static u8 obj_fall_rainbowA_tex_rgb_i4[0x80];
#else
static u8 obj_fall_rainbowA_tex_rgb_i4[] = {
#include "assets/obj_fallSE/obj_fall_rainbowA_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
static u8 obj_fallCA1_tex_rgb_ia8[0x400];
#else
static u8 obj_fallCA1_tex_rgb_ia8[] = {
#include "assets/obj_fallSE/obj_fallCA1_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
static u8 obj_fallA2_tex_rgb_i4[0x200];
#else
static u8 obj_fallA2_tex_rgb_i4[] = {
#include "assets/obj_fallSE/obj_fallA2_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
static u8 obj_fallA3_tex_rgb_i4[0x80];
#else
static u8 obj_fallA3_tex_rgb_i4[] = {
#include "assets/obj_fallSE/obj_fallA3_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
static u8 obj_fallC2_tex_rgb_i4[0x200];
#else
static u8 obj_fallC2_tex_rgb_i4[] = {
#include "assets/obj_fallSE/obj_fallC2_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
static u8 obj_fallC3_tex_rgb_i4[0x80];
#else
static u8 obj_fallC3_tex_rgb_i4[] = {
#include "assets/obj_fallSE/obj_fallC3_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_fallSE_v[0x550 / sizeof(Vtx)];
#else
Vtx obj_fallSE_v[] = {
#include "assets/obj_fallSE_v.inc"
};
#endif

Gfx obj_fallSE_grpAT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, ENVIRONMENT, TEXEL0, 0, TEXEL1, 0, TEXEL0, 0, PRIM_LOD_FRAC, COMBINED, 0, 0,
                       0, COMBINED),
    gsDPSetPrimColor(0, 32, 200, 220, 255, 255),
    gsDPSetEnvColor(20, 30, 40, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_fallA2_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_fallC3_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 0, 14),
    gsSPDisplayList(anime_1_txt),
    gsSPVertex(obj_fallSE_v, 9, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 1, 5, 6, 7),
    gsSPNTriangles_5b(8, 7, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_fallSE_grpBT_model[] = {
    gsDPSetCombineLERP(1, 0, PRIMITIVE, TEXEL0, TEXEL1, 0, TEXEL0, 0, COMBINED, 0, SHADE, TEXEL0, COMBINED, 0,
                       PRIM_LOD_FRAC, 0),
    gsDPSetPrimColor(0, 255, 100, 140, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, obj_fallCA1_tex_rgb_ia8),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, obj_fallCA1_tex_rgb_ia8),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_2_txt),
    gsSPVertex(&obj_fallSE_v[9], 14, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 0, 3, 1, 1, 4, 2),
    gsSPNTriangles_5b(3, 5, 6, 3, 6, 1, 6, 7, 4, 6, 4, 1),
    gsSPNTriangles_5b(5, 8, 9, 5, 9, 6, 9, 10, 7, 9, 7, 6),
    gsSPNTriangles_5b(8, 11, 12, 8, 12, 9, 12, 13, 10, 12, 10, 9),
    gsSPEndDisplayList(),
};

Gfx obj_fallSE_grpDT_model[] = {
    gsDPSetCombineLERP(1, 0, PRIMITIVE, TEXEL0, TEXEL0, 0, TEXEL1, 0, COMBINED, 0, SHADE, TEXEL1, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 32, 100, 140, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, obj_fallCA1_tex_rgb_ia8),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_fallA2_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_CLAMP, 0, 1),
    gsSPDisplayList(anime_3_txt),
    gsSPVertex(&obj_fallSE_v[23], 7, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 0, 2, 3, 2, 4, 3),
    gsSPNTriangles_5b(5, 0, 3, 5, 3, 6, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_fallSE_grpCT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, ENVIRONMENT, TEXEL0, 0, TEXEL1, TEXEL1, TEXEL1, 0, PRIM_LOD_FRAC, COMBINED,
                       0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 47, 200, 220, 255, 100),
    gsDPSetEnvColor(30, 40, 50, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_fallC2_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 15, 15),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_fallA3_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPDisplayList(anime_4_txt),
    gsSPVertex(&obj_fallSE_v[30], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 4, 0, 5, 6),
    gsSPNTriangles_5b(0, 2, 5, 0, 7, 3, 0, 8, 7, 0, 9, 1),
    gsSPNTriangles_5b(4, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_fallSE_rainbowT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, PRIMITIVE, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, COMBINED, 0, TEXEL0, 0),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 120),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 8, obj_fall_rainbow_1_tex_rgb_rgba16),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_fall_rainbowA_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_fallSE_v[40], 32, 0),
    gsSPNTrianglesInit_5b(27, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 12, 16, 17, 16, 18, 17, 8, 19, 20),
    gsSPNTriangles_5b(19, 21, 20, 22, 0, 2, 1, 23, 3, 23, 24, 3),
    gsSPNTriangles_5b(23, 15, 24, 23, 14, 15, 12, 25, 13, 12, 17, 25),
    gsSPNTriangles_5b(16, 26, 18, 26, 27, 18, 26, 28, 27, 26, 29, 28),
    gsSPNTriangles_5b(29, 30, 28, 21, 31, 30, 31, 28, 30, 21, 30, 20),
    gsSPVertex(&obj_fallSE_v[72], 13, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 6, 8, 4, 6, 7, 6, 9, 10, 11, 12),
    gsSPEndDisplayList(),
};

Gfx obj_fallSESW_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPDisplayList(obj_fallSE_grpAT_model),
    gsSPDisplayList(obj_fallSE_grpBT_model),
    gsSPDisplayList(obj_fallSE_grpCT_model),
    gsSPDisplayList(obj_fallSE_grpDT_model),
    gsSPEndDisplayList(),
};

EVW_ANIME_SCROLL obj_fallSE_evw_anime_1[] = { { 0, 0, 32, 32 }, { 0, 2, 16, 16 } };

EVW_ANIME_SCROLL obj_fallSE_evw_anime_2[] = { { 0, -3, 32, 32 }, { 0, -8, 32, 32 } };

EVW_ANIME_SCROLL obj_fallSE_evw_anime_3[] = { { 0, -8, 32, 32 }, { 0, 0, 32, 32 } };

EVW_ANIME_SCROLL obj_fallSE_evw_anime_4[] = { { -1, 1, 32, 32 }, { 0, 0, 16, 16 } };

EVW_ANIME_DATA obj_fallSE_evw_anime[] = { { 1, EVW_ANIME_TYPE_SCROLL2, obj_fallSE_evw_anime_1 },
                                          { 2, EVW_ANIME_TYPE_SCROLL2, obj_fallSE_evw_anime_2 },
                                          { 3, EVW_ANIME_TYPE_SCROLL2, obj_fallSE_evw_anime_3 },
                                          { -4, EVW_ANIME_TYPE_SCROLL2, obj_fallSE_evw_anime_4 } };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_fallSE_c(void) {
    pc_load_asset("assets/obj_fallSE/obj_fall_rainbow_1_tex_rgb_rgba16.bin", obj_fall_rainbow_1_tex_rgb_rgba16, 0x100, 0x8006A0, 0, 0);
    pc_load_asset("assets/obj_fallSE/obj_fall_rainbowA_tex_rgb_i4.bin", obj_fall_rainbowA_tex_rgb_i4, 0x80, 0x8007A0, 0, 0);
    pc_load_asset("assets/obj_fallSE/obj_fallCA1_tex_rgb_ia8.bin", obj_fallCA1_tex_rgb_ia8, 0x400, 0x800820, 0, 0);
    pc_load_asset("assets/obj_fallSE/obj_fallA2_tex_rgb_i4.bin", obj_fallA2_tex_rgb_i4, 0x200, 0x800C20, 0, 0);
    pc_load_asset("assets/obj_fallSE/obj_fallA3_tex_rgb_i4.bin", obj_fallA3_tex_rgb_i4, 0x80, 0x800E20, 0, 0);
    pc_load_asset("assets/obj_fallSE/obj_fallC2_tex_rgb_i4.bin", obj_fallC2_tex_rgb_i4, 0x200, 0x800EA0, 0, 0);
    pc_load_asset("assets/obj_fallSE/obj_fallC3_tex_rgb_i4.bin", obj_fallC3_tex_rgb_i4, 0x80, 0x8010A0, 0, 0);
}
#endif
