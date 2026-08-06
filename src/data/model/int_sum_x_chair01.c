#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_x_chair01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_x_chair01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_x_chair01_pal[] = {
#include "assets/int_sum_x_chair01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_chair01_seat[0x100];
#else
u8 int_sum_x_chair01_seat[] = {
#include "assets/int_sum_x_chair01_seat.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_chair01_side[0x100];
#else
u8 int_sum_x_chair01_side[] = {
#include "assets/int_sum_x_chair01_side.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_chair01_leg[0x100];
#else
u8 int_sum_x_chair01_leg[] = {
#include "assets/int_sum_x_chair01_leg.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_chair01_head[0x80];
#else
u8 int_sum_x_chair01_head[] = {
#include "assets/int_sum_x_chair01_head.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_chair01_base[0x180];
#else
u8 int_sum_x_chair01_base[] = {
#include "assets/int_sum_x_chair01_base.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_chair01_back[0x300];
#else
u8 int_sum_x_chair01_back[] = {
#include "assets/int_sum_x_chair01_back.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_x_chair01_v[0x410 / sizeof(Vtx)];
#else
Vtx int_sum_x_chair01_v[] = {
#include "assets/int_sum_x_chair01_v.inc"
};
#endif

Gfx int_sum_x_chair01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_x_chair01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_x_chair01_side),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_x_chair01_v, 25, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 1, 3, 2, 4, 1, 5),
    gsSPNTriangles_5b(4, 6, 1, 7, 8, 9, 8, 10, 9, 11, 8, 7),
    gsSPNTriangles_5b(11, 12, 8, 13, 14, 15, 14, 16, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_x_chair01_seat),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7, 17, 18, 19, 18, 20, 19, 20, 21, 19),
    gsSPNTriangles_5b(21, 17, 19, 22, 23, 21, 23, 17, 21, 23, 24, 17),
    gsSPEndDisplayList(),
};

Gfx int_sum_x_chair01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_x_chair01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_x_chair01_back),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_x_chair01_v[25], 16, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_x_chair01_base),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 6, 7, 8, 9, 10, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_x_chair01_head),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 11, 12, 13, 11, 14, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_x_chair01_leg),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_x_chair01_v[41], 24, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
