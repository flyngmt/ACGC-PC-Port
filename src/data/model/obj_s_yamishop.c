#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_yamishop_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_yamishop_pal[] = {
#include "assets/obj_s_yamishop_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_yamishop_t2_tex_txt[0x800];
#else
u8 obj_s_yamishop_t2_tex_txt[] = {
#include "assets/obj_s_yamishop_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_yamishop_t1_tex_txt[0x800];
#else
u8 obj_s_yamishop_t1_tex_txt[] = {
#include "assets/obj_s_yamishop_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_yamishop_window_tex_txt[0x80];
#else
u8 obj_s_yamishop_window_tex_txt[] = {
#include "assets/obj_s_yamishop_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_yamishop_v[0x420 / sizeof(Vtx)];
#else
Vtx obj_s_yamishop_v[] = {
#include "assets/obj_s_yamishop_v.inc"
};
#endif

Gfx obj_s_yamishop_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_yamishop_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_yamishop_v[62], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_yamishop_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_yamishop_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_yamishop_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_yamishop_v[33], 29, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 9, 11, 12, 13, 9, 8, 14, 9),
    gsSPNTriangles_5b(10, 12, 9, 4, 15, 5, 16, 17, 18, 7, 9, 19),
    gsSPNTriangles_5b(20, 16, 21, 21, 16, 18, 16, 22, 23, 3, 20, 21),
    gsSPNTriangles_5b(3, 2, 20, 24, 25, 0, 16, 23, 17, 0, 25, 1),
    gsSPNTriangles_5b(26, 0, 3, 26, 27, 0, 27, 24, 0, 16, 20, 28),
    gsSPNTriangles_5b(22, 16, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_yamishop_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_yamishop_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_yamishop_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_yamishop_v[25], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_yamishop_door1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_yamishop_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_yamishop_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_yamishop_v[20], 2, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_yamishop_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_s_yamishop_v[22], 3, 2),
    gsSPNTrianglesInit_5b(2, 0, 2, 3, 0, 1, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_yamishop_door2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_yamishop_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_yamishop_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_yamishop_v, 20, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 4, 7, 8, 9, 10, 11, 9, 11, 12),
    gsSPNTriangles_5b(10, 13, 14, 10, 14, 11, 13, 15, 16, 13, 16, 14),
    gsSPNTriangles_5b(15, 17, 18, 15, 18, 16, 0, 19, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_yamishop_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 4000, 60036 } },
    { obj_s_yamishop_light_model, 3, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_yamishop_door1_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } },
    { obj_s_yamishop_door2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 9849, 0, 0 } },
    { obj_s_yamishop_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_yamishop_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 9750, 62536, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_s_yamishop = { ARRAY_COUNT(cKF_je_r_obj_s_yamishop_tbl), 5, cKF_je_r_obj_s_yamishop_tbl };

u8 cKF_ckcb_r_obj_s_yamishop_tbl[] = { 0, 0, 1, 1, 0, 0 };

s16 cKF_kn_obj_s_yamishop_tbl[] = { 4, 5 };

s16 cKF_c_obj_s_yamishop_tbl[] = { 0, 4000, -5500, 0, 0, 0, 1800, -900, 0, 0, 0, 0, 0, 0, 0, 0, -900, 1800, -900 };

s16 cKF_ds_obj_s_yamishop_tbl[] = { 1,    240, -140, 3,     222, -504,  16,    -170, -267,  17,    -175, -140,  1,   0,
                                    -606, 2,   -20,  -1160, 10,  -1068, -4957, 16,   -1780, -1160, 17,   -1800, -606 };

cKF_Animation_R_c cKF_ba_r_obj_s_yamishop = { cKF_ckcb_r_obj_s_yamishop_tbl,
                                              cKF_ds_obj_s_yamishop_tbl,
                                              cKF_kn_obj_s_yamishop_tbl,
                                              cKF_c_obj_s_yamishop_tbl,
                                              -1,
                                              17 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_w_yamishop_t2_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_w_yamishop_t2_tex_txt[] = {
#include "assets/obj_w_yamishop_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_yamishop_t1_tex_txt[0x800];
#else
u8 obj_w_yamishop_t1_tex_txt[] = {
#include "assets/obj_w_yamishop_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_yamishop_window_tex_txt[0x80];
#else
u8 obj_w_yamishop_window_tex_txt[] = {
#include "assets/obj_w_yamishop_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_yamishop_v[0x420 / sizeof(Vtx)];
#else
Vtx obj_w_yamishop_v[] = {
#include "assets/obj_w_yamishop_v.inc"
};
#endif

Gfx obj_w_yamishop_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_yamishop_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_yamishop_v[62], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_yamishop_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_yamishop_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_yamishop_v[33], 29, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 9, 11, 12, 13, 9, 8, 14, 9),
    gsSPNTriangles_5b(10, 12, 9, 4, 15, 5, 16, 17, 18, 7, 9, 19),
    gsSPNTriangles_5b(20, 16, 21, 21, 16, 18, 16, 22, 23, 3, 20, 21),
    gsSPNTriangles_5b(3, 2, 20, 24, 25, 0, 16, 23, 17, 0, 25, 1),
    gsSPNTriangles_5b(26, 0, 3, 26, 27, 0, 27, 24, 0, 16, 20, 28),
    gsSPNTriangles_5b(22, 16, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_yamishop_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_yamishop_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_yamishop_v[25], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_yamishop_door1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_yamishop_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_yamishop_v[20], 2, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_yamishop_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_w_yamishop_v[22], 3, 2),
    gsSPNTrianglesInit_5b(2, 0, 2, 3, 0, 1, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_yamishop_door2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_yamishop_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_yamishop_v, 20, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 4, 7, 8, 9, 10, 11, 9, 11, 12),
    gsSPNTriangles_5b(10, 13, 14, 10, 14, 11, 13, 15, 16, 13, 16, 14),
    gsSPNTriangles_5b(15, 17, 18, 15, 18, 16, 0, 19, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_yamishop_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 4000, 60036 } },
    { obj_w_yamishop_light_model, 3, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_yamishop_door1_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } },
    { obj_w_yamishop_door2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 9849, 0, 0 } },
    { obj_w_yamishop_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_yamishop_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 9750, 62536, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_w_yamishop = { ARRAY_COUNT(cKF_je_r_obj_w_yamishop_tbl), 5, cKF_je_r_obj_w_yamishop_tbl };

u8 cKF_ckcb_r_obj_w_yamishop_tbl[] = { 0, 0, 1, 1, 0, 0 };

s16 cKF_kn_obj_w_yamishop_tbl[] = { 4, 5 };

s16 cKF_c_obj_w_yamishop_tbl[] = { 0, 4000, -5500, 0, 0, 0, 1800, -900, 0, 0, 0, 0, 0, 0, 0, 0, -900, 1800, -900 };

s16 cKF_ds_obj_w_yamishop_tbl[] = { 1,    240, -140, 3,     222, -504,  16,    -170, -267,  17,    -175, -140,  1,   0,
                                    -606, 2,   -20,  -1160, 10,  -1068, -4957, 16,   -1780, -1160, 17,   -1800, -606 };

cKF_Animation_R_c cKF_ba_r_obj_w_yamishop = { cKF_ckcb_r_obj_w_yamishop_tbl,
                                              cKF_ds_obj_w_yamishop_tbl,
                                              cKF_kn_obj_w_yamishop_tbl,
                                              cKF_c_obj_w_yamishop_tbl,
                                              -1,
                                              17 };
