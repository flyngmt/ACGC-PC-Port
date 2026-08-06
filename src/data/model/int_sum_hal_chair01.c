#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_hal_chair01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_hal_chair01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_hal_chair01_pal[] = {
#include "assets/int_sum_hal_chair01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_chair01_seat_tex[0x200];
#else
u8 int_sum_hal_chair01_seat_tex[] = {
#include "assets/int_sum_hal_chair01_seat_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_chair01_back_tex[0x200];
#else
u8 int_sum_hal_chair01_back_tex[] = {
#include "assets/int_sum_hal_chair01_back_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_chair01_side_tex[0x100];
#else
u8 int_sum_hal_chair01_side_tex[] = {
#include "assets/int_sum_hal_chair01_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_chair01_top_tex[0x80];
#else
u8 int_sum_hal_chair01_top_tex[] = {
#include "assets/int_sum_hal_chair01_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_chair01_kuki_tex[0x80];
#else
u8 int_sum_hal_chair01_kuki_tex[] = {
#include "assets/int_sum_hal_chair01_kuki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_chair01_armside_tex[0x200];
#else
u8 int_sum_hal_chair01_armside_tex[] = {
#include "assets/int_sum_hal_chair01_armside_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_hal_chair01_v[0x470 / sizeof(Vtx)];
#else
Vtx int_sum_hal_chair01_v[] = {
#include "assets/int_sum_hal_chair01_v.inc"
};
#endif

Gfx int_sum_hal_chair01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hal_chair01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_chair01_kuki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_hal_chair01_v, 24, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 4, 3, 5, 6),
    gsSPNTriangles_5b(3, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_chair01_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 8, 9, 10, 8, 10, 11, 12, 13, 9),
    gsSPNTriangles_5b(12, 9, 8, 11, 10, 14, 11, 14, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_hal_chair01_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_hal_chair01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hal_chair01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_hal_chair01_armside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hal_chair01_v[24], 18, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 6, 7, 8, 9, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_hal_chair01_back_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hal_chair01_v[42], 29, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 6, 7, 8, 6, 8, 9, 8, 10, 11),
    gsSPNTriangles_5b(8, 11, 9, 15, 10, 16, 15, 16, 12, 17, 18, 7),
    gsSPNTriangles_5b(17, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_hal_chair01_seat_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 19, 20, 21, 20, 22, 21, 22, 23, 21),
    gsSPNTriangles_5b(24, 25, 26, 25, 27, 26, 27, 28, 26, 0, 0, 0),
    gsSPEndDisplayList(),
};
