#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_wc02_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_wc02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_wc02_pal[] = {
#include "assets/int_sum_wc02_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 int_sum_wc02_mizu_tex_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
u16 int_sum_wc02_mizu_tex_rgb_ci4_pal[] = {
#include "assets/int_sum_wc02_mizu_tex_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc02_huta_tex[0x80];
#else
u8 int_sum_wc02_huta_tex[] = {
#include "assets/int_sum_wc02_huta_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc02_washside_tex[0x80];
#else
u8 int_sum_wc02_washside_tex[] = {
#include "assets/int_sum_wc02_washside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc02_tankfront_tex[0x100];
#else
u8 int_sum_wc02_tankfront_tex[] = {
#include "assets/int_sum_wc02_tankfront_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc02_benzaside_tex[0x100];
#else
u8 int_sum_wc02_benzaside_tex[] = {
#include "assets/int_sum_wc02_benzaside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc02_base_tex[0x80];
#else
u8 int_sum_wc02_base_tex[] = {
#include "assets/int_sum_wc02_base_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc02_paipside_tex[0x40];
#else
u8 int_sum_wc02_paipside_tex[] = {
#include "assets/int_sum_wc02_paipside_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc02_paip_tex[0x40];
#else
u8 int_sum_wc02_paip_tex[] = {
#include "assets/int_sum_wc02_paip_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc02_tankrevar_tex[0x40];
#else
u8 int_sum_wc02_tankrevar_tex[] = {
#include "assets/int_sum_wc02_tankrevar_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc02_shawer_tex[0x40];
#else
u8 int_sum_wc02_shawer_tex[] = {
#include "assets/int_sum_wc02_shawer_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc02_washtop_tex[0x80];
#else
u8 int_sum_wc02_washtop_tex[] = {
#include "assets/int_sum_wc02_washtop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc02_tanktop_tex[0x40];
#else
u8 int_sum_wc02_tanktop_tex[] = {
#include "assets/int_sum_wc02_tanktop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc02_benza_tex[0x100];
#else
u8 int_sum_wc02_benza_tex[] = {
#include "assets/int_sum_wc02_benza_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc02_boxtop_tex[0x80];
#else
u8 int_sum_wc02_boxtop_tex[] = {
#include "assets/int_sum_wc02_boxtop_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_wc02_mizu_tex[0x40];
#else
u8 int_sum_wc02_mizu_tex[] = {
#include "assets/int_sum_wc02_mizu_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_wc02_v[0x580 / sizeof(Vtx)];
#else
Vtx int_sum_wc02_v[] = {
#include "assets/int_sum_wc02_v.inc"
};
#endif

Gfx int_sum_wc02_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_wc02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_wc02_boxtop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_wc02_v, 10, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_wc02_tanktop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 6, 7, 8, 6, 8, 9, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_wc02_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_wc02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_wc02_benza_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_wc02_v[10], 26, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 8, int_sum_wc02_washtop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 4, 5, 6, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_wc02_shawer_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 7, 8, 9, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_wc02_tankrevar_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 10, 11, 12, 13, 14, 12, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_wc02_paip_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 15, 16, 17, 15, 17, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_wc02_paipside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 19, 20, 21, 22, 23, 24, 22, 24, 25),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_wc02_base_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_wc02_v[36], 19, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 2, 5, 6, 7),
    gsSPNTriangles_5b(7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_wc02_benzaside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(5, 9, 10, 11, 12, 13, 9, 14, 15, 12),
    gsSPNTriangles_5b(16, 17, 18, 11, 18, 17, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_wc02_tankfront_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_wc02_v[55], 29, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 4, 6, 7),
    gsSPNTriangles_5b(8, 9, 10, 6, 8, 11, 12, 13, 14, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_wc02_washside_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 15, 16, 17, 18, 19, 20, 21, 22, 23),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_wc02_huta_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(3, 24, 25, 26, 24, 27, 25, 27, 28, 25),
    gsSPEndDisplayList(),
};

Gfx int_sum_wc02_evwT_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 200),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_wc02_mizu_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_sum_wc02_mizu_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 2, 4),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH |
                         G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_wc02_v[84], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
