#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_bon_ume_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_bon_ume_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_bon_ume_pal[] = {
#include "assets/int_sum_bon_ume_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_ume_hachi_tex[0x100];
#else
u8 int_sum_bon_ume_hachi_tex[] = {
#include "assets/int_sum_bon_ume_hachi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_ume_stand_tex[0x200];
#else
u8 int_sum_bon_ume_stand_tex[] = {
#include "assets/int_sum_bon_ume_stand_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_ume_standside_tex[0x100];
#else
u8 int_sum_bon_ume_standside_tex[] = {
#include "assets/int_sum_bon_ume_standside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_ume_hana_tex[0x200];
#else
u8 int_sum_bon_ume_hana_tex[] = {
#include "assets/int_sum_bon_ume_hana_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_ume_tubomi_tex[0x100];
#else
u8 int_sum_bon_ume_tubomi_tex[] = {
#include "assets/int_sum_bon_ume_tubomi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bon_ume_earth_tex[0x80];
#else
u8 int_sum_bon_ume_earth_tex[] = {
#include "assets/int_sum_bon_ume_earth_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_bon_ume_v[0x420 / sizeof(Vtx)];
#else
Vtx int_sum_bon_ume_v[] = {
#include "assets/int_sum_bon_ume_v.inc"
};
#endif

Gfx int_sum_bon_ume_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bon_ume_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_bon_ume_earth_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_bon_ume_v, 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_bon_ume_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bon_ume_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_bon_ume_tubomi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_bon_ume_v[5], 15, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(5, 8, 9, 10, 11, 12, 10, 13, 14, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_bon_ume_hana_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_bon_ume_v[20], 31, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 6, 7, 8, 9, 6, 8, 10, 9, 8),
    gsSPNTriangles_5b(11, 10, 8, 7, 11, 8, 12, 13, 14, 12, 15, 13),
    gsSPNTriangles_5b(12, 16, 15, 12, 17, 16, 12, 14, 17, 0, 5, 1),
    gsSPNTriangles_5b(18, 19, 20, 19, 21, 20, 21, 22, 20, 22, 23, 20),
    gsSPNTriangles_5b(23, 18, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_bon_ume_standside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 30, 26, 25, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 27, 28, 29, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_bon_ume_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_bon_ume_v[51], 15, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_bon_ume_hachi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 6, 7, 8, 9, 10, 11, 10, 6, 12),
    gsSPNTriangles_5b(7, 13, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
