#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_hachi_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_hachi_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_hachi_pal[] = {
#include "assets/int_sum_hachi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_sum_hachi_hand_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_sum_hachi_hand_pic_ci4_pal[] = {
#include "assets/int_sum_hachi_hand_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hachi_base_txt[0x80];
#else
u8 int_sum_hachi_base_txt[] = {
#include "assets/int_sum_hachi_base_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hachi_top_txt[0x200];
#else
u8 int_sum_hachi_top_txt[] = {
#include "assets/int_sum_hachi_top_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hachi_body_txt[0x100];
#else
u8 int_sum_hachi_body_txt[] = {
#include "assets/int_sum_hachi_body_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hachi_side_txt[0x200];
#else
u8 int_sum_hachi_side_txt[] = {
#include "assets/int_sum_hachi_side_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hachi_hane_txt[0x100];
#else
u8 int_sum_hachi_hane_txt[] = {
#include "assets/int_sum_hachi_hane_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hachi_hand_txt[0x100];
#else
u8 int_sum_hachi_hand_txt[] = {
#include "assets/int_sum_hachi_hand_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_hachi_v[0x440 / sizeof(Vtx)];
#else
Vtx int_sum_hachi_v[] = {
#include "assets/int_sum_hachi_v.inc"
};
#endif

Gfx int_sum_hachi_side_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 140),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hachi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_hachi_side_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hachi_v[32], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_hachi_komado_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 140),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hachi_hand_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_hachi_hand_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 3),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hachi_v[48], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_hachi_glass_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 70),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hachi_hand_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_hachi_hand_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 5),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hachi_v[52], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 7, 6, 1, 7, 1, 0, 4, 8, 9),
    gsSPNTriangles_5b(4, 9, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_hachi_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hachi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hachi_base_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_hachi_v, 24, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_hachi_top_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 4, 5, 6, 4, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_hachi_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hachi_v[24], 8, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 1, 0),
    gsSPNTriangles_5b(5, 4, 0, 6, 0, 3, 5, 0, 6, 6, 3, 7),
    gsSPNTriangles_5b(6, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_hachi_body_R_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 200),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hachi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_hachi_hane_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hachi_v[62], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_hachi_body_L_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 200),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hachi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_hachi_hane_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hachi_v[65], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_hachi_tbl[] = { 7, 0, 7, 0, 7, 0, 0, 0 };

s16 cKF_kn_int_sum_hachi_tbl[] = { 2, 2, 2, 2, 3, 2, 2, 3, 2 };

s16 cKF_c_int_sum_hachi_tbl[] = { 0, 0, 0, 0, 250, 1800, 0, 250, 1800, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_sum_hachi_tbl[] = { 1, 0, 0, 3, 0, 0, 1, 0, 0,    3,   0, 0, 1, 0, 0, 3, 0, 0, 1, 0,
                                   0, 3, 0, 0, 1, 0, 0, 2, -100, 0,   3, 0, 0, 1, 0, 0, 3, 0, 0, 1,
                                   0, 0, 3, 0, 0, 1, 0, 0, 2,    100, 0, 3, 0, 0, 1, 0, 0, 3, 0, 0 };

cKF_Animation_R_c cKF_ba_r_int_sum_hachi = {
    cKF_ckcb_r_int_sum_hachi_tbl, cKF_ds_int_sum_hachi_tbl, cKF_kn_int_sum_hachi_tbl, cKF_c_int_sum_hachi_tbl, -1, 3
};

cKF_Joint_R_c cKF_je_r_int_sum_hachi_tbl[] = { { int_sum_hachi_base_model, 5, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                               { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                               { int_sum_hachi_body_L_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                               { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                               { int_sum_hachi_body_R_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                               { int_sum_hachi_glass_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                               { int_sum_hachi_komado_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                               { int_sum_hachi_side_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_sum_hachi = { ARRAY_COUNT(cKF_je_r_int_sum_hachi_tbl), 6, cKF_je_r_int_sum_hachi_tbl };
