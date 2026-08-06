#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_kisha_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_kisha_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_kisha_pal[] = {
#include "assets/int_sum_kisha_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kisha_kishafront_tex_txt[0x100];
#else
u8 int_sum_kisha_kishafront_tex_txt[] = {
#include "assets/int_sum_kisha_kishafront_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kisha_kishaside_tex_txt[0x100];
#else
u8 int_sum_kisha_kishaside_tex_txt[] = {
#include "assets/int_sum_kisha_kishaside_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kisha_kishatop_tex_txt[0x100];
#else
u8 int_sum_kisha_kishatop_tex_txt[] = {
#include "assets/int_sum_kisha_kishatop_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kisha_nidai_tex_txt[0x100];
#else
u8 int_sum_kisha_nidai_tex_txt[] = {
#include "assets/int_sum_kisha_nidai_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kisha_top_tex_txt[0x200];
#else
u8 int_sum_kisha_top_tex_txt[] = {
#include "assets/int_sum_kisha_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kisha_yama_tex_txt[0x200];
#else
u8 int_sum_kisha_yama_tex_txt[] = {
#include "assets/int_sum_kisha_yama_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_kisha_v[0x6F0 / sizeof(Vtx)];
#else
Vtx int_sum_kisha_v[] = {
#include "assets/int_sum_kisha_v.inc"
};
#endif

Gfx int_sum_kisha_kisha_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_kisha_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_kisha_kishafront_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_kisha_v, 29, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_kisha_kishaside_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(6, 16, 17, 18, 17, 19, 20, 17, 20, 18),
    gsSPNTriangles_5b(19, 21, 22, 19, 22, 20, 16, 18, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_kisha_kishatop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 27, 28, 24, 0, 0, 0),
    gsSPVertex(&int_sum_kisha_v[29], 22, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_kisha_nidai_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 252),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(10, 4, 5, 6, 4, 7, 5, 8, 6, 9),
    gsSPNTriangles_5b(8, 4, 6, 10, 11, 12, 10, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(15, 18, 19, 8, 20, 21, 8, 9, 20, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_kisha_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_kisha_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_kisha_kishafront_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_kisha_v[51], 20, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 7, 10, 11, 12, 13, 14, 12, 15, 16, 17),
    gsSPNTriangles_5b(15, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_kisha_kishatop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&int_sum_kisha_v[71], 31, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 3, 1, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 6, 9, 10, 11, 12, 13, 14, 15, 16, 14, 17),
    gsSPNTriangles_5b(18, 19, 20, 21, 19, 22, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_kisha_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 23, 24, 25, 23, 26, 24, 27, 28, 29),
    gsSPNTriangles_5b(27, 29, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_kisha_yama_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsSPVertex(&int_sum_kisha_v[102], 9, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 4, 5, 3, 6, 4),
    gsSPNTriangles_5b(2, 7, 6, 0, 8, 1, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_kisha_tbl[] = { 0, 0, 1 };

s16 cKF_kn_int_sum_kisha_tbl[] = { 2 };

s16 cKF_c_int_sum_kisha_tbl[] = { 0, 0, 500, -900, 0, 0, 0, 0, 900, 0, 0 };

s16 cKF_ds_int_sum_kisha_tbl[] = { 1, -900, 563, 193, 2700, 563 };

cKF_Animation_R_c cKF_ba_r_int_sum_kisha = {
    cKF_ckcb_r_int_sum_kisha_tbl, cKF_ds_int_sum_kisha_tbl, cKF_kn_int_sum_kisha_tbl, cKF_c_int_sum_kisha_tbl, -1, 193
};

cKF_Joint_R_c cKF_je_r_int_sum_kisha_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 500 } },
    { int_sum_kisha_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_kisha_kisha_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_kisha = { ARRAY_COUNT(cKF_je_r_int_sum_kisha_tbl), 2, cKF_je_r_int_sum_kisha_tbl };
