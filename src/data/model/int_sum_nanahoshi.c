#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_nanahoshi_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_nanahoshi_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_nanahoshi_pal[] = {
#include "assets/int_sum_nanahoshi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_sum_nanahoshi_hand_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_sum_nanahoshi_hand_pic_ci4_pal[] = {
#include "assets/int_sum_nanahoshi_hand_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_nanahoshi_body_txt[0x100];
#else
u8 int_sum_nanahoshi_body_txt[] = {
#include "assets/int_sum_nanahoshi_body_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_nanahoshi_base_txt[0x80];
#else
u8 int_sum_nanahoshi_base_txt[] = {
#include "assets/int_sum_nanahoshi_base_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_nanahoshi_top_txt[0x200];
#else
u8 int_sum_nanahoshi_top_txt[] = {
#include "assets/int_sum_nanahoshi_top_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_nanahoshi_side_txt[0x200];
#else
u8 int_sum_nanahoshi_side_txt[] = {
#include "assets/int_sum_nanahoshi_side_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_nanahoshi_hand_txt[0x100];
#else
u8 int_sum_nanahoshi_hand_txt[] = {
#include "assets/int_sum_nanahoshi_hand_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_nanahoshi_v[0x3D0 / sizeof(Vtx)];
#else
Vtx int_sum_nanahoshi_v[] = {
#include "assets/int_sum_nanahoshi_v.inc"
};
#endif

Gfx int_sum_nanahoshi_side_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 140),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_nanahoshi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_nanahoshi_side_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_nanahoshi_v[47], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 1, 6, 7, 1, 7, 2, 6, 8, 9),
    gsSPNTriangles_5b(6, 9, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_nanahoshi_komado_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 140),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_nanahoshi_hand_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_nanahoshi_hand_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 3),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_nanahoshi_v[57], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_nanahoshi_glass_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 70),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_nanahoshi_hand_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_nanahoshi_hand_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 5),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_nanahoshi_v[37], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 7, 6, 1, 7, 1, 0, 4, 8, 9),
    gsSPNTriangles_5b(4, 9, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_nanahoshi_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_nanahoshi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_nanahoshi_base_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_nanahoshi_v[9], 28, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_nanahoshi_top_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(12, 4, 5, 6, 5, 7, 6, 7, 8, 6),
    gsSPNTriangles_5b(9, 10, 11, 9, 12, 10, 12, 13, 10, 14, 15, 16),
    gsSPNTriangles_5b(15, 17, 16, 17, 18, 16, 19, 20, 21, 19, 22, 20),
    gsSPNTriangles_5b(22, 23, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 26, 27, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_nanahoshi_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_nanahoshi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_nanahoshi_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_nanahoshi_v, 9, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 0, 2, 4, 3, 2),
    gsSPNTriangles_5b(2, 5, 6, 7, 8, 2, 7, 2, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_nanahoshi_tbl[] = { 7, 0, 7, 0, 0, 0 };

s16 cKF_kn_int_sum_nanahoshi_tbl[] = { 2, 2, 2, 8, 7, 7 };

s16 cKF_c_int_sum_nanahoshi_tbl[] = { 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_sum_nanahoshi_tbl[] = { 1,    0,   0,   257,  0,   0,   1,   0,  0,    257, 0,  0,    1,   0,
                                       0,    257, 0,   0,    1,   300, 0,   33, -350, 0,   51, -200, 0,   73,
                                       -300, 0,   115, -500, 0,   165, 150, 0,  211,  150, 0,  257,  300, 0,
                                       1,    0,   0,   33,   0,   0,   73,  0,  0,    115, 0,  3,    165, 10,
                                       3,    211, 10,  -3,   257, 0,   0,   1,  -15,  0,   33, 0,    0,   73,
                                       0,    0,   115, 15,   0,   165, 0,   0,  211,  0,   0,  257,  -15, 0 };

cKF_Animation_R_c cKF_ba_r_int_sum_nanahoshi = { cKF_ckcb_r_int_sum_nanahoshi_tbl,
                                                 cKF_ds_int_sum_nanahoshi_tbl,
                                                 cKF_kn_int_sum_nanahoshi_tbl,
                                                 cKF_c_int_sum_nanahoshi_tbl,
                                                 -1,
                                                 257 };

cKF_Joint_R_c cKF_je_r_int_sum_nanahoshi_tbl[] = {
    { int_sum_nanahoshi_base_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 60036, 0 } },
    { int_sum_nanahoshi_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_nanahoshi_glass_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_sum_nanahoshi_komado_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_sum_nanahoshi_side_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_nanahoshi = { ARRAY_COUNT(cKF_je_r_int_sum_nanahoshi_tbl), 5,
                                                cKF_je_r_int_sum_nanahoshi_tbl };
