#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_uwa_vase03_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_uwa_vase03_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_uwa_vase03_pal[] = {
#include "assets/int_sum_uwa_vase03_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_vase03_side[0x100];
#else
u8 int_sum_uwa_vase03_side[] = {
#include "assets/int_sum_uwa_vase03_side.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_vase03_kuki[0x100];
#else
u8 int_sum_uwa_vase03_kuki[] = {
#include "assets/int_sum_uwa_vase03_kuki.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_vase03_leaf[0x100];
#else
u8 int_sum_uwa_vase03_leaf[] = {
#include "assets/int_sum_uwa_vase03_leaf.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_vase03_flawer[0x100];
#else
u8 int_sum_uwa_vase03_flawer[] = {
#include "assets/int_sum_uwa_vase03_flawer.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_vase03_naka[0x80];
#else
u8 int_sum_uwa_vase03_naka[] = {
#include "assets/int_sum_uwa_vase03_naka.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_vase03_base[0x80];
#else
u8 int_sum_uwa_vase03_base[] = {
#include "assets/int_sum_uwa_vase03_base.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_uwa_vase03_v[0x330 / sizeof(Vtx)];
#else
Vtx int_sum_uwa_vase03_v[] = {
#include "assets/int_sum_uwa_vase03_v.inc"
};
#endif

Gfx int_sum_uwa_vase03_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_uwa_vase03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_uwa_vase03_base),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_uwa_vase03_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 1, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_uwa_vase03_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_uwa_vase03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_uwa_vase03_naka),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_uwa_vase03_v[4], 29, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 1, 0, 4),
    gsSPNTriangles_5b(4, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_uwa_vase03_flawer),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 5, 6, 7, 8, 5, 7, 9, 10, 11),
    gsSPNTriangles_5b(10, 12, 11, 12, 9, 11, 6, 8, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_uwa_vase03_leaf),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 13, 14, 15, 14, 16, 15, 17, 18, 19),
    gsSPNTriangles_5b(17, 19, 20, 21, 22, 23, 24, 21, 23, 25, 26, 27),
    gsSPNTriangles_5b(25, 28, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_uwa_vase03_kuki),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_uwa_vase03_v[33], 18, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_uwa_vase03_side),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 5, 6, 7, 11, 9, 6, 12, 13, 14),
    gsSPNTriangles_5b(17, 14, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 7, 6, 8, 6, 9, 10, 14, 13, 15),
    gsSPNTriangles_5b(9, 14, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
