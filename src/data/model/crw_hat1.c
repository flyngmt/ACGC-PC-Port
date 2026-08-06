#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx crw_hat1_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 crw_hat1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 crw_hat1_pal[] = {
#include "assets/crw_hat1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 crw_hat1_tex_txt[0x80];
#else
u8 crw_hat1_tex_txt[] = {
#include "assets/crw_hat1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 crw_hat2_tex_txt[0x200];
#else
u8 crw_hat2_tex_txt[] = {
#include "assets/crw_hat2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 crw_hat3_tex_txt[0x80];
#else
u8 crw_hat3_tex_txt[] = {
#include "assets/crw_hat3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx crw_hat1_v[0x250 / sizeof(Vtx)];
#else
Vtx crw_hat1_v[] = {
#include "assets/crw_hat1_v.inc"
};
#endif

Gfx crw_hat1_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, crw_hat1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, crw_hat1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(crw_hat1_v, 30, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 1, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(3, 8, 9, 8, 10, 11, 10, 7, 6, 7, 0, 5),
    gsSPNTriangles_5b(2, 5, 0, 4, 2, 1, 9, 4, 3, 11, 9, 8),
    gsSPNTriangles_5b(6, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, crw_hat2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(18, 12, 13, 14, 15, 16, 12, 14, 15, 12),
    gsSPNTriangles_5b(17, 18, 19, 19, 15, 17, 20, 21, 22, 22, 17, 20),
    gsSPNTriangles_5b(23, 24, 25, 25, 20, 23, 26, 27, 28, 23, 26, 28),
    gsSPNTriangles_5b(14, 13, 29, 29, 26, 14, 25, 21, 20, 29, 27, 26),
    gsSPNTriangles_5b(22, 18, 17, 28, 24, 23, 19, 16, 15, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, crw_hat3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&crw_hat1_v[30], 7, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 2, 5, 3, 2),
    gsSPNTriangles_5b(6, 0, 2, 1, 5, 2, 4, 6, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};
