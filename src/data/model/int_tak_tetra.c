#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_tetra_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_tetra_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_tetra_pal[] = {
#include "assets/int_tak_tetra_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_tetra_side_tex[0x200];
#else
u8 int_tak_tetra_side_tex[] = {
#include "assets/int_tak_tetra_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_tetra_top_tex[0x80];
#else
u8 int_tak_tetra_top_tex[] = {
#include "assets/int_tak_tetra_top_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_tetra_v[0x510 / sizeof(Vtx)];
#else
Vtx int_tak_tetra_v[] = {
#include "assets/int_tak_tetra_v.inc"
};
#endif

Gfx int_tak_tetra_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_tetra_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_tetra_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_tetra_v, 24, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 6, 7, 8, 6, 8, 9, 6, 9, 10),
    gsSPNTriangles_5b(6, 10, 11, 12, 13, 14, 12, 14, 15, 12, 15, 16),
    gsSPNTriangles_5b(12, 16, 17, 18, 19, 20, 18, 20, 21, 18, 21, 22),
    gsSPNTriangles_5b(18, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_tak_tetra_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_tetra_v[24], 32, 0),
    gsSPNTrianglesInit_5b(25, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 6, 4, 5, 6, 5, 7, 8, 6, 7),
    gsSPNTriangles_5b(8, 7, 9, 10, 8, 9, 10, 9, 11, 12, 10, 11),
    gsSPNTriangles_5b(13, 12, 11, 14, 15, 16, 14, 16, 17, 18, 14, 17),
    gsSPNTriangles_5b(18, 17, 19, 6, 18, 19, 6, 19, 20, 21, 6, 20),
    gsSPNTriangles_5b(21, 20, 22, 23, 21, 22, 24, 23, 25, 26, 24, 25),
    gsSPNTriangles_5b(27, 28, 29, 30, 27, 31, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_tak_tetra_v[56], 25, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 0, 2, 3, 2, 4),
    gsSPNTriangles_5b(5, 3, 4, 5, 4, 6, 7, 5, 6, 7, 6, 8),
    gsSPNTriangles_5b(9, 7, 8, 10, 9, 8, 11, 12, 13, 14, 11, 15),
    gsSPNTriangles_5b(14, 15, 16, 17, 14, 16, 17, 16, 18, 19, 17, 18),
    gsSPNTriangles_5b(19, 18, 20, 21, 19, 20, 21, 20, 22, 23, 21, 22),
    gsSPNTriangles_5b(24, 23, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
