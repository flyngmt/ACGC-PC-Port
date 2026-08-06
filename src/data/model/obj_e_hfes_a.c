#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_e_hfes01_t1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_e_hfes01_t1_pal[] = {
#include "assets/obj_e_hfes01_t1_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_e_hfes01_t4_pal[0x20 / sizeof(u16)];
#else
u16 obj_e_hfes01_t4_pal[] = {
#include "assets/obj_e_hfes01_t4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_e_hfes01_t2_pal[0x20 / sizeof(u16)];
#else
u16 obj_e_hfes01_t2_pal[] = {
#include "assets/obj_e_hfes01_t2_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_e_hfes01_t3_pal[0x20 / sizeof(u16)];
#else
u16 obj_e_hfes01_t3_pal[] = {
#include "assets/obj_e_hfes01_t3_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_hfes01_t1[0x800];
#else
u8 obj_e_hfes01_t1[] = {
#include "assets/obj_e_hfes01_t1.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_hfes01_t6[0x80];
#else
u8 obj_e_hfes01_t6[] = {
#include "assets/obj_e_hfes01_t6.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_hfes01_t2[0x400];
#else
u8 obj_e_hfes01_t2[] = {
#include "assets/obj_e_hfes01_t2.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_hfes01_t7[0x20];
#else
u8 obj_e_hfes01_t7[] = {
#include "assets/obj_e_hfes01_t7.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_hfes01_t3[0x400];
#else
u8 obj_e_hfes01_t3[] = {
#include "assets/obj_e_hfes01_t3.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_hfes01_t4[0x40];
#else
u8 obj_e_hfes01_t4[] = {
#include "assets/obj_e_hfes01_t4.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_hfes_a_v[0xB40 / sizeof(Vtx)];
#else
Vtx obj_e_hfes_a_v[] = {
#include "assets/obj_e_hfes_a_v.inc"
};
#endif

Gfx obj_e_hfes_a_modelT[] = {
    gsSPEndDisplayList(),
};

Gfx obj_e_hfes_a_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hfes01_t4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, obj_e_hfes01_t4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_hfes_a_v, 20, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 2, 4, 5, 4, 6),
    gsSPNTriangles_5b(7, 6, 8, 9, 8, 10, 11, 1, 12, 15, 16, 4),
    gsSPNTriangles_5b(4, 16, 2, 16, 17, 2, 2, 17, 1, 17, 18, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(7, 13, 14, 8, 10, 13, 8, 8, 14, 6),
    gsSPNTriangles_5b(14, 15, 6, 6, 15, 4, 1, 18, 11, 11, 18, 19),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, obj_e_hfes01_t7),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_hfes_a_v[20], 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 0, 5, 6, 0, 6, 7, 0, 7, 8),
    gsSPNTriangles_5b(0, 8, 9, 0, 9, 10, 0, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_e_hfes01_t6),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_e_hfes_a_v[32], 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 6, 4, 5, 6, 5, 7, 8, 6, 7),
    gsSPNTriangles_5b(8, 7, 9, 10, 11, 12, 10, 12, 13, 14, 10, 13),
    gsSPNTriangles_5b(14, 13, 15, 14, 15, 16, 14, 16, 17, 17, 16, 18),
    gsSPNTriangles_5b(17, 18, 19, 19, 18, 20, 19, 20, 21, 22, 8, 9),
    gsSPNTriangles_5b(22, 9, 23, 24, 25, 26, 24, 26, 27, 26, 28, 29),
    gsSPNTriangles_5b(26, 29, 27, 30, 31, 21, 30, 21, 20, 1, 29, 28),
    gsSPNTriangles_5b(1, 28, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hfes01_t3_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_e_hfes01_t3),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_hfes_a_v[64], 26, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 0, 2, 3, 4, 0),
    gsSPNTriangles_5b(4, 5, 0, 6, 7, 8, 7, 9, 8, 7, 10, 9),
    gsSPNTriangles_5b(7, 11, 10, 10, 12, 13, 10, 14, 12, 12, 8, 13),
    gsSPNTriangles_5b(12, 15, 8, 16, 17, 18, 17, 19, 18, 17, 20, 19),
    gsSPNTriangles_5b(17, 21, 20, 20, 22, 23, 20, 24, 22, 22, 18, 23),
    gsSPNTriangles_5b(22, 25, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hfes01_t2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_e_hfes01_t2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_hfes_a_v[90], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 5, 0, 6, 7, 8, 6, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 14, 16, 17, 18, 17, 16),
    gsSPNTriangles_5b(18, 16, 19, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 28, 29, 30, 28, 30, 31, 0, 0, 0),
    gsSPVertex(&obj_e_hfes_a_v[122], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hfes01_t1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_e_hfes01_t1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_hfes_a_v[126], 32, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 14, 15, 3, 14, 3, 2, 2, 5, 6),
    gsSPNTriangles_5b(2, 6, 14, 16, 17, 18, 18, 19, 16, 20, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 25, 26, 27, 28, 29, 27, 29, 30),
    gsSPVertex(&obj_e_hfes_a_v[157], 23, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 17, 18, 15, 19, 20, 21, 21, 22, 19),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
Vtx obj_e_hfes_b_v[0xAA0 / sizeof(Vtx)];
#else
Vtx obj_e_hfes_b_v[] = {
#include "assets/obj_e_hfes_b_v.inc"
};
#endif

Gfx obj_e_hfes_b_modelT[] = {
    gsSPEndDisplayList(),
};

Gfx obj_e_hfes_b_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hfes01_t4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_e_hfes01_t6),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_hfes_b_v, 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 6, 2, 1, 6, 1, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 12, 8, 11, 12, 11, 13, 14, 12, 13),
    gsSPNTriangles_5b(14, 13, 15, 16, 14, 15, 16, 15, 17, 18, 16, 17),
    gsSPNTriangles_5b(18, 17, 19, 20, 18, 19, 20, 19, 21, 22, 23, 24),
    gsSPNTriangles_5b(22, 24, 25, 25, 24, 26, 25, 26, 27, 27, 26, 5),
    gsSPNTriangles_5b(27, 5, 4, 9, 28, 29, 9, 29, 10, 30, 31, 20),
    gsSPNTriangles_5b(30, 20, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, obj_e_hfes01_t7),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_e_hfes_b_v[32], 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 0, 5, 6, 0, 6, 7, 0, 7, 8),
    gsSPNTriangles_5b(0, 8, 9, 0, 9, 10, 0, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, obj_e_hfes01_t4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_e_hfes_b_v[44], 20, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 0, 2, 4, 0, 3),
    gsSPNTriangles_5b(5, 4, 3, 6, 4, 5, 12, 2, 13, 14, 9, 10),
    gsSPNTriangles_5b(15, 7, 9, 16, 5, 7, 17, 3, 5, 18, 2, 3),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(7, 7, 6, 5, 8, 6, 7, 9, 8, 7),
    gsSPNTriangles_5b(10, 11, 9, 11, 8, 9, 12, 1, 19, 2, 1, 12),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hfes01_t3_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_e_hfes01_t3),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_hfes_b_v[64], 26, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 2, 3, 4, 2, 4, 5),
    gsSPNTriangles_5b(0, 2, 5, 6, 7, 0, 6, 0, 8, 6, 8, 4),
    gsSPNTriangles_5b(9, 6, 4, 10, 11, 12, 11, 13, 12, 11, 14, 13),
    gsSPNTriangles_5b(11, 15, 14, 14, 16, 17, 16, 12, 17, 16, 18, 12),
    gsSPNTriangles_5b(14, 19, 16, 20, 21, 22, 23, 20, 22, 23, 22, 24),
    gsSPNTriangles_5b(22, 25, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hfes01_t2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_e_hfes01_t2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_hfes_b_v[90], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 2, 1, 4),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 7, 6, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 14, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 23, 24, 22, 24, 25, 26, 27, 28),
    gsSPNTriangles_5b(26, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_e_hfes_b_v[120], 18, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 14, 16, 15, 14, 17, 16, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hfes01_t1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_e_hfes01_t1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_hfes_b_v[138], 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 3, 4, 5),
    gsSPNTriangles_5b(3, 5, 0, 5, 0, 6, 5, 6, 7, 8, 1, 2),
    gsSPNTriangles_5b(8, 2, 9, 4, 3, 10, 4, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(14, 15, 12, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(22, 23, 20, 24, 25, 26, 26, 27, 24, 28, 29, 30),
    gsSPNTriangles_5b(30, 31, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_e_hfes01_t5_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_e_hfes01_t5_pal[] = {
#include "assets/obj_e_hfes01_t5_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_hfes01_t5[0x400];
#else
u8 obj_e_hfes01_t5[] = {
#include "assets/obj_e_hfes01_t5.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_hfes_c_v[0x1440 / sizeof(Vtx)];
#else
Vtx obj_e_hfes_c_v[] = {
#include "assets/obj_e_hfes_c_v.inc"
};
#endif

Gfx obj_e_hfes_c_modelT[] = {
    gsSPEndDisplayList(),
};

Gfx obj_e_hfes_c_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hfes01_t4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_e_hfes01_t6),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_hfes_c_v, 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 5, 4, 8),
    gsSPNTriangles_5b(5, 8, 11, 12, 10, 9, 12, 9, 13, 14, 12, 13),
    gsSPNTriangles_5b(14, 13, 15, 1, 14, 15, 1, 15, 2, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 16, 19, 20, 19, 21, 22, 20, 21),
    gsSPNTriangles_5b(22, 21, 23, 24, 22, 23, 24, 23, 25, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 27, 26, 28, 27, 28, 29, 29, 28, 30),
    gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_e_hfes_c_v[32], 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 0, 5, 6, 0, 6, 7, 0, 7, 8),
    gsSPNTriangles_5b(0, 8, 9, 0, 9, 10, 0, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 21, 24, 21, 20, 26, 27, 25),
    gsSPNTriangles_5b(26, 25, 24, 26, 28, 29, 26, 29, 27, 28, 30, 31),
    gsSPNTriangles_5b(28, 31, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_e_hfes_c_v[64], 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 6, 7, 8, 6, 8, 9, 7, 10, 11),
    gsSPNTriangles_5b(7, 11, 8, 10, 12, 13, 10, 13, 11, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 16, 13, 12, 16, 12, 17, 15, 14, 18),
    gsSPNTriangles_5b(15, 18, 19, 20, 6, 9, 20, 9, 21, 22, 23, 24),
    gsSPNTriangles_5b(22, 24, 25, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsSPVertex(&obj_e_hfes_c_v[94], 32, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 0, 2, 3, 4, 5, 0),
    gsSPNTriangles_5b(4, 0, 3, 6, 2, 1, 6, 1, 7, 8, 6, 7),
    gsSPNTriangles_5b(8, 7, 9, 10, 8, 9, 10, 9, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 12, 15, 16, 15, 17, 18, 16, 17),
    gsSPNTriangles_5b(18, 17, 19, 20, 18, 19, 20, 19, 21, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 23, 22, 24, 23, 24, 25, 25, 24, 26),
    gsSPNTriangles_5b(25, 26, 27, 28, 29, 30, 28, 30, 31, 0, 0, 0),
    gsSPVertex(&obj_e_hfes_c_v[126], 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 12, 15, 16, 12, 16, 17, 18, 14, 13),
    gsSPNTriangles_5b(18, 13, 19, 20, 8, 11, 20, 11, 21, 22, 20, 21),
    gsSPNTriangles_5b(22, 21, 23, 24, 25, 26, 24, 26, 27, 28, 24, 27),
    gsSPNTriangles_5b(28, 27, 29, 5, 28, 29, 5, 29, 6, 0, 0, 0),
    gsSPVertex(&obj_e_hfes_c_v[156], 32, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 5, 4, 6, 5, 6, 7, 7, 6, 8),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 10, 12, 13, 10, 13, 14),
    gsSPNTriangles_5b(10, 14, 15, 16, 12, 11, 16, 11, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 18, 21, 22, 21, 23, 24, 22, 23),
    gsSPNTriangles_5b(24, 23, 25, 26, 24, 25, 26, 25, 27, 28, 26, 27),
    gsSPNTriangles_5b(28, 27, 29, 30, 28, 29, 30, 29, 31, 0, 0, 0),
    gsSPVertex(&obj_e_hfes_c_v[188], 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 5, 4, 6, 5, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 8, 11, 12, 8, 12, 13, 8, 13, 14),
    gsSPNTriangles_5b(8, 14, 15, 8, 15, 16, 8, 16, 17, 8, 17, 18),
    gsSPNTriangles_5b(8, 18, 19, 20, 21, 22, 20, 22, 23, 24, 25, 21),
    gsSPNTriangles_5b(24, 21, 20, 26, 27, 25, 26, 25, 24, 26, 28, 29),
    gsSPNTriangles_5b(26, 29, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_e_hfes_c_v[218], 22, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 4, 6, 7, 4, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 9, 12, 13, 9, 13, 10, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 18, 19, 20, 18, 20, 21, 18, 16, 15),
    gsSPNTriangles_5b(18, 15, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, obj_e_hfes01_t7),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_e_hfes_c_v[240], 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 0, 5, 6, 0, 6, 7, 0, 7, 8),
    gsSPNTriangles_5b(0, 8, 9, 0, 9, 10, 0, 10, 11, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hfes01_t5_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_e_hfes01_t5),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_e_hfes_c_v[252], 28, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hfes01_t2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_e_hfes01_t2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(12, 4, 5, 6, 4, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hfes01_t1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_e_hfes01_t1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_hfes_c_v[280], 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 9, 10, 10, 11, 8, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 21, 20, 15, 21, 15, 14, 14, 17, 18),
    gsSPNTriangles_5b(14, 18, 21, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_e_hfes_c_v[312], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 10, 11, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};
