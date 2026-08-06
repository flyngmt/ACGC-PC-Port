#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_redclock_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kon_redclock_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kon_redclock_pal[] = {
#include "assets/int_kon_redclock_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_redclock_e_tex_txt[0x80];
#else
u8 int_kon_redclock_e_tex_txt[] = {
#include "assets/int_kon_redclock_e_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_redclock_d_tex_txt[0x80];
#else
u8 int_kon_redclock_d_tex_txt[] = {
#include "assets/int_kon_redclock_d_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_redclock_f_tex_txt[0x100];
#else
u8 int_kon_redclock_f_tex_txt[] = {
#include "assets/int_kon_redclock_f_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_redclock_b_tex_txt[0x80];
#else
u8 int_kon_redclock_b_tex_txt[] = {
#include "assets/int_kon_redclock_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_redclock_a_tex_txt[0x400];
#else
u8 int_kon_redclock_a_tex_txt[] = {
#include "assets/int_kon_redclock_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_redclock_c_tex_txt[0x100];
#else
u8 int_kon_redclock_c_tex_txt[] = {
#include "assets/int_kon_redclock_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_redclock_v[0x2F0 / sizeof(Vtx)];
#else
Vtx int_kon_redclock_v[] = {
#include "assets/int_kon_redclock_v.inc"
};
#endif

Gfx int_kon_redclock_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_redclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_redclock_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_redclock_v, 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_redclock_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_redclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_redclock_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_redclock_v[6], 29, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 4, 3, 5, 6),
    gsSPNTriangles_5b(5, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_redclock_f_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 9, 10, 11, 9, 11, 12, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 13, 14, 15, 13, 15, 16, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_redclock_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(4, 17, 18, 19, 17, 19, 20, 17, 20, 21),
    gsSPNTriangles_5b(17, 21, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_kon_redclock_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsSPNTrianglesInit_5b(4, 23, 24, 25, 23, 25, 26, 23, 26, 27),
    gsSPNTriangles_5b(23, 27, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_kon_redclock_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 60),
    gsSPVertex(&int_kon_redclock_v[35], 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 5, 4, 6, 5, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 7, 6, 9, 7, 9, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_redclock_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_redclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_redclock_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_redclock_v[3], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_kon_redclock_tbl[] = { 0, 0, 0, 0, 0 };

s16 cKF_c_int_kon_redclock_tbl[] = { 0, 1000, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_int_kon_redclock = { cKF_ckcb_r_int_kon_redclock_tbl, NULL, NULL,
                                                cKF_c_int_kon_redclock_tbl,      -1,   100 };

cKF_Joint_R_c cKF_je_r_int_kon_redclock_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 1000, 0 } },
    { int_kon_redclock_base_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } },
    { int_kon_redclock_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_kon_redclock_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_kon_redclock = { ARRAY_COUNT(cKF_je_r_int_kon_redclock_tbl), 3,
                                               cKF_je_r_int_kon_redclock_tbl };
