#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 brt_win_cake2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 brt_win_cake2_pal[] = {
#include "assets/brt_win_cake2_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 brt_win_star_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 brt_win_star_tex_rgb_ci4_pal[] = {
#include "assets/brt_win_star_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 brt_win_sw1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 brt_win_sw1_tex_rgb_ci4_pal[] = {
#include "assets/brt_win_sw1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 brt_win_sw2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 brt_win_sw2_tex_rgb_ci4_pal[] = {
#include "assets/brt_win_sw2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 brt_win_sw3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 brt_win_sw3_tex_rgb_ci4_pal[] = {
#include "assets/brt_win_sw3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 brt_win_sw4_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 brt_win_sw4_tex_rgb_ci4_pal[] = {
#include "assets/brt_win_sw4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 brt_win_sw5_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 brt_win_sw5_tex_rgb_ci4_pal[] = {
#include "assets/brt_win_sw5_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 brt_win_sw6_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 brt_win_sw6_tex_rgb_ci4_pal[] = {
#include "assets/brt_win_sw6_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 brt_win_sw7_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 brt_win_sw7_tex_rgb_ci4_pal[] = {
#include "assets/brt_win_sw7_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 brt_win_cake2_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 brt_win_cake2_tex[] = {
#include "assets/brt_win_cake2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 brt_win_ue1_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 brt_win_ue1_tex[] = {
#include "assets/brt_win_ue1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 brt_win_ue2_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 brt_win_ue2_tex[] = {
#include "assets/brt_win_ue2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 brt_win_ue3_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 brt_win_ue3_tex[] = {
#include "assets/brt_win_ue3_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 brt_win_ue4_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 brt_win_ue4_tex[] = {
#include "assets/brt_win_ue4_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 brt_win_ue5_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 brt_win_ue5_tex[] = {
#include "assets/brt_win_ue5_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 mra_win_fuki_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 mra_win_fuki_tex[] = {
#include "assets/bir_win/mra_win_fuki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 brt_win_star_tex_rgb_ci4[0x200];
#else
u8 brt_win_star_tex_rgb_ci4[] = {
#include "assets/brt_win_star_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 brt_win_sw1_tex_rgb_ci4[0x400];
#else
u8 brt_win_sw1_tex_rgb_ci4[] = {
#include "assets/brt_win_sw1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 brt_win_sw2_tex_rgb_ci4[0x400];
#else
u8 brt_win_sw2_tex_rgb_ci4[] = {
#include "assets/brt_win_sw2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 brt_win_sw3_tex_rgb_ci4[0x400];
#else
u8 brt_win_sw3_tex_rgb_ci4[] = {
#include "assets/brt_win_sw3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 brt_win_sw4_tex_rgb_ci4[0x400];
#else
u8 brt_win_sw4_tex_rgb_ci4[] = {
#include "assets/brt_win_sw4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 brt_win_sw5_tex_rgb_ci4[0x400];
#else
u8 brt_win_sw5_tex_rgb_ci4[] = {
#include "assets/brt_win_sw5_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 brt_win_sw6_tex_rgb_ci4[0x400];
#else
u8 brt_win_sw6_tex_rgb_ci4[] = {
#include "assets/brt_win_sw6_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 brt_win_sw7_tex_rgb_ci4[0x400];
#else
u8 brt_win_sw7_tex_rgb_ci4[] = {
#include "assets/brt_win_sw7_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx bir_win_v[0x700 / sizeof(Vtx)];
#else
Vtx bir_win_v[] = {
#include "assets/bir_win_v.inc"
};
#endif

Gfx brt_win_month_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(bir_win_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx brt_win_ueT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 225, 225, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, brt_win_ue5_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&bir_win_v[4], 24, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, brt_win_ue4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, brt_win_ue3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(23, 20, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, brt_win_ue2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&bir_win_v[28], 20, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, brt_win_ue1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 17, 19, 18, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx brt_win_fukiT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 205, 0, 0, 180),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 128, 32, mra_win_fuki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&bir_win_v[48], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx brt_win_cakeT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, brt_win_cake2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, brt_win_cake2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bir_win_v[52], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx brt_win_sw1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, brt_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, brt_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&bir_win_v[56], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx brt_win_sw2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, brt_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, brt_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&bir_win_v[60], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx brt_win_sw3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, brt_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, brt_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&bir_win_v[64], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx brt_win_sw4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, brt_win_sw4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, brt_win_sw4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&bir_win_v[68], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx brt_win_sw5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, brt_win_sw5_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, brt_win_sw5_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&bir_win_v[72], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx brt_win_sw6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, brt_win_sw6_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, brt_win_sw6_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&bir_win_v[76], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx brt_win_sw7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, brt_win_sw7_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, brt_win_sw7_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&bir_win_v[80], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx brt_win_sw8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, brt_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, brt_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&bir_win_v[84], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx brt_win_sw9T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, brt_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, brt_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&bir_win_v[88], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx brt_win_sw10T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, brt_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, brt_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&bir_win_v[92], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx brt_win_sw11T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, brt_win_sw4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, brt_win_sw4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&bir_win_v[96], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx brt_win_sw12T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, brt_win_sw5_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, brt_win_sw5_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&bir_win_v[100], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx brt_win_sw13T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, brt_win_sw6_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, brt_win_sw6_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&bir_win_v[104], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx brt_win_sw14T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, brt_win_sw7_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, brt_win_sw7_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&bir_win_v[108], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx birthday_win_mode[] = {
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_TEX_EDGE2),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(14, 16, 1, brt_win_star_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, brt_win_star_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

Gfx birthday_win_model[] = {
    gsSPDisplayList(brt_win_sw1T_model),
    gsSPDisplayList(brt_win_sw2T_model),
    gsSPDisplayList(brt_win_sw3T_model),
    gsSPDisplayList(brt_win_sw4T_model),
    gsSPDisplayList(brt_win_sw5T_model),
    gsSPDisplayList(brt_win_sw6T_model),
    gsSPDisplayList(brt_win_sw7T_model),
    gsSPDisplayList(brt_win_sw8T_model),
    gsSPDisplayList(brt_win_sw9T_model),
    gsSPDisplayList(brt_win_sw10T_model),
    gsSPDisplayList(brt_win_sw11T_model),
    gsSPDisplayList(brt_win_sw12T_model),
    gsSPDisplayList(brt_win_sw13T_model),
    gsSPDisplayList(brt_win_sw14T_model),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPDisplayList(brt_win_ueT_model),
    gsSPDisplayList(brt_win_fukiT_model),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSPDisplayList(brt_win_cakeT_model),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_bir_win_c(void) {
    pc_load_asset("assets/bir_win/mra_win_fuki_tex.bin", mra_win_fuki_tex, 0x800, 0x69A8A0, 0, 0);
}
#endif
