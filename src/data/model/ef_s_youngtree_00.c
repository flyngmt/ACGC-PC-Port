#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_s_yungtree_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 ef_s_yungtree_tex[] = {
#include "assets/ef_s_yungtree_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_s_youngtree_00_v[0x50 / sizeof(Vtx)];
#else
Vtx ef_s_youngtree_00_v[] = {
#include "assets/ef_s_youngtree_00_v.inc"
};
#endif

Gfx ef_s_youngtree_00_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, ef_s_yungtree_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_s_youngtree_00_v, 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 0, 2),
    gsSPNTriangles_5b(3, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_w_youngtree_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 ef_w_youngtree_tex[] = {
#include "assets/ef_w_youngtree_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_w_youngtree_00_v[0x50 / sizeof(Vtx)];
#else
Vtx ef_w_youngtree_00_v[] = {
#include "assets/ef_w_youngtree_00_v.inc"
};
#endif

Gfx ef_w_youngtree_00_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, ef_w_youngtree_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_w_youngtree_00_v, 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 0, 2),
    gsSPNTriangles_5b(3, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_f_youngtree_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 ef_f_youngtree_tex[] = {
#include "assets/ef_f_youngtree_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_f_youngtree_00_v[0x50 / sizeof(Vtx)];
#else
Vtx ef_f_youngtree_00_v[] = {
#include "assets/ef_f_youngtree_00_v.inc"
};
#endif

Gfx ef_f_youngtree_00_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, ef_f_youngtree_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_f_youngtree_00_v, 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 0, 2),
    gsSPNTriangles_5b(3, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_s_young_palm_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 ef_s_young_palm_tex[] = {
#include "assets/ef_s_young_palm_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_s_young_palm_v[0x60 / sizeof(Vtx)];
#else
Vtx ef_s_young_palm_v[] = {
#include "assets/ef_s_young_palm_v.inc"
};
#endif

Gfx ef_s_young_palm_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, ef_s_young_palm_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_s_young_palm_v, 6, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 0, 3, 1, 4, 1, 5),
    gsSPNTriangles_5b(4, 2, 1, 3, 5, 1, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_w_young_palm_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 ef_w_young_palm_tex[] = {
#include "assets/ef_w_young_palm_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_w_young_palm_v[0x60 / sizeof(Vtx)];
#else
Vtx ef_w_young_palm_v[] = {
#include "assets/ef_w_young_palm_v.inc"
};
#endif

Gfx ef_w_young_palm_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, ef_w_young_palm_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_w_young_palm_v, 6, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 0, 3, 1, 4, 1, 5),
    gsSPNTriangles_5b(4, 2, 1, 3, 5, 1, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_s_young_cedar_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 ef_s_young_cedar_tex[] = {
#include "assets/ef_s_young_cedar_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_s_young_cedar_v[0x60 / sizeof(Vtx)];
#else
Vtx ef_s_young_cedar_v[] = {
#include "assets/ef_s_young_cedar_v.inc"
};
#endif

Gfx ef_s_young_cedar_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, ef_s_young_cedar_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_s_young_cedar_v, 6, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 2, 3, 0, 3, 4, 0),
    gsSPNTriangles_5b(0, 5, 1, 0, 4, 5, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 ef_w_young_cedar_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 ef_w_young_cedar_tex[] = {
#include "assets/ef_w_young_cedar_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx ef_w_young_cedar_v[0x60 / sizeof(Vtx)];
#else
Vtx ef_w_young_cedar_v[] = {
#include "assets/ef_w_young_cedar_v.inc"
};
#endif

Gfx ef_w_young_cedar_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, ef_w_young_cedar_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_w_young_cedar_v, 6, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 2, 3, 0, 3, 4, 0),
    gsSPNTriangles_5b(0, 5, 1, 0, 4, 5, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
