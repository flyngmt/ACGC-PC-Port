#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_stew_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_stew_a1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_stew_a1_pal[] = {
#include "assets/int_tak_stew_a1_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_stew_nabe_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_stew_nabe_pal[] = {
#include "assets/int_tak_stew_nabe_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_stew_a1_tex[0x200];
#else
u8 int_tak_stew_a1_tex[] = {
#include "assets/int_tak_stew_a1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_stew_nabe_tex[0x80];
#else
u8 int_tak_stew_nabe_tex[] = {
#include "assets/int_tak_stew_nabe_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_stew_etc_tex[0x80];
#else
u8 int_tak_stew_etc_tex[] = {
#include "assets/int_tak_stew_etc_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_stew_a2_tex_rgb_ci4[0x200];
#else
u8 int_tak_stew_a2_tex_rgb_ci4[] = {
#include "assets/int_tak_stew_a2_tex_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_stew_v[0x400 / sizeof(Vtx)];
#else
Vtx int_tak_stew_v[] = {
#include "assets/int_tak_stew_v.inc"
};
#endif

Gfx int_tak_stew_nabe_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_stew_nabe_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 32, int_tak_stew_nabe_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_stew_v, 18, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 1, 3, 1, 0),
    gsSPNTriangles_5b(5, 4, 3, 6, 7, 8, 8, 9, 5, 8, 7, 9),
    gsSPNTriangles_5b(5, 9, 4, 10, 11, 12, 13, 2, 11, 13, 11, 10),
    gsSPNTriangles_5b(0, 2, 13, 10, 12, 14, 14, 15, 16, 14, 12, 15),
    gsSPNTriangles_5b(16, 15, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_stew_nabe_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_stew_nabe_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_stew_etc_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_stew_v[18], 32, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 10, 9, 11),
    gsSPNTriangles_5b(10, 4, 9, 12, 13, 14, 13, 15, 14, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(12, 4, 5, 6, 4, 6, 7, 4, 7, 8),
    gsSPNTriangles_5b(4, 8, 9, 13, 16, 17, 13, 17, 15, 17, 18, 19),
    gsSPNTriangles_5b(17, 19, 15, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_tak_stew_v[50], 10, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 3, 2),
    gsSPNTriangles_5b(4, 2, 5, 6, 7, 8, 6, 8, 9, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_stew_a1T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_stew_a1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_stew_v[60], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
