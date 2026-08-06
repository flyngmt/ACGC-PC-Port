#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 act_killer_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 act_killer_pal[] = {
#include "assets/act_killer_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 act_killer_tex_txt[0x200];
#else
u8 act_killer_tex_txt[] = {
#include "assets/act_killer_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx act_killer_v[0x190 / sizeof(Vtx)];
#else
Vtx act_killer_v[] = {
#include "assets/act_killer_v.inc"
};
#endif

Gfx act_killer_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_killer_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_killer_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(act_killer_v, 25, 0),
    gsSPNTrianglesInit_5b(34, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 4, 10, 11, 4, 11, 5, 12, 8, 7),
    gsSPNTriangles_5b(10, 13, 14, 10, 14, 11, 15, 8, 12, 2, 16, 17),
    gsSPNTriangles_5b(13, 18, 19, 13, 19, 14, 20, 8, 15, 18, 21, 22),
    gsSPNTriangles_5b(18, 22, 19, 23, 8, 20, 21, 3, 6, 21, 6, 22),
    gsSPNTriangles_5b(9, 8, 23, 17, 24, 2, 2, 24, 0, 23, 22, 6),
    gsSPNTriangles_5b(23, 6, 9, 20, 19, 22, 20, 22, 23, 15, 14, 19),
    gsSPNTriangles_5b(15, 19, 20, 12, 11, 14, 12, 14, 15, 7, 5, 11),
    gsSPNTriangles_5b(7, 11, 12, 9, 6, 5, 9, 5, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};
