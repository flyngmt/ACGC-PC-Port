#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 des_cursor_undo_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 des_cursor_undo_tex[]= {
#include "assets/des_cursor_undo_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 des_cursor_sp_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 des_cursor_sp_tex[]= {
#include "assets/des_cursor_sp_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 des_cursor_sen_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 des_cursor_sen_tex[]= {
#include "assets/des_cursor_sen_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 des_cursor_pen_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 des_cursor_pen_tex[]= {
#include "assets/des_cursor_pen_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 des_cursor_nuri_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 des_cursor_nuri_tex[]= {
#include "assets/des_cursor_nuri_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 des_cursor_mark1_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 des_cursor_mark1_tex[]= {
#include "assets/des_cursor_mark1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 des_cursor_mark2_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 des_cursor_mark2_tex[]= {
#include "assets/des_cursor_mark2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 des_cursor_mark3_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 des_cursor_mark3_tex[]= {
#include "assets/des_cursor_mark3_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 des_cursor_mark4_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) u8 des_cursor_mark4_tex[]= {
#include "assets/des_cursor_mark4_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 des_cursor_waku_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 des_cursor_waku_tex[]= {
#include "assets/des_cursor_waku_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx des_cursor_v[0x2C0 / sizeof(Vtx)];
#else
Vtx des_cursor_v[] = {
#include "assets/des_cursor_v.inc"
};
#endif

Gfx des_cursor_mark1_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 60, 70, 60, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 32, des_cursor_mark1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(des_cursor_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_cursor_mark2_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 60, 70, 60, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 32, des_cursor_mark2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&des_cursor_v[4], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_cursor_mark3_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 60, 70, 60, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, des_cursor_mark3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&des_cursor_v[8], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_cursor_mark4_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 60, 70, 60, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, des_cursor_mark4_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&des_cursor_v[12], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_cursor_undo_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 60, 70, 60, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, des_cursor_undo_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&des_cursor_v[16], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_cursor_penT_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 61, 70, 60, 255),
gsDPSetEnvColor(235, 235, 225, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_cursor_pen_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&des_cursor_v[20], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_cursor_nuriT_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 60, 70, 60, 255),
gsDPSetEnvColor(235, 235, 225, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_cursor_nuri_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&des_cursor_v[24], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_cursor_waku1T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 60, 70, 60, 255),
gsDPSetEnvColor(235, 235, 225, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_cursor_waku_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&des_cursor_v[28], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_cursor_waku2T_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 60, 70, 60, 255),
gsDPSetEnvColor(235, 235, 225, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_cursor_waku_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&des_cursor_v[32], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_cursor_spT_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 60, 70, 60, 255),
gsDPSetEnvColor(235, 235, 225, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_cursor_sp_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&des_cursor_v[36], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx des_cursor_wakuT_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 60, 70, 60, 255),
gsDPSetEnvColor(225, 235, 225, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, des_cursor_sen_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&des_cursor_v[40], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

