#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_guitar02_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_guitar02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_guitar02_pal[] = {
#include "assets/int_sum_guitar02_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_guitar02_front[0x480];
#else
u8 int_sum_guitar02_front[] = {
#include "assets/int_sum_guitar02_front.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_guitar02_back[0x100];
#else
u8 int_sum_guitar02_back[] = {
#include "assets/int_sum_guitar02_back.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_guitar02_neck[0x80];
#else
u8 int_sum_guitar02_neck[] = {
#include "assets/int_sum_guitar02_neck.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_guitar02_headstock[0x80];
#else
u8 int_sum_guitar02_headstock[] = {
#include "assets/int_sum_guitar02_headstock.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_guitar02_hand[0x80];
#else
u8 int_sum_guitar02_hand[] = {
#include "assets/int_sum_guitar02_hand.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_guitar02_chest[0x100];
#else
u8 int_sum_guitar02_chest[] = {
#include "assets/int_sum_guitar02_chest.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_guitar02_v[0x400 / sizeof(Vtx)];
#else
Vtx int_sum_guitar02_v[] = {
#include "assets/int_sum_guitar02_v.inc"
};
#endif

Gfx int_sum_guitar02_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_guitar02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_guitar02_neck),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_guitar02_v, 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 7, 5, 9, 10, 11, 12, 9, 11),
    gsSPNTriangles_5b(10, 13, 14, 11, 10, 14, 13, 15, 16, 13, 16, 14),
    gsSPNTriangles_5b(15, 17, 18, 15, 18, 16, 17, 19, 20, 17, 20, 18),
    gsSPNTriangles_5b(21, 22, 20, 19, 21, 20, 23, 24, 25, 26, 23, 25),
    gsSPNTriangles_5b(26, 25, 27, 28, 26, 27, 29, 28, 27, 29, 27, 30),
    gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_sum_guitar02_v[32], 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 0, 2, 4, 3, 2),
    gsSPEndDisplayList(),
};

Gfx int_sum_guitar02_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_guitar02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_guitar02_chest),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_guitar02_v[37], 27, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_guitar02_hand),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 7, 8, 9, 8, 10, 9, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_guitar02_headstock),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 11, 12, 13, 14, 15, 16, 15, 17, 16),
    gsSPNTriangles_5b(11, 13, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_guitar02_back),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 19, 20, 21, 22, 19, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 48, int_sum_guitar02_front),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 23, 24, 25, 26, 23, 25, 0, 0, 0),
    gsSPEndDisplayList(),
};
