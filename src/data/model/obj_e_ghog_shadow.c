#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_e_ghog_shadow_tex[0x40];
#else
ATTRIBUTE_ALIGN(32) u8 obj_e_ghog_shadow_tex[] = {
#include "assets/obj_e_ghog_shadow_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_ghog_shadow_v[0xA0 / sizeof(Vtx)];
#else
Vtx obj_e_ghog_shadow_v[] = {
#include "assets/obj_e_ghog_shadow_v.inc"
};
#endif

Gfx obj_e_ghog_shadow_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 8, 16, obj_e_ghog_shadow_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(anime_1_txt, 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 3, 4, 5),
    gsSPNTriangles_5b(3, 1, 4, 2, 3, 6, 3, 7, 6, 8, 1, 0),
    gsSPNTriangles_5b(9, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
