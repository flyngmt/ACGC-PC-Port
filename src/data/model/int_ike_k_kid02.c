#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_k_kid02_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_k_kid02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_k_kid02_pal[] = {
#include "assets/int_ike_k_kid02_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kid2door1_tex[0x100];
#else
u8 int_ike_k_kid2door1_tex[] = {
#include "assets/int_ike_k_kid2door1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kid2yane1_tex[0x100];
#else
u8 int_ike_k_kid2yane1_tex[] = {
#include "assets/int_ike_k_kid2yane1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kid2door2_tex[0x100];
#else
u8 int_ike_k_kid2door2_tex[] = {
#include "assets/int_ike_k_kid2door2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kid2under_tex[0x40];
#else
u8 int_ike_k_kid2under_tex[] = {
#include "assets/int_ike_k_kid2under_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kid2kousi_tex[0x80];
#else
u8 int_ike_k_kid2kousi_tex[] = {
#include "assets/int_ike_k_kid2kousi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kid2side1_tex[0x100];
#else
u8 int_ike_k_kid2side1_tex[] = {
#include "assets/int_ike_k_kid2side1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kid2sunoko_tex[0x80];
#else
u8 int_ike_k_kid2sunoko_tex[] = {
#include "assets/int_ike_k_kid2sunoko_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kid2tire_tex[0x80];
#else
u8 int_ike_k_kid2tire_tex[] = {
#include "assets/int_ike_k_kid2tire_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kid2tire2_tex[0x100];
#else
u8 int_ike_k_kid2tire2_tex[] = {
#include "assets/int_ike_k_kid2tire2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_kid2base_tex[0x80];
#else
u8 int_ike_k_kid2base_tex[] = {
#include "assets/int_ike_k_kid2base_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_k_kid02_v[0x780 / sizeof(Vtx)];
#else
Vtx int_ike_k_kid02_v[] = {
#include "assets/int_ike_k_kid02_v.inc"
};
#endif

Gfx int_ike_k_kid02_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_k_kid02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_kid2base_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_k_kid02_v, 25, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 1, 4, 2),
    gsSPNTriangles_5b(4, 5, 2, 4, 6, 7, 4, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_kid2sunoko_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(3, 16, 17, 18, 18, 19, 16, 16, 20, 17),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_k_kid2under_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 21, 22, 23, 24, 21, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_k_kid2yane1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_ike_k_kid02_v[25], 9, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 2, 1, 3, 4, 1, 0),
    gsSPNTriangles_5b(1, 5, 3, 5, 6, 3, 1, 4, 5, 4, 7, 5),
    gsSPNTriangles_5b(5, 8, 6, 7, 8, 5, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_k_kid02_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_k_kid02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_k_kid2tire2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_k_kid02_v[34], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_kid2tire_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_ike_k_kid02_v[50], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 12, 14, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 24, 25, 26, 27, 24, 26, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_k_kid2side1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_ike_k_kid02_v[82], 26, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_kid2kousi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 10, 16, 17, 18, 19, 20, 19, 21, 20),
    gsSPNTriangles_5b(10, 17, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_k_kid2door2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 22, 23, 24, 22, 24, 25, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_k_kid2door1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_ike_k_kid02_v[108], 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 1, 0),
    gsSPNTriangles_5b(4, 5, 1, 2, 6, 7, 2, 3, 6, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
