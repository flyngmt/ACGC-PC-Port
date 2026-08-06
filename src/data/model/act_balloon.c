#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 act_balloon_wire_tex_txt[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 act_balloon_wire_tex_txt[] = {
#include "assets/act_balloon_wire_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 act_balloon_head_tex_rgb_ia8[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 act_balloon_head_tex_rgb_ia8[] = {
#include "assets/act_balloon_head_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_balloon_v[0x340 / sizeof(Vtx)];
#else
Vtx act_balloon_v[] = {
#include "assets/act_balloon_v.inc"
};
#endif

Gfx act_balloon_head_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, act_balloon_head_tex_rgb_ia8),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH),
    gsSPVertex(act_balloon_v, 26, 0),
    gsSPNTrianglesInit_5b(36, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(5, 4, 3, 6, 5, 3, 7, 6, 3, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 11, 4, 10, 10, 4, 5, 12, 10, 5),
    gsSPNTriangles_5b(13, 12, 5, 14, 15, 11, 15, 16, 11, 16, 4, 11),
    gsSPNTriangles_5b(2, 4, 16, 17, 2, 16, 18, 17, 16, 19, 17, 18),
    gsSPNTriangles_5b(19, 20, 17, 19, 21, 20, 22, 21, 19, 22, 19, 15),
    gsSPNTriangles_5b(22, 15, 14, 23, 12, 13, 23, 24, 12, 23, 21, 24),
    gsSPNTriangles_5b(24, 21, 22, 24, 22, 9, 24, 9, 8, 25, 6, 7),
    gsSPNTriangles_5b(25, 23, 6, 25, 21, 23, 20, 21, 25, 20, 25, 1),
    gsSPNTriangles_5b(20, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList()
};

Gfx act_balloon_wireB_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, act_balloon_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&act_balloon_v[26], 4, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, act_balloon_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&act_balloon_v[30], 14, 4),
    gsSPNTrianglesInit_5b(4, 0, 1, 4, 1, 6, 5, 2, 3, 7),
    gsSPNTriangles_5b(3, 9, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 10, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList()
};

Gfx act_balloon_wireA_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, act_balloon_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&act_balloon_v[44], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList()
};

u8 cKF_ckcb_r_act_balloon_tbl[] = { 0, 3, 3, 3 };

s16 cKF_kn_act_balloon_tbl[] = { 5, 5, 5, 5, 4, 4 };

s16 cKF_c_act_balloon_tbl[] = { 0, 1500, 0, 0, 0, 900, 0, 0, 0 };

s16 cKF_ds_act_balloon_tbl[] = { 1,   -100, 20,   10,  -57,  252, 32,   99,   -38, 60,  -99, -38, 61,  -100,
                                 -20, 1,    100,  -20, 10,   57,  -252, 32,   -99, 38,  60,  99,  38,  61,
                                 100, 20,   1,    100, -20,  10,  57,   -252, 32,  -99, 38,  60,  99,  38,
                                 61,  100,  20,   1,   -100, 20,  10,   -57,  252, 32,  99,  -38, 60,  -99,
                                 -38, 61,   -100, -20, 1,    24,  130,  14,   47,  -54, 43,  -49, 37,  61,
                                 24,  136,  1,    -24, -130, 14,  -47,  54,   43,  49,  -37, 61,  -24, -136 };

cKF_Animation_R_c cKF_ba_r_act_balloon = {
    cKF_ckcb_r_act_balloon_tbl, cKF_ds_act_balloon_tbl, cKF_kn_act_balloon_tbl, cKF_c_act_balloon_tbl, -1, 61
};

cKF_Joint_R_c cKF_je_r_act_balloon_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 1500, 0 } },
                                             { act_balloon_wireA_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { act_balloon_wireB_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1250, 0, 0 } },
                                             { act_balloon_head_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1250, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_act_balloon = { ARRAY_COUNT(cKF_je_r_act_balloon_tbl), 3, cKF_je_r_act_balloon_tbl };
