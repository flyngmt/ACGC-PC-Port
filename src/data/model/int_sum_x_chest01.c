#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_x_chest01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_x_chest01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_x_chest01_pal[] = {
#include "assets/int_sum_x_chest01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_chest01_hiki_txt[0x100];
#else
u8 int_sum_x_chest01_hiki_txt[] = {
#include "assets/int_sum_x_chest01_hiki_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_chest01_into_txt[0x100];
#else
u8 int_sum_x_chest01_into_txt[] = {
#include "assets/int_sum_x_chest01_into_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_chest01_front_txt[0x200];
#else
u8 int_sum_x_chest01_front_txt[] = {
#include "assets/int_sum_x_chest01_front_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_chest01_side_txt[0x300];
#else
u8 int_sum_x_chest01_side_txt[] = {
#include "assets/int_sum_x_chest01_side_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_chest01_head_txt[0x80];
#else
u8 int_sum_x_chest01_head_txt[] = {
#include "assets/int_sum_x_chest01_head_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_x_chest01_v[0x510 / sizeof(Vtx)];
#else
Vtx int_sum_x_chest01_v[] = {
#include "assets/int_sum_x_chest01_v.inc"
};
#endif

Gfx int_sum_x_chest01_L_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_x_chest01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_x_chest01_hiki_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_x_chest01_v, 15, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_x_chest01_into_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(5, 4, 5, 6, 7, 8, 9, 7, 9, 10),
    gsSPNTriangles_5b(11, 12, 13, 11, 14, 12, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_x_chest01_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_x_chest01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_x_chest01_front_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_x_chest01_v[30], 17, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_x_chest01_side_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_x_chest01_v[47], 29, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 16, 17, 18, 16, 19, 17, 19, 20, 17),
    gsSPNTriangles_5b(21, 22, 23, 22, 24, 23, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_x_chest01_into_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 25, 26, 27, 25, 28, 26, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_x_chest01_head_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_x_chest01_v[76], 5, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_x_chest01_R_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_x_chest01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_x_chest01_hiki_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_x_chest01_v[15], 15, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_x_chest01_into_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(5, 4, 5, 6, 7, 8, 9, 8, 10, 9),
    gsSPNTriangles_5b(11, 12, 13, 11, 13, 14, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_x_chest01_tbl[] = { 56, 7, 0, 7, 7 };

s16 cKF_kn_int_sum_x_chest01_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 3 };

s16 cKF_c_int_sum_x_chest01_tbl[] = { -900, 0, 0, 0, 0, 900 };

s16 cKF_ds_int_sum_x_chest01_tbl[] = { 1, -1375, 0,    12, -1375, 0,    1,   3625, 0, 12,  3625,  0,  1,    0,  0, 12,
                                       0, 0,     1,    0,  0,     12,   0,   0,    1, 0,   0,     12, 0,    0,  1, -900,
                                       0, 12,    -900, 0,  1,     0,    0,   12,   0, 0,   1,     0,  0,    12, 0, 0,
                                       1, 1800,  0,    6,  2250,  3785, 12,  2850, 0, 1,   0,     0,  12,   0,  0, 1,
                                       0, 0,     12,   0,  0,     1,    900, 0,    6, 450, -3818, 12, -150, 0 };

cKF_Animation_R_c cKF_ba_r_int_sum_x_chest01 = { cKF_ckcb_r_int_sum_x_chest01_tbl,
                                                 cKF_ds_int_sum_x_chest01_tbl,
                                                 cKF_kn_int_sum_x_chest01_tbl,
                                                 cKF_c_int_sum_x_chest01_tbl,
                                                 -1,
                                                 12 };

cKF_Joint_R_c cKF_je_r_int_sum_x_chest01_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 64161, 3625, 0 } },
    { int_sum_x_chest01_base_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1500, 2750, 0 } },
    { int_sum_x_chest01_R_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_x_chest01_L_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1500, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_x_chest01 = { ARRAY_COUNT(cKF_je_r_int_sum_x_chest01_tbl), 3,
                                                cKF_je_r_int_sum_x_chest01_tbl };
