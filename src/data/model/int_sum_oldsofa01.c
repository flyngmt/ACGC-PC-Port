#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_oldsofa01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_oldsofa01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_oldsofa01_pal[] = {
#include "assets/int_sum_oldsofa01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_oldsofa01_seat[0x200];
#else
u8 int_sum_oldsofa01_seat[] = {
#include "assets/int_sum_oldsofa01_seat.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_oldsofa01_side1[0x100];
#else
u8 int_sum_oldsofa01_side1[] = {
#include "assets/int_sum_oldsofa01_side1.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_oldsofa01_side2[0x100];
#else
u8 int_sum_oldsofa01_side2[] = {
#include "assets/int_sum_oldsofa01_side2.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_oldsofa01_top[0x200];
#else
u8 int_sum_oldsofa01_top[] = {
#include "assets/int_sum_oldsofa01_top.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_oldsofa01_side3[0x100];
#else
u8 int_sum_oldsofa01_side3[] = {
#include "assets/int_sum_oldsofa01_side3.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_oldsofa01_foot[0x80];
#else
u8 int_sum_oldsofa01_foot[] = {
#include "assets/int_sum_oldsofa01_foot.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_oldsofa01_v[0x3F0 / sizeof(Vtx)];
#else
Vtx int_sum_oldsofa01_v[] = {
#include "assets/int_sum_oldsofa01_v.inc"
};
#endif

Gfx int_sum_oldsofa01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_oldsofa01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_oldsofa01_foot),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_oldsofa01_v, 26, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_oldsofa01_side3),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_oldsofa01_top),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 20, 24, 25, 20, 25, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_oldsofa01_side2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_oldsofa01_v[26], 28, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 6, 8, 9, 7, 6, 9, 8, 1, 0),
    gsSPNTriangles_5b(9, 8, 0, 10, 11, 12, 10, 12, 13, 13, 12, 14),
    gsSPNTriangles_5b(13, 14, 15, 15, 14, 16, 15, 16, 17, 18, 19, 11),
    gsSPNTriangles_5b(18, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_oldsofa01_side1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_oldsofa01_seat),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_oldsofa01_v[54], 9, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(5, 0, 6, 0, 3, 6, 3, 4, 6, 5, 4, 7),
    gsSPNTriangles_5b(5, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
