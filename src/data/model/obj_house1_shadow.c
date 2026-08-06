#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_house1_shadow[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_house1_shadow[] = {
#include "assets/obj_house1_shadow.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_house1_shadow_v[0x140 / sizeof(Vtx)];
#else
Vtx obj_house1_shadow_v[] = {
#include "assets/obj_house1_shadow_v.inc"
};
#endif

Gfx obj_house1_shadow_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_house1_shadow),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(anime_1_txt, 20, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 6, 7, 1, 6, 1, 0, 6, 7, 8),
    gsSPNTriangles_5b(6, 8, 9, 10, 11, 4, 10, 4, 5, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 15, 14, 16, 15, 16, 17, 17, 16, 18),
    gsSPNTriangles_5b(17, 18, 19, 5, 4, 2, 5, 2, 3, 0, 1, 7),
    gsSPNTriangles_5b(0, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_house2_shadow_tex_txt[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_house2_shadow_tex_txt[] = {
#include "assets/obj_s_house2_shadow_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_house2_shadow_v[0x1C0 / sizeof(Vtx)];
#else
Vtx obj_s_house2_shadow_v[] = {
#include "assets/obj_s_house2_shadow_v.inc"
};
#endif

Gfx obj_s_house2_shadow_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_s_house2_shadow_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsSPVertex(anime_1_txt, 28, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 5, 4, 6, 5, 6, 7, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_house3_shadow_tex_txt[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_house3_shadow_tex_txt[] = {
#include "assets/obj_s_house3_shadow_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_house3_shadow_v[0x180 / sizeof(Vtx)];
#else
Vtx obj_s_house3_shadow_v[] = {
#include "assets/obj_s_house3_shadow_v.inc"
};
#endif

Gfx obj_s_house3_shadow_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_s_house3_shadow_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsSPVertex(anime_1_txt, 24, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 5, 4, 6, 5, 6, 7, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_house4_shadow_tex_txt[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_house4_shadow_tex_txt[] = {
#include "assets/obj_s_house4_shadow_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_house4_shadow_v[0x1C0 / sizeof(Vtx)];
#else
Vtx obj_s_house4_shadow_v[] = {
#include "assets/obj_s_house4_shadow_v.inc"
};
#endif

Gfx obj_s_house4_shadow_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_s_house4_shadow_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 124),
    gsSPVertex(anime_1_txt, 28, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 5, 4, 6, 5, 6, 7, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_house5_shadow_tex_txt[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_house5_shadow_tex_txt[] = {
#include "assets/obj_s_house5_shadow_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_house5_shadow_v[0x1C0 / sizeof(Vtx)];
#else
Vtx obj_s_house5_shadow_v[] = {
#include "assets/obj_s_house5_shadow_v.inc"
};
#endif

Gfx obj_s_house5_shadow_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_s_house5_shadow_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 124),
    gsSPVertex(anime_1_txt, 28, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 5, 4, 6, 5, 6, 7, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
