#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 tim_win_newtokei_tex[0x20];
#else
ATTRIBUTE_ALIGN(32) u8 tim_win_newtokei_tex[] = {
#include "assets/tim_win_newtokei_tex.inc"
};
#endif

#ifdef TARGET_PC
u16 tim_win_nuno_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 tim_win_nuno_tex_rgb_ci4_pal[] = {
#include "assets/tim_win_nuno_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 tim_win_sw1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 tim_win_sw1_tex_rgb_ci4_pal[] = {
#include "assets/tim_win_sw1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 tim_win_sw2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 tim_win_sw2_tex_rgb_ci4_pal[] = {
#include "assets/tim_win_sw2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 tim_win_sw3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 tim_win_sw3_tex_rgb_ci4_pal[] = {
#include "assets/tim_win_sw3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 tim_win_sw4_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 tim_win_sw4_tex_rgb_ci4_pal[] = {
#include "assets/tim_win_sw4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 tim_win_sw5_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 tim_win_sw5_tex_rgb_ci4_pal[] = {
#include "assets/tim_win_sw5_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 tim_win_sw6_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 tim_win_sw6_tex_rgb_ci4_pal[] = {
#include "assets/tim_win_sw6_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 tim_win_sw7_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 tim_win_sw7_tex_rgb_ci4_pal[] = {
#include "assets/tim_win_sw7_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_tokei1_tex[0x800];
#else
u8 tim_win_tokei1_tex[] = {
#include "assets/tim_win_tokei1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_fuki_tex[0x800];
#else
u8 tim_win_fuki_tex[] = {
#include "assets/tim_win_fuki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_moji_tex[0x80];
#else
u8 tim_win_moji_tex[] = {
#include "assets/tim_win_moji_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_on_tex[0x80];
#else
u8 tim_win_on_tex[] = {
#include "assets/tim_win_on_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 testmocomma[0x80];
#else
u8 testmocomma[] = {
#include "assets/testmocomma.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_maru_tex[0x80];
#else
u8 tim_win_maru_tex[] = {
#include "assets/tim_win_maru_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_w1_tex[0x400];
#else
u8 tim_win_w1_tex[] = {
#include "assets/tim_win_w1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_w2_tex[0x400];
#else
u8 tim_win_w2_tex[] = {
#include "assets/tim_win_w2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_w3_tex[0x200];
#else
u8 tim_win_w3_tex[] = {
#include "assets/tim_win_w3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_w4_tex[0x400];
#else
u8 tim_win_w4_tex[] = {
#include "assets/tim_win_w4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_w5_tex[0x400];
#else
u8 tim_win_w5_tex[] = {
#include "assets/tim_win_w5_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_april_tex_rgb_i4[0x200];
#else
u8 tim_win_april_tex_rgb_i4[] = {
#include "assets/tim_win_april_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_august_tex_rgb_i4[0x200];
#else
u8 tim_win_august_tex_rgb_i4[] = {
#include "assets/tim_win_august_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_december_tex_rgb_i4[0x200];
#else
u8 tim_win_december_tex_rgb_i4[] = {
#include "assets/tim_win_december_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_february_tex_rgb_i4[0x200];
#else
u8 tim_win_february_tex_rgb_i4[] = {
#include "assets/tim_win_february_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_january_tex_rgb_i4[0x200];
#else
u8 tim_win_january_tex_rgb_i4[] = {
#include "assets/tim_win_january_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_july_tex_rgb_i4[0x200];
#else
u8 tim_win_july_tex_rgb_i4[] = {
#include "assets/tim_win_july_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_june_tex_rgb_i4[0x200];
#else
u8 tim_win_june_tex_rgb_i4[] = {
#include "assets/tim_win_june_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_march_tex_rgb_i4[0x200];
#else
u8 tim_win_march_tex_rgb_i4[] = {
#include "assets/tim_win_march_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_may_tex_rgb_i4[0x200];
#else
u8 tim_win_may_tex_rgb_i4[] = {
#include "assets/tim_win_may_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_november_tex_rgb_i4[0x200];
#else
u8 tim_win_november_tex_rgb_i4[] = {
#include "assets/tim_win_november_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_october_tex_rgb_i4[0x200];
#else
u8 tim_win_october_tex_rgb_i4[] = {
#include "assets/tim_win_october_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_september_tex_rgb_i4[0x200];
#else
u8 tim_win_september_tex_rgb_i4[] = {
#include "assets/tim_win_september_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_fri_tex_rgb_i4[0x200];
#else
u8 tim_win_fri_tex_rgb_i4[] = {
#include "assets/tim_win_fri_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_mon_tex_rgb_i4[0x200];
#else
u8 tim_win_mon_tex_rgb_i4[] = {
#include "assets/tim_win_mon_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_sat_tex_rgb_i4[0x200];
#else
u8 tim_win_sat_tex_rgb_i4[] = {
#include "assets/tim_win_sat_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_sun_tex_rgb_i4[0x200];
#else
u8 tim_win_sun_tex_rgb_i4[] = {
#include "assets/tim_win_sun_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_thu_tex_rgb_i4[0x200];
#else
u8 tim_win_thu_tex_rgb_i4[] = {
#include "assets/tim_win_thu_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_tue_tex_rgb_i4[0x200];
#else
u8 tim_win_tue_tex_rgb_i4[] = {
#include "assets/tim_win_tue_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_wed_tex_rgb_i4[0x200];
#else
u8 tim_win_wed_tex_rgb_i4[] = {
#include "assets/tim_win_wed_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_nuno_tex_rgb_ci4[0x200];
#else
u8 tim_win_nuno_tex_rgb_ci4[] = {
#include "assets/tim_win_nuno_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_sw1_tex_rgb_ci4[0x400];
#else
u8 tim_win_sw1_tex_rgb_ci4[] = {
#include "assets/tim_win_sw1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_sw2_tex_rgb_ci4[0x400];
#else
u8 tim_win_sw2_tex_rgb_ci4[] = {
#include "assets/tim_win_sw2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_sw3_tex_rgb_ci4[0x400];
#else
u8 tim_win_sw3_tex_rgb_ci4[] = {
#include "assets/tim_win_sw3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_sw4_tex_rgb_ci4[0x400];
#else
u8 tim_win_sw4_tex_rgb_ci4[] = {
#include "assets/tim_win_sw4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_sw5_tex_rgb_ci4[0x400];
#else
u8 tim_win_sw5_tex_rgb_ci4[] = {
#include "assets/tim_win_sw5_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_sw6_tex_rgb_ci4[0x400];
#else
u8 tim_win_sw6_tex_rgb_ci4[] = {
#include "assets/tim_win_sw6_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 tim_win_sw7_tex_rgb_ci4[0x400];
#else
u8 tim_win_sw7_tex_rgb_ci4[] = {
#include "assets/tim_win_sw7_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx tim_win_v[0x870 / sizeof(Vtx)];
#else
Vtx tim_win_v[] = {
#include "assets/tim_win_v.inc"
};
#endif

Gfx tim_win_ue_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 235, 245, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, tim_win_w5_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(tim_win_v, 27, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, tim_win_w4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 11, 17, 11, 18, 17, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, tim_win_w3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 19, 20, 21, 22, 19, 21, 23, 24, 25),
    gsSPNTriangles_5b(24, 26, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, tim_win_w2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tim_win_v[27], 16, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, tim_win_w1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_moji_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 105, 40, 185, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tim_win_maru_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tim_win_v[43], 20, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, testmocomma),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 5, 7, 6, 8, 9, 10),
    gsSPNTriangles_5b(11, 8, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tim_win_on_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 13, 15, 14, 0, 0, 0),
#ifndef TARGET_PC
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tim_win_moji_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 17, 19, 18, 0, 0, 0),
#endif
    gsSPEndDisplayList(),
};

Gfx tim_win_youbi_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 105, 40, 185, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&tim_win_v[63], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_month_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&tim_win_v[67], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_sw1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, tim_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, tim_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tim_win_v[71], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_sw2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, tim_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, tim_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tim_win_v[75], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_sw3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, tim_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, tim_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tim_win_v[79], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_sw4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, tim_win_sw4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, tim_win_sw4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tim_win_v[83], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_sw5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, tim_win_sw5_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, tim_win_sw5_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tim_win_v[87], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_sw6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, tim_win_sw6_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, tim_win_sw6_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tim_win_v[91], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_sw7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, tim_win_sw7_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, tim_win_sw7_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tim_win_v[95], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_sw8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, tim_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, tim_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&tim_win_v[99], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_sw9T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, tim_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, tim_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&tim_win_v[103], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_sw10T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, tim_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, tim_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&tim_win_v[107], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_sw11T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, tim_win_sw4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, tim_win_sw4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&tim_win_v[111], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_sw12T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, tim_win_sw5_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, tim_win_sw5_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&tim_win_v[115], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_sw13T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, tim_win_sw6_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, tim_win_sw6_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&tim_win_v[119], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_sw14T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, tim_win_sw7_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, tim_win_sw7_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&tim_win_v[123], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_tokeiT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tim_win_newtokei_tex),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, tim_win_tokei1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tim_win_v[127], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_fukiT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 115, 0, 115, 190),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 128, 32, tim_win_fuki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&tim_win_v[131], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 1, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_mode[] = {
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_TEX_EDGE2),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(14, 16, 1, tim_win_nuno_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tim_win_nuno_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tim_win_model[] = {
    gsSPDisplayList(tim_win_sw1T_model),
    gsSPDisplayList(tim_win_sw2T_model),
    gsSPDisplayList(tim_win_sw3T_model),
    gsSPDisplayList(tim_win_sw4T_model),
    gsSPDisplayList(tim_win_sw5T_model),
    gsSPDisplayList(tim_win_sw6T_model),
    gsSPDisplayList(tim_win_sw7T_model),
    gsSPDisplayList(tim_win_sw8T_model),
    gsSPDisplayList(tim_win_sw9T_model),
    gsSPDisplayList(tim_win_sw10T_model),
    gsSPDisplayList(tim_win_sw11T_model),
    gsSPDisplayList(tim_win_sw12T_model),
    gsSPDisplayList(tim_win_sw13T_model),
    gsSPDisplayList(tim_win_sw14T_model),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPDisplayList(tim_win_ue_model),
    gsSPDisplayList(tim_win_fukiT_model),
    gsSPDisplayList(tim_win_tokeiT_model),
    gsSPDisplayList(tim_win_moji_model),
    gsSPEndDisplayList(),
};
