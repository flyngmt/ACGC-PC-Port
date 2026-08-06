#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 obj_shop_net2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 obj_shop_net2_pal[]= {
#include "assets/obj_shop_axe2/obj_shop_net2_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_shop_axe2_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_shop_axe2_tex[]= {
#include "assets/obj_shop_axe2_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop_axe2_v[0x1A0 / sizeof(Vtx)];
#else
Vtx obj_shop_axe2_v[] = {
#include "assets/obj_shop_axe2_v.inc"
};
#endif

Gfx obj_axe2T_mat_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_net2_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_axe2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_axe2T_gfx_model[] = {
gsSPVertex(obj_shop_axe2_v, 26, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 2, 4, 5),
gsSPNTriangles_5b(2, 5, 3, 6, 7, 8, 6, 8, 9, 8, 10, 9),
gsSPNTriangles_5b(6, 11, 7, 12, 6, 9, 12, 9, 13, 14, 15, 16),
gsSPNTriangles_5b(17, 18, 19, 20, 21, 22, 20, 22, 23, 23, 24, 25),
gsSPNTriangles_5b(23, 25, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};


#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_shop_axe2_c(void) {
    pc_load_asset("assets/obj_shop_axe2/obj_shop_net2_pal.bin", obj_shop_net2_pal, 0x20, 0x676B60, 0, 1);
}
#endif
