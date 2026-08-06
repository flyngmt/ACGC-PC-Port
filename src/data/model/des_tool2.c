#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 des_tool_kao1_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 des_tool_kao1_tex[]= {
#include "assets/des_tool_kao1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 des_tool_kao2_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 des_tool_kao2_tex[]= {
#include "assets/des_tool_kao2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 des_tool_kao3_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 des_tool_kao3_tex[]= {
#include "assets/des_tool_kao3_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 des_tool_kao4_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 des_tool_kao4_tex[]= {
#include "assets/des_tool_kao4_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 des_tool_kao5_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 des_tool_kao5_tex[]= {
#include "assets/des_tool_kao5_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx des_tool2_v[0x140 / sizeof(Vtx)];
#else
Vtx des_tool2_v[] = {
#include "assets/des_tool2_v.inc"
};
#endif

Gfx des_tool_kao1T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_kao1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(des_tool2_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_kao2T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_kao2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool2_v[4], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_kao3T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_kao3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool2_v[8], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_kao4T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_kao4_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool2_v[12], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_kao5T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 80, 50, 255),
gsDPSetEnvColor(235, 205, 145, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_tool_kao5_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&des_tool2_v[16], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_tool_kao_all_model[] = {
gsSPDisplayList(des_tool_kao1T_model),
gsSPDisplayList(des_tool_kao2T_model),
gsSPDisplayList(des_tool_kao3T_model),
gsSPDisplayList(des_tool_kao4T_model),
gsSPDisplayList(des_tool_kao5T_model),
gsSPEndDisplayList(),
};

