#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_schoolnote_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_schoolnote_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_schoolnote_pal[] = {
#include "assets/int_nog_schoolnote_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_schoolnote_tex[0x400];
#else
u8 int_nog_schoolnote_tex[] = {
#include "assets/int_nog_schoolnote_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_schoolnote_v[0x3D0 / sizeof(Vtx)];
#else
Vtx int_nog_schoolnote_v[] = {
#include "assets/int_nog_schoolnote_v.inc"
};
#endif

Gfx int_nog_schoolnote_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_schoolnote_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_nog_schoolnote_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_schoolnote_v, 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 3, 4, 6, 7, 4, 7, 5, 6, 8, 9),
    gsSPNTriangles_5b(6, 9, 7, 10, 11, 12, 10, 12, 13, 10, 13, 14),
    gsSPNTriangles_5b(10, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 20, 23, 24, 20, 24, 25, 26, 27, 28),
    gsSPNTriangles_5b(26, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_schoolnote_v[30], 31, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 3, 2, 6, 3, 6, 7, 7, 6, 8),
    gsSPNTriangles_5b(7, 8, 9, 9, 10, 7, 7, 11, 3, 0, 12, 4),
    gsSPNTriangles_5b(3, 13, 0, 4, 14, 15, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(20, 21, 22, 23, 24, 25, 22, 26, 23, 25, 27, 28),
    gsSPNTriangles_5b(28, 29, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
