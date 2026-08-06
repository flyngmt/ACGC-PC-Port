#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_snowbox_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kon_snowbox_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kon_snowbox_tex_pal[] = {
#include "assets/int_kon_snowbox_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowbox05_tex_txt[0x200];
#else
u8 int_kon_snowbox05_tex_txt[] = {
#include "assets/int_kon_snowbox05_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowbox07_tex_txt[0x80];
#else
u8 int_kon_snowbox07_tex_txt[] = {
#include "assets/int_kon_snowbox07_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowbox03_tex_txt[0x100];
#else
u8 int_kon_snowbox03_tex_txt[] = {
#include "assets/int_kon_snowbox03_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowbox04_tex_txt[0x80];
#else
u8 int_kon_snowbox04_tex_txt[] = {
#include "assets/int_kon_snowbox04_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowbox06_tex_txt[0x80];
#else
u8 int_kon_snowbox06_tex_txt[] = {
#include "assets/int_kon_snowbox06_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowbox01_tex_txt[0x200];
#else
u8 int_kon_snowbox01_tex_txt[] = {
#include "assets/int_kon_snowbox01_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowbox02_tex_txt[0x200];
#else
u8 int_kon_snowbox02_tex_txt[] = {
#include "assets/int_kon_snowbox02_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_snowbox_v[0x3D0 / sizeof(Vtx)];
#else
Vtx int_kon_snowbox_v[] = {
#include "assets/int_kon_snowbox_v.inc"
};
#endif

Gfx int_kon_snowbox_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_snowbox_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kon_snowbox05_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_snowbox_v, 15, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_snowbox07_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 6, 7, 8, 9, 10, 11),
    gsSPNTriangles_5b(12, 13, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_snowbox_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_snowbox_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_kon_snowbox03_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_snowbox_v[15], 28, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 6, 7, 5, 6, 5, 4, 8, 9, 7),
    gsSPNTriangles_5b(8, 7, 6, 10, 11, 9, 10, 9, 8, 12, 13, 11),
    gsSPNTriangles_5b(12, 11, 10, 3, 2, 14, 3, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 17, 20, 17, 16, 22, 23, 21),
    gsSPNTriangles_5b(22, 21, 20, 24, 25, 23, 24, 23, 22, 26, 27, 25),
    gsSPNTriangles_5b(26, 25, 24, 15, 14, 27, 15, 27, 26, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_snowbox04_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_kon_snowbox_v[43], 18, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_snowbox06_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 5, 6, 7, 7, 8, 9, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_kon_snowbox01_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 10, 11, 12, 10, 12, 13, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_kon_snowbox02_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(2, 14, 15, 16, 14, 16, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_kon_snowbox_tbl[] = { 0, 0, 1 };

s16 cKF_kn_int_kon_snowbox_tbl[] = { 7 };

s16 cKF_c_int_kon_snowbox_tbl[] = { 1200, 1375, 0, -900, -900, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_kon_snowbox_tbl[] = { 1,    -900, 0,    2,    -900, 0,  4,    -883, 900, 9,  -500,
                                     3068, 12,   -185, 2935, 15,   32, 1018, 16,   50,  543 };

cKF_Animation_R_c cKF_ba_r_int_kon_snowbox = { cKF_ckcb_r_int_kon_snowbox_tbl,
                                               cKF_ds_int_kon_snowbox_tbl,
                                               cKF_kn_int_kon_snowbox_tbl,
                                               cKF_c_int_kon_snowbox_tbl,
                                               -1,
                                               16 };

cKF_Joint_R_c cKF_je_r_int_kon_snowbox_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1200, 1375, 0 } },
    { int_kon_snowbox_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_kon_snowbox_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1200, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_kon_snowbox = { ARRAY_COUNT(cKF_je_r_int_kon_snowbox_tbl), 2,
                                              cKF_je_r_int_kon_snowbox_tbl };
