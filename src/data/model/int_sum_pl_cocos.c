#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_pl_cocos_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_pl_cocos_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_pl_cocos_pal[] = {
#include "assets/int_sum_pl_cocos_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_cocos_earth_tex[0x80];
#else
u8 int_sum_pl_cocos_earth_tex[] = {
#include "assets/int_sum_pl_cocos_earth_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_cocos_hachi_tex[0x100];
#else
u8 int_sum_pl_cocos_hachi_tex[] = {
#include "assets/int_sum_pl_cocos_hachi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_cocos_cocos_tex[0x100];
#else
u8 int_sum_pl_cocos_cocos_tex[] = {
#include "assets/int_sum_pl_cocos_cocos_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_cocos_leaf_tex[0x180];
#else
u8 int_sum_pl_cocos_leaf_tex[] = {
#include "assets/int_sum_pl_cocos_leaf_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_cocos_leaf2_tex[0x180];
#else
u8 int_sum_pl_cocos_leaf2_tex[] = {
#include "assets/int_sum_pl_cocos_leaf2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_pl_cocos_v[0x2E0 / sizeof(Vtx)];
#else
Vtx int_sum_pl_cocos_v[] = {
#include "assets/int_sum_pl_cocos_v.inc"
};
#endif

Gfx int_sum_pl_cocos_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_pl_cocos_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_pl_cocos_cocos_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_pl_cocos_v, 18, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 0, 2, 4, 5, 0),
    gsSPNTriangles_5b(3, 4, 0, 6, 7, 5, 4, 6, 5, 6, 8, 9),
    gsSPNTriangles_5b(6, 9, 7, 3, 10, 4, 6, 4, 10, 0, 5, 11),
    gsSPNTriangles_5b(7, 11, 5, 6, 10, 8, 11, 7, 9, 10, 3, 2),
    gsSPNTriangles_5b(1, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_pl_cocos_earth_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 12, 15, 13, 16, 15, 12),
    gsSPNTriangles_5b(16, 17, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_pl_cocos_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_pl_cocos_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_pl_cocos_leaf2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_pl_cocos_v[18], 28, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_pl_cocos_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 4, 5, 6, 7, 8, 5, 9, 8, 10),
    gsSPNTriangles_5b(9, 10, 11, 12, 9, 11, 12, 11, 13, 14, 4, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_pl_cocos_hachi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 15, 16, 17, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 24, 25, 15, 26, 23, 25, 27, 0, 0, 0),
    gsSPEndDisplayList(),
};
