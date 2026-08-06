#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 hni_nwin2_hani_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 hni_nwin2_hani_tex_rgb_ci4_pal[] = {
#include "assets/hni_nwin2_hani_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 hni_win_shita7_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 hni_win_shita7_tex_rgb_ci4_pal[] = {
#include "assets/hni_win_shita7_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 hni_win_shita1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 hni_win_shita1_tex_rgb_ci4_pal[] = {
#include "assets/hni_win_shita1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 hni_win_shita2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 hni_win_shita2_tex_rgb_ci4_pal[] = {
#include "assets/hni_win_shita2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 hni_win_shita3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 hni_win_shita3_tex_rgb_ci4_pal[] = {
#include "assets/hni_win_shita3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 hni_win_shita4_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 hni_win_shita4_tex_rgb_ci4_pal[] = {
#include "assets/hni_win_shita4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 hni_win_shita5_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 hni_win_shita5_tex_rgb_ci4_pal[] = {
#include "assets/hni_win_shita5_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 hni_win_shita6_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 hni_win_shita6_tex_rgb_ci4_pal[] = {
#include "assets/hni_win_shita6_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mwin_nwaku_tex[0x400];
#else
static u8 inv_mwin_nwaku_tex[] = {
#include "assets/hni_win/inv_mwin_nwaku_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 hni_nwin2_w_tex[0xA00];
#else
u8 hni_nwin2_w_tex[] = {
#include "assets/hni_nwin2_w_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 hni_win_ue1_tex[0x800];
#else
u8 hni_win_ue1_tex[] = {
#include "assets/hni_win_ue1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 hni_win_ue2_tex[0x800];
#else
u8 hni_win_ue2_tex[] = {
#include "assets/hni_win_ue2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 hni_win_ue3_tex[0x400];
#else
u8 hni_win_ue3_tex[] = {
#include "assets/hni_win_ue3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 hni_win_ue4_tex[0x100];
#else
u8 hni_win_ue4_tex[] = {
#include "assets/hni_win_ue4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 hni_win_ue5_tex[0x800];
#else
u8 hni_win_ue5_tex[] = {
#include "assets/hni_win_ue5_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 hni_win_ue6_tex[0x800];
#else
u8 hni_win_ue6_tex[] = {
#include "assets/hni_win_ue6_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 hni_win_ue7_tex[0x800];
#else
u8 hni_win_ue7_tex[] = {
#include "assets/hni_win_ue7_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 inv_mwin_3Dma_tex[0x800];
#else
static u8 inv_mwin_3Dma_tex[] = {
#include "assets/hni_win/inv_mwin_3Dma_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 hni_nwin2_hani_tex_rgb_ci4[0x200];
#else
u8 hni_nwin2_hani_tex_rgb_ci4[] = {
#include "assets/hni_nwin2_hani_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 hni_win_shita7_tex_rgb_ci4[0x200];
#else
u8 hni_win_shita7_tex_rgb_ci4[] = {
#include "assets/hni_win_shita7_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 hni_win_shita1_tex_rgb_ci4[0x400];
#else
u8 hni_win_shita1_tex_rgb_ci4[] = {
#include "assets/hni_win_shita1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 hni_win_shita2_tex_rgb_ci4[0x400];
#else
u8 hni_win_shita2_tex_rgb_ci4[] = {
#include "assets/hni_win_shita2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 hni_win_shita3_tex_rgb_ci4[0x200];
#else
u8 hni_win_shita3_tex_rgb_ci4[] = {
#include "assets/hni_win_shita3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 hni_win_shita4_tex_rgb_ci4[0x400];
#else
u8 hni_win_shita4_tex_rgb_ci4[] = {
#include "assets/hni_win_shita4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 hni_win_shita5_tex_rgb_ci4[0x400];
#else
u8 hni_win_shita5_tex_rgb_ci4[] = {
#include "assets/hni_win_shita5_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 hni_win_shita6_tex_rgb_ci4[0x400];
#else
u8 hni_win_shita6_tex_rgb_ci4[] = {
#include "assets/hni_win_shita6_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx hni_win_v[0x800 / sizeof(Vtx)];
#else
Vtx hni_win_v[] = {
#include "assets/hni_win_v.inc"
};
#endif

Gfx hni_win_w13_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, hni_win_shita7_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, hni_win_shita7_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(hni_win_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hni_nwin2_winT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 245, 125, 55, 225),
    gsDPSetEnvColor(215, 185, 155, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, hni_win_ue7_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&hni_win_v[4], 27, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, hni_win_ue6_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(6, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 13, 16, 17, 16, 18, 17, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, hni_win_ue5_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 19, 20, 21, 20, 22, 21, 23, 24, 25),
    gsSPNTriangles_5b(26, 23, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, hni_win_ue4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&hni_win_v[31], 26, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 2, 4, 5),
    gsSPNTriangles_5b(4, 6, 5, 7, 8, 9, 9, 0, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, hni_win_ue3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 11, 13, 12, 14, 15, 16),
    gsSPNTriangles_5b(15, 17, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, hni_win_ue2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 18, 19, 20, 19, 21, 20, 22, 23, 24),
    gsSPNTriangles_5b(25, 22, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, hni_win_ue1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&hni_win_v[57], 11, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 3, 10, 8, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hni_nwin2_win2T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 215, 185, 155, 215),
    gsDPSetEnvColor(100, 100, 255, 90),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&hni_win_v[68], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hni_nwin_3DmT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 60, 130, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 64, inv_mwin_3Dma_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&hni_win_v[72], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hni_nwin2_wakuT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 190, 255, 100, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 160, 32, hni_nwin2_w_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPVertex(&hni_win_v[76], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hni_win_w1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, hni_win_shita1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, hni_win_shita1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hni_win_v[80], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hni_win_w2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, hni_win_shita2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, hni_win_shita2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hni_win_v[84], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hni_win_w3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, hni_win_shita3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, hni_win_shita3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hni_win_v[88], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hni_win_w4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, hni_win_shita5_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, hni_win_shita5_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hni_win_v[92], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hni_win_w5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, hni_win_shita6_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, hni_win_shita6_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hni_win_v[96], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hni_win_w6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, hni_win_shita4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, hni_win_shita4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hni_win_v[100], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hni_win_w7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, hni_win_shita1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, hni_win_shita1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hni_win_v[104], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hni_win_w8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, hni_win_shita2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, hni_win_shita2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hni_win_v[108], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hni_win_w9T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, hni_win_shita3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, hni_win_shita3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hni_win_v[112], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hni_win_w10T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, hni_win_shita5_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, hni_win_shita5_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hni_win_v[116], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hni_win_w11T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, hni_win_shita6_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, hni_win_shita6_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hni_win_v[120], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hni_win_w12T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, hni_win_shita4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, hni_win_shita4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hni_win_v[124], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hni_win_mode[] = {
    gsDPPipeSync(),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | AA_EN | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_OPA | FORCE_BL |
                         G_RM_PASS | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
    gsDPSetRenderMode(AA_EN | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_OPA | FORCE_BL | G_RM_PASS,
                      AA_EN | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_OPA | FORCE_BL |
                          GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(14, 16, 1, hni_nwin2_hani_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, hni_nwin2_hani_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

Gfx hni_win_modelT[] = {
    gsSPDisplayList(hni_win_w1T_model),
    gsSPDisplayList(hni_win_w2T_model),
    gsSPDisplayList(hni_win_w3T_model),
    gsSPDisplayList(hni_win_w4T_model),
    gsSPDisplayList(hni_win_w5T_model),
    gsSPDisplayList(hni_win_w6T_model),
    gsSPDisplayList(hni_win_w7T_model),
    gsSPDisplayList(hni_win_w8T_model),
    gsSPDisplayList(hni_win_w9T_model),
    gsSPDisplayList(hni_win_w10T_model),
    gsSPDisplayList(hni_win_w11T_model),
    gsSPDisplayList(hni_win_w12T_model),
    gsSPDisplayList(hni_win_w13_model),
    gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPDisplayList(hni_nwin2_winT_model),
    gsSPDisplayList(hni_nwin2_win2T_model),
    gsSPDisplayList(hni_nwin_3DmT_model),
    gsSPDisplayList(hni_nwin2_wakuT_model),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_hni_win_c(void) {
    pc_load_asset("assets/hni_win/inv_mwin_nwaku_tex.bin", inv_mwin_nwaku_tex, 0x400, 0x70A840, 0, 0);
    pc_load_asset("assets/hni_win/inv_mwin_3Dma_tex.bin", inv_mwin_3Dma_tex, 0x800, 0x70E340, 0, 0);
}
#endif
