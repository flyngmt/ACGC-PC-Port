#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_carpet_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_carpet_pal[] = {
#include "assets/obj_shop_carpet_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_shop_carpet_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_shop_carpet_tex[] = {
#include "assets/obj_shop_carpet_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop_carpet_v[0x2F0 / sizeof(Vtx)];
#else
Vtx obj_shop_carpet_v[] = {
#include "assets/obj_shop_carpet_v.inc"
};
#endif

Gfx obj_carpetT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_carpet_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_carpet_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPEndDisplayList(),
};

Gfx obj_carpetT_gfx_model[] = {
    gsSPVertex(obj_shop_carpet_v, 32, 0),
    gsSPNTrianglesInit_5b(35, 0, 1, 2, 0, 2, 3, 4, 2, 1),
    gsSPNTriangles_5b(4, 1, 5, 5, 6, 7, 7, 8, 4, 4, 5, 7),
    gsSPNTriangles_5b(9, 10, 8, 6, 11, 9, 9, 7, 6, 8, 7, 9),
    gsSPNTriangles_5b(12, 13, 10, 11, 14, 12, 12, 9, 11, 10, 9, 12),
    gsSPNTriangles_5b(15, 16, 13, 14, 17, 15, 13, 12, 15, 15, 12, 14),
    gsSPNTriangles_5b(17, 18, 19, 19, 20, 16, 16, 15, 19, 19, 15, 17),
    gsSPNTriangles_5b(18, 20, 19, 21, 22, 23, 21, 23, 24, 25, 21, 24),
    gsSPNTriangles_5b(24, 26, 25, 27, 25, 26, 28, 25, 27, 25, 28, 21),
    gsSPNTriangles_5b(26, 29, 27, 30, 27, 29, 31, 27, 30, 27, 31, 28),
    gsSPVertex(&obj_shop_carpet_v[32], 15, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 2, 3, 4, 5, 2, 1),
    gsSPNTriangles_5b(3, 2, 5, 6, 7, 8, 6, 8, 9, 5, 10, 3),
    gsSPNTriangles_5b(11, 12, 10, 10, 5, 11, 1, 13, 5, 11, 5, 13),
    gsSPNTriangles_5b(13, 14, 11, 11, 14, 12, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
