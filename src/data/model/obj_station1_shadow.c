#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_station1_shadow_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_station1_shadow_tex[] = {
#include "assets/obj_station1_shadow_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_station1_shadow_v[0x1F0 / sizeof(Vtx)];
#else
Vtx obj_station1_shadow_v[] = {
#include "assets/obj_station1_shadow_v.inc"
};
#endif

Gfx obj_station1_shadow_hiT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_station1_shadow_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(anime_1_txt, 19, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 12, 6, 7),
    gsSPNTriangles_5b(12, 13, 6, 14, 13, 15, 14, 16, 13, 4, 17, 18),
    gsSPNTriangles_5b(9, 11, 8, 10, 9, 8, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_station1_shadow_lowT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_station1_shadow_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(anime_1_txt + 0x130, 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsSPNTriangles_5b(5, 6, 7, 5, 8, 6, 8, 9, 6, 10, 11, 9),
    gsSPNTriangles_5b(11, 6, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
u8 obj_station2_shadow_tex_txt[0x200];
#else
u8 obj_station2_shadow_tex_txt[] = {
#include "assets/obj_station2_shadow_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_station2_shadow_v[0x400 / sizeof(Vtx)];
#else
Vtx obj_station2_shadow_v[] = {
#include "assets/obj_station2_shadow_v.inc"
};
#endif

Gfx obj_station2_shadow_low_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_station2_shadow_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(anime_1_txt + 0x2C0, 20, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 0, 7, 0, 9, 10, 11, 12, 10, 12, 13),
    gsSPNTriangles_5b(14, 15, 16, 14, 16, 17, 18, 15, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_station2_shadow_hi_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_station2_shadow_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(anime_1_txt, 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 16, 17, 18, 16, 19, 17, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(anime_1_txt + 0x200, 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_station3_shadow_tex_txt[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_station3_shadow_tex_txt[] = {
#include "assets/obj_station3_shadow_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_station3_shadow_v[0x3E0 / sizeof(Vtx)];
#else
Vtx obj_station3_shadow_v[] = {
#include "assets/obj_station3_shadow_v.inc"
};
#endif

Gfx obj_station3_shadow_low_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_station3_shadow_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(anime_1_txt + 0x2C0, 18, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 6, 8, 7, 9, 10, 11, 9, 11, 12),
    gsSPNTriangles_5b(13, 14, 15, 14, 16, 15, 14, 17, 16, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_station3_shadow_hi_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_station3_shadow_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(anime_1_txt, 32, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 3, 5),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(19, 16, 18, 20, 21, 22, 20, 23, 21, 8, 24, 9),
    gsSPNTriangles_5b(2, 7, 0, 25, 26, 27, 25, 27, 28, 29, 30, 31),
    gsSPVertex(anime_1_txt + 0x200, 12, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
