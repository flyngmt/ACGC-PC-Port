#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 kti_win_hate_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 kti_win_hate_pal[] = {
#include "assets/kti_win_hate_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 kti_win_nuno_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 kti_win_nuno_tex_rgb_ci4_pal[] = {
#include "assets/kti_win_nuno_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 kti_win_sw1_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 kti_win_sw1_tex_rgb_ci4_pal[] = {
#include "assets/kti_win_sw1_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 kti_win_sw2_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 kti_win_sw2_tex_rgb_ci4_pal[] = {
#include "assets/kti_win_sw2_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 kti_win_sw3_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 kti_win_sw3_tex_rgb_ci4_pal[] = {
#include "assets/kti_win_sw3_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 kti_win_sw4_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 kti_win_sw4_tex_rgb_ci4_pal[] = {
#include "assets/kti_win_sw4_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 kti_win_sw5_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 kti_win_sw5_tex_rgb_ci4_pal[] = {
#include "assets/kti_win_sw5_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 kti_win_sw6_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 kti_win_sw6_tex_rgb_ci4_pal[] = {
#include "assets/kti_win_sw6_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 kti_win_sw7_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 kti_win_sw7_tex_rgb_ci4_pal[] = {
#include "assets/kti_win_sw7_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 kti_win_w1_tex[0x400];
#else
u8 kti_win_w1_tex[] = {
#include "assets/kti_win_w1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kti_win_w2_tex[0x400];
#else
u8 kti_win_w2_tex[] = {
#include "assets/kti_win_w2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kti_win_w3_tex[0x200];
#else
u8 kti_win_w3_tex[] = {
#include "assets/kti_win_w3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kti_win_w4_tex[0x400];
#else
u8 kti_win_w4_tex[] = {
#include "assets/kti_win_w4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kti_win_w5_tex[0x400];
#else
u8 kti_win_w5_tex[] = {
#include "assets/kti_win_w5_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kti_win_fuki_tex[0x800];
#else
u8 kti_win_fuki_tex[] = {
#include "assets/kti_win_fuki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kti_win_hate_tex[0x800];
#else
u8 kti_win_hate_tex[] = {
#include "assets/kti_win_hate_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kti_win_nuno_tex_rgb_ci4[0x200];
#else
u8 kti_win_nuno_tex_rgb_ci4[] = {
#include "assets/kti_win_nuno_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 kti_win_sw1_tex_rgb_ci4[0x400];
#else
u8 kti_win_sw1_tex_rgb_ci4[] = {
#include "assets/kti_win_sw1_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 kti_win_sw2_tex_rgb_ci4[0x400];
#else
u8 kti_win_sw2_tex_rgb_ci4[] = {
#include "assets/kti_win_sw2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 kti_win_sw3_tex_rgb_ci4[0x400];
#else
u8 kti_win_sw3_tex_rgb_ci4[] = {
#include "assets/kti_win_sw3_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 kti_win_sw4_tex_rgb_ci4[0x400];
#else
u8 kti_win_sw4_tex_rgb_ci4[] = {
#include "assets/kti_win_sw4_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 kti_win_sw5_tex_rgb_ci4[0x400];
#else
u8 kti_win_sw5_tex_rgb_ci4[] = {
#include "assets/kti_win_sw5_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 kti_win_sw6_tex_rgb_ci4[0x400];
#else
u8 kti_win_sw6_tex_rgb_ci4[] = {
#include "assets/kti_win_sw6_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
u8 kti_win_sw7_tex_rgb_ci4[0x400];
#else
u8 kti_win_sw7_tex_rgb_ci4[] = {
#include "assets/kti_win_sw7_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx kti_win_v[0x7A0 / sizeof(Vtx)];
#else
Vtx kti_win_v[] = {
#include "assets/kti_win_v.inc"
};
#endif

Gfx kti_win_sen_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
    gsDPSetPrimColor(0, 255, 80, 80, 235, 255),
    gsSPVertex(kti_win_v, 14, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(6, 1, 4, 7, 8, 9, 8, 10, 9, 11, 12, 9),
    gsSPNTriangles_5b(11, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kti_win_ueT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 245, 255, 245, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, kti_win_w5_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kti_win_v[14], 28, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 6, 3, 5),
    gsSPNTriangles_5b(7, 8, 9, 8, 10, 9, 1, 11, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, kti_win_w4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 15, 16, 17, 16, 18, 17),
    gsSPNTriangles_5b(13, 19, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, kti_win_w3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 23, 24, 25, 26, 23, 25),
    gsSPNTriangles_5b(27, 20, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, kti_win_w2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kti_win_v[42], 16, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 4, 6, 5),
    gsSPNTriangles_5b(1, 7, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, kti_win_w1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 12, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kti_win_fukiT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0,
                       0),
    gsDPSetPrimColor(0, 255, 60, 145, 0, 180),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 128, 32, kti_win_fuki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kti_win_v[58], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kti_win_kafuT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, kti_win_hate_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, kti_win_hate_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kti_win_v[62], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kti_win_sw1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, kti_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, kti_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kti_win_v[66], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kti_win_sw2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, kti_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, kti_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kti_win_v[70], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kti_win_sw3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, kti_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, kti_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kti_win_v[74], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kti_win_sw4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, kti_win_sw4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, kti_win_sw4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kti_win_v[78], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kti_win_sw5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, kti_win_sw5_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, kti_win_sw5_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kti_win_v[82], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kti_win_sw6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, kti_win_sw6_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, kti_win_sw6_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kti_win_v[86], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kti_win_sw7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, kti_win_sw7_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, kti_win_sw7_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kti_win_v[90], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kti_win_sw8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, kti_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, kti_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kti_win_v[94], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kti_win_sw9T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, kti_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, kti_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kti_win_v[98], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kti_win_sw10T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, kti_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, kti_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kti_win_v[102], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kti_win_sw11T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, kti_win_sw4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, kti_win_sw4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kti_win_v[106], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kti_win_sw12T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, kti_win_sw5_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, kti_win_sw5_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kti_win_v[110], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kti_win_sw13T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, kti_win_sw6_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, kti_win_sw6_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kti_win_v[114], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kti_win_sw14T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, kti_win_sw7_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, kti_win_sw7_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kti_win_v[118], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx ephrase_win_mode[] = {
    gsDPLoadTLUT_Dolphin(14, 16, 1, kti_win_nuno_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, kti_win_nuno_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

Gfx ephrase_win_model[] = {
    gsSPDisplayList(kti_win_sw1T_model),
    gsSPDisplayList(kti_win_sw2T_model),
    gsSPDisplayList(kti_win_sw3T_model),
    gsSPDisplayList(kti_win_sw4T_model),
    gsSPDisplayList(kti_win_sw5T_model),
    gsSPDisplayList(kti_win_sw6T_model),
    gsSPDisplayList(kti_win_sw7T_model),
    gsSPDisplayList(kti_win_sw8T_model),
    gsSPDisplayList(kti_win_sw9T_model),
    gsSPDisplayList(kti_win_sw10T_model),
    gsSPDisplayList(kti_win_sw11T_model),
    gsSPDisplayList(kti_win_sw12T_model),
    gsSPDisplayList(kti_win_sw13T_model),
    gsSPDisplayList(kti_win_sw14T_model),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPDisplayList(kti_win_ueT_model),
    gsSPDisplayList(kti_win_fukiT_model),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsSPDisplayList(kti_win_sen_model),
    gsDPSetRenderMode(G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSPDisplayList(kti_win_kafuT_model),
    gsSPEndDisplayList(),
};
