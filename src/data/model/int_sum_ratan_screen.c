#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_ratan_screen_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_ratan_screen_pal[] = {
#include "assets/int_sum_ratan_screen_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_ratan_screen_front_tex[0x200];
#else
u8 int_sum_ratan_screen_front_tex[] = {
#include "assets/int_sum_ratan_screen_front_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_ratan_screen_v[0xE0 / sizeof(Vtx)];
#else
Vtx int_sum_ratan_screen_v[] = {
#include "assets/int_sum_ratan_screen_v.inc"
};
#endif

Gfx int_sum_ratan_screen_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_ratan_screen_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_ratan_screen_front_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_ratan_screen_v, 14, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(4, 0, 2, 0, 4, 5, 4, 6, 5, 6, 7, 5),
    gsSPNTriangles_5b(7, 0, 5, 1, 8, 9, 8, 10, 9, 10, 3, 9),
    gsSPNTriangles_5b(3, 1, 9, 3, 10, 11, 10, 8, 11, 8, 1, 11),
    gsSPNTriangles_5b(1, 3, 11, 7, 6, 12, 6, 4, 12, 4, 0, 12),
    gsSPNTriangles_5b(0, 7, 12, 4, 3, 13, 3, 1, 13, 1, 0, 13),
    gsSPNTriangles_5b(0, 4, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
