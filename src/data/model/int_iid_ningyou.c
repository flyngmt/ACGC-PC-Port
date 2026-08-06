#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iid_ningyou_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iid_ningyou_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iid_ningyou_pal[] = {
#include "assets/int_iid_ningyou_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_ningyou_hada_tex[0x80];
#else
u8 int_iid_ningyou_hada_tex[] = {
#include "assets/int_iid_ningyou_hada_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_ningyou_boushi_tex[0x80];
#else
u8 int_iid_ningyou_boushi_tex[] = {
#include "assets/int_iid_ningyou_boushi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_ningyou_kao_tex[0x200];
#else
u8 int_iid_ningyou_kao_tex[] = {
#include "assets/int_iid_ningyou_kao_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_ningyou_kutushita_tex[0x80];
#else
u8 int_iid_ningyou_kutushita_tex[] = {
#include "assets/int_iid_ningyou_kutushita_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_ningyou_futi_tex[0x20];
#else
u8 int_iid_ningyou_futi_tex[] = {
#include "assets/int_iid_ningyou_futi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_ningyou_fuku_tex[0x20];
#else
u8 int_iid_ningyou_fuku_tex[] = {
#include "assets/int_iid_ningyou_fuku_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_ningyou_ribbon_tex[0x80];
#else
u8 int_iid_ningyou_ribbon_tex[] = {
#include "assets/int_iid_ningyou_ribbon_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_ningyou_ashi_tex[0x40];
#else
u8 int_iid_ningyou_ashi_tex[] = {
#include "assets/int_iid_ningyou_ashi_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iid_ningyou_v[0x1070 / sizeof(Vtx)];
#else
Vtx int_iid_ningyou_v[] = {
#include "assets/int_iid_ningyou_v.inc"
};
#endif

Gfx int_iid_ningyou_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iid_ningyou_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_iid_ningyou_ashi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iid_ningyou_v, 27, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 0, 5, 6, 0, 6, 7, 0, 7, 8),
    gsSPNTriangles_5b(9, 3, 2, 9, 2, 10, 9, 10, 11, 11, 12, 13),
    gsSPNTriangles_5b(11, 13, 3, 11, 3, 9, 14, 15, 16, 14, 16, 17),
    gsSPNTriangles_5b(16, 18, 4, 16, 4, 3, 16, 3, 13, 16, 13, 19),
    gsSPNTriangles_5b(16, 19, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iid_ningyou_ribbon_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 20, 21, 22, 20, 22, 23, 21, 20, 24),
    gsSPNTriangles_5b(21, 24, 25, 21, 26, 22, 25, 26, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_iid_ningyou_fuku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iid_ningyou_v[27], 16, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 2, 3, 2, 5),
    gsSPNTriangles_5b(6, 7, 0, 2, 1, 8, 2, 8, 9, 2, 9, 5),
    gsSPNTriangles_5b(10, 6, 0, 10, 0, 11, 12, 6, 10, 12, 10, 13),
    gsSPNTriangles_5b(14, 7, 6, 14, 6, 12, 14, 12, 15, 11, 0, 2),
    gsSPNTriangles_5b(11, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_iid_ningyou_futi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iid_ningyou_v[43], 27, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 5, 6, 0, 6, 7, 0, 7, 1, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 8, 11, 12, 13, 14, 15, 13, 15, 16),
    gsSPNTriangles_5b(15, 17, 18, 15, 18, 16, 19, 20, 21, 19, 21, 22),
    gsSPNTriangles_5b(23, 24, 19, 23, 19, 22, 25, 26, 8, 25, 8, 12),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iid_ningyou_kutushita_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iid_ningyou_v[70], 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 11, 12, 13),
    gsSPNTriangles_5b(11, 13, 14, 11, 14, 8, 15, 16, 3, 15, 3, 2),
    gsSPNTriangles_5b(16, 6, 5, 16, 5, 3, 17, 18, 19, 17, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 21, 23, 24, 23, 18, 17, 23, 17, 25),
    gsSPNTriangles_5b(26, 27, 22, 26, 22, 21, 28, 29, 30, 28, 30, 31),
    gsSPNTriangles_5b(31, 21, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_iid_ningyou_v[102], 18, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 5, 8, 9, 5, 9, 6, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 14, 16, 17, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iid_ningyou_kao_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iid_ningyou_v[120], 32, 0),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 0, 2, 3, 2, 4, 3),
    gsSPNTriangles_5b(1, 5, 6, 7, 8, 9, 7, 9, 10, 8, 11, 9),
    gsSPNTriangles_5b(11, 12, 13, 14, 15, 16, 15, 17, 18, 15, 18, 16),
    gsSPNTriangles_5b(17, 19, 18, 14, 20, 17, 14, 17, 21, 20, 22, 23),
    gsSPNTriangles_5b(24, 25, 26, 25, 27, 28, 25, 28, 26, 27, 29, 28),
    gsSPNTriangles_5b(27, 30, 29, 29, 31, 28, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_iid_ningyou_v[152], 25, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 0, 2, 3, 0, 4, 1),
    gsSPNTriangles_5b(4, 5, 2, 4, 2, 1, 5, 6, 2, 7, 8, 9),
    gsSPNTriangles_5b(7, 9, 10, 11, 12, 13, 12, 14, 15, 12, 15, 16),
    gsSPNTriangles_5b(17, 18, 19, 17, 19, 20, 21, 22, 23, 21, 23, 24),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iid_ningyou_boushi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iid_ningyou_v[177], 21, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 16, 18, 19),
    gsSPNTriangles_5b(16, 19, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iid_ningyou_hada_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iid_ningyou_v[198], 32, 0),
    gsSPNTrianglesInit_5b(27, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 10, 5, 4),
    gsSPNTriangles_5b(10, 4, 11, 12, 13, 9, 12, 9, 8, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 6, 1, 18, 6, 18, 19, 6, 19, 7),
    gsSPNTriangles_5b(13, 2, 1, 13, 1, 6, 12, 20, 2, 12, 2, 13),
    gsSPNTriangles_5b(16, 21, 20, 16, 20, 17, 22, 23, 6, 22, 6, 7),
    gsSPNTriangles_5b(3, 2, 20, 24, 25, 26, 27, 28, 29, 27, 29, 30),
    gsSPVertex(&int_iid_ningyou_v[229], 32, 0),
    gsSPNTrianglesInit_5b(29, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 6, 7, 8, 5, 7, 5, 4, 9, 10, 11),
    gsSPNTriangles_5b(9, 11, 12, 9, 12, 13, 0, 3, 14, 0, 14, 15),
    gsSPNTriangles_5b(16, 17, 4, 16, 4, 6, 18, 19, 20, 18, 20, 21),
    gsSPNTriangles_5b(20, 17, 16, 20, 16, 21, 9, 13, 19, 9, 19, 18),
    gsSPNTriangles_5b(22, 5, 8, 22, 8, 23, 1, 22, 23, 1, 23, 2),
    gsSPNTriangles_5b(17, 20, 24, 17, 24, 7, 17, 7, 4, 25, 26, 27),
    gsSPNTriangles_5b(25, 27, 28, 25, 28, 29, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_iid_ningyou_v[259], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
