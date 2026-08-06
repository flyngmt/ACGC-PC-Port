#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 tol_tamaire_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 tol_tamaire_pal[] = {
#include "assets/tol_tamaire_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_tamaire_r1_tex[0x200];
#else
u8 tol_tamaire_r1_tex[] = {
#include "assets/tol_tamaire_r1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_tamaire_r2_tex[0x200];
#else
u8 tol_tamaire_r2_tex[] = {
#include "assets/tol_tamaire_r2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_tamaire_r3_tex[0x200];
#else
u8 tol_tamaire_r3_tex[] = {
#include "assets/tol_tamaire_r3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_tamaire_w1_tex[0x200];
#else
u8 tol_tamaire_w1_tex[] = {
#include "assets/tol_tamaire_w1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_tamaire_w2_tex[0x200];
#else
u8 tol_tamaire_w2_tex[] = {
#include "assets/tol_tamaire_w2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 tol_tamaire_w3_tex[0x200];
#else
u8 tol_tamaire_w3_tex[] = {
#include "assets/tol_tamaire_w3_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx tol_tamaire_v[0x40 / sizeof(Vtx)];
#else
Vtx tol_tamaire_v[] = {
#include "assets/tol_tamaire_v.inc"
};
#endif

Gfx tol_tamaire_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_tamaire_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_tamaire_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
