#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_pst_pig01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_pst_pig01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_pst_pig01_pal[] = {
#include "assets/int_ike_pst_pig01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_pst_pig01_base1_tex[0x80];
#else
u8 int_ike_pst_pig01_base1_tex[] = {
#include "assets/int_ike_pst_pig01_base1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_pst_pig01_nose1_tex[0x80];
#else
u8 int_ike_pst_pig01_nose1_tex[] = {
#include "assets/int_ike_pst_pig01_nose1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_pst_pig01_ear1_tex[0x80];
#else
u8 int_ike_pst_pig01_ear1_tex[] = {
#include "assets/int_ike_pst_pig01_ear1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_pst_pig01_eye1_tex[0x80];
#else
u8 int_ike_pst_pig01_eye1_tex[] = {
#include "assets/int_ike_pst_pig01_eye1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_pst_pig01_hole1_tex[0x100];
#else
u8 int_ike_pst_pig01_hole1_tex[] = {
#include "assets/int_ike_pst_pig01_hole1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_pst_pig01_hand1_tex[0x80];
#else
u8 int_ike_pst_pig01_hand1_tex[] = {
#include "assets/int_ike_pst_pig01_hand1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_pst_pig01_tail1_tex[0x80];
#else
u8 int_ike_pst_pig01_tail1_tex[] = {
#include "assets/int_ike_pst_pig01_tail1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_pst_pig01_mark1_tex[0x80];
#else
u8 int_ike_pst_pig01_mark1_tex[] = {
#include "assets/int_ike_pst_pig01_mark1_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_pst_pig01_v[0x500 / sizeof(Vtx)];
#else
Vtx int_ike_pst_pig01_v[] = {
#include "assets/int_ike_pst_pig01_v.inc"
};
#endif

Gfx int_ike_pst_pig01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_pst_pig01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_pst_pig01_mark1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_pst_pig01_v, 27, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 0, 4, 1, 0),
    gsSPNTriangles_5b(5, 6, 7, 8, 9, 5, 9, 6, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_pst_pig01_hole1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 10, 11, 12, 11, 13, 14, 12, 11, 14),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_pst_pig01_eye1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 15, 16, 17, 15, 17, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_pst_pig01_ear1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 19, 20, 21, 19, 21, 22, 23, 24, 25),
    gsSPNTriangles_5b(23, 25, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_pst_pig01_nose1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_pst_pig01_v[27], 15, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(0, 7, 1, 8, 9, 10, 8, 10, 11, 10, 0, 12),
    gsSPNTriangles_5b(10, 12, 11, 0, 2, 13, 0, 13, 12, 4, 3, 13),
    gsSPNTriangles_5b(4, 13, 2, 0, 10, 7, 10, 14, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_pst_pig01_base1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_ike_pst_pig01_v[42], 19, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 1, 6, 2),
    gsSPNTriangles_5b(1, 7, 6, 0, 4, 1, 4, 3, 1, 3, 7, 1),
    gsSPNTriangles_5b(5, 4, 8, 9, 10, 11, 12, 13, 10, 9, 12, 10),
    gsSPNTriangles_5b(14, 15, 16, 14, 17, 15, 18, 14, 16, 4, 0, 8),
    gsSPEndDisplayList(),
};

Gfx int_ike_pst_pig01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_pst_pig01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_pst_pig01_tail1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_pst_pig01_v[61], 19, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_pst_pig01_hand1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 11, 12, 13, 8, 14, 15),
    gsSPNTriangles_5b(16, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
