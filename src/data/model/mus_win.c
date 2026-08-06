#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 mus_win_nuno_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 mus_win_nuno_tex_rgb_ci4_pal[] = {
#include "assets/mus_win_nuno_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 mus_win_sw4_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 mus_win_sw4_tex_rgb_ci4_pal[] = {
#include "assets/mus_win_sw4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 mus_win_sw1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 mus_win_sw1_tex_rgb_ci4_pal[] = {
#include "assets/mus_win_sw1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 mus_win_sw2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 mus_win_sw2_tex_rgb_ci4_pal[] = {
#include "assets/mus_win_sw2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 mus_win_sw3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 mus_win_sw3_tex_rgb_ci4_pal[] = {
#include "assets/mus_win_sw3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mwin_nwaku_tex[0x400];
#else
static u8 inv_mwin_nwaku_tex[] = {
#include "assets/mus_win/inv_mwin_nwaku_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 mus_win_w1_tex[0x400];
#else
u8 mus_win_w1_tex[] = {
#include "assets/mus_win_w1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 mus_win_w2_tex[0x800];
#else
u8 mus_win_w2_tex[] = {
#include "assets/mus_win_w2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 mus_win_w3_tex[0x800];
#else
u8 mus_win_w3_tex[] = {
#include "assets/mus_win_w3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 mus_win_w4_tex[0x400];
#else
u8 mus_win_w4_tex[] = {
#include "assets/mus_win_w4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 mus_win_w5_tex[0x100];
#else
u8 mus_win_w5_tex[] = {
#include "assets/mus_win_w5_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 mus_win_nuno_tex_rgb_ci4[0x200];
#else
u8 mus_win_nuno_tex_rgb_ci4[] = {
#include "assets/mus_win_nuno_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 mus_win_sw4_tex_rgb_ci4[0x80];
#else
u8 mus_win_sw4_tex_rgb_ci4[] = {
#include "assets/mus_win_sw4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 mus_win_sw1_tex_rgb_ci4[0x400];
#else
u8 mus_win_sw1_tex_rgb_ci4[] = {
#include "assets/mus_win_sw1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 mus_win_sw2_tex_rgb_ci4[0x400];
#else
u8 mus_win_sw2_tex_rgb_ci4[] = {
#include "assets/mus_win_sw2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 mus_win_sw3_tex_rgb_ci4[0x400];
#else
u8 mus_win_sw3_tex_rgb_ci4[] = {
#include "assets/mus_win_sw3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx mus_win_v[0x760 / sizeof(Vtx)];
#else
Vtx mus_win_v[] = {
#include "assets/mus_win_v.inc"
};
#endif

Gfx mus_win_sw13_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, mus_win_sw4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(mus_win_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx mus_win_sw1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, mus_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mus_win_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx mus_win_sw2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, mus_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mus_win_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx mus_win_sw3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, mus_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mus_win_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx mus_win_sw4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, mus_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mus_win_v[16], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx mus_win_sw5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mus_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mus_win_v[20], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx mus_win_sw6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mus_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mus_win_v[24], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx mus_win_sw7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, mus_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mus_win_v[28], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx mus_win_sw8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, mus_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mus_win_v[32], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx mus_win_sw9T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, mus_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mus_win_v[36], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx mus_win_sw10T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, mus_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mus_win_v[40], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx mus_win_sw11T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mus_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mus_win_v[44], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx mus_win_sw12T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mus_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mus_win_v[48], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx mus_win_ueT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 0, 0, 0, 255),
    gsDPSetEnvColor(110, 105, 110, 255),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, mus_win_w5_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&mus_win_v[52], 16, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, mus_win_w4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, mus_win_w3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&mus_win_v[68], 26, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 12, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, mus_win_w2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(6, 16, 17, 18, 16, 19, 17, 20, 21, 19),
    gsSPNTriangles_5b(20, 19, 16, 22, 23, 24, 22, 25, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, mus_win_w1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&mus_win_v[94], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx mus_win_ue2T_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 110, 105, 110, 255),
    gsDPSetEnvColor(40, 60, 70, 255),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&mus_win_v[110], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx mus_win_model_before[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(14, 16, 1, mus_win_nuno_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, mus_win_nuno_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

Gfx mus_win_model[] = {
    gsSPDisplayList(mus_win_sw13_model),  gsSPDisplayList(mus_win_sw1T_model),
    gsSPDisplayList(mus_win_sw2T_model),  gsSPDisplayList(mus_win_sw3T_model),
    gsSPDisplayList(mus_win_sw4T_model),  gsSPDisplayList(mus_win_sw5T_model),
    gsSPDisplayList(mus_win_sw6T_model),  gsSPDisplayList(mus_win_sw7T_model),
    gsSPDisplayList(mus_win_sw8T_model),  gsSPDisplayList(mus_win_sw9T_model),
    gsSPDisplayList(mus_win_sw10T_model), gsSPDisplayList(mus_win_sw11T_model),
    gsSPDisplayList(mus_win_sw12T_model), gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_mus_win_c(void) {
    pc_load_asset("assets/mus_win/inv_mwin_nwaku_tex.bin", inv_mwin_nwaku_tex, 0x400, 0x7982E0, 0, 0);
}
#endif
