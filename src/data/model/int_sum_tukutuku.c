#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_tukutuku_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_tukutuku_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_tukutuku_pal[] = {
#include "assets/int_sum_tukutuku_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_sum_tukutuku_hand_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_sum_tukutuku_hand_pic_ci4_pal[] = {
#include "assets/int_sum_tukutuku_hand_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_tukutuku_side_txt[0x200];
#else
u8 int_sum_tukutuku_side_txt[] = {
#include "assets/int_sum_tukutuku_side_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_tukutuku_base_txt[0x80];
#else
u8 int_sum_tukutuku_base_txt[] = {
#include "assets/int_sum_tukutuku_base_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_tukutuku_top_txt[0x200];
#else
u8 int_sum_tukutuku_top_txt[] = {
#include "assets/int_sum_tukutuku_top_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_tukutuku_body_txt[0x200];
#else
u8 int_sum_tukutuku_body_txt[] = {
#include "assets/int_sum_tukutuku_body_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_tukutuku_hand_txt[0x100];
#else
u8 int_sum_tukutuku_hand_txt[] = {
#include "assets/int_sum_tukutuku_hand_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_tukutuku_v[0x470 / sizeof(Vtx)];
#else
Vtx int_sum_tukutuku_v[] = {
#include "assets/int_sum_tukutuku_v.inc"
};
#endif

Gfx int_sum_tukutuku_side_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 140),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_tukutuku_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_tukutuku_side_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_tukutuku_v, 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_tukutuku_komado_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 140),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_tukutuku_hand_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_tukutuku_hand_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 3),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_tukutuku_v[26], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_tukutuku_glass_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 70),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_tukutuku_hand_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_tukutuku_hand_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 5),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_tukutuku_v[16], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 7, 6, 1, 7, 1, 0, 4, 8, 9),
    gsSPNTriangles_5b(4, 9, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_tukutuku_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_tukutuku_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_tukutuku_base_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_tukutuku_v[30], 25, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 1, 0, 0, 4, 3),
    gsSPNTriangles_5b(0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_tukutuku_top_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 5, 6, 7, 5, 7, 8, 9, 10, 11),
    gsSPNTriangles_5b(9, 11, 12, 13, 14, 15, 13, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(17, 19, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 21, 22, 23, 21, 23, 24, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_tukutuku_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_tukutuku_v[55], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 1, 6, 2),
    gsSPNTriangles_5b(3, 5, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_tukutuku_body_R_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 160),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_tukutuku_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_tukutuku_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_tukutuku_v[67], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_tukutuku_body_L_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 160),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_tukutuku_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_tukutuku_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_tukutuku_v[63], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_tukutuku_tbl[] = { 7, 0, 7, 0, 7, 0, 0, 0 };

s16 cKF_kn_int_sum_tukutuku_tbl[] = { 2, 2, 2, 2, 53, 2, 2, 53, 2 };

s16 cKF_c_int_sum_tukutuku_tbl[] = { 0, 0, 0, 0, 0, 1800, 0, 0, 5400, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_sum_tukutuku_tbl[] = {
    1,   0,   0, 391, 0,   0, 1,   0,   0, 391, 0,   0, 1,   0,   0, 391, 0,   0, 1,   0,   0, 391, 0,   0, 1,   250, 0,
    48,  250, 0, 51,  150, 0, 54,  250, 0, 76,  250, 0, 79,  150, 0, 82,  250, 0, 102, 250, 0, 105, 150, 0, 108, 250, 0,
    128, 250, 0, 131, 150, 0, 134, 250, 0, 155, 250, 0, 158, 150, 0, 161, 250, 0, 182, 250, 0, 185, 150, 0, 188, 250, 0,
    209, 250, 0, 212, 150, 0, 215, 250, 0, 236, 250, 0, 239, 185, 0, 242, 250, 0, 245, 185, 0, 248, 250, 0, 257, 250, 0,
    260, 185, 0, 263, 250, 0, 266, 185, 0, 269, 250, 0, 278, 250, 0, 281, 185, 0, 284, 250, 0, 287, 185, 0, 290, 250, 0,
    299, 250, 0, 302, 135, 0, 305, 250, 0, 308, 145, 0, 311, 250, 0, 315, 160, 0, 319, 250, 0, 323, 175, 0, 327, 250, 0,
    331, 190, 0, 335, 250, 0, 340, 200, 0, 345, 250, 0, 350, 215, 0, 355, 250, 0, 391, 250, 0, 1,   0,   0, 391, 0,   0,
    1,   0,   0, 391, 0,   0, 1,   250, 0, 48,  250, 0, 51,  350, 0, 54,  250, 0, 76,  250, 0, 79,  350, 0, 82,  250, 0,
    102, 250, 0, 105, 350, 0, 108, 250, 0, 128, 250, 0, 131, 350, 0, 134, 250, 0, 155, 250, 0, 158, 350, 0, 161, 250, 0,
    182, 250, 0, 185, 350, 0, 188, 250, 0, 209, 250, 0, 212, 350, 0, 215, 250, 0, 236, 250, 0, 239, 315, 0, 242, 250, 0,
    245, 315, 0, 248, 250, 0, 257, 250, 0, 260, 315, 0, 263, 250, 0, 266, 315, 0, 269, 250, 0, 278, 250, 0, 281, 315, 0,
    284, 250, 0, 287, 315, 0, 290, 250, 0, 299, 250, 0, 302, 365, 0, 305, 250, 0, 308, 355, 0, 311, 250, 0, 315, 340, 0,
    319, 250, 0, 323, 325, 0, 327, 250, 0, 331, 310, 0, 335, 250, 0, 340, 300, 0, 345, 250, 0, 350, 285, 0, 355, 250, 0,
    391, 250, 0, 1,   0,   0, 391, 0,   0
};

cKF_Animation_R_c cKF_ba_r_int_sum_tukutuku = { cKF_ckcb_r_int_sum_tukutuku_tbl,
                                                cKF_ds_int_sum_tukutuku_tbl,
                                                cKF_kn_int_sum_tukutuku_tbl,
                                                cKF_c_int_sum_tukutuku_tbl,
                                                -1,
                                                391 };

cKF_Joint_R_c cKF_je_r_int_sum_tukutuku_tbl[] = {
    { int_sum_tukutuku_base_model, 5, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_tukutuku_body_L_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_tukutuku_body_R_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_sum_tukutuku_glass_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_sum_tukutuku_komado_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_sum_tukutuku_side_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_tukutuku = { ARRAY_COUNT(cKF_je_r_int_sum_tukutuku_tbl), 6,
                                               cKF_je_r_int_sum_tukutuku_tbl };
