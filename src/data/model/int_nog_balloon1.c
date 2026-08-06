#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_balloon1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_balloon1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_balloon1_pal[] = {
#include "assets/int_nog_balloon1_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_balloon1_wire_tex_txt[0x80];
#else
static u8 tol_balloon1_wire_tex_txt[] = {
#include "assets/int_nog_balloon1/tol_balloon1_wire_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_balloon1_weight_tex_txt[0x100];
#else
u8 int_nog_balloon1_weight_tex_txt[] = {
#include "assets/int_nog_balloon1_weight_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_balloon1_head_tex_rgb_ia8[0x400];
#else
u8 int_nog_balloon1_head_tex_rgb_ia8[] = {
#include "assets/int_nog_balloon1_head_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_balloon1_v[0x620 / sizeof(Vtx)];
#else
Vtx int_nog_balloon1_v[] = {
#include "assets/int_nog_balloon1_v.inc"
};
#endif

Gfx int_nog_balloon1_weight_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_balloon1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_nog_balloon1_weight_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_balloon1_v[70], 28, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 2, 3, 0, 3, 4, 5),
    gsSPNTriangles_5b(5, 0, 3, 6, 7, 8, 8, 9, 6, 9, 2, 1),
    gsSPNTriangles_5b(1, 6, 9, 7, 10, 11, 11, 8, 7, 12, 11, 10),
    gsSPNTriangles_5b(10, 13, 12, 14, 15, 16, 14, 16, 17, 14, 17, 18),
    gsSPNTriangles_5b(14, 18, 19, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_balloon1_a_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloon1_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_balloon1_v[62], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_balloon1_b_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloon1_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_balloon1_v[44], 4, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloon1_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_balloon1_v[48], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 1, 6, 7, 0, 1, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_balloon1_c_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloon1_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_balloon1_v[26], 4, 0),
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloon1_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_balloon1_v[30], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 0, 1, 6, 1, 7, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_balloon1_head_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(255, 0, 0, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, int_nog_balloon1_head_tex_rgb_ia8),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(int_nog_balloon1_v, 26, 0),
    gsSPNTrianglesInit_5b(36, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(5, 4, 3, 6, 5, 3, 7, 6, 3, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 11, 4, 10, 10, 4, 5, 12, 10, 5),
    gsSPNTriangles_5b(13, 12, 5, 14, 15, 11, 15, 16, 11, 16, 4, 11),
    gsSPNTriangles_5b(2, 4, 16, 17, 2, 16, 18, 17, 16, 19, 17, 18),
    gsSPNTriangles_5b(19, 20, 17, 19, 21, 20, 22, 21, 19, 22, 19, 15),
    gsSPNTriangles_5b(22, 15, 14, 23, 12, 13, 23, 24, 12, 23, 21, 24),
    gsSPNTriangles_5b(24, 21, 22, 24, 22, 9, 24, 9, 8, 25, 6, 7),
    gsSPNTriangles_5b(25, 23, 6, 25, 21, 23, 20, 21, 25, 20, 25, 1),
    gsSPNTriangles_5b(20, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_nog_balloon1_tbl[] = { 0, 0, 3, 3, 3, 3 };

s16 cKF_kn_int_nog_balloon1_tbl[] = { 5, 5, 4, 5, 5, 6, 4, 5 };

s16 cKF_c_int_nog_balloon1_tbl[] = { 0, 0, 0, 0, 0, 0, 0, -900, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_nog_balloon1_tbl[] = { 1,  -50,  10,   19, 15,   144,  34, 47,   -54, 60, -50,  -19,  61, -50,  -10,
                                      1,  1000, -20,  10, 957,  -252, 32, 801,  38,  60, 999,  38,   61, 1000, 20,
                                      1,  48,   -273, 22, -99,  38,   52, 99,   -38, 61, 48,   -260, 1,  -96,  546,
                                      11, 96,   532,  22, 199,  -76,  52, -199, 76,  61, -96,  519,  1,  72,   389,
                                      12, 149,  -57,  42, -149, 57,   60, 59,   417, 61, 72,   409,  1,  -144, -779,
                                      7,  -271, -415, 13, -292, 223,  41, 300,  0,   60, -117, -835, 61, -144, -819,
                                      1,  -52,  -161, 11, -72,  68,   40, 74,   -42, 61, -52,  -176, 1,  103,  322,
                                      10, 148,  -85,  39, -150, 29,   60, 91,   365, 61, 103,  352 };

cKF_Animation_R_c cKF_ba_r_int_nog_balloon1 = { cKF_ckcb_r_int_nog_balloon1_tbl,
                                                cKF_ds_int_nog_balloon1_tbl,
                                                cKF_kn_int_nog_balloon1_tbl,
                                                cKF_c_int_nog_balloon1_tbl,
                                                -1,
                                                61 };

cKF_Joint_R_c cKF_je_r_int_nog_balloon1_tbl[] = {
    { int_nog_balloon1_weight_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 500, 0 } },
    { int_nog_balloon1_a_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_nog_balloon1_b_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 875, 0, 0 } },
    { int_nog_balloon1_c_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 875, 0, 0 } },
    { int_nog_balloon1_head_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 875, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_nog_balloon1 = { ARRAY_COUNT(cKF_je_r_int_nog_balloon1_tbl), 5,
                                               cKF_je_r_int_nog_balloon1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_nog_balloon1_c(void) {
    pc_load_asset("assets/int_nog_balloon1/tol_balloon1_wire_tex_txt.bin", tol_balloon1_wire_tex_txt, 0x80, 0xBC3B00, 0, 0);
}
#endif
