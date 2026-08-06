#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 pas_win_nimotu_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 pas_win_nimotu_pal[] = {
#include "assets/pas_win_nimotu_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 pas_win_nuno_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 pas_win_nuno_tex_rgb_ci4_pal[] = {
#include "assets/pas_win_nuno_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 pas_win_ta1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 pas_win_ta1_tex_rgb_ci4_pal[] = {
#include "assets/pas_win_ta1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 pas_win_ta2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 pas_win_ta2_tex_rgb_ci4_pal[] = {
#include "assets/pas_win_ta2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 pas_win_ta3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 pas_win_ta3_tex_rgb_ci4_pal[] = {
#include "assets/pas_win_ta3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 pas_win_name_tex[0x200];
#else
u8 pas_win_name_tex[] = {
#include "assets/pas_win_name_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 pas_win_town_tex[0x200];
#else
u8 pas_win_town_tex[] = {
#include "assets/pas_win_town_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 fkm_win_fuki2_tex[0x800];
#else
static u8 fkm_win_fuki2_tex[] = {
#include "assets/pas_win/fkm_win_fuki2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 pas_win_wa_tex[0x80];
#else
u8 pas_win_wa_tex[] = {
#include "assets/pas_win_wa_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 pas_win_test_tex[0x80];
#else
u8 pas_win_test_tex[] = {
#include "assets/pas_win_test_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 pas_win_icon_tex[0x800];
#else
u8 pas_win_icon_tex[] = {
#include "assets/pas_win_icon_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 fkm_win_w4_tex[0x80];
#else
static u8 fkm_win_w4_tex[] = {
#include "assets/pas_win/fkm_win_w4_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 fkm_win_w3_tex[0x200];
#else
static u8 fkm_win_w3_tex[] = {
#include "assets/pas_win/fkm_win_w3_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 fkm_win_w2_tex[0x200];
#else
static u8 fkm_win_w2_tex[] = {
#include "assets/pas_win/fkm_win_w2_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 fkm_win_w1_tex[0x400];
#else
static u8 fkm_win_w1_tex[] = {
#include "assets/pas_win/fkm_win_w1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 pas_win_nuno_tex_rgb_ci4[0x200];
#else
u8 pas_win_nuno_tex_rgb_ci4[] = {
#include "assets/pas_win_nuno_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 pas_win_ta1_tex_rgb_ci4[0x400];
#else
u8 pas_win_ta1_tex_rgb_ci4[] = {
#include "assets/pas_win_ta1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 pas_win_ta2_tex_rgb_ci4[0x400];
#else
u8 pas_win_ta2_tex_rgb_ci4[] = {
#include "assets/pas_win_ta2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 pas_win_ta3_tex_rgb_ci4[0x400];
#else
u8 pas_win_ta3_tex_rgb_ci4[] = {
#include "assets/pas_win_ta3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx pas_win_v[0x940 / sizeof(Vtx)];
#else
Vtx pas_win_v[] = {
#include "assets/pas_win_v.inc"
};
#endif

Gfx pas_win_fuki_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
    gsDPSetPrimColor(0, 255, 55, 35, 0, 180),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 128, 32, fkm_win_fuki2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(pas_win_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_win_wmura_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, pas_win_test_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pas_win_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_win_wname_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, pas_win_test_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pas_win_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_win_name_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 70, 60, 50, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, pas_win_town_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pas_win_v[12], 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, pas_win_name_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_win_waku1_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, pas_win_wa_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pas_win_v[20], 24, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 2, 3, 4),
    gsSPNTriangles_5b(3, 5, 4, 6, 7, 8, 7, 9, 8, 10, 11, 12),
    gsSPNTriangles_5b(13, 10, 12, 14, 10, 13, 15, 14, 13, 16, 17, 18),
    gsSPNTriangles_5b(19, 16, 18, 20, 19, 21, 19, 18, 21, 22, 9, 7),
    gsSPNTriangles_5b(22, 23, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_win_waku2_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, pas_win_wa_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pas_win_v[44], 24, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 4, 8, 5, 8, 9, 5, 10, 11, 12),
    gsSPNTriangles_5b(11, 13, 12, 12, 13, 14, 13, 15, 14, 3, 2, 16),
    gsSPNTriangles_5b(17, 3, 16, 18, 19, 20, 21, 18, 20, 22, 18, 21),
    gsSPNTriangles_5b(23, 22, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_win_w1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pas_win_ta1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, pas_win_ta1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pas_win_v[68], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_win_w2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pas_win_ta2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, pas_win_ta2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&pas_win_v[72], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_win_w3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pas_win_ta3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, pas_win_ta3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pas_win_v[76], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_win_w4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pas_win_ta2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, pas_win_ta2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pas_win_v[80], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_win_w5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pas_win_ta1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, pas_win_ta1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pas_win_v[84], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_win_w6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pas_win_ta1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, pas_win_ta1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pas_win_v[88], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_win_w7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pas_win_ta2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, pas_win_ta2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pas_win_v[92], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_win_w8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pas_win_ta3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, pas_win_ta3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pas_win_v[96], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_win_w9T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pas_win_ta2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, pas_win_ta2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pas_win_v[100], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_win_w10T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pas_win_ta1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, pas_win_ta1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pas_win_v[104], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_win_ueT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 255, 245, 195, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, fkm_win_w1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pas_win_v[108], 24, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 12, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, fkm_win_w2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 19, 16, 18, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, fkm_win_w3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pas_win_v[132], 12, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, fkm_win_w4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 9, 11, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_win_iconT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, pas_win_nimotu_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, pas_win_icon_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pas_win_v[144], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_win_mode[] = {
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_TEX_EDGE2),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(14, 16, 1, pas_win_nuno_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, pas_win_nuno_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pas_win_model[] = {
    gsSPDisplayList(pas_win_w1T_model),
    gsSPDisplayList(pas_win_w2T_model),
    gsSPDisplayList(pas_win_w3T_model),
    gsSPDisplayList(pas_win_w4T_model),
    gsSPDisplayList(pas_win_w5T_model),
    gsSPDisplayList(pas_win_w6T_model),
    gsSPDisplayList(pas_win_w7T_model),
    gsSPDisplayList(pas_win_w8T_model),
    gsSPDisplayList(pas_win_w9T_model),
    gsSPDisplayList(pas_win_w10T_model),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPDisplayList(pas_win_ueT_model),
    gsSPDisplayList(pas_win_fuki_model),
    gsSPDisplayList(pas_win_wmura_model),
    gsSPDisplayList(pas_win_wname_model),
    gsSPDisplayList(pas_win_name_model),
    gsSPDisplayList(pas_win_iconT_model),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_pas_win_c(void) {
    pc_load_asset("assets/pas_win/fkm_win_fuki2_tex.bin", fkm_win_fuki2_tex, 0x800, 0x7B1BA0, 0, 0);
    pc_load_asset("assets/pas_win/fkm_win_w4_tex.bin", fkm_win_w4_tex, 0x80, 0x7B6AC0, 0, 0);
    pc_load_asset("assets/pas_win/fkm_win_w3_tex.bin", fkm_win_w3_tex, 0x200, 0x7B6B40, 0, 0);
    pc_load_asset("assets/pas_win/fkm_win_w2_tex.bin", fkm_win_w2_tex, 0x200, 0x7B6D40, 0, 0);
    pc_load_asset("assets/pas_win/fkm_win_w1_tex.bin", fkm_win_w1_tex, 0x400, 0x7B3120, 0, 0);
}
#endif
