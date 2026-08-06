#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_touro03_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_touro03_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_touro03_pal[] = {
#include "assets/int_sum_touro03_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro03_madoside_tex[0x80];
#else
u8 int_sum_touro03_madoside_tex[] = {
#include "assets/int_sum_touro03_madoside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro03_mado_tex[0x100];
#else
u8 int_sum_touro03_mado_tex[] = {
#include "assets/int_sum_touro03_mado_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro03_yanetop_tex[0x80];
#else
u8 int_sum_touro03_yanetop_tex[] = {
#include "assets/int_sum_touro03_yanetop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro03_standup_tex[0x80];
#else
u8 int_sum_touro03_standup_tex[] = {
#include "assets/int_sum_touro03_standup_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro03_kazari_tex[0x80];
#else
u8 int_sum_touro03_kazari_tex[] = {
#include "assets/int_sum_touro03_kazari_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro03_yane_tex[0x100];
#else
u8 int_sum_touro03_yane_tex[] = {
#include "assets/int_sum_touro03_yane_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro03_foot_tex[0x200];
#else
u8 int_sum_touro03_foot_tex[] = {
#include "assets/int_sum_touro03_foot_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro03_footop_tex[0x100];
#else
u8 int_sum_touro03_footop_tex[] = {
#include "assets/int_sum_touro03_footop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro03_kazaritop_tex[0x80];
#else
u8 int_sum_touro03_kazaritop_tex[] = {
#include "assets/int_sum_touro03_kazaritop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro03_madotop_tex[0x80];
#else
u8 int_sum_touro03_madotop_tex[] = {
#include "assets/int_sum_touro03_madotop_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_touro03_v[0x570 / sizeof(Vtx)];
#else
Vtx int_sum_touro03_v[] = {
#include "assets/int_sum_touro03_v.inc"
};
#endif

Gfx int_sum_touro03_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_touro03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_touro03_madotop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_touro03_v, 25, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 3, 0),
    gsSPNTriangles_5b(4, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_touro03_kazaritop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 6, 7, 8, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_touro03_mado_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 9, 10, 11, 12, 13, 14, 12, 14, 15),
    gsSPNTriangles_5b(16, 17, 18, 17, 19, 18, 20, 21, 22, 21, 23, 22),
    gsSPNTriangles_5b(9, 24, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_touro03_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_touro03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_touro03_footop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_touro03_v[25], 18, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_touro03_foot_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 15, 16, 17, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_touro03_yane_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_touro03_v[43], 31, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 6, 7, 0),
    gsSPNTriangles_5b(8, 9, 2, 3, 10, 11, 5, 12, 13, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_touro03_kazari_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 14, 15, 16, 17, 15, 14, 16, 18, 19),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_touro03_standup_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 20, 23, 24, 25, 21, 20),
    gsSPNTriangles_5b(24, 26, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_touro03_yanetop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 27, 28, 29, 27, 30, 28, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_touro03_madoside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_touro03_v[74], 13, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 0, 0, 5, 6),
    gsSPNTriangles_5b(7, 8, 0, 9, 10, 0, 0, 11, 12, 0, 0, 0),
    gsSPEndDisplayList(),
};
