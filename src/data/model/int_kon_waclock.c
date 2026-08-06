#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_waclock_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kon_waclock_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kon_waclock_pal[] = {
#include "assets/int_kon_waclock_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_waclock_g_tex_txt[0x100];
#else
u8 int_kon_waclock_g_tex_txt[] = {
#include "assets/int_kon_waclock_g_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_waclock_f_tex_txt[0x100];
#else
u8 int_kon_waclock_f_tex_txt[] = {
#include "assets/int_kon_waclock_f_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_waclock_e_tex_txt[0x80];
#else
u8 int_kon_waclock_e_tex_txt[] = {
#include "assets/int_kon_waclock_e_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_waclock_d_tex_txt[0x100];
#else
u8 int_kon_waclock_d_tex_txt[] = {
#include "assets/int_kon_waclock_d_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_waclock_h_tex_txt[0x80];
#else
u8 int_kon_waclock_h_tex_txt[] = {
#include "assets/int_kon_waclock_h_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_waclock_b_tex_txt[0x100];
#else
u8 int_kon_waclock_b_tex_txt[] = {
#include "assets/int_kon_waclock_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_waclock_c_tex_txt[0x80];
#else
u8 int_kon_waclock_c_tex_txt[] = {
#include "assets/int_kon_waclock_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_waclock_a_tex_txt[0x200];
#else
u8 int_kon_waclock_a_tex_txt[] = {
#include "assets/int_kon_waclock_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_waclock_v[0x340 / sizeof(Vtx)];
#else
Vtx int_kon_waclock_v[] = {
#include "assets/int_kon_waclock_v.inc"
};
#endif

Gfx int_kon_waclock_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_waclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_waclock_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_waclock_v[17], 31, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_waclock_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 5, 6, 7, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_waclock_h_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 11, 8, 12, 13, 11, 14),
    gsSPNTriangles_5b(15, 13, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_waclock_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(8, 17, 18, 19, 17, 19, 20, 21, 22, 18),
    gsSPNTriangles_5b(21, 18, 17, 23, 24, 22, 23, 22, 21, 25, 26, 24),
    gsSPNTriangles_5b(25, 24, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_waclock_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(2, 27, 28, 29, 27, 29, 30, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kon_waclock_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsSPVertex(&int_kon_waclock_v[48], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_waclock_huriko_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_waclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_kon_waclock_f_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_waclock_v[3], 14, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_waclock_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 11, 12, 13, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_waclock_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_waclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_waclock_g_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_waclock_v, 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_kon_waclock_tbl[] = { 0, 0, 0, 0, 2 };

s16 cKF_kn_int_kon_waclock_tbl[] = { 14 };

s16 cKF_c_int_kon_waclock_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_kon_waclock_tbl[] = { 1,    0,     5045, 6,   862,   5300, 20,    3334,  5019, 22,    3658,
                                     4546, 41,    4800, 10,  56,    4206, -3203, 60,    3671, -4890, 62,
                                     3320, -5447, 80,   140, -4290, 86,   -617,  -3301, 100,  -1496, -246,
                                     103,  -1491, 276,  120, -180,  5181, 121,   0,     5399 };

cKF_Animation_R_c cKF_ba_r_int_kon_waclock = { cKF_ckcb_r_int_kon_waclock_tbl,
                                               cKF_ds_int_kon_waclock_tbl,
                                               cKF_kn_int_kon_waclock_tbl,
                                               cKF_c_int_kon_waclock_tbl,
                                               -1,
                                               121 };

cKF_Joint_R_c cKF_je_r_int_kon_waclock_tbl[] = {
    { int_kon_waclock_base_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 2000, 0 } },
    { int_kon_waclock_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 3500, 0 } },
    { int_kon_waclock_huriko_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_kon_waclock = { ARRAY_COUNT(cKF_je_r_int_kon_waclock_tbl), 3,
                                              cKF_je_r_int_kon_waclock_tbl };
