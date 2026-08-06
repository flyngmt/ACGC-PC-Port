#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 des_tool_undo_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 des_tool_undo_tex[]= {
#include "assets/des_tool_undo_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 des_tool_waku5_tex_rgb_ia8[0x400];
#else
u8 des_tool_waku5_tex_rgb_ia8[] = {
#include "assets/des_tool_waku5_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 des_tool_nuri6_tex_rgb_ia8[0x400];
#else
u8 des_tool_nuri6_tex_rgb_ia8[] = {
#include "assets/des_tool_nuri6_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 des_tool_mark1_tex_rgb_ia8[0x400];
#else
u8 des_tool_mark1_tex_rgb_ia8[] = {
#include "assets/des_tool_mark1_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 des_tool_mark2_tex_rgb_ia8[0x400];
#else
u8 des_tool_mark2_tex_rgb_ia8[] = {
#include "assets/des_tool_mark2_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 des_tool_mark3_tex_rgb_ia8[0x400];
#else
u8 des_tool_mark3_tex_rgb_ia8[] = {
#include "assets/des_tool_mark3_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 des_tool_mark4_tex_rgb_ia8[0x400];
#else
u8 des_tool_mark4_tex_rgb_ia8[] = {
#include "assets/des_tool_mark4_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 des_tool_nuri1_tex_rgb_ia8[0x400];
#else
u8 des_tool_nuri1_tex_rgb_ia8[] = {
#include "assets/des_tool_nuri1_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 des_tool_nuri2_tex_rgb_ia8[0x400];
#else
u8 des_tool_nuri2_tex_rgb_ia8[] = {
#include "assets/des_tool_nuri2_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 des_tool_nuri3_tex_rgb_ia8[0x400];
#else
u8 des_tool_nuri3_tex_rgb_ia8[] = {
#include "assets/des_tool_nuri3_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 des_tool_nuri4_tex_rgb_ia8[0x400];
#else
u8 des_tool_nuri4_tex_rgb_ia8[] = {
#include "assets/des_tool_nuri4_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 des_tool_nuri5_tex_rgb_ia8[0x400];
#else
u8 des_tool_nuri5_tex_rgb_ia8[] = {
#include "assets/des_tool_nuri5_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 des_tool_pen1_tex_rgb_ia8[0x400];
#else
u8 des_tool_pen1_tex_rgb_ia8[] = {
#include "assets/des_tool_pen1_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 des_tool_pen2_tex_rgb_ia8[0x400];
#else
u8 des_tool_pen2_tex_rgb_ia8[] = {
#include "assets/des_tool_pen2_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 des_tool_pen3_tex_rgb_ia8[0x400];
#else
u8 des_tool_pen3_tex_rgb_ia8[] = {
#include "assets/des_tool_pen3_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 des_tool_waku1_tex_rgb_ia8[0x400];
#else
u8 des_tool_waku1_tex_rgb_ia8[] = {
#include "assets/des_tool_waku1_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 des_tool_waku2_tex_rgb_ia8[0x400];
#else
u8 des_tool_waku2_tex_rgb_ia8[] = {
#include "assets/des_tool_waku2_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 des_tool_waku3_tex_rgb_ia8[0x400];
#else
u8 des_tool_waku3_tex_rgb_ia8[] = {
#include "assets/des_tool_waku3_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
u8 des_tool_waku4_tex_rgb_ia8[0x400];
#else
u8 des_tool_waku4_tex_rgb_ia8[] = {
#include "assets/des_tool_waku4_tex_rgb_ia8.inc"
};
#endif

#ifdef TARGET_PC
Vtx des_tool_v[0x4C0 / sizeof(Vtx)];
#else
Vtx des_tool_v[] = {
#include "assets/des_tool_v.inc"
};
#endif

Gfx des_tool_pen1T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, anime_1_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(des_tool_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_pen2T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_pen2_tex_rgb_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool_v[4], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_pen3T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_pen3_tex_rgb_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool_v[8], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_nuriT_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, anime_2_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool_v[12], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_nuri2T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_nuri2_tex_rgb_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool_v[16], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_nuri3T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_nuri3_tex_rgb_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool_v[20], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_nuri4T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_nuri4_tex_rgb_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool_v[24], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_nuri5T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_nuri5_tex_rgb_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool_v[28], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_nuri6T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_nuri6_tex_rgb_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&des_tool_v[32], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_waku1T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, anime_3_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool_v[36], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_waku2T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_waku2_tex_rgb_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool_v[40], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_waku3T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_waku3_tex_rgb_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool_v[44], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_waku4T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_waku4_tex_rgb_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool_v[48], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_waku5T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_waku5_tex_rgb_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool_v[52], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_mark1T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, anime_4_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool_v[56], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_mark2T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_mark2_tex_rgb_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool_v[60], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_mark3T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_mark3_tex_rgb_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool_v[64], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_mark4T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_mark4_tex_rgb_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool_v[68], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_undoT_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_undo_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool_v[72], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_pen_all_model[] = {
gsSPDisplayList(des_tool_pen1T_model),
gsSPDisplayList(des_tool_pen2T_model),
gsSPDisplayList(des_tool_pen3T_model),
gsSPEndDisplayList(),
};

Gfx des_tool_nuri_all_model[] = {
gsSPDisplayList(des_tool_nuriT_model),
gsSPDisplayList(des_tool_nuri2T_model),
gsSPDisplayList(des_tool_nuri3T_model),
gsSPDisplayList(des_tool_nuri4T_model),
gsSPDisplayList(des_tool_nuri5T_model),
gsSPDisplayList(des_tool_nuri6T_model),
gsSPEndDisplayList(),
};

Gfx des_tool_waku_all_model[] = {
gsSPDisplayList(des_tool_waku1T_model),
gsSPDisplayList(des_tool_waku2T_model),
gsSPDisplayList(des_tool_waku3T_model),
gsSPDisplayList(des_tool_waku4T_model),
gsSPDisplayList(des_tool_waku5T_model),
gsSPEndDisplayList(),
};

Gfx des_tool_mark_all_model[] = {
gsSPDisplayList(des_tool_mark1T_model),
gsSPDisplayList(des_tool_mark2T_model),
gsSPDisplayList(des_tool_mark3T_model),
gsSPDisplayList(des_tool_mark4T_model),
gsSPEndDisplayList(),
};

