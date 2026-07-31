#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx hem_1_v[0x14D0 / sizeof(Vtx)];
#else
static Vtx hem_1_v[] = {
#include "assets/npc/mdl/hem_1_v.inc"
};
#endif

static Gfx head_hem_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hem_1_v[26], 9, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 380, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hem_1_v[35], 23, 9),
    gsSPNTrianglesInit_5b(14,        // tri count
                          4, 2, 9,   // tri0
                          1, 10, 11, // tri1
                          4, 12, 13  // tri2
                          ),
    gsSPNTriangles_5b(5, 14, 15, // tri0
                      4, 16, 17, // tri1
                      1, 3, 18,  // tri2
                      5, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(2, 0, 21,  // tri0
                      3, 5, 22,  // tri1
                      4, 23, 24, // tri2
                      0, 1, 25   // tri3
                      ),
    gsSPNTriangles_5b(1, 27, 26, // tri0
                      5, 28, 29, // tri1
                      0, 30, 31, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&hem_1_v[58], 20, 9),
    gsSPNTrianglesInit_5b(4,        // tri count
                          6, 9, 10, // tri0
                          6, 11, 8, // tri1
                          7, 4, 12  // tri2
                          ),
    gsSPNTriangles_5b(5, 8, 13, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          14, 15, 16, // tri0
                          17, 18, 19, // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(8,          // tri count
                          20, 21, 22, // tri0
                          23, 21, 24, // tri1
                          25, 21, 20  // tri2
                          ),
    gsSPNTriangles_5b(24, 21, 26, // tri0
                      27, 21, 25, // tri1
                      26, 21, 27, // tri2
                      28, 21, 23  // tri3
                      ),
    gsSPNTriangles_5b(22, 21, 28, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsSPVertex(&hem_1_v[78], 14, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 6,  // tri0
                      10, 4, 3, // tri1
                      3, 0, 10, // tri2
                      5, 11, 3  // tri3
                      ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      6, 11, 5,  // tri1
                      0, 12, 10, // tri2
                      8, 13, 9   // tri3
                      ),
    gsSPNTriangles_5b(9, 13, 2, // tri0
                      2, 12, 0, // tri1
                      2, 1, 9,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x340, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 60, 124),
    gsSPVertex(&hem_1_v[92], 25, 0),
    gsSPNTrianglesInit_5b(30,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 1  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,   // tri0
                      11, 12, 13, // tri1
                      13, 7, 11,  // tri2
                      14, 4, 15   // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 9, // tri0
                      2, 1, 13,  // tri1
                      2, 13, 16, // tri2
                      5, 4, 14   // tri3
                      ),
    gsSPNTriangles_5b(5, 14, 17,  // tri0
                      18, 19, 12, // tri1
                      4, 19, 18,  // tri2
                      10, 20, 8   // tri3
                      ),
    gsSPNTriangles_5b(1, 21, 6,  // tri0
                      9, 8, 14,  // tri1
                      13, 1, 7,  // tri2
                      16, 13, 12 // tri3
                      ),
    gsSPNTriangles_5b(16, 12, 22, // tri0
                      22, 12, 19, // tri1
                      22, 19, 3,  // tri2
                      12, 11, 18  // tri3
                      ),
    gsSPNTriangles_5b(18, 15, 4, // tri0
                      17, 14, 8, // tri1
                      17, 8, 23, // tri2
                      23, 8, 20  // tri3
                      ),
    gsSPNTriangles_5b(23, 20, 24, // tri0
                      3, 19, 4,   // tri1
                      0, 21, 1,   // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx feel_hem_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hem_1_v[117], 16, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          2, 4, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 1, 3, // tri0
                      2, 6, 4, // tri1
                      1, 7, 2, // tri2
                      5, 4, 8  // tri3
                      ),
    gsSPNTriangles_5b(9, 1, 5, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x580, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1,          // tri count
                          10, 11, 12, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          13, 14, 15, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx mouth_hem_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hem_1_v[0], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hem_1_v[5], 21, 5),
    gsSPNTrianglesInit_5b(10,      // tri count
                          2, 6, 5, // tri0
                          2, 8, 7, // tri1
                          3, 10, 9 // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 11, // tri0
                      0, 2, 12, // tri1
                      3, 0, 13, // tri2
                      1, 4, 14  // tri3
                      ),
    gsSPNTriangles_5b(4, 16, 15, // tri0
                      4, 3, 17,  // tri1
                      3, 19, 18, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(5,          // tri count
                          20, 21, 22, // tri0
                          23, 21, 20, // tri1
                          24, 21, 25  // tri2
                          ),
    gsSPNTriangles_5b(25, 21, 23, // tri0
                      22, 21, 24, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_hem_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hem_1_v[133], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hem_1_v[138], 16, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 5, 6, // tri0
                          4, 7, 8, // tri1
                          4, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 11,  // tri0
                      2, 4, 12,  // tri1
                      0, 13, 14, // tri2
                      3, 0, 15   // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 16, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          17, 18, 19, // tri0
                          20, 19, 18, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_hem_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hem_1_v[154], 9, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 3, 5  // tri2
                          ),
    gsSPNTriangles_5b(7, 0, 6, // tri0
                      7, 6, 5, // tri1
                      1, 0, 7, // tri2
                      2, 8, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_hem_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hem_1_v[163], 9, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 380, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hem_1_v[172], 22, 9),
    gsSPNTrianglesInit_5b(14,       // tri count
                          4, 5, 9,  // tri0
                          2, 3, 10, // tri1
                          8, 11, 12 // tri2
                          ),
    gsSPNTriangles_5b(3, 8, 13,  // tri0
                      2, 14, 15, // tri1
                      0, 6, 16,  // tri2
                      0, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(5, 19, 20, // tri0
                      8, 4, 21,  // tri1
                      1, 23, 22, // tri2
                      7, 1, 24   // tri3
                      ),
    gsSPNTriangles_5b(6, 25, 26, // tri0
                      0, 27, 28, // tri1
                      1, 29, 30, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&hem_1_v[194], 15, 9),
    gsSPNTrianglesInit_5b(2,        // tri count
                          1, 2, 9,  // tri0
                          5, 0, 10, // tri1
                          0, 0, 0   // tri2
                          ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7,          // tri count
                          11, 12, 13, // tri0
                          14, 15, 16, // tri1
                          14, 16, 17  // tri2
                          ),
    gsSPNTriangles_5b(17, 13, 18, // tri0
                      14, 17, 18, // tri1
                      18, 13, 12, // tri2
                      13, 19, 11  // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          20, 21, 22, // tri0
                          23, 20, 22, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx base_hem_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hem_1_v[209], 32, 0),
    gsSPNTrianglesInit_5b(39,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      6, 8, 9,   // tri1
                      10, 7, 11, // tri2
                      5, 1, 0    // tri3
                      ),
    gsSPNTriangles_5b(12, 8, 7,   // tri0
                      12, 7, 10,  // tri1
                      13, 14, 15, // tri2
                      13, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      17, 19, 20, // tri1
                      10, 2, 1,   // tri2
                      10, 1, 12   // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 5,   // tri0
                      9, 21, 22, // tri1
                      9, 22, 6,  // tri2
                      11, 23, 3  // tri3
                      ),
    gsSPNTriangles_5b(5, 8, 12,   // tri0
                      20, 19, 14, // tri1
                      20, 14, 13, // tri2
                      11, 7, 6    // tri3
                      ),
    gsSPNTriangles_5b(12, 1, 5,  // tri0
                      11, 2, 10, // tri1
                      21, 9, 5,  // tri2
                      5, 24, 21  // tri3
                      ),
    gsSPNTriangles_5b(11, 6, 22,  // tri0
                      11, 22, 25, // tri1
                      16, 15, 18, // tri2
                      16, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(11, 25, 26, // tri0
                      11, 26, 5,  // tri1
                      3, 2, 11,   // tri2
                      4, 0, 3     // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 23,   // tri0
                      27, 28, 29, // tri1
                      27, 29, 30, // tri2
                      31, 25, 22  // tri3
                      ),
    gsSPVertex(&hem_1_v[241], 12, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 5, 0  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 4, // tri0
                      6, 4, 3, // tri1
                      2, 1, 7, // tri2
                      2, 7, 6  // tri3
                      ),
    gsSPNTriangles_5b(8, 0, 2,  // tri0
                      8, 2, 9,  // tri1
                      10, 3, 0, // tri2
                      10, 0, 8  // tri3
                      ),
    gsSPNTriangles_5b(11, 6, 3,  // tri0
                      11, 3, 10, // tri1
                      9, 2, 6,   // tri2
                      9, 6, 11   // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 380, 124),
    gsSPVertex(&hem_1_v[253], 27, 0),
    gsSPNTrianglesInit_5b(32,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 2, 1  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      10, 11, 12, // tri1
                      13, 8, 14,  // tri2
                      15, 14, 7   // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 7,   // tri0
                      12, 16, 10, // tri1
                      7, 14, 8,   // tri2
                      4, 17, 18   // tri3
                      ),
    gsSPNTriangles_5b(19, 6, 1,  // tri0
                      4, 3, 17,  // tri1
                      7, 10, 15, // tri2
                      20, 21, 2  // tri3
                      ),
    gsSPNTriangles_5b(3, 22, 23,  // tri0
                      20, 24, 14, // tri1
                      10, 16, 23, // tri2
                      15, 25, 14  // tri3
                      ),
    gsSPNTriangles_5b(6, 13, 24,  // tri0
                      16, 12, 17, // tri1
                      17, 3, 16,  // tri2
                      14, 24, 13  // tri3
                      ),
    gsSPNTriangles_5b(24, 2, 6,   // tri0
                      23, 26, 10, // tri1
                      23, 16, 3,  // tri2
                      14, 25, 20  // tri3
                      ),
    gsSPNTriangles_5b(11, 10, 7, // tri0
                      2, 24, 20, // tri1
                      5, 22, 3,  // tri2
                      2, 21, 0   // tri3
                      ),
    gsSPNTriangles_5b(10, 26, 15, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&hem_1_v[280], 32, 0),
    gsSPNTrianglesInit_5b(39,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      6, 8, 9,   // tri1
                      10, 7, 11, // tri2
                      5, 1, 0    // tri3
                      ),
    gsSPNTriangles_5b(12, 8, 7,   // tri0
                      12, 7, 10,  // tri1
                      13, 14, 15, // tri2
                      13, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      17, 19, 20, // tri1
                      10, 2, 1,   // tri2
                      10, 1, 12   // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 5,   // tri0
                      9, 21, 22, // tri1
                      9, 22, 6,  // tri2
                      11, 23, 3  // tri3
                      ),
    gsSPNTriangles_5b(5, 8, 12,   // tri0
                      20, 19, 14, // tri1
                      20, 14, 13, // tri2
                      11, 7, 6    // tri3
                      ),
    gsSPNTriangles_5b(12, 1, 5,  // tri0
                      11, 2, 10, // tri1
                      21, 9, 5,  // tri2
                      5, 24, 21  // tri3
                      ),
    gsSPNTriangles_5b(11, 6, 22,  // tri0
                      11, 22, 25, // tri1
                      16, 15, 18, // tri2
                      16, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(11, 25, 26, // tri0
                      11, 26, 5,  // tri1
                      3, 2, 11,   // tri2
                      4, 0, 3     // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 23,   // tri0
                      27, 28, 29, // tri1
                      27, 29, 30, // tri2
                      31, 25, 22  // tri3
                      ),
    gsSPVertex(&hem_1_v[312], 21, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 5, 0  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 4, // tri0
                      6, 4, 3, // tri1
                      2, 1, 7, // tri2
                      2, 7, 6  // tri3
                      ),
    gsSPNTriangles_5b(8, 0, 2,  // tri0
                      8, 2, 9,  // tri1
                      10, 3, 0, // tri2
                      10, 0, 8  // tri3
                      ),
    gsSPNTriangles_5b(11, 6, 3,  // tri0
                      11, 3, 10, // tri1
                      9, 2, 6,   // tri2
                      9, 6, 11   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8,          // tri count
                          12, 13, 14, // tri0
                          15, 16, 17, // tri1
                          16, 12, 18  // tri2
                          ),
    gsSPNTriangles_5b(12, 16, 19, // tri0
                      17, 20, 15, // tri1
                      14, 18, 12, // tri2
                      13, 12, 19  // tri3
                      ),
    gsSPNTriangles_5b(15, 19, 16, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_hem_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,500,0 },
    /* joint 1 */ { base_hem_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-700,0 },
    /* joint 3 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 200,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 201,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,700,0 },
    /* joint 7 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 201,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 199,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 300,0,-950 },
    /* joint 11 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_hem_model, 3, cKF_JOINT_FLAG_DISP_OPA, 603,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 600,-1500,0 },
    /* joint 15 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 600,1500,0 },
    /* joint 18 */ { Rarm1_hem_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_hem_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 1197,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,1300 },
    /* joint 23 */ { mouth_hem_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_hem_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { feel_hem_model, 0, cKF_JOINT_FLAG_DISP_OPA, 501,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_hem_1 = { 26, 7, cKF_je_r_hem_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_hem_1_c(void) {
    pc_load_asset("assets/npc/mdl/hem_1_v.bin", hem_1_v, 0x14D0, 0x52B8C0, 0, 2);
}
#endif
