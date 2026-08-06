#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kob_getabako1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_kob_getabako1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_kob_getabako1_pal[] = {
#include "assets/int_kob_getabako1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_getabako1_naka1_tex[0x80];
#else
u8 int_kob_getabako1_naka1_tex[] = {
#include "assets/int_kob_getabako1_naka1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_getabako1_naka2_tex[0x80];
#else
u8 int_kob_getabako1_naka2_tex[] = {
#include "assets/int_kob_getabako1_naka2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_getabako1_side_tex[0x100];
#else
u8 int_kob_getabako1_side_tex[] = {
#include "assets/int_kob_getabako1_side_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_getabako1_top_tex[0x100];
#else
u8 int_kob_getabako1_top_tex[] = {
#include "assets/int_kob_getabako1_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_getabako1_ura_tex[0x200];
#else
u8 int_kob_getabako1_ura_tex[] = {
#include "assets/int_kob_getabako1_ura_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_getabako1_atumi_tex[0x200];
#else
u8 int_kob_getabako1_atumi_tex[] = {
#include "assets/int_kob_getabako1_atumi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_getabako1_wear_tex[0x80];
#else
u8 int_kob_getabako1_wear_tex[] = {
#include "assets/int_kob_getabako1_wear_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_getabako1_book2_tex[0x80];
#else
u8 int_kob_getabako1_book2_tex[] = {
#include "assets/int_kob_getabako1_book2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_getabako1_book1_tex[0x80];
#else
u8 int_kob_getabako1_book1_tex[] = {
#include "assets/int_kob_getabako1_book1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kob_getabako1_book3_tex[0x80];
#else
u8 int_kob_getabako1_book3_tex[] = {
#include "assets/int_kob_getabako1_book3_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kob_getabako1_v[0x5C0 / sizeof(Vtx)];
#else
Vtx int_kob_getabako1_v[] = {
#include "assets/int_kob_getabako1_v.inc"
};
#endif

Gfx int_kob_getabako1_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kob_getabako1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kob_getabako1_ura_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kob_getabako1_v, 16, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_kob_getabako1_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_kob_getabako1_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kob_getabako1_naka2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kob_getabako1_v[16], 24, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 4, 6, 7, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kob_getabako1_naka1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&int_kob_getabako1_v[40], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kob_getabako1_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kob_getabako1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kob_getabako1_book3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kob_getabako1_v[56], 21, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kob_getabako1_book1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(3, 7, 8, 9, 7, 9, 10, 11, 12, 13),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kob_getabako1_book2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(3, 14, 15, 16, 17, 18, 19, 17, 19, 20),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kob_getabako1_wear_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_kob_getabako1_v[77], 15, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 0, 4, 5, 0),
    gsSPNTriangles_5b(6, 1, 0, 7, 8, 9, 7, 9, 10, 3, 0, 2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kob_getabako1_atumi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 11, 12, 13, 11, 13, 14, 0, 0, 0),
    gsSPEndDisplayList(),
};
