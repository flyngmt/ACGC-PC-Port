#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 cal_win_tuki1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 cal_win_tuki1_pal[]= {
#include "assets/cal_win_tuki1_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 cal_win_f1_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 cal_win_f1_tex[]= {
#include "assets/cal_win_f1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 cal_win_f2_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 cal_win_f2_tex[]= {
#include "assets/cal_win_f2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 cal_win_f3_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 cal_win_f3_tex[]= {
#include "assets/cal_win_f3_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 cal_win_f4_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 cal_win_f4_tex[]= {
#include "assets/cal_win_f4_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 cal_win_event_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 cal_win_event_tex[]= {
#include "assets/cal_win_event_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 cal_win_m_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 cal_win_m_tex[]= {
#include "assets/cal_win_m_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 cal_win_f_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 cal_win_f_tex[]= {
#include "assets/cal_win_f_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 cal_win_s_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 cal_win_s_tex[]= {
#include "assets/cal_win_s_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 cal_win_t_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 cal_win_t_tex[]= {
#include "assets/cal_win_t_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 cal_win_w_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 cal_win_w_tex[]= {
#include "assets/cal_win_w_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 cal_win_tuki1_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 cal_win_tuki1_tex[]= {
#include "assets/cal_win_tuki1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_april_tex_rgb_ia8[0x1000];
#else
u8 cal_win_april_tex_rgb_ia8[] = {
#include "assets/cal_win_april_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_august_tex_rgb_ia8[0x1000];
#else
u8 cal_win_august_tex_rgb_ia8[] = {
#include "assets/cal_win_august_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_december_tex_rgb_ia8[0x1000];
#else
u8 cal_win_december_tex_rgb_ia8[] = {
#include "assets/cal_win_december_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_february_tex_rgb_ia8[0x1000];
#else
u8 cal_win_february_tex_rgb_ia8[] = {
#include "assets/cal_win_february_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_january_tex_rgb_ia8[0x1000];
#else
u8 cal_win_january_tex_rgb_ia8[] = {
#include "assets/cal_win_january_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_july_tex_rgb_ia8[0x1000];
#else
u8 cal_win_july_tex_rgb_ia8[] = {
#include "assets/cal_win_july_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_june_tex_rgb_ia8[0x1000];
#else
u8 cal_win_june_tex_rgb_ia8[] = {
#include "assets/cal_win_june_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_march_tex_rgb_ia8[0x1000];
#else
u8 cal_win_march_tex_rgb_ia8[] = {
#include "assets/cal_win_march_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_may_tex_rgb_ia8[0x1000];
#else
u8 cal_win_may_tex_rgb_ia8[] = {
#include "assets/cal_win_may_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_november_tex_rgb_ia8[0x1000];
#else
u8 cal_win_november_tex_rgb_ia8[] = {
#include "assets/cal_win_november_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_october_tex_rgb_ia8[0x1000];
#else
u8 cal_win_october_tex_rgb_ia8[] = {
#include "assets/cal_win_october_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_september_tex_rgb_ia8[0x1000];
#else
u8 cal_win_september_tex_rgb_ia8[] = {
#include "assets/cal_win_september_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji10_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji10_tex_rgb_i4[] = {
#include "assets/cal_win_suuji10_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji11_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji11_tex_rgb_i4[] = {
#include "assets/cal_win_suuji11_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji12_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji12_tex_rgb_i4[] = {
#include "assets/cal_win_suuji12_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji13_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji13_tex_rgb_i4[] = {
#include "assets/cal_win_suuji13_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji14_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji14_tex_rgb_i4[] = {
#include "assets/cal_win_suuji14_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji15_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji15_tex_rgb_i4[] = {
#include "assets/cal_win_suuji15_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji16_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji16_tex_rgb_i4[] = {
#include "assets/cal_win_suuji16_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji17_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji17_tex_rgb_i4[] = {
#include "assets/cal_win_suuji17_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji18_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji18_tex_rgb_i4[] = {
#include "assets/cal_win_suuji18_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji19_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji19_tex_rgb_i4[] = {
#include "assets/cal_win_suuji19_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji1_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji1_tex_rgb_i4[] = {
#include "assets/cal_win_suuji1_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji20_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji20_tex_rgb_i4[] = {
#include "assets/cal_win_suuji20_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji21_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji21_tex_rgb_i4[] = {
#include "assets/cal_win_suuji21_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji22_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji22_tex_rgb_i4[] = {
#include "assets/cal_win_suuji22_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji23_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji23_tex_rgb_i4[] = {
#include "assets/cal_win_suuji23_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji24_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji24_tex_rgb_i4[] = {
#include "assets/cal_win_suuji24_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji25_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji25_tex_rgb_i4[] = {
#include "assets/cal_win_suuji25_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji26_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji26_tex_rgb_i4[] = {
#include "assets/cal_win_suuji26_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji27_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji27_tex_rgb_i4[] = {
#include "assets/cal_win_suuji27_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji28_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji28_tex_rgb_i4[] = {
#include "assets/cal_win_suuji28_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji29_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji29_tex_rgb_i4[] = {
#include "assets/cal_win_suuji29_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji2_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji2_tex_rgb_i4[] = {
#include "assets/cal_win_suuji2_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji30_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji30_tex_rgb_i4[] = {
#include "assets/cal_win_suuji30_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji31_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji31_tex_rgb_i4[] = {
#include "assets/cal_win_suuji31_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji3_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji3_tex_rgb_i4[] = {
#include "assets/cal_win_suuji3_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji4_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji4_tex_rgb_i4[] = {
#include "assets/cal_win_suuji4_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji5_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji5_tex_rgb_i4[] = {
#include "assets/cal_win_suuji5_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji6_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji6_tex_rgb_i4[] = {
#include "assets/cal_win_suuji6_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji7_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji7_tex_rgb_i4[] = {
#include "assets/cal_win_suuji7_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji8_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji8_tex_rgb_i4[] = {
#include "assets/cal_win_suuji8_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_suuji9_tex_rgb_i4[0x80];
#else
u8 cal_win_suuji9_tex_rgb_i4[] = {
#include "assets/cal_win_suuji9_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_box2_tex_rgb_ia8[0x400];
#else
u8 cal_win_box2_tex_rgb_ia8[] = {
#include "assets/cal_win_box2_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_box_tex_rgb_ia8[0x400];
#else
u8 cal_win_box_tex_rgb_ia8[] = {
#include "assets/cal_win_box_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
Vtx cal_win_v[0xA40 / sizeof(Vtx)];
#else
Vtx cal_win_v[] = {
#include "assets/cal_win_v.inc"
};
#endif

Gfx cal_win_tuki_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, PRIMITIVE, ENVIRONMENT, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
gsDPSetEnvColor(215, 215, 215, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsSPVertex(cal_win_v, 32, 0),
gsSPNTrianglesInit_5b(30, 0, 1, 2, 2, 3, 0, 1, 4, 5),
gsSPNTriangles_5b(1, 6, 4, 4, 7, 5, 5, 8, 2, 5, 9, 8),
gsSPNTriangles_5b(10, 11, 0, 0, 12, 10, 10, 1, 11, 10, 13, 1),
gsSPNTriangles_5b(12, 14, 15, 15, 16, 12, 15, 10, 16, 15, 17, 10),
gsSPNTriangles_5b(18, 19, 20, 21, 18, 20, 12, 21, 20, 20, 14, 12),
gsSPNTriangles_5b(22, 23, 18, 24, 22, 18, 18, 12, 0, 0, 24, 18),
gsSPNTriangles_5b(25, 26, 27, 28, 25, 27, 27, 29, 30, 30, 31, 22),
gsSPNTriangles_5b(27, 30, 22, 0, 3, 28, 28, 22, 0, 0, 0, 0),
gsSPVertex(&cal_win_v[32], 32, 0),
gsSPNTrianglesInit_5b(30, 0, 1, 2, 2, 3, 0, 1, 4, 5),
gsSPNTriangles_5b(1, 6, 4, 4, 7, 5, 5, 8, 2, 5, 9, 8),
gsSPNTriangles_5b(10, 11, 0, 0, 12, 10, 10, 1, 11, 10, 13, 1),
gsSPNTriangles_5b(12, 14, 15, 15, 16, 12, 15, 10, 16, 15, 17, 10),
gsSPNTriangles_5b(18, 19, 20, 21, 18, 20, 12, 21, 20, 20, 14, 12),
gsSPNTriangles_5b(22, 23, 18, 24, 22, 18, 18, 12, 0, 0, 24, 18),
gsSPNTriangles_5b(25, 26, 27, 28, 25, 27, 27, 29, 30, 30, 31, 22),
gsSPNTriangles_5b(27, 30, 22, 0, 3, 28, 28, 22, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx cal_win_shita_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 80, 50, 50, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsSPVertex(&cal_win_v[64], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx cal_win_futi_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 40, 40, 205, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, cal_win_f4_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&cal_win_v[68], 20, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 2, 1, 4),
gsSPNTriangles_5b(2, 4, 5, 6, 7, 8, 6, 9, 7, 10, 11, 9),
gsSPNTriangles_5b(10, 9, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 32, cal_win_f3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(4, 12, 13, 14, 13, 15, 14, 16, 17, 18),
gsSPNTriangles_5b(19, 16, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, cal_win_f2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&cal_win_v[88], 16, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 12, 13, 14),
gsSPNTriangles_5b(15, 12, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, cal_win_f1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&cal_win_v[104], 16, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 4, 5, 6),
gsSPNTriangles_5b(7, 8, 9, 8, 10, 9, 11, 12, 13, 12, 14, 13),
gsSPNTriangles_5b(15, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx cal_win_suuji_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsSPVertex(&cal_win_v[120], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx cal_win_eventT_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsSPVertex(&cal_win_v[124], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx cal_win_boxT_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsSPVertex(&cal_win_v[128], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx cal_win_hijituT_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 205, 205, 60, 255),
gsDPSetEnvColor(80, 80, 20, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, cal_win_w_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&cal_win_v[132], 20, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, cal_win_t_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(4, 4, 5, 6, 5, 7, 6, 8, 9, 10),
gsSPNTriangles_5b(9, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, cal_win_f_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(2, 12, 13, 14, 13, 15, 14, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, cal_win_m_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(2, 16, 17, 18, 17, 19, 18, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx cal_win_doyouT_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 155, 155, 255, 255),
gsDPSetEnvColor(50, 50, 70, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, cal_win_s_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&cal_win_v[152], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx cal_win_nitiyouT_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 185, 100, 100, 255),
gsDPSetEnvColor(80, 50, 50, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, cal_win_s_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&cal_win_v[156], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx cal_win_monthT_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 20, 20, 50, 255),
gsDPSetEnvColor(85, 165, 255, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsSPVertex(&cal_win_v[160], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

