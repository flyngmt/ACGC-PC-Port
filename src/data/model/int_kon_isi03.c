#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_isi03_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kon_isi03_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kon_isi03_pal[] = {
#include "assets/int_kon_isi03_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_isi03_a_tex[0x300];
#else
u8 int_kon_isi03_a_tex[] = {
#include "assets/int_kon_isi03_a_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_isi03_b_tex[0x200];
#else
u8 int_kon_isi03_b_tex[] = {
#include "assets/int_kon_isi03_b_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_isi03_c_tex[0x200];
#else
u8 int_kon_isi03_c_tex[] = {
#include "assets/int_kon_isi03_c_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_isi03_d_tex[0x100];
#else
u8 int_kon_isi03_d_tex[] = {
#include "assets/int_kon_isi03_d_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_isi03_v[0x240 / sizeof(Vtx)];
#else
Vtx int_kon_isi03_v[] = {
#include "assets/int_kon_isi03_v.inc"
};
#endif

Gfx int_kon_isi03_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_isi03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_isi03_d_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_isi03_v, 21, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kon_isi03_c_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 4, 5, 6, 7, 4, 6, 8, 7, 6),
    gsSPNTriangles_5b(8, 6, 9, 5, 10, 6, 10, 11, 6, 11, 12, 6),
    gsSPNTriangles_5b(12, 9, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kon_isi03_b_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7, 13, 14, 15, 13, 16, 14, 14, 17, 15),
    gsSPNTriangles_5b(16, 18, 19, 16, 19, 14, 19, 20, 17, 19, 17, 14),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, int_kon_isi03_a_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_kon_isi03_v[21], 15, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 7, 8, 6, 5, 9, 10, 5, 10, 7),
    gsSPNTriangles_5b(11, 12, 13, 11, 13, 14, 12, 0, 3, 12, 3, 13),
    gsSPEndDisplayList(),
};
