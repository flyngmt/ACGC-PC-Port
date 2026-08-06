#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_yos_b_feeder_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_yaz_b_feeder_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_yaz_b_feeder_pal[] = {
#include "assets/int_yaz_b_feeder_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_b_feeder_pole_tex_txt[0x1C0];
#else
u8 int_yaz_b_feeder_pole_tex_txt[] = {
#include "assets/int_yaz_b_feeder_pole_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_b_feeder_ana_tex_txt[0x180];
#else
u8 int_yaz_b_feeder_ana_tex_txt[] = {
#include "assets/int_yaz_b_feeder_ana_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_b_feeder_ura_tex_txt[0x180];
#else
u8 int_yaz_b_feeder_ura_tex_txt[] = {
#include "assets/int_yaz_b_feeder_ura_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_b_feeder_wood_tex_txt[0x80];
#else
u8 int_yaz_b_feeder_wood_tex_txt[] = {
#include "assets/int_yaz_b_feeder_wood_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_b_feeder_yane_tex_txt[0x80];
#else
u8 int_yaz_b_feeder_yane_tex_txt[] = {
#include "assets/int_yaz_b_feeder_yane_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_b_feeder_wa_tex_txt[0x200];
#else
u8 int_yaz_b_feeder_wa_tex_txt[] = {
#include "assets/int_yaz_b_feeder_wa_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_yos_b_feeder_v[0x410 / sizeof(Vtx)];
#else
Vtx int_yos_b_feeder_v[] = {
#include "assets/int_yos_b_feeder_v.inc"
};
#endif

Gfx int_yaz_b_feeder_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yaz_b_feeder_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 56, int_yaz_b_feeder_pole_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_yos_b_feeder_v, 26, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(3, 4, 5, 6, 6, 7, 4, 4, 7, 5),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(14, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(15, 9, 8, 15, 8, 16, 16, 14, 13, 16, 13, 15),
    gsSPNTriangles_5b(17, 18, 19, 17, 19, 20, 21, 22, 23, 24, 18, 17),
    gsSPNTriangles_5b(24, 17, 25, 25, 23, 22, 25, 22, 24, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_yaz_b_feeder_ana_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 188),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_yos_b_feeder_v[26], 30, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 5, 8, 9, 5, 9, 6, 1, 4, 7),
    gsSPNTriangles_5b(1, 7, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_yaz_b_feeder_ura_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 188),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 10, 12, 13, 14, 10, 13),
    gsSPNTriangles_5b(14, 13, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_yaz_b_feeder_wood_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 20, 21, 22, 20, 22, 23, 23, 22, 24),
    gsSPNTriangles_5b(23, 24, 25, 26, 27, 28, 26, 28, 29, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_yaz_b_feeder_yane_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_yos_b_feeder_v[56], 9, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_yaz_b_feeder_wa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 6, 7, 8, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
