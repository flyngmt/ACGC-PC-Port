#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_yaz_turkey_chest_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_yaz_turkey_chest_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_yaz_turkey_chest_pal[] = {
#include "assets/int_yaz_turkey_chest_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_turkey_chest_drwr_tex_txt[0x100];
#else
u8 int_yaz_turkey_chest_drwr_tex_txt[] = {
#include "assets/int_yaz_turkey_chest_drwr_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_turkey_chest_drwr_frnt_tex_txt[0x100];
#else
u8 int_yaz_turkey_chest_drwr_frnt_tex_txt[] = {
#include "assets/int_yaz_turkey_chest_drwr_frnt_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_turkey_chest_knob_tex_txt[0x80];
#else
u8 int_yaz_turkey_chest_knob_tex_txt[] = {
#include "assets/int_yaz_turkey_chest_knob_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_turkey_chest_asi_tex_txt[0x40];
#else
u8 int_yaz_turkey_chest_asi_tex_txt[] = {
#include "assets/int_yaz_turkey_chest_asi_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_turkey_chest_back_tex_txt[0x200];
#else
u8 int_yaz_turkey_chest_back_tex_txt[] = {
#include "assets/int_yaz_turkey_chest_back_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_turkey_chest_side_tex_txt[0x100];
#else
u8 int_yaz_turkey_chest_side_tex_txt[] = {
#include "assets/int_yaz_turkey_chest_side_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_turkey_chest_frnt_tex_txt[0x200];
#else
u8 int_yaz_turkey_chest_frnt_tex_txt[] = {
#include "assets/int_yaz_turkey_chest_frnt_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_yaz_turkey_chest_v[0x580 / sizeof(Vtx)];
#else
Vtx int_yaz_turkey_chest_v[] = {
#include "assets/int_yaz_turkey_chest_v.inc"
};
#endif

Gfx int_yaz_turkey_chest_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yaz_turkey_chest_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_yaz_turkey_chest_drwr_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_yaz_turkey_chest_v, 23, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsDPSetTile_Dolphin(8, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_yaz_turkey_chest_drwr_frnt_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_yaz_turkey_chest_knob_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 20, 21, 22, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_yaz_turkey_chest_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yaz_turkey_chest_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_yaz_turkey_chest_knob_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_yaz_turkey_chest_v[23], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, int_yaz_turkey_chest_asi_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_yaz_turkey_chest_v[26], 32, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 24, 25, 26, 27, 28, 29, 0, 0, 0),
    gsSPVertex(&int_yaz_turkey_chest_v[56], 28, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_yaz_turkey_chest_back_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsSPNTrianglesInit_5b(2, 6, 7, 8, 6, 8, 9, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_yaz_turkey_chest_side_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(16, 10, 11, 12, 10, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(14, 16, 17, 18, 19, 20, 18, 20, 21, 22, 20, 19),
    gsSPNTriangles_5b(22, 19, 23, 13, 24, 25, 13, 25, 10, 23, 25, 24),
    gsSPNTriangles_5b(23, 24, 22, 21, 26, 27, 21, 27, 18, 17, 12, 11),
    gsSPNTriangles_5b(17, 11, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_yaz_turkey_chest_frnt_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsSPVertex(&int_yaz_turkey_chest_v[84], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_yaz_turkey_chest_tbl[] = { 56, 7, 7 };

s16 cKF_kn_int_yaz_turkey_chest_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2 };

s16 cKF_c_int_yaz_turkey_chest_tbl[] = { 0, 900, 0 };

s16 cKF_ds_int_yaz_turkey_chest_tbl[] = {
    1,  2000, 0, 10, 2000, 0, 1,  -24000, 0, 10, -24000, 0, 1,  1500, 0, 10, 1500, 0, 1,  0, 0, 10, 0, 0, 1,  0,  0,
    10, 0,    0, 1,  900,  0, 10, 900,    0, 1,  0,      0, 10, 0,    0, 1,  0,    0, 10, 0, 0, 1,  0, 0, 10, 28, 83
};

cKF_Animation_R_c cKF_ba_r_int_yaz_turkey_chest = { cKF_ckcb_r_int_yaz_turkey_chest_tbl,
                                                    cKF_ds_int_yaz_turkey_chest_tbl,
                                                    cKF_kn_int_yaz_turkey_chest_tbl,
                                                    cKF_c_int_yaz_turkey_chest_tbl,
                                                    -1,
                                                    10 };

cKF_Joint_R_c cKF_je_r_int_yaz_turkey_chest_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2000, 41536, 1500 } },
    { int_yaz_turkey_chest_body_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_yaz_turkey_chest_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_yaz_turkey_chest = { ARRAY_COUNT(cKF_je_r_int_yaz_turkey_chest_tbl), 2,
                                                   cKF_je_r_int_yaz_turkey_chest_tbl };
