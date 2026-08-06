#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_toudai_glass_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_toudai_glass_tex_pic_ci4_pal[] = {
#include "assets/obj_s_toudai_glass_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_toudai_light_tex_txt[0x100];
#else
u8 obj_s_toudai_light_tex_txt[] = {
#include "assets/obj_s_toudai_light_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_toudai_arm_tex_txt[0x80];
#else
u8 obj_s_toudai_arm_tex_txt[] = {
#include "assets/obj_s_toudai_arm_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_toudai_dai_tex_txt[0x200];
#else
u8 obj_s_toudai_dai_tex_txt[] = {
#include "assets/obj_s_toudai_dai_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_toudai_dou_tex_txt[0x400];
#else
u8 obj_s_toudai_dou_tex_txt[] = {
#include "assets/obj_s_toudai_dou_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_toudai_plate_tex_txt[0x80];
#else
u8 obj_s_toudai_plate_tex_txt[] = {
#include "assets/obj_s_toudai_plate_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_toudai_side_tex_txt[0x80];
#else
u8 obj_s_toudai_side_tex_txt[] = {
#include "assets/obj_s_toudai_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_toudai_tesuri_tex_txt[0x80];
#else
u8 obj_s_toudai_tesuri_tex_txt[] = {
#include "assets/obj_s_toudai_tesuri_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_toudai_yane_tex_txt[0x80];
#else
u8 obj_s_toudai_yane_tex_txt[] = {
#include "assets/obj_s_toudai_yane_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_toudai_glass_tex_pic_ci4[0x80];
#else
u8 obj_s_toudai_glass_tex_pic_ci4[] = {
#include "assets/obj_s_toudai_glass_tex_pic_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_toudai_v[0x990 / sizeof(Vtx)];
#else
Vtx obj_s_toudai_v[] = {
#include "assets/obj_s_toudai_v.inc"
};
#endif

Gfx obj_s_toudai_mirror_model[] = {
    gsSPTexture(1000, 1000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_toudai_glass_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_s_toudai_glass_tex_pic_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_toudai_v[143], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(6, 7, 8, 6, 8, 5, 6, 5, 4, 0, 4, 1),
    gsSPNTriangles_5b(7, 9, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_toudai_glass_model[] = {
    gsSPTexture(2400, 500, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 155, 190, 255, 130),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_toudai_glass_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_s_toudai_glass_tex_pic_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 14),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_toudai_v[133], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 4, 5, 6, 7),
    gsSPNTriangles_5b(5, 7, 8, 6, 3, 9, 0, 2, 4, 3, 4, 9),
    gsSPNTriangles_5b(7, 6, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_toudai_body_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_s_toudai_dai_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_toudai_v[27], 29, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_s_toudai_dou_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(11, 16, 17, 18, 19, 16, 20, 21, 19, 22),
    gsSPNTriangles_5b(23, 24, 25, 24, 26, 27, 25, 24, 27, 23, 25, 28),
    gsSPNTriangles_5b(17, 23, 28, 18, 17, 28, 16, 18, 20, 19, 20, 22),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_s_toudai_plate_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_s_toudai_v[56], 21, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(0, 5, 3, 4, 6, 1, 3, 7, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_s_toudai_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(11, 8, 9, 10, 11, 9, 8, 12, 13, 14),
    gsSPNTriangles_5b(15, 12, 14, 16, 15, 14, 17, 18, 19, 9, 17, 10),
    gsSPNTriangles_5b(18, 15, 16, 12, 20, 13, 17, 19, 10, 18, 16, 19),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_s_toudai_tesuri_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_s_toudai_v[77], 18, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 2, 3, 4),
    gsSPNTriangles_5b(3, 5, 4, 6, 7, 8, 6, 9, 7, 8, 5, 4),
    gsSPNTriangles_5b(8, 7, 5, 10, 11, 12, 11, 13, 12, 12, 13, 0),
    gsSPNTriangles_5b(13, 1, 0, 10, 14, 15, 10, 11, 14, 15, 16, 17),
    gsSPNTriangles_5b(15, 14, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_s_toudai_yane_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_s_toudai_v[95], 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 1, 3, 2, 4, 5, 0),
    gsSPNTriangles_5b(0, 2, 6, 4, 7, 5, 8, 9, 10, 8, 11, 9),
    gsSPNTriangles_5b(11, 12, 9, 13, 14, 8, 14, 15, 8, 14, 16, 15),
    gsSPNTriangles_5b(17, 18, 19, 18, 20, 19, 18, 21, 20, 19, 22, 13),
    gsSPNTriangles_5b(19, 23, 22, 23, 24, 22, 25, 26, 27, 25, 28, 26),
    gsSPNTriangles_5b(28, 29, 26, 10, 30, 25, 30, 31, 25, 0, 0, 0),
    gsSPVertex(&obj_s_toudai_v[127], 6, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_toudai_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, COMBINED, 0, PRIM_LOD_FRAC, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, obj_s_toudai_light_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_toudai_v[6], 18, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 1, 4, 5, 0),
    gsSPNTriangles_5b(5, 3, 0, 6, 5, 4, 6, 7, 5, 8, 9, 6),
    gsSPNTriangles_5b(9, 7, 6, 10, 9, 8, 10, 11, 9, 2, 1, 10),
    gsSPNTriangles_5b(1, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 13, 15, 14, 15, 16, 14),
    gsSPNTriangles_5b(13, 17, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_toudai_lenz_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0,
                       0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 220, 100, 255),
    gsDPSetEnvColor(0, 80, 80, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_toudai_glass_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_s_toudai_glass_tex_pic_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 3),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_toudai_v, 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(0, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_toudai_arm_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_s_toudai_arm_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_toudai_v[24], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_toudai_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 10000, 0 } },
                                              { obj_s_toudai_body_model, 3, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_toudai_arm_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_s_toudai_lenz_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_toudai_light_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                              { obj_s_toudai_glass_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_s_toudai_mirror_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_s_toudai = { ARRAY_COUNT(cKF_je_r_obj_s_toudai_tbl), 6, cKF_je_r_obj_s_toudai_tbl };

u8 cKF_ckcb_r_obj_s_toudai_tbl[] = { 0, 0, 4, 0, 0, 0, 0 };

s16 cKF_kn_obj_s_toudai_tbl[] = { 2 };

s16 cKF_c_obj_s_toudai_tbl[] = { 0, 10000, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_s_toudai_tbl[] = { 1, 0, 1080, 100, 3564, 1080 };

cKF_Animation_R_c cKF_ba_r_obj_s_toudai = {
    cKF_ckcb_r_obj_s_toudai_tbl, cKF_ds_obj_s_toudai_tbl, cKF_kn_obj_s_toudai_tbl, cKF_c_obj_s_toudai_tbl, -1, 100
};

#ifdef TARGET_PC
u16 obj_w_toudai_glass_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 obj_w_toudai_glass_tex_pic_ci4_pal[] = {
#include "assets/obj_w_toudai_glass_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_toudai_light_tex_txt[0x100];
#else
u8 obj_w_toudai_light_tex_txt[] = {
#include "assets/obj_w_toudai_light_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_toudai_arm_tex_txt[0x80];
#else
u8 obj_w_toudai_arm_tex_txt[] = {
#include "assets/obj_w_toudai_arm_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_toudai_dai_tex_txt[0x200];
#else
u8 obj_w_toudai_dai_tex_txt[] = {
#include "assets/obj_w_toudai_dai_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_toudai_dou_tex_txt[0x400];
#else
u8 obj_w_toudai_dou_tex_txt[] = {
#include "assets/obj_w_toudai_dou_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_toudai_plate_tex_txt[0x80];
#else
u8 obj_w_toudai_plate_tex_txt[] = {
#include "assets/obj_w_toudai_plate_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_toudai_side_tex_txt[0x80];
#else
u8 obj_w_toudai_side_tex_txt[] = {
#include "assets/obj_w_toudai_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_toudai_tesuri_tex_txt[0x80];
#else
u8 obj_w_toudai_tesuri_tex_txt[] = {
#include "assets/obj_w_toudai_tesuri_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_toudai_yane_tex_txt[0x80];
#else
u8 obj_w_toudai_yane_tex_txt[] = {
#include "assets/obj_w_toudai_yane_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_toudai_glass_tex_pic_ci4[0x80];
#else
u8 obj_w_toudai_glass_tex_pic_ci4[] = {
#include "assets/obj_w_toudai_glass_tex_pic_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_toudai_v[0x950 / sizeof(Vtx)];
#else
Vtx obj_w_toudai_v[] = {
#include "assets/obj_w_toudai_v.inc"
};
#endif

Gfx obj_w_toudai_mirror_model[] = {
    gsSPTexture(1000, 1000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_toudai_glass_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_w_toudai_glass_tex_pic_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_toudai_v[37], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(6, 7, 8, 6, 8, 5, 6, 5, 4, 0, 4, 1),
    gsSPNTriangles_5b(7, 9, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_toudai_glass_model[] = {
    gsSPTexture(2400, 500, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 155, 190, 255, 130),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_toudai_glass_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_w_toudai_glass_tex_pic_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 14),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_toudai_v[27], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 4, 5, 6, 7),
    gsSPNTriangles_5b(5, 7, 8, 6, 3, 9, 0, 2, 4, 3, 4, 9),
    gsSPNTriangles_5b(7, 6, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_toudai_body_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, obj_w_toudai_dai_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_toudai_v[47], 25, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 8, 6, 8, 9, 6, 0, 6, 10),
    gsSPNTriangles_5b(6, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_w_toudai_dou_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(11, 12, 13, 14, 15, 12, 16, 17, 15, 18),
    gsSPNTriangles_5b(19, 20, 21, 20, 22, 23, 21, 20, 23, 19, 21, 24),
    gsSPNTriangles_5b(13, 19, 24, 14, 13, 24, 12, 14, 16, 15, 16, 18),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_w_toudai_plate_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_w_toudai_v[72], 21, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(0, 5, 3, 4, 6, 1, 3, 7, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_w_toudai_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(11, 8, 9, 10, 11, 9, 8, 12, 13, 14),
    gsSPNTriangles_5b(15, 12, 14, 16, 15, 14, 17, 18, 19, 9, 17, 10),
    gsSPNTriangles_5b(18, 15, 16, 12, 20, 13, 17, 19, 10, 18, 16, 19),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_w_toudai_tesuri_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_w_toudai_v[93], 18, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 2, 3, 4),
    gsSPNTriangles_5b(3, 5, 4, 6, 7, 8, 6, 9, 7, 8, 5, 4),
    gsSPNTriangles_5b(8, 7, 5, 10, 11, 12, 11, 13, 12, 12, 13, 0),
    gsSPNTriangles_5b(13, 1, 0, 10, 14, 15, 10, 11, 14, 15, 16, 17),
    gsSPNTriangles_5b(15, 14, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_w_toudai_yane_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_w_toudai_v[111], 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 1, 3, 2, 4, 5, 0),
    gsSPNTriangles_5b(0, 2, 6, 4, 7, 5, 8, 9, 10, 8, 11, 9),
    gsSPNTriangles_5b(11, 12, 9, 13, 14, 8, 14, 15, 8, 14, 16, 15),
    gsSPNTriangles_5b(17, 18, 19, 18, 20, 19, 18, 21, 20, 19, 22, 13),
    gsSPNTriangles_5b(19, 23, 22, 23, 24, 22, 25, 26, 27, 25, 28, 26),
    gsSPNTriangles_5b(28, 29, 26, 10, 30, 25, 30, 31, 25, 0, 0, 0),
    gsSPVertex(&obj_w_toudai_v[143], 6, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_toudai_light_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, COMBINED, 0, PRIM_LOD_FRAC, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, obj_w_toudai_light_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_toudai_v[6], 18, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 1, 4, 5, 0),
    gsSPNTriangles_5b(5, 3, 0, 6, 5, 4, 6, 7, 5, 8, 9, 6),
    gsSPNTriangles_5b(9, 7, 6, 10, 9, 8, 10, 11, 9, 2, 1, 10),
    gsSPNTriangles_5b(1, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 13, 15, 14, 15, 16, 14),
    gsSPNTriangles_5b(13, 17, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_toudai_lenz_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0,
                       0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 220, 100, 255),
    gsDPSetEnvColor(0, 80, 80, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_toudai_glass_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_w_toudai_glass_tex_pic_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 3),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_toudai_v, 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(0, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_toudai_arm_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_w_toudai_arm_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_toudai_v[24], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_toudai_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 10000, 0 } },
                                              { obj_w_toudai_body_model, 3, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_toudai_arm_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
                                              { obj_w_toudai_lenz_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_toudai_light_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                              { obj_w_toudai_glass_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { obj_w_toudai_mirror_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_w_toudai = { ARRAY_COUNT(cKF_je_r_obj_w_toudai_tbl), 6, cKF_je_r_obj_w_toudai_tbl };

u8 cKF_ckcb_r_obj_w_toudai_tbl[] = { 0, 0, 4, 0, 0, 0, 0 };

s16 cKF_kn_obj_w_toudai_tbl[] = { 2 };

s16 cKF_c_obj_w_toudai_tbl[] = { 0, 10000, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_w_toudai_tbl[] = { 1, 0, 1080, 100, 3564, 1080 };

cKF_Animation_R_c cKF_ba_r_obj_w_toudai = {
    cKF_ckcb_r_obj_w_toudai_tbl, cKF_ds_obj_w_toudai_tbl, cKF_kn_obj_w_toudai_tbl, cKF_c_obj_w_toudai_tbl, -1, 100
};
