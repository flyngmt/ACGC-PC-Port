#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx ef_daruma01_02_v[];
extern Vtx ef_daruma01_01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 ef_daruma01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 ef_daruma01_pal[] = {
#include "assets/ef_daruma01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 ef_daruma01_00_tex[0x80];
#else
u8 ef_daruma01_00_tex[] = {
#include "assets/ef_daruma01_00_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_daruma01_00_v[0x1D0 / sizeof(Vtx)];
#else
Vtx ef_daruma01_00_v[] = {
#include "assets/ef_daruma01_00_v.inc"
};
#endif

Gfx ef_daruma01_00_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, ef_daruma01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ef_daruma01_00_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_daruma01_00_v, 29, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 2, 3, 4, 2, 1, 3),
    gsSPNTriangles_5b(5, 6, 7, 6, 8, 7, 9, 10, 11, 9, 0, 10),
    gsSPNTriangles_5b(12, 13, 9, 14, 15, 12, 16, 17, 14, 9, 18, 0),
    gsSPNTriangles_5b(0, 19, 20, 21, 22, 23, 21, 23, 5, 24, 25, 26),
    gsSPNTriangles_5b(27, 24, 26, 26, 25, 28, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
Vtx ef_daruma01_01_v[0x280 / sizeof(Vtx)];
#else
Vtx ef_daruma01_01_v[] = {
#include "assets/ef_daruma01_01_v.inc"
};
#endif

Gfx ef_daruma01_01_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, ef_daruma01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ef_daruma01_00_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_daruma01_01_v, 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 2, 3, 4, 2, 1, 3),
    gsSPNTriangles_5b(5, 6, 7, 6, 8, 7, 9, 10, 11, 11, 12, 13),
    gsSPNTriangles_5b(14, 15, 10, 16, 17, 14, 12, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 27, 24, 26, 26, 25, 28),
    gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&ef_daruma01_01_v[32], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
Vtx ef_daruma01_02_v[0x280 / sizeof(Vtx)];
#else
Vtx ef_daruma01_02_v[] = {
#include "assets/ef_daruma01_02_v.inc"
};
#endif

Gfx ef_daruma01_02_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, ef_daruma01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ef_daruma01_00_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_daruma01_02_v, 32, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 3, 4, 0, 4, 1, 0),
    gsSPNTriangles_5b(5, 6, 7, 5, 8, 6, 9, 10, 11, 11, 12, 13),
    gsSPNTriangles_5b(11, 10, 12, 14, 15, 16, 15, 17, 16, 18, 19, 20),
    gsSPNTriangles_5b(20, 21, 18, 18, 22, 19, 23, 24, 21, 25, 26, 23),
    gsSPNTriangles_5b(22, 27, 28, 29, 30, 31, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&ef_daruma01_02_v[32], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 3, 5),
    gsSPNTriangles_5b(5, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
