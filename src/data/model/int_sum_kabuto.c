#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_kabuto_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_kabuto_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_kabuto_pal[] = {
#include "assets/int_sum_kabuto_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_sum_kabuto_hand_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_sum_kabuto_hand_pic_ci4_pal[] = {
#include "assets/int_sum_kabuto_hand_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kabuto_body_txt[0x100];
#else
u8 int_sum_kabuto_body_txt[] = {
#include "assets/int_sum_kabuto_body_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kabuto_base_txt[0x80];
#else
u8 int_sum_kabuto_base_txt[] = {
#include "assets/int_sum_kabuto_base_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kabuto_top_txt[0x200];
#else
u8 int_sum_kabuto_top_txt[] = {
#include "assets/int_sum_kabuto_top_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kabuto_side_txt[0x200];
#else
u8 int_sum_kabuto_side_txt[] = {
#include "assets/int_sum_kabuto_side_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kabuto_hand_txt[0x100];
#else
u8 int_sum_kabuto_hand_txt[] = {
#include "assets/int_sum_kabuto_hand_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_kabuto_v[0x370 / sizeof(Vtx)];
#else
Vtx int_sum_kabuto_v[] = {
#include "assets/int_sum_kabuto_v.inc"
};
#endif

Gfx int_sum_kabuto_side_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 140),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_kabuto_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_kabuto_side_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_kabuto_v[35], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 1, 6, 7, 1, 7, 2, 6, 8, 9),
    gsSPNTriangles_5b(6, 9, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_kabuto_glass_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 70),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_kabuto_hand_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_kabuto_hand_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 5),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_kabuto_v[45], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 7, 6, 1, 7, 1, 0, 4, 8, 9),
    gsSPNTriangles_5b(4, 9, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_kabuto_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_kabuto_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_kabuto_base_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_kabuto_v[11], 24, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_kabuto_top_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 4, 5, 6, 5, 7, 6, 8, 9, 10),
    gsSPNTriangles_5b(8, 11, 9, 12, 13, 14, 12, 15, 13, 16, 17, 18),
    gsSPNTriangles_5b(17, 19, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_kabuto_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_kabuto_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_kabuto_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_kabuto_v, 11, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 2, 3, 0, 4, 1, 0),
    gsSPNTriangles_5b(0, 5, 4, 0, 6, 5, 4, 5, 7, 4, 7, 8),
    gsSPNTriangles_5b(8, 1, 4, 2, 1, 8, 7, 9, 8, 8, 10, 2),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_kabuto_tbl[] = { 7, 0, 7, 0, 0 };

s16 cKF_kn_int_sum_kabuto_tbl[] = { 2, 2, 2, 5, 6, 5 };

s16 cKF_c_int_sum_kabuto_tbl[] = { 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_sum_kabuto_tbl[] = { 1, 0, 0,    193, 0,  0,    1,   0,   0,    193, 0,   0,    1,   0,   0,    193, 0,
                                    0, 1, -250, 0,   13, -250, 0,   33,  -200, 0,   165, -200, 0,   193, -250, 0,   1,
                                    0, 0, 13,   0,   0,  33,   -15, 0,   125,  -15, 0,   143,  0,   0,   193,  0,   0,
                                    1, 0, 0,    13,  0,  0,    33,  -10, 0,    165, -10, 0,    193, 0,   0 };

cKF_Animation_R_c cKF_ba_r_int_sum_kabuto = { cKF_ckcb_r_int_sum_kabuto_tbl,
                                              cKF_ds_int_sum_kabuto_tbl,
                                              cKF_kn_int_sum_kabuto_tbl,
                                              cKF_c_int_sum_kabuto_tbl,
                                              -1,
                                              193 };

cKF_Joint_R_c cKF_je_r_int_sum_kabuto_tbl[] = {
    { int_sum_kabuto_base_model, 3, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 64586, 0 } },
    { int_sum_kabuto_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_kabuto_glass_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_sum_kabuto_side_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_kabuto = { ARRAY_COUNT(cKF_je_r_int_sum_kabuto_tbl), 4, cKF_je_r_int_sum_kabuto_tbl };
