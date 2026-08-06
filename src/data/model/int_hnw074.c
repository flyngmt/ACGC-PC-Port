#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_hnw074_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_hnw074_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_hnw074_pal[] = {
#include "assets/int_hnw074_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw074_arm_tex_txt[0x100];
#else
u8 int_hnw074_arm_tex_txt[] = {
#include "assets/int_hnw074_arm_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw074_armtop_tex_txt[0x80];
#else
u8 int_hnw074_armtop_tex_txt[] = {
#include "assets/int_hnw074_armtop_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw074_c_front_tex_txt[0x300];
#else
u8 int_hnw074_c_front_tex_txt[] = {
#include "assets/int_hnw074_c_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw074_c_back_tex_txt[0x180];
#else
u8 int_hnw074_c_back_tex_txt[] = {
#include "assets/int_hnw074_c_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw074_b_back_tex_txt[0x80];
#else
u8 int_hnw074_b_back_tex_txt[] = {
#include "assets/int_hnw074_b_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw074_b_front_tex_txt[0x100];
#else
u8 int_hnw074_b_front_tex_txt[] = {
#include "assets/int_hnw074_b_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_hnw074_v[0x470 / sizeof(Vtx)];
#else
Vtx int_hnw074_v[] = {
#include "assets/int_hnw074_v.inc"
};
#endif

Gfx int_hnw074_chest_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw074_v[24], 7, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw074_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_hnw074_c_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&int_hnw074_v[31], 22, 7),
    gsSPNTrianglesInit_5b(7, 5, 7, 8, 6, 5, 9, 5, 4, 10),
    gsSPNTriangles_5b(6, 11, 12, 0, 6, 13, 4, 2, 14, 4, 15, 16),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_hnw074_c_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 1, 18, 17, 3, 1, 19, 3, 20, 21),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_hnw074_c_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 22, 23, 24, 25, 26, 24, 27, 28, 22),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_hnw074_c_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_hnw074_v[53], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 1, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw074_armR_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw074_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_hnw074_arm_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_hnw074_v, 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 2, 3, 0, 4, 3, 5),
    gsSPNTriangles_5b(5, 1, 4, 6, 1, 7, 8, 1, 6, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw074_armtop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw074_armL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw074_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_hnw074_arm_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw074_v[12], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 1, 0, 4, 1, 5),
    gsSPNTriangles_5b(5, 6, 4, 7, 6, 8, 8, 1, 7, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw074_armtop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw074_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw074_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw074_b_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw074_v[57], 14, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_hnw074_b_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7, 5, 6, 7, 6, 8, 7, 6, 9, 8),
    gsSPNTriangles_5b(9, 10, 11, 11, 8, 9, 5, 7, 12, 5, 12, 13),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_hnw074_tbl[] = { 0, 0, 4, 0, 1, 0, 1 };

s16 cKF_kn_int_hnw074_tbl[] = { 27, 26, 26 };

s16 cKF_c_int_hnw074_tbl[] = { 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, -900, -1800, 0, 0, 0, -2700, 0, 0 };

s16 cKF_ds_int_hnw074_tbl[] = { 1,  0,    -1789, 2,   -60,  -2556, 3,   -170, -2556, 4,   -230, 778,   5,  -119, 4778,
                                6,  89,   4778,  7,   200,  233,   8,   104,  -4111, 9,   -74,  -4111, 10, -170, -233,
                                11, -90,  3444,  12,  60,   3444,  13,  140,  233,   14,  75,   -2778, 15, -45,  -2778,
                                16, -110, -194,  17,  -58,  2222,  18,  38,   2222,  19,  90,   156,   20, 49,   -1778,
                                21, -29,  -1778, 22,  -70,  -350,  23,  -52,  778,   24,  -18,  778,   25, 0,    272,
                                26, 0,    0,     129, 0,    0,     1,   0,    -2022, 2,   -67,  -2889, 3,  -193, -2889,
                                4,  -260, 856,   5,   -136, 5333,  6,   96,   5333,  7,   220,  311,   8,  116,  -4444,
                                9,  -76,  -4444, 10,  -180, -272,  11,  -94,  3667,  12,  64,   3667,  13, 150,  233,
                                14, 80,   -3000, 15,  -50,  -3000, 16,  -120, -233,  17,  -66,  2333,  18, 36,   2333,
                                19, 90,   233,   21,  -21,  -1667, 22,  -60,  -350,  23,  -44,  667,   24, -16,  667,
                                25, 0,    233,   26,  0,    0,     129, 0,    0,     1,   0,    2022,  2,  67,   2889,
                                3,  193,  2889,  4,   260,  -856,  5,   136,  -5333, 6,   -96,  -5333, 7,  -220, -311,
                                8,  -116, 4444,  9,   76,   4444,  10,  180,  272,   11,  94,   -3667, 12, -64,  -3667,
                                13, -150, -233,  14,  -80,  3000,  15,  50,   3000,  16,  120,  233,   17, 66,   -2333,
                                18, -36,  -2333, 19,  -90,  -233,  21,  21,   1667,  22,  60,   350,   23, 44,   -667,
                                24, 16,   -667,  25,  0,    -233,  26,  0,    0,     129, 0,    0 };

cKF_Animation_R_c cKF_ba_r_int_hnw074 = {
    cKF_ckcb_r_int_hnw074_tbl, cKF_ds_int_hnw074_tbl, cKF_kn_int_hnw074_tbl, cKF_c_int_hnw074_tbl, -1, 129
};

cKF_Joint_R_c cKF_je_r_int_hnw074_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { int_hnw074_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { int_hnw074_chest_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 1210, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1290, 64836, 0 } },
                                            { int_hnw074_armL_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1290, 700, 0 } },
                                            { int_hnw074_armR_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_hnw074 = { ARRAY_COUNT(cKF_je_r_int_hnw074_tbl), 4, cKF_je_r_int_hnw074_tbl };
