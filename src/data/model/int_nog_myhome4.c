#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_myhome4_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 int_nog_myhome4_body_tex[0x600];
#else
ATTRIBUTE_ALIGN(32) u8 int_nog_myhome4_body_tex[] = {
#include "assets/int_nog_myhome4_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_myhome4_chimney_tex[0x80];
#else
u8 int_nog_myhome4_chimney_tex[] = {
#include "assets/int_nog_myhome4_chimney_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_myhome4_grass_tex[0x80];
#else
u8 int_nog_myhome4_grass_tex[] = {
#include "assets/int_nog_myhome4_grass_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_myhome4_v[0x630 / sizeof(Vtx)];
#else
Vtx int_nog_myhome4_v[] = {
#include "assets/int_nog_myhome4_v.inc"
};
#endif

Gfx int_nog_myhome4_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_myhome4_grass_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_myhome4_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_myhome4_chimney_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsSPVertex(&int_nog_myhome4_v[4], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_myhome4_v[36], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_myhome4_off_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_myhome4_chimney_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_myhome4_v[44], 15, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 11, 12, 13, 11, 13, 14),
    gsSPEndDisplayList(),
};

Gfx int_nog_myhome4_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 96, int_nog_myhome4_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_myhome4_v[59], 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 2, 3, 2, 4, 3),
    gsSPNTriangles_5b(2, 5, 6, 2, 6, 7, 8, 9, 10, 8, 10, 3),
    gsSPNTriangles_5b(11, 12, 13, 14, 15, 16, 14, 16, 17, 16, 18, 17),
    gsSPNTriangles_5b(19, 17, 20, 19, 20, 21, 17, 22, 23, 17, 23, 20),
    gsSPNTriangles_5b(13, 24, 11, 11, 25, 12, 2, 7, 26, 2, 26, 4),
    gsSPNTriangles_5b(4, 27, 8, 4, 8, 3, 28, 29, 30, 28, 30, 16),
    gsSPNTriangles_5b(31, 28, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_myhome4_v[91], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
