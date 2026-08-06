#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 shi_win_yashi_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 shi_win_yashi_pal[] = {
#include "assets/shi_win_yashi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 shi_win_nuno_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 shi_win_nuno_tex_rgb_ci4_pal[] = {
#include "assets/shi_win_nuno_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 shi_win_w4_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 shi_win_w4_tex_rgb_ci4_pal[] = {
#include "assets/shi_win_w4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 shi_win_w1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 shi_win_w1_tex_rgb_ci4_pal[] = {
#include "assets/shi_win_w1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 shi_win_w2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 shi_win_w2_tex_rgb_ci4_pal[] = {
#include "assets/shi_win_w2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 shi_win_w3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 shi_win_w3_tex_rgb_ci4_pal[] = {
#include "assets/shi_win_w3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 mra_win_w1_tex[0x400];
#else
static u8 mra_win_w1_tex[] = {
#include "assets/shi_win/mra_win_w1_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 mra_win_w2_tex[0x400];
#else
static u8 mra_win_w2_tex[] = {
#include "assets/shi_win/mra_win_w2_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 mra_win_w3_tex[0x200];
#else
static u8 mra_win_w3_tex[] = {
#include "assets/shi_win/mra_win_w3_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 mra_win_w4_tex[0x400];
#else
static u8 mra_win_w4_tex[] = {
#include "assets/shi_win/mra_win_w4_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 mra_win_w5_tex[0x400];
#else
static u8 mra_win_w5_tex[] = {
#include "assets/shi_win/mra_win_w5_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 mra_win_fuki_tex[0x800];
#else
static u8 mra_win_fuki_tex[] = {
#include "assets/shi_win/mra_win_fuki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 shi_win_yashi_tex[0x800];
#else
u8 shi_win_yashi_tex[] = {
#include "assets/shi_win_yashi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 shi_win_yajirushi1_tex[0x400];
#else
u8 shi_win_yajirushi1_tex[] = {
#include "assets/shi_win_yajirushi1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 shi_win_yajirushi2_tex[0x100];
#else
u8 shi_win_yajirushi2_tex[] = {
#include "assets/shi_win_yajirushi2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 shi_win_nuno_tex_rgb_ci4[0x200];
#else
u8 shi_win_nuno_tex_rgb_ci4[] = {
#include "assets/shi_win_nuno_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 shi_win_w4_tex_rgb_ci4[0x80];
#else
u8 shi_win_w4_tex_rgb_ci4[] = {
#include "assets/shi_win_w4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 shi_win_w1_tex_rgb_ci4[0x400];
#else
u8 shi_win_w1_tex_rgb_ci4[] = {
#include "assets/shi_win_w1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 shi_win_w2_tex_rgb_ci4[0x400];
#else
u8 shi_win_w2_tex_rgb_ci4[] = {
#include "assets/shi_win_w2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 shi_win_w3_tex_rgb_ci4[0x200];
#else
u8 shi_win_w3_tex_rgb_ci4[] = {
#include "assets/shi_win_w3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx shi_win_v[0x670 / sizeof(Vtx)];
#else
Vtx shi_win_v[] = {
#include "assets/shi_win_v.inc"
};
#endif

Gfx shi_win_w11_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, shi_win_w4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, shi_win_w4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(shi_win_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx shi_win_yaji_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 80, 80, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, shi_win_yajirushi2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&shi_win_v[4], 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 128, 16, shi_win_yajirushi1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx shi_win_w1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, shi_win_w2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, shi_win_w2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&shi_win_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx shi_win_w2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, shi_win_w3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, shi_win_w3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&shi_win_v[16], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx shi_win_w3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, shi_win_w2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, shi_win_w2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&shi_win_v[20], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx shi_win_w4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, shi_win_w1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, shi_win_w1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&shi_win_v[24], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx shi_win_w5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, shi_win_w1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, shi_win_w1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&shi_win_v[28], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx shi_win_w6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, shi_win_w2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, shi_win_w2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&shi_win_v[32], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx shi_win_w7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, shi_win_w3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, shi_win_w3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&shi_win_v[36], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx shi_win_w8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, shi_win_w2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, shi_win_w2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&shi_win_v[40], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx shi_win_w9T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, shi_win_w1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, shi_win_w1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&shi_win_v[44], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx shi_win_w10T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, shi_win_w1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, shi_win_w1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&shi_win_v[48], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx shi_win_ueT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 205, 245, 235, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, mra_win_w5_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&shi_win_v[52], 24, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, mra_win_w4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 12, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, mra_win_w3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(23, 20, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, mra_win_w2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&shi_win_v[76], 19, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 1, 8, 9, 8, 10, 9, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, mra_win_w1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 11, 12, 13, 12, 14, 13, 15, 16, 17),
    gsSPNTriangles_5b(16, 18, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx shi_win_fukiT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 25, 60, 80, 180),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 128, 32, mra_win_fuki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&shi_win_v[95], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx shi_win_iconT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, shi_win_yashi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, shi_win_yashi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&shi_win_v[99], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx shi_win_mode[] = {
    gsDPLoadTLUT_Dolphin(14, 16, 1, shi_win_nuno_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, shi_win_nuno_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

Gfx shi_win_model[] = {
    gsSPDisplayList(shi_win_w1T_model),
    gsSPDisplayList(shi_win_w2T_model),
    gsSPDisplayList(shi_win_w3T_model),
    gsSPDisplayList(shi_win_w4T_model),
    gsSPDisplayList(shi_win_w5T_model),
    gsSPDisplayList(shi_win_w6T_model),
    gsSPDisplayList(shi_win_w7T_model),
    gsSPDisplayList(shi_win_w8T_model),
    gsSPDisplayList(shi_win_w9T_model),
    gsSPDisplayList(shi_win_w10T_model),
    gsSPDisplayList(shi_win_w11_model),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPDisplayList(shi_win_ueT_model),
    gsSPDisplayList(shi_win_fukiT_model),
    gsSPDisplayList(shi_win_yaji_model),
    gsSPDisplayList(shi_win_iconT_model),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_shi_win_c(void) {
    pc_load_asset("assets/shi_win/mra_win_w1_tex.bin", mra_win_w1_tex, 0x400, 0x742200, 0, 0);
    pc_load_asset("assets/shi_win/mra_win_w2_tex.bin", mra_win_w2_tex, 0x400, 0x742600, 0, 0);
    pc_load_asset("assets/shi_win/mra_win_w3_tex.bin", mra_win_w3_tex, 0x200, 0x742A00, 0, 0);
    pc_load_asset("assets/shi_win/mra_win_w4_tex.bin", mra_win_w4_tex, 0x400, 0x742C00, 0, 0);
    pc_load_asset("assets/shi_win/mra_win_w5_tex.bin", mra_win_w5_tex, 0x400, 0x743000, 0, 0);
    pc_load_asset("assets/shi_win/mra_win_fuki_tex.bin", mra_win_fuki_tex, 0x800, 0x743400, 0, 0);
}
#endif
