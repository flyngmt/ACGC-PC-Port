#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_kingyo_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_kingyo_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_kingyo_pal[] = {
#include "assets/int_sum_kingyo/int_sum_kingyo_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_sum_kingyo_top_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_sum_kingyo_top_pic_ci4_pal[] = {
#include "assets/int_sum_kingyo_top_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_sum_kingyo_front_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_sum_kingyo_front_pic_ci4_pal[] = {
#include "assets/int_sum_kingyo_front_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kingyo_body_txt[0x200];
#else
u8 int_sum_kingyo_body_txt[] = {
#include "assets/int_sum_kingyo_body_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kingyo_kuchi_txt[0x80];
#else
u8 int_sum_kingyo_kuchi_txt[] = {
#include "assets/int_sum_kingyo_kuchi_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kingyo_etc_txt[0x80];
#else
u8 int_sum_kingyo_etc_txt[] = {
#include "assets/int_sum_kingyo_etc_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kingyo_top_txt[0x80];
#else
u8 int_sum_kingyo_top_txt[] = {
#include "assets/int_sum_kingyo_top_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_kingyo_front_txt[0x200];
#else
u8 int_sum_kingyo_front_txt[] = {
#include "assets/int_sum_kingyo_front_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_kingyo_v[0x320 / sizeof(Vtx)];
#else
Vtx int_sum_kingyo_v[] = {
#include "assets/int_sum_kingyo_v.inc"
};
#endif

Gfx int_sum_kingyo_sakana_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_kingyo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_kingyo_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_kingyo_v, 10, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(1, 5, 4, 0, 6, 1, 6, 5, 1, 6, 7, 5),
    gsSPNTriangles_5b(6, 8, 7, 9, 5, 6, 9, 6, 0, 4, 5, 9),
    gsSPNTriangles_5b(3, 4, 9, 2, 3, 9, 2, 9, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_kingyo_glass_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 60),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_kingyo_top_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_kingyo_top_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_kingyo_v[34], 16, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 2, 1, 4, 1, 5),
    gsSPNTriangles_5b(6, 5, 1, 7, 8, 9, 10, 9, 8, 11, 5, 9),
    gsSPNTriangles_5b(12, 9, 5, 13, 8, 14, 15, 14, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_kingyo_body_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 240),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_kingyo_front_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_kingyo_front_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_kingyo_v[24], 10, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 1, 0, 4, 3, 0),
    gsSPNTriangles_5b(4, 0, 2, 1, 5, 2, 1, 3, 5, 6, 7, 4),
    gsSPNTriangles_5b(8, 7, 6, 6, 4, 9, 9, 8, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_kingyo_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_kingyo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_kingyo_kuchi_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_kingyo_v[10], 14, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 2, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 4, 6, 9, 7, 10, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_kingyo_etc_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 11, 12, 13, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_sum_kingyo_tbl[] = { 56, 7, 0, 0, 7 };

s16 cKF_kn_int_sum_kingyo_tbl[] = { 2, 2, 2, 2, 2, 2, 6, 5, 7 };

s16 cKF_c_int_sum_kingyo_tbl[] = { 0, 0, 900, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_sum_kingyo_tbl[] = { 1,   0,    0,    513, 0,    0,    1,   -5000, 0,  513, -5000, 0,   1,   0,    0,
                                    513, 0,    0,    1,   0,    0,    513, 0,     0,  1,   0,     0,   513, 0,    0,
                                    1,   0,    0,    513, 0,    0,    1,   400,   5,  89,  400,   460, 138, 2500, 500,
                                    360, 1500, -701, 424, 1050, -216, 513, 400,   0,  1,   -25,   -6,  89,  -40,  -4,
                                    113, -40,  10,   334, 45,   1,    513, -25,   0,  1,   -60,   6,   89,  35,   21,
                                    113, 20,   -46,  138, -40,  2,    309, 30,    -1, 360, -50,   -13, 513, -60,  0 };

cKF_Animation_R_c cKF_ba_r_int_sum_kingyo = { cKF_ckcb_r_int_sum_kingyo_tbl,
                                              cKF_ds_int_sum_kingyo_tbl,
                                              cKF_kn_int_sum_kingyo_tbl,
                                              cKF_c_int_sum_kingyo_tbl,
                                              -1,
                                              513 };

cKF_Joint_R_c cKF_je_r_int_sum_kingyo_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 60536, 0 } },
    { int_sum_kingyo_base_model, 3, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_sum_kingyo_body_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_sum_kingyo_glass_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_sum_kingyo_sakana_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_sum_kingyo = { ARRAY_COUNT(cKF_je_r_int_sum_kingyo_tbl), 4, cKF_je_r_int_sum_kingyo_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_sum_kingyo_c(void) {
    pc_load_asset("assets/int_sum_kingyo/int_sum_kingyo_pal.bin", int_sum_kingyo_pal, 0x20, 0xCEB880, 0, 1);
}
#endif
