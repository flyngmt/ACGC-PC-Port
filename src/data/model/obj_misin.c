#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_misin_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_misin_pal[] = {
#include "assets/obj_misin_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_misin_belt_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_misin_belt_tex_pic_ci4_pal[] = {
#include "assets/obj_misin_belt_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_misin_ito1_tex_txt[0x20];
#else
u8 obj_misin_ito1_tex_txt[] = {
#include "assets/obj_misin_ito1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_misin_ito2_tex_txt[0x40];
#else
u8 obj_misin_ito2_tex_txt[] = {
#include "assets/obj_misin_ito2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_misin_maru_tex_txt[0x80];
#else
u8 obj_misin_maru_tex_txt[] = {
#include "assets/obj_misin_maru_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_misin_jiku_tex_txt[0x20];
#else
u8 obj_misin_jiku_tex_txt[] = {
#include "assets/obj_misin_jiku_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_misin_ana_tex_txt[0x80];
#else
u8 obj_misin_ana_tex_txt[] = {
#include "assets/obj_misin_ana_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_misin_hari_tex_txt[0x80];
#else
u8 obj_misin_hari_tex_txt[] = {
#include "assets/obj_misin_hari_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_misin_ito3_tex_txt[0x100];
#else
u8 obj_misin_ito3_tex_txt[] = {
#include "assets/obj_misin_ito3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_misin_belt_tex_txt[0x80];
#else
u8 obj_misin_belt_tex_txt[] = {
#include "assets/obj_misin_belt_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_misin_v[0x4C0 / sizeof(Vtx)];
#else
Vtx obj_misin_v[] = {
#include "assets/obj_misin_v.inc"
};
#endif

Gfx obj_misin_belt_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_misin_belt_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 32, obj_misin_belt_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_2_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&obj_misin_v[47], 16, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 3, 4, 6, 7, 4, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 6, 12, 13, 6, 13, 7, 14, 15, 10),
    gsSPNTriangles_5b(14, 10, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_misin_ana_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_misin_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_misin_ana_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&obj_misin_v[44], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_misin_ito2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_misin_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, obj_misin_ito2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&obj_misin_v[8], 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 1, 2, 4, 5),
    gsSPNTriangles_5b(2, 1, 4, 6, 7, 8, 6, 9, 7, 5, 9, 6),
    gsSPNTriangles_5b(5, 4, 9, 8, 10, 11, 8, 7, 10, 11, 12, 13),
    gsSPNTriangles_5b(11, 10, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_misin_ito1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_misin_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, obj_misin_ito1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(obj_misin_v, 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_misin_maru_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_misin_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_misin_maru_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&obj_misin_v[22], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_misin_jiku_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_misin_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, obj_misin_jiku_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&obj_misin_v[30], 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 1, 2, 4, 5),
    gsSPNTriangles_5b(2, 1, 4, 6, 7, 8, 6, 9, 7, 5, 9, 6),
    gsSPNTriangles_5b(5, 4, 9, 8, 10, 11, 8, 7, 10, 11, 12, 13),
    gsSPNTriangles_5b(11, 10, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_misin_ito4_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_misin_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, obj_misin_ito3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&obj_misin_v[72], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_misin_ito3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_misin_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, obj_misin_ito3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&obj_misin_v[67], 2, 0),
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, obj_misin_ito3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_misin_v[69], 3, 2),
    gsSPNTrianglesInit_5b(2, 0, 3, 2, 1, 0, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_misin_hari_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_misin_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_misin_hari_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&obj_misin_v[63], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_obj_misin_tbl[] = { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0 };

s16 cKF_kn_obj_misin_tbl[] = { 13, 2, 2 };

s16 cKF_c_obj_misin_tbl[] = { 5950, 6000, 13000, -900, 0,    0, 0, 0, -900, 900, 0, 900, 0, 0, -900, 900, 0, 900, 0, 0,
                              900,  0,    0,     -900, 1800, 0, 0, 0, 0,    0,   0, 0,   0, 0, 0,    0,   0, 0,   0 };

s16 cKF_ds_obj_misin_tbl[] = { 1,   900,   -24,   30,  820,    10,    54,  848, -33,   78,  812,    35,   102,
                               860, -8,    132,   821, 27,     157,   880, 2,   190,   851, 18,     217,  890,
                               -11, 246,   876,   52,  265,    895,   -63, 282, 861,   32,  300,    900,  9,
                               1,   -1884, -2520, 300, -27000, -2520, 1,   -48, -1440, 300, -14400, -1440 };

cKF_Animation_R_c cKF_ba_r_obj_misin = {
    cKF_ckcb_r_obj_misin_tbl, cKF_ds_obj_misin_tbl, cKF_kn_obj_misin_tbl, cKF_c_obj_misin_tbl, -1, 300
};

cKF_Joint_R_c cKF_je_r_obj_misin_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 5950, 6000, 13000 } },
                                           { obj_misin_ana_model, 5, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1000, 2750, 300 } },
                                           { obj_misin_hari_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 900, 2550, 1000 } },
                                           { obj_misin_ito4_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { obj_misin_ito3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 475, 0, 0 } },
                                           { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1000, 64486, 800 } },
                                           { obj_misin_jiku_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { obj_misin_maru_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { obj_misin_ito1_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } },
                                           { obj_misin_ito2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { obj_misin_belt_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_misin = { ARRAY_COUNT(cKF_je_r_obj_misin_tbl), 9, cKF_je_r_obj_misin_tbl };
