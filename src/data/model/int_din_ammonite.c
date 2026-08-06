#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_din_ammonite_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_din_ammonite_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_din_ammonite_pal[] = {
#include "assets/int_din_ammonite_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_ammonite_2_tex[0x200];
#else
u8 int_din_ammonite_2_tex[] = {
#include "assets/int_din_ammonite_2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_ammonite_3_tex[0x400];
#else
u8 int_din_ammonite_3_tex[] = {
#include "assets/int_din_ammonite_3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_ammonite_4_tex[0x100];
#else
u8 int_din_ammonite_4_tex[] = {
#include "assets/int_din_ammonite_4_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_din_ammonite_v[0x2E0 / sizeof(Vtx)];
#else
Vtx int_din_ammonite_v[] = {
#include "assets/int_din_ammonite_v.inc"
};
#endif

Gfx int_din_ammonite_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_ammonite_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_din_ammonite_3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_din_ammonite_v, 24, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 0, 4, 1),
    gsSPNTriangles_5b(2, 5, 3, 6, 7, 8, 6, 8, 9, 6, 10, 7),
    gsSPNTriangles_5b(8, 11, 9, 12, 13, 14, 12, 14, 15, 12, 16, 13),
    gsSPNTriangles_5b(14, 17, 15, 18, 19, 20, 18, 20, 21, 18, 22, 19),
    gsSPNTriangles_5b(20, 23, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_din_ammonite_2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&int_din_ammonite_v[24], 18, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(3, 6, 7, 3, 7, 8, 9, 10, 11, 10, 4, 3),
    gsSPNTriangles_5b(10, 3, 11, 3, 12, 11, 8, 13, 12, 8, 12, 3),
    gsSPNTriangles_5b(10, 14, 5, 10, 5, 4, 14, 15, 6, 14, 6, 5),
    gsSPNTriangles_5b(15, 0, 6, 0, 2, 7, 0, 7, 6, 2, 13, 8),
    gsSPNTriangles_5b(2, 8, 7, 14, 16, 15, 13, 17, 12, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_din_ammonite_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_ammonite_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_din_ammonite_4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 229),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_din_ammonite_v[42], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
