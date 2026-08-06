#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_asi_lanp01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_asi_lanp01_pal[] = {
#include "assets/int_sum_asi_lanp01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_asi_lanp01_shade_tex_txt[0x100];
#else
u8 int_sum_asi_lanp01_shade_tex_txt[] = {
#include "assets/int_sum_asi_lanp01_shade_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_asi_lanp01_bin_tex_txt[0x200];
#else
u8 int_sum_asi_lanp01_bin_tex_txt[] = {
#include "assets/int_sum_asi_lanp01_bin_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_asi_lanp01_v[0x180 / sizeof(Vtx)];
#else
Vtx int_sum_asi_lanp01_v[] = {
#include "assets/int_sum_asi_lanp01_v.inc"
};
#endif

Gfx int_sum_asi_lanp01_off_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_asi_lanp01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_asi_lanp01_shade_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 380, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_asi_lanp01_v, 24, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 1, 5, 6, 7),
    gsSPNTriangles_5b(8, 7, 4, 9, 10, 6, 11, 12, 10, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_asi_lanp01_bin_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 182, 182, 182, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(16, 13, 14, 15, 16, 17, 18, 16, 18, 19),
    gsSPNTriangles_5b(20, 13, 21, 20, 21, 22, 16, 23, 17, 22, 23, 16),
    gsSPNTriangles_5b(22, 21, 23, 19, 18, 14, 20, 14, 13, 20, 19, 14),
    gsSPNTriangles_5b(14, 18, 15, 18, 17, 15, 17, 23, 15, 23, 21, 15),
    gsSPNTriangles_5b(21, 13, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
