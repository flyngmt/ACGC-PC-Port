#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_shop1_front_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_shop1_front_txt[] = {
#include "assets/obj_s_shop1_front_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shop1_roof_txt[0x800];
#else
u8 obj_s_shop1_roof_txt[] = {
#include "assets/obj_s_shop1_roof_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shop1_side_txt[0x800];
#else
u8 obj_s_shop1_side_txt[] = {
#include "assets/obj_s_shop1_side_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shop1_window_txt[0x80];
#else
u8 obj_s_shop1_window_txt[] = {
#include "assets/obj_s_shop1_window_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_shop1_v[0x320 / sizeof(Vtx)];
#else
Vtx obj_s_shop1_v[] = {
#include "assets/obj_s_shop1_v.inc"
};
#endif

Gfx obj_s_shop1_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_shop1_window_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shop1_v[42], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shop1_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, ENVIRONMENT, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_shop1_front_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shop1_v[4], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shop1_side_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_shop1_side_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shop1_v[25], 9, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 7, 8, 6, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shop1_roof_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_shop1_roof_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shop1_v[12], 13, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 2, 11, 0, 2, 12, 11),
    gsSPEndDisplayList(),
};

Gfx obj_s_shop1_front_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_shop1_front_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shop1_v[34], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shop1_door_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_shop1_front_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_shop1_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_shop1_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 316, 0, 2513 } },
                                             { obj_s_shop1_front_model, 5, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_s_shop1_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 3750, 0, 0 } },
                                             { obj_s_shop1_roof_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_s_shop1_side_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_s_shop1_light_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_s_shop1_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_s_shop1 = { ARRAY_COUNT(cKF_je_r_obj_s_shop1_tbl), 6, cKF_je_r_obj_s_shop1_tbl };

u8 cKF_ckcb_r_obj_s_shop1_tbl[] = { 0, 0, 2, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_shop1_tbl[] = { 5 };

s16 cKF_c_obj_s_shop1_tbl[] = { 316, 0, 2513, 0, -1350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_s_shop1_tbl[] = { 1, -900, -338, 2, -911, -651, 14, -1756, -1233, 15, -1789, -657, 16, -1800, -344 };

cKF_Animation_R_c cKF_ba_r_obj_s_shop1 = {
    cKF_ckcb_r_obj_s_shop1_tbl, cKF_ds_obj_s_shop1_tbl, cKF_kn_obj_s_shop1_tbl, cKF_c_obj_s_shop1_tbl, -1, 16
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_w_shop1_front_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_w_shop1_front_txt[] = {
#include "assets/obj_w_shop1_front_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shop1_roof_txt[0x800];
#else
u8 obj_w_shop1_roof_txt[] = {
#include "assets/obj_w_shop1_roof_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shop1_side_txt[0x800];
#else
u8 obj_w_shop1_side_txt[] = {
#include "assets/obj_w_shop1_side_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shop1_window_txt[0x80];
#else
u8 obj_w_shop1_window_txt[] = {
#include "assets/obj_w_shop1_window_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_shop1_v[0x320 / sizeof(Vtx)];
#else
Vtx obj_w_shop1_v[] = {
#include "assets/obj_w_shop1_v.inc"
};
#endif

Gfx obj_w_shop1_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_shop1_window_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shop1_v[42], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shop1_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, ENVIRONMENT, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_shop1_front_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shop1_v[4], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shop1_side_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_shop1_side_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shop1_v[25], 9, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 7, 8, 6, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shop1_roof_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_shop1_roof_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shop1_v[12], 13, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 2, 11, 0, 2, 12, 11),
    gsSPEndDisplayList(),
};

Gfx obj_w_shop1_front_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_shop1_front_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shop1_v[34], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shop1_door_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_shop1_front_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_shop1_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_shop1_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 316, 0, 2513 } },
                                             { obj_w_shop1_front_model, 5, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_w_shop1_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 3750, 0, 0 } },
                                             { obj_w_shop1_roof_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_w_shop1_side_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_w_shop1_light_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_w_shop1_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_w_shop1 = { ARRAY_COUNT(cKF_je_r_obj_w_shop1_tbl), 6, cKF_je_r_obj_w_shop1_tbl };

u8 cKF_ckcb_r_obj_w_shop1_tbl[] = { 0, 0, 2, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_shop1_tbl[] = { 5 };

s16 cKF_c_obj_w_shop1_tbl[] = { 316, 0, 2513, 0, -1350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_w_shop1_tbl[] = { 1, -900, -338, 2, -911, -651, 14, -1756, -1233, 15, -1789, -657, 16, -1800, -344 };

cKF_Animation_R_c cKF_ba_r_obj_w_shop1 = {
    cKF_ckcb_r_obj_w_shop1_tbl, cKF_ds_obj_w_shop1_tbl, cKF_kn_obj_w_shop1_tbl, cKF_c_obj_w_shop1_tbl, -1, 16
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_shop2_t3_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_shop2_t3_tex_txt[] = {
#include "assets/obj_s_shop2_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shop2_window_tex_txt[0x80];
#else
u8 obj_s_shop2_window_tex_txt[] = {
#include "assets/obj_s_shop2_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shop2_t1_tex_txt[0x800];
#else
u8 obj_s_shop2_t1_tex_txt[] = {
#include "assets/obj_s_shop2_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shop2_t2_tex_txt[0x800];
#else
u8 obj_s_shop2_t2_tex_txt[] = {
#include "assets/obj_s_shop2_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_shop2_v[0x600 / sizeof(Vtx)];
#else
Vtx obj_s_shop2_v[] = {
#include "assets/obj_s_shop2_v.inc"
};
#endif

Gfx obj_s_shop2_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_shop2_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shop2_v[7], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shop2_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_shop2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shop2_v[53], 25, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 11, 9, 9, 12, 10),
    gsSPNTriangles_5b(12, 13, 10, 12, 14, 13, 15, 16, 17, 15, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 19, 21, 22, 23, 21, 20, 23, 20, 24),
    gsSPEndDisplayList(),
};

Gfx obj_s_shop2_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_shop2_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shop2_v[78], 18, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 2, 3, 4, 5, 2, 4),
    gsSPNTriangles_5b(5, 0, 2, 6, 7, 8, 6, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 13, 11, 14, 8, 7, 15, 14, 7, 9, 16, 6),
    gsSPNTriangles_5b(16, 17, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shop2_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, SHADE, PRIM_LOD_FRAC, SHADE, 0, 0, 0, TEXEL0, TEXEL1, 0, COMBINED, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_shop2_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shop2_v[15], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 3, 1, 4, 0, 5),
    gsSPNTriangles_5b(4, 6, 0, 7, 8, 9, 8, 10, 9, 11, 12, 13),
    gsSPNTriangles_5b(11, 13, 14, 15, 16, 17, 15, 17, 18, 0, 19, 3),
    gsSPNTriangles_5b(0, 6, 19, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 28, 29, 30, 28, 31, 29, 0, 0, 0),
    gsSPVertex(&obj_s_shop2_v[47], 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 2, 1, 4),
    gsSPNTriangles_5b(1, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shop2_door1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_shop2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shop2_v[4], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shop2_door2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_shop2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_shop2_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_shop2_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 17213, 0, 56808 } },
                                             { obj_s_shop2_light_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_s_shop2_door1_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1, 0, 0 } },
                                             { obj_s_shop2_door2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 24000, 0, 0 } },
                                             { obj_s_shop2_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_s_shop2_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_s_shop2_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_s_shop2 = { ARRAY_COUNT(cKF_je_r_obj_s_shop2_tbl), 6, cKF_je_r_obj_s_shop2_tbl };

u8 cKF_ckcb_r_obj_s_shop2_tbl[] = { 56, 7, 7, 7, 0, 0, 0 };

s16 cKF_kn_obj_s_shop2_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };

s16 cKF_c_obj_s_shop2_tbl[] = { 0, -1350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_s_shop2_tbl[] = { 1, 17213, 0, 16, 17213, 0, 1, 0,    0, 16, 0,    0, 1, -8728, 0, 16, -8728, 0,
                                 1, 0,     0, 16, 0,     0, 1, 0,    0, 16, 0,    0, 1, 0,     0, 16, 0,     0,
                                 1, 0,     0, 16, 0,     0, 1, 0,    0, 16, -100, 0, 1, 0,     0, 16, 0,     0,
                                 1, 0,     0, 16, 0,     0, 1, -900, 0, 16, -800, 0, 1, 0,     0, 16, 0,     0 };

cKF_Animation_R_c cKF_ba_r_obj_s_shop2 = {
    cKF_ckcb_r_obj_s_shop2_tbl, cKF_ds_obj_s_shop2_tbl, cKF_kn_obj_s_shop2_tbl, cKF_c_obj_s_shop2_tbl, -1, 16
};

#ifdef TARGET_PC
u8 obj_w_shop2_t3_tex_txt[0x800];
#else
u8 obj_w_shop2_t3_tex_txt[] = {
#include "assets/obj_w_shop2_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shop2_window_tex_txt[0x80];
#else
u8 obj_w_shop2_window_tex_txt[] = {
#include "assets/obj_w_shop2_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shop2_t1_tex_txt[0x800];
#else
u8 obj_w_shop2_t1_tex_txt[] = {
#include "assets/obj_w_shop2_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shop2_t2_tex_txt[0x800];
#else
u8 obj_w_shop2_t2_tex_txt[] = {
#include "assets/obj_w_shop2_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_shop2_v[0x600 / sizeof(Vtx)];
#else
Vtx obj_w_shop2_v[] = {
#include "assets/obj_w_shop2_v.inc"
};
#endif

Gfx obj_w_shop2_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_shop2_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shop2_v[7], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shop2_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_w_shop2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shop2_v[53], 25, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 11, 9, 9, 12, 10),
    gsSPNTriangles_5b(12, 13, 10, 12, 14, 13, 15, 16, 17, 15, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 19, 21, 22, 23, 21, 20, 23, 20, 24),
    gsSPEndDisplayList(),
};

Gfx obj_w_shop2_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_shop2_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shop2_v[78], 18, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 2, 3, 4, 5, 2, 4),
    gsSPNTriangles_5b(5, 0, 2, 6, 7, 8, 6, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 13, 11, 14, 8, 7, 15, 14, 7, 9, 16, 6),
    gsSPNTriangles_5b(16, 17, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shop2_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, SHADE, PRIM_LOD_FRAC, SHADE, 0, 0, 0, TEXEL0, TEXEL1, 0, COMBINED, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_shop2_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shop2_v[15], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 3, 1, 4, 0, 5),
    gsSPNTriangles_5b(4, 6, 0, 7, 8, 9, 8, 10, 9, 11, 12, 13),
    gsSPNTriangles_5b(11, 13, 14, 15, 16, 17, 15, 17, 18, 0, 19, 3),
    gsSPNTriangles_5b(0, 6, 19, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 28, 29, 30, 28, 31, 29, 0, 0, 0),
    gsSPVertex(&obj_w_shop2_v[47], 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 2, 1, 4),
    gsSPNTriangles_5b(1, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shop2_door1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_w_shop2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shop2_v[4], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shop2_door2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_w_shop2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_shop2_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_shop2_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 17213, 0, 56808 } },
                                             { obj_w_shop2_light_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_w_shop2_door1_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1, 0, 0 } },
                                             { obj_w_shop2_door2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 24000, 0, 0 } },
                                             { obj_w_shop2_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_w_shop2_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_w_shop2_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_w_shop2 = { ARRAY_COUNT(cKF_je_r_obj_w_shop2_tbl), 6, cKF_je_r_obj_w_shop2_tbl };

u8 cKF_ckcb_r_obj_w_shop2_tbl[] = { 56, 7, 7, 7, 0, 0, 0 };

s16 cKF_kn_obj_w_shop2_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };

s16 cKF_c_obj_w_shop2_tbl[] = { 0, -1350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_w_shop2_tbl[] = { 1, 17213, 0, 16, 17213, 0, 1, 0,    0, 16, 0,    0, 1, -8728, 0, 16, -8728, 0,
                                 1, 0,     0, 16, 0,     0, 1, 0,    0, 16, 0,    0, 1, 0,     0, 16, 0,     0,
                                 1, 0,     0, 16, 0,     0, 1, 0,    0, 16, -100, 0, 1, 0,     0, 16, 0,     0,
                                 1, 0,     0, 16, 0,     0, 1, -900, 0, 16, -800, 0, 1, 0,     0, 16, 0,     0 };

cKF_Animation_R_c cKF_ba_r_obj_w_shop2 = {
    cKF_ckcb_r_obj_w_shop2_tbl, cKF_ds_obj_w_shop2_tbl, cKF_kn_obj_w_shop2_tbl, cKF_c_obj_w_shop2_tbl, -1, 16
};

#ifdef TARGET_PC
u8 obj_s_shop3_t1_tex_txt[0x800];
#else
u8 obj_s_shop3_t1_tex_txt[] = {
#include "assets/obj_s_shop3_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shop3_t2_tex_txt[0x800];
#else
u8 obj_s_shop3_t2_tex_txt[] = {
#include "assets/obj_s_shop3_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shop3_window_tex_txt[0x80];
#else
u8 obj_s_shop3_window_tex_txt[] = {
#include "assets/obj_s_shop3_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shop3_t3_tex_txt[0x800];
#else
u8 obj_s_shop3_t3_tex_txt[] = {
#include "assets/obj_s_shop3_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_shop3_v[0x740 / sizeof(Vtx)];
#else
Vtx obj_s_shop3_v[] = {
#include "assets/obj_s_shop3_v.inc"
};
#endif

Gfx obj_s_shop3_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_shop3_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shop3_v[108], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shop3_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_shop3_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shop3_v[29], 31, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 3, 1, 2, 1, 4),
    gsSPNTriangles_5b(1, 5, 4, 6, 1, 7, 1, 3, 7, 8, 1, 6),
    gsSPNTriangles_5b(8, 5, 1, 9, 10, 11, 10, 12, 11, 13, 14, 15),
    gsSPNTriangles_5b(13, 16, 14, 17, 18, 19, 18, 20, 19, 21, 22, 23),
    gsSPNTriangles_5b(22, 24, 23, 25, 22, 21, 25, 26, 22, 27, 28, 29),
    gsSPNTriangles_5b(27, 29, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shop3_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_shop3_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shop3_v[4], 25, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 8, 12, 9),
    gsSPNTriangles_5b(3, 13, 2, 13, 14, 2, 14, 15, 2, 16, 17, 18),
    gsSPNTriangles_5b(17, 19, 18, 17, 20, 19, 21, 22, 23, 22, 24, 23),
    gsSPEndDisplayList(),
};

Gfx obj_s_shop3_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, SHADE, PRIM_LOD_FRAC, SHADE, 0, 0, 0, TEXEL0, TEXEL1, 0, COMBINED, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_shop3_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shop3_v[60], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 27, 25, 28, 29, 24),
    gsSPNTriangles_5b(29, 27, 24, 30, 17, 16, 30, 31, 17, 0, 0, 0),
    gsSPVertex(&obj_s_shop3_v[92], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 10, 9, 11, 12, 13, 14),
    gsSPNTriangles_5b(15, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shop3_door2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_shop3_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_shop3_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_shop3_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 15213, 0, 58808 } },
                                             { obj_s_shop3_light_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, { 1, 0, 0 } },
                                             { obj_s_shop3_door2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 24000, 0, 0 } },
                                             { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_s_shop3_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_s_shop3_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_s_shop3_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_s_shop3 = { ARRAY_COUNT(cKF_je_r_obj_s_shop3_tbl), 5, cKF_je_r_obj_s_shop3_tbl };

u8 cKF_ckcb_r_obj_s_shop3_tbl[] = { 56, 7, 7, 7, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_shop3_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };

s16 cKF_c_obj_s_shop3_tbl[] = { 0, -1350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_s_shop3_tbl[] = { 1, 15213, 0, 16, 15213, 0, 1, 0,    0, 16, 0,    0, 1, -6728, 0, 16, -6728, 0,
                                 1, 0,     0, 16, 0,     0, 1, 0,    0, 16, 0,    0, 1, 0,     0, 16, 0,     0,
                                 1, 0,     0, 16, 0,     0, 1, 0,    0, 16, -100, 0, 1, 0,     0, 16, 0,     0,
                                 1, 0,     0, 16, 0,     0, 1, -900, 0, 16, -800, 0, 1, 0,     0, 16, 0,     0 };

cKF_Animation_R_c cKF_ba_r_obj_s_shop3 = {
    cKF_ckcb_r_obj_s_shop3_tbl, cKF_ds_obj_s_shop3_tbl, cKF_kn_obj_s_shop3_tbl, cKF_c_obj_s_shop3_tbl, -1, 16
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_w_shop3_t1_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_w_shop3_t1_tex_txt[] = {
#include "assets/obj_w_shop3_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shop3_t2_tex_txt[0x800];
#else
u8 obj_w_shop3_t2_tex_txt[] = {
#include "assets/obj_w_shop3_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shop3_window_tex_txt[0x80];
#else
u8 obj_w_shop3_window_tex_txt[] = {
#include "assets/obj_w_shop3_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shop3_t3_tex_txt[0x800];
#else
u8 obj_w_shop3_t3_tex_txt[] = {
#include "assets/obj_w_shop3_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_shop3_v[0x740 / sizeof(Vtx)];
#else
Vtx obj_w_shop3_v[] = {
#include "assets/obj_w_shop3_v.inc"
};
#endif

Gfx obj_w_shop3_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_shop3_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shop3_v[108], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shop3_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_shop3_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shop3_v[29], 31, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 3, 1, 2, 1, 4),
    gsSPNTriangles_5b(1, 5, 4, 6, 1, 7, 1, 3, 7, 8, 1, 6),
    gsSPNTriangles_5b(8, 5, 1, 9, 10, 11, 10, 12, 11, 13, 14, 15),
    gsSPNTriangles_5b(13, 16, 14, 17, 18, 19, 18, 20, 19, 21, 22, 23),
    gsSPNTriangles_5b(22, 24, 23, 25, 22, 21, 25, 26, 22, 27, 28, 29),
    gsSPNTriangles_5b(27, 29, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shop3_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_w_shop3_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shop3_v[4], 25, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 8, 12, 9),
    gsSPNTriangles_5b(3, 13, 2, 13, 14, 2, 14, 15, 2, 16, 17, 18),
    gsSPNTriangles_5b(17, 19, 18, 17, 20, 19, 21, 22, 23, 22, 24, 23),
    gsSPEndDisplayList(),
};

Gfx obj_w_shop3_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, SHADE, PRIM_LOD_FRAC, SHADE, 0, 0, 0, TEXEL0, TEXEL1, 0, COMBINED, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_shop3_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shop3_v[60], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 27, 25, 28, 29, 24),
    gsSPNTriangles_5b(29, 27, 24, 30, 17, 16, 30, 31, 17, 0, 0, 0),
    gsSPVertex(&obj_w_shop3_v[92], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 10, 9, 11, 12, 13, 14),
    gsSPNTriangles_5b(15, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shop3_door2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_shop3_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_shop3_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_shop3_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 15213, 0, 58808 } },
                                             { obj_w_shop3_light_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, { 1, 0, 0 } },
                                             { obj_w_shop3_door2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 24000, 0, 0 } },
                                             { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_w_shop3_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_w_shop3_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_w_shop3_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_w_shop3 = { ARRAY_COUNT(cKF_je_r_obj_w_shop3_tbl), 5, cKF_je_r_obj_w_shop3_tbl };

u8 cKF_ckcb_r_obj_w_shop3_tbl[] = { 56, 7, 7, 7, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_shop3_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };

s16 cKF_c_obj_w_shop3_tbl[] = { 0, -1350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_w_shop3_tbl[] = { 1, 15213, 0, 16, 15213, 0, 1, 0,    0, 16, 0,    0, 1, -6728, 0, 16, -6728, 0,
                                 1, 0,     0, 16, 0,     0, 1, 0,    0, 16, 0,    0, 1, 0,     0, 16, 0,     0,
                                 1, 0,     0, 16, 0,     0, 1, 0,    0, 16, -100, 0, 1, 0,     0, 16, 0,     0,
                                 1, 0,     0, 16, 0,     0, 1, -900, 0, 16, -800, 0, 1, 0,     0, 16, 0,     0 };

cKF_Animation_R_c cKF_ba_r_obj_w_shop3 = {
    cKF_ckcb_r_obj_w_shop3_tbl, cKF_ds_obj_w_shop3_tbl, cKF_kn_obj_w_shop3_tbl, cKF_c_obj_w_shop3_tbl, -1, 16
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_shop4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_shop4_pal[] = {
#include "assets/obj_s_shop4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shop4_t2_tex_txt[0x800];
#else
u8 obj_s_shop4_t2_tex_txt[] = {
#include "assets/obj_s_shop4_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shop4_t1_tex_txt[0x800];
#else
u8 obj_s_shop4_t1_tex_txt[] = {
#include "assets/obj_s_shop4_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shop4_t3_tex_txt[0x800];
#else
u8 obj_s_shop4_t3_tex_txt[] = {
#include "assets/obj_s_shop4_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shop4_window_tex_txt[0x80];
#else
u8 obj_s_shop4_window_tex_txt[] = {
#include "assets/obj_s_shop4_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_shop4_grass_tex_pic_i4[0x80];
#else
u8 obj_shop4_grass_tex_pic_i4[] = {
#include "assets/obj_shop4_grass_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_shop4_v[0x920 / sizeof(Vtx)];
#else
Vtx obj_s_shop4_v[] = {
#include "assets/obj_s_shop4_v.inc"
};
#endif

Gfx obj_s_shop4_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_shop4_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shop4_v[138], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shop4_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_shop4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_shop4_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shop4_v[100], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 4, 7, 4, 3, 6, 9, 10, 6, 10, 3),
    gsSPNTriangles_5b(4, 11, 12, 4, 12, 5, 13, 14, 15, 13, 15, 16),
    gsSPNTriangles_5b(2, 17, 0, 1, 0, 18, 17, 19, 0, 20, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsSPVertex(&obj_s_shop4_v[130], 8, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 3, 3, 6, 7, 3, 7, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shop4_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_shop4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_shop4_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shop4_v[4], 32, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 4, 6, 7, 4, 7, 5, 2, 7, 6),
    gsSPNTriangles_5b(2, 6, 3, 8, 9, 10, 9, 11, 10, 8, 12, 9),
    gsSPNTriangles_5b(8, 13, 12, 11, 14, 10, 11, 15, 14, 14, 16, 10),
    gsSPNTriangles_5b(16, 17, 10, 16, 18, 17, 16, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 20, 24, 25, 20, 25, 23, 24, 26, 25),
    gsSPNTriangles_5b(24, 27, 26, 28, 29, 30, 28, 30, 31, 0, 0, 0),
    gsSPVertex(&obj_s_shop4_v[36], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shop4_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, SHADE, PRIM_LOD_FRAC, SHADE, 0, 0, 0, TEXEL0, TEXEL1, 0, COMBINED, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_shop4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_shop4_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shop4_v[48], 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 3, 2, 6, 3, 6, 5, 7, 8, 9),
    gsSPNTriangles_5b(7, 9, 10, 11, 12, 13, 11, 13, 14, 15, 16, 12),
    gsSPNTriangles_5b(15, 12, 11, 12, 16, 17, 12, 17, 13, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 23, 24, 22, 24, 25, 26, 27, 28),
    gsSPNTriangles_5b(26, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_shop4_v[78], 14, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 4, 8, 5, 9, 10, 11, 10, 12, 11),
    gsSPNTriangles_5b(9, 13, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shop4_grass_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, TEXEL0, TEXEL0, 0, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 120, 120, 180, 255, 120),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_shop4_grass_tex_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shop4_v[92], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shop4_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_shop4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_shop4_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_shop4_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_shop4_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 15213, 0, 58808 } },
                                             { obj_s_shop4_grass_model, 5, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                             { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, { 1, 0, 0 } },
                                             { obj_s_shop4_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 24000, 0, 0 } },
                                             { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_s_shop4_light_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_s_shop4_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_s_shop4_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_s_shop4_window_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_s_shop4 = { ARRAY_COUNT(cKF_je_r_obj_s_shop4_tbl), 6, cKF_je_r_obj_s_shop4_tbl };

u8 cKF_ckcb_r_obj_s_shop4_tbl[] = { 56, 7, 7, 7, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_shop4_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2 };

s16 cKF_c_obj_s_shop4_tbl[] = { 0, -1350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_s_shop4_tbl[] = { 1,  15213, 0, 16, 15213, 0,   1,  0,     0, 16, 0, 0, 1,  -6728, 0,
                                 16, -6728, 0, 1,  0,     0,   16, 0,     0, 1,  0, 0, 16, 0,     0,
                                 1,  0,     0, 16, 0,     0,   1,  0,     0, 16, 0, 0, 1,  0,     0,
                                 16, -100,  0, 1,  0,     0,   16, 0,     0, 1,  0, 0, 16, 0,     0,
                                 1,  -900,  0, 8,  -855,  306, 16, -1200, 0, 1,  0, 0, 16, 0,     0 };

cKF_Animation_R_c cKF_ba_r_obj_s_shop4 = {
    cKF_ckcb_r_obj_s_shop4_tbl, cKF_ds_obj_s_shop4_tbl, cKF_kn_obj_s_shop4_tbl, cKF_c_obj_s_shop4_tbl, -1, 16
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_shop4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_shop4_pal[] = {
#include "assets/obj_w_shop4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shop4_t2_tex_txt[0x800];
#else
u8 obj_w_shop4_t2_tex_txt[] = {
#include "assets/obj_w_shop4_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shop4_t1_tex_txt[0x800];
#else
u8 obj_w_shop4_t1_tex_txt[] = {
#include "assets/obj_w_shop4_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shop4_t3_tex_txt[0x800];
#else
u8 obj_w_shop4_t3_tex_txt[] = {
#include "assets/obj_w_shop4_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shop4_window_tex_txt[0x80];
#else
u8 obj_w_shop4_window_tex_txt[] = {
#include "assets/obj_w_shop4_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_shop4_v[0x920 / sizeof(Vtx)];
#else
Vtx obj_w_shop4_v[] = {
#include "assets/obj_w_shop4_v.inc"
};
#endif

Gfx obj_w_shop4_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_shop4_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shop4_v[138], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shop4_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_shop4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_shop4_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shop4_v[100], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 4, 7, 4, 3, 6, 9, 10, 6, 10, 3),
    gsSPNTriangles_5b(4, 11, 12, 4, 12, 5, 13, 14, 15, 13, 15, 16),
    gsSPNTriangles_5b(2, 17, 0, 1, 0, 18, 17, 19, 0, 20, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsSPVertex(&obj_w_shop4_v[130], 8, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 3, 3, 6, 7, 3, 7, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shop4_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_shop4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_shop4_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shop4_v[4], 32, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 4, 6, 7, 4, 7, 5, 2, 7, 6),
    gsSPNTriangles_5b(2, 6, 3, 8, 9, 10, 9, 11, 10, 8, 12, 9),
    gsSPNTriangles_5b(8, 13, 12, 11, 14, 10, 11, 15, 14, 14, 16, 10),
    gsSPNTriangles_5b(16, 17, 10, 16, 18, 17, 16, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 20, 24, 25, 20, 25, 23, 24, 26, 25),
    gsSPNTriangles_5b(24, 27, 26, 28, 29, 30, 28, 30, 31, 0, 0, 0),
    gsSPVertex(&obj_w_shop4_v[36], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shop4_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, SHADE, PRIM_LOD_FRAC, SHADE, 0, 0, 0, TEXEL0, TEXEL1, 0, COMBINED, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_shop4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_shop4_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shop4_v[48], 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 3, 2, 6, 3, 6, 5, 7, 8, 9),
    gsSPNTriangles_5b(7, 9, 10, 11, 12, 13, 11, 13, 14, 15, 16, 12),
    gsSPNTriangles_5b(15, 12, 11, 12, 16, 17, 12, 17, 13, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 23, 24, 22, 24, 25, 26, 27, 28),
    gsSPNTriangles_5b(26, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_shop4_v[78], 14, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 4, 8, 5, 9, 10, 11, 10, 12, 11),
    gsSPNTriangles_5b(9, 13, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shop4_grass_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, TEXEL0, TEXEL0, 0, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 120, 120, 180, 255, 120),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_shop4_grass_tex_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shop4_v[92], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shop4_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_shop4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_shop4_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_shop4_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_shop4_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 15213, 0, 58808 } },
                                             { obj_w_shop4_grass_model, 5, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                             { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, { 1, 0, 0 } },
                                             { obj_w_shop4_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 24000, 0, 0 } },
                                             { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_w_shop4_light_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_w_shop4_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_w_shop4_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { obj_w_shop4_window_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_w_shop4 = { ARRAY_COUNT(cKF_je_r_obj_w_shop4_tbl), 6, cKF_je_r_obj_w_shop4_tbl };

u8 cKF_ckcb_r_obj_w_shop4_tbl[] = { 56, 7, 7, 7, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_shop4_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2 };

s16 cKF_c_obj_w_shop4_tbl[] = { 0, -1350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_w_shop4_tbl[] = { 1,  15213, 0, 16, 15213, 0,   1,  0,     0, 16, 0, 0, 1,  -6728, 0,
                                 16, -6728, 0, 1,  0,     0,   16, 0,     0, 1,  0, 0, 16, 0,     0,
                                 1,  0,     0, 16, 0,     0,   1,  0,     0, 16, 0, 0, 1,  0,     0,
                                 16, -100,  0, 1,  0,     0,   16, 0,     0, 1,  0, 0, 16, 0,     0,
                                 1,  -900,  0, 8,  -855,  306, 16, -1200, 0, 1,  0, 0, 16, 0,     0 };

cKF_Animation_R_c cKF_ba_r_obj_w_shop4 = {
    cKF_ckcb_r_obj_w_shop4_tbl, cKF_ds_obj_w_shop4_tbl, cKF_kn_obj_w_shop4_tbl, cKF_c_obj_w_shop4_tbl, -1, 16
};
