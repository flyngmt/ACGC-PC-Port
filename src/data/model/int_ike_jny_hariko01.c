#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_jny_hariko01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_hariko01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_hariko01_pal[] = {
#include "assets/int_ike_jny_hariko01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_harikoface01_tex_txt[0x100];
#else
u8 int_ike_jny_harikoface01_tex_txt[] = {
#include "assets/int_ike_jny_harikoface01_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_harikoear01_tex_txt[0x100];
#else
u8 int_ike_jny_harikoear01_tex_txt[] = {
#include "assets/int_ike_jny_harikoear01_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_harikotail01_tex_txt[0x80];
#else
u8 int_ike_jny_harikotail01_tex_txt[] = {
#include "assets/int_ike_jny_harikotail01_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_harikobody01_tex_txt[0x200];
#else
u8 int_ike_jny_harikobody01_tex_txt[] = {
#include "assets/int_ike_jny_harikobody01_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_jny_hariko01_v[0x9A0 / sizeof(Vtx)];
#else
Vtx int_ike_jny_hariko01_v[] = {
#include "assets/int_ike_jny_hariko01_v.inc"
};
#endif

Gfx int_ike_jny_hariko01_head_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_hariko01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_jny_harikoface01_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_jny_hariko01_v, 26, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 2, 3, 4, 2, 4, 5),
    gsSPNTriangles_5b(6, 5, 4, 6, 4, 7, 8, 7, 4, 8, 4, 3),
    gsSPNTriangles_5b(6, 9, 5, 1, 10, 2, 3, 2, 10, 3, 10, 8),
    gsSPNTriangles_5b(5, 9, 0, 2, 5, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_jny_harikoear01_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(11, 11, 12, 13, 14, 15, 13, 16, 17, 18),
    gsSPNTriangles_5b(19, 20, 13, 21, 22, 16, 13, 23, 24, 12, 23, 13),
    gsSPNTriangles_5b(13, 24, 19, 13, 25, 11, 25, 13, 15, 13, 20, 14),
    gsSPEndDisplayList(),
};

Gfx int_ike_jny_hariko01_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_hariko01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_jny_harikotail01_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_jny_hariko01_v[26], 31, 0),
    gsSPNTrianglesInit_5b(25, 0, 1, 2, 2, 3, 4, 1, 5, 6),
    gsSPNTriangles_5b(7, 0, 2, 8, 9, 2, 1, 0, 10, 11, 12, 3),
    gsSPNTriangles_5b(3, 12, 13, 6, 5, 3, 3, 5, 11, 8, 4, 14),
    gsSPNTriangles_5b(1, 6, 2, 2, 6, 3, 13, 1, 3, 1, 13, 11),
    gsSPNTriangles_5b(1, 11, 5, 13, 12, 11, 0, 7, 14, 14, 4, 0),
    gsSPNTriangles_5b(14, 7, 8, 4, 3, 10, 10, 3, 1, 10, 0, 4),
    gsSPNTriangles_5b(2, 4, 8, 2, 9, 7, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_jny_harikobody01_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(3, 15, 16, 17, 18, 19, 15, 20, 21, 19),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 22, 23, 24, 25, 26, 27, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 28, 29, 30, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_ike_jny_hariko01_v[57], 29, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 3, 4, 5, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 6, 7, 8, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(5, 9, 10, 11, 12, 13, 14, 13, 15, 16),
    gsSPNTriangles_5b(17, 10, 9, 18, 19, 17, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 23, 24, 25, 25, 26, 23),
    gsSPNTriangles_5b(26, 27, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_ike_jny_hariko01_v[86], 30, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 1, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 4, 5, 6, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(1, 7, 8, 9, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 10, 13, 14, 15, 16, 14),
    gsSPNTriangles_5b(17, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 23, 21, 20, 20, 24, 23),
    gsSPNTriangles_5b(25, 26, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 27, 28, 29, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_ike_jny_hariko01_v[116], 29, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 3, 4, 5, 6, 7, 8, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 12, 13, 14, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 15, 16, 17, 18, 17, 16, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 19, 20, 21, 22, 19, 21, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 23, 24, 25, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 26, 27, 28, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_ike_jny_hariko01_v[145], 9, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 3, 4, 5, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 6, 7, 8, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_ike_jny_hariko01_tbl[] = { 56, 7 };

s16 cKF_kn_int_ike_jny_hariko01_tbl[] = { 2, 2, 2, 17, 17, 20 };

s16 cKF_c_int_ike_jny_hariko01_tbl[] = { 0, 450, 0 };

s16 cKF_ds_int_ike_jny_hariko01_tbl[] = {
    1,  120,  0,   101, 120,  0,   1,  1252, 0,   101, 1252, 0,   1,   -127, 0,   101, -127, 0,   1,  0,    0,
    7,  27,   38,  13,  27,   -45, 18, -4,   -47, 24,  -4,   30,  30,  22,   38,  36,  22,   -33, 41, 0,    -36,
    47, -1,   31,  51,  13,   29,  57, 13,   -28, 62,  0,    -26, 68,  0,    26,  73,  7,    19,  78, 7,    -22,
    82, 0,    -9,  101, 0,    0,   1,  0,    0,   8,   38,   37,  14,  38,   -48, 19,  -5,   -49, 25, -5,   47,
    31, 32,   48,  37,  31,   -58, 42, -6,   -48, 48,  -6,   38,  52,  18,   43,  59,  17,   -46, 63, -6,   -31,
    69, -6,   23,  74,  4,    31,  79, 4,    -20, 83,  0,    -6,  101, 0,    0,   1,   1800, 0,   5,  1980, 0,
    11, 1714, 0,   17,  1919, -2,  22, 1744, 0,   28,  1903, 0,   33,  1758, 0,   38,  1887, 0,   44, 1771, 0,
    49, 1869, 0,   54,  1782, 0,   59, 1847, 0,   64,  1792, 0,   69,  1831, 0,   74,  1797, 0,   79, 1820, 5,
    84, 1799, -23, 89,  1812, 3,   94, 1800, -29, 101, 1800, 0
};

cKF_Animation_R_c cKF_ba_r_int_ike_jny_hariko01 = { cKF_ckcb_r_int_ike_jny_hariko01_tbl,
                                                    cKF_ds_int_ike_jny_hariko01_tbl,
                                                    cKF_kn_int_ike_jny_hariko01_tbl,
                                                    cKF_c_int_ike_jny_hariko01_tbl,
                                                    -1,
                                                    101 };

cKF_Joint_R_c cKF_je_r_int_ike_jny_hariko01_tbl[] = {
    { int_ike_jny_hariko01_body_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 120, 1252, 65409 } },
    { int_ike_jny_hariko01_head_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_ike_jny_hariko01 = { ARRAY_COUNT(cKF_je_r_int_ike_jny_hariko01_tbl), 2,
                                                   cKF_je_r_int_ike_jny_hariko01_tbl };
