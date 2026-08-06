#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_tent_shadow[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_tent_shadow[] = {
#include "assets/obj_s_tent_shadow.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_tent_shadow_v[0x1C0 / sizeof(Vtx)];
#else
Vtx obj_s_tent_shadow_v[] = {
#include "assets/obj_s_tent_shadow_v.inc"
};
#endif

Gfx obj_s_tent_shadow_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_tent_shadow),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(anime_1_txt, 28, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 0, 6, 7),
    gsSPNTriangles_5b(0, 8, 6, 3, 7, 9, 3, 0, 7, 10, 11, 9),
    gsSPNTriangles_5b(11, 3, 9, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
