#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_din_trikera_body_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_din_trikera_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_din_trikera_pal[] = {
#include "assets/int_din_trikera_body/int_din_trikera_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trikera_body_tex[0x300];
#else
u8 int_din_trikera_body_tex[] = {
#include "assets/int_din_trikera_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trikera_leg_tex[0x80];
#else
u8 int_din_trikera_leg_tex[] = {
#include "assets/int_din_trikera_leg_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trikera_shin_tex[0x100];
#else
u8 int_din_trikera_shin_tex[] = {
#include "assets/int_din_trikera_shin_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trikera_thigh_tex[0x100];
#else
u8 int_din_trikera_thigh_tex[] = {
#include "assets/int_din_trikera_thigh_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trikera_baceB_tex[0x200];
#else
u8 int_din_trikera_baceB_tex[] = {
#include "assets/int_din_trikera_baceB_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_din_trikera_body_v[0x450 / sizeof(Vtx)];
#else
Vtx int_din_trikera_body_v[] = {
#include "assets/int_din_trikera_body_v.inc"
};
#endif

Gfx int_din_trikera_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_trikera_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_din_trikera_baceB_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_din_trikera_body_v, 8, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 3, 3, 5, 6, 3, 6, 0, 0, 6, 7),
    gsSPNTriangles_5b(0, 7, 1, 1, 7, 4, 1, 4, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_din_trikera_bodyT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_trikera_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_din_trikera_thigh_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_din_trikera_body_v[8], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 9, 10, 10, 11, 8, 12, 13, 14),
    gsSPNTriangles_5b(14, 15, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_din_trikera_shin_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_din_trikera_body_v[24], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 9, 10, 10, 11, 8, 12, 13, 14),
    gsSPNTriangles_5b(14, 15, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_trikera_leg_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_din_trikera_body_v[40], 29, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 9, 10, 10, 11, 8, 12, 13, 14),
    gsSPNTriangles_5b(14, 15, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_din_trikera_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(15, 16, 17, 18, 17, 19, 18, 20, 21, 18),
    gsSPNTriangles_5b(19, 17, 22, 23, 24, 25, 26, 23, 25, 19, 22, 27),
    gsSPNTriangles_5b(19, 27, 20, 25, 20, 27, 26, 25, 27, 19, 20, 18),
    gsSPNTriangles_5b(21, 20, 25, 24, 21, 25, 27, 22, 28, 27, 28, 26),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_din_trikera_body_c(void) {
    pc_load_asset("assets/int_din_trikera_body/int_din_trikera_pal.bin", int_din_trikera_pal, 0x20, 0x91CE20, 0, 1);
}
#endif
