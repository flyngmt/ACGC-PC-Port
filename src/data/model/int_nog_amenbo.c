#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_amenbo_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_amenbo_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_amenbo_pal[] = {
#include "assets/int_nog_amenbo_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_nog_amenbo_glass_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_nog_amenbo_glass_tex_pic_ci4_pal[] = {
#include "assets/int_nog_amenbo_glass_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_amenbo_body_tex_txt[0x100];
#else
u8 int_nog_amenbo_body_tex_txt[] = {
#include "assets/int_nog_amenbo_body_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_amenbo_base_tex_txt[0x80];
#else
u8 int_nog_amenbo_base_tex_txt[] = {
#include "assets/int_nog_amenbo_base_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_amenbo_top_tex_txt[0x200];
#else
u8 int_nog_amenbo_top_tex_txt[] = {
#include "assets/int_nog_amenbo_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_amenbo_side_tex_txt[0x200];
#else
u8 int_nog_amenbo_side_tex_txt[] = {
#include "assets/int_nog_amenbo_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_amenbo_water_tex_txt[0x80];
#else
u8 int_nog_amenbo_water_tex_txt[] = {
#include "assets/int_nog_amenbo_water_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_amenbo_glass_tex_txt[0x100];
#else
u8 int_nog_amenbo_glass_tex_txt[] = {
#include "assets/int_nog_amenbo_glass_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_amenbo_v[0x3B0 / sizeof(Vtx)];
#else
Vtx int_nog_amenbo_v[] = {
#include "assets/int_nog_amenbo_v.inc"
};
#endif

Gfx int_nog_amenbo_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_amenbo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_nog_amenbo_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_amenbo_v, 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(1, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_amenbo_water_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_amenbo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_amenbo_water_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_amenbo_v[55], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_amenbo_side_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 140),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_amenbo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_amenbo_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_amenbo_v[41], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 1, 6, 7, 1, 7, 2, 6, 8, 9),
    gsSPNTriangles_5b(6, 9, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_amenbo_komado_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 140),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_amenbo_glass_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_nog_amenbo_glass_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 3),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_amenbo_v[51], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_amenbo_glass_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 70),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_amenbo_glass_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_nog_amenbo_glass_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 5),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_amenbo_v[31], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 7, 6, 1, 7, 1, 0, 4, 8, 9),
    gsSPNTriangles_5b(4, 9, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_amenbo_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_amenbo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_amenbo_base_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_amenbo_v[6], 25, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 1, 0, 0, 4, 3),
    gsSPNTriangles_5b(0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_amenbo_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 5, 6, 7, 6, 8, 7, 9, 10, 11),
    gsSPNTriangles_5b(9, 12, 10, 13, 14, 15, 13, 16, 14, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 21, 22, 23, 21, 23, 24, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_nog_amenbo_tbl[] = { 0, 0, 0, 0, 0, 0, 7 };

s16 cKF_kn_int_nog_amenbo_tbl[] = { 36, 9, 6 };

s16 cKF_c_int_nog_amenbo_tbl[] = { 0, -10000, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_nog_amenbo_tbl[] = { 1,  1350, -4219, 2,  1209, -6750, 4,  591,  -6750, 5,  450,  -2109, 6,  450,  0,
                                    24, 450,  0,     25, 450,  2109,  26, 591,  6750,  28, 1209, 6750,  29, 1350, 2109,
                                    30, 1350, 0,     36, 1350, 0,     37, 1350, 2109,  38, 1491, 6750,  40, 2109, 6750,
                                    41, 2250, 2109,  42, 2250, 0,     48, 2250, 0,     49, 2250, 2109,  50, 2391, 6750,
                                    52, 3009, 6750,  53, 3150, 2109,  54, 3150, 0,     72, 3150, 0,     73, 3150, -2109,
                                    74, 3009, -6750, 76, 2391, -6750, 77, 2250, -2109, 78, 2250, 0,     84, 2250, 0,
                                    85, 2250, -2109, 86, 2109, -6750, 88, 1491, -6750, 89, 1350, -2109, 90, 1350, 0,
                                    97, 1350, 0,     1,  14,   19,    10, 5,    -37,   25, -14,  -28,   31, -9,   37,
                                    49, 14,   28,    57, 6,    -37,   73, -14,  -28,   81, -6,   37,    97, 14,   37,
                                    1,  16,   -38,   36, -28,  -37,   46, -20,  37,    84, 28,   37,    94, 20,   -38,
                                    97, 16,   -37 };

cKF_Animation_R_c cKF_ba_r_int_nog_amenbo = { cKF_ckcb_r_int_nog_amenbo_tbl,
                                              cKF_ds_int_nog_amenbo_tbl,
                                              cKF_kn_int_nog_amenbo_tbl,
                                              cKF_c_int_nog_amenbo_tbl,
                                              -1,
                                              97 };

cKF_Joint_R_c cKF_je_r_int_nog_amenbo_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 55536, 0 } },
    { int_nog_amenbo_base_model, 5, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_nog_amenbo_glass_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_nog_amenbo_komado_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_nog_amenbo_side_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_nog_amenbo_water_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_nog_amenbo_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_nog_amenbo = { ARRAY_COUNT(cKF_je_r_int_nog_amenbo_tbl), 6, cKF_je_r_int_nog_amenbo_tbl };
