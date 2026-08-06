#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_fruitchair02_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_fruitchair02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_fruitchair02_pal[] = {
#include "assets/int_sum_fruitchair02_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruitchair02_leaf_tex_txt[0x80];
#else
u8 int_sum_fruitchair02_leaf_tex_txt[] = {
#include "assets/int_sum_fruitchair02_leaf_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruitchair02_side_tex_txt[0x300];
#else
u8 int_sum_fruitchair02_side_tex_txt[] = {
#include "assets/int_sum_fruitchair02_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruitchair02_seat_tex_txt[0x200];
#else
u8 int_sum_fruitchair02_seat_tex_txt[] = {
#include "assets/int_sum_fruitchair02_seat_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruitchair02_top_tex_txt[0x80];
#else
u8 int_sum_fruitchair02_top_tex_txt[] = {
#include "assets/int_sum_fruitchair02_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_fruitchair02_v[0x2A0 / sizeof(Vtx)];
#else
Vtx int_sum_fruitchair02_v[] = {
#include "assets/int_sum_fruitchair02_v.inc"
};
#endif

Gfx int_sum_fruitchair02_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_fruitchair02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_fruitchair02_leaf_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_fruitchair02_v, 29, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_fruitchair02_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 764, 188),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(22, 4, 5, 6, 7, 8, 9, 7, 10, 11),
    gsSPNTriangles_5b(12, 13, 9, 14, 15, 4, 16, 17, 4, 16, 18, 11),
    gsSPNTriangles_5b(11, 10, 19, 5, 4, 17, 4, 15, 16, 11, 17, 16),
    gsSPNTriangles_5b(6, 20, 4, 4, 20, 14, 11, 18, 7, 19, 21, 11),
    gsSPNTriangles_5b(9, 13, 22, 9, 8, 12, 9, 10, 7, 19, 10, 9),
    gsSPNTriangles_5b(9, 22, 19, 17, 11, 21, 21, 5, 17, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_fruitchair02_seat_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsSPNTrianglesInit_5b(4, 23, 24, 25, 25, 26, 23, 23, 26, 27),
    gsSPNTriangles_5b(27, 28, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_fruitchair02_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&int_sum_fruitchair02_v[29], 13, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 2, 5, 0, 2),
    gsSPNTriangles_5b(4, 6, 2, 1, 3, 2, 6, 5, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_fruitchair02_seat_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsSPNTrianglesInit_5b(4, 7, 8, 9, 10, 11, 12, 12, 7, 10),
    gsSPNTriangles_5b(9, 10, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
