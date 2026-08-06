#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_blue_table01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_blue_table01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_blue_table01_pal[] = {
#include "assets/int_sum_blue_table01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_blue_table01_top_tex[0x200];
#else
u8 int_sum_blue_table01_top_tex[] = {
#include "assets/int_sum_blue_table01_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_blue_table01_side_tex[0x100];
#else
u8 int_sum_blue_table01_side_tex[] = {
#include "assets/int_sum_blue_table01_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_blue_table01_foot_tex[0x100];
#else
u8 int_sum_blue_table01_foot_tex[] = {
#include "assets/int_sum_blue_table01_foot_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_blue_table01_v[0x340 / sizeof(Vtx)];
#else
Vtx int_sum_blue_table01_v[] = {
#include "assets/int_sum_blue_table01_v.inc"
};
#endif

Gfx int_sum_blue_table01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_blue_table01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_blue_table01_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_blue_table01_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_blue_table01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_blue_table01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_blue_table01_foot_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_blue_table01_v[4], 28, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 2, 3, 4, 2, 5, 0),
    gsSPNTriangles_5b(6, 3, 2, 7, 8, 9, 10, 11, 7, 12, 8, 7),
    gsSPNTriangles_5b(7, 13, 10, 14, 15, 16, 16, 17, 18, 16, 19, 14),
    gsSPNTriangles_5b(20, 17, 16, 21, 22, 23, 24, 25, 21, 26, 22, 21),
    gsSPNTriangles_5b(21, 27, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_blue_table01_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_sum_blue_table01_v[32], 20, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 5, 4, 6, 5, 6, 7, 8, 9, 1),
    gsSPNTriangles_5b(8, 1, 0, 10, 11, 12, 10, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 18, 19, 15, 18, 15, 14, 13, 12, 19),
    gsSPNTriangles_5b(13, 19, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
