#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx clk_win_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 maru[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 maru[] = {
#include "assets/maru.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_am_tex_rgb_ia8[0x400];
#else
u8 clk_win_am_tex_rgb_ia8[] = {
#include "assets/clk_win_am_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_pm_tex_rgb_ia8[0x400];
#else
u8 clk_win_pm_tex_rgb_ia8[] = {
#include "assets/clk_win_pm_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_fri_tex_rgb_ia8[0x400];
#else
u8 clk_win_fri_tex_rgb_ia8[] = {
#include "assets/clk_win_fri_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_mon_tex_rgb_ia8[0x400];
#else
u8 clk_win_mon_tex_rgb_ia8[] = {
#include "assets/clk_win_mon_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_sat_tex_rgb_ia8[0x400];
#else
u8 clk_win_sat_tex_rgb_ia8[] = {
#include "assets/clk_win_sat_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_sun_tex_rgb_ia8[0x400];
#else
u8 clk_win_sun_tex_rgb_ia8[] = {
#include "assets/clk_win_sun_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_thu_tex_rgb_ia8[0x400];
#else
u8 clk_win_thu_tex_rgb_ia8[] = {
#include "assets/clk_win_thu_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_tue_tex_rgb_ia8[0x400];
#else
u8 clk_win_tue_tex_rgb_ia8[] = {
#include "assets/clk_win_tue_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 clk_win_wed_tex_rgb_ia8[0x400];
#else
u8 clk_win_wed_tex_rgb_ia8[] = {
#include "assets/clk_win_wed_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
Vtx clk_win_v[0x140 / sizeof(Vtx)];
#else
Vtx clk_win_v[] = {
#include "assets/clk_win_v.inc"
};
#endif

Gfx clk_win_youbiT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(clk_win_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx clk_win_maru2T_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, maru),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&clk_win_v[4], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx clk_win_ampmT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, anime_3_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&clk_win_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx clk_win_maruT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, maru),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&clk_win_v[16], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx clk_win_mode[] = {
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0,
                       0, 0, COMBINED),
    gsSPEndDisplayList(),
};
