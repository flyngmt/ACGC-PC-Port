#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_bon_matu01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_bon_matu01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_bon_matu01_pal[] = {
#include "assets/int_sum_bon_matu01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_matu01_hachi_tex[0x100];
#else
u8 int_sum_bon_matu01_hachi_tex[] = {
#include "assets/int_sum_bon_matu01_hachi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_matu01_miki_tex[0x300];
#else
u8 int_sum_bon_matu01_miki_tex[] = {
#include "assets/int_sum_bon_matu01_miki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_matu01_mikiside_tex[0x180];
#else
u8 int_sum_bon_matu01_mikiside_tex[] = {
#include "assets/int_sum_bon_matu01_mikiside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_matu01_leaf_tex[0x100];
#else
u8 int_sum_bon_matu01_leaf_tex[] = {
#include "assets/int_sum_bon_matu01_leaf_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_matu01_earth_tex[0x100];
#else
u8 int_sum_bon_matu01_earth_tex[] = {
#include "assets/int_sum_bon_matu01_earth_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_bon_matu01_v[0x560 / sizeof(Vtx)];
#else
Vtx int_sum_bon_matu01_v[] = {
#include "assets/int_sum_bon_matu01_v.inc"
};
#endif

Gfx int_sum_bon_matu01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bon_matu01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_bon_matu01_earth_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_bon_matu01_v, 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_bon_matu01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bon_matu01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_bon_matu01_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_bon_matu01_v[5], 32, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 4, 2, 5, 6, 2),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 9, 12, 13, 9, 14, 15, 16),
    gsSPNTriangles_5b(17, 18, 16, 19, 20, 16, 21, 22, 23, 24, 25, 23),
    gsSPNTriangles_5b(26, 27, 23, 28, 29, 30, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_sum_bon_matu01_v[36], 32, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 4, 2, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 7, 10, 11, 7, 12, 13, 14, 12, 15, 16),
    gsSPNTriangles_5b(12, 17, 18, 19, 20, 21, 19, 22, 23, 19, 24, 25),
    gsSPNTriangles_5b(26, 27, 28, 29, 30, 28, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_sum_bon_matu01_v[67], 19, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_bon_matu01_mikiside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 3, 4, 5, 3, 6, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_bon_matu01_miki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 7, 8, 9, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_bon_matu01_hachi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 10, 14, 15, 16, 17),
    gsSPNTriangles_5b(16, 13, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
