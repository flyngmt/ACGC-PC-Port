#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_piano01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_piano01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_piano01_pal[] = {
#include "assets/int_sum_piano01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_piano01_top_tex[0x300];
#else
u8 int_sum_piano01_top_tex[] = {
#include "assets/int_sum_piano01_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_piano01_key_tex[0x100];
#else
u8 int_sum_piano01_key_tex[] = {
#include "assets/int_sum_piano01_key_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_piano01_side_tex[0x100];
#else
u8 int_sum_piano01_side_tex[] = {
#include "assets/int_sum_piano01_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_piano01_lid_tex[0x200];
#else
u8 int_sum_piano01_lid_tex[] = {
#include "assets/int_sum_piano01_lid_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_piano01_stand_tex[0x80];
#else
u8 int_sum_piano01_stand_tex[] = {
#include "assets/int_sum_piano01_stand_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_piano01_pedal_tex[0x40];
#else
u8 int_sum_piano01_pedal_tex[] = {
#include "assets/int_sum_piano01_pedal_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_piano01_pin_tex[0x40];
#else
u8 int_sum_piano01_pin_tex[] = {
#include "assets/int_sum_piano01_pin_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_piano01_v[0x490 / sizeof(Vtx)];
#else
Vtx int_sum_piano01_v[] = {
#include "assets/int_sum_piano01_v.inc"
};
#endif

Gfx int_sum_piano01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_piano01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_piano01_key_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_piano01_v, 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_piano01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_piano01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_piano01_pin_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_piano01_v[12], 31, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_piano01_pedal_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 3, 4, 5, 5, 6, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_piano01_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(10, 7, 8, 9, 8, 10, 9, 8, 11, 10),
    gsSPNTriangles_5b(8, 12, 11, 13, 14, 15, 16, 17, 15, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 20, 23, 24, 25, 26, 27, 25, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_piano01_lid_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 28, 29, 30, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_piano01_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_piano01_v[43], 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 2, 4, 5),
    gsSPNTriangles_5b(2, 3, 4, 6, 7, 8, 7, 9, 8, 10, 11, 12),
    gsSPNTriangles_5b(10, 13, 11, 14, 15, 16, 14, 17, 15, 18, 14, 16),
    gsSPNTriangles_5b(18, 19, 14, 20, 21, 22, 20, 23, 21, 24, 25, 20),
    gsSPNTriangles_5b(25, 23, 20, 25, 1, 0, 25, 24, 1, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, int_sum_piano01_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 26, 27, 28, 27, 29, 28, 0, 0, 0),
    gsSPEndDisplayList(),
};
