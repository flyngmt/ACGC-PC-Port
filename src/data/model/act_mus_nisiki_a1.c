#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_nisiki_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_nisiki_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_nisiki_pal[] = {
#include "assets/act_mus_nisiki_a1/int_sum_nisiki_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_nisiki_body_txt[0x300];
#else
u8 act_mus_nisiki_body_txt[] = {
#include "assets/act_mus_nisiki_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_nisiki_a1_v[0x3C0 / sizeof(Vtx)];
#else
Vtx act_mus_nisiki_a1_v[] = {
#include "assets/act_mus_nisiki_a1_v.inc"
};
#endif

Gfx act_mus_nisiki_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_nisiki_a1_v, 7, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_nisiki_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_nisiki_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_nisiki_a1_v[7], 16, 7),
    gsSPNTrianglesInit_5b(10, 0, 7, 2, 6, 8, 1, 4, 10, 9),
    gsSPNTriangles_5b(5, 12, 11, 5, 2, 13, 2, 15, 14, 6, 17, 16),
    gsSPNTriangles_5b(6, 19, 18, 3, 21, 20, 6, 4, 22, 0, 0, 0),
    gsSPVertex(&act_mus_nisiki_a1_v[23], 23, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 6, 5, 0, 4, 1, 9, 3, 0, 5, 10, 11),
    gsSPNTriangles_5b(11, 8, 5, 0, 12, 9, 7, 13, 5, 14, 9, 12),
    gsSPNTriangles_5b(13, 7, 15, 0, 2, 12, 13, 10, 5, 16, 17, 14),
    gsSPNTriangles_5b(18, 19, 15, 14, 17, 20, 15, 7, 18, 20, 9, 14),
    gsSPNTriangles_5b(21, 19, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_nisiki_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_nisiki_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_nisiki_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_nisiki_a1_v[46], 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 2, 6, 7),
    gsSPNTriangles_5b(8, 1, 0, 0, 7, 9, 10, 11, 3, 5, 4, 12),
    gsSPNTriangles_5b(13, 10, 5, 5, 10, 3, 2, 7, 0, 9, 8, 0),
    gsSPNTriangles_5b(5, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_nisiki_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 73, 65472, 1195 } },
    { act_mus_nisiki_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_nisiki_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1300, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_nisiki_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_nisiki_a1_tbl), 2,
                                                cKF_je_r_act_mus_nisiki_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_nisiki_a1_c(void) {
    pc_load_asset("assets/act_mus_nisiki_a1/int_sum_nisiki_pal.bin", int_sum_nisiki_pal, 0x20, 0x965000, 0, 1);
}
#endif
