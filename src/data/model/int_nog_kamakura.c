#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_kamakura_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_kamakura_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_kamakura_pal[] = {
#include "assets/int_nog_kamakura_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_kamakura_body_tex[0x400];
#else
u8 int_nog_kamakura_body_tex[] = {
#include "assets/int_nog_kamakura_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_kamakura_grass_tex[0x200];
#else
u8 int_nog_kamakura_grass_tex[] = {
#include "assets/int_nog_kamakura_grass_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_kamakura_v[0x230 / sizeof(Vtx)];
#else
Vtx int_nog_kamakura_v[] = {
#include "assets/int_nog_kamakura_v.inc"
};
#endif

Gfx int_nog_kamakura_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_kamakura_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_kamakura_grass_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_kamakura_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_kamakura_offT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_nog_kamakura_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_kamakura_v[4], 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 0, 4, 4, 0, 2),
    gsSPEndDisplayList(),
};

Gfx int_nog_kamakura_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_kamakura_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_nog_kamakura_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_kamakura_v[9], 26, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 1, 3, 2, 3, 4, 5),
    gsSPNTriangles_5b(2, 3, 5, 11, 13, 12, 13, 1, 0, 12, 13, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(17, 6, 7, 8, 7, 9, 8, 4, 7, 6),
    gsSPNTriangles_5b(5, 4, 6, 10, 11, 12, 14, 15, 10, 15, 11, 10),
    gsSPNTriangles_5b(16, 15, 14, 17, 16, 14, 2, 18, 0, 5, 19, 2),
    gsSPNTriangles_5b(8, 20, 6, 6, 21, 5, 12, 22, 10, 0, 23, 12),
    gsSPNTriangles_5b(10, 24, 14, 14, 25, 17, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
