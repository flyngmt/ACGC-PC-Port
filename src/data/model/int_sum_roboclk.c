#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_roboclk_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_roboclk_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_roboclk_pal[] = {
#include "assets/int_roboclk_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_roboclk_hari_tex_txt[0x80];
#else
u8 int_sum_roboclk_hari_tex_txt[] = {
#include "assets/int_sum_roboclk_hari_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_roboclk_eye1_TA_tex_txt[0x80];
#else
u8 int_sum_roboclk_eye1_TA_tex_txt[] = {
#include "assets/int_sum_roboclk_eye1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_roboclk_eye2_TA_tex_txt[0x80];
#else
u8 int_sum_roboclk_eye2_TA_tex_txt[] = {
#include "assets/int_sum_roboclk_eye2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_roboclk_top_tex_txt[0x80];
#else
u8 int_sum_roboclk_top_tex_txt[] = {
#include "assets/int_sum_roboclk_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_roboclk_base_tex_txt[0x80];
#else
u8 int_sum_roboclk_base_tex_txt[] = {
#include "assets/int_sum_roboclk_base_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_roboclk_front_tex_txt[0x400];
#else
u8 int_sum_roboclk_front_tex_txt[] = {
#include "assets/int_sum_roboclk_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_roboclk_antena_tex_txt[0x80];
#else
u8 int_sum_roboclk_antena_tex_txt[] = {
#include "assets/int_sum_roboclk_antena_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_roboclk_head_tex_txt[0x80];
#else
u8 int_sum_roboclk_head_tex_txt[] = {
#include "assets/int_sum_roboclk_head_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_roboclk_hand_tex_txt[0x80];
#else
u8 int_sum_roboclk_hand_tex_txt[] = {
#include "assets/int_sum_roboclk_hand_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_roboclk_arm_tex_txt[0x80];
#else
u8 int_sum_roboclk_arm_tex_txt[] = {
#include "assets/int_sum_roboclk_arm_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_roboclk_v[0x610 / sizeof(Vtx)];
#else
Vtx int_sum_roboclk_v[] = {
#include "assets/int_sum_roboclk_v.inc"
};
#endif

Gfx int_sum_roboclk_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_roboclk_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_roboclk_hari_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_roboclk_v, 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_roboclk_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_roboclk_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_roboclk_v[6], 31, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_roboclk_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_roboclk_base_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 10, 11, 12, 10, 13, 14),
    gsSPNTriangles_5b(15, 16, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_sum_roboclk_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 17, 18, 19, 17, 19, 20, 21, 22, 19),
    gsSPNTriangles_5b(21, 19, 23, 24, 25, 26, 24, 26, 22, 27, 28, 29),
    gsSPNTriangles_5b(27, 29, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_roboclk_antena_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_roboclk_v[37], 29, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 3, 4, 5, 6, 7),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_roboclk_head_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(5, 8, 9, 10, 11, 12, 13, 13, 14, 15),
    gsSPNTriangles_5b(16, 17, 18, 16, 18, 19, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_roboclk_hand_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 20, 21, 22, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 23, 24, 25, 26, 27, 28, 0, 0, 0),
    gsSPVertex(&int_sum_roboclk_v[66], 31, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_roboclk_arm_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 3, 4, 5, 6, 7, 8, 6, 9, 10),
    gsSPNTriangles_5b(11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 26, 27, 25, 28, 29, 30, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_roboclk_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_roboclk_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_roboclk_hari_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_roboclk_v[3], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_roboclk_tbl[] = { 0, 0, 0, 0, 0 };

s16 cKF_c_int_sum_roboclk_tbl[] = { 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_int_sum_roboclk = { cKF_ckcb_r_int_sum_roboclk_tbl, NULL, NULL,
                                               cKF_c_int_sum_roboclk_tbl,      -1,   61 };

cKF_Joint_R_c cKF_je_r_int_sum_roboclk_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_roboclk_base_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1350, 0, 0 } },
    { int_sum_roboclk_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_roboclk_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1351, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_roboclk = { ARRAY_COUNT(cKF_je_r_int_sum_roboclk_tbl), 3,
                                              cKF_je_r_int_sum_roboclk_tbl };
