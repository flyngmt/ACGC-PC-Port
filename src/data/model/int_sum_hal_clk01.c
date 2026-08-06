#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_hal_clk01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_hal_clk01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_hal_clk01_pal[] = {
#include "assets/int_sum_hal_clk01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_clk01_hari_tex_txt[0x100];
#else
u8 int_sum_hal_clk01_hari_tex_txt[] = {
#include "assets/int_sum_hal_clk01_hari_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_clk01_back_tex_txt[0x180];
#else
u8 int_sum_hal_clk01_back_tex_txt[] = {
#include "assets/int_sum_hal_clk01_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_clk01_base_tex_txt[0x80];
#else
u8 int_sum_hal_clk01_base_tex_txt[] = {
#include "assets/int_sum_hal_clk01_base_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_clk01_front_tex_txt[0x300];
#else
u8 int_sum_hal_clk01_front_tex_txt[] = {
#include "assets/int_sum_hal_clk01_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_clk01_top_tex_txt[0x80];
#else
u8 int_sum_hal_clk01_top_tex_txt[] = {
#include "assets/int_sum_hal_clk01_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_clk01_kuki_tex_txt[0x80];
#else
u8 int_sum_hal_clk01_kuki_tex_txt[] = {
#include "assets/int_sum_hal_clk01_kuki_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_clk01_hiki_tex_txt[0x80];
#else
u8 int_sum_hal_clk01_hiki_tex_txt[] = {
#include "assets/int_sum_hal_clk01_hiki_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_clk01_hari02_tex_txt[0x80];
#else
u8 int_sum_hal_clk01_hari02_tex_txt[] = {
#include "assets/int_sum_hal_clk01_hari02_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_hal_clk01_v[0x4B0 / sizeof(Vtx)];
#else
Vtx int_sum_hal_clk01_v[] = {
#include "assets/int_sum_hal_clk01_v.inc"
};
#endif

Gfx int_sum_hal_clk01_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hal_clk01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_hal_clk01_hari_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_hal_clk01_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_hal_clk01_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hal_clk01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_hal_clk01_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 188),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hal_clk01_v[4], 21, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_clk01_base_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 5, 6, 7, 5, 7, 8, 9, 10, 11),
    gsSPNTriangles_5b(9, 11, 12, 13, 14, 15, 13, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(17, 19, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_hal_clk01_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 188),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hal_clk01_v[25], 25, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 7, 6, 9, 10, 11, 9, 12, 10),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_clk01_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(10, 13, 14, 15, 13, 15, 16, 17, 16, 15),
    gsSPNTriangles_5b(17, 15, 18, 19, 20, 17, 19, 17, 18, 19, 21, 22),
    gsSPNTriangles_5b(19, 22, 20, 22, 21, 23, 22, 23, 24, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_clk01_kuki_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 188, 60),
    gsSPVertex(&int_sum_hal_clk01_v[50], 21, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_clk01_hiki_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPEndDisplayList(),
};

Gfx int_sum_hal_clk01_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hal_clk01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_clk01_hari02_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hal_clk01_v[71], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_hal_clk01_tbl[] = { 0, 0, 0, 0, 0 };

s16 cKF_c_int_sum_hal_clk01_tbl[] = { 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_int_sum_hal_clk01 = { cKF_ckcb_r_int_sum_hal_clk01_tbl, NULL, NULL,
                                                 cKF_c_int_sum_hal_clk01_tbl,      -1,   9 };

cKF_Joint_R_c cKF_je_r_int_sum_hal_clk01_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_hal_clk01_base_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2300, 0, 0 } },
    { int_sum_hal_clk01_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_hal_clk01_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2300, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_hal_clk01 = { ARRAY_COUNT(cKF_je_r_int_sum_hal_clk01_tbl), 3,
                                                cKF_je_r_int_sum_hal_clk01_tbl };
