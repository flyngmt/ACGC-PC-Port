#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_bridgeA_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_bridgeA_pal[] = {
#include "assets/obj_s_bridgeA_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_bridgeA_t1_tex_txt[0x800];
#else
u8 obj_s_bridgeA_t1_tex_txt[] = {
#include "assets/obj_s_bridgeA_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_bridgeA_t2_tex_txt[0x800];
#else
u8 obj_s_bridgeA_t2_tex_txt[] = {
#include "assets/obj_s_bridgeA_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_bridgeA_v[0x8A0 / sizeof(Vtx)];
#else
Vtx obj_s_bridgeA_v[] = {
#include "assets/obj_s_bridgeA_v.inc"
};
#endif

Gfx obj_s_bridgeA_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_bridgeA_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_bridgeA_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_bridgeA_v[75], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 13, 14, 15, 13, 15, 16),
    gsSPNTriangles_5b(14, 17, 18, 14, 18, 15, 17, 19, 20, 17, 20, 18),
    gsSPNTriangles_5b(21, 22, 23, 21, 23, 24, 25, 26, 27, 25, 27, 28),
    gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_bridgeA_v[107], 31, 0),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 0, 2, 3, 2, 4),
    gsSPNTriangles_5b(5, 3, 4, 5, 4, 6, 7, 8, 9, 7, 9, 10),
    gsSPNTriangles_5b(8, 11, 12, 8, 12, 9, 11, 13, 14, 11, 14, 12),
    gsSPNTriangles_5b(15, 16, 17, 15, 17, 18, 19, 20, 21, 19, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 25, 26, 27, 23, 26, 27, 26, 28),
    gsSPNTriangles_5b(29, 27, 28, 29, 28, 30, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_bridgeA_step2_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_bridgeA_v[50], 10, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_bridgeA_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_bridgeA_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&obj_s_bridgeA_v[60], 15, 10),
    gsSPNTrianglesInit_5b(6, 6, 10, 11, 6, 12, 9, 2, 13, 14),
    gsSPNTriangles_5b(2, 15, 7, 3, 16, 17, 3, 18, 8, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_bridgeA_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 5, 4, 19, 4, 21, 20, 1, 0, 22),
    gsSPNTriangles_5b(0, 24, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_bridgeA_step3_model[] = {
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_bridgeA_v[25], 10, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_bridgeA_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_bridgeA_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&obj_s_bridgeA_v[35], 15, 10),
    gsSPNTrianglesInit_5b(6, 2, 10, 11, 2, 12, 5, 0, 13, 14),
    gsSPNTriangles_5b(0, 15, 3, 1, 16, 17, 1, 18, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_bridgeA_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 7, 19, 7, 21, 20, 9, 6, 22),
    gsSPNTriangles_5b(6, 24, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_bridgeA_step4_model[] = {
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_bridgeA_v, 10, 0),
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_bridgeA_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_bridgeA_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&obj_s_bridgeA_v[10], 15, 10),
    gsSPNTrianglesInit_5b(6, 0, 10, 11, 0, 12, 2, 3, 13, 14),
    gsSPNTriangles_5b(3, 15, 5, 1, 16, 17, 1, 18, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_bridgeA_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 19, 20, 8, 7, 21, 9, 22, 23),
    gsSPNTriangles_5b(9, 6, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_bridgeA_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 6000, 4000, 59536 } },
    { obj_s_bridgeA_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2828, 0, 0 } },
    { obj_s_bridgeA_step2_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 4000, 0, 0 } },
    { obj_s_bridgeA_step3_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 8000, 0, 0 } },
    { obj_s_bridgeA_step4_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 4000, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_s_bridgeA = { ARRAY_COUNT(cKF_je_r_obj_s_bridgeA_tbl), 4, cKF_je_r_obj_s_bridgeA_tbl };

u8 cKF_ckcb_r_obj_s_bridgeA_tbl[] = { 0, 0, 1, 1, 1, 1 };

s16 cKF_kn_obj_s_bridgeA_tbl[] = { 5, 5, 5, 4 };

s16 cKF_c_obj_s_bridgeA_tbl[] = { 6000, 4000, -6000, 0, -1350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_s_bridgeA_tbl[] = { 1, -450, -17, 13, -492, -105, 20, -495, 85,  32, -451, 32,  33, -450, 17,
                                   1, 900,  17,  13, 942,  105,  20, 945,  -85, 32, 901,  -32, 33, 900,  -17,
                                   1, -900, 17,  13, -858, 105,  20, -855, -85, 32, -899, -32, 33, -900, -17,
                                   1, 450,  -17, 13, 408,  -105, 21, 408,  105, 33, 450,  17 };

cKF_Animation_R_c cKF_ba_r_obj_s_bridgeA = {
    cKF_ckcb_r_obj_s_bridgeA_tbl, cKF_ds_obj_s_bridgeA_tbl, cKF_kn_obj_s_bridgeA_tbl, cKF_c_obj_s_bridgeA_tbl, -1, 33
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_bridgeA_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_bridgeA_pal[] = {
#include "assets/obj_w_bridgeA_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_bridgeA_t1_tex_txt[0x800];
#else
u8 obj_w_bridgeA_t1_tex_txt[] = {
#include "assets/obj_w_bridgeA_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_bridgeA_t2_tex_txt[0x800];
#else
u8 obj_w_bridgeA_t2_tex_txt[] = {
#include "assets/obj_w_bridgeA_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_bridgeA_v[0x8A0 / sizeof(Vtx)];
#else
Vtx obj_w_bridgeA_v[] = {
#include "assets/obj_w_bridgeA_v.inc"
};
#endif

Gfx obj_w_bridgeA_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_bridgeA_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_bridgeA_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_bridgeA_v[75], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 13, 14, 15, 13, 15, 16),
    gsSPNTriangles_5b(14, 17, 18, 14, 18, 15, 17, 19, 20, 17, 20, 18),
    gsSPNTriangles_5b(21, 22, 23, 21, 23, 24, 25, 26, 27, 25, 27, 28),
    gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_bridgeA_v[107], 31, 0),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 0, 2, 3, 2, 4),
    gsSPNTriangles_5b(5, 3, 4, 5, 4, 6, 7, 8, 9, 7, 9, 10),
    gsSPNTriangles_5b(8, 11, 12, 8, 12, 9, 11, 13, 14, 11, 14, 12),
    gsSPNTriangles_5b(15, 16, 17, 15, 17, 18, 19, 20, 21, 19, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 25, 26, 27, 23, 26, 27, 26, 28),
    gsSPNTriangles_5b(29, 27, 28, 29, 28, 30, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_bridgeA_step2_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_bridgeA_v[50], 10, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_bridgeA_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_w_bridgeA_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&obj_w_bridgeA_v[60], 15, 10),
    gsSPNTrianglesInit_5b(6, 6, 10, 11, 6, 12, 9, 2, 13, 14),
    gsSPNTriangles_5b(2, 15, 7, 3, 16, 17, 3, 18, 8, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_bridgeA_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 5, 4, 19, 4, 21, 20, 1, 0, 22),
    gsSPNTriangles_5b(0, 24, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_bridgeA_step3_model[] = {
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_bridgeA_v[25], 10, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_bridgeA_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_w_bridgeA_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&obj_w_bridgeA_v[35], 15, 10),
    gsSPNTrianglesInit_5b(6, 2, 10, 11, 2, 12, 5, 0, 13, 14),
    gsSPNTriangles_5b(0, 15, 3, 1, 16, 17, 1, 18, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_bridgeA_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 7, 19, 7, 21, 20, 9, 6, 22),
    gsSPNTriangles_5b(6, 24, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_bridgeA_step4_model[] = {
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_bridgeA_v, 10, 0),
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_bridgeA_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_w_bridgeA_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&obj_w_bridgeA_v[10], 15, 10),
    gsSPNTrianglesInit_5b(6, 0, 10, 11, 0, 12, 2, 3, 13, 14),
    gsSPNTriangles_5b(3, 15, 5, 1, 16, 17, 1, 18, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_bridgeA_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 19, 20, 8, 7, 21, 9, 22, 23),
    gsSPNTriangles_5b(9, 6, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_bridgeA_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 6000, 4000, 59536 } },
    { obj_w_bridgeA_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2828, 0, 0 } },
    { obj_w_bridgeA_step2_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 4000, 0, 0 } },
    { obj_w_bridgeA_step3_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 8000, 0, 0 } },
    { obj_w_bridgeA_step4_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 4000, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_w_bridgeA = { ARRAY_COUNT(cKF_je_r_obj_w_bridgeA_tbl), 4, cKF_je_r_obj_w_bridgeA_tbl };

u8 cKF_ckcb_r_obj_w_bridgeA_tbl[] = { 0, 0, 1, 1, 1, 1 };

s16 cKF_kn_obj_w_bridgeA_tbl[] = { 5, 5, 5, 4 };

s16 cKF_c_obj_w_bridgeA_tbl[] = { 6000, 4000, -6000, 0, -1350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_w_bridgeA_tbl[] = { 1, -450, -17, 13, -492, -105, 20, -495, 85,  32, -451, 32,  33, -450, 17,
                                   1, 900,  17,  13, 942,  105,  20, 945,  -85, 32, 901,  -32, 33, 900,  -17,
                                   1, -900, 17,  13, -858, 105,  20, -855, -85, 32, -899, -32, 33, -900, -17,
                                   1, 450,  -17, 13, 408,  -105, 21, 408,  105, 33, 450,  17 };

cKF_Animation_R_c cKF_ba_r_obj_w_bridgeA = {
    cKF_ckcb_r_obj_w_bridgeA_tbl, cKF_ds_obj_w_bridgeA_tbl, cKF_kn_obj_w_bridgeA_tbl, cKF_c_obj_w_bridgeA_tbl, -1, 33
};
