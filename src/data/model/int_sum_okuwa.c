#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_okuwa_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_okuwa_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_okuwa_pal[] = {
#include "assets/int_sum_okuwa_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_sum_okuwa_hand_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_sum_okuwa_hand_pic_ci4_pal[] = {
#include "assets/int_sum_okuwa_hand_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_okuwa_body_txt[0x100];
#else
u8 int_sum_okuwa_body_txt[] = {
#include "assets/int_sum_okuwa_body_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_okuwa_base_txt[0x80];
#else
u8 int_sum_okuwa_base_txt[] = {
#include "assets/int_sum_okuwa_base_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_okuwa_top_txt[0x200];
#else
u8 int_sum_okuwa_top_txt[] = {
#include "assets/int_sum_okuwa_top_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_okuwa_side_txt[0x200];
#else
u8 int_sum_okuwa_side_txt[] = {
#include "assets/int_sum_okuwa_side_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_okuwa_hand_txt[0x100];
#else
u8 int_sum_okuwa_hand_txt[] = {
#include "assets/int_sum_okuwa_hand_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_okuwa_v[0x3A0 / sizeof(Vtx)];
#else
Vtx int_sum_okuwa_v[] = {
#include "assets/int_sum_okuwa_v.inc"
};
#endif

Gfx int_sum_okuwa_side_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 140),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_okuwa_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_okuwa_side_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_okuwa_v[44], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 1, 6, 7, 1, 7, 2, 6, 8, 9),
    gsSPNTriangles_5b(6, 9, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_okuwa_komado_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 140),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_okuwa_hand_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_okuwa_hand_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 3),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_okuwa_v[54], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_okuwa_glass_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 70),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_okuwa_hand_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_okuwa_hand_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 5),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_okuwa_v[34], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 7, 6, 1, 7, 1, 0, 4, 8, 9),
    gsSPNTriangles_5b(4, 9, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_okuwa_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_okuwa_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_okuwa_base_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_okuwa_v[9], 25, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_okuwa_top_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 5, 6, 7, 6, 8, 7, 9, 10, 11),
    gsSPNTriangles_5b(9, 12, 10, 13, 14, 15, 13, 16, 14, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 21, 22, 23, 21, 23, 24, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_okuwa_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_okuwa_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_okuwa_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_okuwa_v, 9, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 1, 4, 2),
    gsSPNTriangles_5b(1, 5, 4, 4, 6, 2, 5, 6, 4, 5, 7, 8),
    gsSPNTriangles_5b(5, 8, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_okuwa_tbl[] = { 7, 0, 7, 0, 0, 0 };

s16 cKF_kn_int_sum_okuwa_tbl[] = { 2, 2, 2, 9, 2, 16 };

s16 cKF_c_int_sum_okuwa_tbl[] = { 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_sum_okuwa_tbl[] = { 1,   0, 0, 257, 0,   0, 1,   0,   0, 257, 0,  0, 1,   0, 0, 257, 0,   0, 1,   0,   0,
                                   15,  0, 0, 42,  -70, 0, 71,  -70, 0, 111, 0,  0, 141, 0, 0, 165, 125, 0, 216, 125, 0,
                                   257, 0, 0, 1,   0,   0, 257, 0,   0, 1,   0,  0, 15,  0, 0, 24,  2,   0, 33,  -2,  0,
                                   42,  0, 0, 71,  0,   0, 81,  2,   0, 91,  -2, 0, 101, 2, 0, 111, 0,   0, 141, 0,   0,
                                   147, 2, 0, 153, -2,  0, 159, 2,   0, 165, 0,  0, 257, 0, 0 };

cKF_Animation_R_c cKF_ba_r_int_sum_okuwa = {
    cKF_ckcb_r_int_sum_okuwa_tbl, cKF_ds_int_sum_okuwa_tbl, cKF_kn_int_sum_okuwa_tbl, cKF_c_int_sum_okuwa_tbl, -1, 257
};

cKF_Joint_R_c cKF_je_r_int_sum_okuwa_tbl[] = { { int_sum_okuwa_base_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                               { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 61536, 0 } },
                                               { int_sum_okuwa_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                               { int_sum_okuwa_glass_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                               { int_sum_okuwa_komado_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                               { int_sum_okuwa_side_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_sum_okuwa = { ARRAY_COUNT(cKF_je_r_int_sum_okuwa_tbl), 5, cKF_je_r_int_sum_okuwa_tbl };
