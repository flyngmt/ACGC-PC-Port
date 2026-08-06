#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_din_egg_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_din_egg_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_din_egg_pal[] = {
#include "assets/int_din_egg_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_egg_3_tex[0x200];
#else
u8 int_din_egg_3_tex[] = {
#include "assets/int_din_egg_3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_egg_1_tex[0x400];
#else
u8 int_din_egg_1_tex[] = {
#include "assets/int_din_egg_1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_egg_2_tex[0x100];
#else
u8 int_din_egg_2_tex[] = {
#include "assets/int_din_egg_2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_din_egg_v[0x220 / sizeof(Vtx)];
#else
Vtx int_din_egg_v[] = {
#include "assets/int_din_egg_v.inc"
};
#endif

Gfx int_din_egg_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_egg_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_din_egg_1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_din_egg_v, 30, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_din_egg_3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(22, 16, 17, 18, 19, 20, 21, 19, 21, 22),
    gsSPNTriangles_5b(22, 21, 23, 18, 22, 23, 16, 18, 23, 18, 24, 19),
    gsSPNTriangles_5b(18, 19, 22, 25, 26, 20, 27, 20, 26, 20, 27, 21),
    gsSPNTriangles_5b(23, 21, 27, 23, 27, 28, 16, 23, 28, 16, 28, 29),
    gsSPNTriangles_5b(29, 17, 16, 29, 26, 25, 29, 25, 17, 25, 20, 19),
    gsSPNTriangles_5b(25, 19, 24, 17, 25, 24, 17, 24, 18, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_din_egg_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_egg_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_din_egg_2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 229),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_din_egg_v[30], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
