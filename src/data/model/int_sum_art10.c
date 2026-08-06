#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_art10_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_art10_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_art10_pal[] = {
#include "assets/int_sum_art10_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_art10_gaku_tex[0x100];
#else
u8 int_sum_art10_gaku_tex[] = {
#include "assets/int_sum_art10_gaku_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_art10_rautrec_tex[0x300];
#else
u8 int_sum_art10_rautrec_tex[] = {
#include "assets/int_sum_art10_rautrec_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_art10_stand_tex[0x200];
#else
u8 int_sum_art10_stand_tex[] = {
#include "assets/int_sum_art10_stand_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_art10_front_tex[0x200];
#else
u8 int_sum_art10_front_tex[] = {
#include "assets/int_sum_art10_front_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_art10_v[0x340 / sizeof(Vtx)];
#else
Vtx int_sum_art10_v[] = {
#include "assets/int_sum_art10_v.inc"
};
#endif

Gfx int_sum_art10_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_art10_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_art10_rautrec_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_art10_v, 24, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_art10_gaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 4, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(8, 11, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 15, 13, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 19, 17, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_art10_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_art10_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_art10_front_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_art10_v[24], 28, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_art10_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 6, 7, 8, 6, 9, 7, 10, 11, 12),
    gsSPNTriangles_5b(10, 13, 11, 18, 16, 19, 18, 14, 16, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 24, 25, 26, 24, 27, 25, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 14, 15, 16, 14, 17, 15, 0, 0, 0),
    gsSPEndDisplayList(),
};
