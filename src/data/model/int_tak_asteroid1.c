#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_asteroid1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_asteroid1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_asteroid1_pal[] = {
#include "assets/int_tak_asteroid1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_asteroid1_body_tex_txt[0x800];
#else
u8 int_tak_asteroid1_body_tex_txt[] = {
#include "assets/int_tak_asteroid1_body_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_asteroid1_v[0x670 / sizeof(Vtx)];
#else
Vtx int_tak_asteroid1_v[] = {
#include "assets/int_tak_asteroid1_v.inc"
};
#endif

Gfx int_tak_asteroid1_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_asteroid1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, int_tak_asteroid1_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_asteroid1_v, 32, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 4, 5, 6, 7, 3),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 1, 14, 2, 15, 16, 17),
    gsSPNTriangles_5b(18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29),
    gsSPVertex(&int_tak_asteroid1_v[30], 32, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 12, 15, 13, 16, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 22, 23, 24, 25, 26, 13, 27, 28, 29),
    gsSPVertex(&int_tak_asteroid1_v[60], 32, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 4, 5, 4, 6, 5),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(19, 16, 18, 20, 21, 22, 23, 24, 25, 26, 27, 28),
    gsSPNTriangles_5b(29, 18, 30, 18, 31, 30, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_tak_asteroid1_v[92], 11, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 4, 5, 4, 6, 5),
    gsSPNTriangles_5b(6, 7, 5, 8, 9, 10, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_tak_asteroid1_tbl[] = { 0, 1, 1, 5 };

s16 cKF_kn_int_tak_asteroid1_tbl[] = { 7, 7, 2, 7 };

s16 cKF_c_int_tak_asteroid1_tbl[] = { 0, 500, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_tak_asteroid1_tbl[] = { 1,   450,   -5,  35,  336,   -117, 57,  306,   57,  103, 449,  -21,
                                       153, 301,   21,  200, 450,   11,   201, 450,   5,   1,   900,  11,
                                       18,  980,   242, 53,  1199,  -41,  103, 901,   41,  153, 1199, -41,
                                       200, 900,   -21, 201, 900,   -11,  1,   0,     540, 201, 3600, 540,
                                       1,   -900,  -5,  35,  -1014, -117, 57,  -1044, 57,  103, -901, -21,
                                       153, -1049, 21,  200, -900,  11,   201, -900,  5 };

cKF_Animation_R_c cKF_ba_r_int_tak_asteroid1 = { cKF_ckcb_r_int_tak_asteroid1_tbl,
                                                 cKF_ds_int_tak_asteroid1_tbl,
                                                 cKF_kn_int_tak_asteroid1_tbl,
                                                 cKF_c_int_tak_asteroid1_tbl,
                                                 -1,
                                                 201 };

cKF_Joint_R_c cKF_je_r_int_tak_asteroid1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 500, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1414, 0, 0 } },
    { int_tak_asteroid1_on_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1414, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_tak_asteroid1 = { ARRAY_COUNT(cKF_je_r_int_tak_asteroid1_tbl), 1,
                                                cKF_je_r_int_tak_asteroid1_tbl };
