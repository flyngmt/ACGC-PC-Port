#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_museum5_on_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_museum5_on_pal[] = {
#include "assets/field/bg/rom_museum5_on_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_museum5_wall_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_museum5_wall_pal[] = {
#include "assets/field/bg/rom_museum5_wall_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_museum5_floor_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_museum5_floor_pal[] = {
#include "assets/field/bg/rom_museum5_floor_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_museum5_step_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_museum5_step_pal[] = {
#include "assets/field/bg/rom_museum5_step_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum5_ki_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum5_ki_tex[] = {
#include "assets/field/bg/rom_museum5_ki_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum5_wallA_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum5_wallA_tex[] = {
#include "assets/field/bg/rom_museum5_wallA_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum5_floor_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum5_floor_tex[] = {
#include "assets/field/bg/rom_museum5_floor_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum5_step_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum5_step_tex[] = {
#include "assets/field/bg/rom_museum5_step_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum5_isi_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum5_isi_tex[] = {
#include "assets/field/bg/rom_museum5_isi_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_museum5_plate_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_museum5_plate_tex[] = {
#include "assets/field/bg/rom_museum5_plate_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx rom_museum5_v[0xD80 / sizeof(Vtx)];
#else
static Vtx rom_museum5_v[] = {
#include "assets/field/bg/rom_museum5_v.inc"
};
#endif

extern Gfx rom_museum5_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx rom_museum5_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum5_step_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum5_plate_tex, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_museum5_v[196], 20, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7,   // tri0
                      8, 9, 10,  // tri1
                      8, 10, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 15, // tri0
                      16, 17, 18, // tri1
                      16, 18, 19, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPVertex(&rom_museum5_v[0], 12, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,   // tri0
                      5, 8, 6,   // tri1
                      9, 10, 11, // tri2
                      11, 2, 1   // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 1, // tri0
                      7, 4, 0,  // tri1
                      4, 3, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum5_step_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum5_v[12], 5, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          0, 4, 1  // tri2
                          ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum5_wall_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum5_wallA_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_museum5_v[17], 32, 0),
    gsSPNTrianglesInit_5b(32,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 3, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 5, 7, // tri0
                      1, 7, 5, // tri1
                      1, 8, 7, // tri2
                      0, 8, 1  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11, // tri0
                      9, 11, 12, // tri1
                      13, 9, 12, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(9, 13, 15,  // tri0
                      15, 14, 16, // tri1
                      15, 16, 17, // tri2
                      9, 18, 10   // tri3
                      ),
    gsSPNTriangles_5b(9, 19, 18,  // tri0
                      19, 20, 18, // tri1
                      21, 2, 22,  // tri2
                      23, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(22, 2, 1,  // tri0
                      23, 22, 1, // tri1
                      5, 4, 24,  // tri2
                      23, 5, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 23, 24, // tri0
                      25, 24, 4,  // tri1
                      23, 1, 5,   // tri2
                      9, 15, 19   // tri3
                      ),
    gsSPNTriangles_5b(15, 26, 19, // tri0
                      26, 27, 19, // tri1
                      15, 17, 26, // tri2
                      26, 17, 27  // tri3
                      ),
    gsSPNTriangles_5b(28, 29, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_museum5_v[48], 9, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          4, 3, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 2, 1, // tri0
                      3, 5, 0, // tri1
                      3, 6, 7, // tri2
                      7, 8, 5  // tri3
                      ),
    gsSPNTriangles_5b(3, 7, 5, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum5_floor_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum5_floor_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_museum5_v[57], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 4, 8,   // tri0
                      5, 7, 9,   // tri1
                      5, 4, 7,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      16, 13, 15, // tri1
                      17, 16, 15, // tri2
                      3, 18, 19   // tri3
                      ),
    gsSPNTriangles_5b(20, 1, 0,   // tri0
                      3, 21, 2,   // tri1
                      22, 23, 24, // tri2
                      25, 26, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 28, // tri0
                      25, 24, 27, // tri1
                      29, 7, 8,   // tri2
                      29, 30, 7   // tri3
                      ),
    gsSPNTriangles_5b(30, 29, 11, // tri0
                      29, 12, 11, // tri1
                      30, 9, 7,   // tri2
                      16, 17, 30  // tri3
                      ),
    gsSPNTriangles_5b(18, 31, 19, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_museum5_v[89], 26, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          2, 1, 3  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 6,   // tri0
                      7, 8, 1,   // tri1
                      9, 10, 11, // tri2
                      9, 12, 10  // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 10, // tri0
                      13, 14, 10, // tri1
                      15, 12, 9,  // tri2
                      13, 12, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      17, 20, 18, // tri1
                      17, 21, 20, // tri2
                      17, 4, 21   // tri3
                      ),
    gsSPNTriangles_5b(22, 20, 23, // tri0
                      24, 20, 21, // tri1
                      25, 10, 17, // tri2
                      10, 2, 17   // tri3
                      ),
    gsSPNTriangles_5b(25, 11, 10, // tri0
                      2, 10, 14,  // tri1
                      25, 17, 19, // tri2
                      17, 2, 4    // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum5_on_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum5_isi_tex, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_museum5_v[115], 32, 0),
    gsSPNTrianglesInit_5b(32,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 2, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 1, 5,   // tri0
                      6, 7, 8,   // tri1
                      6, 8, 9,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(13, 10, 12, // tri0
                      12, 11, 1,  // tri1
                      12, 1, 0,   // tri2
                      5, 1, 14    // tri3
                      ),
    gsSPNTriangles_5b(14, 7, 6, // tri0
                      5, 14, 6, // tri1
                      12, 0, 3, // tri2
                      13, 12, 3 // tri3
                      ),
    gsSPNTriangles_5b(4, 5, 6,    // tri0
                      4, 6, 9,    // tri1
                      15, 16, 17, // tri2
                      18, 19, 15  // tri3
                      ),
    gsSPNTriangles_5b(18, 15, 17, // tri0
                      20, 21, 22, // tri1
                      23, 24, 20, // tri2
                      23, 20, 22  // tri3
                      ),
    gsSPNTriangles_5b(25, 19, 18, // tri0
                      22, 21, 25, // tri1
                      22, 25, 18, // tri2
                      26, 23, 22  // tri3
                      ),
    gsSPNTriangles_5b(26, 22, 18, // tri0
                      26, 18, 17, // tri1
                      27, 28, 29, // tri2
                      28, 30, 29  // tri3
                      ),
    gsSPNTriangles_5b(31, 28, 27, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_museum5_v[147], 9, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          3, 5, 4  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 3, // tri0
                      6, 7, 8, // tri1
                      6, 4, 7, // tri2
                      4, 5, 7  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum5_ki_tex, G_IM_FMT_CI, 16, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_museum5_v[156], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,    // tri0
                      5, 8, 9,    // tri1
                      10, 11, 12, // tri2
                      10, 13, 11  // tri3
                      ),
    gsSPNTriangles_5b(8, 12, 9,  // tri0
                      8, 10, 12, // tri1
                      9, 12, 14, // tri2
                      15, 10, 8  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 10, // tri0
                      17, 18, 19, // tri1
                      20, 21, 22, // tri2
                      20, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(23, 22, 18, // tri0
                      23, 18, 17, // tri1
                      22, 24, 25, // tri2
                      22, 25, 18  // tri3
                      ),
    gsSPNTriangles_5b(26, 23, 17, // tri0
                      26, 27, 28, // tri1
                      29, 26, 28, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_museum5_v[186], 10, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(3, 2, 5, // tri0
                      3, 5, 4, // tri1
                      2, 7, 8, // tri2
                      2, 8, 5  // tri3
                      ),
    gsSPNTriangles_5b(9, 3, 4, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_field_bg_acre_rom_museum5_rom_museum5_c(void) {
    pc_load_asset("assets/field/bg/rom_museum5_on_pal.bin", rom_museum5_on_pal, 0x20, 0xBA9C00, 0, 1);
    pc_load_asset("assets/field/bg/rom_museum5_wall_pal.bin", rom_museum5_wall_pal, 0x20, 0xBA9C20, 0, 1);
    pc_load_asset("assets/field/bg/rom_museum5_floor_pal.bin", rom_museum5_floor_pal, 0x20, 0xBA9C40, 0, 1);
    pc_load_asset("assets/field/bg/rom_museum5_step_pal.bin", rom_museum5_step_pal, 0x20, 0xBA9C60, 0, 1);
    pc_load_asset("assets/field/bg/rom_museum5_ki_tex.bin", rom_museum5_ki_tex, 0x200, 0xBA9C80, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum5_wallA_tex.bin", rom_museum5_wallA_tex, 0x800, 0xBA9E80, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum5_floor_tex.bin", rom_museum5_floor_tex, 0x800, 0xBAA680, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum5_step_tex.bin", rom_museum5_step_tex, 0x800, 0xBAAE80, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum5_isi_tex.bin", rom_museum5_isi_tex, 0x200, 0xBAB680, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum5_plate_tex.bin", rom_museum5_plate_tex, 0x200, 0xBAB880, 0, 0);
    pc_load_asset("assets/field/bg/rom_museum5_v.bin", rom_museum5_v, 0xD80, 0xBABA80, 0, 2);
}
#endif
