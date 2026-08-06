#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_nikki_fan5_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_nikki_fan5_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_nikki_fan5_pal[] = {
#include "assets/int_ike_nikki_fan5_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_nikki_fan5face_tex[0x200];
#else
u8 int_ike_nikki_fan5face_tex[] = {
#include "assets/int_ike_nikki_fan5face_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_nikki_fan5side_tex[0x40];
#else
u8 int_ike_nikki_fan5side_tex[] = {
#include "assets/int_ike_nikki_fan5side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_nikki_fan5pen_tex[0x40];
#else
u8 int_ike_nikki_fan5pen_tex[] = {
#include "assets/int_ike_nikki_fan5pen_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_nikki_fan5_v[0x210 / sizeof(Vtx)];
#else
Vtx int_ike_nikki_fan5_v[] = {
#include "assets/int_ike_nikki_fan5_v.inc"
};
#endif

Gfx int_ike_nikki_fan5_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_nikki_fan5_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_nikki_fan5pen_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_nikki_fan5_v, 25, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 6, 1, 0, 6, 0, 7, 8, 2, 1),
    gsSPNTriangles_5b(8, 1, 6, 9, 3, 2, 9, 2, 8, 10, 4, 3),
    gsSPNTriangles_5b(10, 3, 9, 11, 5, 4, 11, 4, 10, 7, 0, 5),
    gsSPNTriangles_5b(7, 5, 11, 6, 12, 8, 10, 12, 11, 11, 12, 7),
    gsSPNTriangles_5b(10, 9, 12, 9, 8, 12, 6, 7, 12, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_nikki_fan5side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(6, 13, 14, 15, 13, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(17, 19, 20, 21, 22, 23, 21, 23, 24, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_nikki_fan5face_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_ike_nikki_fan5_v[25], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
