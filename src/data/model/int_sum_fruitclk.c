#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_fruitclk_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_fruitclk_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_fruitclk_pal[] = {
#include "assets/int_sum_fruitclk_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruitclk_hari_tex_txt[0x100];
#else
u8 int_sum_fruitclk_hari_tex_txt[] = {
#include "assets/int_sum_fruitclk_hari_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruitclk_body_tex_txt[0x200];
#else
u8 int_sum_fruitclk_body_tex_txt[] = {
#include "assets/int_sum_fruitclk_body_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruitclk_front_tex_txt[0x300];
#else
u8 int_sum_fruitclk_front_tex_txt[] = {
#include "assets/int_sum_fruitclk_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruitclk_antena_tex_txt[0x80];
#else
u8 int_sum_fruitclk_antena_tex_txt[] = {
#include "assets/int_sum_fruitclk_antena_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruitclk_ha_tex_txt[0x80];
#else
u8 int_sum_fruitclk_ha_tex_txt[] = {
#include "assets/int_sum_fruitclk_ha_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_fruitclk_v[0x270 / sizeof(Vtx)];
#else
Vtx int_sum_fruitclk_v[] = {
#include "assets/int_sum_fruitclk_v.inc"
};
#endif

Gfx int_sum_fruitclk_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_fruitclk_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_fruitclk_hari_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_fruitclk_v, 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_fruitclk_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_fruitclk_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_fruitclk_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_fruitclk_v[6], 29, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 2, 3, 4, 5, 6, 0),
    gsSPNTriangles_5b(6, 1, 0, 7, 6, 5, 8, 9, 10, 11, 9, 8),
    gsSPNTriangles_5b(11, 12, 9, 13, 14, 15, 15, 12, 11, 8, 16, 17),
    gsSPNTriangles_5b(8, 10, 16, 16, 5, 17, 16, 7, 5, 13, 15, 11),
    gsSPNTriangles_5b(0, 2, 4, 13, 11, 18, 18, 0, 4, 4, 19, 13),
    gsSPNTriangles_5b(18, 4, 13, 11, 8, 17, 17, 18, 11, 17, 0, 18),
    gsSPNTriangles_5b(17, 5, 0, 13, 19, 14, 19, 4, 3, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, int_sum_fruitclk_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_fruitclk_antena_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 27, 28, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_fruitclk_ha_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_fruitclk_v[35], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_fruitclk_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_fruitclk_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_fruitclk_hari_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_fruitclk_v[3], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_fruitclk_tbl[] = { 0, 0, 0, 0, 0 };

s16 cKF_c_int_sum_fruitclk_tbl[] = { 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_int_sum_fruitclk = { cKF_ckcb_r_int_sum_fruitclk_tbl, NULL, NULL,
                                                cKF_c_int_sum_fruitclk_tbl,      -1,   61 };

cKF_Joint_R_c cKF_je_r_int_sum_fruitclk_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_fruitclk_base_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1550, 0, 0 } },
    { int_sum_fruitclk_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_fruitclk_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1550, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_fruitclk = { ARRAY_COUNT(cKF_je_r_int_sum_fruitclk_tbl), 3,
                                               cKF_je_r_int_sum_fruitclk_tbl };
