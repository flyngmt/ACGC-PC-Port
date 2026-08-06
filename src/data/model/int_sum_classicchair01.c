#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_classicchair01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_classicchair01_pal01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_classicchair01_pal01_pal[] = {
#include "assets/int_sum_classicchair01_pal01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicchair01_seat[0x100];
#else
u8 int_sum_classicchair01_seat[] = {
#include "assets/int_sum_classicchair01_seat.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicchair01_back[0x200];
#else
u8 int_sum_classicchair01_back[] = {
#include "assets/int_sum_classicchair01_back.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicchair01_side[0x80];
#else
u8 int_sum_classicchair01_side[] = {
#include "assets/int_sum_classicchair01_side.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicchair01_foot[0x100];
#else
u8 int_sum_classicchair01_foot[] = {
#include "assets/int_sum_classicchair01_foot.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicchair01_frontseat[0x40];
#else
u8 int_sum_classicchair01_frontseat[] = {
#include "assets/int_sum_classicchair01_frontseat.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicchair01_backfoot[0x100];
#else
u8 int_sum_classicchair01_backfoot[] = {
#include "assets/int_sum_classicchair01_backfoot.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicchairspindle[0x40];
#else
u8 int_sum_classicchairspindle[] = {
#include "assets/int_sum_classicchairspindle.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicchair01_backseat[0x40];
#else
u8 int_sum_classicchair01_backseat[] = {
#include "assets/int_sum_classicchair01_backseat.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_classicchair01_v[0x430 / sizeof(Vtx)];
#else
Vtx int_sum_classicchair01_v[] = {
#include "assets/int_sum_classicchair01_v.inc"
};
#endif

Gfx int_sum_classicchair01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_classicchair01_pal01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_classicchair01_backseat),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_classicchair01_v, 24, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_classicchairspindle),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 4, 5, 6, 4, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(8, 11, 9, 12, 13, 14, 13, 15, 14, 16, 17, 18),
    gsSPNTriangles_5b(17, 19, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_classicchair01_frontseat),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 21, 23, 22, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_sum_classicchair01_side),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_classicchair01_v[24], 12, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_classicchair01_seat),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 9, 11, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_classicchair01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_classicchair01_pal01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 8, int_sum_classicchair01_backfoot),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_classicchair01_v[36], 31, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_classicchair01_foot),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(9, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 16, 13, 16, 14, 17, 18, 19, 17, 20, 18),
    gsSPNTriangles_5b(21, 22, 23, 22, 24, 23, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_classicchair01_back),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 25, 26, 27, 26, 28, 27, 26, 29, 28),
    gsSPNTriangles_5b(26, 30, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
