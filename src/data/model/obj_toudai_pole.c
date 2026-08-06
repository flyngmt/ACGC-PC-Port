#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_toudai_pole_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_toudai_pole_pal[] = {
#include "assets/obj_toudai_pole_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_toudai_poleA_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_toudai_poleA_tex_pic_ci4_pal[] = {
#include "assets/obj_toudai_poleA_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_toudai_poleE_tex_txt[0x20];
#else
u8 obj_toudai_poleE_tex_txt[] = {
#include "assets/obj_toudai_poleE_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_toudai_pole_kage_txt[0x100];
#else
u8 obj_toudai_pole_kage_txt[] = {
#include "assets/obj_toudai_pole_kage_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_toudai_poleB_tex_txt[0x40];
#else
u8 obj_toudai_poleB_tex_txt[] = {
#include "assets/obj_toudai_poleB_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_toudai_poleC_tex_txt[0x200];
#else
u8 obj_toudai_poleC_tex_txt[] = {
#include "assets/obj_toudai_poleC_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_toudai_poleD_tex_txt[0x40];
#else
u8 obj_toudai_poleD_tex_txt[] = {
#include "assets/obj_toudai_poleD_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_toudai_poleA_tex_txt[0x40];
#else
u8 obj_toudai_poleA_tex_txt[] = {
#include "assets/obj_toudai_poleA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_toudai_pole_v[0x1630 / sizeof(Vtx)];
#else
Vtx obj_toudai_pole_v[] = {
#include "assets/obj_toudai_pole_v.inc"
};
#endif

Gfx obj_toudai_pole_kage_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 200, 0, 0, 0, 255),
    gsDPSetEnvColor(0, 0, 0, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, obj_toudai_pole_kage_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&obj_toudai_pole_v[126], 32, 0),
    gsSPNTrianglesInit_5b(32, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 5, 4, 6, 5, 6, 7, 7, 6, 8),
    gsSPNTriangles_5b(7, 8, 9, 9, 8, 10, 9, 10, 11, 11, 10, 12),
    gsSPNTriangles_5b(11, 12, 13, 13, 12, 14, 13, 14, 15, 15, 14, 1),
    gsSPNTriangles_5b(15, 1, 0, 16, 17, 18, 16, 18, 19, 19, 18, 20),
    gsSPNTriangles_5b(19, 20, 21, 21, 20, 22, 21, 22, 23, 23, 22, 24),
    gsSPNTriangles_5b(23, 24, 25, 25, 24, 26, 25, 26, 27, 27, 26, 28),
    gsSPNTriangles_5b(27, 28, 29, 29, 28, 30, 29, 30, 31, 31, 30, 17),
    gsSPNTriangles_5b(31, 17, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_toudai_pole_v[158], 32, 0),
    gsSPNTrianglesInit_5b(32, 0, 1, 2, 1, 3, 2, 4, 5, 0),
    gsSPNTriangles_5b(5, 1, 0, 6, 7, 4, 7, 5, 4, 2, 3, 6),
    gsSPNTriangles_5b(3, 7, 6, 8, 9, 10, 11, 8, 10, 9, 12, 13),
    gsSPNTriangles_5b(10, 9, 13, 12, 14, 15, 13, 12, 15, 14, 8, 11),
    gsSPNTriangles_5b(15, 14, 11, 16, 17, 18, 17, 19, 18, 20, 21, 16),
    gsSPNTriangles_5b(21, 17, 16, 22, 23, 20, 23, 21, 20, 18, 19, 22),
    gsSPNTriangles_5b(19, 23, 22, 24, 25, 26, 27, 24, 26, 25, 28, 29),
    gsSPNTriangles_5b(26, 25, 29, 28, 30, 31, 29, 28, 31, 30, 24, 27),
    gsSPNTriangles_5b(31, 30, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_toudai_pole_v[190], 16, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 5, 4, 6, 5, 6, 7, 7, 6, 8),
    gsSPNTriangles_5b(7, 8, 9, 9, 8, 10, 9, 10, 11, 11, 10, 12),
    gsSPNTriangles_5b(11, 12, 13, 13, 12, 14, 13, 14, 15, 15, 14, 1),
    gsSPNTriangles_5b(15, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_toudai_pole_evw_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED),
    gsDPSetEnvColor(100, 140, 190, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_toudai_poleA_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, obj_toudai_poleA_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 2, 1),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                         G_SHADING_SMOOTH),
    gsSPVertex(&obj_toudai_pole_v[46], 32, 0),
    gsSPNTrianglesInit_5b(32, 0, 1, 2, 0, 3, 1, 4, 3, 0),
    gsSPNTriangles_5b(4, 5, 3, 6, 5, 4, 6, 7, 5, 8, 7, 6),
    gsSPNTriangles_5b(8, 9, 7, 10, 9, 8, 10, 11, 9, 12, 11, 10),
    gsSPNTriangles_5b(12, 13, 11, 14, 13, 12, 14, 15, 13, 2, 15, 14),
    gsSPNTriangles_5b(2, 1, 15, 16, 17, 18, 17, 19, 18, 20, 21, 16),
    gsSPNTriangles_5b(21, 17, 16, 22, 23, 20, 23, 21, 20, 18, 19, 22),
    gsSPNTriangles_5b(19, 23, 22, 24, 25, 26, 27, 24, 26, 25, 28, 29),
    gsSPNTriangles_5b(26, 25, 29, 28, 30, 31, 29, 28, 31, 30, 24, 27),
    gsSPNTriangles_5b(31, 30, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_toudai_pole_v[78], 32, 0),
    gsSPNTrianglesInit_5b(32, 0, 1, 2, 1, 3, 2, 4, 5, 0),
    gsSPNTriangles_5b(5, 1, 0, 6, 7, 4, 7, 5, 4, 2, 3, 6),
    gsSPNTriangles_5b(3, 7, 6, 8, 9, 10, 11, 8, 10, 9, 12, 13),
    gsSPNTriangles_5b(10, 9, 13, 12, 14, 15, 13, 12, 15, 14, 8, 11),
    gsSPNTriangles_5b(15, 14, 11, 16, 17, 18, 16, 18, 19, 19, 18, 20),
    gsSPNTriangles_5b(19, 20, 21, 21, 20, 22, 21, 22, 23, 23, 22, 24),
    gsSPNTriangles_5b(23, 24, 25, 25, 24, 26, 25, 26, 27, 27, 26, 28),
    gsSPNTriangles_5b(27, 28, 29, 29, 28, 30, 29, 30, 31, 31, 30, 17),
    gsSPNTriangles_5b(31, 17, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_toudai_pole_v[110], 16, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 4, 3, 0),
    gsSPNTriangles_5b(4, 5, 3, 6, 5, 4, 6, 7, 5, 8, 7, 6),
    gsSPNTriangles_5b(8, 9, 7, 10, 9, 8, 10, 11, 9, 12, 11, 10),
    gsSPNTriangles_5b(12, 13, 11, 14, 13, 12, 14, 15, 13, 2, 15, 14),
    gsSPNTriangles_5b(2, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_toudai_poleE_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_toudai_pole_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, obj_toudai_poleE_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(obj_toudai_pole_v, 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 0, 5, 6, 0, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(27, 24, 26, 25, 28, 29, 26, 25, 29, 0, 0, 0),
    gsSPVertex(&obj_toudai_pole_v[30], 16, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 0, 2, 4, 0, 3),
    gsSPNTriangles_5b(5, 4, 3, 6, 7, 8, 9, 6, 8, 7, 10, 11),
    gsSPNTriangles_5b(8, 7, 11, 12, 6, 9, 13, 12, 9, 14, 12, 13),
    gsSPNTriangles_5b(15, 14, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_toudai_poleD1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_toudai_pole_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, obj_toudai_poleD_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&obj_toudai_pole_v[251], 18, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 2, 3, 4),
    gsSPNTriangles_5b(3, 5, 4, 6, 7, 8, 7, 9, 8, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 10, 11, 12, 11, 13, 12, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 10, 17, 11, 10, 8, 9, 16),
    gsSPNTriangles_5b(9, 17, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_toudai_poleC1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_toudai_pole_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_toudai_poleC_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&obj_toudai_pole_v[238], 13, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 2, 4, 5, 2),
    gsSPNTriangles_5b(6, 7, 2, 7, 8, 2, 2, 9, 10, 11, 2, 10),
    gsSPNTriangles_5b(12, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_toudai_poleB_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_toudai_pole_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, obj_toudai_poleB_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&obj_toudai_pole_v[206], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_toudai_poleD2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_toudai_pole_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, obj_toudai_poleD_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&obj_toudai_pole_v[316], 26, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 3, 1, 4, 2, 5),
    gsSPNTriangles_5b(4, 0, 2, 0, 6, 3, 6, 7, 3, 8, 9, 10),
    gsSPNTriangles_5b(8, 4, 9, 4, 5, 9, 11, 12, 13, 11, 14, 12),
    gsSPNTriangles_5b(14, 15, 12, 6, 16, 7, 6, 17, 16, 17, 18, 16),
    gsSPNTriangles_5b(14, 19, 15, 14, 20, 19, 20, 21, 19, 22, 23, 24),
    gsSPNTriangles_5b(22, 11, 23, 11, 13, 23, 20, 25, 21, 20, 8, 25),
    gsSPNTriangles_5b(8, 10, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_toudai_poleC2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_toudai_pole_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_toudai_poleC_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&obj_toudai_pole_v[342], 13, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 1),
    gsSPNTriangles_5b(5, 6, 1, 7, 8, 1, 8, 9, 1, 10, 11, 1),
    gsSPNTriangles_5b(11, 12, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_toudai_poleD3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_toudai_pole_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, obj_toudai_poleD_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&obj_toudai_pole_v[290], 26, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 9, 5, 8, 10, 4, 3),
    gsSPNTriangles_5b(10, 3, 11, 12, 10, 11, 13, 14, 15, 13, 15, 16),
    gsSPNTriangles_5b(17, 13, 16, 18, 12, 11, 18, 11, 7, 6, 18, 7),
    gsSPNTriangles_5b(19, 20, 21, 19, 21, 2, 1, 19, 2, 22, 17, 16),
    gsSPNTriangles_5b(22, 16, 23, 24, 23, 21, 20, 24, 21, 25, 22, 23),
    gsSPNTriangles_5b(24, 25, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_toudai_poleC3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_toudai_pole_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_toudai_poleC_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&obj_toudai_pole_v[269], 21, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(4, 5, 1, 6, 7, 1, 7, 8, 1, 8, 9, 1),
    gsSPNTriangles_5b(9, 10, 1, 11, 12, 1, 12, 13, 1, 13, 14, 1),
    gsSPNTriangles_5b(14, 15, 1, 16, 17, 1, 17, 18, 1, 18, 19, 1),
    gsSPNTriangles_5b(19, 20, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_obj_toudai_pole_tbl[] = { 0, 0, 0, 2, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0 };

s16 cKF_kn_obj_toudai_pole_tbl[] = { 2, 2, 2 };

s16 cKF_c_obj_toudai_pole_tbl[] = { 10000, 0, 16000, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1350, 0, 0, 0, 0, 0, 0, 0,
                                    -450,  0, 0,     0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_toudai_pole_tbl[] = { 1,   0,    1080, 100, 3600, 1080, 1,   0,    1080,
                                     100, 3600, 1080, 1,   0,    1080, 100, 3600, 1080 };

cKF_Animation_R_c cKF_ba_r_obj_toudai_pole = { cKF_ckcb_r_obj_toudai_pole_tbl,
                                               cKF_ds_obj_toudai_pole_tbl,
                                               cKF_kn_obj_toudai_pole_tbl,
                                               cKF_c_obj_toudai_pole_tbl,
                                               -1,
                                               100 };

cKF_Joint_R_c cKF_je_r_obj_toudai_pole_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 10000, 0, 16000 } },
    { NULL, 3, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 5500 } },
    { obj_toudai_poleC3_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_toudai_poleD3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 5500 } },
    { obj_toudai_poleC2_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_toudai_poleD2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_toudai_poleB_model, 5, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
    { obj_toudai_poleC1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_toudai_poleD1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_toudai_poleE_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_toudai_pole_evw_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_toudai_pole_kage_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_toudai_pole = { ARRAY_COUNT(cKF_je_r_obj_toudai_pole_tbl), 10,
                                              cKF_je_r_obj_toudai_pole_tbl };
