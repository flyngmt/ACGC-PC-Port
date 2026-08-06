#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clg_win_star_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 clg_win_star_tex[]= {
#include "assets/clg_win_star_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx clg_hoshi_v[0x40 / sizeof(Vtx)];
#else
Vtx clg_hoshi_v[] = {
#include "assets/clg_hoshi_v.inc"
};
#endif

Gfx clg_win_hoshiT_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 255, 0, 215, 255),
gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clg_win_star_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(clg_hoshi_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

