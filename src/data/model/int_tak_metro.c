#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_metro_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_metro_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_metro_pal[] = {
#include "assets/int_tak_metro_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_metro_hari_tex_txt[0x80];
#else
u8 int_tak_metro_hari_tex_txt[] = {
#include "assets/int_tak_metro_hari_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_metro_neji_tex_txt[0x80];
#else
u8 int_tak_metro_neji_tex_txt[] = {
#include "assets/int_tak_metro_neji_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_metro_side_tex_txt[0x180];
#else
u8 int_tak_metro_side_tex_txt[] = {
#include "assets/int_tak_metro_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_metro_front2_tex_txt[0x80];
#else
u8 int_tak_metro_front2_tex_txt[] = {
#include "assets/int_tak_metro_front2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_metro_front_tex_txt[0x100];
#else
u8 int_tak_metro_front_tex_txt[] = {
#include "assets/int_tak_metro_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_metro_v[0x3D0 / sizeof(Vtx)];
#else
Vtx int_tak_metro_v[] = {
#include "assets/int_tak_metro_v.inc"
};
#endif

Gfx int_tak_metro_hari_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_metro_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_metro_hari_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_metro_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_metro_body_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_metro_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_metro_neji_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_metro_v[4], 9, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_tak_metro_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_metro_v[13], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 11, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(20, 21, 22, 23, 24, 9, 11, 25, 9, 2, 26, 0),
    gsSPNTriangles_5b(22, 27, 20, 9, 25, 23, 8, 28, 6, 19, 29, 17),
    gsSPNTriangles_5b(11, 10, 12, 16, 30, 31, 16, 31, 14, 0, 0, 0),
    gsSPVertex(&int_tak_metro_v[45], 16, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_metro_front2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPNTrianglesInit_5b(5, 4, 5, 6, 7, 8, 9, 9, 5, 7),
    gsSPNTriangles_5b(10, 5, 9, 9, 11, 10, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_metro_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 14, 15, 12, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_tak_metro_tbl[] = { 0, 0, 1 };

s16 cKF_kn_int_tak_metro_tbl[] = { 5 };

s16 cKF_c_int_tak_metro_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 900, 0, 0 };

s16 cKF_ds_int_tak_metro_tbl[] = { 1, -300, 59, 4, -283, 323, 31, 300, 0, 60, -298, -115, 61, -300, -59 };

cKF_Animation_R_c cKF_ba_r_int_tak_metro = {
    cKF_ckcb_r_int_tak_metro_tbl, cKF_ds_int_tak_metro_tbl, cKF_kn_int_tak_metro_tbl, cKF_c_int_tak_metro_tbl, -1, 61
};

cKF_Joint_R_c cKF_je_r_int_tak_metro_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_tak_metro_body_on_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_tak_metro_hari_on_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 900, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_tak_metro = { ARRAY_COUNT(cKF_je_r_int_tak_metro_tbl), 2, cKF_je_r_int_tak_metro_tbl };
