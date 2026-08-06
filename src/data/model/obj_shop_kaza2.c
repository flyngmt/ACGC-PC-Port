#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_kaza_2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_kaza_2_pal[]= {
#include "assets/obj_shop_kaza2/tol_kaza_2_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_2_a_tex_txt[0x200];
#else
static u8 tol_kaza_2_a_tex_txt[] = {
#include "assets/obj_shop_kaza2/tol_kaza_2_a_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_2_c_tex_txt[0x200];
#else
static u8 tol_kaza_2_c_tex_txt[] = {
#include "assets/obj_shop_kaza2/tol_kaza_2_c_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_kaza_2_b_tex_txt[0x100];
#else
static u8 tol_kaza_2_b_tex_txt[] = {
#include "assets/obj_shop_kaza2/tol_kaza_2_b_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop_kaza2_v[0x360 / sizeof(Vtx)];
#else
Vtx obj_shop_kaza2_v[] = {
#include "assets/obj_shop_kaza2_v.inc"
};
#endif

Gfx obj_shop_kaza2_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, tol_kaza_2_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_2_a_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(obj_shop_kaza2_v, 24, 0),
gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 2, 4, 0),
gsSPNTriangles_5b(5, 6, 7, 8, 5, 7, 7, 9, 8, 10, 11, 12),
gsSPNTriangles_5b(13, 10, 12, 12, 14, 13, 15, 16, 17, 17, 18, 15),
gsSPNTriangles_5b(18, 19, 15, 20, 21, 22, 20, 22, 23, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_kaza_2_c_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&obj_shop_kaza2_v[24], 30, 0),
gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 3, 4, 2),
gsSPNTriangles_5b(3, 5, 4, 6, 7, 8, 6, 8, 0, 9, 6, 0),
gsSPNTriangles_5b(10, 9, 0, 2, 11, 10, 2, 10, 0, 2, 12, 11),
gsSPNTriangles_5b(12, 13, 11, 13, 14, 11, 13, 15, 14, 16, 17, 18),
gsSPNTriangles_5b(16, 18, 10, 19, 16, 10, 11, 19, 10, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_kaza_2_b_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(2, 20, 21, 22, 22, 23, 20, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 24, 25, 26, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 27, 28, 29, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};


#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_shop_kaza2_c(void) {
    pc_load_asset("assets/obj_shop_kaza2/tol_kaza_2_pal.bin", tol_kaza_2_pal, 0x20, 0x45E220, 0, 1);
    pc_load_asset("assets/obj_shop_kaza2/tol_kaza_2_a_tex_txt.bin", tol_kaza_2_a_tex_txt, 0x200, 0x45E240, 0, 0);
    pc_load_asset("assets/obj_shop_kaza2/tol_kaza_2_c_tex_txt.bin", tol_kaza_2_c_tex_txt, 0x200, 0x45E440, 0, 0);
    pc_load_asset("assets/obj_shop_kaza2/tol_kaza_2_b_tex_txt.bin", tol_kaza_2_b_tex_txt, 0x100, 0x45E640, 0, 0);
}
#endif
