#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 dna_win_icon_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 dna_win_icon_pal[] = {
#include "assets/dna_win_icon_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 dna_win_nuno_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 dna_win_nuno_tex_rgb_ci4_pal[] = {
#include "assets/dna_win_nuno_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 dna_win_sw4_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 dna_win_sw4_tex_rgb_ci4_pal[] = {
#include "assets/dna_win_sw4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 dna_win_sw1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 dna_win_sw1_tex_rgb_ci4_pal[] = {
#include "assets/dna_win_sw1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 dna_win_sw2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 dna_win_sw2_tex_rgb_ci4_pal[] = {
#include "assets/dna_win_sw2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 dna_win_sw3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 dna_win_sw3_tex_rgb_ci4_pal[] = {
#include "assets/dna_win_sw3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 nam_win_fuki_tex[0x800];
#else
static u8 nam_win_fuki_tex[] = {
#include "assets/dna_win/nam_win_fuki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 dna_win_aw1_tex[0x400];
#else
u8 dna_win_aw1_tex[] = {
#include "assets/dna_win_aw1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 dna_win_aw2_tex[0x400];
#else
u8 dna_win_aw2_tex[] = {
#include "assets/dna_win_aw2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 dna_win_aw3_tex[0x200];
#else
u8 dna_win_aw3_tex[] = {
#include "assets/dna_win_aw3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 dna_win_icon_tex[0x800];
#else
u8 dna_win_icon_tex[] = {
#include "assets/dna_win_icon_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 dna_win_batu_tex[0x100];
#else
u8 dna_win_batu_tex[] = {
#include "assets/dna_win_batu_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 dna_win_aw4_tex[0x80];
#else
u8 dna_win_aw4_tex[] = {
#include "assets/dna_win_aw4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 dna_win_nuno_tex_rgb_ci4[0x200];
#else
u8 dna_win_nuno_tex_rgb_ci4[] = {
#include "assets/dna_win_nuno_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 dna_win_sw4_tex_rgb_ci4[0x200];
#else
u8 dna_win_sw4_tex_rgb_ci4[] = {
#include "assets/dna_win_sw4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 dna_win_sw1_tex_rgb_ci4[0x400];
#else
u8 dna_win_sw1_tex_rgb_ci4[] = {
#include "assets/dna_win_sw1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 dna_win_sw2_tex_rgb_ci4[0x400];
#else
u8 dna_win_sw2_tex_rgb_ci4[] = {
#include "assets/dna_win_sw2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 dna_win_sw3_tex_rgb_ci4[0x200];
#else
u8 dna_win_sw3_tex_rgb_ci4[] = {
#include "assets/dna_win_sw3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx dna_win_v[0x600 / sizeof(Vtx)];
#else
Vtx dna_win_v[] = {
#include "assets/dna_win_v.inc"
};
#endif

Gfx dna_win_w11_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, dna_win_sw4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, dna_win_sw4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(dna_win_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx dna_win_ue_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 245, 245, 175, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, dna_win_aw4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&dna_win_v[4], 28, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, dna_win_aw3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 7, 4, 6, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, dna_win_aw2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 12, 13, 14, 15, 12, 14, 16, 17, 18),
    gsSPNTriangles_5b(17, 19, 18, 20, 21, 22, 23, 20, 22, 24, 25, 26),
    gsSPNTriangles_5b(25, 27, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, dna_win_aw1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&dna_win_v[32], 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 3),
    gsSPNTriangles_5b(1, 4, 3, 6, 7, 8, 9, 6, 8, 10, 9, 11),
    gsSPNTriangles_5b(9, 8, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx dna_win_w1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, dna_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, dna_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&dna_win_v[44], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx dna_win_w2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, dna_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, dna_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&dna_win_v[48], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx dna_win_w3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, dna_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, dna_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&dna_win_v[52], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx dna_win_w4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, dna_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, dna_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&dna_win_v[56], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx dna_win_w5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, dna_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, dna_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&dna_win_v[60], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx dna_win_w6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, dna_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, dna_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&dna_win_v[64], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx dna_win_w7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, dna_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, dna_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&dna_win_v[68], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx dna_win_w8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, dna_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, dna_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&dna_win_v[72], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx dna_win_w9T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, dna_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, dna_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&dna_win_v[76], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx dna_win_w10T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, dna_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, dna_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&dna_win_v[80], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx dna_win_fukiT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 30, 20, 10, 180),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 128, 32, nam_win_fuki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&dna_win_v[84], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx dna_win_iconT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, dna_win_icon_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, dna_win_icon_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&dna_win_v[88], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx dna_win_garaT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 210, 100, 60, 255),
    gsDPSetEnvColor(110, 70, 90, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, dna_win_batu_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&dna_win_v[92], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx dna_win_mode[] = {
    gsDPLoadTLUT_Dolphin(14, 16, 1, dna_win_nuno_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, dna_win_nuno_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

Gfx dna_win_model[] = {
    gsSPDisplayList(dna_win_w1T_model),
    gsSPDisplayList(dna_win_w2T_model),
    gsSPDisplayList(dna_win_w3T_model),
    gsSPDisplayList(dna_win_w4T_model),
    gsSPDisplayList(dna_win_w5T_model),
    gsSPDisplayList(dna_win_w6T_model),
    gsSPDisplayList(dna_win_w7T_model),
    gsSPDisplayList(dna_win_w8T_model),
    gsSPDisplayList(dna_win_w9T_model),
    gsSPDisplayList(dna_win_w10T_model),
    gsSPDisplayList(dna_win_w11_model),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPDisplayList(dna_win_ue_model),
    gsSPDisplayList(dna_win_fukiT_model),
    gsSPDisplayList(dna_win_garaT_model),
    gsSPDisplayList(dna_win_iconT_model),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_dna_win_c(void) {
    pc_load_asset("assets/dna_win/nam_win_fuki_tex.bin", nam_win_fuki_tex, 0x800, 0x739F60, 0, 0);
}
#endif
