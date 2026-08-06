#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

ATTRIBUTE_ALIGN(32) EVW_ANIME_SCROLL ef_siawase01_00_evw_anime_2[] = { { 1, -4, 16, 16 }, { 0, 0, 16, 16 } };

EVW_ANIME_DATA ef_siawase01_00_evw_anime[] = { { -1, EVW_ANIME_TYPE_SCROLL2, ef_siawase01_00_evw_anime_2 } };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_siawase01_1[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 ef_siawase01_1[] = {
#include "assets/ef_siawase01_1.inc"
};
#endif

#ifdef TARGET_PC
u8 ef_siawase01_2_int_i4[0x80];
#else
u8 ef_siawase01_2_int_i4[] = {
#include "assets/ef_siawase01_2_int_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_siawase01_00_v[0x110 / sizeof(Vtx)];
#else
Vtx ef_siawase01_00_v[] = {
#include "assets/ef_siawase01_00_v.inc"
};
#endif

Gfx ef_siawase01_00_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, ENVIRONMENT, TEXEL0, PRIMITIVE,
                       ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0),
    gsDPSetEnvColor(255, 255, 0, 230),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, ef_siawase01_1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 13, 13),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, ef_siawase01_2_int_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_siawase01_00_v, 17, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 2, 5, 6, 2),
    gsSPNTriangles_5b(7, 8, 2, 9, 10, 2, 11, 12, 2, 13, 14, 2),
    gsSPNTriangles_5b(15, 16, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_siawase01_0[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 ef_siawase01_0[] = {
#include "assets/ef_siawase01_0.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_siawase01_01_v[0x40 / sizeof(Vtx)];
#else
Vtx ef_siawase01_01_v[] = {
#include "assets/ef_siawase01_01_v.inc"
};
#endif

Gfx ef_siawase01_01_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, ef_siawase01_0),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_siawase01_01_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};
