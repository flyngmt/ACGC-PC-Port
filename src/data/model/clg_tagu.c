#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 ctl_win_tagu2_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 ctl_win_tagu2_tex[]= {
#include "assets/clg_tagu/ctl_win_tagu2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clg_win_ha2_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 clg_win_ha2_tex[]= {
#include "assets/clg_win_ha2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clg_win_jyuutan2_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 clg_win_jyuutan2_tex[]= {
#include "assets/clg_win_jyuutan2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clg_win_kabe2_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 clg_win_kabe2_tex[]= {
#include "assets/clg_win_kabe2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clg_win_fuku2_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 clg_win_fuku2_tex[]= {
#include "assets/clg_win_fuku2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clg_win_hone2_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 clg_win_hone2_tex[]= {
#include "assets/clg_win_hone2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clg_win_tegami2_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 clg_win_tegami2_tex[]= {
#include "assets/clg_win_tegami2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clg_win_onpu2_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 clg_win_onpu2_tex[]= {
#include "assets/clg_win_onpu2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clg_win_hani2_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 clg_win_hani2_tex[]= {
#include "assets/clg_win_hani2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 clg_win_kasa2_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 clg_win_kasa2_tex[]= {
#include "assets/clg_win_kasa2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx clg_tagu_v[0x480 / sizeof(Vtx)];
#else
Vtx clg_tagu_v[] = {
#include "assets/clg_tagu_v.inc"
};
#endif

Gfx clg_tag_win_mode[] = {
gsDPPipeSync(),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, ctl_win_tagu2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_tag_picture_mode[] = {
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsSPEndDisplayList(),
};

Gfx clg_win_haT_model[] = {
gsSPVertex(clg_tagu_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_kabeT_model[] = {
gsSPVertex(&clg_tagu_v[4], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_jyuutanT_model[] = {
gsSPVertex(&clg_tagu_v[8], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_fukuT_model[] = {
gsSPVertex(&clg_tagu_v[12], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_kasaT_model[] = {
gsSPVertex(&clg_tagu_v[16], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_tegamiT_model[] = {
gsSPVertex(&clg_tagu_v[20], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_haniwaT_model[] = {
gsSPVertex(&clg_tagu_v[24], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_honeT_model[] = {
gsSPVertex(&clg_tagu_v[28], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_onpuT_model[] = {
gsSPVertex(&clg_tagu_v[32], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_ha2T_model[] = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clg_win_ha2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_tagu_v[36], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_kabe2T_model[] = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clg_win_kabe2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_tagu_v[40], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_jyuutan2T_model[] = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clg_win_jyuutan2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_tagu_v[44], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_fuku2T_model[] = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clg_win_fuku2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_tagu_v[48], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_kasa2T_model[] = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clg_win_kasa2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_tagu_v[52], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_tegami2T_model[] = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clg_win_tegami2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_tagu_v[56], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_haniwa2T_model[] = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clg_win_hani2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_tagu_v[60], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_hone2T_model[] = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clg_win_hone2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_tagu_v[64], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_onpu2T_model[] = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clg_win_onpu2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_tagu_v[68], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};


#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_clg_tagu_c(void) {
    pc_load_asset("assets/clg_tagu/ctl_win_tagu2_tex.bin", ctl_win_tagu2_tex, 0x200, 0x6C32A0, 0, 0);
}
#endif
