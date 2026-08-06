#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx tol_kenjyu_1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_kenjyu_1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_kenjyu_1_pal[] = {
#include "assets/tol_kenjyu_1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_kenjyu_1_tex[0x200];
#else
u8 tol_kenjyu_1_tex[] = {
#include "assets/tol_kenjyu_1_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_kenjyu_1_v[0x410 / sizeof(Vtx)];
#else
Vtx tol_kenjyu_1_v[] = {
#include "assets/tol_kenjyu_1_v.inc"
};
#endif

Gfx tol_kenjyu_1T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_kenjyu_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kenjyu_1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_kenjyu_1_v, 32, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 6, 9, 10, 6, 6, 10, 7, 11, 12, 13),
    gsSPNTriangles_5b(14, 15, 16, 17, 18, 19, 20, 21, 22, 20, 22, 23),
    gsSPNTriangles_5b(24, 25, 26, 24, 26, 27, 28, 29, 30, 28, 30, 31),
    gsSPVertex(&tol_kenjyu_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 6, 7, 8, 6, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 14, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 23, 24, 22, 24, 25, 26, 27, 28),
    gsSPNTriangles_5b(26, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&tol_kenjyu_1_v[62], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
