#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_train_1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_train_1_pal[] = {
#include "assets/field/bg/rom_train_1_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_train_2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_train_2_pal[] = {
#include "assets/field/bg/rom_train_2_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_train_3_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_train_3_pal[] = {
#include "assets/field/bg/rom_train_3_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_train_seat1_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_train_seat1_tex[] = {
#include "assets/field/bg/rom_train_seat1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_train_seat2_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_train_seat2_tex[] = {
#include "assets/field/bg/rom_train_seat2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_train_floor_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_train_floor_tex[] = {
#include "assets/field/bg/rom_train_floor_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_train_wall1_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_train_wall1_tex[] = {
#include "assets/field/bg/rom_train_wall1_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_train_roof_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_train_roof_tex[] = {
#include "assets/field/bg/rom_train_roof_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_train_wall2_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_train_wall2_tex[] = {
#include "assets/field/bg/rom_train_wall2_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_train_net_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_train_net_tex[] = {
#include "assets/field/bg/rom_train_net_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_train_glass_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_train_glass_tex[] = {
#include "assets/field/bg/rom_train_glass_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_train_light_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_train_light_tex[] = {
#include "assets/field/bg/rom_train_light_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx rom_train_in_v[0x20F0 / sizeof(Vtx)];
#else
static Vtx rom_train_in_v[] = {
#include "assets/field/bg/rom_train_in_v.inc"
};
#endif

extern Gfx rom_train_in_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetEnvColor(0x64, 0xE6, 0xFF, 0xFF),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(rom_train_glass_tex, G_IM_FMT_I, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_train_in_v[479], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
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
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(20, 22, 23, // tri0
                      24, 25, 26, // tri1
                      24, 26, 27, // tri2
                      28, 29, 30  // tri3
                      ),
    gsSPNTriangles_5b(28, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetCombineMode(G_CC_BLENDPEDECALA, G_CC_PASS2),
    gsDPSetEnvColor(0xFF, 0xFF, 0x78, 0xFF),
    gsDPLoadTextureBlock_4b_Dolphin(rom_train_light_tex, G_IM_FMT_I, 32, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_train_in_v[511], 16, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
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
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx rom_train_in_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_train_1_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_train_seat1_tex, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_train_in_v[213], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          3, 1, 0, // tri1
                          0, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(3, 0, 4, // tri0
                      5, 6, 7, // tri1
                      5, 7, 8, // tri2
                      9, 10, 6 // tri3
                      ),
    gsSPNTriangles_5b(9, 6, 5,    // tri0
                      11, 12, 13, // tri1
                      11, 13, 14, // tri2
                      15, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(16, 18, 17, // tri0
                      15, 19, 16, // tri1
                      19, 18, 16, // tri2
                      19, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(19, 21, 18, // tri0
                      22, 23, 24, // tri1
                      22, 24, 25, // tri2
                      25, 24, 26  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 27, // tri0
                      28, 29, 23, // tri1
                      28, 23, 22, // tri2
                      30, 22, 25  // tri3
                      ),
    gsSPNTriangles_5b(30, 25, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_train_in_v[245], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          2, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(2, 5, 6, // tri0
                      7, 8, 9, // tri1
                      7, 9, 1, // tri2
                      1, 9, 4  // tri3
                      ),
    gsSPNTriangles_5b(1, 4, 2,    // tri0
                      10, 11, 12, // tri1
                      10, 12, 13, // tri2
                      14, 10, 13  // tri3
                      ),
    gsSPNTriangles_5b(14, 13, 15, // tri0
                      16, 10, 14, // tri1
                      16, 14, 15, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 20, // tri0
                      21, 22, 23, // tri1
                      21, 23, 24, // tri2
                      25, 26, 22  // tri3
                      ),
    gsSPNTriangles_5b(25, 22, 21, // tri0
                      27, 28, 29, // tri1
                      27, 30, 28, // tri2
                      28, 31, 29  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 28, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_train_in_v[277], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5, // tri0
                      5, 8, 6, // tri1
                      5, 7, 8, // tri2
                      7, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(7, 10, 8,   // tri0
                      11, 12, 13, // tri1
                      11, 13, 14, // tri2
                      15, 16, 12  // tri3
                      ),
    gsSPNTriangles_5b(15, 12, 11, // tri0
                      14, 13, 17, // tri1
                      14, 17, 18, // tri2
                      19, 11, 14  // tri3
                      ),
    gsSPNTriangles_5b(19, 14, 20, // tri0
                      21, 22, 23, // tri1
                      21, 23, 24, // tri2
                      25, 26, 27  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 22, // tri0
                      23, 28, 29, // tri1
                      23, 29, 30, // tri2
                      22, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(22, 28, 23, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_train_in_v[308], 11, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 3, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 0, 4, // tri0
                      4, 3, 6, // tri1
                      5, 4, 6, // tri2
                      7, 8, 9  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 10, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_train_3_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_train_net_tex, G_IM_FMT_CI, 128, 32, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_train_in_v[319], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
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
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(20, 22, 23, // tri0
                      24, 25, 26, // tri1
                      24, 26, 27, // tri2
                      28, 29, 30  // tri3
                      ),
    gsSPNTriangles_5b(28, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_train_in_v[351], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
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
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(20, 22, 23, // tri0
                      24, 25, 26, // tri1
                      24, 26, 27, // tri2
                      28, 29, 30  // tri3
                      ),
    gsSPNTriangles_5b(28, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_train_in_v[383], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
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
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(20, 22, 23, // tri0
                      24, 25, 26, // tri1
                      24, 26, 27, // tri2
                      28, 29, 30  // tri3
                      ),
    gsSPNTriangles_5b(28, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_train_in_v[415], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
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
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(20, 22, 23, // tri0
                      24, 25, 26, // tri1
                      24, 26, 27, // tri2
                      28, 29, 30  // tri3
                      ),
    gsSPNTriangles_5b(28, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_train_in_v[447], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
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
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(20, 22, 23, // tri0
                      24, 25, 26, // tri1
                      24, 26, 27, // tri2
                      28, 29, 30  // tri3
                      ),
    gsSPNTriangles_5b(28, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_train_1_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_train_seat2_tex, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_train_in_v[0], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7,   // tri0
                      8, 9, 10,  // tri1
                      11, 8, 10, // tri2
                      8, 12, 9   // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 8,  // tri0
                      13, 14, 15, // tri1
                      14, 16, 15, // tri2
                      17, 13, 18  // tri3
                      ),
    gsSPNTriangles_5b(13, 19, 18, // tri0
                      13, 15, 19, // tri1
                      15, 20, 19, // tri2
                      15, 21, 20  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 24, // tri0
                      25, 22, 24, // tri1
                      25, 24, 26, // tri2
                      27, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(27, 26, 28, // tri0
                      24, 29, 30, // tri1
                      24, 30, 26, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_train_in_v[31], 26, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          3, 1, 0, // tri1
                          4, 0, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 0, // tri0
                      5, 6, 7, // tri1
                      5, 7, 8, // tri2
                      6, 9, 7  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 8,    // tri0
                      10, 11, 12, // tri1
                      10, 13, 14, // tri2
                      13, 15, 11  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      16, 18, 19, // tri1
                      20, 16, 19, // tri2
                      21, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(23, 22, 24, // tri0
                      21, 23, 25, // tri1
                      23, 24, 25, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_train_2_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_train_wall1_tex, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_train_in_v[57], 32, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      4, 6, 5, // tri1
                      6, 7, 5, // tri2
                      5, 8, 9  // tri3
                      ),
    gsSPNTriangles_5b(5, 7, 8,   // tri0
                      10, 11, 5, // tri1
                      10, 5, 12, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 16, // tri0
                      17, 18, 19, // tri1
                      17, 19, 20, // tri2
                      6, 21, 7    // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 7,  // tri0
                      23, 24, 25, // tri1
                      23, 25, 26, // tri2
                      27, 28, 22  // tri3
                      ),
    gsSPNTriangles_5b(27, 22, 29, // tri0
                      22, 30, 31, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_train_in_v[89], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 8,   // tri0
                      9, 10, 11, // tri1
                      9, 11, 12, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 14, // tri0
                      16, 14, 13, // tri1
                      18, 13, 19, // tri2
                      18, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      21, 23, 24, // tri1
                      25, 13, 15, // tri2
                      25, 15, 26  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 29, // tri0
                      27, 29, 30, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_train_in_v[120], 17, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7,  // tri0
                      8, 9, 5,  // tri1
                      10, 8, 5, // tri2
                      5, 9, 11  // tri3
                      ),
    gsSPNTriangles_5b(5, 11, 12,  // tri0
                      13, 5, 12,  // tri1
                      13, 12, 14, // tri2
                      15, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 14, 16, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_train_roof_tex, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_train_in_v[137], 15, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 1, // tri0
                      2, 1, 6, // tri1
                      1, 7, 6, // tri2
                      1, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(1, 5, 8,  // tri0
                      8, 9, 7,  // tri1
                      8, 10, 9, // tri2
                      9, 6, 7   // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 6,  // tri0
                      11, 9, 12, // tri1
                      9, 13, 12, // tri2
                      9, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 14, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_train_wall2_tex, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_train_in_v[152], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          3, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(3, 4, 5, // tri0
                      3, 5, 6, // tri1
                      7, 3, 6, // tri2
                      7, 6, 8  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      10, 12, 11, // tri1
                      10, 13, 12, // tri2
                      13, 14, 12  // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 12, // tri0
                      15, 16, 12, // tri1
                      15, 17, 16, // tri2
                      18, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(19, 21, 20, // tri0
                      22, 23, 24, // tri1
                      23, 25, 24, // tri2
                      26, 22, 24  // tri3
                      ),
    gsSPNTriangles_5b(20, 27, 24, // tri0
                      20, 28, 27, // tri1
                      27, 26, 24, // tri2
                      21, 28, 20  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_train_in_v[184], 10, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 4, // tri0
                      2, 4, 3, // tri1
                      7, 8, 5, // tri2
                      7, 5, 9  // tri3
                      ),
    gsSPNTriangles_5b(9, 5, 4, // tri0
                      9, 4, 1, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_train_floor_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_train_in_v[194], 19, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          5, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(1, 6, 2, // tri0
                      7, 8, 3, // tri1
                      2, 7, 3, // tri2
                      7, 9, 8  // tri3
                      ),
    gsSPNTriangles_5b(7, 10, 9,  // tri0
                      11, 12, 9, // tri1
                      11, 9, 13, // tri2
                      9, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 14,  // tri0
                      10, 15, 14, // tri1
                      10, 16, 15, // tri2
                      13, 14, 17  // tri3
                      ),
    gsSPNTriangles_5b(14, 18, 17, // tri0
                      0, 2, 3,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_field_bg_acre_rom_train_in_rom_train_in_c(void) {
    pc_load_asset("assets/field/bg/rom_train_1_pal.bin", rom_train_1_pal, 0x20, 0xD96B80, 0, 1);
    pc_load_asset("assets/field/bg/rom_train_2_pal.bin", rom_train_2_pal, 0x20, 0xD96BA0, 0, 1);
    pc_load_asset("assets/field/bg/rom_train_3_pal.bin", rom_train_3_pal, 0x20, 0xD96BC0, 0, 1);
    pc_load_asset("assets/field/bg/rom_train_seat1_tex.bin", rom_train_seat1_tex, 0x800, 0xD96BE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_train_seat2_tex.bin", rom_train_seat2_tex, 0x800, 0xD973E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_train_floor_tex.bin", rom_train_floor_tex, 0x800, 0xD97BE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_train_wall1_tex.bin", rom_train_wall1_tex, 0x800, 0xD983E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_train_roof_tex.bin", rom_train_roof_tex, 0x800, 0xD98BE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_train_wall2_tex.bin", rom_train_wall2_tex, 0x800, 0xD993E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_train_net_tex.bin", rom_train_net_tex, 0x800, 0xD99BE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_train_glass_tex.bin", rom_train_glass_tex, 0x80, 0xD9A3E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_train_light_tex.bin", rom_train_light_tex, 0x200, 0xD9A460, 0, 0);
    pc_load_asset("assets/field/bg/rom_train_in_v.bin", rom_train_in_v, 0x20F0, 0xD9A660, 0, 2);
}
#endif
