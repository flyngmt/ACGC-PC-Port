#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_eisei_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_eisei_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_eisei_pal[] = {
#include "assets/int_tak_eisei_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_tak_eisei_hansya_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_tak_eisei_hansya_tex_pic_ci4_pal[] = {
#include "assets/int_tak_eisei_hansya_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_eisei_omote_tex_txt[0x100];
#else
u8 int_tak_eisei_omote_tex_txt[] = {
#include "assets/int_tak_eisei_omote_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_eisei_ura_tex_txt[0x100];
#else
u8 int_tak_eisei_ura_tex_txt[] = {
#include "assets/int_tak_eisei_ura_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_eisei_top_tex_txt[0x80];
#else
u8 int_tak_eisei_top_tex_txt[] = {
#include "assets/int_tak_eisei_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_eisei_body_tex_txt[0x180];
#else
u8 int_tak_eisei_body_tex_txt[] = {
#include "assets/int_tak_eisei_body_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_eisei_kasa_tex_txt[0x80];
#else
u8 int_tak_eisei_kasa_tex_txt[] = {
#include "assets/int_tak_eisei_kasa_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_eisei_ten_tex_txt[0x80];
#else
u8 int_tak_eisei_ten_tex_txt[] = {
#include "assets/int_tak_eisei_ten_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_eisei_sasae_tex_txt[0x80];
#else
u8 int_tak_eisei_sasae_tex_txt[] = {
#include "assets/int_tak_eisei_sasae_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_eisei_antena_tex_txt[0x80];
#else
u8 int_tak_eisei_antena_tex_txt[] = {
#include "assets/int_tak_eisei_antena_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_eisei_hansya_tex_txt[0x80];
#else
u8 int_tak_eisei_hansya_tex_txt[] = {
#include "assets/int_tak_eisei_hansya_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_eisei_v[0x4B0 / sizeof(Vtx)];
#else
Vtx int_tak_eisei_v[] = {
#include "assets/int_tak_eisei_v.inc"
};
#endif

Gfx int_tak_eisei_ude_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_eisei_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_eisei_omote_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_eisei_v[8], 18, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 3, 4, 5, 6, 7, 8, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_eisei_ura_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 15, 16, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_eisei_ude_env_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_eisei_hansya_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_eisei_hansya_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 4),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(int_tak_eisei_v, 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_eisei_base_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_eisei_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_eisei_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_eisei_v[26], 25, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_tak_eisei_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(10, 5, 6, 7, 6, 8, 7, 9, 10, 11),
    gsSPNTriangles_5b(10, 12, 11, 13, 14, 15, 14, 16, 15, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 19, 21, 22, 23, 22, 24, 23, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_eisei_kasa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_eisei_v[51], 24, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 4, 2, 5, 6, 2),
    gsSPNTriangles_5b(7, 8, 2, 9, 10, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_eisei_ten_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 11, 12, 13, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_eisei_sasae_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 14, 15, 16, 14, 17, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_eisei_antena_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPNTrianglesInit_5b(2, 19, 20, 21, 19, 22, 23, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_tak_eisei_tbl[] = { 0, 0, 2, 0 };

s16 cKF_kn_int_tak_eisei_tbl[] = { 2 };

s16 cKF_c_int_tak_eisei_tbl[] = { 1850, 1000, 100, -100, -50, -80, 0, 0, 900, 0, 0, 0, 0, 0 };

s16 cKF_ds_int_tak_eisei_tbl[] = { 1, 0, -3724, 30, -3600, -3724 };

cKF_Animation_R_c cKF_ba_r_int_tak_eisei = {
    cKF_ckcb_r_int_tak_eisei_tbl, cKF_ds_int_tak_eisei_tbl, cKF_kn_int_tak_eisei_tbl, cKF_c_int_tak_eisei_tbl, -1, 30
};

cKF_Joint_R_c cKF_je_r_int_tak_eisei_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1850, 1000, 100 } },
    { int_tak_eisei_base_on_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_tak_eisei_ude_env_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } },
    { int_tak_eisei_ude_on_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_tak_eisei = { ARRAY_COUNT(cKF_je_r_int_tak_eisei_tbl), 3, cKF_je_r_int_tak_eisei_tbl };
