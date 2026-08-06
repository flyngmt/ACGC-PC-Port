#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 mus_win_tagu_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 mus_win_tagu_tex[] = {
#include "assets/mus_win_tagu_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx mus_win2_v[0x40 / sizeof(Vtx)];
#else
Vtx mus_win2_v[] = {
#include "assets/mus_win2_v.inc"
};
#endif

Gfx mus_tag_nes_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 20, 20, 30, 255),
    gsDPSetEnvColor(145, 145, 145, 255),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, mus_win_tagu_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(mus_win2_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};
