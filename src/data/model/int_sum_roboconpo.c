#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_roboconpo_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_roboconpo_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_roboconpo_pal[] = {
#include "assets/int_roboconpo_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_roboconpo_stand_tex_txt[0x80];
#else
u8 int_sum_roboconpo_stand_tex_txt[] = {
#include "assets/int_sum_roboconpo_stand_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_roboconpo_body_tex_txt[0x400];
#else
u8 int_sum_roboconpo_body_tex_txt[] = {
#include "assets/int_sum_roboconpo_body_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_roboconpo_spika_tex_txt[0x100];
#else
u8 int_sum_roboconpo_spika_tex_txt[] = {
#include "assets/int_sum_roboconpo_spika_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_roboconpo_top_tex_txt[0x100];
#else
u8 int_sum_roboconpo_top_tex_txt[] = {
#include "assets/int_sum_roboconpo_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_roboconpo_face1_TA_tex_txt[0x80];
#else
u8 int_sum_roboconpo_face1_TA_tex_txt[] = {
#include "assets/int_sum_roboconpo_face1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_roboconpo_face2_TA_tex_txt[0x80];
#else
u8 int_sum_roboconpo_face2_TA_tex_txt[] = {
#include "assets/int_sum_roboconpo_face2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_roboconpo_hed_tex_txt[0x80];
#else
u8 int_sum_roboconpo_hed_tex_txt[] = {
#include "assets/int_sum_roboconpo_hed_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_roboconpo_neck_tex_txt[0x80];
#else
u8 int_sum_roboconpo_neck_tex_txt[] = {
#include "assets/int_sum_roboconpo_neck_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_roboconpo_v[0x4F0 / sizeof(Vtx)];
#else
Vtx int_sum_roboconpo_v[] = {
#include "assets/int_sum_roboconpo_v.inc"
};
#endif

Gfx int_sum_roboconpo_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_roboconpo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_roboconpo_stand_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_roboconpo_v, 23, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 5, 6),
    gsSPNTriangles_5b(7, 8, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_sum_roboconpo_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 9, 10, 11, 9, 11, 12, 13, 14, 11),
    gsSPNTriangles_5b(13, 11, 15, 16, 17, 18, 16, 18, 14, 19, 20, 21),
    gsSPNTriangles_5b(19, 21, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_roboconpo_spika_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_roboconpo_v[23], 20, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 2, 5),
    gsSPNTriangles_5b(4, 5, 6, 7, 5, 8, 7, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 12, 15, 14, 15, 16, 17, 15, 18),
    gsSPNTriangles_5b(17, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_roboconpo_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_roboconpo_v[43], 28, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_roboconpo_hed_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(5, 16, 17, 18, 19, 20, 21, 21, 22, 23),
    gsSPNTriangles_5b(24, 25, 26, 24, 26, 27, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_roboconpo_neck_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_roboconpo_v[71], 8, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 3, 6, 7),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_roboconpo_tbl[] = { 0 };

s16 cKF_c_int_sum_roboconpo_tbl[] = { 0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_int_sum_roboconpo = { cKF_ckcb_r_int_sum_roboconpo_tbl, NULL, NULL,
                                                 cKF_c_int_sum_roboconpo_tbl,      -1,   25 };

cKF_Joint_R_c cKF_je_r_int_sum_roboconpo_tbl[] = {
    { int_sum_roboconpo_on_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_roboconpo = { ARRAY_COUNT(cKF_je_r_int_sum_roboconpo_tbl), 1,
                                                cKF_je_r_int_sum_roboconpo_tbl };
