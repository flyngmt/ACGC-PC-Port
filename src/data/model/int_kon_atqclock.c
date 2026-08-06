#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_atqclock_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kon_atqclock_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kon_atqclock_pal[] = {
#include "assets/int_kon_atqclock_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_kon_atqclock_grass_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_kon_atqclock_grass_tex_pic_ci4_pal[] = {
#include "assets/int_kon_atqclock_grass_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_atqclock_f_tex_txt[0x100];
#else
u8 int_kon_atqclock_f_tex_txt[] = {
#include "assets/int_kon_atqclock_f_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_atqclock_c_tex_txt[0x80];
#else
u8 int_kon_atqclock_c_tex_txt[] = {
#include "assets/int_kon_atqclock_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_atqclock_a_tex_txt[0x100];
#else
u8 int_kon_atqclock_a_tex_txt[] = {
#include "assets/int_kon_atqclock_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_atqclock_e_tex_txt[0x80];
#else
u8 int_kon_atqclock_e_tex_txt[] = {
#include "assets/int_kon_atqclock_e_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_atqclock_d_tex_txt[0x80];
#else
u8 int_kon_atqclock_d_tex_txt[] = {
#include "assets/int_kon_atqclock_d_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_atqclock_b_tex_txt[0x200];
#else
u8 int_kon_atqclock_b_tex_txt[] = {
#include "assets/int_kon_atqclock_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_atqclock_h_tex_txt[0x80];
#else
u8 int_kon_atqclock_h_tex_txt[] = {
#include "assets/int_kon_atqclock_h_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_atqclock_g_tex_txt[0x100];
#else
u8 int_kon_atqclock_g_tex_txt[] = {
#include "assets/int_kon_atqclock_g_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_atqclock_grass_tex_txt[0x80];
#else
u8 int_kon_atqclock_grass_tex_txt[] = {
#include "assets/int_kon_atqclock_grass_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_atqclock_v[0x430 / sizeof(Vtx)];
#else
Vtx int_kon_atqclock_v[] = {
#include "assets/int_kon_atqclock_v.inc"
};
#endif

Gfx int_kon_atqclock_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_atqclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_atqclock_f_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_atqclock_v, 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_atqclock_evw_model[] = {
    gsSPTexture(5000, 5000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIM_LOD_FRAC, PRIMITIVE, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 40, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_atqclock_grass_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_atqclock_grass_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 2, 2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_atqclock_v[49], 12, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_atqclock_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_atqclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_atqclock_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_atqclock_v[3], 31, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_atqclock_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_atqclock_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 11, 12, 9, 13, 14, 12),
    gsSPNTriangles_5b(15, 16, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_atqclock_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(2, 17, 18, 19, 17, 19, 20, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_atqclock_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(8, 21, 22, 23, 21, 23, 24, 25, 26, 27),
    gsSPNTriangles_5b(25, 27, 28, 29, 25, 28, 29, 28, 30, 26, 21, 24),
    gsSPNTriangles_5b(26, 24, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_kon_atqclock_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 252),
    gsSPVertex(&int_kon_atqclock_v[34], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 4, 6, 7, 4, 7, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_atqclock_h_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_atqclock_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_atqclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_atqclock_f_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_atqclock_v[46], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_atqclock_huriko_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_atqclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_atqclock_g_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_atqclock_v[61], 6, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_kon_atqclock_tbl[] = { 0, 0, 0, 1, 0, 0, 0, 0 };

s16 cKF_kn_int_kon_atqclock_tbl[] = { 6 };

s16 cKF_c_int_kon_atqclock_tbl[] = { 0, 4900, 0, 0, 0, 900, 0, 0, 0, 0, 0, -1800, 0,
                                     0, 0,    0, 0, 0, 0,   0, 0, 0, 0, 0, 0,     0 };

s16 cKF_ds_int_kon_atqclock_tbl[] = { 1, 0, 381, 20, 110, -266, 25, 56, -317, 40, -91, -283, 46, -122, 6, 61, 0, 349 };

cKF_Animation_R_c cKF_ba_r_int_kon_atqclock = { cKF_ckcb_r_int_kon_atqclock_tbl,
                                                cKF_ds_int_kon_atqclock_tbl,
                                                cKF_kn_int_kon_atqclock_tbl,
                                                cKF_c_int_kon_atqclock_tbl,
                                                -1,
                                                61 };

cKF_Joint_R_c cKF_je_r_int_kon_atqclock_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 4900, 0 } },
    { int_kon_atqclock_base_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 65136, 0, 0 } },
    { int_kon_atqclock_huriko_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } },
    { int_kon_atqclock_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_kon_atqclock_evw_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_kon_atqclock_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_kon_atqclock = { ARRAY_COUNT(cKF_je_r_int_kon_atqclock_tbl), 5,
                                               cKF_je_r_int_kon_atqclock_tbl };
