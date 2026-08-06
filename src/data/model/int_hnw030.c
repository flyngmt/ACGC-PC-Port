#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_hnw030_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_hnw030_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_hnw030_pal[] = {
#include "assets/int_hnw030_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw030_arm_tex_txt[0x100];
#else
u8 int_hnw030_arm_tex_txt[] = {
#include "assets/int_hnw030_arm_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw030_armtop_tex_txt[0x80];
#else
u8 int_hnw030_armtop_tex_txt[] = {
#include "assets/int_hnw030_armtop_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw030_c_front_tex_txt[0x300];
#else
u8 int_hnw030_c_front_tex_txt[] = {
#include "assets/int_hnw030_c_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw030_c_back_tex_txt[0x180];
#else
u8 int_hnw030_c_back_tex_txt[] = {
#include "assets/int_hnw030_c_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw030_b_back_tex_txt[0x80];
#else
u8 int_hnw030_b_back_tex_txt[] = {
#include "assets/int_hnw030_b_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hnw030_b_front_tex_txt[0x100];
#else
u8 int_hnw030_b_front_tex_txt[] = {
#include "assets/int_hnw030_b_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_hnw030_v[0x470 / sizeof(Vtx)];
#else
Vtx int_hnw030_v[] = {
#include "assets/int_hnw030_v.inc"
};
#endif

Gfx int_hnw030_chest_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw030_v[24], 7, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw030_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_hnw030_c_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&int_hnw030_v[31], 22, 7),
    gsSPNTrianglesInit_5b(7, 6, 7, 8, 4, 6, 9, 6, 5, 10),
    gsSPNTriangles_5b(4, 11, 12, 2, 4, 13, 5, 0, 14, 5, 15, 16),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_hnw030_c_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 3, 18, 17, 1, 3, 19, 1, 20, 21),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_hnw030_c_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 22, 23, 24, 25, 26, 24, 27, 28, 22),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_hnw030_c_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_hnw030_v[53], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 1, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw030_armR_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw030_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_hnw030_arm_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_hnw030_v, 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 2, 3, 0, 4, 3, 5),
    gsSPNTriangles_5b(5, 1, 4, 6, 1, 7, 8, 1, 6, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw030_armtop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw030_armL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw030_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_hnw030_arm_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw030_v[12], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 1, 0, 4, 1, 5),
    gsSPNTriangles_5b(5, 6, 4, 7, 6, 8, 8, 1, 7, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw030_armtop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_hnw030_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hnw030_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_hnw030_b_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hnw030_v[57], 14, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_hnw030_b_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7, 5, 6, 7, 6, 8, 7, 6, 9, 8),
    gsSPNTriangles_5b(9, 10, 11, 11, 8, 9, 5, 7, 12, 5, 12, 13),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_hnw030_tbl[] = { 0, 0, 3, 0, 4, 0, 4 };

s16 cKF_kn_int_hnw030_tbl[] = { 7, 10, 7, 7 };

s16 cKF_c_int_hnw030_tbl[] = { 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, -900, 0, 0, 0, 0, -2700, 0, 0 };

s16 cKF_ds_int_hnw030_tbl[] = { 1,  0,     556,   2,  19,    972,  6,  231,  972,   7,  250,   173,   8,  243,   -390,
                                16, 7,     -390,  17, 0,     -210, 1,  0,    1167,  2,  39,    1667,  3,  111,   1667,
                                4,  150,   334,   5,  133,   -892, 10, -133, -892,  11, -150,  -83,   14, -75,   1083,
                                16, -11,   583,   17, 0,     333,  1,  -900, -4511, 2,  -1050, -6880, 4,  -1663, -6620,
                                5,  -1800, -1795, 6,  -1782, 1000, 16, -918, 1000,  17, -900,  531,   1,  -900,  4219,
                                2,  -759,  6750,  4,  -141,  6750, 5,  0,    1844,  6,  -18,   -1000, 16, -882,  -1000,
                                17, -900,  -531 };

cKF_Animation_R_c cKF_ba_r_int_hnw030 = {
    cKF_ckcb_r_int_hnw030_tbl, cKF_ds_int_hnw030_tbl, cKF_kn_int_hnw030_tbl, cKF_c_int_hnw030_tbl, -1, 17
};

cKF_Joint_R_c cKF_je_r_int_hnw030_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { int_hnw030_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { int_hnw030_chest_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 1210, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1290, 64836, 0 } },
                                            { int_hnw030_armL_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1290, 700, 0 } },
                                            { int_hnw030_armR_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_hnw030 = { ARRAY_COUNT(cKF_je_r_int_hnw030_tbl), 4, cKF_je_r_int_hnw030_tbl };
