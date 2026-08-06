#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_boat_t10_tex_txt[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_boat_t10_tex_txt[] = {
#include "assets/obj_s_boat_t10_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_boat_t11_tex_txt[0x80];
#else
u8 obj_s_boat_t11_tex_txt[] = {
#include "assets/obj_s_boat_t11_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_boat_t9_tex_txt[0xC0];
#else
u8 obj_s_boat_t9_tex_txt[] = {
#include "assets/obj_s_boat_t9_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_boat_t6_tex_txt[0x100];
#else
u8 obj_s_boat_t6_tex_txt[] = {
#include "assets/obj_s_boat_t6_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_boat_t7_tex_txt[0x80];
#else
u8 obj_s_boat_t7_tex_txt[] = {
#include "assets/obj_s_boat_t7_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_boat_t1_tex_txt[0x400];
#else
u8 obj_s_boat_t1_tex_txt[] = {
#include "assets/obj_s_boat_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_boat_t3_tex_txt[0x400];
#else
u8 obj_s_boat_t3_tex_txt[] = {
#include "assets/obj_s_boat_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_boat_t2_tex_txt[0x80];
#else
u8 obj_s_boat_t2_tex_txt[] = {
#include "assets/obj_s_boat_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_boat_t5_tex_txt[0x80];
#else
u8 obj_s_boat_t5_tex_txt[] = {
#include "assets/obj_s_boat_t5_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_boat_t8_tex_txt[0x80];
#else
u8 obj_s_boat_t8_tex_txt[] = {
#include "assets/obj_s_boat_t8_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_boat_t4_tex_txt[0x80];
#else
u8 obj_s_boat_t4_tex_txt[] = {
#include "assets/obj_s_boat_t4_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_boat_water1_pic_i4[0x200];
#else
u8 obj_s_boat_water1_pic_i4[] = {
#include "assets/obj_s_boat_water1_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_boat_water2_pic_i4[0x200];
#else
u8 obj_s_boat_water2_pic_i4[] = {
#include "assets/obj_s_boat_water2_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_boat_v[0x9C0 / sizeof(Vtx)];
#else
Vtx obj_e_boat_v[] = {
#include "assets/obj_e_boat_v.inc"
};
#endif

Gfx obj_e_boat_boat1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, obj_s_boat_t6_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_boat_v[30], 30, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_s_boat_t7_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_s_boat_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(5, 16, 17, 18, 16, 18, 19, 16, 20, 21),
    gsSPNTriangles_5b(16, 21, 17, 20, 22, 21, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_s_boat_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(5, 23, 24, 25, 23, 25, 26, 23, 27, 24),
    gsSPNTriangles_5b(26, 25, 28, 26, 28, 29, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_s_boat_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_boat_v[60], 31, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_s_boat_t5_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_s_boat_t8_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 23, 24, 25, 23, 25, 26, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_s_boat_t4_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 27, 28, 29, 27, 29, 30, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_s_boat_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&obj_e_boat_v[91], 7, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 3, 0, 4, 6, 3, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_boat_water1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED,
                       COMBINED, 0, TEXEL0, 0),
    gsDPSetPrimColor(0, 255, 190, 210, 255, 230),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_s_boat_water2_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_s_boat_water1_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 0, 14),
    gsSPDisplayList(anime_2_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_boat_v[142], 14, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 2, 1, 3, 4, 5, 6),
    gsSPNTriangles_5b(2, 7, 8, 2, 9, 0, 10, 11, 12, 8, 9, 2),
    gsSPNTriangles_5b(3, 7, 2, 8, 13, 10, 6, 13, 8, 8, 12, 9),
    gsSPNTriangles_5b(10, 12, 8, 8, 4, 6, 7, 4, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_boat_water2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED,
                       COMBINED, 0, TEXEL0, 0),
    gsDPSetPrimColor(0, 255, 190, 210, 255, 230),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_s_boat_water2_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_s_boat_water1_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 0, 14),
    gsSPDisplayList(anime_2_txt),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_boat_v[125], 5, 0),
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(&obj_e_boat_v[130], 12, 5),
    gsSPNTrianglesInit_5b(8, 1, 5, 6, 3, 7, 8, 0, 4, 9),
    gsSPNTriangles_5b(4, 10, 11, 0, 12, 13, 4, 2, 14, 3, 1, 15),
    gsSPNTriangles_5b(2, 3, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_boat_water3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED,
                       COMBINED, 0, TEXEL0, 0),
    gsDPSetPrimColor(0, 255, 190, 210, 255, 230),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_s_boat_water2_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_s_boat_water1_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 0, 14),
    gsSPDisplayList(anime_2_txt),
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_boat_v[98], 5, 0),
    gsSPMatrix(&anime_6_mdl[4], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(&obj_e_boat_v[103], 22, 5),
    gsSPNTrianglesInit_5b(8, 0, 1, 5, 0, 6, 7, 1, 2, 8),
    gsSPNTriangles_5b(2, 3, 9, 3, 4, 10, 4, 11, 12, 3, 13, 14),
    gsSPNTriangles_5b(1, 15, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(8, 17, 18, 19, 20, 21, 22, 19, 23, 24),
    gsSPNTriangles_5b(20, 22, 25, 23, 26, 24, 25, 26, 23, 25, 23, 20),
    gsSPNTriangles_5b(24, 17, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_boat_oar1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_s_boat_t10_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_boat_v, 30, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_s_boat_t11_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(6, 6, 7, 8, 6, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 14, 16, 17, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 8, obj_s_boat_t9_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 18, 19, 20, 21, 18, 20, 22, 23, 24),
    gsSPNTriangles_5b(25, 22, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 8, obj_s_boat_t9_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_e_boat_tbl[] = { { obj_e_boat_boat1_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 300, 2200, 61036 } },
                                            { obj_e_boat_oar1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 4000 } },
                                            { obj_e_boat_water1_model, 1, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                            { obj_e_boat_water2_model, 1, cKF_JOINT_FLAG_DISP_XLU, { 8400, 0, 0 } },
                                            { obj_e_boat_water3_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 4600, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_e_boat = { ARRAY_COUNT(cKF_je_r_obj_e_boat_tbl), 5, cKF_je_r_obj_e_boat_tbl };

u8 cKF_ckcb_r_obj_e_boat_tbl[] = { 0, 0, 7, 0, 0, 0, 0 };

s16 cKF_kn_obj_e_boat_tbl[] = { 8, 5, 9 };

s16 cKF_c_obj_e_boat_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 900, 900, -450, 900, 450, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_e_boat_tbl[] = { 1,    904,  648,  13,   1075, 212,  23,   1099, -60,  40,  920, -572, 45,   828,
                                -481, 62,   701,  20,   80,   877,  651,  81,   900,  675, 1,   449,  134,  27,
                                495,  -50,  43,   442,  -124, 67,   405,  49,   81,   449, 132, 1,    -180, 143,
                                5,    -143, 443,  20,   141,  303,  26,   177,  119,  40,  183, -81,  44,   156,
                                -370, 60,   -141, -305, 65,   -173, -137, 81,   -180, 83 };

cKF_Animation_R_c cKF_ba_r_obj_e_boat = {
    cKF_ckcb_r_obj_e_boat_tbl, cKF_ds_obj_e_boat_tbl, cKF_kn_obj_e_boat_tbl, cKF_c_obj_e_boat_tbl, -1, 81
};
