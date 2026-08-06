#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_hnw076_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_hnw076_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_hnw076_pal[] = {
#include "assets/int_hnw076_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw076_arm_tex_txt[0x100];
#else
u8 int_hnw076_arm_tex_txt[] = {
#include "assets/int_hnw076_arm_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw076_armtop_tex_txt[0x80];
#else
u8 int_hnw076_armtop_tex_txt[] = {
#include "assets/int_hnw076_armtop_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw076_c_front_tex_txt[0x300];
#else
u8 int_hnw076_c_front_tex_txt[] = {
#include "assets/int_hnw076_c_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw076_c_back_tex_txt[0x180];
#else
u8 int_hnw076_c_back_tex_txt[] = {
#include "assets/int_hnw076_c_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw076_b_back_tex_txt[0x80];
#else
u8 int_hnw076_b_back_tex_txt[] = {
#include "assets/int_hnw076_b_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw076_b_front_tex_txt[0x100];
#else
u8 int_hnw076_b_front_tex_txt[] = {
#include "assets/int_hnw076_b_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_hnw076_v[0x470 / sizeof(Vtx)];
#else
Vtx int_hnw076_v[] = {
#include "assets/int_hnw076_v.inc"
};
#endif

Gfx int_hnw076_chest_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw076_v[24], 7, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw076_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_hnw076_c_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&int_hnw076_v[31], 22, 7),
    gsSPNTrianglesInit_5b(7, 5, 7, 8, 4, 5, 9, 5, 6, 10),
    gsSPNTriangles_5b(4, 11, 12, 0, 4, 13, 6, 2, 14, 6, 15, 16),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_hnw076_c_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 1, 18, 17, 3, 1, 19, 3, 20, 21),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_hnw076_c_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 22, 23, 24, 25, 26, 24, 27, 28, 22),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_hnw076_c_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_hnw076_v[53], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 1, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw076_armR_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw076_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_hnw076_arm_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_hnw076_v, 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 2, 3, 0, 4, 3, 5),
    gsSPNTriangles_5b(5, 1, 4, 6, 1, 7, 8, 1, 6, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw076_armtop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw076_armL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw076_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_hnw076_arm_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw076_v[12], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 1, 0, 4, 1, 5),
    gsSPNTriangles_5b(5, 6, 4, 7, 6, 8, 8, 1, 7, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw076_armtop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw076_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw076_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw076_b_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw076_v[57], 14, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_hnw076_b_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7, 5, 6, 7, 5, 8, 6, 8, 9, 6),
    gsSPNTriangles_5b(7, 10, 11, 11, 5, 7, 9, 8, 12, 9, 12, 13),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_hnw076_tbl[] = { 0, 0, 5, 0, 4, 0, 4 };

s16 cKF_kn_int_hnw076_tbl[] = { 7, 36, 9, 9 };

s16 cKF_c_int_hnw076_tbl[] = { 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, -900, 0, 0, 0, 0, -2700, 0, 0 };

s16 cKF_ds_int_hnw076_tbl[] = {
    1,   -200,  938,    2,  -169,  1500,  4,   -31,   1500,   5,   0,     469,    6,  0,     0,     55,  0,     -2,
    129, -200,  -3,     1,  350,   -3047, 2,   248,   -4875,  4,   -198,  -4875,  5,  -300,  -634,  6,   -241,  3010,
    8,   69,    4651,   9,  211,   3010,  10,  270,   109,    11,  218,   -2640,  13, -54,   -4080, 14,  -178,  -2640,
    15,  -230,  -109,   17, -79,   3509,  19,  155,   2270,   20,  200,   78,     22, 66,    -3101, 24,  -140,  -2006,
    25,  -180,  -78,    27, -64,   2693,  29,  116,   1742,   30,  150,   78,     32, 51,    -2285, 34,  -101,  -1478,
    35,  -130,  -78,    37, -49,   1877,  39,  76,    1214,   40,  100,   94,     43, -10,   -1387, 44,  -52,   -898,
    45,  -70,   -78,    48, 8,     979,   50,  50,    62,     54,  -22,   -422,   57, -29,   24,    128, 350,   12,
    129, 350,   6,      1,  0,     -8438, 2,   -281,  -13500, 4,   -1519, -13500, 5,  -1800, -4219, 6,   -1800, 0,
    54,  -1800, 0,      59, -1785, 224,   128, -1,    58,     129, 0,     29,     1,  0,     -8438, 2,   -281,  -13500,
    4,   -1519, -13500, 5,  -1800, -4219, 6,   -1800, 0,      54,  -1800, 0,      59, -1785, 224,   128, -1,    58,
    129, 0,     29
};

cKF_Animation_R_c cKF_ba_r_int_hnw076 = {
    cKF_ckcb_r_int_hnw076_tbl, cKF_ds_int_hnw076_tbl, cKF_kn_int_hnw076_tbl, cKF_c_int_hnw076_tbl, -1, 129
};

cKF_Joint_R_c cKF_je_r_int_hnw076_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { int_hnw076_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { int_hnw076_chest_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 650, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 850, 64836, 0 } },
                                            { int_hnw076_armL_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 850, 700, 0 } },
                                            { int_hnw076_armR_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_hnw076 = { ARRAY_COUNT(cKF_je_r_int_hnw076_tbl), 4, cKF_je_r_int_hnw076_tbl };
