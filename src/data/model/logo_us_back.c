#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx logo_us_back_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 logo_us_back_4_tex_4i4_txt[0x1000];
#else
ATTRIBUTE_ALIGN(32) u8 logo_us_back_4_tex_4i4_txt[] = {
#include "assets/logo_us_back_4_tex_4i4_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 logo_us_back_3_tex_4i4_txt[0x1000];
#else
u8 logo_us_back_3_tex_4i4_txt[] = {
#include "assets/logo_us_back_3_tex_4i4_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 logo_us_back_1_tex_4i4_txt[0x1000];
#else
u8 logo_us_back_1_tex_4i4_txt[] = {
#include "assets/logo_us_back_1_tex_4i4_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 logo_us_back_2_tex_4i4_txt[0x1000];
#else
u8 logo_us_back_2_tex_4i4_txt[] = {
#include "assets/logo_us_back_2_tex_4i4_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx logo_us_back_v[0x100 / sizeof(Vtx)];
#else
Vtx logo_us_back_v[] = {
#include "assets/logo_us_back_v.inc"
};
#endif

Gfx logo_us_backD_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 128, logo_us_back_4_tex_4i4_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(logo_us_back_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx logo_us_backC_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 128, logo_us_back_3_tex_4i4_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&logo_us_back_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx logo_us_backB_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 128, logo_us_back_2_tex_4i4_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&logo_us_back_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx logo_us_backA_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 128, logo_us_back_1_tex_4i4_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&logo_us_back_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
