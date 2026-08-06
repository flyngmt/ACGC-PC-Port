#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_douzou_dai_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_douzou_dai_tex_txt[] = {
#include "assets/obj_s_douzou_dai_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_name_tex_txt[0x80];
#else
u8 obj_s_douzou_name_tex_txt[] = {
#include "assets/obj_s_douzou_name_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_b1_tex_pic_i4[0x100];
#else
u8 obj_s_douzou_b1_tex_pic_i4[] = {
#include "assets/obj_s_douzou_b1_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_b2_tex_pic_i4[0x100];
#else
u8 obj_s_douzou_b2_tex_pic_i4[] = {
#include "assets/obj_s_douzou_b2_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_b3_tex_pic_i4[0x100];
#else
u8 obj_s_douzou_b3_tex_pic_i4[] = {
#include "assets/obj_s_douzou_b3_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_b4_tex_pic_i4[0x100];
#else
u8 obj_s_douzou_b4_tex_pic_i4[] = {
#include "assets/obj_s_douzou_b4_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_b5_tex_pic_i4[0x100];
#else
u8 obj_s_douzou_b5_tex_pic_i4[] = {
#include "assets/obj_s_douzou_b5_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_b6_tex_pic_i4[0x100];
#else
u8 obj_s_douzou_b6_tex_pic_i4[] = {
#include "assets/obj_s_douzou_b6_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_b7_tex_pic_i4[0x100];
#else
u8 obj_s_douzou_b7_tex_pic_i4[] = {
#include "assets/obj_s_douzou_b7_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_b8_tex_pic_i4[0x100];
#else
u8 obj_s_douzou_b8_tex_pic_i4[] = {
#include "assets/obj_s_douzou_b8_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_bm1_tex_pic_i4[0x80];
#else
u8 obj_s_douzou_bm1_tex_pic_i4[] = {
#include "assets/obj_s_douzou_bm1_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_bm2_tex_pic_i4[0x80];
#else
u8 obj_s_douzou_bm2_tex_pic_i4[] = {
#include "assets/obj_s_douzou_bm2_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_g1_tex_pic_i4[0x100];
#else
u8 obj_s_douzou_g1_tex_pic_i4[] = {
#include "assets/obj_s_douzou_g1_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_g2_tex_pic_i4[0x100];
#else
u8 obj_s_douzou_g2_tex_pic_i4[] = {
#include "assets/obj_s_douzou_g2_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_g3_tex_pic_i4[0x100];
#else
u8 obj_s_douzou_g3_tex_pic_i4[] = {
#include "assets/obj_s_douzou_g3_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_g4_tex_pic_i4[0x100];
#else
u8 obj_s_douzou_g4_tex_pic_i4[] = {
#include "assets/obj_s_douzou_g4_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_g5_tex_pic_i4[0x100];
#else
u8 obj_s_douzou_g5_tex_pic_i4[] = {
#include "assets/obj_s_douzou_g5_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_g6_tex_pic_i4[0x100];
#else
u8 obj_s_douzou_g6_tex_pic_i4[] = {
#include "assets/obj_s_douzou_g6_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_g8_tex_pic_i4[0x100];
#else
u8 obj_s_douzou_g8_tex_pic_i4[] = {
#include "assets/obj_s_douzou_g8_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_gm1_tex_pic_i4[0x80];
#else
u8 obj_s_douzou_gm1_tex_pic_i4[] = {
#include "assets/obj_s_douzou_gm1_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_gm2_tex_pic_i4[0x80];
#else
u8 obj_s_douzou_gm2_tex_pic_i4[] = {
#include "assets/obj_s_douzou_gm2_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_douzou_metal_tex_pic_i4[0x40];
#else
u8 obj_s_douzou_metal_tex_pic_i4[] = {
#include "assets/obj_s_douzou_metal_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_douzou_v[0x11B0 / sizeof(Vtx)];
#else
Vtx obj_s_douzou_v[] = {
#include "assets/obj_s_douzou_v.inc"
};
#endif

Gfx obj_s_douzou_name_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_douzou_name_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_douzou_v[279], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_douzou_dai_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, obj_s_douzou_dai_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_douzou_v[267], 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 1, 3, 4),
    gsSPNTriangles_5b(3, 5, 4, 3, 6, 7, 6, 8, 7, 9, 1, 10),
    gsSPNTriangles_5b(1, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_douzou_girl_mouth_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_douzou_v[123], 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 0, 2, 4, 3),
    gsSPNTriangles_5b(5, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_douzou_girl_face_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_douzou_v[116], 7, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 0, 2, 3, 2, 4),
    gsSPNTriangles_5b(0, 5, 1, 6, 3, 4, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_douzou_girl_model[] = {
    gsSPTexture(2700, 480, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 8, obj_s_douzou_metal_tex_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(obj_s_douzou_v, 32, 0),
    gsSPNTrianglesInit_5b(34, 0, 1, 2, 3, 4, 5, 6, 0, 7),
    gsSPNTriangles_5b(5, 8, 9, 0, 10, 7, 3, 5, 6, 2, 10, 0),
    gsSPNTriangles_5b(11, 8, 5, 12, 1, 0, 7, 10, 13, 5, 4, 11),
    gsSPNTriangles_5b(14, 4, 3, 4, 14, 15, 16, 12, 0, 5, 9, 17),
    gsSPNTriangles_5b(16, 0, 18, 3, 7, 13, 5, 17, 18, 14, 3, 13),
    gsSPNTriangles_5b(19, 15, 14, 19, 14, 13, 0, 6, 18, 6, 5, 18),
    gsSPNTriangles_5b(3, 6, 7, 20, 19, 13, 20, 13, 21, 13, 10, 21),
    gsSPNTriangles_5b(4, 15, 9, 10, 12, 21, 22, 23, 24, 25, 26, 27),
    gsSPNTriangles_5b(25, 27, 28, 25, 29, 30, 28, 29, 25, 0, 0, 0),
    gsSPVertex(&obj_s_douzou_v[31], 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 6, 8, 12, 10, 13, 8, 14, 15, 16),
    gsSPNTriangles_5b(9, 2, 10, 1, 0, 17, 2, 18, 0, 19, 15, 20),
    gsSPNTriangles_5b(21, 20, 15, 15, 22, 16, 22, 15, 19, 23, 24, 25),
    gsSPNTriangles_5b(26, 25, 27, 28, 23, 29, 25, 26, 23, 15, 14, 21),
    gsSPNTriangles_5b(30, 20, 25, 12, 8, 13, 24, 23, 28, 27, 31, 26),
    gsSPNTriangles_5b(11, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_douzou_v[63], 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 6, 8, 10, 7, 11, 3, 12, 4, 13, 14, 15),
    gsSPNTriangles_5b(13, 15, 16, 2, 17, 18, 2, 18, 0, 14, 19, 20),
    gsSPNTriangles_5b(21, 14, 20, 22, 23, 24, 25, 26, 27, 28, 27, 26),
    gsSPNTriangles_5b(21, 29, 14, 29, 16, 15, 29, 15, 14, 30, 8, 10),
    gsSPNTriangles_5b(2, 1, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_douzou_v[95], 21, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 6, 5, 8, 5, 4, 9, 10, 8, 11, 10, 9),
    gsSPNTriangles_5b(12, 11, 13, 12, 13, 14, 11, 9, 13, 7, 14, 15),
    gsSPNTriangles_5b(6, 7, 15, 4, 6, 15, 16, 17, 18, 8, 17, 9),
    gsSPNTriangles_5b(8, 4, 17, 4, 15, 19, 4, 19, 18, 17, 4, 18),
    gsSPNTriangles_5b(20, 13, 9, 20, 9, 16, 9, 17, 16, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_douzou_boy_mouth_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_douzou_v[262], 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPEndDisplayList(),
};

Gfx obj_s_douzou_boy_face_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_douzou_v[255], 7, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 2, 1, 3, 4, 2),
    gsSPNTriangles_5b(0, 2, 5, 2, 6, 5, 2, 4, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_douzou_boy_model[] = {
    gsSPTexture(2700, 480, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 8, obj_s_douzou_metal_tex_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_douzou_v[129], 32, 0),
    gsSPNTrianglesInit_5b(42, 0, 1, 2, 1, 3, 2, 3, 1, 4),
    gsSPNTriangles_5b(1, 5, 4, 6, 2, 7, 7, 2, 8, 8, 2, 3),
    gsSPNTriangles_5b(9, 4, 10, 3, 4, 9, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(10, 4, 17, 6, 0, 2, 4, 5, 17, 16, 12, 11),
    gsSPNTriangles_5b(18, 13, 12, 15, 19, 20, 16, 11, 14, 21, 22, 23),
    gsSPNTriangles_5b(24, 22, 21, 25, 18, 26, 27, 28, 26, 20, 21, 15),
    gsSPNTriangles_5b(1, 0, 16, 21, 20, 24, 19, 15, 14, 26, 28, 25),
    gsSPNTriangles_5b(12, 26, 18, 3, 9, 8, 12, 16, 0, 6, 27, 26),
    gsSPNTriangles_5b(6, 26, 12, 0, 6, 12, 17, 5, 15, 21, 23, 17),
    gsSPNTriangles_5b(21, 17, 15, 5, 1, 16, 15, 5, 16, 8, 29, 7),
    gsSPNTriangles_5b(30, 9, 10, 29, 8, 9, 29, 9, 30, 0, 0, 0),
    gsSPVertex(&obj_s_douzou_v[160], 32, 0),
    gsSPNTrianglesInit_5b(27, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 10, 8, 11, 7, 9, 12, 13, 14),
    gsSPNTriangles_5b(15, 14, 13, 16, 2, 17, 11, 9, 18, 9, 19, 18),
    gsSPNTriangles_5b(4, 20, 21, 4, 22, 20, 23, 8, 10, 23, 9, 8),
    gsSPNTriangles_5b(24, 25, 26, 27, 25, 28, 21, 5, 4, 16, 17, 29),
    gsSPNTriangles_5b(27, 12, 14, 26, 15, 30, 31, 17, 3, 24, 28, 25),
    gsSPNTriangles_5b(25, 14, 15, 30, 15, 13, 14, 25, 27, 15, 26, 25),
    gsSPVertex(&obj_s_douzou_v[192], 32, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 2, 3, 4, 5, 4, 6),
    gsSPNTriangles_5b(0, 2, 7, 5, 8, 4, 9, 10, 11, 12, 11, 13),
    gsSPNTriangles_5b(13, 11, 10, 13, 14, 12, 13, 15, 14, 16, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 22, 23, 24, 22, 25, 26, 26, 27, 23),
    gsSPNTriangles_5b(26, 23, 22, 28, 29, 30, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_douzou_v[223], 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 3, 4, 0, 2, 3, 0),
    gsSPNTriangles_5b(4, 3, 5, 4, 5, 6, 4, 6, 0, 7, 8, 9),
    gsSPNTriangles_5b(10, 11, 12, 13, 9, 14, 14, 15, 16, 17, 16, 15),
    gsSPNTriangles_5b(15, 10, 17, 18, 19, 8, 8, 7, 18, 9, 13, 7),
    gsSPNTriangles_5b(12, 17, 10, 6, 20, 21, 6, 5, 22, 6, 22, 20),
    gsSPNTriangles_5b(20, 23, 21, 21, 23, 24, 25, 26, 21, 25, 21, 24),
    gsSPNTriangles_5b(25, 24, 27, 24, 23, 28, 29, 24, 28, 30, 22, 5),
    gsSPNTriangles_5b(30, 5, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_obj_s_douzou_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_c_obj_s_douzou_tbl[] = { 0, 2800, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0,
                                 0, 0,    0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_obj_s_douzou = { cKF_ckcb_r_obj_s_douzou_tbl, NULL, NULL, cKF_c_obj_s_douzou_tbl, -1, 100 };

cKF_Joint_R_c cKF_je_r_obj_s_douzou_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 2800, 0 } },
    { obj_s_douzou_dai_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_douzou_boy_model, 5, cKF_JOINT_FLAG_DISP_OPA, { 270, 0, 0 } },
    { obj_s_douzou_boy_face_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_douzou_boy_mouth_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_douzou_girl_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_douzou_girl_face_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_douzou_girl_mouth_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_douzou_name_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_s_douzou = { ARRAY_COUNT(cKF_je_r_obj_s_douzou_tbl), 8, cKF_je_r_obj_s_douzou_tbl };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_w_douzou_dai_tex_txt[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 obj_w_douzou_dai_tex_txt[] = {
#include "assets/obj_w_douzou_dai_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_name_tex_txt[0x80];
#else
u8 obj_w_douzou_name_tex_txt[] = {
#include "assets/obj_w_douzou_name_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_b1_tex_pic_i4[0x100];
#else
u8 obj_w_douzou_b1_tex_pic_i4[] = {
#include "assets/obj_w_douzou_b1_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_b2_tex_pic_i4[0x100];
#else
u8 obj_w_douzou_b2_tex_pic_i4[] = {
#include "assets/obj_w_douzou_b2_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_b3_tex_pic_i4[0x100];
#else
u8 obj_w_douzou_b3_tex_pic_i4[] = {
#include "assets/obj_w_douzou_b3_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_b4_tex_pic_i4[0x100];
#else
u8 obj_w_douzou_b4_tex_pic_i4[] = {
#include "assets/obj_w_douzou_b4_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_b5_tex_pic_i4[0x100];
#else
u8 obj_w_douzou_b5_tex_pic_i4[] = {
#include "assets/obj_w_douzou_b5_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_b6_tex_pic_i4[0x100];
#else
u8 obj_w_douzou_b6_tex_pic_i4[] = {
#include "assets/obj_w_douzou_b6_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_b7_tex_pic_i4[0x100];
#else
u8 obj_w_douzou_b7_tex_pic_i4[] = {
#include "assets/obj_w_douzou_b7_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_b8_tex_pic_i4[0x100];
#else
u8 obj_w_douzou_b8_tex_pic_i4[] = {
#include "assets/obj_w_douzou_b8_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_bm1_tex_pic_i4[0x80];
#else
u8 obj_w_douzou_bm1_tex_pic_i4[] = {
#include "assets/obj_w_douzou_bm1_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_bm2_tex_pic_i4[0x80];
#else
u8 obj_w_douzou_bm2_tex_pic_i4[] = {
#include "assets/obj_w_douzou_bm2_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_g1_tex_pic_i4[0x100];
#else
u8 obj_w_douzou_g1_tex_pic_i4[] = {
#include "assets/obj_w_douzou_g1_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_g2_tex_pic_i4[0x100];
#else
u8 obj_w_douzou_g2_tex_pic_i4[] = {
#include "assets/obj_w_douzou_g2_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_g3_tex_pic_i4[0x100];
#else
u8 obj_w_douzou_g3_tex_pic_i4[] = {
#include "assets/obj_w_douzou_g3_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_g4_tex_pic_i4[0x100];
#else
u8 obj_w_douzou_g4_tex_pic_i4[] = {
#include "assets/obj_w_douzou_g4_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_g5_tex_pic_i4[0x100];
#else
u8 obj_w_douzou_g5_tex_pic_i4[] = {
#include "assets/obj_w_douzou_g5_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_g6_tex_pic_i4[0x100];
#else
u8 obj_w_douzou_g6_tex_pic_i4[] = {
#include "assets/obj_w_douzou_g6_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_g8_tex_pic_i4[0x100];
#else
u8 obj_w_douzou_g8_tex_pic_i4[] = {
#include "assets/obj_w_douzou_g8_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_gm1_tex_pic_i4[0x80];
#else
u8 obj_w_douzou_gm1_tex_pic_i4[] = {
#include "assets/obj_w_douzou_gm1_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_gm2_tex_pic_i4[0x80];
#else
u8 obj_w_douzou_gm2_tex_pic_i4[] = {
#include "assets/obj_w_douzou_gm2_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_douzou_metal_tex_pic_i4[0x40];
#else
u8 obj_w_douzou_metal_tex_pic_i4[] = {
#include "assets/obj_w_douzou_metal_tex_pic_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_douzou_v[0x11B0 / sizeof(Vtx)];
#else
Vtx obj_w_douzou_v[] = {
#include "assets/obj_w_douzou_v.inc"
};
#endif

Gfx obj_w_douzou_name_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_douzou_name_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_douzou_v[279], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_douzou_dai_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, obj_w_douzou_dai_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_douzou_v[267], 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 1, 3, 4),
    gsSPNTriangles_5b(3, 5, 4, 3, 6, 7, 6, 8, 7, 9, 1, 10),
    gsSPNTriangles_5b(1, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_douzou_girl_mouth_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_douzou_v[123], 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 0, 2, 4, 3),
    gsSPNTriangles_5b(5, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_douzou_girl_face_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_douzou_v[116], 7, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 0, 2, 3, 2, 4),
    gsSPNTriangles_5b(0, 5, 1, 6, 3, 4, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_douzou_girl_model[] = {
    gsSPTexture(2700, 480, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 8, obj_w_douzou_metal_tex_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(obj_w_douzou_v, 32, 0),
    gsSPNTrianglesInit_5b(34, 0, 1, 2, 3, 4, 5, 6, 0, 7),
    gsSPNTriangles_5b(5, 8, 9, 0, 10, 7, 3, 5, 6, 2, 10, 0),
    gsSPNTriangles_5b(11, 8, 5, 12, 1, 0, 7, 10, 13, 5, 4, 11),
    gsSPNTriangles_5b(14, 4, 3, 4, 14, 15, 16, 12, 0, 5, 9, 17),
    gsSPNTriangles_5b(16, 0, 18, 3, 7, 13, 5, 17, 18, 14, 3, 13),
    gsSPNTriangles_5b(19, 15, 14, 19, 14, 13, 0, 6, 18, 6, 5, 18),
    gsSPNTriangles_5b(3, 6, 7, 20, 19, 13, 20, 13, 21, 13, 10, 21),
    gsSPNTriangles_5b(4, 15, 9, 10, 12, 21, 22, 23, 24, 25, 26, 27),
    gsSPNTriangles_5b(25, 27, 28, 25, 29, 30, 28, 29, 25, 0, 0, 0),
    gsSPVertex(&obj_w_douzou_v[31], 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 6, 8, 12, 10, 13, 8, 14, 15, 16),
    gsSPNTriangles_5b(9, 2, 10, 1, 0, 17, 2, 18, 0, 19, 15, 20),
    gsSPNTriangles_5b(21, 20, 15, 15, 22, 16, 22, 15, 19, 23, 24, 25),
    gsSPNTriangles_5b(26, 25, 27, 28, 23, 29, 25, 26, 23, 15, 14, 21),
    gsSPNTriangles_5b(30, 20, 25, 12, 8, 13, 24, 23, 28, 27, 31, 26),
    gsSPNTriangles_5b(11, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_douzou_v[63], 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 6, 8, 10, 7, 11, 3, 12, 4, 13, 14, 15),
    gsSPNTriangles_5b(13, 15, 16, 2, 17, 18, 2, 18, 0, 14, 19, 20),
    gsSPNTriangles_5b(21, 14, 20, 22, 23, 24, 25, 26, 27, 28, 27, 26),
    gsSPNTriangles_5b(21, 29, 14, 29, 16, 15, 29, 15, 14, 30, 8, 10),
    gsSPNTriangles_5b(2, 1, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_douzou_v[95], 21, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 6, 5, 8, 5, 4, 9, 10, 8, 11, 10, 9),
    gsSPNTriangles_5b(12, 11, 13, 12, 13, 14, 11, 9, 13, 7, 14, 15),
    gsSPNTriangles_5b(6, 7, 15, 4, 6, 15, 16, 17, 18, 8, 17, 9),
    gsSPNTriangles_5b(8, 4, 17, 4, 15, 19, 4, 19, 18, 17, 4, 18),
    gsSPNTriangles_5b(20, 13, 9, 20, 9, 16, 9, 17, 16, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_douzou_boy_mouth_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_douzou_v[262], 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPEndDisplayList(),
};

Gfx obj_w_douzou_boy_face_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_douzou_v[255], 7, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 2, 1, 3, 4, 2),
    gsSPNTriangles_5b(0, 2, 5, 2, 6, 5, 2, 4, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_douzou_boy_model[] = {
    gsSPTexture(2700, 480, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 8, obj_w_douzou_metal_tex_pic_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_douzou_v[129], 32, 0),
    gsSPNTrianglesInit_5b(42, 0, 1, 2, 1, 3, 2, 3, 1, 4),
    gsSPNTriangles_5b(1, 5, 4, 6, 2, 7, 7, 2, 8, 8, 2, 3),
    gsSPNTriangles_5b(9, 4, 10, 3, 4, 9, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(10, 4, 17, 6, 0, 2, 4, 5, 17, 16, 12, 11),
    gsSPNTriangles_5b(18, 13, 12, 15, 19, 20, 16, 11, 14, 21, 22, 23),
    gsSPNTriangles_5b(24, 22, 21, 25, 18, 26, 27, 28, 26, 20, 21, 15),
    gsSPNTriangles_5b(1, 0, 16, 21, 20, 24, 19, 15, 14, 26, 28, 25),
    gsSPNTriangles_5b(12, 26, 18, 3, 9, 8, 12, 16, 0, 6, 27, 26),
    gsSPNTriangles_5b(6, 26, 12, 0, 6, 12, 17, 5, 15, 21, 23, 17),
    gsSPNTriangles_5b(21, 17, 15, 5, 1, 16, 15, 5, 16, 8, 29, 7),
    gsSPNTriangles_5b(30, 9, 10, 29, 8, 9, 29, 9, 30, 0, 0, 0),
    gsSPVertex(&obj_w_douzou_v[160], 32, 0),
    gsSPNTrianglesInit_5b(27, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 10, 8, 11, 7, 9, 12, 13, 14),
    gsSPNTriangles_5b(15, 14, 13, 16, 2, 17, 11, 9, 18, 9, 19, 18),
    gsSPNTriangles_5b(4, 20, 21, 4, 22, 20, 23, 8, 10, 23, 9, 8),
    gsSPNTriangles_5b(24, 25, 26, 27, 25, 28, 21, 5, 4, 16, 17, 29),
    gsSPNTriangles_5b(27, 12, 14, 26, 15, 30, 31, 17, 3, 24, 28, 25),
    gsSPNTriangles_5b(25, 14, 15, 30, 15, 13, 14, 25, 27, 15, 26, 25),
    gsSPVertex(&obj_w_douzou_v[192], 32, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 2, 3, 4, 5, 4, 6),
    gsSPNTriangles_5b(0, 2, 7, 5, 8, 4, 9, 10, 11, 12, 11, 13),
    gsSPNTriangles_5b(13, 11, 10, 13, 14, 12, 13, 15, 14, 16, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 22, 23, 24, 22, 25, 26, 26, 27, 23),
    gsSPNTriangles_5b(26, 23, 22, 28, 29, 30, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_douzou_v[223], 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 3, 4, 0, 2, 3, 0),
    gsSPNTriangles_5b(4, 3, 5, 4, 5, 6, 4, 6, 0, 7, 8, 9),
    gsSPNTriangles_5b(10, 11, 12, 13, 9, 14, 14, 15, 16, 17, 16, 15),
    gsSPNTriangles_5b(15, 10, 17, 18, 19, 8, 8, 7, 18, 9, 13, 7),
    gsSPNTriangles_5b(12, 17, 10, 6, 20, 21, 6, 5, 22, 6, 22, 20),
    gsSPNTriangles_5b(20, 23, 21, 21, 23, 24, 25, 26, 21, 25, 21, 24),
    gsSPNTriangles_5b(25, 24, 27, 24, 23, 28, 29, 24, 28, 30, 22, 5),
    gsSPNTriangles_5b(30, 5, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_obj_w_douzou_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_c_obj_w_douzou_tbl[] = { 0, 2800, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0,
                                 0, 0,    0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_obj_w_douzou = { cKF_ckcb_r_obj_w_douzou_tbl, NULL, NULL, cKF_c_obj_w_douzou_tbl, -1, 100 };

cKF_Joint_R_c cKF_je_r_obj_w_douzou_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 2800, 0 } },
    { obj_w_douzou_dai_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_douzou_boy_model, 5, cKF_JOINT_FLAG_DISP_OPA, { 270, 0, 0 } },
    { obj_w_douzou_boy_face_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_douzou_boy_mouth_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_douzou_girl_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_douzou_girl_face_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_douzou_girl_mouth_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_douzou_name_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_w_douzou = { ARRAY_COUNT(cKF_je_r_obj_w_douzou_tbl), 8, cKF_je_r_obj_w_douzou_tbl };
