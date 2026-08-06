#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx dia_hyouji_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 dir_win_diary_tex[0x500];
#else
ATTRIBUTE_ALIGN(32) u8 dir_win_diary_tex[] = {
#include "assets/dir_win_diary_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 kei_win_quit_tex[0x200];
#else
static u8 kei_win_quit_tex[] = {
#include "assets/dia_hyouji/kei_win_quit_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 lat_tegami_b2_tex[0x800];
#else
static u8 lat_tegami_b2_tex[] = {
#include "assets/dia_hyouji/lat_tegami_b2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_sousa_2b1_tex_rgb_i4[0x200];
#else
u8 lat_sousa_2b1_tex_rgb_i4[] = {
#include "assets/lat_sousa_2b1_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
static u8 lat_tegami_b3_tex[0x800];
#else
static u8 lat_tegami_b3_tex[] = {
#include "assets/dia_hyouji/lat_tegami_b3_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 kei_win_2b1_tex_rgb_i4[0x200];
#else
static u8 kei_win_2b1_tex_rgb_i4[] = {
#include "assets/dia_hyouji/kei_win_2b1_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx dia_hyouji_v[0x100 / sizeof(Vtx)];
#else
Vtx dia_hyouji_v[] = {
#include "assets/dia_hyouji_v.inc"
};
#endif

Gfx kei_win_b2_model_1_data_4075A0[] = {
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, lat_tegami_b3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, kei_win_2b1_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(dia_hyouji_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx dia_win_bb_model[] = {
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, lat_tegami_b2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, lat_sousa_2b1_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&dia_hyouji_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kei_win_amojiT_model_1_data_407620[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(30, 130, 55, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 80, 16, dir_win_diary_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&dia_hyouji_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx dia_win_mojiT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 235, 235, 255),
    gsDPSetEnvColor(145, 50, 40, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, kei_win_quit_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&dia_hyouji_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx dia_init_mode_letter[] = {
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

Gfx dia_init_mode[] = {
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_CLD_SURF2),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_dia_hyouji_c(void) {
    pc_load_asset("assets/dia_hyouji/kei_win_quit_tex.bin", kei_win_quit_tex, 0x200, 0x7A1660, 0, 0);
    pc_load_asset("assets/dia_hyouji/lat_tegami_b2_tex.bin", lat_tegami_b2_tex, 0x800, 0x7A8CE0, 0, 0);
    pc_load_asset("assets/dia_hyouji/lat_tegami_b3_tex.bin", lat_tegami_b3_tex, 0x800, 0x7A94E0, 0, 0);
    pc_load_asset("assets/dia_hyouji/kei_win_2b1_tex_rgb_i4.bin", kei_win_2b1_tex_rgb_i4, 0x200, 0x6E45E0, 0, 0);
}
#endif
