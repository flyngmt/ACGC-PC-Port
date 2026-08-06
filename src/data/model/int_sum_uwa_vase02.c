#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_uwa_vase02_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_uwa_vase02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_uwa_vase02_pal[] = {
#include "assets/int_sum_uwa_vase02_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_vase02_side[0x100];
#else
u8 int_sum_uwa_vase02_side[] = {
#include "assets/int_sum_uwa_vase02_side.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_vase02_frower[0x200];
#else
u8 int_sum_uwa_vase02_frower[] = {
#include "assets/int_sum_uwa_vase02_frower.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_vase02_stand[0x100];
#else
u8 int_sum_uwa_vase02_stand[] = {
#include "assets/int_sum_uwa_vase02_stand.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_vase02_stand2[0x100];
#else
u8 int_sum_uwa_vase02_stand2[] = {
#include "assets/int_sum_uwa_vase02_stand2.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_vase02_leaf[0x80];
#else
u8 int_sum_uwa_vase02_leaf[] = {
#include "assets/int_sum_uwa_vase02_leaf.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_uwa_vase02_v[0x490 / sizeof(Vtx)];
#else
Vtx int_sum_uwa_vase02_v[] = {
#include "assets/int_sum_uwa_vase02_v.inc"
};
#endif

Gfx int_sum_uwa_vase02_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_uwa_vase02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_uwa_vase02_leaf),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_uwa_vase02_v, 23, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_uwa_vase02_stand2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(5, 9, 10, 11, 12, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(18, 19, 20, 21, 22, 11, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_uwa_vase02_stand),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_uwa_vase02_v[23], 31, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_uwa_vase02_frower),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(17, 9, 10, 11, 12, 13, 14, 13, 15, 14),
    gsSPNTriangles_5b(13, 16, 15, 12, 16, 13, 9, 11, 17, 18, 19, 20),
    gsSPNTriangles_5b(19, 21, 20, 21, 18, 20, 22, 23, 24, 25, 22, 24),
    gsSPNTriangles_5b(23, 25, 24, 11, 26, 17, 27, 28, 29, 28, 30, 29),
    gsSPNTriangles_5b(30, 27, 29, 11, 10, 26, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_uwa_vase02_side),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_uwa_vase02_v[54], 19, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 6, 1, 5, 7, 8, 0),
    gsSPNTriangles_5b(10, 8, 12, 13, 14, 15, 5, 14, 18, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 0, 3, 1, 4, 5, 1, 9, 0, 8),
    gsSPNTriangles_5b(10, 11, 8, 16, 15, 14, 5, 17, 14, 0, 0, 0),
    gsSPEndDisplayList(),
};
