#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_e_tukimi_t2_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_e_tukimi_t2_tex_txt[] = {
#include "assets/obj_e_tukimi_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_tukimi_t3_tex_txt[0x800];
#else
u8 obj_e_tukimi_t3_tex_txt[] = {
#include "assets/obj_e_tukimi_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_tukimi_t1_tex_txt[0x800];
#else
u8 obj_e_tukimi_t1_tex_txt[] = {
#include "assets/obj_e_tukimi_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_tukimi_r_v[0x480 / sizeof(Vtx)];
#else
Vtx obj_e_tukimi_r_v[] = {
#include "assets/obj_e_tukimi_r_v.inc"
};
#endif

Gfx obj_e_tukimi_r_ne2_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_tukimi_r_v[40], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_tukimi_r_ne1_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_tukimi_r_v[44], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_tukimi_r_moti_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_tukimi_r_v, 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 4, 2, 5),
    gsSPNTriangles_5b(4, 0, 2, 6, 7, 8, 6, 9, 7, 8, 10, 11),
    gsSPNTriangles_5b(8, 7, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_tukimi_r_hako_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_tukimi_r_v[24], 16, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 4, 7, 8, 7, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 10, 13, 14, 13, 15, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_tukimi_r_endai_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIM_LOD_FRAC, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_tukimi_r_v[68], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_tukimi_r_dai_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_tukimi_r_v[12], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_tukimi_r_kuki2_model[] = {
    gsSPMatrix(&anime_6_mdl[9], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_tukimi_r_v[63], 2, 0),
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_e_tukimi_r_v[65], 3, 2),
    gsSPNTrianglesInit_5b(2, 0, 2, 1, 0, 3, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_tukimi_r_ho2_model[] = {
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_tukimi_r_v[58], 2, 0),
    gsSPMatrix(&anime_6_mdl[4], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_e_tukimi_r_v[60], 3, 2),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_tukimi_r_kuki1_model[] = {
    gsSPMatrix(&anime_6_mdl[8], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_tukimi_r_v[53], 2, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_e_tukimi_r_v[55], 3, 2),
    gsSPNTrianglesInit_5b(2, 0, 2, 1, 0, 3, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_tukimi_r_ho1_model[] = {
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_tukimi_r_v[48], 2, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_e_tukimi_r_v[50], 3, 2),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_e_tukimi_r_tbl[] = {
    { obj_e_tukimi_r_dai_model, 7, cKF_JOINT_FLAG_DISP_OPA, { 0, 63536, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 64320, 4800, 63736 } },
    { obj_e_tukimi_r_kuki1_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_e_tukimi_r_ho1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1100, 4800, 500 } },
    { obj_e_tukimi_r_kuki2_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_e_tukimi_r_ho2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } },
    { obj_e_tukimi_r_endai_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_e_tukimi_r_hako_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_e_tukimi_r_moti_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_e_tukimi_r_ne1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_e_tukimi_r_ne2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_e_tukimi_r = { ARRAY_COUNT(cKF_je_r_obj_e_tukimi_r_tbl), 10,
                                             cKF_je_r_obj_e_tukimi_r_tbl };

u8 cKF_ckcb_r_obj_e_tukimi_r_tbl[] = { 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_e_tukimi_r_tbl[] = { 7, 7, 7, 7 };

s16 cKF_c_obj_e_tukimi_r_tbl[] = { 0, -2000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0,     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_e_tukimi_r_tbl[] = { 1,    900, 0,   51,   900, -2,  94,   821, 23,  113, 840, -6,  157, 812,
                                    20,   212, 901, 21,   271, 900, 0,    1,   20,  0,   31,  20,  -3,  83,
                                    -149, 24,  102, -120, -4,  145, -159, 16,  231, 30,  1,   271, 20,  -1,
                                    1,    900, 0,   51,   900, -2,  94,   821, 23,  113, 840, -6,  160, 815,
                                    34,   211, 900, 1,    271, 900, 0,    1,   20,  0,   31,  20,  -3,  83,
                                    -149, 24,  102, -120, -4,  145, -159, 16,  231, 30,  1,   271, 20,  -1 };

cKF_Animation_R_c cKF_ba_r_obj_e_tukimi_r = { cKF_ckcb_r_obj_e_tukimi_r_tbl,
                                              cKF_ds_obj_e_tukimi_r_tbl,
                                              cKF_kn_obj_e_tukimi_r_tbl,
                                              cKF_c_obj_e_tukimi_r_tbl,
                                              -1,
                                              271 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_e_tukimi_l_t2_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_e_tukimi_l_t2_tex_txt[] = {
#include "assets/obj_e_tukimi_l_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_tukimi_l_t1_tex_txt[0x800];
#else
u8 obj_e_tukimi_l_t1_tex_txt[] = {
#include "assets/obj_e_tukimi_l_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_tukimi_l_t3_tex_txt[0x800];
#else
u8 obj_e_tukimi_l_t3_tex_txt[] = {
#include "assets/obj_e_tukimi_l_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_tukimi_l_v[0x480 / sizeof(Vtx)];
#else
Vtx obj_e_tukimi_l_v[] = {
#include "assets/obj_e_tukimi_l_v.inc"
};
#endif

Gfx obj_e_tukimi_l_ne2_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_l_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_tukimi_l_v[16], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_tukimi_l_ne1_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_l_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_tukimi_l_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_tukimi_l_moti_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_l_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_tukimi_l_v[4], 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 4, 2, 5),
    gsSPNTriangles_5b(4, 0, 2, 6, 7, 8, 6, 9, 7, 8, 10, 11),
    gsSPNTriangles_5b(8, 7, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_tukimi_l_hako_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_l_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_tukimi_l_v[20], 16, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 4, 7, 8, 7, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 10, 13, 14, 13, 15, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_tukimi_l_endai_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIM_LOD_FRAC, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_l_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_tukimi_l_v[36], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_tukimi_l_dai_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_l_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_tukimi_l_v[40], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_tukimi_l_kuki2_model[] = {
    gsSPMatrix(&anime_6_mdl[9], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_tukimi_l_v[67], 2, 0),
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_l_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_e_tukimi_l_v[69], 3, 2),
    gsSPNTrianglesInit_5b(2, 0, 2, 1, 0, 3, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_tukimi_l_ho2_model[] = {
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_tukimi_l_v[62], 2, 0),
    gsSPMatrix(&anime_6_mdl[4], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_l_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_e_tukimi_l_v[64], 3, 2),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_tukimi_l_kuki1_model[] = {
    gsSPMatrix(&anime_6_mdl[8], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_tukimi_l_v[57], 2, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_l_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_e_tukimi_l_v[59], 3, 2),
    gsSPNTrianglesInit_5b(2, 0, 2, 1, 0, 3, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_tukimi_l_ho1_model[] = {
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_tukimi_l_v[52], 2, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_tukimi_l_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_e_tukimi_l_v[54], 3, 2),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_e_tukimi_l_tbl[] = { { obj_e_tukimi_l_dai_model, 7, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 64220, 2800, 600 } },
                                                { obj_e_tukimi_l_kuki1_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { obj_e_tukimi_l_ho1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } },
                                                { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1200, 2800, 63636 } },
                                                { obj_e_tukimi_l_kuki2_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { obj_e_tukimi_l_ho2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } },
                                                { obj_e_tukimi_l_endai_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { obj_e_tukimi_l_hako_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { obj_e_tukimi_l_moti_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { obj_e_tukimi_l_ne1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { obj_e_tukimi_l_ne2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_e_tukimi_l = { ARRAY_COUNT(cKF_je_r_obj_e_tukimi_l_tbl), 10,
                                             cKF_je_r_obj_e_tukimi_l_tbl };

u8 cKF_ckcb_r_obj_e_tukimi_l_tbl[] = { 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_e_tukimi_l_tbl[] = { 7, 7, 7, 7 };

s16 cKF_c_obj_e_tukimi_l_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_e_tukimi_l_tbl[] = { 1,    900, 0,   51,   900, -2,  94,   821, 23,  113, 840, -6,  157, 812,
                                    20,   212, 901, 21,   271, 900, 0,    1,   20,  0,   31,  20,  -3,  83,
                                    -149, 24,  102, -120, -4,  145, -159, 16,  231, 30,  1,   271, 20,  -1,
                                    1,    900, 0,   51,   900, -2,  94,   821, 23,  113, 840, -6,  160, 815,
                                    34,   211, 900, 1,    271, 900, 0,    1,   20,  0,   31,  20,  -3,  83,
                                    -149, 24,  102, -120, -4,  145, -159, 16,  231, 30,  1,   271, 20,  -1 };

cKF_Animation_R_c cKF_ba_r_obj_e_tukimi_l = { cKF_ckcb_r_obj_e_tukimi_l_tbl,
                                              cKF_ds_obj_e_tukimi_l_tbl,
                                              cKF_kn_obj_e_tukimi_l_tbl,
                                              cKF_c_obj_e_tukimi_l_tbl,
                                              -1,
                                              271 };
