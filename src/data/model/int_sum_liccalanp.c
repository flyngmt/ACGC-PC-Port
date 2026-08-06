#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_liccalanp_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_liccalanp_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_liccalanp_pal[] = {
#include "assets/int_sum_liccalanp_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccalanp_shade_tex[0x100];
#else
u8 int_sum_liccalanp_shade_tex[] = {
#include "assets/int_sum_liccalanp_shade_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccalanp_stand_tex[0x180];
#else
u8 int_sum_liccalanp_stand_tex[] = {
#include "assets/int_sum_liccalanp_stand_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccalanp_hiki_tex[0x80];
#else
u8 int_sum_liccalanp_hiki_tex[] = {
#include "assets/int_sum_liccalanp_hiki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_liccalanp_base_tex[0x100];
#else
u8 int_sum_liccalanp_base_tex[] = {
#include "assets/int_sum_liccalanp_base_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_liccalanp_v[0x3D0 / sizeof(Vtx)];
#else
Vtx int_sum_liccalanp_v[] = {
#include "assets/int_sum_liccalanp_v.inc"
};
#endif

Gfx int_sum_liccalanp_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_liccalanp_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_liccalanp_base_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_liccalanp_v, 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 6, 7, 1, 6, 1, 0, 8, 9, 7),
    gsSPNTriangles_5b(8, 7, 6, 5, 4, 10, 5, 10, 11, 11, 10, 12),
    gsSPNTriangles_5b(11, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_liccalanp_offT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_liccalanp_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_liccalanp_base_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_liccalanp_v[14], 22, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_liccalanp_hiki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 6, 7, 8, 6, 9, 10, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 16, int_sum_liccalanp_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 11, 12, 13, 11, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(15, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_liccalanp_shade_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 19, 20, 21, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_sum_liccalanp_v[36], 25, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 9),
    gsSPNTriangles_5b(12, 9, 8, 11, 10, 5, 11, 5, 4, 3, 2, 13),
    gsSPNTriangles_5b(3, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(5, 14, 15, 16, 17, 18, 14, 19, 20, 21),
    gsSPNTriangles_5b(21, 18, 22, 23, 20, 24, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
