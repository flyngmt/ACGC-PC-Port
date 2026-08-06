#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_post_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_post_pal[] = {
#include "assets/obj_s_post_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_post_flag1_tex_txt[0x100];
#else
u8 obj_s_post_flag1_tex_txt[] = {
#include "assets/obj_s_post_flag1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_post_flag2_TA_tex_txt[0x100];
#else
u8 obj_s_post_flag2_TA_tex_txt[] = {
#include "assets/obj_s_post_flag2_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_post_flag3_TA_tex_txt[0x100];
#else
u8 obj_s_post_flag3_TA_tex_txt[] = {
#include "assets/obj_s_post_flag3_TA_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_post_front1_tex_txt[0x100];
#else
u8 obj_s_post_front1_tex_txt[] = {
#include "assets/obj_s_post_front1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_post_front2_tex_txt[0x100];
#else
u8 obj_s_post_front2_tex_txt[] = {
#include "assets/obj_s_post_front2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_post_side1_tex_txt[0x200];
#else
u8 obj_s_post_side1_tex_txt[] = {
#include "assets/obj_s_post_side1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_post_leg1_tex_txt[0x80];
#else
u8 obj_s_post_leg1_tex_txt[] = {
#include "assets/obj_s_post_leg1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_post_inside1_tex_txt[0x80];
#else
u8 obj_s_post_inside1_tex_txt[] = {
#include "assets/obj_s_post_inside1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_post_v[0x350 / sizeof(Vtx)];
#else
Vtx obj_s_post_v[] = {
#include "assets/obj_s_post_v.inc"
};
#endif

Gfx obj_s_post_main_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_post_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_s_post_side1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&obj_s_post_v[16], 25, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 6, 7, 8, 6, 8, 9, 10, 11, 9),
    gsSPNTriangles_5b(10, 9, 12, 7, 13, 14, 7, 14, 8, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_s_post_leg1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 15, 16, 17, 15, 17, 18, 19, 20, 21),
    gsSPNTriangles_5b(19, 21, 22, 16, 19, 22, 16, 22, 17, 23, 15, 18),
    gsSPNTriangles_5b(23, 18, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_s_post_inside1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_s_post_v[41], 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 6, 0, 3, 6, 3, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 9, 6, 7, 9, 7, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_post_front_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_post_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, obj_s_post_front1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&obj_s_post_v[8], 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, obj_s_post_front2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_post_flag_saki_model[] = {
    gsSPVertex(&obj_s_post_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_post_flag_ne_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_post_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, obj_s_post_flag1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(obj_s_post_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_obj_s_post_tbl[] = { { obj_s_post_main_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 550, 0, 65086 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 63656, 2200, 100 } },
                                            { obj_s_post_flag_ne_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { obj_s_post_flag_saki_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 64369, 2000, 1167 } },
                                            { obj_s_post_front_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_obj_s_post = { ARRAY_COUNT(cKF_je_r_obj_s_post_tbl), 4, cKF_je_r_obj_s_post_tbl };
