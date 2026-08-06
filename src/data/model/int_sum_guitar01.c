#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_guitar01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_guitar01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_guitar01_pal[] = {
#include "assets/int_sum_guitar01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_guitar01_front[0x400];
#else
u8 int_sum_guitar01_front[] = {
#include "assets/int_sum_guitar01_front.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_guitar01_back[0x100];
#else
u8 int_sum_guitar01_back[] = {
#include "assets/int_sum_guitar01_back.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_guitar01_side[0x80];
#else
u8 int_sum_guitar01_side[] = {
#include "assets/int_sum_guitar01_side.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_guitar01_neck[0x80];
#else
u8 int_sum_guitar01_neck[] = {
#include "assets/int_sum_guitar01_neck.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_guitar01_headstock[0x80];
#else
u8 int_sum_guitar01_headstock[] = {
#include "assets/int_sum_guitar01_headstock.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_guitar01_hand[0x80];
#else
u8 int_sum_guitar01_hand[] = {
#include "assets/int_sum_guitar01_hand.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_guitar01_chest[0x100];
#else
u8 int_sum_guitar01_chest[] = {
#include "assets/int_sum_guitar01_chest.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_guitar01_v[0x3C0 / sizeof(Vtx)];
#else
Vtx int_sum_guitar01_v[] = {
#include "assets/int_sum_guitar01_v.inc"
};
#endif

Gfx int_sum_guitar01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_guitar01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_guitar01_neck),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_guitar01_v, 9, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 7, 5, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_guitar01_side),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_guitar01_v[9], 24, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(5, 6, 7, 6, 8, 7, 9, 10, 11, 10, 12, 11),
    gsSPNTriangles_5b(13, 14, 10, 14, 12, 10, 13, 15, 14, 15, 16, 14),
    gsSPNTriangles_5b(15, 17, 16, 17, 18, 16, 17, 19, 18, 17, 20, 19),
    gsSPNTriangles_5b(8, 6, 21, 6, 22, 21, 22, 0, 21, 0, 23, 21),
    gsSPNTriangles_5b(0, 2, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 4, 19, 20, 4, 3, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_guitar01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_guitar01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_guitar01_chest),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_guitar01_v[33], 27, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_guitar01_hand),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 7, 8, 9, 8, 10, 9, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_guitar01_headstock),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 11, 12, 13, 14, 15, 16, 15, 17, 16),
    gsSPNTriangles_5b(11, 13, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_guitar01_back),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 19, 20, 21, 22, 19, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_sum_guitar01_front),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 23, 24, 25, 26, 23, 25, 0, 0, 0),
    gsSPEndDisplayList(),
};
