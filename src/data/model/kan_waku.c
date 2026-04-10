#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
u8 kan_win_waku4_tex[0x1000] ATTRIBUTE_ALIGN(32);
#else
u8 kan_win_waku4_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/kan_win_waku4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kan_win_waku3_tex[0x1000];
#else
u8 kan_win_waku3_tex[] = {
#include "assets/kan_win_waku3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kan_win_waku5_tex[0x1000];
#else
u8 kan_win_waku5_tex[] = {
#include "assets/kan_win_waku5_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kan_win_waku1a_tex[0x1000];
#else
u8 kan_win_waku1a_tex[] = {
#include "assets/kan_win_waku1a_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kan_win_waku1b_tex[0x1000];
#else
u8 kan_win_waku1b_tex[] = {
#include "assets/kan_win_waku1b_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx kan_waku_v[0x140 / sizeof(Vtx)];
#else
Vtx kan_waku_v[] = {
#include "assets/kan_waku_v.inc"
};
#endif

Gfx kan_waku_w1T_model[] = {
    gsSPDisplayList(anime_4_txt + 11 * sizeof(Gfx)),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, kan_win_waku1b_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(kan_waku_v, 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, kan_win_waku1a_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kan_waku_w2T_model[] = {
    gsSPDisplayList(anime_4_txt + 11 * sizeof(Gfx)),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, kan_win_waku3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kan_waku_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kan_waku_w3T_model[] = {
    gsSPDisplayList(anime_4_txt + 11 * sizeof(Gfx)),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, kan_win_waku4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kan_waku_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kan_waku_w4T_model[] = {
    gsSPDisplayList(anime_4_txt + 11 * sizeof(Gfx)),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, kan_win_waku5_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kan_waku_v[16], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};
