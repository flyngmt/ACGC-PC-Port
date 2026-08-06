#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_yubinkyoku_t3_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_yubinkyoku_t3_txt[] = {
#include "assets/obj_s_yubinkyoku_t3_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_yubinkyoku_t1_txt[0x800];
#else
u8 obj_s_yubinkyoku_t1_txt[] = {
#include "assets/obj_s_yubinkyoku_t1_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_yubinkyoku_window_tex_txt[0x80];
#else
u8 obj_s_yubinkyoku_window_tex_txt[] = {
#include "assets/obj_s_yubinkyoku_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_yubinkyoku_t2_txt[0x800];
#else
u8 obj_s_yubinkyoku_t2_txt[] = {
#include "assets/obj_s_yubinkyoku_t2_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_yubinkyoku_v[0x310 / sizeof(Vtx)];
#else
Vtx obj_s_yubinkyoku_v[] = {
#include "assets/obj_s_yubinkyoku_v.inc"
};
#endif

Gfx obj_s_yubinkyoku_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_yubinkyoku_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_yubinkyoku_v[13], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_yubinkyoku_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_yubinkyoku_v[37], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_yubinkyoku_t3_1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_yubinkyoku_t3_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 1020, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_yubinkyoku_v[25], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_yubinkyoku_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_yubinkyoku_t2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_yubinkyoku_v[17], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_yubinkyoku_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_yubinkyoku_t1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_yubinkyoku_v[4], 9, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 8, 8, 5, 4, 6, 7, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_yubinkyoku_neon_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_yubinkyoku_t3_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 508),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_yubinkyoku_v[29], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_yubinkyoku_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_yubinkyoku_t3_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_yubinkyoku_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_yubinkyoku_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 64436, 0, 4000 } },
    { obj_s_yubinkyoku_light_model, 6, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_yubinkyoku_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
    { obj_s_yubinkyoku_neon_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_yubinkyoku_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_yubinkyoku_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_yubinkyoku_t3_1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_yubinkyoku_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_s_yubinkyoku = { ARRAY_COUNT(cKF_je_r_obj_s_yubinkyoku_tbl), 7,
                                               cKF_je_r_obj_s_yubinkyoku_tbl };

u8 cKF_ckcb_r_obj_s_yubinkyoku_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_yubinkyoku_tbl[] = { 11 };

s16 cKF_c_obj_s_yubinkyoku_tbl[] = { -1100, 0, 4000, 0, -900, 0, 0, -450, 0, 0, 0, 0, 0,
                                     0,     0, 0,    0, 0,    0, 0, 0,    0, 0, 0, 0, 0 };

s16 cKF_ds_obj_s_yubinkyoku_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                      1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                      -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_s_yubinkyoku = { cKF_ckcb_r_obj_s_yubinkyoku_tbl,
                                                cKF_ds_obj_s_yubinkyoku_tbl,
                                                cKF_kn_obj_s_yubinkyoku_tbl,
                                                cKF_c_obj_s_yubinkyoku_tbl,
                                                -1,
                                                51 };

u8 cKF_ckcb_r_obj_s_yubinkyoku_out_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_yubinkyoku_out_tbl[] = { 13 };

s16 cKF_c_obj_s_yubinkyoku_out_tbl[] = { -1100, 0, 4000, 0, -900, 0, 0, -450, 0, 0, 0, 0, 0,
                                         0,     0, 0,    0, 0,    0, 0, 0,    0, 0, 0, 0, 0 };

s16 cKF_ds_obj_s_yubinkyoku_out_tbl[] = { 1,    -900, 817,  2,   -873, 1200, 3,    -820,  1610, 5,    -705, 1886, 14,
                                          -149, 1163, 19,   -50, 193,  29,   -239, -1584, 41,   -907, -439, 42,   -915,
                                          336,  43,   -885, 225, 44,   -900, -225, 45,    -900, 0,    51,   -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_s_yubinkyoku_out = { cKF_ckcb_r_obj_s_yubinkyoku_out_tbl,
                                                    cKF_ds_obj_s_yubinkyoku_out_tbl,
                                                    cKF_kn_obj_s_yubinkyoku_out_tbl,
                                                    cKF_c_obj_s_yubinkyoku_out_tbl,
                                                    -1,
                                                    51 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_w_yubinkyoku_t3_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_w_yubinkyoku_t3_txt[] = {
#include "assets/obj_w_yubinkyoku_t3_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_yubinkyoku_t1_txt[0x800];
#else
u8 obj_w_yubinkyoku_t1_txt[] = {
#include "assets/obj_w_yubinkyoku_t1_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_yubinkyoku_window_tex_txt[0x80];
#else
u8 obj_w_yubinkyoku_window_tex_txt[] = {
#include "assets/obj_w_yubinkyoku_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_yubinkyoku_t2_txt[0x800];
#else
u8 obj_w_yubinkyoku_t2_txt[] = {
#include "assets/obj_w_yubinkyoku_t2_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_yubinkyoku_v[0x340 / sizeof(Vtx)];
#else
Vtx obj_w_yubinkyoku_v[] = {
#include "assets/obj_w_yubinkyoku_v.inc"
};
#endif

Gfx obj_w_yubinkyoku_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_yubinkyoku_v[40], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_yubinkyoku_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_yubinkyoku_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_yubinkyoku_v[16], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_yubinkyoku_t3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_yubinkyoku_t3_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 1020, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_yubinkyoku_v[28], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_yubinkyoku_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_yubinkyoku_t2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_yubinkyoku_v[20], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_yubinkyoku_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_yubinkyoku_t1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 1020, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_yubinkyoku_v[4], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 5, 4, 11, 8, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_yubinkyoku_neon_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_yubinkyoku_t3_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 508),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_yubinkyoku_v[32], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_yubinkyoku_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_yubinkyoku_t3_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_yubinkyoku_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_yubinkyoku_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 64436, 0, 4000 } },
    { obj_w_yubinkyoku_light_model, 6, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_yubinkyoku_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
    { obj_w_yubinkyoku_neon_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_yubinkyoku_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_yubinkyoku_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_yubinkyoku_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_yubinkyoku_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_w_yubinkyoku = { ARRAY_COUNT(cKF_je_r_obj_w_yubinkyoku_tbl), 7,
                                               cKF_je_r_obj_w_yubinkyoku_tbl };

u8 cKF_ckcb_r_obj_w_yubinkyoku_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_yubinkyoku_tbl[] = { 11 };

s16 cKF_c_obj_w_yubinkyoku_tbl[] = { -1100, 0, 4000, 0, -900, 0, 0, -450, 0, 0, 0, 0, 0,
                                     0,     0, 0,    0, 0,    0, 0, 0,    0, 0, 0, 0, 0 };

s16 cKF_ds_obj_w_yubinkyoku_tbl[] = { 1,    -900,  0,   7,    -900, 0,    9,     -891, 506,  20,    -250,
                                      1566, 29,    -45, -12,  36,   -183, -1187, 46,   -754, -1989, 47,
                                      -820, -1958, 49,  -915, -14,  50,   -885,  225,  51,   -900,  -450 };

cKF_Animation_R_c cKF_ba_r_obj_w_yubinkyoku = { cKF_ckcb_r_obj_w_yubinkyoku_tbl,
                                                cKF_ds_obj_w_yubinkyoku_tbl,
                                                cKF_kn_obj_w_yubinkyoku_tbl,
                                                cKF_c_obj_w_yubinkyoku_tbl,
                                                -1,
                                                51 };

u8 cKF_ckcb_r_obj_w_yubinkyoku_out_tbl[] = { 0, 0, 2, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_yubinkyoku_out_tbl[] = { 13 };

s16 cKF_c_obj_w_yubinkyoku_out_tbl[] = { -1100, 0, 4000, 0, -900, 0, 0, -450, 0, 0, 0, 0, 0,
                                         0,     0, 0,    0, 0,    0, 0, 0,    0, 0, 0, 0, 0 };

s16 cKF_ds_obj_w_yubinkyoku_out_tbl[] = { 1,    -900, 817,  2,   -873, 1200, 3,    -820,  1610, 5,    -705, 1886, 14,
                                          -149, 1163, 19,   -50, 193,  29,   -239, -1584, 41,   -907, -439, 42,   -915,
                                          336,  43,   -885, 225, 44,   -900, -225, 45,    -900, 0,    51,   -900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_w_yubinkyoku_out = { cKF_ckcb_r_obj_w_yubinkyoku_out_tbl,
                                                    cKF_ds_obj_w_yubinkyoku_out_tbl,
                                                    cKF_kn_obj_w_yubinkyoku_out_tbl,
                                                    cKF_c_obj_w_yubinkyoku_out_tbl,
                                                    -1,
                                                    51 };
