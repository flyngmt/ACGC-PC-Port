#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iid_snow_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iid_snow_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iid_snow_pal[] = {
#include "assets/int_iid_snow_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_snow_ashiue_tex[0x80];
#else
u8 int_iid_snow_ashiue_tex[] = {
#include "assets/int_iid_snow_ashiue_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_snow_ashiyoko_tex[0x100];
#else
u8 int_iid_snow_ashiyoko_tex[] = {
#include "assets/int_iid_snow_ashiyoko_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_snow_ashimae_tex[0x80];
#else
u8 int_iid_snow_ashimae_tex[] = {
#include "assets/int_iid_snow_ashimae_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_snow_ashisoko_tex[0x100];
#else
u8 int_iid_snow_ashisoko_tex[] = {
#include "assets/int_iid_snow_ashisoko_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_snow_ashiback_tex[0x80];
#else
u8 int_iid_snow_ashiback_tex[] = {
#include "assets/int_iid_snow_ashiback_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_snow_bordue_tex[0x100];
#else
u8 int_iid_snow_bordue_tex[] = {
#include "assets/int_iid_snow_bordue_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_snow_bordshita_tex[0x80];
#else
u8 int_iid_snow_bordshita_tex[] = {
#include "assets/int_iid_snow_bordshita_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_snow_bordyoko_tex[0x20];
#else
u8 int_iid_snow_bordyoko_tex[] = {
#include "assets/int_iid_snow_bordyoko_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_snow_bordkakato_tex[0x100];
#else
u8 int_iid_snow_bordkakato_tex[] = {
#include "assets/int_iid_snow_bordkakato_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_snow_bordura_tex[0x80];
#else
u8 int_iid_snow_bordura_tex[] = {
#include "assets/int_iid_snow_bordura_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_snow_bordana_tex[0x20];
#else
u8 int_iid_snow_bordana_tex[] = {
#include "assets/int_iid_snow_bordana_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_snow_bordpin_tex[0x20];
#else
u8 int_iid_snow_bordpin_tex[] = {
#include "assets/int_iid_snow_bordpin_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_snow_bordtate_tex[0x20];
#else
u8 int_iid_snow_bordtate_tex[] = {
#include "assets/int_iid_snow_bordtate_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iid_snow_v[0x18D0 / sizeof(Vtx)];
#else
Vtx int_iid_snow_v[] = {
#include "assets/int_iid_snow_v.inc"
};
#endif

Gfx int_iid_snow_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iid_snow_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_iid_snow_bordtate_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iid_snow_v, 32, 0),
    gsSPNTrianglesInit_5b(19, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 0, 7, 8, 7, 9, 1, 10, 11),
    gsSPNTriangles_5b(1, 11, 12, 13, 14, 15, 13, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(17, 19, 20, 21, 22, 23, 21, 23, 24, 25, 26, 16),
    gsSPNTriangles_5b(25, 16, 23, 22, 17, 27, 22, 27, 28, 29, 30, 31),
    gsSPVertex(&int_iid_snow_v[32], 32, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 11, 12, 13, 11, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 15, 17, 18, 19, 20, 21, 19, 21, 22),
    gsSPNTriangles_5b(2, 1, 23, 2, 23, 24, 25, 26, 27, 25, 27, 28),
    gsSPNTriangles_5b(29, 30, 16, 29, 16, 15, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_iid_snow_v[63], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_iid_snow_v[95], 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_iid_snow_v[127], 32, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 15, 14, 28),
    gsSPNTriangles_5b(15, 28, 29, 21, 30, 31, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_iid_snow_v[159], 31, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 11, 12, 13, 11, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 15, 17, 18, 19, 20, 21, 19, 21, 22),
    gsSPNTriangles_5b(23, 24, 25, 23, 25, 26, 27, 28, 29, 27, 29, 30),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_iid_snow_bordpin_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iid_snow_v[190], 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_iid_snow_bordana_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iid_snow_bordura_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iid_snow_v[198], 24, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 4, 7, 8, 4, 8, 9, 4, 9, 10),
    gsSPNTriangles_5b(10, 11, 12, 10, 12, 13, 10, 13, 14, 10, 14, 4),
    gsSPNTriangles_5b(15, 16, 0, 15, 0, 3, 15, 3, 17, 15, 17, 18),
    gsSPNTriangles_5b(18, 19, 20, 18, 20, 21, 18, 21, 22, 18, 22, 23),
    gsSPNTriangles_5b(18, 23, 15, 1, 13, 12, 1, 12, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_iid_snow_bordkakato_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iid_snow_v[222], 25, 0),
    gsSPNTrianglesInit_5b(25, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 6, 7, 8, 6, 8, 9, 6, 9, 10),
    gsSPNTriangles_5b(6, 10, 11, 10, 12, 13, 10, 13, 14, 10, 14, 15),
    gsSPNTriangles_5b(10, 15, 5, 10, 5, 4, 10, 4, 11, 12, 16, 17),
    gsSPNTriangles_5b(12, 17, 13, 2, 18, 19, 2, 19, 20, 2, 20, 21),
    gsSPNTriangles_5b(2, 21, 22, 2, 22, 7, 2, 7, 6, 2, 6, 3),
    gsSPNTriangles_5b(23, 24, 15, 23, 15, 14, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_iid_snow_bordyoko_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iid_snow_v[247], 32, 0),
    gsSPNTrianglesInit_5b(25, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 9, 10, 6, 9, 6, 5),
    gsSPNTriangles_5b(11, 12, 1, 11, 1, 0, 13, 14, 12, 13, 12, 11),
    gsSPNTriangles_5b(4, 3, 15, 4, 15, 16, 17, 18, 19, 17, 19, 20),
    gsSPNTriangles_5b(16, 15, 18, 16, 18, 17, 21, 22, 23, 21, 23, 24),
    gsSPNTriangles_5b(25, 26, 22, 25, 22, 21, 24, 23, 27, 24, 27, 28),
    gsSPNTriangles_5b(29, 30, 26, 29, 26, 25, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_iid_snow_v[278], 30, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 6, 7, 5, 6, 5, 4, 8, 9, 7),
    gsSPNTriangles_5b(8, 7, 6, 10, 11, 9, 10, 9, 8, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 17),
    gsSPNTriangles_5b(20, 17, 16, 22, 23, 21, 22, 21, 20, 24, 25, 23),
    gsSPNTriangles_5b(24, 23, 22, 26, 27, 25, 26, 25, 24, 28, 29, 27),
    gsSPNTriangles_5b(28, 27, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iid_snow_bordshita_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iid_snow_v[308], 23, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_iid_snow_bordue_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(17, 4, 5, 6, 4, 6, 7, 4, 7, 8),
    gsSPNTriangles_5b(4, 8, 9, 10, 11, 12, 10, 12, 13, 9, 14, 15),
    gsSPNTriangles_5b(9, 15, 16, 9, 16, 17, 9, 17, 18, 9, 18, 4),
    gsSPNTriangles_5b(6, 19, 20, 6, 20, 13, 6, 13, 12, 6, 12, 7),
    gsSPNTriangles_5b(19, 21, 22, 19, 22, 20, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_iid_snowT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iid_snow_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iid_snow_ashiback_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iid_snow_v[331], 24, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 6, 7, 8, 6, 8, 9, 9, 8, 10),
    gsSPNTriangles_5b(9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iid_snow_ashisoko_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 12, 13, 14, 12, 14, 15, 12, 15, 16),
    gsSPNTriangles_5b(12, 16, 17, 18, 19, 20, 18, 20, 21, 18, 21, 22),
    gsSPNTriangles_5b(18, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iid_snow_ashimae_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iid_snow_v[355], 28, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 6, 7, 8, 6, 8, 9, 10, 11, 7),
    gsSPNTriangles_5b(10, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_iid_snow_ashiyoko_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iid_snow_ashiue_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iid_snow_v[383], 14, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 6, 7, 8, 9, 7, 9, 10, 11, 12, 7),
    gsSPNTriangles_5b(11, 7, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
