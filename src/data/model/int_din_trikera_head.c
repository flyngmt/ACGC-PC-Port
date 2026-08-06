#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_din_trikera_head_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_din_trikera_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_din_trikera_pal[] = {
#include "assets/int_din_trikera_head/int_din_trikera_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trikera_skull_tex[0x400];
#else
u8 int_din_trikera_skull_tex[] = {
#include "assets/int_din_trikera_skull_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trikera_horn_tex[0x100];
#else
u8 int_din_trikera_horn_tex[] = {
#include "assets/int_din_trikera_horn_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trikera_baceA_tex[0x200];
#else
u8 int_din_trikera_baceA_tex[] = {
#include "assets/int_din_trikera_baceA_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_trikera_poleA_tex[0x80];
#else
u8 int_din_trikera_poleA_tex[] = {
#include "assets/int_din_trikera_poleA_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_din_trikera_head_v[0x330 / sizeof(Vtx)];
#else
Vtx int_din_trikera_head_v[] = {
#include "assets/int_din_trikera_head_v.inc"
};
#endif

Gfx int_din_trikera_head_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_trikera_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_din_trikera_baceA_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_din_trikera_head_v, 8, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 3, 2, 6, 3, 6, 7, 0, 3, 7),
    gsSPNTriangles_5b(0, 7, 4, 7, 6, 5, 7, 5, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_din_trikera_headT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_trikera_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_trikera_poleA_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_din_trikera_head_v[8], 25, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 1, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 6, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_din_trikera_horn_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(9, 10, 11, 12, 12, 13, 10, 14, 15, 16),
    gsSPNTriangles_5b(16, 17, 14, 14, 18, 15, 19, 20, 21, 21, 22, 19),
    gsSPNTriangles_5b(20, 23, 21, 13, 24, 10, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_din_trikera_skull_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_din_trikera_head_v[33], 18, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 4, 2, 4, 0, 2),
    gsSPNTriangles_5b(5, 6, 7, 3, 5, 8, 5, 7, 8, 3, 9, 10),
    gsSPNTriangles_5b(0, 4, 11, 4, 10, 11, 4, 3, 10, 9, 8, 12),
    gsSPNTriangles_5b(9, 3, 8, 8, 7, 12, 10, 13, 14, 9, 15, 13),
    gsSPNTriangles_5b(12, 15, 9, 10, 14, 11, 9, 13, 10, 11, 16, 0),
    gsSPNTriangles_5b(7, 17, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_din_trikera_head_c(void) {
    pc_load_asset("assets/int_din_trikera_head/int_din_trikera_pal.bin", int_din_trikera_pal, 0x20, 0x91DEA0, 0, 1);
}
#endif
