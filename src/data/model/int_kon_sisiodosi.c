#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_sisiodosi_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kon_sisiodosi_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kon_sisiodosi_pal[] = {
#include "assets/int_kon_sisiodosi_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_sisiodosi_tutu_tex_txt[0x100];
#else
u8 int_kon_sisiodosi_tutu_tex_txt[] = {
#include "assets/int_kon_sisiodosi_tutu_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_sisiodosi_soko_tex_txt[0x80];
#else
u8 int_kon_sisiodosi_soko_tex_txt[] = {
#include "assets/int_kon_sisiodosi_soko_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_sisiodosi_mae_tex_txt[0x80];
#else
u8 int_kon_sisiodosi_mae_tex_txt[] = {
#include "assets/int_kon_sisiodosi_mae_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_sisiodosi_tuti_tex_txt[0x80];
#else
u8 int_kon_sisiodosi_tuti_tex_txt[] = {
#include "assets/int_kon_sisiodosi_tuti_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_sisiodosi_iwa_tex_txt[0x80];
#else
u8 int_kon_sisiodosi_iwa_tex_txt[] = {
#include "assets/int_kon_sisiodosi_iwa_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_sisiodosi_koisi_tex_txt[0x400];
#else
u8 int_kon_sisiodosi_koisi_tex_txt[] = {
#include "assets/int_kon_sisiodosi_koisi_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_sisiodosi_v[0x3E0 / sizeof(Vtx)];
#else
Vtx int_kon_sisiodosi_v[] = {
#include "assets/int_kon_sisiodosi_v.inc"
};
#endif

Gfx int_kon_sisiodisi_ue_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_sisiodosi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_sisiodosi_tutu_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_sisiodosi_v, 23, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 1, 0, 8, 0, 9, 3, 2, 7),
    gsSPNTriangles_5b(3, 7, 6, 10, 5, 4, 10, 4, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_sisiodosi_soko_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 12, 13, 14, 12, 14, 15, 12, 15, 16),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_sisiodosi_mae_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(5, 17, 18, 19, 20, 21, 19, 19, 18, 20),
    gsSPNTriangles_5b(19, 21, 22, 19, 22, 17, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_sisiodosi_sita_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_sisiodosi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_sisiodosi_tuti_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_sisiodosi_v[23], 30, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_sisiodosi_iwa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 178, 178, 178, 255),
    gsSPNTrianglesInit_5b(1, 4, 5, 6, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 7, 8, 9, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 10, 11, 12, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 13, 14, 15, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_kon_sisiodosi_koisi_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 19, 20, 18, 18, 20, 16),
    gsSPNTriangles_5b(18, 17, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_sisiodosi_tutu_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 21, 22, 23, 21, 24, 22, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_sisiodosi_soko_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 27, 28, 29, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kon_sisiodosi_tutu_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_sisiodosi_v[53], 9, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(4, 3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_sisiodosi_soko_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 6, 7, 8, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_kon_sisiodosi_tbl[] = { 0, 0, 1 };

s16 cKF_kn_int_kon_sisiodosi_tbl[] = { 13 };

s16 cKF_c_int_kon_sisiodosi_tbl[] = { 0, 25, 0, 0, 900, 0, -450, 0, 900, 0, 0 };

s16 cKF_ds_int_kon_sisiodosi_tbl[] = { 1,   1200, -122, 2,   1196, -239, 15,  658,  -1729, 16,  600, -1004, 17,
                                       591, 150,  18,   610, 251,  19,   607, -111, 22,    600, 0,   50,    600,
                                       0,   57,   618,  169, 82,   914,  416, 120,  1200,  12,  121, 1200,  6 };

cKF_Animation_R_c cKF_ba_r_int_kon_sisiodosi = { cKF_ckcb_r_int_kon_sisiodosi_tbl,
                                                 cKF_ds_int_kon_sisiodosi_tbl,
                                                 cKF_kn_int_kon_sisiodosi_tbl,
                                                 cKF_c_int_kon_sisiodosi_tbl,
                                                 -1,
                                                 121 };

cKF_Joint_R_c cKF_je_r_int_kon_sisiodosi_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 25, 0 } },
    { int_kon_sisiodosi_sita_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_kon_sisiodisi_ue_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2482, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_kon_sisiodosi = { ARRAY_COUNT(cKF_je_r_int_kon_sisiodosi_tbl), 2,
                                                cKF_je_r_int_kon_sisiodosi_tbl };
