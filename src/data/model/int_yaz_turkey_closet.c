#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_yaz_turkey_closet_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_yaz_turkey_closet_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_yaz_turkey_closet_pal[] = {
#include "assets/int_yaz_turkey_closet_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_turkey_closet_door_tex_txt[0x100];
#else
u8 int_yaz_turkey_closet_door_tex_txt[] = {
#include "assets/int_yaz_turkey_closet_door_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_turkey_closet_knob_tex_txt[0x80];
#else
u8 int_yaz_turkey_closet_knob_tex_txt[] = {
#include "assets/int_yaz_turkey_closet_knob_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_turkey_closet_back_tex_txt[0x100];
#else
u8 int_yaz_turkey_closet_back_tex_txt[] = {
#include "assets/int_yaz_turkey_closet_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_turkey_closet_side2_tex_txt[0x100];
#else
u8 int_yaz_turkey_closet_side2_tex_txt[] = {
#include "assets/int_yaz_turkey_closet_side2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_turkey_closet_asi_tex_txt[0x40];
#else
u8 int_yaz_turkey_closet_asi_tex_txt[] = {
#include "assets/int_yaz_turkey_closet_asi_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_turkey_closet_frnt_tex_txt[0x400];
#else
u8 int_yaz_turkey_closet_frnt_tex_txt[] = {
#include "assets/int_yaz_turkey_closet_frnt_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_yaz_turkey_closet_v[0x4E0 / sizeof(Vtx)];
#else
Vtx int_yaz_turkey_closet_v[] = {
#include "assets/int_yaz_turkey_closet_v.inc"
};
#endif

Gfx int_yaz_turkey_closet_doorL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yaz_turkey_closet_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_yaz_turkey_closet_door_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_yaz_turkey_closet_v, 6, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_yaz_turkey_closet_knob_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 3, 4, 5, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_yaz_turkey_closet_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yaz_turkey_closet_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_yaz_turkey_closet_knob_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_yaz_turkey_closet_v[12], 16, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_yaz_turkey_closet_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(2, 3, 4, 5, 3, 5, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_yaz_turkey_closet_side2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(9, 7, 8, 9, 7, 10, 11, 12, 13, 10),
    gsSPNTriangles_5b(14, 11, 10, 8, 7, 15, 10, 9, 12, 10, 13, 14),
    gsSPNTriangles_5b(11, 15, 7, 9, 10, 7, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, int_yaz_turkey_closet_asi_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_yaz_turkey_closet_v[28], 28, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 4, 6, 5),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 10, 13, 11, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(25, 27, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_yaz_turkey_closet_side2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&int_yaz_turkey_closet_v[56], 22, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 10, 9),
    gsSPNTriangles_5b(12, 9, 13, 3, 14, 15, 3, 15, 0, 13, 15, 14),
    gsSPNTriangles_5b(13, 14, 12, 11, 16, 17, 11, 17, 8, 7, 2, 1),
    gsSPNTriangles_5b(7, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_yaz_turkey_closet_frnt_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsSPNTrianglesInit_5b(2, 18, 19, 20, 18, 20, 21, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_yaz_turkey_closet_doorR_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yaz_turkey_closet_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_yaz_turkey_closet_door_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_yaz_turkey_closet_v[6], 6, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_yaz_turkey_closet_knob_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 3, 4, 5, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_yaz_turkey_closet_tbl[] = { 56, 7, 0, 7, 7 };

s16 cKF_kn_int_yaz_turkey_closet_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 3 };

s16 cKF_c_int_yaz_turkey_closet_tbl[] = { -900, 0, 0, 0, 0, 900 };

s16 cKF_ds_int_yaz_turkey_closet_tbl[] = { 1,    -1450, 0,  12,   -1450, 0,    1,  3625, 0,    12,    3625, 0,    1,
                                           -60,  0,     12, -60,  0,     1,    0,  0,    12,   0,     0,    1,    0,
                                           0,    12,    0,  0,    1,     -900, 0,  12,   -900, 0,     1,    0,    0,
                                           12,   0,     0,  1,    0,     0,    12, 0,    0,    1,     1800, 0,    6,
                                           2250, 3785,  12, 2850, 0,     1,    0,  0,    12,   0,     0,    1,    0,
                                           0,    12,    0,  0,    1,     900,  0,  6,    450,  -3818, 12,   -150, 0 };

cKF_Animation_R_c cKF_ba_r_int_yaz_turkey_closet = { cKF_ckcb_r_int_yaz_turkey_closet_tbl,
                                                     cKF_ds_int_yaz_turkey_closet_tbl,
                                                     cKF_kn_int_yaz_turkey_closet_tbl,
                                                     cKF_c_int_yaz_turkey_closet_tbl,
                                                     -1,
                                                     12 };

cKF_Joint_R_c cKF_je_r_int_yaz_turkey_closet_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 64086, 3625, 65476 } },
    { int_yaz_turkey_closet_body_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1500, 2900, 0 } },
    { int_yaz_turkey_closet_doorR_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_yaz_turkey_closet_doorL_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1500, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_yaz_turkey_closet = { ARRAY_COUNT(cKF_je_r_int_yaz_turkey_closet_tbl), 3,
                                                    cKF_je_r_int_yaz_turkey_closet_tbl };
