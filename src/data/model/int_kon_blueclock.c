#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_blueclock_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kon_blueclock_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kon_blueclock_pal[] = {
#include "assets/int_kon_blueclock_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_kon_blueclock_grass_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_kon_blueclock_grass_tex_pic_ci4_pal[] = {
#include "assets/int_kon_blueclock_grass_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_blueclock_d_tex_txt[0x80];
#else
u8 int_kon_blueclock_d_tex_txt[] = {
#include "assets/int_kon_blueclock_d_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_blueclock_a_tex_txt[0x100];
#else
u8 int_kon_blueclock_a_tex_txt[] = {
#include "assets/int_kon_blueclock_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_blueclock_c_tex_txt[0x80];
#else
u8 int_kon_blueclock_c_tex_txt[] = {
#include "assets/int_kon_blueclock_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_blueclock_b_tex_txt[0x100];
#else
u8 int_kon_blueclock_b_tex_txt[] = {
#include "assets/int_kon_blueclock_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_blueclock_grass_tex_txt[0x200];
#else
u8 int_kon_blueclock_grass_tex_txt[] = {
#include "assets/int_kon_blueclock_grass_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_blueclock_v[0x280 / sizeof(Vtx)];
#else
Vtx int_kon_blueclock_v[] = {
#include "assets/int_kon_blueclock_v.inc"
};
#endif

Gfx int_kon_blueclock_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_blueclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_blueclock_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_blueclock_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_blueclock_evw_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIM_LOD_FRAC, PRIMITIVE, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 60, 255, 255, 255, 150),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_blueclock_grass_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kon_blueclock_grass_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 3),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_blueclock_v[8], 16, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 0, 4, 5),
    gsSPNTriangles_5b(0, 5, 1, 4, 6, 7, 4, 7, 5, 6, 3, 2),
    gsSPNTriangles_5b(6, 2, 7, 3, 8, 9, 3, 9, 0, 6, 10, 8),
    gsSPNTriangles_5b(6, 8, 3, 4, 11, 10, 4, 10, 6, 8, 12, 13),
    gsSPNTriangles_5b(8, 13, 9, 14, 11, 9, 14, 9, 13, 8, 10, 15),
    gsSPNTriangles_5b(8, 15, 12, 10, 11, 14, 10, 14, 15, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_blueclock_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_blueclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_blueclock_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_blueclock_v[24], 16, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_blueclock_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 380, 60),
    gsSPNTrianglesInit_5b(6, 4, 5, 6, 4, 6, 7, 8, 9, 5),
    gsSPNTriangles_5b(8, 5, 4, 7, 6, 10, 7, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_blueclock_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_blueclock_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_blueclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_blueclock_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_blueclock_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_kon_blueclock_tbl[] = { 0, 0, 0, 0, 0, 0 };

s16 cKF_c_int_kon_blueclock_tbl[] = { 0, 975, 812, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_int_kon_blueclock = { cKF_ckcb_r_int_kon_blueclock_tbl, NULL, NULL,
                                                 cKF_c_int_kon_blueclock_tbl,      -1,   121 };

cKF_Joint_R_c cKF_je_r_int_kon_blueclock_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 975, 812 } },
    { int_kon_blueclock_base_model, 3, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 300, 0, 0 } },
    { int_kon_blueclock_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_kon_blueclock_evw_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_kon_blueclock_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 300, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_kon_blueclock = { ARRAY_COUNT(cKF_je_r_int_kon_blueclock_tbl), 4,
                                                cKF_je_r_int_kon_blueclock_tbl };
