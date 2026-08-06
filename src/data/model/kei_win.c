#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 kei_win_pin_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 kei_win_pin_pal[] = {
#include "assets/kei_win_pin_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 kei_win_pin_tex[0x200];
#else
u8 kei_win_pin_tex[] = {
#include "assets/kei_win_pin_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kei_win_w1_tex[0x1000];
#else
u8 kei_win_w1_tex[] = {
#include "assets/kei_win_w1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kei_win_w2_tex[0x800];
#else
u8 kei_win_w2_tex[] = {
#include "assets/kei_win_w2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kei_win_w3_tex[0x400];
#else
u8 kei_win_w3_tex[] = {
#include "assets/kei_win_w3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kei_win_kage2_tex[0x800];
#else
u8 kei_win_kage2_tex[] = {
#include "assets/kei_win_kage2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kei_win_kage3_tex[0x400];
#else
u8 kei_win_kage3_tex[] = {
#include "assets/kei_win_kage3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kei_win_kage4_tex[0x400];
#else
u8 kei_win_kage4_tex[] = {
#include "assets/kei_win_kage4_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx kei_win_v[0x3B0 / sizeof(Vtx)];
#else
Vtx kei_win_v[] = {
#include "assets/kei_win_v.inc"
};
#endif

Gfx kei_win_kamiT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, kei_win_kage4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(kei_win_v, 23, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 0, 4, 2, 1),
    gsSPNTriangles_5b(1, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, kei_win_kage3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 6, 7, 8, 8, 9, 6, 7, 6, 10),
    gsSPNTriangles_5b(6, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, kei_win_kage2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 12, 13, 14, 13, 15, 14, 16, 17, 18),
    gsSPNTriangles_5b(16, 19, 17, 20, 21, 18, 21, 16, 18, 17, 22, 13),
    gsSPNTriangles_5b(13, 12, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kei_win_pinT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
    gsDPSetRenderMode(G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, kei_win_pin_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, kei_win_pin_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kei_win_v[23], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kei_win_wakuT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 255, 225, 0, 255),
    gsDPSetEnvColor(115, 0, 0, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, kei_win_w3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kei_win_v[27], 24, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, kei_win_w2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 128, 32, kei_win_w1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(23, 20, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kei_win_mode[] = {
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

Gfx kei_win_model[] = {
    gsSPDisplayList(kei_win_mode),
    gsSPDisplayList(kei_win_wakuT_model),
    gsSPDisplayList(kei_win_kamiT_model),
    gsSPDisplayList(kei_win_pinT_model),
    gsSPEndDisplayList(),
};
