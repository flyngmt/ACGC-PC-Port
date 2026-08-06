#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_aroana_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_aroana_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_aroana_pal[] = {
#include "assets/act_mus_aroana_a1/int_sum_aroana_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_aroana_body_txt[0x300];
#else
u8 act_mus_aroana_body_txt[] = {
#include "assets/act_mus_aroana_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_aroana_a1_v[0x340 / sizeof(Vtx)];
#else
Vtx act_mus_aroana_a1_v[] = {
#include "assets/act_mus_aroana_a1_v.inc"
};
#endif

Gfx act_mus_aroana_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_aroana_a1_v, 6, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_aroana_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_aroana_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_aroana_a1_v[6], 12, 6),
    gsSPNTrianglesInit_5b(8, 2, 7, 6, 0, 8, 2, 5, 9, 1),
    gsSPNTriangles_5b(3, 2, 10, 5, 4, 11, 5, 13, 12, 2, 15, 14),
    gsSPNTriangles_5b(5, 17, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&act_mus_aroana_a1_v[18], 20, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 3, 4, 5, 0, 2),
    gsSPNTriangles_5b(6, 7, 8, 0, 4, 1, 3, 0, 5, 8, 9, 10),
    gsSPNTriangles_5b(10, 6, 8, 9, 8, 11, 12, 3, 13, 14, 7, 15),
    gsSPNTriangles_5b(13, 5, 16, 3, 5, 13, 14, 11, 7, 17, 11, 14),
    gsSPNTriangles_5b(11, 8, 7, 14, 18, 17, 16, 19, 13, 15, 18, 14),
    gsSPNTriangles_5b(13, 19, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_aroana_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_aroana_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_aroana_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_aroana_a1_v[38], 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 6, 7, 2),
    gsSPNTriangles_5b(3, 8, 9, 3, 10, 8, 7, 11, 2, 7, 12, 11),
    gsSPNTriangles_5b(2, 1, 6, 2, 11, 0, 10, 13, 8, 9, 4, 3),
    gsSPNTriangles_5b(5, 10, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_aroana_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 58, 65499, 1195 } },
    { act_mus_aroana_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_aroana_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1300, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_aroana_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_aroana_a1_tbl), 2,
                                                cKF_je_r_act_mus_aroana_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_aroana_a1_c(void) {
    pc_load_asset("assets/act_mus_aroana_a1/int_sum_aroana_pal.bin", int_sum_aroana_pal, 0x20, 0x956B40, 0, 1);
}
#endif
