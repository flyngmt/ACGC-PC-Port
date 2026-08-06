#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_tri_chest03_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_tri_chest03_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_tri_chest03_pal[] = {
#include "assets/int_nog_tri_chest03_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_nog_tri_chest03_tex_txt[0x800];
#else
u8 obj_nog_tri_chest03_tex_txt[] = {
#include "assets/obj_nog_tri_chest03_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_tri_chest03_v[0x390 / sizeof(Vtx)];
#else
Vtx int_nog_tri_chest03_v[] = {
#include "assets/int_nog_tri_chest03_v.inc"
};
#endif

Gfx int_nog_tri_chest03_door_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_tri_chest03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_nog_tri_chest03_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_tri_chest03_v, 18, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_tri_chest03_base_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_tri_chest03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_nog_tri_chest03_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_tri_chest03_v[18], 32, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 11, 12, 13, 11, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 15, 17, 18, 19, 20, 21, 19, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 25, 26, 27, 28, 29, 27, 29, 30),
    gsSPVertex(&int_nog_tri_chest03_v[49], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_nog_tri_chest03_tbl[] = { 0, 0, 7 };

s16 cKF_kn_int_nog_tri_chest03_tbl[] = { 2, 2, 5 };

s16 cKF_c_int_nog_tri_chest03_tbl[] = { 1375, 3625, 0, -900, 0, 0, 0, 0, -900 };

s16 cKF_ds_int_nog_tri_chest03_tbl[] = { 1, 0, 0,    16, 0, 0,    1,    0, 0,    16,   0,  0,  1, -900,
                                         0, 3, -900, 0,  5, -840, 1590, 9, -500, 3027, 16, 50, 0 };

cKF_Animation_R_c cKF_ba_r_int_nog_tri_chest03 = { cKF_ckcb_r_int_nog_tri_chest03_tbl,
                                                   cKF_ds_int_nog_tri_chest03_tbl,
                                                   cKF_kn_int_nog_tri_chest03_tbl,
                                                   cKF_c_int_nog_tri_chest03_tbl,
                                                   -1,
                                                   16 };

cKF_Joint_R_c cKF_je_r_int_nog_tri_chest03_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1375, 3625, 0 } },
    { int_nog_tri_chest03_base_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { int_nog_tri_chest03_door_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1500, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_nog_tri_chest03 = { ARRAY_COUNT(cKF_je_r_int_nog_tri_chest03_tbl), 2,
                                                  cKF_je_r_int_nog_tri_chest03_tbl };
