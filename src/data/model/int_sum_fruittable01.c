#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_fruittable01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_fruittable01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_fruittable01_pal[] = {
#include "assets/int_sum_fruittable01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruittable01_side_tex_txt[0x300];
#else
u8 int_sum_fruittable01_side_tex_txt[] = {
#include "assets/int_sum_fruittable01_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruittable01_top_tex_txt[0x200];
#else
u8 int_sum_fruittable01_top_tex_txt[] = {
#include "assets/int_sum_fruittable01_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruittable01_douwnside_tex_txt[0x100];
#else
u8 int_sum_fruittable01_douwnside_tex_txt[] = {
#include "assets/int_sum_fruittable01_douwnside_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruittable01_douwntop_tex_txt[0x80];
#else
u8 int_sum_fruittable01_douwntop_tex_txt[] = {
#include "assets/int_sum_fruittable01_douwntop_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_fruittable01_v[0x2D0 / sizeof(Vtx)];
#else
Vtx int_sum_fruittable01_v[] = {
#include "assets/int_sum_fruittable01_v.inc"
};
#endif

Gfx int_sum_fruittable01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_fruittable01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_fruittable01_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 764, 188),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_fruittable01_v, 29, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 0, 3, 4, 5, 6, 2),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 9, 10, 12, 4, 13, 14, 15),
    gsSPNTriangles_5b(15, 9, 11, 9, 8, 10, 4, 11, 10, 16, 15, 17),
    gsSPNTriangles_5b(16, 18, 9, 9, 18, 7, 4, 12, 0, 19, 13, 4),
    gsSPNTriangles_5b(13, 19, 20, 19, 21, 22, 2, 6, 21, 2, 1, 5),
    gsSPNTriangles_5b(2, 3, 0, 19, 3, 2, 2, 21, 19, 11, 4, 13),
    gsSPNTriangles_5b(13, 15, 11, 4, 3, 19, 9, 15, 16, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_fruittable01_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsSPNTrianglesInit_5b(4, 23, 24, 25, 25, 26, 23, 27, 28, 25),
    gsSPNTriangles_5b(25, 24, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_fruittable01_douwnside_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsSPVertex(&int_sum_fruittable01_v[29], 16, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(5, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_fruittable01_douwntop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(4, 11, 12, 13, 14, 15, 13, 13, 15, 11),
    gsSPNTriangles_5b(13, 12, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
