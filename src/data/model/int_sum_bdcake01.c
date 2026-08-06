#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_bdcake01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_bdcake01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_bdcake01_pal[] = {
#include "assets/int_sum_bdcake01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bdcake01_top_tex_txt[0x80];
#else
u8 int_sum_bdcake01_top_tex_txt[] = {
#include "assets/int_sum_bdcake01_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bdcake01_ichigo_tex_txt[0x200];
#else
u8 int_sum_bdcake01_ichigo_tex_txt[] = {
#include "assets/int_sum_bdcake01_ichigo_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bdcake01_mesege_tex_txt[0x300];
#else
u8 int_sum_bdcake01_mesege_tex_txt[] = {
#include "assets/int_sum_bdcake01_mesege_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bdcake01_side_tex_txt[0x100];
#else
u8 int_sum_bdcake01_side_tex_txt[] = {
#include "assets/int_sum_bdcake01_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bdcake01_a_candol1_TA_tex_txt[0x40];
#else
u8 int_sum_bdcake01_a_candol1_TA_tex_txt[] = {
#include "assets/int_sum_bdcake01_a_candol1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bdcake01_a_candol2_TA_tex_txt[0x40];
#else
u8 int_sum_bdcake01_a_candol2_TA_tex_txt[] = {
#include "assets/int_sum_bdcake01_a_candol2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bdcake01_b_candol1_TA_tex_txt[0x40];
#else
u8 int_sum_bdcake01_b_candol1_TA_tex_txt[] = {
#include "assets/int_sum_bdcake01_b_candol1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bdcake01_b_candol2_TA_tex_txt[0x40];
#else
u8 int_sum_bdcake01_b_candol2_TA_tex_txt[] = {
#include "assets/int_sum_bdcake01_b_candol2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_bdcake01_v[0x540 / sizeof(Vtx)];
#else
Vtx int_sum_bdcake01_v[] = {
#include "assets/int_sum_bdcake01_v.inc"
};
#endif

Gfx int_sum_bdcake01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bdcake01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_bdcake01_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_bdcake01_v, 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 3, 0),
    gsSPNTriangles_5b(4, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_bdcake01_ichigo_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_bdcake01_v[6], 30, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 2, 5, 6, 7),
    gsSPNTriangles_5b(5, 8, 9, 10, 11, 12, 10, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(18, 19, 17, 20, 21, 22, 23, 24, 22, 25, 26, 27),
    gsSPNTriangles_5b(25, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, int_sum_bdcake01_mesege_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_bdcake01_v[36], 15, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_bdcake01_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(10, 3, 4, 5, 3, 5, 6, 7, 6, 5),
    gsSPNTriangles_5b(7, 5, 8, 7, 8, 9, 9, 8, 10, 9, 10, 11),
    gsSPNTriangles_5b(12, 4, 3, 12, 13, 4, 12, 14, 13, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_bdcake01_off1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bdcake01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_bdcake01_v[67], 17, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_bdcake01_off_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bdcake01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_bdcake01_v[51], 16, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 2, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 13, 0, 0, 0),
    gsSPEndDisplayList(),
};
