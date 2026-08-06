#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_din_trex_tail_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_din_trex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_din_trex_pal[] = {
#include "assets/int_din_trex_tail/int_din_trex_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trex_tail_tex[0x400];
#else
u8 int_din_trex_tail_tex[] = {
#include "assets/int_din_trex_tail_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trex_baceC_tex[0x200];
#else
u8 int_din_trex_baceC_tex[] = {
#include "assets/int_din_trex_baceC_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trex_poleC_tex[0x80];
#else
u8 int_din_trex_poleC_tex[] = {
#include "assets/int_din_trex_poleC_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_din_trex_tail_v[0x240 / sizeof(Vtx)];
#else
Vtx int_din_trex_tail_v[] = {
#include "assets/int_din_trex_tail_v.inc"
};
#endif

Gfx int_din_trex_tail_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_trex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_din_trex_baceC_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_din_trex_tail_v, 8, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 0),
    gsSPNTriangles_5b(4, 0, 3, 5, 6, 1, 5, 1, 0, 3, 2, 7),
    gsSPNTriangles_5b(3, 7, 4, 4, 7, 6, 4, 6, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_din_trex_tailT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_trex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_trex_poleC_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_din_trex_tail_v[8], 28, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 1, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 6, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_din_trex_tail_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(14, 10, 11, 12, 13, 10, 12, 13, 12, 14),
    gsSPNTriangles_5b(15, 13, 14, 15, 14, 16, 17, 15, 16, 17, 16, 18),
    gsSPNTriangles_5b(19, 20, 21, 19, 21, 22, 23, 19, 22, 23, 22, 24),
    gsSPNTriangles_5b(25, 23, 24, 25, 24, 26, 27, 25, 26, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_din_trex_tail_c(void) {
    pc_load_asset("assets/int_din_trex_tail/int_din_trex_pal.bin", int_din_trex_pal, 0x20, 0x91C440, 0, 1);
}
#endif
