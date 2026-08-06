#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_pl_draca02_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_pl_draca02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_pl_draca02_pal[] = {
#include "assets/int_sum_pl_draca02_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 int_sum_pl_kuroton_pal[0x20 / sizeof(u16)];
#else
static u16 int_sum_pl_kuroton_pal[] = {
#include "assets/int_sum_pl_draca02/int_sum_pl_kuroton_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_draca02_stand2_tex[0x100];
#else
u8 int_sum_pl_draca02_stand2_tex[] = {
#include "assets/int_sum_pl_draca02_stand2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_draca02_stand_tex[0x180];
#else
u8 int_sum_pl_draca02_stand_tex[] = {
#include "assets/int_sum_pl_draca02_stand_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_draca02_leaf_tex[0x180];
#else
u8 int_sum_pl_draca02_leaf_tex[] = {
#include "assets/int_sum_pl_draca02_leaf_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_draca02_hachi_tex[0x100];
#else
u8 int_sum_pl_draca02_hachi_tex[] = {
#include "assets/int_sum_pl_draca02_hachi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_pl_draca02_earth_tex[0x80];
#else
u8 int_sum_pl_draca02_earth_tex[] = {
#include "assets/int_sum_pl_draca02_earth_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_pl_draca02_v[0x650 / sizeof(Vtx)];
#else
Vtx int_sum_pl_draca02_v[] = {
#include "assets/int_sum_pl_draca02_v.inc"
};
#endif

Gfx int_sum_pl_draca02_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_pl_draca02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_pl_draca02_earth_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_pl_draca02_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_pl_draca02_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_pl_kuroton_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_pl_draca02_hachi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_pl_draca02_v[4], 9, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 1, 0, 5, 6),
    gsSPNTriangles_5b(7, 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_pl_draca02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_pl_draca02_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_pl_draca02_v[13], 32, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 7, 6, 10, 11, 12, 13, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(31, 29, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_sum_pl_draca02_v[45], 32, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 2, 1, 3, 4, 5, 6),
    gsSPNTriangles_5b(7, 5, 4, 8, 9, 10, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(17, 18, 19, 20, 21, 22, 22, 21, 23, 24, 25, 26),
    gsSPNTriangles_5b(27, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_sum_pl_draca02_v[75], 26, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 1, 0, 4, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_pl_draca02_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 19, 20, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_pl_draca02_stand2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 21, 22, 23, 21, 24, 25, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_sum_pl_draca02_c(void) {
    pc_load_asset("assets/int_sum_pl_draca02/int_sum_pl_kuroton_pal.bin", int_sum_pl_kuroton_pal, 0x20, 0xD1E5C0, 0, 1);
}
#endif
