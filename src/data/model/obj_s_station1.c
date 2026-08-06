#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_station1_t3_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_station1_t3_tex_txt[] = {
#include "assets/obj_s_station1_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_station1_t2_tex_txt[0x800];
#else
u8 obj_s_station1_t2_tex_txt[] = {
#include "assets/obj_s_station1_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_station1_t1_tex_txt[0x800];
#else
u8 obj_s_station1_t1_tex_txt[] = {
#include "assets/obj_s_station1_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_station1_v[0x7D0 / sizeof(Vtx)];
#else
Vtx obj_s_station1_v[] = {
#include "assets/obj_s_station1_v.inc"
};
#endif

Gfx obj_s_station1_t3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_station1_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_station1_v[8], 32, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 9, 11, 10, 9, 12, 11),
    gsSPNTriangles_5b(13, 14, 15, 13, 16, 14, 13, 17, 16, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 24, 25, 26, 20, 27, 28, 29, 30, 31),
    gsSPVertex(&obj_s_station1_v[40], 28, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 2, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 10, 8, 11, 9, 12, 13, 14, 13, 15, 14),
    gsSPNTriangles_5b(16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23),
    gsSPNTriangles_5b(24, 25, 26, 24, 26, 27, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_station1_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_station1_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_station1_v[68], 10, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 2, 5),
    gsSPNTriangles_5b(4, 0, 2, 6, 7, 8, 7, 9, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_station1_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_station1_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_station1_v[78], 32, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 5, 0, 2, 6),
    gsSPNTriangles_5b(7, 8, 9, 8, 10, 9, 11, 12, 13, 12, 14, 13),
    gsSPNTriangles_5b(15, 16, 17, 18, 19, 20, 18, 21, 19, 22, 23, 24),
    gsSPNTriangles_5b(23, 25, 24, 24, 26, 18, 27, 28, 29, 0, 0, 0),
    gsSPVertex(&obj_s_station1_v[108], 17, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 10, 13, 11, 14, 15, 16),
    gsSPEndDisplayList(),
};

Gfx obj_s_station1_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_station1_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_station1_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_station1_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_station1_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_station1_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_station1_tbl[] = { { obj_s_station1_t1_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 8000, 13000, 6000 } },
                                                { obj_s_station1_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 8000, 13000, 6000 } },
                                                { obj_s_station1_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { obj_s_station1_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { obj_s_station1_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_s_station1 = { ARRAY_COUNT(cKF_je_r_obj_s_station1_tbl), 5, cKF_je_r_obj_s_station1_tbl };

u8 cKF_ckcb_r_obj_s_station1_tbl[] = { 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_c_obj_s_station1_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_obj_s_station1 = {
    cKF_ckcb_r_obj_s_station1_tbl, NULL, NULL, cKF_c_obj_s_station1_tbl, -1, 2
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_w_station1_t3_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_w_station1_t3_tex_txt[] = {
#include "assets/obj_w_station1_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_station1_t2_tex_txt[0x800];
#else
u8 obj_w_station1_t2_tex_txt[] = {
#include "assets/obj_w_station1_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_station1_t1_tex_txt[0x800];
#else
u8 obj_w_station1_t1_tex_txt[] = {
#include "assets/obj_w_station1_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_station1_v[0x7B0 / sizeof(Vtx)];
#else
Vtx obj_w_station1_v[] = {
#include "assets/obj_w_station1_v.inc"
};
#endif

Gfx obj_w_station1_t3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_station1_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_station1_v[8], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 6, 7, 8, 7, 9, 8, 7, 10, 9),
    gsSPNTriangles_5b(11, 12, 13, 11, 14, 12, 11, 15, 14, 16, 17, 18),
    gsSPNTriangles_5b(18, 19, 20, 18, 21, 19, 18, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(27, 28, 24, 24, 29, 30, 24, 31, 25, 0, 0, 0),
    gsSPVertex(&obj_w_station1_v[40], 16, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 3, 1, 2, 1, 4),
    gsSPNTriangles_5b(1, 5, 4, 6, 7, 8, 6, 8, 9, 9, 8, 10),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_station1_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_station1_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_station1_v[56], 13, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 6, 8, 9, 6, 9, 7, 1, 10, 3),
    gsSPNTriangles_5b(10, 11, 3, 3, 12, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_station1_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_station1_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_station1_v[69], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 0, 6, 1),
    gsSPNTriangles_5b(6, 7, 1, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 18, 20, 21),
    gsSPNTriangles_5b(18, 21, 19, 22, 23, 24, 22, 24, 25, 23, 26, 27),
    gsSPNTriangles_5b(23, 27, 24, 28, 29, 30, 28, 31, 29, 0, 0, 0),
    gsSPVertex(&obj_w_station1_v[101], 22, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 4, 5, 3, 6, 4),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 16, 7, 17, 18, 19, 17, 19, 20, 0, 21, 1),
    gsSPEndDisplayList(),
};

Gfx obj_w_station1_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_station1_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_station1_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_station1_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_station1_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_station1_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_station1_tbl[] = { { obj_w_station1_t1_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 8000, 13000, 6000 } },
                                                { obj_w_station1_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 8000, 13000, 6000 } },
                                                { obj_w_station1_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { obj_w_station1_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { obj_w_station1_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_w_station1 = { ARRAY_COUNT(cKF_je_r_obj_w_station1_tbl), 5, cKF_je_r_obj_w_station1_tbl };

u8 cKF_ckcb_r_obj_w_station1_tbl[] = { 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_c_obj_w_station1_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_obj_w_station1 = {
    cKF_ckcb_r_obj_w_station1_tbl, NULL, NULL, cKF_c_obj_w_station1_tbl, -1, 2
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_station2_t1_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_station2_t1_tex_txt[] = {
#include "assets/obj_s_station2_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_station2_t2_tex_txt[0x800];
#else
u8 obj_s_station2_t2_tex_txt[] = {
#include "assets/obj_s_station2_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_station2_t3_tex_txt[0x800];
#else
u8 obj_s_station2_t3_tex_txt[] = {
#include "assets/obj_s_station2_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_station2_v[0x710 / sizeof(Vtx)];
#else
Vtx obj_s_station2_v[] = {
#include "assets/obj_s_station2_v.inc"
};
#endif

Gfx obj_s_station2_t3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_station2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_station2_v[73], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_station2_t2_2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_station2_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_station2_v[53], 20, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 16, 17, 18, 17, 19, 18, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_station2_t1_1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_station2_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_station2_v, 32, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(15, 16, 12, 15, 12, 14, 17, 18, 19, 17, 20, 18),
    gsSPNTriangles_5b(18, 21, 19, 21, 22, 19, 23, 24, 25, 23, 25, 26),
    gsSPNTriangles_5b(27, 28, 29, 27, 29, 30, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_station2_v[31], 22, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 2, 1),
    gsSPNTriangles_5b(12, 1, 13, 14, 12, 13, 14, 13, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 19, 17, 16, 18, 20, 18, 21, 20, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_station2_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_station2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_station2_v[109], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_station2_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_station2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_station2_v[105], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_station2_tbl[] = { { obj_s_station2_t1_1_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 8000, 11200, 6000 } },
                                                { obj_s_station2_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 8000, 11200, 6000 } },
                                                { obj_s_station2_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { obj_s_station2_t2_2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { obj_s_station2_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_s_station2 = { ARRAY_COUNT(cKF_je_r_obj_s_station2_tbl), 5, cKF_je_r_obj_s_station2_tbl };

u8 cKF_ckcb_r_obj_s_station2_tbl[] = { 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_c_obj_s_station2_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_obj_s_station2 = { cKF_ckcb_r_obj_s_station2_tbl, NULL, NULL,
                                              cKF_c_obj_s_station2_tbl,      -1,   25 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_w_station2_t1_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_w_station2_t1_tex_txt[] = {
#include "assets/obj_w_station2_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_station2_t2_tex_txt[0x800];
#else
u8 obj_w_station2_t2_tex_txt[] = {
#include "assets/obj_w_station2_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_station2_t3_tex_txt[0x800];
#else
u8 obj_w_station2_t3_tex_txt[] = {
#include "assets/obj_w_station2_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_station2_v[0x730 / sizeof(Vtx)];
#else
Vtx obj_w_station2_v[] = {
#include "assets/obj_w_station2_v.inc"
};
#endif

Gfx obj_w_station2_t3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_station2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_station2_v[75], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_station2_t2_1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_station2_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_station2_v[55], 20, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 16, 17, 18, 17, 19, 18, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_station2_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_station2_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_station2_v, 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 4, 7, 4, 6, 9, 10, 11, 9, 12, 10),
    gsSPNTriangles_5b(10, 13, 11, 13, 14, 11, 15, 16, 17, 15, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 19, 21, 22, 20, 23, 24, 20, 24, 21),
    gsSPNTriangles_5b(25, 26, 27, 25, 27, 28, 29, 30, 31, 0, 0, 0),
    gsSPVertex(&obj_w_station2_v[32], 23, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 3, 6, 7, 6, 8, 9, 10, 11, 9, 12, 10),
    gsSPNTriangles_5b(9, 11, 13, 11, 14, 13, 15, 16, 17, 15, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 19, 21, 22, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_station2_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_station2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_station2_v[107], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_ststion2_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_station2_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_station2_v[111], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_station2_tbl[] = { { obj_w_station2_t1_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 8000, 11200, 6000 } },
                                                { obj_w_ststion2_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 8000, 11200, 6000 } },
                                                { obj_w_station2_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { obj_w_station2_t2_1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                                { obj_w_station2_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_w_station2 = { ARRAY_COUNT(cKF_je_r_obj_w_station2_tbl), 5, cKF_je_r_obj_w_station2_tbl };

u8 cKF_ckcb_r_obj_w_station2_tbl[] = { 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_c_obj_w_station2_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_obj_w_station2 = { cKF_ckcb_r_obj_w_station2_tbl, NULL, NULL,
                                              cKF_c_obj_w_station2_tbl,      -1,   25 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_station3_t3_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_station3_t3_tex_txt[] = {
#include "assets/obj_s_station3_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_station3_t1_tex_txt[0x800];
#else
u8 obj_s_station3_t1_tex_txt[] = {
#include "assets/obj_s_station3_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_station3_t2_tex_txt[0x800];
#else
u8 obj_s_station3_t2_tex_txt[] = {
#include "assets/obj_s_station3_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_station3_v[0x660 / sizeof(Vtx)];
#else
Vtx obj_s_station3_v[] = {
#include "assets/obj_s_station3_v.inc"
};
#endif

Gfx obj_s_station3_t3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_station3_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_station3_v[82], 20, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_station3_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_station3_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_station3_v[46], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 11, 12, 13, 12, 14, 13),
    gsSPNTriangles_5b(8, 10, 15, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 24, 25, 26, 24, 27, 25, 28, 29, 30),
    gsSPNTriangles_5b(29, 31, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_station3_v[78], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_station3_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_station3_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_station3_v[8], 32, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 19, 22, 20, 23, 24, 25, 24, 26, 25),
    gsSPNTriangles_5b(27, 11, 10, 9, 28, 29, 30, 28, 9, 0, 0, 0),
    gsSPVertex(&obj_s_station3_v[39], 7, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 1, 0, 4, 5, 6),
    gsSPEndDisplayList(),
};

Gfx obj_s_station3_shourt_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_station3_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_station3_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_ststion3_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_station3_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_station3_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_station3_tbl[] = {
    { obj_s_station3_t1_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 8000, 11700, 6000 } },
    { obj_s_ststion3_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 8000, 11700, 6000 } },
    { obj_s_station3_shourt_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_station3_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_s_station3_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_s_station3 = { ARRAY_COUNT(cKF_je_r_obj_s_station3_tbl), 5, cKF_je_r_obj_s_station3_tbl };

u8 cKF_ckcb_r_obj_s_station3_tbl[] = { 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_c_obj_s_station3_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_obj_s_station3 = { cKF_ckcb_r_obj_s_station3_tbl, NULL, NULL,
                                              cKF_c_obj_s_station3_tbl,      -1,   25 };

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_w_station3_t3_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_w_station3_t3_tex_txt[] = {
#include "assets/obj_w_station3_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_station3_t2_tex_txt[0x800];
#else
u8 obj_w_station3_t2_tex_txt[] = {
#include "assets/obj_w_station3_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_station3_t1_tex_txt[0x800];
#else
u8 obj_w_station3_t1_tex_txt[] = {
#include "assets/obj_w_station3_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_station3_v[0x670 / sizeof(Vtx)];
#else
Vtx obj_w_station3_v[] = {
#include "assets/obj_w_station3_v.inc"
};
#endif

Gfx obj_w_station3_t3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_station3_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_station3_v[4], 20, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_station3_t2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_station3_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_station3_v[24], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 11, 12, 13, 12, 14, 13),
    gsSPNTriangles_5b(8, 10, 15, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 24, 25, 26, 24, 14, 25, 27, 28, 29),
    gsSPNTriangles_5b(28, 30, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_station3_v[55], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_station3_t1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_station3_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_station3_v[59], 32, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 19, 22, 20, 23, 24, 25, 24, 26, 25),
    gsSPNTriangles_5b(27, 28, 10, 9, 8, 29, 30, 31, 9, 0, 0, 0),
    gsSPVertex(&obj_w_station3_v[91], 8, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 0, 5, 6, 7),
    gsSPEndDisplayList(),
};

Gfx obj_w_station3_shourt_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_station3_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_station3_v[99], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_ststion3_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_w_station3_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_station3_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_station3_tbl[] = {
    { obj_w_station3_t1_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 8000, 11700, 6000 } },
    { obj_w_ststion3_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 8000, 11700, 6000 } },
    { obj_w_station3_shourt_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_station3_t2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_w_station3_t3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_w_station3 = { ARRAY_COUNT(cKF_je_r_obj_w_station3_tbl), 5, cKF_je_r_obj_w_station3_tbl };

u8 cKF_ckcb_r_obj_w_station3_tbl[] = { 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_c_obj_w_station3_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_obj_w_station3 = { cKF_ckcb_r_obj_w_station3_tbl, NULL, NULL,
                                              cKF_c_obj_w_station3_tbl,      -1,   25 };
