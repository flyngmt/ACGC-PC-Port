#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_gre_bed01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_gre_bed01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_gre_bed01_pal[] = {
#include "assets/int_sum_gre_bed01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_gre_bed01_headback_tex[0x200];
#else
u8 int_sum_gre_bed01_headback_tex[] = {
#include "assets/int_sum_gre_bed01_headback_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_gre_bed01_headfront_tex[0x100];
#else
u8 int_sum_gre_bed01_headfront_tex[] = {
#include "assets/int_sum_gre_bed01_headfront_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_gre_bed01_top_tex[0x300];
#else
u8 int_sum_gre_bed01_top_tex[] = {
#include "assets/int_sum_gre_bed01_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_gre_bed01_pillow_tex[0x80];
#else
u8 int_sum_gre_bed01_pillow_tex[] = {
#include "assets/int_sum_gre_bed01_pillow_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_gre_bed01_side2_tex[0x100];
#else
u8 int_sum_gre_bed01_side2_tex[] = {
#include "assets/int_sum_gre_bed01_side2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_gre_bed01_book_tex[0x80];
#else
u8 int_sum_gre_bed01_book_tex[] = {
#include "assets/int_sum_gre_bed01_book_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_gre_bed01_v[0x380 / sizeof(Vtx)];
#else
Vtx int_sum_gre_bed01_v[] = {
#include "assets/int_sum_gre_bed01_v.inc"
};
#endif

Gfx int_sum_gre_bed01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_gre_bed01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_gre_bed01_book_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_gre_bed01_v, 13, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 1, 0),
    gsSPNTriangles_5b(4, 0, 5, 1, 6, 7, 1, 7, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_gre_bed01_pillow_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 9, 11, 10, 11, 12, 10),
    gsSPNTriangles_5b(12, 8, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_gre_bed01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_gre_bed01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_gre_bed01_side2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_gre_bed01_v[13], 21, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 4, 3, 2, 4, 2, 5, 6, 1, 0),
    gsSPNTriangles_5b(6, 0, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, int_sum_gre_bed01_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 18, 17, 20, 17, 12, 20, 12, 15, 20),
    gsSPNTriangles_5b(15, 18, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_gre_bed01_headfront_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_sum_gre_bed01_v[34], 22, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 3, 2),
    gsSPNTriangles_5b(4, 2, 5, 6, 7, 8, 6, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_gre_bed01_headback_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 14, 15, 16, 14, 16, 17, 18, 19, 14),
    gsSPNTriangles_5b(18, 14, 17, 20, 19, 18, 20, 18, 21, 0, 0, 0),
    gsSPEndDisplayList(),
};
