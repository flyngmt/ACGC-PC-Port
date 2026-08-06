#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_jny_ningyo01_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_ningyo01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_ningyo01_pal[] = {
#include "assets/int_ike_jny_ningyo01_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_ningyobody2_tex_txt[0x200];
#else
u8 int_ike_jny_ningyobody2_tex_txt[] = {
#include "assets/int_ike_jny_ningyobody2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_ningyoface_tex_txt[0x200];
#else
u8 int_ike_jny_ningyoface_tex_txt[] = {
#include "assets/int_ike_jny_ningyoface_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_ningyobody_tex_txt[0x200];
#else
u8 int_ike_jny_ningyobody_tex_txt[] = {
#include "assets/int_ike_jny_ningyobody_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_ningyoleg1_tex_txt[0x200];
#else
u8 int_ike_jny_ningyoleg1_tex_txt[] = {
#include "assets/int_ike_jny_ningyoleg1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_ningyohand_tex_txt[0x100];
#else
u8 int_ike_jny_ningyohand_tex_txt[] = {
#include "assets/int_ike_jny_ningyohand_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_jny_ningyo01_v[0x5B0 / sizeof(Vtx)];
#else
Vtx int_ike_jny_ningyo01_v[] = {
#include "assets/int_ike_jny_ningyo01_v.inc"
};
#endif

Gfx int_ike_jny_ningyo01_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_ningyo01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_jny_ningyobody2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_jny_ningyo01_v, 27, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 1, 5, 6, 4),
    gsSPNTriangles_5b(7, 2, 6, 0, 2, 7, 4, 6, 8, 2, 1, 8),
    gsSPNTriangles_5b(8, 6, 2, 8, 1, 4, 4, 3, 5, 6, 5, 7),
    gsSPNTriangles_5b(0, 9, 3, 7, 9, 0, 3, 1, 0, 0, 0, 0),
    gsSPNTrianglesInit_5b(18, 10, 11, 12, 13, 14, 12, 15, 14, 16),
    gsSPNTriangles_5b(16, 14, 13, 17, 18, 19, 20, 19, 18, 13, 21, 16),
    gsSPNTriangles_5b(21, 22, 23, 21, 13, 19, 15, 16, 24, 18, 25, 20),
    gsSPNTriangles_5b(19, 20, 22, 21, 23, 26, 19, 22, 21, 17, 19, 13),
    gsSPNTriangles_5b(13, 12, 17, 14, 15, 10, 12, 14, 10, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_jny_ningyoface_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_jny_ningyo01_v[27], 21, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 0, 5, 6, 7),
    gsSPNTriangles_5b(2, 8, 6, 6, 0, 2, 9, 1, 0, 6, 8, 7),
    gsSPNTriangles_5b(3, 0, 6, 6, 5, 3, 9, 0, 4, 0, 0, 0),
    gsSPNTrianglesInit_5b(12, 10, 11, 12, 12, 13, 14, 15, 16, 17),
    gsSPNTriangles_5b(14, 10, 12, 14, 15, 10, 15, 18, 16, 17, 16, 11),
    gsSPNTriangles_5b(19, 18, 15, 16, 18, 20, 20, 11, 16, 11, 10, 17),
    gsSPNTriangles_5b(17, 10, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_jny_ningyobody_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_jny_ningyo01_v[48], 28, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 1, 0, 3, 4, 3, 5),
    gsSPNTriangles_5b(0, 2, 6, 7, 3, 0, 5, 8, 4, 3, 4, 1),
    gsSPNTriangles_5b(9, 7, 0, 7, 9, 10, 6, 9, 0, 11, 2, 1),
    gsSPNTriangles_5b(2, 12, 6, 12, 2, 11, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_jny_ningyoleg1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(15, 13, 14, 15, 14, 13, 16, 16, 17, 14),
    gsSPNTriangles_5b(18, 17, 19, 17, 16, 19, 20, 15, 17, 18, 21, 17),
    gsSPNTriangles_5b(19, 22, 23, 19, 23, 18, 15, 24, 13, 15, 20, 25),
    gsSPNTriangles_5b(15, 14, 17, 17, 26, 20, 25, 24, 15, 17, 27, 26),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_jny_ningyohand_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_jny_ningyo01_v[76], 15, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(2, 9, 6, 2, 8, 3, 2, 3, 0, 8, 2, 6),
    gsSPNTriangles_5b(0, 3, 10, 11, 12, 3, 11, 3, 8, 13, 11, 8),
    gsSPNTriangles_5b(10, 14, 0, 8, 7, 13, 5, 10, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
