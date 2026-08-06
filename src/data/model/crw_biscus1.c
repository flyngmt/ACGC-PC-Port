#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx crw_biscus1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 crw_biscus1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 crw_biscus1_pal[] = {
#include "assets/crw_biscus1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 crw_biscus2_tex_txt[0x100];
#else
u8 crw_biscus2_tex_txt[] = {
#include "assets/crw_biscus2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 crw_biscus4_tex_txt[0x80];
#else
u8 crw_biscus4_tex_txt[] = {
#include "assets/crw_biscus4_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 crw_biscus3_tex_txt[0x80];
#else
u8 crw_biscus3_tex_txt[] = {
#include "assets/crw_biscus3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 crw_biscus1_tex_txt[0x200];
#else
u8 crw_biscus1_tex_txt[] = {
#include "assets/crw_biscus1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx crw_biscus1_v[0x390 / sizeof(Vtx)];
#else
Vtx crw_biscus1_v[] = {
#include "assets/crw_biscus1_v.inc"
};
#endif

Gfx crw_biscus1_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, crw_biscus1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, crw_biscus2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 178, 178, 178, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(crw_biscus1_v, 27, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 3, 4, 5),
    gsSPNTriangles_5b(3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 6, 7, 8, 6, 8, 9, 9, 10, 11),
    gsSPNTriangles_5b(9, 11, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, crw_biscus4_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 15, 12, 14, 13, 16, 14),
    gsSPNTriangles_5b(16, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, crw_biscus3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 17, 18, 19, 20, 17, 19, 18, 21, 19),
    gsSPNTriangles_5b(21, 20, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 22, 23, 24, 25, 22, 24, 23, 26, 24),
    gsSPNTriangles_5b(26, 25, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, crw_biscus1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&crw_biscus1_v[27], 30, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 1, 3, 3, 1, 4),
    gsSPNTriangles_5b(3, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 6, 7, 8, 8, 7, 9, 9, 7, 10),
    gsSPNTriangles_5b(9, 11, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 14, 13, 15, 15, 13, 16),
    gsSPNTriangles_5b(15, 17, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 18, 19, 20, 20, 19, 21, 21, 19, 22),
    gsSPNTriangles_5b(21, 23, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 24, 25, 26, 26, 25, 27, 27, 25, 28),
    gsSPNTriangles_5b(27, 29, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
