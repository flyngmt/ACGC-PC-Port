#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx mny_win_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 mny_win_money_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 mny_win_money_tex[] = {
#include "assets/mny_win_money_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 fri_win_bell_tex[0x100];
#else
static u8 fri_win_bell_tex[] = {
#include "assets/mny_win/fri_win_bell_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 mny_win_u_tex[0x800];
#else
u8 mny_win_u_tex[] = {
#include "assets/mny_win_u_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx mny_win_v[0x100 / sizeof(Vtx)];
#else
Vtx mny_win_v[] = {
#include "assets/mny_win_v.inc"
};
#endif

Gfx mny_win_beruT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, fri_win_bell_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(mny_win_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx mny_win_mojiT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, mny_win_money_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&mny_win_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx mny_win_ueT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 64, mny_win_u_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&mny_win_v[8], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_mny_win_c(void) {
    pc_load_asset("assets/mny_win/fri_win_bell_tex.bin", fri_win_bell_tex, 0x100, 0xB73BE0, 0, 0);
}
#endif
