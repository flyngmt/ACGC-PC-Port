#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 cal_win_choose_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 cal_win_choose_tex[] = {
#include "assets/cal_win_choose_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 lat_sousa_2b1_tex[0x200];
#else
static u8 lat_sousa_2b1_tex[] = {
#include "assets/cal_hyouji/lat_sousa_2b1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_hyouji_yaji2_tex[0x400];
#else
u8 cal_hyouji_yaji2_tex[] = {
#include "assets/cal_hyouji_yaji2_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 std_tex[0x800];
#else
static u8 std_tex[] = {
#include "assets/cal_hyouji/std_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_hyouji_st1_tex_rgb_ia8[0x1000];
#else
u8 cal_hyouji_st1_tex_rgb_ia8[] = {
#include "assets/cal_hyouji_st1_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_hyouji_st5_tex_rgb_ia8[0x1000];
#else
u8 cal_hyouji_st5_tex_rgb_ia8[] = {
#include "assets/cal_hyouji_st5_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
static u8 lat_tegami_b3_tex[0x800];
#else
static u8 lat_tegami_b3_tex[] = {
#include "assets/cal_hyouji/lat_tegami_b3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_hyouji_2b1_tex_rgb_i4[0x200];
#else
u8 cal_hyouji_2b1_tex_rgb_i4[] = {
#include "assets/cal_hyouji_2b1_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx cal_hyouji_v[0x1C0 / sizeof(Vtx)];
#else
Vtx cal_hyouji_v[] = {
#include "assets/cal_hyouji_v.inc"
};
#endif

Gfx cal_hyouji_b2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, lat_tegami_b3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, cal_hyouji_2b1_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(cal_hyouji_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx cal_hyouji_3DT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(0, 0, 0, 255),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, std_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&cal_hyouji_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx cal_hyouji_shitaT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 0, 0, 0, 255),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, lat_sousa_2b1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&cal_hyouji_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx cal_hyouji_amojiT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(30, 130, 55, 255),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, cal_win_choose_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&cal_hyouji_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx cal_hyouji_stT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 215, 215, 215, 255),
    gsDPSetEnvColor(50, 50, 50, 255),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsSPVertex(&cal_hyouji_v[16], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx cal_hyoji_yaji1T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 165, 255, 255),
    gsDPSetEnvColor(70, 0, 0, 255),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, cal_hyouji_yaji2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&cal_hyouji_v[20], 8, 0),
    gsSPEndDisplayList(),
};

Gfx cal_hyoji_yajiA_gfx[] = {
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx cal_hyoji_yajiB_gfx[] = {
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_cal_hyouji_c(void) {
    pc_load_asset("assets/cal_hyouji/lat_sousa_2b1_tex.bin", lat_sousa_2b1_tex, 0x200, 0x6A8940, 0, 0);
    pc_load_asset("assets/cal_hyouji/std_tex.bin", std_tex, 0x800, 0x6A8F40, 0, 0);
    pc_load_asset("assets/cal_hyouji/lat_tegami_b3_tex.bin", lat_tegami_b3_tex, 0x800, 0x7A94E0, 0, 0);
}
#endif
