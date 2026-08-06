#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ari_isu01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_ari_nagaisu1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_ari_nagaisu1_pal[] = {
#include "assets/int_ari_isu01/int_ari_nagaisu1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ari_isu01_1_tex[0x200];
#else
u8 int_ari_isu01_1_tex[] = {
#include "assets/int_ari_isu01_1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ari_isu01_0_tex[0x400];
#else
u8 int_ari_isu01_0_tex[] = {
#include "assets/int_ari_isu01_0_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ari_isu01_2_tex[0x200];
#else
u8 int_ari_isu01_2_tex[] = {
#include "assets/int_ari_isu01_2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ari_isu01_v[0x260 / sizeof(Vtx)];
#else
Vtx int_ari_isu01_v[] = {
#include "assets/int_ari_isu01_v.inc"
};
#endif

Gfx int_ari_isu01_00T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ari_nagaisu1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ari_isu01_2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ari_isu01_v, 18, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 2, 3, 4, 0, 2, 4),
    gsSPNTriangles_5b(5, 4, 6, 5, 0, 4, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_ari_isu01_0_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(9, 7, 8, 9, 7, 10, 8, 7, 11, 10),
    gsSPNTriangles_5b(10, 12, 8, 9, 13, 14, 13, 15, 14, 13, 16, 15),
    gsSPNTriangles_5b(16, 17, 15, 14, 7, 9, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, int_ari_isu01_1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ari_isu01_v[18], 20, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 4, 6, 5),
    gsSPNTriangles_5b(4, 7, 6, 4, 3, 7, 8, 9, 10, 9, 11, 10),
    gsSPNTriangles_5b(9, 12, 11, 9, 8, 12, 13, 14, 15, 16, 13, 15),
    gsSPNTriangles_5b(17, 16, 15, 17, 15, 14, 18, 2, 1, 19, 18, 1),
    gsSPNTriangles_5b(0, 19, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_ari_isu01_c(void) {
    pc_load_asset("assets/int_ari_isu01/int_ari_nagaisu1_pal.bin", int_ari_nagaisu1_pal, 0x20, 0x8E6780, 0, 1);
}
#endif
