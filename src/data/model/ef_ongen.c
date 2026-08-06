#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ut_mike[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 ut_mike[] = {
#include "assets/ut_mike.inc"
};
#endif

#ifdef TARGET_PC
u8 utPal_mike[0x20];
#else
u8 utPal_mike[] = {
#include "assets/utPal_mike.inc"
};
#endif

#ifdef TARGET_PC
u8 ut_mouth[0x80];
#else
u8 ut_mouth[] = {
#include "assets/ut_mouth.inc"
};
#endif

#ifdef TARGET_PC
u8 utPal_mouth[0x20];
#else
u8 utPal_mouth[] = {
#include "assets/utPal_mouth.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_ongen_v[0x40 / sizeof(Vtx)];
#else
Vtx ef_ongen_v[] = {
#include "assets/ef_ongen_v.inc"
};
#endif

Gfx ef_ongen_mic_model[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, utPal_mike),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ut_mike),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_ongen_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSPEndDisplayList(),
};

Gfx ef_ongen_mouth_model[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, utPal_mouth),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ut_mouth),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_ongen_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSPEndDisplayList(),
};
