#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_museum_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_museum_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_museum_pal[] = {
#include "assets/int_nog_museum_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_museum_body_tex[0x400];
#else
u8 int_nog_museum_body_tex[] = {
#include "assets/int_nog_museum_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_museum_gate_tex[0x100];
#else
u8 int_nog_museum_gate_tex[] = {
#include "assets/int_nog_museum_gate_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_museum_grass_tex[0x80];
#else
u8 int_nog_museum_grass_tex[] = {
#include "assets/int_nog_museum_grass_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_museum_v[0x8E0 / sizeof(Vtx)];
#else
Vtx int_nog_museum_v[] = {
#include "assets/int_nog_museum_v.inc"
};
#endif

Gfx int_nog_museum_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_museum_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_museum_grass_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_museum_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_museum_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_museum_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_nog_museum_gate_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_museum_v[4], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 16, int_nog_museum_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPVertex(&int_nog_museum_v[20], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 6, 5, 16, 5, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 23, 24, 22, 24, 25, 26, 27, 28),
    gsSPNTriangles_5b(26, 28, 29, 30, 24, 23, 30, 23, 31, 0, 0, 0),
    gsSPVertex(&int_nog_museum_v[52], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 16, 23, 24, 25, 23, 25, 20, 26, 27, 28),
    gsSPNTriangles_5b(26, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_museum_v[82], 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 8, 10, 16, 17, 8, 16, 18, 12, 15),
    gsSPNTriangles_5b(18, 15, 17, 18, 17, 16, 19, 20, 21, 20, 22, 21),
    gsSPNTriangles_5b(22, 23, 21, 19, 24, 20, 19, 25, 24, 22, 26, 23),
    gsSPNTriangles_5b(26, 27, 23, 25, 28, 29, 25, 29, 24, 0, 0, 0),
    gsSPVertex(&int_nog_museum_v[112], 26, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(0, 5, 1, 0, 6, 5, 3, 7, 4, 7, 8, 4),
    gsSPNTriangles_5b(6, 9, 10, 6, 10, 5, 11, 12, 13, 12, 14, 13),
    gsSPNTriangles_5b(15, 16, 17, 15, 17, 18, 11, 13, 19, 20, 11, 19),
    gsSPNTriangles_5b(21, 15, 18, 21, 18, 20, 21, 20, 19, 22, 23, 24),
    gsSPNTriangles_5b(22, 24, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_museum_offT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_nog_museum_gate_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_museum_v[138], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
