#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_hos_mario_kinoko_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_hos_mario_kinoko_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_hos_mario_kinoko_pal[] = {
#include "assets/int_hos_mario_kinoko_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hos_mario_kino_top_txt[0x200];
#else
u8 int_hos_mario_kino_top_txt[] = {
#include "assets/int_hos_mario_kino_top_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hos_mario_kino_jiku_txt[0x200];
#else
u8 int_hos_mario_kino_jiku_txt[] = {
#include "assets/int_hos_mario_kino_jiku_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_hos_mario_kinoko_v[0x270 / sizeof(Vtx)];
#else
Vtx int_hos_mario_kinoko_v[] = {
#include "assets/int_hos_mario_kinoko_v.inc"
};
#endif

Gfx int_hos_mario_kinoko_all_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hos_mario_kinoko_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_hos_mario_kino_top_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 380, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_hos_mario_kinoko_v, 24, 0),
    gsSPNTrianglesInit_5b(30, 0, 1, 2, 3, 4, 1, 3, 1, 0),
    gsSPNTriangles_5b(5, 6, 4, 5, 4, 3, 6, 7, 8, 6, 8, 4),
    gsSPNTriangles_5b(4, 8, 9, 4, 9, 1, 1, 9, 2, 10, 0, 11),
    gsSPNTriangles_5b(12, 3, 0, 12, 0, 10, 13, 5, 3, 13, 3, 12),
    gsSPNTriangles_5b(14, 15, 16, 14, 16, 17, 17, 16, 18, 17, 18, 19),
    gsSPNTriangles_5b(19, 18, 20, 21, 10, 11, 22, 12, 10, 22, 10, 21),
    gsSPNTriangles_5b(23, 13, 12, 23, 12, 22, 15, 23, 22, 15, 22, 16),
    gsSPNTriangles_5b(16, 22, 21, 16, 21, 18, 18, 21, 20, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_hos_mario_kino_jiku_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsSPVertex(&int_hos_mario_kinoko_v[24], 15, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 6, 7, 5, 6, 5, 4, 3, 2, 8),
    gsSPNTriangles_5b(3, 8, 9, 10, 11, 0, 12, 10, 3, 13, 14, 6),
    gsSPNTriangles_5b(11, 13, 4, 4, 0, 11, 6, 4, 13, 3, 9, 12),
    gsSPNTriangles_5b(0, 3, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
