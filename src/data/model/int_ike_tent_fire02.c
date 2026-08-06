#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_tent_fire02_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_tent_fire02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_tent_fire02_pal[] = {
#include "assets/int_ike_tent_fire02_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_fire02_tree3_tex_txt[0x80];
#else
u8 int_ike_tent_fire02_tree3_tex_txt[] = {
#include "assets/int_ike_tent_fire02_tree3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_fire02_tree2_tex_txt[0x80];
#else
u8 int_ike_tent_fire02_tree2_tex_txt[] = {
#include "assets/int_ike_tent_fire02_tree2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_fire02_tree5_tex_txt[0x80];
#else
u8 int_ike_tent_fire02_tree5_tex_txt[] = {
#include "assets/int_ike_tent_fire02_tree5_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_fire02_tree1_tex_txt[0x80];
#else
u8 int_ike_tent_fire02_tree1_tex_txt[] = {
#include "assets/int_ike_tent_fire02_tree1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_fire02_f2_4i4_pic_i4[0x400];
#else
u8 int_ike_tent_fire02_f2_4i4_pic_i4[] = {
#include "assets/int_ike_tent_fire02_f2_4i4_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_fire02_tex_4i4_pic_i4[0x400];
#else
u8 int_ike_tent_fire02_tex_4i4_pic_i4[] = {
#include "assets/int_ike_tent_fire02_tex_4i4_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_tent_fire02_v[0x630 / sizeof(Vtx)];
#else
Vtx int_ike_tent_fire02_v[] = {
#include "assets/int_ike_tent_fire02_v.inc"
};
#endif

Gfx int_ike_tent_firetree02_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_tent_fire02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_tent_fire02_tree3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_tent_fire02_v[8], 31, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 2, 2, 5, 3),
    gsSPNTriangles_5b(2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_tent_fire02_tree2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 124),
    gsSPNTrianglesInit_5b(2, 7, 8, 9, 7, 9, 10, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_tent_fire02_tree2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 124),
    gsSPNTrianglesInit_5b(2, 11, 12, 13, 11, 13, 14, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_tent_fire02_tree2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 124),
    gsSPNTrianglesInit_5b(2, 15, 16, 17, 15, 17, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_tent_fire02_tree2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 124),
    gsSPNTrianglesInit_5b(2, 19, 20, 21, 19, 21, 22, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_tent_fire02_tree2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 124),
    gsSPNTrianglesInit_5b(2, 23, 24, 25, 23, 25, 26, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_tent_fire02_tree2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 124),
    gsSPNTrianglesInit_5b(2, 27, 28, 29, 27, 29, 30, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_tent_fire02_tree2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 124),
    gsSPVertex(&int_ike_tent_fire02_v[39], 30, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_tent_fire02_tree5_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 4, 6, 7, 5, 8, 9),
    gsSPNTriangles_5b(5, 9, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_tent_fire02_tree5_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 10, 12, 13, 11, 14, 15),
    gsSPNTriangles_5b(11, 15, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_tent_fire02_tree5_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 18, 19, 17, 20, 21),
    gsSPNTriangles_5b(17, 21, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_tent_fire02_tree1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 22, 23, 24, 22, 24, 25, 23, 26, 27),
    gsSPNTriangles_5b(23, 27, 24, 26, 28, 29, 26, 29, 27, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_tent_fire02_tree2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 124),
    gsSPVertex(&int_ike_tent_fire02_v[69], 30, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_tent_fire02_tree1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 4, 5, 6, 4, 6, 7, 5, 8, 9),
    gsSPNTriangles_5b(5, 9, 6, 8, 10, 11, 8, 11, 9, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_tent_fire02_tree5_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 12, 14, 15, 13, 16, 17),
    gsSPNTriangles_5b(13, 17, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_tent_fire02_tree5_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 18, 19, 20, 18, 20, 21, 19, 22, 23),
    gsSPNTriangles_5b(19, 23, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_tent_fire02_tree5_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 24, 25, 26, 24, 26, 27, 25, 28, 29),
    gsSPNTriangles_5b(25, 29, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_fire1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, PRIMITIVE, 0,
                       COMBINED, 0, TEXEL0, 0),
    gsDPSetPrimColor(0, 140, 255, 240, 30, 255),
    gsDPSetEnvColor(220, 30, 0, 120),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, int_ike_tent_fire02_f2_4i4_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, int_ike_tent_fire02_tex_4i4_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 2, 0),
    gsSPDisplayList(anime_2_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_tent_fire02_v, 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_ike_tent_fire02_tbl[] = { 0, 0, 0 };

s16 cKF_c_int_ike_tent_fire02_tbl[] = { 0, 0, 0, 0, 0, 0, 0, -900, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_int_ike_tent_fire02 = { cKF_ckcb_r_int_ike_tent_fire02_tbl, NULL, NULL,
                                                   cKF_c_int_ike_tent_fire02_tbl,      -1,   101 };

cKF_Joint_R_c cKF_je_r_int_ike_tent_fire02_tbl[] = {
    { int_ike_tent_firetree02_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 2700, 0 } },
    { int_ike_fire1_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_ike_tent_fire02 = { ARRAY_COUNT(cKF_je_r_int_ike_tent_fire02_tbl), 2,
                                                  cKF_je_r_int_ike_tent_fire02_tbl };
