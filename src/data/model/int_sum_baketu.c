#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_baketu_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_baketu_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_baketu_pal[] = {
#include "assets/int_sum_baketu_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_baketu_side_tex[0x300];
#else
u8 int_sum_baketu_side_tex[] = {
#include "assets/int_sum_baketu_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_baketu_stand_tex[0x280];
#else
u8 int_sum_baketu_stand_tex[] = {
#include "assets/int_sum_baketu_stand_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_baketu_s_side_tex[0x200];
#else
u8 int_sum_baketu_s_side_tex[] = {
#include "assets/int_sum_baketu_s_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_baketu_hand_tex[0x80];
#else
u8 int_sum_baketu_hand_tex[] = {
#include "assets/int_sum_baketu_hand_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_baketu_v[0x220 / sizeof(Vtx)];
#else
Vtx int_sum_baketu_v[] = {
#include "assets/int_sum_baketu_v.inc"
};
#endif

Gfx int_sum_baketu_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_baketu_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_baketu_hand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_baketu_v, 23, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_baketu_s_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 6, 7, 8, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 80, int_sum_baketu_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 9, 10, 11, 12, 9, 11, 13, 14, 15),
    gsSPNTriangles_5b(11, 16, 17, 14, 9, 12, 22, 14, 12, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 18, 19, 20, 18, 20, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, int_sum_baketu_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_baketu_v[23], 11, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 4, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 6, 9, 7, 4, 10, 9, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};
