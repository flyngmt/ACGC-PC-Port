#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_mus_kingyo_a1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_kingyo_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_kingyo_pal[] = {
#include "assets/act_mus_kingyo_a1/int_sum_kingyo_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_mus_kingyo_body_txt[0x200];
#else
u8 act_mus_kingyo_body_txt[] = {
#include "assets/act_mus_kingyo_body_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_mus_kingyo_a1_v[0x610 / sizeof(Vtx)];
#else
Vtx act_mus_kingyo_a1_v[] = {
#include "assets/act_mus_kingyo_a1_v.inc"
};
#endif

Gfx act_mus_kingyo_sakana_body_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(act_mus_kingyo_a1_v, 7, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_kingyo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_kingyo_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_kingyo_a1_v[7], 22, 7),
    gsSPNTrianglesInit_5b(14, 0, 7, 8, 1, 9, 10, 0, 11, 12),
    gsSPNTriangles_5b(1, 13, 14, 1, 15, 16, 6, 1, 17, 0, 6, 18),
    gsSPNTriangles_5b(0, 19, 20, 2, 21, 4, 5, 22, 23, 4, 24, 25),
    gsSPNTriangles_5b(5, 26, 3, 1, 4, 27, 5, 0, 28, 0, 0, 0),
    gsSPVertex(&act_mus_kingyo_a1_v[29], 16, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 3, 4, 5, 6, 7, 8, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(3, 9, 10, 11, 12, 13, 14, 15, 11, 10),
    gsSPVertex(&act_mus_kingyo_a1_v[45], 16, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 5, 6, 7, 1),
    gsSPNTriangles_5b(8, 7, 9, 10, 4, 11, 6, 0, 12, 12, 0, 5),
    gsSPNTriangles_5b(5, 10, 13, 14, 9, 6, 5, 13, 15, 15, 14, 6),
    gsSPNTriangles_5b(15, 12, 5, 6, 12, 15, 1, 0, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_mus_kingyo_sakana_head_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_kingyo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_kingyo_body_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&act_mus_kingyo_a1_v[61], 27, 0),
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
    gsSPVertex(&act_mus_kingyo_a1_v[88], 9, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 2, 3, 4, 1, 5, 6),
    gsSPNTriangles_5b(7, 8, 0, 4, 3, 7, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_kingyo_a1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 57, 65499, 699 } },
    { act_mus_kingyo_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_mus_kingyo_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 700, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_kingyo_a1 = { ARRAY_COUNT(cKF_je_r_act_mus_kingyo_a1_tbl), 2,
                                                cKF_je_r_act_mus_kingyo_a1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_mus_kingyo_a1_c(void) {
    pc_load_asset("assets/act_mus_kingyo_a1/int_sum_kingyo_pal.bin", int_sum_kingyo_pal, 0x20, 0x961300, 0, 1);
}
#endif
