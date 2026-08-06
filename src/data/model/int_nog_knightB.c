#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_knightB_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_knightB_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_knightB_pal[] = {
#include "assets/int_nog_knightB_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_knightB_head_tex[0x400];
#else
u8 int_nog_knightB_head_tex[] = {
#include "assets/int_nog_knightB_head_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_knightB_top_tex[0x80];
#else
u8 int_nog_knightB_top_tex[] = {
#include "assets/int_nog_knightB_top_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_knightB_v[0x3E0 / sizeof(Vtx)];
#else
Vtx int_nog_knightB_v[] = {
#include "assets/int_nog_knightB_v.inc"
};
#endif

Gfx int_nog_knightBT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_knightB_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_knightB_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_knightB_v, 6, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_nog_knightB_head_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_nog_knightB_v[6], 32, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(1, 5, 4, 10, 11, 3, 10, 3, 4, 12, 13, 10),
    gsSPNTriangles_5b(12, 10, 14, 16, 17, 18, 16, 18, 11, 10, 13, 20),
    gsSPNTriangles_5b(11, 10, 20, 16, 11, 20, 16, 20, 7, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(13, 6, 7, 8, 6, 8, 9, 7, 6, 15),
    gsSPNTriangles_5b(19, 17, 16, 7, 15, 21, 19, 16, 22, 2, 23, 24),
    gsSPNTriangles_5b(2, 24, 0, 7, 21, 22, 7, 22, 16, 25, 26, 27),
    gsSPNTriangles_5b(28, 29, 25, 30, 31, 28, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_knightB_v[38], 24, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 4, 0, 5, 6, 3),
    gsSPNTriangles_5b(7, 8, 9, 7, 10, 11, 7, 12, 13, 13, 14, 7),
    gsSPNTriangles_5b(15, 16, 7, 17, 8, 7, 18, 19, 20, 21, 22, 23),
    gsSPEndDisplayList(),
};
