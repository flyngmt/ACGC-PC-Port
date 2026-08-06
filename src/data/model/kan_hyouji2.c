#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kan_win_yane_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 kan_win_yane_tex[] = {
#include "assets/kan_win_yane_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kan_win_yashiro_tex[0x80];
#else
u8 kan_win_yashiro_tex[] = {
#include "assets/kan_win_yashiro_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kan_win_yubin_tex[0x80];
#else
u8 kan_win_yubin_tex[] = {
#include "assets/kan_win_yubin_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kan_win_kouban_tex[0x80];
#else
u8 kan_win_kouban_tex[] = {
#include "assets/kan_win_kouban_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kan_win_omise_tex[0x80];
#else
u8 kan_win_omise_tex[] = {
#include "assets/kan_win_omise_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kan_win_play_tex[0x100];
#else
u8 kan_win_play_tex[] = {
#include "assets/kan_win_play_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kan_win_ply_tex[0x100];
#else
u8 kan_win_ply_tex[] = {
#include "assets/kan_win_ply_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx kan_hyouji2_v[0x240 / sizeof(Vtx)];
#else
Vtx kan_hyouji2_v[] = {
#include "assets/kan_hyouji2_v.inc"
};
#endif

Gfx kan_win_genzaiT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 80, 50, 50, 255),
    gsDPSetEnvColor(255, 70, 30, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_play_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(kan_hyouji2_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kan_win_npc2T_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_yane_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kan_hyouji2_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kan_win_npc2T_1_model[] = {
    gsDPSetPrimColor(0, 255, 90, 90, 225, 255),
    gsDPSetEnvColor(225, 225, 225, 255),
    gsSPDisplayList(kan_win_npc2T_base_model),
    gsSPEndDisplayList(),
};

Gfx kan_win_npc2T_2_model[] = {
    gsDPSetPrimColor(0, 255, 145, 70, 205, 255),
    gsDPSetEnvColor(225, 225, 225, 255),
    gsSPDisplayList(kan_win_npc2T_base_model),
    gsSPEndDisplayList(),
};

Gfx kan_win_npc2T_3_model[] = {
    gsDPSetPrimColor(0, 255, 170, 115, 20, 255),
    gsDPSetEnvColor(225, 225, 225, 255),
    gsSPDisplayList(kan_win_npc2T_base_model),
    gsSPEndDisplayList(),
};

Gfx kan_win_npcT_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_yane_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kan_hyouji2_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kan_win_npcT_1_model[] = {
    gsDPSetPrimColor(0, 255, 110, 110, 185, 255),
    gsDPSetEnvColor(225, 225, 225, 255),
    gsSPDisplayList(kan_win_npcT_base_model),
    gsSPEndDisplayList(),
};

Gfx kan_win_npcT_2_model[] = {
    gsDPSetPrimColor(0, 255, 145, 70, 205, 255),
    gsDPSetEnvColor(225, 225, 225, 255),
    gsSPDisplayList(kan_win_npcT_base_model),
    gsSPEndDisplayList(),
};

Gfx kan_win_npcT_3_model[] = {
    gsDPSetPrimColor(0, 255, 170, 115, 20, 255),
    gsDPSetEnvColor(225, 225, 225, 255),
    gsSPDisplayList(kan_win_npcT_base_model),
    gsSPEndDisplayList(),
};

Gfx kan_win_koubanT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 195, 80, 45, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, kan_win_kouban_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kan_hyouji2_v[16], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kan_win_yashiroT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 190, 70, 60, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, kan_win_yashiro_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&kan_hyouji2_v[20], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kan_win_omiseT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 195, 80, 45, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, kan_win_omise_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kan_hyouji2_v[24], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kan_win_yuuT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 190, 70, 60, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, kan_win_yubin_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kan_hyouji2_v[28], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kan_win_playerT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 110, 120, 165, 255),
    gsDPSetEnvColor(235, 235, 80, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_ply_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kan_hyouji2_v[32], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};
