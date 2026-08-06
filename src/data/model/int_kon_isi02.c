#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_isi02_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kon_isi02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kon_isi02_pal[] = {
#include "assets/int_kon_isi02_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_isi02_front_tex[0x200];
#else
u8 int_kon_isi02_front_tex[] = {
#include "assets/int_kon_isi02_front_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_isi02_side_tex[0x100];
#else
u8 int_kon_isi02_side_tex[] = {
#include "assets/int_kon_isi02_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_isi02_top_tex[0x100];
#else
u8 int_kon_isi02_top_tex[] = {
#include "assets/int_kon_isi02_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_isi02_mini_tex[0x200];
#else
u8 int_kon_isi02_mini_tex[] = {
#include "assets/int_kon_isi02_mini_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_isi02_v[0x300 / sizeof(Vtx)];
#else
Vtx int_kon_isi02_v[] = {
#include "assets/int_kon_isi02_v.inc"
};
#endif

Gfx int_kon_isi02_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_isi02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kon_isi02_mini_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_isi02_v, 24, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 5, 8, 9, 5, 9, 6, 8, 0, 3),
    gsSPNTriangles_5b(8, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_kon_isi02_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(13, 10, 11, 12, 13, 14, 10, 14, 15, 10),
    gsSPNTriangles_5b(15, 11, 10, 16, 17, 18, 17, 19, 18, 16, 20, 17),
    gsSPNTriangles_5b(20, 21, 17, 21, 19, 17, 22, 12, 11, 22, 23, 12),
    gsSPNTriangles_5b(23, 13, 12, 13, 10, 12, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_isi02_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_kon_isi02_v[24], 24, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kon_isi02_front_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 12, 13, 14, 12, 14, 15, 16, 12, 15),
    gsSPNTriangles_5b(16, 15, 17, 18, 19, 20, 18, 20, 21, 19, 22, 23),
    gsSPNTriangles_5b(19, 23, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
