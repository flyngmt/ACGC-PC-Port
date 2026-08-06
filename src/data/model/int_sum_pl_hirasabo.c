#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_pl_hirasabo_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_pl_hirasabo_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_pl_hirasabo_pal[] = {
#include "assets/int_sum_pl_hirasabo_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_hirasabo_earth_tex[0x80];
#else
u8 int_sum_pl_hirasabo_earth_tex[] = {
#include "assets/int_sum_pl_hirasabo_earth_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_hirasabo_hachi_tex[0x100];
#else
u8 int_sum_pl_hirasabo_hachi_tex[] = {
#include "assets/int_sum_pl_hirasabo_hachi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_hirasabo_sabo1_tex[0x200];
#else
u8 int_sum_pl_hirasabo_sabo1_tex[] = {
#include "assets/int_sum_pl_hirasabo_sabo1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_hirasabo_sabo2_tex[0x300];
#else
u8 int_sum_pl_hirasabo_sabo2_tex[] = {
#include "assets/int_sum_pl_hirasabo_sabo2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_hirasabo_sabo3_tex[0x100];
#else
u8 int_sum_pl_hirasabo_sabo3_tex[] = {
#include "assets/int_sum_pl_hirasabo_sabo3_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_pl_hirasabo_v[0x2F0 / sizeof(Vtx)];
#else
Vtx int_sum_pl_hirasabo_v[] = {
#include "assets/int_sum_pl_hirasabo_v.inc"
};
#endif

Gfx int_sum_pl_hirasabo_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_pl_hirasabo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_pl_hirasabo_earth_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_pl_hirasabo_v, 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 3, 0),
    gsSPNTriangles_5b(4, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_pl_hirasabo_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_pl_hirasabo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_pl_hirasabo_sabo3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_pl_hirasabo_v[6], 28, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 1, 0, 3, 3, 2, 1),
    gsSPNTriangles_5b(3, 0, 2, 4, 5, 6, 7, 4, 6, 6, 5, 7),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 8, 10, 11, 11, 9, 8),
    gsSPNTriangles_5b(9, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_pl_hirasabo_sabo2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 13, 12, 15, 15, 14, 13),
    gsSPNTriangles_5b(15, 12, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_pl_hirasabo_sabo1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12, 16, 17, 18, 19, 18, 17, 18, 19, 16),
    gsSPNTriangles_5b(17, 16, 19, 20, 21, 22, 23, 22, 21, 22, 23, 20),
    gsSPNTriangles_5b(21, 20, 23, 24, 25, 26, 25, 24, 27, 26, 27, 24),
    gsSPNTriangles_5b(27, 26, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_pl_hirasabo_hachi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_pl_hirasabo_v[34], 13, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(6, 8, 9, 10, 0, 11, 8, 10, 12, 0, 0, 0),
    gsSPEndDisplayList(),
};
