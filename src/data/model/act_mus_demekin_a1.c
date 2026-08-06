#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_demekin_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_demekin_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_demekin_pal[] = {
#include "assets/act_mus_demekin_a1/int_sum_demekin_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_demekin_body_txt[0x200];
#else
u8 act_mus_demekin_body_txt[] = {
#include "assets/act_mus_demekin_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_demekin_a1_v[0x640 / sizeof(Vtx)];
#else
Vtx act_mus_demekin_a1_v[] = {
#include "assets/act_mus_demekin_a1_v.inc"
};
#endif

Gfx act_mus_demekin_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_demekin_a1_v, 8, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_demekin_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_demekin_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_demekin_a1_v[8], 22, 8),
    gsSPNTrianglesInit_5b(1, 0, 8, 9, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 1, 10, 11, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(3, 0, 12, 13, 1, 14, 15, 1, 16, 17),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(3, 6, 1, 18, 0, 7, 19, 0, 20, 21),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 2, 22, 4, 5, 23, 24, 4, 25, 26),
    gsSPNTriangles_5b(5, 27, 3, 1, 4, 28, 5, 0, 29, 0, 0, 0),
    gsSPVertex(&act_mus_demekin_a1_v[30], 30, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 3, 4, 5, 6, 7, 8, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 9, 10, 11, 12, 13, 14, 15, 11, 10),
    gsSPNTriangles_5b(10, 16, 15, 11, 17, 9, 13, 12, 16, 18, 12, 14),
    gsSPNTriangles_5b(19, 17, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 21, 22, 23, 23, 22, 24, 24, 25, 26),
    gsSPNTriangles_5b(27, 28, 21, 24, 26, 29, 29, 27, 21, 29, 23, 24),
    gsSPNTriangles_5b(21, 23, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&act_mus_demekin_a1_v[60], 3, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPEndDisplayList(),
};

Gfx act_mus_demekin_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_demekin_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_demekin_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_demekin_a1_v[63], 27, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 6, 7, 8, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 12, 13, 14, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 15, 16, 17, 18, 19, 15, 20, 19, 18),
    gsSPNTriangles_5b(18, 21, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 22, 23, 24, 24, 25, 26, 0, 0, 0),
    gsSPVertex(&act_mus_demekin_a1_v[90], 10, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 2, 3, 4, 1, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 4, 3, 7, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_demekin_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 57, 65499, 699 } },
    { act_mus_demekin_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_demekin_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 700, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_demekin_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_demekin_a1_tbl), 2,
                                                 cKF_je_r_act_mus_demekin_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_demekin_a1_c(void) {
    pc_load_asset("assets/act_mus_demekin_a1/int_sum_demekin_pal.bin", int_sum_demekin_pal, 0x20, 0x959580, 0, 1);
}
#endif
