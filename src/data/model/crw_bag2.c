#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 crw_bag2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 crw_bag2_pal[] = {
#include "assets/crw_bag2_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 crw_bag21_tex_txt[0x400];
#else
u8 crw_bag21_tex_txt[] = {
#include "assets/crw_bag21_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx crw_bag2_v[0x1B0 / sizeof(Vtx)];
#else
Vtx crw_bag2_v[] = {
#include "assets/crw_bag2_v.inc"
};
#endif

Gfx crw_bag2_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, crw_bag2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, crw_bag21_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(crw_bag2_v, 27, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(25, 3, 4, 5, 6, 4, 3, 7, 8, 9),
    gsSPNTriangles_5b(7, 10, 11, 5, 4, 12, 13, 12, 6, 12, 4, 6),
    gsSPNTriangles_5b(11, 10, 14, 12, 15, 5, 16, 15, 17, 17, 14, 16),
    gsSPNTriangles_5b(12, 13, 11, 6, 18, 13, 16, 5, 15, 13, 18, 7),
    gsSPNTriangles_5b(11, 17, 15, 11, 15, 12, 14, 17, 11, 11, 13, 7),
    gsSPNTriangles_5b(19, 10, 7, 20, 16, 14, 5, 16, 21, 22, 23, 24),
    gsSPNTriangles_5b(5, 25, 3, 19, 26, 14, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
