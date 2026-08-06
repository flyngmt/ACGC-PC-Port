#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 rst_win_kao2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 rst_win_kao2_pal[] = {
#include "assets/rst_win_kao2_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 rst_win_bittkuri_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 rst_win_bittkuri_tex_rgb_ci4_pal[] = {
#include "assets/rst_win_bittkuri_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 rst_win_sw4_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 rst_win_sw4_tex_rgb_ci4_pal[] = {
#include "assets/rst_win_sw4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 rst_win_sw1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 rst_win_sw1_tex_rgb_ci4_pal[] = {
#include "assets/rst_win_sw1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 rst_win_sw2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 rst_win_sw2_tex_rgb_ci4_pal[] = {
#include "assets/rst_win_sw2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 rst_win_sw3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 rst_win_sw3_tex_rgb_ci4_pal[] = {
#include "assets/rst_win_sw3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 rst_win_kagi2_tex[0x80];
#else
u8 rst_win_kagi2_tex[] = {
#include "assets/rst_win_kagi2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rst_win_seri_tex[0x400];
#else
u8 rst_win_seri_tex[] = {
#include "assets/rst_win_seri_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 req_win_w1_tex[0x400];
#else
static u8 req_win_w1_tex[] = {
#include "assets/rst_win/req_win_w1_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 req_win_w2_tex[0x400];
#else
static u8 req_win_w2_tex[] = {
#include "assets/rst_win/req_win_w2_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 req_win_w3_tex[0x200];
#else
static u8 req_win_w3_tex[] = {
#include "assets/rst_win/req_win_w3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rst_win_kao_tex[0x800];
#else
u8 rst_win_kao_tex[] = {
#include "assets/rst_win_kao_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rst_win_kagi1_tex[0x80];
#else
u8 rst_win_kagi1_tex[] = {
#include "assets/rst_win_kagi1_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 req_win_w4_tex[0x80];
#else
static u8 req_win_w4_tex[] = {
#include "assets/rst_win/req_win_w4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rst_win_bittkuri_tex_rgb_ci4[0x200];
#else
u8 rst_win_bittkuri_tex_rgb_ci4[] = {
#include "assets/rst_win_bittkuri_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 rst_win_sw4_tex_rgb_ci4[0x200];
#else
u8 rst_win_sw4_tex_rgb_ci4[] = {
#include "assets/rst_win_sw4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 rst_win_sw1_tex_rgb_ci4[0x400];
#else
u8 rst_win_sw1_tex_rgb_ci4[] = {
#include "assets/rst_win_sw1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 rst_win_sw2_tex_rgb_ci4[0x400];
#else
u8 rst_win_sw2_tex_rgb_ci4[] = {
#include "assets/rst_win_sw2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 rst_win_sw3_tex_rgb_ci4[0x200];
#else
u8 rst_win_sw3_tex_rgb_ci4[] = {
#include "assets/rst_win_sw3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx rst_win_v[0x680 / sizeof(Vtx)];
#else
Vtx rst_win_v[] = {
#include "assets/rst_win_v.inc"
};
#endif

Gfx rst_win_fuki_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 30, 30, 20, 180),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, rst_win_seri_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(rst_win_v, 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rst_win_waku11_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, rst_win_sw4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rst_win_sw4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rst_win_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rst_win_ueT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 200, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, req_win_w4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rst_win_v[12], 28, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, req_win_w3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 7, 4, 6, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, req_win_w2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 12, 13, 14, 15, 12, 14, 16, 17, 18),
    gsSPNTriangles_5b(17, 19, 18, 20, 21, 22, 23, 20, 22, 24, 25, 26),
    gsSPNTriangles_5b(25, 27, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, req_win_w1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rst_win_v[40], 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 3),
    gsSPNTriangles_5b(1, 4, 3, 6, 7, 8, 9, 6, 8, 10, 9, 11),
    gsSPNTriangles_5b(9, 8, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rst_win_kaoT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rst_win_kao2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rst_win_kao_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&rst_win_v[52], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rst_win_kagiT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 40, 150, 40, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, rst_win_kagi1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rst_win_v[56], 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, rst_win_kagi2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rst_win_waku1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, rst_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, rst_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rst_win_v[64], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rst_win_waku2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, rst_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, rst_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rst_win_v[68], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rst_win_waku3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, rst_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rst_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rst_win_v[72], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rst_win_waku4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, rst_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, rst_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rst_win_v[76], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rst_win_waku5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, rst_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, rst_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rst_win_v[80], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rst_win_waku6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, rst_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, rst_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rst_win_v[84], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rst_win_waku7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, rst_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, rst_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rst_win_v[88], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rst_win_waku8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, rst_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rst_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rst_win_v[92], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rst_win_waku9T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, rst_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, rst_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rst_win_v[96], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rst_win_waku10T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, rst_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, rst_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rst_win_v[100], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx ledit_common_mode[] = {
    gsDPPipeSync(),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_TEX_EDGE2),
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
};

Gfx rst_win_mode[] = {
    gsDPLoadTLUT_Dolphin(14, 16, 1, rst_win_bittkuri_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rst_win_bittkuri_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rst_win_model[] = {
    gsSPDisplayList(rst_win_waku1T_model),
    gsSPDisplayList(rst_win_waku2T_model),
    gsSPDisplayList(rst_win_waku3T_model),
    gsSPDisplayList(rst_win_waku4T_model),
    gsSPDisplayList(rst_win_waku5T_model),
    gsSPDisplayList(rst_win_waku6T_model),
    gsSPDisplayList(rst_win_waku7T_model),
    gsSPDisplayList(rst_win_waku8T_model),
    gsSPDisplayList(rst_win_waku9T_model),
    gsSPDisplayList(rst_win_waku10T_model),
    gsSPDisplayList(rst_win_waku11_model),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPDisplayList(rst_win_ueT_model),
    gsSPDisplayList(rst_win_fuki_model),
    gsSPDisplayList(rst_win_kaoT_model),
    gsSPDisplayList(rst_win_kagiT_model),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_rst_win_c(void) {
    pc_load_asset("assets/rst_win/req_win_w1_tex.bin", req_win_w1_tex, 0x400, 0x750860, 0, 0);
    pc_load_asset("assets/rst_win/req_win_w2_tex.bin", req_win_w2_tex, 0x400, 0x750C60, 0, 0);
    pc_load_asset("assets/rst_win/req_win_w3_tex.bin", req_win_w3_tex, 0x200, 0x751060, 0, 0);
    pc_load_asset("assets/rst_win/req_win_w4_tex.bin", req_win_w4_tex, 0x80, 0x751AE0, 0, 0);
}
#endif
