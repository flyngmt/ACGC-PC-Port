#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_museum2_wall_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_museum2_wall_pal[] = {
#include "assets/field/bg/rom_museum2_wall_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_museum2_floor_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_museum2_floor_pal[] = {
#include "assets/field/bg/rom_museum2_floor_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_museum2_step1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_museum2_step1_pal[] = {
#include "assets/field/bg/rom_museum2_step1_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum2_wallA_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum2_wallA_tex[] = {
#include "assets/field/bg/rom_museum2_wallA_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum2_wallB_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum2_wallB_tex[] = {
#include "assets/field/bg/rom_museum2_wallB_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum2_floorA_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum2_floorA_tex[] = {
#include "assets/field/bg/rom_museum2_floorA_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum2_step1_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum2_step1_tex[] = {
#include "assets/field/bg/rom_museum2_step1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum2_plate_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum2_plate_tex[] = {
#include "assets/field/bg/rom_museum2_plate_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx rom_museum2_v[0x1100 / sizeof(Vtx)];
#else
static Vtx rom_museum2_v[] = {
#include "assets/field/bg/rom_museum2_v.inc"
};
#endif

extern Gfx rom_museum2_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx rom_museum2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum2_step1_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum2_step1_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_museum2_v[0], 5, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          0, 4, 1  // tri2
                          ),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum2_wall_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum2_wallB_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum2_v[5], 25, 0),
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
    gsSPNTriangles_5b(4, 3, 11,  // tri0
                      3, 12, 11, // tri1
                      6, 5, 13,  // tri2
                      5, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 9,  // tri0
                      7, 9, 15,   // tri1
                      13, 14, 15, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(19, 16, 18, // tri0
                      20, 21, 22, // tri1
                      23, 16, 19, // tri2
                      16, 23, 22  // tri3
                      ),
    gsSPNTriangles_5b(24, 22, 23, // tri0
                      24, 20, 22, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum2_wallA_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum2_v[30], 25, 0),
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
                      15, 5, 1    // tri3
                      ),
    gsSPNTriangles_5b(0, 3, 15,  // tri0
                      3, 5, 15,  // tri1
                      7, 6, 14,  // tri2
                      16, 17, 18 // tri3
                      ),
    gsSPNTriangles_5b(19, 18, 20, // tri0
                      18, 17, 20, // tri1
                      21, 20, 17, // tri2
                      21, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(17, 16, 22, // tri0
                      16, 23, 22, // tri1
                      24, 22, 23, // tri2
                      24, 17, 22  // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum2_floor_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum2_floorA_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_museum2_v[55], 32, 0),
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
    gsSPVertex(&rom_museum2_v[87], 27, 0),
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
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum2_step1_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum2_plate_tex, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum2_v[114], 32, 0),
    gsSPNTrianglesInit_5b(30,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          2, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(2, 5, 3, // tri0
                      1, 6, 4, // tri1
                      1, 4, 2, // tri2
                      0, 7, 6  // tri3
                      ),
    gsSPNTriangles_5b(0, 6, 1,   // tri0
                      8, 9, 10,  // tri1
                      8, 10, 11, // tri2
                      11, 10, 12 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      13, 12, 14, // tri1
                      13, 14, 15, // tri2
                      8, 11, 13   // tri3
                      ),
    gsSPNTriangles_5b(8, 13, 15,  // tri0
                      16, 17, 18, // tri1
                      16, 18, 19, // tri2
                      18, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(18, 21, 19, // tri0
                      17, 22, 20, // tri1
                      17, 20, 18, // tri2
                      16, 23, 22  // tri3
                      ),
    gsSPNTriangles_5b(16, 22, 17, // tri0
                      24, 25, 26, // tri1
                      24, 26, 27, // tri2
                      27, 26, 28  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 29, // tri0
                      24, 27, 29, // tri1
                      24, 29, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_museum2_v[145], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          1, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 2, // tri0
                      0, 6, 4, // tri1
                      0, 4, 1, // tri2
                      7, 8, 9  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 10,   // tri0
                      10, 9, 11,  // tri1
                      10, 11, 12, // tri2
                      7, 10, 12   // tri3
                      ),
    gsSPNTriangles_5b(7, 12, 13,  // tri0
                      14, 15, 16, // tri1
                      14, 16, 17, // tri2
                      17, 16, 18  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      20, 14, 17, // tri1
                      20, 17, 19, // tri2
                      21, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(21, 23, 24, // tri0
                      23, 25, 26, // tri1
                      23, 26, 24, // tri2
                      22, 27, 25  // tri3
                      ),
    gsSPNTriangles_5b(22, 25, 23, // tri0
                      28, 29, 30, // tri1
                      28, 30, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_museum2_v[177], 32, 0),
    gsSPNTrianglesInit_5b(30,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          3, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(3, 4, 5, // tri0
                      6, 0, 3, // tri1
                      6, 3, 5, // tri2
                      7, 8, 9  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 10,  // tri0
                      9, 11, 12, // tri1
                      9, 12, 10, // tri2
                      8, 13, 11  // tri3
                      ),
    gsSPNTriangles_5b(8, 11, 9,  // tri0
                      7, 14, 13, // tri1
                      7, 13, 8,  // tri2
                      15, 16, 17 // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 18, // tri0
                      18, 17, 19, // tri1
                      18, 19, 20, // tri2
                      20, 19, 21  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 22, // tri0
                      15, 18, 20, // tri1
                      15, 20, 22, // tri2
                      23, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(23, 25, 26, // tri0
                      25, 27, 28, // tri1
                      25, 28, 26, // tri2
                      24, 29, 27  // tri3
                      ),
    gsSPNTriangles_5b(24, 27, 25, // tri0
                      23, 30, 29, // tri1
                      23, 29, 24, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_museum2_v[208], 32, 0),
    gsSPNTrianglesInit_5b(32,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          3, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(3, 4, 5, // tri0
                      5, 4, 6, // tri1
                      5, 6, 7, // tri2
                      0, 3, 5  // tri3
                      ),
    gsSPNTriangles_5b(0, 5, 7,   // tri0
                      8, 9, 10,  // tri1
                      8, 10, 11, // tri2
                      10, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      9, 14, 12,  // tri1
                      9, 12, 10,  // tri2
                      8, 15, 14   // tri3
                      ),
    gsSPNTriangles_5b(8, 14, 9,   // tri0
                      16, 17, 18, // tri1
                      16, 18, 19, // tri2
                      19, 18, 20  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      21, 20, 22, // tri1
                      21, 22, 23, // tri2
                      16, 19, 21  // tri3
                      ),
    gsSPNTriangles_5b(16, 21, 23, // tri0
                      24, 25, 26, // tri1
                      24, 26, 27, // tri2
                      26, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(26, 29, 27, // tri0
                      25, 30, 28, // tri1
                      25, 28, 26, // tri2
                      24, 31, 30  // tri3
                      ),
    gsSPNTriangles_5b(24, 30, 25, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_museum2_v[240], 32, 0),
    gsSPNTrianglesInit_5b(32,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          3, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(3, 4, 5, // tri0
                      5, 4, 6, // tri1
                      5, 6, 7, // tri2
                      0, 3, 5  // tri3
                      ),
    gsSPNTriangles_5b(0, 5, 7,   // tri0
                      8, 9, 10,  // tri1
                      8, 10, 11, // tri2
                      10, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      9, 14, 12,  // tri1
                      9, 12, 10,  // tri2
                      8, 15, 14   // tri3
                      ),
    gsSPNTriangles_5b(8, 14, 9,   // tri0
                      16, 17, 18, // tri1
                      16, 18, 19, // tri2
                      18, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(18, 21, 19, // tri0
                      17, 22, 20, // tri1
                      17, 20, 18, // tri2
                      16, 23, 22  // tri3
                      ),
    gsSPNTriangles_5b(16, 22, 17, // tri0
                      24, 25, 26, // tri1
                      24, 26, 27, // tri2
                      27, 26, 28  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 29, // tri0
                      29, 28, 30, // tri1
                      29, 30, 31, // tri2
                      24, 27, 29  // tri3
                      ),
    gsSPNTriangles_5b(24, 29, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_field_bg_acre_rom_museum2_rom_museum2_c(void) {
    pc_load_asset("assets/field/bg/rom_museum2_wall_pal.bin", rom_museum2_wall_pal, 0x20, 0xBAD400, 0, 1);
    pc_load_asset("assets/field/bg/rom_museum2_floor_pal.bin", rom_museum2_floor_pal, 0x20, 0xBAD420, 0, 1);
    pc_load_asset("assets/field/bg/rom_museum2_step1_pal.bin", rom_museum2_step1_pal, 0x20, 0xBAD440, 0, 1);
    pc_load_asset("assets/field/bg/rom_museum2_wallA_tex.bin", rom_museum2_wallA_tex, 0x800, 0xBAD460, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum2_wallB_tex.bin", rom_museum2_wallB_tex, 0x800, 0xBADC60, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum2_floorA_tex.bin", rom_museum2_floorA_tex, 0x800, 0xBAE460, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum2_step1_tex.bin", rom_museum2_step1_tex, 0x800, 0xBAEC60, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum2_plate_tex.bin", rom_museum2_plate_tex, 0x100, 0xBAF460, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum2_v.bin", rom_museum2_v, 0x1100, 0xBAF560, 0, 2);
}
#endif
