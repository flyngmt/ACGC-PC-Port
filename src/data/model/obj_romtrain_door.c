#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx obj_romtrain_door_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_romtrain_door_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_romtrain_door_pal[] = {
#include "assets/obj_romtrain_door_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_romtrain_door_tex_txt[0x400];
#else
u8 obj_romtrain_door_tex_txt[] = {
#include "assets/obj_romtrain_door_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_romtrain_glass_tex_txt[0x100];
#else
u8 obj_romtrain_glass_tex_txt[] = {
#include "assets/obj_romtrain_glass_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_romtrain_door_v[0xF0 / sizeof(Vtx)];
#else
Vtx obj_romtrain_door_v[] = {
#include "assets/obj_romtrain_door_v.inc"
};
#endif

Gfx obj_romtrain_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_romtrain_door_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_romtrain_door_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_romtrain_door_v[12], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_romtrain_glass_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 150),
    gsDPSetEnvColor(100, 200, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, obj_romtrain_glass_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_romtrain_door_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_romtrain_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_romtrain_door_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_romtrain_door_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_romtrain_door_v, 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_romtrain_door_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 51036 } },
    { obj_romtrain_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_romtrain_door_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 16000, 0, 0 } },
    { obj_romtrain_glass_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_romtrain_door = { ARRAY_COUNT(cKF_je_r_obj_romtrain_door_tbl), 3,
                                                cKF_je_r_obj_romtrain_door_tbl };
