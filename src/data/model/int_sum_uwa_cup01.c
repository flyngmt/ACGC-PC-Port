#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_uwa_cup01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_uwa_cup01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_uwa_cup01_pal[] = {
#include "assets/int_sum_uwa_cup01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_cup01_side[0x100];
#else
u8 int_sum_uwa_cup01_side[] = {
#include "assets/int_sum_uwa_cup01_side.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_cup01_tote[0x100];
#else
u8 int_sum_uwa_cup01_tote[] = {
#include "assets/int_sum_uwa_cup01_tote.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_cup01_kuchi[0x80];
#else
u8 int_sum_uwa_cup01_kuchi[] = {
#include "assets/int_sum_uwa_cup01_kuchi.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_cup01_cup[0x80];
#else
u8 int_sum_uwa_cup01_cup[] = {
#include "assets/int_sum_uwa_cup01_cup.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_cup01_top[0x80];
#else
u8 int_sum_uwa_cup01_top[] = {
#include "assets/int_sum_uwa_cup01_top.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_cup01_cuptote[0x80];
#else
u8 int_sum_uwa_cup01_cuptote[] = {
#include "assets/int_sum_uwa_cup01_cuptote.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_uwa_cup01_base[0x100];
#else
u8 int_sum_uwa_cup01_base[] = {
#include "assets/int_sum_uwa_cup01_base.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_uwa_cup01_v[0x450 / sizeof(Vtx)];
#else
Vtx int_sum_uwa_cup01_v[] = {
#include "assets/int_sum_uwa_cup01_v.inc"
};
#endif

Gfx int_sum_uwa_cup01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_uwa_cup01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_uwa_cup01_base),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_uwa_cup01_v, 18, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 1, 6, 5, 1, 5, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_uwa_cup01_top),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 15, 16, 14, 16, 12, 14, 17, 11, 10),
    gsSPNTriangles_5b(9, 17, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_uwa_cup01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_uwa_cup01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_uwa_cup01_cuptote),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_uwa_cup01_v[18], 29, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_uwa_cup01_cup),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 6, 7, 8, 6, 9, 10, 11, 12, 13),
    gsSPNTriangles_5b(13, 8, 14, 15, 16, 17, 15, 18, 19, 20, 19, 21),
    gsSPNTriangles_5b(22, 23, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_uwa_cup01_kuchi),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(3, 24, 25, 26, 25, 27, 28, 28, 26, 25),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_uwa_cup01_tote),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_uwa_cup01_v[47], 22, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_uwa_cup01_side),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(12, 3, 4, 5, 6, 7, 8, 9, 8, 7),
    gsSPNTriangles_5b(10, 7, 11, 12, 11, 7, 13, 14, 15, 16, 15, 14),
    gsSPNTriangles_5b(17, 11, 15, 18, 15, 11, 19, 5, 14, 20, 14, 5),
    gsSPNTriangles_5b(21, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
