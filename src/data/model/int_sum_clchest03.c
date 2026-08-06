#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_clchest03_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_clchest03_pal01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_clchest03_pal01_pal[] = {
#include "assets/int_sum_clchest03_pal01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clchest03_hiki_txt[0x100];
#else
u8 int_sum_clchest03_hiki_txt[] = {
#include "assets/int_sum_clchest03_hiki_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clchest03_hikiura_txt[0x100];
#else
u8 int_sum_clchest03_hikiura_txt[] = {
#include "assets/int_sum_clchest03_hikiura_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clchest03_top_txt[0x100];
#else
u8 int_sum_clchest03_top_txt[] = {
#include "assets/int_sum_clchest03_top_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clchest03_stand_txt[0x80];
#else
u8 int_sum_clchest03_stand_txt[] = {
#include "assets/int_sum_clchest03_stand_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clchest03_front_txt[0x180];
#else
u8 int_sum_clchest03_front_txt[] = {
#include "assets/int_sum_clchest03_front_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clchest03_side_txt[0x180];
#else
u8 int_sum_clchest03_side_txt[] = {
#include "assets/int_sum_clchest03_side_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clchest03_hisasi_txt[0x80];
#else
u8 int_sum_clchest03_hisasi_txt[] = {
#include "assets/int_sum_clchest03_hisasi_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_clchest03_v[0x480 / sizeof(Vtx)];
#else
Vtx int_sum_clchest03_v[] = {
#include "assets/int_sum_clchest03_v.inc"
};
#endif

Gfx int_sum_clchest03_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_clchest03_pal01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_clchest03_hiki_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_clchest03_v, 20, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_clchest03_hikiura_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_clchest03_top_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(6, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_clchest03_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_clchest03_pal01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_clchest03_stand_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_clchest03_v[20], 24, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_clchest03_top_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 19, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_clchest03_front_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_clchest03_side_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_clchest03_v[44], 28, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_clchest03_hisasi_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_clchest03_tbl[] = { 56, 0, 7 };

s16 cKF_kn_int_sum_clchest03_tbl[] = { 2, 2, 2, 2, 2, 5 };

s16 cKF_c_int_sum_clchest03_tbl[] = { -900, 0, 0, 0, 0, -900 };

s16 cKF_ds_int_sum_clchest03_tbl[] = { 1,  1225, 0, 16, 1225, 0, 1,  3625, 0,    16, 3625, 0,    1,  -175, 0,
                                       16, -175, 0, 1,  0,    0, 16, 0,    0,    1,  0,    0,    16, 0,    0,
                                       1,  -900, 0, 3,  -900, 0, 5,  -840, 1590, 9,  -500, 3027, 16, 50,   0 };

cKF_Animation_R_c cKF_ba_r_int_sum_clchest03 = { cKF_ckcb_r_int_sum_clchest03_tbl,
                                                 cKF_ds_int_sum_clchest03_tbl,
                                                 cKF_kn_int_sum_clchest03_tbl,
                                                 cKF_c_int_sum_clchest03_tbl,
                                                 -1,
                                                 16 };

cKF_Joint_R_c cKF_je_r_int_sum_clchest03_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1225, 3625, 65361 } },
    { int_sum_clchest03_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_clchest03_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1500, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_clchest03 = { ARRAY_COUNT(cKF_je_r_int_sum_clchest03_tbl), 2,
                                                cKF_je_r_int_sum_clchest03_tbl };
