#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_yos_mario_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_yos_mario_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_yos_mario_pal[] = {
#include "assets/int_yos_mario_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_mario_dai_tex_txt[0x40];
#else
u8 int_yos_mario_dai_tex_txt[] = {
#include "assets/int_yos_mario_dai_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_mario_zubon_tex_txt[0x200];
#else
u8 int_yos_mario_zubon_tex_txt[] = {
#include "assets/int_yos_mario_zubon_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_mario_kao_tex_txt[0x200];
#else
u8 int_yos_mario_kao_tex_txt[] = {
#include "assets/int_yos_mario_kao_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_mario_hana_tex_txt[0x20];
#else
u8 int_yos_mario_hana_tex_txt[] = {
#include "assets/int_yos_mario_hana_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_mario_mimi_tex_txt[0x80];
#else
u8 int_yos_mario_mimi_tex_txt[] = {
#include "assets/int_yos_mario_mimi_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_mario_boushimae_tex_txt[0x80];
#else
u8 int_yos_mario_boushimae_tex_txt[] = {
#include "assets/int_yos_mario_boushimae_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_mario_boushiushiro_tex_txt[0x80];
#else
u8 int_yos_mario_boushiushiro_tex_txt[] = {
#include "assets/int_yos_mario_boushiushiro_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_mario_tuba_tex_txt[0x80];
#else
u8 int_yos_mario_tuba_tex_txt[] = {
#include "assets/int_yos_mario_tuba_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_mario_ude_tex_txt[0x80];
#else
u8 int_yos_mario_ude_tex_txt[] = {
#include "assets/int_yos_mario_ude_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_mario_te_tex_txt[0x80];
#else
u8 int_yos_mario_te_tex_txt[] = {
#include "assets/int_yos_mario_te_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_mario_kutu_tex_txt[0x80];
#else
u8 int_yos_mario_kutu_tex_txt[] = {
#include "assets/int_yos_mario_kutu_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_mario_fuda_tex_txt[0x20];
#else
u8 int_yos_mario_fuda_tex_txt[] = {
#include "assets/int_yos_mario_fuda_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_yos_mario_v[0x590 / sizeof(Vtx)];
#else
Vtx int_yos_mario_v[] = {
#include "assets/int_yos_mario_v.inc"
};
#endif

Gfx int_yos_mario_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yos_mario_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, int_yos_mario_dai_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_yos_mario_v, 29, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 0, 0, 5, 3),
    gsSPNTriangles_5b(2, 6, 0, 7, 8, 9, 7, 9, 10, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_yos_mario_zubon_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12, 11, 12, 13, 14, 15, 16, 17, 11, 13),
    gsSPNTriangles_5b(15, 18, 16, 12, 19, 13, 20, 14, 16, 19, 17, 13),
    gsSPNTriangles_5b(18, 20, 16, 21, 22, 23, 22, 21, 24, 25, 26, 27),
    gsSPNTriangles_5b(26, 25, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_yos_mario_kao_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_yos_mario_v[29], 30, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 1, 6, 2),
    gsSPNTriangles_5b(7, 3, 5, 8, 0, 2, 4, 9, 5, 6, 8, 2),
    gsSPNTriangles_5b(9, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_yos_mario_hana_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 10, 11, 12, 11, 10, 13, 11, 14, 12),
    gsSPNTriangles_5b(14, 11, 13, 15, 16, 17, 18, 19, 15, 17, 18, 15),
    gsSPNTriangles_5b(19, 16, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_yos_mario_mimi_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 23, 24, 25, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_yos_mario_boushimae_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 26, 27, 28, 27, 29, 28, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_yos_mario_boushiushiro_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_yos_mario_v[59], 30, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_yos_mario_tuba_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 7, 4, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_yos_mario_ude_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 11, 9, 8, 12, 13, 14),
    gsSPNTriangles_5b(14, 13, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_yos_mario_te_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 19, 20, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_yos_mario_kutu_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 22, 23, 24, 25, 23, 22, 26, 25, 22),
    gsSPNTriangles_5b(22, 24, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_yos_mario_fuda_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 27, 28, 29, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
