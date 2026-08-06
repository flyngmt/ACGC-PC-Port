#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_bla_chest03_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_bla_chest03_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_bla_chest03_pal[] = {
#include "assets/int_sum_bla_chest03_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bla_chest03_hiki_tex_txt[0x200];
#else
u8 int_sum_bla_chest03_hiki_tex_txt[] = {
#include "assets/int_sum_bla_chest03_hiki_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bla_chest03_front_tex_txt[0x300];
#else
u8 int_sum_bla_chest03_front_tex_txt[] = {
#include "assets/int_sum_bla_chest03_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bla_chest03_side_tex_txt[0x200];
#else
u8 int_sum_bla_chest03_side_tex_txt[] = {
#include "assets/int_sum_bla_chest03_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_bla_chest03_v[0x420 / sizeof(Vtx)];
#else
Vtx int_sum_bla_chest03_v[] = {
#include "assets/int_sum_bla_chest03_v.inc"
};
#endif

Gfx int_sum_bla_chest03_doorL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bla_chest03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_bla_chest03_hiki_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_bla_chest03_v, 15, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPEndDisplayList(),
};

Gfx int_sum_bla_chest03_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bla_chest03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_bla_chest03_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_bla_chest03_v[30], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_bla_chest03_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_sum_bla_chest03_v[34], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_bla_chest03_doorR_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bla_chest03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_bla_chest03_hiki_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_bla_chest03_v[15], 15, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 11, 12, 13, 11, 13, 14),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_bla_chest03_tbl[] = { 56, 7, 0, 7, 7 };

s16 cKF_kn_int_sum_bla_chest03_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 3 };

s16 cKF_c_int_sum_bla_chest03_tbl[] = { -900, 0, 0, 0, 0, 900 };

s16 cKF_ds_int_sum_bla_chest03_tbl[] = { 1,    -1800, 0,  12,   -1800, 0,    1,  3625, 0,    12,    3625, 0,    1,
                                         100,  0,     12, 100,  0,     1,    0,  0,    12,   0,     0,    1,    0,
                                         0,    12,    0,  0,    1,     -900, 0,  12,   -900, 0,     1,    0,    0,
                                         12,   0,     0,  1,    0,     0,    12, 0,    0,    1,     1800, 0,    6,
                                         2250, 3785,  12, 2850, 0,     1,    0,  0,    12,   0,     0,    1,    0,
                                         0,    12,    0,  0,    1,     900,  0,  6,    450,  -3818, 12,   -150, 0 };

cKF_Animation_R_c cKF_ba_r_int_sum_bla_chest03 = { cKF_ckcb_r_int_sum_bla_chest03_tbl,
                                                   cKF_ds_int_sum_bla_chest03_tbl,
                                                   cKF_kn_int_sum_bla_chest03_tbl,
                                                   cKF_c_int_sum_bla_chest03_tbl,
                                                   -1,
                                                   12 };

cKF_Joint_R_c cKF_je_r_int_sum_bla_chest03_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 63736, 3625, 100 } },
    { int_sum_bla_chest03_base_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1500, 3600, 0 } },
    { int_sum_bla_chest03_doorR_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_bla_chest03_doorL_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1500, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_bla_chest03 = { ARRAY_COUNT(cKF_je_r_int_sum_bla_chest03_tbl), 3,
                                                  cKF_je_r_int_sum_bla_chest03_tbl };
