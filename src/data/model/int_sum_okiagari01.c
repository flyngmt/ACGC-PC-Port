#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_okiagari01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_okiagari01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_okiagari01_pal[] = {
#include "assets/int_sum_okiagari01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_okiagari01_hand_tex_txt[0x80];
#else
u8 int_sum_okiagari01_hand_tex_txt[] = {
#include "assets/int_sum_okiagari01_hand_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_okiagari01_bodyback_tex_txt[0x100];
#else
u8 int_sum_okiagari01_bodyback_tex_txt[] = {
#include "assets/int_sum_okiagari01_bodyback_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_okiagari01_bodyfront_tex_txt[0x100];
#else
u8 int_sum_okiagari01_bodyfront_tex_txt[] = {
#include "assets/int_sum_okiagari01_bodyfront_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_okiagari01_face_tex_txt[0x200];
#else
u8 int_sum_okiagari01_face_tex_txt[] = {
#include "assets/int_sum_okiagari01_face_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_okiagari01_head_tex_txt[0x100];
#else
u8 int_sum_okiagari01_head_tex_txt[] = {
#include "assets/int_sum_okiagari01_head_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_okiagari01_v[0x340 / sizeof(Vtx)];
#else
Vtx int_sum_okiagari01_v[] = {
#include "assets/int_sum_okiagari01_v.inc"
};
#endif

Gfx int_sum_okiagari01_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_okiagari01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_okiagari01_hand_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_okiagari01_v, 31, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 2, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 5, 6, 7, 8, 9, 10, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_okiagari01_bodyback_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 11, 12, 13, 13, 14, 11, 15, 16, 13),
    gsSPNTriangles_5b(13, 17, 14, 13, 12, 15, 16, 17, 13, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_okiagari01_bodyfront_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(10, 18, 19, 20, 20, 21, 18, 20, 22, 21),
    gsSPNTriangles_5b(23, 24, 22, 22, 20, 23, 23, 20, 25, 18, 26, 19),
    gsSPNTriangles_5b(25, 20, 19, 22, 27, 21, 28, 29, 30, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_okiagari01_face_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_okiagari01_v[31], 21, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 2, 5, 6, 7),
    gsSPNTriangles_5b(3, 5, 4, 3, 8, 5, 7, 4, 5, 2, 4, 0),
    gsSPNTriangles_5b(7, 9, 0, 0, 4, 7, 9, 7, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_okiagari01_head_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(10, 10, 11, 12, 13, 10, 14, 11, 13, 15),
    gsSPNTriangles_5b(15, 16, 17, 15, 17, 11, 15, 13, 14, 15, 14, 18),
    gsSPNTriangles_5b(11, 19, 12, 11, 10, 13, 15, 18, 20, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_okiagari01_tbl[] = { 56, 7 };

s16 cKF_kn_int_sum_okiagari01_tbl[] = { 2, 2, 2, 2, 9, 9 };

s16 cKF_c_int_sum_okiagari01_tbl[] = { 0, 0, 900 };

s16 cKF_ds_int_sum_okiagari01_tbl[] = { 1,   0,  0,    71, 0,  0,   1,   0,   0,   71, 0,    0,  1,    0,   0,   71,
                                        0,   0,  1,    0,  0,  71,  0,   0,   1,   0,  0,    5,  -180, 0,   19,  190,
                                        0,   32, -120, 0,  43, 100, 0,   52,  -70, 0,  59,   40, 0,    65,  -30, 0,
                                        71,  0,  0,    1,  0,  0,   12,  220, 0,   26, -150, 0,  38,   130, 0,   48,
                                        -90, 0,  56,   60, 0,  62,  -40, 0,   68,  20, 0,    71, 0,    0 };

cKF_Animation_R_c cKF_ba_r_int_sum_okiagari01 = { cKF_ckcb_r_int_sum_okiagari01_tbl,
                                                  cKF_ds_int_sum_okiagari01_tbl,
                                                  cKF_kn_int_sum_okiagari01_tbl,
                                                  cKF_c_int_sum_okiagari01_tbl,
                                                  -1,
                                                  71 };

cKF_Joint_R_c cKF_je_r_int_sum_okiagari01_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_okiagari01_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_okiagari01 = { ARRAY_COUNT(cKF_je_r_int_sum_okiagari01_tbl), 1,
                                                 cKF_je_r_int_sum_okiagari01_tbl };
