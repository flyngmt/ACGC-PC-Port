#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_namazu_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_namazu_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_namazu_pal[] = {
#include "assets/act_mus_namazu_a1/int_sum_namazu_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_namazu_body_txt[0x300];
#else
u8 act_mus_namazu_body_txt[] = {
#include "assets/act_mus_namazu_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_namazu_a1_v[0x5A0 / sizeof(Vtx)];
#else
Vtx act_mus_namazu_a1_v[] = {
#include "assets/act_mus_namazu_a1_v.inc"
};
#endif

Gfx act_mus_namazu_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(act_mus_namazu_a1_v, 11, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_namazu_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_namazu_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_namazu_a1_v[11], 20, 11),
    gsSPNTrianglesInit_5b(10, 9, 7, 11, 7, 3, 12, 0, 4, 13),
    gsSPNTriangles_5b(3, 0, 14, 4, 8, 15, 3, 16, 17, 4, 18, 19),
    gsSPNTriangles_5b(8, 10, 20, 7, 21, 22, 8, 23, 24, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 6, 1, 25, 5, 26, 27, 6, 28, 29),
    gsSPNTriangles_5b(2, 5, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&act_mus_namazu_a1_v[31], 15, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 4, 5, 0, 2),
    gsSPNTriangles_5b(6, 7, 8, 0, 4, 1, 3, 0, 5, 8, 2, 9),
    gsSPNTriangles_5b(9, 6, 8, 2, 8, 10, 11, 5, 12, 10, 8, 7),
    gsSPNTriangles_5b(10, 13, 2, 2, 12, 5, 5, 11, 3, 7, 14, 10),
    gsSPNTriangles_5b(13, 10, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_namazu_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_namazu_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_namazu_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&act_mus_namazu_a1_v[46], 19, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 1, 3, 5),
    gsSPNTriangles_5b(1, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 6, 7, 8, 9, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(15, 9, 11, 16, 7, 17, 12, 18, 13, 0, 0, 0),
    gsSPVertex(&act_mus_namazu_a1_v[65], 25, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 1, 0, 10, 11, 12, 2, 1, 7, 7, 1, 9),
    gsSPNTriangles_5b(9, 10, 8, 13, 5, 2, 13, 7, 6, 2, 7, 13),
    gsSPNTriangles_5b(8, 7, 9, 2, 4, 0, 0, 11, 9, 2, 5, 4),
    gsSPNTriangles_5b(11, 10, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(10, 14, 15, 16, 16, 15, 17, 18, 19, 17),
    gsSPNTriangles_5b(18, 20, 21, 22, 14, 16, 17, 23, 16, 17, 20, 18),
    gsSPNTriangles_5b(24, 19, 18, 16, 23, 22, 18, 21, 24, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_namazu_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 65529, 1199 } },
    { act_mus_namazu_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_namazu_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1300, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_namazu_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_namazu_a1_tbl), 2,
                                                cKF_je_r_act_mus_namazu_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_namazu_a1_c(void) {
    pc_load_asset("assets/act_mus_namazu_a1/int_sum_namazu_pal.bin", int_sum_namazu_pal, 0x20, 0x9632E0, 0, 1);
}
#endif
