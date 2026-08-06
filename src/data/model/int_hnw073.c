#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_hnw073_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_hnw073_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_hnw073_pal[] = {
#include "assets/int_hnw073_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw073_arm_tex_txt[0x100];
#else
u8 int_hnw073_arm_tex_txt[] = {
#include "assets/int_hnw073_arm_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw073_armtop_tex_txt[0x80];
#else
u8 int_hnw073_armtop_tex_txt[] = {
#include "assets/int_hnw073_armtop_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw073_c_front_tex_txt[0x300];
#else
u8 int_hnw073_c_front_tex_txt[] = {
#include "assets/int_hnw073_c_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw073_c_back_tex_txt[0x180];
#else
u8 int_hnw073_c_back_tex_txt[] = {
#include "assets/int_hnw073_c_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw073_b_back_tex_txt[0x80];
#else
u8 int_hnw073_b_back_tex_txt[] = {
#include "assets/int_hnw073_b_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw073_b_front_tex_txt[0x100];
#else
u8 int_hnw073_b_front_tex_txt[] = {
#include "assets/int_hnw073_b_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_hnw073_v[0x470 / sizeof(Vtx)];
#else
Vtx int_hnw073_v[] = {
#include "assets/int_hnw073_v.inc"
};
#endif

Gfx int_hnw073_chest_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw073_v[24], 7, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw073_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_hnw073_c_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&int_hnw073_v[31], 22, 7),
    gsSPNTrianglesInit_5b(7, 5, 7, 8, 6, 5, 9, 5, 4, 10),
    gsSPNTriangles_5b(6, 11, 12, 0, 6, 13, 4, 2, 14, 4, 15, 16),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_hnw073_c_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 1, 18, 17, 3, 1, 19, 3, 20, 21),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_hnw073_c_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 22, 23, 24, 25, 26, 24, 27, 28, 22),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_hnw073_c_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_hnw073_v[53], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 1, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw073_armR_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw073_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_hnw073_arm_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_hnw073_v, 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 2, 3, 0, 4, 3, 5),
    gsSPNTriangles_5b(5, 1, 4, 6, 1, 7, 8, 1, 6, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw073_armtop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw073_armL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw073_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_hnw073_arm_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw073_v[12], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 1, 0, 4, 1, 5),
    gsSPNTriangles_5b(5, 6, 4, 7, 6, 8, 8, 1, 7, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw073_armtop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw073_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw073_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw073_b_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw073_v[57], 14, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_hnw073_b_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7, 5, 6, 7, 5, 8, 6, 8, 9, 6),
    gsSPNTriangles_5b(7, 10, 11, 11, 5, 7, 9, 8, 12, 9, 12, 13),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_hnw073_tbl[] = { 0, 0, 2, 0, 1, 0, 1 };

s16 cKF_kn_int_hnw073_tbl[] = { 26, 27, 27 };

s16 cKF_c_int_hnw073_tbl[] = { 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, -900, 0, 100, 0, 0, -2700, -1800, 100 };

s16 cKF_ds_int_hnw073_tbl[] = { 1,   100,  1167,  2,  139,  1667,  3,   211,  1667,  4,  250,  0,     5,   211,  -1667,
                                6,   139,  -1667, 7,  100,  194,   8,   152,  2222,  9,  248,  2222,  10,  300,  194,
                                11,  261,  -1667, 12, 189,  -1667, 13,  150,  194,   14, 202,  2222,  15,  298,  2222,
                                16,  350,  194,   17, 311,  -1667, 18,  239,  -1667, 19, 200,  194,   20,  252,  2222,
                                22,  400,  -389,  23, 322,  -3333, 24,  178,  -3333, 25, 100,  -1167, 26,  100,  0,
                                129, 100,  0,     1,  -250, 2722,  2,   -159, 3889,  3,  9,    3889,  4,   100,  583,
                                5,   48,   -2222, 6,  -48,  -2222, 7,   -100, 0,     8,  -48,  2222,  9,   48,   2222,
                                10,  100,  0,     11, 48,   -2222, 12,  -48,  -2222, 13, -100, 0,     14,  -48,  2222,
                                15,  48,   2222,  16, 100,  0,     17,  48,   -2222, 18, -48,  -2222, 19,  -100, 0,
                                20,  -48,  2222,  21, 48,   2222,  22,  100,  -583,  23, 9,    -3889, 24,  -159, -3889,
                                25,  -250, -1361, 26, -250, 0,     129, -250, 0,     1,  250,  -2722, 2,   159,  -3889,
                                3,   -9,   -3889, 4,  -100, -583,  5,   -48,  2222,  6,  48,   2222,  7,   100,  0,
                                8,   48,   -2222, 9,  -48,  -2222, 10,  -100, 0,     11, -48,  2222,  12,  48,   2222,
                                13,  100,  0,     14, 48,   -2222, 15,  -48,  -2222, 16, -100, 0,     17,  -48,  2222,
                                18,  48,   2222,  19, 100,  0,     20,  48,   -2222, 21, -48,  -2222, 22,  -100, 583,
                                23,  -9,   3889,  24, 159,  3889,  25,  250,  1361,  26, 250,  0,     129, 250,  0 };

cKF_Animation_R_c cKF_ba_r_int_hnw073 = {
    cKF_ckcb_r_int_hnw073_tbl, cKF_ds_int_hnw073_tbl, cKF_kn_int_hnw073_tbl, cKF_c_int_hnw073_tbl, -1, 129
};

cKF_Joint_R_c cKF_je_r_int_hnw073_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { int_hnw073_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { int_hnw073_chest_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 650, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 850, 64836, 0 } },
                                            { int_hnw073_armL_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 850, 700, 0 } },
                                            { int_hnw073_armR_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_hnw073 = { ARRAY_COUNT(cKF_je_r_int_hnw073_tbl), 4, cKF_je_r_int_hnw073_tbl };
