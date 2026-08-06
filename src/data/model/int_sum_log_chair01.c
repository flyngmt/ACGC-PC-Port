#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_log_chair01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_log_chair01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_log_chair01_pal[] = {
#include "assets/int_sum_log_chair01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_chair01_head_tex[0x400];
#else
u8 int_sum_log_chair01_head_tex[] = {
#include "assets/int_sum_log_chair01_head_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_chair01_cusion_tex[0x80];
#else
u8 int_sum_log_chair01_cusion_tex[] = {
#include "assets/int_sum_log_chair01_cusion_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_chair01_seat_tex[0x200];
#else
u8 int_sum_log_chair01_seat_tex[] = {
#include "assets/int_sum_log_chair01_seat_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_chair01_stand_tex[0x100];
#else
u8 int_sum_log_chair01_stand_tex[] = {
#include "assets/int_sum_log_chair01_stand_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_log_chair01_cusion2_tex[0x80];
#else
u8 int_sum_log_chair01_cusion2_tex[] = {
#include "assets/int_sum_log_chair01_cusion2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_log_chair01_v[0x410 / sizeof(Vtx)];
#else
Vtx int_sum_log_chair01_v[] = {
#include "assets/int_sum_log_chair01_v.inc"
};
#endif

Gfx int_sum_log_chair01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_log_chair01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_log_chair01_cusion2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_log_chair01_v, 15, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(4, 0, 2, 5, 6, 7, 5, 7, 8, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_log_chair01_seat_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 9, 10, 11, 9, 11, 12, 13, 9, 12),
    gsSPNTriangles_5b(13, 12, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_log_chair01_cusion_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_sum_log_chair01_v[15], 18, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 3, 8, 2, 8, 0, 2, 9, 10, 11),
    gsSPNTriangles_5b(9, 11, 12, 13, 14, 15, 13, 15, 16, 13, 16, 17),
    gsSPNTriangles_5b(13, 17, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_log_chair01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_log_chair01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_log_chair01_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_log_chair01_v[33], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_sum_log_chair01_head_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_log_chair01_v[45], 20, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};
