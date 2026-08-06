#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_hos_turkey_sofa_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_hos_turkey_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_hos_turkey_pal[] = {
#include "assets/int_hos_turkey_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hos_turkey_sofa_se_txt[0x200];
#else
u8 int_hos_turkey_sofa_se_txt[] = {
#include "assets/int_hos_turkey_sofa_se_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hos_turkey_sofa_asi_txt[0x80];
#else
u8 int_hos_turkey_sofa_asi_txt[] = {
#include "assets/int_hos_turkey_sofa_asi_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hos_turkey_sofa_cov_txt[0x200];
#else
u8 int_hos_turkey_sofa_cov_txt[] = {
#include "assets/int_hos_turkey_sofa_cov_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_hos_turkey_sofa_yoko_txt[0x200];
#else
u8 int_hos_turkey_sofa_yoko_txt[] = {
#include "assets/int_hos_turkey_sofa_yoko_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_hos_turkey_sofa_v[0x590 / sizeof(Vtx)];
#else
Vtx int_hos_turkey_sofa_v[] = {
#include "assets/int_hos_turkey_sofa_v.inc"
};
#endif

Gfx int_hos_turkey_sofa_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_hos_turkey_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_hos_turkey_sofa_se_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_hos_turkey_sofa_v, 29, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 0, 2, 3, 4, 2, 1),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 9, 10, 11, 9, 11, 12),
    gsSPNTriangles_5b(13, 14, 15, 13, 15, 16, 13, 16, 17, 18, 19, 7),
    gsSPNTriangles_5b(18, 7, 6, 20, 21, 22, 20, 22, 23, 20, 23, 24),
    gsSPNTriangles_5b(3, 25, 26, 3, 26, 0, 8, 27, 28, 8, 28, 5),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 32, int_hos_turkey_sofa_asi_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_hos_turkey_sofa_v[29], 27, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_hos_turkey_sofa_cov_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsSPNTrianglesInit_5b(1, 24, 25, 26, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_hos_turkey_sofa_v[56], 7, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(2, 5, 4, 2, 4, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_hos_turkey_sofa_yoko_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_hos_turkey_sofa_v[63], 26, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 10, 11, 7, 12, 13, 7, 14, 15),
    gsSPNTriangles_5b(16, 17, 18, 16, 18, 19, 20, 21, 2, 22, 23, 2),
    gsSPNTriangles_5b(24, 25, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
