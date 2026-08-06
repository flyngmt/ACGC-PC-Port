#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_fan_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_fan_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_fan_pal[] = {
#include "assets/int_nog_fan_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_fan_net_tex_txt[0x200];
#else
u8 int_nog_fan_net_tex_txt[] = {
#include "assets/int_nog_fan_net_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_fan_motor_tex_txt[0x100];
#else
u8 int_nog_fan_motor_tex_txt[] = {
#include "assets/int_nog_fan_motor_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_fan_hole_tex_txt[0x80];
#else
u8 int_nog_fan_hole_tex_txt[] = {
#include "assets/int_nog_fan_hole_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_fan_fan1_TA_tex_txt[0x100];
#else
u8 int_nog_fan_fan1_TA_tex_txt[] = {
#include "assets/int_nog_fan_fan1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_fan_fan2_TA_tex_txt[0x100];
#else
u8 int_nog_fan_fan2_TA_tex_txt[] = {
#include "assets/int_nog_fan_fan2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_fan_fan3_TA_tex_txt[0x100];
#else
u8 int_nog_fan_fan3_TA_tex_txt[] = {
#include "assets/int_nog_fan_fan3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_fan_bace_tex_txt[0x200];
#else
u8 int_nog_fan_bace_tex_txt[] = {
#include "assets/int_nog_fan_bace_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_fan_pole_tex_txt[0x80];
#else
u8 int_nog_fan_pole_tex_txt[] = {
#include "assets/int_nog_fan_pole_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_fan_v[0x2E0 / sizeof(Vtx)];
#else
Vtx int_nog_fan_v[] = {
#include "assets/int_nog_fan_v.inc"
};
#endif

Gfx head_int_nog_fan_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_fan_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_fan_net_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_fan_v, 26, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 0, 3, 0, 2, 4),
    gsSPNTriangles_5b(0, 5, 6, 5, 0, 4, 0, 6, 7, 3, 0, 8),
    gsSPNTriangles_5b(8, 0, 7, 9, 8, 7, 9, 6, 5, 9, 1, 3),
    gsSPNTriangles_5b(9, 5, 4, 2, 1, 9, 9, 4, 2, 7, 6, 9),
    gsSPNTriangles_5b(3, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_nog_fan_motor_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 10, 11, 12, 13, 14, 15, 10, 12, 16),
    gsSPNTriangles_5b(17, 16, 18, 18, 16, 12, 12, 11, 19, 19, 11, 20),
    gsSPNTriangles_5b(21, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_fan_hole_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 22, 23, 24, 24, 25, 22, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_fan_v[26], 7, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 0, 5, 6, 0),
    gsSPEndDisplayList(),
};

Gfx bece_int_nog_fan_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_fan_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_fan_bace_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_fan_v[33], 13, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 0, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_fan_pole_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(6, 5, 6, 7, 5, 7, 8, 9, 10, 11),
    gsSPNTriangles_5b(11, 10, 6, 5, 11, 6, 9, 12, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_nog_fan_tbl[] = { 0, 3, 2 };

s16 cKF_kn_int_nog_fan_tbl[] = { 2, 2, 3 };

s16 cKF_c_int_nog_fan_tbl[] = { -707, 2500, -707, 0, -450, 0, 0, 0, 0 };

s16 cKF_ds_int_nog_fan_tbl[] = { 1, 0, 0, 321, 0, 0, 1, 0, 0, 321, 0, 0, 1, -450, 0, 161, 450, 0, 321, -450, 0 };

cKF_Animation_R_c cKF_ba_r_int_nog_fan = {
    cKF_ckcb_r_int_nog_fan_tbl, cKF_ds_int_nog_fan_tbl, cKF_kn_int_nog_fan_tbl, cKF_c_int_nog_fan_tbl, -1, 321
};

cKF_Joint_R_c cKF_je_r_int_nog_fan_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 64829, 2500, 64829 } },
                                             { bece_int_nog_fan_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { head_int_nog_fan_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 550, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_nog_fan = { ARRAY_COUNT(cKF_je_r_int_nog_fan_tbl), 2, cKF_je_r_int_nog_fan_tbl };
