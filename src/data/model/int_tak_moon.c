#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_moon_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_moon_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_moon_pal[] = {
#include "assets/int_tak_moon_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_moon_tex_txt[0x800];
#else
u8 int_tak_moon_tex_txt[] = {
#include "assets/int_tak_moon_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_moon_v[0x390 / sizeof(Vtx)];
#else
Vtx int_tak_moon_v[] = {
#include "assets/int_tak_moon_v.inc"
};
#endif

Gfx int_tak_moon_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_moon_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, int_tak_moon_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_moon_v, 32, 0),
    gsSPNTrianglesInit_5b(44, 0, 1, 2, 1, 3, 2, 0, 4, 1),
    gsSPNTriangles_5b(4, 5, 1, 5, 3, 1, 6, 0, 7, 0, 2, 7),
    gsSPNTriangles_5b(2, 8, 7, 2, 9, 8, 2, 3, 9, 3, 10, 9),
    gsSPNTriangles_5b(6, 11, 0, 11, 4, 0, 11, 12, 4, 12, 13, 4),
    gsSPNTriangles_5b(13, 5, 4, 13, 14, 5, 14, 15, 5, 15, 3, 5),
    gsSPNTriangles_5b(15, 10, 3, 16, 7, 17, 7, 8, 17, 8, 18, 17),
    gsSPNTriangles_5b(8, 9, 18, 9, 19, 18, 9, 10, 19, 10, 20, 19),
    gsSPNTriangles_5b(10, 15, 20, 16, 6, 7, 16, 21, 6, 21, 11, 6),
    gsSPNTriangles_5b(21, 22, 11, 22, 12, 11, 22, 23, 12, 23, 13, 12),
    gsSPNTriangles_5b(23, 24, 13, 24, 14, 13, 24, 25, 14, 25, 15, 14),
    gsSPNTriangles_5b(25, 20, 15, 26, 27, 28, 29, 26, 28, 29, 28, 30),
    gsSPNTriangles_5b(31, 29, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_tak_moon_v[32], 25, 0),
    gsSPNTrianglesInit_5b(36, 0, 1, 2, 3, 0, 2, 3, 2, 4),
    gsSPNTriangles_5b(5, 3, 4, 5, 4, 6, 7, 5, 6, 7, 6, 8),
    gsSPNTriangles_5b(9, 7, 8, 10, 11, 12, 13, 10, 12, 13, 12, 14),
    gsSPNTriangles_5b(15, 13, 14, 15, 14, 16, 17, 15, 16, 17, 16, 9),
    gsSPNTriangles_5b(17, 9, 8, 18, 12, 11, 19, 18, 11, 19, 11, 20),
    gsSPNTriangles_5b(19, 20, 0, 21, 19, 0, 21, 0, 3, 21, 3, 5),
    gsSPNTriangles_5b(22, 21, 5, 22, 5, 7, 14, 12, 18, 14, 18, 23),
    gsSPNTriangles_5b(16, 14, 23, 9, 16, 23, 9, 23, 22, 9, 22, 7),
    gsSPNTriangles_5b(24, 18, 19, 24, 19, 21, 24, 21, 22, 23, 18, 24),
    gsSPNTriangles_5b(23, 24, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_tak_moon_tbl[] = { 0, 0 };

s16 cKF_c_int_tak_moon_tbl[] = { 0, 5000, 0, -900, 0, -80, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_int_tak_moon = { cKF_ckcb_r_int_tak_moon_tbl, NULL, NULL, cKF_c_int_tak_moon_tbl, -1, 100 };

cKF_Joint_R_c cKF_je_r_int_tak_moon_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 5000, 0 } },
                                              { int_tak_moon_on_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_tak_moon = { ARRAY_COUNT(cKF_je_r_int_tak_moon_tbl), 1, cKF_je_r_int_tak_moon_tbl };
