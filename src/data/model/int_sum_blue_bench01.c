#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_blue_bench01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_blue_bench01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_blue_bench01_pal[] = {
#include "assets/int_sum_blue_bench01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_blue_bench01_back_tex[0x200];
#else
u8 int_sum_blue_bench01_back_tex[] = {
#include "assets/int_sum_blue_bench01_back_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_blue_bench01_seat_tex[0x300];
#else
u8 int_sum_blue_bench01_seat_tex[] = {
#include "assets/int_sum_blue_bench01_seat_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_blue_bench01_foot_tex[0x100];
#else
u8 int_sum_blue_bench01_foot_tex[] = {
#include "assets/int_sum_blue_bench01_foot_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_blue_bench01_v[0x2A0 / sizeof(Vtx)];
#else
Vtx int_sum_blue_bench01_v[] = {
#include "assets/int_sum_blue_bench01_v.inc"
};
#endif

Gfx int_sum_blue_bench01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_blue_bench01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_blue_bench01_seat_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_blue_bench01_v, 14, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 0, 4, 5),
    gsSPNTriangles_5b(0, 5, 1, 6, 7, 8, 6, 8, 9, 10, 11, 4),
    gsSPNTriangles_5b(10, 4, 0, 9, 8, 12, 9, 12, 13, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_blue_bench01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_blue_bench01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_blue_bench01_foot_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_blue_bench01_v[14], 28, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 7, 6, 1, 7, 1, 0, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 11, 10, 12, 11, 12, 13, 14, 15, 9),
    gsSPNTriangles_5b(14, 9, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_blue_bench01_back_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 0, 0, 0),
    gsSPEndDisplayList(),
};
