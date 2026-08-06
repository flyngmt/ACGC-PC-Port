#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_tri_bed01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_tri_bed01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_tri_bed01_pal[] = {
#include "assets/int_nog_tri_bed01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_nog_tri_bed01_tex[0x800];
#else
u8 obj_nog_tri_bed01_tex[] = {
#include "assets/obj_nog_tri_bed01_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_tri_bed01_v[0x330 / sizeof(Vtx)];
#else
Vtx int_nog_tri_bed01_v[] = {
#include "assets/int_nog_tri_bed01_v.inc"
};
#endif

Gfx int_nog_tri_bed01T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_tri_bed01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_nog_tri_bed01_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_tri_bed01_v, 32, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 10, 3, 2),
    gsSPNTriangles_5b(10, 2, 11, 12, 13, 14, 12, 14, 15, 14, 5, 4),
    gsSPNTriangles_5b(14, 4, 15, 16, 17, 18, 16, 18, 19, 18, 1, 0),
    gsSPNTriangles_5b(18, 0, 19, 6, 20, 21, 6, 21, 7, 20, 22, 23),
    gsSPNTriangles_5b(20, 23, 21, 24, 12, 9, 24, 9, 25, 24, 13, 12),
    gsSPNTriangles_5b(9, 8, 25, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsSPVertex(&int_nog_tri_bed01_v[30], 21, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 4, 8, 5, 6, 9, 7, 5, 10, 6),
    gsSPNTriangles_5b(10, 11, 12, 10, 12, 6, 5, 11, 10, 13, 14, 15),
    gsSPNTriangles_5b(13, 15, 16, 17, 18, 19, 17, 19, 20, 0, 0, 0),
    gsSPEndDisplayList(),
};
