#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_hos_deskL_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_hos_deskL_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_hos_deskL_pal[] = {
#include "assets/int_hos_deskL_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hos_deskL_tex_txt[0x800];
#else
u8 int_hos_deskL_tex_txt[] = {
#include "assets/int_hos_deskL_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_hos_deskL_v[0x590 / sizeof(Vtx)];
#else
Vtx int_hos_deskL_v[] = {
#include "assets/int_hos_deskL_v.inc"
};
#endif

Gfx int_hos_deskL_model_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hos_deskL_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, int_hos_deskL_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 178, 178, 178, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_hos_deskL_v, 22, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 4, 5, 5, 6, 7),
    gsSPNTriangles_5b(2, 8, 9, 2, 9, 10, 10, 11, 0, 0, 2, 10),
    gsSPNTriangles_5b(12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19),
    gsSPNTriangles_5b(20, 14, 13, 20, 13, 21, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_hos_deskL_v[22], 30, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 1, 3, 4, 5, 6, 1),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 13, 14, 8, 15, 16, 17),
    gsSPNTriangles_5b(18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29),
    gsSPVertex(&int_hos_deskL_v[52], 29, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 1, 3, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(10, 4, 5, 6, 7, 8, 9, 5, 10, 11),
    gsSPNTriangles_5b(12, 13, 14, 15, 16, 13, 13, 17, 18, 19, 20, 21),
    gsSPNTriangles_5b(19, 21, 22, 23, 24, 25, 26, 27, 28, 0, 0, 0),
    gsSPVertex(&int_hos_deskL_v[81], 8, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
