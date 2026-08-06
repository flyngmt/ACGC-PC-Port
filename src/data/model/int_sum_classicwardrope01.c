#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_classicwardrope01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_classicwardrope01_pal01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_classicwardrope01_pal01_pal[] = {
#include "assets/int_sum_classicwardrope01_pal01_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_sum_classicwardrope01_mirror_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_sum_classicwardrope01_mirror_rgb_ci4_pal[] = {
#include "assets/int_sum_classicwardrope01_mirror_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicwardrope01_back[0x200];
#else
u8 int_sum_classicwardrope01_back[] = {
#include "assets/int_sum_classicwardrope01_back.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicwardrope01_front[0x200];
#else
u8 int_sum_classicwardrope01_front[] = {
#include "assets/int_sum_classicwardrope01_front.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicwardrope01_side[0x200];
#else
u8 int_sum_classicwardrope01_side[] = {
#include "assets/int_sum_classicwardrope01_side.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicwardrope01_top[0x80];
#else
u8 int_sum_classicwardrope01_top[] = {
#include "assets/int_sum_classicwardrope01_top.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicwardrope01_dolls[0x100];
#else
u8 int_sum_classicwardrope01_dolls[] = {
#include "assets/int_sum_classicwardrope01_dolls.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicwardrope01_mirror[0x80];
#else
u8 int_sum_classicwardrope01_mirror[] = {
#include "assets/int_sum_classicwardrope01_mirror.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_classicwardrope01_v[0x3F0 / sizeof(Vtx)];
#else
Vtx int_sum_classicwardrope01_v[] = {
#include "assets/int_sum_classicwardrope01_v.inc"
};
#endif

Gfx int_sum_classcwardrope01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, SHADE, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_classicwardrope01_pal01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_classicwardrope01_top),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_classicwardrope01_v, 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_classcwardrope01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_classicwardrope01_pal01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_classicwardrope01_dolls),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_classicwardrope01_v[12], 30, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 1, 4, 1, 3),
    gsSPNTriangles_5b(4, 5, 1, 6, 7, 8, 7, 9, 8, 8, 10, 11),
    gsSPNTriangles_5b(8, 9, 10, 12, 13, 14, 12, 15, 13, 16, 13, 17),
    gsSPNTriangles_5b(16, 14, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_classicwardrope01_side),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 18, 19, 20, 19, 21, 20, 24, 28, 25),
    gsSPNTriangles_5b(28, 29, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 22, 23, 20, 23, 18, 20, 24, 25, 26),
    gsSPNTriangles_5b(25, 27, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_classicwardrope01_front),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_classicwardrope01_v[42], 13, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 4, 1, 3, 4, 5, 1, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_classicwardrope01_back),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 6, 7, 8, 6, 9, 7, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 6, 10, 11, 6, 12, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_classicwardrope_envT_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 110),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_classicwardrope01_mirror_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_classicwardrope01_mirror),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_classicwardrope01_v[55], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
