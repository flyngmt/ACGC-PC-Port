#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_iid_yuki_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_iid_yuki_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_iid_yuki_pal[] = {
#include "assets/int_iid_yuki_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_yuki_ha_tex[0x100];
#else
u8 int_iid_yuki_ha_tex[] = {
#include "assets/int_iid_yuki_ha_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_yuki_body_tex[0x400];
#else
u8 int_iid_yuki_body_tex[] = {
#include "assets/int_iid_yuki_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_yuki_eye_tex[0x20];
#else
u8 int_iid_yuki_eye_tex[] = {
#include "assets/int_iid_yuki_eye_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_yuki_bonyoko_tex[0x80];
#else
u8 int_iid_yuki_bonyoko_tex[] = {
#include "assets/int_iid_yuki_bonyoko_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_iid_yuki_bonue_tex[0x80];
#else
u8 int_iid_yuki_bonue_tex[] = {
#include "assets/int_iid_yuki_bonue_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_iid_yuki_v[0x4D0 / sizeof(Vtx)];
#else
Vtx int_iid_yuki_v[] = {
#include "assets/int_iid_yuki_v.inc"
};
#endif

Gfx int_iid_yuki_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iid_yuki_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iid_yuki_bonue_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_iid_yuki_v, 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 0, 3, 4),
    gsSPNTriangles_5b(0, 4, 5, 0, 5, 6, 0, 6, 7, 0, 7, 8),
    gsSPNTriangles_5b(0, 8, 9, 0, 9, 10, 0, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_iid_yuki_bonyoko_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_iid_yuki_v[12], 24, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 6, 7, 5, 6, 5, 4, 8, 9, 7),
    gsSPNTriangles_5b(8, 7, 6, 10, 11, 9, 10, 9, 8, 12, 13, 11),
    gsSPNTriangles_5b(12, 11, 10, 14, 15, 13, 14, 13, 12, 16, 17, 15),
    gsSPNTriangles_5b(16, 15, 14, 18, 19, 17, 18, 17, 16, 20, 21, 19),
    gsSPNTriangles_5b(20, 19, 18, 22, 23, 21, 22, 21, 20, 3, 2, 23),
    gsSPNTriangles_5b(3, 23, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_iid_yukiT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_iid_yuki_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, int_iid_yuki_eye_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iid_yuki_v[36], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_iid_yuki_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iid_yuki_v[44], 25, 0),
    gsSPNTrianglesInit_5b(40, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(5, 7, 0, 5, 0, 6, 7, 1, 0, 4, 8, 9),
    gsSPNTriangles_5b(4, 9, 5, 9, 10, 7, 9, 7, 5, 10, 1, 7),
    gsSPNTriangles_5b(8, 11, 12, 8, 12, 9, 12, 13, 10, 12, 10, 9),
    gsSPNTriangles_5b(13, 1, 10, 11, 14, 15, 11, 15, 12, 15, 16, 13),
    gsSPNTriangles_5b(15, 13, 12, 16, 1, 13, 14, 17, 18, 14, 18, 15),
    gsSPNTriangles_5b(18, 19, 16, 18, 16, 15, 19, 1, 16, 17, 20, 21),
    gsSPNTriangles_5b(17, 21, 18, 21, 22, 19, 21, 19, 18, 22, 1, 19),
    gsSPNTriangles_5b(20, 23, 24, 20, 24, 21, 24, 2, 22, 24, 22, 21),
    gsSPNTriangles_5b(2, 1, 22, 23, 3, 6, 23, 6, 24, 6, 0, 2),
    gsSPNTriangles_5b(6, 2, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_iid_yuki_ha_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_iid_yuki_v[69], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
