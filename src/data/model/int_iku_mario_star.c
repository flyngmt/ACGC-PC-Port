#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_mario_star_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_mario_star_c_pal[] = {
#include "assets/int_iku_mario_star_c_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_iku_mario_star_a_pal[0x20 / sizeof(u16)];
#else
u16 int_iku_mario_star_a_pal[] = {
#include "assets/int_iku_mario_star_a_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_iku_mario_star_b_pal[0x20 / sizeof(u16)];
#else
u16 int_iku_mario_star_b_pal[] = {
#include "assets/int_iku_mario_star_b_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_iku_mario_star_d_pal[0x20 / sizeof(u16)];
#else
u16 int_iku_mario_star_d_pal[] = {
#include "assets/int_iku_mario_star_d_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_mario_star_a_tex_txt[0x80];
#else
u8 int_iku_mario_star_a_tex_txt[] = {
#include "assets/int_iku_mario_star_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_mario_star_v[0x200 / sizeof(Vtx)];
#else
Vtx int_iku_mario_star_v[] = {
#include "assets/int_iku_mario_star_v.inc"
};
#endif

Gfx int_iku_mario_star_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_2_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iku_mario_star_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_mario_star_v, 32, 0),
    gsSPNTrianglesInit_5b(40, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 7, 12, 8, 5, 10, 9, 8, 13, 4),
    gsSPNTriangles_5b(4, 13, 5, 8, 12, 14, 14, 13, 8, 5, 13, 14),
    gsSPNTriangles_5b(11, 10, 14, 14, 10, 5, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 15, 23, 7, 24, 11, 25, 26, 23, 12, 7),
    gsSPNTriangles_5b(26, 25, 18, 19, 27, 23, 18, 27, 19, 14, 12, 23),
    gsSPNTriangles_5b(23, 27, 14, 14, 27, 18, 14, 25, 11, 18, 25, 14),
    gsSPNTriangles_5b(11, 26, 28, 20, 26, 18, 29, 30, 21, 5, 9, 3),
    gsSPNTriangles_5b(28, 9, 11, 17, 1, 0, 24, 19, 23, 2, 31, 29),
    gsSPNTriangles_5b(8, 4, 6, 15, 0, 21, 21, 0, 29, 29, 0, 2),
    gsSPNTriangles_5b(17, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
