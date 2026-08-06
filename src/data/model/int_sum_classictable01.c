#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_classictable01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_dolltable01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_dolltable01_pal[] = {
#include "assets/int_sum_dolltable01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classictable01_top[0x200];
#else
u8 int_sum_classictable01_top[] = {
#include "assets/int_sum_classictable01_top.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classictable01_side[0x80];
#else
u8 int_sum_classictable01_side[] = {
#include "assets/int_sum_classictable01_side.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classictable01_lag[0x180];
#else
u8 int_sum_classictable01_lag[] = {
#include "assets/int_sum_classictable01_lag.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_classictable01_foot[0x100];
#else
u8 int_sum_classictable01_foot[] = {
#include "assets/int_sum_classictable01_foot.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_classictable01_v[0x350 / sizeof(Vtx)];
#else
Vtx int_sum_classictable01_v[] = {
#include "assets/int_sum_classictable01_v.inc"
};
#endif

Gfx int_sum_classictable01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_dolltable01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_classictable01_side),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_classictable01_v, 24, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 3, 1, 1, 4, 2),
    gsSPNTriangles_5b(1, 5, 4, 5, 6, 4, 6, 7, 4, 8, 6, 9),
    gsSPNTriangles_5b(8, 7, 6, 10, 8, 11, 8, 9, 11, 10, 11, 12),
    gsSPNTriangles_5b(11, 13, 12, 14, 15, 0, 15, 3, 0, 14, 16, 15),
    gsSPNTriangles_5b(16, 17, 15, 16, 18, 17, 16, 19, 18, 12, 20, 21),
    gsSPNTriangles_5b(12, 13, 20, 20, 22, 21, 20, 23, 22, 23, 18, 22),
    gsSPNTriangles_5b(18, 19, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_classictable01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_dolltable01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_classictable01_foot),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_classictable01_v[24], 29, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 1, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 6, 9, 10, 11, 12, 13, 11, 14, 15, 16, 17),
    gsSPNTriangles_5b(18, 16, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_classictable01_lag),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 23, 24, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_classictable01_top),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 25, 26, 27, 25, 28, 26, 0, 0, 0),
    gsSPEndDisplayList(),
};
