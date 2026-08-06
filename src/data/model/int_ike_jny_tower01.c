#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_jny_tower01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 int_ike_jny_tower01[0x20];
#else
ATTRIBUTE_ALIGN(32) u8 int_ike_jny_tower01[] = {
#include "assets/int_ike_jny_tower01.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_towerbase_tex_txt[0x80];
#else
u8 int_ike_jny_towerbase_tex_txt[] = {
#include "assets/int_ike_jny_towerbase_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_towertem1_tex_txt[0x40];
#else
u8 int_ike_jny_towertem1_tex_txt[] = {
#include "assets/int_ike_jny_towertem1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_towertem2_tex_txt[0x200];
#else
u8 int_ike_jny_towertem2_tex_txt[] = {
#include "assets/int_ike_jny_towertem2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_towertem3_tex_txt[0x40];
#else
u8 int_ike_jny_towertem3_tex_txt[] = {
#include "assets/int_ike_jny_towertem3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_towername_tex_txt[0x40];
#else
u8 int_ike_jny_towername_tex_txt[] = {
#include "assets/int_ike_jny_towername_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_towerbelt_tex_txt[0x40];
#else
u8 int_ike_jny_towerbelt_tex_txt[] = {
#include "assets/int_ike_jny_towerbelt_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_towerbottom_tex_txt[0x200];
#else
u8 int_ike_jny_towerbottom_tex_txt[] = {
#include "assets/int_ike_jny_towerbottom_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_towermiddle_tex_txt[0x80];
#else
u8 int_ike_jny_towermiddle_tex_txt[] = {
#include "assets/int_ike_jny_towermiddle_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_jny_tower01_v[0x900 / sizeof(Vtx)];
#else
Vtx int_ike_jny_tower01_v[] = {
#include "assets/int_ike_jny_tower01_v.inc"
};
#endif

Gfx int_ike_jny_tower01_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_tower01),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_jny_towerbase_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_jny_tower01_v, 28, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 2),
    gsSPNTriangles_5b(4, 2, 1, 6, 7, 8, 6, 8, 9, 10, 11, 0),
    gsSPNTriangles_5b(10, 0, 3, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_jny_towertem1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, int_ike_jny_towertem2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_jny_tower01_v[28], 22, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_jny_towertem3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_jny_towername_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_jny_towerbelt_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 12, 13, 14, 15, 16, 14, 16, 12, 14),
    gsSPNTriangles_5b(13, 15, 14, 17, 18, 19, 19, 18, 20, 20, 18, 21),
    gsSPNTriangles_5b(21, 18, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile_Dolphin(8, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 28),
    gsSPVertex(&int_ike_jny_tower01_v[50], 20, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 18, 17, 19, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_jny_towerbottom_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_jny_tower01_v[70], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 19, 18, 20),
    gsSPNTriangles_5b(19, 20, 21, 22, 23, 24, 22, 24, 25, 26, 27, 28),
    gsSPNTriangles_5b(26, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_ike_jny_tower01_v[100], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_jny_towermiddle_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 124),
    gsSPVertex(&int_ike_jny_tower01_v[116], 28, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
