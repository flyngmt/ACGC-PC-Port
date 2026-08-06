#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_ike_jny_sirser201_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_sirser02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_ike_jny_sirser02_pal[] = {
#include "assets/int_ike_jny_sirser02_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_sirser2face_tex_txt[0x200];
#else
u8 int_ike_jny_sirser2face_tex_txt[] = {
#include "assets/int_ike_jny_sirser2face_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_sirser2ear_tex_txt[0x80];
#else
u8 int_ike_jny_sirser2ear_tex_txt[] = {
#include "assets/int_ike_jny_sirser2ear_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_sirser2head_tex_txt[0x100];
#else
u8 int_ike_jny_sirser2head_tex_txt[] = {
#include "assets/int_ike_jny_sirser2head_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_sirser2hair_tex_txt[0x100];
#else
u8 int_ike_jny_sirser2hair_tex_txt[] = {
#include "assets/int_ike_jny_sirser2hair_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_sirser2foot_tex_txt[0x80];
#else
u8 int_ike_jny_sirser2foot_tex_txt[] = {
#include "assets/int_ike_jny_sirser2foot_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_sirser2tail_tex_txt[0x100];
#else
u8 int_ike_jny_sirser2tail_tex_txt[] = {
#include "assets/int_ike_jny_sirser2tail_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
u8 int_ike_jny_sirser2foot2_tex_txt[0x80];
#else
u8 int_ike_jny_sirser2foot2_tex_txt[] = {
#include "assets/int_ike_jny_sirser2foot2_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_ike_jny_sirser201_v[0x570 / sizeof(Vtx)];
#else
Vtx int_ike_jny_sirser201_v[] = {
#include "assets/int_ike_jny_sirser201_v.inc"
};
#endif

Gfx int_ike_jny_sirser201_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_jny_sirser02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_ike_jny_sirser2face_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_ike_jny_sirser201_v, 22, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 0, 1, 5, 6),
    gsSPNTriangles_5b(7, 0, 4, 8, 9, 10, 10, 5, 1, 6, 2, 1),
    gsSPNTriangles_5b(0, 2, 3, 7, 11, 8, 8, 10, 7, 5, 10, 9),
    gsSPNTriangles_5b(11, 7, 4, 1, 0, 7, 1, 7, 10, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_jny_sirser2ear_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 12, 13, 14, 14, 15, 12, 16, 17, 18),
    gsSPNTriangles_5b(14, 13, 19, 18, 20, 16, 21, 20, 18, 18, 17, 21),
    gsSPNTriangles_5b(19, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_jny_sirser2head_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&int_ike_jny_sirser201_v[22], 27, 0),
    gsSPNTrianglesInit_5b(11, 0, 1, 2, 3, 2, 1, 4, 1, 5),
    gsSPNTriangles_5b(5, 1, 0, 6, 0, 2, 6, 2, 7, 0, 6, 5),
    gsSPNTriangles_5b(8, 3, 1, 2, 3, 9, 5, 10, 4, 7, 11, 6),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_ike_jny_sirser2hair_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 60),
    gsSPNTrianglesInit_5b(13, 12, 13, 14, 15, 16, 17, 15, 17, 18),
    gsSPNTriangles_5b(19, 20, 21, 22, 23, 19, 20, 14, 24, 20, 24, 25),
    gsSPNTriangles_5b(16, 15, 12, 14, 16, 12, 25, 21, 20, 14, 13, 24),
    gsSPNTriangles_5b(19, 21, 26, 19, 26, 22, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_jny_sirser2foot_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
    gsSPVertex(&int_ike_jny_sirser201_v[49], 28, 0),
    gsSPNTrianglesInit_5b(23, 0, 1, 2, 3, 1, 0, 4, 5, 3),
    gsSPNTriangles_5b(6, 4, 3, 7, 8, 9, 3, 0, 6, 8, 7, 10),
    gsSPNTriangles_5b(1, 3, 5, 10, 7, 2, 8, 10, 11, 12, 5, 4),
    gsSPNTriangles_5b(10, 13, 11, 12, 14, 5, 7, 15, 0, 4, 6, 12),
    gsSPNTriangles_5b(10, 16, 17, 18, 19, 5, 5, 14, 18, 17, 13, 10),
    gsSPNTriangles_5b(2, 16, 10, 2, 7, 0, 5, 19, 1, 11, 9, 8),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_ike_jny_sirser2tail_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(10, 20, 21, 22, 23, 24, 22, 22, 25, 23),
    gsSPNTriangles_5b(20, 24, 26, 25, 21, 27, 20, 27, 21, 22, 24, 20),
    gsSPNTriangles_5b(26, 27, 20, 26, 24, 23, 22, 21, 25, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_jny_sirser2foot2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_ike_jny_sirser201_v[77], 10, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 2, 6, 0),
    gsSPNTriangles_5b(5, 4, 7, 5, 8, 3, 9, 1, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
