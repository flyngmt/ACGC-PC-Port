#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_x_chest03_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_x_chest03_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_x_chest03_pal[] = {
#include "assets/int_sum_x_chest03_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_chest03_side[0x200];
#else
u8 int_sum_x_chest03_side[] = {
#include "assets/int_sum_x_chest03_side.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_chest03_into[0x80];
#else
u8 int_sum_x_chest03_into[] = {
#include "assets/int_sum_x_chest03_into.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_chest03_front[0x280];
#else
u8 int_sum_x_chest03_front[] = {
#include "assets/int_sum_x_chest03_front.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_chest03_head[0x80];
#else
u8 int_sum_x_chest03_head[] = {
#include "assets/int_sum_x_chest03_head.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_chest03_tree[0x100];
#else
u8 int_sum_x_chest03_tree[] = {
#include "assets/int_sum_x_chest03_tree.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_chest03_book[0x100];
#else
u8 int_sum_x_chest03_book[] = {
#include "assets/int_sum_x_chest03_book.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_chest03_present[0x80];
#else
u8 int_sum_x_chest03_present[] = {
#include "assets/int_sum_x_chest03_present.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_x_chest03_v[0x540 / sizeof(Vtx)];
#else
Vtx int_sum_x_chest03_v[] = {
#include "assets/int_sum_x_chest03_v.inc"
};
#endif

Gfx int_sum_x_chest03_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_x_chest03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_x_chest03_book),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_x_chest03_v, 20, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_x_chest03_into),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(6, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 16, 17, 18, 16, 19, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_x_chest03_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_x_chest03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_x_chest03_present),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_x_chest03_v[20], 22, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 1, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(5, 7, 8, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_x_chest03_tree),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 15, 16, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_x_chest03_head),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 17, 18, 19, 17, 20, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 80, int_sum_x_chest03_front),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_x_chest03_v[42], 17, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 0, 2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_x_chest03_side),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_x_chest03_v[59], 25, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 4, 5, 3, 6, 4),
    gsSPNTriangles_5b(7, 8, 9, 8, 10, 9, 11, 12, 13, 11, 14, 12),
    gsSPNTriangles_5b(6, 15, 4, 16, 17, 18, 16, 19, 17, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 24, 0, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
