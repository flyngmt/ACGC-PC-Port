#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_barber_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_barber_body_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_barber_body_pal[] = {
#include "assets/int_tak_barber_body_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_barber_glass_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_barber_glass_tex_pic_ci4_pal[] = {
#include "assets/int_tak_barber_glass_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_barber_body_tex_txt[0x100];
#else
u8 int_tak_barber_body_tex_txt[] = {
#include "assets/int_tak_barber_body_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_barber_kosi_tex_txt[0x80];
#else
u8 int_tak_barber_kosi_tex_txt[] = {
#include "assets/int_tak_barber_kosi_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_barber_kasa_tex_txt[0x80];
#else
u8 int_tak_barber_kasa_tex_txt[] = {
#include "assets/int_tak_barber_kasa_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_barber_asi_tex_txt[0x80];
#else
u8 int_tak_barber_asi_tex_txt[] = {
#include "assets/int_tak_barber_asi_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_barber_glass_tex_txt[0x80];
#else
u8 int_tak_barber_glass_tex_txt[] = {
#include "assets/int_tak_barber_glass_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_barber_v[0x3E0 / sizeof(Vtx)];
#else
Vtx int_tak_barber_v[] = {
#include "assets/int_tak_barber_v.inc"
};
#endif

Gfx int_tak_barber_pole_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_barber_body_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_barber_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_barber_v, 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 5, 8, 9, 5, 9, 6, 10, 0, 3),
    gsSPNTriangles_5b(10, 3, 11, 11, 12, 13, 11, 13, 10, 7, 2, 1),
    gsSPNTriangles_5b(7, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_barber_glass_env_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIM_LOD_FRAC, PRIMITIVE, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 60, 255, 255, 255, 20),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_barber_glass_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_barber_glass_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 2, 3),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_barber_v[14], 12, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 5, 8, 9, 5, 9, 6, 10, 0, 3),
    gsSPNTriangles_5b(10, 3, 11, 11, 9, 8, 11, 8, 10, 7, 2, 1),
    gsSPNTriangles_5b(7, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_barber_body_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_barber_body_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_barber_kosi_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_barber_v[26], 26, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 4, 0, 5, 6),
    gsSPNTriangles_5b(0, 7, 8, 0, 9, 10, 0, 11, 12, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_barber_kasa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 13, 14, 15, 16, 17, 15, 18, 19, 15),
    gsSPNTriangles_5b(20, 21, 15, 22, 23, 15, 24, 25, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_barber_asi_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_barber_v[52], 10, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 2, 6, 7),
    gsSPNTriangles_5b(2, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_tak_barber_tbl[] = { 0, 0, 0, 4 };

s16 cKF_kn_int_tak_barber_tbl[] = { 2 };

s16 cKF_c_int_tak_barber_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_tak_barber_tbl[] = { 1, 0, -1091, 100, -3600, -1091 };

cKF_Animation_R_c cKF_ba_r_int_tak_barber = { cKF_ckcb_r_int_tak_barber_tbl,
                                              cKF_ds_int_tak_barber_tbl,
                                              cKF_kn_int_tak_barber_tbl,
                                              cKF_c_int_tak_barber_tbl,
                                              -1,
                                              100 };

cKF_Joint_R_c cKF_je_r_int_tak_barber_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_tak_barber_body_on_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_tak_barber_glass_env_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
    { int_tak_barber_pole_on_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1400, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_tak_barber = { ARRAY_COUNT(cKF_je_r_int_tak_barber_tbl), 3, cKF_je_r_int_tak_barber_tbl };
