#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx crw_rei2_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 crw_rei2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 crw_rei2_pal[] = {
#include "assets/crw_rei2_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 crw_rei21_tex_txt[0x200];
#else
u8 crw_rei21_tex_txt[] = {
#include "assets/crw_rei21_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx crw_rei2_v[0xDC0 / sizeof(Vtx)];
#else
Vtx crw_rei2_v[] = {
#include "assets/crw_rei2_v.inc"
};
#endif

Gfx crw_rei2_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, crw_rei2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, crw_rei21_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(crw_rei2_v, 30, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 0, 4, 1),
    gsSPNTrianglesInit_5b(3, 5, 6, 7, 5, 7, 8, 5, 9, 6),
    gsSPNTrianglesInit_5b(3, 10, 11, 12, 10, 12, 13, 10, 14, 11),
    gsSPNTrianglesInit_5b(3, 15, 16, 17, 15, 17, 18, 15, 19, 16),
    gsSPNTrianglesInit_5b(3, 20, 21, 22, 20, 22, 23, 20, 24, 21),
    gsSPNTrianglesInit_5b(3, 25, 26, 27, 25, 27, 28, 25, 29, 26),
    gsSPVertex(&crw_rei2_v[30], 30, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 0, 4, 1),
    gsSPNTrianglesInit_5b(3, 5, 6, 7, 5, 7, 8, 5, 9, 6),
    gsSPNTrianglesInit_5b(3, 10, 11, 12, 10, 12, 13, 10, 14, 11),
    gsSPNTrianglesInit_5b(3, 15, 16, 17, 15, 17, 18, 15, 19, 16),
    gsSPNTrianglesInit_5b(3, 20, 21, 22, 20, 22, 23, 20, 24, 21),
    gsSPNTrianglesInit_5b(3, 25, 26, 27, 25, 27, 28, 25, 29, 26),
    gsSPVertex(&crw_rei2_v[60], 30, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 0, 4, 1),
    gsSPNTrianglesInit_5b(3, 5, 6, 7, 5, 7, 8, 5, 9, 6),
    gsSPNTrianglesInit_5b(3, 10, 11, 12, 10, 12, 13, 10, 14, 11),
    gsSPNTrianglesInit_5b(3, 15, 16, 17, 15, 17, 18, 15, 19, 16),
    gsSPNTrianglesInit_5b(3, 20, 21, 22, 20, 22, 23, 20, 24, 21),
    gsSPNTrianglesInit_5b(3, 25, 26, 27, 25, 27, 28, 25, 29, 26),
    gsSPVertex(&crw_rei2_v[90], 30, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 0, 4, 1),
    gsSPNTrianglesInit_5b(3, 5, 6, 7, 5, 7, 8, 5, 9, 6),
    gsSPNTrianglesInit_5b(3, 10, 11, 12, 10, 12, 13, 10, 14, 11),
    gsSPNTrianglesInit_5b(3, 15, 16, 17, 15, 17, 18, 15, 19, 16),
    gsSPNTrianglesInit_5b(3, 20, 21, 22, 20, 22, 23, 20, 24, 21),
    gsSPNTrianglesInit_5b(3, 25, 26, 27, 25, 27, 28, 25, 29, 26),
    gsSPVertex(&crw_rei2_v[120], 30, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 0, 4, 1),
    gsSPNTrianglesInit_5b(3, 5, 6, 7, 5, 7, 8, 5, 9, 6),
    gsSPNTrianglesInit_5b(3, 10, 11, 12, 10, 12, 13, 10, 14, 11),
    gsSPNTrianglesInit_5b(3, 15, 16, 17, 15, 17, 18, 15, 19, 16),
    gsSPNTrianglesInit_5b(3, 20, 21, 22, 20, 22, 23, 20, 24, 21),
    gsSPNTrianglesInit_5b(3, 25, 26, 27, 25, 27, 28, 25, 29, 26),
    gsSPVertex(&crw_rei2_v[150], 30, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 0, 4, 1),
    gsSPNTrianglesInit_5b(3, 5, 6, 7, 5, 7, 8, 5, 9, 6),
    gsSPNTrianglesInit_5b(3, 10, 11, 12, 10, 12, 13, 10, 14, 11),
    gsSPNTrianglesInit_5b(3, 15, 16, 17, 15, 17, 18, 15, 19, 16),
    gsSPNTrianglesInit_5b(3, 20, 21, 22, 20, 22, 23, 20, 24, 21),
    gsSPNTrianglesInit_5b(3, 25, 26, 27, 25, 27, 28, 25, 29, 26),
    gsSPVertex(&crw_rei2_v[180], 30, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 0, 4, 1),
    gsSPNTrianglesInit_5b(3, 5, 6, 7, 5, 7, 8, 5, 9, 6),
    gsSPNTrianglesInit_5b(3, 10, 11, 12, 10, 12, 13, 10, 14, 11),
    gsSPNTrianglesInit_5b(3, 15, 16, 17, 15, 17, 18, 15, 19, 16),
    gsSPNTrianglesInit_5b(3, 20, 21, 22, 20, 22, 23, 20, 24, 21),
    gsSPNTrianglesInit_5b(3, 25, 26, 27, 25, 27, 28, 25, 29, 26),
    gsSPVertex(&crw_rei2_v[210], 10, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 0, 4, 1),
    gsSPNTrianglesInit_5b(3, 5, 6, 7, 5, 7, 8, 5, 9, 6),
    gsSPEndDisplayList(),
};
