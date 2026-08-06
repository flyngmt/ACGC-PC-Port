#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_din_bront_tail_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_din_bront_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_din_bront_pal[] = {
#include "assets/int_din_bront_tail/int_din_bront_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_bront_kb2C_tex[0x80];
#else
u8 int_din_bront_kb2C_tex[] = {
#include "assets/int_din_bront_kb2C_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_bront_baceC_tex[0x200];
#else
u8 int_din_bront_baceC_tex[] = {
#include "assets/int_din_bront_baceC_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_din_bront_poleC_tex[0x80];
#else
u8 int_din_bront_poleC_tex[] = {
#include "assets/int_din_bront_poleC_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_din_bront_tail_v[0x350 / sizeof(Vtx)];
#else
Vtx int_din_bront_tail_v[] = {
#include "assets/int_din_bront_tail_v.inc"
};
#endif

Gfx int_din_bront_tail_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_bront_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_din_bront_baceC_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_din_bront_tail_v, 8, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 0),
    gsSPNTriangles_5b(4, 0, 3, 5, 6, 1, 5, 1, 0, 3, 2, 7),
    gsSPNTriangles_5b(3, 7, 4, 4, 7, 6, 4, 6, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_din_bront_tailT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_din_bront_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_bront_poleC_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_din_bront_tail_v[8], 10, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 1, 4, 5, 6, 7),
    gsSPNTriangles_5b(8, 6, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_din_bront_kb2C_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsSPVertex(&int_din_bront_tail_v[18], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 10, 13, 15, 16, 13, 16, 14, 17, 18, 19),
    gsSPNTriangles_5b(17, 19, 20, 21, 22, 23, 21, 23, 24, 23, 25, 26),
    gsSPNTriangles_5b(23, 26, 24, 27, 28, 29, 27, 29, 30, 0, 0, 0),
    gsSPVertex(&int_din_bront_tail_v[49], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_din_bront_tail_c(void) {
    pc_load_asset("assets/int_din_bront_tail/int_din_bront_pal.bin", int_din_bront_pal, 0x20, 0x90F460, 0, 1);
}
#endif
