#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_hnw079_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_hnw079_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_hnw079_pal[] = {
#include "assets/int_hnw079_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw079_arm_tex_txt[0x100];
#else
u8 int_hnw079_arm_tex_txt[] = {
#include "assets/int_hnw079_arm_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw079_armtop_tex_txt[0x80];
#else
u8 int_hnw079_armtop_tex_txt[] = {
#include "assets/int_hnw079_armtop_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw079_c_front_tex_txt[0x300];
#else
u8 int_hnw079_c_front_tex_txt[] = {
#include "assets/int_hnw079_c_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw079_c_back_tex_txt[0x180];
#else
u8 int_hnw079_c_back_tex_txt[] = {
#include "assets/int_hnw079_c_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw079_b_back_tex_txt[0x80];
#else
u8 int_hnw079_b_back_tex_txt[] = {
#include "assets/int_hnw079_b_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw079_b_front_tex_txt[0x100];
#else
u8 int_hnw079_b_front_tex_txt[] = {
#include "assets/int_hnw079_b_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_hnw079_v[0x470 / sizeof(Vtx)];
#else
Vtx int_hnw079_v[] = {
#include "assets/int_hnw079_v.inc"
};
#endif

Gfx int_hnw079_chest_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw079_v[24], 7, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw079_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_hnw079_c_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&int_hnw079_v[31], 22, 7),
    gsSPNTrianglesInit_5b(7, 5, 7, 8, 4, 5, 9, 5, 6, 10),
    gsSPNTriangles_5b(4, 11, 12, 0, 4, 13, 6, 2, 14, 6, 15, 16),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_hnw079_c_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 1, 18, 17, 3, 1, 19, 3, 20, 21),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_hnw079_c_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 22, 23, 24, 25, 26, 24, 27, 28, 22),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_hnw079_c_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_hnw079_v[53], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 1, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw079_armR_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw079_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_hnw079_arm_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw079_v[12], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 2, 3, 0, 4, 3, 5),
    gsSPNTriangles_5b(5, 1, 4, 6, 1, 7, 8, 1, 6, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw079_armtop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw079_armL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw079_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_hnw079_arm_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_hnw079_v, 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 1, 0, 4, 1, 5),
    gsSPNTriangles_5b(5, 6, 4, 7, 6, 8, 8, 1, 7, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw079_armtop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw079_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw079_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw079_b_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw079_v[57], 14, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_hnw079_b_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7, 5, 6, 7, 5, 8, 6, 8, 9, 6),
    gsSPNTriangles_5b(7, 10, 11, 11, 5, 7, 9, 8, 12, 9, 12, 13),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_hnw079_tbl[] = { 0, 0, 1, 0, 4, 0, 4 };

s16 cKF_kn_int_hnw079_tbl[] = { 36, 44, 44 };

s16 cKF_c_int_hnw079_tbl[] = { 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, -900, 0, 0, 0, 0, -2700, 0, 0 };

s16 cKF_ds_int_hnw079_tbl[] = {
    1,   -330,  2953,   2,  -232,  4725,   4,   202,   4725,   5,   300,   587,    6,   241,   -3010,
    8,   -69,   -4651,  9,  -211,  -3010,  10,  -270,  -94,    11,  -217,  2693,   13,  60,    4162,
    14,  187,   2693,   15, 240,   94,     17,  82,    -3672,  19,  -163,  -2376,  20,  -210,  -94,
    22,  -73,   3182,   24, 139,   2059,   25,  180,   94,     27,  64,    -2693,  29,  -116,  -1742,
    30,  -150,  -94,    32, -55,   2203,   34,  92,    1426,   35,  120,   94,     38,  -16,   -1714,
    39,  -68,   -1109,  40, -90,   -94,    43,  7,     1224,   44,  44,    792,    45,  60,    94,
    47,  28,    -734,   49, -21,   -475,   54,  6,     211,    57,  9,     -17,    128, -250,  -8,
    129, -250,  -4,     1,  0,     -7969,  2,   -266,  -12750, 4,   -1434, -12750, 5,   -1700, -1332,
    6,   -1523, 8976,   8,  -598,  13872,  9,   -177,  8976,   10,  0,     312,    11,  -156,  -7920,
    13,  -972,  -12240, 14, -1344, -7920,  15,  -1500, -156,   16,  -1354, 7392,   18,  -593,  11424,
    19,  -246,  7392,   20, -100,  312,    21,  -225,  -6336,  23,  -878,  -9792,  24,  -1175, -6336,
    25,  -1300, -156,   26, -1186, 5808,   28,  -587,  8976,   29,  -314,  5808,   30,  -200,  312,
    31,  -294,  -4752,  33, -783,  -7344,  34,  -1006, -4752,  35,  -1100, -156,   36,  -1017, 4224,
    38,  -582,  6528,   39, -383,  4224,   40,  -300,  312,    42,  -511,  -4896,  44,  -838,  -3168,
    45,  -900,  -156,   47, -724,  4080,   49,  -452,  2640,   50,  -400,  156,    52,  -541,  -3264,
    54,  -758,  -2112,  55, -800,  -617,   56,  -800,  26,     128, 0,     26,     129, 0,     13,
    1,   0,     -8438,  2,  -281,  -13500, 4,   -1519, -13500, 5,   -1800, -1411,  6,   -1613, 9504,
    8,   -634,  14688,  9,  -187,  9504,   10,  0,     312,    11,  -166,  -8448,  13,  -1037, -13056,
    14,  -1434, -8448,  15, -1600, -156,   16,  -1444, 7920,   18,  -628,  12240,  19,  -256,  7920,
    20,  -100,  312,    21, -235,  -6864,  23,  -942,  -10608, 24,  -1265, -6864,  25,  -1400, -156,
    26,  -1275, 6336,   28, -622,  9792,   29,  -325,  6336,   30,  -200,  312,    31,  -304,  -5280,
    33,  -848,  -8160,  34, -1096, -5280,  35,  -1200, -156,   36,  -1106, 4752,   38,  -617,  7344,
    39,  -394,  4752,   40, -300,  312,    42,  -546,  -5712,  44,  -927,  -3696,  45,  -1000, -156,
    47,  -789,  4896,   49, -462,  3168,   50,  -400,  156,    52,  -576,  -4080,  54,  -848,  -2640,
    55,  -900,  -773,   56, -900,  29,     128, 0,     29,     129, 0,     15
};

cKF_Animation_R_c cKF_ba_r_int_hnw079 = {
    cKF_ckcb_r_int_hnw079_tbl, cKF_ds_int_hnw079_tbl, cKF_kn_int_hnw079_tbl, cKF_c_int_hnw079_tbl, -1, 129
};

cKF_Joint_R_c cKF_je_r_int_hnw079_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { int_hnw079_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { int_hnw079_chest_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 700, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 600, 64836, 0 } },
                                            { int_hnw079_armL_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 600, 700, 0 } },
                                            { int_hnw079_armR_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_hnw079 = { ARRAY_COUNT(cKF_je_r_int_hnw079_tbl), 4, cKF_je_r_int_hnw079_tbl };
