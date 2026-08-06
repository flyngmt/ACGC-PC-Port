#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 onp_win_shiro_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 onp_win_shiro_tex[] = {
#include "assets/onp_win_shiro_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_ok_tex[0x100];
#else
u8 onp_win_ok_tex[] = {
#include "assets/onp_win_ok_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_ga_tex[0x100];
#else
u8 onp_win_ga_tex[] = {
#include "assets/onp_win_ga_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_ga4_tex[0x100];
#else
u8 onp_win_ga4_tex[] = {
#include "assets/onp_win_ga4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_ga3_tex[0x100];
#else
u8 onp_win_ga3_tex[] = {
#include "assets/onp_win_ga3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_ga2_tex[0x100];
#else
u8 onp_win_ga2_tex[] = {
#include "assets/onp_win_ga2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_ottpo_tex[0x200];
#else
u8 onp_win_ottpo_tex[] = {
#include "assets/onp_win_ottpo_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_tama1_tex[0x100];
#else
u8 onp_win_tama1_tex[] = {
#include "assets/onp_win_tama1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_tama2_tex[0x400];
#else
u8 onp_win_tama2_tex[] = {
#include "assets/onp_win_tama2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_tama5_tex[0x100];
#else
u8 onp_win_tama5_tex[] = {
#include "assets/onp_win_tama5_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_w1_tex[0x800];
#else
u8 onp_win_w1_tex[] = {
#include "assets/onp_win_w1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_me_tex[0x100];
#else
u8 onp_win_me_tex[] = {
#include "assets/onp_win_me_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_ohana_tex[0x100];
#else
u8 onp_win_ohana_tex[] = {
#include "assets/onp_win_ohana_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_w2_tex[0x800];
#else
u8 onp_win_w2_tex[] = {
#include "assets/onp_win_w2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_w3_tex[0x400];
#else
u8 onp_win_w3_tex[] = {
#include "assets/onp_win_w3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_ha_tex[0x800];
#else
u8 onp_win_ha_tex[] = {
#include "assets/onp_win_ha_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_ha2_tex[0x800];
#else
u8 onp_win_ha2_tex[] = {
#include "assets/onp_win_ha2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_carde_tex[0x400];
#else
u8 onp_win_carde_tex[] = {
#include "assets/onp_win_carde_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rmoji[0x80];
#else
u8 rmoji[] = {
#include "assets/rmoji.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_rbutton2_tex_rgb_ia8[0x200];
#else
u8 onp_win_rbutton2_tex_rgb_ia8[] = {
#include "assets/onp_win_rbutton2_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_rbutton_tex_rgb_ia8[0x200];
#else
u8 onp_win_rbutton_tex_rgb_ia8[] = {
#include "assets/onp_win_rbutton_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
Vtx onp_win_v[0x9E0 / sizeof(Vtx)];
#else
Vtx onp_win_v[] = {
#include "assets/onp_win_v.inc"
};
#endif

#ifdef TARGET_PC
Vtx onp_carde_v[0x100 / sizeof(Vtx)];
#else
Vtx onp_carde_v[] = {
#include "assets/onp_carde_v.inc"
};
#endif

Gfx onp_win_ga3_model[] = {
    gsDPSetPrimColor(0, 255, 255, 255, 230, 255),
    gsSPVertex(onp_win_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx onp_win_wakuT_model[] = {
    gsDPSetPrimColor(0, 255, 255, 255, 70, 255),
    gsDPSetEnvColor(0, 0, 215, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, onp_win_w3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&onp_win_v[8], 20, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, onp_win_w2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 8, 9, 10, 8, 11, 9, 10, 9, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 15, 17, 16, 17, 18, 19),
    gsSPNTriangles_5b(16, 17, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, onp_win_w1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&onp_win_v[28], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx onp_win_meT_model[] = {
    gsDPSetPrimColor(0, 255, 70, 80, 0, 255),
    gsDPSetEnvColor(0, 255, 0, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, onp_win_me_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&onp_win_v[44], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx onp_win_ga1T_model[] = {
    gsDPSetPrimColor(0, 255, 110, 255, 0, 255),
    gsDPSetEnvColor(0, 0, 0, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, onp_win_ga2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&onp_win_v[52], 14, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 0, 4, 3),
    gsSPNTriangles_5b(0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, onp_win_ga3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 6, 7, 8, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, onp_win_ga_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 9, 10, 11, 11, 10, 12, 11, 12, 13),
    gsSPEndDisplayList(),
};

Gfx onp_win_ga2T_model[] = {
    gsDPSetPrimColor(0, 255, 0, 255, 0, 255),
    gsDPSetEnvColor(0, 30, 0, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, onp_win_ga2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&onp_win_v[66], 16, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 4, 2, 1, 4),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, onp_win_ga3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 5, 6, 7, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, onp_win_ga4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 8, 9, 10, 8, 11, 12, 11, 8, 10),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, onp_win_ga_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 13, 14, 15, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx onp_win_hanaT_model[] = {
    gsDPSetPrimColor(0, 255, 0, 80, 0, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, onp_win_ohana_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&onp_win_v[82], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx onp_win_senT_model[] = {
    gsDPSetPrimColor(0, 255, 255, 110, 30, 95),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, onp_win_tama5_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&onp_win_v[86], 24, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 128, 16, onp_win_tama2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 12, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, onp_win_tama1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(23, 20, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx onp_win_waku2T_model[] = {
    gsDPSetPrimColor(0, 255, 0, 0, 205, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, onp_win_ottpo_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&onp_win_v[110], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx onp_win_waku3T_model[] = {
    gsDPSetPrimColor(0, 255, 80, 255, 20, 255),
    gsDPSetEnvColor(0, 80, 0, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, onp_win_ha_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&onp_win_v[114], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx onp_win_shiroT_model[] = {
    gsDPSetPrimColor(0, 255, 55, 175, 55, 255),
    gsDPSetEnvColor(255, 255, 230, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, onp_win_shiro_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&onp_win_v[138], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx onp_win_owariT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, onp_win_ok_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&onp_win_v[142], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx onp_win_waku5T_model[] = {
    gsDPSetPrimColor(0, 255, 75, 225, 30, 255),
    gsDPSetEnvColor(0, 70, 0, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, onp_win_ha2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&onp_win_v[150], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx onp_win_waku6T_model[] = {
    gsDPSetPrimColor(0, 255, 95, 255, 10, 255),
    gsDPSetEnvColor(0, 80, 0, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, onp_win_ha2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&onp_win_v[154], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

static Gfx onp_win_rmoji_model[] = {
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, rmoji),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(onp_carde_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx onp_win_rbuttonT_model[] = {
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(95, 95, 95, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, anime_4_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&onp_carde_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx onp_win_leafT_model[] = {
    gsDPSetPrimColor(0, 255, 205, 255, 0, 255),
    gsDPSetEnvColor(30, 40, 0, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, onp_win_ha_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&onp_carde_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx onp_win_cardeT_model[] = {
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(40, 105, 20, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, onp_win_carde_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&onp_carde_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx onp_win_mode[] = {
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_DECAL_LEQUAL),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsSPEndDisplayList(),
};

Gfx onp_win_model[] = {
    gsSPDisplayList(onp_win_mode),
    gsSPDisplayList(onp_win_waku2T_model),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsSPDisplayList(onp_win_wakuT_model),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsSPDisplayList(onp_win_ga3_model),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPDisplayList(onp_win_ga2T_model),
    gsSPDisplayList(onp_win_ga1T_model),
    gsSPDisplayList(onp_win_meT_model),
    gsSPDisplayList(onp_win_waku5T_model),
    gsSPDisplayList(onp_win_waku3T_model),
    gsSPDisplayList(onp_win_waku6T_model),
    gsSPDisplayList(onp_win_shiroT_model),
    gsSPDisplayList(onp_win_rbuttonT_model),
    gsSPDisplayList(onp_win_leafT_model),
    gsSPDisplayList(onp_win_cardeT_model),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsSPDisplayList(onp_win_hanaT_model),
    gsSPDisplayList(onp_win_senT_model),
    gsSPDisplayList(onp_win_rmoji_model),
    gsSPEndDisplayList(),
};
