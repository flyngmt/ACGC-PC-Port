#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_jny_rosia01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_rosia01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_rosia01_pal[] = {
#include "assets/int_ike_jny_rosia01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_rosiabase1_tex_txt[0x100];
#else
u8 int_ike_jny_rosiabase1_tex_txt[] = {
#include "assets/int_ike_jny_rosiabase1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_rosia01_tex_txt[0x300];
#else
u8 int_ike_jny_rosia01_tex_txt[] = {
#include "assets/int_ike_jny_rosia01_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_jny_rosia01_v[0x570 / sizeof(Vtx)];
#else
Vtx int_ike_jny_rosia01_v[] = {
#include "assets/int_ike_jny_rosia01_v.inc"
};
#endif

Gfx int_ike_jny_rosia01_lb_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_rosia01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_jny_rosiabase1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_jny_rosia01_v, 25, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 6, 5, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_ike_jny_rosia01_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 8, 9, 10, 11, 12, 13, 13, 10, 11),
    gsSPNTriangles_5b(14, 15, 16, 17, 16, 18, 16, 17, 14, 19, 18, 9),
    gsSPNTriangles_5b(9, 8, 19, 10, 13, 8, 18, 19, 17, 0, 0, 0),
    gsSPNTrianglesInit_5b(3, 20, 21, 22, 20, 22, 23, 20, 23, 24),
    gsSPEndDisplayList(),
};

Gfx int_ike_jny_rosia01_l_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_rosia01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_ike_jny_rosia01_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_jny_rosia01_v[25], 13, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(1, 8, 2, 9, 6, 1, 4, 10, 11, 11, 5, 4),
    gsSPNTriangles_5b(10, 4, 2, 8, 1, 6, 1, 0, 9, 5, 12, 3),
    gsSPNTriangles_5b(4, 3, 2, 3, 0, 2, 0, 3, 12, 12, 9, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_jny_rosia01_2mb_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_rosia01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_ike_jny_rosia01_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_jny_rosia01_v[38], 17, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 4, 5, 5, 2, 3),
    gsSPNTriangles_5b(6, 7, 8, 9, 8, 10, 8, 9, 6, 11, 10, 1),
    gsSPNTriangles_5b(1, 0, 11, 2, 5, 0, 10, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 12, 15, 16, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_jny_rosia01_2sb_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_rosia01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_ike_jny_rosia01_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_jny_rosia01_v[55], 19, 0),
    gsSPNTrianglesInit_5b(25, 0, 1, 2, 3, 4, 5, 5, 4, 6),
    gsSPNTriangles_5b(1, 6, 2, 7, 5, 1, 8, 9, 10, 10, 9, 11),
    gsSPNTriangles_5b(12, 11, 2, 13, 5, 7, 14, 15, 9, 9, 15, 16),
    gsSPNTriangles_5b(11, 16, 2, 16, 0, 2, 17, 7, 15, 15, 7, 0),
    gsSPNTriangles_5b(0, 16, 15, 1, 0, 7, 6, 1, 5, 11, 12, 10),
    gsSPNTriangles_5b(16, 11, 9, 15, 14, 17, 9, 8, 14, 10, 18, 8),
    gsSPNTriangles_5b(5, 13, 3, 7, 17, 13, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_jny_rosia01_m_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_rosia01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_ike_jny_rosia01_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_jny_rosia01_v[74], 13, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(1, 8, 2, 9, 6, 1, 4, 10, 11, 11, 5, 4),
    gsSPNTriangles_5b(10, 4, 2, 8, 1, 6, 1, 0, 9, 5, 12, 3),
    gsSPNTriangles_5b(4, 3, 2, 3, 0, 2, 0, 3, 12, 12, 9, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_ike_jny_rosia01_tbl[] = { 0, 0, 0, 7, 7, 0, 7, 0, 7, 7, 7 };

s16 cKF_kn_int_ike_jny_rosia01_tbl[] = { 2, 2, 6, 4, 4, 6, 2, 2, 7, 2, 2, 6, 4, 4, 6, 2, 2, 7 };

s16 cKF_c_int_ike_jny_rosia01_tbl[] = { 0, 0, 0, 0, 0, 0, 0, -550, 0, 0, 550, 0, 0, -550, 1800, 0, 0, 1800 };

s16 cKF_ds_int_ike_jny_rosia01_tbl[] = {
    1,  0,    0,      46, 0,    0,    1,  0,    0,    46, 0,   0,     1,  1800, 0,     11, 1800, 25,    16, 1280, -6341,
    20, 0,    -11489, 22, 0,    0,    46, 0,    0,    1,  0,   0,     11, 0,    0,     20, 0,    0,     46, 0,    0,
    1,  0,    0,      11, 0,    0,    20, 0,    0,    46, 0,   0,     1,  0,    0,     11, 0,    -13,   16, 520,  6599,
    20, 1800, 10924,  22, 1800, 0,    46, 1800, 0,    1,  0,   0,     46, 0,    0,     1,  0,    0,     46, 0,    0,
    1,  0,    0,      20, 0,    -7,   27, 360,  4352, 29, 900, 698,   39, 710,  -1899, 44, 0,    -4992, 46, 0,    0,
    1,  0,    0,      46, 0,    0,    1,  0,    0,    46, 0,   0,     1,  1800, 0,     30, 1800, 20,    35, 1320, -6425,
    39, 0,    -9855,  41, 0,    0,    46, 0,    0,    1,  0,   0,     30, 0,    0,     39, 0,    0,     46, 0,    0,
    1,  0,    0,      30, 0,    0,    39, 0,    0,    46, 0,   0,     1,  0,    0,     30, 0,    -13,   35, 460,  6227,
    39, 1800, 9916,   41, 1800, 0,    46, 1800, 0,    1,  0,   0,     46, 0,    0,     1,  0,    0,     46, 0,    0,
    1,  0,    0,      8,  300,  3616, 10, 900,  857,  20, 680, -2258, 25, 0,    -5414, 27, 0,    0,     46, 0,    0
};

cKF_Animation_R_c cKF_ba_r_int_ike_jny_rosia01 = { cKF_ckcb_r_int_ike_jny_rosia01_tbl,
                                                   cKF_ds_int_ike_jny_rosia01_tbl,
                                                   cKF_kn_int_ike_jny_rosia01_tbl,
                                                   cKF_c_int_ike_jny_rosia01_tbl,
                                                   -1,
                                                   46 };

cKF_Joint_R_c cKF_je_r_int_ike_jny_rosia01_tbl[] = {
    { int_ike_jny_rosia01_lb_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, { 64906, 1348, 64636 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1832, 64414, 64489 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_ike_jny_rosia01_2mb_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 1269, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 567, 64651, 64771 } },
    { int_ike_jny_rosia01_m_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 64584, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_ike_jny_rosia01_2sb_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 952, 0, 0 } },
    { int_ike_jny_rosia01_l_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_ike_jny_rosia01 = { ARRAY_COUNT(cKF_je_r_int_ike_jny_rosia01_tbl), 5,
                                                  cKF_je_r_int_ike_jny_rosia01_tbl };
