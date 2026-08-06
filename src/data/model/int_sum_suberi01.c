#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_suberi01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_suberi01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_suberi01_pal[] = {
#include "assets/int_sum_suberi01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_suberi01_side_tex[0x400];
#else
u8 int_sum_suberi01_side_tex[] = {
#include "assets/int_sum_suberi01_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_suberi01_dan_tex[0x100];
#else
u8 int_sum_suberi01_dan_tex[] = {
#include "assets/int_sum_suberi01_dan_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_suberi01_danue_tex[0x80];
#else
u8 int_sum_suberi01_danue_tex[] = {
#include "assets/int_sum_suberi01_danue_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_suberi01_suberu_tex[0x100];
#else
u8 int_sum_suberi01_suberu_tex[] = {
#include "assets/int_sum_suberi01_suberu_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_suberi01_danyoko_tex[0x40];
#else
u8 int_sum_suberi01_danyoko_tex[] = {
#include "assets/int_sum_suberi01_danyoko_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_suberi01_v[0x440 / sizeof(Vtx)];
#else
Vtx int_sum_suberi01_v[] = {
#include "assets/int_sum_suberi01_v.inc"
};
#endif

Gfx int_sum_suberi01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_suberi01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_suberi01_danyoko_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_suberi01_v, 30, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 7, 6, 8, 7, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 15, 17, 16, 13, 12, 18),
    gsSPNTriangles_5b(12, 19, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_suberi01_suberu_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 20, 22, 23, 23, 24, 25),
    gsSPNTriangles_5b(23, 25, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_suberi01_danue_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_suberi01_dan_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_suberi01_v[30], 22, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 4, 7, 8, 7, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 11, 14, 15, 11, 15, 12, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 1, 20, 21, 1, 21, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_suberi01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_suberi01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_sum_suberi01_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_suberi01_v[52], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
