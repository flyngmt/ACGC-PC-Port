#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_s_buildsite_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 obj_s_buildsite_tex[] = {
#include "assets/obj_s_buildsite_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_buildsite_v[0xC0 / sizeof(Vtx)];
#else
Vtx obj_s_buildsite_v[] = {
#include "assets/obj_s_buildsite_v.inc"
};
#endif

Gfx reserve_DL_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_s_buildsite_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_buildsite_v, 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 8, 7, 9, 8, 9, 10),
    gsSPNTriangles_5b(7, 11, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_attention_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_attention_pal[] = {
#include "assets/obj_s_attention_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_s_attention_tex[0x400];
#else
u8 obj_s_attention_tex[] = {
#include "assets/obj_s_attention_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_s_attention_v[0x80 / sizeof(Vtx)];
#else
Vtx obj_s_attention_v[] = {
#include "assets/obj_s_attention_v.inc"
};
#endif

Gfx obj_s_attentionT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_attention_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_s_attention_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_s_attention_v, 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
u8 obj_w_buildsite_tex[0x400];
#else
u8 obj_w_buildsite_tex[] = {
#include "assets/obj_w_buildsite_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_buildsite_v[0xC0 / sizeof(Vtx)];
#else
Vtx obj_w_buildsite_v[] = {
#include "assets/obj_w_buildsite_v.inc"
};
#endif

Gfx reserve_winter_DL_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_w_buildsite_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_buildsite_v, 12, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 8, 7, 9, 8, 9, 10),
    gsSPNTriangles_5b(7, 11, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_attention_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_attention_pal[] = {
#include "assets/obj_w_attention_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_w_attention_tex[0x400];
#else
u8 obj_w_attention_tex[] = {
#include "assets/obj_w_attention_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_w_attention_v[0x80 / sizeof(Vtx)];
#else
Vtx obj_w_attention_v[] = {
#include "assets/obj_w_attention_v.inc"
};
#endif

Gfx obj_w_attentionT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_w_attention_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_w_attention_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_w_attention_v, 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
