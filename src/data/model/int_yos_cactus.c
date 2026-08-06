#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_yos_cactus_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_yos_cactus_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_yos_cactus_pal[] = {
#include "assets/int_yos_cactus_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_cactus_bou_tex_txt[0x400];
#else
u8 int_yos_cactus_bou_tex_txt[] = {
#include "assets/int_yos_cactus_bou_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_yos_cactus_v[0x380 / sizeof(Vtx)];
#else
Vtx int_yos_cactus_v[] = {
#include "assets/int_yos_cactus_v.inc"
};
#endif

Gfx int_yos_cactus_obj_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yos_cactus_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, int_yos_cactus_bou_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_yos_cactus_v, 32, 0),
    gsSPNTrianglesInit_5b(25, 0, 1, 2, 1, 0, 3, 4, 0, 2),
    gsSPNTriangles_5b(0, 4, 3, 1, 5, 6, 5, 1, 7, 5, 4, 6),
    gsSPNTriangles_5b(4, 5, 7, 8, 9, 10, 9, 8, 11, 12, 13, 14),
    gsSPNTriangles_5b(13, 12, 15, 9, 16, 17, 16, 9, 18, 19, 12, 20),
    gsSPNTriangles_5b(12, 19, 21, 10, 14, 13, 11, 8, 13, 17, 16, 19),
    gsSPNTriangles_5b(18, 21, 19, 22, 23, 24, 23, 22, 25, 26, 27, 28),
    gsSPNTriangles_5b(27, 26, 29, 23, 30, 31, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_yos_cactus_v[32], 24, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 4, 3, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 7, 11, 0, 3, 5, 0, 2, 6),
    gsSPNTriangles_5b(6, 3, 0, 11, 12, 10, 5, 13, 0, 9, 11, 7),
    gsSPNTriangles_5b(14, 15, 16, 17, 18, 19, 17, 20, 21, 14, 22, 23),
    gsSPEndDisplayList(),
};
