#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kan_win_mu_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 kan_win_mu_tex[] = {
#include "assets/kan_win_mu_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kan_win_ta_tex[0x80];
#else
u8 kan_win_ta_tex[] = {
#include "assets/kan_win_ta_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx kan_hyouji_v[0x80 / sizeof(Vtx)];
#else
static Vtx kan_hyouji_v[] = {
#include "assets/kan_hyouji3/kan_hyouji_v.inc"
};
#endif

Gfx kan_win_mu_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 190, 70, 60, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, kan_win_mu_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(kan_hyouji_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kan_win_ta_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 190, 70, 60, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, kan_win_ta_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kan_hyouji_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_kan_hyouji3_c(void) {
    pc_load_asset("assets/kan_hyouji3/kan_hyouji_v.bin", kan_hyouji_v, 0x80, 0x78C540, 0, 2);
}
#endif
