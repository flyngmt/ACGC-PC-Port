#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_touro04_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_touro04_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_touro04_pal[] = {
#include "assets/int_sum_touro04_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro04_mado_tex[0x100];
#else
u8 int_sum_touro04_mado_tex[] = {
#include "assets/int_sum_touro04_mado_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro04_yane_tex[0x100];
#else
u8 int_sum_touro04_yane_tex[] = {
#include "assets/int_sum_touro04_yane_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro04_madosita_tex[0x80];
#else
u8 int_sum_touro04_madosita_tex[] = {
#include "assets/int_sum_touro04_madosita_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro04_madotop_tex[0x80];
#else
u8 int_sum_touro04_madotop_tex[] = {
#include "assets/int_sum_touro04_madotop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro04_stand_tex[0x80];
#else
u8 int_sum_touro04_stand_tex[] = {
#include "assets/int_sum_touro04_stand_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro04_base_tex[0x200];
#else
u8 int_sum_touro04_base_tex[] = {
#include "assets/int_sum_touro04_base_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro04_dan_tex[0x100];
#else
u8 int_sum_touro04_dan_tex[] = {
#include "assets/int_sum_touro04_dan_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro04_dantop_tex[0x80];
#else
u8 int_sum_touro04_dantop_tex[] = {
#include "assets/int_sum_touro04_dantop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_touro04_kazari_tex[0x100];
#else
u8 int_sum_touro04_kazari_tex[] = {
#include "assets/int_sum_touro04_kazari_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_touro04_v[0x550 / sizeof(Vtx)];
#else
Vtx int_sum_touro04_v[] = {
#include "assets/int_sum_touro04_v.inc"
};
#endif

Gfx int_sum_touro04_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_touro04_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_touro04_dantop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_touro04_v, 19, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_touro04_madotop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_touro04_madosita_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 15, 16, 12, 14, 17, 12),
    gsSPNTriangles_5b(12, 16, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_touro04_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_touro04_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_touro04_kazari_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_touro04_v[19], 29, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_touro04_dan_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 5, 6, 7, 8, 9, 10, 11, 12, 13),
    gsSPNTriangles_5b(14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25),
    gsSPNTriangles_5b(26, 27, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_touro04_base_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_touro04_v[48], 21, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 4, 5, 1, 0),
    gsSPNTriangles_5b(4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_touro04_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 7, 8, 9, 10, 11, 7, 9, 12, 7),
    gsSPNTriangles_5b(7, 11, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_touro04_yane_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 14, 15, 16, 17, 18, 16, 16, 19, 14),
    gsSPNTriangles_5b(16, 18, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_touro04_mado_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_touro04_v[69], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
