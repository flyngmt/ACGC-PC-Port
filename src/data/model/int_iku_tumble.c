#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_tumble_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_tumble_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_tumble_pal[] = {
#include "assets/int_iku_tumble_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_tumble_tex_txt[0x800];
#else
u8 int_iku_tumble_tex_txt[] = {
#include "assets/int_iku_tumble_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_tumble_v[0x350 / sizeof(Vtx)];
#else
Vtx int_iku_tumble_v[] = {
#include "assets/int_iku_tumble_v.inc"
};
#endif

Gfx int_iku_tumble_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_tumble_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, int_iku_tumble_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_tumble_v, 32, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 8, 8, 5, 4, 6, 7, 4, 9, 10, 11),
    gsSPNTriangles_5b(9, 11, 12, 13, 14, 15, 16, 17, 15, 15, 14, 16),
    gsSPNTriangles_5b(15, 17, 13, 18, 19, 20, 18, 20, 21, 22, 23, 24),
    gsSPNTriangles_5b(22, 24, 19, 19, 24, 25, 19, 25, 20, 26, 22, 19),
    gsSPNTriangles_5b(26, 19, 18, 27, 18, 21, 27, 21, 28, 23, 29, 30),
    gsSPNTriangles_5b(23, 30, 24, 24, 30, 31, 24, 31, 25, 0, 0, 0),
    gsSPVertex(&int_iku_tumble_v[32], 21, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 3, 5),
    gsSPNTriangles_5b(4, 5, 6, 7, 8, 4, 7, 4, 9, 9, 4, 6),
    gsSPNTriangles_5b(9, 6, 10, 8, 0, 3, 8, 3, 4, 11, 12, 13),
    gsSPNTriangles_5b(11, 13, 14, 15, 16, 17, 15, 17, 18, 14, 19, 20),
    gsSPNTriangles_5b(14, 20, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
