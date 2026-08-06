#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_turip_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 int_nog_turip_grass_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 int_nog_turip_grass_tex[] = {
#include "assets/int_nog_turip_grass_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_turip_leaf_tex[0x80];
#else
u8 int_nog_turip_leaf_tex[] = {
#include "assets/int_nog_turip_leaf_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_turip_flower_tex[0x100];
#else
u8 int_nog_turip_flower_tex[] = {
#include "assets/int_nog_turip_flower_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_turip_v[0x510 / sizeof(Vtx)];
#else
Vtx int_nog_turip_v[] = {
#include "assets/int_nog_turip_v.inc"
};
#endif

Gfx int_nog_turip_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_turip_grass_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_turip_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_turipT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_nog_turip_flower_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_turip_v[4], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 5, 9, 6, 10, 11, 10, 12, 5, 8, 13),
    gsSPNTriangles_5b(6, 5, 14, 10, 6, 15, 12, 10, 16, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 21, 20, 22, 23, 22, 24, 25, 26, 18, 17),
    gsSPNTriangles_5b(27, 20, 18, 28, 24, 22, 29, 22, 20, 0, 0, 0),
    gsSPVertex(&int_nog_turip_v[34], 32, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 11, 12, 9, 13, 10, 14),
    gsSPNTriangles_5b(15, 14, 16, 9, 12, 17, 10, 9, 18, 14, 10, 19),
    gsSPNTriangles_5b(16, 14, 20, 21, 22, 23, 21, 23, 24, 25, 26, 27),
    gsSPNTriangles_5b(25, 27, 28, 29, 30, 31, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_turip_v[66], 15, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_turip_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 3, 4, 5, 5, 6, 3, 7, 8, 9),
    gsSPNTriangles_5b(9, 10, 7, 11, 12, 13, 13, 14, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};
