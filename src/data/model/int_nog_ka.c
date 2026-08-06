#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_ka_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_ka_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_ka_pal[] = {
#include "assets/int_nog_ka_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_nog_ka_glass_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_nog_ka_glass_tex_pic_ci4_pal[] = {
#include "assets/int_nog_ka_glass_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_ka_body_tex_txt[0x180];
#else
u8 int_nog_ka_body_tex_txt[] = {
#include "assets/int_nog_ka_body_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_ka_side_tex_txt[0x200];
#else
u8 int_nog_ka_side_tex_txt[] = {
#include "assets/int_nog_ka_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_ka_base_tex_txt[0x80];
#else
u8 int_nog_ka_base_tex_txt[] = {
#include "assets/int_nog_ka_base_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_ka_top_tex_txt[0x200];
#else
u8 int_nog_ka_top_tex_txt[] = {
#include "assets/int_nog_ka_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_ka_glass_tex_txt[0x100];
#else
u8 int_nog_ka_glass_tex_txt[] = {
#include "assets/int_nog_ka_glass_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_ka_v[0x410 / sizeof(Vtx)];
#else
Vtx int_nog_ka_v[] = {
#include "assets/int_nog_ka_v.inc"
};
#endif

Gfx int_nog_ka_wing_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_ka_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_nog_ka_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_ka_v, 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_ka_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_ka_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_nog_ka_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_ka_v[8], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_ka_side_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 140),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_ka_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_ka_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_ka_v[20], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 1, 6, 7, 1, 7, 2, 6, 8, 9),
    gsSPNTriangles_5b(6, 9, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_ka_komado_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 140),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_ka_glass_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_nog_ka_glass_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 3),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_ka_v[16], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_ka_glass_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 70),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_ka_glass_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_nog_ka_glass_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 5),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_ka_v[30], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 7, 6, 1, 7, 1, 0, 4, 8, 9),
    gsSPNTriangles_5b(4, 9, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_ka_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_ka_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_ka_base_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_ka_v[40], 25, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 1, 0, 0, 4, 3),
    gsSPNTriangles_5b(0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_ka_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 5, 6, 7, 6, 8, 7, 9, 10, 11),
    gsSPNTriangles_5b(9, 12, 10, 13, 14, 15, 13, 16, 14, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 21, 22, 23, 21, 23, 24, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_nog_ka_tbl[] = { 0, 0, 0, 0, 0, 7, 0 };

s16 cKF_kn_int_nog_ka_tbl[] = { 4, 6, 5 };

s16 cKF_c_int_nog_ka_tbl[] = { 750, -5000, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_nog_ka_tbl[] = { 1,  0,   5056, 17, 1800, 0,    49, -1800, 0,   65, 0,   5056, 1,  0,   -448,
                                10, -79, 84,   25, 50,   5,    43, -44,   158, 58, 78,  -103, 65, 0,   -448,
                                1,  200, -22,  10, 152,  -284, 34, -49,   42,  64, 199, 42,   65, 200, 22 };

cKF_Animation_R_c cKF_ba_r_int_nog_ka = {
    cKF_ckcb_r_int_nog_ka_tbl, cKF_ds_int_nog_ka_tbl, cKF_kn_int_nog_ka_tbl, cKF_c_int_nog_ka_tbl, -1, 65
};

cKF_Joint_R_c cKF_je_r_int_nog_ka_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 750, 60536, 0 } },
                                            { int_nog_ka_base_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                            { int_nog_ka_glass_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                            { int_nog_ka_komado_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                            { int_nog_ka_side_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                            { int_nog_ka_body_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } },
                                            { int_nog_ka_wing_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_int_nog_ka = { ARRAY_COUNT(cKF_je_r_int_nog_ka_tbl), 6, cKF_je_r_int_nog_ka_tbl };
