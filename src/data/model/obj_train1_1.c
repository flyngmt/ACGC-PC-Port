#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_train1_t3_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_train1_t3_tex_txt[] = {
#include "assets/obj_train1_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_train1_t1_tex_txt[0x800];
#else
u8 obj_train1_t1_tex_txt[] = {
#include "assets/obj_train1_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_train1_t2_tex_txt[0x800];
#else
u8 obj_train1_t2_tex_txt[] = {
#include "assets/obj_train1_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_train1_1_v[0x860 / sizeof(Vtx)];
#else
Vtx obj_train1_1_v[] = {
#include "assets/obj_train1_1_v.inc"
};
#endif

Gfx obj_train1_1_t3_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_train1_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_train1_1_v[93], 15, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 11, 12, 13, 11, 13, 14, 0, 0, 0),
    gsSPVertex(&obj_train1_1_v[108], 26, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 6, 8, 9, 6, 7, 8, 10, 11, 12),
    gsSPNTriangles_5b(10, 13, 11, 14, 15, 16, 14, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 21, 19, 22, 23, 24, 23, 25, 24, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_train1_1_t2_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_train1_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_train1_1_v[71], 22, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(12, 4, 5, 6, 6, 7, 4, 4, 8, 5),
    gsSPNTriangles_5b(5, 8, 9, 9, 7, 6, 6, 5, 9, 10, 11, 12),
    gsSPNTriangles_5b(13, 14, 15, 13, 16, 14, 12, 11, 17, 10, 18, 11),
    gsSPNTriangles_5b(19, 20, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_train1_1_t1_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_train1_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_train1_1_v[16], 32, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(4, 5, 1, 4, 6, 5, 4, 7, 6, 8, 9, 10),
    gsSPNTriangles_5b(8, 11, 9, 12, 13, 14, 12, 15, 13, 16, 17, 18),
    gsSPNTriangles_5b(18, 19, 16, 18, 20, 19, 19, 21, 16, 21, 22, 16),
    gsSPNTriangles_5b(18, 23, 20, 24, 17, 25, 26, 17, 27, 28, 29, 30),
    gsSPVertex(&obj_train1_1_v[47], 24, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 0, 2, 4, 5, 3),
    gsSPNTriangles_5b(4, 3, 2, 6, 7, 8, 9, 10, 6, 11, 12, 13),
    gsSPNTriangles_5b(13, 14, 11, 12, 15, 13, 13, 16, 14, 13, 17, 16),
    gsSPNTriangles_5b(13, 15, 17, 18, 19, 20, 21, 22, 23, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_train1_1_wheel2_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_train1_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_train1_1_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_train1_1_rod1_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_train1_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_train1_1_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_train1_1_rod2_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_train1_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_train1_1_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_train1_1_wheel1_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_train1_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_train1_1_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_train1_t3_tex_txt_tansui[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_train1_t3_tex_txt_tansui[] = {
#include "assets/obj_train1_t3_tex_txt_tansui.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_train_2_v[0x310 / sizeof(Vtx)];
#else
Vtx obj_train_2_v[] = {
#include "assets/obj_train_2_v.inc"
};
#endif

Gfx obj_train1_2_t2_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_train1_t3_tex_txt_tansui),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_train_2_v[29], 20, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 12, 14, 16, 17, 18, 17, 19, 18, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_train1_2_t1_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_train1_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(obj_train_2_v, 29, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(4, 2, 1, 5, 6, 7, 6, 8, 7, 9, 10, 11),
    gsSPNTriangles_5b(9, 12, 10, 13, 14, 15, 13, 16, 14, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 19, 21, 22, 23, 21, 24, 22, 25, 26, 27),
    gsSPNTriangles_5b(25, 27, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_train1_2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPDisplayList(obj_train1_2_t2_model),
    gsSPDisplayList(obj_train1_2_t1_model),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_train1_1_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 60036, 1500, 0 } },
                                              { obj_train1_1_t1_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 62036, 0 } },
                                              { obj_train1_1_wheel1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_train1_1_wheel2_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 3000, 0, 0 } },
                                              { obj_train1_1_rod1_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 633, 0, 0 } },
                                              { obj_train1_1_rod2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2133, 0, 0 } },
                                              { obj_train1_1_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_train1_1_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_train1_1 = { ARRAY_COUNT(cKF_je_r_obj_train1_1_tbl), 7, cKF_je_r_obj_train1_1_tbl };

u8 cKF_ckcb_r_obj_train1_1_tbl[] = { 56, 7, 0, 7, 7, 7, 7, 0, 0 };

s16 cKF_kn_obj_train1_1_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2 };

s16 cKF_c_obj_train1_1_tbl[] = { 0, -900, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_train1_1_tbl[] = { 1,  -5500, 0, 25, -5500, 0, 1, 1500,  0,    25, 1500, 0,    1,  0,    0, 25, 0,    0,
                                  1,  0,     0, 25, 0,     0, 1, 0,     0,    25, 0,    0,    1,  0,    0, 25, 0,    0,
                                  1,  0,     0, 25, -3600, 0, 1, 0,     0,    25, 0,    0,    1,  0,    0, 25, 0,    0,
                                  1,  0,     0, 25, 0,     0, 1, -2700, 4500, 25, 900,  4500, 1,  900,  0, 25, 900,  0,
                                  1,  0,     0, 25, 0,     0, 1, -2700, 4500, 25, 900,  4500, 1,  1800, 0, 25, 1800, 0,
                                  1,  0,     0, 25, 0,     0, 1, -75,   0,    13, 175,  0,    25, -75,  0, 1,  0,    0,
                                  25, 0,     0 };

cKF_Animation_R_c cKF_ba_r_obj_train1_1 = {
    cKF_ckcb_r_obj_train1_1_tbl, cKF_ds_obj_train1_1_tbl, cKF_kn_obj_train1_1_tbl, cKF_c_obj_train1_1_tbl, -1, 25
};
