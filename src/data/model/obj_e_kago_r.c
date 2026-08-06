#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_e_kago_r_t1_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_e_kago_r_t1_tex[] = {
#include "assets/obj_e_kago_r_t1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_kago_r_t2_tex[0x800];
#else
u8 obj_e_kago_r_t2_tex[] = {
#include "assets/obj_e_kago_r_t2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_kago_r_v[0x290 / sizeof(Vtx)];
#else
Vtx obj_e_kago_r_v[] = {
#include "assets/obj_e_kago_r_v.inc"
};
#endif

Gfx obj_e_kago_r_t1T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_kago_r_t1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_kago_r_v, 15, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 2, 5, 6, 2),
    gsSPNTriangles_5b(7, 8, 2, 9, 10, 11, 9, 11, 12, 10, 13, 14),
    gsSPNTriangles_5b(10, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_kago_r_t2T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_kago_r_t2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_kago_r_v[15], 26, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 2, 1, 3, 2, 3, 4),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 9, 6, 5, 1, 10, 11),
    gsSPNTriangles_5b(1, 11, 3, 12, 10, 1, 13, 14, 10, 10, 14, 15),
    gsSPNTriangles_5b(10, 15, 11, 16, 17, 6, 6, 17, 18, 6, 18, 7),
    gsSPNTriangles_5b(17, 19, 20, 17, 20, 18, 21, 19, 17, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 22, 23, 24, 22, 24, 25, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kago_r_DL_model[] = {
    gsSPDisplayList(obj_e_kago_r_t1T_model),
    gsSPDisplayList(obj_e_kago_r_t2T_model),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 zobj_e_kago_r_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 zobj_e_kago_r_pal[] = {
#include "assets/zobj_e_kago_r_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_kago_r_ball_t1_tex[0x800];
#else
u8 obj_e_kago_r_ball_t1_tex[] = {
#include "assets/obj_e_kago_r_ball_t1_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_kago_r_ball_v[0x270 / sizeof(Vtx)];
#else
Vtx obj_e_kago_r_ball_v[] = {
#include "assets/obj_e_kago_r_ball_v.inc"
};
#endif

Gfx kago_r_ball_DL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, zobj_e_kago_r_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_kago_r_ball_t1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_kago_r_ball_v, 32, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 24, 25, 26, 27, 28, 29, 0, 0, 0),
    gsSPVertex(&obj_e_kago_r_ball_v[30], 9, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_e_kago_w_t1_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_e_kago_w_t1_tex[] = {
#include "assets/obj_e_kago_w_t1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_kago_w_t2_tex[0x800];
#else
u8 obj_e_kago_w_t2_tex[] = {
#include "assets/obj_e_kago_w_t2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_kago_w_v[0x290 / sizeof(Vtx)];
#else
Vtx obj_e_kago_w_v[] = {
#include "assets/obj_e_kago_w_v.inc"
};
#endif

Gfx obj_e_kago_w_t1T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_kago_w_t1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_kago_w_v, 15, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 2, 5, 6, 2),
    gsSPNTriangles_5b(7, 8, 2, 9, 10, 11, 9, 11, 12, 10, 13, 14),
    gsSPNTriangles_5b(10, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_kago_w_t2T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_kago_w_t2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_kago_w_v[15], 26, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 2, 1, 3, 2, 3, 4),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 9, 6, 5, 1, 10, 11),
    gsSPNTriangles_5b(1, 11, 3, 12, 10, 1, 13, 14, 10, 10, 14, 15),
    gsSPNTriangles_5b(10, 15, 11, 16, 17, 6, 6, 17, 18, 6, 18, 7),
    gsSPNTriangles_5b(17, 19, 20, 17, 20, 18, 21, 19, 17, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 22, 23, 24, 22, 24, 25, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kago_w_DL_model[] = {
    gsSPDisplayList(obj_e_kago_w_t1T_model),
    gsSPDisplayList(obj_e_kago_w_t2T_model),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 zobj_e_kago_w_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 zobj_e_kago_w_pal[] = {
#include "assets/zobj_e_kago_w_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_kago_w_ball_t1_tex[0x800];
#else
u8 obj_e_kago_w_ball_t1_tex[] = {
#include "assets/obj_e_kago_w_ball_t1_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_kago_w_ball_v[0x240 / sizeof(Vtx)];
#else
Vtx obj_e_kago_w_ball_v[] = {
#include "assets/obj_e_kago_w_ball_v.inc"
};
#endif

Gfx kago_w_ball_DL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, zobj_e_kago_w_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_kago_w_ball_t1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_kago_w_ball_v, 32, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 24, 25, 26, 27, 28, 29, 0, 0, 0),
    gsSPVertex(&obj_e_kago_w_ball_v[30], 6, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};
