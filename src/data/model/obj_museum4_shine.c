#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_museum4_shine_1[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 obj_museum4_shine_1[] = {
#include "assets/obj_museum4_shine_1.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_museum4_shine_2[0x400];
#else
u8 obj_museum4_shine_2[] = {
#include "assets/obj_museum4_shine_2.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_museum4_shine_v[0x2F0 / sizeof(Vtx)];
#else
Vtx obj_museum4_shine_v[] = {
#include "assets/obj_museum4_shine_v.inc"
};
#endif

Gfx obj_museum4_shine_2T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, obj_museum4_shine_2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_museum4_shine_v, 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(1, 5, 4, 4, 6, 3, 4, 7, 6, 6, 2, 3),
    gsSPNTriangles_5b(6, 8, 2, 7, 9, 6, 9, 10, 6, 10, 11, 6),
    gsSPNTriangles_5b(11, 8, 6, 9, 12, 10, 9, 13, 12, 12, 11, 10),
    gsSPNTriangles_5b(12, 14, 11, 13, 15, 12, 15, 16, 12, 16, 17, 12),
    gsSPNTriangles_5b(17, 14, 12, 15, 18, 16, 15, 19, 18, 18, 17, 16),
    gsSPNTriangles_5b(18, 20, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_GEQUAL),
    gsSPNTrianglesInit_5b(8, 21, 22, 23, 21, 24, 22, 22, 25, 23),
    gsSPNTriangles_5b(22, 26, 25, 24, 27, 22, 27, 28, 22, 28, 29, 22),
    gsSPNTriangles_5b(29, 26, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_museum4_shine_v[30], 9, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(4, 5, 2, 1, 6, 3, 1, 7, 6, 6, 4, 3),
    gsSPNTriangles_5b(6, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPClearGeometryMode(G_DECAL_GEQUAL),
    gsSPEndDisplayList(),
};

Gfx obj_museum4_shine_1T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_museum4_shine_1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_museum4_shine_v[39], 8, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 4, 0, 2, 3),
    gsSPNTriangles_5b(4, 3, 5, 4, 5, 6, 6, 5, 7, 5, 1, 7),
    gsSPNTriangles_5b(7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
