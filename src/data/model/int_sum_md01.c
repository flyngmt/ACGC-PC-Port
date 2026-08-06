#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_md01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_md01_pal[] = {
#include "assets/int_sum_md01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_md01_back_tex_txt[0x200];
#else
u8 int_sum_md01_back_tex_txt[] = {
#include "assets/int_sum_md01_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_md01_front_tex_txt[0x400];
#else
u8 int_sum_md01_front_tex_txt[] = {
#include "assets/int_sum_md01_front_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_md01_hand_tex_txt[0x80];
#else
u8 int_sum_md01_hand_tex_txt[] = {
#include "assets/int_sum_md01_hand_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_md01_v[0x1F0 / sizeof(Vtx)];
#else
Vtx int_sum_md01_v[] = {
#include "assets/int_sum_md01_v.inc"
};
#endif

Gfx int_sum_md01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_md01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_md01_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_md01_v, 31, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 5, 4, 6),
    gsSPNTriangles_5b(1, 6, 2, 7, 5, 1, 8, 5, 7, 2, 6, 9),
    gsSPNTriangles_5b(6, 4, 10, 10, 4, 3, 10, 3, 11, 12, 8, 7),
    gsSPNTriangles_5b(1, 0, 7, 10, 9, 6, 6, 1, 5, 5, 8, 3),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_sum_md01_front_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(17, 13, 14, 15, 16, 17, 18, 17, 19, 20),
    gsSPNTriangles_5b(20, 19, 21, 22, 14, 13, 20, 21, 23, 24, 15, 25),
    gsSPNTriangles_5b(20, 18, 17, 22, 26, 25, 22, 17, 16, 25, 14, 22),
    gsSPNTriangles_5b(26, 22, 16, 15, 14, 25, 21, 19, 13, 13, 15, 21),
    gsSPNTriangles_5b(13, 19, 17, 17, 22, 13, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_md01_hand_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 27, 28, 29, 29, 30, 27, 0, 0, 0),
    gsSPEndDisplayList(),
};
