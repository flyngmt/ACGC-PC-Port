#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_prores_sandbag01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_prores_sandbag01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_prores_sandbag01_pal[] = {
#include "assets/int_ike_prores_sandbag01_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_ike_prores_sandbag01_bodyic1_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_ike_prores_sandbag01_bodyic1_tex_pic_ci4_pal[] = {
#include "assets/int_ike_prores_sandbag01_bodyic1_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_sandbag01_base3_tex_txt[0x80];
#else
u8 int_ike_prores_sandbag01_base3_tex_txt[] = {
#include "assets/int_ike_prores_sandbag01_base3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_sandbag01_pole3_tex_txt[0x40];
#else
u8 int_ike_prores_sandbag01_pole3_tex_txt[] = {
#include "assets/int_ike_prores_sandbag01_pole3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_sandbag01_base1_tex_txt[0x200];
#else
u8 int_ike_prores_sandbag01_base1_tex_txt[] = {
#include "assets/int_ike_prores_sandbag01_base1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_sandbag01_base2_tex_txt[0x100];
#else
u8 int_ike_prores_sandbag01_base2_tex_txt[] = {
#include "assets/int_ike_prores_sandbag01_base2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_sandbag01_pole2_tex_txt[0x80];
#else
u8 int_ike_prores_sandbag01_pole2_tex_txt[] = {
#include "assets/int_ike_prores_sandbag01_pole2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_sandbag01_pole1_tex_txt[0x80];
#else
u8 int_ike_prores_sandbag01_pole1_tex_txt[] = {
#include "assets/int_ike_prores_sandbag01_pole1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_sandbag01_pole4_tex_txt[0x40];
#else
u8 int_ike_prores_sandbag01_pole4_tex_txt[] = {
#include "assets/int_ike_prores_sandbag01_pole4_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_prores_sandbag01_bodyic1_tex_txt[0x100];
#else
u8 int_ike_prores_sandbag01_bodyic1_tex_txt[] = {
#include "assets/int_ike_prores_sandbag01_bodyic1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_prores_sandbag01_v[0x690 / sizeof(Vtx)];
#else
Vtx int_ike_prores_sandbag01_v[] = {
#include "assets/int_ike_prores_sandbag01_v.inc"
};
#endif

Gfx int_ike_prores_sandbag_chain_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_prores_sandbag01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_prores_sandbag01_base3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_prores_sandbag01_v[33], 4, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_prores_sandbag01_base3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_prores_sandbag01_v[37], 18, 4),
    gsSPNTrianglesInit_5b(2, 1, 4, 3, 2, 5, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 6, 7, 8, 8, 7, 9, 10, 11, 12),
    gsSPNTriangles_5b(12, 11, 13, 14, 15, 16, 17, 15, 14, 18, 19, 20),
    gsSPNTriangles_5b(20, 19, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_prores_sandbag_body_model[] = {
    gsSPTexture(4000, 5000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_prores_sandbag01_bodyic1_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_prores_sandbag01_bodyic1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 2, 1),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(int_ike_prores_sandbag01_v, 27, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 4, 5, 0),
    gsSPNTriangles_5b(5, 1, 0, 6, 7, 4, 7, 5, 4, 8, 9, 6),
    gsSPNTriangles_5b(9, 7, 6, 10, 11, 8, 11, 9, 8, 2, 3, 10),
    gsSPNTriangles_5b(3, 11, 10, 9, 11, 12, 1, 5, 12, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 13, 14, 15, 16, 17, 15, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 18, 19, 20, 21, 22, 19, 23, 24, 25),
    gsSPNTriangles_5b(25, 24, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_ike_prores_sandbag01_v[27], 6, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 4, 0, 2, 5),
    gsSPNTriangles_5b(4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_prores_sandbag_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_prores_sandbag01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_prores_sandbag01_pole3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_prores_sandbag01_v[55], 30, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 1, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_prores_sandbag01_base1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 4, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_prores_sandbag01_base2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 19, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_prores_sandbag01_base3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 23, 24, 25, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_prores_sandbag01_pole2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 26, 27, 28, 26, 29, 27, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_prores_sandbag01_pole1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_prores_sandbag01_v[85], 20, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_prores_sandbag01_pole4_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 11, 9, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_prores_sandbag01_pole3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 12, 15, 13, 16, 17, 18),
    gsSPNTriangles_5b(16, 19, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_ike_prores_sandbag01_tbl[] = { 56, 7, 0 };

s16 cKF_kn_int_ike_prores_sandbag01_tbl[] = { 2, 2, 2, 2, 13, 12 };

s16 cKF_c_int_ike_prores_sandbag01_tbl[] = { 0, 0, -900, 0, 0, 0 };

s16 cKF_ds_int_ike_prores_sandbag01_tbl[] = {
    1,  650, 0,  81, 650, 0,  1,  7500, 0,   81,  7500, 0,  1,   750, 0,  81, 750, 0,  1,  0,  0,  106, 0,   0,  1,
    0,  152, 5,  26, 125, 7,  33, 0,    14,  6,   -149, 23, -23, 0,   31, 3,  155, 39, 26, 0,  49, 7,   -74, 58, -13,
    0,  69,  -2, 54, 78,  10, 1,  95,   0,   -10, 106,  0,  6,   1,   0,  24, 6,   5,  0,  9,  1,  -37, 13,  -3, 0,
    23, 0,   14, 33, 3,   0,  44, 0,    -11, 53,  -2,   0,  63,  0,   10, 70, 1,   0,  89, -1, 0,  106, 0,   0
};

cKF_Animation_R_c cKF_ba_r_int_ike_prores_sandbag01 = { cKF_ckcb_r_int_ike_prores_sandbag01_tbl,
                                                        cKF_ds_int_ike_prores_sandbag01_tbl,
                                                        cKF_kn_int_ike_prores_sandbag01_tbl,
                                                        cKF_c_int_ike_prores_sandbag01_tbl,
                                                        -1,
                                                        106 };

cKF_Joint_R_c cKF_je_r_int_ike_prores_sandbag01_tbl[] = {
    { int_ike_prores_sandbag_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 650, 7500, 750 } },
    { int_ike_prores_sandbag_body_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_ike_prores_sandbag_chain_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_ike_prores_sandbag01 = { ARRAY_COUNT(cKF_je_r_int_ike_prores_sandbag01_tbl), 3,
                                                       cKF_je_r_int_ike_prores_sandbag01_tbl };
