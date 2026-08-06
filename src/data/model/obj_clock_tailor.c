#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx obj_clock_tailor_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_clock_tailor_1_tex_txt[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_clock_tailor_1_tex_txt[] = {
#include "assets/obj_clock_tailor_1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_clock_tailor_2_tex_txt[0x200];
#else
u8 obj_clock_tailor_2_tex_txt[] = {
#include "assets/obj_clock_tailor_2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_clock_tailor_v[0x3E0 / sizeof(Vtx)];
#else
Vtx obj_clock_tailor_v[] = {
#include "assets/obj_clock_tailor_v.inc"
};
#endif

Gfx obj_clock_tailor_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 64, obj_clock_tailor_1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_clock_tailor_v[13], 28, 0),
    gsSPNTriangles(18, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 6, 9, 8, 4, 6, 10, 11, 9),
    gsSPNTriangles_5b(11, 8, 9, 12, 13, 14, 12, 15, 13, 16, 12, 17),
    gsSPNTriangles_5b(12, 14, 17, 18, 19, 20, 18, 21, 19, 22, 18, 20),
    gsSPNTriangles_5b(22, 23, 18, 24, 25, 26, 24, 27, 25, 0, 0, 0),
    gsSPVertex(&obj_clock_tailor_v[41], 21, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTriangles(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTriangles(10, 8, 9, 10, 8, 11, 9, 11, 12, 9),
    gsSPNTriangles_5b(12, 13, 9, 13, 14, 9, 14, 15, 9, 15, 16, 9),
    gsSPNTriangles_5b(16, 10, 9, 17, 18, 19, 18, 20, 19, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_clock_tailor_long_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 64, obj_clock_tailor_1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_clock_tailor_v, 5, 0),
    gsSPNTriangles(3, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsSPEndDisplayList(),
};

Gfx obj_clock_tailor_short_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 64, obj_clock_tailor_1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_clock_tailor_v[5], 5, 0),
    gsSPNTriangles(3, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsSPEndDisplayList(),
};

Gfx obj_clock_tailor_furi_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, obj_clock_tailor_2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_clock_tailor_v[10], 3, 0),
    gsSPNTriangles(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_obj_clock_tailor_tbl[] = { 0, 0, 0, 1, 0, 0, 0 };

s16 cKF_kn_obj_clock_tailor_tbl[] = { 5 };

s16 cKF_c_obj_clock_tailor_tbl[] = { 20000, 10000, 5000, 0, 0,    0, 0, 0,   900, 0, 0, -900,
                                     0,     0,     0,    0, -900, 0, 0, 900, 0,   0, 0 };

s16 cKF_ds_obj_clock_tailor_tbl[] = { 1, -1100, 39, 5, -1081, 276, 32, -701, -76, 60, -1099, -76, 61, -1100, -39 };

cKF_Animation_R_c cKF_ba_r_obj_clock_tailor = { cKF_ckcb_r_obj_clock_tailor_tbl,
                                                cKF_ds_obj_clock_tailor_tbl,
                                                cKF_kn_obj_clock_tailor_tbl,
                                                cKF_c_obj_clock_tailor_tbl,
                                                -1,
                                                61 };

cKF_Joint_R_c cKF_je_r_obj_clock_tailor_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 20000, 10000, 5000 } },
    { obj_clock_tailor_base_model, 3, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1100, 0, 65136 } },
    { obj_clock_tailor_furi_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 65436 } },
    { obj_clock_tailor_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_clock_tailor_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_clock_tailor = { ARRAY_COUNT(cKF_je_r_obj_clock_tailor_tbl), 4,
                                               cKF_je_r_obj_clock_tailor_tbl };
