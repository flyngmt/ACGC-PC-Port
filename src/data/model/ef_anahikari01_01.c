#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_anahikari01_02_int_i4[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 ef_anahikari01_02_int_i4[] = {
#include "assets/ef_anahikari01_02_int_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_anahikari01_01_v[0x140 / sizeof(Vtx)];
#else
Vtx ef_anahikari01_01_v[] = {
#include "assets/ef_anahikari01_01_v.inc"
};
#endif

Gfx ef_anahikari01_01_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, TEXEL1_ALPHA, 0, TEXEL0, 0, TEXEL1, 0, PRIMITIVE, ENVIRONMENT, COMBINED, ENVIRONMENT,
                       COMBINED, 0, PRIMITIVE, 0),
    gsDPSetEnvColor(255, 255, 0, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, ef_anahikari01_02_int_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, ef_anahikari01_02_int_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_anahikari01_01_v, 20, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(4, 5, 3, 4, 6, 5, 6, 7, 5, 6, 8, 7),
    gsSPNTriangles_5b(8, 9, 7, 10, 11, 12, 13, 10, 12, 13, 12, 14),
    gsSPNTriangles_5b(15, 13, 14, 15, 14, 16, 17, 15, 16, 17, 16, 18),
    gsSPNTriangles_5b(19, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_anahikari01_01_int_i4[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 ef_anahikari01_01_int_i4[] = {
#include "assets/ef_anahikari01_01_int_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_anahikari01_02_v[0x140 / sizeof(Vtx)];
#else
Vtx ef_anahikari01_02_v[] = {
#include "assets/ef_anahikari01_02_v.inc"
};
#endif

Gfx ef_anahikari01_02_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, TEXEL1_ALPHA, 0, TEXEL0, 0, TEXEL1, 0, PRIMITIVE, ENVIRONMENT, COMBINED, ENVIRONMENT,
                       COMBINED, 0, PRIMITIVE, 0),
    gsDPSetEnvColor(255, 255, 0, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, ef_anahikari01_01_int_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, ef_anahikari01_01_int_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_anahikari01_02_v, 20, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(4, 5, 3, 4, 6, 5, 6, 7, 5, 6, 8, 7),
    gsSPNTriangles_5b(8, 9, 7, 10, 11, 12, 13, 10, 12, 13, 12, 14),
    gsSPNTriangles_5b(15, 13, 14, 15, 14, 16, 17, 15, 16, 17, 16, 18),
    gsSPNTriangles_5b(19, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

EVW_ANIME_SCROLL ef_anahikari01_01_evw_anime_2[] = { { 1, 0, 32, 16 }, { -2, 0, 32, 16 } };

EVW_ANIME_DATA ef_anahikari01_01_evw_anime[] = { { -1, EVW_ANIME_TYPE_SCROLL2, ef_anahikari01_01_evw_anime_2 } };

EVW_ANIME_SCROLL ef_anahikari01_02_evw_anime_2[] = { { 2, 0, 32, 16 }, { -6, 0, 32, 16 } };

EVW_ANIME_DATA ef_anahikari01_02_evw_anime[] = { { -1, EVW_ANIME_TYPE_SCROLL2, ef_anahikari01_02_evw_anime_2 } };
