#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx ef_reset_hole_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 ef_reset_hole_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 ef_reset_hole_pal[] = {
#include "assets/ef_reset_hole_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 ef_reset_hole_tex[0x100];
#else
u8 ef_reset_hole_tex[] = {
#include "assets/ef_reset_hole_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_reset_hole_v[0x620 / sizeof(Vtx)];
#else
Vtx ef_reset_hole_v[] = {
#include "assets/ef_reset_hole_v.inc"
};
#endif

Gfx ef_reset_hole_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, ef_reset_hole_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, ef_reset_hole_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_reset_hole_v, 32, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 4, 5, 6, 7, 1),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 9, 16, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30),
    gsSPVertex(&ef_reset_hole_v[31], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 9, 12, 10, 10, 13, 11, 14, 15, 16),
    gsSPNTriangles_5b(17, 18, 14, 17, 14, 16, 19, 20, 21, 22, 23, 19),
    gsSPNTriangles_5b(22, 19, 21, 24, 25, 26, 24, 27, 25, 25, 28, 26),
    gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&ef_reset_hole_v[63], 32, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 1, 4, 4, 5, 3),
    gsSPNTriangles_5b(6, 7, 8, 9, 10, 6, 9, 6, 8, 11, 12, 13),
    gsSPNTriangles_5b(14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25),
    gsSPNTriangles_5b(26, 27, 28, 29, 30, 31, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&ef_reset_hole_v[95], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
