#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_din_trilobite_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_din_trilobite_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_din_trilobite_pal[] = {
#include "assets/int_din_trilobite_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trilobite_1_tex[0x400];
#else
u8 int_din_trilobite_1_tex[] = {
#include "assets/int_din_trilobite_1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trilobite_2_tex[0x100];
#else
u8 int_din_trilobite_2_tex[] = {
#include "assets/int_din_trilobite_2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trilobite_3_tex[0x200];
#else
u8 int_din_trilobite_3_tex[] = {
#include "assets/int_din_trilobite_3_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_din_trilobite_v[0x220 / sizeof(Vtx)];
#else
Vtx int_din_trilobite_v[] = {
#include "assets/int_din_trilobite_v.inc"
};
#endif

Gfx int_din_trilobite_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_trilobite_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_din_trilobite_3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_din_trilobite_v, 30, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(4, 5, 0, 4, 6, 5, 6, 7, 8, 6, 8, 5),
    gsSPNTriangles_5b(9, 8, 7, 8, 9, 1, 2, 1, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 4, 10, 6, 10, 13, 6, 13, 7, 6),
    gsSPNTriangles_5b(12, 7, 13, 12, 9, 7, 4, 3, 10, 3, 11, 10),
    gsSPNTriangles_5b(3, 2, 11, 2, 12, 11, 2, 9, 12, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_din_trilobite_1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 14, 15, 16, 14, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 23, 24, 22, 24, 25, 26, 27, 28),
    gsSPNTriangles_5b(26, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_din_trilobite_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_trilobite_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_din_trilobite_2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 229),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_din_trilobite_v[30], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
