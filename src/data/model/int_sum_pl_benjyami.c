#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_pl_benjyami_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_pl_benjyami_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_pl_benjyami_pal[] = {
#include "assets/int_sum_pl_benjyami_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_benjyami_hachi_tex[0x100];
#else
u8 int_sum_pl_benjyami_hachi_tex[] = {
#include "assets/int_sum_pl_benjyami_hachi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_benjyami_earth_tex[0x80];
#else
u8 int_sum_pl_benjyami_earth_tex[] = {
#include "assets/int_sum_pl_benjyami_earth_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_benjyami_stand_tex[0x180];
#else
u8 int_sum_pl_benjyami_stand_tex[] = {
#include "assets/int_sum_pl_benjyami_stand_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_benjyami_leaf_tex[0x200];
#else
u8 int_sum_pl_benjyami_leaf_tex[] = {
#include "assets/int_sum_pl_benjyami_leaf_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_pl_benjyami_v[0x2E0 / sizeof(Vtx)];
#else
Vtx int_sum_pl_benjyami_v[] = {
#include "assets/int_sum_pl_benjyami_v.inc"
};
#endif

Gfx int_sum_pl_benjyami_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_pl_benjyami_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_pl_benjyami_earth_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_pl_benjyami_v, 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 3, 0),
    gsSPNTriangles_5b(4, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_pl_benjyami_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_pl_benjyami_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_pl_benjyami_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_pl_benjyami_v[6], 20, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 0, 4, 2),
    gsSPNTriangles_5b(0, 2, 5, 0, 6, 2, 0, 2, 7, 8, 2, 9),
    gsSPNTriangles_5b(8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(5, 10, 11, 12, 10, 12, 13, 11, 14, 12),
    gsSPNTriangles_5b(14, 13, 12, 11, 13, 12, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_pl_benjyami_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 15, 16, 17, 15, 18, 19, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_pl_benjyami_hachi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_pl_benjyami_v[26], 20, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(5, 6, 7, 8, 5, 7, 9, 6, 5, 5, 8, 10),
    gsSPNTriangles_5b(5, 10, 11, 12, 5, 11, 13, 14, 15, 16, 17, 15),
    gsSPNTriangles_5b(14, 16, 15, 18, 11, 14, 16, 14, 11, 16, 11, 10),
    gsSPNTriangles_5b(1, 0, 15, 1, 15, 17, 19, 15, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
