#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 ctl_win_tagu3_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 ctl_win_tagu3_tex[]= {
#include "assets/sav_sentaku/ctl_win_tagu3_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx sav_sentaku_v[0x40 / sizeof(Vtx)];
#else
Vtx sav_sentaku_v[] = {
#include "assets/sav_sentaku_v.inc"
};
#endif

Gfx sav_sentaku_taguT_model[] = {
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, ctl_win_tagu3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(sav_sentaku_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};


#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_sav_sentaku_c(void) {
    pc_load_asset("assets/sav_sentaku/ctl_win_tagu3_tex.bin", ctl_win_tagu3_tex, 0x200, 0x6CCF60, 0, 0);
}
#endif
