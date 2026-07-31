#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx oct_1_v[0x1D80 / sizeof(Vtx)];
#else
static Vtx oct_1_v[] = {
#include "assets/npc/mdl/oct_1_v.inc"
};
#endif

static Gfx head_oct_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&oct_1_v[0], 19, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          2, 6, 0  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 4,  // tri0
                      9, 10, 7, // tri1
                      10, 2, 1, // tri2
                      5, 11, 3  // tri3
                      ),
    gsSPNTriangles_5b(9, 2, 10,  // tri0
                      7, 3, 9,   // tri1
                      1, 12, 10, // tri2
                      4, 3, 7    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,          // tri count
                          13, 14, 15, // tri0
                          13, 15, 16, // tri1
                          15, 17, 18  // tri2
                          ),
    gsSPNTriangles_5b(15, 18, 16, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&oct_1_v[19], 32, 0),
    gsSPNTrianglesInit_5b(37,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 5  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,   // tri0
                      8, 10, 11,  // tri1
                      12, 13, 14, // tri2
                      2, 15, 0    // tri3
                      ),
    gsSPNTriangles_5b(2, 16, 17, // tri0
                      18, 16, 1, // tri1
                      19, 20, 7, // tri2
                      16, 2, 1   // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 20, // tri0
                      1, 0, 23,   // tri1
                      3, 16, 18,  // tri2
                      21, 0, 15   // tri3
                      ),
    gsSPNTriangles_5b(21, 15, 22, // tri0
                      17, 7, 20,  // tri1
                      24, 12, 25, // tri2
                      16, 5, 17   // tri3
                      ),
    gsSPNTriangles_5b(5, 7, 17,   // tri0
                      17, 22, 15, // tri1
                      25, 12, 26, // tri2
                      20, 22, 17  // tri3
                      ),
    gsSPNTriangles_5b(13, 21, 19, // tri0
                      19, 7, 27,  // tri1
                      14, 13, 19, // tri2
                      15, 2, 17   // tri3
                      ),
    gsSPNTriangles_5b(12, 24, 28, // tri0
                      14, 26, 12, // tri1
                      13, 12, 23, // tri2
                      3, 29, 30   // tri3
                      ),
    gsSPNTriangles_5b(11, 6, 31, // tri0
                      11, 31, 8, // tri1
                      29, 3, 10, // tri2
                      1, 23, 28  // tri3
                      ),
    gsSPNTriangles_5b(28, 23, 12, // tri0
                      4, 3, 30,   // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&oct_1_v[51], 19, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          3, 4, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      8, 9, 10,  // tri1
                      8, 3, 2,   // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 14, // tri0
                      15, 16, 2,  // tri1
                      17, 18, 13, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_oct_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&oct_1_v[117], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&oct_1_v[122], 25, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          2, 5, 3, // tri0
                          2, 7, 6, // tri1
                          0, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 10, // tri0
                      2, 1, 11, // tri1
                      4, 12, 0, // tri2
                      0, 14, 13 // tri3
                      ),
    gsSPNTriangles_5b(2, 15, 16, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(14,         // tri count
                          17, 18, 19, // tri0
                          20, 21, 22, // tri1
                          20, 23, 24  // tri2
                          ),
    gsSPNTriangles_5b(19, 22, 21, // tri0
                      22, 23, 20, // tri1
                      19, 18, 25, // tri2
                      25, 23, 22  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 28, // tri0
                      21, 20, 27, // tri1
                      27, 20, 24, // tri2
                      29, 21, 27  // tri3
                      ),
    gsSPNTriangles_5b(19, 21, 29, // tri0
                      25, 22, 19, // tri1
                      24, 28, 27, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_oct_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&oct_1_v[147], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&oct_1_v[151], 11, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 5, 4, // tri0
                          3, 7, 6, // tri1
                          2, 9, 8  // tri2
                          ),
    gsSPNTriangles_5b(3, 2, 10, // tri0
                      2, 0, 11, // tri1
                      1, 3, 12, // tri2
                      1, 13, 14 // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_oct_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&oct_1_v[70], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&oct_1_v[75], 14, 5),
    gsSPNTrianglesInit_5b(9,       // tri count
                          3, 5, 2, // tri0
                          2, 7, 6, // tri1
                          0, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 10, // tri0
                      1, 2, 11, // tri1
                      0, 12, 4, // tri2
                      0, 14, 13 // tri3
                      ),
    gsSPNTriangles_5b(2, 15, 16, // tri0
                      2, 17, 18, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&oct_1_v[89], 13, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 0, // tri0
                      5, 7, 3, // tri1
                      8, 1, 0, // tri2
                      3, 7, 8  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11, // tri0
                      10, 5, 4,  // tri1
                      6, 5, 10,  // tri2
                      12, 4, 0   // tri3
                      ),
    gsSPNTriangles_5b(0, 3, 8,  // tri0
                      10, 9, 6, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_oct_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&oct_1_v[102], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&oct_1_v[106], 11, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 5, 4, // tri0
                          3, 7, 6, // tri1
                          2, 9, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 3, 10, // tri0
                      0, 2, 11, // tri1
                      3, 1, 12, // tri2
                      1, 13, 14 // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_oct_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&oct_1_v[162], 7, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&oct_1_v[169], 20, 7),
    gsSPNTrianglesInit_5b(13,       // tri count
                          3, 1, 7,  // tri0
                          6, 8, 9,  // tri1
                          3, 10, 11 // tri2
                          ),
    gsSPNTriangles_5b(2, 12, 0,  // tri0
                      2, 13, 14, // tri1
                      1, 16, 15, // tri2
                      0, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(0, 19, 20, // tri0
                      1, 21, 22, // tri1
                      6, 3, 23,  // tri2
                      2, 6, 24   // tri3
                      ),
    gsSPNTriangles_5b(4, 0, 25, // tri0
                      5, 26, 1, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPVertex(&oct_1_v[189], 9, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 4, // tri1
                          0, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 7, // tri0
                      2, 5, 0, // tri1
                      1, 8, 2, // tri2
                      6, 3, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot3_oct_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&oct_1_v[329], 12, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&oct_1_v[341], 10, 12),
    gsSPNTrianglesInit_5b(7,         // tri count
                          1, 12, 13, // tri0
                          0, 1, 14,  // tri1
                          3, 15, 16  // tri2
                          ),
    gsSPNTriangles_5b(2, 17, 3,  // tri0
                      2, 18, 19, // tri1
                      1, 3, 20,  // tri2
                      2, 0, 21   // tri3
                      ),
    gsSPVertex(&oct_1_v[351], 10, 12),
    gsSPNTrianglesInit_5b(7,         // tri count
                          4, 12, 6,  // tri0
                          6, 13, 14, // tri1
                          6, 15, 7   // tri2
                          ),
    gsSPNTriangles_5b(7, 16, 17, // tri0
                      4, 18, 19, // tri1
                      4, 5, 20,  // tri2
                      5, 7, 21   // tri3
                      ),
    gsSPVertex(&oct_1_v[361], 19, 12),
    gsSPNTrianglesInit_5b(7,         // tri count
                          11, 12, 8, // tri0
                          8, 13, 14, // tri1
                          11, 15, 16 // tri2
                          ),
    gsSPNTriangles_5b(11, 10, 17, // tri0
                      10, 9, 18,  // tri1
                      9, 19, 20,  // tri2
                      8, 21, 9    // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          22, 23, 24, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          25, 26, 27, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          28, 29, 30, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_oct_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&oct_1_v[380], 12, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&oct_1_v[392], 12, 12),
    gsSPNTrianglesInit_5b(8,         // tri count
                          1, 13, 12, // tri0
                          9, 14, 15, // tri1
                          9, 16, 17  // tri2
                          ),
    gsSPNTriangles_5b(1, 18, 19, // tri0
                      0, 9, 20,  // tri1
                      9, 6, 21,  // tri2
                      1, 0, 22   // tri3
                      ),
    gsSPNTriangles_5b(6, 1, 23, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPVertex(&oct_1_v[404], 12, 12),
    gsSPNTrianglesInit_5b(8,         // tri count
                          2, 3, 12,  // tri0
                          3, 13, 14, // tri1
                          8, 15, 16  // tri2
                          ),
    gsSPNTriangles_5b(11, 17, 18, // tri0
                      11, 8, 19,  // tri1
                      3, 11, 20,  // tri2
                      8, 2, 21    // tri3
                      ),
    gsSPNTriangles_5b(11, 23, 22, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&oct_1_v[416], 12, 12),
    gsSPNTrianglesInit_5b(8,         // tri count
                          5, 7, 12,  // tri0
                          4, 13, 14, // tri1
                          4, 5, 15   // tri2
                          ),
    gsSPNTriangles_5b(7, 10, 16, // tri0
                      7, 17, 18, // tri1
                      10, 4, 19, // tri2
                      4, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(7, 22, 23, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_oct_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&oct_1_v[428], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&oct_1_v[432], 26, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 4, 5, // tri0
                          1, 6, 7, // tri1
                          3, 2, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 9,   // tri0
                      0, 11, 10, // tri1
                      0, 12, 1,  // tri2
                      0, 3, 13   // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          14, 15, 16, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(13,         // tri count
                          17, 18, 19, // tri0
                          17, 19, 20, // tri1
                          20, 21, 22  // tri2
                          ),
    gsSPNTriangles_5b(23, 24, 25, // tri0
                      25, 26, 23, // tri1
                      27, 28, 29, // tri2
                      29, 24, 27  // tri3
                      ),
    gsSPNTriangles_5b(24, 23, 27, // tri0
                      18, 26, 25, // tri1
                      29, 28, 21, // tri2
                      20, 22, 17  // tri3
                      ),
    gsSPNTriangles_5b(20, 29, 21, // tri0
                      25, 19, 18, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot3_oct_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&oct_1_v[198], 12, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&oct_1_v[210], 10, 12),
    gsSPNTrianglesInit_5b(7,         // tri count
                          1, 12, 13, // tri0
                          1, 0, 14,  // tri1
                          3, 15, 16  // tri2
                          ),
    gsSPNTriangles_5b(3, 17, 2,  // tri0
                      2, 18, 19, // tri1
                      3, 1, 20,  // tri2
                      0, 2, 21   // tri3
                      ),
    gsSPVertex(&oct_1_v[220], 10, 12),
    gsSPNTrianglesInit_5b(7,         // tri count
                          6, 12, 4,  // tri0
                          6, 13, 14, // tri1
                          7, 15, 6   // tri2
                          ),
    gsSPNTriangles_5b(7, 16, 17, // tri0
                      4, 18, 19, // tri1
                      5, 4, 20,  // tri2
                      7, 5, 21   // tri3
                      ),
    gsSPVertex(&oct_1_v[230], 19, 12),
    gsSPNTrianglesInit_5b(7,         // tri count
                          8, 12, 11, // tri0
                          8, 13, 14, // tri1
                          11, 15, 16 // tri2
                          ),
    gsSPNTriangles_5b(10, 11, 17, // tri0
                      9, 10, 18,  // tri1
                      9, 19, 20,  // tri2
                      9, 21, 8    // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          22, 23, 24, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          25, 26, 27, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          28, 29, 30, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_oct_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&oct_1_v[249], 12, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&oct_1_v[261], 12, 12),
    gsSPNTrianglesInit_5b(8,         // tri count
                          1, 13, 12, // tri0
                          9, 14, 15, // tri1
                          9, 16, 17  // tri2
                          ),
    gsSPNTriangles_5b(1, 18, 19, // tri0
                      9, 0, 20,  // tri1
                      6, 9, 21,  // tri2
                      0, 1, 22   // tri3
                      ),
    gsSPNTriangles_5b(1, 6, 23, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPVertex(&oct_1_v[273], 12, 12),
    gsSPNTrianglesInit_5b(8,         // tri count
                          3, 2, 12,  // tri0
                          3, 13, 14, // tri1
                          8, 15, 16  // tri2
                          ),
    gsSPNTriangles_5b(11, 17, 18, // tri0
                      8, 11, 19,  // tri1
                      11, 3, 20,  // tri2
                      2, 8, 21    // tri3
                      ),
    gsSPNTriangles_5b(11, 23, 22, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&oct_1_v[285], 12, 12),
    gsSPNTrianglesInit_5b(8,         // tri count
                          7, 5, 12,  // tri0
                          4, 13, 14, // tri1
                          5, 4, 15   // tri2
                          ),
    gsSPNTriangles_5b(10, 7, 16, // tri0
                      7, 17, 18, // tri1
                      4, 10, 19, // tri2
                      4, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(7, 22, 23, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_oct_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&oct_1_v[297], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&oct_1_v[303], 13, 6),
    gsSPNTrianglesInit_5b(7,       // tri count
                          4, 0, 6, // tri0
                          1, 7, 0, // tri1
                          0, 9, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 2, 10,  // tri0
                      3, 11, 12, // tri1
                      1, 13, 14, // tri2
                      3, 5, 15   // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          16, 17, 18, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&oct_1_v[316], 13, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 8, // tri0
                      2, 9, 0, // tri1
                      9, 2, 6, // tri2
                      8, 9, 6  // tri3
                      ),
    gsSPNTriangles_5b(7, 3, 8,   // tri0
                      0, 10, 11, // tri1
                      11, 1, 0,  // tri2
                      5, 4, 12   // tri3
                      ),
    gsSPNTriangles_5b(12, 10, 5,  // tri0
                      12, 11, 10, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_oct_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&oct_1_v[458], 14, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 5, 4,  // tri0
                      10, 4, 0, // tri1
                      10, 9, 4, // tri2
                      7, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(8, 7, 13, // tri0
                      2, 10, 0, // tri1
                      2, 1, 6,  // tri2
                      6, 8, 2   // tri3
                      ),
    gsSPNTriangles_5b(7, 12, 13, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_oct_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_oct_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_oct_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_oct_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { Lfoot3_oct_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_oct_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_oct_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { Rfoot3_oct_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 75,0,-475 },
    /* joint 11 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_oct_model, 3, cKF_JOINT_FLAG_DISP_OPA, 325,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 450,-450,0 },
    /* joint 15 */ { Larm1_oct_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_oct_model, 0, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 450,450,0 },
    /* joint 18 */ { Rarm1_oct_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_oct_model, 1, cKF_JOINT_FLAG_DISP_OPA, 551,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 575,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,600 },
    /* joint 23 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_oct_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1400,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_oct_1 = { 26, 13, cKF_je_r_oct_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_oct_1_c(void) {
    pc_load_asset("assets/npc/mdl/oct_1_v.bin", oct_1_v, 0x1D80, 0x607AF0, 0, 2);
}
#endif
