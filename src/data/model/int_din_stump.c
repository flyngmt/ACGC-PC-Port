#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_din_stump_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_din_stump_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_din_stump_pal[] = {
#include "assets/int_din_stump_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_stump_3_tex[0x200];
#else
u8 int_din_stump_3_tex[] = {
#include "assets/int_din_stump_3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_stump_1_tex[0x400];
#else
u8 int_din_stump_1_tex[] = {
#include "assets/int_din_stump_1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_stump_2_tex[0x100];
#else
u8 int_din_stump_2_tex[] = {
#include "assets/int_din_stump_2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_din_stump_v[0x290 / sizeof(Vtx)];
#else
Vtx int_din_stump_v[] = {
#include "assets/int_din_stump_v.inc"
};
#endif

Gfx int_din_stump_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_stump_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_din_stump_1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_din_stump_v, 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_din_stump_3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_din_stump_v[16], 21, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 1, 3, 2, 3, 4, 5),
    gsSPNTriangles_5b(4, 6, 5, 7, 2, 5, 7, 5, 8, 0, 2, 7),
    gsSPNTriangles_5b(3, 5, 2, 7, 8, 9, 6, 8, 5, 10, 11, 12),
    gsSPNTriangles_5b(10, 13, 11, 14, 15, 10, 10, 15, 13, 16, 17, 15),
    gsSPNTriangles_5b(16, 15, 14, 18, 16, 14, 11, 19, 12, 19, 1, 12),
    gsSPNTriangles_5b(12, 1, 18, 18, 1, 20, 18, 20, 16, 6, 15, 8),
    gsSPNTriangles_5b(15, 9, 8, 9, 16, 7, 16, 0, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_din_stump_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_stump_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_din_stump_2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 229),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_din_stump_v[37], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
