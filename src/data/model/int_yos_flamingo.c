#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_yos_flamingo_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_yos_flamingo_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_yos_flamingo_pal[] = {
#include "assets/int_yos_flamingo_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_flamingo_kao_tex_txt[0x400];
#else
u8 int_yos_flamingo_kao_tex_txt[] = {
#include "assets/int_yos_flamingo_kao_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_flamingo_dou_tex_txt[0x400];
#else
u8 int_yos_flamingo_dou_tex_txt[] = {
#include "assets/int_yos_flamingo_dou_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_yos_flamingo_v[0x450 / sizeof(Vtx)];
#else
Vtx int_yos_flamingo_v[] = {
#include "assets/int_yos_flamingo_v.inc"
};
#endif

Gfx int_yos_flamingo_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yos_flamingo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_yos_flamingo_kao_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_yos_flamingo_v, 28, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 0, 7),
    gsSPNTriangles_5b(6, 7, 8, 7, 9, 10, 7, 10, 8, 11, 12, 13),
    gsSPNTriangles_5b(5, 14, 3, 15, 12, 11, 11, 5, 15, 4, 15, 5),
    gsSPNTriangles_5b(16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27),
    gsSPVertex(&int_yos_flamingo_v[28], 30, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 1, 0),
    gsSPNTriangles_5b(5, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 10, 11, 8, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 15, 13, 12, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsSPNTrianglesInit_5b(1, 24, 25, 26, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(1, 27, 28, 29, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_yos_flamingo_dou_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_yos_flamingo_v[58], 11, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(5, 4, 7, 7, 4, 8, 7, 6, 5, 9, 8, 4),
    gsSPNTriangles_5b(9, 3, 6, 10, 1, 8, 2, 1, 10, 0, 7, 8),
    gsSPNTriangles_5b(2, 7, 0, 2, 6, 7, 10, 9, 2, 4, 3, 9),
    gsSPNTriangles_5b(6, 2, 9, 8, 1, 0, 8, 9, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};
