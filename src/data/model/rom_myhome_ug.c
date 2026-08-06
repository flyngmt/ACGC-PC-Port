#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 rom_myhome_ug_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 rom_myhome_ug_pal[] = {
#include "assets/rom_myhome_ug_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_myhome_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_myhome_pal[] = {
#include "assets/rom_myhome_ug/rom_myhome_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 rom_myhome_ugf1_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 rom_myhome_ugf1_tex[] = {
#include "assets/rom_myhome_ugf1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_myhome_enter2_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_myhome_enter2_tex[] = {
#include "assets/rom_myhome_ug/rom_myhome_enter2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 rom_myhome_ugw1_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 rom_myhome_ugw1_tex[] = {
#include "assets/rom_myhome_ugw1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 rom_myhome_ugw2_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) u8 rom_myhome_ugw2_tex[] = {
#include "assets/rom_myhome_ugw2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx rom_myhome_ug_v[0x980 / sizeof(Vtx)];
#else
Vtx rom_myhome_ug_v[] = {
#include "assets/rom_myhome_ug_v.inc"
};
#endif

Gfx rom_myhome_ug_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_myhome_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_myhome_enter2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(rom_myhome_ug_v, 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 2, 0, 4, 1),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_myhome_ug_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_myhome_ugf1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_myhome_ug_v[5], 28, 0),
    gsSPNTrianglesInit_5b(35, 0, 1, 2, 3, 4, 0, 0, 4, 1),
    gsSPNTriangles_5b(4, 5, 1, 6, 7, 8, 9, 6, 8, 10, 6, 9),
    gsSPNTriangles_5b(9, 8, 11, 9, 11, 12, 10, 9, 12, 13, 5, 12),
    gsSPNTriangles_5b(13, 12, 2, 7, 14, 15, 15, 14, 16, 14, 17, 16),
    gsSPNTriangles_5b(15, 16, 18, 19, 20, 18, 19, 17, 20, 17, 21, 20),
    gsSPNTriangles_5b(21, 22, 20, 21, 23, 22, 17, 24, 21, 21, 24, 23),
    gsSPNTriangles_5b(24, 3, 23, 20, 22, 18, 22, 2, 18, 2, 11, 18),
    gsSPNTriangles_5b(2, 25, 11, 22, 3, 2, 22, 26, 3, 3, 0, 2),
    gsSPNTriangles_5b(7, 15, 18, 11, 27, 7, 11, 7, 18, 25, 5, 10),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_myhome_ugw1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_myhome_ug_v[33], 32, 0),
    gsSPNTrianglesInit_5b(38, 0, 1, 2, 0, 3, 1, 4, 5, 2),
    gsSPNTriangles_5b(4, 6, 5, 7, 8, 9, 7, 10, 8, 7, 11, 10),
    gsSPNTriangles_5b(7, 12, 11, 1, 8, 2, 8, 10, 2, 3, 9, 1),
    gsSPNTriangles_5b(9, 8, 1, 3, 13, 9, 12, 14, 6, 4, 12, 6),
    gsSPNTriangles_5b(4, 11, 12, 2, 11, 4, 2, 15, 11, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 19, 18, 20, 19, 20, 3, 20, 13, 3),
    gsSPNTriangles_5b(21, 22, 23, 23, 24, 25, 21, 23, 25, 24, 26, 16),
    gsSPNTriangles_5b(25, 24, 16, 27, 20, 18, 27, 18, 26, 27, 26, 24),
    gsSPNTriangles_5b(27, 24, 23, 19, 3, 0, 19, 0, 16, 28, 21, 25),
    gsSPNTriangles_5b(28, 25, 16, 5, 29, 30, 5, 6, 29, 0, 0, 0),
    gsSPVertex(&rom_myhome_ug_v[64], 15, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 4, 8, 7, 4, 9, 8, 10, 5, 2),
    gsSPNTriangles_5b(5, 7, 2, 11, 6, 10, 6, 5, 10, 11, 12, 6),
    gsSPNTriangles_5b(9, 13, 3, 0, 9, 3, 0, 8, 9, 2, 8, 0),
    gsSPNTriangles_5b(2, 14, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_myhome_ugw2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_myhome_ug_v[79], 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsSPNTriangles_5b(0, 5, 4, 6, 7, 8, 7, 4, 8, 7, 9, 4),
    gsSPNTriangles_5b(9, 10, 1, 10, 2, 1, 10, 11, 2, 12, 13, 7),
    gsSPNTriangles_5b(10, 14, 15, 16, 17, 18, 15, 14, 19, 16, 20, 21),
    gsSPNTriangles_5b(16, 21, 22, 23, 16, 22, 19, 23, 24, 19, 24, 25),
    gsSPNTriangles_5b(26, 19, 25, 27, 28, 24, 27, 24, 29, 27, 29, 22),
    gsSPNTriangles_5b(27, 22, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_myhome_ug_v[109], 15, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsSPNTriangles_5b(0, 5, 4, 6, 7, 8, 7, 4, 8, 7, 9, 4),
    gsSPNTriangles_5b(9, 10, 1, 10, 2, 1, 10, 11, 2, 12, 13, 7),
    gsSPNTriangles_5b(10, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_rom_myhome_ug_c(void) {
    pc_load_asset("assets/rom_myhome_ug/rom_myhome_pal.bin", rom_myhome_pal, 0x20, 0x59EDA0, 0, 1);
    pc_load_asset("assets/rom_myhome_ug/rom_myhome_enter2_tex.bin", rom_myhome_enter2_tex, 0x800, 0x59F5C0, 0, 0);
}
#endif
