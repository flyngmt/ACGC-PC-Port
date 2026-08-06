#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_mario_coin_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_mario_coin_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_mario_coin_a_pal[] = {
#include "assets/int_iku_mario_coin_a_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_iku_mario_coin_b_pal[0x20 / sizeof(u16)];
#else
u16 int_iku_mario_coin_b_pal[] = {
#include "assets/int_iku_mario_coin_b_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_iku_mario_coin_c_pal[0x20 / sizeof(u16)];
#else
u16 int_iku_mario_coin_c_pal[] = {
#include "assets/int_iku_mario_coin_c_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_mario_coin_tex[0x200];
#else
u8 int_iku_mario_coin_tex[] = {
#include "assets/int_iku_mario_coin_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_mario_coin_center_tex[0x100];
#else
u8 int_iku_mario_coin_center_tex[] = {
#include "assets/int_iku_mario_coin_center_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_mario_coin_v[0x2C0 / sizeof(Vtx)];
#else
Vtx int_iku_mario_coin_v[] = {
#include "assets/int_iku_mario_coin_v.inc"
};
#endif

Gfx int_iku_mario_coin_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_2_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iku_mario_coin_center_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_mario_coin_v, 32, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 4, 6, 7, 4, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 12, 8, 11, 12, 11, 13, 6, 12, 13),
    gsSPNTriangles_5b(6, 13, 7, 14, 15, 16, 14, 16, 17, 15, 18, 19),
    gsSPNTriangles_5b(15, 19, 16, 18, 20, 21, 18, 21, 19, 22, 14, 17),
    gsSPNTriangles_5b(22, 17, 23, 24, 22, 23, 24, 23, 25, 9, 24, 25),
    gsSPNTriangles_5b(9, 25, 10, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsSPVertex(&int_iku_mario_coin_v[30], 14, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_mario_coin_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 4, 5, 6, 4, 7, 5, 7, 8, 5),
    gsSPNTriangles_5b(8, 6, 5, 9, 10, 11, 10, 12, 11, 9, 13, 10),
    gsSPNTriangles_5b(13, 12, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
