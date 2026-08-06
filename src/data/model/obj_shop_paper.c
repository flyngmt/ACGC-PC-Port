#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop_paper_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop_paper_pal[] = {
#include "assets/obj_shop_paper_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u8 obj_shop_paper_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) u8 obj_shop_paper_tex[] = {
#include "assets/obj_shop_paper_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx obj_shop_paper_v[0x230 / sizeof(Vtx)];
#else
Vtx obj_shop_paper_v[] = {
#include "assets/obj_shop_paper_v.inc"
};
#endif

Gfx obj_paper_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_paper_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, obj_shop_paper_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPEndDisplayList(),
};

Gfx obj_paper_gfx_model[] = {
    gsSPVertex(obj_shop_paper_v, 32, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 5, 8, 6, 8, 9, 6, 8, 10, 9),
    gsSPNTriangles_5b(8, 11, 10, 11, 12, 10, 13, 14, 15, 13, 16, 14),
    gsSPNTriangles_5b(16, 17, 14, 17, 15, 14, 18, 19, 20, 18, 20, 21),
    gsSPNTriangles_5b(22, 18, 21, 23, 24, 25, 23, 25, 26, 27, 28, 29),
    gsSPNTriangles_5b(27, 29, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_shop_paper_v[31], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
