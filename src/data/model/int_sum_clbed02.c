#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_clbed02_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_clbed02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_clbed02_pal[] = {
#include "assets/int_sum_clbed02_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clbed02_foot[0x100];
#else
u8 int_sum_clbed02_foot[] = {
#include "assets/int_sum_clbed02_foot.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clbed02_head[0x100];
#else
u8 int_sum_clbed02_head[] = {
#include "assets/int_sum_clbed02_head.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clbed02_mat[0x400];
#else
u8 int_sum_clbed02_mat[] = {
#include "assets/int_sum_clbed02_mat.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_clbed02_pillow[0x200];
#else
u8 int_sum_clbed02_pillow[] = {
#include "assets/int_sum_clbed02_pillow.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_clbed02_v[0x300 / sizeof(Vtx)];
#else
Vtx int_sum_clbed02_v[] = {
#include "assets/int_sum_clbed02_v.inc"
};
#endif

Gfx int_sum_clbed02_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_clbed02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_clbed02_pillow),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_clbed02_v, 28, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 2, 3, 0, 3, 2, 4),
    gsSPNTriangles_5b(2, 1, 4, 5, 6, 7, 8, 5, 7, 5, 8, 9),
    gsSPNTriangles_5b(9, 6, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_sum_clbed02_mat),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 10, 11, 12, 10, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 14, 17, 18, 17, 10, 18, 10, 13, 18),
    gsSPNTriangles_5b(13, 14, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_clbed02_head),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 19, 20, 21, 19, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_clbed02_foot),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_clbed02_v[28], 20, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 9, 12, 13, 14, 15, 8, 3, 16, 17),
    gsSPNTriangles_5b(18, 19, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
