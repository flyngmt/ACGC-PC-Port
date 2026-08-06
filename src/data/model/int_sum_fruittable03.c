#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_fruittable03_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_fruittable03_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_fruittable03_pal[] = {
#include "assets/int_sum_fruittable03_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruittable03_top_tex_txt[0x200];
#else
u8 int_sum_fruittable03_top_tex_txt[] = {
#include "assets/int_sum_fruittable03_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_fruittable03_side_tex_txt[0x200];
#else
u8 int_sum_fruittable03_side_tex_txt[] = {
#include "assets/int_sum_fruittable03_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_fruittable03_v[0x230 / sizeof(Vtx)];
#else
Vtx int_sum_fruittable03_v[] = {
#include "assets/int_sum_fruittable03_v.inc"
};
#endif

Gfx int_sum_fruittable03_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_fruittable03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_fruittable03_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_fruittable03_v, 8, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 6, 0, 2),
    gsSPNTriangles_5b(6, 2, 7, 5, 6, 7, 5, 7, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_fruittable03_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsSPVertex(&int_sum_fruittable03_v[8], 27, 0),
    gsSPNTrianglesInit_5b(32, 0, 1, 2, 3, 4, 5, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 0, 10, 11, 2, 8, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 16, 5, 5, 16, 14, 15, 17, 12, 18, 19, 20),
    gsSPNTriangles_5b(3, 21, 18, 18, 21, 7, 22, 23, 18, 0, 24, 20),
    gsSPNTriangles_5b(22, 24, 0, 7, 21, 5, 5, 21, 3, 5, 4, 15),
    gsSPNTriangles_5b(14, 6, 5, 7, 19, 18, 18, 23, 3, 18, 24, 22),
    gsSPNTriangles_5b(20, 24, 18, 20, 1, 0, 0, 9, 22, 2, 11, 0),
    gsSPNTriangles_5b(0, 11, 8, 10, 25, 8, 2, 26, 10, 12, 16, 15),
    gsSPNTriangles_5b(14, 16, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
