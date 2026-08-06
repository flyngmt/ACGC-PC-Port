#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_yaz_telescope_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_yaz_telescope_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_yaz_telescope_pal[] = {
#include "assets/int_yaz_telescope_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_telescope_body_tex_txt[0x280];
#else
u8 int_yaz_telescope_body_tex_txt[] = {
#include "assets/int_yaz_telescope_body_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_telescope_tutu_tex_txt[0x80];
#else
u8 int_yaz_telescope_tutu_tex_txt[] = {
#include "assets/int_yaz_telescope_tutu_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_telescope_lens_tex_txt[0x200];
#else
u8 int_yaz_telescope_lens_tex_txt[] = {
#include "assets/int_yaz_telescope_lens_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_telescope_maru_tex_txt[0x80];
#else
u8 int_yaz_telescope_maru_tex_txt[] = {
#include "assets/int_yaz_telescope_maru_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_telescope_ashi_tex_txt[0x180];
#else
u8 int_yaz_telescope_ashi_tex_txt[] = {
#include "assets/int_yaz_telescope_ashi_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yaz_telescope_tome_tex_txt[0x100];
#else
u8 int_yaz_telescope_tome_tex_txt[] = {
#include "assets/int_yaz_telescope_tome_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_yaz_telescope_v[0x3A0 / sizeof(Vtx)];
#else
Vtx int_yaz_telescope_v[] = {
#include "assets/int_yaz_telescope_v.inc"
};
#endif

Gfx int_yaz_telescope_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yaz_telescope_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 80, 16, int_yaz_telescope_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_yaz_telescope_v, 30, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 1, 4, 7, 1, 7, 2, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 11, 6, 5, 9, 0, 3, 9, 3, 10),
    gsSPNTriangles_5b(5, 8, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_yaz_telescope_tutu_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(15, 12, 13, 14, 14, 13, 15, 14, 15, 16),
    gsSPNTriangles_5b(12, 14, 16, 12, 16, 17, 13, 12, 17, 13, 17, 15),
    gsSPNTriangles_5b(18, 19, 20, 20, 19, 21, 20, 21, 22, 18, 20, 22),
    gsSPNTriangles_5b(18, 22, 23, 19, 18, 23, 19, 23, 21, 21, 23, 22),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_yaz_telescope_lens_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 24, 25, 26, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_yaz_telescope_maru_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 27, 28, 29, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 96, 8, int_yaz_telescope_ashi_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_yaz_telescope_v[30], 28, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 0, 3, 1),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 4, 5, 6, 7, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(13, 14, 15, 16, 17, 18, 19, 20, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_yaz_telescope_tome_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(1, 22, 23, 24, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 25, 26, 27, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
