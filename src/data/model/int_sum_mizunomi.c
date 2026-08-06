#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_mizunomi_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_mizunomitori_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_mizunomitori_pal[] = {
#include "assets/int_sum_mizunomitori_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_sum_mizunomi_body_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_sum_mizunomi_body_tex_pic_ci4_pal[] = {
#include "assets/int_sum_mizunomi_body_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_sum_mizunomi_neck_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_sum_mizunomi_neck_tex_pic_ci4_pal[] = {
#include "assets/int_sum_mizunomi_neck_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_mizunomi_face_tex_txt[0x200];
#else
u8 int_sum_mizunomi_face_tex_txt[] = {
#include "assets/int_sum_mizunomi_face_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_mizunomi_hat_tex_txt[0x80];
#else
u8 int_sum_mizunomi_hat_tex_txt[] = {
#include "assets/int_sum_mizunomi_hat_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_mizunomi_foot_tex_txt[0x100];
#else
u8 int_sum_mizunomi_foot_tex_txt[] = {
#include "assets/int_sum_mizunomi_foot_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_mizunomi_kuchi_tex_txt[0x80];
#else
u8 int_sum_mizunomi_kuchi_tex_txt[] = {
#include "assets/int_sum_mizunomi_kuchi_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_mizunomi_hane_tex_txt[0x100];
#else
u8 int_sum_mizunomi_hane_tex_txt[] = {
#include "assets/int_sum_mizunomi_hane_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_mizunomi_body_tex_txt[0x80];
#else
u8 int_sum_mizunomi_body_tex_txt[] = {
#include "assets/int_sum_mizunomi_body_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_mizunomi_neck_tex_txt[0x100];
#else
u8 int_sum_mizunomi_neck_tex_txt[] = {
#include "assets/int_sum_mizunomi_neck_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_mizunomi_v[0x370 / sizeof(Vtx)];
#else
Vtx int_sum_mizunomi_v[] = {
#include "assets/int_sum_mizunomi_v.inc"
};
#endif

Gfx int_sum_mizunomi_head_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_mizunomitori_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_mizunomi_face_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_mizunomi_v[16], 21, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 1, 0, 0, 2, 4),
    gsSPNTriangles_5b(4, 5, 0, 1, 6, 2, 1, 7, 6, 8, 9, 10),
    gsSPNTriangles_5b(10, 11, 8, 9, 8, 12, 8, 11, 12, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_mizunomi_hat_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(2, 13, 14, 15, 13, 15, 16, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_mizunomi_kuchi_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 17, 18, 19, 17, 19, 20, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_mizunomi_env2_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIM_LOD_FRAC, PRIMITIVE, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 120, 255, 255, 255, 60),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_mizunomi_neck_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_mizunomi_neck_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 2, 2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_mizunomi_v[10], 6, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 1, 0, 4, 3, 5),
    gsSPEndDisplayList(),
};

Gfx int_sum_mizunomi_env_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIM_LOD_FRAC, PRIMITIVE, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 64),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_mizunomi_body_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_mizunomi_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 2, 2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(int_sum_mizunomi_v, 10, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 1, 0, 4, 3, 0),
    gsSPNTriangles_5b(4, 0, 2, 1, 5, 2, 1, 3, 5, 6, 7, 4),
    gsSPNTriangles_5b(8, 7, 6, 6, 4, 9, 9, 8, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_mizunomi_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_mizunomitori_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_mizunomi_kuchi_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_mizunomi_v[37], 18, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_mizunomi_hane_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 6, 7, 4, 8, 9, 10),
    gsSPNTriangles_5b(10, 11, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_mizunomi_foot_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 15, 13, 16, 15, 14, 13),
    gsSPNTriangles_5b(15, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_mizunomi_tbl[] = { 0, 2, 0, 0 };

s16 cKF_kn_int_sum_mizunomi_tbl[] = { 5 };

s16 cKF_c_int_sum_mizunomi_tbl[] = { 0, 2750, 0, 450, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_sum_mizunomi_tbl[] = { 1, -900, 143, 2, -895, 278, 27, 200, 0, 52, -895, -278, 53, -900, -143 };

cKF_Animation_R_c cKF_ba_r_int_sum_mizunomi = { cKF_ckcb_r_int_sum_mizunomi_tbl,
                                                cKF_ds_int_sum_mizunomi_tbl,
                                                cKF_kn_int_sum_mizunomi_tbl,
                                                cKF_c_int_sum_mizunomi_tbl,
                                                -1,
                                                53 };

cKF_Joint_R_c cKF_je_r_int_sum_mizunomi_tbl[] = {
    { int_sum_mizunomi_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 2750, 0 } },
    { int_sum_mizunomi_env_model, 2, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_sum_mizunomi_env2_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_sum_mizunomi_head_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_mizunomi = { ARRAY_COUNT(cKF_je_r_int_sum_mizunomi_tbl), 4,
                                               cKF_je_r_int_sum_mizunomi_tbl };
