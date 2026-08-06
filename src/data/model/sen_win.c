#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 sen_win_wa1_tex[0x1000];
#else
ATTRIBUTE_ALIGN(32) u8 sen_win_wa1_tex[] = {
#include "assets/sen_win_wa1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 sen_win_wa2_tex[0x1000];
#else
u8 sen_win_wa2_tex[] = {
#include "assets/sen_win_wa2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 sen_win_waku1_tex[0x1000];
#else
u8 sen_win_waku1_tex[] = {
#include "assets/sen_win_waku1_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 sen_win_yaji2_tex[0x100];
#else
static u8 sen_win_yaji2_tex[] = {
#include "assets/sen_win/sen_win_yaji2_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 sen_item2_yaji_tex[0x80];
#else
static u8 sen_item2_yaji_tex[] = {
#include "assets/sen_win/sen_item2_yaji_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx sen_win_v[0x220 / sizeof(Vtx)];
#else
Vtx sen_win_v[] = {
#include "assets/sen_win_v.inc"
};
#endif

Gfx sen_win_cursor_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsSPVertex(sen_win_v, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx sen_win_kageT_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
    gsDPSetPrimColor(0, 255, 20, 20, 30, 160),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 128, sen_win_waku1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_win_v[3], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsSP2Triangles(4, 5, 6, 0, 6, 7, 4, 0),
    gsSPEndDisplayList(),
};

Gfx sen_win_wakuT_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, sen_win_wa2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_win_v[11], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSP2Triangles(4, 5, 6, 0, 7, 4, 6, 0),
    gsDPPipeSync(),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, sen_win_wa1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_win_v[19], 7, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSP2Triangles(4, 3, 5, 0, 6, 4, 5, 0),
    gsSPEndDisplayList(),
};

Gfx sen_win_yajirushiT_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, sen_item2_yaji_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_win_v[26], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx sen_win_yajirushi2T_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetEnvColor(20, 20, 30, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, sen_win_yaji2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_win_v[30], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_sen_win_c(void) {
    pc_load_asset("assets/sen_win/sen_win_yaji2_tex.bin", sen_win_yaji2_tex, 0x100, 0x7BE160, 0, 0);
    pc_load_asset("assets/sen_win/sen_item2_yaji_tex.bin", sen_item2_yaji_tex, 0x80, 0x7BE260, 0, 0);
}
#endif
