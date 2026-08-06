#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_e_count02_0_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_e_count02_0_tex[] = {
#include "assets/obj_e_count02_0_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_count02_1_tex[0x200];
#else
u8 obj_e_count02_1_tex[] = {
#include "assets/obj_e_count02_1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_count02_2_tex[0x200];
#else
u8 obj_e_count02_2_tex[] = {
#include "assets/obj_e_count02_2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_count02_3_tex[0x200];
#else
u8 obj_e_count02_3_tex[] = {
#include "assets/obj_e_count02_3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_count02_4_tex[0x200];
#else
u8 obj_e_count02_4_tex[] = {
#include "assets/obj_e_count02_4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_count02_5_tex[0x200];
#else
u8 obj_e_count02_5_tex[] = {
#include "assets/obj_e_count02_5_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_count02_6_tex[0x200];
#else
u8 obj_e_count02_6_tex[] = {
#include "assets/obj_e_count02_6_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_count02_7_tex[0x200];
#else
u8 obj_e_count02_7_tex[] = {
#include "assets/obj_e_count02_7_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_count02_8_tex[0x200];
#else
u8 obj_e_count02_8_tex[] = {
#include "assets/obj_e_count02_8_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_count02_9_tex[0x200];
#else
u8 obj_e_count02_9_tex[] = {
#include "assets/obj_e_count02_9_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_count02_cl_v[0x100 / sizeof(Vtx)];
#else
Vtx obj_e_count02_cl_v[] = {
#include "assets/obj_e_count02_cl_v.inc"
};
#endif

Gfx obj_e_c2_ani_cl01_sita_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_count02_cl_v[8], 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 7, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_c2_ani_ci01_mae_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_count02_cl_v, 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 7, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_e_count02_cl_tbl[] = {
    { obj_e_c2_ani_cl01_sita_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 800, 3361, 64571 } },
    { obj_e_c2_ani_ci01_mae_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_e_count02_cl = { ARRAY_COUNT(cKF_je_r_obj_e_count02_cl_tbl), 2,
                                               cKF_je_r_obj_e_count02_cl_tbl };

u8 cKF_ckcb_r_obj_e_count02_cl_tbl[] = { 0, 0, 1 };

s16 cKF_kn_obj_e_count02_cl_tbl[] = { 5 };

s16 cKF_c_obj_e_count02_cl_tbl[] = { 0, 0, 0, 0, 0, 0, 900, 900, 900, 0, 0 };

s16 cKF_ds_obj_e_count02_cl_tbl[] = { 1, 764, 1946, 2, 828, 2477, 7, 1555, 5372, 9, 1913, 5179, 10, 2081, 5034 };

cKF_Animation_R_c cKF_ba_r_obj_e_count02_cl = { cKF_ckcb_r_obj_e_count02_cl_tbl,
                                                cKF_ds_obj_e_count02_cl_tbl,
                                                cKF_kn_obj_e_count02_cl_tbl,
                                                cKF_c_obj_e_count02_cl_tbl,
                                                -1,
                                                10 };
