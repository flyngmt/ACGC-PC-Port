#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_uwa_vase01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_uwa_vase01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_uwa_vase01_pal[] = {
#include "assets/int_sum_uwa_vase01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_vase01_side[0x100];
#else
u8 int_sum_uwa_vase01_side[] = {
#include "assets/int_sum_uwa_vase01_side.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_vase01_red[0x80];
#else
u8 int_sum_uwa_vase01_red[] = {
#include "assets/int_sum_uwa_vase01_red.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_vase01_olange[0x80];
#else
u8 int_sum_uwa_vase01_olange[] = {
#include "assets/int_sum_uwa_vase01_olange.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_vase01_top[0x80];
#else
u8 int_sum_uwa_vase01_top[] = {
#include "assets/int_sum_uwa_vase01_top.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_vase01_kuki[0x100];
#else
u8 int_sum_uwa_vase01_kuki[] = {
#include "assets/int_sum_uwa_vase01_kuki.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_vase01_kukiside[0x80];
#else
u8 int_sum_uwa_vase01_kukiside[] = {
#include "assets/int_sum_uwa_vase01_kukiside.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_uwa_vase01_v[0x340 / sizeof(Vtx)];
#else
Vtx int_sum_uwa_vase01_v[] = {
#include "assets/int_sum_uwa_vase01_v.inc"
};
#endif

Gfx int_sum_uwa_vase01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_uwa_vase01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_uwa_vase01_top),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_uwa_vase01_v, 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_uwa_vase01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_uwa_vase01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_uwa_vase01_kukiside),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_uwa_vase01_v[5], 23, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_uwa_vase01_kuki),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 9, 10, 11, 12, 13, 14, 15, 16, 17),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_uwa_vase01_olange),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 18, 19, 20, 19, 21, 20, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_uwa_vase01_red),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_uwa_vase01_v[28], 24, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 4, 3, 2),
    gsSPNTriangles_5b(1, 4, 2, 5, 6, 7, 5, 8, 6, 5, 9, 8),
    gsSPNTriangles_5b(5, 7, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_uwa_vase01_side),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 10, 11, 12, 13, 14, 10, 15, 14, 16),
    gsSPNTriangles_5b(17, 11, 15, 18, 19, 17, 20, 18, 21, 22, 23, 20),
    gsSPNTriangles_5b(12, 19, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
