#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_mario_koura_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_mario_koura_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_mario_koura_pal[] = {
#include "assets/int_iku_mario_koura_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_mario_koura_a_tex_txt[0x400];
#else
u8 int_iku_mario_koura_a_tex_txt[] = {
#include "assets/int_iku_mario_koura_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_mario_koura_b_tex_txt[0x400];
#else
u8 int_iku_mario_koura_b_tex_txt[] = {
#include "assets/int_iku_mario_koura_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_mario_koura_v[0x2E0 / sizeof(Vtx)];
#else
Vtx int_iku_mario_koura_v[] = {
#include "assets/int_iku_mario_koura_v.inc"
};
#endif

Gfx int_iku_mario_koura_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_mario_koura_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_iku_mario_koura_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_mario_koura_v, 13, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 6, 7, 0),
    gsSPNTriangles_5b(2, 8, 9, 4, 8, 2, 7, 10, 11, 1, 0, 11),
    gsSPNTriangles_5b(11, 5, 1, 11, 10, 12, 5, 12, 3, 0, 9, 6),
    gsSPNTriangles_5b(5, 2, 1, 11, 0, 7, 12, 5, 11, 2, 5, 4),
    gsSPNTriangles_5b(9, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_iku_mario_koura_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iku_mario_koura_v[13], 24, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 2, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 6, 5, 9, 5, 10, 10, 11, 12, 13, 14, 1),
    gsSPNTriangles_5b(3, 15, 16, 17, 18, 3, 16, 15, 5, 11, 14, 13),
    gsSPNTriangles_5b(19, 14, 11, 3, 18, 8, 1, 0, 13, 5, 9, 16),
    gsSPNTriangles_5b(1, 20, 17, 19, 20, 1, 11, 10, 7, 16, 4, 3),
    gsSPNTriangles_5b(10, 21, 9, 12, 21, 10, 13, 12, 11, 2, 22, 0),
    gsSPNTriangles_5b(4, 22, 2, 17, 2, 1, 3, 2, 17, 7, 10, 5),
    gsSPNTriangles_5b(7, 23, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_iku_mario_koura_v[37], 9, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 2, 5, 6, 7),
    gsSPNTriangles_5b(7, 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
