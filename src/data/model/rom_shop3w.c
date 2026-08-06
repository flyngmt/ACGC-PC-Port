#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx rom_shop3w_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop3_ent_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop3_ent_pal[] = {
#include "assets/rom_shop3w/rom_shop3_ent_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_shop3_tana_pal[0x20 / sizeof(u16)];
#else
static u16 rom_shop3_tana_pal[] = {
#include "assets/rom_shop3w/rom_shop3_tana_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_shop3_leji_pal[0x20 / sizeof(u16)];
#else
static u16 rom_shop3_leji_pal[] = {
#include "assets/rom_shop3w/rom_shop3_leji_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_shop3_desk_pal[0x20 / sizeof(u16)];
#else
static u16 rom_shop3_desk_pal[] = {
#include "assets/rom_shop3w/rom_shop3_desk_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_shop3_mat_pal[0x20 / sizeof(u16)];
#else
static u16 rom_shop3_mat_pal[] = {
#include "assets/rom_shop3w/rom_shop3_mat_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_shop3_bini_pal[0x20 / sizeof(u16)];
#else
static u16 rom_shop3_bini_pal[] = {
#include "assets/rom_shop3w/rom_shop3_bini_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 rom_shop3_wallC_pal[0x20 / sizeof(u16)];
#else
static u16 rom_shop3_wallC_pal[] = {
#include "assets/rom_shop3w/rom_shop3_wallC_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_ent[0x200];
#else
static u8 rom_shop3_ent[] = {
#include "assets/rom_shop3w/rom_shop3_ent.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop3_tana[0x100];
#else
u8 rom_shop3_tana[] = {
#include "assets/rom_shop3_tana.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_kago_b[0x100];
#else
static u8 rom_shop3_kago_b[] = {
#include "assets/rom_shop3w/rom_shop3_kago_b.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop3_kago_t[0x80];
#else
u8 rom_shop3_kago_t[] = {
#include "assets/rom_shop3_kago_t.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_leji_f[0x80];
#else
static u8 rom_shop3_leji_f[] = {
#include "assets/rom_shop3w/rom_shop3_leji_f.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_leji_k[0x80];
#else
static u8 rom_shop3_leji_k[] = {
#include "assets/rom_shop3w/rom_shop3_leji_k.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_leji_b[0x80];
#else
static u8 rom_shop3_leji_b[] = {
#include "assets/rom_shop3w/rom_shop3_leji_b.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_desk_a[0x200];
#else
static u8 rom_shop3_desk_a[] = {
#include "assets/rom_shop3w/rom_shop3_desk_a.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_desk_b[0x80];
#else
static u8 rom_shop3_desk_b[] = {
#include "assets/rom_shop3w/rom_shop3_desk_b.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_desk_c[0x200];
#else
static u8 rom_shop3_desk_c[] = {
#include "assets/rom_shop3w/rom_shop3_desk_c.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_tana_t[0x80];
#else
static u8 rom_shop3_tana_t[] = {
#include "assets/rom_shop3w/rom_shop3_tana_t.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop3_mat_a[0x80];
#else
u8 rom_shop3_mat_a[] = {
#include "assets/rom_shop3_mat_a.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_shop3_mat_b[0x100];
#else
u8 rom_shop3_mat_b[] = {
#include "assets/rom_shop3_mat_b.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_bini[0x80];
#else
static u8 rom_shop3_bini[] = {
#include "assets/rom_shop3w/rom_shop3_bini.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_bini_b[0x80];
#else
static u8 rom_shop3_bini_b[] = {
#include "assets/rom_shop3w/rom_shop3_bini_b.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_car[0x100];
#else
static u8 rom_shop3_car[] = {
#include "assets/rom_shop3w/rom_shop3_car.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_bini_a[0x80];
#else
static u8 rom_shop3_bini_a[] = {
#include "assets/rom_shop3w/rom_shop3_bini_a.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_wallC[0x800];
#else
static u8 rom_shop3_wallC[] = {
#include "assets/rom_shop3w/rom_shop3_wallC.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_wallD[0x800];
#else
static u8 rom_shop3_wallD[] = {
#include "assets/rom_shop3w/rom_shop3_wallD.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_floorE[0x200];
#else
static u8 rom_shop3_floorE[] = {
#include "assets/rom_shop3w/rom_shop3_floorE.inc"
};
#endif

#ifdef TARGET_PC
static u8 rom_shop3_kage1[0x80];
#else
static u8 rom_shop3_kage1[] = {
#include "assets/rom_shop3w/rom_shop3_kage1.inc"
};
#endif

#ifdef TARGET_PC
Vtx rom_shop3w_v[0x2320 / sizeof(Vtx)];
#else
Vtx rom_shop3w_v[] = {
#include "assets/rom_shop3w_v.inc"
};
#endif

Gfx rom_shop3w_modelT[] = {
    gsSPEndDisplayList(),
};

Gfx rom_shop3w_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_mat_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, rom_shop3_car),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&rom_shop3w_v[309], 28, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 11, 9, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 12, 15, 13, 16, 17, 18),
    gsSPNTriangles_5b(16, 19, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 20, 21, 22, 20, 23, 21, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 25, 27, 26, 0, 0, 0),
    gsSPVertex(&rom_shop3w_v[337], 4, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_bini_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_shop3_bini_a),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop3w_v[341], 18, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_shop3_bini_b),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(15, 17, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_tana_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_shop3_kago_t),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop3w_v[359], 25, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, rom_shop3_kago_b),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 8, 9, 10, 8, 11, 9, 12, 10, 13),
    gsSPNTriangles_5b(12, 8, 10, 9, 14, 15, 9, 16, 14, 17, 18, 19),
    gsSPNTriangles_5b(17, 19, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 21, 22, 23, 21, 23, 24, 0, 0, 0),
    gsSPVertex(&rom_shop3w_v[384], 28, 0),
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
    gsSPVertex(&rom_shop3w_v[412], 28, 0),
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
    gsSPVertex(&rom_shop3w_v[440], 24, 0),
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
    gsSPVertex(&rom_shop3w_v[464], 28, 0),
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
    gsSPVertex(&rom_shop3w_v[492], 28, 0),
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
    gsSPVertex(&rom_shop3w_v[520], 28, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_shop3w_v[548], 14, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 4, 5, 6, 4, 6, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 11, 9, 11, 12, 9, 11, 13, 12, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(rom_shop3w_v, 14, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 1, 3, 2, 0, 4, 1),
    gsSPNTriangles_5b(0, 5, 4, 4, 6, 1, 4, 5, 6, 7, 8, 9),
    gsSPNTriangles_5b(7, 10, 8, 8, 11, 9, 11, 12, 9, 8, 13, 11),
    gsSPNTriangles_5b(13, 12, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop3w_v[14], 14, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 3, 1, 0, 4, 3),
    gsSPNTriangles_5b(4, 5, 3, 5, 6, 3, 7, 8, 9, 8, 10, 9),
    gsSPNTriangles_5b(10, 11, 9, 10, 12, 11, 10, 13, 12, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_wallC_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop3_wallC),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop3w_v[28], 19, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 0, 3, 1, 1, 4, 2),
    gsSPNTriangles_5b(1, 3, 4, 5, 6, 7, 6, 8, 7, 5, 9, 6),
    gsSPNTriangles_5b(9, 8, 6, 10, 11, 12, 13, 14, 15, 13, 10, 14),
    gsSPNTriangles_5b(10, 12, 14, 12, 15, 14, 10, 16, 11, 16, 17, 11),
    gsSPNTriangles_5b(10, 18, 16, 18, 17, 16, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop3_wallD),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop3w_v[47], 19, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(5, 6, 7, 5, 8, 6, 8, 9, 6, 10, 11, 12),
    gsSPNTriangles_5b(11, 13, 12, 14, 15, 16, 15, 17, 16, 16, 18, 12),
    gsSPNTriangles_5b(10, 12, 18, 16, 17, 18, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_ent_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_shop3_floorE),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop3w_v[66], 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 3, 4, 0, 5, 3, 6),
    gsSPNTriangles_5b(3, 7, 6, 2, 8, 9, 2, 1, 8, 1, 0, 10),
    gsSPNTriangles_5b(0, 4, 10, 11, 12, 7, 12, 6, 7, 12, 11, 13),
    gsSPNTriangles_5b(1, 14, 8, 1, 15, 14, 1, 16, 15, 1, 10, 16),
    gsSPNTriangles_5b(17, 15, 18, 19, 15, 16, 9, 20, 21, 8, 20, 9),
    gsSPNTriangles_5b(22, 23, 21, 24, 5, 6, 24, 25, 5, 4, 26, 10),
    gsSPNTriangles_5b(4, 27, 26, 27, 28, 29, 30, 31, 25, 25, 27, 4),
    gsSPNTriangles_5b(14, 20, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_shop3w_v[98], 24, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 0, 2, 4, 3, 2),
    gsSPNTriangles_5b(5, 6, 7, 8, 9, 10, 5, 11, 10, 9, 5, 10),
    gsSPNTriangles_5b(12, 13, 14, 15, 16, 14, 15, 17, 18, 15, 14, 17),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_shop3_ent),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3, 19, 20, 21, 21, 22, 19, 19, 23, 20),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_tana_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_shop3_tana_t),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop3w_v[122], 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, rom_shop3_tana),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop3w_v[134], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 16, 17, 18, 16, 19, 17, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 22, 24, 25, 26, 24, 27, 25, 28, 29, 30),
    gsSPNTriangles_5b(29, 31, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&rom_shop3w_v[166], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 1, 4, 3),
    gsSPNTriangles_5b(4, 5, 3, 6, 7, 8, 6, 9, 7, 10, 11, 12),
    gsSPNTriangles_5b(11, 13, 12, 14, 15, 16, 14, 17, 15, 18, 19, 20),
    gsSPNTriangles_5b(18, 21, 19, 22, 20, 19, 22, 23, 20, 24, 25, 26),
    gsSPNTriangles_5b(24, 27, 25, 28, 29, 30, 28, 31, 29, 0, 0, 0),
    gsSPVertex(&rom_shop3w_v[198], 26, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 15, 13, 16, 17, 18, 16, 19, 17, 20, 15, 21),
    gsSPNTriangles_5b(15, 12, 21, 22, 23, 24, 22, 25, 23, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_desk_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_shop3_desk_c),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop3w_v[224], 29, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 4, 9, 5, 4, 10, 11, 0),
    gsSPNTriangles_5b(10, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_shop3_desk_b),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 13, 14, 15, 14, 16, 15, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_shop3_desk_a),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(6, 17, 18, 19, 18, 20, 19, 21, 22, 23),
    gsSPNTriangles_5b(21, 23, 24, 25, 26, 27, 26, 28, 27, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_mat_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, rom_shop3_mat_b),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop3w_v[253], 16, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_shop3_mat_a),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 4, 5, 6, 4, 7, 5, 8, 9, 10),
    gsSPNTriangles_5b(9, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_leji_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_shop3_leji_b),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop3_bini_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_shop3_bini),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop3w_v[283], 26, 0),
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
    gsSPVertex(&rom_shop3w_v[269], 14, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 2, 3, 4),
    gsSPNTriangles_5b(3, 5, 4, 6, 7, 8, 9, 6, 8, 10, 11, 12),
    gsSPNTriangles_5b(11, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_rom_shop3w_c(void) {
    pc_load_asset("assets/rom_shop3w/rom_shop3_ent_pal.bin", rom_shop3_ent_pal, 0x20, 0xC470A0, 0, 1);
    pc_load_asset("assets/rom_shop3w/rom_shop3_tana_pal.bin", rom_shop3_tana_pal, 0x20, 0xC470E0, 0, 1);
    pc_load_asset("assets/rom_shop3w/rom_shop3_leji_pal.bin", rom_shop3_leji_pal, 0x20, 0xC47100, 0, 1);
    pc_load_asset("assets/rom_shop3w/rom_shop3_desk_pal.bin", rom_shop3_desk_pal, 0x20, 0xC47120, 0, 1);
    pc_load_asset("assets/rom_shop3w/rom_shop3_mat_pal.bin", rom_shop3_mat_pal, 0x20, 0xC47160, 0, 1);
    pc_load_asset("assets/rom_shop3w/rom_shop3_bini_pal.bin", rom_shop3_bini_pal, 0x20, 0xC47140, 0, 1);
    pc_load_asset("assets/rom_shop3w/rom_shop3_wallC_pal.bin", rom_shop3_wallC_pal, 0x20, 0xC47180, 0, 1);
    pc_load_asset("assets/rom_shop3w/rom_shop3_ent.bin", rom_shop3_ent, 0x200, 0xC471A0, 0, 0);
    pc_load_asset("assets/rom_shop3w/rom_shop3_kago_b.bin", rom_shop3_kago_b, 0x100, 0xC47CA0, 0, 0);
    pc_load_asset("assets/rom_shop3w/rom_shop3_leji_f.bin", rom_shop3_leji_f, 0x80, 0xC47DA0, 0, 0);
    pc_load_asset("assets/rom_shop3w/rom_shop3_leji_k.bin", rom_shop3_leji_k, 0x80, 0xC47E20, 0, 0);
    pc_load_asset("assets/rom_shop3w/rom_shop3_leji_b.bin", rom_shop3_leji_b, 0x80, 0xC47EA0, 0, 0);
    pc_load_asset("assets/rom_shop3w/rom_shop3_desk_a.bin", rom_shop3_desk_a, 0x200, 0xC47F20, 0, 0);
    pc_load_asset("assets/rom_shop3w/rom_shop3_desk_b.bin", rom_shop3_desk_b, 0x80, 0xC48120, 0, 0);
    pc_load_asset("assets/rom_shop3w/rom_shop3_desk_c.bin", rom_shop3_desk_c, 0x200, 0xC481A0, 0, 0);
    pc_load_asset("assets/rom_shop3w/rom_shop3_tana_t.bin", rom_shop3_tana_t, 0x80, 0xC483A0, 0, 0);
    pc_load_asset("assets/rom_shop3w/rom_shop3_bini.bin", rom_shop3_bini, 0x80, 0xC48420, 0, 0);
    pc_load_asset("assets/rom_shop3w/rom_shop3_bini_b.bin", rom_shop3_bini_b, 0x80, 0xC484A0, 0, 0);
    pc_load_asset("assets/rom_shop3w/rom_shop3_car.bin", rom_shop3_car, 0x100, 0xC48520, 0, 0);
    pc_load_asset("assets/rom_shop3w/rom_shop3_bini_a.bin", rom_shop3_bini_a, 0x80, 0xC48620, 0, 0);
    pc_load_asset("assets/rom_shop3w/rom_shop3_wallC.bin", rom_shop3_wallC, 0x800, 0xC486A0, 0, 0);
    pc_load_asset("assets/rom_shop3w/rom_shop3_wallD.bin", rom_shop3_wallD, 0x800, 0xC48EA0, 0, 0);
    pc_load_asset("assets/rom_shop3w/rom_shop3_floorE.bin", rom_shop3_floorE, 0x200, 0xC496A0, 0, 0);
    pc_load_asset("assets/rom_shop3w/rom_shop3_kage1.bin", rom_shop3_kage1, 0x80, 0xC441C0, 0, 0);
}
#endif
