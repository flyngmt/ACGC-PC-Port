#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_bass01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_bass01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_bass01_pal[] = {
#include "assets/int_sum_bass01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bass01_front_tex[0x300];
#else
u8 int_sum_bass01_front_tex[] = {
#include "assets/int_sum_bass01_front_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bass01_back_tex[0x180];
#else
u8 int_sum_bass01_back_tex[] = {
#include "assets/int_sum_bass01_back_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bass01_side_tex[0x80];
#else
u8 int_sum_bass01_side_tex[] = {
#include "assets/int_sum_bass01_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bass01_neck_tex[0x100];
#else
u8 int_sum_bass01_neck_tex[] = {
#include "assets/int_sum_bass01_neck_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bass01_neckback_tex[0x80];
#else
u8 int_sum_bass01_neckback_tex[] = {
#include "assets/int_sum_bass01_neckback_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bass01_hand_tex[0x80];
#else
u8 int_sum_bass01_hand_tex[] = {
#include "assets/int_sum_bass01_hand_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_bass01_stand_tex[0x100];
#else
u8 int_sum_bass01_stand_tex[] = {
#include "assets/int_sum_bass01_stand_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_bass01_v[0x390 / sizeof(Vtx)];
#else
Vtx int_sum_bass01_v[] = {
#include "assets/int_sum_bass01_v.inc"
};
#endif

Gfx int_sum_bass01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bass01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_bass01_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_bass01_v, 28, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 2, 1, 4, 2, 4, 7, 8, 9, 0),
    gsSPNTriangles_5b(8, 0, 3, 10, 11, 9, 10, 9, 8, 12, 13, 11),
    gsSPNTriangles_5b(12, 11, 10, 14, 15, 13, 14, 13, 12, 15, 14, 16),
    gsSPNTriangles_5b(15, 16, 17, 18, 19, 20, 18, 20, 21, 22, 21, 20),
    gsSPNTriangles_5b(23, 22, 20, 24, 25, 22, 24, 22, 23, 26, 27, 25),
    gsSPNTriangles_5b(26, 25, 24, 5, 27, 26, 6, 5, 26, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_bass01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bass01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_bass01_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_bass01_v[28], 29, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 6, 3, 5),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_bass01_hand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 7, 8, 9, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_bass01_neckback_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 10, 11, 12, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 13, 14, 15, 14, 16, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_bass01_neck_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 17, 18, 19, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_bass01_back_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 23, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_bass01_front_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 24, 25, 26, 24, 27, 25, 28, 27, 24),
    gsSPNTriangles_5b(24, 26, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
