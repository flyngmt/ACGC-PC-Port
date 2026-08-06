#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_x_piano_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_x_piano_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_x_piano_pal[] = {
#include "assets/int_sum_x_piano_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_piano_back_tex[0x180];
#else
u8 int_sum_x_piano_back_tex[] = {
#include "assets/int_sum_x_piano_back_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_piano_side_tex[0x200];
#else
u8 int_sum_x_piano_side_tex[] = {
#include "assets/int_sum_x_piano_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_piano_front_tex[0x180];
#else
u8 int_sum_x_piano_front_tex[] = {
#include "assets/int_sum_x_piano_front_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_piano_head_tex[0x80];
#else
u8 int_sum_x_piano_head_tex[] = {
#include "assets/int_sum_x_piano_head_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_piano_key_tex[0x100];
#else
u8 int_sum_x_piano_key_tex[] = {
#include "assets/int_sum_x_piano_key_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_piano_down_tex[0x100];
#else
u8 int_sum_x_piano_down_tex[] = {
#include "assets/int_sum_x_piano_down_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_x_piano_foot_tex[0x80];
#else
u8 int_sum_x_piano_foot_tex[] = {
#include "assets/int_sum_x_piano_foot_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_x_piano_v[0x560 / sizeof(Vtx)];
#else
Vtx int_sum_x_piano_v[] = {
#include "assets/int_sum_x_piano_v.inc"
};
#endif

Gfx int_sum_x_piano_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_x_piano_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_x_piano_key_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_x_piano_v, 12, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 16, int_sum_x_piano_front_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_x_piano_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_x_piano_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_x_piano_foot_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_x_piano_v[12], 19, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_x_piano_down_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 3, 4, 5, 3, 5, 6, 11, 12, 13),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 7, 8, 9, 7, 9, 10, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_x_piano_head_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 14, 15, 16, 14, 17, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_x_piano_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_x_piano_v[31], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 0),
    gsSPNTriangles_5b(4, 0, 6, 7, 8, 9, 7, 9, 10, 11, 12, 13),
    gsSPNTriangles_5b(11, 13, 14, 15, 16, 17, 15, 17, 18, 19, 20, 21),
    gsSPNTriangles_5b(19, 21, 22, 23, 24, 25, 23, 25, 26, 27, 28, 29),
    gsSPNTriangles_5b(27, 29, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_sum_x_piano_v[62], 24, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_x_piano_back_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 8, 9, 10, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(17, 18, 19, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsSPEndDisplayList(),
};
