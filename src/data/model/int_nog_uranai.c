#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_uranai_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_uranai_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_uranai_pal[] = {
#include "assets/int_nog_uranai_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_uranai_body_tex[0x400];
#else
u8 int_nog_uranai_body_tex[] = {
#include "assets/int_nog_uranai_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_uranai_roof_tex[0x200];
#else
u8 int_nog_uranai_roof_tex[] = {
#include "assets/int_nog_uranai_roof_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_uranai_grass_tex[0x80];
#else
u8 int_nog_uranai_grass_tex[] = {
#include "assets/int_nog_uranai_grass_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_uranai_v[0x250 / sizeof(Vtx)];
#else
Vtx int_nog_uranai_v[] = {
#include "assets/int_nog_uranai_v.inc"
};
#endif

Gfx int_nog_uranai_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_uranai_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_uranai_grass_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_uranai_v, 18, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_uranai_roof_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 4, 5, 6, 7, 8, 4, 6, 9, 10),
    gsSPNTriangles_5b(11, 12, 13, 11, 13, 14, 15, 8, 7, 10, 9, 16),
    gsSPNTriangles_5b(17, 8, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_uranai_off_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_uranai_roof_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_uranai_v[18], 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 2, 0, 4, 1),
    gsSPEndDisplayList(),
};

Gfx int_nog_uranai_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_uranai_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_nog_uranai_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_uranai_v[23], 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 2, 3, 0, 1, 0, 4),
    gsSPNTriangles_5b(4, 5, 1, 6, 7, 8, 8, 9, 6, 5, 4, 9),
    gsSPNTriangles_5b(9, 8, 5, 10, 11, 12, 12, 13, 10, 11, 10, 3),
    gsSPNTriangles_5b(3, 2, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
