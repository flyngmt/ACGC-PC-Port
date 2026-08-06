#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_cont_bed01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_cont_bed01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_cont_bed01_pal[] = {
#include "assets/int_sum_cont_bed01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_cont_bed01_head_tex[0x200];
#else
u8 int_sum_cont_bed01_head_tex[] = {
#include "assets/int_sum_cont_bed01_head_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_cont_bed01_headside_tex[0x80];
#else
u8 int_sum_cont_bed01_headside_tex[] = {
#include "assets/int_sum_cont_bed01_headside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_cont_bed01_top_tex[0x200];
#else
u8 int_sum_cont_bed01_top_tex[] = {
#include "assets/int_sum_cont_bed01_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_cont_bed01_topside_tex[0x100];
#else
u8 int_sum_cont_bed01_topside_tex[] = {
#include "assets/int_sum_cont_bed01_topside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_cont_bed01_pillow_tex[0x80];
#else
u8 int_sum_cont_bed01_pillow_tex[] = {
#include "assets/int_sum_cont_bed01_pillow_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_cont_bed01_pillow2_tex[0x80];
#else
u8 int_sum_cont_bed01_pillow2_tex[] = {
#include "assets/int_sum_cont_bed01_pillow2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_cont_bed01_pillow3_tex[0x80];
#else
u8 int_sum_cont_bed01_pillow3_tex[] = {
#include "assets/int_sum_cont_bed01_pillow3_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_cont_bed01_v[0x380 / sizeof(Vtx)];
#else
Vtx int_sum_cont_bed01_v[] = {
#include "assets/int_sum_cont_bed01_v.inc"
};
#endif

Gfx int_sum_cont_bed01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_cont_bed01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_cont_bed01_pillow3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_cont_bed01_v, 28, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_cont_bed01_pillow2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 5, 6, 7, 6, 8, 7, 8, 9, 7),
    gsSPNTriangles_5b(9, 5, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_cont_bed01_pillow_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 10, 13, 11, 10, 12, 14),
    gsSPNTriangles_5b(10, 14, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_cont_bed01_topside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 15, 16, 17, 15, 17, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_cont_bed01_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 19, 20, 21, 19, 22, 20, 22, 23, 20),
    gsSPNTriangles_5b(23, 21, 20, 24, 25, 19, 24, 19, 21, 23, 22, 26),
    gsSPNTriangles_5b(23, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_cont_bed01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_cont_bed01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_sum_cont_bed01_headside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_cont_bed01_v[28], 28, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_cont_bed01_head_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 26, 27, 0, 0, 0),
    gsSPEndDisplayList(),
};
