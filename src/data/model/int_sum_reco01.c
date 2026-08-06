#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_reco01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_reco01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_reco01_pal[] = {
#include "assets/int_sum_reco01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_reco01_recotop_tex_txt[0x200];
#else
u8 int_sum_reco01_recotop_tex_txt[] = {
#include "assets/int_sum_reco01_recotop_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_reco01_front_tex_txt[0x400];
#else
u8 int_sum_reco01_front_tex_txt[] = {
#include "assets/int_sum_reco01_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_reco01_side_tex_txt[0x180];
#else
u8 int_sum_reco01_side_tex_txt[] = {
#include "assets/int_sum_reco01_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_reco01_v[0x240 / sizeof(Vtx)];
#else
Vtx int_sum_reco01_v[] = {
#include "assets/int_sum_reco01_v.inc"
};
#endif

Gfx int_sum_reco01_yellow_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_reco01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_reco01_recotop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_reco01_v, 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_reco01_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_reco01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_sum_reco01_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_reco01_v[8], 20, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_reco01_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_reco01_red_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_reco01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_reco01_recotop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_reco01_v[28], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_reco01_tbl[] = { 56, 7, 0, 7, 7 };

s16 cKF_kn_int_sum_reco01_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };

s16 cKF_c_int_sum_reco01_tbl[] = { 0, -900, 0, 0, 0, 0 };

s16 cKF_ds_int_sum_reco01_tbl[] = { 1, 1000, 0,    49, 1000, 0,    1, 2925, 0, 49, 2925, 0, 1, -100, 0, 49, -100, 0,
                                    1, 0,    0,    49, 0,    0,    1, 0,    0, 49, 0,    0, 1, 0,    0, 49, 0,    0,
                                    1, 0,    2257, 49, 3600, 2278, 1, 0,    0, 49, 0,    0, 1, 0,    0, 49, 0,    0,
                                    1, 0,    2226, 49, 3600, 2217, 1, 0,    0, 49, 0,    0, 1, 0,    0, 49, 0,    0 };

cKF_Animation_R_c cKF_ba_r_int_sum_reco01 = { cKF_ckcb_r_int_sum_reco01_tbl,
                                              cKF_ds_int_sum_reco01_tbl,
                                              cKF_kn_int_sum_reco01_tbl,
                                              cKF_c_int_sum_reco01_tbl,
                                              -1,
                                              49 };

cKF_Joint_R_c cKF_je_r_int_sum_reco01_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1000, 2925, 65436 } },
    { int_sum_reco01_base_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 100, 0, 2050 } },
    { int_sum_reco01_red_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_reco01_yellow_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 100, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_reco01 = { ARRAY_COUNT(cKF_je_r_int_sum_reco01_tbl), 3, cKF_je_r_int_sum_reco01_tbl };
