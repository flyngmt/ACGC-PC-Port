#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_e_koinobori_t1_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_e_koinobori_t1_tex_txt[] = {
#include "assets/obj_e_koinobori_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_koinobori_t3_tex_txt[0x800];
#else
u8 obj_e_koinobori_t3_tex_txt[] = {
#include "assets/obj_e_koinobori_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_koinobori_v[0xD10 / sizeof(Vtx)];
#else
Vtx obj_e_koinobori_v[] = {
#include "assets/obj_e_koinobori_v.inc"
};
#endif

Gfx obj_e_koinobori_pole_1_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_koinobori_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_koinobori_v[185], 24, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsSPNTriangles_5b(5, 6, 2, 6, 7, 2, 8, 9, 10, 8, 10, 11),
    gsSPNTriangles_5b(12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19),
    gsSPNTriangles_5b(20, 21, 22, 20, 22, 23, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_koinobori_rope_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_koinobori_v[172], 2, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_koinobori_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&obj_e_koinobori_v[174], 3, 2),
    gsSPNTrianglesInit_5b(2, 1, 2, 3, 1, 4, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_koinobori_magoiA_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_2_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_koinobori_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_koinobori_v[90], 10, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 0, 4, 3, 5, 1),
    gsSPNTriangles_5b(3, 6, 5, 3, 4, 6, 6, 7, 5, 5, 7, 8),
    gsSPNTriangles_5b(8, 4, 9, 5, 8, 9, 1, 5, 9, 4, 0, 9),
    gsSPEndDisplayList(),
};

Gfx obj_e_koinobori_magoiB_model[] = {
    gsSPMatrix(&anime_6_mdl[9], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_koinobori_v[74], 4, 0),
    gsSPMatrix(&anime_6_mdl[10], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_2_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_koinobori_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_koinobori_v[78], 12, 4),
    gsSPNTrianglesInit_5b(8, 1, 4, 2, 2, 5, 6, 0, 7, 1),
    gsSPNTriangles_5b(0, 8, 9, 0, 10, 11, 3, 12, 0, 2, 13, 14),
    gsSPNTriangles_5b(2, 15, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_koinobori_magoiC_model[] = {
    gsSPMatrix(&anime_6_mdl[10], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_koinobori_v[50], 4, 0),
    gsSPMatrix(&anime_6_mdl[11], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_2_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_koinobori_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_koinobori_v[54], 20, 4),
    gsSPNTrianglesInit_5b(8, 2, 4, 0, 2, 5, 6, 1, 7, 8),
    gsSPNTriangles_5b(1, 0, 9, 3, 1, 10, 1, 11, 12, 2, 13, 14),
    gsSPNTriangles_5b(3, 15, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(8, 16, 17, 18, 18, 19, 16, 19, 20, 16),
    gsSPNTriangles_5b(20, 21, 16, 22, 21, 20, 22, 20, 23, 22, 23, 18),
    gsSPNTriangles_5b(18, 17, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_koinobori_higoiA_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_koinobori_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_koinobori_v[40], 10, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 0, 4, 3, 5, 1),
    gsSPNTriangles_5b(3, 6, 5, 3, 4, 6, 6, 7, 5, 5, 7, 8),
    gsSPNTriangles_5b(8, 4, 9, 5, 8, 9, 1, 5, 9, 4, 0, 9),
    gsSPEndDisplayList(),
};

Gfx obj_e_koinobori_higoiB_model[] = {
    gsSPMatrix(&anime_6_mdl[6], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_koinobori_v[24], 4, 0),
    gsSPMatrix(&anime_6_mdl[7], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_koinobori_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_koinobori_v[28], 12, 4),
    gsSPNTrianglesInit_5b(8, 1, 4, 2, 2, 5, 6, 0, 7, 1),
    gsSPNTriangles_5b(0, 8, 9, 0, 10, 11, 3, 12, 0, 2, 13, 14),
    gsSPNTriangles_5b(2, 15, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_koinobori_higoiC_model[] = {
    gsSPMatrix(&anime_6_mdl[7], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_koinobori_v, 4, 0),
    gsSPMatrix(&anime_6_mdl[8], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_koinobori_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_koinobori_v[4], 20, 4),
    gsSPNTrianglesInit_5b(8, 2, 4, 0, 2, 5, 6, 1, 7, 8),
    gsSPNTriangles_5b(1, 0, 9, 3, 1, 10, 1, 11, 12, 2, 13, 14),
    gsSPNTriangles_5b(3, 15, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(8, 16, 17, 18, 18, 19, 16, 19, 20, 16),
    gsSPNTriangles_5b(20, 21, 16, 22, 21, 20, 22, 20, 23, 22, 23, 18),
    gsSPNTriangles_5b(18, 17, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_koinobori_fukiA_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_koinobori_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_koinobori_v[160], 12, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 3, 4, 5, 3, 5, 1),
    gsSPNTriangles_5b(4, 6, 7, 4, 7, 5, 6, 8, 9, 6, 9, 7),
    gsSPNTriangles_5b(8, 10, 11, 8, 11, 9, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_koinobori_fukiB_model[] = {
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_koinobori_v[141], 5, 0),
    gsSPMatrix(&anime_6_mdl[4], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_koinobori_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_koinobori_v[146], 14, 5),
    gsSPNTrianglesInit_5b(9, 0, 5, 6, 2, 8, 7, 2, 0, 9),
    gsSPNTriangles_5b(3, 2, 10, 3, 12, 11, 1, 14, 13, 1, 4, 15),
    gsSPNTriangles_5b(4, 3, 16, 4, 18, 17, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_koinobori_fukiC_model[] = {
    gsSPMatrix(&anime_6_mdl[4], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_koinobori_v[100], 6, 0),
    gsSPMatrix(&anime_6_mdl[5], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_koinobori_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_koinobori_v[106], 15, 6),
    gsSPNTrianglesInit_5b(10, 3, 6, 7, 3, 5, 8, 2, 9, 10),
    gsSPNTriangles_5b(2, 3, 11, 0, 12, 13, 0, 2, 14, 5, 15, 16),
    gsSPNTriangles_5b(5, 4, 17, 4, 18, 19, 4, 1, 20, 0, 0, 0),
    gsSPVertex(&obj_e_koinobori_v[121], 20, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_koinobori_yaguruma_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_koinobori_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_koinobori_v[177], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_e_koinobori_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 64536, 63536, 1000 } },
    { obj_e_koinobori_pole_1_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 18000, 1000, 0 } },
    { obj_e_koinobori_yaguruma_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_e_koinobori_rope_model, 3, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 14000, 0, 0 } },
    { obj_e_koinobori_fukiA_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_e_koinobori_fukiB_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 6000, 0, 0 } },
    { obj_e_koinobori_fukiC_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 3000, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 7500, 64536, 0 } },
    { obj_e_koinobori_higoiA_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_e_koinobori_higoiB_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 4500, 0, 0 } },
    { obj_e_koinobori_higoiC_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2500, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 11000, 65036, 0 } },
    { obj_e_koinobori_magoiA_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_e_koinobori_magoiB_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 5250, 0, 0 } },
    { obj_e_koinobori_magoiC_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2750, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_e_koinobori = { ARRAY_COUNT(cKF_je_r_obj_e_koinobori_tbl), 12,
                                              cKF_je_r_obj_e_koinobori_tbl };

u8 cKF_ckcb_r_obj_e_koinobori_tbl[] = { 56, 7, 0, 7, 7, 0, 7, 7, 7, 0, 7, 7, 7, 0, 7, 7, 7 };

s16 cKF_kn_obj_e_koinobori_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 6, 6, 6, 6, 6, 6, 6, 6,
                                     6, 6, 6, 4, 6, 6, 4, 6, 6, 4, 6, 5, 4, 6, 6, 4, 6, 5, 4 };

s16 cKF_c_obj_e_koinobori_tbl[] = { 350, 0, 900, 0, 0, -900, 0, 0, -900, 0, 0, -900, 0, 0, -900 };

s16 cKF_ds_obj_e_koinobori_tbl[] = {
    1,  -1000, 0,    65, -1000, 0,   1,  -2000, 0,    65, -2000, 0,    1,  1000, 0,    65, 1000, 0,    1,  0,   0,
    65, 0,     0,    1,  0,     0,   65, 0,     0,    1,  0,     0,    65, 0,    0,    1,  0,    0,    65, 0,   0,
    1,  0,     0,    65, 0,     0,   1,  0,     5100, 65, 10800, 5100, 1,  0,    0,    65, 0,    0,    1,  0,   0,
    65, 0,     0,    1,  0,     0,   13, 10,    0,    33, -7,    0,    53, 5,    0,    65, 0,    0,    1,  34,  -210,
    13, -50,   0,    29, 50,    0,   45, -50,   0,    61, 50,    0,    65, 34,   -210, 1,  9,    -55,  13, -13, 4,
    29, 13,    0,    45, -13,   0,   61, 13,    0,    65, 9,     -55,  1,  17,   110,  5,  25,   0,    21, -25, 0,
    37, 25,    0,    53, -25,   0,   65, 17,    110,  1,  37,    560,  7,  100,  0,    23, -100, 0,    39, 100, 0,
    55, -100,  0,    65, 37,    560, 1,  9,     120,  7,  25,    0,    23, -25,  0,    39, 25,   0,    55, -25, 0,
    65, 9,     120,  1,  -34,   90,  15, 38,    -3,   31, -38,   0,    47, 38,   0,    63, -38,  0,    65, -34, 90,
    1,  -138,  750,  13, 200,   0,   29, -200,  0,    45, 200,   0,    61, -200, 0,    65, -137, 750,  1,  -26, 141,
    13, 38,    -13,  29, -38,   0,   45, 38,    0,    61, -38,   0,    65, -26,  141,  1,  -52,  -320, 5,  -75, 0,
    21, 75,    0,    37, -75,   0,   53, 75,    0,    65, -52,   -320, 1,  -17,  -94,  5,  -25,  0,    21, 25,  0,
    37, -25,   0,    53, 25,    0,   65, -17,   -94,  1,  -18,   100,  13, 25,   0,    29, -25,  0,    45, 25,  0,
    61, -25,   0,    65, -17,   94,  1,  -46,   94,   29, 50,    0,    61, -50,  0,    65, -46,  94,   1,  46,  -187,
    15, -50,   0,    31, 50,    0,   47, -50,   0,    63, 50,    0,    65, 46,   -188, 1,  -18,  -250, 7,  -50, 0,
    23, 50,    0,    39, -50,   0,   55, 50,    0,    65, -18,   -250, 1,  0,    -210, 17, -75,  0,    49, 75,  0,
    65, 0,     -210, 1,  69,    450, 5,  100,   0,    21, -100,  0,    37, 100,  0,    53, -100, 0,    65, 69,  375,
    1,  52,    -300, 13, -75,   0,   29, 75,    0,    45, -75,   0,    61, 75,   0,    65, 52,   -300, 1,  137, -185,
    29, -150,  0,    61, 150,   0,   65, 137,   -185, 1,  0,     130,  9,  25,   0,    25, -25,  0,    41, 25,  0,
    57, -25,   0,    65, 0,     130, 1,  25,    0,    17, -25,   0,    33, 25,   0,    49, -25,  0,    65, 25,  0,
    1,  0,     140,  17, 50,    0,   49, -50,   0,    65, 0,     140,  1,  -48,  -187, 3,  -50,  0,    19, 50,  0,
    35, -50,   0,    51, 50,    0,   65, -46,   -180, 1,  -18,   300,  11, 50,   0,    27, -50,  0,    43, 50,  0,
    59, -50,   0,    65, -18,   300, 1,  -69,   -90,  5,  -75,   0,    37, 75,   3,    65, -69,  -90,  1,  0,   -500,
    9,  -100,  0,    25, 100,   0,   41, -100,  0,    57, 100,   0,    65, 0,    -500, 1,  -75,  0,    17, 75,  0,
    33, -75,   0,    49, 75,    0,   65, -75,   0,    1,  0,     -425, 17, -150, 0,    49, 150,  0,    65, 0,   -425
};

cKF_Animation_R_c cKF_ba_r_obj_e_koinobori = { cKF_ckcb_r_obj_e_koinobori_tbl,
                                               cKF_ds_obj_e_koinobori_tbl,
                                               cKF_kn_obj_e_koinobori_tbl,
                                               cKF_c_obj_e_koinobori_tbl,
                                               -1,
                                               65 };
