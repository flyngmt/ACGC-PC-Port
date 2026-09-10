#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 des_win_suuji0_tex_rgb_i4[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 des_win_suuji0_tex_rgb_i4[] = {
#include "assets/des_win_suuji0_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 des_win_suuji1_tex_rgb_i4[0x80];
#else
u8 des_win_suuji1_tex_rgb_i4[] = {
#include "assets/des_win_suuji1_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 des_win_suuji2_tex_rgb_i4[0x80];
#else
u8 des_win_suuji2_tex_rgb_i4[] = {
#include "assets/des_win_suuji2_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 des_win_suuji3_tex_rgb_i4[0x80];
#else
u8 des_win_suuji3_tex_rgb_i4[] = {
#include "assets/des_win_suuji3_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 des_win_suuji4_tex_rgb_i4[0x80];
#else
u8 des_win_suuji4_tex_rgb_i4[] = {
#include "assets/des_win_suuji4_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 des_win_suuji5_tex_rgb_i4[0x80];
#else
u8 des_win_suuji5_tex_rgb_i4[] = {
#include "assets/des_win_suuji5_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 des_win_suuji6_tex_rgb_i4[0x80];
#else
u8 des_win_suuji6_tex_rgb_i4[] = {
#include "assets/des_win_suuji6_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 des_win_suuji7_tex_rgb_i4[0x80];
#else
u8 des_win_suuji7_tex_rgb_i4[] = {
#include "assets/des_win_suuji7_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 des_win_suuji8_tex_rgb_i4[0x80];
#else
u8 des_win_suuji8_tex_rgb_i4[] = {
#include "assets/des_win_suuji8_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 des_win_suuji9_tex_rgb_i4[0x80];
#else
u8 des_win_suuji9_tex_rgb_i4[] = {
#include "assets/des_win_suuji9_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx des_suuji_v[0x100 / sizeof(Vtx)];
#else
Vtx des_suuji_v[] = {
#include "assets/des_suuji_v.inc"
};
#endif

#ifdef TARGET_PC
Gfx des_win_suuji_before[5];
#else
u8 des_win_suuji_before[] = {
#include "assets/des_win_suuji_before.inc"
};
#endif

Gfx des_win_suuji1_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(des_suuji_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx des_win_suuji2_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&des_suuji_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx des_win_suuji3_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, des_win_suuji1_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&des_suuji_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx des_win_suuji4_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, des_win_suuji6_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&des_suuji_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
