#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_kon_isi01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_kon_isi01_pal[] = {
#include "assets/int_kon_isi05/int_kon_isi01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_isi05_a_tex[0x400];
#else
u8 int_kon_isi05_a_tex[] = {
#include "assets/int_kon_isi05_a_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_isi05_c_tex[0x400];
#else
u8 int_kon_isi05_c_tex[] = {
#include "assets/int_kon_isi05_c_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_isi05_v[0x170 / sizeof(Vtx)];
#else
Vtx int_kon_isi05_v[] = {
#include "assets/int_kon_isi05_v.inc"
};
#endif

Gfx int_kon_isi05_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_isi01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_kon_isi05_c_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_isi05_v, 23, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 0, 3, 1, 4, 0, 2),
    gsSPNTriangles_5b(1, 5, 2, 5, 6, 2, 6, 7, 2, 7, 4, 2),
    gsSPNTriangles_5b(0, 8, 3, 9, 4, 7, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_kon_isi05_a_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(13, 10, 11, 12, 13, 14, 15, 13, 15, 16),
    gsSPNTriangles_5b(14, 17, 18, 14, 18, 15, 18, 19, 15, 19, 20, 15),
    gsSPNTriangles_5b(15, 20, 16, 21, 16, 20, 21, 13, 16, 21, 20, 22),
    gsSPNTriangles_5b(10, 21, 22, 10, 22, 11, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_kon_isi05_c(void) {
    pc_load_asset("assets/int_kon_isi05/int_kon_isi01_pal.bin", int_kon_isi01_pal, 0x20, 0xB85060, 0, 1);
}
#endif
