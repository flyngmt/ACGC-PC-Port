#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_sori01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_sori01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_sori01_pal[] = {
#include "assets/int_tak_sori01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_sori01_body_tex[0x400];
#else
u8 int_tak_sori01_body_tex[] = {
#include "assets/int_tak_sori01_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_sori01_ita_tex[0x80];
#else
u8 int_tak_sori01_ita_tex[] = {
#include "assets/int_tak_sori01_ita_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_sori01_sofa_tex[0x100];
#else
u8 int_tak_sori01_sofa_tex[] = {
#include "assets/int_tak_sori01_sofa_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_sori01_ropeside_tex[0x40];
#else
u8 int_tak_sori01_ropeside_tex[] = {
#include "assets/int_tak_sori01_ropeside_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_sori01_v[0x9E0 / sizeof(Vtx)];
#else
Vtx int_tak_sori01_v[] = {
#include "assets/int_tak_sori01_v.inc"
};
#endif

Gfx int_tak_sori01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_sori01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, int_tak_sori01_ropeside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_sori01_v, 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 0, 2, 3, 1, 0, 4),
    gsSPNTriangles_5b(1, 4, 5, 5, 4, 6, 5, 6, 7, 7, 6, 8),
    gsSPNTriangles_5b(7, 8, 9, 9, 8, 10, 9, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 15, 14, 16, 15, 16, 17, 17, 16, 18),
    gsSPNTriangles_5b(17, 18, 19, 19, 18, 3, 19, 3, 2, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 21, 20, 24, 21, 24, 25, 25, 24, 26),
    gsSPNTriangles_5b(25, 26, 27, 27, 26, 28, 27, 28, 29, 29, 28, 30),
    gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_tak_sori01_v[32], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 5, 4, 6, 5, 6, 7, 7, 6, 8),
    gsSPNTriangles_5b(7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 32, int_tak_sori01_ita_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_sori01_v[42], 32, 0),
    gsSPNTrianglesInit_5b(29, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 6, 0, 5, 6, 5, 7, 8, 6, 7),
    gsSPNTriangles_5b(8, 7, 9, 8, 9, 10, 11, 12, 13, 12, 14, 15),
    gsSPNTriangles_5b(12, 15, 13, 14, 16, 17, 14, 17, 15, 16, 18, 19),
    gsSPNTriangles_5b(16, 19, 17, 19, 20, 21, 19, 21, 17, 18, 22, 23),
    gsSPNTriangles_5b(18, 23, 19, 24, 18, 16, 24, 16, 25, 16, 14, 25),
    gsSPNTriangles_5b(25, 14, 26, 14, 27, 26, 14, 12, 27, 12, 28, 27),
    gsSPNTriangles_5b(12, 29, 28, 30, 31, 13, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_tak_sori01_v[74], 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 5, 3, 6, 7, 8, 9, 7, 9, 10),
    gsSPNTriangles_5b(11, 7, 10, 11, 10, 12, 13, 11, 12, 8, 14, 15),
    gsSPNTriangles_5b(8, 15, 9, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 24, 20, 24, 21, 23, 16, 19, 23, 19, 24),
    gsSPNTriangles_5b(25, 26, 27, 27, 26, 28, 26, 29, 28, 26, 30, 29),
    gsSPNTriangles_5b(30, 31, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_tak_sori01_v[106], 16, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 4, 5, 6, 3, 5),
    gsSPNTriangles_5b(6, 5, 7, 8, 6, 7, 8, 7, 9, 9, 7, 10),
    gsSPNTriangles_5b(9, 10, 11, 9, 11, 12, 13, 14, 15, 13, 15, 11),
    gsSPEndDisplayList(),
};

Gfx int_tak_sori01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_sori01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_sori01_sofa_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_sori01_v[122], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 6, 7),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 2, 4, 5, 2, 5, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_tak_sori01_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_sori01_v[134], 24, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 20, 21, 5, 20, 5, 4, 19, 18, 2),
    gsSPNTriangles_5b(19, 2, 1, 11, 10, 12, 11, 12, 15, 20, 22, 23),
    gsSPNTriangles_5b(20, 23, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 4, 5, 6, 4, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};
