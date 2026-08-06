#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx crw_cobra_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 crw_cobra_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 crw_cobra_pal[] = {
#include "assets/crw_cobra_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 crw_cobra_tex_txt[0x200];
#else
u8 crw_cobra_tex_txt[] = {
#include "assets/crw_cobra_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx crw_cobra_v[0x300 / sizeof(Vtx)];
#else
Vtx crw_cobra_v[] = {
#include "assets/crw_cobra_v.inc"
};
#endif

Gfx crw_cobra_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, crw_cobra_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, crw_cobra_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(crw_cobra_v, 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 3, 4, 5, 6, 7, 5),
    gsSPNTriangles_5b(7, 8, 5, 9, 10, 11, 12, 13, 14, 5, 8, 13),
    gsSPNTriangles_5b(5, 14, 3, 15, 16, 17, 18, 19, 15, 20, 1, 21),
    gsSPNTriangles_5b(22, 18, 23, 19, 18, 24, 0, 25, 26, 18, 22, 24),
    gsSPNTriangles_5b(5, 4, 27, 28, 23, 18, 11, 29, 30, 11, 30, 9),
    gsSPNTriangles_5b(29, 11, 17, 14, 5, 12, 12, 5, 13, 17, 11, 10),
    gsSPNTriangles_5b(5, 2, 20, 0, 26, 21, 26, 31, 20, 21, 1, 0),
    gsSPNTriangles_5b(28, 18, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&crw_cobra_v[32], 16, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 6, 10, 7, 9, 4, 7, 11, 1, 0),
    gsSPNTriangles_5b(0, 12, 13, 6, 14, 15, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
