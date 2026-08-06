#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_icons_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_icons_tex[] = {
#include "assets/kai_sousa_icons_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_lwaku_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_lwaku_tex[] = {
#include "assets/kai_sousa_lwaku_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_letters_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_letters_tex[] = {
#include "assets/kai_sousa_letters_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_rcontroller_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_rcontroller_tex[] = {
#include "assets/kai_sousa_rcontroller_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_lcontroller_a_tex[0x1000];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_lcontroller_a_tex[] = {
#include "assets/kai_sousa_lcontroller_a_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_punct_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_punct_tex[] = {
#include "assets/kai_sousa_punct_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_lcontroller_b_tex[0x1000];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_lcontroller_b_tex[] = {
#include "assets/kai_sousa_lcontroller_b_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_lcontroller_c_tex[0x1000];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_lcontroller_c_tex[] = {
#include "assets/kai_sousa_lcontroller_c_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_lcontroller_d_tex[0x1000];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_lcontroller_d_tex[] = {
#include "assets/kai_sousa_lcontroller_d_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_mojiban_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_mojiban_tex[] = {
#include "assets/kai_sousa_mojiban_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_mojiban2_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_mojiban2_tex[] = {
#include "assets/kai_sousa_mojiban2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_kirikae_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_kirikae_tex[] = {
#include "assets/kai_sousa_kirikae_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_3D_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_3D_tex[] = {
#include "assets/kai_sousa_3D_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_ok_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_ok_tex[] = {
#include "assets/kai_sousa_ok_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_backspace_tex[0x500];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_backspace_tex[] = {
#include "assets/kai_sousa_backspace_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_cursor_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_cursor_tex[] = {
#include "assets/kai_sousa_cursor_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 kai_sousa_button3_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 kai_sousa_button3_tex[] = {
#include "assets/kai_sousa/kai_sousa_button3_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_shita_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_shita_tex[] = {
#include "assets/kai_sousa_shita_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 kai_sousa_space_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 kai_sousa_space_tex[] = {
#include "assets/kai_sousa_space_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_caps_tex_rgb_i4[0x180];
#else
u8 kai_sousa_caps_tex_rgb_i4[] = {
#include "assets/kai_sousa_caps_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_small_tex_rgb_i4[0x180];
#else
u8 kai_sousa_small_tex_rgb_i4[] = {
#include "assets/kai_sousa_small_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_rbutton2_tex_rgb_ia8[0x800];
#else
u8 kai_sousa_rbutton2_tex_rgb_ia8[] = {
#include "assets/kai_sousa_rbutton2_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_rbutton_tex_rgb_ia8[0x800];
#else
u8 kai_sousa_rbutton_tex_rgb_ia8[] = {
#include "assets/kai_sousa_rbutton_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_3Dst2_tex_rgb_ia8[0x1000];
#else
u8 kai_sousa_3Dst2_tex_rgb_ia8[] = {
#include "assets/kai_sousa_3Dst2_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_3Dst3_tex_rgb_ia8[0x1000];
#else
u8 kai_sousa_3Dst3_tex_rgb_ia8[] = {
#include "assets/kai_sousa_3Dst3_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_3Dst4_tex_rgb_ia8[0x1000];
#else
u8 kai_sousa_3Dst4_tex_rgb_ia8[] = {
#include "assets/kai_sousa_3Dst4_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_3Dst5_tex_rgb_ia8[0x1000];
#else
u8 kai_sousa_3Dst5_tex_rgb_ia8[] = {
#include "assets/kai_sousa_3Dst5_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_3Dst6_tex_rgb_ia8[0x1000];
#else
u8 kai_sousa_3Dst6_tex_rgb_ia8[] = {
#include "assets/kai_sousa_3Dst6_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_3Dst_tex_rgb_ia8[0x1000];
#else
u8 kai_sousa_3Dst_tex_rgb_ia8[] = {
#include "assets/kai_sousa_3Dst_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_button1a_tex_rgb_ia8[0x800];
#else
u8 kai_sousa_button1a_tex_rgb_ia8[] = {
#include "assets/kai_sousa_button1a_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_button1b_tex_rgb_ia8[0x800];
#else
u8 kai_sousa_button1b_tex_rgb_ia8[] = {
#include "assets/kai_sousa_button1b_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_button2a_tex_rgb_ia8[0x200];
#else
u8 kai_sousa_button2a_tex_rgb_ia8[] = {
#include "assets/kai_sousa_button2a_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_button2b_tex_rgb_ia8[0x200];
#else
u8 kai_sousa_button2b_tex_rgb_ia8[] = {
#include "assets/kai_sousa_button2b_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_controllpad1_tex_rgb_ia8[0x400];
#else
u8 kai_sousa_controllpad1_tex_rgb_ia8[] = {
#include "assets/kai_sousa_controllpad1_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_controllpad2_tex_rgb_ia8[0x400];
#else
u8 kai_sousa_controllpad2_tex_rgb_ia8[] = {
#include "assets/kai_sousa_controllpad2_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_controllpad3_tex_rgb_ia8[0x400];
#else
u8 kai_sousa_controllpad3_tex_rgb_ia8[] = {
#include "assets/kai_sousa_controllpad3_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_controllpad4_tex_rgb_ia8[0x400];
#else
u8 kai_sousa_controllpad4_tex_rgb_ia8[] = {
#include "assets/kai_sousa_controllpad4_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_controllpad5_tex_rgb_ia8[0x400];
#else
u8 kai_sousa_controllpad5_tex_rgb_ia8[] = {
#include "assets/kai_sousa_controllpad5_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_lbutton2_tex_rgb_ia8[0x800];
#else
u8 kai_sousa_lbutton2_tex_rgb_ia8[] = {
#include "assets/kai_sousa_lbutton2_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_lbutton_tex_rgb_ia8[0x800];
#else
u8 kai_sousa_lbutton_tex_rgb_ia8[] = {
#include "assets/kai_sousa_lbutton_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_xbutton2_tex_rgb_ia8[0x200];
#else
u8 kai_sousa_xbutton2_tex_rgb_ia8[] = {
#include "assets/kai_sousa_xbutton2_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_xbutton_tex_rgb_ia8[0x200];
#else
u8 kai_sousa_xbutton_tex_rgb_ia8[] = {
#include "assets/kai_sousa_xbutton_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_ybutton2_tex_rgb_ia8[0x200];
#else
u8 kai_sousa_ybutton2_tex_rgb_ia8[] = {
#include "assets/kai_sousa_ybutton2_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_ybutton_tex_rgb_ia8[0x200];
#else
u8 kai_sousa_ybutton_tex_rgb_ia8[] = {
#include "assets/kai_sousa_ybutton_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 kai_sousa_lwaku_tex_rgb_i4[0x200];
#else
u8 kai_sousa_lwaku_tex_rgb_i4[] = {
#include "assets/kai_sousa_lwaku_tex_rgb_i4.inc"
};
#endif

#ifdef TARGET_PC
Vtx kai_sousa_v[0x830 / sizeof(Vtx)];
#else
Vtx kai_sousa_v[] = {
#include "assets/kai_sousa_v.inc"
};
#endif

Gfx kai_sousa_mode[] = {
    gsDPPipeSync(),
    gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_lwaku_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, kai_sousa_lwaku_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(kai_sousa_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_kirikae_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 50, 50, 70, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, kai_sousa_kirikae_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kai_sousa_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_henkan_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 70, 70, 30, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, kai_sousa_lwaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kai_sousa_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_letter_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, kai_sousa_letters_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kai_sousa_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_sign_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, kai_sousa_punct_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kai_sousa_v[16], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_mark_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, kai_sousa_icons_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kai_sousa_v[20], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_yajirushi_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 215, 195, 40, 255),
    gsSPVertex(&kai_sousa_v[24], 7, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_lmoji_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 48, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kai_sousa_v[31], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_lbuttonT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 225, 225, 225, 255),
    gsDPSetEnvColor(130, 130, 130, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kai_sousa_v[35], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_rbuttonT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 225, 225, 225, 255),
    gsDPSetEnvColor(130, 130, 130, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kai_sousa_v[39], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_controllerT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 215, 215, 215, 255),
    gsDPSetEnvColor(115, 25, 195, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, kai_sousa_lcontroller_d_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kai_sousa_v[43], 16, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, kai_sousa_lcontroller_c_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 7, 4, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, kai_sousa_lcontroller_b_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 11, 8, 10, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, kai_sousa_lcontroller_a_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 13, 15, 14, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_shitaT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(90, 80, 130, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, kai_sousa_shita_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kai_sousa_v[59], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_controller2T_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 65, 95, 165, 255),
    gsDPSetEnvColor(125, 45, 225, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, kai_sousa_rcontroller_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kai_sousa_v[63], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_mojibanT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 225, 205, 225, 255),
    gsDPSetEnvColor(160, 90, 245, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, kai_sousa_mojiban2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kai_sousa_v[67], 16, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, kai_sousa_mojiban_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_controllpadT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 40, 40, 40, 255),
    gsDPSetEnvColor(165, 165, 175, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kai_sousa_v[83], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_ybuttonT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(95, 95, 95, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kai_sousa_v[87], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_xbuttonT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetEnvColor(95, 95, 95, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kai_sousa_v[91], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_3DT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 130, 80, 200, 255),
    gsDPSetEnvColor(175, 140, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, kai_sousa_3D_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kai_sousa_v[95], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_3DstT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 215, 215, 235, 255),
    gsDPSetEnvColor(80, 80, 100, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kai_sousa_v[99], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_bbuttonT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 155, 165, 255),
    gsDPSetEnvColor(90, 10, 10, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kai_sousa_v[103], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_abuttonT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 155, 255, 155, 255),
    gsDPSetEnvColor(30, 100, 30, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&kai_sousa_v[107], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_startbuttonT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 215, 215, 215, 255),
    gsDPSetEnvColor(75, 75, 75, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kai_sousa_button3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kai_sousa_v[111], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_endT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 195, 255, 255),
    gsDPSetEnvColor(100, 40, 80, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, kai_sousa_ok_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kai_sousa_v[115], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_cancelT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 215, 215, 255),
    gsDPSetEnvColor(100, 30, 30, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 80, 16, kai_sousa_backspace_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kai_sousa_v[119], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_cursorT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 215, 215, 165, 255),
    gsDPSetEnvColor(105, 65, 0, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, kai_sousa_cursor_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kai_sousa_v[123], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx kai_sousa_spaceT_model[] = {
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 215, 255, 215, 255),
    gsDPSetEnvColor(40, 110, 40, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, kai_sousa_space_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kai_sousa_v[127], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_kai_sousa_c(void) {
    pc_load_asset("assets/kai_sousa/kai_sousa_button3_tex.bin", kai_sousa_button3_tex, 0x100, 0x6F1100, 0, 0);
}
#endif
