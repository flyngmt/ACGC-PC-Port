#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_pl_dracaena_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_pl_dracaena_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_pl_dracaena_pal[] = {
#include "assets/int_sum_pl_dracaena_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_dracaera_earth_tex[0x80];
#else
u8 int_sum_pl_dracaera_earth_tex[] = {
#include "assets/int_sum_pl_dracaera_earth_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_dracaera_hachi_tex[0x100];
#else
u8 int_sum_pl_dracaera_hachi_tex[] = {
#include "assets/int_sum_pl_dracaera_hachi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_dracaera_leaf_tex[0x400];
#else
u8 int_sum_pl_dracaera_leaf_tex[] = {
#include "assets/int_sum_pl_dracaera_leaf_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_dracaera_base_tex[0x180];
#else
u8 int_sum_pl_dracaera_base_tex[] = {
#include "assets/int_sum_pl_dracaera_base_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_pl_dracaena_v[0x380 / sizeof(Vtx)];
#else
Vtx int_sum_pl_dracaena_v[] = {
#include "assets/int_sum_pl_dracaena_v.inc"
};
#endif

Gfx int_sum_pl_dracaena_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_pl_dracaena_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_pl_dracaera_earth_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_pl_dracaena_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_pl_dracaena_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_pl_dracaena_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_pl_dracaera_base_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_pl_dracaena_v[4], 5, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_sum_pl_dracaera_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_pl_dracaena_v[9], 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 1, 3, 4, 1, 4, 2),
    gsSPNTriangles_5b(3, 5, 6, 3, 6, 7, 5, 8, 6, 7, 9, 10),
    gsSPNTriangles_5b(7, 10, 4, 9, 11, 10, 12, 7, 3, 12, 4, 7),
    gsSPNTriangles_5b(12, 3, 4, 13, 14, 15, 16, 13, 15, 16, 15, 17),
    gsSPNTriangles_5b(18, 19, 20, 21, 18, 20, 21, 20, 16, 22, 21, 17),
    gsSPNTriangles_5b(22, 17, 23, 24, 22, 23, 25, 21, 17, 25, 17, 16),
    gsSPNTriangles_5b(25, 16, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 26, 27, 28, 28, 27, 29, 0, 0, 0),
    gsSPVertex(&int_sum_pl_dracaena_v[39], 17, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 1, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 5, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_pl_dracaera_hachi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 11, 10, 12, 13, 14, 15),
    gsSPNTriangles_5b(11, 16, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
