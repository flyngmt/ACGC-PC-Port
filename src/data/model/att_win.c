#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 att_win_waku1_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 att_win_waku1_tex[] = {
#include "assets/att_win_waku1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 att_win_waku2_tex[0x400];
#else
u8 att_win_waku2_tex[] = {
#include "assets/att_win_waku2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 att_win_waku3_tex[0x400];
#else
u8 att_win_waku3_tex[] = {
#include "assets/att_win_waku3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 att_win_waku4_tex[0x400];
#else
u8 att_win_waku4_tex[] = {
#include "assets/att_win_waku4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 att_win_waku5_tex[0x400];
#else
u8 att_win_waku5_tex[] = {
#include "assets/att_win_waku5_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 att_win_waku6_tex[0x80];
#else
u8 att_win_waku6_tex[] = {
#include "assets/att_win_waku6_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx att_win_v[0x2F0 / sizeof(Vtx)];
#else
Vtx att_win_v[] = {
#include "assets/att_win_v.inc"
};
#endif

Gfx att_win_cursor_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, PRIMITIVE, 0, 0, 0, 0),
    gsDPSetPrimColor(0, 255, 255, 0, 0, 255),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsSPVertex(att_win_v, 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx att_win_winT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 0, 0, 255, 255),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, att_win_waku6_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&att_win_v[3], 28, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, att_win_waku5_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 7, 4, 6, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, att_win_waku4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 15, 12, 14, 16, 17, 18),
    gsSPNTriangles_5b(17, 19, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, att_win_waku3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 23, 20, 22, 24, 25, 26),
    gsSPNTriangles_5b(25, 27, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, att_win_waku2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&att_win_v[31], 16, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, att_win_waku1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx att_win_mode[] = {
    gsDPPipeSync(),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_TEX_EDGE2),
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

Gfx att_win_model[] = {
    gsSPDisplayList(att_win_mode),
    gsSPDisplayList(att_win_winT_model),
    gsSPEndDisplayList(),
};
