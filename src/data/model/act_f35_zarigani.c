#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_nog_zarigani_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_nog_zarigani_pal[] = {
#include "assets/act_f35_zarigani/int_nog_zarigani_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 act_f35_zarigani_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) u8 act_f35_zarigani_tex[] = {
#include "assets/act_f35_zarigani_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_f35_zarigani_a_v[0x90 / sizeof(Vtx)];
#else
Vtx act_f35_zarigani_a_v[] = {
#include "assets/act_f35_zarigani_a_v.inc"
};
#endif

Gfx act_f35_zarigani_aT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_zarigani_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_f35_zarigani_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_f35_zarigani_a_v, 9, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(5, 0, 6, 0, 7, 6, 0, 2, 7, 0, 8, 1),
    gsSPNTriangles_5b(0, 5, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
Vtx act_f35_zarigani_b_v[0x90 / sizeof(Vtx)];
#else
Vtx act_f35_zarigani_b_v[] = {
#include "assets/act_f35_zarigani_b_v.inc"
};
#endif

Gfx act_f35_zarigani_bT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_zarigani_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_f35_zarigani_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_f35_zarigani_b_v, 9, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(5, 0, 6, 0, 7, 6, 0, 2, 7, 0, 8, 1),
    gsSPNTriangles_5b(0, 5, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
Vtx act_f35_zarigani_c_v[0x90 / sizeof(Vtx)];
#else
Vtx act_f35_zarigani_c_v[] = {
#include "assets/act_f35_zarigani_c_v.inc"
};
#endif

Gfx act_f35_zarigani_cT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_zarigani_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_f35_zarigani_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_f35_zarigani_c_v, 9, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(5, 0, 6, 0, 7, 6, 0, 2, 7, 0, 8, 1),
    gsSPNTriangles_5b(0, 5, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_act_f35_zarigani_c(void) {
    pc_load_asset("assets/act_f35_zarigani/int_nog_zarigani_pal.bin", int_nog_zarigani_pal, 0x20, 0x524360, 0, 1);
}
#endif
