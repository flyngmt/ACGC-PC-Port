#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_tak_shuttle_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_shuttle_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_shuttle_pal[] = {
#include "assets/int_tak_shuttle_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_shuttle_back[0x80];
#else
u8 int_tak_shuttle_back[] = {
#include "assets/int_tak_shuttle_back.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_shuttle_eg[0x80];
#else
u8 int_tak_shuttle_eg[] = {
#include "assets/int_tak_shuttle_eg.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_shuttle_fin[0x80];
#else
u8 int_tak_shuttle_fin[] = {
#include "assets/int_tak_shuttle_fin.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_shuttle_wing[0x200];
#else
u8 int_tak_shuttle_wing[] = {
#include "assets/int_tak_shuttle_wing.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_shuttle_face1[0x80];
#else
u8 int_tak_shuttle_face1[] = {
#include "assets/int_tak_shuttle_face1.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_shuttle_face2[0x80];
#else
u8 int_tak_shuttle_face2[] = {
#include "assets/int_tak_shuttle_face2.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_shuttle_face4[0x80];
#else
u8 int_tak_shuttle_face4[] = {
#include "assets/int_tak_shuttle_face4.inc"
};
#endif

#ifdef TARGET_PC
u8 int_tak_shuttle_body3[0x300];
#else
u8 int_tak_shuttle_body3[] = {
#include "assets/int_tak_shuttle_body3.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_tak_shuttle_v[0x430 / sizeof(Vtx)];
#else
Vtx int_tak_shuttle_v[] = {
#include "assets/int_tak_shuttle_v.inc"
};
#endif

Gfx int_tak_shuttle_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_shuttle_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_tak_shuttle_body3),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_tak_shuttle_v, 27, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 4, 3, 1, 5, 4),
    gsSPNTriangles_5b(4, 5, 6, 7, 4, 6, 8, 6, 9, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 1, 3, 2, 8, 7, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_shuttle_face4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(8, 10, 11, 12, 13, 11, 14, 13, 14, 15),
    gsSPNTriangles_5b(16, 13, 17, 10, 13, 16, 13, 15, 18, 15, 17, 18),
    gsSPNTriangles_5b(17, 13, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_shuttle_face2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 19, 20, 21, 19, 22, 20, 23, 24, 25),
    gsSPNTriangles_5b(26, 23, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_shuttle_face1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_tak_shuttle_v[27], 28, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 2, 3, 0, 2, 1, 4),
    gsSPNTriangles_5b(1, 5, 4, 5, 6, 4, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_shuttle_eg),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(9, 7, 8, 9, 10, 9, 11, 12, 11, 13),
    gsSPNTriangles_5b(14, 15, 16, 17, 18, 15, 19, 20, 18, 21, 22, 23),
    gsSPNTriangles_5b(24, 23, 25, 26, 25, 27, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_shuttle_back),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_shuttle_v[55], 5, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPEndDisplayList(),
};

Gfx int_tak_shuttle_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_tak_shuttle_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_tak_shuttle_wing),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_tak_shuttle_v[60], 7, 0),
    gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_tak_shuttle_fin),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 3, 4, 5, 5, 4, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};
