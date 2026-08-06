#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sugi_chesstable_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sugi_chesstable_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sugi_chesstable_pal[] = {
#include "assets/int_sugi_chesstable_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sugi_chesstable_all_tex_txt[0x800];
#else
u8 int_sugi_chesstable_all_tex_txt[] = {
#include "assets/int_sugi_chesstable_all_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sugi_chesstable_v[0x430 / sizeof(Vtx)];
#else
Vtx int_sugi_chesstable_v[] = {
#include "assets/int_sugi_chesstable_v.inc"
};
#endif

Gfx sugi_chesstable_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sugi_chesstable_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, int_sugi_chesstable_all_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sugi_chesstable_v, 32, 0),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 4, 6, 7, 4, 7, 5, 6, 0, 3),
    gsSPNTriangles_5b(6, 3, 7, 8, 9, 10, 9, 11, 10, 12, 8, 10),
    gsSPNTriangles_5b(11, 12, 10, 13, 14, 15, 13, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(17, 19, 20, 21, 22, 23, 21, 23, 24, 25, 26, 27),
    gsSPNTriangles_5b(25, 27, 28, 29, 30, 31, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_sugi_chesstable_v[32], 32, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 11, 12, 13, 11, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 15, 17, 18, 19, 20, 21, 19, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 25, 26, 27, 28, 29, 27, 29, 30),
    gsSPVertex(&int_sugi_chesstable_v[63], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
