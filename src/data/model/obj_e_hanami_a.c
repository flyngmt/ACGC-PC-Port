#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_e_hanami_t1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_e_hanami_t1_pal[] = {
#include "assets/obj_e_hanami_t1_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_e_hanami_t2_pal[0x20 / sizeof(u16)];
#else
u16 obj_e_hanami_t2_pal[] = {
#include "assets/obj_e_hanami_t2_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_e_hanami_t3_pal[0x20 / sizeof(u16)];
#else
u16 obj_e_hanami_t3_pal[] = {
#include "assets/obj_e_hanami_t3_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_e_hanami_t5_pal[0x20 / sizeof(u16)];
#else
u16 obj_e_hanami_t5_pal[] = {
#include "assets/obj_e_hanami_t5_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_hanami_t1[0x800];
#else
u8 obj_e_hanami_t1[] = {
#include "assets/obj_e_hanami_t1.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_hanami_t2[0x400];
#else
u8 obj_e_hanami_t2[] = {
#include "assets/obj_e_hanami_t2.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_hanami_t3[0x200];
#else
u8 obj_e_hanami_t3[] = {
#include "assets/obj_e_hanami_t3.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_hanami_t4[0x40];
#else
u8 obj_e_hanami_t4[] = {
#include "assets/obj_e_hanami_t4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_hanami_t5[0x80];
#else
u8 obj_e_hanami_t5[] = {
#include "assets/obj_e_hanami_t5.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_hanami_t6[0x20];
#else
u8 obj_e_hanami_t6[] = {
#include "assets/obj_e_hanami_t6.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_hanami_a_v[0xB10 / sizeof(Vtx)];
#else
Vtx obj_e_hanami_a_v[] = {
#include "assets/obj_e_hanami_a_v.inc"
};
#endif

Gfx obj_e_hanami_a_modelT[] = {
    gsSPEndDisplayList(),
};

Gfx obj_e_hanami_a_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hanami_t5_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, obj_e_hanami_t6),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_hanami_a_v, 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 0, 5, 6, 0, 6, 7, 0, 7, 8),
    gsSPNTriangles_5b(0, 8, 9, 0, 9, 10, 0, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_e_hanami_t5),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_e_hanami_a_v[12], 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 5, 8, 5, 4, 10, 11, 9),
    gsSPNTriangles_5b(10, 9, 8, 12, 13, 14, 12, 14, 15, 13, 16, 17),
    gsSPNTriangles_5b(13, 17, 14, 16, 18, 19, 16, 19, 17, 18, 20, 21),
    gsSPNTriangles_5b(18, 21, 19, 20, 22, 23, 20, 23, 21, 22, 0, 3),
    gsSPNTriangles_5b(22, 3, 23, 24, 25, 26, 24, 26, 27, 28, 29, 7),
    gsSPNTriangles_5b(28, 7, 6, 28, 26, 25, 28, 25, 29, 30, 31, 12),
    gsSPNTriangles_5b(30, 12, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hanami_t3_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, obj_e_hanami_t4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_e_hanami_a_v[44], 20, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 4, 1, 5, 6, 4),
    gsSPNTriangles_5b(10, 8, 6, 4, 10, 6, 11, 10, 4, 1, 11, 4),
    gsSPNTriangles_5b(12, 11, 1, 7, 6, 17, 18, 14, 15, 19, 2, 14),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(7, 7, 8, 9, 6, 8, 7, 2, 12, 1),
    gsSPNTriangles_5b(13, 12, 2, 14, 13, 2, 15, 16, 14, 16, 13, 14),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_e_hanami_t3),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_hanami_a_v[64], 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 1, 0, 4, 0, 2),
    gsSPNTriangles_5b(4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hanami_t2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_e_hanami_t2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_hanami_a_v[69], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 18, 17, 20),
    gsSPNTriangles_5b(21, 22, 23, 21, 23, 24, 23, 22, 25, 26, 27, 28),
    gsSPNTriangles_5b(26, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_e_hanami_a_v[99], 21, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(14, 15, 12, 16, 17, 18, 13, 16, 18, 14, 13, 18),
    gsSPNTriangles_5b(19, 14, 18, 19, 18, 20, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hanami_t1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_e_hanami_t1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_hanami_a_v[120], 32, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 0, 2, 3, 3, 4, 5),
    gsSPNTriangles_5b(3, 5, 0, 5, 0, 6, 5, 6, 7, 8, 1, 2),
    gsSPNTriangles_5b(8, 2, 9, 10, 11, 12, 10, 12, 13, 10, 13, 14),
    gsSPNTriangles_5b(11, 10, 14, 15, 16, 17, 15, 17, 18, 15, 18, 19),
    gsSPNTriangles_5b(16, 15, 19, 20, 21, 22, 21, 23, 22, 21, 24, 23),
    gsSPNTriangles_5b(21, 20, 24, 25, 26, 27, 25, 27, 28, 25, 28, 29),
    gsSPNTriangles_5b(26, 25, 29, 4, 3, 30, 4, 30, 31, 0, 0, 0),
    gsSPVertex(&obj_e_hanami_a_v[152], 25, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 10, 11, 8, 12, 13, 14),
    gsSPNTriangles_5b(14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 20, 23, 20, 24, 21, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
Vtx obj_e_hanami_b_v[0xBE0 / sizeof(Vtx)];
#else
Vtx obj_e_hanami_b_v[] = {
#include "assets/obj_e_hanami_b_v.inc"
};
#endif

Gfx obj_e_hanami_b_modelT[] = {
    gsSPEndDisplayList(),
};

Gfx obj_e_hanami_b_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hanami_t5_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_e_hanami_t5),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_hanami_b_v, 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 6, 7, 5, 6, 5, 4, 6, 8, 9),
    gsSPNTriangles_5b(6, 9, 7, 8, 10, 11, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 13, 16, 17, 13, 17, 14, 16, 18, 19),
    gsSPNTriangles_5b(16, 19, 17, 18, 20, 21, 18, 21, 19, 20, 22, 23),
    gsSPNTriangles_5b(20, 23, 21, 24, 25, 3, 24, 3, 2, 26, 23, 22),
    gsSPNTriangles_5b(26, 22, 27, 28, 29, 26, 28, 26, 27, 30, 12, 15),
    gsSPNTriangles_5b(30, 15, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, obj_e_hanami_t6),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_e_hanami_b_v[32], 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 0, 5, 6, 0, 6, 7, 0, 7, 8),
    gsSPNTriangles_5b(0, 8, 9, 0, 9, 10, 0, 10, 11, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hanami_t3_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, obj_e_hanami_t4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_e_hanami_b_v[44], 20, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 2, 4, 5, 4, 6),
    gsSPNTriangles_5b(7, 6, 8, 9, 8, 10, 11, 1, 12, 15, 16, 4),
    gsSPNTriangles_5b(4, 16, 2, 16, 17, 2, 2, 17, 1, 17, 18, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(7, 13, 14, 8, 10, 13, 8, 8, 14, 6),
    gsSPNTriangles_5b(14, 15, 6, 6, 15, 4, 1, 18, 11, 11, 18, 19),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_e_hanami_t3),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_hanami_b_v[64], 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 1, 4, 2),
    gsSPNTriangles_5b(2, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hanami_t2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_e_hanami_t2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_hanami_b_v[69], 32, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 5, 4),
    gsSPNTriangles_5b(12, 4, 13, 14, 15, 16, 14, 16, 17, 15, 18, 16),
    gsSPNTriangles_5b(15, 19, 18, 15, 20, 19, 21, 22, 16, 16, 18, 21),
    gsSPNTriangles_5b(23, 24, 25, 23, 25, 26, 27, 28, 29, 27, 29, 30),
    gsSPVertex(&obj_e_hanami_b_v[100], 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 3, 2),
    gsSPNTriangles_5b(4, 2, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_hanami_t1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_e_hanami_t1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_hanami_b_v[106], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 9, 10, 11, 12, 13, 11, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 15, 17, 18, 19, 20, 21, 19, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 25, 26, 27, 28, 29, 27, 29, 30),
    gsSPNTriangles_5b(10, 31, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_e_hanami_b_v[138], 32, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 22, 23, 11, 22, 11, 10, 24, 25, 26),
    gsSPNTriangles_5b(25, 27, 26, 25, 28, 27, 25, 24, 28, 29, 30, 31),
    gsSPVertex(&obj_e_hanami_b_v[170], 20, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(5, 6, 7, 6, 8, 7, 6, 9, 8, 6, 5, 9),
    gsSPNTriangles_5b(10, 11, 12, 11, 13, 12, 11, 14, 13, 11, 10, 14),
    gsSPNTriangles_5b(15, 16, 17, 16, 18, 17, 16, 19, 18, 16, 15, 19),
    gsSPEndDisplayList(),
};
