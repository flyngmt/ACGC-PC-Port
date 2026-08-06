#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iid_funediary_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 int_iid_funediary[0x20];
#else
ATTRIBUTE_ALIGN(32) u8 int_iid_funediary[] = {
#include "assets/int_iid_funediary.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_funediary_mae_tex[0x20];
#else
u8 int_iid_funediary_mae_tex[] = {
#include "assets/int_iid_funediary_mae_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_funediary_hyoushi_tex[0x200];
#else
u8 int_iid_funediary_hyoushi_tex[] = {
#include "assets/int_iid_funediary_hyoushi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_funediary_soko_tex[0x20];
#else
u8 int_iid_funediary_soko_tex[] = {
#include "assets/int_iid_funediary_soko_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_funediary_ue_tex[0x20];
#else
u8 int_iid_funediary_ue_tex[] = {
#include "assets/int_iid_funediary_ue_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_funediary_esaki_tex[0x20];
#else
u8 int_iid_funediary_esaki_tex[] = {
#include "assets/int_iid_funediary_esaki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_funediary_ebody_tex[0x20];
#else
u8 int_iid_funediary_ebody_tex[] = {
#include "assets/int_iid_funediary_ebody_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iid_funediary_v[0x380 / sizeof(Vtx)];
#else
Vtx int_iid_funediary_v[] = {
#include "assets/int_iid_funediary_v.inc"
};
#endif

Gfx int_iid_funediary_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iid_funediary),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_iid_funediary_ebody_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iid_funediary_v, 27, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 6, 7, 5, 6, 5, 4, 8, 9, 7),
    gsSPNTriangles_5b(8, 7, 6, 10, 11, 9, 10, 9, 8, 3, 2, 11),
    gsSPNTriangles_5b(3, 11, 10, 12, 13, 14, 12, 14, 15, 12, 15, 16),
    gsSPNTriangles_5b(12, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_iid_funediary_esaki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(6, 18, 19, 20, 19, 21, 20, 21, 22, 23),
    gsSPNTriangles_5b(22, 24, 23, 24, 25, 23, 25, 18, 26, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_iid_funediary_ue_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iid_funediary_v[27], 29, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 6, 8, 9, 6, 9, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_iid_funediary_soko_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 10, 12, 13, 14, 15, 10),
    gsSPNTriangles_5b(14, 10, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iid_funediary_hyoushi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(5, 16, 17, 18, 19, 20, 21, 22, 19, 21),
    gsSPNTriangles_5b(22, 21, 23, 16, 18, 24, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_iid_funediary_mae_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 25, 26, 27, 25, 27, 28, 0, 0, 0),
    gsSPEndDisplayList(),
};
