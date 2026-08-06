#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_din_trex_body_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_din_trex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_din_trex_pal[] = {
#include "assets/int_din_trex_body/int_din_trex_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trex_bd_tex[0x300];
#else
u8 int_din_trex_bd_tex[] = {
#include "assets/int_din_trex_bd_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trex_leg_tex[0x80];
#else
u8 int_din_trex_leg_tex[] = {
#include "assets/int_din_trex_leg_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trex_ic_tex[0x100];
#else
u8 int_din_trex_ic_tex[] = {
#include "assets/int_din_trex_ic_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trex_ni_tex[0x100];
#else
u8 int_din_trex_ni_tex[] = {
#include "assets/int_din_trex_ni_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trex_baceB_tex[0x200];
#else
u8 int_din_trex_baceB_tex[] = {
#include "assets/int_din_trex_baceB_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_din_trex_body_v[0x4F0 / sizeof(Vtx)];
#else
Vtx int_din_trex_body_v[] = {
#include "assets/int_din_trex_body_v.inc"
};
#endif

Gfx int_din_trex_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_trex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_din_trex_baceB_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_din_trex_body_v, 8, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 6, 7, 1, 6, 1, 0, 5, 4, 7),
    gsSPNTriangles_5b(5, 7, 6, 0, 3, 5, 0, 5, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_din_trex_bodyT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_trex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_din_trex_ni_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_din_trex_body_v[8], 24, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 9, 10, 10, 11, 8, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 14, 16, 17, 18, 16, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(22, 23, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_din_trex_ic_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_din_trex_body_v[32], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 9, 10, 10, 11, 8, 12, 13, 14),
    gsSPNTriangles_5b(14, 15, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_trex_leg_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_din_trex_body_v[48], 31, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_din_trex_bd_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(15, 18, 19, 20, 21, 22, 23, 21, 23, 24),
    gsSPNTriangles_5b(20, 24, 23, 18, 20, 23, 21, 24, 25, 26, 24, 20),
    gsSPNTriangles_5b(23, 22, 27, 23, 27, 18, 28, 26, 20, 28, 20, 19),
    gsSPNTriangles_5b(29, 21, 25, 29, 25, 30, 24, 26, 25, 21, 29, 22),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_din_trex_body_c(void) {
    pc_load_asset("assets/int_din_trex_body/int_din_trex_pal.bin", int_din_trex_pal, 0x20, 0x91A740, 0, 1);
}
#endif
