#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_systemnote_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_systemnote_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_systemnote_pal[] = {
#include "assets/int_nog_systemnote_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_systemnote_tex[0x400];
#else
u8 int_nog_systemnote_tex[] = {
#include "assets/int_nog_systemnote_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_systemnote_v[0x320 / sizeof(Vtx)];
#else
Vtx int_nog_systemnote_v[] = {
#include "assets/int_nog_systemnote_v.inc"
};
#endif

Gfx int_nog_systemnote_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_systemnote_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_nog_systemnote_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_systemnote_v, 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 8, 11, 9, 8, 12, 11),
    gsSPNTriangles_5b(9, 13, 10, 14, 15, 16, 14, 16, 17, 17, 16, 18),
    gsSPNTriangles_5b(17, 18, 19, 19, 18, 20, 19, 20, 21, 22, 23, 24),
    gsSPNTriangles_5b(23, 25, 24, 23, 26, 25, 26, 27, 25, 28, 29, 30),
    gsSPNTriangles_5b(29, 31, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_systemnote_v[32], 18, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 1, 3, 2, 3, 4, 5),
    gsSPNTriangles_5b(3, 5, 2, 5, 6, 7, 5, 7, 2, 4, 8, 5),
    gsSPNTriangles_5b(8, 6, 5, 9, 10, 11, 10, 12, 11, 12, 13, 11),
    gsSPNTriangles_5b(13, 7, 11, 7, 6, 14, 7, 14, 11, 14, 15, 9),
    gsSPNTriangles_5b(14, 9, 11, 6, 16, 14, 16, 15, 14, 1, 0, 17),
    gsSPNTriangles_5b(13, 12, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
