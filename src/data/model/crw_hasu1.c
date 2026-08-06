#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx crw_hasu1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 crw_hasu1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 crw_hasu1_pal[] = {
#include "assets/crw_hasu1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 crw_hasu1_tex_txt[0x200];
#else
u8 crw_hasu1_tex_txt[] = {
#include "assets/crw_hasu1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx crw_hasu1_v[0x570 / sizeof(Vtx)];
#else
Vtx crw_hasu1_v[] = {
#include "assets/crw_hasu1_v.inc"
};
#endif

Gfx crw_hasu1_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, crw_hasu1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, crw_hasu1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(crw_hasu1_v, 31, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 2, 4, 5, 0),
    gsSPNTriangles_5b(2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 6),
    gsSPNTriangles_5b(8, 10, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 15, 16, 14, 16, 17, 12),
    gsSPNTriangles_5b(14, 16, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 18, 19, 20, 21, 22, 20, 22, 23, 18),
    gsSPNTriangles_5b(20, 22, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 24, 25, 26, 27, 28, 29, 28, 30, 24),
    gsSPNTriangles_5b(29, 28, 24, 24, 26, 29, 29, 26, 27, 0, 0, 0),
    gsSPVertex(&crw_hasu1_v[31], 28, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 4, 6, 0),
    gsSPNTriangles_5b(5, 4, 0, 0, 2, 5, 5, 2, 3, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 7, 8, 9, 10, 11, 12, 11, 13, 7),
    gsSPNTriangles_5b(12, 11, 7, 7, 9, 12, 12, 9, 10, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 14, 15, 16, 17, 18, 19, 18, 20, 14),
    gsSPNTriangles_5b(19, 18, 14, 14, 16, 19, 19, 16, 17, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 21, 22, 23, 24, 25, 26, 25, 27, 21),
    gsSPNTriangles_5b(26, 25, 21, 21, 23, 26, 26, 23, 24, 0, 0, 0),
    gsSPVertex(&crw_hasu1_v[59], 28, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTrianglesInit_5b(3, 7, 8, 9, 7, 10, 8, 11, 12, 13),
    gsSPNTrianglesInit_5b(3, 14, 15, 16, 17, 18, 19, 14, 16, 20),
    gsSPNTrianglesInit_5b(3, 21, 22, 23, 21, 23, 24, 25, 26, 27),
    gsSPEndDisplayList(),
};
