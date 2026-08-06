#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_clchest01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_clchest01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_clchest01_pal[] = {
#include "assets/int_sum_clchest01_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_sum_clchest01_glass_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_sum_clchest01_glass_pic_ci4_pal[] = {
#include "assets/int_sum_clchest01_glass_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clchest01_hiki_txt[0x80];
#else
u8 int_sum_clchest01_hiki_txt[] = {
#include "assets/int_sum_clchest01_hiki_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clchest01_mirback_txt[0x80];
#else
u8 int_sum_clchest01_mirback_txt[] = {
#include "assets/int_sum_clchest01_mirback_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clchest01_front_txt[0x200];
#else
u8 int_sum_clchest01_front_txt[] = {
#include "assets/int_sum_clchest01_front_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clchest01_top_txt[0x80];
#else
u8 int_sum_clchest01_top_txt[] = {
#include "assets/int_sum_clchest01_top_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clchest01_side_txt[0x100];
#else
u8 int_sum_clchest01_side_txt[] = {
#include "assets/int_sum_clchest01_side_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clchest01_stand_txt[0x100];
#else
u8 int_sum_clchest01_stand_txt[] = {
#include "assets/int_sum_clchest01_stand_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clchest01_mirside_txt[0x40];
#else
u8 int_sum_clchest01_mirside_txt[] = {
#include "assets/int_sum_clchest01_mirside_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clchest01_mir_txt[0x80];
#else
u8 int_sum_clchest01_mir_txt[] = {
#include "assets/int_sum_clchest01_mir_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clchest01_glass_txt[0x100];
#else
u8 int_sum_clchest01_glass_txt[] = {
#include "assets/int_sum_clchest01_glass_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_clchest01_v[0x4E0 / sizeof(Vtx)];
#else
Vtx int_sum_clchest01_v[] = {
#include "assets/int_sum_clchest01_v.inc"
};
#endif

Gfx int_sum_clcht1_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_clchest01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_clchest01_hiki_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_clchest01_v, 24, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_clchest01_mirback_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_clcht1_evw_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_clchest01_glass_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_clchest01_glass_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_clchest01_v[74], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_clcht1_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_clchest01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_clchest01_front_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_clchest01_v[24], 30, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_clchest01_top_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_clchest01_side_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_clchest01_stand_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 23, 24, 25, 26, 27, 22),
    gsSPNTriangles_5b(28, 29, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_clchest01_mirside_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_clchest01_v[54], 20, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_clchest01_mirback_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 15, 13, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_clchest01_mir_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 17, 19, 18, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_clchest01_tbl[] = { 56, 7, 0, 7 };

s16 cKF_kn_int_sum_clchest01_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2 };

s16 cKF_c_int_sum_clchest01_tbl[] = { 0, 900, 0, 0, 0, 0 };

s16 cKF_ds_int_sum_clchest01_tbl[] = { 1, 0, 0, 10, 0, 0, 1, -24000, 0, 10, -24000, 0, 1, 1500, 0, 10, 1500, 0,
                                       1, 0, 0, 10, 0, 0, 1, 0,      0, 10, 0,      0, 1, 900,  0, 10, 900,  0,
                                       1, 0, 0, 10, 0, 0, 1, 0,      0, 10, 0,      0, 1, 0,    0, 10, 28,   83 };

cKF_Animation_R_c cKF_ba_r_int_sum_clchest01 = { cKF_ckcb_r_int_sum_clchest01_tbl,
                                                 cKF_ds_int_sum_clchest01_tbl,
                                                 cKF_kn_int_sum_clchest01_tbl,
                                                 cKF_c_int_sum_clchest01_tbl,
                                                 -1,
                                                 10 };

cKF_Joint_R_c cKF_je_r_int_sum_clchest01_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 41536, 1500 } },
    { int_sum_clcht1_base_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_clcht1_evw_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_clcht1_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_clchest01 = { ARRAY_COUNT(cKF_je_r_int_sum_clchest01_tbl), 3,
                                                cKF_je_r_int_sum_clchest01_tbl };
