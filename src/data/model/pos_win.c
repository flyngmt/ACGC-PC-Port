#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 pos_win_nuno_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 pos_win_nuno_tex_rgb_ci4_pal[] = {
#include "assets/pos_win_nuno_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 pos_win_sw5_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 pos_win_sw5_tex_rgb_ci4_pal[] = {
#include "assets/pos_win_sw5_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 pos_win_sw1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 pos_win_sw1_tex_rgb_ci4_pal[] = {
#include "assets/pos_win_sw1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 pos_win_sw2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 pos_win_sw2_tex_rgb_ci4_pal[] = {
#include "assets/pos_win_sw2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 pos_win_sw3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 pos_win_sw3_tex_rgb_ci4_pal[] = {
#include "assets/pos_win_sw3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 pos_win_sw4_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 pos_win_sw4_tex_rgb_ci4_pal[] = {
#include "assets/pos_win_sw4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mwin_nwaku_tex[0x400];
#else
static u8 inv_mwin_nwaku_tex[] = {
#include "assets/pos_win/inv_mwin_nwaku_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 pos_win_w6_tex[0x80];
#else
u8 pos_win_w6_tex[] = {
#include "assets/pos_win_w6_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 pos_win_w1_tex[0x800];
#else
u8 pos_win_w1_tex[] = {
#include "assets/pos_win_w1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 pos_win_w2_tex[0x800];
#else
u8 pos_win_w2_tex[] = {
#include "assets/pos_win_w2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 pos_win_w3_tex[0x800];
#else
u8 pos_win_w3_tex[] = {
#include "assets/pos_win_w3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 pos_win_w4_tex[0x800];
#else
u8 pos_win_w4_tex[] = {
#include "assets/pos_win_w4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 pos_win_w5_tex[0x200];
#else
u8 pos_win_w5_tex[] = {
#include "assets/pos_win_w5_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 pos_win_post_tex[0x200];
#else
u8 pos_win_post_tex[] = {
#include "assets/pos_win_post_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 pos_win_nuno_tex_rgb_ci4[0x200];
#else
u8 pos_win_nuno_tex_rgb_ci4[] = {
#include "assets/pos_win_nuno_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 pos_win_sw5_tex_rgb_ci4[0x200];
#else
u8 pos_win_sw5_tex_rgb_ci4[] = {
#include "assets/pos_win_sw5_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 pos_win_sw1_tex_rgb_ci4[0x400];
#else
u8 pos_win_sw1_tex_rgb_ci4[] = {
#include "assets/pos_win_sw1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 pos_win_sw2_tex_rgb_ci4[0x400];
#else
u8 pos_win_sw2_tex_rgb_ci4[] = {
#include "assets/pos_win_sw2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 pos_win_sw3_tex_rgb_ci4[0x400];
#else
u8 pos_win_sw3_tex_rgb_ci4[] = {
#include "assets/pos_win_sw3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 pos_win_sw4_tex_rgb_ci4[0x400];
#else
u8 pos_win_sw4_tex_rgb_ci4[] = {
#include "assets/pos_win_sw4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx pos_win_v[0x610 / sizeof(Vtx)];
#else
Vtx pos_win_v[] = {
#include "assets/pos_win_v.inc"
};
#endif

Gfx pos_win_post_model[] = {
    gsDPSetPrimColor(0, 255, 0, 70, 250, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, pos_win_post_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(pos_win_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pos_win_w9_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pos_win_sw5_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, pos_win_sw5_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&pos_win_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pos_win_ue1T_model[] = {
    gsDPSetPrimColor(0, 255, 165, 165, 255, 255),
    gsDPSetEnvColor(255, 50, 50, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pos_win_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pos_win_ue2T_model[] = {
    gsDPSetPrimColor(0, 255, 100, 100, 225, 255),
    gsDPSetEnvColor(165, 165, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 32, pos_win_w5_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pos_win_v[12], 31, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, pos_win_w4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 11, 9, 8, 12, 11),
    gsSPNTriangles_5b(12, 13, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, pos_win_w3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(6, 14, 15, 16, 15, 17, 16, 18, 19, 20),
    gsSPNTriangles_5b(21, 18, 20, 22, 19, 23, 23, 24, 22, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, pos_win_w2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 25, 26, 27, 26, 28, 27, 29, 25, 30),
    gsSPNTriangles_5b(25, 27, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, pos_win_w1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pos_win_v[43], 11, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 0, 9, 0, 10, 9, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pos_win_ue3T_model[] = {
    gsDPSetPrimColor(0, 255, 165, 165, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, pos_win_w6_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pos_win_v[54], 11, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 2, 4, 5),
    gsSPNTriangles_5b(4, 6, 5, 7, 8, 9, 7, 10, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pos_win_w1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pos_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, pos_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pos_win_v[65], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pos_win_w2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pos_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, pos_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pos_win_v[69], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pos_win_w3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pos_win_sw4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, pos_win_sw4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pos_win_v[73], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pos_win_w4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pos_win_sw4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, pos_win_sw4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pos_win_v[77], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pos_win_w5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pos_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, pos_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pos_win_v[81], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pos_win_w6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pos_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, pos_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pos_win_v[85], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pos_win_w7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pos_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, pos_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pos_win_v[89], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pos_win_w8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, pos_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, pos_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&pos_win_v[93], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx pos_win_mode[] = {
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_TEX_EDGE2),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(14, 16, 1, pos_win_nuno_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, pos_win_nuno_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPEndDisplayList(),
};

Gfx pos_win_model[] = {
    gsSPDisplayList(pos_win_w1T_model),
    gsSPDisplayList(pos_win_w2T_model),
    gsSPDisplayList(pos_win_w3T_model),
    gsSPDisplayList(pos_win_w4T_model),
    gsSPDisplayList(pos_win_w5T_model),
    gsSPDisplayList(pos_win_w6T_model),
    gsSPDisplayList(pos_win_w7T_model),
    gsSPDisplayList(pos_win_w8T_model),
    gsSPDisplayList(pos_win_w9_model),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPDisplayList(pos_win_ue1T_model),
    gsSPDisplayList(pos_win_ue2T_model),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsSPDisplayList(pos_win_ue3T_model),
    gsSPDisplayList(pos_win_post_model),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_pos_win_c(void) {
    pc_load_asset("assets/pos_win/inv_mwin_nwaku_tex.bin", inv_mwin_nwaku_tex, 0x400, 0x786980, 0, 0);
}
#endif
