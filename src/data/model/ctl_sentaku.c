#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
static u8 ctl_win_tagu3_tex[0x200] ATTRIBUTE_ALIGN(32);
#else
static u8 ctl_win_tagu3_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/ctl_sentaku/ctl_win_tagu3_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx ctl_sentaku_v[0x40 / sizeof(Vtx)];
#else
Vtx ctl_sentaku_v[] = {
#include "assets/ctl_sentaku_v.inc"
};
#endif

Gfx ctl_sentaku_taguT_model[] = {
gsDPPipeSync(),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsSPDisplayList(anime_1_txt + 6 * sizeof(Gfx)),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, ctl_win_tagu3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(ctl_sentaku_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};


#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_ctl_sentaku_c(void) {
    pc_load_asset("assets/ctl_sentaku/ctl_win_tagu3_tex.bin", ctl_win_tagu3_tex, 0x200, 0x69DD60, 0, 0);
}
#endif
