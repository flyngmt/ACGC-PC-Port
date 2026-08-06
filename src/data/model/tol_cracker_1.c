#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_cracker_1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_cracker_1_pal[] = {
#include "assets/tol_cracker_1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_cracker_1_tex[0x200];
#else
u8 tol_cracker_1_tex[] = {
#include "assets/tol_cracker_1_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_cracker_1_v[0x1C0 / sizeof(Vtx)];
#else
Vtx tol_cracker_1_v[] = {
#include "assets/tol_cracker_1_v.inc"
};
#endif

Gfx tol_cracker_1T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_cracker_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, tol_cracker_1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_cracker_1_v, 28, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 4, 0, 5, 6),
    gsSPNTriangles_5b(7, 8, 0, 9, 10, 0, 11, 12, 0, 0, 13, 14),
    gsSPNTriangles_5b(0, 15, 16, 0, 8, 17, 18, 5, 0, 19, 20, 0),
    gsSPNTriangles_5b(21, 22, 0, 23, 24, 25, 23, 26, 24, 26, 27, 24),
    gsSPNTriangles_5b(27, 25, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
