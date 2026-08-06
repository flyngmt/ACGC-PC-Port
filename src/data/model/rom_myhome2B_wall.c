#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_myhome_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_myhome_pal[] = {
#include "assets/rom_myhome2B_wall/rom_myhome_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_myhome_window_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_myhome_window_tex[] = {
#include "assets/rom_myhome2B_wall/rom_myhome_window_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_myhome_enter2_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_myhome_enter2_tex[] = {
#include "assets/rom_myhome2B_wall/rom_myhome_enter2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx rom_myhome2B_wall_v[0x5B0 / sizeof(Vtx)];
#else
Vtx rom_myhome2B_wall_v[] = {
#include "assets/rom_myhome2B_wall_v.inc"
};
#endif

Gfx rom_myhome2B_wall_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_myhome_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_myhome_window_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_myhome2B_wall_v[83], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_myhome_enter2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(rom_myhome2B_wall_v, 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_myhome2B_wall_v[5], 27, 0),
    gsSPNTrianglesInit_5b(31, 0, 1, 2, 3, 4, 5, 3, 0, 4),
    gsSPNTriangles_5b(0, 2, 4, 2, 5, 4, 0, 6, 1, 6, 7, 1),
    gsSPNTriangles_5b(0, 8, 6, 8, 7, 6, 9, 10, 11, 12, 9, 11),
    gsSPNTriangles_5b(11, 10, 13, 12, 11, 13, 14, 7, 15, 12, 14, 15),
    gsSPNTriangles_5b(8, 12, 15, 8, 15, 7, 12, 16, 14, 12, 17, 16),
    gsSPNTriangles_5b(12, 13, 17, 18, 19, 20, 18, 20, 21, 18, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 18, 24, 18, 22, 24, 22, 25, 24),
    gsSPNTriangles_5b(18, 26, 19, 26, 5, 19, 18, 3, 26, 3, 5, 26),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_myhome2B_wall_v[32], 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 3, 2, 1, 1, 0, 4),
    gsSPNTriangles_5b(3, 5, 6, 3, 6, 7, 3, 7, 2, 3, 8, 5),
    gsSPNTriangles_5b(9, 4, 10, 4, 0, 11, 4, 11, 12, 4, 12, 10),
    gsSPNTriangles_5b(13, 14, 15, 14, 16, 15, 17, 18, 19, 18, 20, 19),
    gsSPNTriangles_5b(19, 21, 15, 13, 15, 21, 19, 20, 21, 22, 4, 9),
    gsSPNTriangles_5b(23, 22, 9, 18, 17, 8, 3, 18, 8, 24, 25, 26),
    gsSPNTriangles_5b(25, 27, 26, 24, 26, 28, 24, 28, 29, 24, 29, 30),
    gsSPNTriangles_5b(24, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_myhome2B_wall_v[64], 11, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 3, 2, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 7, 3, 8, 7, 8, 9, 7, 9, 10),
    gsSPNTriangles_5b(6, 7, 10, 2, 3, 7, 0, 0, 0, 0, 0, 0),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPVertex(&rom_myhome2B_wall_v[75], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rom_myhome2B_wall_new_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_myhome_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_myhome_window_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_myhome2B_wall_v[83], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_myhome_enter2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(rom_myhome2B_wall_v, 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_myhome2B_wall_v[5], 27, 0),
    gsSPNTrianglesInit_5b(31, 0, 1, 2, 3, 4, 5, 3, 0, 4),
    gsSPNTriangles_5b(0, 2, 4, 2, 5, 4, 0, 6, 1, 6, 7, 1),
    gsSPNTriangles_5b(0, 8, 6, 8, 7, 6, 9, 10, 11, 12, 9, 11),
    gsSPNTriangles_5b(11, 10, 13, 12, 11, 13, 14, 7, 15, 12, 14, 15),
    gsSPNTriangles_5b(8, 12, 15, 8, 15, 7, 12, 16, 14, 12, 17, 16),
    gsSPNTriangles_5b(12, 13, 17, 18, 19, 20, 18, 20, 21, 18, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 18, 24, 18, 22, 24, 22, 25, 24),
    gsSPNTriangles_5b(18, 26, 19, 26, 5, 19, 18, 3, 26, 3, 5, 26),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_myhome2B_wall_v[32], 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 3, 2, 1, 1, 0, 4),
    gsSPNTriangles_5b(3, 5, 6, 3, 6, 7, 3, 7, 2, 3, 8, 5),
    gsSPNTriangles_5b(9, 4, 10, 4, 0, 11, 4, 11, 12, 4, 12, 10),
    gsSPNTriangles_5b(13, 14, 15, 14, 16, 15, 17, 18, 19, 18, 20, 19),
    gsSPNTriangles_5b(19, 21, 15, 13, 15, 21, 19, 20, 21, 22, 4, 9),
    gsSPNTriangles_5b(23, 22, 9, 18, 17, 8, 3, 18, 8, 24, 25, 26),
    gsSPNTriangles_5b(25, 27, 26, 24, 26, 28, 24, 28, 29, 24, 29, 30),
    gsSPNTriangles_5b(24, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_myhome2B_wall_v[64], 11, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 3, 2, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 7, 3, 8, 7, 8, 9, 7, 9, 10),
    gsSPNTriangles_5b(6, 7, 10, 2, 3, 7, 0, 0, 0, 0, 0, 0),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPVertex(&rom_myhome2B_wall_v[75], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rom_myhome2B_wall_new2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_myhome_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_myhome_window_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_myhome2B_wall_v[83], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_myhome_enter2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(rom_myhome2B_wall_v, 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_myhome2B_wall_v[5], 27, 0),
    gsSPNTrianglesInit_5b(31, 0, 1, 2, 3, 4, 5, 3, 0, 4),
    gsSPNTriangles_5b(0, 2, 4, 2, 5, 4, 0, 6, 1, 6, 7, 1),
    gsSPNTriangles_5b(0, 8, 6, 8, 7, 6, 9, 10, 11, 12, 9, 11),
    gsSPNTriangles_5b(11, 10, 13, 12, 11, 13, 14, 7, 15, 12, 14, 15),
    gsSPNTriangles_5b(8, 12, 15, 8, 15, 7, 12, 16, 14, 12, 17, 16),
    gsSPNTriangles_5b(12, 13, 17, 18, 19, 20, 18, 20, 21, 18, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 18, 24, 18, 22, 24, 22, 25, 24),
    gsSPNTriangles_5b(18, 26, 19, 26, 5, 19, 18, 3, 26, 3, 5, 26),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_myhome2B_wall_v[32], 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 3, 2, 1, 1, 0, 4),
    gsSPNTriangles_5b(3, 5, 6, 3, 6, 7, 3, 7, 2, 3, 8, 5),
    gsSPNTriangles_5b(9, 4, 10, 4, 0, 11, 4, 11, 12, 4, 12, 10),
    gsSPNTriangles_5b(13, 14, 15, 14, 16, 15, 17, 18, 19, 18, 20, 19),
    gsSPNTriangles_5b(19, 21, 15, 13, 15, 21, 19, 20, 21, 22, 4, 9),
    gsSPNTriangles_5b(23, 22, 9, 18, 17, 8, 3, 18, 8, 24, 25, 26),
    gsSPNTriangles_5b(25, 27, 26, 24, 26, 28, 24, 28, 29, 24, 29, 30),
    gsSPNTriangles_5b(24, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_myhome2B_wall_v[64], 11, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 3, 2, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 7, 3, 8, 7, 8, 9, 7, 9, 10),
    gsSPNTriangles_5b(6, 7, 10, 2, 3, 7, 0, 0, 0, 0, 0, 0),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPVertex(&rom_myhome2B_wall_v[75], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_rom_myhome2B_wall_c(void) {
    pc_load_asset("assets/rom_myhome2B_wall/rom_myhome_pal.bin", rom_myhome_pal, 0x20, 0x594E40, 0, 1);
    pc_load_asset("assets/rom_myhome2B_wall/rom_myhome_window_tex.bin", rom_myhome_window_tex, 0x200, 0x594E60, 0, 0);
    pc_load_asset("assets/rom_myhome2B_wall/rom_myhome_enter2_tex.bin", rom_myhome_enter2_tex, 0x800, 0x595060, 0, 0);
}
#endif
