#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_kon_snowfreezer_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 int_kon_snowtansu_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 int_kon_snowtansu_tex_pal[] = {
#include "assets/int_kon_snowfreezer/int_kon_snowtansu_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowfreezer01_tex[0x300];
#else
u8 int_kon_snowfreezer01_tex[] = {
#include "assets/int_kon_snowfreezer01_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowfreezer02_tex[0x180];
#else
u8 int_kon_snowfreezer02_tex[] = {
#include "assets/int_kon_snowfreezer02_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowfreezer04_tex[0x100];
#else
u8 int_kon_snowfreezer04_tex[] = {
#include "assets/int_kon_snowfreezer04_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowfreezer03_tex[0x100];
#else
u8 int_kon_snowfreezer03_tex[] = {
#include "assets/int_kon_snowfreezer03_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowfreezer05_tex[0x80];
#else
u8 int_kon_snowfreezer05_tex[] = {
#include "assets/int_kon_snowfreezer05_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_kon_snowfreezer06_tex[0x80];
#else
u8 int_kon_snowfreezer06_tex[] = {
#include "assets/int_kon_snowfreezer06_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_kon_snowfreezer_v[0x360 / sizeof(Vtx)];
#else
Vtx int_kon_snowfreezer_v[] = {
#include "assets/int_kon_snowfreezer_v.inc"
};
#endif

Gfx int_kon_snowfreezer01_body_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_snowtansu_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_snowfreezer05_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_snowfreezer_v, 25, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 0, 5, 6, 7),
    gsSPNTriangles_5b(7, 8, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_kon_snowfreezer03_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(14, 9, 10, 11, 10, 12, 13, 12, 14, 13),
    gsSPNTriangles_5b(15, 16, 17, 18, 15, 17, 19, 18, 20, 14, 19, 20),
    gsSPNTriangles_5b(20, 21, 14, 17, 20, 18, 16, 22, 17, 14, 21, 13),
    gsSPNTriangles_5b(13, 11, 10, 11, 23, 24, 24, 9, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_kon_snowfreezer04_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_kon_snowfreezer_v[25], 16, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 1, 3, 5, 4),
    gsSPNTriangles_5b(6, 7, 8, 6, 8, 9, 10, 9, 11, 10, 11, 12),
    gsSPNTriangles_5b(12, 13, 10, 9, 10, 6, 6, 14, 7, 3, 15, 5),
    gsSPNTriangles_5b(1, 0, 3, 7, 14, 0, 0, 2, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_kon_snowfreezer01_bodyT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_snowtansu_tex_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_snowfreezer06_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_kon_snowfreezer_v[41], 13, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_kon_snowfreezer02_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_kon_snowfreezer01_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 9, 11, 10, 8, 10, 12),
    gsSPNTriangles_5b(11, 12, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_kon_snowfreezer_c(void) {
    pc_load_asset("assets/int_kon_snowfreezer/int_kon_snowtansu_tex_pal.bin", int_kon_snowtansu_tex_pal, 0x20, 0xB8EE40, 0, 1);
}
#endif
