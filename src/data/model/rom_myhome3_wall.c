#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_myhome_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_myhome_pal[] = {
#include "assets/rom_myhome3_wall/rom_myhome_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_myhome_window_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_myhome_window_tex[] = {
#include "assets/rom_myhome3_wall/rom_myhome_window_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_myhome_enter2_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_myhome_enter2_tex[] = {
#include "assets/rom_myhome3_wall/rom_myhome_enter2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx rom_myhome3_wall_v[0x4F0 / sizeof(Vtx)];
#else
Vtx rom_myhome3_wall_v[] = {
#include "assets/rom_myhome3_wall_v.inc"
};
#endif

Gfx rom_myhome3_wall_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_myhome_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_myhome_window_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_myhome3_wall_v[71], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_myhome_enter2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(rom_myhome3_wall_v, 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_myhome3_wall_v[5], 27, 0),
    gsSPNTrianglesInit_5b(31, 0, 1, 2, 3, 4, 5, 3, 6, 4),
    gsSPNTriangles_5b(6, 7, 4, 7, 5, 4, 6, 8, 7, 9, 10, 11),
    gsSPNTriangles_5b(9, 0, 10, 0, 2, 10, 2, 11, 10, 12, 13, 6),
    gsSPNTriangles_5b(12, 14, 13, 14, 15, 13, 15, 6, 13, 15, 16, 6),
    gsSPNTriangles_5b(0, 17, 1, 17, 5, 1, 0, 3, 17, 3, 5, 17),
    gsSPNTriangles_5b(8, 6, 16, 18, 19, 20, 21, 20, 19, 11, 21, 22),
    gsSPNTriangles_5b(21, 19, 22, 9, 22, 19, 9, 11, 22, 19, 18, 23),
    gsSPNTriangles_5b(19, 23, 24, 23, 25, 24, 26, 24, 25, 26, 19, 24),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_myhome3_wall_v[32], 31, 0),
    gsSPNTrianglesInit_5b(29, 0, 1, 2, 3, 2, 1, 2, 3, 4),
    gsSPNTriangles_5b(0, 5, 6, 5, 7, 6, 8, 9, 10, 9, 11, 10),
    gsSPNTriangles_5b(4, 12, 13, 12, 14, 13, 7, 5, 15, 5, 16, 15),
    gsSPNTriangles_5b(15, 17, 10, 18, 1, 6, 1, 0, 6, 8, 10, 17),
    gsSPNTriangles_5b(19, 12, 3, 12, 4, 3, 15, 16, 17, 20, 21, 22),
    gsSPNTriangles_5b(23, 20, 22, 24, 25, 26, 27, 24, 26, 20, 11, 9),
    gsSPNTriangles_5b(21, 20, 9, 28, 29, 26, 30, 22, 21, 22, 30, 24),
    gsSPNTriangles_5b(25, 24, 30, 25, 28, 26, 0, 0, 0, 0, 0, 0),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPVertex(&rom_myhome3_wall_v[63], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rom_myhome3_wall_new_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_myhome_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_myhome_window_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_myhome3_wall_v[71], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_myhome_enter2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(rom_myhome3_wall_v, 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_myhome3_wall_v[5], 27, 0),
    gsSPNTrianglesInit_5b(31, 0, 1, 2, 3, 4, 5, 3, 6, 4),
    gsSPNTriangles_5b(6, 7, 4, 7, 5, 4, 6, 8, 7, 9, 10, 11),
    gsSPNTriangles_5b(9, 0, 10, 0, 2, 10, 2, 11, 10, 12, 13, 6),
    gsSPNTriangles_5b(12, 14, 13, 14, 15, 13, 15, 6, 13, 15, 16, 6),
    gsSPNTriangles_5b(0, 17, 1, 17, 5, 1, 0, 3, 17, 3, 5, 17),
    gsSPNTriangles_5b(8, 6, 16, 18, 19, 20, 21, 20, 19, 11, 21, 22),
    gsSPNTriangles_5b(21, 19, 22, 9, 22, 19, 9, 11, 22, 19, 18, 23),
    gsSPNTriangles_5b(19, 23, 24, 23, 25, 24, 26, 24, 25, 26, 19, 24),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_myhome3_wall_v[32], 31, 0),
    gsSPNTrianglesInit_5b(29, 0, 1, 2, 3, 2, 1, 2, 3, 4),
    gsSPNTriangles_5b(0, 5, 6, 5, 7, 6, 8, 9, 10, 9, 11, 10),
    gsSPNTriangles_5b(4, 12, 13, 12, 14, 13, 7, 5, 15, 5, 16, 15),
    gsSPNTriangles_5b(15, 17, 10, 18, 1, 6, 1, 0, 6, 8, 10, 17),
    gsSPNTriangles_5b(19, 12, 3, 12, 4, 3, 15, 16, 17, 20, 21, 22),
    gsSPNTriangles_5b(23, 20, 22, 24, 25, 26, 27, 24, 26, 20, 11, 9),
    gsSPNTriangles_5b(21, 20, 9, 28, 29, 26, 30, 22, 21, 22, 30, 24),
    gsSPNTriangles_5b(25, 24, 30, 25, 28, 26, 0, 0, 0, 0, 0, 0),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPVertex(&rom_myhome3_wall_v[63], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rom_myhome3_wall_new2_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_myhome_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_myhome_window_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_myhome3_wall_v[71], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_myhome_enter2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(rom_myhome3_wall_v, 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_myhome3_wall_v[5], 27, 0),
    gsSPNTrianglesInit_5b(31, 0, 1, 2, 3, 4, 5, 3, 6, 4),
    gsSPNTriangles_5b(6, 7, 4, 7, 5, 4, 6, 8, 7, 9, 10, 11),
    gsSPNTriangles_5b(9, 0, 10, 0, 2, 10, 2, 11, 10, 12, 13, 6),
    gsSPNTriangles_5b(12, 14, 13, 14, 15, 13, 15, 6, 13, 15, 16, 6),
    gsSPNTriangles_5b(0, 17, 1, 17, 5, 1, 0, 3, 17, 3, 5, 17),
    gsSPNTriangles_5b(8, 6, 16, 18, 19, 20, 21, 20, 19, 11, 21, 22),
    gsSPNTriangles_5b(21, 19, 22, 9, 22, 19, 9, 11, 22, 19, 18, 23),
    gsSPNTriangles_5b(19, 23, 24, 23, 25, 24, 26, 24, 25, 26, 19, 24),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_myhome3_wall_v[32], 31, 0),
    gsSPNTrianglesInit_5b(29, 0, 1, 2, 3, 2, 1, 2, 3, 4),
    gsSPNTriangles_5b(0, 5, 6, 5, 7, 6, 8, 9, 10, 9, 11, 10),
    gsSPNTriangles_5b(4, 12, 13, 12, 14, 13, 7, 5, 15, 5, 16, 15),
    gsSPNTriangles_5b(15, 17, 10, 18, 1, 6, 1, 0, 6, 8, 10, 17),
    gsSPNTriangles_5b(19, 12, 3, 12, 4, 3, 15, 16, 17, 20, 21, 22),
    gsSPNTriangles_5b(23, 20, 22, 24, 25, 26, 27, 24, 26, 20, 11, 9),
    gsSPNTriangles_5b(21, 20, 9, 28, 29, 26, 30, 22, 21, 22, 30, 24),
    gsSPNTriangles_5b(25, 24, 30, 25, 28, 26, 0, 0, 0, 0, 0, 0),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPVertex(&rom_myhome3_wall_v[63], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_rom_myhome3_wall_c(void) {
    pc_load_asset("assets/rom_myhome3_wall/rom_myhome_pal.bin", rom_myhome_pal, 0x20, 0x594E40, 0, 1);
    pc_load_asset("assets/rom_myhome3_wall/rom_myhome_window_tex.bin", rom_myhome_window_tex, 0x200, 0x594E60, 0, 0);
    pc_load_asset("assets/rom_myhome3_wall/rom_myhome_enter2_tex.bin", rom_myhome_enter2_tex, 0x800, 0x595060, 0, 0);
}
#endif
