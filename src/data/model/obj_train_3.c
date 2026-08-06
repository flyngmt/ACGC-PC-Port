#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_train1_t6_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_train1_t6_tex_txt[] = {
#include "assets/obj_train1_t6_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_train1_t5_tex_txt[0x800];
#else
u8 obj_train1_t5_tex_txt[] = {
#include "assets/obj_train1_t5_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_train1_t4_tex_txt[0x800];
#else
u8 obj_train1_t4_tex_txt[] = {
#include "assets/obj_train1_t4_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_train_3_v[0x650 / sizeof(Vtx)];
#else
Vtx obj_train_3_v[] = {
#include "assets/obj_train_3_v.inc"
};
#endif

Gfx obj_train1_3_t6_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_train1_t6_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_train_3_v[54], 26, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 11, 8, 10, 11, 12, 8),
    gsSPNTriangles_5b(13, 14, 15, 14, 16, 15, 17, 18, 19, 19, 20, 17),
    gsSPNTriangles_5b(17, 21, 18, 22, 23, 24, 22, 25, 23, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_train1_3_t5_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 256, 16, obj_train1_t5_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_train_3_v[8], 10, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 4, 7, 5, 8, 4, 9),
    gsSPNTriangles_5b(4, 6, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_train_3_v[18], 32, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 16, 19, 17, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 24, 25, 26, 24, 27, 25, 28, 29, 30),
    gsSPNTriangles_5b(29, 31, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_train_3_v[50], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_train1_3_t4_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_train1_t4_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_train_3_v[80], 21, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 1, 3, 2, 4, 1, 0),
    gsSPNTriangles_5b(4, 5, 1, 2, 6, 7, 2, 3, 6, 8, 9, 10),
    gsSPNTriangles_5b(10, 9, 11, 12, 9, 8, 9, 13, 11, 13, 14, 11),
    gsSPNTriangles_5b(9, 12, 13, 12, 15, 13, 13, 16, 14, 15, 16, 13),
    gsSPNTriangles_5b(17, 18, 19, 17, 19, 20, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_train1_3_door1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_train1_t6_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_train_3_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_train1_3_door2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_train1_t6_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_train_3_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_train1_3_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 8000, 2000, 2500 } },
                                              { obj_train1_3_t4_model, 3, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_train1_3_door1_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_train1_3_door2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_train1_3_t5_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_train1_3_t6_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_train1_3 = { ARRAY_COUNT(cKF_je_r_obj_train1_3_tbl), 5, cKF_je_r_obj_train1_3_tbl };

u8 cKF_ckcb_r_obj_train1_3_close_tbl[] = { 56, 7, 7, 7, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_train1_3_close_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 6, 2, 2, 6, 2 };

s16 cKF_c_obj_train1_3_close_tbl[] = { 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_train1_3_close_tbl[] = {
    1, 8000,  0, 32, 8000,  0,     1,  2000,  0, 32, 2000, 0,    1,  2500, 0, 32, 2500, 0, 1, 0,    0,  32, 0,    0,
    1, 0,     0, 32, 0,     0,     1,  0,     0, 32, 0,    0,    1,  0,    0, 32, 0,    0, 1, -100, -9, 5,  -200, 3,
    6, -200,  3, 28, -900,  -1568, 30, -890,  0, 32, -900, 13,   1,  0,    0, 32, 0,    0, 1, 0,    0,  32, 0,    0,
    1, -1600, 0, 5,  -1400, 0,     6,  -1400, 0, 28, 0,    3075, 30, -20,  0, 32, 0,    9, 1, 0,    0,  32, 0,    0
};

cKF_Animation_R_c cKF_ba_r_obj_train1_3_close = { cKF_ckcb_r_obj_train1_3_close_tbl,
                                                  cKF_ds_obj_train1_3_close_tbl,
                                                  cKF_kn_obj_train1_3_close_tbl,
                                                  cKF_c_obj_train1_3_close_tbl,
                                                  -1,
                                                  32 };

u8 cKF_ckcb_r_obj_train1_3_open_tbl[] = { 56, 7, 7, 7, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_train1_3_open_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 6, 2, 2, 6, 2 };

s16 cKF_c_obj_train1_3_open_tbl[] = { 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_train1_3_open_tbl[] = {
    1, 8000, 0,  24, 8000, 0,    1,  2000, 0,    24, 2000,  0,     1,  2500,  0, 24, 2500,  0, 1, 0,    0,  24, 0,    0,
    1, 0,    0,  24, 0,    0,    1,  0,    0,    24, 0,     0,     1,  0,     0, 24, 0,     0, 1, -900, 13, 5,  -700, 0,
    6, -700, -5, 20, -80,  1491, 22, -120, -150, 24, -100,  -9,    1,  0,     0, 24, 0,     0, 1, 0,    0,  24, 0,    0,
    1, 0,    9,  5,  -400, 0,    6,  -400, 0,    20, -1620, -2972, 22, -1580, 0, 24, -1600, 0, 1, 0,    0,  24, 0,    0
};

cKF_Animation_R_c cKF_ba_r_obj_train1_3_open = { cKF_ckcb_r_obj_train1_3_open_tbl,
                                                 cKF_ds_obj_train1_3_open_tbl,
                                                 cKF_kn_obj_train1_3_open_tbl,
                                                 cKF_c_obj_train1_3_open_tbl,
                                                 -1,
                                                 24 };
