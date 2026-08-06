#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 fkm_win_house_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 fkm_win_house_pal[] = {
#include "assets/fkm_win_house_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 fkm_win_ie_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 fkm_win_ie_tex_rgb_ci4_pal[] = {
#include "assets/fkm_win_ie_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 fkm_win_sw1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 fkm_win_sw1_tex_rgb_ci4_pal[] = {
#include "assets/fkm_win_sw1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 fkm_win_sw2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 fkm_win_sw2_tex_rgb_ci4_pal[] = {
#include "assets/fkm_win_sw2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 fkm_win_sw3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 fkm_win_sw3_tex_rgb_ci4_pal[] = {
#include "assets/fkm_win_sw3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 fri_win_owe_tex[0x300];
#else
u8 fri_win_owe_tex[] = {
#include "assets/fri_win_owe_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 fkm_win_fuki2_tex[0x800];
#else
static u8 fkm_win_fuki2_tex[] = {
#include "assets/fkm_win/fkm_win_fuki2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 fri_win_payment_tex[0x200];
#else
u8 fri_win_payment_tex[] = {
#include "assets/fri_win_payment_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 fri_win_cash_tex[0x200];
#else
static u8 fri_win_cash_tex[] = {
#include "assets/fkm_win/fri_win_cash_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 fri_win_bell_tex[0x100];
#else
static u8 fri_win_bell_tex[] = {
#include "assets/fkm_win/fri_win_bell_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 fkm_win_house_tex[0x800];
#else
u8 fkm_win_house_tex[] = {
#include "assets/fkm_win_house_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 fkm_win_sen_tex[0x80];
#else
u8 fkm_win_sen_tex[] = {
#include "assets/fkm_win_sen_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 fkm_win_w4_tex[0x80];
#else
static u8 fkm_win_w4_tex[] = {
#include "assets/fkm_win/fkm_win_w4_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 fkm_win_w3_tex[0x200];
#else
static u8 fkm_win_w3_tex[] = {
#include "assets/fkm_win/fkm_win_w3_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 fkm_win_w2_tex[0x200];
#else
static u8 fkm_win_w2_tex[] = {
#include "assets/fkm_win/fkm_win_w2_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 fkm_win_w1_tex[0x400];
#else
static u8 fkm_win_w1_tex[] = {
#include "assets/fkm_win/fkm_win_w1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 fkm_win_ie_tex_rgb_ci4[0x200];
#else
u8 fkm_win_ie_tex_rgb_ci4[] = {
#include "assets/fkm_win_ie_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 fkm_win_sw1_tex_rgb_ci4[0x400];
#else
u8 fkm_win_sw1_tex_rgb_ci4[] = {
#include "assets/fkm_win_sw1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 fkm_win_sw2_tex_rgb_ci4[0x400];
#else
u8 fkm_win_sw2_tex_rgb_ci4[] = {
#include "assets/fkm_win_sw2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 fkm_win_sw3_tex_rgb_ci4[0x400];
#else
u8 fkm_win_sw3_tex_rgb_ci4[] = {
#include "assets/fkm_win_sw3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx fkm_win_v[0x740 / sizeof(Vtx)];
#else
Vtx fkm_win_v[] = {
#include "assets/fkm_win_v.inc"
};
#endif

Gfx fkm_win_moji_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 100, 60, 60, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, fri_win_bell_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(fkm_win_v, 24, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 9, 11, 10, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, fri_win_cash_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 13, 15, 14, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, fri_win_payment_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 17, 19, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 96, 16, fri_win_owe_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 21, 23, 22, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx fkm_win_fuki_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 185, 50, 165, 180),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 128, 32, fkm_win_fuki2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&fkm_win_v[24], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx fkm_win_wakuT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 225, 245, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, fkm_win_w1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&fkm_win_v[28], 24, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 12, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, fkm_win_w2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 19, 16, 18, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, fkm_win_w3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&fkm_win_v[52], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 3, 9, 3, 2, 9, 4, 10, 5),
    gsSPNTriangles_5b(10, 11, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, fkm_win_w4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 13, 15, 14, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx fkm_win_iconT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, fkm_win_house_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, fkm_win_house_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&fkm_win_v[68], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx fkm_win_senT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 160, 110, 110, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, fkm_win_sen_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&fkm_win_v[72], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx fkm_win_sw1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, fkm_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, fkm_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&fkm_win_v[76], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx fkm_win_sw2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, fkm_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, fkm_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&fkm_win_v[80], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx fkm_win_sw3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, fkm_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, fkm_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&fkm_win_v[84], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx fkm_win_sw4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, fkm_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, fkm_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&fkm_win_v[88], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx fkm_win_sw5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, fkm_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, fkm_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&fkm_win_v[92], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx fkm_win_sw6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, fkm_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, fkm_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&fkm_win_v[96], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx fkm_win_sw7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, fkm_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, fkm_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&fkm_win_v[100], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx fkm_win_sw8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, fkm_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, fkm_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&fkm_win_v[104], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx fkm_win_sw9T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, fkm_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, fkm_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&fkm_win_v[108], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx fkm_win_sw10T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, fkm_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, fkm_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&fkm_win_v[112], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx fkm_win_mode[] = {
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_TEX_EDGE2),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(14, 16, 1, fkm_win_ie_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, fkm_win_ie_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

Gfx fkm_win_model[] = {
    gsSPDisplayList(fkm_win_sw1T_model),  gsSPDisplayList(fkm_win_sw2T_model),
    gsSPDisplayList(fkm_win_sw3T_model),  gsSPDisplayList(fkm_win_sw4T_model),
    gsSPDisplayList(fkm_win_sw5T_model),  gsSPDisplayList(fkm_win_sw6T_model),
    gsSPDisplayList(fkm_win_sw7T_model),  gsSPDisplayList(fkm_win_sw8T_model),
    gsSPDisplayList(fkm_win_sw9T_model),  gsSPDisplayList(fkm_win_sw10T_model),
    gsDPSetCycleType(G_CYC_1CYCLE),       gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPDisplayList(fkm_win_wakuT_model), gsSPDisplayList(fkm_win_fuki_model),
    gsSPDisplayList(fkm_win_moji_model),  gsSPDisplayList(fkm_win_iconT_model),
    gsSPDisplayList(fkm_win_senT_model),  gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_fkm_win_c(void) {
    pc_load_asset("assets/fkm_win/fkm_win_fuki2_tex.bin", fkm_win_fuki2_tex, 0x800, 0x7B5540, 0, 0);
    pc_load_asset("assets/fkm_win/fri_win_cash_tex.bin", fri_win_cash_tex, 0x200, 0x7B5F40, 0, 0);
    pc_load_asset("assets/fkm_win/fri_win_bell_tex.bin", fri_win_bell_tex, 0x100, 0x7B6140, 0, 0);
    pc_load_asset("assets/fkm_win/fkm_win_w4_tex.bin", fkm_win_w4_tex, 0x80, 0x7B6AC0, 0, 0);
    pc_load_asset("assets/fkm_win/fkm_win_w3_tex.bin", fkm_win_w3_tex, 0x200, 0x7B6B40, 0, 0);
    pc_load_asset("assets/fkm_win/fkm_win_w2_tex.bin", fkm_win_w2_tex, 0x200, 0x7B6D40, 0, 0);
    pc_load_asset("assets/fkm_win/fkm_win_w1_tex.bin", fkm_win_w1_tex, 0x400, 0x7B6F40, 0, 0);
}
#endif
