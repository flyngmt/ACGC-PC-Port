#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 sav_win_w6_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 sav_win_w6_tex_rgb_ci4_pal[] = {
#include "assets/sav_win_w6_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 sav_win_w1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 sav_win_w1_tex_rgb_ci4_pal[] = {
#include "assets/sav_win_w1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 sav_win_w2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 sav_win_w2_tex_rgb_ci4_pal[] = {
#include "assets/sav_win_w2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 sav_win_w3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 sav_win_w3_tex_rgb_ci4_pal[] = {
#include "assets/sav_win_w3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 sav_win_w4_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 sav_win_w4_tex_rgb_ci4_pal[] = {
#include "assets/sav_win_w4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 sav_win_w5_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 sav_win_w5_tex_rgb_ci4_pal[] = {
#include "assets/sav_win_w5_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 inv_original_futa2_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 inv_original_futa2_tex[] = {
#include "assets/sav_win1/inv_original_futa2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 sav_win1_aw1_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 sav_win1_aw1_tex[] = {
#include "assets/sav_win1_aw1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 sav_win1_aw6_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 sav_win1_aw6_tex[] = {
#include "assets/sav_win1_aw6_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 sav_win_waku_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 sav_win_waku_tex[] = {
#include "assets/sav_win1/sav_win_waku_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 sav_win1_aw2_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 sav_win1_aw2_tex[] = {
#include "assets/sav_win1_aw2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 sav_win1_aw3_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 sav_win1_aw3_tex[] = {
#include "assets/sav_win1_aw3_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 sav_win1_aw4_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 sav_win1_aw4_tex[] = {
#include "assets/sav_win1_aw4_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 sav_win1_aw5_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 sav_win1_aw5_tex[] = {
#include "assets/sav_win1_aw5_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 ctl_win_tagu2_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 ctl_win_tagu2_tex[] = {
#include "assets/sav_win1/ctl_win_tagu2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 ctl_win_waku1_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 ctl_win_waku1_tex[] = {
#include "assets/sav_win1/ctl_win_waku1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 ctl_win_waku2_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 ctl_win_waku2_tex[] = {
#include "assets/sav_win1/ctl_win_waku2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 sav_win_1_kage1_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 sav_win_1_kage1_tex[] = {
#include "assets/sav_win_1_kage1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 sav_win_1_kage2_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 sav_win_1_kage2_tex[] = {
#include "assets/sav_win_1_kage2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 sav_win1_nuno_tex_rgb_ci4[0x200];
#else
u8 sav_win1_nuno_tex_rgb_ci4[] = {
#include "assets/sav_win1_nuno_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 sav_win_w6_tex_rgb_ci4[0x80];
#else
u8 sav_win_w6_tex_rgb_ci4[] = {
#include "assets/sav_win_w6_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 sav_win_w1_tex_rgb_ci4[0x400];
#else
u8 sav_win_w1_tex_rgb_ci4[] = {
#include "assets/sav_win_w1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 sav_win_w2_tex_rgb_ci4[0x400];
#else
u8 sav_win_w2_tex_rgb_ci4[] = {
#include "assets/sav_win_w2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 sav_win_w3_tex_rgb_ci4[0x400];
#else
u8 sav_win_w3_tex_rgb_ci4[] = {
#include "assets/sav_win_w3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 sav_win_w4_tex_rgb_ci4[0x400];
#else
u8 sav_win_w4_tex_rgb_ci4[] = {
#include "assets/sav_win_w4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 sav_win_w5_tex_rgb_ci4[0x400];
#else
u8 sav_win_w5_tex_rgb_ci4[] = {
#include "assets/sav_win_w5_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx sav_win1_v[0x1180 / sizeof(Vtx)];
#else
Vtx sav_win1_v[] = {
#include "assets/sav_win1_v.inc"
};
#endif

Gfx sav_win1_w9_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, sav_win_w6_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, sav_win_w6_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(sav_win1_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx sav_win1_kage_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 50, 50, 40, 205),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, sav_win_1_kage2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sav_win1_v[4], 12, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, sav_win_1_kage1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 5, 7, 6, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx sav_win1_waku_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 80, 50, 40, 255),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, sav_win_waku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sav_win1_v[16], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 22, 24, 25, 26, 27, 24, 26, 28, 29, 30),
    gsSPNTriangles_5b(31, 28, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&sav_win1_v[48], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 12, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx sav_win1_f_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 60, 40, 30, 255),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, inv_original_futa2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sav_win1_v[64], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 12, 14, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(23, 20, 22, 24, 25, 26, 25, 27, 26, 28, 29, 30),
    gsSPNTriangles_5b(31, 28, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&sav_win1_v[96], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 12, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx sav_win1_w1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, sav_win_w1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, sav_win_w1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&sav_win1_v[112], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx sav_win1_w2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, sav_win_w2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, sav_win_w2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&sav_win1_v[116], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx sav_win1_w3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, sav_win_w3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, sav_win_w3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&sav_win1_v[120], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx sav_win1_w4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, sav_win_w5_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, sav_win_w5_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&sav_win1_v[124], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx sav_win1_w5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, sav_win_w3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, sav_win_w3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&sav_win1_v[128], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx sav_win1_w6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, sav_win_w2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, sav_win_w2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&sav_win1_v[132], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx sav_win1_w7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, sav_win_w1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, sav_win_w1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&sav_win1_v[136], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx sav_win1_w8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, sav_win_w4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, sav_win_w4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&sav_win1_v[140], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx sav_win1_taguT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, ctl_win_tagu2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sav_win1_v[144], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx sav_win1_ueT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, sav_win1_aw5_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sav_win1_v[148], 22, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, sav_win1_aw4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 7, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, sav_win1_aw3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(14, 15, 12, 15, 16, 17, 17, 16, 18, 19, 11, 20),
    gsSPNTriangles_5b(20, 21, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, sav_win1_aw2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sav_win1_v[170], 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 10, 12, 13),
    gsSPNTriangles_5b(12, 14, 13, 13, 15, 16, 15, 17, 16, 16, 18, 19),
    gsSPNTriangles_5b(18, 20, 19, 19, 21, 22, 21, 23, 22, 7, 24, 25),
    gsSPNTriangles_5b(7, 26, 24, 26, 27, 28, 26, 0, 27, 29, 30, 31),
    gsSPNTriangles_5b(29, 5, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, sav_win1_aw6_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sav_win1_v[202], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 12, 14, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 22, 24, 25, 26, 25, 27, 26, 28, 29, 30),
    gsSPNTriangles_5b(31, 28, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&sav_win1_v[234], 20, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 16, 17, 18, 16, 19, 17, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, sav_win1_aw1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sav_win1_v[254], 14, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 2, 5),
    gsSPNTriangles_5b(5, 6, 4, 7, 8, 9, 7, 10, 8, 11, 10, 12),
    gsSPNTriangles_5b(12, 13, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx sav_win1_nameT_model2[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, ctl_win_waku2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sav_win1_v[268], 12, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, ctl_win_waku1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 5, 7, 6, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx save_win1_w_before_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, sav_win1_nuno_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

Gfx save_win1_w_all_model[] = {
    gsSPDisplayList(sav_win1_w1T_model), gsSPDisplayList(sav_win1_w2T_model),
    gsSPDisplayList(sav_win1_w3T_model), gsSPDisplayList(sav_win1_w4T_model),
    gsSPDisplayList(sav_win1_w5T_model), gsSPDisplayList(sav_win1_w6T_model),
    gsSPDisplayList(sav_win1_w7T_model), gsSPDisplayList(sav_win1_w8T_model),
    gsSPDisplayList(sav_win1_w9_model),  gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_sav_win1_c(void) {
    pc_load_asset("assets/sav_win1/inv_original_futa2_tex.bin", inv_original_futa2_tex, 0x200, 0x6CD2A0, 0, 0);
    pc_load_asset("assets/sav_win1/sav_win_waku_tex.bin", sav_win_waku_tex, 0x200, 0x6CDDA0, 0, 0);
    pc_load_asset("assets/sav_win1/ctl_win_tagu2_tex.bin", ctl_win_tagu2_tex, 0x200, 0x6CFFA0, 0, 0);
    pc_load_asset("assets/sav_win1/ctl_win_waku1_tex.bin", ctl_win_waku1_tex, 0x800, 0x6D01A0, 0, 0);
    pc_load_asset("assets/sav_win1/ctl_win_waku2_tex.bin", ctl_win_waku2_tex, 0x800, 0x6D09A0, 0, 0);
}
#endif
