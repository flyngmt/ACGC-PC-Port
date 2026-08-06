#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_hos_flip_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_hos_flip_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_hos_flip_pal[] = {
#include "assets/int_hos_flip_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hos_flip_top_tex_txt[0x400];
#else
u8 int_hos_flip_top_tex_txt[] = {
#include "assets/int_hos_flip_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hos_flip_asi_tex_txt[0x200];
#else
u8 int_hos_flip_asi_tex_txt[] = {
#include "assets/int_hos_flip_asi_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hos_flip_side_tex_txt[0x200];
#else
u8 int_hos_flip_side_tex_txt[] = {
#include "assets/int_hos_flip_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_hos_flip_v[0x5E0 / sizeof(Vtx)];
#else
Vtx int_hos_flip_v[] = {
#include "assets/int_hos_flip_v.inc"
};
#endif

Gfx int_hos_flip_model_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hos_flip_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_hos_flip_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_hos_flip_v, 24, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_hos_flip_asi_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hos_flip_v[24], 23, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 6, 7, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 11, 12, 13, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 14, 15, 16, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 17, 18, 19, 20, 21, 22, 0, 0, 0),
    gsSPVertex(&int_hos_flip_v[47], 31, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 5, 6, 7, 4),
    gsSPNTriangles_5b(4, 8, 9, 10, 11, 12, 11, 13, 14, 15, 16, 11),
    gsSPNTriangles_5b(17, 18, 19, 19, 20, 21, 22, 23, 24, 18, 25, 20),
    gsSPNTriangles_5b(24, 17, 21, 26, 27, 1, 28, 29, 30, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_hos_flip_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_hos_flip_v[78], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
