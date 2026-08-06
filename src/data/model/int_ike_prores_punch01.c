#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_prores_punch01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_prores_punch01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_prores_punch01_pal[] = {
#include "assets/int_ike_prores_punch01_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_ike_prores_punch01_punch1_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_ike_prores_punch01_punch1_tex_pic_ci4_pal[] = {
#include "assets/int_ike_prores_punch01_punch1_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_punch01_pole3_tex_txt[0x40];
#else
u8 int_ike_prores_punch01_pole3_tex_txt[] = {
#include "assets/int_ike_prores_punch01_pole3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_punch01_base2_tex_txt[0x100];
#else
u8 int_ike_prores_punch01_base2_tex_txt[] = {
#include "assets/int_ike_prores_punch01_base2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_punch01_pole2_tex_txt[0x80];
#else
u8 int_ike_prores_punch01_pole2_tex_txt[] = {
#include "assets/int_ike_prores_punch01_pole2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_punch01_pole1_tex_txt[0x80];
#else
u8 int_ike_prores_punch01_pole1_tex_txt[] = {
#include "assets/int_ike_prores_punch01_pole1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_punch01_base3_tex_txt[0x80];
#else
u8 int_ike_prores_punch01_base3_tex_txt[] = {
#include "assets/int_ike_prores_punch01_base3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_punch01_base1_tex_txt[0x200];
#else
u8 int_ike_prores_punch01_base1_tex_txt[] = {
#include "assets/int_ike_prores_punch01_base1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_punch01_pole4_tex_txt[0x40];
#else
u8 int_ike_prores_punch01_pole4_tex_txt[] = {
#include "assets/int_ike_prores_punch01_pole4_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_punch01_punch1_tex_txt[0x80];
#else
u8 int_ike_prores_punch01_punch1_tex_txt[] = {
#include "assets/int_ike_prores_punch01_punch1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_prores_punch01_v[0x3E0 / sizeof(Vtx)];
#else
Vtx int_ike_prores_punch01_v[] = {
#include "assets/int_ike_prores_punch01_v.inc"
};
#endif

Gfx int_ike_prores_punch_ball_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_prores_punch01_punch1_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_prores_punch01_punch1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 2, 2),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(int_ike_prores_punch01_v, 12, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 4, 2, 1, 5, 2),
    gsSPNTriangles_5b(6, 0, 2, 6, 2, 4, 5, 3, 2, 6, 7, 0),
    gsSPNTriangles_5b(6, 8, 7, 6, 4, 8, 9, 5, 10, 9, 3, 5),
    gsSPNTriangles_5b(5, 1, 10, 10, 1, 0, 10, 0, 7, 8, 4, 3),
    gsSPNTriangles_5b(8, 3, 9, 10, 11, 9, 10, 7, 11, 7, 8, 11),
    gsSPNTriangles_5b(8, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_prores_punch_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_prores_punch01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_prores_punch01_pole3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_prores_punch01_v[12], 30, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 1, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_prores_punch01_base2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 4, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(8, 11, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_prores_punch01_pole2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_prores_punch01_pole1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 19, 17, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_prores_punch01_base3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 27, 28, 29, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_prores_punch01_base1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_prores_punch01_v[42], 20, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_prores_punch01_pole3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_prores_punch01_pole4_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 19, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_ike_prores_punch01_tbl[] = { 0, 7 };

s16 cKF_kn_int_ike_prores_punch01_tbl[] = { 2, 11, 11 };

s16 cKF_c_int_ike_prores_punch01_tbl[] = { 800, 6508, 800, 0, 0, -900 };

s16 cKF_ds_int_ike_prores_punch01_tbl[] = { 1,  0,   0, 69, 0,    0, 1,  0,   0, 3,  -180, 0, 8,  200, 0, 13, -140, 0,
                                            19, 180, 0, 25, -120, 0, 31, 100, 0, 39, -70,  0, 47, 40,  1, 57, -30,  4,
                                            69, 0,   0, 1,  0,    0, 5,  32,  0, 10, -22,  0, 15, 28,  0, 21, -19,  0,
                                            27, 16,  0, 35, -11,  0, 43, 6,   0, 51, -5,   0, 57, 3,   0, 69, 0,    0 };

cKF_Animation_R_c cKF_ba_r_int_ike_prores_punch01 = { cKF_ckcb_r_int_ike_prores_punch01_tbl,
                                                      cKF_ds_int_ike_prores_punch01_tbl,
                                                      cKF_kn_int_ike_prores_punch01_tbl,
                                                      cKF_c_int_ike_prores_punch01_tbl,
                                                      -1,
                                                      69 };

cKF_Joint_R_c cKF_je_r_int_ike_prores_punch01_tbl[] = {
    { int_ike_prores_punch_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 800, 6508, 800 } },
    { int_ike_prores_punch_ball_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_ike_prores_punch01 = { ARRAY_COUNT(cKF_je_r_int_ike_prores_punch01_tbl), 2,
                                                     cKF_je_r_int_ike_prores_punch01_tbl };
