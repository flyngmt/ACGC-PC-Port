#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_balloon8_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_balloon8_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_balloon8_pal[] = {
#include "assets/int_nog_balloon8_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_balloon8_weight_tex_txt[0x100];
#else
u8 int_nog_balloon8_weight_tex_txt[] = {
#include "assets/int_nog_balloon8_weight_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_balloon1_wire_tex_txt[0x80];
#else
static u8 tol_balloon1_wire_tex_txt[] = {
#include "assets/int_nog_balloon8/tol_balloon1_wire_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_balloon85_head_tex_rgb_ia8[0x400];
#else
u8 int_nog_balloon85_head_tex_rgb_ia8[] = {
#include "assets/int_nog_balloon85_head_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_balloon8_v[0xE20 / sizeof(Vtx)];
#else
Vtx int_nog_balloon8_v[] = {
#include "assets/int_nog_balloon8_v.inc"
};
#endif

Gfx int_nog_balloon8_weight_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_balloon8_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_nog_balloon8_weight_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_balloon8_v, 28, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 2, 3, 0, 3, 4, 5),
    gsSPNTriangles_5b(5, 0, 3, 6, 7, 8, 8, 9, 6, 9, 2, 1),
    gsSPNTriangles_5b(1, 6, 9, 7, 10, 11, 11, 8, 7, 12, 11, 10),
    gsSPNTriangles_5b(10, 13, 12, 14, 15, 16, 14, 16, 17, 14, 17, 18),
    gsSPNTriangles_5b(14, 18, 19, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_balloon8_a_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloon1_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_balloon8_v[218], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_balloon8_b_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloon1_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_balloon8_v[200], 4, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloon1_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_balloon8_v[204], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 1, 6, 7, 0, 1, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_balloon8_c_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloon1_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_balloon8_v[182], 4, 0),
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloon1_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_balloon8_v[186], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 0, 1, 6, 1, 7, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_balloon8_head_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(255, 100, 0, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, int_nog_balloon85_head_tex_rgb_ia8),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_balloon8_v[28], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(6, 8, 9, 10, 11, 12, 12, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(18, 19, 10, 18, 16, 15, 20, 17, 21, 22, 0, 23),
    gsSPNTriangles_5b(21, 7, 20, 0, 24, 23, 25, 26, 27, 28, 26, 25),
    gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_balloon8_v[60], 32, 0),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 8, 7, 4, 3, 10, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(9, 2, 17, 18, 14, 10, 19, 20, 17, 15, 14, 18),
    gsSPNTriangles_5b(8, 21, 22, 23, 24, 3, 10, 25, 4, 8, 9, 21),
    gsSPNTriangles_5b(8, 26, 6, 10, 27, 18, 18, 27, 28, 24, 23, 28),
    gsSPNTriangles_5b(29, 30, 31, 17, 20, 13, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_balloon8_v[92], 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(6, 8, 9, 10, 11, 12, 13, 10, 14, 1, 0, 15),
    gsSPNTriangles_5b(1, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25),
    gsSPNTriangles_5b(23, 25, 26, 9, 8, 26, 13, 4, 11, 24, 23, 27),
    gsSPNTriangles_5b(28, 21, 29, 25, 24, 5, 29, 21, 20, 29, 15, 0),
    gsSPNTriangles_5b(5, 30, 31, 5, 24, 3, 5, 4, 13, 0, 0, 0),
    gsSPVertex(&int_nog_balloon8_v[124], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 5, 7),
    gsSPNTriangles_5b(2, 8, 0, 7, 9, 6, 5, 4, 7, 9, 7, 10),
    gsSPNTriangles_5b(11, 12, 13, 14, 15, 16, 14, 16, 17, 14, 18, 5),
    gsSPNTriangles_5b(19, 20, 21, 19, 21, 22, 20, 19, 23, 0, 24, 1),
    gsSPNTriangles_5b(1, 24, 25, 26, 27, 28, 29, 30, 31, 0, 0, 0),
    gsSPVertex(&int_nog_balloon8_v[156], 26, 0),
    gsSPNTrianglesInit_5b(35, 0, 1, 2, 1, 3, 2, 4, 3, 1),
    gsSPNTriangles_5b(5, 4, 1, 6, 5, 1, 7, 8, 9, 8, 10, 9),
    gsSPNTriangles_5b(10, 3, 9, 9, 3, 4, 11, 9, 4, 12, 11, 4),
    gsSPNTriangles_5b(8, 13, 10, 13, 14, 10, 14, 3, 10, 2, 3, 14),
    gsSPNTriangles_5b(15, 2, 14, 16, 15, 14, 17, 15, 16, 17, 18, 15),
    gsSPNTriangles_5b(17, 19, 18, 20, 19, 17, 20, 17, 13, 20, 13, 21),
    gsSPNTriangles_5b(22, 11, 12, 22, 23, 11, 22, 19, 23, 23, 19, 20),
    gsSPNTriangles_5b(23, 20, 8, 23, 8, 7, 24, 5, 25, 24, 22, 5),
    gsSPNTriangles_5b(24, 19, 22, 18, 19, 24, 18, 24, 0, 18, 0, 15),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_nog_balloon8_tbl[] = { 0, 0, 3, 3, 3, 3 };

s16 cKF_kn_int_nog_balloon8_tbl[] = { 5, 5, 4, 5, 5, 6, 4, 5 };

s16 cKF_c_int_nog_balloon8_tbl[] = { 0, 0, 0, 0, 0, 0, 0, -900, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_nog_balloon8_tbl[] = { 1,  -50,  10,   19, 15,   144,  34, 47,   -54, 60, -50,  -19,  61, -50,  -10,
                                      1,  1000, -20,  10, 957,  -252, 32, 801,  38,  60, 999,  38,   61, 1000, 20,
                                      1,  48,   -273, 22, -99,  38,   52, 99,   -38, 61, 48,   -260, 1,  -96,  546,
                                      11, 96,   532,  22, 199,  -76,  52, -199, 76,  61, -96,  519,  1,  72,   389,
                                      12, 149,  -57,  42, -149, 57,   60, 59,   417, 61, 72,   409,  1,  -144, -779,
                                      7,  -271, -415, 13, -292, 223,  41, 300,  0,   60, -117, -835, 61, -144, -819,
                                      1,  -52,  -161, 11, -72,  68,   40, 74,   -42, 61, -52,  -176, 1,  103,  322,
                                      10, 148,  -85,  39, -150, 29,   60, 91,   365, 61, 103,  352 };

cKF_Animation_R_c cKF_ba_r_int_nog_balloon8 = { cKF_ckcb_r_int_nog_balloon8_tbl,
                                                cKF_ds_int_nog_balloon8_tbl,
                                                cKF_kn_int_nog_balloon8_tbl,
                                                cKF_c_int_nog_balloon8_tbl,
                                                -1,
                                                61 };

cKF_Joint_R_c cKF_je_r_int_nog_balloon8_tbl[] = {
    { int_nog_balloon8_weight_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 500, 0 } },
    { int_nog_balloon8_a_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_nog_balloon8_b_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 875, 0, 0 } },
    { int_nog_balloon8_c_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 875, 0, 0 } },
    { int_nog_balloon8_head_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 875, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_nog_balloon8 = { ARRAY_COUNT(cKF_je_r_int_nog_balloon8_tbl), 5,
                                               cKF_je_r_int_nog_balloon8_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_nog_balloon8_c(void) {
    pc_load_asset("assets/int_nog_balloon8/tol_balloon1_wire_tex_txt.bin", tol_balloon1_wire_tex_txt, 0x80, 0xBCBD80, 0, 0);
}
#endif
