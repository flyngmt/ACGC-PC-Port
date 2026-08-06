#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_makada01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_makada01_pal[] = {
#include "assets/int_ike_jny_makada01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_makada01_face2_tex[0x100];
#else
u8 int_ike_jny_makada01_face2_tex[] = {
#include "assets/int_ike_jny_makada01_face2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_makada01_face1_tex[0x400];
#else
u8 int_ike_jny_makada01_face1_tex[] = {
#include "assets/int_ike_jny_makada01_face1_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_jny_makada01_v[0x140 / sizeof(Vtx)];
#else
Vtx int_ike_jny_makada01_v[] = {
#include "assets/int_ike_jny_makada01_v.inc"
};
#endif

Gfx int_ike_jny_makada01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_makada01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_ike_jny_makada01_face1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_jny_makada01_v, 20, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 8, int_ike_jny_makada01_face2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 4, 5, 6, 5, 7, 6, 8, 9, 10),
    gsSPNTriangles_5b(8, 11, 9, 12, 13, 14, 12, 15, 13, 16, 17, 18),
    gsSPNTriangles_5b(17, 19, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
