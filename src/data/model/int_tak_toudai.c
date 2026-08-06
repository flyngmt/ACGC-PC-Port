#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_toudai_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_toudai_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_toudai_pal[] = {
#include "assets/int_tak_toudai_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_toudai_evw_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_toudai_evw_tex_pic_ci4_pal[] = {
#include "assets/int_tak_toudai_evw_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_toudai_right_tex_txt[0x80];
#else
u8 int_tak_toudai_right_tex_txt[] = {
#include "assets/int_tak_toudai_right_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_toudai_dai_tex_txt[0x40];
#else
u8 int_tak_toudai_dai_tex_txt[] = {
#include "assets/int_tak_toudai_dai_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_toudai_grass_tex_txt[0x80];
#else
u8 int_tak_toudai_grass_tex_txt[] = {
#include "assets/int_tak_toudai_grass_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_toudai_tesuri_tex_txt[0x40];
#else
u8 int_tak_toudai_tesuri_tex_txt[] = {
#include "assets/int_tak_toudai_tesuri_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_toudai_body2_tex_txt[0x100];
#else
u8 int_tak_toudai_body2_tex_txt[] = {
#include "assets/int_tak_toudai_body2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_toudai_body_tex_txt[0x80];
#else
u8 int_tak_toudai_body_tex_txt[] = {
#include "assets/int_tak_toudai_body_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_toudai_evw_tex_txt[0x20];
#else
u8 int_tak_toudai_evw_tex_txt[] = {
#include "assets/int_tak_toudai_evw_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_toudai_v[0x710 / sizeof(Vtx)];
#else
Vtx int_tak_toudai_v[] = {
#include "assets/int_tak_toudai_v.inc"
};
#endif

Gfx int_tak_toudai_right_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, int_tak_toudai_right_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_toudai_v, 12, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 4, 5, 6, 6, 5, 7, 5, 8, 7),
    gsSPNTriangles_5b(9, 7, 8, 9, 8, 10, 10, 11, 9, 4, 6, 11),
    gsSPNTriangles_5b(11, 10, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_toudai_back_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_toudai_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, int_tak_toudai_dai_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_toudai_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_toudai_tesuri_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_toudai_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, int_tak_toudai_tesuri_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_toudai_v[38], 28, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 1, 3, 2, 4, 5, 0),
    gsSPNTriangles_5b(5, 1, 0, 6, 7, 8, 7, 9, 8, 8, 9, 4),
    gsSPNTriangles_5b(9, 5, 4, 2, 3, 10, 3, 11, 10, 10, 11, 12),
    gsSPNTriangles_5b(11, 13, 12, 14, 15, 16, 14, 16, 17, 17, 16, 18),
    gsSPNTriangles_5b(17, 18, 19, 20, 21, 22, 20, 22, 23, 19, 18, 21),
    gsSPNTriangles_5b(19, 21, 20, 23, 22, 24, 23, 24, 25, 25, 24, 26),
    gsSPNTriangles_5b(25, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_toudai_grass_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_toudai_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_toudai_grass_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_toudai_v[16], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_toudai_evw_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 200, 200, 255, 155),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_toudai_evw_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_tak_toudai_evw_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_toudai_v[66], 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 1, 3, 2, 4, 5, 0),
    gsSPNTriangles_5b(5, 1, 0, 6, 7, 8, 7, 9, 8, 8, 9, 4),
    gsSPNTriangles_5b(9, 5, 4, 2, 3, 10, 3, 11, 10, 10, 11, 12),
    gsSPNTriangles_5b(11, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_toudai_dai_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_toudai_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, int_tak_toudai_dai_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_toudai_v[20], 18, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 2, 6, 7, 2, 7, 3, 6, 8, 9),
    gsSPNTriangles_5b(6, 9, 10, 10, 11, 7, 10, 7, 6, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 12, 15, 16, 12, 16, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_toudai_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_toudai_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_toudai_body2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_toudai_v[80], 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 2, 4, 1, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 32, int_tak_toudai_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_toudai_v[85], 28, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 0, 3, 8, 7, 3, 9, 10, 5, 11, 12, 13),
    gsSPNTriangles_5b(14, 15, 16, 17, 12, 11, 18, 17, 11, 19, 6, 20),
    gsSPNTriangles_5b(21, 16, 22, 23, 7, 8, 24, 25, 26, 27, 22, 10),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_tak_toudai_tbl[] = { 0, 0, 0, 0, 0, 0, 1, 0 };

s16 cKF_kn_int_tak_toudai_tbl[] = { 2 };

s16 cKF_c_int_tak_toudai_tbl[] = {
    0, 0, 2000, -900, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

s16 cKF_ds_int_tak_toudai_tbl[] = { 1, 0, 1080, 100, 3564, 1080 };

cKF_Animation_R_c cKF_ba_r_int_tak_toudai = { cKF_ckcb_r_int_tak_toudai_tbl,
                                              cKF_ds_int_tak_toudai_tbl,
                                              cKF_kn_int_tak_toudai_tbl,
                                              cKF_c_int_tak_toudai_tbl,
                                              -1,
                                              100 };

cKF_Joint_R_c cKF_je_r_int_tak_toudai_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 2000 } },
    { int_tak_toudai_body_model, 5, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_tak_toudai_dai_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_tak_toudai_evw_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_tak_toudai_grass_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_tak_toudai_tesuri_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_tak_toudai_back_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
    { int_tak_toudai_right_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_tak_toudai = { ARRAY_COUNT(cKF_je_r_int_tak_toudai_tbl), 7, cKF_je_r_int_tak_toudai_tbl };
