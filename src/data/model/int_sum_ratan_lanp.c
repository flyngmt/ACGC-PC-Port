#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_ratan_lanp_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_ratan_lanp_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_ratan_lanp_pal[] = {
#include "assets/int_sum_ratan_lanp_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_ratan_lanp_kasa_tax[0x100];
#else
u8 int_sum_ratan_lanp_kasa_tax[] = {
#include "assets/int_sum_ratan_lanp_kasa_tax.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_ratan_lanp_stand_tax[0x100];
#else
u8 int_sum_ratan_lanp_stand_tax[] = {
#include "assets/int_sum_ratan_lanp_stand_tax.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_ratan_lanp_base_tax[0x100];
#else
u8 int_sum_ratan_lanp_base_tax[] = {
#include "assets/int_sum_ratan_lanp_base_tax.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_ratan_lanp_basetop_tax[0x80];
#else
u8 int_sum_ratan_lanp_basetop_tax[] = {
#include "assets/int_sum_ratan_lanp_basetop_tax.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_ratan_lanp_hiki_tax[0x80];
#else
u8 int_sum_ratan_lanp_hiki_tax[] = {
#include "assets/int_sum_ratan_lanp_hiki_tax.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_ratan_lanp_v[0x280 / sizeof(Vtx)];
#else
Vtx int_sum_ratan_lanp_v[] = {
#include "assets/int_sum_ratan_lanp_v.inc"
};
#endif

Gfx int_sum_ratan_lanp_off_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_ratan_lanp_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_ratan_lanp_kasa_tax),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_ratan_lanp_v, 21, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 3, 0, 2, 4, 5, 3),
    gsSPNTriangles_5b(2, 4, 3, 3, 5, 6, 3, 6, 7, 7, 8, 0),
    gsSPNTriangles_5b(7, 0, 3, 9, 10, 11, 12, 9, 11, 13, 14, 12),
    gsSPNTriangles_5b(11, 13, 12, 7, 6, 13, 7, 13, 11, 11, 10, 8),
    gsSPNTriangles_5b(11, 8, 7, 15, 16, 9, 15, 9, 12, 12, 14, 17),
    gsSPNTriangles_5b(12, 17, 15, 15, 17, 18, 15, 18, 19, 19, 20, 16),
    gsSPNTriangles_5b(19, 16, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_ratan_lanp_offT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_ratan_lanp_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_ratan_lanp_hiki_tax),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_ratan_lanp_v[21], 19, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_ratan_lanp_basetop_tax),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 5, 6, 7, 5, 7, 8, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_ratan_lanp_base_tax),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 9, 10, 11, 12, 13, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_ratan_lanp_stand_tax),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 14, 15, 16, 14, 17, 18, 0, 0, 0),
    gsSPEndDisplayList(),
};
