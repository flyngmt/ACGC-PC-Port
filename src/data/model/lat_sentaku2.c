#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 lat_tegami_sw3_tex[0x1000];
#else
ATTRIBUTE_ALIGN(32) u8 lat_tegami_sw3_tex[]= {
#include "assets/lat_tegami_sw3_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx lat_sentaku2_v[0xB0 / sizeof(Vtx)];
#else
Vtx lat_sentaku2_v[] = {
#include "assets/lat_sentaku2_v.inc"
};
#endif

Gfx lat_sentaku2_c_model[] = {
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
gsDPSetPrimColor(0, 255, 255, 0, 0, 255),
gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
gsSPVertex(lat_sentaku2_v, 3, 0),
gsSP1Triangle(0, 1, 2, 0),
gsSPEndDisplayList(),
};

Gfx lat_sentaku2_winT_model[] = {
gsDPPipeSync(),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 255, 255, 165, 255),
gsDPSetEnvColor(255, 70, 0, 255),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, lat_tegami_sw3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sentaku2_v[3], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsSPEndDisplayList(),
};

