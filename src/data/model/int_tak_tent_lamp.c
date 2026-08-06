#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_tent_lamp_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_tent_lamp_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_tent_lamp_pal[] = {
#include "assets/int_tak_tent_lamp_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_tent_lamp_tex[0x200];
#else
u8 int_tak_tent_lamp_tex[] = {
#include "assets/int_tak_tent_lamp_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_tent_lamp_v[0x460 / sizeof(Vtx)];
#else
Vtx int_tak_tent_lamp_v[] = {
#include "assets/int_tak_tent_lamp_v.inc"
};
#endif

Gfx obj_tent_lamp_offT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_tent_lamp_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_tak_tent_lamp_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_tent_lamp_v, 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 2, 3, 4, 5, 6, 0),
    gsSPNTriangles_5b(7, 8, 5, 4, 9, 10, 10, 11, 12, 13, 14, 15),
    gsSPNTriangles_5b(16, 17, 13, 18, 19, 20, 20, 21, 22, 23, 24, 16),
    gsSPNTriangles_5b(22, 25, 23, 26, 27, 28, 26, 28, 29, 30, 26, 29),
    gsSPNTriangles_5b(30, 29, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_tak_tent_lamp_v[32], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 6, 4, 5, 6, 5, 7, 8, 9, 6),
    gsSPNTriangles_5b(8, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_tak_tent_lamp_v[42], 28, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 6, 8, 9, 6, 9, 7, 8, 10, 11),
    gsSPNTriangles_5b(8, 11, 9, 10, 12, 13, 10, 13, 11, 12, 14, 15),
    gsSPNTriangles_5b(12, 15, 13, 14, 16, 17, 14, 17, 15, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 18, 21, 22, 21, 23, 24, 22, 23),
    gsSPNTriangles_5b(24, 23, 25, 26, 24, 25, 26, 25, 27, 0, 0, 0),
    gsSPEndDisplayList(),
};
