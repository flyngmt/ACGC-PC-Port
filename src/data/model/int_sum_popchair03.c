#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_popchair03_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_popchair03_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_popchair03_pal[] = {
#include "assets/int_sum_popchair03_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_popchair03_top_tex[0x200];
#else
u8 int_sum_popchair03_top_tex[] = {
#include "assets/int_sum_popchair03_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_popchair03_standtop_tex[0x80];
#else
u8 int_sum_popchair03_standtop_tex[] = {
#include "assets/int_sum_popchair03_standtop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_popchair03_side1_tex[0x100];
#else
u8 int_sum_popchair03_side1_tex[] = {
#include "assets/int_sum_popchair03_side1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_popchair03_stand_tex[0x100];
#else
u8 int_sum_popchair03_stand_tex[] = {
#include "assets/int_sum_popchair03_stand_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_popchair03_board_tex[0x200];
#else
u8 int_sum_popchair03_board_tex[] = {
#include "assets/int_sum_popchair03_board_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_popchair03_v[0x320 / sizeof(Vtx)];
#else
Vtx int_sum_popchair03_v[] = {
#include "assets/int_sum_popchair03_v.inc"
};
#endif

Gfx int_sum_popchair03_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_popchair03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_popchair03_board_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_popchair03_v, 15, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_popchair03_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 10, 11, 12, 10, 13, 8),
    gsSPNTriangles_5b(14, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_popchair03_side1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_popchair03_v[15], 30, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 0, 5, 6, 3),
    gsSPNTriangles_5b(7, 8, 5, 9, 10, 7, 11, 12, 9, 13, 14, 11),
    gsSPNTriangles_5b(15, 1, 13, 16, 1, 15, 17, 18, 16, 19, 20, 17),
    gsSPNTriangles_5b(21, 22, 19, 23, 8, 21, 24, 6, 23, 25, 4, 24),
    gsSPNTriangles_5b(2, 1, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_popchair03_standtop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_popchair03_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_sum_popchair03_v[45], 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 0, 2),
    gsSPNTriangles_5b(3, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
