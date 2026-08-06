#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx tol_kamicup_1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_kamicup_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_kamicup_pal[] = {
#include "assets/tol_kamicup_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_kamicup_tex[0x200];
#else
u8 tol_kamicup_tex[] = {
#include "assets/tol_kamicup_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_kamicup_1_v[0x330 / sizeof(Vtx)];
#else
Vtx tol_kamicup_1_v[] = {
#include "assets/tol_kamicup_1_v.inc"
};
#endif

Gfx tol_kamicup_1T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_kamicup_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kamicup_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_kamicup_1_v, 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 3, 4, 2, 3, 5, 4),
    gsSPNTriangles_5b(3, 6, 5, 3, 7, 6, 8, 9, 7, 10, 9, 1),
    gsSPNTriangles_5b(11, 10, 1, 12, 11, 1, 13, 12, 1, 14, 13, 1),
    gsSPNTriangles_5b(14, 1, 0, 15, 16, 17, 15, 17, 18, 19, 20, 16),
    gsSPNTriangles_5b(19, 16, 15, 21, 22, 23, 21, 23, 24, 25, 26, 22),
    gsSPNTriangles_5b(25, 22, 21, 27, 28, 29, 27, 29, 30, 0, 0, 0),
    gsSPVertex(&tol_kamicup_1_v[31], 20, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 6, 7, 5, 6, 5, 4, 8, 9, 7),
    gsSPNTriangles_5b(8, 7, 6, 10, 11, 9, 10, 9, 8, 12, 13, 11),
    gsSPNTriangles_5b(12, 11, 10, 14, 15, 13, 14, 13, 12, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
