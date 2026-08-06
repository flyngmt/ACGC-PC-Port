#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_hana01_tu_a_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 ef_hana01_tu_a_tex[] = {
#include "assets/ef_hana01_tu_a_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_hana01_tu_a_v[0x50 / sizeof(Vtx)];
#else
Vtx ef_hana01_tu_a_v[] = {
#include "assets/ef_hana01_tu_a_v.inc"
};
#endif

Gfx ef_hana01_tu_a_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ef_hana01_tu_a_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_hana01_tu_a_v, 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 2, 3, 4),
    gsSPNTriangles_5b(0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_hana01_co_a_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 ef_hana01_co_a_tex[] = {
#include "assets/ef_hana01_co_a_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_hana01_co_a_v[0x50 / sizeof(Vtx)];
#else
Vtx ef_hana01_co_a_v[] = {
#include "assets/ef_hana01_co_a_v.inc"
};
#endif

Gfx ef_hana01_co_a_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ef_hana01_co_a_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_hana01_co_a_v, 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 2, 3, 4),
    gsSPNTriangles_5b(0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_hana01_pa_a_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 ef_hana01_pa_a_tex[] = {
#include "assets/ef_hana01_pa_a_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_hana01_pa_a_v[0x50 / sizeof(Vtx)];
#else
Vtx ef_hana01_pa_a_v[] = {
#include "assets/ef_hana01_pa_a_v.inc"
};
#endif

Gfx ef_hana01_pa_a_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ef_hana01_pa_a_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_hana01_pa_a_v, 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 2, 3, 4),
    gsSPNTriangles_5b(0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_hana01_ha_a_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 ef_hana01_ha_a_tex[] = {
#include "assets/ef_hana01_ha_a_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_hana01_ha_a_v[0x50 / sizeof(Vtx)];
#else
Vtx ef_hana01_ha_a_v[] = {
#include "assets/ef_hana01_ha_a_v.inc"
};
#endif

Gfx ef_hana01_ha_a_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ef_hana01_ha_a_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_hana01_ha_a_v, 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 2, 3, 4),
    gsSPNTriangles_5b(0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
