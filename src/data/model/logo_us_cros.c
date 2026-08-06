#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx logo_us_cros_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 logo_us_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 logo_us_pal[] = {
#include "assets/logo_us_cros/logo_us_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 logo_us_s_tex_txt[0x600];
#else
static u8 logo_us_s_tex_txt[] = {
#include "assets/logo_us_cros/logo_us_s_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 logo_us_o_tex_txt[0x800];
#else
u8 logo_us_o_tex_txt[] = {
#include "assets/logo_us_o_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 logo_us_r_tex_txt[0x800];
#else
u8 logo_us_r_tex_txt[] = {
#include "assets/logo_us_r_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 logo_us_c_1_tex_txt[0x800];
#else
u8 logo_us_c_1_tex_txt[] = {
#include "assets/logo_us_c_1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 logo_us_c_2_tex_txt[0x400];
#else
u8 logo_us_c_2_tex_txt[] = {
#include "assets/logo_us_c_2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx logo_us_cros_v[0x140 / sizeof(Vtx)];
#else
Vtx logo_us_cros_v[] = {
#include "assets/logo_us_cros_v.inc"
};
#endif

Gfx logo_us_zs_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, logo_us_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 64, logo_us_s_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(logo_us_cros_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx logo_us_zr_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, logo_us_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, logo_us_r_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&logo_us_cros_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx logo_us_zo_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, logo_us_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, logo_us_o_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&logo_us_cros_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx logo_us_zcB_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, logo_us_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, logo_us_c_2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&logo_us_cros_v[16], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx logo_us_zcA_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, logo_us_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, logo_us_c_1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&logo_us_cros_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_logo_us_cros_tbl[] = { { NULL, 4, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 55911, 62411, 61036 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { logo_us_zcA_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 4500, 0, 0 } },
                                              { logo_us_zcB_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 62161, 62411, 61036 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { logo_us_zo_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 4500, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 59036, 62411, 61036 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { logo_us_zr_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 4500, 0, 0 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 64848, 62411, 61036 } },
                                              { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
                                              { logo_us_zs_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 4500, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_logo_us_cros = { ARRAY_COUNT(cKF_je_r_logo_us_cros_tbl), 5, cKF_je_r_logo_us_cros_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_logo_us_cros_c(void) {
    pc_load_asset("assets/logo_us_cros/logo_us_pal.bin", logo_us_pal, 0x20, 0x8CBE80, 0, 1);
    pc_load_asset("assets/logo_us_cros/logo_us_s_tex_txt.bin", logo_us_s_tex_txt, 0x600, 0x8CBEA0, 0, 0);
}
#endif
