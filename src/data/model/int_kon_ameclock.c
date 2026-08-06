#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_ameclock_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kon_ameclock_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kon_ameclock_pal[] = {
#include "assets/int_kon_ameclock_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_ameclock_e_tex_txt[0x80];
#else
u8 int_kon_ameclock_e_tex_txt[] = {
#include "assets/int_kon_ameclock_e_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_ameclock_a_tex_txt[0x200];
#else
u8 int_kon_ameclock_a_tex_txt[] = {
#include "assets/int_kon_ameclock_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_ameclock_c_tex_txt[0x80];
#else
u8 int_kon_ameclock_c_tex_txt[] = {
#include "assets/int_kon_ameclock_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_ameclock_b_tex_txt[0x100];
#else
u8 int_kon_ameclock_b_tex_txt[] = {
#include "assets/int_kon_ameclock_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_ameclock_d_tex_txt[0x80];
#else
u8 int_kon_ameclock_d_tex_txt[] = {
#include "assets/int_kon_ameclock_d_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_ameclock_f_tex_txt[0x100];
#else
u8 int_kon_ameclock_f_tex_txt[] = {
#include "assets/int_kon_ameclock_f_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_ameclock_g_tex_txt[0x100];
#else
u8 int_kon_ameclock_g_tex_txt[] = {
#include "assets/int_kon_ameclock_g_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_ameclock_v[0x3A0 / sizeof(Vtx)];
#else
Vtx int_kon_ameclock_v[] = {
#include "assets/int_kon_ameclock_v.inc"
};
#endif

Gfx int_kon_ameclock_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_ameclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_ameclock_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_ameclock_v, 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_ameclock_off_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_ameclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kon_ameclock_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_ameclock_v[6], 9, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(1, 5, 4, 0, 6, 1, 6, 7, 1, 7, 8, 1),
    gsSPNTriangles_5b(8, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_ameclock_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_ameclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_ameclock_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_ameclock_v[3], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_ameclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_ameclock_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_ameclock_v[15], 26, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 4, 6, 7, 5, 4, 7, 6, 8, 9),
    gsSPNTriangles_5b(7, 6, 9, 9, 8, 10, 9, 10, 11, 11, 10, 12),
    gsSPNTriangles_5b(11, 12, 13, 12, 14, 15, 13, 12, 15, 15, 14, 16),
    gsSPNTriangles_5b(15, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_ameclock_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(6, 18, 19, 20, 18, 21, 19, 22, 21, 18),
    gsSPNTriangles_5b(22, 23, 21, 24, 23, 22, 24, 25, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_ameclock_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_ameclock_v[41], 17, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(5, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_ameclock_f_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 10, 11, 12, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_kon_ameclock_g_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 13, 14, 15, 13, 15, 16, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_kon_ameclock_tbl[] = { 0, 0, 0, 0, 0, 0 };

s16 cKF_c_int_kon_ameclock_tbl[] = { 0, 6000, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_int_kon_ameclock = { cKF_ckcb_r_int_kon_ameclock_tbl, NULL, NULL,
                                                cKF_c_int_kon_ameclock_tbl,      -1,   100 };

cKF_Joint_R_c cKF_je_r_int_kon_ameclock_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 6000, 0 } },
    { base_model, 3, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } },
    { int_kon_ameclock_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_kon_ameclock_off_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_kon_ameclock_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_kon_ameclock = { ARRAY_COUNT(cKF_je_r_int_kon_ameclock_tbl), 4,
                                               cKF_je_r_int_kon_ameclock_tbl };
