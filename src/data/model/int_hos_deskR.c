#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_hos_deskR_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_hos_deskR_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_hos_deskR_pal[] = {
#include "assets/int_hos_deskR_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hos_deskR_tex_txt[0x800];
#else
u8 int_hos_deskR_tex_txt[] = {
#include "assets/int_hos_deskR_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_hos_deskR_v[0x610 / sizeof(Vtx)];
#else
Vtx int_hos_deskR_v[] = {
#include "assets/int_hos_deskR_v.inc"
};
#endif

Gfx int_hos_deskR_model_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hos_deskR_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, int_hos_deskR_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 178, 178, 178, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_hos_deskR_v, 24, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 4, 5, 6, 7, 3),
    gsSPNTriangles_5b(8, 9, 10, 8, 10, 0, 2, 11, 8, 8, 0, 2),
    gsSPNTriangles_5b(12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19),
    gsSPNTriangles_5b(20, 21, 22, 20, 22, 23, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_hos_deskR_v[24], 32, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 24, 25, 26, 27, 28, 29, 0, 0, 0),
    gsSPVertex(&int_hos_deskR_v[54], 7, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 3, 4, 5, 6, 4, 3, 0, 0, 0),
    gsSPVertex(&int_hos_deskR_v[61], 28, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 23, 24, 25, 26, 27, 0, 0, 0),
    gsSPVertex(&int_hos_deskR_v[89], 8, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
