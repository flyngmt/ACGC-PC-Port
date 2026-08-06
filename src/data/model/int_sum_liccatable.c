#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_liccatable_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_liccatable_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_liccatable_pal[] = {
#include "assets/int_sum_liccatable_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccatable_top_txt[0x200];
#else
u8 int_sum_liccatable_top_txt[] = {
#include "assets/int_sum_liccatable_top_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccatable_leg_txt[0x300];
#else
u8 int_sum_liccatable_leg_txt[] = {
#include "assets/int_sum_liccatable_leg_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccatable_side_txt[0x80];
#else
u8 int_sum_liccatable_side_txt[] = {
#include "assets/int_sum_liccatable_side_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_liccatable_v[0x210 / sizeof(Vtx)];
#else
Vtx int_sum_liccatable_v[] = {
#include "assets/int_sum_liccatable_v.inc"
};
#endif

Gfx int_sum_liccatable_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_liccatable_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_liccatable_side_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_liccatable_v, 24, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 3, 1, 1, 4, 2),
    gsSPNTriangles_5b(1, 5, 4, 5, 6, 4, 6, 7, 4, 6, 8, 7),
    gsSPNTriangles_5b(6, 9, 8, 9, 10, 8, 10, 11, 8, 10, 12, 11),
    gsSPNTriangles_5b(10, 13, 12, 14, 12, 15, 12, 13, 15, 16, 15, 17),
    gsSPNTriangles_5b(16, 14, 15, 18, 16, 19, 16, 17, 19, 20, 19, 21),
    gsSPNTriangles_5b(20, 18, 19, 22, 20, 23, 20, 21, 23, 22, 23, 0),
    gsSPNTriangles_5b(23, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_liccatable_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_liccatable_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_liccatable_leg_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_liccatable_v[24], 9, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 1, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_liccatable_top_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 5, 6, 7, 5, 7, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};
