#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_hal_sofa01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_hal_sofa01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_hal_sofa01_pal[] = {
#include "assets/int_sum_hal_sofa01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_sofa01_seat_tex[0x300];
#else
u8 int_sum_hal_sofa01_seat_tex[] = {
#include "assets/int_sum_hal_sofa01_seat_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_sofa01_arm_tex[0x100];
#else
u8 int_sum_hal_sofa01_arm_tex[] = {
#include "assets/int_sum_hal_sofa01_arm_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_sofa01_side_tex[0x100];
#else
u8 int_sum_hal_sofa01_side_tex[] = {
#include "assets/int_sum_hal_sofa01_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_sofa01_head_tex[0x200];
#else
u8 int_sum_hal_sofa01_head_tex[] = {
#include "assets/int_sum_hal_sofa01_head_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_sofa01_top_tex[0x80];
#else
u8 int_sum_hal_sofa01_top_tex[] = {
#include "assets/int_sum_hal_sofa01_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_hal_sofa01_kuki_tex[0x80];
#else
u8 int_sum_hal_sofa01_kuki_tex[] = {
#include "assets/int_sum_hal_sofa01_kuki_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_hal_sofa01_v[0x410 / sizeof(Vtx)];
#else
Vtx int_sum_hal_sofa01_v[] = {
#include "assets/int_sum_hal_sofa01_v.inc"
};
#endif

Gfx int_sum_hal_sofa01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hal_sofa01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_sofa01_kuki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_hal_sofa01_v, 15, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 1, 5, 6, 4),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_hal_sofa01_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 7, 8, 9, 10, 11, 12, 10, 12, 13),
    gsSPNTriangles_5b(9, 14, 11, 9, 11, 10, 8, 14, 9, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_hal_sofa01_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_hal_sofa01_v[15], 24, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 6, 3, 5),
    gsSPNTriangles_5b(7, 8, 9, 10, 7, 9, 11, 12, 13, 14, 11, 13),
    gsSPNTriangles_5b(15, 16, 17, 15, 17, 18, 19, 20, 21, 19, 21, 22),
    gsSPNTriangles_5b(21, 15, 18, 21, 18, 22, 0, 6, 5, 0, 5, 23),
    gsSPNTriangles_5b(0, 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_hal_sofa01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_hal_sofa01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_hal_sofa01_head_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_hal_sofa01_v[39], 26, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_hal_sofa01_arm_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 7, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_hal_sofa01_seat_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(9, 16, 17, 18, 16, 19, 20, 19, 21, 20),
    gsSPNTriangles_5b(21, 17, 20, 17, 16, 20, 17, 22, 18, 19, 23, 24),
    gsSPNTriangles_5b(19, 24, 21, 25, 16, 18, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
