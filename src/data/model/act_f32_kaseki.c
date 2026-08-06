#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 act_f32_kaseki_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 act_f32_kaseki_pal[] = {
#include "assets/act_f32_kaseki_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 act_f32_kaseki_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 act_f32_kaseki_tex[] = {
#include "assets/act_f32_kaseki_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_f32_kaseki_a_v[0xA0 / sizeof(Vtx)];
#else
Vtx act_f32_kaseki_a_v[] = {
#include "assets/act_f32_kaseki_a_v.inc"
};
#endif

Gfx act_f32_kaseki_aT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_f32_kaseki_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_f32_kaseki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_f32_kaseki_a_v, 10, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 2, 1, 3, 0, 2, 4),
    gsSPNTriangles_5b(2, 5, 4, 2, 3, 5, 1, 6, 3, 0, 7, 1),
    gsSPNTriangles_5b(7, 6, 1, 7, 8, 9, 7, 9, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
Vtx act_f32_kaseki_b_v[0xA0 / sizeof(Vtx)];
#else
Vtx act_f32_kaseki_b_v[] = {
#include "assets/act_f32_kaseki_b_v.inc"
};
#endif

Gfx act_f32_kasekiT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_f32_kaseki_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_f32_kaseki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_f32_kaseki_b_v, 10, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 2, 1, 3, 0, 2, 4),
    gsSPNTriangles_5b(2, 5, 4, 2, 3, 5, 1, 6, 3, 0, 7, 1),
    gsSPNTriangles_5b(7, 6, 1, 7, 8, 9, 7, 9, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
Vtx act_f32_kaseki_c_v[0xA0 / sizeof(Vtx)];
#else
Vtx act_f32_kaseki_c_v[] = {
#include "assets/act_f32_kaseki_c_v.inc"
};
#endif

Gfx act_f32_kaseki_cT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_f32_kaseki_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_f32_kaseki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_f32_kaseki_c_v, 10, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 1, 0, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 4, 7, 1, 3, 4, 1, 1, 7, 2),
    gsSPNTriangles_5b(0, 2, 8, 0, 8, 9, 3, 0, 9, 0, 0, 0),
    gsSPEndDisplayList(),
};
