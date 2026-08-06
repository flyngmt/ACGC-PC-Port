#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_e_mikuji_2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_e_mikuji_2_pal[] = {
#include "assets/obj_e_mikuji_2_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_e_mikuji_1_pal[0x20 / sizeof(u16)];
#else
u16 obj_e_mikuji_1_pal[] = {
#include "assets/obj_e_mikuji_1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_mikuji_2[0x200];
#else
u8 obj_e_mikuji_2[] = {
#include "assets/obj_e_mikuji_2.inc"
};
#endif

#ifdef TARGET_PC
u8 obj_e_mikuji_1[0x800];
#else
u8 obj_e_mikuji_1[] = {
#include "assets/obj_e_mikuji_1.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_e_mikuji_v[0x330 / sizeof(Vtx)];
#else
Vtx obj_e_mikuji_v[] = {
#include "assets/obj_e_mikuji_v.inc"
};
#endif

Gfx obj_e_mikuji_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_mikuji_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_e_mikuji_1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_e_mikuji_v, 27, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 6, 7, 8, 6, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(11, 13, 12, 11, 14, 13, 11, 15, 14, 16, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 20, 22, 21, 19, 23, 20, 23, 24, 20),
    gsSPNTriangles_5b(24, 25, 20, 25, 22, 20, 24, 26, 25, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_mikuji_2_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_e_mikuji_2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_e_mikuji_v[27], 24, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
