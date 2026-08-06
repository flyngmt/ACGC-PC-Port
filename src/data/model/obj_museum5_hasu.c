#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx obj_museum5_hasu_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_museum5_hasu_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_museum5_hasu_pal[] = {
#include "assets/obj_museum5_hasu_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_museum5_hasu1_tex_txt[0x200];
#else
u8 obj_museum5_hasu1_tex_txt[] = {
#include "assets/obj_museum5_hasu1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_museum5_hasu_v[0x170 / sizeof(Vtx)];
#else
Vtx obj_museum5_hasu_v[] = {
#include "assets/obj_museum5_hasu_v.inc"
};
#endif

Gfx obj_museum5_hasu1_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_museum5_hasu_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_museum5_hasu1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_museum5_hasu_v, 5, 0),
    gsSPNTriangles(4, 0, 1, 2, 1, 3, 2, 0, 4, 1),
    gsSPNTriangles_5b(4, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_museum5_hasu3_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_museum5_hasu_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_museum5_hasu1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_museum5_hasu_v[5], 9, 0),
    gsSPNTriangles(6, 0, 1, 2, 0, 3, 1, 0, 4, 5),
    gsSPNTriangles_5b(0, 6, 4, 0, 7, 6, 0, 8, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_museum5_hasu2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_museum5_hasu_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_museum5_hasu1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_museum5_hasu_v[14], 9, 0),
    gsSPNTriangles(6, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsSPNTriangles_5b(0, 5, 4, 0, 6, 7, 0, 8, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_museum5_hasu_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 3390, 0, 2800 } },
    { NULL, 3, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 64306, 62436, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_museum5_hasu2_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 50, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 690, 63086, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_museum5_hasu3_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 50, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 200, 0, 0 } },
    { obj_museum5_hasu1_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 50, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_museum5_hasu = { ARRAY_COUNT(cKF_je_r_obj_museum5_hasu_tbl), 3,
                                               cKF_je_r_obj_museum5_hasu_tbl };
