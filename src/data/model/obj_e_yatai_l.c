#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_e_yatai_3_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_e_yatai_3_pal[] = {
#include "assets/obj_e_yatai_3_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_e_yatai_2_pal[0x20 / sizeof(u16)];
#else
u16 obj_e_yatai_2_pal[] = {
#include "assets/obj_e_yatai_2_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_e_yatai_1_pal[0x20 / sizeof(u16)];
#else
u16 obj_e_yatai_1_pal[] = {
#include "assets/obj_e_yatai_1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_yatai_3[0x400];
#else
u8 obj_e_yatai_3[] = {
#include "assets/obj_e_yatai_3.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_yatai_2[0x800];
#else
u8 obj_e_yatai_2[] = {
#include "assets/obj_e_yatai_2.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_yatai_4[0x100];
#else
u8 obj_e_yatai_4[] = {
#include "assets/obj_e_yatai_4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_yatai_1[0x800];
#else
u8 obj_e_yatai_1[] = {
#include "assets/obj_e_yatai_1.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_yatai_l_v[0xE20 / sizeof(Vtx)];
#else
Vtx obj_e_yatai_l_v[] = {
#include "assets/obj_e_yatai_l_v.inc"
};
#endif

Gfx obj_e_yatai_l_modelT[] = {
    gsSPEndDisplayList(),
};

Gfx obj_e_yatai_l_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_yatai_3_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, obj_e_yatai_4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_yatai_l_v, 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 0, 4, 1),
    gsSPNTriangles_5b(4, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_yatai_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_e_yatai_1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_yatai_l_v[5], 32, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 9, 10, 11, 9, 11, 12),
    gsSPNTriangles_5b(13, 14, 15, 14, 16, 15, 16, 17, 15, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 23, 21, 22, 21, 24, 25, 26, 27),
    gsSPNTriangles_5b(26, 28, 27, 25, 29, 26, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_e_yatai_l_v[35], 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_yatai_2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_yatai_2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_yatai_l_v[40], 32, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 18, 19, 20, 18, 20, 21, 22, 23, 24),
    gsSPNTriangles_5b(22, 24, 25, 26, 27, 28, 26, 28, 29, 13, 30, 31),
    gsSPVertex(&obj_e_yatai_l_v[72], 32, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 9, 11, 12, 13, 14, 15, 13, 15, 16),
    gsSPNTriangles_5b(17, 18, 19, 17, 19, 20, 21, 22, 23, 21, 23, 24),
    gsSPNTriangles_5b(25, 26, 27, 25, 27, 28, 29, 30, 31, 0, 0, 0),
    gsSPVertex(&obj_e_yatai_l_v[104], 7, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_yatai_3_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_e_yatai_3),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_yatai_l_v[111], 32, 0),
    gsSPNTrianglesInit_5b(27, 0, 1, 2, 1, 3, 2, 0, 4, 1),
    gsSPNTriangles_5b(1, 5, 3, 4, 6, 1, 6, 7, 1, 7, 8, 1),
    gsSPNTriangles_5b(8, 5, 1, 9, 10, 11, 12, 9, 11, 13, 12, 11),
    gsSPNTriangles_5b(14, 13, 11, 11, 10, 15, 16, 14, 11, 11, 15, 17),
    gsSPNTriangles_5b(16, 11, 17, 18, 19, 20, 21, 18, 20, 22, 21, 20),
    gsSPNTriangles_5b(23, 22, 20, 20, 19, 24, 25, 23, 20, 20, 24, 26),
    gsSPNTriangles_5b(25, 20, 26, 27, 28, 29, 28, 30, 29, 27, 31, 28),
    gsSPVertex(&obj_e_yatai_l_v[143], 16, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 4, 0, 4, 5, 0),
    gsSPNTriangles_5b(5, 6, 0, 6, 1, 0, 7, 8, 9, 10, 7, 9),
    gsSPNTriangles_5b(11, 10, 9, 12, 11, 9, 9, 8, 13, 14, 12, 9),
    gsSPNTriangles_5b(9, 13, 15, 14, 9, 15, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_yatai_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_e_yatai_1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_yatai_l_v[159], 32, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 3, 6, 0, 3, 7, 6, 0, 8, 4),
    gsSPNTriangles_5b(9, 6, 10, 6, 7, 10, 11, 12, 13, 11, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 15, 17, 18, 19, 20, 21, 19, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 25, 26, 27, 28, 29, 27, 29, 30),
    gsSPVertex(&obj_e_yatai_l_v[190], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_yatai_2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_yatai_2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_yatai_l_v[194], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
Vtx obj_e_yatai_r_v[0xE20 / sizeof(Vtx)];
#else
Vtx obj_e_yatai_r_v[] = {
#include "assets/obj_e_yatai_r_v.inc"
};
#endif

Gfx obj_e_yatai_r_modelT[] = {
    gsSPEndDisplayList(),
};

Gfx obj_e_yatai_r_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_yatai_3_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, obj_e_yatai_4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_yatai_r_v, 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 1, 4, 2),
    gsSPNTriangles_5b(1, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_yatai_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_e_yatai_1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_yatai_r_v[5], 32, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 9, 10, 11, 9, 11, 12),
    gsSPNTriangles_5b(13, 14, 15, 13, 16, 14, 13, 17, 16, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 18, 23, 22, 23, 24, 25, 26, 27),
    gsSPNTriangles_5b(25, 28, 26, 26, 29, 27, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_e_yatai_r_v[35], 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 0, 2, 3, 2, 4),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_yatai_2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_yatai_2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_yatai_r_v[40], 32, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 18, 19, 20, 18, 20, 21, 22, 23, 24),
    gsSPNTriangles_5b(22, 24, 25, 26, 27, 28, 26, 28, 29, 30, 31, 11),
    gsSPVertex(&obj_e_yatai_r_v[72], 32, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 9, 11, 12, 13, 14, 15, 13, 15, 16),
    gsSPNTriangles_5b(17, 18, 19, 17, 19, 20, 21, 22, 23, 21, 23, 24),
    gsSPNTriangles_5b(25, 26, 27, 25, 27, 28, 29, 30, 31, 0, 0, 0),
    gsSPVertex(&obj_e_yatai_r_v[104], 7, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_yatai_3_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_e_yatai_3),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_yatai_r_v[111], 32, 0),
    gsSPNTrianglesInit_5b(27, 0, 1, 2, 0, 3, 1, 1, 4, 2),
    gsSPNTriangles_5b(3, 5, 1, 1, 6, 4, 1, 7, 6, 1, 8, 7),
    gsSPNTriangles_5b(1, 5, 8, 9, 10, 11, 9, 11, 12, 9, 12, 13),
    gsSPNTriangles_5b(9, 13, 14, 15, 10, 9, 9, 14, 16, 17, 15, 9),
    gsSPNTriangles_5b(17, 9, 16, 18, 19, 20, 18, 20, 21, 18, 21, 22),
    gsSPNTriangles_5b(18, 22, 23, 24, 19, 18, 18, 23, 25, 26, 24, 18),
    gsSPNTriangles_5b(26, 18, 25, 27, 28, 29, 27, 30, 28, 28, 31, 29),
    gsSPVertex(&obj_e_yatai_r_v[143], 16, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 2, 3, 4, 2, 5, 3),
    gsSPNTriangles_5b(2, 6, 5, 2, 1, 6, 7, 8, 9, 7, 9, 10),
    gsSPNTriangles_5b(7, 10, 11, 7, 11, 12, 13, 8, 7, 7, 12, 14),
    gsSPNTriangles_5b(15, 13, 7, 15, 7, 14, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_yatai_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_e_yatai_1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_yatai_r_v[159], 32, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 3, 6, 0, 6, 7, 0, 5, 8, 3),
    gsSPNTriangles_5b(9, 6, 10, 9, 7, 6, 11, 12, 13, 11, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 15, 17, 18, 19, 20, 21, 19, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 25, 26, 27, 28, 29, 27, 29, 30),
    gsSPVertex(&obj_e_yatai_r_v[190], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_yatai_2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_yatai_2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_yatai_r_v[194], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
