#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_pet01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_pet01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_pet01_pal[] = {
#include "assets/int_sum_pet01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pet01_wing_tex_txt[0x180];
#else
u8 int_sum_pet01_wing_tex_txt[] = {
#include "assets/int_sum_pet01_wing_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pet01_belly_tex_txt[0x180];
#else
u8 int_sum_pet01_belly_tex_txt[] = {
#include "assets/int_sum_pet01_belly_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pet01_stand_tex_txt[0x180];
#else
u8 int_sum_pet01_stand_tex_txt[] = {
#include "assets/int_sum_pet01_stand_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pet01_wood_tex_txt[0x40];
#else
u8 int_sum_pet01_wood_tex_txt[] = {
#include "assets/int_sum_pet01_wood_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pet01_hand_tex_txt[0x80];
#else
u8 int_sum_pet01_hand_tex_txt[] = {
#include "assets/int_sum_pet01_hand_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pet01_cagedown_tex_txt[0x80];
#else
u8 int_sum_pet01_cagedown_tex_txt[] = {
#include "assets/int_sum_pet01_cagedown_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pet01_cage_tex_txt[0x180];
#else
u8 int_sum_pet01_cage_tex_txt[] = {
#include "assets/int_sum_pet01_cage_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pet01_foot_tex_txt[0x80];
#else
u8 int_sum_pet01_foot_tex_txt[] = {
#include "assets/int_sum_pet01_foot_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_pet01_v[0x510 / sizeof(Vtx)];
#else
Vtx int_sum_pet01_v[] = {
#include "assets/int_sum_pet01_v.inc"
};
#endif

Gfx int_sum_pet01_bard_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_pet01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_pet01_wing_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 188),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_pet01_v, 16, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 2, 3, 0, 4, 3, 5),
    gsSPNTriangles_5b(6, 1, 7, 6, 5, 2, 1, 6, 2, 2, 5, 3),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_pet01_belly_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 188),
    gsSPNTrianglesInit_5b(7, 8, 9, 10, 8, 11, 12, 12, 13, 14),
    gsSPNTriangles_5b(10, 9, 15, 15, 9, 14, 12, 9, 8, 14, 9, 12),
    gsSPEndDisplayList(),
};

Gfx int_sum_pet01_cage_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_pet01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_pet01_stand_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_pet01_v[16], 31, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_pet01_wood_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 6, 7, 8, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_pet01_hand_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_pet01_cagedown_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 14, 15, 12, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_pet01_cage_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 764, 188),
    gsSPNTrianglesInit_5b(1, 16, 17, 18, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 19, 20, 21, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 22, 23, 24, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 25, 26, 27, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 28, 29, 30, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_sum_pet01_v[47], 30, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 3, 4, 5, 6, 7, 8, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 9, 10, 11, 12, 13, 14, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 15, 16, 17, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(7, 18, 19, 20, 21, 22, 20, 18, 23, 24),
    gsSPNTriangles_5b(20, 22, 18, 25, 26, 21, 27, 26, 25, 28, 29, 27),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_pet01_foot_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_pet01_v[77], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_pet01_tbl[] = { 0, 0, 2 };

s16 cKF_kn_int_sum_pet01_tbl[] = { 7 };

s16 cKF_c_int_sum_pet01_tbl[] = { 0, 2500, 0, 0, 0, 900, 450, 0, 0, 0, 0 };

s16 cKF_ds_int_sum_pet01_tbl[] = {
    1, 0, -125, 2, -4, -223, 8, -75, -14, 16, 0, -2, 23, -60, -11, 30, -3, 141, 31, 0, 77
};

cKF_Animation_R_c cKF_ba_r_int_sum_pet01 = {
    cKF_ckcb_r_int_sum_pet01_tbl, cKF_ds_int_sum_pet01_tbl, cKF_kn_int_sum_pet01_tbl, cKF_c_int_sum_pet01_tbl, -1, 31
};

cKF_Joint_R_c cKF_je_r_int_sum_pet01_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 2500, 0 } },
    { int_sum_pet01_cage_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_pet01_bard_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_pet01 = { ARRAY_COUNT(cKF_je_r_int_sum_pet01_tbl), 2, cKF_je_r_int_sum_pet01_tbl };
