#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_museum3_wall_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_museum3_wall_pal[] = {
#include "assets/field/bg/rom_museum3_wall_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_museum3_back_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_museum3_back_pal[] = {
#include "assets/field/bg/rom_museum3_back_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_museum3_floor_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_museum3_floor_pal[] = {
#include "assets/field/bg/rom_museum3_floor_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum3_wallA_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum3_wallA_tex[] = {
#include "assets/field/bg/rom_museum3_wallA_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum3_wallB_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum3_wallB_tex[] = {
#include "assets/field/bg/rom_museum3_wallB_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum3_back_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum3_back_tex[] = {
#include "assets/field/bg/rom_museum3_back_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum3_floorA_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum3_floorA_tex[] = {
#include "assets/field/bg/rom_museum3_floorA_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum3_step_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum3_step_tex[] = {
#include "assets/field/bg/rom_museum3_step_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum3_hasira_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum3_hasira_tex[] = {
#include "assets/field/bg/rom_museum3_hasira_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum3_backside_tex[0x180];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum3_backside_tex[] = {
#include "assets/field/bg/rom_museum3_backside_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx rom_museum3_v[0x11B0 / sizeof(Vtx)];
#else
static Vtx rom_museum3_v[] = {
#include "assets/field/bg/rom_museum3_v.inc"
};
#endif

extern Gfx rom_museum3_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx rom_museum3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum3_back_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum3_step_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_museum3_v[0], 5, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          0, 4, 1  // tri2
                          ),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum3_wall_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum3_wallA_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum3_v[5], 27, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 4,  // tri0
                      7, 5, 4,  // tri1
                      8, 9, 10, // tri2
                      8, 0, 9   // tri3
                      ),
    gsSPNTriangles_5b(0, 2, 9,   // tri0
                      2, 10, 9,  // tri1
                      11, 12, 6, // tri2
                      11, 13, 12 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 12, // tri0
                      14, 6, 12,  // tri1
                      0, 15, 1,   // tri2
                      15, 16, 1   // tri3
                      ),
    gsSPNTriangles_5b(0, 17, 15,  // tri0
                      17, 16, 15, // tri1
                      7, 6, 14,   // tri2
                      18, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(21, 20, 22, // tri0
                      20, 19, 22, // tri1
                      23, 22, 19, // tri2
                      23, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(19, 18, 24, // tri0
                      18, 25, 24, // tri1
                      26, 24, 25, // tri2
                      26, 19, 24  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum3_wallB_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum3_v[32], 27, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          3, 2, 1, // tri1
                          2, 3, 4  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 1, // tri0
                      5, 6, 1, // tri1
                      7, 8, 9, // tri2
                      8, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 11,   // tri0
                      3, 12, 11,  // tri1
                      13, 14, 15, // tri2
                      14, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 9,  // tri0
                      7, 9, 17,   // tri1
                      15, 16, 17, // tri2
                      18, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(21, 18, 20, // tri0
                      22, 23, 24, // tri1
                      25, 18, 21, // tri2
                      18, 25, 24  // tri3
                      ),
    gsSPNTriangles_5b(26, 24, 25, // tri0
                      26, 22, 24, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum3_floor_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum3_floorA_tex, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_museum3_v[59], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          3, 1, 0  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 1,   // tri0
                      6, 7, 8,   // tri1
                      9, 10, 11, // tri2
                      12, 9, 11  // tri3
                      ),
    gsSPNTriangles_5b(13, 12, 11, // tri0
                      14, 15, 16, // tri1
                      17, 18, 19, // tri2
                      14, 20, 19  // tri3
                      ),
    gsSPNTriangles_5b(18, 14, 19, // tri0
                      21, 22, 23, // tri1
                      24, 25, 23, // tri2
                      24, 26, 27  // tri3
                      ),
    gsSPNTriangles_5b(24, 23, 26, // tri0
                      28, 0, 2,   // tri1
                      28, 29, 0,  // tri2
                      29, 28, 7   // tri3
                      ),
    gsSPNTriangles_5b(28, 8, 7,   // tri0
                      29, 4, 0,   // tri1
                      12, 13, 29, // tri2
                      15, 30, 16  // tri3
                      ),
    gsSPNTriangles_5b(15, 31, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_museum3_v[91], 27, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          2, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 5,   // tri0
                      5, 6, 7,   // tri1
                      8, 9, 0,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      13, 14, 11, // tri1
                      14, 15, 11, // tri2
                      16, 13, 10  // tri3
                      ),
    gsSPNTriangles_5b(14, 13, 17, // tri0
                      18, 19, 20, // tri1
                      18, 21, 19, // tri2
                      18, 22, 21  // tri3
                      ),
    gsSPNTriangles_5b(18, 4, 22,  // tri0
                      23, 21, 24, // tri1
                      25, 21, 22, // tri2
                      26, 11, 18  // tri3
                      ),
    gsSPNTriangles_5b(11, 2, 18,  // tri0
                      26, 12, 11, // tri1
                      2, 11, 15,  // tri2
                      26, 18, 20  // tri3
                      ),
    gsSPNTriangles_5b(18, 2, 4, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum3_wall_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum3_hasira_tex, G_IM_FMT_CI, 16, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum3_v[118], 32, 0),
    gsSPNTrianglesInit_5b(40,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 6, // tri0
                      5, 7, 6, // tri1
                      7, 8, 6, // tri2
                      9, 0, 10 // tri3
                      ),
    gsSPNTriangles_5b(0, 11, 10,  // tri0
                      11, 12, 10, // tri1
                      13, 9, 14,  // tri2
                      9, 15, 14   // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 14, // tri0
                      17, 18, 19, // tri1
                      17, 13, 18, // tri2
                      18, 20, 19  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      21, 17, 22, // tri1
                      22, 24, 23, // tri2
                      16, 18, 14  // tri3
                      ),
    gsSPNTriangles_5b(16, 20, 18, // tri0
                      18, 13, 14, // tri1
                      12, 16, 10, // tri2
                      16, 15, 10  // tri3
                      ),
    gsSPNTriangles_5b(15, 9, 10,  // tri0
                      20, 22, 19, // tri1
                      20, 24, 22, // tri2
                      22, 17, 19  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 23, // tri0
                      24, 26, 25, // tri1
                      25, 21, 23, // tri2
                      4, 12, 2    // tri3
                      ),
    gsSPNTriangles_5b(12, 11, 2, // tri0
                      11, 0, 2,  // tri1
                      8, 4, 6,   // tri2
                      4, 3, 6    // tri3
                      ),
    gsSPNTriangles_5b(3, 1, 6,   // tri0
                      27, 7, 28, // tri1
                      27, 8, 7,  // tri2
                      7, 5, 28   // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_museum3_v[150], 32, 0),
    gsSPNTrianglesInit_5b(32,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 3, 4  // tri2
                          ),
    gsSPNTriangles_5b(0, 4, 5, // tri0
                      0, 5, 6, // tri1
                      7, 8, 9, // tri2
                      7, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(7, 11, 10,  // tri0
                      12, 13, 8,  // tri1
                      12, 14, 13, // tri2
                      12, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(16, 9, 17,  // tri0
                      16, 18, 9,  // tri1
                      16, 19, 18, // tri2
                      20, 17, 21  // tri3
                      ),
    gsSPNTriangles_5b(20, 22, 17, // tri0
                      20, 23, 22, // tri1
                      24, 25, 26, // tri2
                      25, 21, 26  // tri3
                      ),
    gsSPNTriangles_5b(24, 27, 25, // tri0
                      28, 29, 30, // tri1
                      29, 26, 30, // tri2
                      28, 31, 29  // tri3
                      ),
    gsSPNTriangles_5b(20, 25, 23, // tri0
                      25, 27, 23, // tri1
                      20, 21, 25, // tri2
                      16, 23, 19  // tri3
                      ),
    gsSPNTriangles_5b(16, 22, 23, // tri0
                      16, 17, 22, // tri1
                      24, 29, 27, // tri2
                      29, 31, 27  // tri3
                      ),
    gsSPNTriangles_5b(24, 26, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_museum3_v[182], 26, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,  // tri0
                      5, 8, 6,  // tri1
                      5, 9, 8,  // tri2
                      10, 7, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 12, 7,  // tri0
                      10, 13, 12, // tri1
                      14, 15, 16, // tri2
                      15, 11, 16  // tri3
                      ),
    gsSPNTriangles_5b(14, 17, 15, // tri0
                      18, 19, 20, // tri1
                      18, 20, 21, // tri2
                      18, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(18, 22, 23, // tri0
                      18, 23, 24, // tri1
                      18, 24, 25, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum3_back_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum3_backside_tex, G_IM_FMT_CI, 16, 48, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum3_v[208], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,   // tri0
                      8, 9, 10,  // tri1
                      8, 11, 9,  // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(12, 15, 13, // tri0
                      16, 17, 18, // tri1
                      17, 19, 18, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(21, 23, 22, // tri0
                      24, 25, 26, // tri1
                      24, 27, 25, // tri2
                      28, 29, 30  // tri3
                      ),
    gsSPNTriangles_5b(28, 31, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_museum3_v[240], 8, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 4, 6, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum3_back_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum3_v[248], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 2,  // tri0
                      6, 7, 8,  // tri1
                      6, 8, 9,  // tri2
                      10, 7, 11 // tri3
                      ),
    gsSPNTriangles_5b(7, 6, 11,   // tri0
                      12, 13, 14, // tri1
                      12, 14, 15, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      18, 20, 21, // tri1
                      17, 19, 18, // tri2
                      22, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(23, 25, 24, // tri0
                      25, 23, 26, // tri1
                      25, 26, 27, // tri2
                      13, 12, 28  // tri3
                      ),
    gsSPNTriangles_5b(12, 29, 28, // tri0
                      4, 30, 31,  // tri1
                      4, 3, 30,   // tri2
                      3, 1, 30    // tri3
                      ),
    gsSPVertex(&rom_museum3_v[280], 3, 0),
    gsSPNTrianglesInit_5b(1,       // tri count
                          0, 1, 2, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_field_bg_acre_rom_museum3_rom_museum3_c(void) {
    pc_load_asset("assets/field/bg/rom_museum3_wall_pal.bin", rom_museum3_wall_pal, 0x20, 0xBB3C80, 0, 1);
    pc_load_asset("assets/field/bg/rom_museum3_back_pal.bin", rom_museum3_back_pal, 0x20, 0xBB3CA0, 0, 1);
    pc_load_asset("assets/field/bg/rom_museum3_floor_pal.bin", rom_museum3_floor_pal, 0x20, 0xBB3CC0, 0, 1);
    pc_load_asset("assets/field/bg/rom_museum3_wallA_tex.bin", rom_museum3_wallA_tex, 0x800, 0xBB3CE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum3_wallB_tex.bin", rom_museum3_wallB_tex, 0x800, 0xBB44E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum3_back_tex.bin", rom_museum3_back_tex, 0x800, 0xBB4CE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum3_floorA_tex.bin", rom_museum3_floorA_tex, 0x800, 0xBB54E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum3_step_tex.bin", rom_museum3_step_tex, 0x800, 0xBB5CE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum3_hasira_tex.bin", rom_museum3_hasira_tex, 0x100, 0xBB64E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum3_backside_tex.bin", rom_museum3_backside_tex, 0x180, 0xBB65E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum3_v.bin", rom_museum3_v, 0x11B0, 0xBB6760, 0, 2);
}
#endif
