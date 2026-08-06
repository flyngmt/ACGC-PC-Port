#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 act_f28_akikan_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 act_f28_akikan_pal[] = {
#include "assets/act_f28_akikan_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 act_f28_akikan_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 act_f28_akikan_tex[] = {
#include "assets/act_f28_akikan_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_f28_akikan_v[0x60 / sizeof(Vtx)];
#else
Vtx act_f28_akikan_v[] = {
#include "assets/act_f28_akikan_v.inc"
};
#endif

Gfx act_f28_akikanT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_f28_akikan_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, act_f28_akikan_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_f28_akikan_v, 6, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 1, 3, 2, 0, 4, 1),
    gsSPNTriangles_5b(4, 5, 1, 5, 3, 1, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
