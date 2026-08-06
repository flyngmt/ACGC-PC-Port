#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_table02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_table02_pal[] = {
#include "assets/int_tak_table02_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_table02_top_tex[0x400];
#else
u8 int_tak_table02_top_tex[] = {
#include "assets/int_tak_table02_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_table02_under_tex[0x200];
#else
u8 int_tak_table02_under_tex[] = {
#include "assets/int_tak_table02_under_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_table02_wa_tex[0x80];
#else
u8 int_tak_table02_wa_tex[] = {
#include "assets/int_tak_table02_wa_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_table02_asi_tex[0x100];
#else
u8 int_tak_table02_asi_tex[] = {
#include "assets/int_tak_table02_asi_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_table02_v[0x1C0 / sizeof(Vtx)];
#else
Vtx int_tak_table02_v[] = {
#include "assets/int_tak_table02_v.inc"
};
#endif

Gfx int_tak_table02_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_table02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_table02_asi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_table02_v, 28, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_table02_wa_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_tak_table02_under_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_tak_table02_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
