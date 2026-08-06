#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_x_sofa01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_x_sofa01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_x_sofa01_pal[] = {
#include "assets/int_sum_x_sofa01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_sofa01_head[0x80];
#else
u8 int_sum_x_sofa01_head[] = {
#include "assets/int_sum_x_sofa01_head.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_sofa01_seat[0x300];
#else
u8 int_sum_x_sofa01_seat[] = {
#include "assets/int_sum_x_sofa01_seat.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_sofa01_leg[0x80];
#else
u8 int_sum_x_sofa01_leg[] = {
#include "assets/int_sum_x_sofa01_leg.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_sofa01_back[0x200];
#else
u8 int_sum_x_sofa01_back[] = {
#include "assets/int_sum_x_sofa01_back.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_sofa01_arm[0x100];
#else
u8 int_sum_x_sofa01_arm[] = {
#include "assets/int_sum_x_sofa01_arm.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_sofa01_side[0x100];
#else
u8 int_sum_x_sofa01_side[] = {
#include "assets/int_sum_x_sofa01_side.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_x_sofa01_v[0x4A0 / sizeof(Vtx)];
#else
Vtx int_sum_x_sofa01_v[] = {
#include "assets/int_sum_x_sofa01_v.inc"
};
#endif

Gfx int_sum_x_sofa01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_x_sofa01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_x_sofa01_side),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_x_sofa01_v, 22, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 3, 1, 4, 5, 0),
    gsSPNTriangles_5b(4, 6, 5, 6, 7, 5, 8, 9, 10, 8, 11, 9),
    gsSPNTriangles_5b(12, 8, 10, 13, 14, 12, 14, 15, 12, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_x_sofa01_arm),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 19, 20, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_x_sofa01_back),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_x_sofa01_v[22], 23, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 2, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(6, 8, 7, 5, 9, 6, 7, 10, 11, 7, 8, 10),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_x_sofa01_seat),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 12, 13, 14, 12, 15, 13, 12, 16, 15),
    gsSPNTriangles_5b(17, 18, 19, 18, 14, 19, 14, 13, 19, 13, 17, 19),
    gsSPNTriangles_5b(17, 20, 18, 20, 21, 18, 17, 22, 20, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_x_sofa01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_x_sofa01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_x_sofa01_leg),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_x_sofa01_v[45], 29, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_x_sofa01_head),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 27, 28, 0, 0, 0),
    gsSPEndDisplayList(),
};
