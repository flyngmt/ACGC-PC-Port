#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_pl_ananas_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_pl_ananas_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_pl_ananas_pal[] = {
#include "assets/int_sum_pl_ananas_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_ananas_earth_tex[0x80];
#else
u8 int_sum_pl_ananas_earth_tex[] = {
#include "assets/int_sum_pl_ananas_earth_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_ananas_hachi_tex[0x100];
#else
u8 int_sum_pl_ananas_hachi_tex[] = {
#include "assets/int_sum_pl_ananas_hachi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_ananas_hana_tex[0x200];
#else
u8 int_sum_pl_ananas_hana_tex[] = {
#include "assets/int_sum_pl_ananas_hana_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_ananas_leaf_tex[0x200];
#else
u8 int_sum_pl_ananas_leaf_tex[] = {
#include "assets/int_sum_pl_ananas_leaf_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_pl_ananas_v[0x4E0 / sizeof(Vtx)];
#else
Vtx int_sum_pl_ananas_v[] = {
#include "assets/int_sum_pl_ananas_v.inc"
};
#endif

Gfx int_sum_pl_ananas_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_pl_ananas_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_pl_ananas_earth_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_pl_ananas_v, 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 2, 1, 4),
    gsSPNTriangles_5b(2, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_pl_ananas_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_pl_ananas_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_pl_ananas_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_pl_ananas_v[6], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 13, 10, 12, 13, 12, 14),
    gsSPNTriangles_5b(13, 14, 15, 16, 17, 18, 16, 19, 20, 16, 20, 17),
    gsSPNTriangles_5b(21, 22, 23, 24, 25, 26, 27, 24, 26, 27, 26, 28),
    gsSPNTriangles_5b(27, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_sum_pl_ananas_v[36], 29, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 13, 14, 11, 10, 13, 11),
    gsSPNTriangles_5b(15, 16, 17, 18, 19, 20, 18, 21, 22, 18, 22, 19),
    gsSPNTriangles_5b(21, 23, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_pl_ananas_hana_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 27, 28, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_pl_ananas_hachi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_pl_ananas_v[65], 13, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 0, 4, 5, 6, 7),
    gsSPNTriangles_5b(6, 3, 8, 9, 5, 10, 11, 9, 12, 0, 0, 0),
    gsSPEndDisplayList(),
};
