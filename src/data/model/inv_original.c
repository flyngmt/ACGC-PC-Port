#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 inv_ori_tw4_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 inv_ori_tw4_tex_rgb_ci4_pal[] = {
#include "assets/inv_ori_tw4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_original_cloth_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 inv_original_cloth_tex_rgb_ci4_pal[] = {
#include "assets/inv_original_cloth_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_ori_tw1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 inv_ori_tw1_tex_rgb_ci4_pal[] = {
#include "assets/inv_ori_tw1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_ori_tw2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 inv_ori_tw2_tex_rgb_ci4_pal[] = {
#include "assets/inv_ori_tw2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 inv_ori_tw3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 inv_ori_tw3_tex_rgb_ci4_pal[] = {
#include "assets/inv_ori_tw3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_ori_w1_tex[0x800];
#else
u8 inv_ori_w1_tex[] = {
#include "assets/inv_ori_w1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_ori_w2_tex[0x400];
#else
u8 inv_ori_w2_tex[] = {
#include "assets/inv_ori_w2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_ori_w3_tex[0x800];
#else
u8 inv_ori_w3_tex[] = {
#include "assets/inv_ori_w3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_ori_w4_tex[0x100];
#else
u8 inv_ori_w4_tex[] = {
#include "assets/inv_ori_w4_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 sav_win_waku_tex[0x200];
#else
static u8 sav_win_waku_tex[] = {
#include "assets/inv_original/sav_win_waku_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_original_futa2_tex[0x200];
#else
static u8 inv_original_futa2_tex[] = {
#include "assets/inv_original/inv_original_futa2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_ori_tw4_tex_rgb_ci4[0x80];
#else
u8 inv_ori_tw4_tex_rgb_ci4[] = {
#include "assets/inv_ori_tw4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_original_cloth_tex_rgb_ci4[0x200];
#else
u8 inv_original_cloth_tex_rgb_ci4[] = {
#include "assets/inv_original_cloth_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_ori_tw1_tex_rgb_ci4[0x400];
#else
u8 inv_ori_tw1_tex_rgb_ci4[] = {
#include "assets/inv_ori_tw1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_ori_tw2_tex_rgb_ci4[0x200];
#else
u8 inv_ori_tw2_tex_rgb_ci4[] = {
#include "assets/inv_ori_tw2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 inv_ori_tw3_tex_rgb_ci4[0x400];
#else
u8 inv_ori_tw3_tex_rgb_ci4[] = {
#include "assets/inv_ori_tw3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx inv_original_v[0xDE0 / sizeof(Vtx)];
#else
Vtx inv_original_v[] = {
#include "assets/inv_original_v.inc"
};
#endif

Gfx needlework_before_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_TEX_EDGE2),
    gsSPEndDisplayList(),
};

Gfx inv_original_w_model_before[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(14, 16, 1, inv_original_cloth_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_original_cloth_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_w9_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_ori_tw4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, inv_ori_tw4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(inv_original_v, 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_waku_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 165, 120, 70, 255),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, sav_win_waku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_original_v[4], 32, 0),
    gsSPNTriangles(16, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 19, 16, 18, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 22, 24, 25, 26, 27, 24, 26, 28, 29, 30),
    gsSPNTriangles_5b(31, 28, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_mb_before_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsSPEndDisplayList(),
};

Gfx inv_original_mb1_model[] = {
    gsSPVertex(&inv_original_v[36], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_mb2_model[] = {
    gsSPVertex(&inv_original_v[40], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_mb3_model[] = {
    gsSPVertex(&inv_original_v[44], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_mb4_model[] = {
    gsSPVertex(&inv_original_v[48], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_mb5_model[] = {
    gsSPVertex(&inv_original_v[52], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_mb6_model[] = {
    gsSPVertex(&inv_original_v[56], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_mb7_model[] = {
    gsSPVertex(&inv_original_v[60], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_mb8_model[] = {
    gsSPVertex(&inv_original_v[64], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_f_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 60, 40, 30, 255),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, inv_original_futa2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_original_v[68], 32, 0),
    gsSPNTriangles(16, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 12, 14, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 22, 24, 25, 26, 27, 24, 26, 28, 29, 30),
    gsSPNTriangles_5b(29, 31, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_w1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_ori_tw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_ori_tw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&inv_original_v[100], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_w2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_ori_tw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_ori_tw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&inv_original_v[104], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_w3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_ori_tw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_ori_tw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&inv_original_v[108], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_w4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_ori_tw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, inv_ori_tw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&inv_original_v[112], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_w5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_ori_tw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_ori_tw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&inv_original_v[116], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_w6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_ori_tw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_ori_tw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&inv_original_v[120], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_w7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_ori_tw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_ori_tw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&inv_original_v[124], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_w8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_ori_tw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, inv_ori_tw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&inv_original_v[128], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original_ueT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 70, 40, 50, 255),
    gsDPSetEnvColor(165, 145, 95, 255),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, inv_ori_w4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_original_v[132], 32, 0),
    gsSPNTriangles(16, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 22, 24, 25, 26, 25, 27, 26, 28, 29, 30),
    gsSPNTriangles_5b(29, 31, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&inv_original_v[164], 30, 0),
    gsSPNTriangles(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, inv_ori_w3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTriangles(4, 4, 5, 6, 4, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 11, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_ori_w2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTriangles(10, 12, 13, 14, 14, 15, 12, 16, 17, 18),
    gsSPNTriangles_5b(18, 19, 16, 20, 21, 22, 22, 23, 20, 23, 24, 25),
    gsSPNTriangles_5b(23, 26, 24, 26, 27, 28, 26, 29, 27, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, inv_ori_w1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_original_v[194], 28, 0),
    gsSPNTriangles(16, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 7, 9, 1, 11, 12),
    gsSPNTriangles_5b(12, 13, 1, 14, 15, 16, 16, 17, 14, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 19, 21, 22, 23, 21, 24, 22, 25, 24, 26),
    gsSPNTriangles_5b(24, 27, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 inv_original_aw5_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 inv_original_aw5_tex[] = {
#include "assets/inv_original_aw5_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx inv_original2_v[0xDC0 / sizeof(Vtx)];
#else
Vtx inv_original2_v[] = {
#include "assets/inv_original2_v.inc"
};
#endif

Gfx inv_original2_w9_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_ori_tw4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, inv_ori_tw4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(inv_original2_v, 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original2_waku_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 165, 120, 70, 255),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, sav_win_waku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_original2_v[4], 32, 0),
    gsSPNTriangles(16, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 12, 14, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(23, 20, 22, 24, 25, 26, 25, 27, 26, 28, 29, 30),
    gsSPNTriangles_5b(29, 31, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original2_mb1_model[] = {
    gsSPVertex(&inv_original2_v[36], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original2_mb2_model[] = {
    gsSPVertex(&inv_original2_v[40], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original2_mb3_model[] = {
    gsSPVertex(&inv_original2_v[44], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original2_mb4_model[] = {
    gsSPVertex(&inv_original2_v[48], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original2_mb5_model[] = {
    gsSPVertex(&inv_original2_v[52], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original2_mb6_model[] = {
    gsSPVertex(&inv_original2_v[56], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original2_mb7_model[] = {
    gsSPVertex(&inv_original2_v[60], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original2_mb8_model[] = {
    gsSPVertex(&inv_original2_v[64], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original2_f_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 60, 40, 30, 255),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, inv_original_futa2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_original2_v[68], 32, 0),
    gsSPNTriangles(16, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 19, 16, 18, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 22, 24, 25, 26, 25, 27, 26, 28, 29, 30),
    gsSPNTriangles_5b(31, 28, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original2_w1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_ori_tw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_ori_tw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&inv_original2_v[100], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original2_w2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_ori_tw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_ori_tw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&inv_original2_v[104], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original2_w3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_ori_tw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_ori_tw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&inv_original2_v[108], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original2_w4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_ori_tw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, inv_ori_tw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&inv_original2_v[112], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original2_w5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_ori_tw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_ori_tw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&inv_original2_v[116], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original2_w6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_ori_tw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_ori_tw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&inv_original2_v[120], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original2_w7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_ori_tw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_ori_tw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&inv_original2_v[124], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original2_w8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, inv_ori_tw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, inv_ori_tw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&inv_original2_v[128], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx inv_original2_ueT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 70, 40, 50, 255),
    gsDPSetEnvColor(165, 145, 95, 255),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, inv_ori_w3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_original2_v[132], 24, 0),
    gsSPNTriangles(4, 0, 1, 2, 3, 4, 5, 3, 6, 4),
    gsSPNTriangles_5b(0, 7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_ori_w2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTriangles(8, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 16, 18, 17, 19, 20, 21, 20, 22, 21),
    gsSPNTriangles_5b(13, 23, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, inv_ori_w1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_original2_v[156], 28, 0),
    gsSPNTriangles(16, 0, 1, 2, 3, 1, 4, 5, 6, 7),
    gsSPNTriangles_5b(6, 8, 7, 9, 10, 8, 8, 11, 9, 4, 12, 3),
    gsSPNTriangles_5b(13, 14, 15, 15, 14, 16, 17, 18, 16, 19, 20, 21),
    gsSPNTriangles_5b(20, 22, 21, 23, 22, 24, 22, 25, 24, 2, 26, 0),
    gsSPNTriangles_5b(18, 27, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, inv_original_aw5_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&inv_original2_v[184], 32, 0),
    gsSPNTriangles(16, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 16, 19, 17, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 24, 25, 26, 24, 27, 25, 28, 29, 30),
    gsSPNTriangles_5b(29, 31, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&inv_original2_v[216], 4, 0),
    gsSPNTriangles(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_inv_original_c(void) {
    pc_load_asset("assets/inv_original/sav_win_waku_tex.bin", sav_win_waku_tex, 0x200, 0x79D4E0, 0, 0);
    pc_load_asset("assets/inv_original/inv_original_futa2_tex.bin", inv_original_futa2_tex, 0x200, 0x79D6E0, 0, 0);
}
#endif
