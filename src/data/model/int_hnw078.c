#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_hnw078_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_hnw078_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_hnw078_pal[] = {
#include "assets/int_hnw078_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw078_c_front_tex_txt[0x300];
#else
u8 int_hnw078_c_front_tex_txt[] = {
#include "assets/int_hnw078_c_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw078_c_back_tex_txt[0x180];
#else
u8 int_hnw078_c_back_tex_txt[] = {
#include "assets/int_hnw078_c_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw078_arm_tex_txt[0x100];
#else
u8 int_hnw078_arm_tex_txt[] = {
#include "assets/int_hnw078_arm_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw078_armtop_tex_txt[0x80];
#else
u8 int_hnw078_armtop_tex_txt[] = {
#include "assets/int_hnw078_armtop_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw078_b_back_tex_txt[0x80];
#else
u8 int_hnw078_b_back_tex_txt[] = {
#include "assets/int_hnw078_b_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw078_b_front_tex_txt[0x100];
#else
u8 int_hnw078_b_front_tex_txt[] = {
#include "assets/int_hnw078_b_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_hnw078_v[0x470 / sizeof(Vtx)];
#else
Vtx int_hnw078_v[] = {
#include "assets/int_hnw078_v.inc"
};
#endif

Gfx int_hnw078_chest_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_hnw078_v, 7, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw078_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_hnw078_c_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 188),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&int_hnw078_v[7], 22, 7),
    gsSPNTrianglesInit_5b(7, 5, 7, 8, 4, 5, 9, 5, 6, 10),
    gsSPNTriangles_5b(4, 11, 12, 0, 4, 13, 6, 2, 14, 6, 15, 16),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_hnw078_c_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 188),
    gsSPNTrianglesInit_5b(3, 1, 18, 17, 3, 1, 19, 3, 20, 21),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_hnw078_c_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 188),
    gsSPNTrianglesInit_5b(3, 22, 23, 24, 25, 26, 24, 27, 28, 22),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_hnw078_c_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 188),
    gsSPVertex(&int_hnw078_v[29], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 1, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw078_armR_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw078_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_hnw078_arm_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw078_v[45], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 1, 4, 4, 5, 3),
    gsSPNTriangles_5b(6, 5, 7, 8, 5, 6, 2, 5, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw078_armtop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw078_armL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw078_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_hnw078_arm_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw078_v[33], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 1, 4, 4, 5, 3),
    gsSPNTriangles_5b(6, 5, 7, 7, 1, 6, 2, 1, 8, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw078_armtop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw078_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw078_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw078_b_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw078_v[57], 14, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_hnw078_b_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 60),
    gsSPNTrianglesInit_5b(7, 5, 6, 7, 5, 8, 6, 8, 9, 6),
    gsSPNTriangles_5b(7, 10, 11, 11, 5, 7, 9, 8, 12, 9, 12, 13),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_hnw078_tbl[] = { 0, 0, 4, 0, 4, 0, 4 };

s16 cKF_kn_int_hnw078_tbl[] = { 37, 9, 9 };

s16 cKF_c_int_hnw078_tbl[] = { 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, -900, 0, 0, 0, 0, -2700, 0, 0 };

s16 cKF_ds_int_hnw078_tbl[] = {
    1,   500,   -4453,  2,  352,   -7125, 4,   -302,  -7125,  5,   -450,  -901,   6,  -362,  4488,  8,   101,   6936,
    9,   312,   4488,   10, 400,   156,   11,  322,   -3960,  13,  -86,   -6120,  14, -272,  -3960, 15,  -350,  -156,
    16,  -282,  3432,   18, 71,    5304,  19,  232,   3432,   20,  300,   156,    21, 243,   -2904, 23,  -56,   -4488,
    24,  -193,  -2904,  25, -250,  -156,  27,  -92,   3672,   29,  153,   2376,   30, 200,   156,   32,  77,    -2856,
    34,  -114,  -1848,  35, -150,  -156,  37,  -62,   2040,   39,  74,    1320,   40, 100,   78,    42,  30,    -1632,
    44,  -79,   -1056,  45, -100,  -47,   49,  52,    898,    50,  70,    268,    51, 70,    12,    128, 500,   12,
    129, 500,   6,      1,  0,     -8438, 2,   -281,  -13500, 4,   -1519, -13500, 5,  -1800, -4219, 6,   -1800, 0,
    49,  -1800, 0,      54, -1787, 197,   128, -1,    51,     129, 0,     26,     1,  0,     -8438, 2,   -281,  -13500,
    4,   -1519, -13500, 5,  -1800, -4219, 6,   -1800, 0,      49,  -1800, 0,      54, -1787, 197,   128, -1,    51,
    129, 0,     26
};

cKF_Animation_R_c cKF_ba_r_int_hnw078 = {
    cKF_ckcb_r_int_hnw078_tbl, cKF_ds_int_hnw078_tbl, cKF_kn_int_hnw078_tbl, cKF_c_int_hnw078_tbl, -1, 129
};

cKF_Joint_R_c cKF_je_r_int_hnw078_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { int_hnw078_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { int_hnw078_chest_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 700, 64836, 0 } },
                                            { int_hnw078_armL_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 700, 700, 0 } },
                                            { int_hnw078_armR_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_hnw078 = { ARRAY_COUNT(cKF_je_r_int_hnw078_tbl), 4, cKF_je_r_int_hnw078_tbl };
