#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_ham1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_ham1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_ham1_pal[] = {
#include "assets/int_tak_ham1_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_ham1_a1_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_ham1_a1_tex_pic_ci4_pal[] = {
#include "assets/int_tak_ham1_a1_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ham1_maru_tex_txt[0x80];
#else
u8 int_tak_ham1_maru_tex_txt[] = {
#include "assets/int_tak_ham1_maru_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ham1_wa_tex_txt[0x20];
#else
u8 int_tak_ham1_wa_tex_txt[] = {
#include "assets/int_tak_ham1_wa_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ham1_kuzu_tex_txt[0x80];
#else
u8 int_tak_ham1_kuzu_tex_txt[] = {
#include "assets/int_tak_ham1_kuzu_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ham1_cage_tex_txt[0x100];
#else
u8 int_tak_ham1_cage_tex_txt[] = {
#include "assets/int_tak_ham1_cage_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ham1_a1_tex_txt[0x80];
#else
u8 int_tak_ham1_a1_tex_txt[] = {
#include "assets/int_tak_ham1_a1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_ham1_a2_tex_pic_ci4[0x80];
#else
u8 int_tak_ham1_a2_tex_pic_ci4[] = {
#include "assets/int_tak_ham1_a2_tex_pic_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_ham1_v[0x640 / sizeof(Vtx)];
#else
Vtx int_tak_ham1_v[] = {
#include "assets/int_tak_ham1_v.inc"
};
#endif

Gfx int_tak_ham1_wa_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_ham1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_tak_ham1_wa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_ham1_v[4], 18, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 6, 7, 5, 6, 5, 4, 8, 9, 7),
    gsSPNTriangles_5b(8, 7, 6, 10, 11, 12, 10, 12, 13, 14, 15, 11),
    gsSPNTriangles_5b(14, 11, 10, 16, 17, 15, 16, 15, 14, 3, 2, 17),
    gsSPNTriangles_5b(3, 17, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_ham1_maru_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_ham1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_ham1_maru_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_ham1_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_ham1_kuzu_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_ham1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_ham1_kuzu_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_ham1_v[25], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_ham1_cage_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_ham1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_ham1_cage_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_ham1_v[29], 31, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 1, 4, 2),
    gsSPNTriangles_5b(5, 4, 6, 7, 4, 8, 9, 4, 10, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 11, 12, 13, 11, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(15, 17, 18, 19, 20, 21, 19, 21, 22, 23, 24, 25),
    gsSPNTriangles_5b(23, 25, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 27, 28, 29, 27, 29, 30, 0, 0, 0),
    gsSPVertex(&int_tak_ham1_v[60], 28, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 14, 16, 17, 14, 17, 15, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 18, 21, 22, 21, 23, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 26, 27, 0, 0, 0),
    gsSPVertex(&int_tak_ham1_v[88], 12, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 0),
    gsSPNTriangles_5b(4, 0, 3, 6, 7, 8, 6, 8, 9, 7, 10, 11),
    gsSPNTriangles_5b(7, 11, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_ham1_a1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_ham1_a1_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_ham1_v[22], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_tak_ham1_tbl[] = { 0, 0, 0, 1, 0, 1, 0 };

s16 cKF_kn_int_tak_ham1_tbl[] = { 15, 2 };

s16 cKF_c_int_tak_ham1_tbl[] = { 500, 2500, 0, 0, 0, 0, 0, 0, -900, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_tak_ham1_tbl[] = { 1,  -1260, 31,   7,   -1232, 223, 14, -1190, 40,   23, -1217, 176,  32,  -1118, 102,
                                  39, -1121, 274,  46,  -1030, -1,  53, -1125, -335, 62, -1196, -369, 67,  -1239, 93,
                                  72, -1191, 87,   80,  -1255, -21, 89, -1195, 3,    99, -1259, -84,  100, -1260, -45,
                                  1,  0,     1091, 100, 3600,  1091 };

cKF_Animation_R_c cKF_ba_r_int_tak_ham1 = {
    cKF_ckcb_r_int_tak_ham1_tbl, cKF_ds_int_tak_ham1_tbl, cKF_kn_int_tak_ham1_tbl, cKF_c_int_tak_ham1_tbl, -1, 100
};

cKF_Joint_R_c cKF_je_r_int_tak_ham1_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 500, 2500, 0 } },
                                              { int_tak_ham1_cage_model, 3, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1200, 0, 0 } },
                                              { int_tak_ham1_a1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { int_tak_ham1_kuzu_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { int_tak_ham1_maru_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1200, 0, 0 } },
                                              { int_tak_ham1_wa_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_tak_ham1 = { ARRAY_COUNT(cKF_je_r_int_tak_ham1_tbl), 5, cKF_je_r_int_tak_ham1_tbl };
