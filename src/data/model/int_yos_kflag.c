#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_yos_kflag_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 int_yos_kflag_pat[0x20];
#else
ATTRIBUTE_ALIGN(32) u8 int_yos_kflag_pat[] = {
#include "assets/int_yos_kflag_pat.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_kflag_pole_tex_txt[0x80];
#else
u8 int_yos_kflag_pole_tex_txt[] = {
#include "assets/int_yos_kflag_pole_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_kflag_flag_tex_txt[0x180];
#else
u8 int_yos_kflag_flag_tex_txt[] = {
#include "assets/int_yos_kflag_flag_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_yos_kflag_v[0x450 / sizeof(Vtx)];
#else
Vtx int_yos_kflag_v[] = {
#include "assets/int_yos_kflag_v.inc"
};
#endif

Gfx int_yos_kflag_obj_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yos_kflag_pat),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_yos_kflag_pole_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_yos_kflag_v, 32, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 6, 5, 7, 6, 8, 4, 6, 9, 10, 11),
    gsSPNTriangles_5b(12, 13, 11, 14, 15, 11, 16, 17, 11, 18, 19, 11),
    gsSPNTriangles_5b(20, 21, 11, 22, 23, 11, 24, 25, 11, 26, 27, 11),
    gsSPNTriangles_5b(28, 29, 11, 30, 31, 11, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_yos_kflag_v[32], 23, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 4, 5, 6, 5, 7),
    gsSPNTriangles_5b(4, 7, 5, 6, 8, 5, 9, 3, 5, 8, 9, 5),
    gsSPNTriangles_5b(10, 11, 12, 12, 13, 14, 15, 16, 12, 12, 17, 18),
    gsSPNTriangles_5b(12, 19, 20, 21, 22, 12, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 24, int_yos_kflag_flag_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_yos_kflag_v[55], 14, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 0, 4, 5),
    gsSPNTriangles_5b(6, 4, 0, 6, 0, 3, 7, 8, 9, 8, 10, 9),
    gsSPNTriangles_5b(11, 10, 8, 7, 12, 8, 12, 13, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};
