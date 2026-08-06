#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_liccalowtable_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_liccalowtable_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_liccalowtable_pal[] = {
#include "assets/int_sum_liccalowtable_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccalowtable_top_tex[0x200];
#else
u8 int_sum_liccalowtable_top_tex[] = {
#include "assets/int_sum_liccalowtable_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccalowtable_side_tex[0x100];
#else
u8 int_sum_liccalowtable_side_tex[] = {
#include "assets/int_sum_liccalowtable_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccalowtable_leg_tex[0x100];
#else
u8 int_sum_liccalowtable_leg_tex[] = {
#include "assets/int_sum_liccalowtable_leg_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccalowtable_shelf_tex[0x100];
#else
u8 int_sum_liccalowtable_shelf_tex[] = {
#include "assets/int_sum_liccalowtable_shelf_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_liccalowtable_v[0x340 / sizeof(Vtx)];
#else
Vtx int_sum_liccalowtable_v[] = {
#include "assets/int_sum_liccalowtable_v.inc"
};
#endif

Gfx int_sum_liccalowtable_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_liccalowtable_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_liccalowtable_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_liccalowtable_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_liccalowtable_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_liccalowtable_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_liccalowtable_shelf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_liccalowtable_v[4], 16, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 5, 4, 8, 9, 5, 8, 10, 9),
    gsSPNTriangles_5b(8, 11, 10, 12, 13, 14, 13, 15, 14, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_liccalowtable_leg_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_liccalowtable_v[20], 20, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 2, 5, 6, 7),
    gsSPNTriangles_5b(5, 8, 9, 10, 11, 12, 13, 14, 12, 15, 16, 17),
    gsSPNTriangles_5b(15, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_liccalowtable_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_liccalowtable_v[40], 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 2, 3, 7, 8, 2, 9, 10, 5, 10, 6, 5),
    gsSPNTriangles_5b(4, 11, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
