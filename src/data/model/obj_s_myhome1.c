#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_myhome_mark_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_myhome_mark_pal[] = {
#include "assets/obj_myhome_mark_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_myhome1_t3_tex_txt[0x800];
#else
u8 obj_s_myhome1_t3_tex_txt[] = {
#include "assets/obj_s_myhome1_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_myhome_mark_tex_txt[0x200];
#else
u8 obj_myhome_mark_tex_txt[] = {
#include "assets/obj_myhome_mark_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_myhome1_window_txt[0x80];
#else
u8 obj_s_myhome1_window_txt[] = {
#include "assets/obj_s_myhome1_window_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_myhome1_t2_tex_txt[0x800];
#else
u8 obj_s_myhome1_t2_tex_txt[] = {
#include "assets/obj_s_myhome1_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_myhome1_t1_tex_txt[0x800];
#else
u8 obj_s_myhome1_t1_tex_txt[] = {
#include "assets/obj_s_myhome1_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_myhome1_v[0x780 / sizeof(Vtx)];
#else
Vtx obj_s_myhome1_v[] = {
#include "assets/obj_s_myhome1_v.inc"
};
#endif

Gfx obj_s_myhome1_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_myhome1_window_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome1_v[18], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome1_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome1_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome1_v[26], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome1_t3_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome1_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome1_v[38], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 16, 19, 17, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 24, 25, 26, 25, 27, 26, 28, 29, 30),
    gsSPNTriangles_5b(28, 31, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_myhome1_v[70], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome1_t2_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome1_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome1_v[104], 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 3, 1, 4, 0, 5),
    gsSPNTriangles_5b(0, 2, 5, 5, 6, 4, 5, 7, 6, 7, 8, 6),
    gsSPNTriangles_5b(7, 9, 8, 9, 10, 8, 10, 11, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome1_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome1_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome1_v[98], 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(3, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome1_fuda_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome1_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome1_v[116], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome1_mark_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome1_v[4], 14, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(1, 5, 4, 1, 6, 5, 1, 7, 6, 0, 8, 1),
    gsSPNTriangles_5b(8, 9, 1, 9, 10, 1, 10, 11, 1, 11, 12, 1),
    gsSPNTriangles_5b(12, 13, 1, 13, 7, 1, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome1_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome1_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_myhome1_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome1_kazamiB_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome1_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome1_v[74], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 4, 6, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome1_kazamiA_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome1_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome1_v[90], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_myhome1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 828, 0, 2000 } },
    { obj_s_myhome1_fuda_model, 8, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1287, 9956, 1994 } },
    { obj_s_myhome1_kazamiA_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1317, 9956, 2024 } },
    { obj_s_myhome1_kazamiB_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome1_door_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
    { obj_s_myhome1_mark_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome1_light_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome1_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome1_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome1_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome1_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_s_myhome1 = { ARRAY_COUNT(cKF_je_r_obj_s_myhome1_tbl), 10, cKF_je_r_obj_s_myhome1_tbl };

u8 cKF_ckcb_r_obj_s_myhome1_tbl[] = { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_myhome1_tbl[] = { 9 };

s16 cKF_c_obj_s_myhome1_tbl[] = { 828, 0, 2000, 0, -1350, 0, 0, 0, 0, 0, 1350, 0, 0, 0, 900, 0, 1350, 0, 0, 0, 900,
                                  0,   0, 0,    0, 0,     0, 0, 0, 0, 0, 0,    0, 0, 0, 0,   0, 0,    0, 0, 0 };

s16 cKF_ds_obj_s_myhome1_tbl[] = { 1,    -900, 0,    8,     -900, 0,    20, -250, 1556, 29, -45, 0,    34, -115,
                                   -855, 47,   -820, -1992, 49,   -915, 0,  50,   -885, 0,  51,  -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_s_myhome1 = {
    cKF_ckcb_r_obj_s_myhome1_tbl, cKF_ds_obj_s_myhome1_tbl, cKF_kn_obj_s_myhome1_tbl, cKF_c_obj_s_myhome1_tbl, -1, 51
};

u8 cKF_ckcb_r_obj_s_myhome1_out_tbl[] = { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_myhome1_out_tbl[] = { 9 };

s16 cKF_c_obj_s_myhome1_out_tbl[] = { 828, 0, 2000, 0, -1350, 0, 0, 0, 0, 0, 1350, 0, 0, 0, 900, 0, 1350, 0, 0, 0, 900,
                                      0,   0, 0,    0, 0,     0, 0, 0, 0, 0, 0,    0, 0, 0, 0,   0, 0,    0, 0, 0 };

s16 cKF_ds_obj_s_myhome1_out_tbl[] = { 1,     -900, 0,    3, -820, 1531, 15, -115, 854,  19, -50, 187,  28, -190,
                                       -1336, 42,   -915, 0, 43,   -885, 0,  44,   -900, 0,  51,  -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_s_myhome1_out = { cKF_ckcb_r_obj_s_myhome1_out_tbl,
                                                 cKF_ds_obj_s_myhome1_out_tbl,
                                                 cKF_kn_obj_s_myhome1_out_tbl,
                                                 cKF_c_obj_s_myhome1_out_tbl,
                                                 -1,
                                                 51 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_myhome2_t3_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_myhome2_t3_tex_txt[] = {
#include "assets/obj_s_myhome2_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_myhome2_window_txt[0x80];
#else
u8 obj_s_myhome2_window_txt[] = {
#include "assets/obj_s_myhome2_window_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_myhome2_t2_tex_txt[0x800];
#else
u8 obj_s_myhome2_t2_tex_txt[] = {
#include "assets/obj_s_myhome2_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_myhome2_t1_tex_txt[0x800];
#else
u8 obj_s_myhome2_t1_tex_txt[] = {
#include "assets/obj_s_myhome2_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_myhome2_v[0x880 / sizeof(Vtx)];
#else
Vtx obj_s_myhome2_v[] = {
#include "assets/obj_s_myhome2_v.inc"
};
#endif

Gfx obj_s_myhome2_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_myhome2_window_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome2_v[18], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome2_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome2_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome2_v[62], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome2_t3_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome2_v[26], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 16, 19, 17, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 22, 24, 25, 26, 24, 27, 25, 28, 29, 30),
    gsSPNTriangles_5b(29, 31, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_myhome2_v[58], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome2_t2_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome2_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome2_v[98], 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 3, 1, 4, 5, 2),
    gsSPNTriangles_5b(5, 0, 2, 4, 6, 5, 6, 7, 5, 6, 8, 7),
    gsSPNTriangles_5b(6, 9, 8, 3, 10, 1, 10, 11, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome2_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome2_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome2_v[110], 22, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 1, 3, 2, 2, 4, 0),
    gsSPNTriangles_5b(2, 5, 4, 6, 7, 8, 6, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 14, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome2_fuda_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome2_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome2_v[132], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome2_mark_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome2_v[4], 14, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(1, 5, 4, 1, 6, 5, 1, 7, 6, 0, 8, 1),
    gsSPNTriangles_5b(8, 9, 1, 9, 10, 1, 10, 11, 1, 11, 12, 1),
    gsSPNTriangles_5b(12, 13, 1, 13, 7, 1, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome2_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_myhome2_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome2_kazamiB_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome2_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome2_v[82], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 4, 6, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome2_kazamiA_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome2_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome2_v[74], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_myhome2_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 828, 0, 2000 } },
    { obj_s_myhome2_fuda_model, 8, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1293, 12000, 2000 } },
    { obj_s_myhome2_kazamiA_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1293, 12000, 2000 } },
    { obj_s_myhome2_kazamiB_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome2_door_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
    { obj_s_myhome2_mark_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome2_light_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome2_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome2_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome2_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome2_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_s_myhome2 = { ARRAY_COUNT(cKF_je_r_obj_s_myhome2_tbl), 10, cKF_je_r_obj_s_myhome2_tbl };

u8 cKF_ckcb_r_obj_s_myhome2_tbl[] = { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_myhome2_tbl[] = { 11 };

s16 cKF_c_obj_s_myhome2_tbl[] = { 828, 0, 2000, 0, -1350, 0, 0, 0, 0, 1350, 0, 900, 0, 0, 900, 1350, 0, 900, 0, 0, 900,
                                  0,   0, 0,    0, 0,     0, 0, 0, 0, 0,    0, 0,   0, 0, 0,   0,    0, 0,   0, 0 };

s16 cKF_ds_obj_s_myhome2_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                   1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                   -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_s_myhome2 = {
    cKF_ckcb_r_obj_s_myhome2_tbl, cKF_ds_obj_s_myhome2_tbl, cKF_kn_obj_s_myhome2_tbl, cKF_c_obj_s_myhome2_tbl, -1, 51
};

u8 cKF_ckcb_r_obj_s_myhome2_out_tbl[] = { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_myhome2_out_tbl[] = { 9 };

s16 cKF_c_obj_s_myhome2_out_tbl[] = { 828, 0,    2000, 0,   -1350, 0, 0,   0, 0, 1350, 0, 900, 0, 0,
                                      900, 1350, 0,    900, 0,     0, 900, 0, 0, 0,    0, 0,   0, 0,
                                      0,   0,    0,    0,   0,     0, 0,   0, 0, 0,    0, 0,   0 };

s16 cKF_ds_obj_s_myhome2_out_tbl[] = { 1,     -900, 0,    3, -820, 1531, 15, -115, 854,  19, -50, 187,  28, -190,
                                       -1336, 42,   -915, 0, 43,   -885, 0,  44,   -900, 0,  51,  -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_s_myhome2_out = { cKF_ckcb_r_obj_s_myhome2_out_tbl,
                                                 cKF_ds_obj_s_myhome2_out_tbl,
                                                 cKF_kn_obj_s_myhome2_out_tbl,
                                                 cKF_c_obj_s_myhome2_out_tbl,
                                                 -1,
                                                 51 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_myhome3_t3_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_myhome3_t3_tex_txt[] = {
#include "assets/obj_s_myhome3_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_myhome3_t2_tex_txt[0x800];
#else
u8 obj_s_myhome3_t2_tex_txt[] = {
#include "assets/obj_s_myhome3_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_myhome3_window_txt[0x80];
#else
u8 obj_s_myhome3_window_txt[] = {
#include "assets/obj_s_myhome3_window_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_myhome3_t1_tex_txt[0x800];
#else
u8 obj_s_myhome3_t1_tex_txt[] = {
#include "assets/obj_s_myhome3_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_myhome3_v[0x980 / sizeof(Vtx)];
#else
Vtx obj_s_myhome3_v[] = {
#include "assets/obj_s_myhome3_v.inc"
};
#endif

Gfx obj_s_myhome3_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_myhome3_window_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome3_v[42], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome3_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome3_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome3_v[116], 18, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome3_t3_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome3_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome3_v[50], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 24, 25, 26, 25, 27, 26, 28, 29, 30),
    gsSPNTriangles_5b(28, 31, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_myhome3_v[82], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome3_t2_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome3_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome3_v[86], 30, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 6, 0, 4, 0, 2, 4, 8, 9, 10),
    gsSPNTriangles_5b(10, 9, 11, 12, 13, 14, 14, 13, 15, 7, 16, 5),
    gsSPNTriangles_5b(16, 17, 5, 16, 18, 17, 16, 19, 18, 1, 20, 3),
    gsSPNTriangles_5b(1, 21, 20, 21, 22, 20, 22, 23, 20, 24, 25, 26),
    gsSPNTriangles_5b(24, 27, 25, 25, 28, 26, 24, 29, 27, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome3_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome3_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome3_v[134], 14, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(7, 9, 8, 9, 10, 8, 6, 11, 7, 7, 12, 9),
    gsSPNTriangles_5b(7, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome3_fuda_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome3_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome3_v[148], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome3_mark_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome3_v[4], 14, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(1, 5, 4, 1, 6, 5, 1, 7, 6, 0, 8, 1),
    gsSPNTriangles_5b(8, 9, 1, 9, 10, 1, 10, 11, 1, 11, 12, 1),
    gsSPNTriangles_5b(12, 13, 1, 13, 7, 1, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome3_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome3_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_myhome3_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome3_kazamiB_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome3_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome3_v[26], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 4, 6, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome3_kazamiA_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome3_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome3_v[18], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_myhome3_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 828, 0, 2000 } },
    { obj_s_myhome3_fuda_model, 8, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1293, 13000, 2000 } },
    { obj_s_myhome3_kazamiA_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1293, 13000, 2000 } },
    { obj_s_myhome3_kazamiB_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome3_door_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
    { obj_s_myhome3_mark_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome3_light_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome3_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome3_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome3_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome3_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_s_myhome3 = { ARRAY_COUNT(cKF_je_r_obj_s_myhome3_tbl), 10, cKF_je_r_obj_s_myhome3_tbl };

u8 cKF_ckcb_r_obj_s_myhome3_tbl[] = { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_myhome3_tbl[] = { 11 };

s16 cKF_c_obj_s_myhome3_tbl[] = { 828, 0, 2000, 0, -1350, 0, 0, 0, 0, 1350, 0, 900, 0, 0, 0, 1350, 0, 900, 0, 0, 0,
                                  0,   0, 0,    0, 0,     0, 0, 0, 0, 0,    0, 0,   0, 0, 0, 0,    0, 0,   0, 0 };

s16 cKF_ds_obj_s_myhome3_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                   1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                   -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_s_myhome3 = {
    cKF_ckcb_r_obj_s_myhome3_tbl, cKF_ds_obj_s_myhome3_tbl, cKF_kn_obj_s_myhome3_tbl, cKF_c_obj_s_myhome3_tbl, -1, 51
};

u8 cKF_ckcb_r_obj_s_myhome3_out_tbl[] = { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_myhome3_out_tbl[] = { 13 };

s16 cKF_c_obj_s_myhome3_out_tbl[] = { 828, 0, 2000, 0, -1350, 0, 0, 0, 0, 1350, 0, 900, 0, 0, 0, 1350, 0, 900, 0, 0, 0,
                                      0,   0, 0,    0, 0,     0, 0, 0, 0, 0,    0, 0,   0, 0, 0, 0,    0, 0,   0, 0 };

s16 cKF_ds_obj_s_myhome3_out_tbl[] = { 1,    -900, 817,  2,   -873, 1200, 3,    -820,  1610, 5,    -705, 1886, 14,
                                       -149, 1163, 19,   -50, 193,  29,   -239, -1584, 41,   -907, -439, 42,   -915,
                                       336,  43,   -885, 225, 44,   -900, -225, 45,    -900, 0,    51,   -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_s_myhome3_out = { cKF_ckcb_r_obj_s_myhome3_out_tbl,
                                                 cKF_ds_obj_s_myhome3_out_tbl,
                                                 cKF_kn_obj_s_myhome3_out_tbl,
                                                 cKF_c_obj_s_myhome3_out_tbl,
                                                 -1,
                                                 51 };

#ifdef TARGET_PC
u8 obj_w_myhome1_t3_tex_txt[0x800];
#else
u8 obj_w_myhome1_t3_tex_txt[] = {
#include "assets/obj_w_myhome1_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_myhome1_window_txt[0x80];
#else
u8 obj_w_myhome1_window_txt[] = {
#include "assets/obj_w_myhome1_window_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_myhome1_t2_tex_txt[0x800];
#else
u8 obj_w_myhome1_t2_tex_txt[] = {
#include "assets/obj_w_myhome1_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_myhome1_t1_tex_txt[0x800];
#else
u8 obj_w_myhome1_t1_tex_txt[] = {
#include "assets/obj_w_myhome1_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_myhome1_v[0x780 / sizeof(Vtx)];
#else
Vtx obj_w_myhome1_v[] = {
#include "assets/obj_w_myhome1_v.inc"
};
#endif

Gfx obj_w_myhome1_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_myhome1_window_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome1_v[18], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome1_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome1_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome1_v[26], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome1_t3_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome1_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome1_v[38], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 16, 19, 17, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 24, 25, 26, 25, 27, 26, 28, 29, 30),
    gsSPNTriangles_5b(28, 31, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_myhome1_v[70], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome1_t2_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome1_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome1_v[104], 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 3, 1, 4, 0, 5),
    gsSPNTriangles_5b(0, 2, 5, 5, 6, 4, 5, 7, 6, 7, 8, 6),
    gsSPNTriangles_5b(7, 9, 8, 9, 10, 8, 10, 11, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome1_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome1_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome1_v[98], 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(3, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome1_fuda_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome1_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome1_v[116], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome1_mark_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome1_v[4], 14, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(1, 5, 4, 1, 6, 5, 1, 7, 6, 0, 8, 1),
    gsSPNTriangles_5b(8, 9, 1, 9, 10, 1, 10, 11, 1, 11, 12, 1),
    gsSPNTriangles_5b(12, 13, 1, 13, 7, 1, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome1_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome1_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_myhome1_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome1_kazamiB_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome1_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome1_v[74], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 4, 6, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome1_kazamiA_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome1_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome1_v[90], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_myhome1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 828, 0, 2000 } },
    { obj_w_myhome1_fuda_model, 8, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1287, 9956, 1994 } },
    { obj_w_myhome1_kazamiA_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1317, 9956, 2024 } },
    { obj_w_myhome1_kazamiB_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome1_door_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
    { obj_w_myhome1_mark_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome1_light_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome1_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome1_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome1_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome1_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_w_myhome1 = { ARRAY_COUNT(cKF_je_r_obj_w_myhome1_tbl), 10, cKF_je_r_obj_w_myhome1_tbl };

u8 cKF_ckcb_r_obj_w_myhome1_tbl[] = { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_myhome1_tbl[] = { 11 };

s16 cKF_c_obj_w_myhome1_tbl[] = { 828, 0, 2000, 0, -1350, 0, 0, 0, 0, 0, 1350, 0, 0, 0, 900, 0, 1350, 0, 0, 0, 900,
                                  0,   0, 0,    0, 0,     0, 0, 0, 0, 0, 0,    0, 0, 0, 0,   0, 0,    0, 0, 0 };

s16 cKF_ds_obj_w_myhome1_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                   1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                   -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_w_myhome1 = {
    cKF_ckcb_r_obj_w_myhome1_tbl, cKF_ds_obj_w_myhome1_tbl, cKF_kn_obj_w_myhome1_tbl, cKF_c_obj_w_myhome1_tbl, -1, 51
};

u8 cKF_ckcb_r_obj_w_myhome1_out_tbl[] = { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_myhome1_out_tbl[] = { 9 };

s16 cKF_c_obj_w_myhome1_out_tbl[] = { 828, 0, 2000, 0, -1350, 0, 0, 0, 0, 0, 1350, 0, 0, 0, 900, 0, 1350, 0, 0, 0, 900,
                                      0,   0, 0,    0, 0,     0, 0, 0, 0, 0, 0,    0, 0, 0, 0,   0, 0,    0, 0, 0 };

s16 cKF_ds_obj_w_myhome1_out_tbl[] = { 1,     -900, 0,    3, -820, 1531, 15, -115, 854,  19, -50, 187,  28, -190,
                                       -1336, 42,   -915, 0, 43,   -885, 0,  44,   -900, 0,  51,  -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_w_myhome1_out = { cKF_ckcb_r_obj_w_myhome1_out_tbl,
                                                 cKF_ds_obj_w_myhome1_out_tbl,
                                                 cKF_kn_obj_w_myhome1_out_tbl,
                                                 cKF_c_obj_w_myhome1_out_tbl,
                                                 -1,
                                                 51 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_w_myhome2_t3_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_w_myhome2_t3_tex_txt[] = {
#include "assets/obj_w_myhome2_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_myhome2_window_txt[0x80];
#else
u8 obj_w_myhome2_window_txt[] = {
#include "assets/obj_w_myhome2_window_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_myhome2_t2_tex_txt[0x800];
#else
u8 obj_w_myhome2_t2_tex_txt[] = {
#include "assets/obj_w_myhome2_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_myhome2_t1_tex_txt[0x800];
#else
u8 obj_w_myhome2_t1_tex_txt[] = {
#include "assets/obj_w_myhome2_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_myhome2_v[0x840 / sizeof(Vtx)];
#else
Vtx obj_w_myhome2_v[] = {
#include "assets/obj_w_myhome2_v.inc"
};
#endif

Gfx obj_w_myhome2_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_myhome2_window_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome2_v[18], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome2_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome2_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome2_v[62], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome2_t3_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome2_v[26], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 16, 19, 17, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 22, 24, 25, 26, 24, 27, 25, 28, 29, 30),
    gsSPNTriangles_5b(29, 31, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_myhome2_v[58], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome2_t2_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome2_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome2_v[98], 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 3, 1, 4, 5, 2),
    gsSPNTriangles_5b(5, 0, 2, 4, 6, 5, 6, 7, 5, 6, 8, 7),
    gsSPNTriangles_5b(6, 9, 8, 3, 10, 1, 10, 11, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome2_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome2_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome2_v[110], 18, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 1, 3, 2, 2, 4, 0),
    gsSPNTriangles_5b(2, 5, 4, 6, 7, 8, 6, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 9, 13, 14, 15, 13, 15, 10, 9, 8, 16),
    gsSPNTriangles_5b(9, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome2_fuda_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome2_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome2_v[128], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome2_mark_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome2_v[4], 14, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(1, 5, 4, 1, 6, 5, 1, 7, 6, 0, 8, 1),
    gsSPNTriangles_5b(8, 9, 1, 9, 10, 1, 10, 11, 1, 11, 12, 1),
    gsSPNTriangles_5b(12, 13, 1, 13, 7, 1, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome2_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_myhome2_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome2_kazamiB_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome2_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome2_v[82], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 4, 6, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome2_kazamiA_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome2_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome2_v[74], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_myhome2_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 828, 0, 2000 } },
    { obj_w_myhome2_fuda_model, 8, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1293, 12000, 2000 } },
    { obj_w_myhome2_kazamiA_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1293, 12000, 2000 } },
    { obj_w_myhome2_kazamiB_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome2_door_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
    { obj_w_myhome2_mark_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome2_light_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome2_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 64708, 0, 2000 } },
    { obj_w_myhome2_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome2_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome2_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_w_myhome2 = { ARRAY_COUNT(cKF_je_r_obj_w_myhome2_tbl), 10, cKF_je_r_obj_w_myhome2_tbl };

u8 cKF_ckcb_r_obj_w_myhome2_tbl[] = { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_myhome2_tbl[] = { 9 };

s16 cKF_c_obj_w_myhome2_tbl[] = { 828, 0, 2000, 0, -1350, 0, 0, 0, 0, 1350, 0, 900, 0, 0, 900, 1350, 0, 900, 0, 0, 900,
                                  0,   0, 0,    0, 0,     0, 0, 0, 0, 1350, 0, 0,   0, 0, 0,   0,    0, 0,   0, 0 };

s16 cKF_ds_obj_w_myhome2_tbl[] = { 1,    -900, 0,    8,     -900, 0,    20, -250, 1556, 29, -45, 0,    34, -115,
                                   -855, 47,   -820, -1992, 49,   -915, 0,  50,   -885, 0,  51,  -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_w_myhome2 = {
    cKF_ckcb_r_obj_w_myhome2_tbl, cKF_ds_obj_w_myhome2_tbl, cKF_kn_obj_w_myhome2_tbl, cKF_c_obj_w_myhome2_tbl, -1, 51
};

u8 cKF_ckcb_r_obj_w_myhome2_out_tbl[] = { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_myhome2_out_tbl[] = { 9 };

s16 cKF_c_obj_w_myhome2_out_tbl[] = { 828, 0,    2000, 0,   -1350, 0, 0,   0, 0, 1350, 0, 900, 0, 0,
                                      900, 1350, 0,    900, 0,     0, 900, 0, 0, 0,    0, 0,   0, 0,
                                      0,   0,    1350, 0,   0,     0, 0,   0, 0, 0,    0, 0,   0 };

s16 cKF_ds_obj_w_myhome2_out_tbl[] = { 1,     -900, 0,    3, -820, 1531, 15, -115, 854,  19, -50, 187,  28, -190,
                                       -1336, 42,   -915, 0, 43,   -885, 0,  44,   -900, 0,  51,  -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_w_myhome2_out = { cKF_ckcb_r_obj_w_myhome2_out_tbl,
                                                 cKF_ds_obj_w_myhome2_out_tbl,
                                                 cKF_kn_obj_w_myhome2_out_tbl,
                                                 cKF_c_obj_w_myhome2_out_tbl,
                                                 -1,
                                                 51 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_w_myhome3_t3_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_w_myhome3_t3_tex_txt[] = {
#include "assets/obj_w_myhome3_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_myhome3_t2_tex_txt[0x800];
#else
u8 obj_w_myhome3_t2_tex_txt[] = {
#include "assets/obj_w_myhome3_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_myhome3_window_txt[0x80];
#else
u8 obj_w_myhome3_window_txt[] = {
#include "assets/obj_w_myhome3_window_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_myhome3_t1_tex_txt[0x800];
#else
u8 obj_w_myhome3_t1_tex_txt[] = {
#include "assets/obj_w_myhome3_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_myhome3_v[0x980 / sizeof(Vtx)];
#else
Vtx obj_w_myhome3_v[] = {
#include "assets/obj_w_myhome3_v.inc"
};
#endif

Gfx obj_w_myhome3_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_myhome3_window_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome3_v[42], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome3_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome3_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome3_v[116], 18, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome3_t3_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome3_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome3_v[50], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 24, 25, 26, 25, 27, 26, 28, 29, 30),
    gsSPNTriangles_5b(28, 31, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_myhome3_v[82], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome3_t2_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome3_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome3_v[86], 30, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 6, 0, 4, 0, 2, 4, 8, 9, 10),
    gsSPNTriangles_5b(10, 9, 11, 12, 13, 14, 14, 13, 15, 7, 16, 5),
    gsSPNTriangles_5b(16, 17, 5, 16, 18, 17, 16, 19, 18, 1, 20, 3),
    gsSPNTriangles_5b(1, 21, 20, 21, 22, 20, 22, 23, 20, 24, 25, 26),
    gsSPNTriangles_5b(24, 27, 25, 25, 28, 26, 24, 29, 27, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome3_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome3_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome3_v[134], 14, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(7, 9, 8, 9, 10, 8, 6, 11, 7, 7, 12, 9),
    gsSPNTriangles_5b(7, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome3_fuda_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome3_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome3_v[148], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome3_mark_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome3_v[4], 14, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(1, 5, 4, 1, 6, 5, 1, 7, 6, 0, 8, 1),
    gsSPNTriangles_5b(8, 9, 1, 9, 10, 1, 10, 11, 1, 11, 12, 1),
    gsSPNTriangles_5b(12, 13, 1, 13, 7, 1, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome3_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome3_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_myhome3_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome3_kazamiB_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome3_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome3_v[26], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 4, 6, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome3_kazamiA_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome3_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome3_v[18], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_myhome3_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 828, 0, 2000 } },
    { obj_w_myhome3_fuda_model, 8, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1293, 13000, 2000 } },
    { obj_w_myhome3_kazamiA_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1293, 13000, 2000 } },
    { obj_w_myhome3_kazamiB_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome3_door_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
    { obj_w_myhome3_mark_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome3_light_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome3_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome3_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome3_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome3_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_w_myhome3 = { ARRAY_COUNT(cKF_je_r_obj_w_myhome3_tbl), 10, cKF_je_r_obj_w_myhome3_tbl };

u8 cKF_ckcb_r_obj_w_myhome3_tbl[] = { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_myhome3_tbl[] = { 11 };

s16 cKF_c_obj_w_myhome3_tbl[] = { 828, 0, 2000, 0, -1350, 0, 0, 0, 0, 1350, 0, 900, 0, 0, 0, 1350, 0, 900, 0, 0, 0,
                                  0,   0, 0,    0, 0,     0, 0, 0, 0, 0,    0, 0,   0, 0, 0, 0,    0, 0,   0, 0 };

s16 cKF_ds_obj_w_myhome3_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                   1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                   -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_w_myhome3 = {
    cKF_ckcb_r_obj_w_myhome3_tbl, cKF_ds_obj_w_myhome3_tbl, cKF_kn_obj_w_myhome3_tbl, cKF_c_obj_w_myhome3_tbl, -1, 51
};

u8 cKF_ckcb_r_obj_w_myhome3_out_tbl[] = { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_myhome3_out_tbl[] = { 13 };

s16 cKF_c_obj_w_myhome3_out_tbl[] = { 828, 0, 2000, 0, -1350, 0, 0, 0, 0, 1350, 0, 900, 0, 0, 0, 1350, 0, 900, 0, 0, 0,
                                      0,   0, 0,    0, 0,     0, 0, 0, 0, 0,    0, 0,   0, 0, 0, 0,    0, 0,   0, 0 };

s16 cKF_ds_obj_w_myhome3_out_tbl[] = { 1,    -900, 817,  2,   -873, 1200, 3,    -820,  1610, 5,    -705, 1886, 14,
                                       -149, 1163, 19,   -50, 193,  29,   -239, -1584, 41,   -907, -439, 42,   -915,
                                       336,  43,   -885, 225, 44,   -900, -225, 45,    -900, 0,    51,   -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_w_myhome3_out = { cKF_ckcb_r_obj_w_myhome3_out_tbl,
                                                 cKF_ds_obj_w_myhome3_out_tbl,
                                                 cKF_kn_obj_w_myhome3_out_tbl,
                                                 cKF_c_obj_w_myhome3_out_tbl,
                                                 -1,
                                                 51 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_myhome4_t3_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_myhome4_t3_tex_txt[] = {
#include "assets/obj_s_myhome4_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_myhome4_t2_tex_txt[0x800];
#else
u8 obj_s_myhome4_t2_tex_txt[] = {
#include "assets/obj_s_myhome4_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_myhome4_t1_tex_txt[0x800];
#else
u8 obj_s_myhome4_t1_tex_txt[] = {
#include "assets/obj_s_myhome4_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_myhome4_window_txt[0x80];
#else
u8 obj_s_myhome4_window_txt[] = {
#include "assets/obj_s_myhome4_window_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_myhome4_v[0xC60 / sizeof(Vtx)];
#else
Vtx obj_s_myhome4_v[] = {
#include "assets/obj_s_myhome4_v.inc"
};
#endif

Gfx obj_s_myhome4_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_myhome4_window_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome4_v[86], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome4_t3_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome4_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome4_v[42], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 19, 16, 18, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 27, 24, 26, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_myhome4_v[74], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome4_t2_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome4_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome4_v[117], 15, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 1, 3, 2, 4, 2, 5),
    gsSPNTriangles_5b(4, 0, 2, 6, 7, 8, 6, 9, 7, 10, 6, 11),
    gsSPNTriangles_5b(6, 8, 11, 12, 13, 14, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome4_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_myhome4_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome4_v[132], 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 4, 5, 3, 6, 4),
    gsSPNTriangles_5b(7, 8, 5, 7, 9, 8, 10, 11, 12, 11, 13, 12),
    gsSPNTriangles_5b(14, 15, 10, 14, 16, 15, 17, 18, 19, 18, 20, 19),
    gsSPNTriangles_5b(21, 17, 22, 17, 19, 22, 23, 24, 25, 23, 26, 24),
    gsSPNTriangles_5b(26, 27, 24, 27, 28, 24, 27, 29, 28, 29, 30, 28),
    gsSPNTriangles_5b(27, 31, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_myhome4_v[164], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 3, 1, 2, 1, 4),
    gsSPNTriangles_5b(1, 5, 4, 6, 7, 8, 7, 9, 8, 7, 10, 9),
    gsSPNTriangles_5b(10, 11, 9, 12, 13, 14, 12, 15, 13, 14, 16, 17),
    gsSPNTriangles_5b(16, 18, 17, 19, 20, 21, 19, 22, 20, 23, 24, 25),
    gsSPNTriangles_5b(24, 26, 25, 27, 28, 29, 28, 19, 29, 0, 0, 0),
    gsSPVertex(&obj_s_myhome4_v[194], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome4_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_myhome4_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome4_v[94], 23, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 15, 17, 18, 19, 20, 21, 19, 21, 22),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome4_fuda_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_myhome4_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome4_v[78], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome4_mark_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome4_v[4], 14, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(1, 5, 4, 1, 6, 5, 1, 7, 6, 0, 8, 1),
    gsSPNTriangles_5b(8, 9, 1, 9, 10, 1, 10, 11, 1, 11, 12, 1),
    gsSPNTriangles_5b(12, 13, 1, 13, 7, 1, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome4_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome4_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_myhome4_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome4_kazamiB_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome4_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome4_v[26], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_myhome4_kazamiA_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_myhome4_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_myhome4_v[18], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_myhome4_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 828, 0, 2000 } },
    { obj_s_myhome4_fuda_model, 8, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 586, 13500, 2000 } },
    { obj_s_myhome4_kazamiA_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 586, 13500, 2000 } },
    { obj_s_myhome4_kazamiB_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome4_door_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
    { obj_s_myhome4_mark_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome4_light_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome4_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome4_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome4_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_myhome4_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_s_myhome4 = { ARRAY_COUNT(cKF_je_r_obj_s_myhome4_tbl), 10, cKF_je_r_obj_s_myhome4_tbl };

u8 cKF_ckcb_r_obj_s_myhome4_tbl[] = { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_myhome4_tbl[] = { 11 };

s16 cKF_c_obj_s_myhome4_tbl[] = { 828, 0, 2000, 0, -1350, 0, 0, 0, 0, 1350, 0, 900, 0, 0, 0, 1350, 0, 900, 0, 0, 0,
                                  0,   0, 0,    0, 0,     0, 0, 0, 0, 0,    0, 0,   0, 0, 0, 0,    0, 0,   0, 0 };

s16 cKF_ds_obj_s_myhome4_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                   1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                   -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_s_myhome4 = {
    cKF_ckcb_r_obj_s_myhome4_tbl, cKF_ds_obj_s_myhome4_tbl, cKF_kn_obj_s_myhome4_tbl, cKF_c_obj_s_myhome4_tbl, -1, 51
};

u8 cKF_ckcb_r_obj_s_myhome4_out_tbl[] = { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_myhome4_out_tbl[] = { 13 };

s16 cKF_c_obj_s_myhome4_out_tbl[] = { 828, 0, 2000, 0, -1350, 0, 0, 0, 0, 1350, 0, 900, 0, 0, 0, 1350, 0, 900, 0, 0, 0,
                                      0,   0, 0,    0, 0,     0, 0, 0, 0, 0,    0, 0,   0, 0, 0, 0,    0, 0,   0, 0 };

s16 cKF_ds_obj_s_myhome4_out_tbl[] = { 1,    -900, 817,  2,   -873, 1200, 3,    -820,  1610, 5,    -705, 1886, 14,
                                       -149, 1163, 19,   -50, 193,  29,   -239, -1584, 41,   -907, -439, 42,   -915,
                                       336,  43,   -885, 225, 44,   -900, -225, 45,    -900, 0,    51,   -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_s_myhome4_out = { cKF_ckcb_r_obj_s_myhome4_out_tbl,
                                                 cKF_ds_obj_s_myhome4_out_tbl,
                                                 cKF_kn_obj_s_myhome4_out_tbl,
                                                 cKF_c_obj_s_myhome4_out_tbl,
                                                 -1,
                                                 51 };

#ifdef TARGET_PC
u8 obj_w_myhome4_t3_tex_txt[0x800];
#else
u8 obj_w_myhome4_t3_tex_txt[] = {
#include "assets/obj_w_myhome4_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_myhome4_t2_tex_txt[0x800];
#else
u8 obj_w_myhome4_t2_tex_txt[] = {
#include "assets/obj_w_myhome4_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_myhome4_t1_tex_txt[0x800];
#else
u8 obj_w_myhome4_t1_tex_txt[] = {
#include "assets/obj_w_myhome4_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_myhome4_window_txt[0x80];
#else
u8 obj_w_myhome4_window_txt[] = {
#include "assets/obj_w_myhome4_window_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_myhome4_v[0xC60 / sizeof(Vtx)];
#else
Vtx obj_w_myhome4_v[] = {
#include "assets/obj_w_myhome4_v.inc"
};
#endif

Gfx obj_w_myhome4_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_myhome4_window_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome4_v[86], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome4_t3_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome4_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome4_v[42], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 19, 16, 18, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 27, 24, 26, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_myhome4_v[74], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome4_t2_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome4_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome4_v[117], 15, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 1, 3, 2, 4, 2, 5),
    gsSPNTriangles_5b(4, 0, 2, 6, 7, 8, 6, 9, 7, 10, 6, 11),
    gsSPNTriangles_5b(6, 8, 11, 12, 13, 14, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome4_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_w_myhome4_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome4_v[132], 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 4, 5, 3, 6, 4),
    gsSPNTriangles_5b(7, 8, 5, 7, 9, 8, 10, 11, 12, 11, 13, 12),
    gsSPNTriangles_5b(14, 15, 10, 14, 16, 15, 17, 18, 19, 18, 20, 19),
    gsSPNTriangles_5b(21, 17, 22, 17, 19, 22, 23, 24, 25, 23, 26, 24),
    gsSPNTriangles_5b(26, 27, 24, 27, 28, 24, 27, 29, 28, 29, 30, 28),
    gsSPNTriangles_5b(27, 31, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_myhome4_v[164], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 3, 1, 2, 1, 4),
    gsSPNTriangles_5b(1, 5, 4, 6, 7, 8, 7, 9, 8, 7, 10, 9),
    gsSPNTriangles_5b(10, 11, 9, 12, 13, 14, 12, 15, 13, 14, 16, 17),
    gsSPNTriangles_5b(16, 18, 17, 19, 20, 21, 19, 22, 20, 23, 24, 25),
    gsSPNTriangles_5b(24, 26, 25, 27, 28, 29, 28, 19, 29, 0, 0, 0),
    gsSPVertex(&obj_w_myhome4_v[194], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome4_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_w_myhome4_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome4_v[94], 23, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 15, 17, 18, 19, 20, 21, 19, 21, 22),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome4_fuda_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_w_myhome4_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome4_v[78], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome4_mark_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome4_v[4], 14, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(1, 5, 4, 1, 6, 5, 1, 7, 6, 0, 8, 1),
    gsSPNTriangles_5b(8, 9, 1, 9, 10, 1, 10, 11, 1, 11, 12, 1),
    gsSPNTriangles_5b(12, 13, 1, 13, 7, 1, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome4_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome4_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_myhome4_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome4_kazamiB_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome4_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome4_v[26], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_myhome4_kazamiA_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_myhome4_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_myhome4_v[18], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_myhome4_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 828, 0, 2000 } },
    { obj_w_myhome4_fuda_model, 8, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 586, 13500, 2000 } },
    { obj_w_myhome4_kazamiA_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 586, 13500, 2000 } },
    { obj_w_myhome4_kazamiB_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome4_door_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
    { obj_w_myhome4_mark_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome4_light_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome4_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome4_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome4_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_myhome4_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_w_myhome4 = { ARRAY_COUNT(cKF_je_r_obj_w_myhome4_tbl), 10, cKF_je_r_obj_w_myhome4_tbl };

u8 cKF_ckcb_r_obj_w_myhome4_tbl[] = { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_myhome4_tbl[] = { 11 };

s16 cKF_c_obj_w_myhome4_tbl[] = { 828, 0, 2000, 0, -1350, 0, 0, 0, 0, 1350, 0, 900, 0, 0, 0, 1350, 0, 900, 0, 0, 0,
                                  0,   0, 0,    0, 0,     0, 0, 0, 0, 0,    0, 0,   0, 0, 0, 0,    0, 0,   0, 0 };

s16 cKF_ds_obj_w_myhome4_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                   1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                   -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_w_myhome4 = {
    cKF_ckcb_r_obj_w_myhome4_tbl, cKF_ds_obj_w_myhome4_tbl, cKF_kn_obj_w_myhome4_tbl, cKF_c_obj_w_myhome4_tbl, -1, 51
};

u8 cKF_ckcb_r_obj_w_myhome4_out_tbl[] = { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_myhome4_out_tbl[] = { 13 };

s16 cKF_c_obj_w_myhome4_out_tbl[] = { 828, 0, 2000, 0, -1350, 0, 0, 0, 0, 1350, 0, 900, 0, 0, 0, 1350, 0, 900, 0, 0, 0,
                                      0,   0, 0,    0, 0,     0, 0, 0, 0, 0,    0, 0,   0, 0, 0, 0,    0, 0,   0, 0 };

s16 cKF_ds_obj_w_myhome4_out_tbl[] = { 1,    -900, 817,  2,   -873, 1200, 3,    -820,  1610, 5,    -705, 1886, 14,
                                       -149, 1163, 19,   -50, 193,  29,   -239, -1584, 41,   -907, -439, 42,   -915,
                                       336,  43,   -885, 225, 44,   -900, -225, 45,    -900, 0,    51,   -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_w_myhome4_out = { cKF_ckcb_r_obj_w_myhome4_out_tbl,
                                                 cKF_ds_obj_w_myhome4_out_tbl,
                                                 cKF_kn_obj_w_myhome4_out_tbl,
                                                 cKF_c_obj_w_myhome4_out_tbl,
                                                 -1,
                                                 51 };
