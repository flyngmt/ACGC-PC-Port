#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_zari_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 act_mus_zari_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 act_mus_zari_pal[] = {
#include "assets/act_mus_zari_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_zari_tex_txt[0x400];
#else
u8 act_mus_zari_tex_txt[] = {
#include "assets/act_mus_zari_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_zari_v[0x370 / sizeof(Vtx)];
#else
Vtx act_mus_zari_v[] = {
#include "assets/act_mus_zari_v.inc"
};
#endif

Gfx act_mus_zari_tail_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(act_mus_zari_v, 5, 0),
    gsSPMatrix(&anime_6_mdl[4], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_mus_zari_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, act_mus_zari_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&act_mus_zari_v[5], 20, 5),
    gsSPNTrianglesInit_5b(8, 0, 1, 5, 1, 2, 6, 2, 7, 8),
    gsSPNTriangles_5b(0, 9, 10, 0, 11, 12, 4, 14, 13, 4, 3, 15),
    gsSPNTriangles_5b(3, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 17, 18, 19, 20, 21, 17, 21, 22, 17),
    gsSPNTriangles_5b(22, 18, 17, 22, 23, 18, 21, 24, 22, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPEndDisplayList(),
};

Gfx act_mus_zari_right_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_mus_zari_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, act_mus_zari_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&act_mus_zari_v[30], 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_zari_left_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_mus_zari_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, act_mus_zari_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&act_mus_zari_v[25], 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 0, 3, 1, 3, 4),
    gsSPNTriangles_5b(1, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_zari_asi_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_mus_zari_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, act_mus_zari_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&act_mus_zari_v[35], 10, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsSPNTriangles_5b(5, 6, 7, 8, 5, 7, 9, 8, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_zari_base_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_mus_zari_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, act_mus_zari_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&act_mus_zari_v[45], 10, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 1, 3, 2, 4, 5, 1),
    gsSPNTriangles_5b(4, 6, 5, 5, 3, 1, 7, 8, 9, 7, 2, 8),
    gsSPNTriangles_5b(2, 3, 8, 0, 2, 7, 0, 4, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_zari_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 900, 50 } },
                                              { act_mus_zari_base_model, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 885, 161, 0 } },
                                              { act_mus_zari_asi_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 885, 161, 0 } },
                                              { act_mus_zari_left_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 885, 161, 0 } },
                                              { act_mus_zari_right_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { act_mus_zari_tail_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1118, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_act_mus_zari = { ARRAY_COUNT(cKF_je_r_act_mus_zari_tbl), 5, cKF_je_r_act_mus_zari_tbl };
