#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kei_win_latest_tex[0x500];
#else
ATTRIBUTE_ALIGN(32) u8 kei_win_latest_tex[] = {
#include "assets/kei_win_latest_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kei_win_entry_tex[0x400];
#else
u8 kei_win_entry_tex[] = {
#include "assets/kei_win_entry_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 kei_win_quit_tex[0x200];
#else
static u8 kei_win_quit_tex[] = {
#include "assets/kei_hyouji/kei_win_quit_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kei_win_writen_tex[0x400];
#else
u8 kei_win_writen_tex[] = {
#include "assets/kei_win_writen_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kei_win_yaji2_tex[0x400];
#else
u8 kei_win_yaji2_tex[] = {
#include "assets/kei_win_yaji2_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 std_tex[0x800];
#else
static u8 std_tex[] = {
#include "assets/kei_hyouji/std_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 yaji[0x80];
#else
static u8 yaji[] = {
#include "assets/kei_hyouji/yaji.inc"
};
#endif

#ifdef TARGET_PC
static u8 ct_tex[0x400];
#else
static u8 ct_tex[] = {
#include "assets/kei_hyouji/ct_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kei_win_st1_tex_rgb_ia8[0x1000];
#else
u8 kei_win_st1_tex_rgb_ia8[] = {
#include "assets/kei_win_st1_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kei_win_st2_tex_rgb_ia8[0x1000];
#else
u8 kei_win_st2_tex_rgb_ia8[] = {
#include "assets/kei_win_st2_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kei_win_st3_tex_rgb_ia8[0x1000];
#else
u8 kei_win_st3_tex_rgb_ia8[] = {
#include "assets/kei_win_st3_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kei_win_st4_tex_rgb_ia8[0x1000];
#else
u8 kei_win_st4_tex_rgb_ia8[] = {
#include "assets/kei_win_st4_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kei_win_st5_tex_rgb_ia8[0x1000];
#else
u8 kei_win_st5_tex_rgb_ia8[] = {
#include "assets/kei_win_st5_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kei_win_st6_tex_rgb_ia8[0x1000];
#else
u8 kei_win_st6_tex_rgb_ia8[] = {
#include "assets/kei_win_st6_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
static u8 lat_tegami_b2_tex[0x800];
#else
static u8 lat_tegami_b2_tex[] = {
#include "assets/kei_hyouji/lat_tegami_b2_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 lat_tegami_b3_tex[0x800];
#else
static u8 lat_tegami_b3_tex[] = {
#include "assets/kei_hyouji/lat_tegami_b3_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 kei_win_2b1_tex_rgb_i4[0x200];
#else
static u8 kei_win_2b1_tex_rgb_i4[] = {
#include "assets/kei_hyouji/kei_win_2b1_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx kei_hyouji_v[0x340 / sizeof(Vtx)];
#else
Vtx kei_hyouji_v[] = {
#include "assets/kei_hyouji_v.inc"
};
#endif

Gfx kei_win_bt_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, lat_tegami_b2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, kei_win_2b1_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(kei_hyouji_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

static Gfx kei_win_b2_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, lat_tegami_b3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, kei_win_2b1_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kei_hyouji_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kei_win_cbt_model[] = {
    gsDPSetPrimColor(0, 255, 255, 215, 0, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, yaji),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kei_hyouji_v[8], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kei_win_3DT_model[] = {
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(0, 0, 0, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, std_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kei_hyouji_v[16], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kei_win_cmojiT_model[] = {
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(165, 80, 40, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, kei_win_entry_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kei_hyouji_v[20], 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 80, 16, kei_win_latest_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kei_win_bmojiT_model[] = {
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(155, 0, 0, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, kei_win_quit_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kei_hyouji_v[28], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

static Gfx kei_win_amojiT_model[] = {
    gsDPSetPrimColor(0, 255, 235, 255, 235, 255),
    gsDPSetEnvColor(30, 130, 55, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, kei_win_writen_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kei_hyouji_v[32], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kei_win_stT_model[] = {
    gsDPSetPrimColor(0, 255, 215, 215, 215, 255),
    gsDPSetEnvColor(50, 50, 50, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kei_hyouji_v[36], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kei_win_cbT_model[] = {
    gsDPSetPrimColor(0, 255, 255, 195, 50, 255),
    gsDPSetEnvColor(70, 70, 50, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, ct_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kei_hyouji_v[40], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kei_win_yaji1T_mode[] = {
    gsDPSetPrimColor(0, 255, 255, 165, 255, 255),
    gsDPSetEnvColor(70, 0, 0, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, kei_win_yaji2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kei_hyouji_v[44], 8, 0),
    gsSPEndDisplayList(),
};

Gfx kei_win_yaji1T_model[] = {
    gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
    gsSPEndDisplayList(),
};

Gfx kei_win_yaji2T_model[] = {
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx kei_hyouji_mode[] = {
    gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_CLD_SURF2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

Gfx kei_hyouji_model[] = {
    gsSPDisplayList(kei_hyouji_mode),
    gsSPDisplayList(kei_win_bt_model),
    gsSPDisplayList(kei_win_b2_model),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPDisplayList(kei_win_cbt_model),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsSPDisplayList(kei_win_3DT_model),
    gsSPDisplayList(kei_win_cbT_model),
    gsSPDisplayList(kei_win_cmojiT_model),
    gsSPDisplayList(kei_win_bmojiT_model),
    gsSPDisplayList(kei_win_amojiT_model),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_kei_hyouji_c(void) {
    pc_load_asset("assets/kei_hyouji/kei_win_quit_tex.bin", kei_win_quit_tex, 0x200, 0x7A1660, 0, 0);
    pc_load_asset("assets/kei_hyouji/std_tex.bin", std_tex, 0x800, 0x7A2060, 0, 0);
    pc_load_asset("assets/kei_hyouji/yaji.bin", yaji, 0x80, 0xB5C980, 0, 0);
    pc_load_asset("assets/kei_hyouji/ct_tex.bin", ct_tex, 0x400, 0xB5BD80, 0, 0);
    pc_load_asset("assets/kei_hyouji/lat_tegami_b2_tex.bin", lat_tegami_b2_tex, 0x800, 0x7A8CE0, 0, 0);
    pc_load_asset("assets/kei_hyouji/lat_tegami_b3_tex.bin", lat_tegami_b3_tex, 0x800, 0x7A94E0, 0, 0);
    pc_load_asset("assets/kei_hyouji/kei_win_2b1_tex_rgb_i4.bin", kei_win_2b1_tex_rgb_i4, 0x200, 0x7A9CE0, 0, 0);
}
#endif
