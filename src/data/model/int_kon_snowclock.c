#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_snowclock_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kon_snowclock_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kon_snowclock_pal[] = {
#include "assets/int_kon_snowclock_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowclock06_tex_txt[0x80];
#else
u8 int_kon_snowclock06_tex_txt[] = {
#include "assets/int_kon_snowclock06_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowclock05_tex_txt[0x80];
#else
u8 int_kon_snowclock05_tex_txt[] = {
#include "assets/int_kon_snowclock05_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowclock07_tex_txt[0x80];
#else
u8 int_kon_snowclock07_tex_txt[] = {
#include "assets/int_kon_snowclock07_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowclock04_tex_txt[0x100];
#else
u8 int_kon_snowclock04_tex_txt[] = {
#include "assets/int_kon_snowclock04_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowclock01_tex_txt[0x200];
#else
u8 int_kon_snowclock01_tex_txt[] = {
#include "assets/int_kon_snowclock01_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowclock02_tex_txt[0x200];
#else
u8 int_kon_snowclock02_tex_txt[] = {
#include "assets/int_kon_snowclock02_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowclock03_tex_txt[0x80];
#else
u8 int_kon_snowclock03_tex_txt[] = {
#include "assets/int_kon_snowclock03_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_snowclock_v[0x410 / sizeof(Vtx)];
#else
Vtx int_kon_snowclock_v[] = {
#include "assets/int_kon_snowclock_v.inc"
};
#endif

Gfx int_kon_snowclock_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_snowclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_snowclock07_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_snowclock_v[14], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_snowclock_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_snowclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_kon_snowclock04_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_snowclock_v[20], 28, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 4, 6, 7, 4, 7, 5, 6, 8, 9),
    gsSPNTriangles_5b(6, 9, 7, 8, 10, 11, 8, 11, 9, 10, 12, 13),
    gsSPNTriangles_5b(10, 13, 11, 14, 15, 16, 14, 16, 17, 18, 14, 17),
    gsSPNTriangles_5b(18, 17, 19, 20, 18, 19, 20, 19, 21, 22, 20, 21),
    gsSPNTriangles_5b(22, 21, 23, 24, 22, 23, 24, 23, 25, 26, 24, 25),
    gsSPNTriangles_5b(26, 25, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_kon_snowclock01_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_snowclock_v[48], 17, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_kon_snowclock02_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_snowclock03_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 9, 11, 12, 11, 13, 14),
    gsSPNTriangles_5b(13, 15, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_snowclock_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_snowclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_snowclock07_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_snowclock_v[17], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_snowclock_arm_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_snowclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_snowclock06_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_snowclock_v, 14, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_snowclock05_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 11, 12, 13, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_kon_snowclock_tbl[] = { 0, 7, 7, 0, 7, 0, 7, 0 };

s16 cKF_kn_int_kon_snowclock_tbl[] = { 2, 2, 2, 3, 3, 5, 2, 2, 2, 2, 2, 2 };

s16 cKF_c_int_kon_snowclock_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_kon_snowclock_tbl[] = { 1,  0,    0,   31, 0,   0,   1,  0,   0,   31, 0,   0,    1,  900,  0,
                                       31, 900,  0,   1,  0,   0,   16, 0,   0,   31, 0,   0,    1,  0,    0,
                                       16, 0,    0,   31, 0,   0,   1,  100, 400, 2,  100, -400, 16, -100, -400,
                                       17, -100, 400, 31, 100, 400, 1,  0,   0,   31, 0,   0,    1,  0,    0,
                                       31, 0,    0,   1,  0,   0,   31, 0,   0,   1,  0,   0,    31, 0,    0,
                                       1,  0,    0,   31, 0,   0,   1,  0,   0,   31, 0,   0 };

cKF_Animation_R_c cKF_ba_r_int_kon_snowclock = { cKF_ckcb_r_int_kon_snowclock_tbl,
                                                 cKF_ds_int_kon_snowclock_tbl,
                                                 cKF_kn_int_kon_snowclock_tbl,
                                                 cKF_c_int_kon_snowclock_tbl,
                                                 -1,
                                                 31 };

cKF_Joint_R_c cKF_je_r_int_kon_snowclock_tbl[] = {
    { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 500, 0 } },
    { int_kon_snowclock_arm_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_kon_snowclock_body_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2875, 0, 0 } },
    { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 2875, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_kon_snowclock = { ARRAY_COUNT(cKF_je_r_int_kon_snowclock_tbl), 4,
                                                cKF_je_r_int_kon_snowclock_tbl };
