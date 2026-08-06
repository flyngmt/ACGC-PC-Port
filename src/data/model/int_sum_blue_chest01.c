#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_blue_chest01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_blue_chest01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_blue_chest01_pal[] = {
#include "assets/int_sum_blue_chest01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_blue_chest01_front_tex[0x300];
#else
u8 int_sum_blue_chest01_front_tex[] = {
#include "assets/int_sum_blue_chest01_front_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_blue_chest01_back_tex[0x180];
#else
u8 int_sum_blue_chest01_back_tex[] = {
#include "assets/int_sum_blue_chest01_back_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_blue_chest01_top_tex[0x80];
#else
u8 int_sum_blue_chest01_top_tex[] = {
#include "assets/int_sum_blue_chest01_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_blue_chest01_lanp_tex[0x80];
#else
u8 int_sum_blue_chest01_lanp_tex[] = {
#include "assets/int_sum_blue_chest01_lanp_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_blue_chest01_stand_tex[0x100];
#else
u8 int_sum_blue_chest01_stand_tex[] = {
#include "assets/int_sum_blue_chest01_stand_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_blue_chest01_topshade_tex[0x80];
#else
u8 int_sum_blue_chest01_topshade_tex[] = {
#include "assets/int_sum_blue_chest01_topshade_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_blue_chest01_v[0x2E0 / sizeof(Vtx)];
#else
Vtx int_sum_blue_chest01_v[] = {
#include "assets/int_sum_blue_chest01_v.inc"
};
#endif

Gfx int_sum_blue_chest01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_blue_chest01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_blue_chest01_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_blue_chest01_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_blue_chest01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_blue_chest01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_blue_chest01_topshade_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_blue_chest01_v[4], 18, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_blue_chest01_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 7, 8, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_blue_chest01_lanp_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 9, 10, 11, 10, 12, 13, 12, 14, 15),
    gsSPNTriangles_5b(9, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_blue_chest01_back_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_blue_chest01_v[22], 24, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_blue_chest01_front_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12, 6, 7, 8, 6, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 14, 16, 17, 9, 8, 18),
    gsSPNTriangles_5b(9, 18, 19, 20, 21, 11, 20, 11, 10, 22, 23, 17),
    gsSPNTriangles_5b(22, 17, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
