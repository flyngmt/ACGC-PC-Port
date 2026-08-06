#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_fruitchest01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_fruitchest01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_fruitchest01_pal[] = {
#include "assets/int_sum_fruitchest01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruitchest01_hiki_tex_txt[0x80];
#else
u8 int_sum_fruitchest01_hiki_tex_txt[] = {
#include "assets/int_sum_fruitchest01_hiki_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruitchest01_into_tex_txt[0x100];
#else
u8 int_sum_fruitchest01_into_tex_txt[] = {
#include "assets/int_sum_fruitchest01_into_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruitchest01_kuki_tex_txt[0x80];
#else
u8 int_sum_fruitchest01_kuki_tex_txt[] = {
#include "assets/int_sum_fruitchest01_kuki_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruitchest01_front_tex_txt[0x300];
#else
u8 int_sum_fruitchest01_front_tex_txt[] = {
#include "assets/int_sum_fruitchest01_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruitchest01_side_tex_txt[0x200];
#else
u8 int_sum_fruitchest01_side_tex_txt[] = {
#include "assets/int_sum_fruitchest01_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_fruitchest01_v[0x3E0 / sizeof(Vtx)];
#else
Vtx int_sum_fruitchest01_v[] = {
#include "assets/int_sum_fruitchest01_v.inc"
};
#endif

Gfx int_sum_fruitchest01_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_fruitchest01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_fruitchest01_hiki_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_fruitchest01_v, 22, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_fruitchest01_into_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 5, 7, 6, 8, 9, 10),
    gsSPNTriangles_5b(9, 4, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 11, 12, 13, 14, 15, 13, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 19, 20, 21, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_fruitchest01_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_fruitchest01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_fruitchest01_kuki_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_fruitchest01_v[22], 16, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 1, 0, 4, 5, 1),
    gsSPNTriangles_5b(6, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_fruitchest01_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_fruitchest01_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPVertex(&int_sum_fruitchest01_v[38], 24, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 0, 4, 5),
    gsSPNTriangles_5b(0, 5, 1, 4, 6, 7, 4, 7, 5, 6, 8, 9),
    gsSPNTriangles_5b(6, 9, 7, 8, 10, 11, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 12, 15, 16, 15, 17, 18, 16, 17),
    gsSPNTriangles_5b(18, 17, 19, 2, 18, 19, 2, 19, 3, 13, 20, 21),
    gsSPNTriangles_5b(13, 21, 14, 10, 22, 23, 10, 23, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_fruitchest01_tbl[] = { 56, 7, 7 };

s16 cKF_kn_int_sum_fruitchest01_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2 };

s16 cKF_c_int_sum_fruitchest01_tbl[] = { 0, 900, 0 };

s16 cKF_ds_int_sum_fruitchest01_tbl[] = { 1, 0, 0, 10, 0, 0, 1, -24000, 0, 10, -24000, 0, 1, 1175, 0, 10, 1175, 0,
                                          1, 0, 0, 10, 0, 0, 1, 0,      0, 10, 0,      0, 1, 900,  0, 10, 900,  0,
                                          1, 0, 0, 10, 0, 0, 1, 0,      0, 10, 0,      0, 1, 0,    0, 10, 28,   83 };

cKF_Animation_R_c cKF_ba_r_int_sum_fruitchest01 = { cKF_ckcb_r_int_sum_fruitchest01_tbl,
                                                    cKF_ds_int_sum_fruitchest01_tbl,
                                                    cKF_kn_int_sum_fruitchest01_tbl,
                                                    cKF_c_int_sum_fruitchest01_tbl,
                                                    -1,
                                                    10 };

cKF_Joint_R_c cKF_je_r_int_sum_fruitchest01_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 41536, 1175 } },
    { int_sum_fruitchest01_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_fruitchest01_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_fruitchest01 = { ARRAY_COUNT(cKF_je_r_int_sum_fruitchest01_tbl), 2,
                                                   cKF_je_r_int_sum_fruitchest01_tbl };
