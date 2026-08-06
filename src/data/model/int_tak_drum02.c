#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_drum02_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_drum02_body_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_drum02_body_tex_pal[] = {
#include "assets/int_tak_drum02_body_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_drum02_body_tex[0x300];
#else
u8 int_tak_drum02_body_tex[] = {
#include "assets/int_tak_drum02_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_drum02_top_tex[0x100];
#else
u8 int_tak_drum02_top_tex[] = {
#include "assets/int_tak_drum02_top_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_drum02_futa_tex[0x80];
#else
u8 int_tak_drum02_futa_tex[] = {
#include "assets/int_tak_drum02_futa_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_drum02_v[0x1D0 / sizeof(Vtx)];
#else
Vtx int_tak_drum02_v[] = {
#include "assets/int_tak_drum02_v.inc"
};
#endif

Gfx int_tak_drum02_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_drum02_body_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_tak_drum02_top_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_drum02_v, 26, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(3, 5, 4, 3, 6, 5, 6, 7, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_tak_drum02_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(16, 8, 9, 10, 8, 11, 9, 10, 12, 13),
    gsSPNTriangles_5b(10, 9, 12, 14, 15, 16, 14, 17, 15, 13, 17, 14),
    gsSPNTriangles_5b(13, 12, 17, 18, 19, 20, 18, 21, 19, 20, 22, 23),
    gsSPNTriangles_5b(20, 19, 22, 24, 21, 18, 24, 25, 21, 16, 25, 24),
    gsSPNTriangles_5b(16, 15, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_tak_drum02_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_drum02_body_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_drum02_futa_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_drum02_v[26], 3, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
