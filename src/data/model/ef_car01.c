#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx ef_car01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_car01_1_int_i4[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 ef_car01_1_int_i4[] = {
#include "assets/ef_car01_1_int_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_car01_v[0x250 / sizeof(Vtx)];
#else
Vtx ef_car01_v[] = {
#include "assets/ef_car01_v.inc"
};
#endif

Gfx ef_car01_modelT[] = {
    gsSPTexture(5000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, TEXEL1, 0, 0, 0, 0, COMBINED, COMBINED, 0, PRIMITIVE, 0),
    gsDPSetPrimColor(0, 130, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, ef_car01_1_int_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 1),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, ef_car01_1_int_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 3, 1),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_EQUAL),
    gsSPVertex(ef_car01_v, 32, 0),
    gsSPNTrianglesInit_5b(36, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 9, 11, 10, 9, 12, 11),
    gsSPNTriangles_5b(10, 11, 13, 11, 14, 13, 14, 11, 15, 14, 16, 17),
    gsSPNTriangles_5b(16, 14, 15, 18, 19, 20, 21, 18, 22, 18, 23, 24),
    gsSPNTriangles_5b(25, 8, 10, 24, 26, 22, 24, 22, 18, 18, 20, 23),
    gsSPNTriangles_5b(26, 25, 10, 26, 10, 22, 27, 21, 22, 22, 10, 27),
    gsSPNTriangles_5b(9, 8, 28, 12, 28, 26, 8, 25, 28, 24, 29, 30),
    gsSPNTriangles_5b(12, 26, 31, 25, 26, 28, 24, 23, 29, 24, 30, 31),
    gsSPNTriangles_5b(26, 24, 31, 12, 9, 28, 29, 19, 30, 20, 19, 29),
    gsSPNTriangles_5b(23, 20, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, TEXEL0, 0, 0, 0, 0, COMBINED, COMBINED, 0, PRIMITIVE, 0),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, ef_car01_1_int_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, ef_car01_1_int_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_2_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&ef_car01_v[32], 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 0, 2, 2, 4, 3),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
u8 ef_carhosi01_01[0x400];
#else
u8 ef_carhosi01_01[] = {
#include "assets/ef_carhosi01_01.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_carhosi01_00_v[0x40 / sizeof(Vtx)];
#else
Vtx ef_carhosi01_00_v[] = {
#include "assets/ef_carhosi01_00_v.inc"
};
#endif

Gfx ef_carhosi01_00_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, ef_carhosi01_01),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_carhosi01_00_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};
