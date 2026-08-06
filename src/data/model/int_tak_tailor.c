#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_tailor_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_tailor_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_tailor_pal[] = {
#include "assets/int_tak_tailor_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_tailor_body_tex[0x400];
#else
u8 int_tak_tailor_body_tex[] = {
#include "assets/int_tak_tailor_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_tailor_grass_tex[0x80];
#else
u8 int_tak_tailor_grass_tex[] = {
#include "assets/int_tak_tailor_grass_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_tailor_roof_tex[0x80];
#else
u8 int_tak_tailor_roof_tex[] = {
#include "assets/int_tak_tailor_roof_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_tailor_sign_tex[0x100];
#else
u8 int_tak_tailor_sign_tex[] = {
#include "assets/int_tak_tailor_sign_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_tailor_tent_tex[0x20];
#else
u8 int_tak_tailor_tent_tex[] = {
#include "assets/int_tak_tailor_tent_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_tailor_v[0x700 / sizeof(Vtx)];
#else
Vtx int_tak_tailor_v[] = {
#include "assets/int_tak_tailor_v.inc"
};
#endif

Gfx int_tak_tailor_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_tailor_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_tailor_roof_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_tailor_v, 16, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 11, 9, 8, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_tailor_grass_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_tailor_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_tailor_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_tak_tailor_tent_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_tailor_v[16], 14, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 1, 0),
    gsSPNTriangles_5b(2, 5, 3, 3, 5, 6, 3, 6, 7, 0, 3, 7),
    gsSPNTriangles_5b(0, 7, 8, 9, 4, 0, 9, 0, 8, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_tak_tailor_sign_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 10, 11, 12, 10, 12, 13, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 128, int_tak_tailor_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_tailor_v[30], 32, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 9, 11, 12, 13, 14, 15, 13, 15, 16),
    gsSPNTriangles_5b(17, 18, 19, 17, 19, 20, 21, 22, 23, 21, 23, 24),
    gsSPNTriangles_5b(25, 26, 27, 25, 27, 28, 29, 30, 31, 0, 0, 0),
    gsSPVertex(&int_tak_tailor_v[62], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(5, 7, 8, 5, 8, 6, 9, 10, 11, 9, 11, 12),
    gsSPNTriangles_5b(13, 14, 15, 13, 15, 16, 17, 18, 19, 17, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 21, 23, 24, 25, 26, 27, 25, 27, 28),
    gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_tak_tailor_v[94], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_tailor_offT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 128, int_tak_tailor_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_tailor_v[97], 15, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPEndDisplayList(),
};
