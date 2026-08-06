#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_whi_sofa01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_whi_sofa01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_whi_sofa01_pal[] = {
#include "assets/int_sum_whi_sofa01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_sofa01_seat_tex[0x200];
#else
u8 int_sum_whi_sofa01_seat_tex[] = {
#include "assets/int_sum_whi_sofa01_seat_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_sofa01_heard_tex[0x100];
#else
u8 int_sum_whi_sofa01_heard_tex[] = {
#include "assets/int_sum_whi_sofa01_heard_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_sofa01_arm_tex[0x100];
#else
u8 int_sum_whi_sofa01_arm_tex[] = {
#include "assets/int_sum_whi_sofa01_arm_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_sofa01_foot_tex[0x100];
#else
u8 int_sum_whi_sofa01_foot_tex[] = {
#include "assets/int_sum_whi_sofa01_foot_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_sofa01_side_tex[0x200];
#else
u8 int_sum_whi_sofa01_side_tex[] = {
#include "assets/int_sum_whi_sofa01_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_whi_sofa01_top_tex[0x80];
#else
u8 int_sum_whi_sofa01_top_tex[] = {
#include "assets/int_sum_whi_sofa01_top_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_whi_sofa01_v[0x3C0 / sizeof(Vtx)];
#else
Vtx int_sum_whi_sofa01_v[] = {
#include "assets/int_sum_whi_sofa01_v.inc"
};
#endif

Gfx int_sum_whi_sofa01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_whi_sofa01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_whi_sofa01_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_whi_sofa01_v, 27, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_whi_sofa01_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7, 9, 10, 11, 10, 12, 11, 13, 14, 15),
    gsSPNTriangles_5b(14, 16, 15, 9, 17, 10, 17, 15, 10, 17, 13, 15),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_whi_sofa01_heard_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7, 18, 19, 20, 19, 21, 20, 22, 23, 24),
    gsSPNTriangles_5b(22, 25, 23, 24, 23, 26, 23, 19, 26, 19, 18, 26),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_whi_sofa01_seat_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_whi_sofa01_v[27], 7, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 0, 4, 1),
    gsSPNTriangles_5b(4, 5, 1, 0, 6, 4, 6, 5, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_whi_sofa01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_whi_sofa01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_whi_sofa01_foot_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_whi_sofa01_v[34], 26, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 7, 10, 11, 12, 10, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(18, 19, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_whi_sofa01_arm_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 23, 24, 25, 0, 0, 0),
    gsSPEndDisplayList(),
};
