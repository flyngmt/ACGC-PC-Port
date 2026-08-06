#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_taru01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 it_sum_taru01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 it_sum_taru01_pal[] = {
#include "assets/it_sum_taru01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_taru01_side_tex[0x200];
#else
u8 int_sum_taru01_side_tex[] = {
#include "assets/int_sum_taru01_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_taru01_top_tex[0x400];
#else
u8 int_sum_taru01_top_tex[] = {
#include "assets/int_sum_taru01_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_taru01_sentop_tex[0x80];
#else
u8 int_sum_taru01_sentop_tex[] = {
#include "assets/int_sum_taru01_sentop_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_taru01_v[0x320 / sizeof(Vtx)];
#else
Vtx int_sum_taru01_v[] = {
#include "assets/int_sum_taru01_v.inc"
};
#endif

Gfx int_sum_taru01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, it_sum_taru01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_taru01_sentop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_taru01_v, 7, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_sum_taru01_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 3, 4, 5, 3, 6, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_taru01_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_taru01_v[7], 32, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 2, 7, 6, 5),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 2, 7, 13, 12, 7, 14, 15),
    gsSPNTriangles_5b(17, 16, 2, 7, 18, 19, 20, 21, 2, 7, 23, 22),
    gsSPNTriangles_5b(25, 24, 2, 26, 27, 2, 7, 30, 31, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(13, 5, 6, 4, 5, 4, 3, 9, 8, 1),
    gsSPNTriangles_5b(12, 13, 11, 12, 11, 10, 15, 14, 16, 15, 16, 17),
    gsSPNTriangles_5b(22, 23, 21, 22, 21, 20, 19, 18, 24, 19, 24, 25),
    gsSPNTriangles_5b(28, 29, 27, 28, 27, 26, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_sum_taru01_v[39], 11, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 2, 4, 5, 6, 7),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 0, 2, 3, 8, 9, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};
