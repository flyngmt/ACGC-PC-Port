#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_pst_tesyu01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_pst_tesyu01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_pst_tesyu01_pal[] = {
#include "assets/int_ike_pst_tesyu01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_pst_tesyu01_side1_tex[0x100];
#else
u8 int_ike_pst_tesyu01_side1_tex[] = {
#include "assets/int_ike_pst_tesyu01_side1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_pst_tesyu01_side2_tex[0x80];
#else
u8 int_ike_pst_tesyu01_side2_tex[] = {
#include "assets/int_ike_pst_tesyu01_side2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_pst_tesyu01_top1_tex[0x100];
#else
u8 int_ike_pst_tesyu01_top1_tex[] = {
#include "assets/int_ike_pst_tesyu01_top1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_pst_tesyu01_tesyu1_tex[0x200];
#else
u8 int_ike_pst_tesyu01_tesyu1_tex[] = {
#include "assets/int_ike_pst_tesyu01_tesyu1_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_pst_tesyu01_v[0x240 / sizeof(Vtx)];
#else
Vtx int_ike_pst_tesyu01_v[] = {
#include "assets/int_ike_pst_tesyu01_v.inc"
};
#endif

Gfx int_ike_pst_tesyu01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_pst_tesyu01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_pst_tesyu01_top1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_pst_tesyu01_v, 20, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_pst_tesyu01_side2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 5, 7, 6, 8, 9, 10),
    gsSPNTriangles_5b(8, 11, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_pst_tesyu01_side1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 12, 15, 13, 16, 17, 18),
    gsSPNTriangles_5b(17, 19, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_ike_pst_tesyu01_offT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, COMBINED, 0, PRIMITIVE, 0),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 190),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_pst_tesyu01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_pst_tesyu01_tesyu1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_pst_tesyu01_v[20], 16, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(3, 5, 4, 3, 6, 5, 6, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 12, 8, 11, 13, 12, 11, 13, 11, 14),
    gsSPNTriangles_5b(15, 13, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
