#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_house_i_1_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_house_i_1_tex_txt[] = {
#include "assets/obj_s_house_i_1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house_i_window_tex_txt[0x100];
#else
u8 obj_s_house_i_window_tex_txt[] = {
#include "assets/obj_s_house_i_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house_i_2_tex_txt[0x800];
#else
u8 obj_s_house_i_2_tex_txt[] = {
#include "assets/obj_s_house_i_2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house_i_3_us_tex_txt[0x400];
#else
u8 obj_s_house_i_3_us_tex_txt[] = {
#include "assets/obj_s_house_i_3_us_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_house_i_v[0xA40 / sizeof(Vtx)];
#else
Vtx obj_s_house_i_v[] = {
#include "assets/obj_s_house_i_v.inc"
};
#endif

Gfx obj_s_house_i_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, obj_s_house_i_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_s_house_i_v[16], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house_i_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, obj_s_house_i_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house_i_v[4], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house_i_3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_s_house_i_3_us_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house_i_v[156], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house_i_2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_house_i_2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house_i_v[24], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house_i_1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 128, obj_s_house_i_1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house_i_v[36], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_house_i_v[68], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 22, 24, 23, 25, 23, 21, 25, 26, 27, 28),
    gsSPNTriangles_5b(27, 29, 28, 25, 27, 24, 27, 26, 24, 0, 0, 0),
    gsSPVertex(&obj_s_house_i_v[98], 32, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(4, 5, 3, 4, 6, 5, 7, 8, 9, 10, 11, 7),
    gsSPNTriangles_5b(12, 13, 14, 12, 14, 15, 16, 17, 18, 19, 16, 18),
    gsSPNTriangles_5b(19, 18, 20, 2, 19, 20, 2, 20, 0, 21, 22, 23),
    gsSPNTriangles_5b(9, 24, 21, 23, 25, 26, 26, 27, 28, 29, 30, 31),
    gsSPVertex(&obj_s_house_i_v[130], 26, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 3, 6, 7, 6, 8, 9, 7, 8, 10, 11, 12),
    gsSPNTriangles_5b(12, 13, 14, 15, 16, 17, 15, 18, 16, 18, 19, 16),
    gsSPNTriangles_5b(18, 20, 19, 20, 21, 19, 22, 23, 24, 23, 25, 24),
    gsSPEndDisplayList(),
};

Gfx obj_s_house_i_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 128, obj_s_house_i_1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_house_i_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_house_i_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
    { obj_s_house_i_1_model, 5, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_house_i_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
    { obj_s_house_i_2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_house_i_3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_house_i_light_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_house_i_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_s_house_i = { ARRAY_COUNT(cKF_je_r_obj_s_house_i_tbl), 6, cKF_je_r_obj_s_house_i_tbl };

u8 cKF_ckcb_r_obj_s_house_i_tbl[] = { 0, 0, 2, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_house_i_tbl[] = { 11 };

s16 cKF_c_obj_s_house_i_tbl[] = { 2000, 0, 0, -900, 0, 900, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_s_house_i_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                   1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                   -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_s_house_i = {
    cKF_ckcb_r_obj_s_house_i_tbl, cKF_ds_obj_s_house_i_tbl, cKF_kn_obj_s_house_i_tbl, cKF_c_obj_s_house_i_tbl, -1, 51
};

u8 cKF_ckcb_r_obj_s_house_i_out_tbl[] = { 0, 0, 2, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_house_i_out_tbl[] = { 13 };

s16 cKF_c_obj_s_house_i_out_tbl[] = { 2000, 0, 0, -900, 0, 900, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_s_house_i_out_tbl[] = { 1,    -900, 817,  2,   -873, 1200, 3,    -820,  1610, 5,    -705, 1886, 14,
                                       -149, 1163, 19,   -50, 193,  29,   -239, -1584, 41,   -907, -439, 42,   -915,
                                       336,  43,   -885, 225, 44,   -900, -225, 45,    -900, 0,    51,   -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_s_house_i_out = { cKF_ckcb_r_obj_s_house_i_out_tbl,
                                                 cKF_ds_obj_s_house_i_out_tbl,
                                                 cKF_kn_obj_s_house_i_out_tbl,
                                                 cKF_c_obj_s_house_i_out_tbl,
                                                 -1,
                                                 51 };
