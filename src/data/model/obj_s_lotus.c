#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_lotus_flower_tex_txt[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_lotus_flower_tex_txt[] = {
#include "assets/obj_lotus_flower_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_lotus_leaf_tex_txt[0x400];
#else
u8 obj_lotus_leaf_tex_txt[] = {
#include "assets/obj_lotus_leaf_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_lotus_v[0x9C0 / sizeof(Vtx)];
#else
Vtx obj_s_lotus_v[] = {
#include "assets/obj_s_lotus_v.inc"
};
#endif

Gfx obj_s_lotus_flower1_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_lotus_flower_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_lotus_v, 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 17, 16, 18),
    gsSPNTriangles_5b(19, 13, 12, 20, 10, 9, 8, 7, 21, 5, 4, 22),
    gsSPNTriangles_5b(23, 1, 0, 24, 1, 25, 5, 26, 27, 8, 28, 29),
    gsSPNTriangles_5b(30, 31, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_lotus_v[32], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 6, 4, 3),
    gsSPNTriangles_5b(2, 1, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(17, 18, 19, 20, 18, 21, 22, 23, 16, 24, 25, 13),
    gsSPNTriangles_5b(8, 26, 27, 2, 28, 0, 5, 4, 29, 29, 4, 30),
    gsSPNTriangles_5b(31, 28, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_lotus_v[64], 12, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_lotus_leafH_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_lotus_leaf_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_lotus_v[76], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 2, 1, 4),
    gsSPNTriangles_5b(3, 2, 4, 5, 6, 7, 8, 5, 7, 9, 8, 7),
    gsSPNTriangles_5b(9, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_lotus_leafG_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_lotus_leaf_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_lotus_v[86], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 2, 1, 4),
    gsSPNTriangles_5b(3, 2, 4, 5, 6, 7, 8, 5, 7, 9, 8, 7),
    gsSPNTriangles_5b(9, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_lotus_leafF_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_lotus_leaf_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_lotus_v[96], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 2, 1, 4),
    gsSPNTriangles_5b(3, 2, 4, 5, 6, 7, 8, 5, 7, 9, 8, 7),
    gsSPNTriangles_5b(9, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_lotus_leafE_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_lotus_leaf_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_lotus_v[106], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 2, 1, 4),
    gsSPNTriangles_5b(3, 2, 4, 5, 6, 7, 8, 5, 7, 9, 8, 7),
    gsSPNTriangles_5b(9, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_lotus_leafD_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_lotus_leaf_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_lotus_v[116], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 2, 1, 4),
    gsSPNTriangles_5b(3, 2, 4, 5, 6, 7, 8, 5, 7, 9, 8, 7),
    gsSPNTriangles_5b(9, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_lotus_leafC_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_lotus_leaf_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_lotus_v[126], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 2, 1, 4),
    gsSPNTriangles_5b(3, 2, 4, 5, 6, 7, 8, 5, 7, 9, 8, 7),
    gsSPNTriangles_5b(9, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_lotus_leafB_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_lotus_leaf_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_lotus_v[136], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 2, 1, 4),
    gsSPNTriangles_5b(3, 2, 4, 5, 6, 7, 8, 5, 7, 9, 8, 7),
    gsSPNTriangles_5b(9, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_lotus_leafA_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_lotus_leaf_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_lotus_v[146], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 2, 1, 4),
    gsSPNTriangles_5b(3, 2, 4, 5, 6, 7, 8, 5, 7, 9, 8, 7),
    gsSPNTriangles_5b(9, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_lotus_tbl[] = { { NULL, 9, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 4000, 49536, 3000 } },
                                             { obj_s_lotus_leafA_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 64536, 49536, 5000 } },
                                             { obj_s_lotus_leafB_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 60536, 49536, 2500 } },
                                             { obj_s_lotus_leafC_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 64036, 49536, 1500 } },
                                             { obj_s_lotus_leafD_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 61536, 49536, 63536 } },
                                             { obj_s_lotus_leafE_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 64536, 49536, 60536 } },
                                             { obj_s_lotus_leafF_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 3500, 49536, 60536 } },
                                             { obj_s_lotus_leafG_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 4500, 49536, 64036 } },
                                             { obj_s_lotus_leafH_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1000, 49536, 64536 } },
                                             { obj_s_lotus_flower1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_s_lotus = { ARRAY_COUNT(cKF_je_r_obj_s_lotus_tbl), 9, cKF_je_r_obj_s_lotus_tbl };

u8 cKF_ckcb_r_obj_s_lotus_tbl[] = { 56, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5 };

s16 cKF_kn_obj_s_lotus_tbl[] = { 2, 2, 2, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 3 };

s16 cKF_c_obj_s_lotus_tbl[] = { 0, 0,   0, 0, 0, 900, 0, 0, 0, 900, 0, 0, 0, 900, 0, 0, 0, 900, 0, 0,
                                0, 900, 0, 0, 0, 900, 0, 0, 0, 900, 0, 0, 0, 900, 0, 0, 0, 900, 0 };

s16 cKF_ds_obj_s_lotus_tbl[] = {
    1,  0,  0, 129, 0,  0, 1,   0, 0,  129, 0,  0, 1,   0,  0, 129, 0,  0,  1,  0,  0, 129, 0,  0, 1,   0,  -7,
    33, -5, 0, 97,  5,  0, 129, 0, -7, 1,   0,  0, 129, 0,  0, 1,   -3, 5,  49, 5,  0, 113, -5, 0, 129, -3, 5,
    1,  0,  0, 129, 0,  0, 1,   3, -5, 49,  -5, 0, 113, 5,  0, 129, 3,  -5, 1,  0,  0, 129, 0,  0, 1,   0,  7,
    33, 5,  0, 97,  -5, 0, 129, 0, 7,  1,   0,  0, 129, 0,  0, 1,   -5, -3, 9,  -5, 0, 73,  5,  0, 129, -5, -3,
    1,  0,  0, 129, 0,  0, 1,   3, 5,  17,  5,  0, 81,  -5, 0, 129, 3,  5,  1,  0,  0, 129, 0,  0, 1,   4,  -4,
    55, -5, 0, 119, 5,  0, 129, 4, -4, 1,   0,  0, 129, 0,  0, 1,   -2, -7, 25, -5, 0, 89,  5,  0, 129, -2, -7,
    1,  0,  0, 129, 0,  0, 1,   5, 0,  65,  -5, 0, 129, 5,  0
};

cKF_Animation_R_c cKF_ba_r_obj_s_lotus = {
    cKF_ckcb_r_obj_s_lotus_tbl, cKF_ds_obj_s_lotus_tbl, cKF_kn_obj_s_lotus_tbl, cKF_c_obj_s_lotus_tbl, -1, 129
};
