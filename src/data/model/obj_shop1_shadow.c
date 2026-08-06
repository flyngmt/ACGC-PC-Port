#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_shop1_shadow[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_shop1_shadow[] = {
#include "assets/obj_shop1_shadow.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop1_shadow_v[0x80 / sizeof(Vtx)];
#else
Vtx obj_shop1_shadow_v[] = {
#include "assets/obj_shop1_shadow_v.inc"
};
#endif

Gfx obj_shop1_shadowT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_shop1_shadow),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(anime_1_txt, 8, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 2, 1, 4),
    gsSPNTriangles_5b(1, 5, 4, 4, 5, 6, 4, 6, 7, 6, 3, 0),
    gsSPNTriangles_5b(7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_shop2_shadow[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_shop2_shadow[] = {
#include "assets/obj_shop2_shadow.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop2_shadow_v[0xC0 / sizeof(Vtx)];
#else
Vtx obj_shop2_shadow_v[] = {
#include "assets/obj_shop2_shadow_v.inc"
};
#endif

Gfx obj_shop2_shadowT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_shop2_shadow),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(anime_1_txt, 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 5, 8, 5, 4, 10, 11, 9),
    gsSPNTriangles_5b(10, 9, 8, 7, 6, 11, 7, 11, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_shop3_shadow[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_shop3_shadow[] = {
#include "assets/obj_shop3_shadow.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop3_shadow_v[0x80 / sizeof(Vtx)];
#else
Vtx obj_shop3_shadow_v[] = {
#include "assets/obj_shop3_shadow_v.inc"
};
#endif

Gfx obj_shop3_shadowT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_shop3_shadow),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(anime_1_txt, 8, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 6, 7, 5, 6, 5, 4, 3, 2, 7),
    gsSPNTriangles_5b(3, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_shop4_shadow_txt[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_shop4_shadow_txt[] = {
#include "assets/obj_shop4_shadow_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop4_shadow_v[0xC0 / sizeof(Vtx)];
#else
Vtx obj_shop4_shadow_v[] = {
#include "assets/obj_shop4_shadow_v.inc"
};
#endif

Gfx obj_shop4_shadowT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_shop4_shadow_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(anime_1_txt, 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 3, 6, 7, 8, 6, 8, 9, 10, 11, 7),
    gsSPNTriangles_5b(10, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
