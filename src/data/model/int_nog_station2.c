#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_station2_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 int_nog_station2_bese_tex_txt[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 int_nog_station2_bese_tex_txt[] = {
#include "assets/int_nog_station2_bese_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_station2_grass_tex_txt[0x80];
#else
u8 int_nog_station2_grass_tex_txt[] = {
#include "assets/int_nog_station2_grass_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_station2_side_tex_txt[0x300];
#else
u8 int_nog_station2_side_tex_txt[] = {
#include "assets/int_nog_station2_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_station2_front_tex_txt[0x400];
#else
u8 int_nog_station2_front_tex_txt[] = {
#include "assets/int_nog_station2_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_station2_v[0x1090 / sizeof(Vtx)];
#else
Vtx int_nog_station2_v[] = {
#include "assets/int_nog_station2_v.inc"
};
#endif

Gfx int_nog_station2_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_nog_station2_bese_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_station2_v, 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_station2_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_station2_grass_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_station2_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 96, int_nog_station2_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_nog_station2_v[12], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_station2_v[44], 32, 0),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 11, 10, 12),
    gsSPNTriangles_5b(11, 12, 13, 13, 12, 14, 13, 14, 15, 15, 14, 16),
    gsSPNTriangles_5b(15, 16, 17, 9, 18, 10, 10, 19, 12, 12, 20, 14),
    gsSPNTriangles_5b(14, 21, 16, 22, 23, 24, 25, 26, 22, 27, 28, 25),
    gsSPNTriangles_5b(29, 30, 27, 31, 22, 24, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_station2_v[76], 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 3, 4, 5, 3, 5, 0),
    gsSPNTriangles_5b(6, 7, 4, 6, 4, 3, 8, 9, 7, 8, 7, 6),
    gsSPNTriangles_5b(10, 11, 12, 10, 12, 13, 13, 12, 14, 13, 14, 15),
    gsSPNTriangles_5b(15, 14, 16, 15, 16, 17, 17, 16, 18, 17, 18, 19),
    gsSPNTriangles_5b(11, 20, 12, 12, 21, 14, 14, 22, 16, 16, 23, 18),
    gsSPNTriangles_5b(24, 25, 26, 27, 28, 24, 29, 30, 27, 0, 0, 0),
    gsSPVertex(&int_nog_station2_v[107], 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 4, 7, 4, 3, 9, 2, 8, 9, 8, 7),
    gsSPNTriangles_5b(10, 0, 2, 10, 2, 9, 11, 12, 13, 11, 13, 14),
    gsSPNTriangles_5b(14, 13, 15, 14, 15, 16, 16, 15, 17, 16, 17, 18),
    gsSPNTriangles_5b(18, 17, 19, 18, 19, 20, 12, 21, 13, 13, 22, 15),
    gsSPNTriangles_5b(15, 23, 17, 17, 24, 19, 25, 26, 27, 28, 29, 25),
    gsSPNTriangles_5b(30, 31, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_station2_v[139], 20, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 4, 7, 4, 3, 9, 2, 8, 9, 8, 7),
    gsSPNTriangles_5b(10, 0, 2, 10, 2, 9, 11, 12, 13, 11, 13, 14),
    gsSPNTriangles_5b(13, 15, 16, 13, 16, 14, 12, 17, 18, 12, 18, 13),
    gsSPNTriangles_5b(18, 19, 15, 18, 15, 13, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_nog_station2_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_nog_station2_v[159], 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 9, 8, 10, 7, 11, 8, 6, 5, 12),
    gsSPNTriangles_5b(4, 13, 5, 14, 15, 16, 15, 17, 16, 14, 18, 15),
    gsSPNTriangles_5b(14, 19, 18, 17, 20, 16, 14, 21, 19, 14, 22, 21),
    gsSPNTriangles_5b(20, 23, 16, 23, 24, 16, 25, 26, 27, 25, 27, 28),
    gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_station2_v[191], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 0, 2),
    gsSPNTriangles_5b(7, 6, 2, 3, 5, 7, 3, 7, 2, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 23, 20, 22, 24, 25, 26),
    gsSPNTriangles_5b(25, 27, 26, 28, 29, 30, 28, 30, 31, 0, 0, 0),
    gsSPVertex(&int_nog_station2_v[223], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_nog_station2_bese_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsSPVertex(&int_nog_station2_v[235], 30, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_station2_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_nog_station2_bese_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_station2_v[3], 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 2, 4, 3),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_nog_station2_tbl[] = { 0, 0, 0, 0, 0 };

s16 cKF_c_int_nog_station2_tbl[] = { 3750, 125, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_int_nog_station2 = { cKF_ckcb_r_int_nog_station2_tbl, NULL, NULL,
                                                cKF_c_int_nog_station2_tbl,      -1,   100 };

cKF_Joint_R_c cKF_je_r_int_nog_station2_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 3750, 125, 0 } },
    { int_nog_station2_body_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 3000, 0, 0 } },
    { int_nog_station2_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_nog_station2_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 3000, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_nog_station2 = { ARRAY_COUNT(cKF_je_r_int_nog_station2_tbl), 3,
                                               cKF_je_r_int_nog_station2_tbl };
