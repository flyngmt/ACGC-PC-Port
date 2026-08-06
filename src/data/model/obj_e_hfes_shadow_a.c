#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_e_hfes_shadow_tex[0x40];
#else
ATTRIBUTE_ALIGN(32) u8 obj_e_hfes_shadow_tex[] = {
#include "assets/obj_e_hfes_shadow_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_hfes_shadow_a_v[0x1C0 / sizeof(Vtx)];
#else
Vtx obj_e_hfes_shadow_a_v[] = {
#include "assets/obj_e_hfes_shadow_a_v.inc"
};
#endif

Gfx obj_e_hfes_shadow_a_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 8, 16, obj_e_hfes_shadow_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(anime_1_txt, 28, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(5, 0, 4, 6, 7, 8, 7, 9, 8, 7, 10, 9),
    gsSPNTriangles_5b(7, 11, 10, 12, 13, 14, 12, 14, 15, 12, 15, 16),
    gsSPNTriangles_5b(17, 12, 16, 18, 19, 20, 19, 21, 20, 19, 22, 21),
    gsSPNTriangles_5b(19, 23, 22, 24, 25, 26, 24, 26, 27, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
Vtx obj_e_hfes_shadow_b_v[0x1C0 / sizeof(Vtx)];
#else
Vtx obj_e_hfes_shadow_b_v[] = {
#include "assets/obj_e_hfes_shadow_b_v.inc"
};
#endif

Gfx obj_e_hfes_shadow_b_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 8, 16, obj_e_hfes_shadow_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(anime_1_txt, 28, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 0, 2, 4, 3, 2),
    gsSPNTriangles_5b(4, 2, 5, 6, 7, 8, 6, 9, 7, 9, 10, 7),
    gsSPNTriangles_5b(10, 11, 7, 12, 13, 14, 15, 12, 14, 16, 15, 14),
    gsSPNTriangles_5b(16, 14, 17, 18, 19, 20, 18, 21, 19, 21, 22, 19),
    gsSPNTriangles_5b(22, 23, 19, 24, 25, 26, 25, 27, 26, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
Vtx obj_e_hfes_shadow_c_v[0x1C0 / sizeof(Vtx)];
#else
Vtx obj_e_hfes_shadow_c_v[] = {
#include "assets/obj_e_hfes_shadow_c_v.inc"
};
#endif

Gfx obj_e_hfes_shadow_c_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 8, 16, obj_e_hfes_shadow_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(anime_1_txt, 28, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 0, 2, 4, 3, 2),
    gsSPNTriangles_5b(4, 2, 5, 6, 7, 8, 6, 9, 7, 9, 10, 7),
    gsSPNTriangles_5b(10, 11, 7, 12, 13, 14, 15, 12, 14, 16, 15, 14),
    gsSPNTriangles_5b(16, 14, 17, 18, 19, 20, 18, 21, 19, 21, 22, 19),
    gsSPNTriangles_5b(22, 23, 19, 24, 25, 26, 24, 27, 25, 0, 0, 0),
    gsSPEndDisplayList(),
};
