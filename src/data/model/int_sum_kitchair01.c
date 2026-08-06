#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_kitchair01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_kitchair01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_kitchair01_pal[] = {
#include "assets/int_sum_kitchair01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kitchair01_board_tex[0x180];
#else
u8 int_sum_kitchair01_board_tex[] = {
#include "assets/int_sum_kitchair01_board_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kitchair01_seat_tex[0x80];
#else
u8 int_sum_kitchair01_seat_tex[] = {
#include "assets/int_sum_kitchair01_seat_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kitchair01_seatside_tex[0x40];
#else
u8 int_sum_kitchair01_seatside_tex[] = {
#include "assets/int_sum_kitchair01_seatside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kitchair01_side_tex[0x40];
#else
u8 int_sum_kitchair01_side_tex[] = {
#include "assets/int_sum_kitchair01_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kitchair01_backf_tex[0x200];
#else
u8 int_sum_kitchair01_backf_tex[] = {
#include "assets/int_sum_kitchair01_backf_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kitchair01_frontf_tex[0x100];
#else
u8 int_sum_kitchair01_frontf_tex[] = {
#include "assets/int_sum_kitchair01_frontf_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kitchair01_support_tex[0x80];
#else
u8 int_sum_kitchair01_support_tex[] = {
#include "assets/int_sum_kitchair01_support_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_kitchair01_v[0x480 / sizeof(Vtx)];
#else
Vtx int_sum_kitchair01_v[] = {
#include "assets/int_sum_kitchair01_v.inc"
};
#endif

Gfx it_sum_kitchair01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_kitchair01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_kitchair01_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_kitchair01_v, 30, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 7, 6, 8, 7, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_kitchair01_seatside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 14, 15, 16, 14, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 20, 19, 22, 19, 23, 17, 24, 25),
    gsSPNTriangles_5b(17, 25, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_kitchair01_seat_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx it_sum_kitchair01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_kitchair01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_kitchair01_support_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_kitchair01_v[30], 22, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_kitchair01_frontf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 15, 16, 14, 17, 18, 19),
    gsSPNTriangles_5b(17, 20, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_kitchair01_backf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_kitchair01_v[52], 20, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 1, 0, 8, 1, 8, 9, 5, 4, 10),
    gsSPNTriangles_5b(5, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_kitchair01_board_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
