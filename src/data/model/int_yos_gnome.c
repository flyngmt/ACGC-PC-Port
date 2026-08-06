#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_yos_gnome_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_yos_gnome_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_yos_gnome_pal[] = {
#include "assets/int_yos_gnome_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_yos_gnome_all_tex_txt[0x800];
#else
u8 int_yos_gnome_all_tex_txt[] = {
#include "assets/int_yos_gnome_all_tex_txt.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_yos_gnome_v[0x480 / sizeof(Vtx)];
#else
Vtx int_yos_gnome_v[] = {
#include "assets/int_yos_gnome_v.inc"
};
#endif

Gfx int_yos_gnome_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_yos_gnome_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, int_yos_gnome_all_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_yos_gnome_v, 31, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 2, 6, 0),
    gsSPNTriangles_5b(5, 7, 8, 8, 3, 5, 0, 9, 1, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 10, 11, 12, 13, 12, 11, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 14, 15, 16, 17, 16, 15, 17, 15, 18),
    gsSPNTriangles_5b(14, 18, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 19, 20, 21, 20, 19, 22, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(5, 23, 24, 25, 26, 25, 24, 26, 24, 27),
    gsSPNTriangles_5b(23, 27, 24, 28, 29, 30, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_yos_gnome_v[31], 26, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 2, 1, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 4, 5, 6, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 7, 8, 9, 10, 7, 9, 9, 8, 11),
    gsSPNTriangles_5b(11, 10, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(5, 12, 13, 14, 15, 13, 12, 16, 12, 14),
    gsSPNTriangles_5b(12, 16, 17, 12, 17, 15, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(1, 18, 19, 20, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 21, 22, 23, 22, 21, 24, 25, 22, 24),
    gsSPNTriangles_5b(22, 25, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_yos_gnome_v[57], 15, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 4, 3, 6),
    gsSPNTriangles_5b(7, 8, 9, 8, 7, 10, 11, 12, 13, 14, 13, 12),
    gsSPEndDisplayList(),
};
