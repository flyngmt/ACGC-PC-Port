#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_touro01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_touro01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_touro01_pal[] = {
#include "assets/int_sum_touro01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro01_mado_tex[0x100];
#else
u8 int_sum_touro01_mado_tex[] = {
#include "assets/int_sum_touro01_mado_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro01_madodown_tex[0x80];
#else
u8 int_sum_touro01_madodown_tex[] = {
#include "assets/int_sum_touro01_madodown_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro01_stand_tex[0x200];
#else
u8 int_sum_touro01_stand_tex[] = {
#include "assets/int_sum_touro01_stand_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro01_madotop_tex[0x80];
#else
u8 int_sum_touro01_madotop_tex[] = {
#include "assets/int_sum_touro01_madotop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro01_yanetop_tex[0x100];
#else
u8 int_sum_touro01_yanetop_tex[] = {
#include "assets/int_sum_touro01_yanetop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro01_kazari_tex[0x80];
#else
u8 int_sum_touro01_kazari_tex[] = {
#include "assets/int_sum_touro01_kazari_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro01_yane_tex[0x80];
#else
u8 int_sum_touro01_yane_tex[] = {
#include "assets/int_sum_touro01_yane_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_touro01_v[0x450 / sizeof(Vtx)];
#else
Vtx int_sum_touro01_v[] = {
#include "assets/int_sum_touro01_v.inc"
};
#endif

Gfx int_sum_touro01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_touro01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_touro01_yane_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_touro01_v, 24, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_touro01_kazari_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 6, 7, 8, 6, 5, 9),
    gsSPNTriangles_5b(8, 10, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 11, 12, 13, 14, 15, 11, 16, 12, 11),
    gsSPNTriangles_5b(11, 17, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_touro01_madotop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 18, 19, 20, 18, 21, 19, 20, 22, 23),
    gsSPNTriangles_5b(20, 19, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_touro01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_touro01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_touro01_yanetop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_touro01_v[24], 27, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 5, 0),
    gsSPNTriangles_5b(6, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_touro01_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 7, 8, 9, 9, 10, 11, 9, 12, 7),
    gsSPNTriangles_5b(13, 10, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_touro01_madodown_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 14, 15, 16, 17, 18, 14, 14, 19, 20),
    gsSPNTriangles_5b(21, 22, 14, 14, 23, 24, 25, 26, 14, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_touro01_mado_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_touro01_v[51], 18, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 2, 1),
    gsSPNTriangles_5b(4, 1, 5, 6, 7, 8, 6, 8, 9, 10, 8, 7),
    gsSPNTriangles_5b(10, 7, 11, 0, 12, 13, 0, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(15, 17, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
