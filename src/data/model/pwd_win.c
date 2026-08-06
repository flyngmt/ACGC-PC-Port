#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 pwd_win_kagi2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 pwd_win_kagi2_pal[] = {
#include "assets/pwd_win_kagi2_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 pwd_win_nuno_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 pwd_win_nuno_tex_rgb_ci4_pal[] = {
#include "assets/pwd_win_nuno_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 pwd_win_w4_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 pwd_win_w4_tex_rgb_ci4_pal[] = {
#include "assets/pwd_win_w4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 pwd_win_w1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 pwd_win_w1_tex_rgb_ci4_pal[] = {
#include "assets/pwd_win_w1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 pwd_win_w2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 pwd_win_w2_tex_rgb_ci4_pal[] = {
#include "assets/pwd_win_w2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 pwd_win_w3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 pwd_win_w3_tex_rgb_ci4_pal[] = {
#include "assets/pwd_win_w3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 pwd_win_moji_tex[0x80];
#else
u8 pwd_win_moji_tex[] = {
#include "assets/pwd_win_moji_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 fkm_win_fuki2_tex[0x800];
#else
static u8 fkm_win_fuki2_tex[] = {
#include "assets/pwd_win/fkm_win_fuki2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 pwd_win_sw1_tex[0x400];
#else
u8 pwd_win_sw1_tex[] = {
#include "assets/pwd_win_sw1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 pwd_win_sw2_tex[0x400];
#else
u8 pwd_win_sw2_tex[] = {
#include "assets/pwd_win_sw2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 pwd_win_sw3_tex[0x200];
#else
u8 pwd_win_sw3_tex[] = {
#include "assets/pwd_win_sw3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 pwd_win_sw4_tex[0x80];
#else
u8 pwd_win_sw4_tex[] = {
#include "assets/pwd_win_sw4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 pwd_win_icon_tex[0x800];
#else
u8 pwd_win_icon_tex[] = {
#include "assets/pwd_win_icon_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 pwd_win_nuno_tex_rgb_ci4[0x200];
#else
u8 pwd_win_nuno_tex_rgb_ci4[] = {
#include "assets/pwd_win_nuno_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 pwd_win_w4_tex_rgb_ci4[0x80];
#else
u8 pwd_win_w4_tex_rgb_ci4[] = {
#include "assets/pwd_win_w4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 pwd_win_w1_tex_rgb_ci4[0x400];
#else
u8 pwd_win_w1_tex_rgb_ci4[] = {
#include "assets/pwd_win_w1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 pwd_win_w2_tex_rgb_ci4[0x400];
#else
u8 pwd_win_w2_tex_rgb_ci4[] = {
#include "assets/pwd_win_w2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 pwd_win_w3_tex_rgb_ci4[0x200];
#else
u8 pwd_win_w3_tex_rgb_ci4[] = {
#include "assets/pwd_win_w3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx pwd_win_v[0xE80 / sizeof(Vtx)];
#else
Vtx pwd_win_v[] = {
#include "assets/pwd_win_v.inc"
};
#endif

Gfx pwd_win_w11_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pwd_win_w4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, pwd_win_w4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(pwd_win_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pwd_win_ue_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, pwd_win_sw4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pwd_win_v[4], 28, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, pwd_win_sw3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 7, 4, 6, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, pwd_win_sw2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 12, 13, 14, 15, 12, 14, 16, 17, 18),
    gsSPNTriangles_5b(17, 19, 18, 20, 21, 22, 23, 20, 22, 24, 25, 26),
    gsSPNTriangles_5b(25, 27, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, pwd_win_sw1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pwd_win_v[32], 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 3),
    gsSPNTriangles_5b(1, 4, 3, 6, 7, 8, 9, 6, 8, 10, 9, 11),
    gsSPNTriangles_5b(9, 8, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pwd_win_fuki_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
    gsDPSetPrimColor(0, 255, 10, 10, 30, 180),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 128, 32, fkm_win_fuki2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pwd_win_v[44], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pwd_win_waku_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
    gsDPSetPrimColor(0, 255, 40, 40, 50, 255),
    gsSPVertex(&pwd_win_v[48], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pwd_win_moji_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 135, 135, 80, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, pwd_win_moji_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pwd_win_v[52], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pwd_win_sen_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
    gsDPSetPrimColor(0, 255, 90, 90, 100, 255),
    gsSPVertex(&pwd_win_v[56], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 9, 11, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pwd_win_sen2_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
    gsDPSetPrimColor(0, 255, 110, 110, 80, 180),
    gsSPVertex(&pwd_win_v[68], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 9, 10, 10, 11, 8, 12, 13, 14),
    gsSPNTriangles_5b(14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21, 22),
    gsSPNTriangles_5b(22, 23, 20, 24, 25, 26, 26, 27, 24, 28, 29, 30),
    gsSPNTriangles_5b(30, 31, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&pwd_win_v[100], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 9, 10, 10, 11, 8, 12, 13, 14),
    gsSPNTriangles_5b(14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21, 22),
    gsSPNTriangles_5b(22, 23, 20, 24, 25, 26, 26, 27, 24, 28, 29, 30),
    gsSPNTriangles_5b(30, 31, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&pwd_win_v[132], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 9, 10, 10, 11, 8, 12, 13, 14),
    gsSPNTriangles_5b(14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21, 22),
    gsSPNTriangles_5b(22, 23, 20, 24, 25, 26, 26, 27, 24, 28, 29, 30),
    gsSPNTriangles_5b(30, 31, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&pwd_win_v[164], 24, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pwd_win_w1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pwd_win_w1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, pwd_win_w1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pwd_win_v[188], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pwd_win_w2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pwd_win_w2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, pwd_win_w2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pwd_win_v[192], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pwd_win_w3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pwd_win_w3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, pwd_win_w3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pwd_win_v[196], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pwd_win_w4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pwd_win_w2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, pwd_win_w2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pwd_win_v[200], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pwd_win_w5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pwd_win_w1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, pwd_win_w1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pwd_win_v[204], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pwd_win_w6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pwd_win_w1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, pwd_win_w1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pwd_win_v[208], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pwd_win_w7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pwd_win_w2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, pwd_win_w2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pwd_win_v[212], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pwd_win_w8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pwd_win_w3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, pwd_win_w3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pwd_win_v[216], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pwd_win_w9T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pwd_win_w2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, pwd_win_w2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pwd_win_v[220], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pwd_win_w10T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pwd_win_w1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, pwd_win_w1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pwd_win_v[224], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pwd_win_iconT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, pwd_win_kagi2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, pwd_win_icon_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pwd_win_v[228], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pwd_win_mode[] = {
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_TEX_EDGE2),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(14, 16, 1, pwd_win_nuno_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, pwd_win_nuno_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pwd_win_model[] = {
    gsSPDisplayList(pwd_win_w1T_model),
    gsSPDisplayList(pwd_win_w2T_model),
    gsSPDisplayList(pwd_win_w3T_model),
    gsSPDisplayList(pwd_win_w4T_model),
    gsSPDisplayList(pwd_win_w5T_model),
    gsSPDisplayList(pwd_win_w6T_model),
    gsSPDisplayList(pwd_win_w7T_model),
    gsSPDisplayList(pwd_win_w8T_model),
    gsSPDisplayList(pwd_win_w9T_model),
    gsSPDisplayList(pwd_win_w10T_model),
    gsSPDisplayList(pwd_win_w11_model),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPDisplayList(pwd_win_ue_model),
    gsSPDisplayList(pwd_win_waku_model),
    gsSPDisplayList(pwd_win_fuki_model),
    gsSPDisplayList(pwd_win_moji_model),
    gsSPDisplayList(pwd_win_iconT_model),
    gsSPDisplayList(pwd_win_sen_model),
    gsSPDisplayList(pwd_win_sen2_model),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_pwd_win_c(void) {
    pc_load_asset("assets/pwd_win/fkm_win_fuki2_tex.bin", fkm_win_fuki2_tex, 0x800, 0x7AD9C0, 0, 0);
}
#endif
