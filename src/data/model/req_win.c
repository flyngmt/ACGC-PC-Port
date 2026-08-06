#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 req_win_kao_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 req_win_kao_pal[] = {
#include "assets/req_win_kao_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 req_win_nuno_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 req_win_nuno_tex_rgb_ci4_pal[] = {
#include "assets/req_win_nuno_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 req_win_sw4_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 req_win_sw4_tex_rgb_ci4_pal[] = {
#include "assets/req_win_sw4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 req_win_sw1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 req_win_sw1_tex_rgb_ci4_pal[] = {
#include "assets/req_win_sw1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 req_win_sw2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 req_win_sw2_tex_rgb_ci4_pal[] = {
#include "assets/req_win_sw2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 req_win_sw3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 req_win_sw3_tex_rgb_ci4_pal[] = {
#include "assets/req_win_sw3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 req_win_fuki_tex[0x800];
#else
u8 req_win_fuki_tex[] = {
#include "assets/req_win_fuki_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 req_win_w1_tex[0x400];
#else
static u8 req_win_w1_tex[] = {
#include "assets/req_win/req_win_w1_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 req_win_w2_tex[0x400];
#else
static u8 req_win_w2_tex[] = {
#include "assets/req_win/req_win_w2_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 req_win_w3_tex[0x200];
#else
static u8 req_win_w3_tex[] = {
#include "assets/req_win/req_win_w3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 req_win_kao_tex[0x800];
#else
u8 req_win_kao_tex[] = {
#include "assets/req_win_kao_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 req_win_sen2_tex[0xC00];
#else
u8 req_win_sen2_tex[] = {
#include "assets/req_win_sen2_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 req_win_w4_tex[0x80];
#else
static u8 req_win_w4_tex[] = {
#include "assets/req_win/req_win_w4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 req_win_nuno_tex_rgb_ci4[0x200];
#else
u8 req_win_nuno_tex_rgb_ci4[] = {
#include "assets/req_win_nuno_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 req_win_sw4_tex_rgb_ci4[0x200];
#else
u8 req_win_sw4_tex_rgb_ci4[] = {
#include "assets/req_win_sw4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 req_win_sw1_tex_rgb_ci4[0x400];
#else
u8 req_win_sw1_tex_rgb_ci4[] = {
#include "assets/req_win_sw1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 req_win_sw2_tex_rgb_ci4[0x400];
#else
u8 req_win_sw2_tex_rgb_ci4[] = {
#include "assets/req_win_sw2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 req_win_sw3_tex_rgb_ci4[0x200];
#else
u8 req_win_sw3_tex_rgb_ci4[] = {
#include "assets/req_win_sw3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx req_win_v[0x600 / sizeof(Vtx)];
#else
Vtx req_win_v[] = {
#include "assets/req_win_v.inc"
};
#endif

Gfx req_win_req_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 235, 50, 140, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 192, 32, req_win_sen2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(req_win_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx req_win_w11_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, req_win_sw4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, req_win_sw4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&req_win_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx req_win_ueT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 205, 205, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, req_win_w4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&req_win_v[8], 28, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, req_win_w3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 5, 7, 6, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, req_win_w2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 12, 13, 14, 13, 15, 14, 16, 17, 18),
    gsSPNTriangles_5b(17, 19, 18, 20, 21, 22, 21, 23, 22, 24, 25, 26),
    gsSPNTriangles_5b(25, 27, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, req_win_w1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&req_win_v[36], 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 0, 9, 0, 2, 9, 10, 11, 5),
    gsSPNTriangles_5b(5, 4, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx req_win_fukiT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 30, 30, 55, 180),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 128, 32, req_win_fuki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&req_win_v[48], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx req_win_iconT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, req_win_kao_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, req_win_kao_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&req_win_v[52], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx req_win_w1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, req_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, req_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&req_win_v[56], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx req_win_w2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, req_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, req_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&req_win_v[60], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx req_win_w3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, req_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, req_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&req_win_v[64], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx req_win_w4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, req_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, req_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&req_win_v[68], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx req_win_w5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, req_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, req_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&req_win_v[72], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx req_win_w6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, req_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, req_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&req_win_v[76], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx req_win_w7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, req_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, req_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&req_win_v[80], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx req_win_w8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, req_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, req_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&req_win_v[84], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx req_win_w9T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, req_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, req_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&req_win_v[88], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx req_win_w10T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, req_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, req_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&req_win_v[92], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx req_win_mode[] = {
    gsDPLoadTLUT_Dolphin(14, 16, 1, req_win_nuno_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, req_win_nuno_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

Gfx req_win_model[] = {
    gsSPDisplayList(req_win_w1T_model),
    gsSPDisplayList(req_win_w2T_model),
    gsSPDisplayList(req_win_w3T_model),
    gsSPDisplayList(req_win_w4T_model),
    gsSPDisplayList(req_win_w5T_model),
    gsSPDisplayList(req_win_w6T_model),
    gsSPDisplayList(req_win_w7T_model),
    gsSPDisplayList(req_win_w8T_model),
    gsSPDisplayList(req_win_w9T_model),
    gsSPDisplayList(req_win_w10T_model),
    gsSPDisplayList(req_win_w11_model),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPDisplayList(req_win_ueT_model),
    gsSPDisplayList(req_win_fukiT_model),
    gsSPDisplayList(req_win_req_model),
    gsSPDisplayList(req_win_iconT_model),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_req_win_c(void) {
    pc_load_asset("assets/req_win/req_win_w1_tex.bin", req_win_w1_tex, 0x400, 0x750860, 0, 0);
    pc_load_asset("assets/req_win/req_win_w2_tex.bin", req_win_w2_tex, 0x400, 0x750C60, 0, 0);
    pc_load_asset("assets/req_win/req_win_w3_tex.bin", req_win_w3_tex, 0x200, 0x74D460, 0, 0);
    pc_load_asset("assets/req_win/req_win_w4_tex.bin", req_win_w4_tex, 0x80, 0x74EA60, 0, 0);
}
#endif
