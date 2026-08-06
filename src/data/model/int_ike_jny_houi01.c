#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_jny_houi01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_houi01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_houi01_pal[] = {
#include "assets/int_ike_jny_houi01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_houijisyaku_tex_txt[0x80];
#else
u8 int_ike_jny_houijisyaku_tex_txt[] = {
#include "assets/int_ike_jny_houijisyaku_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_houi1_tex_txt[0x80];
#else
u8 int_ike_jny_houi1_tex_txt[] = {
#include "assets/int_ike_jny_houi1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_houiface1_tex_txt[0x200];
#else
u8 int_ike_jny_houiface1_tex_txt[] = {
#include "assets/int_ike_jny_houiface1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_houiface2_pic_i4[0x200];
#else
u8 int_ike_jny_houiface2_pic_i4[] = {
#include "assets/int_ike_jny_houiface2_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_jny_houi01_v[0x270 / sizeof(Vtx)];
#else
Vtx int_ike_jny_houi01_v[] = {
#include "assets/int_ike_jny_houi01_v.inc"
};
#endif

Gfx int_ike_jny_houi01_on_hari_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_houi01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_jny_houijisyaku_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_jny_houi01_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 0, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_jny_houi01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_houi01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_jny_houi1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 178, 178, 178, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_jny_houi01_v[4], 26, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 3, 4, 5, 5, 4, 6),
    gsSPNTriangles_5b(7, 8, 4, 4, 8, 6, 1, 0, 8, 8, 0, 6),
    gsSPNTriangles_5b(2, 9, 0, 0, 9, 6, 8, 7, 1, 10, 11, 9),
    gsSPNTriangles_5b(9, 11, 6, 12, 13, 11, 11, 13, 6, 14, 15, 13),
    gsSPNTriangles_5b(13, 15, 6, 16, 5, 15, 15, 5, 6, 11, 10, 12),
    gsSPNTriangles_5b(9, 2, 10, 13, 12, 14, 15, 14, 16, 5, 16, 3),
    gsSPNTriangles_5b(4, 3, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_jny_houiface1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPNTrianglesInit_5b(8, 17, 18, 19, 20, 17, 19, 18, 21, 19),
    gsSPNTriangles_5b(22, 20, 19, 21, 23, 19, 24, 22, 19, 23, 25, 19),
    gsSPNTriangles_5b(25, 24, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_jny_houi01_off_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0,
                       0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 90, 150, 190, 170),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, int_ike_jny_houiface2_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 14, 14),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_jny_houi01_v[30], 9, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 1, 4, 2),
    gsSPNTriangles_5b(5, 3, 2, 4, 6, 2, 7, 5, 2, 6, 8, 2),
    gsSPNTriangles_5b(8, 7, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_ike_jny_houi01_tbl[] = { 0, 0, 7, 7 };

s16 cKF_kn_int_ike_jny_houi01_tbl[] = { 2, 2, 2, 8, 8, 8 };

s16 cKF_c_int_ike_jny_houi01_tbl[] = { 0, -1000, 0, 0, 900, 0, 0, 0, 0 };

s16 cKF_ds_int_ike_jny_houi01_tbl[] = { 1,  0,    0,    21, 0,    0,    1,  0,    0,   21, 0,    0,    1,  900,  0,
                                        21, 900,  0,    1,  0,    0,    4,  -2,   -30, 7,  -6,   -28,  10, -7,   -9,
                                        13, -8,   37,   16, 0,    39,   19, 0,    0,   21, 0,    0,    1,  0,    0,
                                        4,  57,   -429, 7,  -86,  -115, 10, 34,   315, 13, -23,  -142, 16, 6,    78,
                                        19, -7,   -35,  21, 0,    0,    1,  -900, 0,   4,  -917, 61,   7,  -888, 26,
                                        10, -912, -60,  13, -900, 58,   16, -901, -3,  19, -901, 0,    21, -901, 0 };

cKF_Animation_R_c cKF_ba_r_int_ike_jny_houi01 = { cKF_ckcb_r_int_ike_jny_houi01_tbl,
                                                  cKF_ds_int_ike_jny_houi01_tbl,
                                                  cKF_kn_int_ike_jny_houi01_tbl,
                                                  cKF_c_int_ike_jny_houi01_tbl,
                                                  -1,
                                                  21 };

cKF_Joint_R_c cKF_je_r_int_ike_jny_houi01_tbl[] = {
    { int_ike_jny_houi01_off_model, 2, cKF_JOINT_FLAG_DISP_XLU, { 0, 64536, 0 } },
    { int_ike_jny_houi01_on_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_ike_jny_houi01_on_hari_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_ike_jny_houi01 = { ARRAY_COUNT(cKF_je_r_int_ike_jny_houi01_tbl), 3,
                                                 cKF_je_r_int_ike_jny_houi01_tbl };
