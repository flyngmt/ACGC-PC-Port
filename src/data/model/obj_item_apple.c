#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 obj_item_apple_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 obj_item_apple_pal[] = {
#include "assets/obj_item_apple/obj_item_apple_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 obj_item_apple_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 obj_item_apple_tex[] = {
#include "assets/obj_item_apple/obj_item_apple_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx obj_item_apple_v[0x40 / sizeof(Vtx)];
#else
static Vtx obj_item_apple_v[] = {
#include "assets/obj_item_apple/obj_item_apple_v.inc"
};
#endif

Gfx obj_apple2_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_item_apple_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_item_apple_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_item_apple_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_item_apple_c(void) {
    pc_load_asset("assets/obj_item_apple/obj_item_apple_pal.bin", obj_item_apple_pal, 0x20, 0x66AB20, 0, 1);
    pc_load_asset("assets/obj_item_apple/obj_item_apple_tex.bin", obj_item_apple_tex, 0x200, 0x66AB40, 0, 0);
    pc_load_asset("assets/obj_item_apple/obj_item_apple_v.bin", obj_item_apple_v, 0x40, 0x66AD40, 0, 2);
}
#endif
