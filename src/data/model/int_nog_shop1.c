#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_shop1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_shop1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_shop1_pal[] = {
#include "assets/int_nog_shop1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_shop1_body_tex[0x400];
#else
u8 int_nog_shop1_body_tex[] = {
#include "assets/int_nog_shop1_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_shop1_grass_tex[0x80];
#else
u8 int_nog_shop1_grass_tex[] = {
#include "assets/int_nog_shop1_grass_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_shop1_roof_tex[0x200];
#else
u8 int_nog_shop1_roof_tex[] = {
#include "assets/int_nog_shop1_roof_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_shop1_back_tex[0x100];
#else
u8 int_nog_shop1_back_tex[] = {
#include "assets/int_nog_shop1_back_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_shop1_v[0x440 / sizeof(Vtx)];
#else
Vtx int_nog_shop1_v[] = {
#include "assets/int_nog_shop1_v.inc"
};
#endif

Gfx int_nog_shop1_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_shop1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_nog_shop1_back_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_shop1_v, 28, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_shop1_roof_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 4, 5, 6, 4, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_shop1_grass_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 26, 27, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_shop1_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_shop1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_nog_shop1_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_shop1_v[28], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 1, 4, 2),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 9, 10, 11, 9, 11, 12),
    gsSPNTriangles_5b(10, 13, 11, 18, 19, 20, 18, 20, 21, 21, 20, 22),
    gsSPNTriangles_5b(21, 22, 23, 26, 27, 28, 26, 28, 29, 30, 31, 27),
    gsSPNTriangles_5b(30, 27, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 14, 15, 16, 14, 16, 17, 24, 16, 15),
    gsSPNTriangles_5b(24, 15, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_shop1_offT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_nog_shop1_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_shop1_v[60], 8, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 1, 0, 4),
    gsSPNTriangles_5b(1, 4, 5, 6, 7, 5, 6, 5, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};
