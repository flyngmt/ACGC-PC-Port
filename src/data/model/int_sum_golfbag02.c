#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_golfbag02_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_sum_golfbag02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_sum_golfbag02_pal[] = {
#include "assets/int_sum_golfbag02_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 int_sum_golfbag_pal[0x20 / sizeof(u16)];
#else
static u16 int_sum_golfbag_pal[] = {
#include "assets/int_sum_golfbag02/int_sum_golfbag_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_golfbag02_top_tex_txt[0x100];
#else
u8 int_sum_golfbag02_top_tex_txt[] = {
#include "assets/int_sum_golfbag02_top_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_golfbag02_carry_tex_txt[0x180];
#else
u8 int_sum_golfbag02_carry_tex_txt[] = {
#include "assets/int_sum_golfbag02_carry_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_golfbag02_body_tex_txt[0x400];
#else
u8 int_sum_golfbag02_body_tex_txt[] = {
#include "assets/int_sum_golfbag02_body_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_golfbag02_clab2_tex_txt[0x80];
#else
u8 int_sum_golfbag02_clab2_tex_txt[] = {
#include "assets/int_sum_golfbag02_clab2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_golfbag02_clab1_tex_txt[0x80];
#else
u8 int_sum_golfbag02_clab1_tex_txt[] = {
#include "assets/int_sum_golfbag02_clab1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_sum_golfbag02_clab3_tex_txt[0x80];
#else
u8 int_sum_golfbag02_clab3_tex_txt[] = {
#include "assets/int_sum_golfbag02_clab3_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_sum_golfbag02_v[0x560 / sizeof(Vtx)];
#else
Vtx int_sum_golfbag02_v[] = {
#include "assets/int_sum_golfbag02_v.inc"
};
#endif

Gfx int_sum_golfbag02_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_golfbag02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_golfbag02_top_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_golfbag02_v, 30, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(1, 3, 4, 5, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_golfbag02_carry_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 188),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 6, 7, 8, 6, 8, 9, 9, 8, 10),
    gsSPNTriangles_5b(9, 11, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, int_sum_golfbag02_body_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsSPNTrianglesInit_5b(5, 12, 13, 14, 13, 15, 14, 16, 17, 18),
    gsSPNTriangles_5b(19, 16, 20, 20, 16, 18, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(5, 21, 22, 23, 21, 23, 24, 25, 26, 27),
    gsSPNTriangles_5b(25, 27, 28, 22, 29, 23, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_sum_golfbag02_v[30], 22, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 3, 4, 5, 6, 7, 8, 4, 9, 6),
    gsSPNTriangles_5b(10, 11, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 13, 14, 15, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 16, 17, 18, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 19, 20, 21, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_sum_golfbag02_v[52], 28, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 1, 4, 5, 0, 2),
    gsSPNTriangles_5b(4, 6, 3, 5, 2, 7, 8, 3, 6, 9, 10, 11),
    gsSPNTriangles_5b(0, 5, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 12, 13, 14, 14, 13, 15, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_golfbag_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_golfbag02_clab2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 16, 17, 18, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_golfbag02_clab1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 19, 20, 21, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_golfbag02_clab3_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 22, 23, 24, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_golfbag02_clab2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 25, 26, 27, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_golfbag02_clab1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_golfbag02_v[80], 6, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_sum_golfbag02_c(void) {
    pc_load_asset("assets/int_sum_golfbag02/int_sum_golfbag_pal.bin", int_sum_golfbag_pal, 0x20, 0xCC7C00, 0, 1);
}
#endif
