#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_myhome_i_1_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_myhome_i_1_tex_txt[] = {
#include "assets/obj_s_myhome_i_1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_myhome_i_2_tex_txt[0x800];
#else
u8 obj_s_myhome_i_2_tex_txt[] = {
#include "assets/obj_s_myhome_i_2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_myhome_i_3_tex_txt[0x800];
#else
u8 obj_s_myhome_i_3_tex_txt[] = {
#include "assets/obj_s_myhome_i_3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_myhome_i_window_tex_txt[0x80];
#else
u8 obj_s_myhome_i_window_tex_txt[] = {
#include "assets/obj_s_myhome_i_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_myhome_i_v[0x880 / sizeof(Vtx)];
#else
Vtx obj_s_myhome_i_v[] = {
#include "assets/obj_s_myhome_i_v.inc"
};
#endif

Gfx obj_s_myhome_i_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_myhome_i_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_s_myhome_i_v[38], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome_i_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_myhome_i_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome_i_v[30], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome_i_3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_myhome_i_3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome_i_v[18], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome_i_2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_myhome_i_2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome_i_v[4], 14, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 9),
    gsSPNTriangles_5b(12, 9, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome_i_1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 128, obj_s_myhome_i_1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome_i_v[46], 32, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 1, 5, 7, 8, 9, 7, 10, 8, 11, 5, 6),
    gsSPNTriangles_5b(11, 8, 5, 12, 13, 14, 15, 12, 14, 15, 14, 16),
    gsSPNTriangles_5b(17, 15, 16, 17, 16, 18, 19, 20, 21, 22, 23, 19),
    gsSPNTriangles_5b(24, 25, 26, 27, 24, 26, 28, 29, 30, 29, 31, 30),
    gsSPVertex(&obj_s_myhome_i_v[78], 32, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(5, 6, 7, 8, 9, 5, 10, 11, 12, 12, 13, 8),
    gsSPNTriangles_5b(14, 15, 16, 14, 17, 15, 18, 19, 20, 18, 21, 19),
    gsSPNTriangles_5b(17, 22, 15, 17, 3, 22, 3, 4, 22, 23, 24, 25),
    gsSPNTriangles_5b(25, 26, 10, 27, 28, 29, 27, 29, 30, 31, 27, 30),
    gsSPVertex(&obj_s_myhome_i_v[110], 26, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 9, 11, 10, 11, 9, 12),
    gsSPNTriangles_5b(12, 13, 14, 13, 15, 14, 15, 13, 2, 13, 0, 2),
    gsSPNTriangles_5b(14, 11, 12, 16, 1, 3, 17, 16, 3, 18, 19, 20),
    gsSPNTriangles_5b(21, 18, 20, 22, 23, 24, 22, 24, 25, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome_i_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 128, obj_s_myhome_i_1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_myhome_i_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_myhome_i_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 3414, 60, 64122 } },
    { obj_s_myhome_i_1_model, 5, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome_i_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
    { obj_s_myhome_i_2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome_i_3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome_i_light_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome_i_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_s_myhome_i = { ARRAY_COUNT(cKF_je_r_obj_s_myhome_i_tbl), 6, cKF_je_r_obj_s_myhome_i_tbl };

u8 cKF_ckcb_r_obj_s_myhome_i_tbl[] = { 0, 0, 2, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_myhome_i_tbl[] = { 11 };

s16 cKF_c_obj_s_myhome_i_tbl[] = {
    3414, 60, -1414, -900, 0, 900, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

s16 cKF_ds_obj_s_myhome_i_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                    1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                    -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_s_myhome_i = { cKF_ckcb_r_obj_s_myhome_i_tbl,
                                              cKF_ds_obj_s_myhome_i_tbl,
                                              cKF_kn_obj_s_myhome_i_tbl,
                                              cKF_c_obj_s_myhome_i_tbl,
                                              -1,
                                              51 };

u8 cKF_ckcb_r_obj_s_myhome_i_out_tbl[] = { 0, 0, 2, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_myhome_i_out_tbl[] = { 13 };

s16 cKF_c_obj_s_myhome_i_out_tbl[] = { 3414, 60, -1414, -900, 0, 900, 0, 0, -900, 0, 0, 0,
                                       0,    0,  0,     0,    0, 0,   0, 0, 0,    0, 0 };

s16 cKF_ds_obj_s_myhome_i_out_tbl[] = { 1,    -900, 817,  2,   -873, 1200, 3,    -820,  1610, 5,    -705, 1886, 14,
                                        -149, 1163, 19,   -50, 193,  29,   -239, -1584, 41,   -907, -439, 42,   -915,
                                        336,  43,   -885, 225, 44,   -900, -225, 45,    -900, 0,    51,   -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_s_myhome_i_out = { cKF_ckcb_r_obj_s_myhome_i_out_tbl,
                                                  cKF_ds_obj_s_myhome_i_out_tbl,
                                                  cKF_kn_obj_s_myhome_i_out_tbl,
                                                  cKF_c_obj_s_myhome_i_out_tbl,
                                                  -1,
                                                  51 };
