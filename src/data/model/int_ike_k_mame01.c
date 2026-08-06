#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_k_mame01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_k_mame01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_k_mame01_pal[] = {
#include "assets/int_ike_k_mame01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_mamebox1_tex_txt[0x100];
#else
u8 int_ike_k_mamebox1_tex_txt[] = {
#include "assets/int_ike_k_mamebox1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_mamemame1_tex_txt[0x80];
#else
u8 int_ike_k_mamemame1_tex_txt[] = {
#include "assets/int_ike_k_mamemame1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_mamen_tex_txt[0x200];
#else
u8 int_ike_k_mamen_tex_txt[] = {
#include "assets/int_ike_k_mamen_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_k_mamehimo_tex_txt[0x100];
#else
u8 int_ike_k_mamehimo_tex_txt[] = {
#include "assets/int_ike_k_mamehimo_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_k_mame01_v[0x450 / sizeof(Vtx)];
#else
Vtx int_ike_k_mame01_v[] = {
#include "assets/int_ike_k_mame01_v.inc"
};
#endif

Gfx int_ike_k_mame01_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_k_mame01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_k_mamebox1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_k_mame01_v, 21, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_k_mamemame1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 18, 19, 16, 20, 17, 16),
    gsSPNTriangles_5b(16, 19, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_k_mamen_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_ike_k_mame01_v[21], 32, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 19, 20, 21, 21, 20, 22),
    gsSPNTriangles_5b(21, 22, 16, 3, 23, 24, 3, 24, 0, 25, 26, 19),
    gsSPNTriangles_5b(11, 27, 28, 11, 28, 8, 21, 18, 25, 29, 30, 31),
    gsSPVertex(&int_ike_k_mame01_v[53], 16, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 2, 3, 4, 2, 4, 0),
    gsSPNTriangles_5b(5, 6, 7, 8, 6, 9, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_k_mamehimo_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 178, 178, 178, 255),
    gsSPNTrianglesInit_5b(4, 10, 11, 12, 10, 12, 13, 13, 14, 15),
    gsSPNTriangles_5b(13, 15, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
