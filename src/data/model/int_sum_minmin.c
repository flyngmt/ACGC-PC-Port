#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_minmin_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_minmin_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_minmin_pal[] = {
#include "assets/int_sum_minmin_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_sum_minmin_hand_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_sum_minmin_hand_pic_ci4_pal[] = {
#include "assets/int_sum_minmin_hand_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_minmin_base_txt[0x80];
#else
u8 int_sum_minmin_base_txt[] = {
#include "assets/int_sum_minmin_base_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_minmin_top_txt[0x200];
#else
u8 int_sum_minmin_top_txt[] = {
#include "assets/int_sum_minmin_top_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_minmin_body_txt[0x200];
#else
u8 int_sum_minmin_body_txt[] = {
#include "assets/int_sum_minmin_body_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_minmin_side_txt[0x200];
#else
u8 int_sum_minmin_side_txt[] = {
#include "assets/int_sum_minmin_side_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_minmin_hand_txt[0x100];
#else
u8 int_sum_minmin_hand_txt[] = {
#include "assets/int_sum_minmin_hand_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_minmin_v[0x450 / sizeof(Vtx)];
#else
Vtx int_sum_minmin_v[] = {
#include "assets/int_sum_minmin_v.inc"
};
#endif

Gfx int_sum_minmin_side_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 140),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_minmin_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_minmin_side_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_minmin_v[45], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_minmin_komado_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 140),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_minmin_hand_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_minmin_hand_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 3),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_minmin_v[41], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_minmin_glass_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 70),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_minmin_hand_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_minmin_hand_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 5),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_minmin_v[31], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 7, 6, 1, 7, 1, 0, 4, 8, 9),
    gsSPNTriangles_5b(4, 9, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_minmin_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_minmin_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_minmin_base_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_minmin_v, 31, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 1, 0, 0, 4, 3),
    gsSPNTriangles_5b(0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_minmin_top_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 5, 6, 7, 5, 7, 8, 9, 10, 11),
    gsSPNTriangles_5b(9, 11, 12, 13, 14, 15, 13, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(17, 19, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 21, 22, 23, 21, 23, 24, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_minmin_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 25, 26, 27, 26, 28, 29, 26, 30, 27),
    gsSPNTriangles_5b(26, 29, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_minmin_body_R_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 160),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_minmin_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_minmin_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_minmin_v[61], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_minmin_body_L_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 160),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_minmin_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_minmin_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_minmin_v[65], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_minmin_tbl[] = { 7, 0, 7, 0, 7, 0, 0, 0 };

s16 cKF_kn_int_sum_minmin_tbl[] = { 2, 2, 2, 2, 34, 2, 2, 34, 2 };

s16 cKF_c_int_sum_minmin_tbl[] = { 0, 0, 0, 0, 0, 1800, 0, 0, 1800, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_sum_minmin_tbl[] = {
    1,  0,  0,   109, 0,   0,  1,  0,   0,   109, 0,   0,  1,   0,   0,  109, 0,  0,   1,   0,  0,  109, 0,   0,   1,
    0,  0,  3,   -75, 0,   5,  0,  0,   7,   -80, 0,   9,  0,   0,   11, -85, 0,  13,  0,   0,  15, -80, 0,   17,  0,
    0,  19, -75, 0,   21,  0,  0,  23,  -70, 0,   26,  0,  0,   33,  0,  0,   36, -85, 0,   39, 0,  0,   42,  -80, 0,
    45, 0,  0,   51,  0,   0,  54, -65, 0,   57,  0,   0,  60,  -60, 0,  63,  0,  0,   69,  0,  0,  72,  -45, 0,   75,
    0,  0,  78,  -40, 0,   81, 0,  0,   86,  0,   0,   89, -35, 0,   92, 0,   0,  95,  -25, 0,  98, 0,   0,   109, 0,
    0,  1,  0,   0,   109, 0,  0,  1,   0,   0,   109, 0,  0,   1,   0,  0,   3,  75,  0,   5,  0,  0,   7,   80,  0,
    9,  0,  0,   11,  85,  0,  13, 0,   0,   15,  80,  0,  17,  0,   0,  19,  75, 0,   21,  0,  0,  23,  70,  0,   26,
    0,  0,  33,  0,   0,   36, 85, 0,   39,  0,   0,   42, 80,  0,   45, 0,   0,  51,  0,   0,  54, 65,  0,   57,  0,
    0,  60, 60,  0,   63,  0,  0,  69,  0,   0,   72,  50, 0,   75,  0,  0,   78, 45,  0,   81, 0,  0,   86,  0,   0,
    89, 40, 0,   92,  0,   0,  95, 30,  0,   98,  0,   0,  109, 0,   0,  1,   0,  0,   109, 0,  0
};

cKF_Animation_R_c cKF_ba_r_int_sum_minmin = { cKF_ckcb_r_int_sum_minmin_tbl,
                                              cKF_ds_int_sum_minmin_tbl,
                                              cKF_kn_int_sum_minmin_tbl,
                                              cKF_c_int_sum_minmin_tbl,
                                              -1,
                                              109 };

cKF_Joint_R_c cKF_je_r_int_sum_minmin_tbl[] = {
    { int_sum_minmin_base_model, 5, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 200, 0, 200 } },
    { int_sum_minmin_body_L_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 200, 0, 65336 } },
    { int_sum_minmin_body_R_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_sum_minmin_glass_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_sum_minmin_komado_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_sum_minmin_side_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_minmin = { ARRAY_COUNT(cKF_je_r_int_sum_minmin_tbl), 6, cKF_je_r_int_sum_minmin_tbl };
