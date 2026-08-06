#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_mimiclock_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kon_mimiclock_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kon_mimiclock_pal[] = {
#include "assets/int_kon_mimiclock_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_mimiclock_c_tex_txt[0x100];
#else
u8 int_kon_mimiclock_c_tex_txt[] = {
#include "assets/int_kon_mimiclock_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_mimiclock_d_tex_txt[0x100];
#else
u8 int_kon_mimiclock_d_tex_txt[] = {
#include "assets/int_kon_mimiclock_d_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_mimiclock_b_tex_txt[0x180];
#else
u8 int_kon_mimiclock_b_tex_txt[] = {
#include "assets/int_kon_mimiclock_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_mimiclock_a_tex_txt[0x180];
#else
u8 int_kon_mimiclock_a_tex_txt[] = {
#include "assets/int_kon_mimiclock_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_mimiclock_e_tex_txt[0x200];
#else
u8 int_kon_mimiclock_e_tex_txt[] = {
#include "assets/int_kon_mimiclock_e_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_mimiclock_f_tex_txt[0x80];
#else
u8 int_kon_mimiclock_f_tex_txt[] = {
#include "assets/int_kon_mimiclock_f_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_mimiclock_v[0x2F0 / sizeof(Vtx)];
#else
Vtx int_kon_mimiclock_v[] = {
#include "assets/int_kon_mimiclock_v.inc"
};
#endif

Gfx int_kon_mimiclock_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_mimiclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_mimiclock_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_mimiclock_v, 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_mimiclock_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_mimiclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_kon_mimiclock_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 188),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_mimiclock_v[9], 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_kon_mimiclock_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 188),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, int_kon_mimiclock_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_mimiclock_v[17], 30, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 5, 4, 6, 5, 6, 7, 7, 6, 8),
    gsSPNTriangles_5b(7, 8, 9, 9, 8, 10, 9, 10, 11, 11, 10, 12),
    gsSPNTriangles_5b(11, 12, 13, 13, 12, 14, 13, 14, 15, 15, 14, 16),
    gsSPNTriangles_5b(15, 16, 17, 17, 16, 18, 17, 18, 19, 19, 18, 20),
    gsSPNTriangles_5b(19, 20, 21, 21, 20, 22, 21, 22, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_mimiclock_f_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPNTrianglesInit_5b(4, 24, 25, 26, 24, 26, 27, 27, 26, 28),
    gsSPNTriangles_5b(27, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_mimiclock_eye_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_mimiclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_kon_mimiclock_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_mimiclock_v[6], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_mimiclock_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_mimiclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_mimiclock_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_mimiclock_v[3], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_kon_mimiclock_tbl[] = { 0, 0, 0, 0, 0, 1, 0 };

s16 cKF_kn_int_kon_mimiclock_tbl[] = { 4 };

s16 cKF_c_int_kon_mimiclock_tbl[] = { 0, 1300, 500, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1800, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_kon_mimiclock_tbl[] = { 1, 0, -97, 11, -15, 78, 21, 15, 78, 31, 0, -103 };

cKF_Animation_R_c cKF_ba_r_int_kon_mimiclock = { cKF_ckcb_r_int_kon_mimiclock_tbl,
                                                 cKF_ds_int_kon_mimiclock_tbl,
                                                 cKF_kn_int_kon_mimiclock_tbl,
                                                 cKF_c_int_kon_mimiclock_tbl,
                                                 -1,
                                                 31 };

cKF_Joint_R_c cKF_je_r_int_kon_mimiclock_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 1300, 500 } },
    { int_kon_mimiclock_base_model, 3, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } },
    { int_kon_mimiclock_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 6200, 0, 0 } },
    { int_kon_mimiclock_eye_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_kon_mimiclock_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_kon_mimiclock = { ARRAY_COUNT(cKF_je_r_int_kon_mimiclock_tbl), 4,
                                                cKF_je_r_int_kon_mimiclock_tbl };
