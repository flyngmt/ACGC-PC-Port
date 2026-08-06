#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_gomi04_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kon_gomi04_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kon_gomi04_pal[] = {
#include "assets/int_kon_gomi04_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_gomi04_huta_tex_txt[0x100];
#else
u8 int_kon_gomi04_huta_tex_txt[] = {
#include "assets/int_kon_gomi04_huta_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_gomi04_huta2_tex_txt[0x100];
#else
u8 int_kon_gomi04_huta2_tex_txt[] = {
#include "assets/int_kon_gomi04_huta2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_gomi04_yoko_tex_txt[0x80];
#else
u8 int_kon_gomi04_yoko_tex_txt[] = {
#include "assets/int_kon_gomi04_yoko_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_gomi04_ue_tex_txt[0x100];
#else
u8 int_kon_gomi04_ue_tex_txt[] = {
#include "assets/int_kon_gomi04_ue_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_gomi04_naka_tex_txt[0x80];
#else
u8 int_kon_gomi04_naka_tex_txt[] = {
#include "assets/int_kon_gomi04_naka_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_gomi04_sita_tex_txt[0x100];
#else
u8 int_kon_gomi04_sita_tex_txt[] = {
#include "assets/int_kon_gomi04_sita_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_gomi04_v[0x2E0 / sizeof(Vtx)];
#else
Vtx int_kon_gomi04_v[] = {
#include "assets/int_kon_gomi04_v.inc"
};
#endif

Gfx int_kon_gomi04_huta2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_gomi04_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_kon_gomi04_huta2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_gomi04_v[6], 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 3, 4, 5),
    gsSPNTriangles_5b(3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_gomi04_huta_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_gomi04_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_kon_gomi04_huta_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_gomi04_v, 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 3, 4, 5),
    gsSPNTriangles_5b(3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_gomi04_sita_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_gomi04_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_gomi04_yoko_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_gomi04_v[12], 25, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 1, 4, 2),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 6, 9, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_kon_gomi04_ue_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 10, 11, 12, 10, 12, 13, 14, 12, 11),
    gsSPNTriangles_5b(14, 11, 15, 16, 17, 18, 16, 18, 19, 13, 18, 17),
    gsSPNTriangles_5b(13, 17, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_gomi04_naka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 21, 23, 22, 20, 24, 21),
    gsSPNTriangles_5b(24, 23, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_gomi04_sita_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_kon_gomi04_v[37], 9, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 4, 0, 5, 6),
    gsSPNTriangles_5b(0, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_kon_gomi04_tbl[] = { 0, 0, 1, 0 };

s16 cKF_kn_int_kon_gomi04_tbl[] = { 22 };

s16 cKF_c_int_kon_gomi04_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_kon_gomi04_tbl[] = { 1,     -1800, 0,     2,     -1800, 1612,  3,     -1693, 3242,  10,    -1114,
                                    778,   11,    -1100, -45,   14,    -1235, -2473, 24,    -2337, -1780, 26,
                                    -2400, -38,   32,    -2013, 3148,  40,    -1314, 802,   54,    -2156, -1232,
                                    56,    -2200, -38,   61,    -2019, 1854,  70,    -1509, 510,   85,    -2092,
                                    -437,  91,    -1996, 1060,  100,   -1705, 292,   104,   -1721, -380,  116,
                                    -1900, -10,   130,   -1752, 109,   140,   -1799, -78,   141,   -1800, -42 };

cKF_Animation_R_c cKF_ba_r_int_kon_gomi04 = { cKF_ckcb_r_int_kon_gomi04_tbl,
                                              cKF_ds_int_kon_gomi04_tbl,
                                              cKF_kn_int_kon_gomi04_tbl,
                                              cKF_c_int_kon_gomi04_tbl,
                                              -1,
                                              141 };

cKF_Joint_R_c cKF_je_r_int_kon_gomi04_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_kon_gomi04_sita_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_kon_gomi04_huta_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 5000, 0, 0 } },
    { int_kon_gomi04_huta2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_kon_gomi04 = { ARRAY_COUNT(cKF_je_r_int_kon_gomi04_tbl), 3, cKF_je_r_int_kon_gomi04_tbl };
