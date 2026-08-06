#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_isi06_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kon_isi06_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kon_isi06_pal[] = {
#include "assets/int_kon_isi06_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_isi06_a_tex[0x480];
#else
u8 int_kon_isi06_a_tex[] = {
#include "assets/int_kon_isi06_a_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_isi06_c_tex[0x100];
#else
u8 int_kon_isi06_c_tex[] = {
#include "assets/int_kon_isi06_c_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_isi06_d_tex[0x180];
#else
u8 int_kon_isi06_d_tex[] = {
#include "assets/int_kon_isi06_d_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_isi06_b_tex[0x100];
#else
u8 int_kon_isi06_b_tex[] = {
#include "assets/int_kon_isi06_b_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_isi06_v[0x350 / sizeof(Vtx)];
#else
Vtx int_kon_isi06_v[] = {
#include "assets/int_kon_isi06_v.inc"
};
#endif

Gfx int_kon_isi06_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_isi06_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_isi06_b_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_isi06_v, 27, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 6, 8, 7, 9, 10, 11, 9, 11, 12),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_kon_isi06_d_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 13, 14, 15, 15, 14, 16, 17, 18, 19),
    gsSPNTriangles_5b(17, 19, 20, 19, 21, 22, 19, 22, 20, 23, 24, 18),
    gsSPNTriangles_5b(23, 18, 17, 25, 26, 24, 25, 24, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_isi06_c_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_kon_isi06_v[27], 26, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(1, 0, 7, 7, 0, 4, 4, 0, 3, 4, 3, 5),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 48, int_kon_isi06_a_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(14, 8, 9, 10, 11, 12, 13, 14, 11, 13),
    gsSPNTriangles_5b(14, 13, 15, 16, 17, 18, 16, 18, 19, 18, 14, 15),
    gsSPNTriangles_5b(18, 15, 19, 20, 21, 22, 20, 22, 23, 22, 24, 25),
    gsSPNTriangles_5b(22, 25, 23, 21, 20, 8, 21, 8, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};
