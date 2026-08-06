#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx tol_npcsao_1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_npcsao_1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_npcsao_1_pal[] = {
#include "assets/tol_npcsao_1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_npcsao_1_tex[0x200];
#else
u8 tol_npcsao_1_tex[] = {
#include "assets/tol_npcsao_1_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_npcsao_1_v[0x470 / sizeof(Vtx)];
#else
Vtx tol_npcsao_1_v[] = {
#include "assets/tol_npcsao_1_v.inc"
};
#endif

Gfx tol_npcsao_1_sao_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_npcsao_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, tol_npcsao_1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_npcsao_1_v, 30, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 3, 4, 6, 7, 4, 7, 5, 6, 8, 7),
    gsSPNTriangles_5b(9, 10, 11, 9, 11, 12, 11, 13, 14, 11, 14, 12),
    gsSPNTriangles_5b(13, 15, 16, 13, 16, 14, 15, 17, 16, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 20, 22, 23, 20, 23, 21, 22, 24, 25),
    gsSPNTriangles_5b(22, 25, 23, 24, 26, 25, 27, 28, 29, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_npcsao_1_uki_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_npcsao_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, tol_npcsao_1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&tol_npcsao_1_v[30], 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 2, 1, 8, 6, 5, 8, 4, 7, 9),
    gsSPNTriangles_5b(0, 3, 9, 10, 11, 12, 10, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 12, 11, 18, 16, 15, 18, 14, 17, 19),
    gsSPNTriangles_5b(10, 13, 19, 20, 21, 22, 21, 23, 22, 23, 20, 22),
    gsSPNTriangles_5b(24, 25, 26, 27, 28, 26, 29, 30, 31, 0, 0, 0),
    gsSPVertex(&tol_npcsao_1_v[62], 9, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 1, 0, 7, 0, 8, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
