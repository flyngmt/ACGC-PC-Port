#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_house1_t1_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_house1_t1_tex_txt[] = {
#include "assets/obj_s_house1_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house1_window_txt[0x80];
#else
u8 obj_s_house1_window_txt[] = {
#include "assets/obj_s_house1_window_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house1_t3_tex_txt[0x800];
#else
u8 obj_s_house1_t3_tex_txt[] = {
#include "assets/obj_s_house1_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house1_t2_tex_txt[0x800];
#else
u8 obj_s_house1_t2_tex_txt[] = {
#include "assets/obj_s_house1_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house1_t4_tex_txt[0x200];
#else
u8 obj_s_house1_t4_tex_txt[] = {
#include "assets/obj_s_house1_t4_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_house1_v[0x730 / sizeof(Vtx)];
#else
Vtx obj_s_house1_v[] = {
#include "assets/obj_s_house1_v.inc"
};
#endif

Gfx obj_s_house1_windowL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_house1_window_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_s_house1_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house1_windowR_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_house1_window_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_s_house1_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house1_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house1_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house1_v[12], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house1_t4_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_s_house1_t4_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house1_v[111], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house1_t3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house1_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house1_v[28], 11, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 5, 6, 4, 7, 8, 9, 7, 9, 10),
    gsSPEndDisplayList(),
};

Gfx obj_s_house1_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house1_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house1_v[39], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 6, 7, 8, 6, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 14, 16, 17, 15, 18, 19),
    gsSPNTriangles_5b(15, 19, 16, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 28, 29, 30, 28, 30, 31, 0, 0, 0),
    gsSPVertex(&obj_s_house1_v[71], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house1_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house1_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house1_v[75], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 22, 24, 25, 26, 24, 27, 25, 28, 29, 30),
    gsSPNTriangles_5b(29, 31, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_house1_v[107], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house1_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house1_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_house1_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_house1_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_s_house1_light_model, 6, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house1_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_s_house1_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house1_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house1_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house1_t4_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_s_house1 = { ARRAY_COUNT(cKF_je_r_obj_s_house1_tbl), 7, cKF_je_r_obj_s_house1_tbl };

u8 cKF_ckcb_r_obj_s_house1_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_house1_tbl[] = { 11 };

s16 cKF_c_obj_s_house1_tbl[] = { 2000, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_s_house1_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                  1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                  -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_s_house1 = {
    cKF_ckcb_r_obj_s_house1_tbl, cKF_ds_obj_s_house1_tbl, cKF_kn_obj_s_house1_tbl, cKF_c_obj_s_house1_tbl, -1, 51
};

u8 cKF_ckcb_r_obj_s_house1_out_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_house1_out_tbl[] = { 13 };

s16 cKF_c_obj_s_house1_out_tbl[] = {
    2000, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

s16 cKF_ds_obj_s_house1_out_tbl[] = { 1,    -900, 817,  2,   -873, 1200, 3,    -820,  1610, 5,    -705, 1886, 14,
                                      -149, 1163, 19,   -50, 193,  29,   -239, -1584, 41,   -907, -439, 42,   -915,
                                      336,  43,   -885, 225, 44,   -900, -225, 45,    -900, 0,    51,   -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_s_house1_out = { cKF_ckcb_r_obj_s_house1_out_tbl,
                                                cKF_ds_obj_s_house1_out_tbl,
                                                cKF_kn_obj_s_house1_out_tbl,
                                                cKF_c_obj_s_house1_out_tbl,
                                                -1,
                                                51 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_house2_t3_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_house2_t3_tex_txt[] = {
#include "assets/obj_s_house2_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house2_window_tex_txt[0x80];
#else
u8 obj_s_house2_window_tex_txt[] = {
#include "assets/obj_s_house2_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house2_t2_tex_txt[0x800];
#else
u8 obj_s_house2_t2_tex_txt[] = {
#include "assets/obj_s_house2_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house2_t1_tex_txt[0x800];
#else
u8 obj_s_house2_t1_tex_txt[] = {
#include "assets/obj_s_house2_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house2_name_tex_txt[0x200];
#else
u8 obj_s_house2_name_tex_txt[] = {
#include "assets/obj_s_house2_name_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_house2_v[0x6D0 / sizeof(Vtx)];
#else
Vtx obj_s_house2_v[] = {
#include "assets/obj_s_house2_v.inc"
};
#endif

Gfx obj_s_house2_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_house2_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&obj_s_house2_v[4], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house2_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house2_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house2_v[29], 15, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 11, 12, 13, 11, 13, 14),
    gsSPEndDisplayList(),
};

Gfx obj_s_house2_t3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house2_v[61], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_house2_v[93], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house2_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house2_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house2_v[12], 17, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 7, 13),
    gsSPNTriangles_5b(12, 13, 14, 7, 6, 15, 7, 15, 13, 7, 12, 16),
    gsSPNTriangles_5b(7, 16, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house2_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house2_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 1020, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house2_v[44], 17, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 0, 2, 3, 3, 4, 0),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 6, 9, 10, 6, 10, 7),
    gsSPNTriangles_5b(9, 11, 12, 9, 12, 10, 13, 14, 15, 13, 15, 16),
    gsSPEndDisplayList(),
};

Gfx obj_s_house2_name_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_s_house2_name_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house2_v[105], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house2_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_house2_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_house2_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_s_house2_light_model, 6, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house2_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_s_house2_name_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house2_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house2_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house2_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_s_house2 = { ARRAY_COUNT(cKF_je_r_obj_s_house2_tbl), 7, cKF_je_r_obj_s_house2_tbl };

u8 cKF_ckcb_r_obj_s_house2_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_house2_tbl[] = { 11 };

s16 cKF_c_obj_s_house2_tbl[] = { 2000, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_s_house2_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                  1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                  -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_s_house2 = {
    cKF_ckcb_r_obj_s_house2_tbl, cKF_ds_obj_s_house2_tbl, cKF_kn_obj_s_house2_tbl, cKF_c_obj_s_house2_tbl, -1, 51
};

u8 cKF_ckcb_r_obj_s_house2_out_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_house2_out_tbl[] = { 13 };

s16 cKF_c_obj_s_house2_out_tbl[] = {
    2000, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

s16 cKF_ds_obj_s_house2_out_tbl[] = { 1,    -900, 817,  2,   -873, 1200, 3,    -820,  1610, 5,    -705, 1886, 14,
                                      -149, 1163, 19,   -50, 193,  29,   -239, -1584, 41,   -907, -439, 42,   -915,
                                      336,  43,   -885, 225, 44,   -900, -225, 45,    -900, 0,    51,   -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_s_house2_out = { cKF_ckcb_r_obj_s_house2_out_tbl,
                                                cKF_ds_obj_s_house2_out_tbl,
                                                cKF_kn_obj_s_house2_out_tbl,
                                                cKF_c_obj_s_house2_out_tbl,
                                                -1,
                                                51 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_house3_t3_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_house3_t3_tex_txt[] = {
#include "assets/obj_s_house3_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house3_t1_tex_txt[0x800];
#else
u8 obj_s_house3_t1_tex_txt[] = {
#include "assets/obj_s_house3_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house3_t2_tex_txt[0x800];
#else
u8 obj_s_house3_t2_tex_txt[] = {
#include "assets/obj_s_house3_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house3_window_tex_txt[0x80];
#else
u8 obj_s_house3_window_tex_txt[] = {
#include "assets/obj_s_house3_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house3_name_tex_txt[0x200];
#else
u8 obj_s_house3_name_tex_txt[] = {
#include "assets/obj_s_house3_name_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_house3_v[0x640 / sizeof(Vtx)];
#else
Vtx obj_s_house3_v[] = {
#include "assets/obj_s_house3_v.inc"
};
#endif

Gfx obj_s_house3_windowL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_house3_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&obj_s_house3_v[40], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house3_windowR_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_house3_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&obj_s_house3_v[44], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house3_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house3_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house3_v[25], 15, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 11, 12, 13, 11, 13, 14),
    gsSPEndDisplayList(),
};

Gfx obj_s_house3_t3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house3_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house3_v[48], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_house3_v[80], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house3_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house3_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house3_v[11], 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 6, 7, 8, 6, 8, 9, 9, 8, 5),
    gsSPNTriangles_5b(9, 5, 4, 6, 10, 11, 6, 11, 7, 0, 12, 13),
    gsSPNTriangles_5b(0, 13, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house3_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house3_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house3_v[4], 7, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(2, 3, 6, 2, 6, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house3_name_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_s_house3_name_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house3_v[96], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house3_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house3_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_house3_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_house3_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_s_house3_light_model, 6, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house3_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_s_house3_name_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house3_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house3_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house3_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 2000 } },
                                              { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_s_house3 = { ARRAY_COUNT(cKF_je_r_obj_s_house3_tbl), 7, cKF_je_r_obj_s_house3_tbl };

u8 cKF_ckcb_r_obj_s_house3_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_house3_tbl[] = { 11 };

s16 cKF_c_obj_s_house3_tbl[] = { 2000, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0 };

s16 cKF_ds_obj_s_house3_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                  1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                  -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_s_house3 = {
    cKF_ckcb_r_obj_s_house3_tbl, cKF_ds_obj_s_house3_tbl, cKF_kn_obj_s_house3_tbl, cKF_c_obj_s_house3_tbl, -1, 51
};

u8 cKF_ckcb_r_obj_s_house3_out_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_house3_out_tbl[] = { 13 };

s16 cKF_c_obj_s_house3_out_tbl[] = { 2000, 0, 0, 0, -900, 0, 0, 0, 0,   0, 0, 0, 0,
                                     0,    0, 0, 0, 0,    0, 0, 0, 900, 0, 0, 0, 0 };

s16 cKF_ds_obj_s_house3_out_tbl[] = { 1,    -900, 817,  2,   -873, 1200, 3,    -820,  1610, 5,    -705, 1886, 14,
                                      -149, 1163, 19,   -50, 193,  29,   -239, -1584, 41,   -907, -439, 42,   -915,
                                      336,  43,   -885, 225, 44,   -900, -225, 45,    -900, 0,    51,   -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_s_house3_out = { cKF_ckcb_r_obj_s_house3_out_tbl,
                                                cKF_ds_obj_s_house3_out_tbl,
                                                cKF_kn_obj_s_house3_out_tbl,
                                                cKF_c_obj_s_house3_out_tbl,
                                                -1,
                                                51 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_house4_t3_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_house4_t3_tex_txt[] = {
#include "assets/obj_s_house4_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house4_t1_tex_txt[0x800];
#else
u8 obj_s_house4_t1_tex_txt[] = {
#include "assets/obj_s_house4_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house4_t2_tex_txt[0x800];
#else
u8 obj_s_house4_t2_tex_txt[] = {
#include "assets/obj_s_house4_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house4_window_tex_txt[0x80];
#else
u8 obj_s_house4_window_tex_txt[] = {
#include "assets/obj_s_house4_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house4_name_tex_txt[0x200];
#else
u8 obj_s_house4_name_tex_txt[] = {
#include "assets/obj_s_house4_name_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_house4_v[0x590 / sizeof(Vtx)];
#else
Vtx obj_s_house4_v[] = {
#include "assets/obj_s_house4_v.inc"
};
#endif

Gfx obj_s_house4_windowL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_house4_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&obj_s_house4_v[77], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house4_windowR_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_house4_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&obj_s_house4_v[81], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house4_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house4_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house4_v[63], 14, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 7, 12, 13),
    gsSPNTriangles_5b(7, 13, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house4_t3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house4_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 508),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house4_v[29], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 7, 25, 24, 25, 26, 12, 27, 28),
    gsSPNTriangles_5b(12, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_house4_v[59], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house4_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house4_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house4_v[11], 18, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 8, 15, 2, 1, 15, 1, 16, 17, 10, 9),
    gsSPNTriangles_5b(17, 9, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house4_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house4_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house4_v[4], 7, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(6, 0, 3, 6, 3, 4, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house4_name_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_s_house4_name_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house4_v[85], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house4_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house4_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_house4_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_house4_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_s_house4_light_model, 6, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house4_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_s_house4_name_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house4_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house4_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house4_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_s_house4 = { ARRAY_COUNT(cKF_je_r_obj_s_house4_tbl), 7, cKF_je_r_obj_s_house4_tbl };

u8 cKF_ckcb_r_obj_s_house4_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_house4_tbl[] = { 11 };

s16 cKF_c_obj_s_house4_tbl[] = { 2000, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_s_house4_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                  1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                  -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_s_house4 = {
    cKF_ckcb_r_obj_s_house4_tbl, cKF_ds_obj_s_house4_tbl, cKF_kn_obj_s_house4_tbl, cKF_c_obj_s_house4_tbl, -1, 51
};

u8 cKF_ckcb_r_obj_s_house4_out_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_house4_out_tbl[] = { 13 };

s16 cKF_c_obj_s_house4_out_tbl[] = {
    2000, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

s16 cKF_ds_obj_s_house4_out_tbl[] = { 1,    -900, 817,  2,   -873, 1200, 3,    -820,  1610, 5,    -705, 1886, 14,
                                      -149, 1163, 19,   -50, 193,  29,   -239, -1584, 41,   -907, -439, 42,   -915,
                                      336,  43,   -885, 225, 44,   -900, -225, 45,    -900, 0,    51,   -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_s_house4_out = { cKF_ckcb_r_obj_s_house4_out_tbl,
                                                cKF_ds_obj_s_house4_out_tbl,
                                                cKF_kn_obj_s_house4_out_tbl,
                                                cKF_c_obj_s_house4_out_tbl,
                                                -1,
                                                51 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_house5_t3_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_house5_t3_tex_txt[] = {
#include "assets/obj_s_house5_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house5_t1_tex_txt[0x800];
#else
u8 obj_s_house5_t1_tex_txt[] = {
#include "assets/obj_s_house5_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house5_window_tex_txt[0x80];
#else
u8 obj_s_house5_window_tex_txt[] = {
#include "assets/obj_s_house5_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house5_t2_tex_txt[0x800];
#else
u8 obj_s_house5_t2_tex_txt[] = {
#include "assets/obj_s_house5_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_house5_name_tex_txt[0x200];
#else
u8 obj_s_house5_name_tex_txt[] = {
#include "assets/obj_s_house5_name_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_house5_v[0x830 / sizeof(Vtx)];
#else
Vtx obj_s_house5_v[] = {
#include "assets/obj_s_house5_v.inc"
};
#endif

Gfx obj_s_house5_windowL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_house5_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&obj_s_house5_v[20], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house5_windowR_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_house5_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&obj_s_house5_v[24], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house5_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house5_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house5_v[4], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house5_t3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house5_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 508),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house5_v[28], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house5_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house5_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house5_v[72], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 11, 12, 13, 11, 14, 12),
    gsSPNTriangles_5b(15, 16, 17, 15, 18, 16, 19, 20, 21, 22, 23, 24),
    gsSPNTriangles_5b(22, 25, 23, 25, 26, 23, 27, 28, 29, 27, 30, 28),
    gsSPNTriangles_5b(31, 28, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_house5_v[104], 23, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 1, 4, 1, 0, 4),
    gsSPNTriangles_5b(5, 6, 7, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 18, 15, 17, 19, 20, 21, 19, 22, 20),
    gsSPEndDisplayList(),
};

Gfx obj_s_house5_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house5_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house5_v[60], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house5_name_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_s_house5_name_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_house5_v[127], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_house5_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_house5_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_house5_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_house5_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_s_house5_light_model, 6, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house5_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_s_house5_name_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house5_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house5_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_house5_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_s_house5 = { ARRAY_COUNT(cKF_je_r_obj_s_house5_tbl), 7, cKF_je_r_obj_s_house5_tbl };

u8 cKF_ckcb_r_obj_s_house5_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_house5_tbl[] = { 11 };

s16 cKF_c_obj_s_house5_tbl[] = { 2000, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_s_house5_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                  1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                  -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_s_house5 = {
    cKF_ckcb_r_obj_s_house5_tbl, cKF_ds_obj_s_house5_tbl, cKF_kn_obj_s_house5_tbl, cKF_c_obj_s_house5_tbl, -1, 51
};

u8 cKF_ckcb_r_obj_s_house5_out_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_house5_out_tbl[] = { 13 };

s16 cKF_c_obj_s_house5_out_tbl[] = {
    2000, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

s16 cKF_ds_obj_s_house5_out_tbl[] = { 1,    -900, 817,  2,   -873, 1200, 3,    -820,  1610, 5,    -705, 1886, 14,
                                      -149, 1163, 19,   -50, 193,  29,   -239, -1584, 41,   -907, -439, 42,   -915,
                                      336,  43,   -885, 225, 44,   -900, -225, 45,    -900, 0,    51,   -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_s_house5_out = { cKF_ckcb_r_obj_s_house5_out_tbl,
                                                cKF_ds_obj_s_house5_out_tbl,
                                                cKF_kn_obj_s_house5_out_tbl,
                                                cKF_c_obj_s_house5_out_tbl,
                                                -1,
                                                51 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_w_house1_t1_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_w_house1_t1_tex_txt[] = {
#include "assets/obj_w_house1_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house1_window_txt[0x80];
#else
u8 obj_w_house1_window_txt[] = {
#include "assets/obj_w_house1_window_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house1_t3_tex_txt[0x800];
#else
u8 obj_w_house1_t3_tex_txt[] = {
#include "assets/obj_w_house1_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house1_t2_tex_txt[0x800];
#else
u8 obj_w_house1_t2_tex_txt[] = {
#include "assets/obj_w_house1_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house1_t4_tex_txt[0x200];
#else
u8 obj_w_house1_t4_tex_txt[] = {
#include "assets/obj_w_house1_t4_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_house1_v[0x730 / sizeof(Vtx)];
#else
Vtx obj_w_house1_v[] = {
#include "assets/obj_w_house1_v.inc"
};
#endif

Gfx obj_w_house1_windowL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_house1_window_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_w_house1_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house1_windowR_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_house1_window_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_w_house1_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house1_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house1_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house1_v[12], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house1_t4_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_w_house1_t4_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house1_v[111], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house1_t3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house1_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house1_v[28], 11, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 5, 6, 4, 7, 8, 9, 7, 9, 10),
    gsSPEndDisplayList(),
};

Gfx obj_w_house1_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house1_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house1_v[75], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 6, 7, 8, 6, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 14, 16, 17, 15, 18, 19),
    gsSPNTriangles_5b(15, 19, 16, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 28, 29, 30, 28, 30, 31, 0, 0, 0),
    gsSPVertex(&obj_w_house1_v[107], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house1_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house1_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house1_v[39], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 22, 24, 25, 26, 24, 27, 25, 28, 29, 30),
    gsSPNTriangles_5b(29, 31, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_house1_v[71], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house1_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house1_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_house1_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_house1_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_w_house1_light_model, 6, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house1_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_w_house1_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house1_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house1_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house1_t4_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_w_house1 = { ARRAY_COUNT(cKF_je_r_obj_w_house1_tbl), 7, cKF_je_r_obj_w_house1_tbl };

u8 cKF_ckcb_r_obj_w_house1_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_house1_tbl[] = { 11 };

s16 cKF_c_obj_w_house1_tbl[] = { 2000, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_w_house1_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                  1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                  -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_w_house1 = {
    cKF_ckcb_r_obj_w_house1_tbl, cKF_ds_obj_w_house1_tbl, cKF_kn_obj_w_house1_tbl, cKF_c_obj_w_house1_tbl, -1, 51
};

u8 cKF_ckcb_r_obj_w_house1_out_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_house1_out_tbl[] = { 13 };

s16 cKF_c_obj_w_house1_out_tbl[] = {
    2000, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

s16 cKF_ds_obj_w_house1_out_tbl[] = { 1,    -900, 817,  2,   -873, 1200, 3,    -820,  1610, 5,    -705, 1886, 14,
                                      -149, 1163, 19,   -50, 193,  29,   -239, -1584, 41,   -907, -439, 42,   -915,
                                      336,  43,   -885, 225, 44,   -900, -225, 45,    -900, 0,    51,   -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_w_house1_out = { cKF_ckcb_r_obj_w_house1_out_tbl,
                                                cKF_ds_obj_w_house1_out_tbl,
                                                cKF_kn_obj_w_house1_out_tbl,
                                                cKF_c_obj_w_house1_out_tbl,
                                                -1,
                                                51 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_w_house2_t3_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_w_house2_t3_tex_txt[] = {
#include "assets/obj_w_house2_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house2_window_tex_txt[0x80];
#else
u8 obj_w_house2_window_tex_txt[] = {
#include "assets/obj_w_house2_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house2_t2_tex_txt[0x800];
#else
u8 obj_w_house2_t2_tex_txt[] = {
#include "assets/obj_w_house2_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house2_t1_tex_txt[0x800];
#else
u8 obj_w_house2_t1_tex_txt[] = {
#include "assets/obj_w_house2_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house2_name_tex_txt[0x200];
#else
u8 obj_w_house2_name_tex_txt[] = {
#include "assets/obj_w_house2_name_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_house2_v[0x6D0 / sizeof(Vtx)];
#else
Vtx obj_w_house2_v[] = {
#include "assets/obj_w_house2_v.inc"
};
#endif

Gfx obj_w_house2_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_house2_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house2_v[4], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house2_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house2_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house2_v[29], 15, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 11, 12, 13, 11, 13, 14),
    gsSPEndDisplayList(),
};

Gfx obj_w_house2_t3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house2_v[61], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_house2_v[93], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house2_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house2_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house2_v[12], 17, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 7, 13),
    gsSPNTriangles_5b(12, 13, 14, 7, 6, 15, 7, 15, 13, 7, 12, 16),
    gsSPNTriangles_5b(7, 16, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house2_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house2_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 1020, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house2_v[44], 17, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 0, 2, 3, 3, 4, 0),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 6, 9, 10, 6, 10, 7),
    gsSPNTriangles_5b(9, 11, 12, 9, 12, 10, 13, 14, 15, 13, 15, 16),
    gsSPEndDisplayList(),
};

Gfx obj_w_house2_name_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_w_house2_name_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house2_v[105], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house2_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_house2_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_house2_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_w_house2_light_model, 6, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house2_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_w_house2_name_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house2_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house2_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house2_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_w_house2 = { ARRAY_COUNT(cKF_je_r_obj_w_house2_tbl), 7, cKF_je_r_obj_w_house2_tbl };

u8 cKF_ckcb_r_obj_w_house2_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_house2_tbl[] = { 11 };

s16 cKF_c_obj_w_house2_tbl[] = { 2000, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_w_house2_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                  1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                  -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_w_house2 = {
    cKF_ckcb_r_obj_w_house2_tbl, cKF_ds_obj_w_house2_tbl, cKF_kn_obj_w_house2_tbl, cKF_c_obj_w_house2_tbl, -1, 51
};

u8 cKF_ckcb_r_obj_w_house2_out_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_house2_out_tbl[] = { 13 };

s16 cKF_c_obj_w_house2_out_tbl[] = {
    2000, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

s16 cKF_ds_obj_w_house2_out_tbl[] = { 1,    -900, 817,  2,   -873, 1200, 3,    -820,  1610, 5,    -705, 1886, 14,
                                      -149, 1163, 19,   -50, 193,  29,   -239, -1584, 41,   -907, -439, 42,   -915,
                                      336,  43,   -885, 225, 44,   -900, -225, 45,    -900, 0,    51,   -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_w_house2_out = { cKF_ckcb_r_obj_w_house2_out_tbl,
                                                cKF_ds_obj_w_house2_out_tbl,
                                                cKF_kn_obj_w_house2_out_tbl,
                                                cKF_c_obj_w_house2_out_tbl,
                                                -1,
                                                51 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 obj_w_house3_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 obj_w_house3_a_pal[] = {
#include "assets/obj_s_house1/obj_w_house3_a_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house3_t3_tex_txt[0x800];
#else
u8 obj_w_house3_t3_tex_txt[] = {
#include "assets/obj_w_house3_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house3_t1_tex_txt[0x800];
#else
u8 obj_w_house3_t1_tex_txt[] = {
#include "assets/obj_w_house3_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house3_t2_tex_txt[0x800];
#else
u8 obj_w_house3_t2_tex_txt[] = {
#include "assets/obj_w_house3_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house3_window_tex_txt[0x80];
#else
u8 obj_w_house3_window_tex_txt[] = {
#include "assets/obj_w_house3_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house3_name_tex_txt[0x200];
#else
u8 obj_w_house3_name_tex_txt[] = {
#include "assets/obj_w_house3_name_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_house3_v[0x640 / sizeof(Vtx)];
#else
Vtx obj_w_house3_v[] = {
#include "assets/obj_w_house3_v.inc"
};
#endif

Gfx obj_w_house3_windowL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_house3_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&obj_w_house3_v[40], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house3_windowR_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_house3_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&obj_w_house3_v[44], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house3_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house3_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house3_v[25], 15, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 11, 12, 13, 11, 13, 14),
    gsSPEndDisplayList(),
};

Gfx obj_w_house3_t3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house3_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house3_v[48], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_house3_v[80], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house3_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house3_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house3_v[11], 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 6, 7, 8, 6, 8, 9, 9, 8, 5),
    gsSPNTriangles_5b(9, 5, 4, 6, 10, 11, 6, 11, 7, 0, 12, 13),
    gsSPNTriangles_5b(0, 13, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house3_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house3_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house3_v[4], 7, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(2, 3, 6, 2, 6, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house3_name_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_house3_a_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_w_house3_name_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house3_v[96], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house3_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house3_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_house3_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_house3_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_w_house3_name_model, 6, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house3_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_w_house3_light_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house3_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house3_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house3_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 2000 } },
                                              { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_w_house3 = { ARRAY_COUNT(cKF_je_r_obj_w_house3_tbl), 7, cKF_je_r_obj_w_house3_tbl };

u8 cKF_ckcb_r_obj_w_house3_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_house3_tbl[] = { 11 };

s16 cKF_c_obj_w_house3_tbl[] = { 2000, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0 };

s16 cKF_ds_obj_w_house3_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                  1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                  -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_w_house3 = {
    cKF_ckcb_r_obj_w_house3_tbl, cKF_ds_obj_w_house3_tbl, cKF_kn_obj_w_house3_tbl, cKF_c_obj_w_house3_tbl, -1, 51
};

u8 cKF_ckcb_r_obj_w_house3_out_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_house3_out_tbl[] = { 13 };

s16 cKF_c_obj_w_house3_out_tbl[] = { 2000, 0, 0, 0, -900, 0, 0, 0, 0,   0, 0, 0, 0,
                                     0,    0, 0, 0, 0,    0, 0, 0, 900, 0, 0, 0, 0 };

s16 cKF_ds_obj_w_house3_out_tbl[] = { 1,    -900, 817,  2,   -873, 1200, 3,    -820,  1610, 5,    -705, 1886, 14,
                                      -149, 1163, 19,   -50, 193,  29,   -239, -1584, 41,   -907, -439, 42,   -915,
                                      336,  43,   -885, 225, 44,   -900, -225, 45,    -900, 0,    51,   -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_w_house3_out = { cKF_ckcb_r_obj_w_house3_out_tbl,
                                                cKF_ds_obj_w_house3_out_tbl,
                                                cKF_kn_obj_w_house3_out_tbl,
                                                cKF_c_obj_w_house3_out_tbl,
                                                -1,
                                                51 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_w_house4_t3_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_w_house4_t3_tex_txt[] = {
#include "assets/obj_w_house4_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house4_t1_tex_txt[0x800];
#else
u8 obj_w_house4_t1_tex_txt[] = {
#include "assets/obj_w_house4_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house4_t2_tex_txt[0x800];
#else
u8 obj_w_house4_t2_tex_txt[] = {
#include "assets/obj_w_house4_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house4_window_tex_txt[0x80];
#else
u8 obj_w_house4_window_tex_txt[] = {
#include "assets/obj_w_house4_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house4_name_tex_txt[0x200];
#else
u8 obj_w_house4_name_tex_txt[] = {
#include "assets/obj_w_house4_name_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_house4_v[0x5D0 / sizeof(Vtx)];
#else
Vtx obj_w_house4_v[] = {
#include "assets/obj_w_house4_v.inc"
};
#endif

Gfx obj_w_house4_windowL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_house4_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&obj_w_house4_v[81], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house4_windowR_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_house4_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&obj_w_house4_v[85], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house4_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house4_v[67], 14, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 7, 12, 13),
    gsSPNTriangles_5b(7, 13, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house4_t3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house4_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 508),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house4_v[33], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 7, 25, 24, 25, 26, 12, 27, 28),
    gsSPNTriangles_5b(12, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_house4_v[63], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house4_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house4_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house4_v[11], 22, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 10, 9),
    gsSPNTriangles_5b(20, 9, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house4_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house4_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house4_v[4], 7, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(6, 0, 3, 6, 3, 4, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house4_name_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_w_house4_name_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house4_v[89], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house4_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house4_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_house4_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_house4_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_w_house4_light_model, 6, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house4_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_w_house4_name_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house4_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house4_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house4_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_w_house4 = { ARRAY_COUNT(cKF_je_r_obj_w_house4_tbl), 7, cKF_je_r_obj_w_house4_tbl };

u8 cKF_ckcb_r_obj_w_house4_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_house4_tbl[] = { 11 };

s16 cKF_c_obj_w_house4_tbl[] = { 2000, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_w_house4_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                  1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                  -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_w_house4 = {
    cKF_ckcb_r_obj_w_house4_tbl, cKF_ds_obj_w_house4_tbl, cKF_kn_obj_w_house4_tbl, cKF_c_obj_w_house4_tbl, -1, 51
};

u8 cKF_ckcb_r_obj_w_house4_out_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_house4_out_tbl[] = { 13 };

s16 cKF_c_obj_w_house4_out_tbl[] = {
    2000, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

s16 cKF_ds_obj_w_house4_out_tbl[] = { 1,    -900, 817,  2,   -873, 1200, 3,    -820,  1610, 5,    -705, 1886, 14,
                                      -149, 1163, 19,   -50, 193,  29,   -239, -1584, 41,   -907, -439, 42,   -915,
                                      336,  43,   -885, 225, 44,   -900, -225, 45,    -900, 0,    51,   -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_w_house4_out = { cKF_ckcb_r_obj_w_house4_out_tbl,
                                                cKF_ds_obj_w_house4_out_tbl,
                                                cKF_kn_obj_w_house4_out_tbl,
                                                cKF_c_obj_w_house4_out_tbl,
                                                -1,
                                                51 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_w_house5_t3_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_w_house5_t3_tex_txt[] = {
#include "assets/obj_w_house5_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house5_t1_tex_txt[0x800];
#else
u8 obj_w_house5_t1_tex_txt[] = {
#include "assets/obj_w_house5_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house5_window_tex_txt[0x80];
#else
u8 obj_w_house5_window_tex_txt[] = {
#include "assets/obj_w_house5_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house5_t2_tex_txt[0x800];
#else
u8 obj_w_house5_t2_tex_txt[] = {
#include "assets/obj_w_house5_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_house5_name_tex_txt[0x200];
#else
u8 obj_w_house5_name_tex_txt[] = {
#include "assets/obj_w_house5_name_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_house5_v[0x830 / sizeof(Vtx)];
#else
Vtx obj_w_house5_v[] = {
#include "assets/obj_w_house5_v.inc"
};
#endif

Gfx obj_w_house5_windowL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_house5_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&obj_w_house5_v[20], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house5_windowR_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_house5_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&obj_w_house5_v[24], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house5_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house5_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house5_v[4], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house5_t3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house5_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 508),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house5_v[28], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house5_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house5_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house5_v[60], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 4, 6, 5),
    gsSPNTriangles_5b(7, 8, 9, 8, 10, 9, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(14, 17, 15, 18, 19, 20, 18, 21, 19, 22, 23, 24),
    gsSPNTriangles_5b(25, 26, 27, 25, 28, 26, 28, 29, 26, 30, 1, 31),
    gsSPNTriangles_5b(30, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_house5_v[92], 23, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 1, 4, 1, 0, 4),
    gsSPNTriangles_5b(5, 6, 7, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 18, 15, 17, 19, 20, 21, 20, 22, 21),
    gsSPEndDisplayList(),
};

Gfx obj_w_house5_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house5_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house5_v[115], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house5_name_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_w_house5_name_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_house5_v[127], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_house5_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_house5_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_house5_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_house5_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_w_house5_light_model, 6, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house5_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_w_house5_name_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house5_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house5_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_house5_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_w_house5 = { ARRAY_COUNT(cKF_je_r_obj_w_house5_tbl), 7, cKF_je_r_obj_w_house5_tbl };

u8 cKF_ckcb_r_obj_w_house5_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_house5_tbl[] = { 11 };

s16 cKF_c_obj_w_house5_tbl[] = { 2000, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_w_house5_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                  1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                  -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_w_house5 = {
    cKF_ckcb_r_obj_w_house5_tbl, cKF_ds_obj_w_house5_tbl, cKF_kn_obj_w_house5_tbl, cKF_c_obj_w_house5_tbl, -1, 51
};

u8 cKF_ckcb_r_obj_w_house5_out_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_house5_out_tbl[] = { 13 };

s16 cKF_c_obj_w_house5_out_tbl[] = {
    2000, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

s16 cKF_ds_obj_w_house5_out_tbl[] = { 1,    -900, 817,  2,   -873, 1200, 3,    -820,  1610, 5,    -705, 1886, 14,
                                      -149, 1163, 19,   -50, 193,  29,   -239, -1584, 41,   -907, -439, 42,   -915,
                                      336,  43,   -885, 225, 44,   -900, -225, 45,    -900, 0,    51,   -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_w_house5_out = { cKF_ckcb_r_obj_w_house5_out_tbl,
                                                cKF_ds_obj_w_house5_out_tbl,
                                                cKF_kn_obj_w_house5_out_tbl,
                                                cKF_c_obj_w_house5_out_tbl,
                                                -1,
                                                51 };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_s_house1_c(void) {
    pc_load_asset("assets/obj_s_house1/obj_w_house3_a_pal.bin", obj_w_house3_a_pal, 0x20, 0x833420, 0, 1);
}
#endif
