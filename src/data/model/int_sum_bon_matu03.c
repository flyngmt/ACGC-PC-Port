#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_bon_matu03_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_bon_matu03_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_bon_matu03_pal[] = {
#include "assets/int_sum_bon_matu03_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_matu03_hachi_tex[0x100];
#else
u8 int_sum_bon_matu03_hachi_tex[] = {
#include "assets/int_sum_bon_matu03_hachi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_matu03_stand_tex[0x400];
#else
u8 int_sum_bon_matu03_stand_tex[] = {
#include "assets/int_sum_bon_matu03_stand_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_matu03_standside_tex[0x100];
#else
u8 int_sum_bon_matu03_standside_tex[] = {
#include "assets/int_sum_bon_matu03_standside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_matu03_earth_tex[0x80];
#else
u8 int_sum_bon_matu03_earth_tex[] = {
#include "assets/int_sum_bon_matu03_earth_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_matu03_leaf_tex[0x100];
#else
u8 int_sum_bon_matu03_leaf_tex[] = {
#include "assets/int_sum_bon_matu03_leaf_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_bon_matu03_v[0x510 / sizeof(Vtx)];
#else
Vtx int_sum_bon_matu03_v[] = {
#include "assets/int_sum_bon_matu03_v.inc"
};
#endif

Gfx int_sum_bon_matu03_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bon_matu03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_bon_matu03_earth_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_bon_matu03_v, 7, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(4, 5, 2, 5, 6, 2, 6, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_bon_matu03_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bon_matu03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_bon_matu03_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_bon_matu03_v[7], 32, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(5, 8, 9, 10, 11, 12, 10, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(15, 18, 19, 20, 21, 22, 20, 23, 24, 25, 26, 27),
    gsSPNTriangles_5b(25, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_sum_bon_matu03_v[37], 29, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 7, 10, 11, 12, 10, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(15, 18, 19, 20, 21, 22, 23, 24, 22, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_bon_matu03_standside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 25, 26, 27, 28, 27, 26, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_sum_bon_matu03_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_bon_matu03_v[66], 15, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_bon_matu03_hachi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 3, 4, 5, 6, 5, 4, 7, 8, 9),
    gsSPNTriangles_5b(10, 11, 12, 6, 10, 13, 7, 3, 14, 0, 0, 0),
    gsSPEndDisplayList(),
};
