#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 mus_win_mark_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 mus_win_mark_tex[] = {
#include "assets/mus_win_mark_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx mus_mark_v[0x40 / sizeof(Vtx)];
#else
Vtx mus_mark_v[] = {
#include "assets/mus_mark_v.inc"
};
#endif

Gfx mus_mark_before[] = {
    gsDPPipeSync(),
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, mus_win_mark_tex),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 127, 1024),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 2, 0, G_TX_RENDERTILE, 0, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
    gsSPEndDisplayList(),
};

Gfx mus_mark_model[] = {
    gsSPVertex(mus_mark_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};
