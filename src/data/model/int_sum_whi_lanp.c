#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_whi_lanp_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_whi_lanp_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_whi_lanp_pal[] = {
#include "assets/int_sum_whi_lanp_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_lanp_shade_tex[0x100];
#else
u8 int_sum_whi_lanp_shade_tex[] = {
#include "assets/int_sum_whi_lanp_shade_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_lanp_stand_tex[0x180];
#else
u8 int_sum_whi_lanp_stand_tex[] = {
#include "assets/int_sum_whi_lanp_stand_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_lanp_foot_tex[0x100];
#else
u8 int_sum_whi_lanp_foot_tex[] = {
#include "assets/int_sum_whi_lanp_foot_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_lanp_down_tex[0x80];
#else
u8 int_sum_whi_lanp_down_tex[] = {
#include "assets/int_sum_whi_lanp_down_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_lanp_hiki_tex[0x100];
#else
u8 int_sum_whi_lanp_hiki_tex[] = {
#include "assets/int_sum_whi_lanp_hiki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_lanp_top_tex[0x80];
#else
u8 int_sum_whi_lanp_top_tex[] = {
#include "assets/int_sum_whi_lanp_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_lanp_topside_tex[0x80];
#else
u8 int_sum_whi_lanp_topside_tex[] = {
#include "assets/int_sum_whi_lanp_topside_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_whi_lanp_v[0x410 / sizeof(Vtx)];
#else
Vtx int_sum_whi_lanp_v[] = {
#include "assets/int_sum_whi_lanp_v.inc"
};
#endif

Gfx int_sum_whi_lanp_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_whi_lanp_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_whi_lanp_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_whi_lanp_v, 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 3, 0),
    gsSPNTriangles_5b(4, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_whi_lanp_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_whi_lanp_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_whi_lanp_topside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_whi_lanp_v[6], 12, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 3, 2, 6, 3, 6, 7, 7, 6, 8),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 5, 10, 5, 4, 9, 8, 11),
    gsSPNTriangles_5b(9, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_whi_lanp_foot_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_whi_lanp_v[18], 20, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 2, 5, 6, 7),
    gsSPNTriangles_5b(5, 8, 9, 10, 11, 12, 10, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(18, 19, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_whi_lanp_offT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_whi_lanp_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_whi_lanp_hiki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_whi_lanp_v[38], 27, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_whi_lanp_down_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 5, 6, 7, 5, 7, 8, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_whi_lanp_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 9, 10, 11, 9, 12, 13, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_whi_lanp_shade_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 14, 15, 16, 17, 18, 14, 19, 20, 18),
    gsSPNTriangles_5b(21, 22, 20, 23, 24, 22, 25, 26, 24, 0, 0, 0),
    gsSPEndDisplayList(),
};
