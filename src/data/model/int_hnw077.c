#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_hnw077_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_hnw077_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_hnw077_pal[] = {
#include "assets/int_hnw077_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw077_arm_tex_txt[0x100];
#else
u8 int_hnw077_arm_tex_txt[] = {
#include "assets/int_hnw077_arm_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw077_armtop_tex_txt[0x80];
#else
u8 int_hnw077_armtop_tex_txt[] = {
#include "assets/int_hnw077_armtop_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw077_c_front_tex_txt[0x300];
#else
u8 int_hnw077_c_front_tex_txt[] = {
#include "assets/int_hnw077_c_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw077_c_back_tex_txt[0x180];
#else
u8 int_hnw077_c_back_tex_txt[] = {
#include "assets/int_hnw077_c_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw077_b_back_tex_txt[0x80];
#else
u8 int_hnw077_b_back_tex_txt[] = {
#include "assets/int_hnw077_b_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw077_b_front_tex_txt[0x100];
#else
u8 int_hnw077_b_front_tex_txt[] = {
#include "assets/int_hnw077_b_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_hnw077_v[0x470 / sizeof(Vtx)];
#else
Vtx int_hnw077_v[] = {
#include "assets/int_hnw077_v.inc"
};
#endif

Gfx int_hnw077_chest_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw077_v[24], 7, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw077_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_hnw077_c_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&int_hnw077_v[31], 22, 7),
    gsSPNTrianglesInit_5b(7, 4, 7, 8, 5, 4, 9, 4, 6, 10),
    gsSPNTriangles_5b(5, 11, 12, 0, 5, 13, 6, 2, 14, 6, 15, 16),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_hnw077_c_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 1, 18, 17, 3, 1, 19, 3, 20, 21),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_hnw077_c_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 22, 23, 24, 25, 26, 24, 27, 28, 22),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_hnw077_c_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_hnw077_v[53], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 1, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw077_armR_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw077_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_hnw077_arm_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_hnw077_v, 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 2, 3, 0, 4, 3, 5),
    gsSPNTriangles_5b(5, 1, 4, 6, 1, 7, 8, 1, 6, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw077_armtop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw077_armL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw077_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_hnw077_arm_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw077_v[12], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 1, 0, 4, 1, 5),
    gsSPNTriangles_5b(5, 6, 4, 7, 6, 8, 8, 1, 7, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw077_armtop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw077_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw077_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw077_b_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw077_v[57], 14, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_hnw077_b_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7, 5, 6, 7, 6, 8, 7, 6, 9, 8),
    gsSPNTriangles_5b(9, 10, 11, 11, 8, 9, 5, 7, 12, 5, 12, 13),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_hnw077_tbl[] = { 0, 0, 2, 0, 4, 0, 4 };

s16 cKF_kn_int_hnw077_tbl[] = { 35, 35, 37 };

s16 cKF_c_int_hnw077_tbl[] = { 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, -900, 0, 0, 0, 0, -2700, 0, 0 };

s16 cKF_ds_int_hnw077_tbl[] = {
    1,  -250,  2344,   2,  -172,  3750,   4,   172,   3750,   5,   250,   439,   6,   201,   -2482, 8,  -55,   -3835,
    9,  -171,  -2482,  10, -220,  -78,    11,  -176,  2218,   13,  52,    3427,  14,  156,   2218,  15, 200,   62,
    16, 160,   -2006,  18, -46,   -3101,  19,  -140,  -2006,  20,  -180,  -62,   21,  -145,  1795,  23, 40,    2774,
    24, 125,   1795,   25, 160,   62,     27,  54,    -2448,  29,  -109,  -1584, 30,  -140,  -62,   32, -48,   2122,
    34, 93,    1373,   35, 120,   62,     37,  43,    -1795,  39,  -77,   -1162, 40,  -100,  -62,   42, -37,   1469,
    44, 61,    950,    45, 80,    72,     49,  -43,   -782,   51,  -64,   -117,  129, -250,  -1,    1,  0,     -7969,
    2,  -266,  -12750, 4,  -1434, -12750, 5,   -1700, -1488,  6,   -1534, 8448,  8,   -663,  13056, 9,  -266,  8448,
    10, -100,  312,    11, -246,  -7392,  13,  -1007, -11424, 14,  -1354, -7392, 15,  -1500, -624,  16, -1396, 5280,
    18, -852,  8160,   19, -604,  5280,   20,  -500,  312,    22,  -782,  -6528, 24,  -1217, -4224, 25, -1300, -156,
    26, -1227, 3696,   28, -846,  5712,   29,  -673,  3696,   30,  -600,  312,   32,  -776,  -4080, 34, -1048, -2640,
    35, -1100, -312,   36, -1069, 1584,   38,  -906,  2448,   39,  -831,  1584,  40,  -800,  312,   41, -810,  -528,
    44, -890,  -528,   47, -898,  45,     128, 0,     23,     129, 0,     11,    1,   0,     -8438, 2,  -281,  -13500,
    4,  -1519, -13500, 5,  -1800, -1411,  6,   -1613, 9504,   8,   -634,  14688, 9,   -187,  9504,  10, 0,     312,
    11, -166,  -8448,  13, -1037, -13056, 14,  -1434, -8448,  15,  -1600, -468,  16,  -1465, 6864,  18, -758,  10608,
    19, -435,  6864,   20, -300,  312,    21,  -414,  -5808,  23,  -1013, -8976, 24,  -1286, -5808, 25, -1400, -312,
    26, -1306, 4752,   28, -817,  7344,   29,  -594,  4752,   30,  -500,  312,   32,  -746,  -5712, 34, -1127, -3696,
    35, -1200, -156,   36, -1138, 3168,   38,  -811,  4896,   39,  -662,  3168,  40,  -600,  312,   42, -741,  -3264,
    44, -958,  -2112,  45, -1000, -618,   46,  -1000, 25,     128, 0,     25,    129, 0,     13
};

cKF_Animation_R_c cKF_ba_r_int_hnw077 = {
    cKF_ckcb_r_int_hnw077_tbl, cKF_ds_int_hnw077_tbl, cKF_kn_int_hnw077_tbl, cKF_c_int_hnw077_tbl, -1, 129
};

cKF_Joint_R_c cKF_je_r_int_hnw077_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { int_hnw077_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { int_hnw077_chest_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 1210, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1290, 64836, 0 } },
                                            { int_hnw077_armL_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1290, 700, 0 } },
                                            { int_hnw077_armR_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_hnw077 = { ARRAY_COUNT(cKF_je_r_int_hnw077_tbl), 4, cKF_je_r_int_hnw077_tbl };
