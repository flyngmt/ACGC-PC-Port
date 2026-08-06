#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_tai_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_nog_tai_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_nog_tai_pal[] = {
#include "assets/act_mus_tai_a1/int_nog_tai_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_tai_body_txt[0x300];
#else
u8 act_mus_tai_body_txt[] = {
#include "assets/act_mus_tai_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_tai_a1_v[0x3C0 / sizeof(Vtx)];
#else
Vtx act_mus_tai_a1_v[] = {
#include "assets/act_mus_tai_a1_v.inc"
};
#endif

Gfx act_mus_tai_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_tai_a1_v, 8, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_tai_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_tai_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_tai_a1_v[8], 18, 8),
    gsSPNTrianglesInit_5b(12, 6, 8, 9, 6, 10, 5, 2, 0, 11),
    gsSPNTriangles_5b(4, 12, 7, 3, 5, 13, 4, 14, 15, 0, 16, 17),
    gsSPNTriangles_5b(1, 3, 18, 1, 19, 20, 4, 2, 21, 5, 22, 23),
    gsSPNTriangles_5b(4, 24, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&act_mus_tai_a1_v[26], 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 4, 5, 0, 2),
    gsSPNTriangles_5b(6, 7, 8, 0, 4, 1, 5, 9, 3, 8, 10, 11),
    gsSPNTriangles_5b(11, 6, 8, 10, 8, 12, 3, 0, 5, 7, 13, 12),
    gsSPNTriangles_5b(12, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_tai_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_tai_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_tai_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_tai_a1_v[40], 20, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 7, 0),
    gsSPNTriangles_5b(8, 9, 10, 3, 11, 12, 0, 13, 6, 12, 4, 3),
    gsSPNTriangles_5b(2, 13, 0, 5, 14, 3, 15, 16, 17, 15, 13, 2),
    gsSPNTriangles_5b(2, 16, 15, 7, 18, 0, 10, 9, 5, 3, 19, 11),
    gsSPNTriangles_5b(14, 19, 3, 0, 18, 1, 5, 4, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_tai_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 56, 65486, 1297 } },
    { act_mus_tai_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_tai_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1500, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_tai_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_tai_a1_tbl), 2, cKF_je_r_act_mus_tai_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_tai_a1_c(void) {
    pc_load_asset("assets/act_mus_tai_a1/int_nog_tai_pal.bin", int_nog_tai_pal, 0x20, 0x969D40, 0, 1);
}
#endif
