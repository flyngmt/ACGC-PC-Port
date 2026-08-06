#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_x_clk_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_x_clk_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_x_clk_pal[] = {
#include "assets/int_sum_x_clk_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_sum_x_clk_glass_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_sum_x_clk_glass_pic_ci4_pal[] = {
#include "assets/int_sum_x_clk_glass_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_clk_hari_txt[0x100];
#else
u8 int_sum_x_clk_hari_txt[] = {
#include "assets/int_sum_x_clk_hari_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_clk_into_txt[0x80];
#else
u8 int_sum_x_clk_into_txt[] = {
#include "assets/int_sum_x_clk_into_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_clk_front_txt[0x280];
#else
u8 int_sum_x_clk_front_txt[] = {
#include "assets/int_sum_x_clk_front_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_clk_head_txt[0x80];
#else
u8 int_sum_x_clk_head_txt[] = {
#include "assets/int_sum_x_clk_head_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_clk_side_txt[0x200];
#else
u8 int_sum_x_clk_side_txt[] = {
#include "assets/int_sum_x_clk_side_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_clk_huriko_txt[0x80];
#else
u8 int_sum_x_clk_huriko_txt[] = {
#include "assets/int_sum_x_clk_huriko_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_clk_glass_txt[0x80];
#else
u8 int_sum_x_clk_glass_txt[] = {
#include "assets/int_sum_x_clk_glass_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_x_clk_v[0x420 / sizeof(Vtx)];
#else
Vtx int_sum_x_clk_v[] = {
#include "assets/int_sum_x_clk_v.inc"
};
#endif

Gfx int_sum_x_clk_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_x_clk_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_x_clk_hari_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_x_clk_v, 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_x_clk_evw_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_x_clk_glass_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_x_clk_glass_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_x_clk_v[54], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_x_clk_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_x_clk_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_x_clk_into_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_x_clk_v[3], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 80, int_sum_x_clk_front_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_x_clk_v[19], 22, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 3, 1, 1, 4, 2),
    gsSPNTriangles_5b(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_x_clk_head_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 17, 18, 19, 17, 20, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_x_clk_side_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_x_clk_v[41], 13, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 5, 8, 6, 9, 10, 11, 9, 12, 10),
    gsSPEndDisplayList(),
};

Gfx int_sum_x_clk_huriko_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_x_clk_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_x_clk_huriko_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_x_clk_v[58], 5, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_x_clk_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_x_clk_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_x_clk_hari_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_x_clk_v[63], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_x_clk_tbl[] = { 0, 0, 0, 0, 0, 1, 0, 0 };

s16 cKF_kn_int_sum_x_clk_tbl[] = { 5 };

s16 cKF_c_int_sum_x_clk_tbl[] = { 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1800, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_sum_x_clk_tbl[] = { 1, -100, 20, 10, -57, 252, 32, 99, -38, 60, -99, -38, 61, -100, -20 };

cKF_Animation_R_c cKF_ba_r_int_sum_x_clk = {
    cKF_ckcb_r_int_sum_x_clk_tbl, cKF_ds_int_sum_x_clk_tbl, cKF_kn_int_sum_x_clk_tbl, cKF_c_int_sum_x_clk_tbl, -1, 61
};

cKF_Joint_R_c cKF_je_r_int_sum_x_clk_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_x_clk_base_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 5925, 0, 0 } },
    { int_sum_x_clk_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 4900, 0, 0 } },
    { int_sum_x_clk_huriko_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_x_clk_evw_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_sum_x_clk_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 5925, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_x_clk = { ARRAY_COUNT(cKF_je_r_int_sum_x_clk_tbl), 5, cKF_je_r_int_sum_x_clk_tbl };
