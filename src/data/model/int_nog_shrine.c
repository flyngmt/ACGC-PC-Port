#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_shrine_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_shrine_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_shrine_pal[] = {
#include "assets/int_nog_shrine_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_shrine_figure_tex[0x200];
#else
u8 int_nog_shrine_figure_tex[] = {
#include "assets/int_nog_shrine_figure_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_shrine_base_tex[0x200];
#else
u8 int_nog_shrine_base_tex[] = {
#include "assets/int_nog_shrine_base_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_shrine_grass_tex[0x80];
#else
u8 int_nog_shrine_grass_tex[] = {
#include "assets/int_nog_shrine_grass_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_shrine_water_tex[0x80];
#else
u8 int_nog_shrine_water_tex[] = {
#include "assets/int_nog_shrine_water_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_shrine_v[0x9A0 / sizeof(Vtx)];
#else
Vtx int_nog_shrine_v[] = {
#include "assets/int_nog_shrine_v.inc"
};
#endif

Gfx int_nog_shrine_grass_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_shrine_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_shrine_grass_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_shrine_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_shrine_figure_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_shrine_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, int_nog_shrine_figure_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_shrine_v[4], 29, 0),
    gsSPNTrianglesInit_5b(27, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(4, 5, 2, 5, 6, 2, 0, 7, 8, 0, 8, 1),
    gsSPNTriangles_5b(1, 8, 9, 1, 9, 10, 11, 5, 12, 11, 12, 13),
    gsSPNTriangles_5b(14, 6, 5, 14, 5, 11, 15, 16, 17, 15, 17, 18),
    gsSPNTriangles_5b(15, 18, 8, 15, 8, 7, 13, 12, 10, 13, 10, 9),
    gsSPNTriangles_5b(19, 20, 21, 19, 21, 22, 20, 23, 24, 20, 24, 21),
    gsSPNTriangles_5b(23, 25, 26, 23, 26, 24, 24, 27, 28, 24, 28, 21),
    gsSPEndDisplayList(),
};

Gfx int_nog_shrine_baseT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_shrine_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, int_nog_shrine_base_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_shrine_v[33], 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 2, 3, 4, 2, 4, 0),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 8, 1, 5, 9, 1, 10),
    gsSPNTriangles_5b(10, 11, 12, 10, 12, 9, 13, 14, 15, 13, 15, 16),
    gsSPNTriangles_5b(16, 1, 13, 17, 1, 18, 18, 19, 20, 18, 20, 17),
    gsSPNTriangles_5b(21, 22, 23, 21, 23, 24, 24, 1, 21, 25, 1, 26),
    gsSPNTriangles_5b(26, 27, 28, 26, 28, 25, 29, 30, 31, 0, 0, 0),
    gsSPVertex(&int_nog_shrine_v[65], 32, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 8, 6, 8, 4, 9, 10, 11, 11, 12, 13),
    gsSPNTriangles_5b(11, 13, 9, 14, 15, 7, 14, 7, 6, 6, 10, 14),
    gsSPNTriangles_5b(16, 5, 17, 17, 18, 19, 17, 19, 16, 9, 13, 20),
    gsSPNTriangles_5b(9, 20, 21, 21, 5, 9, 22, 10, 23, 23, 24, 25),
    gsSPNTriangles_5b(23, 25, 22, 26, 27, 18, 26, 18, 17, 17, 10, 26),
    gsSPNTriangles_5b(22, 25, 28, 22, 28, 29, 29, 5, 22, 0, 0, 0),
    gsSPVertex(&int_nog_shrine_v[95], 6, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(0, 5, 1, 5, 4, 1, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_shrine_waterT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(1, 0, TEXEL0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, PRIMITIVE, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 50, 80, 80, 80, 60),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_shrine_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_shrine_water_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_2_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_shrine_v[101], 32, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 0, 5, 6, 7),
    gsSPNTriangles_5b(7, 8, 3, 9, 10, 11, 12, 13, 9, 11, 14, 15),
    gsSPNTriangles_5b(15, 16, 5, 17, 18, 19, 20, 21, 17, 22, 23, 24),
    gsSPNTriangles_5b(24, 25, 20, 26, 27, 28, 19, 29, 26, 28, 30, 31),
    gsSPVertex(&int_nog_shrine_v[133], 21, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(4, 7, 8, 4, 8, 5, 9, 10, 11, 9, 11, 12),
    gsSPNTriangles_5b(7, 9, 12, 7, 12, 8, 13, 14, 15, 13, 15, 16),
    gsSPNTriangles_5b(10, 13, 16, 10, 16, 11, 14, 17, 18, 14, 18, 15),
    gsSPNTriangles_5b(17, 19, 20, 17, 20, 18, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
