#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_station3_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 int_nog_station3_bese_tex_txt[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 int_nog_station3_bese_tex_txt[] = {
#include "assets/int_nog_station3_bese_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_station3_side_tex_txt[0x200];
#else
u8 int_nog_station3_side_tex_txt[] = {
#include "assets/int_nog_station3_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_station3_front_tex_txt[0x400];
#else
u8 int_nog_station3_front_tex_txt[] = {
#include "assets/int_nog_station3_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_station3_grass_tex_txt[0x80];
#else
u8 int_nog_station3_grass_tex_txt[] = {
#include "assets/int_nog_station3_grass_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_station3_v[0x940 / sizeof(Vtx)];
#else
Vtx int_nog_station3_v[] = {
#include "assets/int_nog_station3_v.inc"
};
#endif

Gfx int_nog_station3_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_nog_station3_bese_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_station3_v, 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_station3_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_nog_station3_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_station3_v[8], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 0, 3, 0, 2),
    gsSPNTriangles_5b(5, 6, 7, 8, 9, 10, 9, 11, 12, 13, 14, 15),
    gsSPNTriangles_5b(13, 15, 16, 13, 17, 18, 13, 18, 19, 13, 20, 21),
    gsSPNTriangles_5b(13, 21, 22, 13, 23, 24, 13, 24, 25, 26, 27, 28),
    gsSPNTriangles_5b(26, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_station3_v[38], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_nog_station3_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_nog_station3_v[50], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 2, 4, 3),
    gsSPNTriangles_5b(2, 5, 4, 5, 6, 4, 5, 7, 8, 5, 8, 6),
    gsSPNTriangles_5b(9, 10, 11, 9, 11, 12, 13, 14, 15, 13, 15, 16),
    gsSPNTriangles_5b(17, 18, 19, 17, 19, 20, 21, 22, 23, 21, 23, 24),
    gsSPNTriangles_5b(25, 26, 27, 25, 27, 28, 29, 30, 31, 0, 0, 0),
    gsSPVertex(&int_nog_station3_v[82], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 11, 12, 13, 12, 14, 13),
    gsSPNTriangles_5b(12, 15, 14, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_station3_grass_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&int_nog_station3_v[114], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_nog_station3_bese_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsSPVertex(&int_nog_station3_v[118], 30, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_station3_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_nog_station3_bese_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_station3_v[3], 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_nog_station3_tbl[] = { 0, 0, 0, 0, 0 };

s16 cKF_c_int_nog_station3_tbl[] = { 3750, 125, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_int_nog_station3 = { cKF_ckcb_r_int_nog_station3_tbl, NULL, NULL,
                                                cKF_c_int_nog_station3_tbl,      -1,   100 };

cKF_Joint_R_c cKF_je_r_int_nog_station3_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 3750, 125, 0 } },
    { int_nog_station3_body_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 3375, 0, 0 } },
    { int_nog_station3_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_nog_station3_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 3375, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_nog_station3 = { ARRAY_COUNT(cKF_je_r_int_nog_station3_tbl), 3,
                                               cKF_je_r_int_nog_station3_tbl };
