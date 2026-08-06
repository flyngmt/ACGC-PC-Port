#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_ufo_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_ufo_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_ufo_pal[] = {
#include "assets/int_tak_ufo_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ufo_yane_tex_txt[0x80];
#else
u8 int_tak_ufo_yane_tex_txt[] = {
#include "assets/int_tak_ufo_yane_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ufo_body_tex_txt[0x100];
#else
u8 int_tak_ufo_body_tex_txt[] = {
#include "assets/int_tak_ufo_body_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ufo_mado_tex_txt[0x80];
#else
u8 int_tak_ufo_mado_tex_txt[] = {
#include "assets/int_tak_ufo_mado_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ufo_asi_tex_txt[0x80];
#else
u8 int_tak_ufo_asi_tex_txt[] = {
#include "assets/int_tak_ufo_asi_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ufo_hikari_tex_txt[0x80];
#else
u8 int_tak_ufo_hikari_tex_txt[] = {
#include "assets/int_tak_ufo_hikari_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_ufo_v[0x5B0 / sizeof(Vtx)];
#else
Vtx int_tak_ufo_v[] = {
#include "assets/int_tak_ufo_v.inc"
};
#endif

Gfx int_tak_ufo_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_ufo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_ufo_yane_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_ufo_v, 28, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 2, 5, 6, 2),
    gsSPNTriangles_5b(6, 7, 2, 7, 8, 2, 9, 10, 2, 11, 12, 2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_ufo_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(7, 13, 14, 15, 16, 17, 15, 18, 19, 15),
    gsSPNTriangles_5b(20, 21, 15, 22, 23, 15, 24, 25, 15, 26, 27, 15),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_ufo_mado_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPVertex(&int_tak_ufo_v[28], 15, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 3, 4, 0, 5, 6),
    gsSPNTriangles_5b(0, 7, 8, 9, 10, 0, 11, 12, 0, 13, 14, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_ufo_off_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_ufo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_ufo_asi_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_ufo_v[43], 27, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 4, 0, 5, 6),
    gsSPNTriangles_5b(0, 7, 8, 9, 10, 11, 9, 12, 13, 9, 14, 15),
    gsSPNTriangles_5b(9, 16, 17, 18, 19, 20, 21, 22, 20, 23, 24, 20),
    gsSPNTriangles_5b(25, 26, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_ufo_hikari_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_ufo_v[70], 21, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_tak_ufo_tbl[] = { 0, 4, 0, 0 };

s16 cKF_kn_int_tak_ufo_tbl[] = { 2 };

s16 cKF_c_int_tak_ufo_tbl[] = { 0, -1800, 0, 0, 0, 0, 0, 900, 0, 0, 50, 0, 0, 0 };

s16 cKF_ds_int_tak_ufo_tbl[] = { 1, 0, -1085, 200, -7200, -1085 };

cKF_Animation_R_c cKF_ba_r_int_tak_ufo = {
    cKF_ckcb_r_int_tak_ufo_tbl, cKF_ds_int_tak_ufo_tbl, cKF_kn_int_tak_ufo_tbl, cKF_c_int_tak_ufo_tbl, -1, 200
};

cKF_Joint_R_c cKF_je_r_int_tak_ufo_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 63736, 0 } },
                                             { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { int_tak_ufo_off_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } },
                                             { int_tak_ufo_on_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_tak_ufo = { ARRAY_COUNT(cKF_je_r_int_tak_ufo_tbl), 2, cKF_je_r_int_tak_ufo_tbl };
