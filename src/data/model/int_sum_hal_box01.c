#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_hal_box01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_hal_box01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_hal_box01_pal[] = {
#include "assets/int_sum_hal_box01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_box01_pkin_tex_txt[0x200];
#else
u8 int_sum_hal_box01_pkin_tex_txt[] = {
#include "assets/int_sum_hal_box01_pkin_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_box01_kuki_tex_txt[0x80];
#else
u8 int_sum_hal_box01_kuki_tex_txt[] = {
#include "assets/int_sum_hal_box01_kuki_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_box01_bane_tex_txt[0x100];
#else
u8 int_sum_hal_box01_bane_tex_txt[] = {
#include "assets/int_sum_hal_box01_bane_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_box01_in_tex_txt[0x80];
#else
u8 int_sum_hal_box01_in_tex_txt[] = {
#include "assets/int_sum_hal_box01_in_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_box01_boxside_tex_txt[0x200];
#else
u8 int_sum_hal_box01_boxside_tex_txt[] = {
#include "assets/int_sum_hal_box01_boxside_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_box01_boxtop_tex_txt[0x80];
#else
u8 int_sum_hal_box01_boxtop_tex_txt[] = {
#include "assets/int_sum_hal_box01_boxtop_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_hal_box01_v[0x490 / sizeof(Vtx)];
#else
Vtx int_sum_hal_box01_v[] = {
#include "assets/int_sum_hal_box01_v.inc"
};
#endif

Gfx int_sum_hal_box01_bane_on_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_hal_box01_v, 1, 0),
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hal_box01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_hal_box01_bane_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hal_box01_v[1], 30, 1),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_hal_box01_pkin_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(5, 5, 6, 7, 8, 9, 7, 6, 8, 7),
    gsSPNTriangles_5b(10, 9, 8, 11, 8, 12, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 13, 14, 15, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 16, 17, 18, 19, 16, 18, 20, 21, 16),
    gsSPNTriangles_5b(22, 16, 21, 22, 23, 16, 22, 21, 24, 25, 23, 24),
    gsSPNTriangles_5b(26, 24, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 28, 29, 30, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_sum_hal_box01_v[31], 13, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 0, 2, 4, 5, 0),
    gsSPNTriangles_5b(5, 6, 1, 5, 1, 0, 7, 1, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_box01_kuki_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 11, 12, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_hal_box01_bane_off_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hal_box01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_box01_in_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hal_box01_v[44], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_hal_box01_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hal_box01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, int_sum_hal_box01_boxside_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hal_box01_v[48], 17, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_box01_boxtop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 15, 12, 14, 15, 16, 12),
    gsSPNTriangles_5b(16, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_hal_box01_top_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hal_box01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_box01_boxtop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hal_box01_v[65], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_hal_box01_tbl[] = { 0, 0, 0, 2, 2, 0 };

s16 cKF_kn_int_sum_hal_box01_tbl[] = { 7, 10 };

s16 cKF_c_int_sum_hal_box01_tbl[] = { 0, 875, -8675, -900, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_sum_hal_box01_tbl[] = { 1,   0,  -6791, 9,  -1100, 18,  43, -1100, -22,  54,   0,   9,   57,
                                       -40, 0,  59,    0,  -10,   65,  0,  0,     1,    275,  0,   7,   275,
                                       2,   11, 40,    -5, 15,    130, 0,  19,    40,   -922, 23,  110, 0,
                                       27,  50, -587,  31, 90,    0,   35, 60,    -343, 46,   275, 696 };

cKF_Animation_R_c cKF_ba_r_int_sum_hal_box01 = { cKF_ckcb_r_int_sum_hal_box01_tbl,
                                                 cKF_ds_int_sum_hal_box01_tbl,
                                                 cKF_kn_int_sum_hal_box01_tbl,
                                                 cKF_c_int_sum_hal_box01_tbl,
                                                 -1,
                                                 65 };

cKF_Joint_R_c cKF_je_r_int_sum_hal_box01_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 875, 56861 } },
    { int_sum_hal_box01_base_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 7425, 0, 1625 } },
    { int_sum_hal_box01_top_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_hal_box01_bane_off_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 300, 0, 0 } },
    { int_sum_hal_box01_bane_on_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_hal_box01 = { ARRAY_COUNT(cKF_je_r_int_sum_hal_box01_tbl), 4,
                                                cKF_je_r_int_sum_hal_box01_tbl };
