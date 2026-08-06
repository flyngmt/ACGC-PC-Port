#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_nog_dump_v[];
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_dump_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_dump_pal[] = {
#include "assets/int_nog_dump_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 obj_item_trash_pal[0x20 / sizeof(u16)];
#else
static u16 obj_item_trash_pal[] = {
#include "assets/int_nog_dump/obj_item_trash_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_dump_body_tex[0x200];
#else
u8 int_nog_dump_body_tex[] = {
#include "assets/int_nog_dump_body_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_dump_grass_tex[0x200];
#else
u8 int_nog_dump_grass_tex[] = {
#include "assets/int_nog_dump_grass_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 int_nog_dump_wire_tex[0x100];
#else
u8 int_nog_dump_wire_tex[] = {
#include "assets/int_nog_dump_wire_tex.inc"
};
#endif

#ifdef TARGET_PC
Vtx int_nog_dump_v[0xDC0 / sizeof(Vtx)];
#else
Vtx int_nog_dump_v[] = {
#include "assets/int_nog_dump_v.inc"
};
#endif

Gfx int_nog_dump_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_dump_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_nog_dump_grass_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_nog_dump_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_nog_dumpT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_item_trash_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_nog_dump_wire_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_dump_v[4], 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 3, 2, 4),
    gsSPNTriangles_5b(3, 4, 5, 6, 7, 1, 6, 1, 0, 8, 7, 6),
    gsSPNTriangles_5b(8, 6, 9, 5, 4, 10, 5, 10, 11, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_dump_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, int_nog_dump_body_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_nog_dump_v[16], 32, 0),
    gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 13),
    gsSPNTriangles_5b(20, 13, 12, 19, 18, 21, 19, 21, 20, 22, 19, 20),
    gsSPNTriangles_5b(22, 20, 23, 24, 25, 26, 24, 26, 27, 25, 28, 29),
    gsSPNTriangles_5b(25, 29, 26, 26, 29, 30, 26, 30, 31, 0, 0, 0),
    gsSPVertex(&int_nog_dump_v[48], 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 9, 16, 9, 8, 15, 14, 17),
    gsSPNTriangles_5b(15, 17, 16, 18, 15, 16, 18, 16, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 21, 24, 25, 21, 25, 22, 22, 25, 26),
    gsSPNTriangles_5b(22, 26, 27, 28, 29, 24, 28, 24, 21, 27, 26, 30),
    gsSPNTriangles_5b(27, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_dump_v[80], 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 1, 8, 1, 0, 7, 6, 9),
    gsSPNTriangles_5b(7, 9, 8, 10, 7, 8, 10, 8, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 13, 16, 17, 13, 17, 14, 14, 17, 18),
    gsSPNTriangles_5b(14, 18, 19, 20, 21, 16, 20, 16, 13, 19, 18, 22),
    gsSPNTriangles_5b(19, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_dump_v[112], 32, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 6, 4, 0, 6, 0, 7, 8, 9, 10),
    gsSPNTriangles_5b(8, 10, 11, 9, 12, 13, 9, 13, 10, 10, 13, 14),
    gsSPNTriangles_5b(10, 14, 15, 16, 17, 12, 16, 12, 9, 15, 14, 18),
    gsSPNTriangles_5b(15, 18, 19, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 28, 29, 21, 28, 21, 20, 27, 26, 29),
    gsSPNTriangles_5b(27, 29, 28, 30, 27, 28, 30, 28, 31, 0, 0, 0),
    gsSPVertex(&int_nog_dump_v[144], 32, 0),
    gsSPNTrianglesInit_5b(26, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 1, 8, 1, 0, 7, 6, 9),
    gsSPNTriangles_5b(7, 9, 8, 10, 7, 8, 10, 8, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 13, 16, 17, 13, 17, 14, 14, 17, 18),
    gsSPNTriangles_5b(14, 18, 19, 20, 21, 16, 20, 16, 13, 19, 18, 22),
    gsSPNTriangles_5b(19, 22, 23, 24, 25, 26, 24, 26, 27, 25, 28, 29),
    gsSPNTriangles_5b(25, 29, 26, 26, 29, 30, 26, 30, 31, 0, 0, 0),
    gsSPVertex(&int_nog_dump_v[176], 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 9, 16, 9, 8, 15, 14, 17),
    gsSPNTriangles_5b(15, 17, 16, 18, 15, 16, 18, 16, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 21, 24, 25, 21, 25, 22, 22, 25, 26),
    gsSPNTriangles_5b(22, 26, 27, 28, 29, 24, 28, 24, 21, 27, 26, 30),
    gsSPNTriangles_5b(27, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&int_nog_dump_v[208], 12, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 2, 5, 6, 2, 6, 7, 8, 9, 4),
    gsSPNTriangles_5b(8, 4, 1, 7, 6, 10, 7, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_model_int_nog_dump_c(void) {
    pc_load_asset("assets/int_nog_dump/obj_item_trash_pal.bin", obj_item_trash_pal, 0x20, 0xBD4080, 0, 1);
}
#endif
