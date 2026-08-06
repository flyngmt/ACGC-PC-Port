#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_mezaclock_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_mezaclock_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_mezaclock_pal[] = {
#include "assets/int_sum_mezaclock_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_mezaclock_hand_tex_txt[0x100];
#else
u8 int_sum_mezaclock_hand_tex_txt[] = {
#include "assets/int_sum_mezaclock_hand_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_mezaclock_hari_tex_txt[0x100];
#else
u8 int_sum_mezaclock_hari_tex_txt[] = {
#include "assets/int_sum_mezaclock_hari_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_mezaclock_foot_tex_txt[0x80];
#else
u8 int_sum_mezaclock_foot_tex_txt[] = {
#include "assets/int_sum_mezaclock_foot_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_mezaclock_kane_tex_txt[0x100];
#else
u8 int_sum_mezaclock_kane_tex_txt[] = {
#include "assets/int_sum_mezaclock_kane_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_mezaclock_top_tex_txt[0x200];
#else
u8 int_sum_mezaclock_top_tex_txt[] = {
#include "assets/int_sum_mezaclock_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_mezaclock_side_tex_txt[0x100];
#else
u8 int_sum_mezaclock_side_tex_txt[] = {
#include "assets/int_sum_mezaclock_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_mezaclock_back_tex_txt[0x100];
#else
u8 int_sum_mezaclock_back_tex_txt[] = {
#include "assets/int_sum_mezaclock_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_mezaclock_tataki_tex_txt[0x80];
#else
u8 int_sum_mezaclock_tataki_tex_txt[] = {
#include "assets/int_sum_mezaclock_tataki_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_mezaclock_v[0x3E0 / sizeof(Vtx)];
#else
Vtx int_sum_mezaclock_v[] = {
#include "assets/int_sum_mezaclock_v.inc"
};
#endif

Gfx int_sum_mezaclock_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_mezaclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_mezaclock_hari_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_mezaclock_v, 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_mezaclock_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_mezaclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_mezaclock_hand_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_mezaclock_v[6], 31, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_mezaclock_foot_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 3, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(11, 12, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_mezaclock_kane_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 13, 14, 15, 16, 15, 14, 17, 15, 16),
    gsSPNTriangles_5b(15, 17, 13, 18, 19, 20, 21, 20, 19, 22, 20, 21),
    gsSPNTriangles_5b(20, 22, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_mezaclock_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 23, 24, 25, 23, 25, 26, 23, 26, 27),
    gsSPNTriangles_5b(23, 27, 28, 23, 28, 29, 23, 29, 30, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_mezaclock_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsSPVertex(&int_sum_mezaclock_v[37], 25, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsSPNTriangles_5b(2, 1, 5, 2, 5, 6, 5, 7, 8, 5, 8, 6),
    gsSPNTriangles_5b(7, 9, 10, 7, 10, 8, 11, 12, 13, 11, 13, 4),
    gsSPNTriangles_5b(0, 11, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_mezaclock_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(6, 14, 15, 16, 14, 16, 17, 14, 18, 19),
    gsSPNTriangles_5b(14, 19, 20, 14, 20, 21, 14, 21, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_mezaclock_tataki_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 22, 23, 24, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_mezaclock_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_mezaclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_mezaclock_hari_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_mezaclock_v[3], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_mezaclock_tbl[] = { 0, 0, 0, 0, 0 };

s16 cKF_c_int_sum_mezaclock_tbl[] = { 0, 1100, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_int_sum_mezaclock = { cKF_ckcb_r_int_sum_mezaclock_tbl, NULL, NULL,
                                                 cKF_c_int_sum_mezaclock_tbl,      -1,   17 };

cKF_Joint_R_c cKF_je_r_int_sum_mezaclock_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 1100, 0 } },
    { int_sum_mezaclock_base_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1280, 0, 0 } },
    { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 1280, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_mezaclock = { ARRAY_COUNT(cKF_je_r_int_sum_mezaclock_tbl), 3,
                                                cKF_je_r_int_sum_mezaclock_tbl };
