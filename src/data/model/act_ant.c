#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 act_ant_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 act_ant_tex[] = {
#include "assets/act_ant_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_ant_v[0xB0 / sizeof(Vtx)];
#else
Vtx act_ant_v[] = {
#include "assets/act_ant_v.inc"
};
#endif

Gfx act_antT_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 1, 0, TEXEL0, TEXEL1, 0, 0, 0, COMBINED, COMBINED, 0, PRIMITIVE, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, act_ant_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, act_ant_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                         G_SHADING_SMOOTH),
    gsSPVertex(act_ant_v, 11, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(4, 5, 3, 4, 6, 5, 0, 2, 7, 2, 8, 7),
    gsSPNTriangles_5b(8, 9, 7, 8, 5, 9, 5, 10, 9, 2, 3, 5),
    gsSPNTriangles_5b(2, 5, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
