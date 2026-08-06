#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_kera_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_kera_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_kera_pal[] = {
#include "assets/int_nog_kera_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_nog_kera_glass_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_nog_kera_glass_tex_pic_ci4_pal[] = {
#include "assets/int_nog_kera_glass_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_kera_body_tex_txt[0x100];
#else
u8 int_nog_kera_body_tex_txt[] = {
#include "assets/int_nog_kera_body_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_kera_base_tex_txt[0x80];
#else
u8 int_nog_kera_base_tex_txt[] = {
#include "assets/int_nog_kera_base_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_kera_top_tex_txt[0x200];
#else
u8 int_nog_kera_top_tex_txt[] = {
#include "assets/int_nog_kera_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_kera_side_tex_txt[0x200];
#else
u8 int_nog_kera_side_tex_txt[] = {
#include "assets/int_nog_kera_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_kera_glass_tex_txt[0x100];
#else
u8 int_nog_kera_glass_tex_txt[] = {
#include "assets/int_nog_kera_glass_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_kera_v[0x370 / sizeof(Vtx)];
#else
Vtx int_nog_kera_v[] = {
#include "assets/int_nog_kera_v.inc"
};
#endif

Gfx int_nog_kera_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_kera_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_nog_kera_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_kera_v, 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_kera_side_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 140),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_kera_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_kera_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_kera_v[41], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 1, 6, 7, 1, 7, 2, 6, 8, 9),
    gsSPNTriangles_5b(6, 9, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_kera_komado_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 140),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_kera_glass_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_nog_kera_glass_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 3),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_kera_v[51], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_kera_glass_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 70),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_kera_glass_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_nog_kera_glass_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 5),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_kera_v[31], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 7, 6, 1, 7, 1, 0, 4, 8, 9),
    gsSPNTriangles_5b(4, 9, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_kera_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_kera_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_kera_base_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_kera_v[6], 25, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 1, 0, 0, 4, 3),
    gsSPNTriangles_5b(0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_kera_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 5, 6, 7, 6, 8, 7, 9, 10, 11),
    gsSPNTriangles_5b(9, 12, 10, 13, 14, 15, 13, 16, 14, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 21, 22, 23, 21, 23, 24, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_nog_kera_tbl[] = { 0, 0, 0, 0, 0, 7 };

s16 cKF_kn_int_nog_kera_tbl[] = { 39, 4, 4 };

s16 cKF_c_int_nog_kera_tbl[] = { 0, -7000, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_nog_kera_tbl[] = {
    1,  50,   -1102, 4,  -41,  -469, 5,  -50, 105,  6,  -34, 750,  8,  34,   750,   9,  50,   0,    13, -50,  0,
    17, 50,   0,     21, -50,  0,    23, 0,   1031, 24, 34,  750,  25, 50,   175,   26, 46,   -222, 36, -146, -222,
    37, -150, 175,   38, -134, 750,  40, -66, 750,  41, -50, 0,    43, -100, -1031, 44, -134, -750, 45, -150, -146,
    46, -144, 333,   56, 144,  333,  57, 150, -146, 58, 134, -750, 60, 66,   -750,  61, 50,   0,    65, 150,  0,
    69, 50,   0,     73, 150,  0,    77, 50,  0,    81, 150, 0,    85, 50,   0,     87, 100,  1031, 88, 134,  750,
    89, 150,  175,   90, 146,  -222, 96, 25,  -722, 97, 2,   -701, 1,  5,    -1,    41, -7,   23,   61, 6,    4,
    97, 5,    0,     1,  10,   -1,   38, -6,  -4,   80, 5,   14,   97, 10,   1
};

cKF_Animation_R_c cKF_ba_r_int_nog_kera = {
    cKF_ckcb_r_int_nog_kera_tbl, cKF_ds_int_nog_kera_tbl, cKF_kn_int_nog_kera_tbl, cKF_c_int_nog_kera_tbl, -1, 97
};

cKF_Joint_R_c cKF_je_r_int_nog_kera_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 58536, 0 } },
                                              { int_nog_kera_base_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { int_nog_kera_glass_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                              { int_nog_kera_komado_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                              { int_nog_kera_side_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                              { int_nog_kera_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_nog_kera = { ARRAY_COUNT(cKF_je_r_int_nog_kera_tbl), 5, cKF_je_r_int_nog_kera_tbl };
