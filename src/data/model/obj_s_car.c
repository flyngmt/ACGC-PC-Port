#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_car_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_car_pal[] = {
#include "assets/obj_s_car_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_car_t1_tex[0x800];
#else
u8 obj_s_car_t1_tex[] = {
#include "assets/obj_s_car_t1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_car_t2_tex[0x800];
#else
u8 obj_s_car_t2_tex[] = {
#include "assets/obj_s_car_t2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_car_t3_tex[0x800];
#else
u8 obj_s_car_t3_tex[] = {
#include "assets/obj_s_car_t3_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_car_v[0x6E0 / sizeof(Vtx)];
#else
Vtx obj_s_car_v[] = {
#include "assets/obj_s_car_v.inc"
};
#endif

Gfx obj_s_car_t1T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_car_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_car_t1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_car_v, 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 2, 4, 1, 5, 2),
    gsSPNTriangles_5b(6, 7, 8, 9, 10, 11, 5, 4, 2, 6, 12, 7),
    gsSPNTriangles_5b(13, 14, 11, 10, 13, 11, 3, 0, 2, 7, 15, 8),
    gsSPNTriangles_5b(16, 15, 7, 12, 16, 7, 17, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(22, 23, 20, 21, 24, 22, 25, 19, 18, 26, 27, 28),
    gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_car_v[32], 14, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 10, 12, 13, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_car_t2T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_car_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_car_t2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_car_v[46], 13, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(2, 3, 5, 3, 6, 5, 6, 3, 7, 6, 8, 9),
    gsSPNTriangles_5b(8, 6, 7, 10, 11, 12, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_car_t3T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_car_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_car_t3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_car_v[59], 21, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 4, 5, 6, 3, 5),
    gsSPNTriangles_5b(5, 4, 7, 6, 5, 7, 8, 9, 10, 9, 11, 10),
    gsSPNTriangles_5b(8, 12, 9, 12, 11, 9, 13, 14, 15, 13, 15, 16),
    gsSPNTriangles_5b(17, 18, 19, 17, 19, 20, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_car_innerT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_car_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_car_t3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_car_v[80], 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 15, 16, 13, 17, 18, 15, 17, 15, 12),
    gsSPNTriangles_5b(19, 20, 21, 22, 19, 21, 22, 21, 23, 24, 25, 18),
    gsSPNTriangles_5b(24, 18, 17, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx s_car_DL_model[] = {
    gsSPDisplayList(obj_s_car_t1T_model),
    gsSPDisplayList(obj_s_car_t2T_model),
    gsSPDisplayList(obj_s_car_t3T_model),
    gsSPDisplayList(obj_s_car_innerT_model),
    gsSPEndDisplayList(),
};
