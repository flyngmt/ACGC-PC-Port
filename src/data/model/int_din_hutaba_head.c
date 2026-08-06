#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_din_hutaba_head_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_din_hutaba_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_din_hutaba_pal[] = {
#include "assets/int_din_hutaba_head/int_din_hutaba_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_hutaba_h_tex[0x400];
#else
u8 int_din_hutaba_h_tex[] = {
#include "assets/int_din_hutaba_h_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_hutaba_kubi2_tex[0x80];
#else
u8 int_din_hutaba_kubi2_tex[] = {
#include "assets/int_din_hutaba_kubi2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_hutaba_baceA_tex[0x200];
#else
u8 int_din_hutaba_baceA_tex[] = {
#include "assets/int_din_hutaba_baceA_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_hutaba_poleA_tex[0x80];
#else
u8 int_din_hutaba_poleA_tex[] = {
#include "assets/int_din_hutaba_poleA_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_hutaba_kubi_tex[0x100];
#else
u8 int_din_hutaba_kubi_tex[] = {
#include "assets/int_din_hutaba_kubi_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_din_hutaba_head_v[0x370 / sizeof(Vtx)];
#else
Vtx int_din_hutaba_head_v[] = {
#include "assets/int_din_hutaba_head_v.inc"
};
#endif

Gfx int_din_hutaba_head_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_hutaba_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_din_hutaba_baceA_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_din_hutaba_head_v, 8, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 3, 2, 6, 3, 6, 7, 0, 3, 7),
    gsSPNTriangles_5b(0, 7, 4, 7, 6, 5, 7, 5, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_din_hutaba_headT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_hutaba_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_din_hutaba_kubi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_din_hutaba_head_v[8], 22, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 5, 8, 9, 5, 9, 6, 8, 10, 11),
    gsSPNTriangles_5b(8, 11, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_hutaba_poleA_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 15, 13, 16, 17, 18, 19),
    gsSPNTriangles_5b(20, 18, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_hutaba_kubi2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&int_din_hutaba_head_v[30], 25, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 5, 8, 9, 5, 9, 6, 8, 10, 11),
    gsSPNTriangles_5b(8, 11, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_din_hutaba_h_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(18, 12, 13, 14, 12, 15, 13, 15, 16, 13),
    gsSPNTriangles_5b(16, 17, 13, 18, 13, 17, 17, 19, 18, 19, 20, 18),
    gsSPNTriangles_5b(18, 14, 13, 15, 19, 16, 15, 21, 19, 21, 20, 19),
    gsSPNTriangles_5b(17, 16, 19, 21, 22, 20, 22, 23, 18, 22, 18, 20),
    gsSPNTriangles_5b(18, 23, 24, 18, 24, 14, 24, 12, 14, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_din_hutaba_head_c(void) {
    pc_load_asset("assets/int_din_hutaba_head/int_din_hutaba_pal.bin", int_din_hutaba_pal, 0x20, 0x911F80, 0, 1);
}
#endif
