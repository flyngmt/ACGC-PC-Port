#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_taiko01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_taiko01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_taiko01_pal[] = {
#include "assets/int_sum_taiko01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_taiko01_foot_txt_txt[0x80];
#else
u8 int_sum_taiko01_foot_txt_txt[] = {
#include "assets/int_sum_taiko01_foot_txt_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_taiko01_standside_txt_txt[0x180];
#else
u8 int_sum_taiko01_standside_txt_txt[] = {
#include "assets/int_sum_taiko01_standside_txt_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_taiko01_standfront_txt_txt[0x180];
#else
u8 int_sum_taiko01_standfront_txt_txt[] = {
#include "assets/int_sum_taiko01_standfront_txt_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_taiko01_side_txt_txt[0x300];
#else
u8 int_sum_taiko01_side_txt_txt[] = {
#include "assets/int_sum_taiko01_side_txt_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_taiko01_front_txt_txt[0x100];
#else
u8 int_sum_taiko01_front_txt_txt[] = {
#include "assets/int_sum_taiko01_front_txt_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_taiko01_v[0x370 / sizeof(Vtx)];
#else
Vtx int_sum_taiko01_v[] = {
#include "assets/int_sum_taiko01_v.inc"
};
#endif

Gfx int_sum_taiko01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_taiko01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_taiko01_foot_txt_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_taiko01_v, 24, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_taiko01_standside_txt_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 188),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_taiko01_standfront_txt_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 188),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_taiko01_side_txt_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 188),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_taiko01_v[24], 31, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 4, 1, 5, 6, 7),
    gsSPNTriangles_5b(8, 6, 5, 6, 8, 9, 10, 11, 0, 12, 5, 3),
    gsSPNTriangles_5b(11, 13, 3, 5, 12, 8, 3, 13, 12, 14, 4, 3),
    gsSPNTriangles_5b(3, 0, 11, 1, 0, 3, 0, 15, 10, 2, 15, 0),
    gsSPNTriangles_5b(7, 14, 5, 15, 2, 16, 17, 10, 15, 18, 7, 6),
    gsSPNTriangles_5b(3, 5, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_taiko01_front_txt_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(8, 19, 20, 21, 20, 22, 21, 20, 23, 22),
    gsSPNTriangles_5b(21, 24, 19, 25, 26, 27, 25, 27, 28, 29, 25, 28),
    gsSPNTriangles_5b(28, 30, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
