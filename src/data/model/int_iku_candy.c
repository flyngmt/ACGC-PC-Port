#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_candy_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_candy_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_candy_pal[] = {
#include "assets/int_iku_candy_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_candy_bb_tex_txt[0x400];
#else
u8 int_iku_candy_bb_tex_txt[] = {
#include "assets/int_iku_candy_bb_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_candy_ab_tex_txt[0x400];
#else
u8 int_iku_candy_ab_tex_txt[] = {
#include "assets/int_iku_candy_ab_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_candy_v[0x340 / sizeof(Vtx)];
#else
Vtx int_iku_candy_v[] = {
#include "assets/int_iku_candy_v.inc"
};
#endif

Gfx int_iku_candy_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_candy_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_iku_candy_bb_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_candy_v, 28, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(6, 17, 3, 2, 18, 19, 2, 19, 0, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 11, 11, 13, 24, 16, 26, 27),
    gsSPNTriangles_5b(27, 14, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_iku_candy_ab_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iku_candy_v[28], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_iku_candy_off_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_candy_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_iku_candy_bb_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iku_candy_v[44], 8, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 3, 2),
    gsSPNTriangles_5b(4, 2, 5, 6, 7, 4, 6, 4, 5, 7, 6, 1),
    gsSPNTriangles_5b(7, 1, 0, 7, 0, 3, 7, 3, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};
