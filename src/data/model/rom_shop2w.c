#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx rom_shop2w_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_conveni_ent_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_conveni_ent_pal[] = {
#include "assets/rom_shop2w/rom_conveni_ent_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_conveni_floor_E_pal[0x20 / sizeof(u16)];
#else
static u16 rom_conveni_floor_E_pal[] = {
#include "assets/rom_shop2w/rom_conveni_floor_E_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_conveni_cooler_pal[0x20 / sizeof(u16)];
#else
static u16 rom_conveni_cooler_pal[] = {
#include "assets/rom_shop2w/rom_conveni_cooler_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_conveni_tana_pal[0x20 / sizeof(u16)];
#else
static u16 rom_conveni_tana_pal[] = {
#include "assets/rom_shop2w/rom_conveni_tana_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_conveni_leji_pal[0x20 / sizeof(u16)];
#else
static u16 rom_conveni_leji_pal[] = {
#include "assets/rom_shop2w/rom_conveni_leji_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_conveni_mirror_rgb_ci4_pal[0x20 / sizeof(u16)];
#else
static u16 rom_conveni_mirror_rgb_ci4_pal[] = {
#include "assets/rom_shop2w/rom_conveni_mirror_rgb_ci4_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_conveni_ent[0x200];
#else
static u8 rom_conveni_ent[] = {
#include "assets/rom_shop2w/rom_conveni_ent.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_conveni_floor_F[0x400];
#else
u8 rom_conveni_floor_F[] = {
#include "assets/rom_conveni_floor_F.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_conveni_maruwaku[0x200];
#else
static u8 rom_conveni_maruwaku[] = {
#include "assets/rom_shop2w/rom_conveni_maruwaku.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_conveni_counter[0x200];
#else
static u8 rom_conveni_counter[] = {
#include "assets/rom_shop2w/rom_conveni_counter.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_conveni_bou[0x80];
#else
static u8 rom_conveni_bou[] = {
#include "assets/rom_shop2w/rom_conveni_bou.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_conveni_tana_bf2[0x80];
#else
static u8 rom_conveni_tana_bf2[] = {
#include "assets/rom_shop2w/rom_conveni_tana_bf2.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_conveni_floor_E[0x200];
#else
static u8 rom_conveni_floor_E[] = {
#include "assets/rom_shop2w/rom_conveni_floor_E.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_conveni_tana_f[0x80];
#else
static u8 rom_conveni_tana_f[] = {
#include "assets/rom_shop2w/rom_conveni_tana_f.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_convevi_kage1[0x100];
#else
static u8 rom_convevi_kage1[] = {
#include "assets/rom_shop2w/rom_convevi_kage1.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_conveni_leji_e[0x80];
#else
static u8 rom_conveni_leji_e[] = {
#include "assets/rom_shop2w/rom_conveni_leji_e.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_conveni_leji_k[0x80];
#else
static u8 rom_conveni_leji_k[] = {
#include "assets/rom_shop2w/rom_conveni_leji_k.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_conveni_leji_s[0x80];
#else
static u8 rom_conveni_leji_s[] = {
#include "assets/rom_shop2w/rom_conveni_leji_s.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_conveni_leji_t[0x80];
#else
static u8 rom_conveni_leji_t[] = {
#include "assets/rom_shop2w/rom_conveni_leji_t.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_conveni_wall_C[0x400];
#else
static u8 rom_conveni_wall_C[] = {
#include "assets/rom_shop2w/rom_conveni_wall_C.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_conveni_door[0x300];
#else
static u8 rom_conveni_door[] = {
#include "assets/rom_shop2w/rom_conveni_door.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_conveni_tana_bf[0x80];
#else
static u8 rom_conveni_tana_bf[] = {
#include "assets/rom_shop2w/rom_conveni_tana_bf.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_conveni_mirror_rgb_ci4[0x80];
#else
static u8 rom_conveni_mirror_rgb_ci4[] = {
#include "assets/rom_shop2w/rom_conveni_mirror_rgb_ci4.inc"
};
#endif

#ifdef TARGET_PC
Vtx rom_shop2w_v[0x1340 / sizeof(Vtx)];
#else
Vtx rom_shop2w_v[] = {
#include "assets/rom_shop2w_v.inc"
};
#endif

Gfx rom_shop2w_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 0, 0, 0, 65),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, rom_convevi_kage1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&rom_shop2w_v[160], 20, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 8, 11, 9, 9, 12, 10),
    gsSPNTriangles_5b(12, 13, 10, 14, 15, 16, 14, 17, 15, 15, 18, 16),
    gsSPNTriangles_5b(18, 19, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx rom_shop2w_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_conveni_tana_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_conveni_tana_bf),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&rom_shop2w_v[180], 24, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_conveni_tana_f),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop2w_v[204], 24, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 3, 1, 1, 4, 2),
    gsSPNTriangles_5b(4, 5, 2, 4, 6, 5, 6, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 9, 12, 11, 12, 13, 11, 12, 14, 13),
    gsSPNTriangles_5b(12, 15, 14, 16, 17, 18, 16, 19, 17, 17, 20, 18),
    gsSPNTriangles_5b(20, 21, 18, 20, 22, 21, 22, 23, 21, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_conveni_tana_bf2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop2w_v[228], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 9, 11, 10, 0, 0, 0),
    gsSPVertex(&rom_shop2w_v[240], 24, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 16, 19, 17, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_shop2w_v[264], 32, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(23, 20, 22, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 31, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_shop2w_v[296], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_conveni_cooler_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, rom_conveni_door),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop2w_v[300], 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_conveni_maruwaku),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 7, 4, 6, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(rom_shop2w_v, 19, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 3, 5),
    gsSPNTriangles_5b(3, 6, 7, 3, 7, 4, 7, 8, 4, 4, 0, 2),
    gsSPNTriangles_5b(0, 4, 9, 0, 9, 1, 4, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 13, 11, 13, 14, 11, 14, 12, 11, 15, 13, 10),
    gsSPNTriangles_5b(16, 13, 15, 17, 13, 18, 18, 13, 16, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop2w_v[19], 21, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 3, 4, 1, 3, 5, 4),
    gsSPNTriangles_5b(6, 7, 8, 6, 9, 7, 8, 7, 0, 2, 8, 0),
    gsSPNTriangles_5b(1, 0, 3, 10, 11, 12, 11, 13, 12, 14, 15, 16),
    gsSPNTriangles_5b(14, 17, 15, 17, 18, 15, 18, 19, 15, 18, 20, 19),
    gsSPNTriangles_5b(20, 11, 19, 20, 13, 11, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_conveni_cooler_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 128, rom_conveni_wall_C),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop2w_v[40], 25, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 3, 4, 5, 1, 3, 2),
    gsSPNTriangles_5b(3, 5, 2, 0, 2, 5, 5, 4, 6, 5, 6, 7),
    gsSPNTriangles_5b(6, 8, 7, 9, 7, 8, 9, 5, 7, 6, 4, 10),
    gsSPNTriangles_5b(4, 11, 10, 4, 12, 11, 4, 13, 12, 4, 3, 13),
    gsSPNTriangles_5b(3, 1, 14, 13, 3, 14, 15, 8, 6, 10, 15, 6),
    gsSPNTriangles_5b(16, 17, 18, 19, 17, 16, 20, 16, 18, 19, 16, 20),
    gsSPNTriangles_5b(20, 18, 21, 22, 23, 21, 23, 20, 21, 23, 24, 20),
    gsSPNTriangles_5b(24, 19, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_conveni_floor_E_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_conveni_floor_E),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop2w_v[65], 26, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 0, 2, 4, 5, 1),
    gsSPNTriangles_5b(5, 2, 1, 6, 7, 8, 3, 7, 9, 3, 2, 7),
    gsSPNTriangles_5b(6, 9, 7, 10, 6, 11, 6, 8, 11, 12, 10, 11),
    gsSPNTriangles_5b(0, 13, 14, 1, 0, 14, 1, 14, 4, 0, 3, 15),
    gsSPNTriangles_5b(0, 15, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, rom_conveni_floor_F),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(9, 16, 17, 18, 19, 20, 21, 19, 22, 20),
    gsSPNTriangles_5b(23, 24, 19, 24, 22, 19, 24, 25, 22, 23, 16, 24),
    gsSPNTriangles_5b(18, 25, 24, 16, 18, 24, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_conveni_ent_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_conveni_counter),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop2w_v[91], 19, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 0, 5),
    gsSPNTriangles_5b(4, 1, 0, 6, 7, 8, 7, 9, 8, 10, 11, 12),
    gsSPNTriangles_5b(11, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_conveni_ent),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 14, 15, 16, 17, 18, 14, 14, 16, 17),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_conveni_leji_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_conveni_leji_t),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop2w_v[110], 24, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 7, 5, 8, 9, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_conveni_leji_s),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 10, 13, 11, 12, 14, 15),
    gsSPNTriangles_5b(12, 11, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_conveni_leji_k),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 19, 16, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_conveni_leji_e),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 21, 23, 22, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_conveni_cooler_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_conveni_bou),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop2w_v[134], 7, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 0, 4, 5),
    gsSPNTriangles_5b(0, 5, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPTexture(700, 1650, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_conveni_mirror_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_conveni_mirror_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 14, 15),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                         G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&rom_shop2w_v[141], 19, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(4, 5, 3, 5, 6, 3, 6, 2, 3, 0, 7, 1),
    gsSPNTriangles_5b(0, 8, 7, 7, 4, 1, 9, 10, 11, 9, 12, 10),
    gsSPNTriangles_5b(10, 4, 11, 12, 13, 10, 12, 14, 13, 13, 4, 10),
    gsSPNTriangles_5b(14, 15, 13, 14, 16, 15, 15, 4, 13, 16, 17, 15),
    gsSPNTriangles_5b(16, 18, 17, 17, 4, 15, 18, 5, 17, 18, 6, 5),
    gsSPNTriangles_5b(5, 4, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_rom_shop2w_c(void) {
    pc_load_asset("assets/rom_shop2w/rom_conveni_ent_pal.bin", rom_conveni_ent_pal, 0x20, 0xC2CBC0, 0, 1);
    pc_load_asset("assets/rom_shop2w/rom_conveni_floor_E_pal.bin", rom_conveni_floor_E_pal, 0x20, 0xC2CC40, 0, 1);
    pc_load_asset("assets/rom_shop2w/rom_conveni_cooler_pal.bin", rom_conveni_cooler_pal, 0x20, 0xC2CBE0, 0, 1);
    pc_load_asset("assets/rom_shop2w/rom_conveni_tana_pal.bin", rom_conveni_tana_pal, 0x20, 0xC2CC20, 0, 1);
    pc_load_asset("assets/rom_shop2w/rom_conveni_leji_pal.bin", rom_conveni_leji_pal, 0x20, 0xC2CC60, 0, 1);
    pc_load_asset("assets/rom_shop2w/rom_conveni_mirror_rgb_ci4_pal.bin", rom_conveni_mirror_rgb_ci4_pal, 0x20, 0xC2CC80, 0, 1);
    pc_load_asset("assets/rom_shop2w/rom_conveni_ent.bin", rom_conveni_ent, 0x200, 0xC2CCA0, 0, 0);
    pc_load_asset("assets/rom_shop2w/rom_conveni_maruwaku.bin", rom_conveni_maruwaku, 0x200, 0xC2CEA0, 0, 0);
    pc_load_asset("assets/rom_shop2w/rom_conveni_counter.bin", rom_conveni_counter, 0x200, 0xC2D8A0, 0, 0);
    pc_load_asset("assets/rom_shop2w/rom_conveni_bou.bin", rom_conveni_bou, 0x80, 0xC2DAA0, 0, 0);
    pc_load_asset("assets/rom_shop2w/rom_conveni_tana_bf2.bin", rom_conveni_tana_bf2, 0x80, 0xC2DB20, 0, 0);
    pc_load_asset("assets/rom_shop2w/rom_conveni_floor_E.bin", rom_conveni_floor_E, 0x200, 0xC2DBA0, 0, 0);
    pc_load_asset("assets/rom_shop2w/rom_conveni_tana_f.bin", rom_conveni_tana_f, 0x80, 0xC2DDA0, 0, 0);
    pc_load_asset("assets/rom_shop2w/rom_convevi_kage1.bin", rom_convevi_kage1, 0x100, 0xC2DE20, 0, 0);
    pc_load_asset("assets/rom_shop2w/rom_conveni_leji_e.bin", rom_conveni_leji_e, 0x80, 0xC2DF20, 0, 0);
    pc_load_asset("assets/rom_shop2w/rom_conveni_leji_k.bin", rom_conveni_leji_k, 0x80, 0xC2DFA0, 0, 0);
    pc_load_asset("assets/rom_shop2w/rom_conveni_leji_s.bin", rom_conveni_leji_s, 0x80, 0xC2E020, 0, 0);
    pc_load_asset("assets/rom_shop2w/rom_conveni_leji_t.bin", rom_conveni_leji_t, 0x80, 0xC2E0A0, 0, 0);
    pc_load_asset("assets/rom_shop2w/rom_conveni_wall_C.bin", rom_conveni_wall_C, 0x400, 0xC2E120, 0, 0);
    pc_load_asset("assets/rom_shop2w/rom_conveni_door.bin", rom_conveni_door, 0x300, 0xC2E520, 0, 0);
    pc_load_asset("assets/rom_shop2w/rom_conveni_tana_bf.bin", rom_conveni_tana_bf, 0x80, 0xC2E820, 0, 0);
    pc_load_asset("assets/rom_shop2w/rom_conveni_mirror_rgb_ci4.bin", rom_conveni_mirror_rgb_ci4, 0x80, 0xC2AE60, 0, 0);
}
#endif
