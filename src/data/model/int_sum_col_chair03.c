#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_col_chair03_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_col_chair03_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_col_chair03_pal[] = {
#include "assets/int_sum_col_chair03_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_col_chair03_backboard_tex[0x180];
#else
u8 int_sum_col_chair03_backboard_tex[] = {
#include "assets/int_sum_col_chair03_backboard_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_col_chair03_front_tex[0x40];
#else
u8 int_sum_col_chair03_front_tex[] = {
#include "assets/int_sum_col_chair03_front_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_col_chair03_seatside_tex[0x40];
#else
u8 int_sum_col_chair03_seatside_tex[] = {
#include "assets/int_sum_col_chair03_seatside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_col_chair03_top_tex[0x80];
#else
u8 int_sum_col_chair03_top_tex[] = {
#include "assets/int_sum_col_chair03_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_col_chair03_boardside_tex[0x80];
#else
u8 int_sum_col_chair03_boardside_tex[] = {
#include "assets/int_sum_col_chair03_boardside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_col_chair03_foot_tex[0x100];
#else
u8 int_sum_col_chair03_foot_tex[] = {
#include "assets/int_sum_col_chair03_foot_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_col_chair03_v[0x390 / sizeof(Vtx)];
#else
Vtx int_sum_col_chair03_v[] = {
#include "assets/int_sum_col_chair03_v.inc"
};
#endif

Gfx int_sum_col_chair03_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_col_chair03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_sum_col_chair03_boardside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_col_chair03_v, 27, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 0, 4, 1),
    gsSPNTriangles_5b(5, 6, 7, 5, 8, 6, 6, 9, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_col_chair03_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 11, 13, 12, 13, 14, 12),
    gsSPNTriangles_5b(14, 10, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_col_chair03_seatside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 15, 16, 17, 16, 18, 17, 19, 20, 21),
    gsSPNTriangles_5b(19, 22, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_col_chair03_front_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 23, 24, 25, 23, 26, 24, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_col_chair03_backboard_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_col_chair03_v[27], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 6, 0, 3, 6, 3, 7, 8, 5, 4),
    gsSPNTriangles_5b(8, 4, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_col_chair03_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_col_chair03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_col_chair03_foot_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_col_chair03_v[37], 20, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 2, 2, 4, 0),
    gsSPNTriangles_5b(5, 6, 7, 7, 6, 8, 7, 9, 5, 10, 11, 12),
    gsSPNTriangles_5b(13, 14, 12, 12, 14, 10, 15, 16, 17, 17, 16, 18),
    gsSPNTriangles_5b(17, 19, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
