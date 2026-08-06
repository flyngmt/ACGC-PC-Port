#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_asi_chest02_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_asi_chest02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_asi_chest02_pal[] = {
#include "assets/int_sum_asi_chest02_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_asi_chest02_draw_tex_txt[0x80];
#else
u8 int_sum_asi_chest02_draw_tex_txt[] = {
#include "assets/int_sum_asi_chest02_draw_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_asi_chest02_drawin_tex_txt[0x80];
#else
u8 int_sum_asi_chest02_drawin_tex_txt[] = {
#include "assets/int_sum_asi_chest02_drawin_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_asi_chest02_front_tex_txt[0x300];
#else
u8 int_sum_asi_chest02_front_tex_txt[] = {
#include "assets/int_sum_asi_chest02_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_asi_chest02_side_tex_txt[0x200];
#else
u8 int_sum_asi_chest02_side_tex_txt[] = {
#include "assets/int_sum_asi_chest02_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_asi_chest02_v[0x2F0 / sizeof(Vtx)];
#else
Vtx int_sum_asi_chest02_v[] = {
#include "assets/int_sum_asi_chest02_v.inc"
};
#endif

Gfx int_sum_asi_chest02_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_asi_chest02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_asi_chest02_draw_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_asi_chest02_v, 25, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 0, 2, 4, 3, 2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 5, 6, 7, 5, 7, 8, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_asi_chest02_drawin_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 9, 10, 11, 9, 11, 12, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 13, 14, 15, 13, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(17, 19, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 21, 22, 23, 21, 23, 24, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_asi_chest02_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_asi_chest02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_asi_chest02_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_asi_chest02_v[25], 22, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(5, 6, 7, 5, 8, 6, 8, 9, 6, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_asi_chest02_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 10, 11, 12, 10, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(17, 18, 19, 17, 20, 18, 14, 16, 21, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_asi_chest02_tbl[] = { 56, 7, 7 };

s16 cKF_kn_int_sum_asi_chest02_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2 };

s16 cKF_c_int_sum_asi_chest02_tbl[] = { 0, 900, 0 };

s16 cKF_ds_int_sum_asi_chest02_tbl[] = {
    1,  2000, 0, 10, 2000, 0, 1,  -24000, 0, 10, -24000, 0, 1,  1500, 0, 10, 1500, 0, 1,  0, 0, 10, 0, 0, 1,  0,  0,
    10, 0,    0, 1,  900,  0, 10, 900,    0, 1,  0,      0, 10, 0,    0, 1,  0,    0, 10, 0, 0, 1,  0, 0, 10, 28, 83
};

cKF_Animation_R_c cKF_ba_r_int_sum_asi_chest02 = { cKF_ckcb_r_int_sum_asi_chest02_tbl,
                                                   cKF_ds_int_sum_asi_chest02_tbl,
                                                   cKF_kn_int_sum_asi_chest02_tbl,
                                                   cKF_c_int_sum_asi_chest02_tbl,
                                                   -1,
                                                   10 };

cKF_Joint_R_c cKF_je_r_int_sum_asi_chest02_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 41536, 1500 } },
    { int_sum_asi_chest02_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_asi_chest02_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_asi_chest02 = { ARRAY_COUNT(cKF_je_r_int_sum_asi_chest02_tbl), 2,
                                                  cKF_je_r_int_sum_asi_chest02_tbl };
