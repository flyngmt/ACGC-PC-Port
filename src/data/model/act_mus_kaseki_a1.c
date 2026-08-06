#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_kaseki_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_kaseki_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_kaseki_pal[] = {
#include "assets/act_mus_kaseki_a1/int_sum_kaseki_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_kaseki_body_txt[0x400];
#else
u8 act_mus_kaseki_body_txt[] = {
#include "assets/act_mus_kaseki_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_kaseki_a1_v[0x590 / sizeof(Vtx)];
#else
Vtx act_mus_kaseki_a1_v[] = {
#include "assets/act_mus_kaseki_a1_v.inc"
};
#endif

Gfx act_mus_kaseki_sakana_leg_model[] = {
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_kaseki_a1_v, 6, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_kaseki_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_mus_kaseki_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_kaseki_a1_v[6], 22, 6),
    gsSPNTrianglesInit_5b(8, 2, 5, 6, 5, 0, 7, 5, 8, 9),
    gsSPNTriangles_5b(4, 10, 11, 1, 4, 12, 5, 14, 13, 4, 3, 15),
    gsSPNTriangles_5b(4, 17, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(6, 18, 19, 20, 18, 21, 19, 22, 23, 24),
    gsSPNTriangles_5b(23, 25, 24, 26, 21, 18, 24, 25, 27, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_kaseki_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(&act_mus_kaseki_a1_v[28], 6, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_kaseki_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_mus_kaseki_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_kaseki_a1_v[34], 16, 6),
    gsSPNTrianglesInit_5b(10, 0, 6, 7, 1, 8, 9, 1, 11, 10),
    gsSPNTriangles_5b(1, 12, 13, 0, 14, 15, 4, 16, 0, 1, 17, 5),
    gsSPNTriangles_5b(0, 18, 2, 3, 19, 1, 0, 21, 20, 0, 0, 0),
    gsSPVertex(&act_mus_kaseki_a1_v[50], 18, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 1, 0, 6),
    gsSPNTriangles_5b(7, 8, 3, 9, 5, 4, 2, 10, 0, 11, 9, 4),
    gsSPNTriangles_5b(12, 2, 1, 4, 3, 13, 5, 7, 3, 1, 6, 14),
    gsSPNTriangles_5b(2, 12, 15, 16, 13, 3, 3, 8, 16, 15, 17, 2),
    gsSPNTriangles_5b(2, 17, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_kaseki_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_kaseki_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_mus_kaseki_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_kaseki_a1_v[68], 21, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 3, 4, 5, 6, 1, 0),
    gsSPNTriangles_5b(3, 7, 8, 6, 9, 1, 7, 9, 8, 7, 5, 10),
    gsSPNTriangles_5b(11, 2, 1, 1, 12, 11, 13, 0, 14, 15, 16, 4),
    gsSPNTriangles_5b(2, 14, 0, 17, 12, 1, 5, 7, 3, 7, 12, 17),
    gsSPNTriangles_5b(10, 12, 7, 14, 18, 13, 4, 3, 15, 15, 3, 19),
    gsSPNTriangles_5b(20, 0, 13, 19, 16, 15, 13, 18, 20, 17, 9, 7),
    gsSPNTriangles_5b(1, 9, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_kaseki_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 65399, 62, 1627 } },
    { act_mus_kaseki_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_kaseki_sakana_body_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1554, 0, 0 } },
    { act_mus_kaseki_sakana_leg_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1050, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_kaseki_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_kaseki_a1_tbl), 3,
                                                cKF_je_r_act_mus_kaseki_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_kaseki_a1_c(void) {
    pc_load_asset("assets/act_mus_kaseki_a1/int_sum_kaseki_pal.bin", int_sum_kaseki_pal, 0x20, 0x9606E0, 0, 1);
}
#endif
