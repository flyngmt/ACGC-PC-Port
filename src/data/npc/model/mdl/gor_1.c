#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx gor_1_v[0x1AD0 / sizeof(Vtx)];
#else
static Vtx gor_1_v[] = {
#include "assets/npc/mdl/gor_1_v.inc"
};
#endif

static Gfx head_gor_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&gor_1_v[32], 10, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&gor_1_v[42], 21, 10),
    gsSPNTrianglesInit_5b(13,        // tri count
                          9, 10, 11, // tri0
                          0, 7, 12,  // tri1
                          0, 13, 14  // tri2
                          ),
    gsSPNTriangles_5b(7, 15, 16, // tri0
                      0, 17, 18, // tri1
                      8, 19, 7,  // tri2
                      0, 20, 9   // tri3
                      ),
    gsSPNTriangles_5b(4, 21, 22, // tri0
                      1, 9, 23,  // tri1
                      1, 24, 25, // tri2
                      8, 4, 26   // tri3
                      ),
    gsSPNTriangles_5b(8, 27, 28, // tri0
                      9, 29, 30, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&gor_1_v[63], 13, 10),
    gsSPNTrianglesInit_5b(3,         // tri count
                          9, 10, 11, // tri0
                          8, 12, 13, // tri1
                          8, 14, 15  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 252, 124),
    gsSPNTrianglesInit_5b(5,         // tri count
                          5, 16, 17, // tri0
                          5, 2, 18,  // tri1
                          6, 19, 20  // tri2
                          ),
    gsSPNTriangles_5b(3, 6, 21, // tri0
                      6, 5, 22, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&gor_1_v[76], 21, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          2, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 3, // tri0
                      6, 7, 3, // tri1
                      8, 5, 2, // tri2
                      6, 5, 8  // tri3
                      ),
    gsSPNTriangles_5b(9, 7, 6,  // tri0
                      2, 4, 0,  // tri1
                      6, 10, 9, // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(2, 1, 8,   // tri0
                      1, 12, 13, // tri1
                      0, 14, 15, // tri2
                      16, 17, 10 // tri3
                      ),
    gsSPNTriangles_5b(15, 18, 12, // tri0
                      15, 1, 0,   // tri1
                      10, 8, 16,  // tri2
                      13, 8, 1    // tri3
                      ),
    gsSPNTriangles_5b(13, 16, 8,  // tri0
                      11, 10, 17, // tri1
                      8, 10, 6,   // tri2
                      11, 19, 9   // tri3
                      ),
    gsSPNTriangles_5b(17, 20, 11, // tri0
                      12, 1, 15,  // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&gor_1_v[97], 22, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 4, // tri1
                          5, 0, 4  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      9, 1, 0,   // tri1
                      2, 1, 10,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(2, 3, 0,    // tri0
                      14, 7, 15,  // tri1
                      15, 16, 14, // tri2
                      8, 7, 17    // tri3
                      ),
    gsSPNTriangles_5b(18, 13, 19, // tri0
                      7, 14, 10,  // tri1
                      18, 14, 20, // tri2
                      20, 11, 18  // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 20, // tri0
                      18, 19, 10, // tri1
                      9, 8, 17,   // tri2
                      0, 5, 9     // tri3
                      ),
    gsSPNTriangles_5b(7, 6, 15,  // tri0
                      10, 1, 9,  // tri1
                      19, 13, 2, // tri2
                      9, 17, 10  // tri3
                      ),
    gsSPNTriangles_5b(10, 17, 7,  // tri0
                      10, 19, 2,  // tri1
                      10, 14, 18, // tri2
                      13, 18, 11  // tri3
                      ),
    gsSPNTriangles_5b(8, 21, 6, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&gor_1_v[119], 29, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 6, 10,  // tri0
                      3, 5, 11,  // tri1
                      2, 12, 13, // tri2
                      14, 15, 16 // tri3
                      ),
    gsSPNTriangles_5b(17, 16, 10, // tri0
                      18, 19, 9,  // tri1
                      17, 20, 14, // tri2
                      16, 17, 14  // tri3
                      ),
    gsSPNTriangles_5b(18, 9, 16, // tri0
                      0, 10, 8,  // tri1
                      10, 16, 9, // tri2
                      10, 0, 17  // tri3
                      ),
    gsSPNTriangles_5b(6, 9, 11,   // tri0
                      20, 17, 21, // tri1
                      5, 7, 6,    // tri2
                      16, 15, 18  // tri3
                      ),
    gsSPNTriangles_5b(21, 17, 0, // tri0
                      8, 10, 6,  // tri1
                      8, 1, 0,   // tri2
                      21, 2, 13  // tri3
                      ),
    gsSPNTriangles_5b(13, 20, 21, // tri0
                      0, 2, 21,   // tri1
                      11, 9, 19,  // tri2
                      11, 19, 3   // tri3
                      ),
    gsSPNTriangles_5b(11, 5, 6, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 60, 60),
    gsSPNTrianglesInit_5b(5,          // tri count
                          22, 23, 24, // tri0
                          25, 26, 23, // tri1
                          25, 23, 22  // tri2
                          ),
    gsSPNTriangles_5b(27, 26, 25, // tri0
                      27, 25, 28, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&gor_1_v[148], 20, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 0, 2  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 6,   // tri0
                      5, 9, 3,   // tri1
                      2, 7, 6,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      10, 12, 16, // tri1
                      16, 17, 18, // tri2
                      15, 19, 13  // tri3
                      ),
    gsSPNTriangles_5b(16, 18, 10, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx mouth_gor_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&gor_1_v[0], 7, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 60, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&gor_1_v[7], 18, 7),
    gsSPNTrianglesInit_5b(2,       // tri count
                          3, 7, 8, // tri0
                          3, 9, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 60, 60),
    gsSPNTrianglesInit_5b(7,         // tri count
                          2, 4, 10,  // tri0
                          5, 11, 12, // tri1
                          4, 6, 13   // tri2
                          ),
    gsSPNTriangles_5b(4, 14, 15, // tri0
                      5, 1, 16,  // tri1
                      6, 5, 17,  // tri2
                      6, 18, 19  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 60, 60),
    gsSPNTrianglesInit_5b(3,          // tri count
                          20, 21, 22, // tri0
                          22, 23, 24, // tri1
                          22, 24, 20  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 60, 60),
    gsSPVertex(&gor_1_v[25], 7, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 5, 0  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 5, // tri0
                      0, 2, 6, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_gor_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&gor_1_v[214], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&gor_1_v[218], 21, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          2, 5, 4, // tri0
                          0, 7, 6, // tri1
                          1, 9, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 10, // tri0
                      0, 2, 11, // tri1
                      3, 0, 12, // tri2
                      1, 3, 13  // tri3
                      ),
    gsSPNTriangles_5b(0, 14, 15, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(8,          // tri count
                          16, 17, 18, // tri0
                          18, 19, 20, // tri1
                          20, 19, 21  // tri2
                          ),
    gsSPNTriangles_5b(19, 22, 23, // tri0
                      24, 18, 17, // tri1
                      24, 22, 18, // tri2
                      18, 22, 19  // tri3
                      ),
    gsSPNTriangles_5b(23, 22, 24, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_gor_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&gor_1_v[239], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&gor_1_v[244], 16, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          4, 6, 5, // tri0
                          0, 8, 7, // tri1
                          4, 0, 9  // tri2
                          ),
    gsSPNTriangles_5b(1, 10, 11, // tri0
                      1, 12, 0,  // tri1
                      4, 13, 3,  // tri2
                      2, 3, 14   // tri3
                      ),
    gsSPNTriangles_5b(3, 16, 15, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          17, 18, 19, // tri0
                          20, 18, 17, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_gor_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&gor_1_v[168], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&gor_1_v[172], 21, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          1, 5, 4, // tri0
                          3, 7, 6, // tri1
                          0, 9, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 10,  // tri0
                      3, 11, 12, // tri1
                      3, 2, 13,  // tri2
                      2, 0, 14   // tri3
                      ),
    gsSPNTriangles_5b(1, 3, 15, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(8,          // tri count
                          16, 17, 18, // tri0
                          18, 19, 20, // tri1
                          21, 19, 18  // tri2
                          ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      17, 16, 24, // tri1
                      16, 22, 24, // tri2
                      23, 22, 16  // tri3
                      ),
    gsSPNTriangles_5b(24, 22, 21, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_gor_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&gor_1_v[193], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&gor_1_v[198], 16, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          4, 6, 5, // tri0
                          2, 8, 7, // tri1
                          2, 4, 9  // tri2
                          ),
    gsSPNTriangles_5b(3, 10, 11, // tri0
                      2, 12, 3,  // tri1
                      0, 13, 4,  // tri2
                      1, 3, 14   // tri3
                      ),
    gsSPNTriangles_5b(1, 16, 15, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          17, 18, 19, // tri0
                          19, 18, 20, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx chest_gor_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&gor_1_v[260], 10, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x340, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&gor_1_v[270], 8, 10),
    gsSPNTrianglesInit_5b(6,         // tri count
                          2, 10, 11, // tri0
                          2, 12, 13, // tri1
                          1, 7, 14   // tri2
                          ),
    gsSPNTriangles_5b(9, 0, 15, // tri0
                      2, 1, 16, // tri1
                      0, 2, 17, // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 252, 124),
    gsSPVertex(&gor_1_v[278], 17, 10),
    gsSPNTrianglesInit_5b(10,        // tri count
                          3, 4, 10,  // tri0
                          4, 12, 11, // tri1
                          3, 13, 14  // tri2
                          ),
    gsSPNTriangles_5b(4, 15, 16, // tri0
                      4, 8, 17,  // tri1
                      6, 18, 19, // tri2
                      6, 3, 20   // tri3
                      ),
    gsSPNTriangles_5b(5, 21, 22, // tri0
                      8, 23, 24, // tri1
                      8, 25, 26, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&gor_1_v[295], 19, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(7, 6, 9,    // tri0
                      10, 11, 12, // tri1
                      9, 5, 4,    // tri2
                      4, 7, 9     // tri3
                      ),
    gsSPNTriangles_5b(8, 13, 6,  // tri0
                      5, 14, 3,  // tri1
                      2, 15, 16, // tri2
                      12, 17, 18 // tri3
                      ),
    gsSPNTriangles_5b(2, 16, 0,   // tri0
                      18, 10, 12, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_gor_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&gor_1_v[359], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&gor_1_v[363], 18, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          2, 3, 4, // tri0
                          1, 5, 6, // tri1
                          0, 2, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 8, 9,  // tri0
                      1, 10, 3, // tri1
                      1, 0, 11, // tri2
                      1, 13, 12 // tri3
                      ),
    gsSPNTriangles_5b(2, 15, 14, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(6,          // tri count
                          16, 17, 18, // tri0
                          19, 17, 16, // tri1
                          20, 21, 18  // tri2
                          ),
    gsSPNTriangles_5b(18, 17, 19, // tri0
                      16, 20, 19, // tri1
                      19, 20, 18, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_gor_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&gor_1_v[381], 9, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&gor_1_v[390], 14, 9),
    gsSPNTrianglesInit_5b(2,         // tri count
                          5, 9, 10,  // tri0
                          5, 12, 11, // tri1
                          0, 0, 0    // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x340, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,        // tri count
                          0, 1, 13, // tri0
                          1, 3, 14, // tri1
                          1, 15, 16 // tri2
                          ),
    gsSPNTriangles_5b(6, 0, 17, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x3C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 60, 60),
    gsSPNTrianglesInit_5b(4,         // tri count
                          8, 18, 4,  // tri0
                          4, 19, 20, // tri1
                          2, 4, 21   // tri2
                          ),
    gsSPNTriangles_5b(7, 22, 8, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_gor_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&gor_1_v[314], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&gor_1_v[318], 18, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          3, 2, 4, // tri0
                          0, 5, 6, // tri1
                          2, 1, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 8, 9,  // tri0
                      3, 10, 0, // tri1
                      1, 0, 11, // tri2
                      0, 13, 12 // tri3
                      ),
    gsSPNTriangles_5b(2, 15, 14, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(6,          // tri count
                          16, 17, 18, // tri0
                          18, 17, 19, // tri1
                          16, 20, 21  // tri2
                          ),
    gsSPNTriangles_5b(19, 17, 16, // tri0
                      19, 21, 18, // tri1
                      16, 21, 19, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_gor_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&gor_1_v[336], 9, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&gor_1_v[345], 14, 9),
    gsSPNTrianglesInit_5b(2,         // tri count
                          6, 10, 9,  // tri0
                          6, 11, 12, // tri1
                          0, 0, 0    // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x340, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,         // tri count
                          1, 13, 14, // tri0
                          0, 4, 15,  // tri1
                          1, 0, 16   // tri2
                          ),
    gsSPNTriangles_5b(8, 1, 17, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x3C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 60, 60),
    gsSPNTrianglesInit_5b(4,         // tri count
                          3, 18, 19, // tri0
                          5, 7, 20,  // tri1
                          3, 2, 21   // tri2
                          ),
    gsSPNTriangles_5b(3, 22, 7, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_gor_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x340, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&gor_1_v[404], 25, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          2, 1, 3  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 6,  // tri0
                      1, 6, 3,  // tri1
                      7, 4, 8,  // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(2, 9, 0,  // tri0
                      8, 12, 7, // tri1
                      11, 0, 9, // tri2
                      4, 7, 2   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x3C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 60, 60),
    gsSPNTrianglesInit_5b(8,          // tri count
                          13, 14, 15, // tri0
                          13, 15, 16, // tri1
                          17, 14, 13  // tri2
                          ),
    gsSPNTriangles_5b(13, 18, 17, // tri0
                      19, 20, 16, // tri1
                      15, 14, 21, // tri2
                      16, 15, 19  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 24, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_gor_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_gor_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-400,0 },
    /* joint 3 */ { Lfoot1_gor_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_gor_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,400,0 },
    /* joint 7 */ { Rfoot1_gor_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_gor_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 75,0,-875 },
    /* joint 11 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_gor_model, 3, cKF_JOINT_FLAG_DISP_OPA, 546,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 825,-1400,350 },
    /* joint 15 */ { Larm1_gor_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_gor_model, 0, cKF_JOINT_FLAG_DISP_OPA, 658,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 825,1400,350 },
    /* joint 18 */ { Rarm1_gor_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_gor_model, 1, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 1187,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 137,0,750 },
    /* joint 23 */ { mouth_gor_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_gor_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1300,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_gor_1 = { 26, 12, cKF_je_r_gor_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_gor_1_c(void) {
    pc_load_asset("assets/npc/mdl/gor_1_v.bin", gor_1_v, 0x1AD0, 0x50A200, 0, 2);
}
#endif
