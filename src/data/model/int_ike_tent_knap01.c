#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_tent_knap01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_tent_knap01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_tent_knap01_pal[] = {
#include "assets/int_ike_tent_knap01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_knap_frontside_txt[0x80];
#else
u8 int_ike_tent_knap_frontside_txt[] = {
#include "assets/int_ike_tent_knap_frontside_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_knap_top_txt[0x100];
#else
u8 int_ike_tent_knap_top_txt[] = {
#include "assets/int_ike_tent_knap_top_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_knap_base_txt[0x100];
#else
u8 int_ike_tent_knap_base_txt[] = {
#include "assets/int_ike_tent_knap_base_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_knap_topback_txt[0x100];
#else
u8 int_ike_tent_knap_topback_txt[] = {
#include "assets/int_ike_tent_knap_topback_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_knap_side_txt[0x80];
#else
u8 int_ike_tent_knap_side_txt[] = {
#include "assets/int_ike_tent_knap_side_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_knap_back_txt[0x100];
#else
u8 int_ike_tent_knap_back_txt[] = {
#include "assets/int_ike_tent_knap_back_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_knap_front_txt[0x100];
#else
u8 int_ike_tent_knap_front_txt[] = {
#include "assets/int_ike_tent_knap_front_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_tent_knap_topside_txt[0x80];
#else
u8 int_ike_tent_knap_topside_txt[] = {
#include "assets/int_ike_tent_knap_topside_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_tent_knap01_v[0x640 / sizeof(Vtx)];
#else
Vtx int_ike_tent_knap01_v[] = {
#include "assets/int_ike_tent_knap01_v.inc"
};
#endif

Gfx int_ike_tent_knap01_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_tent_knap01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_tent_knap_frontside_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_tent_knap01_v, 26, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(10, 8, 9, 10, 11, 12, 13, 11, 13, 14),
    gsSPNTriangles_5b(10, 15, 8, 16, 17, 18, 19, 20, 21, 19, 21, 22),
    gsSPNTriangles_5b(18, 23, 16, 18, 24, 23, 15, 25, 8, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_tent_knap_top_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 60),
    gsSPVertex(&int_ike_tent_knap01_v[26], 24, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 1, 0, 3, 0, 4, 5),
    gsSPNTriangles_5b(2, 4, 0, 6, 7, 8, 3, 9, 1, 8, 0, 6),
    gsSPNTriangles_5b(0, 8, 3, 5, 6, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_tent_knap_base_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(2, 10, 11, 12, 10, 12, 13, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_tent_knap_topback_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 60),
    gsSPNTrianglesInit_5b(9, 14, 15, 16, 17, 18, 19, 19, 18, 20),
    gsSPNTriangles_5b(21, 19, 22, 19, 16, 17, 16, 19, 14, 21, 14, 19),
    gsSPNTriangles_5b(22, 23, 21, 20, 22, 19, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_ike_tent_knap_side_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 253, 255, 255),
    gsSPVertex(&int_ike_tent_knap01_v[50], 28, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_tent_knap_back_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 11, 9, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_tent_knap_front_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 15, 16, 17, 15, 17, 12),
    gsSPNTriangles_5b(12, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_tent_knap_topside_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 18, 19, 20, 21, 22, 18, 23, 24, 25),
    gsSPNTriangles_5b(18, 20, 21, 25, 26, 27, 27, 23, 25, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_tent_knap_base_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&int_ike_tent_knap01_v[78], 22, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile_Dolphin(8, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 124),
    gsSPNTrianglesInit_5b(6, 6, 7, 8, 6, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 16, 17, 14, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 18, 19, 20, 20, 19, 21, 0, 0, 0),
    gsSPEndDisplayList(),
};
