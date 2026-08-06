#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_yaz_candle_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_yaz_candle_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_yaz_candle_pal[] = {
#include "assets/int_yaz_candle_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_yaz_candle_fire1_tex_pic_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_yaz_candle_fire1_tex_pic_ci4_pal[] = {
#include "assets/int_yaz_candle_fire1_tex_pic_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_candle_base_tex_txt[0x200];
#else
u8 int_yaz_candle_base_tex_txt[] = {
#include "assets/int_yaz_candle_base_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_candle_base2_tex_txt[0x80];
#else
u8 int_yaz_candle_base2_tex_txt[] = {
#include "assets/int_yaz_candle_base2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_candle_green_tex_txt[0x100];
#else
u8 int_yaz_candle_green_tex_txt[] = {
#include "assets/int_yaz_candle_green_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_candle_red_tex_txt[0x100];
#else
u8 int_yaz_candle_red_tex_txt[] = {
#include "assets/int_yaz_candle_red_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_candle_black_tex_txt[0x100];
#else
u8 int_yaz_candle_black_tex_txt[] = {
#include "assets/int_yaz_candle_black_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_candle_fire1_tex_txt[0x100];
#else
u8 int_yaz_candle_fire1_tex_txt[] = {
#include "assets/int_yaz_candle_fire1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_candle_fire2_tex_txt[0x100];
#else
u8 int_yaz_candle_fire2_tex_txt[] = {
#include "assets/int_yaz_candle_fire2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_yaz_candle_v[0x640 / sizeof(Vtx)];
#else
Vtx int_yaz_candle_v[] = {
#include "assets/int_yaz_candle_v.inc"
};
#endif

Gfx int_yaz_candle_fire_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yaz_candle_fire1_tex_pic_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_yaz_candle_v, 32, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 24, 25, 26, 27, 28, 29, 0, 0, 0),
    gsSPVertex(&int_yaz_candle_v[30], 12, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_yaz_candle_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yaz_candle_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_yaz_candle_base_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_yaz_candle_v[42], 16, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 4, 3, 0, 2),
    gsSPNTriangles_5b(1, 0, 4, 5, 6, 7, 8, 9, 10, 11, 10, 9),
    gsSPNTriangles_5b(8, 7, 6, 11, 9, 8, 5, 7, 8, 8, 10, 5),
    gsSPNTriangles_5b(8, 6, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_yaz_candle_base2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 28),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_yaz_candle_green_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_yaz_candle_v[58], 18, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_yaz_candle_red_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_yaz_candle_v[76], 24, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_yaz_candle_black_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 18, 19, 20, 21, 22, 23, 0, 0, 0),
    gsSPEndDisplayList(),
};
