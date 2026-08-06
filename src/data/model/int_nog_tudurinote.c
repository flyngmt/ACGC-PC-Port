#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_tudurinote_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_tudurinote_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_tudurinote_pal[] = {
#include "assets/int_nog_tudurinote_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_tudurinote_tex[0x800];
#else
u8 int_nog_tudurinote_tex[] = {
#include "assets/int_nog_tudurinote_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_tudurinote_v[0x460 / sizeof(Vtx)];
#else
Vtx int_nog_tudurinote_v[] = {
#include "assets/int_nog_tudurinote_v.inc"
};
#endif

Gfx int_nog_tudurinoteT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_tudurinote_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, int_nog_tudurinote_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_tudurinote_v, 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 3, 2, 8, 3, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 14, 16, 17, 15, 18, 19),
    gsSPNTriangles_5b(15, 19, 16, 17, 16, 20, 17, 20, 21, 16, 19, 22),
    gsSPNTriangles_5b(16, 22, 20, 23, 24, 25, 23, 25, 26, 24, 27, 28),
    gsSPNTriangles_5b(24, 28, 25, 21, 20, 24, 21, 24, 23, 20, 22, 27),
    gsSPNTriangles_5b(20, 27, 24, 26, 25, 29, 26, 29, 30, 25, 28, 31),
    gsSPNTriangles_5b(25, 31, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_tudurinote_v[32], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 6, 7, 8, 8, 9, 10, 11, 12, 13),
    gsSPNTriangles_5b(10, 14, 11, 13, 15, 4, 4, 16, 5, 17, 18, 19),
    gsSPNTriangles_5b(17, 19, 20, 21, 22, 23, 24, 25, 21, 26, 27, 24),
    gsSPNTriangles_5b(28, 29, 26, 3, 30, 0, 0, 31, 28, 0, 0, 0),
    gsSPVertex(&int_nog_tudurinote_v[64], 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
