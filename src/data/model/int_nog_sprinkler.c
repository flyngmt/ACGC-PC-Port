#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_sprinkler_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 int_noga_sprinkler[0x20];
#else
ATTRIBUTE_ALIGN(32) u8 int_noga_sprinkler[] = {
#include "assets/int_noga_sprinkler.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_sprinkler_tex[0x800];
#else
u8 int_nog_sprinkler_tex[] = {
#include "assets/int_nog_sprinkler_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_sprinkler_fade_tex_rgb_i4[0x80];
#else
u8 int_nog_sprinkler_fade_tex_rgb_i4[] = {
#include "assets/int_nog_sprinkler_fade_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_sprinkler_water_tex_rgb_i4[0x80];
#else
u8 int_nog_sprinkler_water_tex_rgb_i4[] = {
#include "assets/int_nog_sprinkler_water_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_sprinkler_v[0x630 / sizeof(Vtx)];
#else
Vtx int_nog_sprinkler_v[] = {
#include "assets/int_nog_sprinkler_v.inc"
};
#endif

Gfx int_nog_sprinkler_water_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0,
                       COMBINED, 0, TEXEL0, 0),
    gsDPSetPrimColor(0, 255, 120, 210, 255, 80),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, int_nog_sprinkler_fade_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, int_nog_sprinkler_water_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 14, 15),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_sprinkler_v, 15, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(2, 5, 0, 5, 6, 0, 7, 8, 5, 7, 9, 8),
    gsSPNTriangles_5b(7, 3, 9, 3, 10, 9, 8, 11, 5, 0, 6, 12),
    gsSPNTriangles_5b(13, 4, 1, 14, 13, 1, 14, 1, 0, 14, 0, 12),
    gsSPEndDisplayList(),
};

Gfx int_nog_sprinkler_bodyT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_noga_sprinkler),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, int_nog_sprinkler_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_sprinkler_v[15], 32, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(20, 8, 9, 10, 10, 11, 8, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 20, 23, 15, 20, 15, 16, 24, 17, 14),
    gsSPNTriangles_5b(24, 14, 25, 24, 25, 26, 24, 26, 27, 15, 14, 17),
    gsSPNTriangles_5b(15, 17, 16, 28, 29, 30, 28, 30, 31, 31, 30, 19),
    gsSPNTriangles_5b(31, 19, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_sprinkler_v[47], 32, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(19, 4, 5, 6, 4, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 8, 11, 12, 9, 13, 14, 9, 14, 10),
    gsSPNTriangles_5b(13, 15, 16, 13, 16, 14, 17, 16, 15, 17, 15, 18),
    gsSPNTriangles_5b(19, 17, 18, 19, 18, 20, 21, 19, 20, 21, 20, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 25, 26, 27, 28, 29, 27, 29, 30),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPVertex(&int_nog_sprinkler_v[78], 21, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 8, 9, 10),
    gsSPNTriangles_5b(11, 12, 13, 11, 13, 14, 12, 15, 13, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 16, 19, 20, 11, 14, 10, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};
