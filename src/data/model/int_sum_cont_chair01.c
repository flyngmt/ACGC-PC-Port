#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_cont_chair01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_cont_chair01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_cont_chair01_pal[] = {
#include "assets/int_sum_cont_chair01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_cont_chair01_board_tex[0x200];
#else
u8 int_sum_cont_chair01_board_tex[] = {
#include "assets/int_sum_cont_chair01_board_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_cont_chair01_seat_tex[0x100];
#else
u8 int_sum_cont_chair01_seat_tex[] = {
#include "assets/int_sum_cont_chair01_seat_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_cont_chair01_foot_tex[0x180];
#else
u8 int_sum_cont_chair01_foot_tex[] = {
#include "assets/int_sum_cont_chair01_foot_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_cont_chair01_seatside_tex[0x100];
#else
u8 int_sum_cont_chair01_seatside_tex[] = {
#include "assets/int_sum_cont_chair01_seatside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_cont_chair01_stand_tex[0x80];
#else
u8 int_sum_cont_chair01_stand_tex[] = {
#include "assets/int_sum_cont_chair01_stand_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_cont_chair01_v[0x420 / sizeof(Vtx)];
#else
Vtx int_sum_cont_chair01_v[] = {
#include "assets/int_sum_cont_chair01_v.inc"
};
#endif

Gfx int_sum_cont_chair01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_cont_chair01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_cont_chair01_seatside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_cont_chair01_v, 20, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 5, 0),
    gsSPNTriangles_5b(4, 0, 3, 6, 7, 5, 6, 5, 4, 8, 9, 7),
    gsSPNTriangles_5b(8, 7, 6, 10, 11, 9, 10, 9, 8, 2, 1, 12),
    gsSPNTriangles_5b(2, 12, 13, 13, 12, 14, 13, 14, 15, 15, 14, 16),
    gsSPNTriangles_5b(15, 16, 17, 17, 16, 18, 17, 18, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_cont_chair01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_cont_chair01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_sum_cont_chair01_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_cont_chair01_v[20], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_cont_chair01_foot_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_cont_chair01_v[36], 30, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 7, 10, 11, 12, 10, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(18, 19, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_cont_chair01_seat_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_cont_chair01_board_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 24, 25, 26, 27, 24, 28, 24, 29, 28),
    gsSPNTriangles_5b(24, 26, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
