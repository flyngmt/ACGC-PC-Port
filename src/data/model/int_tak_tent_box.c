#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_tent_box_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_tent_box_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_tent_box_pal[] = {
#include "assets/int_tak_tent_box_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_tent_box_2_tex[0x80];
#else
u8 int_tak_tent_box_2_tex[] = {
#include "assets/int_tak_tent_box_2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_tent_box_1_tex[0x400];
#else
u8 int_tak_tent_box_1_tex[] = {
#include "assets/int_tak_tent_box_1_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_tent_box_v[0x410 / sizeof(Vtx)];
#else
Vtx int_tak_tent_box_v[] = {
#include "assets/int_tak_tent_box_v.inc"
};
#endif

Gfx int_tak_tent_box_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_tent_box_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_tak_tent_box_1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_tent_box_v, 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 8, 9, 0, 9, 1, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 14, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 3, 2, 22, 2, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 28, 29, 30, 28, 30, 31, 0, 0, 0),
    gsSPVertex(&int_tak_tent_box_v[32], 29, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 3, 4, 5),
    gsSPNTriangles_5b(3, 5, 6, 19, 20, 21, 19, 21, 22, 22, 23, 24),
    gsSPNTriangles_5b(22, 24, 25, 25, 26, 27, 25, 27, 28, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 7, 8, 9, 7, 9, 10, 11, 12, 13),
    gsSPNTriangles_5b(11, 13, 14, 15, 16, 17, 15, 17, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_tent_box_2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_tent_box_v[61], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
