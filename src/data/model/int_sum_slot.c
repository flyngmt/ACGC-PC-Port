#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_slot_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_slot_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_slot_pal[] = {
#include "assets/int_sum_slot_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_slot_reel1_TA_tex_txt[0x100];
#else
u8 int_sum_slot_reel1_TA_tex_txt[] = {
#include "assets/int_sum_slot_reel1_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_slot_reel2_TA_tex_txt[0x100];
#else
u8 int_sum_slot_reel2_TA_tex_txt[] = {
#include "assets/int_sum_slot_reel2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_slot_leverbase_tex_txt[0x100];
#else
u8 int_sum_slot_leverbase_tex_txt[] = {
#include "assets/int_sum_slot_leverbase_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_slot_lever_tex_txt[0x100];
#else
u8 int_sum_slot_lever_tex_txt[] = {
#include "assets/int_sum_slot_lever_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_slot_side_tex_txt[0x100];
#else
u8 int_sum_slot_side_tex_txt[] = {
#include "assets/int_sum_slot_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_slot_front_tex_txt[0x300];
#else
u8 int_sum_slot_front_tex_txt[] = {
#include "assets/int_sum_slot_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_slot_foot_tex_txt[0x100];
#else
u8 int_sum_slot_foot_tex_txt[] = {
#include "assets/int_sum_slot_foot_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_slot_v[0x470 / sizeof(Vtx)];
#else
Vtx int_sum_slot_v[] = {
#include "assets/int_sum_slot_v.inc"
};
#endif

Gfx int_sum_slot_reel_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_slot_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 380),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_slot_v, 18, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 0, 4, 5),
    gsSPNTriangles_5b(0, 5, 1, 6, 7, 8, 6, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 6, 9, 14, 9, 15, 4, 16, 17),
    gsSPNTriangles_5b(4, 17, 5, 14, 15, 17, 14, 17, 16, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_slot_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_slot_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_slot_leverbase_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_slot_v[23], 25, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 1, 0, 4),
    gsSPNTriangles_5b(5, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 6, 7, 8, 6, 8, 9, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_slot_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 252),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 10, 11, 12, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 13, 14, 15, 13, 15, 16, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 17, 18, 19, 18, 20, 21, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 22, 23, 24, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_sum_slot_v[48], 23, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 0, 2, 5, 0, 7, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 8, 9, 10, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_slot_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 11, 12, 13, 11, 14, 15, 13, 16, 11),
    gsSPNTriangles_5b(15, 12, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_slot_foot_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 17, 18, 19, 20, 21, 22, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_slot_lever_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_slot_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_slot_lever_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_slot_v[18], 5, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_slot_tbl[] = { 0, 0, 0, 2, 4 };

s16 cKF_kn_int_sum_slot_tbl[] = { 11, 6 };

s16 cKF_c_int_sum_slot_tbl[] = { 0, 1250, 100, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 900 };

s16 cKF_ds_int_sum_slot_tbl[] = { 1,    0,   -98,  3,    -13,    -393, 16,   -746,   -3008, 17,  -850,   -2237, 18,
                                  -895, 185, 20,   -707, 4584,   22,   -344, 5387,   24,    -48, 2595,   25,    0,
                                  724,  26,  0,    0,    121,    0,    0,    1,      0,     4,   27,     4,     -106,
                                  29,   -10, -447, 115,  -14395, -327, 117,  -14400, 0,     121, -14400, 0 };

cKF_Animation_R_c cKF_ba_r_int_sum_slot = {
    cKF_ckcb_r_int_sum_slot_tbl, cKF_ds_int_sum_slot_tbl, cKF_kn_int_sum_slot_tbl, cKF_c_int_sum_slot_tbl, -1, 121
};

cKF_Joint_R_c cKF_je_r_int_sum_slot_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 1250, 100 } },
                                              { int_sum_slot_base_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2050, 0, 65436 } },
                                              { int_sum_slot_lever_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { int_sum_slot_reel_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2050, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_sum_slot = { ARRAY_COUNT(cKF_je_r_int_sum_slot_tbl), 3, cKF_je_r_int_sum_slot_tbl };
