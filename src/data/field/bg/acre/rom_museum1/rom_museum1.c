#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_museum1_mado_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_museum1_mado_pal[] = {
#include "assets/field/bg/rom_museum1_mado_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_museum1_step_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_museum1_step_pal[] = {
#include "assets/field/bg/rom_museum1_step_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_museum1_floor_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_museum1_floor_pal[] = {
#include "assets/field/bg/rom_museum1_floor_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_museum1_wall_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_museum1_wall_pal[] = {
#include "assets/field/bg/rom_museum1_wall_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_mado1_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_mado1_tex[] = {
#include "assets/field/bg/rom_museum1_mado1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_step1_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_step1_tex[] = {
#include "assets/field/bg/rom_museum1_step1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_step2_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_step2_tex[] = {
#include "assets/field/bg/rom_museum1_step2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_floorA_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_floorA_tex[] = {
#include "assets/field/bg/rom_museum1_floorA_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_floorB_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_floorB_tex[] = {
#include "assets/field/bg/rom_museum1_floorB_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_mado2_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_mado2_tex[] = {
#include "assets/field/bg/rom_museum1_mado2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_sign1_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_sign1_tex[] = {
#include "assets/field/bg/rom_museum1_sign1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_wallA_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_wallA_tex[] = {
#include "assets/field/bg/rom_museum1_wallA_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_wallB_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_wallB_tex[] = {
#include "assets/field/bg/rom_museum1_wallB_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_sign2_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_sign2_tex[] = {
#include "assets/field/bg/rom_museum1_sign2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_sign3_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_sign3_tex[] = {
#include "assets/field/bg/rom_museum1_sign3_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_sign4_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum1_sign4_tex[] = {
#include "assets/field/bg/rom_museum1_sign4_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx rom_museum1_v[0x12C0 / sizeof(Vtx)];
#else
static Vtx rom_museum1_v[] = {
#include "assets/field/bg/rom_museum1_v.inc"
};
#endif

extern Gfx rom_museum1_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 1, 0, PRIM_LOD_FRAC, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum1_mado_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_mado2_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_museum1_v[268], 16, 0),
    gsSPNTriangles(8,       // tri count
                   0, 1, 2, // tri0
                   3, 4, 5, // tri1
                   3, 5, 6  // tri2
                   ),
    gsSPNTriangles_5b(0, 2, 7,    // tri0
                      8, 9, 10,   // tri1
                      11, 12, 13, // tri2
                      8, 10, 14   // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 15, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_mado1_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum1_v[284], 16, 0),
    gsSPNTriangles(8,       // tri count
                   0, 1, 2, // tri0
                   1, 3, 2, // tri1
                   4, 5, 6  // tri2
                   ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      10, 11, 12, // tri1
                      13, 4, 6,   // tri2
                      14, 7, 9    // tri3
                      ),
    gsSPNTriangles_5b(11, 15, 12, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx rom_museum1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_museum1_v[0], 16, 0),
    gsSPNTriangles(8,       // tri count
                   0, 1, 2, // tri0
                   0, 3, 1, // tri1
                   4, 5, 6  // tri2
                   ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      8, 9, 10,  // tri1
                      11, 8, 10, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 15, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum1_step_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_sign4_tex, G_IM_FMT_CI, 64, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum1_v[16], 20, 0),
    gsSPNTriangles(3,       // tri count
                   0, 1, 2, // tri0
                   0, 3, 4, // tri1
                   0, 2, 3  // tri2
                   ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_sign3_tex, G_IM_FMT_CI, 64, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTriangles(3,       // tri count
                   5, 6, 7, // tri0
                   7, 8, 9, // tri1
                   5, 7, 9  // tri2
                   ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_sign2_tex, G_IM_FMT_CI, 64, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTriangles(3,          // tri count
                   10, 11, 12, // tri0
                   12, 13, 10, // tri1
                   10, 14, 11  // tri2
                   ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_sign1_tex, G_IM_FMT_CI, 64, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTriangles(3,          // tri count
                   15, 16, 17, // tri0
                   17, 18, 15, // tri1
                   15, 19, 16  // tri2
                   ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_step2_tex, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_museum1_v[36], 27, 0),
    gsSPNTriangles(14,      // tri count
                   0, 1, 2, // tri0
                   2, 3, 4, // tri1
                   4, 5, 2  // tri2
                   ),
    gsSPNTriangles_5b(5, 0, 2, // tri0
                      6, 7, 8, // tri1
                      6, 9, 7, // tri2
                      8, 10, 6 // tri3
                      ),
    gsSPNTriangles_5b(6, 11, 9,   // tri0
                      12, 13, 14, // tri1
                      15, 16, 12, // tri2
                      12, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      19, 20, 17, // tri1
                      17, 21, 18, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_step1_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTriangles(3,          // tri count
                   22, 23, 24, // tri0
                   24, 25, 22, // tri1
                   22, 26, 23  // tri2
                   ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum1_wall_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_wallA_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum1_v[63], 32, 0),
    gsSPNTriangles(24,      // tri count
                   0, 1, 2, // tri0
                   3, 4, 5, // tri1
                   6, 0, 7  // tri2
                   ),
    gsSPNTriangles_5b(4, 8, 9,  // tri0
                      10, 6, 7, // tri1
                      8, 11, 9, // tri2
                      12, 2, 1  // tri3
                      ),
    gsSPNTriangles_5b(5, 13, 3, // tri0
                      2, 14, 0, // tri1
                      4, 15, 5, // tri2
                      0, 16, 7  // tri3
                      ),
    gsSPNTriangles_5b(17, 4, 9,   // tri0
                      18, 19, 14, // tri1
                      20, 15, 21, // tri2
                      15, 4, 21   // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 17, // tri0
                      23, 4, 17,  // tri1
                      24, 25, 16, // tri2
                      0, 24, 16   // tri3
                      ),
    gsSPNTriangles_5b(19, 0, 14, // tri0
                      26, 10, 7, // tri1
                      0, 19, 24, // tri2
                      12, 27, 2  // tri3
                      ),
    gsSPNTriangles_5b(28, 29, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_museum1_v[94], 18, 0),
    gsSPNTriangles(11,      // tri count
                   0, 1, 2, // tri0
                   0, 3, 1, // tri1
                   3, 4, 1  // tri2
                   ),
    gsSPNTriangles_5b(4, 2, 1, // tri0
                      3, 5, 6, // tri1
                      5, 7, 6, // tri2
                      3, 8, 5  // tri3
                      ),
    gsSPNTriangles_5b(8, 7, 5,    // tri0
                      9, 10, 11,  // tri1
                      12, 13, 14, // tri2
                      15, 16, 17  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_wallB_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum1_v[112], 32, 0),
    gsSPNTriangles(21,      // tri count
                   0, 1, 2, // tri0
                   0, 3, 1, // tri1
                   4, 5, 6  // tri2
                   ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      8, 9, 10,  // tri1
                      9, 11, 10, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 14, // tri0
                      8, 16, 9,   // tri1
                      8, 17, 16,  // tri2
                      17, 18, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 18, // tri0
                      20, 11, 9,  // tri1
                      21, 22, 23, // tri2
                      22, 24, 23  // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 25, // tri0
                      22, 12, 24, // tri1
                      12, 14, 24, // tri2
                      26, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(29, 26, 28, // tri0
                      29, 28, 30, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_museum1_v[143], 32, 0),
    gsSPNTriangles(20,      // tri count
                   0, 1, 2, // tri0
                   1, 3, 2, // tri1
                   4, 5, 6  // tri2
                   ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      5, 8, 7,   // tri1
                      9, 0, 2,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      13, 14, 11, // tri1
                      15, 16, 17, // tri2
                      18, 15, 17  // tri3
                      ),
    gsSPNTriangles_5b(15, 19, 16, // tri0
                      20, 21, 22, // tri1
                      23, 20, 22, // tri2
                      23, 22, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 23, 24, // tri0
                      25, 26, 27, // tri1
                      28, 26, 25, // tri2
                      28, 25, 24  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_museum1_v[175], 8, 0),
    gsSPNTriangles(6,       // tri count
                   0, 1, 2, // tri0
                   0, 2, 3, // tri1
                   4, 0, 3  // tri2
                   ),
    gsSPNTriangles_5b(4, 3, 5, // tri0
                      6, 4, 5, // tri1
                      6, 5, 7, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum1_floor_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_floorB_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum1_v[183], 32, 0),
    gsSPNTriangles(20,      // tri count
                   0, 1, 2, // tri0
                   0, 3, 1, // tri1
                   3, 4, 1  // tri2
                   ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      6, 8, 7,   // tri1
                      8, 9, 7,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      11, 14, 12, // tri1
                      15, 16, 17, // tri2
                      16, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(16, 19, 18, // tri0
                      20, 21, 22, // tri1
                      20, 23, 21, // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(24, 27, 25, // tri0
                      20, 22, 28, // tri1
                      26, 29, 24, // tri2
                      3, 30, 4    // tri3
                      ),
    gsSPNTriangles_5b(14, 31, 12, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_museum1_v[215], 10, 0),
    gsSPNTriangles(4,       // tri count
                   0, 1, 2, // tri0
                   3, 4, 5, // tri1
                   6, 7, 8  // tri2
                   ),
    gsSPNTriangles_5b(7, 9, 8, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_floorA_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum1_v[225], 27, 0),
    gsSPNTriangles(16,      // tri count
                   0, 1, 2, // tri0
                   0, 2, 3, // tri1
                   4, 0, 3  // tri2
                   ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      8, 9, 10,  // tri1
                      9, 11, 12, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(16, 13, 17, // tri0
                      6, 18, 7,   // tri1
                      19, 20, 21, // tri2
                      22, 19, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 21, 14, // tri0
                      23, 24, 25, // tri1
                      23, 26, 24, // tri2
                      10, 9, 12   // tri3
                      ),
    gsSPNTriangles_5b(17, 13, 15, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_museum1_v[252], 16, 0),
    gsSPNTriangles(12,      // tri count
                   0, 1, 2, // tri0
                   1, 3, 2, // tri1
                   3, 4, 2  // tri2
                   ),
    gsSPNTriangles_5b(5, 6, 1, // tri0
                      7, 6, 5, // tri1
                      5, 1, 0, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(8, 11, 9,   // tri0
                      8, 10, 12,  // tri1
                      12, 10, 13, // tri2
                      10, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_field_bg_acre_rom_museum1_rom_museum1_c(void) {
    pc_load_asset("assets/field/bg/rom_museum1_mado_pal.bin", rom_museum1_mado_pal, 0x20, 0xBA38E0, 0, 1);
    pc_load_asset("assets/field/bg/rom_museum1_step_pal.bin", rom_museum1_step_pal, 0x20, 0xBA3900, 0, 1);
    pc_load_asset("assets/field/bg/rom_museum1_floor_pal.bin", rom_museum1_floor_pal, 0x20, 0xBA3920, 0, 1);
    pc_load_asset("assets/field/bg/rom_museum1_wall_pal.bin", rom_museum1_wall_pal, 0x20, 0xBA3940, 0, 1);
    pc_load_asset("assets/field/bg/rom_museum1_mado1_tex.bin", rom_museum1_mado1_tex, 0x800, 0xBA3960, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum1_step1_tex.bin", rom_museum1_step1_tex, 0x800, 0xBA4160, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum1_step2_tex.bin", rom_museum1_step2_tex, 0x400, 0xBA4960, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum1_floorA_tex.bin", rom_museum1_floorA_tex, 0x800, 0xBA4D60, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum1_floorB_tex.bin", rom_museum1_floorB_tex, 0x800, 0xBA5560, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum1_mado2_tex.bin", rom_museum1_mado2_tex, 0x800, 0xBA5D60, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum1_sign1_tex.bin", rom_museum1_sign1_tex, 0x400, 0xBA6560, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum1_wallA_tex.bin", rom_museum1_wallA_tex, 0x800, 0xBA6960, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum1_wallB_tex.bin", rom_museum1_wallB_tex, 0x800, 0xBA7160, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum1_sign2_tex.bin", rom_museum1_sign2_tex, 0x400, 0xBA7960, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum1_sign3_tex.bin", rom_museum1_sign3_tex, 0x400, 0xBA7D60, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum1_sign4_tex.bin", rom_museum1_sign4_tex, 0x400, 0xBA8160, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum1_v.bin", rom_museum1_v, 0x12C0, 0xBA8560, 0, 2);
}
#endif
