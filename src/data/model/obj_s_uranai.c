#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_uranai_t2_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_uranai_t2_tex_txt[] = {
#include "assets/obj_s_uranai_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_uranai_window_tex_txt[0x80];
#else
u8 obj_s_uranai_window_tex_txt[] = {
#include "assets/obj_s_uranai_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_uranai_t1_tex_txt[0x800];
#else
u8 obj_s_uranai_t1_tex_txt[] = {
#include "assets/obj_s_uranai_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_uranai_v[0x370 / sizeof(Vtx)];
#else
Vtx obj_s_uranai_v[] = {
#include "assets/obj_s_uranai_v.inc"
};
#endif

Gfx obj_s_uranai_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_s_uranai_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_uranai_v[10], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_uranai_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_uranai_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_uranai_v[48], 7, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPEndDisplayList(),
};

Gfx obj_s_uranai_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_uranai_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_uranai_v[18], 30, 0),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 2, 3, 0, 3, 4, 0),
    gsSPNTriangles_5b(3, 5, 4, 5, 6, 4, 5, 7, 6, 8, 9, 10),
    gsSPNTriangles_5b(8, 11, 9, 12, 13, 14, 15, 12, 14, 15, 14, 16),
    gsSPNTriangles_5b(17, 15, 16, 17, 16, 18, 18, 19, 17, 20, 21, 22),
    gsSPNTriangles_5b(23, 21, 20, 22, 24, 20, 20, 24, 25, 20, 26, 27),
    gsSPNTriangles_5b(28, 26, 20, 20, 29, 28, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_uranai_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_uranai_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_uranai_v[14], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_uranai_doorA_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 150),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_uranai_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_uranai_v, 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPEndDisplayList(),
};

Gfx obj_s_uranai_doorB_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 150),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_uranai_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_uranai_v[5], 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_uranai_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 64536 } },
                                              { obj_s_uranai_light_model, 5, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } },
                                              { obj_s_uranai_doorB_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                              { obj_s_uranai_doorA_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 1000, 0, 0 } },
                                              { obj_s_uranai_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_uranai_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_uranai_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_s_uranai = { ARRAY_COUNT(cKF_je_r_obj_s_uranai_tbl), 6, cKF_je_r_obj_s_uranai_tbl };

u8 cKF_ckcb_r_obj_s_uranai_tbl[] = { 56, 7, 0, 7, 7, 0, 0, 0 };

s16 cKF_kn_obj_s_uranai_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };

s16 cKF_c_obj_s_uranai_tbl[] = { 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_s_uranai_tbl[] = { 1, 0, 0, 17, 0, 0, 1, 0, 0, 17, 0,    0, 1, -1000, 0, 17, -1000, 0,
                                  1, 0, 0, 17, 0, 0, 1, 0, 0, 17, 0,    0, 1, 0,     0, 17, 0,     0,
                                  1, 0, 0, 17, 0, 0, 1, 0, 0, 17, -450, 0, 1, 0,     0, 17, 50,    0,
                                  1, 0, 0, 17, 0, 0, 1, 0, 0, 17, 450,  0, 1, 0,     0, 17, 50,    0 };

cKF_Animation_R_c cKF_ba_r_obj_s_uranai = {
    cKF_ckcb_r_obj_s_uranai_tbl, cKF_ds_obj_s_uranai_tbl, cKF_kn_obj_s_uranai_tbl, cKF_c_obj_s_uranai_tbl, -1, 17
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_w_uranai_t2_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_w_uranai_t2_tex_txt[] = {
#include "assets/obj_w_uranai_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_uranai_window_tex_txt[0x80];
#else
u8 obj_w_uranai_window_tex_txt[] = {
#include "assets/obj_w_uranai_window_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_uranai_t1_tex_txt[0x800];
#else
u8 obj_w_uranai_t1_tex_txt[] = {
#include "assets/obj_w_uranai_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_uranai_v[0x370 / sizeof(Vtx)];
#else
Vtx obj_w_uranai_v[] = {
#include "assets/obj_w_uranai_v.inc"
};
#endif

Gfx obj_w_uranai_window_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_w_uranai_window_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_uranai_v[10], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_uranai_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_uranai_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_uranai_v[48], 7, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPEndDisplayList(),
};

Gfx obj_w_uranai_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_w_uranai_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_uranai_v[18], 30, 0),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 2, 3, 0, 3, 4, 0),
    gsSPNTriangles_5b(3, 5, 4, 5, 6, 4, 5, 7, 6, 8, 9, 10),
    gsSPNTriangles_5b(8, 11, 9, 12, 13, 14, 15, 12, 14, 15, 14, 16),
    gsSPNTriangles_5b(17, 15, 16, 17, 16, 18, 18, 19, 17, 20, 21, 22),
    gsSPNTriangles_5b(23, 21, 20, 22, 24, 20, 20, 24, 25, 20, 26, 27),
    gsSPNTriangles_5b(28, 26, 20, 20, 29, 28, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_uranai_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_uranai_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_uranai_v[14], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_uranai_doorA_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 150),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_uranai_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_uranai_v, 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPEndDisplayList(),
};

Gfx obj_w_uranai_doorB_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 150),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_uranai_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_uranai_v[5], 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_uranai_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 64536 } },
                                              { obj_w_uranai_light_model, 5, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } },
                                              { obj_w_uranai_doorB_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                              { obj_w_uranai_doorA_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 1000, 0, 0 } },
                                              { obj_w_uranai_t1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_uranai_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_uranai_window_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_w_uranai = { ARRAY_COUNT(cKF_je_r_obj_w_uranai_tbl), 6, cKF_je_r_obj_w_uranai_tbl };

u8 cKF_ckcb_r_obj_w_uranai_tbl[] = { 56, 7, 0, 7, 7, 0, 0, 0 };

s16 cKF_kn_obj_w_uranai_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };

s16 cKF_c_obj_w_uranai_tbl[] = { 0, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_w_uranai_tbl[] = { 1, 0, 0, 17, 0, 0, 1, 0, 0, 17, 0,    0, 1, -1000, 0, 17, -1000, 0,
                                  1, 0, 0, 17, 0, 0, 1, 0, 0, 17, 0,    0, 1, 0,     0, 17, 0,     0,
                                  1, 0, 0, 17, 0, 0, 1, 0, 0, 17, -450, 0, 1, 0,     0, 17, 50,    0,
                                  1, 0, 0, 17, 0, 0, 1, 0, 0, 17, 450,  0, 1, 0,     0, 17, 50,    0 };

cKF_Animation_R_c cKF_ba_r_obj_w_uranai = {
    cKF_ckcb_r_obj_w_uranai_tbl, cKF_ds_obj_w_uranai_tbl, cKF_kn_obj_w_uranai_tbl, cKF_c_obj_w_uranai_tbl, -1, 17
};
