#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_timpani01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_timpani01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_timpani01_pal[] = {
#include "assets/int_sum_timpani01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_timpani01_legtop_tex_txt[0x80];
#else
u8 int_sum_timpani01_legtop_tex_txt[] = {
#include "assets/int_sum_timpani01_legtop_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_timpani01_top_tex_txt[0x200];
#else
u8 int_sum_timpani01_top_tex_txt[] = {
#include "assets/int_sum_timpani01_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_timpani01_leg_tex_txt[0x180];
#else
u8 int_sum_timpani01_leg_tex_txt[] = {
#include "assets/int_sum_timpani01_leg_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_timpani01_pedal_tex_txt[0x100];
#else
u8 int_sum_timpani01_pedal_tex_txt[] = {
#include "assets/int_sum_timpani01_pedal_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_timpani01_crown_tex_txt[0x200];
#else
u8 int_sum_timpani01_crown_tex_txt[] = {
#include "assets/int_sum_timpani01_crown_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_timpani01_side_tex_txt[0x100];
#else
u8 int_sum_timpani01_side_tex_txt[] = {
#include "assets/int_sum_timpani01_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_timpani01_v[0x500 / sizeof(Vtx)];
#else
Vtx int_sum_timpani01_v[] = {
#include "assets/int_sum_timpani01_v.inc"
};
#endif

Gfx int_sum_timpani01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_timpani01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_timpani01_legtop_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_timpani01_v, 30, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_timpani01_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsSPNTrianglesInit_5b(4, 24, 25, 26, 24, 27, 25, 28, 27, 24),
    gsSPNTriangles_5b(28, 29, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_timpani01_leg_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_timpani01_v[30], 30, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_timpani01_pedal_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 24, 25, 26, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_timpani01_crown_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 27, 28, 29, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_timpani01_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsSPVertex(&int_sum_timpani01_v[60], 20, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(5, 3, 6, 8, 5, 9, 5, 7, 9, 10, 3, 5),
    gsSPNTriangles_5b(3, 1, 6, 1, 11, 6, 1, 12, 11, 1, 0, 12),
    gsSPNTriangles_5b(13, 9, 14, 13, 8, 9, 15, 13, 16, 13, 14, 16),
    gsSPNTriangles_5b(8, 13, 17, 18, 13, 15, 5, 8, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};
