#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 tol_fan7_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 tol_fan7_pal[]= {
#include "assets/obj_shop_utiwa7/tol_fan7_pal.inc"
};
#endif

#ifdef TARGET_PC
static u8 tol_fan7_tex_txt[0x400];
#else
static u8 tol_fan7_tex_txt[] = {
#include "assets/obj_shop_utiwa7/tol_fan7_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop_utiwa7_v[0x80 / sizeof(Vtx)];
#else
Vtx obj_shop_utiwa7_v[] = {
#include "assets/obj_shop_utiwa7_v.inc"
};
#endif

Gfx obj_shop_utiwa7_mat_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, tol_fan7_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, tol_fan7_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_shop_utiwa7_gfx_model[] = {
gsSPVertex(obj_shop_utiwa7_v, 8, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
gsSPEndDisplayList(),
};


#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_shop_utiwa7_c(void) {
    pc_load_asset("assets/obj_shop_utiwa7/tol_fan7_pal.bin", tol_fan7_pal, 0x20, 0x4653A0, 0, 1);
    pc_load_asset("assets/obj_shop_utiwa7/tol_fan7_tex_txt.bin", tol_fan7_tex_txt, 0x400, 0x4653C0, 0, 0);
}
#endif
