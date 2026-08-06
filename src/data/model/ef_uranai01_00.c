#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_uranai01_0_int_i4[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 ef_uranai01_0_int_i4[] = {
#include "assets/ef_uranai01_0_int_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 ef_uranai01_1_int_i4[0x200];
#else
u8 ef_uranai01_1_int_i4[] = {
#include "assets/ef_uranai01_1_int_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_uranai01_00_v[0xD0 / sizeof(Vtx)];
#else
Vtx ef_uranai01_00_v[] = {
#include "assets/ef_uranai01_00_v.inc"
};
#endif

Gfx ef_uranai01_00_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, TEXEL1, 0, TEXEL0, 0, TEXEL1, 0, PRIMITIVE, ENVIRONMENT, COMBINED, ENVIRONMENT,
                       COMBINED, 0, PRIMITIVE, 0),
    gsDPSetEnvColor(255, 0, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, ef_uranai01_0_int_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 15, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, ef_uranai01_1_int_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 15, 15),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_uranai01_00_v, 13, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(1, 5, 4, 1, 6, 5, 1, 7, 6, 1, 8, 7),
    gsSPNTriangles_5b(1, 9, 8, 1, 10, 9, 1, 11, 10, 1, 12, 11),
    gsSPEndDisplayList(),
};

EVW_ANIME_SCROLL ef_uranai01_00_evw_anime_1[] = { { -1, 0, 32, 32 }, { 1, 7, 32, 32 } };

EVW_ANIME_DATA ef_uranai01_00_evw_anime[] = { { -1, EVW_ANIME_TYPE_SCROLL2, ef_uranai01_00_evw_anime_1 } };
