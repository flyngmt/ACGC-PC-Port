#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_axe_1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_axe_1_pal[] = {
#include "assets/tol_axe_1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_axe_1_tuka1_tex_txt[0x200];
#else
u8 tol_axe_1_tuka1_tex_txt[] = {
#include "assets/tol_axe_1_tuka1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_axe_1_edge2_tex_txt[0x100];
#else
u8 tol_axe_1_edge2_tex_txt[] = {
#include "assets/tol_axe_1_edge2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_axe_1_edge1_tex_txt[0x100];
#else
u8 tol_axe_1_edge1_tex_txt[] = {
#include "assets/tol_axe_1_edge1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_axe_1_v[0x220 / sizeof(Vtx)];
#else
Vtx tol_axe_1_v[] = {
#include "assets/tol_axe_1_v.inc"
};
#endif

Gfx tol_axe_1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_axe_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_axe_1_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_axe_1_v, 22, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 2),
    gsSPNTriangles_5b(4, 2, 1, 4, 6, 7, 4, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(11, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, tol_axe_1_edge2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(10, 14, 15, 16, 14, 16, 17, 18, 19, 14),
    gsSPNTriangles_5b(18, 14, 17, 20, 15, 14, 20, 14, 19, 21, 18, 17),
    gsSPNTriangles_5b(21, 17, 16, 15, 20, 21, 15, 21, 16, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, tol_axe_1_edge1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&tol_axe_1_v[22], 12, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 1, 0, 4, 5, 6),
    gsSPNTriangles_5b(7, 5, 4, 8, 5, 7, 9, 1, 3, 10, 9, 3),
    gsSPNTriangles_5b(3, 4, 10, 0, 2, 11, 7, 0, 11, 7, 11, 8),
    gsSPNTriangles_5b(6, 10, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_axe_1_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_axe_1_b_pal[] = {
#include "assets/tol_axe_1_b_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_axe_1_b_tuka1_tex_txt[0x200];
#else
u8 tol_axe_1_b_tuka1_tex_txt[] = {
#include "assets/tol_axe_1_b_tuka1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_axe_1_b_edge2_tex_txt[0x100];
#else
u8 tol_axe_1_b_edge2_tex_txt[] = {
#include "assets/tol_axe_1_b_edge2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_axe_1_b_edge1_tex_txt[0x100];
#else
u8 tol_axe_1_b_edge1_tex_txt[] = {
#include "assets/tol_axe_1_b_edge1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_axe_1_b_v[0x220 / sizeof(Vtx)];
#else
Vtx tol_axe_1_b_v[] = {
#include "assets/tol_axe_1_b_v.inc"
};
#endif

Gfx tol_axe_1_b_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_axe_1_b_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_axe_1_b_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_axe_1_b_v, 22, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 2),
    gsSPNTriangles_5b(4, 2, 1, 4, 6, 7, 4, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(11, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, tol_axe_1_b_edge2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(10, 14, 15, 16, 14, 16, 17, 18, 19, 14),
    gsSPNTriangles_5b(18, 14, 17, 20, 15, 14, 20, 14, 19, 21, 18, 17),
    gsSPNTriangles_5b(21, 17, 16, 15, 20, 21, 15, 21, 16, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, tol_axe_1_b_edge1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&tol_axe_1_b_v[22], 12, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 1, 0, 4, 5, 6),
    gsSPNTriangles_5b(7, 5, 4, 8, 5, 7, 9, 1, 3, 10, 9, 3),
    gsSPNTriangles_5b(3, 4, 10, 0, 2, 11, 7, 0, 11, 7, 11, 8),
    gsSPNTriangles_5b(6, 10, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_axe_1_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_axe_1_c_pal[] = {
#include "assets/tol_axe_1_c_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_axe_1_c_tuka1_tex_txt[0x200];
#else
u8 tol_axe_1_c_tuka1_tex_txt[] = {
#include "assets/tol_axe_1_c_tuka1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_axe_1_c_edge2_tex_txt[0x100];
#else
u8 tol_axe_1_c_edge2_tex_txt[] = {
#include "assets/tol_axe_1_c_edge2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_axe_1_c_edge1_tex_txt[0x200];
#else
u8 tol_axe_1_c_edge1_tex_txt[] = {
#include "assets/tol_axe_1_c_edge1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_axe_1_c_v[0x220 / sizeof(Vtx)];
#else
Vtx tol_axe_1_c_v[] = {
#include "assets/tol_axe_1_c_v.inc"
};
#endif

Gfx tol_axe_1_c_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_axe_1_c_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_axe_1_c_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_axe_1_c_v, 22, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 2),
    gsSPNTriangles_5b(4, 2, 1, 4, 6, 7, 4, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(11, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, tol_axe_1_c_edge2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(10, 14, 15, 16, 14, 16, 17, 18, 19, 14),
    gsSPNTriangles_5b(18, 14, 17, 20, 15, 14, 20, 14, 19, 21, 18, 17),
    gsSPNTriangles_5b(21, 17, 16, 15, 20, 21, 15, 21, 16, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_axe_1_c_edge1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tol_axe_1_c_v[22], 12, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 1, 0, 4, 5, 6),
    gsSPNTriangles_5b(7, 5, 4, 8, 5, 7, 9, 1, 3, 10, 9, 3),
    gsSPNTriangles_5b(3, 4, 10, 0, 2, 11, 7, 0, 11, 7, 11, 8),
    gsSPNTriangles_5b(6, 10, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_axe_2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_axe_2_pal[] = {
#include "assets/tol_axe_2_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_axe_2_tuka1_tex_txt[0x200];
#else
u8 tol_axe_2_tuka1_tex_txt[] = {
#include "assets/tol_axe_2_tuka1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_axe_2_edge2_tex_txt[0x100];
#else
u8 tol_axe_2_edge2_tex_txt[] = {
#include "assets/tol_axe_2_edge2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_axe_2_edge1_tex_txt[0x100];
#else
u8 tol_axe_2_edge1_tex_txt[] = {
#include "assets/tol_axe_2_edge1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_axe_2_v[0x220 / sizeof(Vtx)];
#else
Vtx tol_axe_2_v[] = {
#include "assets/tol_axe_2_v.inc"
};
#endif

Gfx tol_axe_2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_axe_2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_axe_2_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_axe_2_v, 22, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 2),
    gsSPNTriangles_5b(4, 2, 1, 4, 6, 7, 4, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(11, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, tol_axe_2_edge2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(10, 14, 15, 16, 14, 16, 17, 18, 19, 14),
    gsSPNTriangles_5b(18, 14, 17, 20, 15, 14, 20, 14, 19, 21, 18, 17),
    gsSPNTriangles_5b(21, 17, 16, 15, 20, 21, 15, 21, 16, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, tol_axe_2_edge1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&tol_axe_2_v[22], 12, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 1, 0, 4, 5, 6),
    gsSPNTriangles_5b(7, 5, 4, 8, 5, 7, 9, 1, 3, 10, 9, 3),
    gsSPNTriangles_5b(3, 4, 10, 0, 2, 11, 7, 0, 11, 7, 11, 8),
    gsSPNTriangles_5b(6, 10, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 act_m_net1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 act_m_net1_pal[] = {
#include "assets/act_m_net1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_net_1_tuka1_tex_txt[0x200];
#else
u8 tol_net_1_tuka1_tex_txt[] = {
#include "assets/tol_net_1_tuka1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_net_1_main1_tex_txt[0x300];
#else
u8 tol_net_1_main1_tex_txt[] = {
#include "assets/tol_net_1_main1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_net_1_hole1_tex_txt[0x100];
#else
u8 tol_net_1_hole1_tex_txt[] = {
#include "assets/tol_net_1_hole1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_net_1_v[0x4F0 / sizeof(Vtx)];
#else
Vtx tol_net_1_v[] = {
#include "assets/tol_net_1_v.inc"
};
#endif

Gfx main_net_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_net_1_v[17], 8, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_m_net1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, tol_net_1_main1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 188),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_net_1_v[25], 18, 8),
    gsSPNTrianglesInit_5b(13, 5, 8, 9, 4, 10, 11, 7, 3, 12),
    gsSPNTriangles_5b(7, 13, 14, 6, 15, 16, 0, 4, 17, 7, 1, 1),
    gsSPNTriangles_5b(0, 18, 19, 3, 20, 21, 3, 5, 22, 5, 6, 23),
    gsSPNTriangles_5b(6, 2, 24, 4, 7, 25, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx main2_net_model[] = {
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_net_1_v, 7, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_m_net1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, tol_net_1_main1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 188),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_net_1_v[7], 10, 7),
    gsSPNTrianglesInit_5b(8, 3, 5, 7, 0, 3, 8, 4, 2, 9),
    gsSPNTriangles_5b(3, 10, 11, 2, 6, 12, 5, 4, 13, 6, 1, 14),
    gsSPNTriangles_5b(2, 15, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx e_net_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_m_net1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_net_1_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_net_1_v[43], 29, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 2, 3, 2, 1, 4),
    gsSPNTriangles_5b(2, 4, 5, 0, 3, 6, 0, 6, 7, 8, 9, 10),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, tol_net_1_main1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 188),
    gsSPNTrianglesInit_5b(13, 11, 12, 13, 12, 14, 13, 13, 15, 16),
    gsSPNTriangles_5b(13, 17, 15, 16, 15, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(23, 12, 11, 23, 11, 24, 25, 19, 18, 25, 18, 26),
    gsSPNTriangles_5b(26, 27, 28, 26, 28, 25, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_net_1_hole1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&tol_net_1_v[72], 7, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 0, 2, 1, 4, 2),
    gsSPNTriangles_5b(5, 3, 2, 6, 5, 2, 4, 6, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_net_1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 100, 0, 4000 } },
    { e_net_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 100, 0, 0 } },
    { main_net_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 100, 0, 0 } },
    { main2_net_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1900, 0, 0 } },
};

cKF_Skeleton_R_c cKF_bs_r_tol_net_1 = { ARRAY_COUNT(cKF_je_r_tol_net_1_tbl), 3, cKF_je_r_tol_net_1_tbl };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_net_2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_net_2_pal[] = {
#include "assets/tol_net_2_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_net_2_main1_tex_txt[0x300];
#else
u8 tol_net_2_main1_tex_txt[] = {
#include "assets/tol_net_2_main1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_net_2_tuka1_tex_txt[0x200];
#else
u8 tol_net_2_tuka1_tex_txt[] = {
#include "assets/tol_net_2_tuka1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_net_2_hole1_tex_txt[0x100];
#else
u8 tol_net_2_hole1_tex_txt[] = {
#include "assets/tol_net_2_hole1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_net_2_v[0x500 / sizeof(Vtx)];
#else
Vtx tol_net_2_v[] = {
#include "assets/tol_net_2_v.inc"
};
#endif

Gfx main_netB_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_net_2_v[17], 9, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_net_2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, tol_net_2_main1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 188),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_net_2_v[26], 18, 9),
    gsSPNTrianglesInit_5b(13, 5, 9, 10, 4, 11, 12, 0, 3, 13),
    gsSPNTriangles_5b(0, 14, 15, 6, 16, 17, 1, 4, 18, 8, 7, 7),
    gsSPNTriangles_5b(1, 19, 20, 3, 21, 22, 3, 5, 23, 5, 6, 24),
    gsSPNTriangles_5b(6, 2, 25, 4, 0, 26, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx main2_netB_model[] = {
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_net_2_v, 7, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_net_2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, tol_net_2_main1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 188),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_net_2_v[7], 10, 7),
    gsSPNTrianglesInit_5b(8, 3, 5, 7, 0, 3, 8, 4, 2, 9),
    gsSPNTriangles_5b(3, 10, 11, 2, 6, 12, 5, 4, 13, 6, 1, 14),
    gsSPNTriangles_5b(2, 15, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx e_netB_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_net_2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_net_2_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_net_2_v[44], 29, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 2, 3, 2, 1, 4),
    gsSPNTriangles_5b(2, 4, 5, 0, 3, 6, 0, 6, 7, 8, 9, 10),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, tol_net_2_main1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 188),
    gsSPNTrianglesInit_5b(13, 11, 12, 13, 12, 14, 13, 13, 15, 16),
    gsSPNTriangles_5b(13, 17, 15, 16, 15, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(23, 12, 11, 23, 11, 24, 25, 19, 18, 25, 18, 26),
    gsSPNTriangles_5b(26, 27, 28, 26, 28, 25, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_net_2_hole1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&tol_net_2_v[73], 7, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 0, 2, 1, 4, 2),
    gsSPNTriangles_5b(5, 3, 2, 6, 5, 2, 4, 6, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_net_2_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 100, 0, 4000 } },
                                           { e_netB_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 100, 0, 0 } },
                                           { main_netB_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 100, 0, 0 } },
                                           { main2_netB_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1900, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_tol_net_2 = { ARRAY_COUNT(cKF_je_r_tol_net_2_tbl), 3, cKF_je_r_tol_net_2_tbl };

u8 cKF_ckcb_r_tol_net_1_get_m1_tbl[] = { 0, 0, 7, 0, 7, 7 };

s16 cKF_kn_tol_net_1_get_m1_tbl[] = { 2, 2, 2, 3, 5, 12, 2, 5, 9 };

s16 cKF_c_tol_net_1_get_m1_tbl[] = { 0, 0, 0, 0, 0, 0, -450, 900, 450, 0, 0, 0 };

s16 cKF_ds_tol_net_1_get_m1_tbl[] = {
    1,  0,    0,    52, 0,    0,     1,  0,    0, 52, 0,    0,     1,  900,  0,    52, 900,  0,   1,  0,    0,
    32, -200, 0,    52, -200, 0,     1,  250,  0, 17, 250,  0,     30, 0,    -281, 46, 350,  0,   52, 300,  0,
    1,  -850, 0,    5,  -800, 0,     9,  -850, 0, 13, -800, 0,     17, -850, -605, 22, -880, 476, 25, -660, 2338,
    30, -500, 0,    35, -660, -2258, 40, -910, 0, 46, -750, 0,     52, -850, 0,    1,  0,    0,   52, 0,    0,
    1,  0,    0,    17, 0,    0,     42, 0,    0, 48, 100,  0,     52, -100, 0,    1,  -350, 0,   17, -350, 0,
    24, -290, 1235, 29, 150,  1869,  34, 250,  0, 36, 100,  -3725, 42, -600, 0,    48, 200,  0,   52, -100, 0
};

cKF_Animation_R_c cKF_ba_r_tol_net_1_get_m1 = { cKF_ckcb_r_tol_net_1_get_m1_tbl,
                                                cKF_ds_tol_net_1_get_m1_tbl,
                                                cKF_kn_tol_net_1_get_m1_tbl,
                                                cKF_c_tol_net_1_get_m1_tbl,
                                                -1,
                                                52 };

u8 cKF_ckcb_r_tol_net_1_net_swing1_tbl[] = { 0, 0, 7, 0, 7, 7 };

s16 cKF_kn_tol_net_1_net_swing1_tbl[] = { 2, 2, 2, 2, 2, 4, 2, 2, 4 };

s16 cKF_c_tol_net_1_net_swing1_tbl[] = { 0, 0, 0, 0, 0, 0, 1350, 900, -1350, 0, 0, 0 };

s16 cKF_ds_tol_net_1_net_swing1_tbl[] = { 1,    0, 0, 10, 0,  0,  1, 0,    0, 10, 0,  0,  1,  900,  0, 10, 900,
                                          0,    1, 0, 0,  10, 0,  0, 1,    0, 0,  10, 0,  0,  1,    0, 0,  5,
                                          -100, 0, 9, 0,  0,  10, 0, 0,    1, 0,  0,  10, 0,  0,    1, 0,  0,
                                          10,   0, 0, 1,  0,  0,  5, -350, 0, 7,  0,  0,  10, -150, 0 };

cKF_Animation_R_c cKF_ba_r_tol_net_1_net_swing1 = { cKF_ckcb_r_tol_net_1_net_swing1_tbl,
                                                    cKF_ds_tol_net_1_net_swing1_tbl,
                                                    cKF_kn_tol_net_1_net_swing1_tbl,
                                                    cKF_c_tol_net_1_net_swing1_tbl,
                                                    -1,
                                                    10 };

u8 cKF_ckcb_r_tol_net_1_kamae_main_m1_tbl[] = { 0, 0, 7, 0, 7, 7 };

s16 cKF_kn_tol_net_1_kamae_main_m1_tbl[] = { 2, 2, 2, 2, 5, 3, 2, 6, 4 };

s16 cKF_c_tol_net_1_kamae_main_m1_tbl[] = { 0, 0, 0, 0, 0, 0, 1350, 900, -1350, 0, 0, 0 };

s16 cKF_ds_tol_net_1_kamae_main_m1_tbl[] = { 1,   0,   0,   17,  0,    0,  1,   0,  0,  17,   0,   0,   1,   900,
                                             0,   17,  900, 0,   1,    0,  0,   17, 0,  0,    1,   0,   449, 5,
                                             25,  0,   9,   0,   -444, 13, -25, 0,  17, 0,    449, 1,   25,  0,
                                             9,   -25, 0,   17,  25,   0,  1,   0,  0,  17,   0,   0,   1,   -19,
                                             188, 3,   0,   373, 7,    25, 0,   11, 0,  -381, 15,  -25, 0,   17,
                                             -19, 188, 1,   18,  223,  3,  25,  0,  11, -25,  0,   17,  18,  223 };

cKF_Animation_R_c cKF_ba_r_tol_net_1_kamae_main_m1 = { cKF_ckcb_r_tol_net_1_kamae_main_m1_tbl,
                                                       cKF_ds_tol_net_1_kamae_main_m1_tbl,
                                                       cKF_kn_tol_net_1_kamae_main_m1_tbl,
                                                       cKF_c_tol_net_1_kamae_main_m1_tbl,
                                                       -1,
                                                       17 };

u8 cKF_ckcb_r_tol_net_1_kokeru_getup_n1_tbl[] = { 0, 0, 0, 0, 3, 7 };

s16 cKF_kn_tol_net_1_kokeru_getup_n1_tbl[] = { 8, 13, 5, 7, 12 };

s16 cKF_c_tol_net_1_kokeru_getup_n1_tbl[] = { 0, 0, 0, 0, 0, 0, 1350, 900, -1350, 0, 0, 900, 0, 0, 0, 0 };

s16 cKF_ds_tol_net_1_kokeru_getup_n1_tbl[] = {
    1,    -450,  22,   5,    -399,  1181, 9,    -135,  2245, 12,   61,   1415,  15,   145,  491,   26,    70,
    -599, 29,    18,   -359, 32,    0,    -58,  1,     450,  -51,  5,    418,   -529, 12,   126,   -2126, 14,
    -40,  -2924, 19,   -555, -2237, 20,   -618, -1423, 22,   -662, -280, 26,    -610, 1447, 27,    -550,  2447,
    28,   -446,  3685, 30,   -159,  3880, 31,   -46,   2383, 32,   0,    1369,  1,    -100, 59,    4,     -84,
    278,  12,    -2,   111,  16,    0,    0,    32,    0,    0,    1,    700,   -649, 2,    678,   -1222, 12,
    -378, -1222, 15,   -365, 956,   23,   -9,   523,   25,   0,    0,    32,    0,    0,    1,     0,     4066,
    5,    510,   3182, 8,    733,   999,  10,   744,   -347, 16,   448,  -2708, 23,   -255, -1738, 24,    -300,
    -773, 25,    -307, 417,  26,    -272, 1604, 28,    -122, 2022, 31,   -6,    412,  32,   0,     195
};

cKF_Animation_R_c cKF_ba_r_tol_net_1_kokeru_getup_n1 = { cKF_ckcb_r_tol_net_1_kokeru_getup_n1_tbl,
                                                         cKF_ds_tol_net_1_kokeru_getup_n1_tbl,
                                                         cKF_kn_tol_net_1_kokeru_getup_n1_tbl,
                                                         cKF_c_tol_net_1_kokeru_getup_n1_tbl,
                                                         -1,
                                                         32 };

u8 cKF_ckcb_r_tol_net_1_kokeru_n1_tbl[] = { 0, 0, 7, 0, 7, 7 };

s16 cKF_kn_tol_net_1_kokeru_n1_tbl[] = { 2, 2, 2, 2, 5, 5, 4, 6, 6 };

s16 cKF_c_tol_net_1_kokeru_n1_tbl[] = { 0, 0, 0, 0, 0, 0, 1350, 900, -1350, 0, 0, 0 };

s16 cKF_ds_tol_net_1_kokeru_n1_tbl[] = { 1,  0,    0,     31, 0,    0,     1,  0,    0,    31, 0,   0, 1,  900,  0,
                                         31, 900,  0,     1,  0,    0,     31, 0,    0,    1,  0,   0, 7,  0,    0,
                                         10, 0,    -1210, 17, -450, -1143, 31, -600, 0,    1,  0,   0, 7,  -550, 0,
                                         10, 0,    4914,  17, 450,  646,   31, 600,  0,    1,  0,   0, 10, 0,    0,
                                         17, -100, -410,  31, -200, 0,     1,  0,    0,    5,  250, 0, 8,  50,   -1488,
                                         10, 0,    0,     17, 700,  1073,  31, 900,  0,    1,  0,   0, 5,  500,  0,
                                         8,  -290, -3843, 11, -450, 0,     17, 0,    2439, 31, 390, 0 };

cKF_Animation_R_c cKF_ba_r_tol_net_1_kokeru_n1 = { cKF_ckcb_r_tol_net_1_kokeru_n1_tbl,
                                                   cKF_ds_tol_net_1_kokeru_n1_tbl,
                                                   cKF_kn_tol_net_1_kokeru_n1_tbl,
                                                   cKF_c_tol_net_1_kokeru_n1_tbl,
                                                   -1,
                                                   31 };

u8 cKF_ckcb_r_tol_net_1_swing_wait1_tbl[] = { 0, 0, 7, 0, 7, 7 };

s16 cKF_kn_tol_net_1_swing_wait1_tbl[] = { 2, 2, 2, 2, 2, 5, 2, 2, 6 };

s16 cKF_c_tol_net_1_swing_wait1_tbl[] = { 0, 0, 0, 0, 0, 0, 1350, 900, -1350, 0, 0, 0 };

s16 cKF_ds_tol_net_1_swing_wait1_tbl[] = { 1,    0,    0,     21,  0,    0,   1,     0,     0,    21,   0,  0,    1,
                                           900,  0,    21,    900, 0,    1,   0,     0,     21,   0,    0,  1,    0,
                                           0,    21,   0,     0,   1,    0,   2998,  5,     150,  -769, 10, -300, -3985,
                                           15,   -760, -1215, 21,  -800, 0,   1,     0,     0,    21,   0,  0,    1,
                                           0,    0,    21,    0,   0,    1,   0,     -6054, 3,    -200, 0,  5,    0,
                                           6067, 10,   700,   0,   18,   -50, -1513, 21,    -100, 0 };

cKF_Animation_R_c cKF_ba_r_tol_net_1_swing_wait1 = { cKF_ckcb_r_tol_net_1_swing_wait1_tbl,
                                                     cKF_ds_tol_net_1_swing_wait1_tbl,
                                                     cKF_kn_tol_net_1_swing_wait1_tbl,
                                                     cKF_c_tol_net_1_swing_wait1_tbl,
                                                     -1,
                                                     21 };

u8 cKF_ckcb_r_tol_net_1_yatta_m1_tbl[] = { 0, 0, 7, 0, 7, 7 };

s16 cKF_kn_tol_net_1_yatta_m1_tbl[] = { 2, 2, 2, 2, 11, 11, 2, 10, 10 };

s16 cKF_c_tol_net_1_yatta_m1_tbl[] = { 0, 0, 0, 0, 0, 0, 1350, 900, -1350, 0, 0, 0 };

s16 cKF_ds_tol_net_1_yatta_m1_tbl[] = {
    1,  0,    0,     53, 0,    0,     1,  0,    0,    53, 0,    0,     1,  900,  0,   53, 900,  0,    1,  -200, 0,
    53, -200, 0,     1,  300,  0,     6,  150,  -732, 11, 150,  0,     16, 150,  0,   22, 150,  0,    28, 105,  -226,
    34, 75,   -147,  37, 0,    -1467, 40, -200, -966, 48, 200,  3058,  53, 400,  0,   1,  -850, 0,    6,  -250, 0,
    11, -250, 0,     16, -300, -975,  22, -750, -730, 28, -800, 0,     34, -800, 0,   37, -650, 3435, 40, -250, 757,
    44, -300, -1471, 53, -850, 0,     1,  0,    0,    53, 0,    0,     1,  -100, 0,   6,  0,    0,    11, -100, -1439,
    16, -350, 0,     22, -100, 1261,  34, 50,   0,    37, -25,  -1906, 44, -150, 494, 48, 0,    0,    53, -200, 0,
    1,  -100, 0,     11, -100, 993,   16, 200,  1288, 22, 250,  -753,  28, -100, 0,   34, -25,  0,    40, -350, 0,
    44, 0,    0,     48, -200, -2347, 53, -550, 0
};

cKF_Animation_R_c cKF_ba_r_tol_net_1_yatta_m1 = { cKF_ckcb_r_tol_net_1_yatta_m1_tbl,
                                                  cKF_ds_tol_net_1_yatta_m1_tbl,
                                                  cKF_kn_tol_net_1_yatta_m1_tbl,
                                                  cKF_c_tol_net_1_yatta_m1_tbl,
                                                  -1,
                                                  53 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_sao_1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_sao_1_pal[] = {
#include "assets/player_tool/tol_sao_1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_sao_1_main1_tex_txt[0x200];
#else
u8 tol_sao_1_main1_tex_txt[] = {
#include "assets/tol_sao_1_main1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_sao_1_v[0x3A0 / sizeof(Vtx)];
#else
Vtx tol_sao_1_v[] = {
#include "assets/tol_sao_1_v.inc"
};
#endif

Gfx main1_sao_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_sao_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_sao_1_main1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_sao_1_v[52], 6, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 2, 1, 3, 2, 3, 4),
    gsSPNTriangles_5b(0, 2, 4, 0, 4, 5, 1, 0, 5, 1, 5, 3),
    gsSPEndDisplayList(),
};

Gfx main2_sao_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_sao_1_v[34], 3, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_sao_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_sao_1_main1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tol_sao_1_v[37], 15, 3),
    gsSPNTrianglesInit_5b(6, 2, 0, 3, 2, 4, 5, 0, 1, 6),
    gsSPNTriangles_5b(0, 7, 8, 1, 2, 9, 1, 10, 11, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 12, 13, 14, 12, 14, 15, 13, 16, 17),
    gsSPNTriangles_5b(13, 17, 14, 16, 12, 15, 16, 15, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx main3_sao_model[] = {
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_sao_1_v[16], 3, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_sao_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_sao_1_main1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tol_sao_1_v[19], 15, 3),
    gsSPNTrianglesInit_5b(6, 2, 0, 3, 2, 4, 5, 1, 2, 6),
    gsSPNTriangles_5b(1, 7, 8, 0, 1, 9, 0, 10, 11, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 12, 13, 14, 12, 14, 15, 16, 12, 15),
    gsSPNTriangles_5b(16, 15, 17, 13, 16, 17, 13, 17, 14, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx main4_sao_model[] = {
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_sao_1_v, 3, 0),
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_sao_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_sao_1_main1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tol_sao_1_v[3], 13, 3),
    gsSPNTrianglesInit_5b(6, 2, 0, 3, 2, 4, 5, 1, 2, 6),
    gsSPNTriangles_5b(1, 7, 8, 0, 1, 9, 0, 10, 11, 0, 0, 0),
    gsSPNTrianglesInit_5b(3, 12, 13, 14, 13, 15, 14, 15, 12, 14),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_sao_1_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { main1_sao_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { main2_sao_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1500, 0, 0 } },
                                           { main3_sao_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1850, 0, 0 } },
                                           { main4_sao_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1600, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_tol_sao_1 = { ARRAY_COUNT(cKF_je_r_tol_sao_1_tbl), 4, cKF_je_r_tol_sao_1_tbl };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_sao_2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_sao_2_pal[] = {
#include "assets/player_tool/tol_sao_2_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_sao_2_main1_tex_txt[0x200];
#else
u8 tol_sao_2_main1_tex_txt[] = {
#include "assets/tol_sao_2_main1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_sao_2_v[0x3A0 / sizeof(Vtx)];
#else
Vtx tol_sao_2_v[] = {
#include "assets/tol_sao_2_v.inc"
};
#endif

Gfx main1_saoB_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_sao_2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_sao_2_main1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_sao_2_v[52], 6, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 2, 1, 3, 2, 3, 4),
    gsSPNTriangles_5b(0, 2, 4, 0, 4, 5, 1, 0, 5, 1, 5, 3),
    gsSPEndDisplayList(),
};

Gfx main2_saoB_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_sao_2_v[34], 3, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_sao_2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_sao_2_main1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tol_sao_2_v[37], 15, 3),
    gsSPNTrianglesInit_5b(6, 2, 0, 3, 2, 4, 5, 0, 1, 6),
    gsSPNTriangles_5b(0, 7, 8, 1, 2, 9, 1, 10, 11, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 12, 13, 14, 12, 14, 15, 13, 16, 17),
    gsSPNTriangles_5b(13, 17, 14, 16, 12, 15, 16, 15, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx main3_saoB_model[] = {
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_sao_2_v[16], 3, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_sao_2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_sao_2_main1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tol_sao_2_v[19], 15, 3),
    gsSPNTrianglesInit_5b(6, 2, 0, 3, 2, 4, 5, 1, 2, 6),
    gsSPNTriangles_5b(1, 7, 8, 0, 1, 9, 0, 10, 11, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 12, 13, 14, 12, 14, 15, 16, 12, 15),
    gsSPNTriangles_5b(16, 15, 17, 13, 16, 17, 13, 17, 14, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx main4_saoB_model[] = {
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_sao_2_v, 3, 0),
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_sao_2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_sao_2_main1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&tol_sao_2_v[3], 13, 3),
    gsSPNTrianglesInit_5b(6, 2, 0, 3, 2, 4, 5, 1, 2, 6),
    gsSPNTriangles_5b(1, 7, 8, 0, 1, 9, 0, 10, 11, 0, 0, 0),
    gsSPNTrianglesInit_5b(3, 12, 13, 14, 13, 15, 14, 15, 12, 14),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_sao_2_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { main1_saoB_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { main2_saoB_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1500, 0, 0 } },
                                           { main3_saoB_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1850, 0, 0 } },
                                           { main4_saoB_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1600, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_tol_sao_2 = { ARRAY_COUNT(cKF_je_r_tol_sao_2_tbl), 4, cKF_je_r_tol_sao_2_tbl };

u8 cKF_ckcb_r_tol_sao_1_sao_get_t1_tbl[] = { 0, 0, 1, 1, 1 };

s16 cKF_kn_tol_sao_1_sao_get_t1_tbl[] = { 7, 10, 12 };

s16 cKF_c_tol_sao_1_sao_get_t1_tbl[] = { 0, 0, 0, 900, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_tol_sao_1_sao_get_t1_tbl[] = { 1,    -150, -279, 3,    -160, 139,  8,    -34,  1025, 10,   23,   437, 14,
                                          5,    -219, 17,   0,    0,    22,   0,    0,    1,    -300, -442, 3,   -318,
                                          221,  4,    -300, 902,  6,    -203, 1807, 8,    -69,  2068, 9,    0,   1727,
                                          10,   46,   892,  14,   9,    -446, 17,   0,    0,    22,   0,    0,   1,
                                          -450, -664, 3,    -478, 332,  4,    -450, 1352, 6,    -304, 2705, 8,   -103,
                                          3107, 9,    0,    2602, 10,   70,   1345, 13,   45,   -925, 14,   14,  -673,
                                          15,   0,    -210, 16,   0,    0,    22,   0,    0 };

cKF_Animation_R_c cKF_ba_r_tol_sao_1_sao_get_t1 = { cKF_ckcb_r_tol_sao_1_sao_get_t1_tbl,
                                                    cKF_ds_tol_sao_1_sao_get_t1_tbl,
                                                    cKF_kn_tol_sao_1_sao_get_t1_tbl,
                                                    cKF_c_tol_sao_1_sao_get_t1_tbl,
                                                    -1,
                                                    22 };

u8 cKF_ckcb_r_tol_sao_1_sao_move1_tbl[] = { 56, 7, 1, 7, 7 };

s16 cKF_kn_tol_sao_1_sao_move1_tbl[] = { 2, 2, 2, 2, 2, 2, 6, 2, 2, 6, 2, 2, 6 };

s16 cKF_c_tol_sao_1_sao_move1_tbl[] = { 900, 0, 0, 0, 0 };

s16 cKF_ds_tol_sao_1_sao_move1_tbl[] = {
    1, 0,   0, 17, 0,   0, 1, 0,  0,     17, 0,   0, 1, 0,  0, 17, 0,   0, 1,  0,  0, 17, 0,  0,     1, 0, 0, 17, 0, 0,
    1, 900, 0, 17, 900, 0, 1, -8, -360,  2,  -15, 0, 6, 30, 0, 10, -15, 0, 14, 30, 0, 17, -8, -360,  1, 0, 0, 17, 0, 0,
    1, 0,   0, 17, 0,   0, 1, 15, -1012, 3,  -30, 0, 7, 60, 0, 11, -30, 0, 15, 60, 0, 17, 15, -1012, 1, 0, 0, 17, 0, 0,
    1, 0,   0, 17, 0,   0, 1, 69, -1141, 4,  -45, 0, 8, 90, 0, 12, -45, 0, 16, 90, 0, 17, 69, -1141
};

cKF_Animation_R_c cKF_ba_r_tol_sao_1_sao_move1 = { cKF_ckcb_r_tol_sao_1_sao_move1_tbl,
                                                   cKF_ds_tol_sao_1_sao_move1_tbl,
                                                   cKF_kn_tol_sao_1_sao_move1_tbl,
                                                   cKF_c_tol_sao_1_sao_move1_tbl,
                                                   -1,
                                                   17 };

u8 cKF_ckcb_r_tol_sao_1_sao_sinari1_tbl[] = { 0, 0, 1, 1, 1 };

s16 cKF_kn_tol_sao_1_sao_sinari1_tbl[] = { 2, 2, 2 };

s16 cKF_c_tol_sao_1_sao_sinari1_tbl[] = { 0, 0, 0, 900, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_tol_sao_1_sao_sinari1_tbl[] = { 1,   300,  -50,  360, -300, -50,  1,   600,  -100,
                                           360, -600, -100, 1,   900,  -150, 360, -900, -150 };

cKF_Animation_R_c cKF_ba_r_tol_sao_1_sao_sinari1 = { cKF_ckcb_r_tol_sao_1_sao_sinari1_tbl,
                                                     cKF_ds_tol_sao_1_sao_sinari1_tbl,
                                                     cKF_kn_tol_sao_1_sao_sinari1_tbl,
                                                     cKF_c_tol_sao_1_sao_sinari1_tbl,
                                                     -1,
                                                     360 };

u8 cKF_ckcb_r_tol_sao_1_sao_swing1_tbl[] = { 0, 0, 1, 1, 1 };

s16 cKF_kn_tol_sao_1_sao_swing1_tbl[] = { 14, 17, 19 };

s16 cKF_c_tol_sao_1_sao_swing1_tbl[] = { 0, 0, 0, 900, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_tol_sao_1_sao_swing1_tbl[] = {
    1,    0,    -457,  2,     -15,  -723, 4,     -80,  -739, 8,     -76,   654,  10,    -21,   900,  12,   45,
    1035, 16,   120,   -435,  18,   50,   -1354, 20,   -35,  -799,  21,    -50,  -38,   23,    -13,  556,  24,
    0,    194,  25,    0,     0,    34,   0,     0,    1,    0,     -944,  2,    -31,   -1477, 3,    -98,  -1928,
    4,    -160, -1400, 8,     -150, 1260, 10,    -40,  1800, 12,    83,    1902, 15,    236,   579,  16,   240,
    -612, 17,   195,   -1955, 19,   13,   -2650, 20,   -67,  -1689, 21,    -100, -106,  23,    -26,  1111, 24,
    0,    389,  25,    0,     0,    34,   0,     0,    1,    0,     -1493, 2,    -50,   -2293, 3,    -153, -2853,
    4,    -240, -1899, 5,     -279, -713, 8,     -220, 1753, 10,    -67,   2550, 12,    114,   2861, 15,   349,
    992,  16,   360,   -774,  17,   297,  -2859, 19,   22,   -4032, 20,    -99,  -2582, 21,    -150, -175, 22,
    -111, 1667, 23,    -39,   1667, 24,   0,     583,  25,   0,     0,     34,   0,     0
};

cKF_Animation_R_c cKF_ba_r_tol_sao_1_sao_swing1 = { cKF_ckcb_r_tol_sao_1_sao_swing1_tbl,
                                                    cKF_ds_tol_sao_1_sao_swing1_tbl,
                                                    cKF_kn_tol_sao_1_sao_swing1_tbl,
                                                    cKF_c_tol_sao_1_sao_swing1_tbl,
                                                    -1,
                                                    34 };

u8 cKF_ckcb_r_tol_sao_1_sao_wait1_tbl[] = { 56, 7, 7, 7, 7 };

s16 cKF_kn_tol_sao_1_sao_wait1_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 5, 3, 3, 6, 3, 3, 6 };

s16 cKF_c_tol_sao_1_sao_wait1_tbl[] = { 900, 0, 0 };

s16 cKF_ds_tol_sao_1_sao_wait1_tbl[] = { 1,  0,   0, 33, 0,  0, 1,  0,   0,    33, 0,   0,    1, 0,   0, 33, 0,   0,
                                         1,  0,   0, 33, 0,  0, 1,  0,   0,    33, 0,   0,    1, 900, 0, 33, 900, 0,
                                         1,  0,   0, 33, 0,  0, 1,  0,   0,    33, 0,   0,    1, -15, 0, 8,  30,  0,
                                         17, -15, 0, 25, 30, 0, 33, -15, 0,    1,  0,   0,    2, 0,   0, 33, 0,   0,
                                         1,  0,   0, 2,  0,  0, 33, 0,   0,    1,  -26, -222, 2, -30, 0, 9,  60,  0,
                                         18, -30, 0, 26, 60, 0, 33, -26, -222, 1,  0,   0,    3, 0,   0, 33, 0,   0,
                                         1,  0,   0, 3,  0,  0, 33, 0,   0,    1,  -24, -569, 3, -45, 0, 10, 90,  0,
                                         19, -45, 0, 27, 90, 0, 33, -24, -569 };

cKF_Animation_R_c cKF_ba_r_tol_sao_1_sao_wait1 = { cKF_ckcb_r_tol_sao_1_sao_wait1_tbl,
                                                   cKF_ds_tol_sao_1_sao_wait1_tbl,
                                                   cKF_kn_tol_sao_1_sao_wait1_tbl,
                                                   cKF_c_tol_sao_1_sao_wait1_tbl,
                                                   -1,
                                                   33 };

u8 cKF_ckcb_r_tol_sao_1_not_sao_swing1_tbl[] = { 0, 0, 1, 1, 1 };

s16 cKF_kn_tol_sao_1_not_sao_swing1_tbl[] = { 13, 16, 19 };

s16 cKF_c_tol_sao_1_not_sao_swing1_tbl[] = { 0, 0, 0, 900, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_tol_sao_1_not_sao_swing1_tbl[] = {
    1,  0,   -457,  2,  -15, -723,  4,  -80,  -739,  8,  -76,  654,   13, 61,   534,   16, 75,   -298, 19, 23,   -481,
    23, -18, -113,  24, -20, 88,    27, 10,   42,    29, 0,    -75,   31, 0,    0,     34, 0,    0,    1,  0,    -944,
    2,  -31, -1477, 3,  -98, -1928, 4,  -160, -1400, 8,  -150, 1260,  12, 71,   1307,  17, 120,  -577, 23, -34,  -352,
    24, -40, 137,   25, -24, 667,   26, 4,    667,   27, 20,   83,    28, 10,   -300,  29, 0,    -150, 30, 0,    0,
    34, 0,   0,     1,  0,   -1493, 2,  -50,  -2293, 3,  -153, -2853, 4,  -240, -1899, 5,  -279, -713, 8,  -220, 1753,
    10, -67, 2550,  12, 96,  1933,  16, 194,  -232,  18, 152,  -1018, 23, -49,  -592,  24, -60,  187,  25, -37,  1000,
    26, 7,   1000,  27, 30,  125,   28, 15,   -450,  29, 0,    -225,  30, 0,    0,     34, 0,    0
};

cKF_Animation_R_c cKF_ba_r_tol_sao_1_not_sao_swing1 = { cKF_ckcb_r_tol_sao_1_not_sao_swing1_tbl,
                                                        cKF_ds_tol_sao_1_not_sao_swing1_tbl,
                                                        cKF_kn_tol_sao_1_not_sao_swing1_tbl,
                                                        cKF_c_tol_sao_1_not_sao_swing1_tbl,
                                                        -1,
                                                        34 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 act_m_scoop_1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 act_m_scoop_1_pal[] = {
#include "assets/act_m_scoop_1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_scoop_1_main1_tex_txt[0x100];
#else
u8 tol_scoop_1_main1_tex_txt[] = {
#include "assets/tol_scoop_1_main1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_scoop_1_tuka1_tex_txt[0x200];
#else
u8 tol_scoop_1_tuka1_tex_txt[] = {
#include "assets/tol_scoop_1_tuka1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_scoop_1_tuka2_tex_txt[0x80];
#else
u8 tol_scoop_1_tuka2_tex_txt[] = {
#include "assets/tol_scoop_1_tuka2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_scoop_1_tuka3_tex_txt[0x80];
#else
u8 tol_scoop_1_tuka3_tex_txt[] = {
#include "assets/tol_scoop_1_tuka3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_scoop_1_main2_tex_txt[0x100];
#else
u8 tol_scoop_1_main2_tex_txt[] = {
#include "assets/tol_scoop_1_main2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_scoop_1_v[0x330 / sizeof(Vtx)];
#else
Vtx tol_scoop_1_v[] = {
#include "assets/tol_scoop_1_v.inc"
};
#endif

Gfx tol_scoop_1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_m_scoop_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_scoop_1_main1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 178, 178, 178, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_scoop_1_v, 31, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 0, 5, 6, 0),
    gsSPNTriangles_5b(0, 6, 3, 0, 4, 1, 7, 5, 0, 0, 2, 7),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_scoop_1_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPNTrianglesInit_5b(6, 8, 9, 10, 11, 12, 9, 11, 9, 8),
    gsSPNTriangles_5b(13, 14, 12, 13, 12, 11, 8, 10, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, tol_scoop_1_tuka2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 18, 19, 20, 16, 19),
    gsSPNTriangles_5b(20, 19, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1, 22, 23, 24, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(4, 25, 26, 27, 25, 27, 28, 29, 25, 28),
    gsSPNTriangles_5b(29, 28, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, tol_scoop_1_tuka3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_scoop_1_v[31], 20, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 4, 6, 7, 4, 7, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_scoop_1_main2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(12, 8, 9, 10, 8, 10, 11, 11, 12, 8),
    gsSPNTriangles_5b(10, 13, 14, 8, 12, 15, 16, 17, 11, 17, 12, 11),
    gsSPNTriangles_5b(9, 18, 19, 9, 19, 10, 19, 13, 10, 14, 16, 11),
    gsSPNTriangles_5b(14, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_scoop_2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_scoop_2_pal[] = {
#include "assets/tol_scoop_2_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_scoop_2_main1_tex_txt[0x100];
#else
u8 tol_scoop_2_main1_tex_txt[] = {
#include "assets/tol_scoop_2_main1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_scoop_2_tuka1_tex_txt[0x200];
#else
u8 tol_scoop_2_tuka1_tex_txt[] = {
#include "assets/tol_scoop_2_tuka1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_scoop_2_tuka2_tex_txt[0x80];
#else
u8 tol_scoop_2_tuka2_tex_txt[] = {
#include "assets/tol_scoop_2_tuka2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_scoop_2_tuka3_tex_txt[0x80];
#else
u8 tol_scoop_2_tuka3_tex_txt[] = {
#include "assets/tol_scoop_2_tuka3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_scoop_2_main2_tex_txt[0x100];
#else
u8 tol_scoop_2_main2_tex_txt[] = {
#include "assets/tol_scoop_2_main2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_scoop_2_v[0x330 / sizeof(Vtx)];
#else
Vtx tol_scoop_2_v[] = {
#include "assets/tol_scoop_2_v.inc"
};
#endif

Gfx tol_scoop_2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_scoop_2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_scoop_2_main1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 178, 178, 178, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_scoop_2_v, 31, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 0, 5, 6, 0),
    gsSPNTriangles_5b(0, 6, 3, 0, 4, 1, 7, 5, 0, 0, 2, 7),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_scoop_2_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPNTrianglesInit_5b(6, 8, 9, 10, 11, 12, 9, 11, 9, 8),
    gsSPNTriangles_5b(13, 14, 12, 13, 12, 11, 8, 10, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, tol_scoop_2_tuka2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 18, 19, 20, 16, 19),
    gsSPNTriangles_5b(20, 19, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1, 22, 23, 24, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(4, 25, 26, 27, 25, 27, 28, 29, 25, 28),
    gsSPNTriangles_5b(29, 28, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, tol_scoop_2_tuka3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_scoop_2_v[31], 20, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 4, 6, 7, 4, 7, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_scoop_2_main2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(12, 8, 9, 10, 8, 10, 11, 11, 12, 8),
    gsSPNTriangles_5b(10, 13, 14, 8, 12, 15, 16, 17, 11, 17, 12, 11),
    gsSPNTriangles_5b(9, 18, 19, 9, 19, 10, 19, 13, 10, 14, 16, 11),
    gsSPNTriangles_5b(14, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 tol_balloon1_wire_tex_txt[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 tol_balloon1_wire_tex_txt[] = {
#include "assets/player_tool/tol_balloon1_wire_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_balloonA_head_tex_rgb_ia8[0x400];
#else
u8 tol_balloonA_head_tex_rgb_ia8[] = {
#include "assets/tol_balloonA_head_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_balloon1_v[0x460 / sizeof(Vtx)];
#else
Vtx tol_balloon1_v[] = {
#include "assets/tol_balloon1_v.inc"
};
#endif

Gfx tol_balloonA_a_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloon1_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon1_v[62], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonA_b_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloon1_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon1_v[44], 4, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloon1_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon1_v[48], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 1, 6, 7, 0, 1, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonA_c_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloon1_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon1_v[26], 4, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloon1_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon1_v[30], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 0, 1, 6, 1, 7, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonA_head_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(255, 0, 0, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, tol_balloonA_head_tex_rgb_ia8),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH),
    gsSPVertex(tol_balloon1_v, 26, 0),
    gsSPNTrianglesInit_5b(36, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(5, 4, 3, 6, 5, 3, 7, 6, 3, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 11, 4, 10, 10, 4, 5, 12, 10, 5),
    gsSPNTriangles_5b(13, 12, 5, 14, 15, 11, 15, 16, 11, 16, 4, 11),
    gsSPNTriangles_5b(2, 4, 16, 17, 2, 16, 18, 17, 16, 19, 17, 18),
    gsSPNTriangles_5b(19, 20, 17, 19, 21, 20, 22, 21, 19, 22, 19, 15),
    gsSPNTriangles_5b(22, 15, 14, 23, 12, 13, 23, 24, 12, 23, 21, 24),
    gsSPNTriangles_5b(24, 21, 22, 24, 22, 9, 24, 9, 8, 25, 6, 7),
    gsSPNTriangles_5b(25, 23, 6, 25, 21, 23, 20, 21, 25, 20, 25, 1),
    gsSPNTriangles_5b(20, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_balloon1_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonA_a_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonA_b_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 900, 0, 0 } },
                                              { tol_balloonA_c_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 800, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 900, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonA_head_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_tol_balloon1 = { ARRAY_COUNT(cKF_je_r_tol_balloon1_tbl), 4, cKF_je_r_tol_balloon1_tbl };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 tol_balloonB_wire_tex_txt[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 tol_balloonB_wire_tex_txt[] = {
#include "assets/tol_balloonB_wire_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_balloonB_head_tex_rgb_ia8[0x400];
#else
u8 tol_balloonB_head_tex_rgb_ia8[] = {
#include "assets/tol_balloonB_head_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_balloon2_v[0x460 / sizeof(Vtx)];
#else
Vtx tol_balloon2_v[] = {
#include "assets/tol_balloon2_v.inc"
};
#endif

Gfx tol_balloonB_a_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonB_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon2_v[62], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonB_b_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonB_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon2_v[44], 4, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonB_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon2_v[48], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 1, 6, 7, 0, 1, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonB_c_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonB_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon2_v[26], 4, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonB_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon2_v[30], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 0, 1, 6, 1, 7, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonB_head_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(255, 255, 0, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, tol_balloonB_head_tex_rgb_ia8),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH),
    gsSPVertex(tol_balloon2_v, 26, 0),
    gsSPNTrianglesInit_5b(36, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(5, 4, 3, 6, 5, 3, 7, 6, 3, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 11, 4, 10, 10, 4, 5, 12, 10, 5),
    gsSPNTriangles_5b(13, 12, 5, 14, 15, 11, 15, 16, 11, 16, 4, 11),
    gsSPNTriangles_5b(2, 4, 16, 17, 2, 16, 18, 17, 16, 19, 17, 18),
    gsSPNTriangles_5b(19, 20, 17, 19, 21, 20, 22, 21, 19, 22, 19, 15),
    gsSPNTriangles_5b(22, 15, 14, 23, 12, 13, 23, 24, 12, 23, 21, 24),
    gsSPNTriangles_5b(24, 21, 22, 24, 22, 9, 24, 9, 8, 25, 6, 7),
    gsSPNTriangles_5b(25, 23, 6, 25, 21, 23, 20, 21, 25, 20, 25, 1),
    gsSPNTriangles_5b(20, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_balloon2_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonB_a_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonB_b_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 900, 0, 0 } },
                                              { tol_balloonB_c_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 800, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 900, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonB_head_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_tol_balloon2 = { ARRAY_COUNT(cKF_je_r_tol_balloon2_tbl), 4, cKF_je_r_tol_balloon2_tbl };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 tol_balloonC_wire_tex_txt[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 tol_balloonC_wire_tex_txt[] = {
#include "assets/tol_balloonC_wire_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_balloonC_head_tex_rgb_ia8[0x400];
#else
u8 tol_balloonC_head_tex_rgb_ia8[] = {
#include "assets/tol_balloonC_head_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_balloon3_v[0x460 / sizeof(Vtx)];
#else
Vtx tol_balloon3_v[] = {
#include "assets/tol_balloon3_v.inc"
};
#endif

Gfx tol_balloonC_a_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonC_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon3_v[62], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonC_b_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonC_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon3_v[44], 4, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonC_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon3_v[48], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 1, 6, 7, 0, 1, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonC_c_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonC_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon3_v[26], 4, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonC_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon3_v[30], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 0, 1, 6, 1, 7, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonC_head_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(0, 0, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, tol_balloonC_head_tex_rgb_ia8),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH),
    gsSPVertex(tol_balloon3_v, 26, 0),
    gsSPNTrianglesInit_5b(36, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(5, 4, 3, 6, 5, 3, 7, 6, 3, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 11, 4, 10, 10, 4, 5, 12, 10, 5),
    gsSPNTriangles_5b(13, 12, 5, 14, 15, 11, 15, 16, 11, 16, 4, 11),
    gsSPNTriangles_5b(2, 4, 16, 17, 2, 16, 18, 17, 16, 19, 17, 18),
    gsSPNTriangles_5b(19, 20, 17, 19, 21, 20, 22, 21, 19, 22, 19, 15),
    gsSPNTriangles_5b(22, 15, 14, 23, 12, 13, 23, 24, 12, 23, 21, 24),
    gsSPNTriangles_5b(24, 21, 22, 24, 22, 9, 24, 9, 8, 25, 6, 7),
    gsSPNTriangles_5b(25, 23, 6, 25, 21, 23, 20, 21, 25, 20, 25, 1),
    gsSPNTriangles_5b(20, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_balloon3_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { tol_balloonC_a_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { tol_balloonC_b_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 900, 0, 0 } },
    { tol_balloonC_c_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 800, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 900, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { tol_balloonC_head_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
};

cKF_Skeleton_R_c cKF_bs_r_tol_balloon3 = { ARRAY_COUNT(cKF_je_r_tol_balloon3_tbl), 4, cKF_je_r_tol_balloon3_tbl };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 tol_balloonD_wire_tex_txt[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 tol_balloonD_wire_tex_txt[] = {
#include "assets/tol_balloonD_wire_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_balloonD_head_tex_rgb_ia8[0x400];
#else
u8 tol_balloonD_head_tex_rgb_ia8[] = {
#include "assets/tol_balloonD_head_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_balloon4_v[0x460 / sizeof(Vtx)];
#else
Vtx tol_balloon4_v[] = {
#include "assets/tol_balloon4_v.inc"
};
#endif

Gfx tol_balloonD_a_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonD_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon4_v[62], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonD_b_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonD_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon4_v[44], 4, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonD_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon4_v[48], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 1, 6, 7, 0, 1, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonD_c_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonD_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon4_v[26], 4, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonD_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon4_v[30], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 0, 1, 6, 1, 7, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonD_head_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(0, 255, 0, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, tol_balloonD_head_tex_rgb_ia8),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH),
    gsSPVertex(tol_balloon4_v, 26, 0),
    gsSPNTrianglesInit_5b(36, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(5, 4, 3, 6, 5, 3, 7, 6, 3, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 11, 4, 10, 10, 4, 5, 12, 10, 5),
    gsSPNTriangles_5b(13, 12, 5, 14, 15, 11, 15, 16, 11, 16, 4, 11),
    gsSPNTriangles_5b(2, 4, 16, 17, 2, 16, 18, 17, 16, 19, 17, 18),
    gsSPNTriangles_5b(19, 20, 17, 19, 21, 20, 22, 21, 19, 22, 19, 15),
    gsSPNTriangles_5b(22, 15, 14, 23, 12, 13, 23, 24, 12, 23, 21, 24),
    gsSPNTriangles_5b(24, 21, 22, 24, 22, 9, 24, 9, 8, 25, 6, 7),
    gsSPNTriangles_5b(25, 23, 6, 25, 21, 23, 20, 21, 25, 20, 25, 1),
    gsSPNTriangles_5b(20, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_balloon4_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonD_a_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonD_b_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 900, 0, 0 } },
                                              { tol_balloonD_c_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 800, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 900, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonD_head_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_tol_balloon4 = { ARRAY_COUNT(cKF_je_r_tol_balloon4_tbl), 4, cKF_je_r_tol_balloon4_tbl };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 tol_balloonE_wire_tex_txt[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 tol_balloonE_wire_tex_txt[] = {
#include "assets/tol_balloonE_wire_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_balloonE_head_tex_rgb_ia8[0x400];
#else
u8 tol_balloonE_head_tex_rgb_ia8[] = {
#include "assets/tol_balloonE_head_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_balloon5_v[0x460 / sizeof(Vtx)];
#else
Vtx tol_balloon5_v[] = {
#include "assets/tol_balloon5_v.inc"
};
#endif

Gfx tol_balloonE_a_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonE_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon5_v[62], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonE_b_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonE_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon5_v[44], 4, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonE_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon5_v[48], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 1, 6, 7, 0, 1, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonE_c_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonE_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon5_v[26], 4, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonE_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon5_v[30], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 0, 1, 6, 1, 7, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonE_head_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(160, 0, 160, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, tol_balloonE_head_tex_rgb_ia8),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH),
    gsSPVertex(tol_balloon5_v, 26, 0),
    gsSPNTrianglesInit_5b(36, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(5, 4, 3, 6, 5, 3, 7, 6, 3, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 11, 4, 10, 10, 4, 5, 12, 10, 5),
    gsSPNTriangles_5b(13, 12, 5, 14, 15, 11, 15, 16, 11, 16, 4, 11),
    gsSPNTriangles_5b(2, 4, 16, 17, 2, 16, 18, 17, 16, 19, 17, 18),
    gsSPNTriangles_5b(19, 20, 17, 19, 21, 20, 22, 21, 19, 22, 19, 15),
    gsSPNTriangles_5b(22, 15, 14, 23, 12, 13, 23, 24, 12, 23, 21, 24),
    gsSPNTriangles_5b(24, 21, 22, 24, 22, 9, 24, 9, 8, 25, 6, 7),
    gsSPNTriangles_5b(25, 23, 6, 25, 21, 23, 20, 21, 25, 20, 25, 1),
    gsSPNTriangles_5b(20, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_balloon5_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonE_a_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonE_b_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 900, 0, 0 } },
                                              { tol_balloonE_c_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 800, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 900, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonE_head_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_tol_balloon5 = { ARRAY_COUNT(cKF_je_r_tol_balloon5_tbl), 4, cKF_je_r_tol_balloon5_tbl };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 tol_balloonF_wire_tex_txt[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 tol_balloonF_wire_tex_txt[] = {
#include "assets/tol_balloonF_wire_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_balloonF5_head_tex_rgb_ia8[0x400];
#else
u8 tol_balloonF5_head_tex_rgb_ia8[] = {
#include "assets/tol_balloonF5_head_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_balloon6_v[0xC60 / sizeof(Vtx)];
#else
Vtx tol_balloon6_v[] = {
#include "assets/tol_balloon6_v.inc"
};
#endif

Gfx tol_balloonF_a_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonF_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon6_v[190], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonF_b_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonF_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon6_v[172], 4, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonF_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon6_v[176], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 1, 6, 7, 0, 1, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonF_c_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonF_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon6_v[154], 4, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonF_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon6_v[158], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 0, 1, 6, 1, 7, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonF_head_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(255, 50, 120, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, tol_balloonF5_head_tex_rgb_ia8),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH),
    gsSPVertex(tol_balloon6_v, 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(6, 8, 9, 10, 11, 12, 12, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(18, 19, 10, 18, 16, 15, 20, 17, 21, 22, 0, 23),
    gsSPNTriangles_5b(21, 7, 20, 0, 24, 23, 25, 26, 27, 28, 26, 25),
    gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&tol_balloon6_v[32], 32, 0),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 8, 7, 4, 3, 10, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(9, 2, 17, 18, 14, 10, 19, 20, 17, 15, 14, 18),
    gsSPNTriangles_5b(8, 21, 22, 23, 24, 3, 10, 25, 4, 8, 9, 21),
    gsSPNTriangles_5b(8, 26, 6, 10, 27, 18, 18, 27, 28, 24, 23, 28),
    gsSPNTriangles_5b(29, 30, 31, 17, 20, 13, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&tol_balloon6_v[64], 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(6, 8, 9, 10, 11, 12, 13, 10, 14, 1, 0, 15),
    gsSPNTriangles_5b(1, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25),
    gsSPNTriangles_5b(23, 25, 26, 9, 8, 26, 13, 4, 11, 24, 23, 27),
    gsSPNTriangles_5b(28, 21, 29, 25, 24, 5, 29, 21, 20, 29, 15, 0),
    gsSPNTriangles_5b(5, 30, 31, 5, 24, 3, 5, 4, 13, 0, 0, 0),
    gsSPVertex(&tol_balloon6_v[96], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 5, 7),
    gsSPNTriangles_5b(2, 8, 0, 7, 9, 6, 5, 4, 7, 9, 7, 10),
    gsSPNTriangles_5b(11, 12, 13, 14, 15, 16, 14, 16, 17, 14, 18, 5),
    gsSPNTriangles_5b(19, 20, 21, 19, 21, 22, 20, 19, 23, 0, 24, 1),
    gsSPNTriangles_5b(1, 24, 25, 26, 27, 28, 29, 30, 31, 0, 0, 0),
    gsSPVertex(&tol_balloon6_v[128], 26, 0),
    gsSPNTrianglesInit_5b(35, 0, 1, 2, 1, 3, 2, 4, 3, 1),
    gsSPNTriangles_5b(5, 4, 1, 6, 5, 1, 7, 8, 9, 8, 10, 9),
    gsSPNTriangles_5b(10, 3, 9, 9, 3, 4, 11, 9, 4, 12, 11, 4),
    gsSPNTriangles_5b(8, 13, 10, 13, 14, 10, 14, 3, 10, 2, 3, 14),
    gsSPNTriangles_5b(15, 2, 14, 16, 15, 14, 17, 15, 16, 17, 18, 15),
    gsSPNTriangles_5b(17, 19, 18, 20, 19, 17, 20, 17, 13, 20, 13, 21),
    gsSPNTriangles_5b(22, 11, 12, 22, 23, 11, 22, 19, 23, 23, 19, 20),
    gsSPNTriangles_5b(23, 20, 8, 23, 8, 7, 24, 5, 25, 24, 22, 5),
    gsSPNTriangles_5b(24, 19, 22, 18, 19, 24, 18, 24, 0, 18, 0, 15),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_balloon6_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonF_a_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonF_b_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 900, 0, 0 } },
                                              { tol_balloonF_c_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 800, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 900, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonF_head_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_tol_balloon6 = { ARRAY_COUNT(cKF_je_r_tol_balloon6_tbl), 4, cKF_je_r_tol_balloon6_tbl };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 tol_balloonG_wire_tex_txt[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 tol_balloonG_wire_tex_txt[] = {
#include "assets/tol_balloonG_wire_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_balloonG5_head_tex_rgb_ia8[0x400];
#else
u8 tol_balloonG5_head_tex_rgb_ia8[] = {
#include "assets/tol_balloonG5_head_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_balloon7_v[0xC60 / sizeof(Vtx)];
#else
Vtx tol_balloon7_v[] = {
#include "assets/tol_balloon7_v.inc"
};
#endif

Gfx tol_balloonG_a_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonG_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon7_v[190], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonG_b_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonG_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon7_v[172], 4, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonG_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon7_v[176], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 1, 6, 7, 0, 1, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonG_c_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonG_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon7_v[154], 4, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonG_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon7_v[158], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 0, 1, 6, 1, 7, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonG_head_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(0, 80, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, tol_balloonG5_head_tex_rgb_ia8),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH),
    gsSPVertex(tol_balloon7_v, 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(6, 8, 9, 10, 11, 12, 12, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(18, 19, 10, 18, 16, 15, 20, 17, 21, 22, 0, 23),
    gsSPNTriangles_5b(21, 7, 20, 0, 24, 23, 25, 26, 27, 28, 26, 25),
    gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&tol_balloon7_v[32], 32, 0),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 8, 7, 4, 3, 10, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(9, 2, 17, 18, 14, 10, 19, 20, 17, 15, 14, 18),
    gsSPNTriangles_5b(8, 21, 22, 23, 24, 3, 10, 25, 4, 8, 9, 21),
    gsSPNTriangles_5b(8, 26, 6, 10, 27, 18, 18, 27, 28, 24, 23, 28),
    gsSPNTriangles_5b(29, 30, 31, 17, 20, 13, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&tol_balloon7_v[64], 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(6, 8, 9, 10, 11, 12, 13, 10, 14, 1, 0, 15),
    gsSPNTriangles_5b(1, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25),
    gsSPNTriangles_5b(23, 25, 26, 9, 8, 26, 13, 4, 11, 24, 23, 27),
    gsSPNTriangles_5b(28, 21, 29, 25, 24, 5, 29, 21, 20, 29, 15, 0),
    gsSPNTriangles_5b(5, 30, 31, 5, 24, 3, 5, 4, 13, 0, 0, 0),
    gsSPVertex(&tol_balloon7_v[96], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 5, 7),
    gsSPNTriangles_5b(2, 8, 0, 7, 9, 6, 5, 4, 7, 9, 7, 10),
    gsSPNTriangles_5b(11, 12, 13, 14, 15, 16, 14, 16, 17, 14, 18, 5),
    gsSPNTriangles_5b(19, 20, 21, 19, 21, 22, 20, 19, 23, 0, 24, 1),
    gsSPNTriangles_5b(1, 24, 25, 26, 27, 28, 29, 30, 31, 0, 0, 0),
    gsSPVertex(&tol_balloon7_v[128], 26, 0),
    gsSPNTrianglesInit_5b(35, 0, 1, 2, 1, 3, 2, 4, 3, 1),
    gsSPNTriangles_5b(5, 4, 1, 6, 5, 1, 7, 8, 9, 8, 10, 9),
    gsSPNTriangles_5b(10, 3, 9, 9, 3, 4, 11, 9, 4, 12, 11, 4),
    gsSPNTriangles_5b(8, 13, 10, 13, 14, 10, 14, 3, 10, 2, 3, 14),
    gsSPNTriangles_5b(15, 2, 14, 16, 15, 14, 17, 15, 16, 17, 18, 15),
    gsSPNTriangles_5b(17, 19, 18, 20, 19, 17, 20, 17, 13, 20, 13, 21),
    gsSPNTriangles_5b(22, 11, 12, 22, 23, 11, 22, 19, 23, 23, 19, 20),
    gsSPNTriangles_5b(23, 20, 8, 23, 8, 7, 24, 5, 25, 24, 22, 5),
    gsSPNTriangles_5b(24, 19, 22, 18, 19, 24, 18, 24, 0, 18, 0, 15),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_balloon7_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonG_a_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonG_b_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 900, 0, 0 } },
                                              { tol_balloonG_c_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 800, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 900, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonG_head_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_tol_balloon7 = { ARRAY_COUNT(cKF_je_r_tol_balloon7_tbl), 4, cKF_je_r_tol_balloon7_tbl };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 tol_balloonH_wire_tex_txt[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 tol_balloonH_wire_tex_txt[] = {
#include "assets/tol_balloonH_wire_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_balloonH5_head_tex_rgb_ia8[0x400];
#else
u8 tol_balloonH5_head_tex_rgb_ia8[] = {
#include "assets/tol_balloonH5_head_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_balloon8_v[0xC60 / sizeof(Vtx)];
#else
Vtx tol_balloon8_v[] = {
#include "assets/tol_balloon8_v.inc"
};
#endif

Gfx tol_balloonH_a_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonH_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon8_v[190], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonH_b_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonH_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon8_v[172], 4, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonH_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon8_v[176], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 1, 6, 7, 0, 1, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonH_c_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonH_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon8_v[154], 4, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, tol_balloonH_wire_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_balloon8_v[158], 14, 4),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 0, 1, 6, 1, 7, 8),
    gsSPNTriangles_5b(2, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 12, 16, 10),
    gsSPNTriangles_5b(15, 17, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_balloonH_head_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(255, 100, 0, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, tol_balloonH5_head_tex_rgb_ia8),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH),
    gsSPVertex(tol_balloon8_v, 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(6, 8, 9, 10, 11, 12, 12, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(18, 19, 10, 18, 16, 15, 20, 17, 21, 22, 0, 23),
    gsSPNTriangles_5b(21, 7, 20, 0, 24, 23, 25, 26, 27, 28, 26, 25),
    gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&tol_balloon8_v[32], 32, 0),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 8, 7, 4, 3, 10, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(9, 2, 17, 18, 14, 10, 19, 20, 17, 15, 14, 18),
    gsSPNTriangles_5b(8, 21, 22, 23, 24, 3, 10, 25, 4, 8, 9, 21),
    gsSPNTriangles_5b(8, 26, 6, 10, 27, 18, 18, 27, 28, 24, 23, 28),
    gsSPNTriangles_5b(29, 30, 31, 17, 20, 13, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&tol_balloon8_v[64], 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(6, 8, 9, 10, 11, 12, 13, 10, 14, 1, 0, 15),
    gsSPNTriangles_5b(1, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25),
    gsSPNTriangles_5b(23, 25, 26, 9, 8, 26, 13, 4, 11, 24, 23, 27),
    gsSPNTriangles_5b(28, 21, 29, 25, 24, 5, 29, 21, 20, 29, 15, 0),
    gsSPNTriangles_5b(5, 30, 31, 5, 24, 3, 5, 4, 13, 0, 0, 0),
    gsSPVertex(&tol_balloon8_v[96], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 5, 7),
    gsSPNTriangles_5b(2, 8, 0, 7, 9, 6, 5, 4, 7, 9, 7, 10),
    gsSPNTriangles_5b(11, 12, 13, 14, 15, 16, 14, 16, 17, 14, 18, 5),
    gsSPNTriangles_5b(19, 20, 21, 19, 21, 22, 20, 19, 23, 0, 24, 1),
    gsSPNTriangles_5b(1, 24, 25, 26, 27, 28, 29, 30, 31, 0, 0, 0),
    gsSPVertex(&tol_balloon8_v[128], 26, 0),
    gsSPNTrianglesInit_5b(35, 0, 1, 2, 1, 3, 2, 4, 3, 1),
    gsSPNTriangles_5b(5, 4, 1, 6, 5, 1, 7, 8, 9, 8, 10, 9),
    gsSPNTriangles_5b(10, 3, 9, 9, 3, 4, 11, 9, 4, 12, 11, 4),
    gsSPNTriangles_5b(8, 13, 10, 13, 14, 10, 14, 3, 10, 2, 3, 14),
    gsSPNTriangles_5b(15, 2, 14, 16, 15, 14, 17, 15, 16, 17, 18, 15),
    gsSPNTriangles_5b(17, 19, 18, 20, 19, 17, 20, 17, 13, 20, 13, 21),
    gsSPNTriangles_5b(22, 11, 12, 22, 23, 11, 22, 19, 23, 23, 19, 20),
    gsSPNTriangles_5b(23, 20, 8, 23, 8, 7, 24, 5, 25, 24, 22, 5),
    gsSPNTriangles_5b(24, 19, 22, 18, 19, 24, 18, 24, 0, 18, 0, 15),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_balloon8_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonH_a_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonH_b_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 900, 0, 0 } },
                                              { tol_balloonH_c_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 800, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 900, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { tol_balloonH_head_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_tol_balloon8 = { ARRAY_COUNT(cKF_je_r_tol_balloon8_tbl), 4, cKF_je_r_tol_balloon8_tbl };

u8 cKF_ckcb_r_tol_balloon1_wait_tbl[] = { 0, 3, 7, 7, 0, 0, 7 };

s16 cKF_kn_tol_balloon1_wait_tbl[] = { 3, 3, 2, 4, 4, 2, 4, 4, 2, 4, 4 };

s16 cKF_c_tol_balloon1_wait_tbl[] = { 0, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_tol_balloon1_wait_tbl[] = { 1,    -50,  0,    31,  50,  0,    61,   -50,  0,   1,   100, 0,    31,   -100,
                                       0,    61,   100,  0,   1,   0,    0,    61,   0,   0,   1,   48,   -246, 21,
                                       -100, 4,    51,   100, -5,  61,   48,   -236, 1,   -96, 470, 21,   200,  3,
                                       51,   -200, -12,  61,  -96, 527,  1,    0,    0,   61,  0,   0,    1,    72,
                                       388,  11,   150,  -5,  41,  -150, 1,    61,   72,  383, 1,   -144, -742, 11,
                                       -300, -4,   41,   300, -4,  61,   -144, -799, 1,   0,   0,   61,   0,    0,
                                       1,    -52,  -150, 9,   -75, 1,    39,   75,   13,  61,  -52, -150, 1,    103,
                                       331,  9,    150,  -1,  39,  -150, -2,   61,   103, 300 };

cKF_Animation_R_c cKF_ba_r_tol_balloon1_wait = { cKF_ckcb_r_tol_balloon1_wait_tbl,
                                                 cKF_ds_tol_balloon1_wait_tbl,
                                                 cKF_kn_tol_balloon1_wait_tbl,
                                                 cKF_c_tol_balloon1_wait_tbl,
                                                 -1,
                                                 61 };

u8 cKF_ckcb_r_tol_balloon1_gyaza1_tbl[] = { 0, 7, 7, 7, 0, 0, 7 };

s16 cKF_kn_tol_balloon1_gyaza1_tbl[] = { 13, 13, 13, 18, 18, 18, 21, 21, 21, 27, 15, 27 };

s16 cKF_c_tol_balloon1_gyaza1_tbl[] = { 0, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_tol_balloon1_gyaza1_tbl[] = {
    1,  0,     0,     3,  0,     0,     6,  52,    344,   7,  46,    -131,  9,  39,    -401,  10, 6,     -661,
    11, -5,    -58,   13, 0,     0,     15, 0,     0,     17, 0,     0,     23, 0,     0,     25, 0,     0,
    27, 0,     0,     1,  0,     0,     3,  0,     111,   6,  18,    171,   7,  23,    -19,   9,  17,    -114,
    10, 11,    -146,  11, 7,     -114,  13, 0,     0,     15, 0,     0,     17, 0,     0,     23, 0,     0,
    25, 0,     0,     27, 0,     0,     1,  900,   0,     3,  822,   -1426, 6,  662,   -1612, 7,  607,   -1642,
    9,  498,   -1639, 10, 443,   -1607, 11, 391,   -1510, 13, 292,   -1331, 15, 302,   434,   17, 304,   -123,
    23, 189,   -1156, 25, 88,    -1416, 27, 0,     -905,  1,  832,   0,     3,  751,   -2941, 7,  356,   -2974,
    8,  256,   -2657, 10, 90,    -2021, 11, 53,    -1028, 13, 0,     -21,   14, 0,     -5,    15, 0,     3,
    17, 0,     2,     20, 0,     0,     21, 0,     0,     22, 0,     0,     23, 0,     0,     24, 0,     0,
    25, 0,     0,     26, 0,     0,     27, 0,     0,     1,  629,   0,     3,  631,   -63,   7,  549,   -860,
    8,  488,   -2535, 10, 296,   -2947, 11, 193,   -2960, 13, 0,     5,     14, 0,     1,     15, 0,     -1,
    17, 0,     -1,    20, 0,     0,     21, 0,     0,     22, 0,     0,     23, 0,     0,     24, 0,     0,
    25, 0,     0,     26, 0,     0,     27, 0,     0,     1,  -1816, 0,     3,  -1762, -39,   7,  -1823, -494,
    8,  -1844, -102,  10, -1834, 720,   11, -1772, 2785,  13, -1555, 3341,  14, -1438, 2881,  15, -1363, 2290,
    17, -1209, 2302,  20, -979,  2395,  21, -890,  2703,  22, -799,  2972,  23, -692,  3433,  24, -570,  3998,
    25, -425,  4519,  26, -269,  6377,  27, 0,     7654,  1,  -135,  0,     3,  -113,  370,   7,  -61,   307,
    8,  -62,   -61,   9,  -65,   102,   10, -55,   372,   11, -40,   548,   13, 0,     1,     14, 0,     0,
    15, 0,     0,     17, 0,     0,     18, 0,     0,     19, 0,     0,     20, 0,     0,     21, 0,     0,
    22, 0,     0,     23, 0,     0,     24, 0,     0,     25, 0,     0,     26, 0,     0,     27, 0,     0,
    1,  -49,   0,     3,  -51,   -54,   7,  -60,   2,     8,  -51,   356,   9,  -36,   534,   10, -15,   581,
    11, 3,     151,   13, 0,     -28,   14, 0,     -3,    15, 0,     2,     17, 0,     2,     18, 0,     0,
    19, 0,     0,     20, 0,     0,     21, 0,     0,     22, 0,     0,     23, 0,     0,     24, 0,     0,
    25, 0,     0,     26, 0,     0,     27, 0,     0,     1,  -2444, 0,     3,  -2442, 429,   7,  -2358, 703,
    8,  -2324, 939,   9,  -2296, 925,   10, -2263, 881,   11, -2237, 564,   13, -2206, -154,  14, -2252, -1894,
    15, -2333, -2160, 17, -2468, -2079, 18, -2540, -2046, 19, -2605, -1879, 20, -2666, -2056, 21, -2742, -2084,
    22, -2805, -2192, 23, -2888, -2287, 24, -2957, -2619, 25, -3062, -3786, 26, -3210, -8063, 27, -3600, -12780,
    1,  532,   0,     2,  447,   -5172, 3,  187,   -7040, 4,  -22,   -4492, 5,  -112,  -1387, 6,  -115,  -283,
    7,  -131,  23,    8,  -113,  722,   9,  -83,   651,   10, -70,   516,   11, -49,   691,   12, -24,   732,
    13, 0,     386,   14, 2,     -31,   15, -2,    -56,   16, -1,    17,    17, -1,    19,    18, 0,     15,
    19, 0,     22,    20, 1,     29,    21, 2,     27,    22, 3,     19,    23, 4,     -4,    24, 3,     -28,
    25, 2,     -33,   26, 1,     -25,   27, 0,     0,     1,  781,   0,     2,  794,   259,   3,  798,   -501,
    4,  761,   -1522, 5,  697,   -1993, 6,  628,   -1761, 7,  580,   -2042, 8,  492,   -2994, 9,  380,   -3221,
    10, 277,   -3116, 11, 172,   -3268, 12, 59,    -2584, 13, 0,     -14,   14, 0,     0,     27, 0,     0,
    1,  907,   0,     2,  829,   -5235, 3,  558,   -7620, 4,  321,   -4995, 5,  225,   -2042, 6,  185,   -1084,
    7,  153,   -823,  8,  130,   -641,  9,  110,   -842,  10, 74,    -1260, 11, 26,    -1978, 12, -58,   -2348,
    13, -131,  -2010, 14, -192,  -1148, 15, -207,  -450,  16, -222,  -300,  17, -227,  -15,   18, -223,  30,
    19, -225,  -75,   20, -228,  82,    21, -220,  105,   22, -221,  165,   23, -209,  120,   24, -213,  120,
    25, -201,  780,   26, -161,  3008,  27, 0,     5394
};

cKF_Animation_R_c cKF_ba_r_tol_balloon1_gyaza1 = { cKF_ckcb_r_tol_balloon1_gyaza1_tbl,
                                                   cKF_ds_tol_balloon1_gyaza1_tbl,
                                                   cKF_kn_tol_balloon1_gyaza1_tbl,
                                                   cKF_c_tol_balloon1_gyaza1_tbl,
                                                   -1,
                                                   27 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_kaza_1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_kaza_1_pal[] = {
#include "assets/player_tool/tol_kaza_1_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_1_a_tex_txt[0x200];
#else
static u8 tol_kaza_1_a_tex_txt[] = {
#include "assets/player_tool/tol_kaza_1_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_1_c_tex_txt[0x200];
#else
static u8 tol_kaza_1_c_tex_txt[] = {
#include "assets/player_tool/tol_kaza_1_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_1_b_tex_txt[0x100];
#else
static u8 tol_kaza_1_b_tex_txt[] = {
#include "assets/player_tool/tol_kaza_1_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_kaza1_v[0x300 / sizeof(Vtx)];
#else
Vtx tol_kaza1_v[] = {
#include "assets/tol_kaza1_v.inc"
};
#endif

Gfx tol_kaza1_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_kaza_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_kaza_1_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_kaza1_v[44], 4, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 0, 2, 1, 3),
    gsSPNTriangles_5b(3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_kaza1_fan_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_kaza_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_1_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_kaza1_v, 24, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 2, 4, 0),
    gsSPNTriangles_5b(5, 6, 7, 8, 5, 7, 7, 9, 8, 10, 11, 12),
    gsSPNTriangles_5b(13, 10, 12, 12, 14, 13, 15, 16, 17, 17, 18, 15),
    gsSPNTriangles_5b(18, 19, 15, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_1_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&tol_kaza1_v[24], 20, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(3, 5, 4, 6, 7, 8, 6, 8, 0, 9, 6, 0),
    gsSPNTriangles_5b(10, 9, 0, 2, 11, 10, 2, 10, 0, 2, 12, 11),
    gsSPNTriangles_5b(12, 13, 11, 13, 14, 11, 13, 15, 14, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 10, 19, 16, 10, 11, 19, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_kaza1_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { tol_kaza1_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { tol_kaza1_fan_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2250, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_tol_kaza1 = { ARRAY_COUNT(cKF_je_r_tol_kaza1_tbl), 2, cKF_je_r_tol_kaza1_tbl };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_kaza_2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_kaza_2_pal[] = {
#include "assets/player_tool/tol_kaza_2_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_2_a_tex_txt[0x200];
#else
static u8 tol_kaza_2_a_tex_txt[] = {
#include "assets/player_tool/tol_kaza_2_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_2_c_tex_txt[0x200];
#else
static u8 tol_kaza_2_c_tex_txt[] = {
#include "assets/player_tool/tol_kaza_2_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_2_b_tex_txt[0x100];
#else
static u8 tol_kaza_2_b_tex_txt[] = {
#include "assets/player_tool/tol_kaza_2_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_kaza2_v[0x300 / sizeof(Vtx)];
#else
Vtx tol_kaza2_v[] = {
#include "assets/tol_kaza2_v.inc"
};
#endif

Gfx tol_kaza2_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_kaza_2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_kaza_2_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_kaza2_v[44], 4, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 0, 2, 1, 3),
    gsSPNTriangles_5b(3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_kaza2_fan_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_kaza_2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_2_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_kaza2_v, 24, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 2, 4, 0),
    gsSPNTriangles_5b(5, 6, 7, 8, 5, 7, 7, 9, 8, 10, 11, 12),
    gsSPNTriangles_5b(13, 10, 12, 12, 14, 13, 15, 16, 17, 17, 18, 15),
    gsSPNTriangles_5b(18, 19, 15, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_2_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&tol_kaza2_v[24], 20, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(3, 5, 4, 6, 7, 8, 6, 8, 0, 9, 6, 0),
    gsSPNTriangles_5b(10, 9, 0, 2, 11, 10, 2, 10, 0, 2, 12, 11),
    gsSPNTriangles_5b(12, 13, 11, 13, 14, 11, 13, 15, 14, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 10, 19, 16, 10, 11, 19, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_kaza2_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { tol_kaza2_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { tol_kaza2_fan_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2250, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_tol_kaza2 = { ARRAY_COUNT(cKF_je_r_tol_kaza2_tbl), 2, cKF_je_r_tol_kaza2_tbl };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_kaza_3_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_kaza_3_pal[] = {
#include "assets/player_tool/tol_kaza_3_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_3_a_tex_txt[0x200];
#else
static u8 tol_kaza_3_a_tex_txt[] = {
#include "assets/player_tool/tol_kaza_3_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_3_c_tex_txt[0x200];
#else
static u8 tol_kaza_3_c_tex_txt[] = {
#include "assets/player_tool/tol_kaza_3_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_3_b_tex_txt[0x100];
#else
static u8 tol_kaza_3_b_tex_txt[] = {
#include "assets/player_tool/tol_kaza_3_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_kaza3_v[0x300 / sizeof(Vtx)];
#else
Vtx tol_kaza3_v[] = {
#include "assets/tol_kaza3_v.inc"
};
#endif

Gfx tol_kaza3_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_kaza_3_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_kaza_3_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_kaza3_v[44], 4, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 0, 2, 1, 3),
    gsSPNTriangles_5b(3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_kaza3_fan_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_kaza_3_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_3_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_kaza3_v, 24, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 2, 4, 0),
    gsSPNTriangles_5b(5, 6, 7, 8, 5, 7, 7, 9, 8, 10, 11, 12),
    gsSPNTriangles_5b(13, 10, 12, 12, 14, 13, 15, 16, 17, 17, 18, 15),
    gsSPNTriangles_5b(18, 19, 15, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_3_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&tol_kaza3_v[24], 20, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(3, 5, 4, 6, 7, 8, 6, 8, 0, 9, 6, 0),
    gsSPNTriangles_5b(10, 9, 0, 2, 11, 10, 2, 10, 0, 2, 12, 11),
    gsSPNTriangles_5b(12, 13, 11, 13, 14, 11, 13, 15, 14, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 10, 19, 16, 10, 11, 19, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_kaza3_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { tol_kaza3_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { tol_kaza3_fan_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2250, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_tol_kaza3 = { ARRAY_COUNT(cKF_je_r_tol_kaza3_tbl), 2, cKF_je_r_tol_kaza3_tbl };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_kaza_4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_kaza_4_pal[] = {
#include "assets/player_tool/tol_kaza_4_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_4_a_tex_txt[0x200];
#else
static u8 tol_kaza_4_a_tex_txt[] = {
#include "assets/player_tool/tol_kaza_4_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_4_c_tex_txt[0x200];
#else
static u8 tol_kaza_4_c_tex_txt[] = {
#include "assets/player_tool/tol_kaza_4_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_4_b_tex_txt[0x100];
#else
static u8 tol_kaza_4_b_tex_txt[] = {
#include "assets/player_tool/tol_kaza_4_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_kaza4_v[0x300 / sizeof(Vtx)];
#else
Vtx tol_kaza4_v[] = {
#include "assets/tol_kaza4_v.inc"
};
#endif

Gfx tol_kaza4_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_kaza_4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_kaza_4_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_kaza4_v[44], 4, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 0, 2, 1, 3),
    gsSPNTriangles_5b(3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_kaza4_fan_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_kaza_4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_4_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_kaza4_v, 24, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 2, 4, 0),
    gsSPNTriangles_5b(5, 6, 7, 8, 5, 7, 7, 9, 8, 10, 11, 12),
    gsSPNTriangles_5b(13, 10, 12, 12, 14, 13, 15, 16, 17, 17, 18, 15),
    gsSPNTriangles_5b(18, 19, 15, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_4_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&tol_kaza4_v[24], 20, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(3, 5, 4, 6, 7, 8, 6, 8, 0, 9, 6, 0),
    gsSPNTriangles_5b(10, 9, 0, 2, 11, 10, 2, 10, 0, 2, 12, 11),
    gsSPNTriangles_5b(12, 13, 11, 13, 14, 11, 13, 15, 14, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 10, 19, 16, 10, 11, 19, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_kaza4_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { tol_kaza4_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { tol_kaza4_fan_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2250, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_tol_kaza4 = { ARRAY_COUNT(cKF_je_r_tol_kaza4_tbl), 2, cKF_je_r_tol_kaza4_tbl };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_kaza_5_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_kaza_5_pal[] = {
#include "assets/player_tool/tol_kaza_5_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_5_a_tex_txt[0x200];
#else
static u8 tol_kaza_5_a_tex_txt[] = {
#include "assets/player_tool/tol_kaza_5_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_5_c_tex_txt[0x200];
#else
static u8 tol_kaza_5_c_tex_txt[] = {
#include "assets/player_tool/tol_kaza_5_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_5_b_tex_txt[0x100];
#else
static u8 tol_kaza_5_b_tex_txt[] = {
#include "assets/player_tool/tol_kaza_5_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_kaza5_v[0x300 / sizeof(Vtx)];
#else
Vtx tol_kaza5_v[] = {
#include "assets/tol_kaza5_v.inc"
};
#endif

Gfx tol_kaza5_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_kaza_5_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_kaza_5_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_kaza5_v[44], 4, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 0, 2, 1, 3),
    gsSPNTriangles_5b(3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_kaza5_fan_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_kaza_5_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_5_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_kaza5_v, 24, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 2, 4, 0),
    gsSPNTriangles_5b(5, 6, 7, 8, 5, 7, 7, 9, 8, 10, 11, 12),
    gsSPNTriangles_5b(13, 10, 12, 12, 14, 13, 15, 16, 17, 17, 18, 15),
    gsSPNTriangles_5b(18, 19, 15, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_5_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&tol_kaza5_v[24], 20, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(3, 5, 4, 6, 7, 8, 6, 8, 0, 9, 6, 0),
    gsSPNTriangles_5b(10, 9, 0, 2, 11, 10, 2, 10, 0, 2, 12, 11),
    gsSPNTriangles_5b(12, 13, 11, 13, 14, 11, 13, 15, 14, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 10, 19, 16, 10, 11, 19, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_kaza5_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { tol_kaza5_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { tol_kaza5_fan_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2250, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_tol_kaza5 = { ARRAY_COUNT(cKF_je_r_tol_kaza5_tbl), 2, cKF_je_r_tol_kaza5_tbl };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_kaza_6_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_kaza_6_pal[] = {
#include "assets/player_tool/tol_kaza_6_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_6_a_tex_txt[0x200];
#else
static u8 tol_kaza_6_a_tex_txt[] = {
#include "assets/player_tool/tol_kaza_6_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_6_c_tex_txt[0x200];
#else
static u8 tol_kaza_6_c_tex_txt[] = {
#include "assets/player_tool/tol_kaza_6_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_6_b_tex_txt[0x100];
#else
static u8 tol_kaza_6_b_tex_txt[] = {
#include "assets/player_tool/tol_kaza_6_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_kaza6_v[0x300 / sizeof(Vtx)];
#else
Vtx tol_kaza6_v[] = {
#include "assets/tol_kaza6_v.inc"
};
#endif

Gfx tol_kaza6_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_kaza_6_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_kaza_6_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_kaza6_v[44], 4, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 0, 2, 1, 3),
    gsSPNTriangles_5b(3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_kaza6_fan_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_kaza_6_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_6_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_kaza6_v, 24, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 2, 4, 0),
    gsSPNTriangles_5b(5, 6, 7, 8, 5, 7, 7, 9, 8, 10, 11, 12),
    gsSPNTriangles_5b(13, 10, 12, 12, 14, 13, 15, 16, 17, 17, 18, 15),
    gsSPNTriangles_5b(18, 19, 15, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_6_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&tol_kaza6_v[24], 20, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(3, 5, 4, 6, 7, 8, 6, 8, 0, 9, 6, 0),
    gsSPNTriangles_5b(10, 9, 0, 2, 11, 10, 2, 10, 0, 2, 12, 11),
    gsSPNTriangles_5b(12, 13, 11, 13, 14, 11, 13, 15, 14, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 10, 19, 16, 10, 11, 19, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_kaza6_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { tol_kaza6_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { tol_kaza6_fan_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2250, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_tol_kaza6 = { ARRAY_COUNT(cKF_je_r_tol_kaza6_tbl), 2, cKF_je_r_tol_kaza6_tbl };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_kaza_7_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_kaza_7_pal[] = {
#include "assets/player_tool/tol_kaza_7_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_7_a_tex_txt[0x200];
#else
static u8 tol_kaza_7_a_tex_txt[] = {
#include "assets/player_tool/tol_kaza_7_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_7_c_tex_txt[0x200];
#else
static u8 tol_kaza_7_c_tex_txt[] = {
#include "assets/player_tool/tol_kaza_7_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_7_d_tex_txt[0x80];
#else
static u8 tol_kaza_7_d_tex_txt[] = {
#include "assets/player_tool/tol_kaza_7_d_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_7_b_tex_txt[0x100];
#else
static u8 tol_kaza_7_b_tex_txt[] = {
#include "assets/player_tool/tol_kaza_7_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_kaza7_v[0x980 / sizeof(Vtx)];
#else
Vtx tol_kaza7_v[] = {
#include "assets/tol_kaza7_v.inc"
};
#endif

Gfx tol_kaza7_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_kaza_7_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_kaza_7_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_kaza7_v[148], 4, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 0, 2, 1, 3),
    gsSPNTriangles_5b(3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_kaza7_fan_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_kaza_7_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_7_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_kaza7_v, 24, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 2, 4, 0),
    gsSPNTriangles_5b(5, 6, 7, 8, 5, 7, 7, 9, 8, 10, 11, 12),
    gsSPNTriangles_5b(13, 10, 12, 12, 14, 13, 15, 16, 17, 17, 18, 15),
    gsSPNTriangles_5b(18, 19, 15, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_7_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tol_kaza7_v[24], 28, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(3, 5, 4, 6, 7, 8, 6, 8, 0, 9, 6, 0),
    gsSPNTriangles_5b(10, 9, 0, 2, 11, 10, 2, 10, 0, 2, 12, 11),
    gsSPNTriangles_5b(12, 13, 11, 13, 14, 11, 13, 15, 14, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 10, 19, 16, 10, 11, 19, 10, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, tol_kaza_7_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 23, 21, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 27, 25, 0, 0, 0),
    gsSPVertex(&tol_kaza7_v[52], 24, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 7, 5, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 11, 9, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 15, 13, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 19, 17, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 23, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_7_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_kaza7_v[76], 20, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 1, 3, 2, 2, 4, 0),
    gsSPNTriangles_5b(5, 6, 7, 8, 5, 7, 7, 9, 8, 10, 11, 12),
    gsSPNTriangles_5b(13, 10, 12, 12, 14, 13, 15, 16, 17, 17, 18, 15),
    gsSPNTriangles_5b(18, 19, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_7_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&tol_kaza7_v[96], 28, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 7, 8, 6, 7, 9, 8, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 4, 13, 10, 4, 2, 13, 4, 6, 0, 2),
    gsSPNTriangles_5b(6, 2, 4, 6, 14, 0, 14, 15, 0, 15, 16, 0),
    gsSPNTriangles_5b(15, 17, 16, 3, 18, 19, 3, 19, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, tol_kaza_7_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 23, 21, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 27, 25, 0, 0, 0),
    gsSPVertex(&tol_kaza7_v[124], 24, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 7, 5, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 11, 9, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 15, 13, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 19, 17, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 23, 21, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_kaza7_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { tol_kaza7_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { tol_kaza7_fan_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2250, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_tol_kaza7 = { ARRAY_COUNT(cKF_je_r_tol_kaza7_tbl), 2, cKF_je_r_tol_kaza7_tbl };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_kaza_8_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_kaza_8_pal[] = {
#include "assets/player_tool/tol_kaza_8_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_8_d_tex_txt[0x80];
#else
static u8 tol_kaza_8_d_tex_txt[] = {
#include "assets/player_tool/tol_kaza_8_d_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_8_a_tex_txt[0x200];
#else
static u8 tol_kaza_8_a_tex_txt[] = {
#include "assets/player_tool/tol_kaza_8_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_8_c_tex_txt[0x200];
#else
static u8 tol_kaza_8_c_tex_txt[] = {
#include "assets/player_tool/tol_kaza_8_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_8_e_tex_txt[0x80];
#else
static u8 tol_kaza_8_e_tex_txt[] = {
#include "assets/player_tool/tol_kaza_8_e_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_8_b_tex_txt[0x100];
#else
static u8 tol_kaza_8_b_tex_txt[] = {
#include "assets/player_tool/tol_kaza_8_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_kaza8_v[0x780 / sizeof(Vtx)];
#else
Vtx tol_kaza8_v[] = {
#include "assets/tol_kaza8_v.inc"
};
#endif

Gfx tol_kaza8_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_kaza_8_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_kaza_8_b_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_kaza8_v[116], 4, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 0, 2, 1, 3),
    gsSPNTriangles_5b(3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx tol_kaza8_fan_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_kaza_8_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, tol_kaza_8_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_kaza8_v, 24, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_8_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(12, 4, 5, 6, 5, 7, 6, 6, 8, 4),
    gsSPNTriangles_5b(9, 10, 11, 12, 9, 11, 11, 13, 12, 14, 15, 16),
    gsSPNTriangles_5b(17, 14, 16, 16, 18, 17, 19, 20, 21, 21, 22, 19),
    gsSPNTriangles_5b(22, 23, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_8_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&tol_kaza8_v[24], 28, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 7, 8, 6, 7, 9, 8, 10, 11, 12),
    gsSPNTriangles_5b(10, 12, 4, 13, 10, 4, 2, 13, 4, 6, 0, 2),
    gsSPNTriangles_5b(6, 2, 4, 6, 14, 0, 14, 15, 0, 15, 16, 0),
    gsSPNTriangles_5b(15, 17, 16, 3, 18, 19, 3, 19, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, tol_kaza_8_d_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 23, 21, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 27, 25, 0, 0, 0),
    gsSPVertex(&tol_kaza8_v[52], 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, tol_kaza_8_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 7, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_8_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tol_kaza8_v[60], 24, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 2, 4, 0),
    gsSPNTriangles_5b(5, 6, 7, 8, 5, 7, 7, 9, 8, 10, 11, 12),
    gsSPNTriangles_5b(13, 10, 12, 12, 14, 13, 15, 16, 17, 17, 18, 15),
    gsSPNTriangles_5b(18, 19, 15, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_8_c_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&tol_kaza8_v[84], 28, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(3, 5, 4, 6, 7, 8, 6, 8, 0, 9, 6, 0),
    gsSPNTriangles_5b(10, 9, 0, 2, 11, 10, 2, 10, 0, 2, 12, 11),
    gsSPNTriangles_5b(12, 13, 11, 13, 14, 11, 13, 15, 14, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 10, 19, 16, 10, 11, 19, 10, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, tol_kaza_8_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 23, 21, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 27, 25, 0, 0, 0),
    gsSPVertex(&tol_kaza8_v[112], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_tol_kaza8_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { tol_kaza8_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                           { tol_kaza8_fan_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2250, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_tol_kaza8 = { ARRAY_COUNT(cKF_je_r_tol_kaza8_tbl), 2, cKF_je_r_tol_kaza8_tbl };

u8 cKF_ckcb_r_tol_kaza1_wait_tbl[] = { 56, 7, 7 };

s16 cKF_kn_tol_kaza1_wait_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2 };

s16 cKF_c_tol_kaza1_wait_tbl[] = { 0, 0, 0 };

s16 cKF_ds_tol_kaza1_wait_tbl[] = { 1, 0, 0, 361, 0, 0, 1, 0,    0, 361, 0,    0, 1, 0, 0,   361, 0,    0,
                                    1, 0, 0, 361, 0, 0, 1, -900, 0, 361, -900, 0, 1, 0, 0,   361, 0,    0,
                                    1, 0, 0, 361, 0, 0, 1, 0,    0, 361, 0,    0, 1, 0, 300, 361, 3600, 300 };

cKF_Animation_R_c cKF_ba_r_tol_kaza1_wait = { cKF_ckcb_r_tol_kaza1_wait_tbl,
                                              cKF_ds_tol_kaza1_wait_tbl,
                                              cKF_kn_tol_kaza1_wait_tbl,
                                              cKF_c_tol_kaza1_wait_tbl,
                                              -1,
                                              361 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_fan1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_fan1_pal[] = {
#include "assets/player_tool/tol_fan1_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_fan1_tex_txt[0x400];
#else
static u8 tol_fan1_tex_txt[] = {
#include "assets/player_tool/tol_fan1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_fan1_v[0x80 / sizeof(Vtx)];
#else
Vtx tol_fan1_v[] = {
#include "assets/tol_fan1_v.inc"
};
#endif

Gfx tol_fan1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_fan1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, tol_fan1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_fan1_v, 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_fan2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_fan2_pal[] = {
#include "assets/player_tool/tol_fan2_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_fan2_tex_txt[0x400];
#else
static u8 tol_fan2_tex_txt[] = {
#include "assets/player_tool/tol_fan2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_fan2_v[0x80 / sizeof(Vtx)];
#else
Vtx tol_fan2_v[] = {
#include "assets/tol_fan2_v.inc"
};
#endif

Gfx tol_fan2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_fan2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, tol_fan2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_fan2_v, 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_fan3_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_fan3_pal[] = {
#include "assets/player_tool/tol_fan3_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_fan3_tex_txt[0x400];
#else
static u8 tol_fan3_tex_txt[] = {
#include "assets/player_tool/tol_fan3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_fan3_v[0x80 / sizeof(Vtx)];
#else
Vtx tol_fan3_v[] = {
#include "assets/tol_fan3_v.inc"
};
#endif

Gfx tol_fan3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_fan3_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, tol_fan3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_fan3_v, 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_fan4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_fan4_pal[] = {
#include "assets/player_tool/tol_fan4_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_fan4_tex_txt[0x400];
#else
static u8 tol_fan4_tex_txt[] = {
#include "assets/player_tool/tol_fan4_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_fan4_v[0x80 / sizeof(Vtx)];
#else
Vtx tol_fan4_v[] = {
#include "assets/tol_fan4_v.inc"
};
#endif

Gfx tol_fan4_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_fan4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, tol_fan4_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_fan4_v, 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_fan5_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_fan5_pal[] = {
#include "assets/player_tool/tol_fan5_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_fan5_tex_txt[0x400];
#else
static u8 tol_fan5_tex_txt[] = {
#include "assets/player_tool/tol_fan5_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_fan5_v[0x80 / sizeof(Vtx)];
#else
Vtx tol_fan5_v[] = {
#include "assets/tol_fan5_v.inc"
};
#endif

Gfx tol_fan5_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_fan5_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, tol_fan5_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_fan5_v, 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_fan6_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_fan6_pal[] = {
#include "assets/player_tool/tol_fan6_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_fan6_tex_txt[0x400];
#else
static u8 tol_fan6_tex_txt[] = {
#include "assets/player_tool/tol_fan6_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_fan6_v[0x280 / sizeof(Vtx)];
#else
Vtx tol_fan6_v[] = {
#include "assets/tol_fan6_v.inc"
};
#endif

Gfx tol_fan6_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_fan6_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, tol_fan6_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_fan6_v, 20, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 2, 18, 0),
    gsSPNTriangles_5b(5, 19, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&tol_fan6_v[20], 20, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 2, 18, 0),
    gsSPNTriangles_5b(5, 19, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_fan7_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_fan7_pal[] = {
#include "assets/player_tool/tol_fan7_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_fan7_tex_txt[0x400];
#else
static u8 tol_fan7_tex_txt[] = {
#include "assets/player_tool/tol_fan7_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_fan7_v[0x80 / sizeof(Vtx)];
#else
Vtx tol_fan7_v[] = {
#include "assets/tol_fan7_v.inc"
};
#endif

Gfx tol_fan7_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_fan7_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, tol_fan7_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_fan7_v, 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_fan8_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_fan8_pal[] = {
#include "assets/player_tool/tol_fan8_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_fan8_tex_txt[0x400];
#else
static u8 tol_fan8_tex_txt[] = {
#include "assets/player_tool/tol_fan8_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_fan8_v[0x80 / sizeof(Vtx)];
#else
Vtx tol_fan8_v[] = {
#include "assets/tol_fan8_v.inc"
};
#endif

Gfx tol_fan8_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_fan8_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, tol_fan8_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(tol_fan8_v, 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_player_tool_c(void) {
    pc_load_asset("assets/player_tool/tol_sao_1_pal.bin", tol_sao_1_pal, 0x20, 0x8DED60, 0, 1);
    pc_load_asset("assets/player_tool/tol_sao_2_pal.bin", tol_sao_2_pal, 0x20, 0x8DF0A0, 0, 1);
    pc_load_asset("assets/player_tool/tol_balloon1_wire_tex_txt.bin", tol_balloon1_wire_tex_txt, 0x80, 0xBCBD80, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_1_pal.bin", tol_kaza_1_pal, 0x20, 0x66CFE0, 0, 1);
    pc_load_asset("assets/player_tool/tol_kaza_1_a_tex_txt.bin", tol_kaza_1_a_tex_txt, 0x200, 0x66D100, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_1_c_tex_txt.bin", tol_kaza_1_c_tex_txt, 0x200, 0x66D300, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_1_b_tex_txt.bin", tol_kaza_1_b_tex_txt, 0x100, 0x66D000, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_2_pal.bin", tol_kaza_2_pal, 0x20, 0x66D960, 0, 1);
    pc_load_asset("assets/player_tool/tol_kaza_2_a_tex_txt.bin", tol_kaza_2_a_tex_txt, 0x200, 0x66D980, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_2_c_tex_txt.bin", tol_kaza_2_c_tex_txt, 0x200, 0x66DB80, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_2_b_tex_txt.bin", tol_kaza_2_b_tex_txt, 0x100, 0x66DD80, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_3_pal.bin", tol_kaza_3_pal, 0x20, 0x66E2E0, 0, 1);
    pc_load_asset("assets/player_tool/tol_kaza_3_a_tex_txt.bin", tol_kaza_3_a_tex_txt, 0x200, 0x66E300, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_3_c_tex_txt.bin", tol_kaza_3_c_tex_txt, 0x200, 0x66E500, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_3_b_tex_txt.bin", tol_kaza_3_b_tex_txt, 0x100, 0x66E700, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_4_pal.bin", tol_kaza_4_pal, 0x20, 0x66EC60, 0, 1);
    pc_load_asset("assets/player_tool/tol_kaza_4_a_tex_txt.bin", tol_kaza_4_a_tex_txt, 0x200, 0x66EC80, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_4_c_tex_txt.bin", tol_kaza_4_c_tex_txt, 0x200, 0x66EE80, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_4_b_tex_txt.bin", tol_kaza_4_b_tex_txt, 0x100, 0x66F080, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_5_pal.bin", tol_kaza_5_pal, 0x20, 0x66F5E0, 0, 1);
    pc_load_asset("assets/player_tool/tol_kaza_5_a_tex_txt.bin", tol_kaza_5_a_tex_txt, 0x200, 0x66F600, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_5_c_tex_txt.bin", tol_kaza_5_c_tex_txt, 0x200, 0x66F800, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_5_b_tex_txt.bin", tol_kaza_5_b_tex_txt, 0x100, 0x66FA00, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_6_pal.bin", tol_kaza_6_pal, 0x20, 0x66FF60, 0, 1);
    pc_load_asset("assets/player_tool/tol_kaza_6_a_tex_txt.bin", tol_kaza_6_a_tex_txt, 0x200, 0x66FF80, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_6_c_tex_txt.bin", tol_kaza_6_c_tex_txt, 0x200, 0x670180, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_6_b_tex_txt.bin", tol_kaza_6_b_tex_txt, 0x100, 0x670380, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_7_pal.bin", tol_kaza_7_pal, 0x20, 0x6708E0, 0, 1);
    pc_load_asset("assets/player_tool/tol_kaza_7_a_tex_txt.bin", tol_kaza_7_a_tex_txt, 0x200, 0x670900, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_7_c_tex_txt.bin", tol_kaza_7_c_tex_txt, 0x200, 0x670B00, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_7_d_tex_txt.bin", tol_kaza_7_d_tex_txt, 0x80, 0x670D00, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_7_b_tex_txt.bin", tol_kaza_7_b_tex_txt, 0x100, 0x670D80, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_8_pal.bin", tol_kaza_8_pal, 0x20, 0x671A40, 0, 1);
    pc_load_asset("assets/player_tool/tol_kaza_8_d_tex_txt.bin", tol_kaza_8_d_tex_txt, 0x80, 0x671A60, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_8_a_tex_txt.bin", tol_kaza_8_a_tex_txt, 0x200, 0x671AE0, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_8_c_tex_txt.bin", tol_kaza_8_c_tex_txt, 0x200, 0x671CE0, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_8_e_tex_txt.bin", tol_kaza_8_e_tex_txt, 0x80, 0x671EE0, 0, 0);
    pc_load_asset("assets/player_tool/tol_kaza_8_b_tex_txt.bin", tol_kaza_8_b_tex_txt, 0x100, 0x671F60, 0, 0);
    pc_load_asset("assets/player_tool/tol_fan1_pal.bin", tol_fan1_pal, 0x20, 0x678D60, 0, 1);
    pc_load_asset("assets/player_tool/tol_fan1_tex_txt.bin", tol_fan1_tex_txt, 0x400, 0x678D80, 0, 0);
    pc_load_asset("assets/player_tool/tol_fan2_pal.bin", tol_fan2_pal, 0x20, 0x679280, 0, 1);
    pc_load_asset("assets/player_tool/tol_fan2_tex_txt.bin", tol_fan2_tex_txt, 0x400, 0x6792A0, 0, 0);
    pc_load_asset("assets/player_tool/tol_fan3_pal.bin", tol_fan3_pal, 0x20, 0x6797A0, 0, 1);
    pc_load_asset("assets/player_tool/tol_fan3_tex_txt.bin", tol_fan3_tex_txt, 0x400, 0x6797C0, 0, 0);
    pc_load_asset("assets/player_tool/tol_fan4_pal.bin", tol_fan4_pal, 0x20, 0x679CC0, 0, 1);
    pc_load_asset("assets/player_tool/tol_fan4_tex_txt.bin", tol_fan4_tex_txt, 0x400, 0x679CE0, 0, 0);
    pc_load_asset("assets/player_tool/tol_fan5_pal.bin", tol_fan5_pal, 0x20, 0x67A1E0, 0, 1);
    pc_load_asset("assets/player_tool/tol_fan5_tex_txt.bin", tol_fan5_tex_txt, 0x400, 0x67A200, 0, 0);
    pc_load_asset("assets/player_tool/tol_fan6_pal.bin", tol_fan6_pal, 0x20, 0x67A700, 0, 1);
    pc_load_asset("assets/player_tool/tol_fan6_tex_txt.bin", tol_fan6_tex_txt, 0x400, 0x67A720, 0, 0);
    pc_load_asset("assets/player_tool/tol_fan7_pal.bin", tol_fan7_pal, 0x20, 0x67AC20, 0, 1);
    pc_load_asset("assets/player_tool/tol_fan7_tex_txt.bin", tol_fan7_tex_txt, 0x400, 0x67AC40, 0, 0);
    pc_load_asset("assets/player_tool/tol_fan8_pal.bin", tol_fan8_pal, 0x20, 0x67B140, 0, 1);
    pc_load_asset("assets/player_tool/tol_fan8_tex_txt.bin", tol_fan8_tex_txt, 0x400, 0x67B160, 0, 0);
}
#endif
