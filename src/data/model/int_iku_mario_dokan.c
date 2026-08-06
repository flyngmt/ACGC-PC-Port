#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_mario_dokan_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_mario_dokan_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_mario_dokan_pal[] = {
#include "assets/int_iku_mario_dokan_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_iku_mario_dokan_b_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_iku_mario_dokan_b_tex_pic_ci4_pal[] = {
#include "assets/int_iku_mario_dokan_b_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_mario_dokan_a_tex_txt[0x200];
#else
u8 int_iku_mario_dokan_a_tex_txt[] = {
#include "assets/int_iku_mario_dokan_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_mario_dokan_c_tex_txt[0x40];
#else
u8 int_iku_mario_dokan_c_tex_txt[] = {
#include "assets/int_iku_mario_dokan_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_mario_dokan_b_tex_txt[0x100];
#else
u8 int_iku_mario_dokan_b_tex_txt[] = {
#include "assets/int_iku_mario_dokan_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_mario_dokan_v[0x2F0 / sizeof(Vtx)];
#else
Vtx int_iku_mario_dokan_v[] = {
#include "assets/int_iku_mario_dokan_v.inc"
};
#endif

Gfx int_iku_mario_dokan_model_b_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_mario_dokan_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_iku_mario_dokan_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iku_mario_dokan_v[32], 15, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 3, 4, 5),
    gsSPNTriangles_5b(3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, int_iku_mario_dokan_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 6, 7, 8, 7, 9, 8, 10, 6, 8),
    gsSPNTriangles_5b(9, 11, 8, 12, 10, 8, 11, 13, 8, 14, 12, 8),
    gsSPNTriangles_5b(13, 14, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_iku_mario_dokan_model_a_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_mario_dokan_b_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_iku_mario_dokan_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(int_iku_mario_dokan_v, 32, 0),
    gsSPNTrianglesInit_5b(32, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 6, 0, 3, 6, 3, 7, 8, 6, 7),
    gsSPNTriangles_5b(8, 7, 9, 4, 10, 11, 4, 11, 5, 12, 8, 9),
    gsSPNTriangles_5b(12, 9, 13, 14, 12, 13, 14, 13, 15, 10, 14, 15),
    gsSPNTriangles_5b(10, 15, 11, 16, 17, 18, 16, 18, 19, 17, 20, 21),
    gsSPNTriangles_5b(17, 21, 18, 22, 16, 19, 22, 19, 23, 24, 22, 23),
    gsSPNTriangles_5b(24, 23, 25, 20, 26, 27, 20, 27, 21, 28, 24, 25),
    gsSPNTriangles_5b(28, 25, 29, 30, 28, 29, 30, 29, 31, 26, 30, 31),
    gsSPNTriangles_5b(26, 31, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
