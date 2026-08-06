#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_island_hako01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_island_hako01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_island_hako01_pal[] = {
#include "assets/int_ike_island_hako01_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_ike_island_hakoin2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_ike_island_hakoin2_tex_rgb_ci4_pal[] = {
#include "assets/int_ike_island_hakoin2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_ike_island_hakoin3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_ike_island_hakoin3_tex_rgb_ci4_pal[] = {
#include "assets/int_ike_island_hakoin3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_ike_island_hakoin5_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_ike_island_hakoin5_tex_rgb_ci4_pal[] = {
#include "assets/int_ike_island_hakoin5_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_hakotop3_tex_txt[0x80];
#else
u8 int_ike_island_hakotop3_tex_txt[] = {
#include "assets/int_ike_island_hakotop3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_hakotop1_tex_txt[0x100];
#else
u8 int_ike_island_hakotop1_tex_txt[] = {
#include "assets/int_ike_island_hakotop1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_hakotop2_tex_txt[0x80];
#else
u8 int_ike_island_hakotop2_tex_txt[] = {
#include "assets/int_ike_island_hakotop2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_hakoin4_tex_txt[0x80];
#else
u8 int_ike_island_hakoin4_tex_txt[] = {
#include "assets/int_ike_island_hakoin4_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_hakokagi2_tex_txt[0x40];
#else
u8 int_ike_island_hakokagi2_tex_txt[] = {
#include "assets/int_ike_island_hakokagi2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_hakokagi1_tex_txt[0x80];
#else
u8 int_ike_island_hakokagi1_tex_txt[] = {
#include "assets/int_ike_island_hakokagi1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_hakoside1_tex_txt[0x80];
#else
u8 int_ike_island_hakoside1_tex_txt[] = {
#include "assets/int_ike_island_hakoside1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_hakoin1_tex_txt[0x200];
#else
u8 int_ike_island_hakoin1_tex_txt[] = {
#include "assets/int_ike_island_hakoin1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_hakoin2_tex_txt[0x80];
#else
u8 int_ike_island_hakoin2_tex_txt[] = {
#include "assets/int_ike_island_hakoin2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_hakoin3_tex_txt[0x80];
#else
u8 int_ike_island_hakoin3_tex_txt[] = {
#include "assets/int_ike_island_hakoin3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_hakoin5_tex_txt[0x80];
#else
u8 int_ike_island_hakoin5_tex_txt[] = {
#include "assets/int_ike_island_hakoin5_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_island_hako01_v[0x10C0 / sizeof(Vtx)];
#else
Vtx int_ike_island_hako01_v[] = {
#include "assets/int_ike_island_hako01_v.inc"
};
#endif

Gfx int_ike_island_hako01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_island_hako01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_island_hakoin4_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_island_hako01_v[62], 32, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 22, 23, 24, 25, 26, 27, 25, 27, 28),
    gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_ike_island_hako01_v[94], 22, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 18, 19, 20, 18, 20, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_island_hakokagi2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_island_hako01_v[116], 24, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_island_hakokagi1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPVertex(&int_ike_island_hako01_v[140], 29, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 6, 10, 0, 3, 11, 1, 0),
    gsSPNTriangles_5b(11, 0, 10, 3, 2, 6, 3, 6, 9, 10, 8, 7),
    gsSPNTriangles_5b(10, 7, 11, 2, 12, 4, 9, 8, 10, 3, 9, 10),
    gsSPNTriangles_5b(4, 6, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_island_hakoside1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPNTrianglesInit_5b(8, 13, 14, 15, 13, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(17, 19, 20, 21, 22, 23, 21, 23, 24, 25, 26, 27),
    gsSPNTriangles_5b(25, 27, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_island_hakoin1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_island_hako01_v[169], 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 2, 2, 4, 0),
    gsSPNTriangles_5b(2, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_island_hako01_in3_off_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_island_hakoin3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_island_hakoin3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_island_hako01_v[174], 20, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPVertex(&int_ike_island_hako01_v[194], 14, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 11, 12, 13, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_island_hako01_in2_off_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 178, 178, 178, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_island_hakoin5_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_island_hakoin5_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_2_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_island_hako01_v[32], 30, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 8, 11),
    gsSPNTriangles_5b(28, 11, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_island_hako01_in1_off_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 178, 178, 178, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_island_hakoin2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_island_hakoin2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_3_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_island_hako01_v[208], 30, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 8, 11),
    gsSPNTriangles_5b(28, 11, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_ike_island_hako01_v[238], 30, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 8, 11),
    gsSPNTriangles_5b(28, 11, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_island_hako01_top_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_island_hako01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_island_hakotop3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_island_hako01_v, 18, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_island_hakotop1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(12, 4, 5, 6, 4, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 12, 7, 6, 12, 6, 13, 11, 14, 15),
    gsSPNTriangles_5b(11, 15, 8, 13, 15, 14, 13, 14, 12, 16, 17, 10),
    gsSPNTriangles_5b(16, 10, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_island_hakotop2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPVertex(&int_ike_island_hako01_v[18], 14, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(2, 3, 6, 2, 6, 0, 7, 8, 9, 7, 9, 10),
    gsSPNTriangles_5b(11, 7, 10, 11, 10, 12, 12, 13, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_ike_island_hako01_tbl[] = { 0, 0, 1, 0, 0, 0 };

s16 cKF_kn_int_ike_island_hako01_tbl[] = { 8 };

s16 cKF_c_int_ike_island_hako01_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 750, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_ike_island_hako01_tbl[] = { 1,  -1800, 3,    31, -2432, -2007, 35, -2771, -3408, 36, -2894, -1545,
                                           37, -2874, 1027, 38, -2826, 1329,  50, -2784, -840,  51, -2814, -895 };

cKF_Animation_R_c cKF_ba_r_int_ike_island_hako01 = { cKF_ckcb_r_int_ike_island_hako01_tbl,
                                                     cKF_ds_int_ike_island_hako01_tbl,
                                                     cKF_kn_int_ike_island_hako01_tbl,
                                                     cKF_c_int_ike_island_hako01_tbl,
                                                     -1,
                                                     51 };

u8 cKF_ckcb_r_int_ike_island_hako02_tbl[] = { 0, 0, 7, 0, 0, 0 };

s16 cKF_kn_int_ike_island_hako02_tbl[] = { 2, 2, 4 };

s16 cKF_c_int_ike_island_hako02_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 750, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_ike_island_hako02_tbl[] = { 1, 0,     0, 51, 0,     0,    1,  0,     0,    51, 0,     0,
                                           1, -2814, 0, 41, -1770, 2110, 42, -1760, -592, 51, -1800, 130 };

cKF_Animation_R_c cKF_ba_r_int_ike_island_hako02 = { cKF_ckcb_r_int_ike_island_hako02_tbl,
                                                     cKF_ds_int_ike_island_hako02_tbl,
                                                     cKF_kn_int_ike_island_hako02_tbl,
                                                     cKF_c_int_ike_island_hako02_tbl,
                                                     -1,
                                                     51 };

cKF_Joint_R_c cKF_je_r_int_ike_island_hako01_tbl[] = {
    { int_ike_island_hako01_in1_off_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 264, 1900, 64832 } },
    { int_ike_island_hako01_top_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_ike_island_hako01_in2_off_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_ike_island_hako01_in3_off_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_ike_island_hako01_on_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_ike_island_hako01 = { ARRAY_COUNT(cKF_je_r_int_ike_island_hako01_tbl), 5,
                                                    cKF_je_r_int_ike_island_hako01_tbl };
