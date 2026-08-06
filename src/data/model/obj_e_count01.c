#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_e_count_t1_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_e_count_t1_tex_txt[] = {
#include "assets/obj_e_count_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_count_t2_tex_txt[0x800];
#else
u8 obj_e_count_t2_tex_txt[] = {
#include "assets/obj_e_count_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_count_t3_tex_txt[0x800];
#else
u8 obj_e_count_t3_tex_txt[] = {
#include "assets/obj_e_count_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_count01_spot_tex_sgi_i4[0x80];
#else
u8 obj_e_count01_spot_tex_sgi_i4[] = {
#include "assets/obj_e_count01_spot_tex_sgi_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_count01_v[0x3B0 / sizeof(Vtx)];
#else
Vtx obj_e_count01_v[] = {
#include "assets/obj_e_count01_v.inc"
};
#endif

Gfx obj_e_count_spot_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, TEXEL1, 0, 0, 0, 0, COMBINED, COMBINED, 0, PRIMITIVE, 0),
    gsDPSetPrimColor(0, 255, 255, 255, 180, 120),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_e_count01_spot_tex_sgi_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 1, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_e_count01_spot_tex_sgi_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_REPEAT, 1, 0),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_count01_v[13], 6, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_count_lamp_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_2_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_count_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_count01_v[47], 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 2, 5),
    gsSPNTriangles_5b(4, 0, 2, 6, 7, 8, 7, 9, 8, 7, 10, 9),
    gsSPNTriangles_5b(7, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_count_front_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL0, 0, 0, 0, TEXEL0, SHADE, ENVIRONMENT, PRIMITIVE, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_2_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_count_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_count01_v[35], 12, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(4, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_count_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 6, 7, 8, 7, 9, 8, 6, 8, 10),
    gsSPNTriangles_5b(8, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_count_baloon_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL0, 0, 0, 0, TEXEL0, SHADE, ENVIRONMENT, PRIMITIVE, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_2_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_count_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_count01_v[19], 16, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_count_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_count_back_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_2_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_count_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_count01_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_count_new_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, COMBINED, ENVIRONMENT, 0, 0,
                       0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_2_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_count_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_count01_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_count_down_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_2_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_count_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_count01_v[8], 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_e_count01_tbl[] = { { obj_e_count_back_model, 5, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                               { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 6500, 61536 } },
                                               { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                               { obj_e_count_down_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 3000, 0, 0 } },
                                               { obj_e_count_new_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                               { obj_e_count_baloon_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                               { obj_e_count_front_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                               { obj_e_count_lamp_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                               { obj_e_count_spot_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_e_count01 = { ARRAY_COUNT(cKF_je_r_obj_e_count01_tbl), 7, cKF_je_r_obj_e_count01_tbl };

u8 cKF_ckcb_r_obj_e_count01_tbl[] = { 0, 0, 1, 1, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_e_count01_tbl[] = { 15, 12 };

s16 cKF_c_obj_e_count01_tbl[] = { 0, 0, 0, 0, 0, 0, 900, 1050, 900, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0,   0,    0,   0, 0, 0, 0, 0 };

s16 cKF_ds_obj_e_count01_tbl[] = { 1,  -1800, -168, 2,  -1806, -321,  17, -2354, -321,  20, -2360, 0,
                                   36, -2360, 0,    39, -2337, 674,   48, -1866, 1973,  49, -1800, 1459,
                                   50, -1768, 261,  52, -1813, -711,  53, -1830, -182,  54, -1825, 225,
                                   56, -1805, 225,  59, -1800, 0,     61, -1800, 0,     1,  0,     0,
                                   15, 0,     0,    17, 21,    1217,  27, 1637,  6184,  28, 1840,  5204,
                                   29, 1984,  2922, 31, 2019,  -1096, 33, 1889,  -2028, 34, 1827,  -1335,
                                   35, 1800,  -398, 36, 1800,  0,     61, 1800,  0 };

cKF_Animation_R_c cKF_ba_r_obj_e_count01 = {
    cKF_ckcb_r_obj_e_count01_tbl, cKF_ds_obj_e_count01_tbl, cKF_kn_obj_e_count01_tbl, cKF_c_obj_e_count01_tbl, -1, 61
};
