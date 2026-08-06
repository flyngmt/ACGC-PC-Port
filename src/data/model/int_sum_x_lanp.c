#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_x_lanp_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_x_lanp_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_x_lanp_pal[] = {
#include "assets/int_sum_x_lanp_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_lanp_base[0x400];
#else
u8 int_sum_x_lanp_base[] = {
#include "assets/int_sum_x_lanp_base.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_lanp_head[0x80];
#else
u8 int_sum_x_lanp_head[] = {
#include "assets/int_sum_x_lanp_head.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_lanp_top[0x100];
#else
u8 int_sum_x_lanp_top[] = {
#include "assets/int_sum_x_lanp_top.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_lanp_shade[0x100];
#else
u8 int_sum_x_lanp_shade[] = {
#include "assets/int_sum_x_lanp_shade.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_lanp_stand[0x100];
#else
u8 int_sum_x_lanp_stand[] = {
#include "assets/int_sum_x_lanp_stand.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_lanp_hiki[0x80];
#else
u8 int_sum_x_lanp_hiki[] = {
#include "assets/int_sum_x_lanp_hiki.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_x_lanp_v[0x3B0 / sizeof(Vtx)];
#else
Vtx int_sum_x_lanp_v[] = {
#include "assets/int_sum_x_lanp_v.inc"
};
#endif

Gfx int_sum_x_lanp_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_x_lanp_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_x_lanp_top),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_x_lanp_v, 22, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_sum_x_lanp_base),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 4, 5, 6, 7, 8, 9, 7, 10, 8),
    gsSPNTriangles_5b(11, 12, 13, 11, 14, 12, 12, 15, 13, 16, 17, 18),
    gsSPNTriangles_5b(17, 19, 18, 20, 4, 6, 20, 21, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_x_lanp_offT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_x_lanp_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_x_lanp_hiki),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_x_lanp_v[22], 28, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_x_lanp_stand),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 3, 4, 5, 3, 6, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_x_lanp_shade),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(18, 8, 9, 10, 10, 9, 11, 12, 13, 10),
    gsSPNTriangles_5b(13, 14, 10, 12, 10, 15, 16, 17, 18, 16, 19, 17),
    gsSPNTriangles_5b(19, 20, 17, 17, 12, 21, 20, 13, 17, 13, 12, 17),
    gsSPNTriangles_5b(22, 19, 23, 19, 16, 23, 23, 16, 24, 25, 26, 23),
    gsSPNTriangles_5b(26, 22, 23, 25, 23, 27, 14, 8, 10, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_x_lanp_top),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_sum_x_lanp_v[50], 9, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_x_lanp_head),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 7, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};
