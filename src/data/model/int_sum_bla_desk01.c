#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_bla_desk01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_bla_desk01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_bla_desk01_pal[] = {
#include "assets/int_sum_bla_desk01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bla_desk01_top_tex[0x100];
#else
u8 int_sum_bla_desk01_top_tex[] = {
#include "assets/int_sum_bla_desk01_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bla_desk01_side2_tex[0x800];
#else
u8 int_sum_bla_desk01_side2_tex[] = {
#include "assets/int_sum_bla_desk01_side2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_bla_desk01_v[0x240 / sizeof(Vtx)];
#else
Vtx int_sum_bla_desk01_v[] = {
#include "assets/int_sum_bla_desk01_v.inc"
};
#endif

Gfx int_sum_bla_desk01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bla_desk01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, int_sum_bla_desk01_side2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_bla_desk01_v, 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 2, 7, 6, 2, 6, 3, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 20, 22, 23, 19, 18, 23),
    gsSPNTriangles_5b(19, 23, 22, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_bla_desk01_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_bla_desk01_v[32], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
