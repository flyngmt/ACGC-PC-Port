#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_e_yatai_shadow_tex[0x40];
#else
ATTRIBUTE_ALIGN(32) u8 obj_e_yatai_shadow_tex[] = {
#include "assets/obj_e_yatai_shadow_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_yatai_shadow_l_v[0x70 / sizeof(Vtx)];
#else
Vtx obj_e_yatai_shadow_l_v[] = {
#include "assets/obj_e_yatai_shadow_l_v.inc"
};
#endif

Gfx obj_e_yatai_shadow_l_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 8, 16, obj_e_yatai_shadow_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(anime_1_txt, 7, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 3, 4, 5),
    gsSPNTriangles_5b(3, 1, 4, 2, 3, 6, 3, 5, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
Vtx obj_e_yatai_shadow_r_v[0x70 / sizeof(Vtx)];
#else
Vtx obj_e_yatai_shadow_r_v[] = {
#include "assets/obj_e_yatai_shadow_r_v.inc"
};
#endif

Gfx obj_e_yatai_shadow_r_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 8, 16, obj_e_yatai_shadow_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(anime_1_txt, 7, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 1, 4, 5, 3),
    gsSPNTriangles_5b(5, 1, 3, 6, 3, 0, 6, 4, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
