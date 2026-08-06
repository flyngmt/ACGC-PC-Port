#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_island_uku01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_island_uku01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_island_uku01_pal[] = {
#include "assets/int_ike_island_uku01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_ukuneck_tex_txt[0x80];
#else
u8 int_ike_island_ukuneck_tex_txt[] = {
#include "assets/int_ike_island_ukuneck_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_ukuneck3_tex_txt[0x40];
#else
u8 int_ike_island_ukuneck3_tex_txt[] = {
#include "assets/int_ike_island_ukuneck3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_ukuneck2_tex_txt[0x40];
#else
u8 int_ike_island_ukuneck2_tex_txt[] = {
#include "assets/int_ike_island_ukuneck2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_ukuside1_tex_txt[0x80];
#else
u8 int_ike_island_ukuside1_tex_txt[] = {
#include "assets/int_ike_island_ukuside1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_ukuface1_tex_txt[0x200];
#else
u8 int_ike_island_ukuface1_tex_txt[] = {
#include "assets/int_ike_island_ukuface1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_island_ukuface2_tex_txt[0x200];
#else
u8 int_ike_island_ukuface2_tex_txt[] = {
#include "assets/int_ike_island_ukuface2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_island_uku01_v[0x4B0 / sizeof(Vtx)];
#else
Vtx int_ike_island_uku01_v[] = {
#include "assets/int_ike_island_uku01_v.inc"
};
#endif

Gfx int_ike_island_uku01_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_island_uku01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_island_ukuneck_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_island_uku01_v, 31, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_island_ukuneck3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 19, 20, 21),
    gsSPNTriangles_5b(19, 21, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_island_ukuneck2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
    gsSPNTrianglesInit_5b(5, 22, 23, 24, 24, 25, 22, 26, 27, 28),
    gsSPNTriangles_5b(26, 28, 29, 22, 30, 23, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_island_ukuside1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_island_uku01_v[31], 32, 0),
    gsSPNTrianglesInit_5b(32, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 6, 7, 8, 6, 8, 9, 7, 10, 11),
    gsSPNTriangles_5b(7, 11, 8, 12, 0, 3, 12, 3, 13, 4, 14, 15),
    gsSPNTriangles_5b(4, 15, 5, 16, 12, 13, 16, 13, 17, 14, 18, 19),
    gsSPNTriangles_5b(14, 19, 15, 20, 6, 9, 20, 9, 21, 10, 22, 23),
    gsSPNTriangles_5b(10, 23, 11, 24, 16, 17, 24, 17, 25, 18, 26, 27),
    gsSPNTriangles_5b(18, 27, 19, 28, 24, 25, 28, 25, 29, 26, 30, 31),
    gsSPNTriangles_5b(26, 31, 27, 30, 20, 21, 30, 21, 31, 22, 28, 29),
    gsSPNTriangles_5b(22, 29, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_island_ukuface1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_island_uku01_v[63], 12, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 3, 4, 5),
    gsSPNTriangles_5b(3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_island_ukuface2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsSPNTrianglesInit_5b(4, 6, 7, 8, 6, 8, 9, 9, 10, 11),
    gsSPNTriangles_5b(9, 11, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
