#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_classicchest02_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_classicchest02_pal01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_classicchest02_pal01_pal[] = {
#include "assets/int_sum_classicchest02_pal01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicchest02_back[0x180];
#else
u8 int_sum_classicchest02_back[] = {
#include "assets/int_sum_classicchest02_back.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicchest02_side[0x180];
#else
u8 int_sum_classicchest02_side[] = {
#include "assets/int_sum_classicchest02_side.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicchest02_top[0x200];
#else
u8 int_sum_classicchest02_top[] = {
#include "assets/int_sum_classicchest02_top.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicchest02_front[0x100];
#else
u8 int_sum_classicchest02_front[] = {
#include "assets/int_sum_classicchest02_front.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicchest02_tablefront[0x40];
#else
u8 int_sum_classicchest02_tablefront[] = {
#include "assets/int_sum_classicchest02_tablefront.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicchest02_tableside[0x40];
#else
u8 int_sum_classicchest02_tableside[] = {
#include "assets/int_sum_classicchest02_tableside.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicchest02_uptop[0x80];
#else
u8 int_sum_classicchest02_uptop[] = {
#include "assets/int_sum_classicchest02_uptop.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicchest02_ink[0x80];
#else
u8 int_sum_classicchest02_ink[] = {
#include "assets/int_sum_classicchest02_ink.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicchest02_pensaki[0x40];
#else
u8 int_sum_classicchest02_pensaki[] = {
#include "assets/int_sum_classicchest02_pensaki.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classicchest02_pen[0x40];
#else
u8 int_sum_classicchest02_pen[] = {
#include "assets/int_sum_classicchest02_pen.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_classicchest02_v[0x320 / sizeof(Vtx)];
#else
Vtx int_sum_classicchest02_v[] = {
#include "assets/int_sum_classicchest02_v.inc"
};
#endif

Gfx int_sum_classicchest02_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_classicchest02_pal01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_classicchest02_ink),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_classicchest02_v, 27, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 4, 3, 5, 6),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_classicchest02_uptop),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 7, 8, 9, 7, 9, 10, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_classicchest02_tableside),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 11, 12, 13, 11, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(15, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_classicchest02_tablefront),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 19, 20, 21, 19, 21, 22, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_classicchest02_top),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 23, 24, 25, 23, 25, 26, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_classicchest02_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_classicchest02_pal01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_classicchest02_pen),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_classicchest02_v[27], 23, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_classicchest02_pensaki),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 3, 4, 5, 6, 3, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_classicchest02_front),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 7, 8, 9, 7, 9, 10, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_classicchest02_side),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 11, 12, 13, 11, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(15, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_classicchest02_back),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 19, 20, 21, 19, 21, 22, 0, 0, 0),
    gsSPEndDisplayList(),
};
