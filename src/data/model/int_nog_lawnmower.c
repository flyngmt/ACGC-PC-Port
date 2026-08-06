#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_lawnmower_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_lawnmower_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_lawnmower_pal[] = {
#include "assets/int_nog_lawnmower_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_lawnmowre_body_tex[0x400];
#else
u8 int_nog_lawnmowre_body_tex[] = {
#include "assets/int_nog_lawnmowre_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_lawnmowre_handle_tex[0x400];
#else
u8 int_nog_lawnmowre_handle_tex[] = {
#include "assets/int_nog_lawnmowre_handle_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_lawnmower_fade_tex_rgb_i4[0x80];
#else
u8 int_nog_lawnmower_fade_tex_rgb_i4[] = {
#include "assets/int_nog_lawnmower_fade_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_lawnmower_grass_tex_rgb_i4[0x80];
#else
u8 int_nog_lawnmower_grass_tex_rgb_i4[] = {
#include "assets/int_nog_lawnmower_grass_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_lawnmower_v[0x830 / sizeof(Vtx)];
#else
Vtx int_nog_lawnmower_v[] = {
#include "assets/int_nog_lawnmower_v.inc"
};
#endif

Gfx int_nog_lawnmower_grass_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, COMBINED, 0, TEXEL0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, int_nog_lawnmower_fade_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, int_nog_lawnmower_grass_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_lawnmower_v, 10, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(5, 6, 7, 6, 8, 7, 6, 9, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_lawnmower_bodyT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_lawnmower_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_nog_lawnmowre_handle_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_lawnmower_v[10], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 9, 10, 11, 9, 11, 12),
    gsSPNTriangles_5b(13, 14, 15, 16, 17, 18, 16, 18, 19, 17, 1, 18),
    gsSPNTriangles_5b(1, 4, 18, 17, 2, 1, 15, 20, 21, 22, 23, 24),
    gsSPNTriangles_5b(25, 26, 22, 27, 28, 29, 29, 30, 25, 0, 0, 0),
    gsSPVertex(&int_nog_lawnmower_v[41], 32, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(5, 9, 6, 8, 10, 11, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(17, 18, 19, 19, 20, 14, 21, 22, 17, 23, 24, 21),
    gsSPNTriangles_5b(25, 26, 27, 27, 28, 29, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_lawnmower_v[71], 15, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 0, 2, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 11, 12, 13, 11, 13, 14),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_nog_lawnmowre_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_lawnmower_v[86], 32, 0),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 10, 7, 8, 7, 10, 6),
    gsSPNTriangles_5b(11, 12, 13, 12, 11, 4, 4, 3, 12, 14, 11, 13),
    gsSPNTriangles_5b(19, 15, 18, 19, 18, 20, 16, 21, 17, 21, 22, 17),
    gsSPNTriangles_5b(16, 23, 21, 15, 24, 25, 15, 25, 16, 17, 26, 27),
    gsSPNTriangles_5b(17, 27, 18, 28, 29, 30, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 15, 16, 17, 15, 17, 18, 0, 0, 0),
    gsSPVertex(&int_nog_lawnmower_v[117], 14, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 6, 5, 7),
    gsSPNTriangles_5b(8, 9, 10, 10, 11, 8, 10, 12, 11, 10, 13, 12),
    gsSPEndDisplayList(),
};
