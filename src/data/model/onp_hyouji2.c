#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 onp_win_play_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 onp_win_play_tex[] = {
#include "assets/onp_win_play_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 onp_win_erase_tex[0x400];
#else
u8 onp_win_erase_tex[] = {
#include "assets/onp_win_erase_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 x[0x80];
#else
u8 x[] = {
#include "assets/x.inc"
};
#endif

#ifdef TARGET_PC
u8 y[0x80];
#else
u8 y[] = {
#include "assets/y.inc"
};
#endif

#ifdef TARGET_PC
u8 start2_tex_rgb_ia8[0x400];
#else
u8 start2_tex_rgb_ia8[] = {
#include "assets/start2_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 start_tex_rgb_ia8[0x400];
#else
u8 start_tex_rgb_ia8[] = {
#include "assets/start_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 onp__x2_tex_rgb_ia8[0x200];
#else
u8 onp__x2_tex_rgb_ia8[] = {
#include "assets/onp__x2_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 onp__x_tex_rgb_ia8[0x200];
#else
u8 onp__x_tex_rgb_ia8[] = {
#include "assets/onp__x_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 onp__y2_tex_rgb_ia8[0x200];
#else
u8 onp__y2_tex_rgb_ia8[] = {
#include "assets/onp__y2_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 onp__y_tex_rgb_ia8[0x200];
#else
u8 onp__y_tex_rgb_ia8[] = {
#include "assets/onp__y_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
Vtx onp_hyouji2_v[0x1C0 / sizeof(Vtx)];
#else
static Vtx onp_hyouji2_v[] = {
#include "assets/onp_hyouji2/onp_hyouji_v.inc"
};
#endif

Gfx onp_win_rmoji_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, y),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(onp_hyouji2_v, 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, x),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx onp_win_zT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 185, 195, 175, 255),
    gsDPSetEnvColor(0, 0, 0, 255),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&onp_hyouji2_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx onp_win_mojiT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(20, 115, 20, 255),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, onp_win_erase_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&onp_hyouji2_v[12], 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, onp_win_play_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx onp_win_rT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 185, 195, 175, 255),
    gsDPSetEnvColor(0, 0, 0, 255),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&onp_hyouji2_v[20], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx onp_win_sT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 225, 225, 225, 255),
    gsDPSetEnvColor(50, 50, 50, 255),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, anime_3_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&onp_hyouji2_v[24], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_onp_hyouji2_c(void) {
    pc_load_asset("assets/onp_hyouji2/onp_hyouji_v.bin", onp_hyouji2_v, 0x1C0, 0x781140, 0, 2);
}
#endif
