#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_myhome_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_myhome_pal[] = {
#include "assets/obj_myhome_step_up/rom_myhome_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 rom_myhome_step_tex[0x800];
#else
u8 rom_myhome_step_tex[] = {
#include "assets/rom_myhome_step_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_myhome_step_up_v[0x140 / sizeof(Vtx)];
#else
Vtx obj_myhome_step_up_v[] = {
#include "assets/obj_myhome_step_up_v.inc"
};
#endif

Gfx obj_myhome_step_up_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_myhome_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, rom_myhome_step_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_myhome_step_up_v, 20, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 2, 1, 4),
    gsSPNTriangles_5b(2, 4, 5, 6, 7, 0, 6, 0, 3, 8, 9, 7),
    gsSPNTriangles_5b(8, 7, 6, 10, 11, 9, 10, 9, 8, 12, 13, 11),
    gsSPNTriangles_5b(12, 11, 10, 14, 15, 16, 14, 16, 17, 18, 19, 15),
    gsSPNTriangles_5b(18, 15, 14, 5, 4, 19, 5, 19, 18, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_obj_myhome_step_up_c(void) {
    pc_load_asset("assets/obj_myhome_step_up/rom_myhome_pal.bin", rom_myhome_pal, 0x20, 0xBB86C0, 0, 1);
}
#endif
