#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_floor_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_floor_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_floor_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_lamp_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_lamp_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_lamp_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_base_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_base_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_base_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_stair_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_stair_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_stair_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_table_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_table_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_table_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_wall_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_wall_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_wall_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_sign01_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_sign01_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_sign01_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_kaunta_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_kaunta_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_kaunta_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_us_sign01_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_us_sign01_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_us_sign01_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_us_sign02_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_us_sign02_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_us_sign02_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_us_sign03_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_us_sign03_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_us_sign03_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_sign03_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_sign03_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_sign03_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_reji_tex_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) static u16 rom_shop4_1_reji_tex_pal[] = {
#include "assets/field/bg/rom_shop4_1_reji_tex_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_floor01_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_floor01_tex[] = {
#include "assets/field/bg/rom_shop4_1_floor01_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_lamp_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_lamp_tex[] = {
#include "assets/field/bg/rom_shop4_1_lamp_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_base_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_base_tex[] = {
#include "assets/field/bg/rom_shop4_1_base_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_stair01_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_stair01_tex[] = {
#include "assets/field/bg/rom_shop4_1_stair01_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_table01_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_table01_tex[] = {
#include "assets/field/bg/rom_shop4_1_table01_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_table02_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_table02_tex[] = {
#include "assets/field/bg/rom_shop4_1_table02_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_wall01_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_wall01_tex[] = {
#include "assets/field/bg/rom_shop4_1_wall01_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_wall02_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_wall02_tex[] = {
#include "assets/field/bg/rom_shop4_1_wall02_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_sign05_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_sign05_tex[] = {
#include "assets/field/bg/rom_shop4_1_sign05_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_kaunta01_tex[0x200];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_kaunta01_tex[] = {
#include "assets/field/bg/rom_shop4_1_kaunta01_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_kaunta02_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_kaunta02_tex[] = {
#include "assets/field/bg/rom_shop4_1_kaunta02_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_us_sign01_tex[0x400];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_us_sign01_tex[] = {
#include "assets/field/bg/rom_shop4_1_us_sign01_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_us_sign02_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_us_sign02_tex[] = {
#include "assets/field/bg/rom_shop4_1_us_sign02_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_us_sign03_tex[0x600];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_us_sign03_tex[] = {
#include "assets/field/bg/rom_shop4_1_us_sign03_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_sign04_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_sign04_tex[] = {
#include "assets/field/bg/rom_shop4_1_sign04_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_reji01_tex[0x300];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_reji01_tex[] = {
#include "assets/field/bg/rom_shop4_1_reji01_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_reji02_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_reji02_tex[] = {
#include "assets/field/bg/rom_shop4_1_reji02_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_reji03_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_reji03_tex[] = {
#include "assets/field/bg/rom_shop4_1_reji03_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_floor02_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_floor02_tex[] = {
#include "assets/field/bg/rom_shop4_1_floor02_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_floor03_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_floor03_tex[] = {
#include "assets/field/bg/rom_shop4_1_floor03_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_floor04_tex[0x800];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_floor04_tex[] = {
#include "assets/field/bg/rom_shop4_1_floor04_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_shadow01_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_shadow01_tex[] = {
#include "assets/field/bg/rom_shop4_1_shadow01_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_shadow02_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_shadow02_tex[] = {
#include "assets/field/bg/rom_shop4_1_shadow02_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_lamp02_tex[0x80];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_lamp02_tex[] = {
#include "assets/field/bg/rom_shop4_1_lamp02_tex.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_shadow03_tex[0x100];
#else
ATTRIBUTE_ALIGN(32) static u8 rom_shop4_1_shadow03_tex[] = {
#include "assets/field/bg/rom_shop4_1_shadow03_tex.inc"
};
#endif

#ifdef TARGET_PC
static Vtx rom_shop4_1_v[0x1620 / sizeof(Vtx)];
#else
static Vtx rom_shop4_1_v[] = {
#include "assets/field/bg/rom_shop4_1_v.inc"
};
#endif

extern Gfx rom_shop4_1_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 140, 50, 0, 40, 100),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_shadow02_tex, G_IM_FMT_I, 16, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_shop4_1_v[322], 24, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
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
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetPrimColor(0, 100, 255, 255, 200, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_shadow01_tex, G_IM_FMT_I, 16, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop4_1_v[346], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPSetPrimColor(0, 140, 255, 255, 130, 255),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_shadow03_tex, G_IM_FMT_I, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_1_v[350], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPEndDisplayList(),
};

extern Gfx rom_shop4_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_lamp_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_lamp02_tex, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_shop4_1_v[294], 6, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          1, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 2, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_us_sign01_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_us_sign01_tex, G_IM_FMT_CI, 32, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_1_v[300], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_kaunta_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_kaunta01_tex, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop4_1_v[304], 6, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 3, 4  // tri2
                          ),
    gsSPNTriangles_5b(0, 4, 5, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_reji_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_reji03_tex, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_1_v[310], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_us_sign03_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_us_sign03_tex, G_IM_FMT_CI, 48, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_1_v[314], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_sign03_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_sign04_tex, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop4_1_v[318], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_base_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_base_tex, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_1_v[0], 7, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 2, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 2, // tri0
                      6, 0, 2, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_stair_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_stair01_tex, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_1_v[7], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 3, // tri0
                      1, 6, 5, // tri1
                      5, 7, 3, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_floor_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_floor01_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_1_v[15], 23, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          3, 1, 0  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 1,   // tri0
                      6, 7, 8,   // tri1
                      7, 9, 8,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      14, 15, 16, // tri1
                      15, 17, 16, // tri2
                      15, 14, 18  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      20, 19, 22, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_floor02_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_1_v[38], 25, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 1  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      9, 10, 11, // tri1
                      12, 9, 13, // tri2
                      9, 11, 13  // tri3
                      ),
    gsSPNTriangles_5b(10, 14, 11, // tri0
                      15, 16, 17, // tri1
                      18, 15, 19, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(20, 23, 21, // tri0
                      24, 22, 21, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_floor03_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_1_v[63], 24, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 3, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      8, 9, 10,  // tri1
                      5, 11, 10, // tri2
                      9, 5, 10   // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 14, // tri0
                      13, 15, 14, // tri1
                      13, 16, 15, // tri2
                      15, 17, 14  // tri3
                      ),
    gsSPNTriangles_5b(12, 18, 19, // tri0
                      20, 21, 22, // tri1
                      20, 22, 23, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_floor04_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_1_v[87], 26, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,    // tri0
                      8, 7, 9,    // tri1
                      10, 11, 12, // tri2
                      13, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(13, 11, 14, // tri0
                      16, 17, 11, // tri1
                      18, 19, 20, // tri2
                      18, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(20, 22, 21, // tri0
                      23, 24, 21, // tri1
                      22, 25, 21, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_wall_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_wall01_tex, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_1_v[113], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,   // tri0
                      5, 8, 6,   // tri1
                      5, 9, 8,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      14, 15, 12, // tri1
                      16, 17, 14, // tri2
                      16, 14, 12  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      19, 21, 20, // tri1
                      18, 22, 19, // tri2
                      18, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(18, 25, 23, // tri0
                      26, 27, 28, // tri1
                      27, 29, 28, // tri2
                      29, 30, 28  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 28, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_shop4_1_v[145], 32, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      7, 8, 6, // tri1
                      5, 9, 7, // tri2
                      9, 0, 7  // tri3
                      ),
    gsSPNTriangles_5b(5, 10, 9, // tri0
                      10, 0, 9, // tri1
                      10, 3, 0, // tri2
                      11, 12, 8 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 8, // tri0
                      13, 4, 8,  // tri1
                      4, 6, 8,   // tri2
                      14, 15, 16 // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 16, // tri0
                      17, 18, 16, // tri1
                      18, 19, 16, // tri2
                      15, 20, 17  // tri3
                      ),
    gsSPNTriangles_5b(21, 18, 17, // tri0
                      21, 22, 18, // tri1
                      23, 24, 25, // tri2
                      26, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(29, 26, 28, // tri0
                      30, 31, 25, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_shop4_1_v[177], 13, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 0, 3  // tri2
                          ),
    gsSPNTriangles_5b(3, 2, 5, // tri0
                      4, 3, 5, // tri1
                      5, 6, 7, // tri2
                      4, 5, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 4, 7,  // tri0
                      2, 1, 9,  // tri1
                      2, 9, 10, // tri2
                      11, 6, 5  // tri3
                      ),
    gsSPNTriangles_5b(12, 11, 5, // tri0
                      10, 12, 5, // tri1
                      2, 10, 5,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_wall02_tex, G_IM_FMT_CI, 32, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_1_v[190], 16, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 1, 0  // tri2
                          ),
    gsSPNTriangles_5b(4, 0, 5, // tri0
                      6, 7, 4, // tri1
                      6, 4, 5, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(8, 10, 11,  // tri0
                      10, 12, 13, // tri1
                      10, 13, 11, // tri2
                      13, 12, 14  // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_table_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_table02_tex, G_IM_FMT_CI, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_1_v[206], 32, 0),
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
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_table01_tex, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop4_1_v[238], 12, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7,   // tri0
                      8, 9, 10,  // tri1
                      8, 10, 11, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_lamp_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_lamp_tex, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_shop4_1_v[250], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          2, 1, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_sign01_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_sign05_tex, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_shop4_1_v[254], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_kaunta_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_kaunta02_tex, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_1_v[258], 16, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          1, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 2, // tri0
                      6, 7, 8, // tri1
                      6, 8, 9, // tri2
                      10, 0, 3 // tri3
                      ),
    gsSPNTriangles_5b(10, 3, 11,  // tri0
                      12, 13, 14, // tri1
                      12, 14, 15, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_reji_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_reji02_tex, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_1_v[274], 6, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_reji01_tex, G_IM_FMT_CI, 32, 48, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_1_v[280], 10, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          1, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 2, // tri0
                      4, 6, 7, // tri1
                      4, 7, 5, // tri2
                      6, 8, 9  // tri3
                      ),
    gsSPNTriangles_5b(6, 9, 7, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_us_sign02_tex_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_shop4_1_us_sign02_tex, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_shop4_1_v[290], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPEndDisplayList(),
};

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_field_bg_acre_rom_shop4_1_rom_shop4_1_c(void) {
    pc_load_asset("assets/field/bg/rom_shop4_1_floor_tex_pal.bin", rom_shop4_1_floor_tex_pal, 0x20, 0xC2FDC0, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_lamp_tex_pal.bin", rom_shop4_1_lamp_tex_pal, 0x20, 0xC2FDE0, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_base_tex_pal.bin", rom_shop4_1_base_tex_pal, 0x20, 0xC2FE00, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_stair_tex_pal.bin", rom_shop4_1_stair_tex_pal, 0x20, 0xC2FE20, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_table_tex_pal.bin", rom_shop4_1_table_tex_pal, 0x20, 0xC2FE40, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_wall_tex_pal.bin", rom_shop4_1_wall_tex_pal, 0x20, 0xC2FE60, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_sign01_tex_pal.bin", rom_shop4_1_sign01_tex_pal, 0x20, 0xC2FE80, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_kaunta_tex_pal.bin", rom_shop4_1_kaunta_tex_pal, 0x20, 0xC2FEA0, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_us_sign01_tex_pal.bin", rom_shop4_1_us_sign01_tex_pal, 0x20, 0xC2FEC0, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_us_sign02_tex_pal.bin", rom_shop4_1_us_sign02_tex_pal, 0x20, 0xC2FEE0, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_us_sign03_tex_pal.bin", rom_shop4_1_us_sign03_tex_pal, 0x20, 0xC2FF00, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_sign03_tex_pal.bin", rom_shop4_1_sign03_tex_pal, 0x20, 0xC2FF20, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_reji_tex_pal.bin", rom_shop4_1_reji_tex_pal, 0x20, 0xC2FF40, 0, 1);
    pc_load_asset("assets/field/bg/rom_shop4_1_floor01_tex.bin", rom_shop4_1_floor01_tex, 0x800, 0xC2FF60, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_lamp_tex.bin", rom_shop4_1_lamp_tex, 0x80, 0xC30760, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_base_tex.bin", rom_shop4_1_base_tex, 0x200, 0xC307E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_stair01_tex.bin", rom_shop4_1_stair01_tex, 0x100, 0xC309E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_table01_tex.bin", rom_shop4_1_table01_tex, 0x100, 0xC30AE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_table02_tex.bin", rom_shop4_1_table02_tex, 0x100, 0xC30BE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_wall01_tex.bin", rom_shop4_1_wall01_tex, 0x800, 0xC30CE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_wall02_tex.bin", rom_shop4_1_wall02_tex, 0x200, 0xC314E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_sign05_tex.bin", rom_shop4_1_sign05_tex, 0x80, 0xC316E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_kaunta01_tex.bin", rom_shop4_1_kaunta01_tex, 0x200, 0xC31760, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_kaunta02_tex.bin", rom_shop4_1_kaunta02_tex, 0x80, 0xC31960, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_us_sign01_tex.bin", rom_shop4_1_us_sign01_tex, 0x400, 0xC319E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_us_sign02_tex.bin", rom_shop4_1_us_sign02_tex, 0x100, 0xC31DE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_us_sign03_tex.bin", rom_shop4_1_us_sign03_tex, 0x600, 0xC31EE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_sign04_tex.bin", rom_shop4_1_sign04_tex, 0x100, 0xC324E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_reji01_tex.bin", rom_shop4_1_reji01_tex, 0x300, 0xC325E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_reji02_tex.bin", rom_shop4_1_reji02_tex, 0x100, 0xC328E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_reji03_tex.bin", rom_shop4_1_reji03_tex, 0x100, 0xC329E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_floor02_tex.bin", rom_shop4_1_floor02_tex, 0x800, 0xC32AE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_floor03_tex.bin", rom_shop4_1_floor03_tex, 0x800, 0xC332E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_floor04_tex.bin", rom_shop4_1_floor04_tex, 0x800, 0xC33AE0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_shadow01_tex.bin", rom_shop4_1_shadow01_tex, 0x100, 0xC342E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_shadow02_tex.bin", rom_shop4_1_shadow02_tex, 0x100, 0xC343E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_lamp02_tex.bin", rom_shop4_1_lamp02_tex, 0x80, 0xC344E0, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_shadow03_tex.bin", rom_shop4_1_shadow03_tex, 0x100, 0xC34560, 0, 0);
    pc_load_asset("assets/field/bg/rom_shop4_1_v.bin", rom_shop4_1_v, 0x1620, 0xC34660, 0, 2);
}
#endif
