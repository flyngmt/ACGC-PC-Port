#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_din_hutaba_neck_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_din_hutaba_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_din_hutaba_pal[] = {
#include "assets/int_din_hutaba_neck/int_din_hutaba_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_hutaba_kubi2c_tex[0x80];
#else
u8 int_din_hutaba_kubi2c_tex[] = {
#include "assets/int_din_hutaba_kubi2c_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_hutaba_baceB_tex[0x200];
#else
u8 int_din_hutaba_baceB_tex[] = {
#include "assets/int_din_hutaba_baceB_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_hutaba_poleB_tex[0x80];
#else
u8 int_din_hutaba_poleB_tex[] = {
#include "assets/int_din_hutaba_poleB_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_hutaba_kubic_tex[0x100];
#else
u8 int_din_hutaba_kubic_tex[] = {
#include "assets/int_din_hutaba_kubic_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_din_hutaba_neck_v[0x320 / sizeof(Vtx)];
#else
Vtx int_din_hutaba_neck_v[] = {
#include "assets/int_din_hutaba_neck_v.inc"
};
#endif

Gfx int_din_hutaba_neck_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_hutaba_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_din_hutaba_baceB_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_din_hutaba_neck_v, 8, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 3, 3, 5, 6, 3, 6, 0, 0, 6, 7),
    gsSPNTriangles_5b(0, 7, 1, 1, 7, 4, 1, 4, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_din_hutaba_neckT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_hutaba_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_din_hutaba_kubic_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_din_hutaba_neck_v[8], 26, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 4, 6, 7, 4, 7, 5, 6, 8, 9),
    gsSPNTriangles_5b(6, 9, 7, 8, 10, 11, 8, 11, 9, 10, 12, 13),
    gsSPNTriangles_5b(10, 13, 11, 12, 14, 15, 12, 15, 13, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_hutaba_poleB_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 19, 17, 20, 21, 22, 23),
    gsSPNTriangles_5b(24, 22, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_hutaba_kubi2c_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_din_hutaba_neck_v[34], 16, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 4, 6, 7, 4, 7, 5, 6, 8, 9),
    gsSPNTriangles_5b(6, 9, 7, 8, 10, 11, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 13, 0, 3, 13, 3, 14, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_din_hutaba_neck_c(void) {
    pc_load_asset("assets/int_din_hutaba_neck/int_din_hutaba_pal.bin", int_din_hutaba_pal, 0x20, 0x912C80, 0, 1);
}
#endif
