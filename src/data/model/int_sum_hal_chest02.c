#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_hal_chest02_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_hal_chest02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_hal_chest02_pal[] = {
#include "assets/int_sum_hal_chest02_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_chest02_hiki_tex_txt[0x200];
#else
u8 int_sum_hal_chest02_hiki_tex_txt[] = {
#include "assets/int_sum_hal_chest02_hiki_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_chest02_hiite_tex_txt[0x80];
#else
u8 int_sum_hal_chest02_hiite_tex_txt[] = {
#include "assets/int_sum_hal_chest02_hiite_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_chest02_top_tex_txt[0x80];
#else
u8 int_sum_hal_chest02_top_tex_txt[] = {
#include "assets/int_sum_hal_chest02_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_chest02_front_tex_txt[0x300];
#else
u8 int_sum_hal_chest02_front_tex_txt[] = {
#include "assets/int_sum_hal_chest02_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_chest02_back_tex_txt[0x180];
#else
u8 int_sum_hal_chest02_back_tex_txt[] = {
#include "assets/int_sum_hal_chest02_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_chest02_kuki_tex_txt[0x80];
#else
u8 int_sum_hal_chest02_kuki_tex_txt[] = {
#include "assets/int_sum_hal_chest02_kuki_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_hal_chest02_v[0x4E0 / sizeof(Vtx)];
#else
Vtx int_sum_hal_chest02_v[] = {
#include "assets/int_sum_hal_chest02_v.inc"
};
#endif

Gfx int_sum_hal_chest01_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hal_chest02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_hal_chest02_hiki_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_hal_chest02_v, 20, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsSPNTriangles_5b(1, 5, 2, 5, 6, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_chest02_hiite_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(3, 7, 8, 9, 10, 11, 12, 13, 14, 15),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_chest02_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_hal_chest02_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hal_chest02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_chest02_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hal_chest02_v[20], 29, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 7, 6, 8, 6, 9, 10, 11, 8),
    gsSPNTriangles_5b(10, 8, 9, 10, 12, 13, 10, 13, 11, 13, 12, 14),
    gsSPNTriangles_5b(13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_hal_chest02_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(3, 24, 25, 26, 25, 27, 26, 28, 24, 26),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_hal_chest02_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hal_chest02_v[49], 29, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_chest02_kuki_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 5, 6, 7, 8, 9, 10, 11, 12, 13),
    gsSPNTriangles_5b(14, 15, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_chest02_hiite_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 17, 18, 19, 20, 21, 22, 23, 24, 25),
    gsSPNTriangles_5b(26, 27, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_hal_chest02_tbl[] = { 56, 0, 7 };

s16 cKF_kn_int_sum_hal_chest02_tbl[] = { 2, 2, 2, 2, 2, 5 };

s16 cKF_c_int_sum_hal_chest02_tbl[] = { -900, 0, 0, 0, 0, -900 };

s16 cKF_ds_int_sum_hal_chest02_tbl[] = { 1,  1350, 0, 16, 1350, 0, 1,  3625, 0,    16, 3625, 0,    1,  100, 0,
                                         16, 100,  0, 1,  0,    0, 16, 0,    0,    1,  0,    0,    16, 0,   0,
                                         1,  -900, 0, 3,  -900, 0, 5,  -840, 1590, 9,  -500, 3027, 16, 50,  0 };

cKF_Animation_R_c cKF_ba_r_int_sum_hal_chest02 = { cKF_ckcb_r_int_sum_hal_chest02_tbl,
                                                   cKF_ds_int_sum_hal_chest02_tbl,
                                                   cKF_kn_int_sum_hal_chest02_tbl,
                                                   cKF_c_int_sum_hal_chest02_tbl,
                                                   -1,
                                                   16 };

cKF_Joint_R_c cKF_je_r_int_sum_hal_chest02_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1350, 3625, 100 } },
    { int_sum_hal_chest02_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_hal_chest01_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1500, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_hal_chest02 = { ARRAY_COUNT(cKF_je_r_int_sum_hal_chest02_tbl), 2,
                                                  cKF_je_r_int_sum_hal_chest02_tbl };
