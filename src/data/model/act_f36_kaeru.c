#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_nog_kaeru_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_nog_kaeru_pal[] = {
#include "assets/act_f36_kaeru/int_nog_kaeru_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 act_f36_kaeru_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) u8 act_f36_kaeru_tex[] = {
#include "assets/act_f36_kaeru_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_f36_kaeru_a_v[0x80 / sizeof(Vtx)];
#else
Vtx act_f36_kaeru_a_v[] = {
#include "assets/act_f36_kaeru_a_v.inc"
};
#endif

Gfx act_f36_kaeru_aT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_kaeru_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 128, act_f36_kaeru_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_f36_kaeru_a_v, 8, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 0, 3, 1, 1, 4, 2),
    gsSPNTriangles_5b(2, 5, 6, 6, 7, 0, 2, 6, 0, 0, 7, 3),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
Vtx act_f36_kaeru_b_v[0x80 / sizeof(Vtx)];
#else
Vtx act_f36_kaeru_b_v[] = {
#include "assets/act_f36_kaeru_b_v.inc"
};
#endif

Gfx act_f36_kaeru_bT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_kaeru_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 128, act_f36_kaeru_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_f36_kaeru_b_v, 8, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 0, 4, 1, 0),
    gsSPNTriangles_5b(3, 5, 4, 6, 7, 3, 0, 2, 6, 0, 6, 3),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
Vtx act_f36_kaeru_c_v[0x80 / sizeof(Vtx)];
#else
Vtx act_f36_kaeru_c_v[] = {
#include "assets/act_f36_kaeru_c_v.inc"
};
#endif

Gfx act_f36_kaeru_cT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_kaeru_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 128, act_f36_kaeru_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_f36_kaeru_c_v, 8, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 0, 4, 1, 0),
    gsSPNTriangles_5b(3, 5, 4, 6, 7, 3, 0, 2, 6, 0, 6, 3),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_f36_kaeru_c(void) {
    pc_load_asset("assets/act_f36_kaeru/int_nog_kaeru_pal.bin", int_nog_kaeru_pal, 0x20, 0x51A920, 0, 1);
}
#endif
