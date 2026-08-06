#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_harddiary_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_harddiary_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_harddiary_pal[] = {
#include "assets/int_nog_harddiary_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_harddiary_tex[0x400];
#else
u8 int_nog_harddiary_tex[] = {
#include "assets/int_nog_harddiary_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_harddiary_v[0x240 / sizeof(Vtx)];
#else
Vtx int_nog_harddiary_v[] = {
#include "assets/int_nog_harddiary_v.inc"
};
#endif

Gfx int_nog_harddiaryT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_harddiary_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_nog_harddiary_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_harddiary_v, 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 6, 8, 9, 6, 9, 7, 8, 10, 11),
    gsSPNTriangles_5b(8, 11, 9, 12, 13, 14, 13, 15, 14, 15, 16, 14),
    gsSPNTriangles_5b(15, 17, 16, 17, 18, 16, 19, 20, 21, 19, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 26, 24, 24, 27, 25, 27, 28, 25),
    gsSPNTriangles_5b(27, 29, 28, 3, 2, 30, 3, 30, 31, 0, 0, 0),
    gsSPVertex(&int_nog_harddiary_v[32], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
