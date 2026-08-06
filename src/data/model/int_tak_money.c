#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_money_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_money_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_money_pal[] = {
#include "assets/int_tak_money_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_money_front_tex_txt[0x400];
#else
u8 int_tak_money_front_tex_txt[] = {
#include "assets/int_tak_money_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_money_side_tex_txt[0x200];
#else
u8 int_tak_money_side_tex_txt[] = {
#include "assets/int_tak_money_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_money_v[0x380 / sizeof(Vtx)];
#else
Vtx int_tak_money_v[] = {
#include "assets/int_tak_money_v.inc"
};
#endif

Gfx int_tak_money_side_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_money_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_tak_money_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_money_v[18], 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 3, 0, 2, 3, 2, 4),
    gsSPNTriangles_5b(5, 3, 4, 5, 4, 6, 7, 5, 6, 7, 6, 8),
    gsSPNTriangles_5b(9, 7, 8, 9, 8, 10, 11, 9, 10, 11, 10, 12),
    gsSPNTriangles_5b(13, 11, 12, 13, 12, 14, 15, 16, 17, 17, 13, 14),
    gsSPNTriangles_5b(15, 17, 14, 18, 19, 20, 19, 21, 20, 18, 22, 19),
    gsSPNTriangles_5b(21, 23, 20, 21, 24, 23, 24, 25, 23, 24, 26, 25),
    gsSPNTriangles_5b(26, 27, 25, 26, 28, 27, 28, 29, 27, 28, 30, 29),
    gsSPNTriangles_5b(30, 31, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_tak_money_v[50], 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(4, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_money_front_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_money_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_tak_money_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_money_v, 18, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(4, 5, 1, 5, 6, 1, 6, 7, 1, 7, 8, 1),
    gsSPNTriangles_5b(8, 2, 1, 9, 10, 11, 9, 12, 10, 12, 13, 10),
    gsSPNTriangles_5b(13, 14, 10, 14, 15, 10, 15, 16, 10, 16, 17, 10),
    gsSPNTriangles_5b(17, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_tak_money_tbl[] = { 0, 1, 0 };

s16 cKF_kn_int_tak_money_tbl[] = { 2 };

s16 cKF_c_int_tak_money_tbl[] = { 2000, 4000, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_tak_money_tbl[] = { 1, 0, 1091, 100, 3600, 1091 };

cKF_Animation_R_c cKF_ba_r_int_tak_money = {
    cKF_ckcb_r_int_tak_money_tbl, cKF_ds_int_tak_money_tbl, cKF_kn_int_tak_money_tbl, cKF_c_int_tak_money_tbl, -1, 100
};

cKF_Joint_R_c cKF_je_r_int_tak_money_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 4000, 0 } },
                                               { int_tak_money_front_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                               { int_tak_money_side_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_tak_money = { ARRAY_COUNT(cKF_je_r_int_tak_money_tbl), 2, cKF_je_r_int_tak_money_tbl };
