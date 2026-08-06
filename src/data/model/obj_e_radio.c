#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_e_radio_t1_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 obj_e_radio_t1_tex[] = {
#include "assets/obj_e_radio_t1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_radio_t2_tex[0x800];
#else
u8 obj_e_radio_t2_tex[] = {
#include "assets/obj_e_radio_t2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_radio_v[0x280 / sizeof(Vtx)];
#else
Vtx obj_e_radio_v[] = {
#include "assets/obj_e_radio_v.inc"
};
#endif

Gfx obj_e_radio_t1_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_radio_t1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_radio_v, 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_e_radio_t2T_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_e_radio_t2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_e_radio_v[16], 24, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(14, 4, 5, 6, 4, 6, 7, 8, 4, 7),
    gsSPNTriangles_5b(8, 7, 9, 10, 11, 12, 10, 12, 13, 14, 11, 10),
    gsSPNTriangles_5b(14, 10, 15, 16, 12, 11, 16, 11, 17, 18, 13, 12),
    gsSPNTriangles_5b(18, 12, 19, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx radio_DL_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPDisplayList(obj_e_radio_t1_model),
    gsSPDisplayList(obj_e_radio_t2T_model),
    gsSPEndDisplayList(),
};
