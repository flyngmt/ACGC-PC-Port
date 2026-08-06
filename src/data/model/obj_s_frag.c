#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_frag_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_frag_pal[] = {
#include "assets/obj_s_frag_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_frag_t3_tex_txt[0x100];
#else
u8 obj_s_frag_t3_tex_txt[] = {
#include "assets/obj_s_frag_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_frag_t1_tex_txt[0x200];
#else
u8 obj_s_frag_t1_tex_txt[] = {
#include "assets/obj_s_frag_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_frag_t2_tex_txt[0x100];
#else
u8 obj_s_frag_t2_tex_txt[] = {
#include "assets/obj_s_frag_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_frag_v[0x7A0 / sizeof(Vtx)];
#else
Vtx obj_s_frag_v[] = {
#include "assets/obj_s_frag_v.inc"
};
#endif

Gfx obj_s_frag_pole_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_frag_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 8, obj_s_frag_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_frag_v[114], 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, obj_s_frag_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_frag_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_frag_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, obj_s_frag_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_frag_v[108], 6, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_frag_wire_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_frag_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, obj_s_frag_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_frag_v[98], 4, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, obj_s_frag_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_s_frag_v[102], 6, 4),
    gsSPNTrianglesInit_5b(4, 0, 1, 4, 1, 6, 5, 2, 3, 7),
    gsSPNTriangles_5b(3, 9, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_frag_fragA_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_frag_v[82], 16, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 3, 6, 5, 7, 3, 7, 2, 3, 8, 9, 10),
    gsSPNTriangles_5b(8, 11, 9, 11, 12, 9, 11, 13, 12, 13, 11, 14),
    gsSPNTriangles_5b(13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_frag_fragB_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_s_frag_v[48], 10, 0),
    gsSPMatrix(&anime_6_mdl[4], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&obj_s_frag_v[58], 20, 10),
    gsSPNTrianglesInit_5b(13, 1, 10, 0, 1, 11, 12, 1, 4, 13),
    gsSPNTriangles_5b(4, 14, 15, 4, 16, 17, 4, 3, 18, 3, 19, 20),
    gsSPNTriangles_5b(3, 2, 21, 6, 5, 22, 5, 23, 24, 5, 7, 25),
    gsSPNTriangles_5b(7, 26, 27, 7, 28, 29, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_frag_v[78], 4, 10),
    gsSPNTrianglesInit_5b(3, 7, 8, 10, 8, 11, 12, 9, 13, 8),
    gsSPEndDisplayList(),
};

Gfx obj_s_frag_fragC_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[4], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_frag_v, 10, 0),
    gsSPMatrix(&anime_6_mdl[5], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&obj_s_frag_v[10], 20, 10),
    gsSPNTrianglesInit_5b(13, 1, 10, 0, 1, 11, 12, 1, 2, 13),
    gsSPNTriangles_5b(2, 14, 15, 2, 16, 17, 2, 3, 18, 3, 19, 20),
    gsSPNTriangles_5b(3, 4, 21, 5, 6, 22, 6, 23, 24, 6, 7, 25),
    gsSPNTriangles_5b(7, 26, 27, 7, 28, 29, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_s_frag_v[30], 18, 10),
    gsSPNTrianglesInit_5b(3, 7, 8, 10, 8, 11, 12, 9, 13, 8),
    gsSPNTrianglesInit_5b(10, 14, 15, 16, 14, 17, 15, 18, 19, 17),
    gsSPNTriangles_5b(18, 20, 19, 17, 19, 15, 21, 22, 23, 22, 24, 25),
    gsSPNTriangles_5b(23, 22, 25, 21, 23, 26, 27, 21, 26, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_frag_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 65036, 63536, 0 } },
                                            { obj_s_frag_pole_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { obj_s_frag_base_model, 1, cKF_JOINT_FLAG_DISP_XLU, { 1000, 0, 0 } },
                                            { obj_s_frag_wire_model, 1, cKF_JOINT_FLAG_DISP_XLU, { 1000, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 13250, 64536, 0 } },
                                            { obj_s_frag_fragA_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { obj_s_frag_fragB_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1250, 0, 0 } },
                                            { obj_s_frag_fragC_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1250, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_s_frag = { ARRAY_COUNT(cKF_je_r_obj_s_frag_tbl), 6, cKF_je_r_obj_s_frag_tbl };

u8 cKF_ckcb_r_obj_s_frag_tbl[] = { 0, 0, 0, 1, 0, 2, 2, 2 };

s16 cKF_kn_obj_s_frag_tbl[] = { 3, 5, 4, 5 };

s16 cKF_c_obj_s_frag_tbl[] = { -500, -2000, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_s_frag_tbl[] = { 1,  5,   -1, 40,   -4, 10,  65,   5,   1,  1,   100, -17, 11,   54,   -241, 35,   -98,
                                66, 64,  99, 34,   65, 100, 17,   1,   0,  562, 18,  199, -67,  50,   -199, 67,   65,
                                0,  562, 1,  -300, 52, 4,   -285, 286, 33, 300, 0,   64,  -298, -101, 65,   -300, -52 };

cKF_Animation_R_c cKF_ba_r_obj_s_frag = {
    cKF_ckcb_r_obj_s_frag_tbl, cKF_ds_obj_s_frag_tbl, cKF_kn_obj_s_frag_tbl, cKF_c_obj_s_frag_tbl, -1, 65
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_frag_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_frag_pal[] = {
#include "assets/obj_w_frag_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_frag_t3_tex_txt[0x100];
#else
u8 obj_w_frag_t3_tex_txt[] = {
#include "assets/obj_w_frag_t3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_frag_t1_tex_txt[0x200];
#else
u8 obj_w_frag_t1_tex_txt[] = {
#include "assets/obj_w_frag_t1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_frag_t2_tex_txt[0x100];
#else
u8 obj_w_frag_t2_tex_txt[] = {
#include "assets/obj_w_frag_t2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_frag_v[0x7A0 / sizeof(Vtx)];
#else
Vtx obj_w_frag_v[] = {
#include "assets/obj_w_frag_v.inc"
};
#endif

Gfx obj_w_frag_pole_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_frag_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 8, obj_w_frag_t1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_frag_v[114], 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, obj_w_frag_t2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_frag_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_frag_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, obj_w_frag_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_frag_v[108], 6, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_frag_wire_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_frag_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, obj_w_frag_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_frag_v[98], 4, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, obj_w_frag_t3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_w_frag_v[102], 6, 4),
    gsSPNTrianglesInit_5b(4, 0, 1, 4, 1, 6, 5, 2, 3, 7),
    gsSPNTriangles_5b(3, 9, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_frag_fragA_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_frag_v[82], 16, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 3, 6, 5, 7, 3, 7, 2, 3, 8, 9, 10),
    gsSPNTriangles_5b(8, 11, 9, 11, 12, 9, 11, 13, 12, 13, 11, 14),
    gsSPNTriangles_5b(13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_w_frag_fragB_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_w_frag_v[48], 10, 0),
    gsSPMatrix(&anime_6_mdl[4], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&obj_w_frag_v[58], 20, 10),
    gsSPNTrianglesInit_5b(13, 1, 10, 0, 1, 11, 12, 1, 4, 13),
    gsSPNTriangles_5b(4, 14, 15, 4, 16, 17, 4, 3, 18, 3, 19, 20),
    gsSPNTriangles_5b(3, 2, 21, 6, 5, 22, 5, 23, 24, 5, 7, 25),
    gsSPNTriangles_5b(7, 26, 27, 7, 28, 29, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_frag_v[78], 4, 10),
    gsSPNTrianglesInit_5b(3, 7, 8, 10, 8, 11, 12, 9, 13, 8),
    gsSPEndDisplayList(),
};

Gfx obj_w_frag_fragC_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPMatrix(&anime_6_mdl[4], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_frag_v, 10, 0),
    gsSPMatrix(&anime_6_mdl[5], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_w_frag_v[10], 20, 10),
    gsSPNTrianglesInit_5b(13, 1, 10, 0, 1, 11, 12, 1, 2, 13),
    gsSPNTriangles_5b(2, 14, 15, 2, 16, 17, 2, 3, 18, 3, 19, 20),
    gsSPNTriangles_5b(3, 4, 21, 5, 6, 22, 6, 23, 24, 6, 7, 25),
    gsSPNTriangles_5b(7, 26, 27, 7, 28, 29, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_w_frag_v[30], 18, 10),
    gsSPNTrianglesInit_5b(3, 7, 8, 10, 8, 11, 12, 9, 13, 8),
    gsSPNTrianglesInit_5b(10, 14, 15, 16, 14, 17, 15, 18, 19, 17),
    gsSPNTriangles_5b(18, 20, 19, 17, 19, 15, 21, 22, 23, 22, 24, 25),
    gsSPNTriangles_5b(23, 22, 25, 21, 23, 26, 27, 21, 26, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_w_frag_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 65036, 63536, 0 } },
                                            { obj_w_frag_pole_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { obj_w_frag_base_model, 1, cKF_JOINT_FLAG_DISP_XLU, { 1000, 0, 0 } },
                                            { obj_w_frag_wire_model, 1, cKF_JOINT_FLAG_DISP_XLU, { 1000, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 13250, 64536, 0 } },
                                            { obj_w_frag_fragA_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { obj_w_frag_fragB_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1250, 0, 0 } },
                                            { obj_w_frag_fragC_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1250, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_w_frag = { ARRAY_COUNT(cKF_je_r_obj_w_frag_tbl), 6, cKF_je_r_obj_w_frag_tbl };

u8 cKF_ckcb_r_obj_w_frag_tbl[] = { 0, 0, 0, 1, 0, 2, 2, 2 };

s16 cKF_kn_obj_w_frag_tbl[] = { 3, 5, 4, 5 };

s16 cKF_c_obj_w_frag_tbl[] = { -500, -2000, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -900, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_w_frag_tbl[] = { 1,  5,   -1, 40,   -4, 10,  65,   5,   1,  1,   100, -17, 11,   54,   -241, 35,   -98,
                                66, 64,  99, 34,   65, 100, 17,   1,   0,  562, 18,  199, -67,  50,   -199, 67,   65,
                                0,  562, 1,  -300, 52, 4,   -285, 286, 33, 300, 0,   64,  -298, -101, 65,   -300, -52 };

cKF_Animation_R_c cKF_ba_r_obj_w_frag = {
    cKF_ckcb_r_obj_w_frag_tbl, cKF_ds_obj_w_frag_tbl, cKF_kn_obj_w_frag_tbl, cKF_c_obj_w_frag_tbl, -1, 65
};
