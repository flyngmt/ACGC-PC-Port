#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_log_hatoclk_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_hatoclock_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_hatoclock_pal[] = {
#include "assets/int_sum_hatoclock_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_sum_log_clk_pal[0x20 / sizeof(u16)];
#else
u16 int_sum_log_clk_pal[] = {
#include "assets/int_sum_log_clk_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hatoclock_hari_tex_txt[0x80];
#else
u8 int_sum_hatoclock_hari_tex_txt[] = {
#include "assets/int_sum_hatoclock_hari_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_hatoclk_stand_tex_txt[0x100];
#else
u8 int_sum_log_hatoclk_stand_tex_txt[] = {
#include "assets/int_sum_log_hatoclk_stand_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_hatoclk_base_tex_txt[0x80];
#else
u8 int_sum_log_hatoclk_base_tex_txt[] = {
#include "assets/int_sum_log_hatoclk_base_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_hatoclk_top_tex_txt[0x80];
#else
u8 int_sum_log_hatoclk_top_tex_txt[] = {
#include "assets/int_sum_log_hatoclk_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_hatoclk_front_tex_txt[0x300];
#else
u8 int_sum_log_hatoclk_front_tex_txt[] = {
#include "assets/int_sum_log_hatoclk_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_hatoclk_tana_tex_txt[0x80];
#else
u8 int_sum_log_hatoclk_tana_tex_txt[] = {
#include "assets/int_sum_log_hatoclk_tana_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hatoclock_jyabara_tex_txt[0x80];
#else
u8 int_sum_hatoclock_jyabara_tex_txt[] = {
#include "assets/int_sum_hatoclock_jyabara_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hatoclock_hatoside_tex_txt[0x80];
#else
u8 int_sum_hatoclock_hatoside_tex_txt[] = {
#include "assets/int_sum_hatoclock_hatoside_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hatoclock_hatotop_tex_txt[0x80];
#else
u8 int_sum_hatoclock_hatotop_tex_txt[] = {
#include "assets/int_sum_hatoclock_hatotop_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_hatoclk_door_tex_txt[0x80];
#else
u8 int_sum_log_hatoclk_door_tex_txt[] = {
#include "assets/int_sum_log_hatoclk_door_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_log_hatoclk_v[0x500 / sizeof(Vtx)];
#else
Vtx int_sum_log_hatoclk_v[] = {
#include "assets/int_sum_log_hatoclk_v.inc"
};
#endif

Gfx int_sum_log_hatoclk_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hatoclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hatoclock_hari_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_log_hatoclk_v, 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_log_hatoclk_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_log_clk_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_log_hatoclk_stand_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_log_hatoclk_v[3], 26, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 0, 5, 6, 4),
    gsSPNTrianglesInit_5b(6, 7, 8, 9, 8, 10, 11, 10, 12, 13),
    gsSPNTriangles_5b(14, 15, 12, 14, 16, 17, 16, 18, 19, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_log_hatoclk_base_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 20, 23, 21, 24, 23, 20),
    gsSPNTriangles_5b(24, 25, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_log_hatoclk_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_log_hatoclk_v[29], 28, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_log_hatoclk_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7, 6, 7, 8, 7, 9, 8, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 17, 14, 16, 17, 16, 18),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 19, 20, 21, 22, 19, 21, 23, 22, 21),
    gsSPNTriangles_5b(22, 24, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_log_hatoclk_tana_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 25, 26, 27, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_log_hatoclk_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hatoclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hatoclock_hari_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_log_hatoclk_v[74], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_log_hatoclk_hato1_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_log_hatoclk_v[57], 2, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hatoclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hatoclock_jyabara_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&int_sum_log_hatoclk_v[59], 15, 2),
    gsSPNTrianglesInit_5b(2, 0, 2, 3, 0, 1, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hatoclock_hatoside_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 5, 6, 7, 5, 8, 6, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_log_clk_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_log_hatoclk_base_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 9, 10, 11, 9, 12, 10, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hatoclock_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hatoclock_hatotop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 13, 14, 15, 13, 16, 14, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_log_hatoclk_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_log_clk_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_log_hatoclk_door_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_log_hatoclk_v[77], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_log_hatoclk_tbl[] = { 0, 0, 0, 2, 0, 2, 0, 0, 0 };

s16 cKF_kn_int_sum_log_hatoclk_tbl[] = { 14, 8 };

s16 cKF_c_int_sum_log_hatoclk_tbl[] = { 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, -2700, 0, 0,
                                        0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0,     0, 0 };

s16 cKF_ds_int_sum_log_hatoclk_tbl[] = { 1,     0,    -1662, 2,     -55, -2974, 4,    -394, -6122, 6,    -802,
                                         -5073, 7,    -945,  -2974, 8,   -1000, -831, 9,    -1000, 0,    17,
                                         -1000, 0,    18,    -1000, 839, 19,    -944, 3003, 21,    -602, 6184,
                                         23,    -190, 5124,  24,    -46, 3003,  25,   10,   1678,  1,    100,
                                         31,    6,    91,    -357,  11,  -4,    -533, 13,   -27,   0,    15,
                                         -5,    472,  22,    93,    240, 23,    100,  117,  25,    100,  -37 };

cKF_Animation_R_c cKF_ba_r_int_sum_log_hatoclk = { cKF_ckcb_r_int_sum_log_hatoclk_tbl,
                                                   cKF_ds_int_sum_log_hatoclk_tbl,
                                                   cKF_kn_int_sum_log_hatoclk_tbl,
                                                   cKF_c_int_sum_log_hatoclk_tbl,
                                                   -1,
                                                   25 };

cKF_Joint_R_c cKF_je_r_int_sum_log_hatoclk_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_log_hatoclk_base_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 6900, 65036, 1700 } },
    { int_sum_log_hatoclk_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 54936, 0, 1300 } },
    { int_sum_log_hatoclk_hato1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 5150, 0, 0 } },
    { int_sum_log_hatoclk_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_log_hatoclk_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 5150, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_log_hatoclk = { ARRAY_COUNT(cKF_je_r_int_sum_log_hatoclk_tbl), 5,
                                                  cKF_je_r_int_sum_log_hatoclk_tbl };
