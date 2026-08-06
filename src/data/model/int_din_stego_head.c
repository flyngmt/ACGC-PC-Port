#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_din_stego_head_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_din_stego_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_din_stego_pal[] = {
#include "assets/int_din_stego_head/int_din_stego_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_stego_finA_tex[0x80];
#else
u8 int_din_stego_finA_tex[] = {
#include "assets/int_din_stego_finA_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_stego_h_tex[0x200];
#else
u8 int_din_stego_h_tex[] = {
#include "assets/int_din_stego_h_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_stego_kubi2_tex[0x80];
#else
u8 int_din_stego_kubi2_tex[] = {
#include "assets/int_din_stego_kubi2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_stego_baceA_tex[0x200];
#else
u8 int_din_stego_baceA_tex[] = {
#include "assets/int_din_stego_baceA_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_stego_poleA_tex[0x80];
#else
u8 int_din_stego_poleA_tex[] = {
#include "assets/int_din_stego_poleA_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_stego_kubi_tex[0x80];
#else
u8 int_din_stego_kubi_tex[] = {
#include "assets/int_din_stego_kubi_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_din_stego_head_v[0x250 / sizeof(Vtx)];
#else
Vtx int_din_stego_head_v[] = {
#include "assets/int_din_stego_head_v.inc"
};
#endif

Gfx int_din_stego_head_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_stego_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_din_stego_baceA_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_din_stego_head_v, 8, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 3, 2, 6, 3, 6, 7, 0, 3, 7),
    gsSPNTriangles_5b(0, 7, 4, 7, 6, 5, 7, 5, 4, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_din_stego_headT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_stego_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_stego_kubi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_din_stego_head_v[8], 29, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_stego_poleA_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 7, 5, 8, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_stego_kubi2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 9, 10, 11, 9, 11, 12, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, int_din_stego_h_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(16, 13, 14, 15, 15, 16, 17, 16, 18, 17),
    gsSPNTriangles_5b(18, 19, 17, 18, 20, 19, 19, 21, 17, 22, 14, 13),
    gsSPNTriangles_5b(22, 13, 23, 19, 20, 24, 19, 24, 23, 23, 13, 25),
    gsSPNTriangles_5b(13, 21, 25, 21, 19, 25, 19, 23, 25, 13, 17, 21),
    gsSPNTriangles_5b(13, 15, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_stego_finA_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 26, 27, 28, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_din_stego_head_c(void) {
    pc_load_asset("assets/int_din_stego_head/int_din_stego_pal.bin", int_din_stego_pal, 0x20, 0x9188A0, 0, 1);
}
#endif
