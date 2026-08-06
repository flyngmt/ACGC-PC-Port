#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 gba_win_nuno_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 gba_win_nuno_tex_rgb_ci4_pal[]= {
#include "assets/gba_win_nuno_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 gba_win_w4_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 gba_win_w4_tex_rgb_ci4_pal[]= {
#include "assets/gba_win_w4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 gba_win_w1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 gba_win_w1_tex_rgb_ci4_pal[]= {
#include "assets/gba_win_w1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 gba_win_w2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 gba_win_w2_tex_rgb_ci4_pal[]= {
#include "assets/gba_win_w2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 gba_win_w3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 gba_win_w3_tex_rgb_ci4_pal[]= {
#include "assets/gba_win_w3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 sav_win_waku_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 sav_win_waku_tex[]= {
#include "assets/gba_win/sav_win_waku_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 gba_win_aw1_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 gba_win_aw1_tex[]= {
#include "assets/gba_win_aw1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 gba_win_aw2_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 gba_win_aw2_tex[]= {
#include "assets/gba_win_aw2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 gba_win_aw3_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 gba_win_aw3_tex[]= {
#include "assets/gba_win_aw3_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 gba_win_aw4_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 gba_win_aw4_tex[]= {
#include "assets/gba_win_aw4_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 inv_original_futa2_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 inv_original_futa2_tex[]= {
#include "assets/gba_win/inv_original_futa2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 gba_win_nuno_tex_rgb_ci4[0x200];
#else
u8 gba_win_nuno_tex_rgb_ci4[] = {
#include "assets/gba_win_nuno_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 gba_win_w4_tex_rgb_ci4[0x80];
#else
u8 gba_win_w4_tex_rgb_ci4[] = {
#include "assets/gba_win_w4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 gba_win_w1_tex_rgb_ci4[0x400];
#else
u8 gba_win_w1_tex_rgb_ci4[] = {
#include "assets/gba_win_w1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 gba_win_w2_tex_rgb_ci4[0x400];
#else
u8 gba_win_w2_tex_rgb_ci4[] = {
#include "assets/gba_win_w2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 gba_win_w3_tex_rgb_ci4[0x100];
#else
u8 gba_win_w3_tex_rgb_ci4[] = {
#include "assets/gba_win_w3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx gba_win_v[0xFA0 / sizeof(Vtx)];
#else
Vtx gba_win_v[] = {
#include "assets/gba_win_v.inc"
};
#endif

Gfx gba_win_w_before_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(14, 16, 1, gba_win_nuno_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, gba_win_nuno_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_w11_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, gba_win_w4_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, gba_win_w4_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(gba_win_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_waku_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 90, 90, 205, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, sav_win_waku_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&gba_win_v[4], 32, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 11, 8, 10, 12, 13, 14),
gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 19, 16, 18, 20, 21, 22),
gsSPNTriangles_5b(21, 23, 22, 24, 25, 26, 25, 27, 26, 28, 29, 30),
gsSPNTriangles_5b(31, 28, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_mb_before_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
};

Gfx gba_win_mb1_model[] = {
gsSPVertex(&gba_win_v[36], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_mb2_model[] = {
gsSPVertex(&gba_win_v[40], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_mb3_model[] = {
gsSPVertex(&gba_win_v[44], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_mb4_model[] = {
gsSPVertex(&gba_win_v[48], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_mb5_model[] = {
gsSPVertex(&gba_win_v[52], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_mb6_model[] = {
gsSPVertex(&gba_win_v[56], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_mb7_model[] = {
gsSPVertex(&gba_win_v[60], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_mb8_model[] = {
gsSPVertex(&gba_win_v[64], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_f_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 50, 50, 115, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, inv_original_futa2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&gba_win_v[68], 32, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 11, 8, 10, 12, 13, 14),
gsSPNTriangles_5b(15, 12, 14, 16, 17, 18, 17, 19, 18, 20, 21, 22),
gsSPNTriangles_5b(21, 23, 22, 24, 25, 26, 27, 24, 26, 28, 29, 30),
gsSPNTriangles_5b(31, 28, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_w1T_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, gba_win_w1_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, gba_win_w1_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&gba_win_v[100], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_w2T_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, gba_win_w2_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, gba_win_w2_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&gba_win_v[104], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_w3T_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, gba_win_w3_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, gba_win_w3_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&gba_win_v[108], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_w4T_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, gba_win_w2_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, gba_win_w2_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&gba_win_v[112], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_w5T_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, gba_win_w1_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, gba_win_w1_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&gba_win_v[116], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_w6T_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, gba_win_w1_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, gba_win_w1_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&gba_win_v[120], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_w7T_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, gba_win_w2_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, gba_win_w2_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&gba_win_v[124], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_w8T_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, gba_win_w3_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, gba_win_w3_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&gba_win_v[128], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_w9T_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, gba_win_w2_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, gba_win_w2_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&gba_win_v[132], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_w10T_model[] = {
gsDPLoadTLUT_Dolphin(15, 16, 1, gba_win_w1_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, gba_win_w1_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&gba_win_v[136], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx gba_win_ueT_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 65, 65, 105, 255),
gsDPSetEnvColor(145, 145, 255, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, gba_win_aw4_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&gba_win_v[140], 32, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 15, 13, 16, 17, 18, 16, 18, 19, 20, 21, 22),
gsSPNTriangles_5b(21, 23, 22, 24, 25, 26, 27, 24, 26, 28, 29, 30),
gsSPNTriangles_5b(29, 31, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&gba_win_v[172], 20, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 32, gba_win_aw3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(8, 4, 5, 6, 5, 7, 6, 8, 9, 10),
gsSPNTriangles_5b(9, 11, 10, 12, 13, 14, 12, 15, 13, 16, 17, 18),
gsSPNTriangles_5b(17, 19, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, gba_win_aw2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&gba_win_v[192], 32, 0),
gsSPNTrianglesInit_5b(17, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 9, 12, 13),
gsSPNTriangles_5b(12, 14, 13, 15, 16, 17, 16, 18, 17, 19, 15, 20),
gsSPNTriangles_5b(15, 21, 20, 22, 23, 24, 23, 25, 24, 26, 27, 28),
gsSPNTriangles_5b(27, 2, 28, 29, 30, 31, 0, 0, 0, 0, 0, 0),
gsSPVertex(&gba_win_v[224], 26, 0),
gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 4, 6, 5),
gsSPNTriangles_5b(7, 8, 9, 8, 10, 9, 11, 12, 13, 12, 5, 13),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, gba_win_aw1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(8, 14, 15, 16, 17, 14, 16, 18, 17, 19),
gsSPNTriangles_5b(17, 16, 19, 20, 21, 22, 21, 23, 22, 20, 22, 24),
gsSPNTriangles_5b(25, 20, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};


#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_gba_win_c(void) {
    pc_load_asset("assets/gba_win/sav_win_waku_tex.bin", sav_win_waku_tex, 0x200, 0x79D4E0, 0, 0);
    pc_load_asset("assets/gba_win/inv_original_futa2_tex.bin", inv_original_futa2_tex, 0x200, 0x79D6E0, 0, 0);
}
#endif
