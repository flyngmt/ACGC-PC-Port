#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 agb_win_yajirushi_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 agb_win_yajirushi_tex[] = {
#include "assets/agb_win_yajirushi_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx agb_yajirushi_v[0x40 / sizeof(Vtx)];
#else
Vtx agb_yajirushi_v[] = {
#include "assets/agb_yajirushi_v.inc"
};
#endif

Gfx agb_win_yajirushiT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 60, 50, 50, 255),
    gsDPSetEnvColor(255, 30, 30, 255),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, agb_win_yajirushi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(agb_yajirushi_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};
