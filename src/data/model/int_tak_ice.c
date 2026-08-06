#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_ice_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_ice_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_ice_pal[] = {
#include "assets/int_tak_ice_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ice_bou2_tex_txt[0x40];
#else
u8 int_tak_ice_bou2_tex_txt[] = {
#include "assets/int_tak_ice_bou2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ice_wa1_tex_txt[0x80];
#else
u8 int_tak_ice_wa1_tex_txt[] = {
#include "assets/int_tak_ice_wa1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ice_bou_tex_txt[0x20];
#else
u8 int_tak_ice_bou_tex_txt[] = {
#include "assets/int_tak_ice_bou_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ice_block_tex_txt[0x80];
#else
u8 int_tak_ice_block_tex_txt[] = {
#include "assets/int_tak_ice_block_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ice_top_tex_txt[0x40];
#else
u8 int_tak_ice_top_tex_txt[] = {
#include "assets/int_tak_ice_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ice_body_tex_txt[0x200];
#else
u8 int_tak_ice_body_tex_txt[] = {
#include "assets/int_tak_ice_body_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ice_dai_tex_txt[0x20];
#else
u8 int_tak_ice_dai_tex_txt[] = {
#include "assets/int_tak_ice_dai_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ice_sara_tex_txt[0x80];
#else
u8 int_tak_ice_sara_tex_txt[] = {
#include "assets/int_tak_ice_sara_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ice_cup_tex_txt[0x20];
#else
u8 int_tak_ice_cup_tex_txt[] = {
#include "assets/int_tak_ice_cup_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ice_wa2_tex_txt[0x40];
#else
u8 int_tak_ice_wa2_tex_txt[] = {
#include "assets/int_tak_ice_wa2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ice_yuki_tex_pic_i4[0x100];
#else
u8 int_tak_ice_yuki_tex_pic_i4[] = {
#include "assets/int_tak_ice_yuki_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_ice_v[0x800 / sizeof(Vtx)];
#else
Vtx int_tak_ice_v[] = {
#include "assets/int_tak_ice_v.inc"
};
#endif

Gfx int_tak_ice_rot_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_ice_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, int_tak_ice_bou2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_ice_v, 13, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_ice_wa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 5, 6, 7, 5, 7, 8, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_tak_ice_bou_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 9, 10, 11, 9, 12, 10, 9, 11, 12),
    gsSPNTriangles_5b(11, 10, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_ice_yuki_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0,
                       0, 0, COMBINED),
    gsDPSetEnvColor(200, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 32, int_tak_ice_yuki_tex_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_2_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_ice_v[13], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_ice_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_ice_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_tak_ice_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_ice_v[55], 31, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 6, 8, 4, 6, 5, 7, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_tak_ice_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(16, 9, 10, 11, 9, 11, 12, 13, 14, 15),
    gsSPNTriangles_5b(13, 15, 16, 14, 17, 18, 14, 18, 15, 14, 13, 19),
    gsSPNTriangles_5b(14, 19, 20, 21, 17, 14, 21, 14, 20, 12, 11, 21),
    gsSPNTriangles_5b(12, 21, 20, 22, 12, 20, 22, 20, 19, 23, 24, 25),
    gsSPNTriangles_5b(23, 25, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_tak_ice_dai_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 27, 28, 29, 27, 29, 30, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_ice_sara_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_tak_ice_v[86], 26, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 4, 5, 6, 4, 6, 7, 8, 4, 9),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 11, 13, 9, 11, 7, 14),
    gsSPNTriangles_5b(11, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_tak_ice_cup_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 16, 17, 18, 16, 19, 17, 17, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 21, 23, 24, 19, 25, 20, 20, 25, 24),
    gsSPNTriangles_5b(25, 21, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_tak_ice_bou_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_ice_v[112], 16, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_tak_ice_wa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_ice_block_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 220, 255, 255, 255),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, int_tak_ice_block_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_ice_v[29], 26, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 4, 3, 5),
    gsSPNTriangles_5b(4, 5, 6, 7, 8, 0, 7, 0, 9, 10, 9, 4),
    gsSPNTriangles_5b(10, 4, 11, 12, 10, 11, 12, 11, 13, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 18, 19, 14, 18, 14, 20, 21, 17, 22),
    gsSPNTriangles_5b(21, 22, 23, 24, 20, 21, 24, 21, 25, 20, 14, 17),
    gsSPNTriangles_5b(20, 17, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_tak_ice_tbl[] = { 0, 0, 0, 1, 0, 2 };

s16 cKF_kn_int_tak_ice_tbl[] = { 2, 2 };

s16 cKF_c_int_tak_ice_tbl[] = { -1000, 0, 0, 0, 0, 0, 0, 0, 900, -900, 0, -900, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_tak_ice_tbl[] = { 1, 0, 4500, 25, 3600, 4500, 1, 0, -4500, 25, -3600, -4500 };

cKF_Animation_R_c cKF_ba_r_int_tak_ice = {
    cKF_ckcb_r_int_tak_ice_tbl, cKF_ds_int_tak_ice_tbl, cKF_kn_int_tak_ice_tbl, cKF_c_int_tak_ice_tbl, -1, 25
};

cKF_Joint_R_c cKF_je_r_int_tak_ice_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 64536, 0, 0 } },
                                             { int_tak_ice_base_model, 3, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                             { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 64256, 0 } },
                                             { int_tak_ice_block_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                             { int_tak_ice_yuki_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                             { int_tak_ice_rot_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 3259, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_tak_ice = { ARRAY_COUNT(cKF_je_r_int_tak_ice_tbl), 4, cKF_je_r_int_tak_ice_tbl };
