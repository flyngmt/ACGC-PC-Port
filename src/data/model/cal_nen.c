#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 cal_win_nen0_tex_rgb_i4[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 cal_win_nen0_tex_rgb_i4[] = {
#include "assets/cal_win_nen0_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_nen1_tex_rgb_i4[0x80];
#else
u8 cal_win_nen1_tex_rgb_i4[] = {
#include "assets/cal_win_nen1_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_nen2_tex_rgb_i4[0x80];
#else
u8 cal_win_nen2_tex_rgb_i4[] = {
#include "assets/cal_win_nen2_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_nen3_tex_rgb_i4[0x80];
#else
u8 cal_win_nen3_tex_rgb_i4[] = {
#include "assets/cal_win_nen3_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_nen4_tex_rgb_i4[0x80];
#else
u8 cal_win_nen4_tex_rgb_i4[] = {
#include "assets/cal_win_nen4_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_nen5_tex_rgb_i4[0x80];
#else
u8 cal_win_nen5_tex_rgb_i4[] = {
#include "assets/cal_win_nen5_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_nen6_tex_rgb_i4[0x80];
#else
u8 cal_win_nen6_tex_rgb_i4[] = {
#include "assets/cal_win_nen6_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_nen7_tex_rgb_i4[0x80];
#else
u8 cal_win_nen7_tex_rgb_i4[] = {
#include "assets/cal_win_nen7_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_nen8_tex_rgb_i4[0x80];
#else
u8 cal_win_nen8_tex_rgb_i4[] = {
#include "assets/cal_win_nen8_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_nen9_tex_rgb_i4[0x80];
#else
u8 cal_win_nen9_tex_rgb_i4[] = {
#include "assets/cal_win_nen9_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx cal_nen_v[0x100 / sizeof(Vtx)];
#else
Vtx cal_nen_v[] = {
#include "assets/cal_nen_v.inc"
};
#endif

#ifdef TARGET_PC
u8 cal_win_nen_before[0x28];
#else
u8 cal_win_nen_before[] = {
#include "assets/cal_win_nen_before.inc"
};
#endif

Gfx cal_win_nen1_model[] = {
    gsSPVertex(cal_nen_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx cal_win_nen2_model[] = {
    gsSPVertex(&cal_nen_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx cal_win_nen3_model[] = {
    gsSPVertex(&cal_nen_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx cal_win_nen4_model[] = {
    gsSPVertex(&cal_nen_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
