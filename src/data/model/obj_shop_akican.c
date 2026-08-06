#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 obj_shop_akican_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 obj_shop_akican_pal[]= {
#include "assets/obj_shop_akican/obj_shop_akican_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_shop_akican_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_shop_akican_tex[]= {
#include "assets/obj_shop_akican_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop_akican_v[0x330 / sizeof(Vtx)];
#else
Vtx obj_shop_akican_v[] = {
#include "assets/obj_shop_akican_v.inc"
};
#endif

Gfx obj_g2T_mat_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_akican_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, obj_shop_akican_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_g2T_gfx_model[] = {
gsSPVertex(obj_shop_akican_v, 32, 0),
gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 0, 3, 4),
gsSPNTriangles_5b(0, 4, 5, 6, 7, 8, 6, 8, 9, 10, 6, 9),
gsSPNTriangles_5b(10, 9, 11, 12, 13, 14, 12, 14, 15, 13, 16, 17),
gsSPNTriangles_5b(13, 17, 14, 16, 18, 19, 16, 19, 17, 18, 10, 11),
gsSPNTriangles_5b(18, 11, 19, 20, 21, 22, 20, 22, 23, 24, 25, 26),
gsSPNTriangles_5b(24, 26, 27, 28, 29, 30, 28, 30, 31, 0, 0, 0),
gsSPVertex(&obj_shop_akican_v[32], 19, 0),
gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 7, 11, 12, 13),
gsSPNTriangles_5b(11, 13, 14, 15, 16, 17, 15, 17, 18, 0, 0, 0),
gsSPEndDisplayList(),
};


#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_shop_akican_c(void) {
    pc_load_asset("assets/obj_shop_akican/obj_shop_akican_pal.bin", obj_shop_akican_pal, 0x20, 0x677C40, 0, 1);
}
#endif
