#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 obj_w_shrine_bubble_tex_pic_i4[];

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 obj_s_shrine_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 obj_s_shrine_pal[] = {
#include "assets/obj_s_shrine/obj_s_shrine_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shrine_t1_tex_txt[0x800];
#else
u8 obj_s_shrine_t1_tex_txt[] = {
#include "assets/obj_s_shrine_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shrine_t3_tex_txt[0x800];
#else
u8 obj_s_shrine_t3_tex_txt[] = {
#include "assets/obj_s_shrine_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shrine_t2_tex_txt[0x800];
#else
u8 obj_s_shrine_t2_tex_txt[] = {
#include "assets/obj_s_shrine_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shrine_t4_tex_txt[0x400];
#else
u8 obj_s_shrine_t4_tex_txt[] = {
#include "assets/obj_s_shrine_t4_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shrine_sprash_tex_pic_i4[0x100];
#else
u8 obj_s_shrine_sprash_tex_pic_i4[] = {
#include "assets/obj_s_shrine_sprash_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shrine_water_tex_pic_i4[0x100];
#else
u8 obj_s_shrine_water_tex_pic_i4[] = {
#include "assets/obj_s_shrine_water_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_shrine_wave_tex_pic_i4[0x100];
#else
u8 obj_s_shrine_wave_tex_pic_i4[] = {
#include "assets/obj_s_shrine_wave_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_shrine_v[0x2110 / sizeof(Vtx)];
#else
Vtx obj_s_shrine_v[] = {
#include "assets/obj_s_shrine_v.inc"
};
#endif

Gfx obj_s_shrine_water_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, TEXEL1_ALPHA, 0, TEXEL0, 0, TEXEL1, 0, PRIMITIVE, 0, SHADE, COMBINED, COMBINED, 0,
                       PRIM_LOD_FRAC, PRIMITIVE),
    gsDPSetPrimColor(0, 50, 0, 100, 255, 50),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, obj_s_shrine_wave_tex_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, obj_s_shrine_water_tex_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_6_mdl),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shrine_v[294], 32, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 3, 1, 0, 4, 0, 5),
    gsSPNTriangles_5b(6, 0, 4, 7, 8, 1, 1, 8, 9, 10, 4, 11),
    gsSPNTriangles_5b(12, 4, 10, 13, 10, 14, 15, 10, 13, 16, 17, 8),
    gsSPNTriangles_5b(8, 17, 18, 10, 15, 12, 13, 19, 15, 8, 7, 16),
    gsSPNTriangles_5b(1, 3, 7, 0, 6, 3, 4, 12, 6, 20, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 25, 26, 27, 28, 29, 27, 29, 21),
    gsSPNTriangles_5b(21, 29, 30, 31, 27, 21, 31, 21, 20, 0, 0, 0),
    gsSPVertex(&obj_s_shrine_v[326], 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(6, 5, 7, 8, 9, 10, 11, 12, 1, 11, 1, 0),
    gsSPNTriangles_5b(4, 13, 14, 4, 14, 5, 5, 14, 15, 16, 17, 9),
    gsSPNTriangles_5b(16, 9, 8, 1, 18, 19, 13, 11, 0, 13, 0, 14),
    gsSPNTriangles_5b(14, 0, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29),
    gsSPNTriangles_5b(30, 24, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_shrine_v[358], 11, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 4, 6, 7),
    gsSPNTriangles_5b(8, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shrine_trunk_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_shrine_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_shrine_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shrine_v[252], 32, 0),
    gsSPNTrianglesInit_5b(30, 0, 1, 2, 3, 4, 5, 4, 6, 5),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 9, 9, 12, 10, 8, 12, 9),
    gsSPNTriangles_5b(9, 11, 7, 11, 13, 7, 11, 14, 13, 14, 15, 13),
    gsSPNTriangles_5b(2, 16, 14, 3, 2, 14, 3, 14, 11, 17, 3, 11),
    gsSPNTriangles_5b(10, 18, 17, 17, 18, 4, 4, 3, 17, 11, 10, 17),
    gsSPNTriangles_5b(8, 7, 19, 19, 20, 8, 19, 7, 21, 7, 22, 21),
    gsSPNTriangles_5b(7, 13, 22, 13, 23, 22, 22, 24, 25, 26, 27, 28),
    gsSPNTriangles_5b(28, 29, 26, 27, 30, 28, 27, 31, 30, 0, 0, 0),
    gsSPVertex(&obj_s_shrine_v[284], 10, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(6, 8, 9, 9, 3, 5, 5, 6, 9, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shrine_statue_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_shrine_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_s_shrine_t4_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 178, 178, 178, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shrine_v[409], 32, 0),
    gsSPNTrianglesInit_5b(38, 0, 1, 2, 2, 1, 3, 2, 3, 4),
    gsSPNTriangles_5b(2, 4, 5, 0, 2, 6, 2, 5, 7, 2, 7, 8),
    gsSPNTriangles_5b(2, 8, 6, 0, 6, 1, 7, 5, 1, 1, 6, 8),
    gsSPNTriangles_5b(1, 8, 7, 9, 10, 11, 11, 10, 12, 9, 11, 13),
    gsSPNTriangles_5b(12, 14, 15, 13, 11, 15, 12, 15, 11, 9, 13, 16),
    gsSPNTriangles_5b(14, 17, 18, 19, 20, 21, 22, 20, 19, 23, 16, 24),
    gsSPNTriangles_5b(25, 26, 27, 20, 22, 28, 28, 22, 29, 27, 29, 22),
    gsSPNTriangles_5b(26, 28, 29, 26, 29, 27, 21, 20, 28, 21, 28, 26),
    gsSPNTriangles_5b(14, 18, 15, 30, 27, 19, 19, 27, 22, 24, 16, 13),
    gsSPNTriangles_5b(31, 13, 15, 13, 31, 24, 31, 15, 18, 0, 0, 0),
    gsSPVertex(&obj_s_shrine_v[441], 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 3, 4, 0, 3, 0, 2),
    gsSPNTriangles_5b(2, 1, 5, 6, 7, 8, 9, 10, 11, 6, 8, 12),
    gsSPNTriangles_5b(9, 11, 13, 6, 12, 14, 13, 11, 14, 13, 14, 12),
    gsSPNTriangles_5b(13, 12, 15, 2, 5, 16, 17, 18, 19, 19, 18, 20),
    gsSPNTriangles_5b(21, 22, 19, 21, 19, 20, 0, 4, 23, 23, 4, 24),
    gsSPNTriangles_5b(25, 26, 27, 28, 29, 30, 22, 21, 31, 0, 0, 0),
    gsSPVertex(&obj_s_shrine_v[473], 32, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 3, 2, 4, 2, 1, 5),
    gsSPNTriangles_5b(2, 5, 4, 6, 7, 8, 9, 10, 11, 11, 10, 12),
    gsSPNTriangles_5b(13, 14, 15, 9, 11, 14, 14, 11, 15, 5, 1, 16),
    gsSPNTriangles_5b(16, 1, 17, 14, 13, 18, 19, 20, 21, 19, 21, 22),
    gsSPNTriangles_5b(17, 23, 16, 24, 25, 26, 10, 9, 27, 9, 14, 27),
    gsSPNTriangles_5b(14, 18, 28, 27, 14, 29, 29, 14, 28, 10, 22, 21),
    gsSPNTriangles_5b(10, 21, 12, 30, 31, 6, 6, 8, 30, 0, 0, 0),
    gsSPVertex(&obj_s_shrine_v[505], 24, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 2, 4, 3),
    gsSPNTriangles_5b(5, 6, 7, 7, 8, 5, 9, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(11, 15, 16, 11, 10, 15, 17, 11, 16, 14, 13, 18),
    gsSPNTriangles_5b(8, 19, 5, 20, 5, 19, 5, 20, 6, 6, 20, 19),
    gsSPNTriangles_5b(21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shrine_sprash_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, TEXEL1_ALPHA, 0, TEXEL0, 0, TEXEL1, 0, PRIMITIVE, 0, SHADE, COMBINED, COMBINED, 0,
                       PRIM_LOD_FRAC, 0),
    gsDPSetPrimColor(0, 120, 127, 160, 160, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, obj_s_shrine_sprash_tex_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, obj_s_shrine_water_tex_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_5_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_shrine_v, 18, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 1, 8, 11, 1, 11, 2, 16, 4, 7),
    gsSPNTriangles_5b(16, 7, 17, 9, 12, 15, 9, 15, 10, 13, 16, 17),
    gsSPNTriangles_5b(13, 17, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shrine_leaf_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_2_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_3_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shrine_v[227], 25, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 0, 2, 2, 1, 4),
    gsSPNTriangles_5b(3, 2, 4, 5, 6, 7, 6, 8, 7, 5, 9, 6),
    gsSPNTriangles_5b(9, 8, 6, 10, 11, 12, 13, 10, 12, 12, 11, 14),
    gsSPNTriangles_5b(13, 12, 14, 15, 16, 17, 16, 18, 17, 15, 19, 16),
    gsSPNTriangles_5b(19, 18, 16, 20, 21, 22, 21, 23, 22, 20, 22, 24),
    gsSPNTriangles_5b(22, 23, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shrine_figure_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_shrine_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_shrine_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 178, 178, 178, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shrine_v[369], 32, 0),
    gsSPNTrianglesInit_5b(29, 0, 1, 2, 0, 2, 3, 0, 4, 5),
    gsSPNTriangles_5b(0, 6, 4, 0, 7, 6, 0, 8, 7, 4, 6, 9),
    gsSPNTriangles_5b(4, 9, 10, 11, 12, 13, 11, 13, 14, 15, 16, 1),
    gsSPNTriangles_5b(15, 1, 17, 12, 8, 18, 12, 18, 13, 17, 19, 20),
    gsSPNTriangles_5b(17, 20, 15, 3, 21, 8, 3, 8, 0, 21, 22, 18),
    gsSPNTriangles_5b(21, 18, 8, 5, 1, 0, 23, 2, 1, 23, 1, 16),
    gsSPNTriangles_5b(24, 25, 26, 24, 26, 27, 28, 29, 30, 28, 30, 26),
    gsSPNTriangles_5b(31, 28, 26, 31, 26, 25, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_shrine_v[401], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shrine_bubble_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 180),
    gsDPSetEnvColor(80, 80, 80, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 64, obj_w_shrine_bubble_tex_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_4_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shrine_v[405], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_shrine_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_shrine_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_shrine_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 178, 178, 178, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_shrine_v[18], 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 1, 0, 3, 1, 3, 4),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 9, 10, 11, 9, 11, 12),
    gsSPNTriangles_5b(13, 14, 15, 13, 15, 16, 14, 13, 17, 18, 9, 12),
    gsSPNTriangles_5b(18, 12, 19, 20, 21, 22, 21, 20, 23, 21, 23, 24),
    gsSPNTriangles_5b(10, 25, 26, 10, 26, 11, 27, 28, 29, 27, 29, 30),
    gsSPNTriangles_5b(28, 27, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_shrine_v[50], 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 1, 0, 3, 1, 3, 4),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 9, 10, 11, 9, 11, 12),
    gsSPNTriangles_5b(13, 14, 15, 13, 15, 16, 14, 13, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 23, 24, 22, 24, 25, 23, 22, 26),
    gsSPNTriangles_5b(10, 5, 8, 10, 8, 11, 27, 28, 29, 27, 29, 30),
    gsSPNTriangles_5b(28, 27, 31, 15, 11, 8, 15, 8, 16, 0, 0, 0),
    gsSPVertex(&obj_s_shrine_v[82], 32, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 6, 7, 8, 5, 7, 5, 9, 10, 11, 8),
    gsSPNTriangles_5b(10, 8, 12, 13, 14, 15, 13, 15, 16, 17, 18, 14),
    gsSPNTriangles_5b(17, 14, 19, 20, 21, 18, 20, 18, 22, 23, 24, 25),
    gsSPNTriangles_5b(26, 24, 23, 26, 23, 27, 28, 29, 30, 28, 30, 31),
    gsSPVertex(&obj_s_shrine_v[114], 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 6, 5, 8, 9, 0, 3, 9, 3, 10),
    gsSPNTriangles_5b(11, 12, 13, 14, 12, 11, 14, 11, 15, 1, 16, 17),
    gsSPNTriangles_5b(1, 17, 2, 18, 19, 20, 18, 20, 21, 20, 19, 22),
    gsSPNTriangles_5b(23, 24, 25, 26, 24, 23, 26, 23, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_shrine_v[146], 32, 0),
    gsSPNTrianglesInit_5b(23, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 6, 5, 8, 9, 10, 11, 9, 11, 12),
    gsSPNTriangles_5b(13, 14, 15, 13, 15, 16, 15, 14, 17, 1, 18, 19),
    gsSPNTriangles_5b(1, 19, 2, 20, 21, 22, 20, 22, 23, 22, 21, 24),
    gsSPNTriangles_5b(23, 2, 19, 23, 19, 20, 7, 3, 2, 7, 2, 4),
    gsSPNTriangles_5b(25, 26, 3, 25, 3, 27, 28, 29, 26, 28, 26, 30),
    gsSPVertex(&obj_s_shrine_v[177], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 5, 8, 5, 10, 11, 12, 13),
    gsSPNTriangles_5b(11, 13, 9, 14, 15, 16, 14, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 23, 24, 22, 24, 25, 26, 27, 28),
    gsSPNTriangles_5b(26, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_shrine_v[207], 20, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 obj_w_shrine_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 obj_w_shrine_pal[] = {
#include "assets/obj_s_shrine/obj_w_shrine_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shrine_t1_tex_txt[0x800];
#else
u8 obj_w_shrine_t1_tex_txt[] = {
#include "assets/obj_w_shrine_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shrine_t3_tex_txt[0x800];
#else
u8 obj_w_shrine_t3_tex_txt[] = {
#include "assets/obj_w_shrine_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shrine_t2_tex_txt[0x800];
#else
u8 obj_w_shrine_t2_tex_txt[] = {
#include "assets/obj_w_shrine_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shrine_t4_tex_txt[0x400];
#else
u8 obj_w_shrine_t4_tex_txt[] = {
#include "assets/obj_w_shrine_t4_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shrine_bubble_tex_pic_i4[0x200];
#else
u8 obj_w_shrine_bubble_tex_pic_i4[] = {
#include "assets/obj_w_shrine_bubble_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shrine_sprash_tex_pic_i4[0x100];
#else
u8 obj_w_shrine_sprash_tex_pic_i4[] = {
#include "assets/obj_w_shrine_sprash_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shrine_water_tex_pic_i4[0x100];
#else
u8 obj_w_shrine_water_tex_pic_i4[] = {
#include "assets/obj_w_shrine_water_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_shrine_wave_tex_pic_i4[0x100];
#else
u8 obj_w_shrine_wave_tex_pic_i4[] = {
#include "assets/obj_w_shrine_wave_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_shrine_v[0x2110 / sizeof(Vtx)];
#else
Vtx obj_w_shrine_v[] = {
#include "assets/obj_w_shrine_v.inc"
};
#endif

Gfx obj_w_shrine_water_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, TEXEL1_ALPHA, 0, TEXEL0, 0, TEXEL1, 0, PRIMITIVE, 0, SHADE, COMBINED, COMBINED, 0,
                       PRIM_LOD_FRAC, PRIMITIVE),
    gsDPSetPrimColor(0, 50, 0, 100, 255, 50),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, obj_w_shrine_wave_tex_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, obj_w_shrine_water_tex_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_6_mdl),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shrine_v[294], 32, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 3, 1, 0, 4, 0, 5),
    gsSPNTriangles_5b(6, 0, 4, 7, 8, 1, 1, 8, 9, 10, 4, 11),
    gsSPNTriangles_5b(12, 4, 10, 13, 10, 14, 15, 10, 13, 16, 17, 8),
    gsSPNTriangles_5b(8, 17, 18, 10, 15, 12, 13, 19, 15, 8, 7, 16),
    gsSPNTriangles_5b(1, 3, 7, 0, 6, 3, 4, 12, 6, 20, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 25, 26, 27, 28, 29, 27, 29, 21),
    gsSPNTriangles_5b(21, 29, 30, 31, 27, 21, 31, 21, 20, 0, 0, 0),
    gsSPVertex(&obj_w_shrine_v[326], 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(6, 5, 7, 8, 9, 10, 11, 12, 1, 11, 1, 0),
    gsSPNTriangles_5b(4, 13, 14, 4, 14, 5, 5, 14, 15, 16, 17, 9),
    gsSPNTriangles_5b(16, 9, 8, 1, 18, 19, 13, 11, 0, 13, 0, 14),
    gsSPNTriangles_5b(14, 0, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29),
    gsSPNTriangles_5b(30, 24, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_shrine_v[358], 11, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 4, 6, 7),
    gsSPNTriangles_5b(8, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shrine_trunk_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_shrine_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_shrine_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shrine_v[252], 32, 0),
    gsSPNTrianglesInit_5b(30, 0, 1, 2, 3, 4, 5, 4, 6, 5),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 9, 9, 12, 10, 8, 12, 9),
    gsSPNTriangles_5b(9, 11, 7, 11, 13, 7, 11, 14, 13, 14, 15, 13),
    gsSPNTriangles_5b(2, 16, 14, 3, 2, 14, 3, 14, 11, 17, 3, 11),
    gsSPNTriangles_5b(10, 18, 17, 17, 18, 4, 4, 3, 17, 11, 10, 17),
    gsSPNTriangles_5b(8, 7, 19, 19, 20, 8, 19, 7, 21, 7, 22, 21),
    gsSPNTriangles_5b(7, 13, 22, 13, 23, 22, 22, 24, 25, 26, 27, 28),
    gsSPNTriangles_5b(28, 29, 26, 27, 30, 28, 27, 31, 30, 0, 0, 0),
    gsSPVertex(&obj_w_shrine_v[284], 10, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(6, 8, 9, 9, 3, 5, 5, 6, 9, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shrine_statue_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_shrine_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_w_shrine_t4_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 178, 178, 178, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shrine_v[409], 32, 0),
    gsSPNTrianglesInit_5b(38, 0, 1, 2, 2, 1, 3, 2, 3, 4),
    gsSPNTriangles_5b(2, 4, 5, 0, 2, 6, 2, 5, 7, 2, 7, 8),
    gsSPNTriangles_5b(2, 8, 6, 0, 6, 1, 7, 5, 1, 1, 6, 8),
    gsSPNTriangles_5b(1, 8, 7, 9, 10, 11, 11, 10, 12, 9, 11, 13),
    gsSPNTriangles_5b(12, 14, 15, 13, 11, 15, 12, 15, 11, 9, 13, 16),
    gsSPNTriangles_5b(14, 17, 18, 19, 20, 21, 22, 20, 19, 23, 16, 24),
    gsSPNTriangles_5b(25, 26, 27, 20, 22, 28, 28, 22, 29, 27, 29, 22),
    gsSPNTriangles_5b(26, 28, 29, 26, 29, 27, 21, 20, 28, 21, 28, 26),
    gsSPNTriangles_5b(14, 18, 15, 30, 27, 19, 19, 27, 22, 24, 16, 13),
    gsSPNTriangles_5b(31, 13, 15, 13, 31, 24, 31, 15, 18, 0, 0, 0),
    gsSPVertex(&obj_w_shrine_v[441], 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 3, 4, 0, 3, 0, 2),
    gsSPNTriangles_5b(2, 1, 5, 6, 7, 8, 9, 10, 11, 6, 8, 12),
    gsSPNTriangles_5b(9, 11, 13, 6, 12, 14, 13, 11, 14, 13, 14, 12),
    gsSPNTriangles_5b(13, 12, 15, 2, 5, 16, 17, 18, 19, 19, 18, 20),
    gsSPNTriangles_5b(21, 22, 19, 21, 19, 20, 0, 4, 23, 23, 4, 24),
    gsSPNTriangles_5b(25, 26, 27, 28, 29, 30, 22, 21, 31, 0, 0, 0),
    gsSPVertex(&obj_w_shrine_v[473], 32, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 3, 2, 4, 2, 1, 5),
    gsSPNTriangles_5b(2, 5, 4, 6, 7, 8, 9, 10, 11, 11, 10, 12),
    gsSPNTriangles_5b(13, 14, 15, 9, 11, 14, 14, 11, 15, 5, 1, 16),
    gsSPNTriangles_5b(16, 1, 17, 14, 13, 18, 19, 20, 21, 19, 21, 22),
    gsSPNTriangles_5b(17, 23, 16, 24, 25, 26, 10, 9, 27, 9, 14, 27),
    gsSPNTriangles_5b(14, 18, 28, 27, 14, 29, 29, 14, 28, 10, 22, 21),
    gsSPNTriangles_5b(10, 21, 12, 30, 31, 6, 6, 8, 30, 0, 0, 0),
    gsSPVertex(&obj_w_shrine_v[505], 24, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 2, 4, 3),
    gsSPNTriangles_5b(5, 6, 7, 7, 8, 5, 9, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(11, 15, 16, 11, 10, 15, 17, 11, 16, 14, 13, 18),
    gsSPNTriangles_5b(8, 19, 5, 20, 5, 19, 5, 20, 6, 6, 20, 19),
    gsSPNTriangles_5b(21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shrine_sprash_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, TEXEL1_ALPHA, 0, TEXEL0, 0, TEXEL1, 0, PRIMITIVE, 0, SHADE, COMBINED, COMBINED, 0,
                       PRIM_LOD_FRAC, 0),
    gsDPSetPrimColor(0, 120, 127, 160, 160, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, obj_w_shrine_sprash_tex_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, obj_w_shrine_water_tex_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_5_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_shrine_v, 18, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 1, 8, 11, 1, 11, 2, 16, 4, 7),
    gsSPNTriangles_5b(16, 7, 17, 9, 12, 15, 9, 15, 10, 13, 16, 17),
    gsSPNTriangles_5b(13, 17, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shrine_leaf_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_2_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_3_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shrine_v[227], 25, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 0, 2, 2, 1, 4),
    gsSPNTriangles_5b(3, 2, 4, 5, 6, 7, 6, 8, 7, 5, 9, 6),
    gsSPNTriangles_5b(9, 8, 6, 10, 11, 12, 13, 10, 12, 12, 11, 14),
    gsSPNTriangles_5b(13, 12, 14, 15, 16, 17, 16, 18, 17, 15, 19, 16),
    gsSPNTriangles_5b(19, 18, 16, 20, 21, 22, 21, 23, 22, 20, 22, 24),
    gsSPNTriangles_5b(22, 23, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shrine_figure_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_shrine_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_shrine_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 178, 178, 178, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shrine_v[369], 32, 0),
    gsSPNTrianglesInit_5b(29, 0, 1, 2, 0, 2, 3, 0, 4, 5),
    gsSPNTriangles_5b(0, 6, 4, 0, 7, 6, 0, 8, 7, 4, 6, 9),
    gsSPNTriangles_5b(4, 9, 10, 11, 12, 13, 11, 13, 14, 15, 16, 1),
    gsSPNTriangles_5b(15, 1, 17, 12, 8, 18, 12, 18, 13, 17, 19, 20),
    gsSPNTriangles_5b(17, 20, 15, 3, 21, 8, 3, 8, 0, 21, 22, 18),
    gsSPNTriangles_5b(21, 18, 8, 5, 1, 0, 23, 2, 1, 23, 1, 16),
    gsSPNTriangles_5b(24, 25, 26, 24, 26, 27, 28, 29, 30, 28, 30, 26),
    gsSPNTriangles_5b(31, 28, 26, 31, 26, 25, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_shrine_v[401], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shrine_bubble_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 180),
    gsDPSetEnvColor(80, 80, 80, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 64, obj_w_shrine_bubble_tex_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(anime_4_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shrine_v[405], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_shrine_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_shrine_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_shrine_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 178, 178, 178, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_shrine_v[18], 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 1, 0, 3, 1, 3, 4),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 9, 10, 11, 9, 11, 12),
    gsSPNTriangles_5b(13, 14, 15, 13, 15, 16, 14, 13, 17, 18, 9, 12),
    gsSPNTriangles_5b(18, 12, 19, 20, 21, 22, 21, 20, 23, 21, 23, 24),
    gsSPNTriangles_5b(10, 25, 26, 10, 26, 11, 27, 28, 29, 27, 29, 30),
    gsSPNTriangles_5b(28, 27, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_shrine_v[50], 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 1, 0, 3, 1, 3, 4),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 9, 10, 11, 9, 11, 12),
    gsSPNTriangles_5b(13, 14, 15, 13, 15, 16, 14, 13, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 23, 24, 22, 24, 25, 23, 22, 26),
    gsSPNTriangles_5b(10, 5, 8, 10, 8, 11, 27, 28, 29, 27, 29, 30),
    gsSPNTriangles_5b(28, 27, 31, 15, 11, 8, 15, 8, 16, 0, 0, 0),
    gsSPVertex(&obj_w_shrine_v[82], 32, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 6, 7, 8, 5, 7, 5, 9, 10, 11, 8),
    gsSPNTriangles_5b(10, 8, 12, 13, 14, 15, 13, 15, 16, 17, 18, 14),
    gsSPNTriangles_5b(17, 14, 19, 20, 21, 18, 20, 18, 22, 23, 24, 25),
    gsSPNTriangles_5b(26, 24, 23, 26, 23, 27, 28, 29, 30, 28, 30, 31),
    gsSPVertex(&obj_w_shrine_v[114], 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 6, 5, 8, 9, 0, 3, 9, 3, 10),
    gsSPNTriangles_5b(11, 12, 13, 14, 12, 11, 14, 11, 15, 1, 16, 17),
    gsSPNTriangles_5b(1, 17, 2, 18, 19, 20, 18, 20, 21, 20, 19, 22),
    gsSPNTriangles_5b(23, 24, 25, 26, 24, 23, 26, 23, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_shrine_v[146], 32, 0),
    gsSPNTrianglesInit_5b(23, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 6, 5, 8, 9, 10, 11, 9, 11, 12),
    gsSPNTriangles_5b(13, 14, 15, 13, 15, 16, 15, 14, 17, 1, 18, 19),
    gsSPNTriangles_5b(1, 19, 2, 20, 21, 22, 20, 22, 23, 22, 21, 24),
    gsSPNTriangles_5b(23, 2, 19, 23, 19, 20, 7, 3, 2, 7, 2, 4),
    gsSPNTriangles_5b(25, 26, 3, 25, 3, 27, 28, 29, 26, 28, 26, 30),
    gsSPVertex(&obj_w_shrine_v[177], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 5, 8, 5, 10, 11, 12, 13),
    gsSPNTriangles_5b(11, 13, 9, 14, 15, 16, 14, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 23, 24, 22, 24, 25, 26, 27, 28),
    gsSPNTriangles_5b(26, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_shrine_v[207], 20, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_s_shrine_c(void) {
    pc_load_asset("assets/obj_s_shrine/obj_s_shrine_pal.bin", obj_s_shrine_pal, 0x20, 0x86C0E0, 0, 1);
    pc_load_asset("assets/obj_s_shrine/obj_w_shrine_pal.bin", obj_w_shrine_pal, 0x20, 0x8707A0, 0, 1);
}
#endif
