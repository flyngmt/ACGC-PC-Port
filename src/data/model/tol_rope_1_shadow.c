#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 tol_rope_1_shadow_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 tol_rope_1_shadow_tex[] = {
#include "assets/tol_rope_1_shadow_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_rope_1_shadow_v[0x200 / sizeof(Vtx)];
#else
Vtx tol_rope_1_shadow_v[] = {
#include "assets/tol_rope_1_shadow_v.inc"
};
#endif

Gfx tol_rope_1_shadowT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 10, 0, 50, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_rope_1_shadow_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_rope_1_shadow_v, 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 6, 7, 8, 6, 8, 9, 5, 4, 10),
    gsSPNTriangles_5b(5, 10, 11, 12, 13, 1, 12, 1, 0, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 18, 19, 20, 18, 20, 21, 22, 23, 24),
    gsSPNTriangles_5b(22, 24, 25, 26, 27, 28, 26, 28, 29, 25, 24, 30),
    gsSPNTriangles_5b(25, 30, 31, 31, 30, 19, 31, 19, 18, 0, 0, 0),
    gsSPEndDisplayList(),
};
