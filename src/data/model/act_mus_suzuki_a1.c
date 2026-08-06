#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_suzuki_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_nog_suzuki_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_nog_suzuki_pal[] = {
#include "assets/act_mus_suzuki_a1/int_nog_suzuki_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_suzuki_body_txt[0x300];
#else
u8 act_mus_suzuki_body_txt[] = {
#include "assets/act_mus_suzuki_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_suzuki_a1_v[0x3B0 / sizeof(Vtx)];
#else
Vtx act_mus_suzuki_a1_v[] = {
#include "assets/act_mus_suzuki_a1_v.inc"
};
#endif

Gfx act_mus_suzuki_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_suzuki_a1_v, 8, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_suzuki_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_suzuki_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_suzuki_a1_v[8], 18, 8),
    gsSPNTrianglesInit_5b(12, 0, 5, 8, 3, 6, 9, 2, 10, 11),
    gsSPNTriangles_5b(5, 12, 13, 7, 14, 15, 6, 16, 17, 7, 19, 18),
    gsSPNTriangles_5b(6, 21, 20, 2, 1, 22, 5, 7, 23, 6, 2, 24),
    gsSPNTriangles_5b(7, 4, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&act_mus_suzuki_a1_v[26], 18, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 1, 1, 0, 3),
    gsSPNTriangles_5b(5, 6, 7, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(8, 15, 9, 12, 14, 2, 11, 5, 7, 7, 8, 11),
    gsSPNTriangles_5b(2, 1, 12, 16, 6, 5, 14, 13, 17, 7, 15, 8),
    gsSPNTriangles_5b(1, 4, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_suzuki_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_suzuki_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_suzuki_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_suzuki_a1_v[44], 15, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 2, 3, 4, 5, 6, 2),
    gsSPNTriangles_5b(2, 6, 7, 2, 1, 5, 7, 3, 2, 5, 8, 9),
    gsSPNTriangles_5b(10, 11, 7, 9, 12, 5, 7, 12, 10, 2, 13, 0),
    gsSPNTriangles_5b(5, 1, 8, 4, 14, 2, 11, 3, 7, 6, 12, 7),
    gsSPNTriangles_5b(5, 12, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_suzuki_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 56, 65486, 1095 } },
    { act_mus_suzuki_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_suzuki_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1196, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_suzuki_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_suzuki_a1_tbl), 2,
                                                cKF_je_r_act_mus_suzuki_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_suzuki_a1_c(void) {
    pc_load_asset("assets/act_mus_suzuki_a1/int_nog_suzuki_pal.bin", int_nog_suzuki_pal, 0x20, 0x969480, 0, 1);
}
#endif
