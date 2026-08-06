#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_asi_chair02_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_asi_chair02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_asi_chair02_pal[] = {
#include "assets/int_sum_asi_chair02_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_asi_chair02_head_tex[0x200];
#else
u8 int_sum_asi_chair02_head_tex[] = {
#include "assets/int_sum_asi_chair02_head_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_asi_chair02_side_tex[0x200];
#else
u8 int_sum_asi_chair02_side_tex[] = {
#include "assets/int_sum_asi_chair02_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_asi_chair02_seat_tex[0x80];
#else
u8 int_sum_asi_chair02_seat_tex[] = {
#include "assets/int_sum_asi_chair02_seat_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_asi_chair02_board_tex[0x80];
#else
u8 int_sum_asi_chair02_board_tex[] = {
#include "assets/int_sum_asi_chair02_board_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_asi_chair02_arm_tex[0x200];
#else
u8 int_sum_asi_chair02_arm_tex[] = {
#include "assets/int_sum_asi_chair02_arm_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_asi_chair02_armside_tex[0x100];
#else
u8 int_sum_asi_chair02_armside_tex[] = {
#include "assets/int_sum_asi_chair02_armside_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_asi_chair02_v[0x280 / sizeof(Vtx)];
#else
Vtx int_sum_asi_chair02_v[] = {
#include "assets/int_sum_asi_chair02_v.inc"
};
#endif

Gfx int_sum_asi_chair02_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_asi_chair02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_asi_chair02_board_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_asi_chair02_v, 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_asi_chair02_seat_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_asi_chair02_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_asi_chair02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_asi_chair02_armside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_asi_chair02_v[8], 28, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 1, 0, 0, 4, 3),
    gsSPNTriangles_5b(5, 6, 7, 7, 8, 5, 9, 8, 7, 10, 11, 12),
    gsSPNTriangles_5b(13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_asi_chair02_arm_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_asi_chair02_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 20, 21, 22, 20, 22, 23, 24, 25, 21),
    gsSPNTriangles_5b(24, 21, 20, 26, 27, 25, 26, 25, 24, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_sum_asi_chair02_head_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_asi_chair02_v[36], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
