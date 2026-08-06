#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx ef_wipe1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_wape_tex[0x40];
#else
ATTRIBUTE_ALIGN(32) u8 ef_wape_tex[] = {
#include "assets/ef_wape_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_wipe1_v[0x440 / sizeof(Vtx)];
#else
Vtx ef_wipe1_v[] = {
#include "assets/ef_wipe1_v.inc"
};
#endif

Gfx ef_wipe1_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 0, 0, 0, 255),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS, G_RM_CLD_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 8, ef_wape_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPDisplayList(anime_2_txt),
    gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_wipe1_v, 32, 0),
    gsSPNTrianglesInit_5b(30, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsSPNTriangles_5b(2, 5, 0, 0, 6, 4, 0, 5, 7, 8, 0, 9),
    gsSPNTriangles_5b(0, 7, 10, 0, 10, 11, 0, 11, 9, 0, 12, 13),
    gsSPNTriangles_5b(0, 14, 12, 0, 15, 14, 6, 0, 13, 0, 16, 15),
    gsSPNTriangles_5b(0, 8, 17, 18, 0, 19, 0, 17, 20, 0, 20, 21),
    gsSPNTriangles_5b(0, 21, 19, 0, 22, 23, 0, 24, 22, 0, 25, 24),
    gsSPNTriangles_5b(26, 0, 23, 0, 27, 25, 0, 18, 28, 27, 0, 29),
    gsSPNTriangles_5b(0, 28, 30, 0, 30, 31, 0, 31, 29, 0, 0, 0),
    gsSPVertex(&ef_wipe1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsSPNTriangles_5b(5, 0, 2, 0, 6, 4, 0, 5, 7, 8, 0, 9),
    gsSPNTriangles_5b(0, 7, 10, 0, 10, 11, 0, 11, 9, 0, 12, 13),
    gsSPNTriangles_5b(0, 14, 12, 0, 15, 14, 6, 0, 13, 0, 16, 15),
    gsSPNTriangles_5b(0, 17, 18, 19, 0, 20, 0, 18, 21, 0, 21, 22),
    gsSPNTriangles_5b(0, 22, 20, 0, 23, 24, 0, 25, 23, 0, 26, 25),
    gsSPNTriangles_5b(27, 0, 24, 0, 28, 26, 0, 19, 29, 30, 28, 0),
    gsSPNTriangles_5b(0, 29, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&ef_wipe1_v[64], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
