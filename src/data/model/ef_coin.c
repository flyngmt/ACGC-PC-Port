#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx ef_coin_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_coin_tex_txt[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 ef_coin_tex_txt[] = {
#include "assets/ef_coin_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_coin_v[0x3C0 / sizeof(Vtx)];
#else
Vtx ef_coin_v[] = {
#include "assets/ef_coin_v.inc"
};
#endif

Gfx ef_coin_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ef_coin_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 2, 2),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(ef_coin_v, 32, 0),
    gsSPNTrianglesInit_5b(25, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 0, 2, 4, 11, 12, 4, 12, 5),
    gsSPNTriangles_5b(8, 13, 9, 14, 10, 2, 11, 15, 16, 11, 16, 12),
    gsSPNTriangles_5b(13, 17, 9, 18, 14, 2, 15, 19, 20, 15, 20, 16),
    gsSPNTriangles_5b(17, 21, 9, 22, 18, 2, 19, 23, 24, 19, 24, 20),
    gsSPNTriangles_5b(21, 25, 9, 26, 22, 2, 23, 27, 28, 23, 28, 24),
    gsSPNTriangles_5b(25, 29, 9, 30, 26, 2, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&ef_coin_v[31], 29, 0),
    gsSPNTrianglesInit_5b(23, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 1, 10, 11, 1, 11, 2, 5, 12, 6),
    gsSPNTriangles_5b(13, 7, 9, 10, 14, 15, 10, 15, 11, 12, 16, 6),
    gsSPNTriangles_5b(17, 13, 9, 14, 18, 19, 14, 19, 15, 16, 20, 6),
    gsSPNTriangles_5b(21, 17, 9, 18, 22, 23, 18, 23, 19, 20, 24, 6),
    gsSPNTriangles_5b(25, 21, 9, 22, 26, 27, 22, 27, 23, 24, 28, 6),
    gsSPEndDisplayList(),
};

Gfx ef_coin_modelT[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, COMBINED, 0, PRIMITIVE, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ef_coin_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 2, 2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(ef_coin_v, 32, 0),
    gsSPNTrianglesInit_5b(25, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 0, 2, 4, 11, 12, 4, 12, 5),
    gsSPNTriangles_5b(8, 13, 9, 14, 10, 2, 11, 15, 16, 11, 16, 12),
    gsSPNTriangles_5b(13, 17, 9, 18, 14, 2, 15, 19, 20, 15, 20, 16),
    gsSPNTriangles_5b(17, 21, 9, 22, 18, 2, 19, 23, 24, 19, 24, 20),
    gsSPNTriangles_5b(21, 25, 9, 26, 22, 2, 23, 27, 28, 23, 28, 24),
    gsSPNTriangles_5b(25, 29, 9, 30, 26, 2, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&ef_coin_v[31], 29, 0),
    gsSPNTrianglesInit_5b(23, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 1, 10, 11, 1, 11, 2, 5, 12, 6),
    gsSPNTriangles_5b(13, 7, 9, 10, 14, 15, 10, 15, 11, 12, 16, 6),
    gsSPNTriangles_5b(17, 13, 9, 14, 18, 19, 14, 19, 15, 16, 20, 6),
    gsSPNTriangles_5b(21, 17, 9, 18, 22, 23, 18, 23, 19, 20, 24, 6),
    gsSPNTriangles_5b(25, 21, 9, 22, 26, 27, 22, 27, 23, 24, 28, 6),
    gsSPEndDisplayList(),
};
