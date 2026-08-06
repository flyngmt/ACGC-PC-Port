#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 crw_anrium1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 crw_anrium1_pal[] = {
#include "assets/crw_anrium1_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 crw_anrium1_tex_txt[0x200];
#else
u8 crw_anrium1_tex_txt[] = {
#include "assets/crw_anrium1_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 crw_anrium2_tex_txt[0x80];
#else
u8 crw_anrium2_tex_txt[] = {
#include "assets/crw_anrium2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx crw_anrium1_v[0x1E0 / sizeof(Vtx)];
#else
Vtx crw_anrium1_v[] = {
#include "assets/crw_anrium1_v.inc"
};
#endif

Gfx crw_anrium1_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, crw_anrium1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, crw_anrium1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(crw_anrium1_v, 30, 0),
    gsSPNTrianglesInit_5b(30, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 2, 1, 13, 12, 11, 13),
    gsSPNTriangles_5b(13, 1, 14, 13, 11, 9, 13, 15, 12, 12, 15, 10),
    gsSPNTriangles_5b(3, 15, 13, 16, 5, 4, 16, 4, 14, 13, 8, 2),
    gsSPNTriangles_5b(2, 8, 0, 9, 8, 13, 9, 11, 7, 17, 0, 8),
    gsSPNTriangles_5b(11, 10, 18, 1, 0, 19, 20, 10, 15, 18, 7, 11),
    gsSPNTriangles_5b(8, 7, 17, 6, 20, 15, 6, 15, 3, 13, 4, 3),
    gsSPNTriangles_5b(14, 1, 19, 14, 19, 16, 14, 4, 13, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, crw_anrium2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(14, 21, 22, 23, 24, 25, 26, 27, 26, 25),
    gsSPNTriangles_5b(28, 27, 25, 29, 26, 27, 23, 22, 28, 22, 21, 29),
    gsSPNTriangles_5b(21, 23, 24, 25, 24, 28, 28, 24, 23, 24, 29, 21),
    gsSPNTriangles_5b(27, 28, 29, 29, 28, 22, 26, 29, 24, 0, 0, 0),
    gsSPEndDisplayList(),
};
