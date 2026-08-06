#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sugi_alchair_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sugi_alchair_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sugi_alchair_pal[] = {
#include "assets/int_sugi_alchair_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sugi_alchair_all_tex_txt[0x800];
#else
u8 int_sugi_alchair_all_tex_txt[] = {
#include "assets/int_sugi_alchair_all_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sugi_alchair_v[0x340 / sizeof(Vtx)];
#else
Vtx int_sugi_alchair_v[] = {
#include "assets/int_sugi_alchair_v.inc"
};
#endif

Gfx sugi_aluminum_c_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sugi_alchair_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, int_sugi_alchair_all_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sugi_alchair_v, 16, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsSPVertex(&int_sugi_alchair_v[16], 32, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 0, 2, 3, 3, 4, 5),
    gsSPNTriangles_5b(3, 5, 0, 6, 7, 8, 6, 8, 9, 9, 10, 11),
    gsSPNTriangles_5b(9, 11, 6, 12, 13, 14, 13, 15, 14, 15, 12, 14),
    gsSPNTriangles_5b(16, 17, 18, 16, 18, 19, 20, 21, 22, 21, 23, 22),
    gsSPNTriangles_5b(23, 20, 22, 24, 25, 26, 24, 27, 25, 24, 26, 27),
    gsSPNTriangles_5b(28, 29, 30, 28, 30, 31, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_sugi_alchair_v[48], 4, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 3, 1, 0, 2, 3),
    gsSPEndDisplayList(),
};
