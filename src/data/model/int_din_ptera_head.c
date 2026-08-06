#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_din_ptera_head_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_din_ptera_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_din_ptera_pal[] = {
#include "assets/int_din_ptera_head/int_din_ptera_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_ptera_body_tex[0x180];
#else
u8 int_din_ptera_body_tex[] = {
#include "assets/int_din_ptera_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_ptera_leg_tex[0x80];
#else
u8 int_din_ptera_leg_tex[] = {
#include "assets/int_din_ptera_leg_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_ptera_shin_tex[0x100];
#else
u8 int_din_ptera_shin_tex[] = {
#include "assets/int_din_ptera_shin_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_ptera_h_tex[0x200];
#else
u8 int_din_ptera_h_tex[] = {
#include "assets/int_din_ptera_h_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_ptera_kubi_tex[0x80];
#else
u8 int_din_ptera_kubi_tex[] = {
#include "assets/int_din_ptera_kubi_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_ptera_baceB_tex[0x200];
#else
u8 int_din_ptera_baceB_tex[] = {
#include "assets/int_din_ptera_baceB_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_ptera_poleB_tex[0x80];
#else
u8 int_din_ptera_poleB_tex[] = {
#include "assets/int_din_ptera_poleB_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_din_ptera_head_v[0x470 / sizeof(Vtx)];
#else
Vtx int_din_ptera_head_v[] = {
#include "assets/int_din_ptera_head_v.inc"
};
#endif

Gfx int_din_ptera_head_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_ptera_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_din_ptera_baceB_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_din_ptera_head_v, 8, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 3, 3, 5, 6, 3, 6, 0, 0, 6, 7),
    gsSPNTriangles_5b(0, 7, 1, 1, 7, 4, 1, 4, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_din_ptera_headT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_ptera_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_ptera_poleB_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_din_ptera_head_v[8], 20, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 1, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_ptera_kubi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 5, 6, 7, 5, 8, 9, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, int_din_ptera_h_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12, 10, 11, 12, 13, 10, 14, 15, 16, 10),
    gsSPNTriangles_5b(17, 18, 11, 18, 12, 11, 19, 16, 15, 14, 19, 13),
    gsSPNTriangles_5b(12, 11, 19, 12, 19, 15, 13, 19, 11, 11, 10, 13),
    gsSPNTriangles_5b(15, 10, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_din_ptera_shin_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_din_ptera_head_v[28], 30, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 9, 10, 10, 11, 8, 12, 13, 14),
    gsSPNTriangles_5b(14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21, 22),
    gsSPNTriangles_5b(22, 23, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_ptera_leg_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 27, 28, 29, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_din_ptera_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_din_ptera_head_v[58], 13, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 9, 6),
    gsSPNTriangles_5b(5, 4, 1, 3, 11, 10, 5, 1, 0, 5, 0, 12),
    gsSPNTriangles_5b(10, 12, 0, 3, 10, 0, 5, 12, 6, 9, 12, 10),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_din_ptera_head_c(void) {
    pc_load_asset("assets/int_din_ptera_head/int_din_ptera_pal.bin", int_din_ptera_pal, 0x20, 0x9166A0, 0, 1);
}
#endif
