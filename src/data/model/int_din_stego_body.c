#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_din_stego_body_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_din_stego_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_din_stego_pal[] = {
#include "assets/int_din_stego_body/int_din_stego_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_stego_body_tex[0x300];
#else
u8 int_din_stego_body_tex[] = {
#include "assets/int_din_stego_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_stego_leg_tex[0x80];
#else
u8 int_din_stego_leg_tex[] = {
#include "assets/int_din_stego_leg_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_stego_shin_tex[0x100];
#else
u8 int_din_stego_shin_tex[] = {
#include "assets/int_din_stego_shin_tex.inc"
};
#endif

#ifdef TARGET_PC
static u8 int_din_stego_fin_tex[0x200];
#else
static u8 int_din_stego_fin_tex[] = {
#include "assets/int_din_stego_body/int_din_stego_fin_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_stego_baceB_tex[0x80];
#else
u8 int_din_stego_baceB_tex[] = {
#include "assets/int_din_stego_baceB_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_din_stego_body_v[0x510 / sizeof(Vtx)];
#else
Vtx int_din_stego_body_v[] = {
#include "assets/int_din_stego_body_v.inc"
};
#endif

Gfx int_din_stego_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_stego_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_stego_baceB_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_din_stego_body_v, 8, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 3, 3, 5, 6, 3, 6, 0, 0, 6, 7),
    gsSPNTriangles_5b(0, 7, 1, 1, 7, 4, 1, 4, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_din_stego_bodyT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_stego_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_din_stego_fin_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_din_stego_body_v[8], 12, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_din_stego_shin_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_din_stego_body_v[20], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 9, 10, 10, 11, 8, 12, 13, 14),
    gsSPNTriangles_5b(14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21, 22),
    gsSPNTriangles_5b(22, 23, 20, 24, 25, 26, 26, 27, 24, 28, 29, 30),
    gsSPNTriangles_5b(30, 31, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_stego_leg_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_din_stego_body_v[52], 29, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 1, 0, 4, 5, 6),
    gsSPNTriangles_5b(7, 5, 4, 8, 9, 10, 11, 9, 8, 12, 13, 14),
    gsSPNTriangles_5b(15, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_din_stego_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 21, 18, 17, 16, 25, 26, 23, 22),
    gsSPNTriangles_5b(17, 25, 27, 17, 27, 24, 22, 24, 27, 26, 22, 27),
    gsSPNTriangles_5b(17, 24, 18, 21, 24, 22, 27, 25, 28, 27, 28, 26),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_din_stego_body_c(void) {
    pc_load_asset("assets/int_din_stego_body/int_din_stego_pal.bin", int_din_stego_pal, 0x20, 0x919260, 0, 1);
    pc_load_asset("assets/int_din_stego_body/int_din_stego_fin_tex.bin", int_din_stego_fin_tex, 0x200, 0x919280, 0, 0);
}
#endif
