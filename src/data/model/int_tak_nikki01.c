#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_nikki01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_nikki01_name_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_nikki01_name_pal[] = {
#include "assets/int_tak_nikki01_name_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nikki01_base_tex[0x200];
#else
u8 int_tak_nikki01_base_tex[] = {
#include "assets/int_tak_nikki01_base_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nikki01_himo_tex[0x100];
#else
u8 int_tak_nikki01_himo_tex[] = {
#include "assets/int_tak_nikki01_himo_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nikki01_name_tex[0x40];
#else
u8 int_tak_nikki01_name_tex[] = {
#include "assets/int_tak_nikki01_name_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nikki01_pen_tex[0x80];
#else
u8 int_tak_nikki01_pen_tex[] = {
#include "assets/int_tak_nikki01_pen_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_nikki01_maki_tex[0x20];
#else
u8 int_tak_nikki01_maki_tex[] = {
#include "assets/int_tak_nikki01_maki_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_nikki01_v[0x420 / sizeof(Vtx)];
#else
Vtx int_tak_nikki01_v[] = {
#include "assets/int_tak_nikki01_v.inc"
};
#endif

Gfx int_tak_nikki01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_nikki01_name_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_tak_nikki01_maki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_nikki01_v, 20, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 6, 7, 8, 6, 8, 9, 6, 9, 10),
    gsSPNTriangles_5b(6, 10, 11, 12, 13, 14, 12, 14, 15, 16, 13, 12),
    gsSPNTriangles_5b(16, 12, 17, 18, 15, 14, 18, 14, 19, 17, 12, 15),
    gsSPNTriangles_5b(17, 15, 18, 18, 19, 16, 18, 16, 17, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 32, int_tak_nikki01_pen_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_nikki01_v[20], 25, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 3, 4, 0, 3, 0, 2),
    gsSPNTriangles_5b(2, 1, 5, 6, 3, 2, 6, 2, 5, 5, 1, 7),
    gsSPNTriangles_5b(7, 1, 8, 9, 10, 7, 9, 7, 8, 8, 1, 0),
    gsSPNTriangles_5b(4, 9, 8, 4, 8, 0, 11, 12, 13, 11, 13, 14),
    gsSPNTriangles_5b(15, 16, 12, 15, 12, 11, 17, 18, 19, 17, 19, 20),
    gsSPNTriangles_5b(14, 13, 18, 14, 18, 17, 21, 20, 22, 21, 22, 23),
    gsSPNTriangles_5b(21, 23, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, int_tak_nikki01_name_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPVertex(&int_tak_nikki01_v[45], 18, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 6, 7, 8, 6, 8, 9, 9, 8, 10),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 7, 12, 7, 6, 5, 4, 13),
    gsSPNTriangles_5b(5, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_tak_nikki01_base_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 14, 15, 16, 14, 16, 17, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_nikki01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_nikki01_name_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_nikki01_himo_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_nikki01_v[63], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
