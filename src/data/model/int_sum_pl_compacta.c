#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_pl_compacta_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_pl_compacta_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_pl_compacta_pal[] = {
#include "assets/int_sum_pl_compacta_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_compacta_earth_tex[0x80];
#else
u8 int_sum_pl_compacta_earth_tex[] = {
#include "assets/int_sum_pl_compacta_earth_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_compacta_hachi_tex[0x100];
#else
u8 int_sum_pl_compacta_hachi_tex[] = {
#include "assets/int_sum_pl_compacta_hachi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_compacta_leaf_tex[0x200];
#else
u8 int_sum_pl_compacta_leaf_tex[] = {
#include "assets/int_sum_pl_compacta_leaf_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_compacta_leaf2_tex[0x200];
#else
u8 int_sum_pl_compacta_leaf2_tex[] = {
#include "assets/int_sum_pl_compacta_leaf2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_pl_compacta_v[0x3C0 / sizeof(Vtx)];
#else
Vtx int_sum_pl_compacta_v[] = {
#include "assets/int_sum_pl_compacta_v.inc"
};
#endif

Gfx int_sum_pl_compacta_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_pl_compacta_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_pl_compacta_earth_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_pl_compacta_v, 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 3, 0),
    gsSPNTriangles_5b(4, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_pl_compacta_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_pl_compacta_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_pl_compacta_leaf2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_pl_compacta_v[6], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 6, 8, 7, 10, 8, 11, 12, 13, 13, 14, 15),
    gsSPNTriangles_5b(11, 13, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_pl_compacta_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_pl_compacta_v[22], 25, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(17, 18, 19, 17, 20, 18, 21, 22, 23, 22, 24, 23),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_pl_compacta_hachi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_pl_compacta_v[47], 13, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 1, 3, 6),
    gsSPNTriangles_5b(4, 7, 8, 7, 9, 10, 11, 0, 12, 0, 0, 0),
    gsSPEndDisplayList(),
};
