#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_arwing_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_arwing_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_arwing_pal[] = {
#include "assets/int_tak_arwing_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_arwing_boost[0x80];
#else
u8 int_tak_arwing_boost[] = {
#include "assets/int_tak_arwing_boost.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_arwing_bottom[0x100];
#else
u8 int_tak_arwing_bottom[] = {
#include "assets/int_tak_arwing_bottom.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_arwing_bulue1[0x80];
#else
u8 int_tak_arwing_bulue1[] = {
#include "assets/int_tak_arwing_bulue1.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_arwing_front[0x100];
#else
u8 int_tak_arwing_front[] = {
#include "assets/int_tak_arwing_front.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_arwing_mark[0x80];
#else
u8 int_tak_arwing_mark[] = {
#include "assets/int_tak_arwing_mark.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_arwing_side[0x100];
#else
u8 int_tak_arwing_side[] = {
#include "assets/int_tak_arwing_side.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_arwing_window[0x80];
#else
u8 int_tak_arwing_window[] = {
#include "assets/int_tak_arwing_window.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_arwing_bou[0x80];
#else
u8 int_tak_arwing_bou[] = {
#include "assets/int_tak_arwing_bou.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_arwing_dai[0x200];
#else
u8 int_tak_arwing_dai[] = {
#include "assets/int_tak_arwing_dai.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_arwing_wing[0x80];
#else
u8 int_tak_arwing_wing[] = {
#include "assets/int_tak_arwing_wing.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_arwing_v[0x710 / sizeof(Vtx)];
#else
Vtx int_tak_arwing_v[] = {
#include "assets/int_tak_arwing_v.inc"
};
#endif

Gfx int_tak_arwing_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_arwing_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_arwing_wing),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_arwing_v, 21, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_tak_arwing_dai),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_tak_arwing_v[21], 30, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_arwing_window),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(5, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 15, 17, 24, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_arwing_side),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 25, 26, 27, 27, 28, 29, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_arwing_mark),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_arwing_v[51], 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_arwing_front),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(1, 5, 6, 7, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_arwing_bulue1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&int_tak_arwing_v[59], 32, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 24, 25, 26, 27, 28, 29, 0, 0, 0),
    gsSPVertex(&int_tak_arwing_v[89], 19, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_arwing_bottom),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 6, 7, 8, 9, 10, 11, 7, 12, 8),
    gsSPNTriangles_5b(13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_arwing_boost),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 16, 17, 18, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_arwing_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_arwing_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_arwing_bou),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_arwing_v[108], 5, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 1, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};
