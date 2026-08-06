#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 lat_atena_win_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 lat_atena_win_tex[] = {
#include "assets/lat_atena_win_tex.inc"
};
#endif

Gfx lat_atena_kageT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
    gsDPSetPrimColor(0, 255, 20, 40, 0, 185),
    gsSPVertex(anime_2_txt, 8, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 2, 5),
    gsSPNTriangles_5b(0, 2, 4, 4, 5, 6, 7, 4, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx lat_atena_winT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsSPVertex(anime_1_txt, 8, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 5, 1),
    gsSPNTriangles_5b(1, 5, 3, 6, 7, 5, 4, 6, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx lat_atena_mode[] = {
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, lat_atena_win_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPEndDisplayList(),
};

Gfx lat_atena_model[] = {
    gsSPDisplayList(lat_atena_mode),
    gsSPDisplayList(lat_atena_kageT_model),
    gsSPEndDisplayList(),
};
