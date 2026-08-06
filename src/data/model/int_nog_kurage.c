#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_kurage_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_kurage_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_kurage_pal[] = {
#include "assets/int_nog_kurage_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_nog_kurage_glass_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_nog_kurage_glass_tex_pic_ci4_pal[] = {
#include "assets/int_nog_kurage_glass_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_kurage_head_tex_txt[0x100];
#else
u8 int_nog_kurage_head_tex_txt[] = {
#include "assets/int_nog_kurage_head_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_kurage_foot_tex_txt[0x100];
#else
u8 int_nog_kurage_foot_tex_txt[] = {
#include "assets/int_nog_kurage_foot_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_kurage_side_tex_txt[0x200];
#else
u8 int_nog_kurage_side_tex_txt[] = {
#include "assets/int_nog_kurage_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_kurage_base_tex_txt[0x80];
#else
u8 int_nog_kurage_base_tex_txt[] = {
#include "assets/int_nog_kurage_base_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_kurage_top_tex_txt[0x100];
#else
u8 int_nog_kurage_top_tex_txt[] = {
#include "assets/int_nog_kurage_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_kurage_glass_tex_pic_ci4[0x100];
#else
u8 int_nog_kurage_glass_tex_pic_ci4[] = {
#include "assets/int_nog_kurage_glass_tex_pic_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_kurage_v[0x3E0 / sizeof(Vtx)];
#else
Vtx int_nog_kurage_v[] = {
#include "assets/int_nog_kurage_v.inc"
};
#endif

Gfx int_nog_kurage_head_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_kurage_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_nog_kurage_head_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_kurage_v, 10, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 4, 3, 8, 5, 4, 8, 0, 7, 9),
    gsSPNTriangles_5b(1, 0, 9, 0, 3, 7, 3, 4, 7, 6, 9, 7),
    gsSPNTriangles_5b(3, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_kurage_top_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIM_LOD_FRAC, PRIMITIVE, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 100, 255, 255, 255, 80),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_kurage_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_nog_kurage_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_kurage_v[58], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_kurage_evw_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 80),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_kurage_glass_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_nog_kurage_glass_tex_pic_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_kurage_v[48], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 5, 4, 6, 5, 6, 7, 7, 6, 8),
    gsSPNTriangles_5b(7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_kurage_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_kurage_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_kurage_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_kurage_v[27], 21, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_nog_kurage_base_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 17, 19, 18, 19, 20, 18),
    gsSPNTriangles_5b(20, 16, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_kurage_foot_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_kurage_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_nog_kurage_foot_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_kurage_v[10], 17, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 2, 3, 4, 2, 4, 0),
    gsSPNTriangles_5b(5, 6, 3, 5, 3, 7, 7, 8, 5, 9, 10, 11),
    gsSPNTriangles_5b(11, 4, 12, 11, 12, 9, 13, 12, 14, 13, 14, 15),
    gsSPNTriangles_5b(15, 16, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_nog_kurage_tbl[] = { 56, 7, 0, 5, 0, 0, 7 };

s16 cKF_kn_int_nog_kurage_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 5, 2, 2, 3 };

s16 cKF_c_int_nog_kurage_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_nog_kurage_tbl[] = { 1,   -6500, 0,   257, -6500, 0,   1,   1375, 0,   257, 1375, 0,   1,   0,  0,  257,
                                    0,   0,     1,   0,   0,     257, 0,   0,    1,   0,   0,    257, 0,   0,  1,  0,
                                    0,   257,   0,   0,   1,     0,   0,   257,  0,   0,   1,    46,  13,  17, 50, 0,
                                    145, -25,   0,   209, 25,    0,   257, 46,   13,  1,   0,    0,   257, 0,  0,  1,
                                    0,   0,     257, 0,   0,     1,   50,  0,    129, -25, 0,    257, 50,  0 };

cKF_Animation_R_c cKF_ba_r_int_nog_kurage = { cKF_ckcb_r_int_nog_kurage_tbl,
                                              cKF_ds_int_nog_kurage_tbl,
                                              cKF_kn_int_nog_kurage_tbl,
                                              cKF_c_int_nog_kurage_tbl,
                                              -1,
                                              257 };

cKF_Joint_R_c cKF_je_r_int_nog_kurage_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 59036, 1375, 0 } },
    { int_sum_kurage_base_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } },
    { int_nog_kurage_foot_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_kurage_evw_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_sum_kurage_top_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_nog_kurage_head_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_nog_kurage = { ARRAY_COUNT(cKF_je_r_int_nog_kurage_tbl), 5, cKF_je_r_int_nog_kurage_tbl };
