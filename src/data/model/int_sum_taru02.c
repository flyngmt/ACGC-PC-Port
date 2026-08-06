#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_taru02_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 it_sum_taru02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 it_sum_taru02_pal[] = {
#include "assets/it_sum_taru02_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_taru02_side_tex[0x200];
#else
u8 int_sum_taru02_side_tex[] = {
#include "assets/int_sum_taru02_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_taru02_top_tex[0x400];
#else
u8 int_sum_taru02_top_tex[] = {
#include "assets/int_sum_taru02_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_taru02_sentop_tex[0x80];
#else
u8 int_sum_taru02_sentop_tex[] = {
#include "assets/int_sum_taru02_sentop_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_taru02_v[0x320 / sizeof(Vtx)];
#else
Vtx int_sum_taru02_v[] = {
#include "assets/int_sum_taru02_v.inc"
};
#endif

Gfx int_sum_taru02_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, it_sum_taru02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_taru02_sentop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_taru02_v, 13, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_sum_taru02_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 3, 4, 5, 3, 6, 4, 7, 8, 9),
    gsSPNTriangles_5b(7, 9, 10, 11, 12, 8, 11, 8, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_taru02_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_taru02_v[13], 32, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 6, 5, 7),
    gsSPNTriangles_5b(6, 7, 8, 14, 15, 13, 14, 13, 12, 11, 10, 16),
    gsSPNTriangles_5b(11, 16, 17, 20, 21, 19, 20, 19, 18, 23, 22, 24),
    gsSPNTriangles_5b(23, 24, 25, 26, 27, 28, 26, 29, 27, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(15, 4, 1, 0, 4, 5, 6, 8, 7, 9),
    gsSPNTriangles_5b(4, 10, 11, 12, 13, 9, 4, 15, 14, 17, 16, 9),
    gsSPNTriangles_5b(18, 19, 9, 4, 22, 23, 25, 24, 9, 4, 21, 20),
    gsSPNTriangles_5b(4, 29, 26, 28, 27, 9, 3, 2, 9, 30, 31, 9),
    gsSPVertex(&int_sum_taru02_v[45], 5, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 4, 3, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
