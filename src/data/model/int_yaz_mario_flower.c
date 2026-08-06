#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_yaz_mario_flower_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_yaz_mario_flower_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_yaz_mario_flower_a_pal[] = {
#include "assets/int_yaz_mario_flower_a_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_yaz_mario_flower_b_pal[0x20 / sizeof(u16)];
#else
u16 int_yaz_mario_flower_b_pal[] = {
#include "assets/int_yaz_mario_flower_b_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_yaz_mario_flower_c_pal[0x20 / sizeof(u16)];
#else
u16 int_yaz_mario_flower_c_pal[] = {
#include "assets/int_yaz_mario_flower_c_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_yaz_mario_flower_d_pal[0x20 / sizeof(u16)];
#else
u16 int_yaz_mario_flower_d_pal[] = {
#include "assets/int_yaz_mario_flower_d_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_mario_flower_hana_a_tex_txt[0x200];
#else
u8 int_yaz_mario_flower_hana_a_tex_txt[] = {
#include "assets/int_yaz_mario_flower_hana_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_mario_flower_ha_tex_txt[0x300];
#else
u8 int_yaz_mario_flower_ha_tex_txt[] = {
#include "assets/int_yaz_mario_flower_ha_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_yaz_mario_flower_v[0x1F0 / sizeof(Vtx)];
#else
Vtx int_yaz_mario_flower_v[] = {
#include "assets/int_yaz_mario_flower_v.inc"
};
#endif

Gfx int_yaz_mario_flower_hana_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_2_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_yaz_mario_flower_hana_a_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_yaz_mario_flower_v, 9, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 1, 4, 2),
    gsSPNTriangles_5b(5, 3, 2, 6, 5, 2, 4, 7, 2, 8, 6, 2),
    gsSPNTriangles_5b(7, 8, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_yaz_mario_flower_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_2_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_yaz_mario_flower_ha_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_yaz_mario_flower_v[9], 22, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 4, 5, 1, 0),
    gsSPNTriangles_5b(6, 3, 0, 0, 4, 5, 0, 2, 6, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 7, 8, 9, 7, 9, 10, 8, 11, 12),
    gsSPNTriangles_5b(8, 12, 9, 11, 13, 14, 11, 14, 12, 13, 7, 10),
    gsSPNTriangles_5b(13, 10, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 15, 16, 17, 18, 19, 17, 17, 16, 20),
    gsSPNTriangles_5b(17, 19, 21, 20, 18, 17, 21, 15, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};
