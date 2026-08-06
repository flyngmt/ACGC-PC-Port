#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 logo_us_tm_tex_4i4_txt[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 logo_us_tm_tex_4i4_txt[] = {
#include "assets/logo_us_tm_tex_4i4_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx logo_us_tm_v[0x40 / sizeof(Vtx)];
#else
Vtx logo_us_tm_v[] = {
#include "assets/logo_us_tm_v.inc"
};
#endif

Gfx logo_us_tm_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, logo_us_tm_tex_4i4_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(logo_us_tm_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
