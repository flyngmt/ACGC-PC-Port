#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_pl_kuroton_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_sum_pl_kuroton_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_sum_pl_kuroton_pal[] = {
#include "assets/int_sum_pl_kuroton/int_sum_pl_kuroton_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_kuroton_leaf_tex[0x400];
#else
u8 int_sum_pl_kuroton_leaf_tex[] = {
#include "assets/int_sum_pl_kuroton_leaf_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_kuroton_kuki_tex[0x100];
#else
u8 int_sum_pl_kuroton_kuki_tex[] = {
#include "assets/int_sum_pl_kuroton_kuki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_kuroton_earth_tex[0x80];
#else
u8 int_sum_pl_kuroton_earth_tex[] = {
#include "assets/int_sum_pl_kuroton_earth_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_kuroton_hachi_tex[0x100];
#else
u8 int_sum_pl_kuroton_hachi_tex[] = {
#include "assets/int_sum_pl_kuroton_hachi_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_pl_kuroton_v[0x5C0 / sizeof(Vtx)];
#else
Vtx int_sum_pl_kuroton_v[] = {
#include "assets/int_sum_pl_kuroton_v.inc"
};
#endif

Gfx int_sum_pl_kuroton_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_pl_kuroton_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_pl_kuroton_earth_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_pl_kuroton_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_pl_kuroton_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_pl_kuroton_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_pl_kuroton_hachi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_pl_kuroton_v[4], 14, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 1, 5, 6, 7),
    gsSPNTriangles_5b(3, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_pl_kuroton_kuki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 9, 10, 11, 9, 12, 13, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_sum_pl_kuroton_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_pl_kuroton_v[18], 32, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 9, 10, 10, 11, 8, 12, 13, 14),
    gsSPNTriangles_5b(14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 0, 0),
    gsSPVertex(&int_sum_pl_kuroton_v[50], 32, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(8, 9, 6, 10, 11, 12, 12, 13, 10, 14, 15, 16),
    gsSPNTriangles_5b(16, 17, 14, 18, 19, 20, 20, 21, 18, 22, 23, 24),
    gsSPNTriangles_5b(24, 25, 22, 26, 27, 28, 29, 30, 31, 0, 0, 0),
    gsSPVertex(&int_sum_pl_kuroton_v[82], 10, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(8, 9, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_sum_pl_kuroton_c(void) {
    pc_load_asset("assets/int_sum_pl_kuroton/int_sum_pl_kuroton_pal.bin", int_sum_pl_kuroton_pal, 0x20, 0xD21840, 0, 1);
}
#endif
