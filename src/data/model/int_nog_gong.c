#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_gong_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_gong_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_gong_pal[] = {
#include "assets/int_nog_gong_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_gong_bell_tex_txt[0x100];
#else
u8 int_nog_gong_bell_tex_txt[] = {
#include "assets/int_nog_gong_bell_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_gong_spring_tex_txt[0x200];
#else
u8 int_nog_gong_spring_tex_txt[] = {
#include "assets/int_nog_gong_spring_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_gong_hammer_tex_txt[0x100];
#else
u8 int_nog_gong_hammer_tex_txt[] = {
#include "assets/int_nog_gong_hammer_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_gong_base_tex_txt[0x200];
#else
u8 int_nog_gong_base_tex_txt[] = {
#include "assets/int_nog_gong_base_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_gong_v[0x2E0 / sizeof(Vtx)];
#else
Vtx int_nog_gong_v[] = {
#include "assets/int_nog_gong_v.inc"
};
#endif

Gfx int_nog_gong_bell_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_gong_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_nog_gong_bell_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_gong_v, 16, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 2, 3, 0, 2, 4, 3),
    gsSPNTriangles_5b(2, 5, 4, 1, 5, 2, 6, 7, 8, 7, 9, 8),
    gsSPNTriangles_5b(9, 10, 8, 10, 9, 11, 12, 10, 11, 11, 13, 12),
    gsSPNTriangles_5b(13, 14, 12, 13, 15, 14, 14, 15, 6, 15, 7, 6),
    gsSPEndDisplayList(),
};

Gfx int_nog_gong_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_gong_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_gong_base_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_gong_v[34], 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 3, 2, 6, 3, 6, 7, 8, 0, 3),
    gsSPNTriangles_5b(8, 3, 9, 1, 10, 11, 1, 11, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_gong_spring_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_gong_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_gong_spring_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_gong_v[16], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_gong_hammer_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_gong_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_nog_gong_hammer_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_gong_v[19], 15, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 6, 5, 10, 6, 10, 11, 11, 10, 4),
    gsSPNTriangles_5b(11, 4, 3, 12, 13, 14, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_nog_gong_tbl[] = { 0, 0, 0, 2, 0, 2, 2 };

s16 cKF_kn_int_nog_gong_tbl[] = { 9, 5, 9 };

s16 cKF_c_int_nog_gong_tbl[] = { 0, 0, -500, 0, 0, 900, 0, 0, 0, -450, -900, -450, 0, 0, -450, -900, -450, 0, 0, 0, 0 };

s16 cKF_ds_int_nog_gong_tbl[] = { 1,    -400, 2281, 2,   -324, 1500, 3,    -300, -700, 4,  -371, -2250, 5,  -450,
                                  -291, 6,    -390, 675, 7,    -405, -150, 8,    -400, 75, 10,   -400,  0,  1,
                                  0,    -524, 3,    -25, 22,   5,    0,    333,  8,    0,  -47,  10,    0,  0,
                                  1,    0,    0,    3,   0,    0,    4,    0,    300,  5,  20,   -150,  6,  -10,
                                  -225, 7,    5,    113, 8,    -3,   -56,  9,    1,    38, 10,   0,     -38 };

cKF_Animation_R_c cKF_ba_r_int_nog_gong = {
    cKF_ckcb_r_int_nog_gong_tbl, cKF_ds_int_nog_gong_tbl, cKF_kn_int_nog_gong_tbl, cKF_c_int_nog_gong_tbl, -1, 10
};

cKF_Joint_R_c cKF_je_r_int_nog_gong_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 65036 } },
                                              { int_nog_gong_base_model, 3, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 65036, 500 } },
                                              { int_nog_gong_hammer_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 750, 0 } },
                                              { int_nog_gong_spring_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { int_nog_gong_bell_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 750, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_nog_gong = { ARRAY_COUNT(cKF_je_r_int_nog_gong_tbl), 4, cKF_je_r_int_nog_gong_tbl };
