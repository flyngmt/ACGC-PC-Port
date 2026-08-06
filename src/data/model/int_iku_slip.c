#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iku_slip_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iku_slip_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iku_slip_pal[] = {
#include "assets/int_iku_slip_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iku_slip_all_tex_txt[0x400];
#else
u8 int_iku_slip_all_tex_txt[] = {
#include "assets/int_iku_slip_all_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iku_slip_v[0x5E0 / sizeof(Vtx)];
#else
Vtx int_iku_slip_v[] = {
#include "assets/int_iku_slip_v.inc"
};
#endif

Gfx int_iku_slip_model_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iku_slip_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_iku_slip_all_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iku_slip_v, 32, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 2, 7),
    gsSPNTriangles_5b(8, 9, 1, 10, 11, 9, 12, 7, 13, 14, 15, 11),
    gsSPNTriangles_5b(16, 17, 15, 18, 5, 4, 19, 13, 17, 20, 21, 3),
    gsSPNTriangles_5b(22, 23, 18, 24, 25, 26, 24, 27, 25, 28, 29, 30),
    gsSPVertex(&int_iku_slip_v[31], 32, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 1, 5, 6, 4),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 27, 29),
    gsSPNTriangles_5b(30, 29, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_iku_slip_v[63], 31, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 2, 4, 5, 4, 6),
    gsSPNTriangles_5b(7, 6, 8, 9, 8, 10, 11, 12, 13, 14, 13, 15),
    gsSPNTriangles_5b(16, 15, 17, 18, 17, 12, 19, 20, 21, 22, 23, 24),
    gsSPNTriangles_5b(25, 26, 27, 28, 29, 30, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
