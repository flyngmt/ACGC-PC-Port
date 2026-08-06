#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx rom_shop3_fuku_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop3_ent_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop3_ent_pal[] = {
#include "assets/rom_shop3_fuku/rom_shop3_ent_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_shop_kouhaku_pal[0x20 / sizeof(u16)];
#else
static u16 rom_shop_kouhaku_pal[] = {
#include "assets/rom_shop3_fuku/rom_shop_kouhaku_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_shop3_tana_pal[0x20 / sizeof(u16)];
#else
static u16 rom_shop3_tana_pal[] = {
#include "assets/rom_shop3_fuku/rom_shop3_tana_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_shop3_leji_pal[0x20 / sizeof(u16)];
#else
static u16 rom_shop3_leji_pal[] = {
#include "assets/rom_shop3_fuku/rom_shop3_leji_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_shop3_desk_pal[0x20 / sizeof(u16)];
#else
static u16 rom_shop3_desk_pal[] = {
#include "assets/rom_shop3_fuku/rom_shop3_desk_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_shop3_bini_pal[0x20 / sizeof(u16)];
#else
static u16 rom_shop3_bini_pal[] = {
#include "assets/rom_shop3_fuku/rom_shop3_bini_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_shop3_mat_pal[0x20 / sizeof(u16)];
#else
static u16 rom_shop3_mat_pal[] = {
#include "assets/rom_shop3_fuku/rom_shop3_mat_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_shop3_wallC_pal[0x20 / sizeof(u16)];
#else
static u16 rom_shop3_wallC_pal[] = {
#include "assets/rom_shop3_fuku/rom_shop3_wallC_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_ent[0x200];
#else
static u8 rom_shop3_ent[] = {
#include "assets/rom_shop3_fuku/rom_shop3_ent.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop_kouhaku_tex[0x800];
#else
static u8 rom_shop_kouhaku_tex[] = {
#include "assets/rom_shop3_fuku/rom_shop_kouhaku_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop3_tana2[0x100];
#else
u8 rom_shop3_tana2[] = {
#include "assets/rom_shop3_tana2.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_kago_b[0x100];
#else
static u8 rom_shop3_kago_b[] = {
#include "assets/rom_shop3_fuku/rom_shop3_kago_b.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_leji_f[0x80];
#else
static u8 rom_shop3_leji_f[] = {
#include "assets/rom_shop3_fuku/rom_shop3_leji_f.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_leji_k[0x80];
#else
static u8 rom_shop3_leji_k[] = {
#include "assets/rom_shop3_fuku/rom_shop3_leji_k.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_leji_b[0x80];
#else
static u8 rom_shop3_leji_b[] = {
#include "assets/rom_shop3_fuku/rom_shop3_leji_b.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_desk_a[0x200];
#else
static u8 rom_shop3_desk_a[] = {
#include "assets/rom_shop3_fuku/rom_shop3_desk_a.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_desk_b[0x80];
#else
static u8 rom_shop3_desk_b[] = {
#include "assets/rom_shop3_fuku/rom_shop3_desk_b.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_desk_c[0x200];
#else
static u8 rom_shop3_desk_c[] = {
#include "assets/rom_shop3_fuku/rom_shop3_desk_c.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_tana_t[0x80];
#else
static u8 rom_shop3_tana_t[] = {
#include "assets/rom_shop3_fuku/rom_shop3_tana_t.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_bini[0x80];
#else
static u8 rom_shop3_bini[] = {
#include "assets/rom_shop3_fuku/rom_shop3_bini.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_bini_b[0x80];
#else
static u8 rom_shop3_bini_b[] = {
#include "assets/rom_shop3_fuku/rom_shop3_bini_b.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_car[0x100];
#else
static u8 rom_shop3_car[] = {
#include "assets/rom_shop3_fuku/rom_shop3_car.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_bini_a[0x80];
#else
static u8 rom_shop3_bini_a[] = {
#include "assets/rom_shop3_fuku/rom_shop3_bini_a.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_wallC[0x800];
#else
static u8 rom_shop3_wallC[] = {
#include "assets/rom_shop3_fuku/rom_shop3_wallC.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_wallD[0x800];
#else
static u8 rom_shop3_wallD[] = {
#include "assets/rom_shop3_fuku/rom_shop3_wallD.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_floorE[0x200];
#else
static u8 rom_shop3_floorE[] = {
#include "assets/rom_shop3_fuku/rom_shop3_floorE.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_kage1[0x80];
#else
static u8 rom_shop3_kage1[] = {
#include "assets/rom_shop3_fuku/rom_shop3_kage1.inc"
};
#endif

#ifdef TARGET_PC
Vtx rom_shop3_fuku_v[0x2030 / sizeof(Vtx)];
#else
Vtx rom_shop3_fuku_v[] = {
#include "assets/rom_shop3_fuku_v.inc"
};
#endif

Gfx rom_shop3_fuku_modelT[] = {
    gsSPEndDisplayList(),
};

Gfx rom_shop3_fuku_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop_kouhaku_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop_kouhaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&rom_shop3_fuku_v[248], 28, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 2, 3, 2, 4, 3),
    gsSPNTriangles_5b(4, 5, 3, 6, 5, 4, 7, 6, 4, 7, 8, 6),
    gsSPNTriangles_5b(7, 9, 8, 10, 11, 12, 10, 12, 13, 10, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 14, 15, 16, 17, 14, 16, 18, 17, 16),
    gsSPNTriangles_5b(18, 19, 17, 20, 21, 22, 23, 20, 22, 23, 24, 20),
    gsSPNTriangles_5b(23, 25, 24, 24, 25, 26, 24, 26, 27, 26, 8, 27),
    gsSPNTriangles_5b(8, 9, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop_kouhaku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop3_fuku_v[276], 9, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 3, 1, 4, 2, 1),
    gsSPNTriangles_5b(2, 5, 6, 2, 4, 5, 7, 8, 0, 8, 3, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_tana_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, rom_shop3_kago_b),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop3_fuku_v[285], 24, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_shop3_fuku_v[309], 24, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsSPVertex(&rom_shop3_fuku_v[333], 28, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 26, 27, 0, 0, 0),
    gsSPVertex(&rom_shop3_fuku_v[361], 28, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_shop3_fuku_v[389], 24, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsSPVertex(&rom_shop3_fuku_v[413], 28, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 26, 27, 0, 0, 0),
    gsSPVertex(&rom_shop3_fuku_v[441], 24, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_bini_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_shop3_bini_a),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop3_fuku_v[465], 28, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_mat_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, rom_shop3_car),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 11, 9, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 12, 15, 13, 16, 17, 18),
    gsSPNTriangles_5b(16, 19, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 23, 21, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 25, 27, 26, 0, 0, 0),
    gsSPVertex(&rom_shop3_fuku_v[493], 22, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 9, 11, 10, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_bini_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_shop3_bini_b),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(19, 21, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_wallC_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop3_wallD),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(rom_shop3_fuku_v, 25, 0),
    gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 0, 2, 3, 2, 4),
    gsSPNTriangles_5b(5, 6, 4, 5, 4, 2, 7, 6, 5, 8, 7, 5),
    gsSPNTriangles_5b(9, 10, 11, 9, 12, 10, 13, 14, 9, 14, 12, 9),
    gsSPNTriangles_5b(14, 13, 15, 13, 16, 15, 13, 17, 16, 18, 19, 20),
    gsSPNTriangles_5b(18, 20, 21, 22, 18, 21, 22, 23, 24, 18, 22, 24),
    gsSPNTriangles_5b(24, 23, 7, 24, 7, 8, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop3_wallC),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop3_fuku_v[25], 25, 0),
    gsSPNTrianglesInit_5b(27, 0, 1, 2, 3, 2, 1, 4, 3, 1),
    gsSPNTriangles_5b(0, 4, 1, 5, 6, 7, 4, 5, 7, 7, 6, 8),
    gsSPNTriangles_5b(9, 10, 11, 10, 12, 11, 10, 13, 12, 10, 9, 13),
    gsSPNTriangles_5b(14, 15, 16, 14, 16, 17, 14, 17, 18, 15, 14, 18),
    gsSPNTriangles_5b(4, 7, 8, 4, 8, 3, 13, 19, 12, 19, 20, 12),
    gsSPNTriangles_5b(19, 21, 20, 20, 22, 12, 20, 21, 22, 23, 6, 5),
    gsSPNTriangles_5b(23, 5, 17, 24, 6, 23, 24, 23, 17, 16, 24, 17),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_ent_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_shop3_floorE),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop3_fuku_v[50], 32, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 10, 13, 14, 15, 16, 17, 8, 18),
    gsSPNTriangles_5b(19, 20, 21, 20, 22, 21, 0, 23, 10, 16, 24, 13),
    gsSPNTriangles_5b(13, 17, 16, 25, 18, 26, 14, 27, 15, 17, 5, 28),
    gsSPNTriangles_5b(10, 29, 30, 31, 17, 13, 16, 17, 28, 28, 19, 16),
    gsSPVertex(&rom_shop3_fuku_v[82], 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(1, 9, 2, 10, 11, 12, 6, 13, 14, 10, 15, 16),
    gsSPNTriangles_5b(10, 16, 0, 6, 14, 7, 17, 15, 12, 18, 19, 20),
    gsSPNTriangles_5b(21, 4, 22, 13, 4, 14, 3, 23, 22, 4, 3, 22),
    gsSPNTriangles_5b(24, 25, 11, 26, 27, 28, 26, 12, 27, 11, 25, 12),
    gsSPNTriangles_5b(29, 5, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_shop3_fuku_v[113], 20, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 6, 3, 5),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 11, 6, 12, 12, 13, 14),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_shop3_ent),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 15, 16, 17, 17, 18, 15, 15, 19, 16),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_tana_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_shop3_tana_t),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop3_fuku_v[133], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, rom_shop3_tana2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop3_fuku_v[141], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 16, 19, 17, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 23, 24, 21, 23, 25, 24, 9, 8, 26),
    gsSPNTriangles_5b(8, 27, 26, 28, 24, 29, 24, 30, 29, 0, 0, 0),
    gsSPVertex(&rom_shop3_fuku_v[172], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_desk_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_shop3_desk_c),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop3_fuku_v[184], 28, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 0, 5, 2, 7, 8, 9, 2, 8, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_shop3_desk_b),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 10, 11, 12, 11, 13, 12, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_shop3_desk_a),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(6, 14, 15, 16, 15, 17, 16, 18, 16, 19),
    gsSPNTriangles_5b(16, 17, 19, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_leji_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_shop3_leji_b),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 26, 27, 0, 0, 0),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_bini_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_shop3_bini),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop3_fuku_v[222], 26, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 1, 4, 2, 5),
    gsSPNTriangles_5b(4, 0, 2, 6, 7, 8, 6, 9, 7, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_leji_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_shop3_leji_k),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 10, 11, 12, 11, 13, 12, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_shop3_leji_f),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12, 14, 15, 16, 14, 17, 15, 18, 19, 20),
    gsSPNTriangles_5b(18, 21, 19, 22, 17, 23, 22, 15, 17, 22, 20, 24),
    gsSPNTriangles_5b(20, 19, 24, 14, 16, 25, 16, 24, 25, 15, 22, 16),
    gsSPNTriangles_5b(22, 24, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 20, 0, 50, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, rom_shop3_kage1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop3_fuku_v[212], 10, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 2, 3, 4),
    gsSPNTriangles_5b(3, 5, 4, 6, 7, 8, 9, 6, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_rom_shop3_fuku_c(void) {
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_ent_pal.bin", rom_shop3_ent_pal, 0x20, 0xC470A0, 0, 1);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop_kouhaku_pal.bin", rom_shop_kouhaku_pal, 0x20, 0xC4F520, 0, 1);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_tana_pal.bin", rom_shop3_tana_pal, 0x20, 0xC470E0, 0, 1);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_leji_pal.bin", rom_shop3_leji_pal, 0x20, 0xC47100, 0, 1);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_desk_pal.bin", rom_shop3_desk_pal, 0x20, 0xC47120, 0, 1);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_bini_pal.bin", rom_shop3_bini_pal, 0x20, 0xC47140, 0, 1);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_mat_pal.bin", rom_shop3_mat_pal, 0x20, 0xC47160, 0, 1);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_wallC_pal.bin", rom_shop3_wallC_pal, 0x20, 0xC47180, 0, 1);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_ent.bin", rom_shop3_ent, 0x200, 0xC471A0, 0, 0);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop_kouhaku_tex.bin", rom_shop_kouhaku_tex, 0x800, 0xC53740, 0, 0);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_kago_b.bin", rom_shop3_kago_b, 0x100, 0xC47CA0, 0, 0);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_leji_f.bin", rom_shop3_leji_f, 0x80, 0xC47DA0, 0, 0);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_leji_k.bin", rom_shop3_leji_k, 0x80, 0xC47E20, 0, 0);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_leji_b.bin", rom_shop3_leji_b, 0x80, 0xC47EA0, 0, 0);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_desk_a.bin", rom_shop3_desk_a, 0x200, 0xC47F20, 0, 0);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_desk_b.bin", rom_shop3_desk_b, 0x80, 0xC48120, 0, 0);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_desk_c.bin", rom_shop3_desk_c, 0x200, 0xC481A0, 0, 0);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_tana_t.bin", rom_shop3_tana_t, 0x80, 0xC483A0, 0, 0);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_bini.bin", rom_shop3_bini, 0x80, 0xC48420, 0, 0);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_bini_b.bin", rom_shop3_bini_b, 0x80, 0xC484A0, 0, 0);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_car.bin", rom_shop3_car, 0x100, 0xC48520, 0, 0);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_bini_a.bin", rom_shop3_bini_a, 0x80, 0xC48620, 0, 0);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_wallC.bin", rom_shop3_wallC, 0x800, 0xC486A0, 0, 0);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_wallD.bin", rom_shop3_wallD, 0x800, 0xC48EA0, 0, 0);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_floorE.bin", rom_shop3_floorE, 0x200, 0xC496A0, 0, 0);
    pc_load_asset("assets/rom_shop3_fuku/rom_shop3_kage1.bin", rom_shop3_kage1, 0x80, 0xC498A0, 0, 0);
}
#endif
