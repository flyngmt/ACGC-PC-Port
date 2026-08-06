#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iid_surf_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iid_surf_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iid_surf_pal[] = {
#include "assets/int_iid_surf_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_surf_mae_tex[0x200];
#else
u8 int_iid_surf_mae_tex[] = {
#include "assets/int_iid_surf_mae_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_surf_ushiro_tex[0x100];
#else
u8 int_iid_surf_ushiro_tex[] = {
#include "assets/int_iid_surf_ushiro_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_surf_fin_tex[0x80];
#else
u8 int_iid_surf_fin_tex[] = {
#include "assets/int_iid_surf_fin_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_surf_tate_tex[0x80];
#else
u8 int_iid_surf_tate_tex[] = {
#include "assets/int_iid_surf_tate_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iid_surf_v[0xED0 / sizeof(Vtx)];
#else
Vtx int_iid_surf_v[] = {
#include "assets/int_iid_surf_v.inc"
};
#endif

Gfx int_iid_surf_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iid_surf_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iid_surf_tate_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iid_surf_v, 32, 0),
    gsSPNTrianglesInit_5b(42, 0, 1, 2, 1, 3, 2, 4, 3, 1),
    gsSPNTriangles_5b(4, 1, 5, 6, 2, 3, 6, 3, 4, 6, 4, 5),
    gsSPNTriangles_5b(5, 1, 0, 5, 0, 7, 7, 0, 2, 7, 2, 6),
    gsSPNTriangles_5b(6, 5, 7, 8, 9, 10, 10, 11, 8, 8, 12, 13),
    gsSPNTriangles_5b(14, 8, 13, 15, 14, 16, 15, 16, 17, 18, 19, 16),
    gsSPNTriangles_5b(19, 20, 16, 20, 21, 22, 22, 23, 20, 24, 23, 22),
    gsSPNTriangles_5b(24, 22, 25, 26, 20, 23, 26, 23, 24, 25, 27, 20),
    gsSPNTriangles_5b(25, 20, 26, 26, 24, 25, 28, 21, 20, 28, 20, 26),
    gsSPNTriangles_5b(25, 22, 21, 25, 21, 28, 25, 28, 26, 29, 20, 19),
    gsSPNTriangles_5b(29, 19, 30, 31, 16, 20, 31, 20, 26, 30, 19, 16),
    gsSPNTriangles_5b(30, 16, 31, 31, 26, 30, 30, 19, 18, 0, 0, 0),
    gsSPVertex(&int_iid_surf_v[32], 32, 0),
    gsSPNTrianglesInit_5b(41, 0, 1, 2, 2, 1, 3, 2, 3, 4),
    gsSPNTriangles_5b(4, 0, 2, 5, 6, 3, 5, 3, 4, 7, 8, 6),
    gsSPNTriangles_5b(7, 6, 5, 5, 4, 7, 9, 10, 8, 9, 8, 7),
    gsSPNTriangles_5b(4, 11, 10, 4, 10, 12, 4, 9, 7, 13, 14, 10),
    gsSPNTriangles_5b(13, 10, 9, 15, 16, 14, 15, 14, 13, 9, 10, 16),
    gsSPNTriangles_5b(9, 16, 15, 15, 13, 9, 17, 18, 14, 17, 14, 13),
    gsSPNTriangles_5b(15, 16, 18, 15, 18, 17, 15, 17, 13, 19, 20, 21),
    gsSPNTriangles_5b(19, 21, 22, 13, 14, 20, 13, 20, 19, 22, 21, 14),
    gsSPNTriangles_5b(22, 14, 13, 13, 19, 22, 23, 24, 14, 23, 14, 13),
    gsSPNTriangles_5b(22, 21, 24, 22, 24, 23, 22, 23, 13, 25, 26, 27),
    gsSPNTriangles_5b(25, 28, 26, 29, 30, 31, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_iid_surf_v[64], 32, 0),
    gsSPNTrianglesInit_5b(53, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(1, 7, 8, 8, 9, 1, 10, 11, 12, 11, 2, 12),
    gsSPNTriangles_5b(13, 2, 11, 13, 11, 14, 15, 12, 2, 15, 2, 13),
    gsSPNTriangles_5b(15, 13, 14, 14, 11, 10, 14, 10, 16, 16, 10, 12),
    gsSPNTriangles_5b(16, 12, 15, 15, 14, 16, 17, 9, 8, 17, 8, 18),
    gsSPNTriangles_5b(19, 1, 9, 19, 9, 17, 19, 17, 18, 20, 7, 1),
    gsSPNTriangles_5b(20, 1, 19, 18, 8, 7, 18, 7, 20, 18, 20, 19),
    gsSPNTriangles_5b(21, 6, 5, 21, 5, 22, 23, 3, 6, 23, 6, 21),
    gsSPNTriangles_5b(23, 21, 22, 24, 4, 3, 24, 3, 23, 22, 5, 4),
    gsSPNTriangles_5b(22, 4, 24, 22, 24, 23, 13, 2, 1, 13, 1, 19),
    gsSPNTriangles_5b(13, 19, 25, 26, 27, 0, 26, 0, 25, 19, 1, 27),
    gsSPNTriangles_5b(19, 27, 26, 19, 26, 25, 22, 5, 11, 22, 11, 14),
    gsSPNTriangles_5b(28, 29, 5, 28, 5, 22, 28, 22, 14, 30, 31, 29),
    gsSPNTriangles_5b(30, 29, 28, 30, 28, 14, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_iid_surf_v[96], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iid_surf_fin_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iid_surf_v[100], 32, 0),
    gsSPNTrianglesInit_5b(35, 0, 1, 2, 2, 1, 3, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 10, 9, 11, 12, 10, 11),
    gsSPNTriangles_5b(13, 14, 15, 13, 15, 16, 14, 17, 10, 14, 10, 15),
    gsSPNTriangles_5b(18, 19, 20, 21, 12, 22, 21, 22, 18, 12, 11, 23),
    gsSPNTriangles_5b(12, 23, 22, 11, 9, 24, 11, 24, 23, 20, 21, 18),
    gsSPNTriangles_5b(25, 17, 24, 24, 17, 23, 17, 22, 23, 17, 25, 10),
    gsSPNTriangles_5b(25, 8, 10, 25, 24, 8, 24, 9, 8, 19, 18, 26),
    gsSPNTriangles_5b(18, 17, 26, 17, 18, 22, 15, 21, 16, 15, 10, 12),
    gsSPNTriangles_5b(15, 12, 21, 27, 28, 29, 27, 30, 28, 31, 30, 27),
    gsSPVertex(&int_iid_surf_v[132], 32, 0),
    gsSPNTrianglesInit_5b(31, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(5, 6, 7, 8, 6, 9, 6, 5, 9, 10, 11, 12),
    gsSPNTriangles_5b(13, 10, 12, 13, 14, 1, 5, 13, 1, 10, 5, 15),
    gsSPNTriangles_5b(5, 7, 15, 13, 5, 10, 16, 3, 6, 2, 17, 15),
    gsSPNTriangles_5b(2, 15, 7, 17, 11, 10, 17, 10, 15, 3, 2, 7),
    gsSPNTriangles_5b(3, 7, 6, 6, 8, 16, 18, 5, 1, 18, 1, 0),
    gsSPNTriangles_5b(19, 18, 0, 19, 0, 4, 20, 21, 22, 20, 22, 23),
    gsSPNTriangles_5b(24, 20, 23, 25, 26, 27, 27, 26, 28, 26, 29, 28),
    gsSPVertex(&int_iid_surf_v[162], 18, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 0, 4, 1, 6, 7, 8, 9, 10, 11),
    gsSPNTriangles_5b(9, 11, 12, 10, 2, 1, 10, 1, 11, 6, 9, 12),
    gsSPNTriangles_5b(6, 12, 7, 8, 13, 6, 14, 4, 5, 14, 5, 15),
    gsSPNTriangles_5b(16, 14, 15, 16, 15, 17, 5, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_iid_surf_ushiro_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iid_surf_v[180], 17, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 6, 4, 5, 6, 5, 7, 8, 6, 7),
    gsSPNTriangles_5b(8, 7, 9, 10, 8, 9, 10, 9, 11, 12, 10, 11),
    gsSPNTriangles_5b(12, 11, 13, 14, 12, 13, 14, 13, 15, 14, 15, 16),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_iid_surf_mae_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_iid_surf_v[197], 32, 0),
    gsSPNTrianglesInit_5b(43, 0, 1, 2, 0, 2, 3, 2, 1, 4),
    gsSPNTriangles_5b(2, 4, 5, 6, 7, 8, 6, 8, 9, 8, 10, 11),
    gsSPNTriangles_5b(8, 11, 9, 10, 12, 13, 10, 13, 11, 12, 14, 15),
    gsSPNTriangles_5b(12, 15, 13, 14, 16, 17, 14, 17, 15, 16, 18, 19),
    gsSPNTriangles_5b(16, 19, 17, 18, 20, 21, 18, 21, 19, 20, 5, 4),
    gsSPNTriangles_5b(20, 4, 21, 7, 22, 8, 22, 23, 10, 22, 10, 8),
    gsSPNTriangles_5b(23, 24, 12, 23, 12, 10, 24, 25, 14, 24, 14, 12),
    gsSPNTriangles_5b(25, 26, 16, 25, 16, 14, 26, 27, 18, 26, 18, 16),
    gsSPNTriangles_5b(27, 3, 20, 27, 20, 18, 3, 2, 5, 3, 5, 20),
    gsSPNTriangles_5b(28, 22, 7, 28, 7, 6, 28, 29, 23, 28, 23, 22),
    gsSPNTriangles_5b(29, 30, 24, 29, 24, 23, 30, 31, 25, 30, 25, 24),
    gsSPVertex(&int_iid_surf_v[229], 8, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 4, 6, 7, 4, 7, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};
