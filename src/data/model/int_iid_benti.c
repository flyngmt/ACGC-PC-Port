#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iid_benti_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iid_benchi_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iid_benchi_pal[] = {
#include "assets/int_iid_benchi_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_iid_benchi_se2_tex_pal[0x20 / sizeof(u16)];
#else
u16 int_iid_benchi_se2_tex_pal[] = {
#include "assets/int_iid_benchi_se2_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_iid_benchi_se3_tex_pal[0x20 / sizeof(u16)];
#else
u16 int_iid_benchi_se3_tex_pal[] = {
#include "assets/int_iid_benchi_se3_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_benchi_se1_tex[0x200];
#else
u8 int_iid_benchi_se1_tex[] = {
#include "assets/int_iid_benchi_se1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_benchi_se2_tex[0x200];
#else
u8 int_iid_benchi_se2_tex[] = {
#include "assets/int_iid_benchi_se2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_benchi_se3_tex[0x200];
#else
u8 int_iid_benchi_se3_tex[] = {
#include "assets/int_iid_benchi_se3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_benchi_ue_tex[0x20];
#else
u8 int_iid_benchi_ue_tex[] = {
#include "assets/int_iid_benchi_ue_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_benchi_koshi_tex[0x40];
#else
u8 int_iid_benchi_koshi_tex[] = {
#include "assets/int_iid_benchi_koshi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_benchi_koshi2_tex[0x40];
#else
u8 int_iid_benchi_koshi2_tex[] = {
#include "assets/int_iid_benchi_koshi2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_benchi_shita_tex[0x20];
#else
u8 int_iid_benchi_shita_tex[] = {
#include "assets/int_iid_benchi_shita_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_benchi_ashi_tex[0x40];
#else
u8 int_iid_benchi_ashi_tex[] = {
#include "assets/int_iid_benchi_ashi_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iid_benti_v[0x900 / sizeof(Vtx)];
#else
Vtx int_iid_benti_v[] = {
#include "assets/int_iid_benti_v.inc"
};
#endif

Gfx int_iid_benti_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iid_benchi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, int_iid_benchi_ashi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iid_benti_v, 32, 0),
    gsSPNTrianglesInit_5b(42, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 0, 11, 12, 9),
    gsSPNTriangles_5b(11, 9, 8, 1, 7, 6, 1, 6, 11, 0, 10, 7),
    gsSPNTriangles_5b(0, 7, 1, 13, 14, 0, 13, 0, 15, 16, 2, 1),
    gsSPNTriangles_5b(16, 1, 13, 17, 3, 2, 17, 2, 18, 15, 0, 3),
    gsSPNTriangles_5b(15, 3, 17, 17, 16, 13, 17, 13, 15, 19, 20, 21),
    gsSPNTriangles_5b(19, 21, 22, 22, 23, 10, 22, 10, 19, 19, 10, 7),
    gsSPNTriangles_5b(19, 7, 20, 20, 7, 24, 20, 24, 21, 21, 24, 23),
    gsSPNTriangles_5b(21, 23, 22, 25, 26, 27, 25, 27, 28, 24, 29, 25),
    gsSPNTriangles_5b(24, 25, 23, 7, 27, 29, 7, 29, 24, 10, 28, 27),
    gsSPNTriangles_5b(10, 27, 7, 23, 25, 28, 23, 28, 10, 0, 0, 0),
    gsSPVertex(&int_iid_benti_v[30], 32, 0),
    gsSPNTrianglesInit_5b(34, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 5, 4, 8, 4, 0, 9, 10, 11),
    gsSPNTriangles_5b(9, 11, 8, 1, 7, 6, 1, 6, 9, 0, 4, 7),
    gsSPNTriangles_5b(0, 7, 1, 12, 13, 0, 12, 0, 14, 15, 2, 1),
    gsSPNTriangles_5b(15, 1, 12, 16, 3, 2, 16, 2, 15, 14, 0, 3),
    gsSPNTriangles_5b(14, 3, 16, 17, 18, 12, 17, 12, 14, 19, 20, 21),
    gsSPNTriangles_5b(19, 21, 22, 22, 23, 4, 22, 4, 19, 19, 24, 25),
    gsSPNTriangles_5b(19, 25, 20, 20, 7, 26, 20, 26, 21, 21, 26, 23),
    gsSPNTriangles_5b(21, 23, 22, 27, 28, 29, 27, 29, 30, 0, 0, 0),
    gsSPVertex(&int_iid_benti_v[61], 27, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 0, 7, 8, 5, 7, 5, 9, 3, 2, 8),
    gsSPNTriangles_5b(3, 8, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_iid_benchi_shita_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12, 11, 12, 13, 11, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(15, 17, 18, 16, 15, 12, 16, 12, 11, 18, 17, 14),
    gsSPNTriangles_5b(18, 14, 13, 19, 20, 21, 19, 21, 22, 23, 24, 25),
    gsSPNTriangles_5b(23, 25, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, int_iid_benchi_koshi2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iid_benti_v[88], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, int_iid_benchi_koshi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_iid_benti_v[100], 24, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(23, 20, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_iid_benchi_ue_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iid_benti_v[124], 20, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iid_benchi_se3_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iid_benchi_se3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 9, 11, 10, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iid_benchi_se2_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iid_benchi_se2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 14, 15, 12, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iid_benchi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iid_benchi_se1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 18, 19, 16, 0, 0, 0),
    gsSPEndDisplayList(),
};
