#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_jny_afmen01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_afmen_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_afmen_pal[] = {
#include "assets/int_ike_jny_afmen_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_afmen01_face1_tex[0x200];
#else
u8 int_ike_jny_afmen01_face1_tex[] = {
#include "assets/int_ike_jny_afmen01_face1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_afmen01_under1_tex[0x100];
#else
u8 int_ike_jny_afmen01_under1_tex[] = {
#include "assets/int_ike_jny_afmen01_under1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_afmen01_face2_tex[0x100];
#else
u8 int_ike_jny_afmen01_face2_tex[] = {
#include "assets/int_ike_jny_afmen01_face2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_afmen01_base1_tex[0x80];
#else
u8 int_ike_jny_afmen01_base1_tex[] = {
#include "assets/int_ike_jny_afmen01_base1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_afmen01_base2_tex[0x40];
#else
u8 int_ike_jny_afmen01_base2_tex[] = {
#include "assets/int_ike_jny_afmen01_base2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_afmen01_base3_tex[0x40];
#else
u8 int_ike_jny_afmen01_base3_tex[] = {
#include "assets/int_ike_jny_afmen01_base3_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_jny_afmen01_v[0x4D0 / sizeof(Vtx)];
#else
Vtx int_ike_jny_afmen01_v[] = {
#include "assets/int_ike_jny_afmen01_v.inc"
};
#endif

Gfx int_ike_jny_afmen01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_afmen_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_jny_afmen01_base3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_jny_afmen01_v, 16, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_jny_afmen01_base2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_ike_jny_afmen01_v[16], 20, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_jny_afmen01_base1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_jny_afmen01_face2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_ike_jny_afmen01_v[36], 12, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(1, 5, 3, 1, 6, 5, 5, 7, 3, 5, 8, 9),
    gsSPNTriangles_5b(5, 9, 7, 6, 10, 11, 6, 11, 5, 8, 5, 11),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_ike_jny_afmen01_face1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_ike_jny_afmen01_v[48], 25, 0),
    gsSPNTrianglesInit_5b(37, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 4, 8, 5, 5, 0, 7, 8, 9, 5),
    gsSPNTriangles_5b(9, 10, 5, 1, 5, 10, 1, 0, 5, 11, 12, 8),
    gsSPNTriangles_5b(11, 8, 4, 12, 13, 9, 12, 9, 8, 14, 15, 10),
    gsSPNTriangles_5b(14, 16, 15, 15, 1, 10, 9, 17, 10, 17, 14, 10),
    gsSPNTriangles_5b(17, 18, 14, 11, 4, 6, 11, 6, 19, 6, 7, 20),
    gsSPNTriangles_5b(6, 20, 19, 13, 21, 17, 13, 17, 9, 22, 15, 16),
    gsSPNTriangles_5b(22, 16, 23, 1, 15, 22, 1, 22, 2, 18, 17, 21),
    gsSPNTriangles_5b(18, 21, 24, 14, 18, 16, 23, 16, 18, 23, 18, 24),
    gsSPNTriangles_5b(7, 0, 3, 7, 3, 20, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_jny_afmen01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_afmen_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_jny_afmen01_under1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_jny_afmen01_v[73], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
