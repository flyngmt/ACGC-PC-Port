#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_tent_bike01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_tent_bike01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_tent_bike01_pal[] = {
#include "assets/int_ike_tent_bike01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_bike_tire1_tex_txt[0x200];
#else
u8 int_ike_tent_bike_tire1_tex_txt[] = {
#include "assets/int_ike_tent_bike_tire1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_bike_tire2_tex_txt[0x80];
#else
u8 int_ike_tent_bike_tire2_tex_txt[] = {
#include "assets/int_ike_tent_bike_tire2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_bike_pedal1_tex_txt[0x40];
#else
u8 int_ike_tent_bike_pedal1_tex_txt[] = {
#include "assets/int_ike_tent_bike_pedal1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_bike_tire3_tex_txt[0x100];
#else
u8 int_ike_tent_bike_tire3_tex_txt[] = {
#include "assets/int_ike_tent_bike_tire3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_bike_handle2_tex_txt[0x80];
#else
u8 int_ike_tent_bike_handle2_tex_txt[] = {
#include "assets/int_ike_tent_bike_handle2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_bike_frame2_tex_txt[0x80];
#else
u8 int_ike_tent_bike_frame2_tex_txt[] = {
#include "assets/int_ike_tent_bike_frame2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_bike_handle1_tex_txt[0x80];
#else
u8 int_ike_tent_bike_handle1_tex_txt[] = {
#include "assets/int_ike_tent_bike_handle1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_bike_chiar1_tex_txt[0x40];
#else
u8 int_ike_tent_bike_chiar1_tex_txt[] = {
#include "assets/int_ike_tent_bike_chiar1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_bike_chiar2_tex_txt[0x40];
#else
u8 int_ike_tent_bike_chiar2_tex_txt[] = {
#include "assets/int_ike_tent_bike_chiar2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_bike_frame1_tex_txt[0x400];
#else
u8 int_ike_tent_bike_frame1_tex_txt[] = {
#include "assets/int_ike_tent_bike_frame1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_tent_bike01_v[0x690 / sizeof(Vtx)];
#else
Vtx int_ike_tent_bike01_v[] = {
#include "assets/int_ike_tent_bike01_v.inc"
};
#endif

Gfx int_ike_tent_bike01_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_tent_bike01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_tent_bike_tire1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_tent_bike01_v, 30, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_tent_bike_tire2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(14, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 15, 16, 17, 15, 17, 12, 18, 10, 9),
    gsSPNTriangles_5b(18, 9, 19, 14, 13, 20, 14, 20, 21, 19, 17, 16),
    gsSPNTriangles_5b(19, 16, 18, 11, 21, 20, 11, 20, 8, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_tent_bike_tire1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsSPNTrianglesInit_5b(2, 22, 23, 24, 22, 24, 25, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_tent_bike_tire2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_tent_bike01_v[30], 30, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 7, 8, 9, 7, 9, 4, 10, 2, 1),
    gsSPNTriangles_5b(10, 1, 11, 6, 5, 12, 6, 12, 13, 11, 9, 8),
    gsSPNTriangles_5b(11, 8, 10, 3, 13, 12, 3, 12, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_tent_bike_pedal1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 14, 15, 16, 14, 16, 17, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 18, 19, 20, 18, 20, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_tent_bike_tire3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 22, 23, 24, 22, 24, 25, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_tent_bike_handle2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 28),
    gsSPNTrianglesInit_5b(2, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_tent_bike_tire3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_tent_bike01_v[60], 31, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_tent_bike_frame2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_tent_bike_handle1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 28),
    gsSPNTrianglesInit_5b(8, 8, 9, 10, 8, 10, 11, 11, 12, 13),
    gsSPNTriangles_5b(11, 13, 8, 14, 15, 12, 14, 12, 11, 11, 10, 16),
    gsSPNTriangles_5b(11, 16, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_tent_bike_chiar1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 17, 18, 19, 17, 20, 21, 17, 21, 18),
    gsSPNTriangles_5b(20, 22, 23, 20, 23, 21, 22, 24, 25, 22, 25, 23),
    gsSPNTriangles_5b(19, 25, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_tent_bike_chiar2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
    gsSPNTrianglesInit_5b(3, 26, 27, 28, 26, 28, 29, 29, 30, 26),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_tent_bike_frame2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_tent_bike01_v[91], 14, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 3),
    gsSPNTriangles_5b(4, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_ike_tent_bike_frame1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 6, 7, 8, 6, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
