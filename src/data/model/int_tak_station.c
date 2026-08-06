#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_station_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_station_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_station_pal[] = {
#include "assets/int_tak_station_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_station_wa_tex_txt[0x200];
#else
u8 int_tak_station_wa_tex_txt[] = {
#include "assets/int_tak_station_wa_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_station_side_tex_txt[0x80];
#else
u8 int_tak_station_side_tex_txt[] = {
#include "assets/int_tak_station_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_station_bou_tex_txt[0x80];
#else
u8 int_tak_station_bou_tex_txt[] = {
#include "assets/int_tak_station_bou_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_station_top_tex_txt[0x80];
#else
u8 int_tak_station_top_tex_txt[] = {
#include "assets/int_tak_station_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_station_mado_tex_txt[0x80];
#else
u8 int_tak_station_mado_tex_txt[] = {
#include "assets/int_tak_station_mado_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_station_v[0x460 / sizeof(Vtx)];
#else
Vtx int_tak_station_v[] = {
#include "assets/int_tak_station_v.inc"
};
#endif

Gfx int_tak_station_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_station_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_tak_station_wa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_station_v, 18, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_station_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 380, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 8, 9, 10, 11, 12, 9, 13, 14, 15),
    gsSPNTriangles_5b(16, 15, 12, 10, 17, 8, 9, 8, 11, 15, 16, 13),
    gsSPNTriangles_5b(12, 11, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_station_bou_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 60),
    gsSPVertex(&int_tak_station_v[18], 22, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 6, 7, 0),
    gsSPNTriangles_5b(2, 1, 4, 0, 7, 1, 8, 9, 10, 11, 12, 13),
    gsSPNTriangles_5b(14, 10, 12, 15, 9, 8, 8, 10, 14, 12, 11, 14),
    gsSPNTriangles_5b(4, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_station_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 19, 20, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_station_mado_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 444, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_station_v[40], 30, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 5, 6, 7, 4),
    gsSPNTriangles_5b(8, 2, 7, 9, 5, 10, 11, 10, 12, 13, 12, 14),
    gsSPNTriangles_5b(15, 16, 17, 16, 18, 19, 18, 20, 21, 22, 23, 24),
    gsSPNTriangles_5b(25, 22, 26, 23, 27, 28, 20, 25, 29, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_tak_station_tbl[] = { 0, 0, 4 };

s16 cKF_kn_int_tak_station_tbl[] = { 2 };

s16 cKF_c_int_tak_station_tbl[] = { 330, 1000, 330, -150, 0, 150, 0, 0, 900, 0, 0 };

s16 cKF_ds_int_tak_station_tbl[] = { 1, 0, 90, 1200, 3600, 90 };

cKF_Animation_R_c cKF_ba_r_int_tak_station = { cKF_ckcb_r_int_tak_station_tbl,
                                               cKF_ds_int_tak_station_tbl,
                                               cKF_kn_int_tak_station_tbl,
                                               cKF_c_int_tak_station_tbl,
                                               -1,
                                               1200 };

cKF_Joint_R_c cKF_je_r_int_tak_station_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 330, 1000, 330 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_tak_station_on_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_tak_station = { ARRAY_COUNT(cKF_je_r_int_tak_station_tbl), 1,
                                              cKF_je_r_int_tak_station_tbl };
