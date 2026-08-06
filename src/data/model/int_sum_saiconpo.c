#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_saiconpo_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_saiconpo_pal[] = {
#include "assets/int_saiconpo_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_saiconpo_body_tex[0x480];
#else
u8 int_sum_saiconpo_body_tex[] = {
#include "assets/int_sum_saiconpo_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_saiconpo_side_tex[0x100];
#else
u8 int_sum_saiconpo_side_tex[] = {
#include "assets/int_sum_saiconpo_side_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_saiconpo_v[0x100 / sizeof(Vtx)];
#else
Vtx int_sum_saiconpo_v[] = {
#include "assets/int_sum_saiconpo_v.inc"
};
#endif

Gfx int_sum_saiconpo_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_saiconpo_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_saiconpo_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_saiconpo_v, 16, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 48, int_sum_saiconpo_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 13, 8, 11, 13, 11, 14, 0, 0, 0),
    gsSPEndDisplayList(),
};
