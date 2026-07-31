#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx lon_1_v[0x1B20 / sizeof(Vtx)];
#else
static Vtx lon_1_v[] = {
#include "assets/npc/mdl/lon_1_v.inc"
};
#endif

static Gfx head_lon_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 178, 178, 178, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&lon_1_v[0], 19, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7, // tri0
                      7, 8, 9, // tri1
                      7, 9, 4, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(7,          // tri count
                          10, 11, 12, // tri0
                          13, 14, 11, // tri1
                          11, 10, 15  // tri2
                          ),
    gsSPNTriangles_5b(16, 17, 12, // tri0
                      12, 18, 16, // tri1
                      11, 15, 13, // tri2
                      12, 17, 10  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 32, 40, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&lon_1_v[19], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 1, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,  // tri0
                      8, 9, 10, // tri1
                      6, 11, 7, // tri2
                      8, 12, 9  // tri3
                      ),
    gsSPNTriangles_5b(11, 2, 13, // tri0
                      14, 1, 12, // tri1
                      1, 15, 12, // tri2
                      11, 16, 2  // tri3
                      ),
    gsSPNTriangles_5b(15, 1, 4,   // tri0
                      17, 18, 19, // tri1
                      20, 21, 22, // tri2
                      23, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(26, 18, 17, // tri0
                      25, 24, 20, // tri1
                      27, 21, 28, // tri2
                      27, 29, 30  // tri3
                      ),
    gsSPNTriangles_5b(31, 8, 10, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&lon_1_v[51], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 4, 7,    // tri0
                      9, 10, 11,  // tri1
                      12, 13, 14, // tri2
                      8, 2, 1     // tri3
                      ),
    gsSPNTriangles_5b(0, 2, 8,   // tri0
                      8, 1, 15,  // tri1
                      16, 5, 15, // tri2
                      17, 0, 8   // tri3
                      ),
    gsSPNTriangles_5b(17, 7, 18,  // tri0
                      19, 20, 21, // tri1
                      21, 13, 19, // tri2
                      12, 14, 22  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 24, // tri0
                      25, 9, 26,  // tri1
                      27, 26, 28, // tri2
                      29, 30, 31  // tri3
                      ),
    gsSPVertex(&lon_1_v[83], 32, 0),
    gsSPNTrianglesInit_5b(31,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,   // tri0
                      3, 10, 11, // tri1
                      12, 2, 11, // tri2
                      6, 13, 4   // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 2,    // tri0
                      14, 9, 15,  // tri1
                      16, 17, 18, // tri2
                      8, 7, 0     // tri3
                      ),
    gsSPNTriangles_5b(0, 2, 8,    // tri0
                      2, 3, 11,   // tri1
                      19, 20, 21, // tri2
                      21, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(24, 21, 23, // tri0
                      21, 9, 25,  // tri1
                      19, 21, 12, // tri2
                      24, 15, 9   // tri3
                      ),
    gsSPNTriangles_5b(15, 26, 16, // tri0
                      16, 14, 15, // tri1
                      9, 21, 24,  // tri2
                      2, 12, 25   // tri3
                      ),
    gsSPNTriangles_5b(25, 12, 21, // tri0
                      2, 25, 9,   // tri1
                      16, 27, 28, // tri2
                      28, 7, 16   // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 7, // tri0
                      10, 29, 6, // tri1
                      4, 19, 12, // tri2
                      10, 5, 12  // tri3
                      ),
    gsSPVertex(&lon_1_v[113], 28, 0),
    gsSPNTrianglesInit_5b(1,       // tri count
                          0, 1, 2, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(30,      // tri count
                          3, 4, 5, // tri0
                          6, 7, 8, // tri1
                          9, 10, 3 // tri2
                          ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      7, 12, 9,   // tri1
                      14, 15, 11, // tri2
                      3, 7, 9     // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 14, // tri0
                      12, 6, 18,  // tri1
                      19, 18, 6,  // tri2
                      3, 10, 4    // tri3
                      ),
    gsSPNTriangles_5b(19, 6, 20,  // tri0
                      21, 3, 22,  // tri1
                      17, 15, 14, // tri2
                      23, 14, 24  // tri3
                      ),
    gsSPNTriangles_5b(3, 5, 22,   // tri0
                      7, 3, 21,   // tri1
                      25, 13, 18, // tri2
                      17, 26, 15  // tri3
                      ),
    gsSPNTriangles_5b(24, 14, 13, // tri0
                      10, 27, 4,  // tri1
                      12, 7, 6,   // tri2
                      18, 13, 12  // tri3
                      ),
    gsSPNTriangles_5b(11, 9, 12,  // tri0
                      14, 23, 16, // tri1
                      8, 7, 21,   // tri2
                      24, 13, 25  // tri3
                      ),
    gsSPNTriangles_5b(25, 18, 19, // tri0
                      20, 6, 8,   // tri1
                      11, 13, 14, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&lon_1_v[141], 24, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      12, 9, 11,  // tri1
                      12, 11, 13, // tri2
                      6, 9, 14    // tri3
                      ),
    gsSPNTriangles_5b(15, 10, 6, // tri0
                      0, 2, 16,  // tri1
                      8, 3, 5,   // tri2
                      17, 12, 18 // tri3
                      ),
    gsSPNTriangles_5b(13, 19, 12, // tri0
                      16, 20, 18, // tri1
                      5, 6, 8,    // tri2
                      18, 20, 17  // tri3
                      ),
    gsSPNTriangles_5b(14, 7, 6,   // tri0
                      16, 18, 0,  // tri1
                      10, 15, 21, // tri2
                      19, 13, 22  // tri3
                      ),
    gsSPNTriangles_5b(22, 13, 11, // tri0
                      22, 11, 21, // tri1
                      9, 6, 10,   // tri2
                      18, 19, 23  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 19, // tri0
                      21, 11, 10, // tri1
                      19, 18, 12, // tri2
                      23, 0, 18   // tri3
                      ),
    gsSPNTriangles_5b(6, 5, 15, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&lon_1_v[165], 27, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          2, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 0, 7, // tri0
                      2, 7, 0, // tri1
                      7, 6, 8, // tri2
                      8, 6, 9  // tri3
                      ),
    gsSPNTriangles_5b(1, 5, 2, // tri0
                      6, 7, 2, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8,          // tri count
                          10, 11, 12, // tri0
                          13, 10, 12, // tri1
                          12, 14, 15  // tri2
                          ),
    gsSPNTriangles_5b(12, 15, 13, // tri0
                      14, 16, 15, // tri1
                      14, 17, 16, // tri2
                      13, 11, 10  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 15, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7,          // tri count
                          18, 19, 20, // tri0
                          20, 21, 18, // tri1
                          22, 23, 24  // tri2
                          ),
    gsSPNTriangles_5b(25, 19, 18, // tri0
                      18, 24, 25, // tri1
                      24, 26, 22, // tri2
                      23, 25, 24  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_lon_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&lon_1_v[228], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&lon_1_v[233], 16, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          2, 5, 3, // tri0
                          1, 4, 6, // tri1
                          1, 8, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 10, 9,  // tri0
                      0, 1, 11,  // tri1
                      2, 12, 13, // tri2
                      2, 0, 14   // tri3
                      ),
    gsSPNTriangles_5b(2, 15, 16, // tri0
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

static Gfx Rarm1_lon_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&lon_1_v[249], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&lon_1_v[253], 11, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 2, 4, // tri0
                          0, 5, 6, // tri1
                          1, 8, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 9, 10, // tri0
                      3, 1, 11, // tri1
                      1, 0, 12, // tri2
                      1, 13, 14 // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_lon_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&lon_1_v[192], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&lon_1_v[197], 16, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 5, 6, // tri0
                          4, 7, 8, // tri1
                          4, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 11,  // tri0
                      4, 2, 12,  // tri1
                      0, 13, 14, // tri2
                      0, 3, 15   // tri3
                      ),
    gsSPNTriangles_5b(3, 4, 16, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          17, 18, 19, // tri0
                          18, 17, 20, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_lon_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&lon_1_v[213], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&lon_1_v[217], 11, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 4, 5, // tri0
                          0, 6, 7, // tri1
                          0, 2, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 3, 9,   // tri0
                      2, 11, 10, // tri1
                      3, 13, 12, // tri2
                      3, 1, 14   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_lon_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&lon_1_v[264], 7, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&lon_1_v[271], 20, 7),
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
    gsSPVertex(&lon_1_v[291], 9, 0),
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

static Gfx tail1_lon_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&lon_1_v[314], 8, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          1, 0, 4  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 1, // tri0
                      0, 2, 6, // tri1
                      7, 5, 6, // tri2
                      6, 2, 7  // tri3
                      ),
    gsSPNTriangles_5b(5, 7, 3, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail2_lon_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&lon_1_v[300], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&lon_1_v[304], 10, 4),
    gsSPNTrianglesInit_5b(4,       // tri count
                          2, 1, 4, // tri0
                          3, 2, 5, // tri1
                          0, 3, 6  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 7, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPNTrianglesInit_5b(8,         // tri count
                          8, 9, 10,  // tri0
                          11, 9, 12, // tri1
                          12, 9, 8   // tri2
                          ),
    gsSPNTriangles_5b(10, 9, 11,  // tri0
                      10, 11, 13, // tri1
                      13, 11, 12, // tri2
                      13, 8, 10   // tri3
                      ),
    gsSPNTriangles_5b(12, 8, 13, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_lon_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&lon_1_v[372], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&lon_1_v[377], 17, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          4, 0, 5, // tri0
                          0, 7, 6, // tri1
                          3, 9, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 2, 10, // tri0
                      2, 3, 11, // tri1
                      3, 4, 12, // tri2
                      2, 13, 14 // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          15, 16, 17, // tri0
                          18, 19, 20, // tri1
                          18, 21, 19  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_lon_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&lon_1_v[394], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&lon_1_v[398], 22, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 3, 4, // tri0
                          0, 5, 1, // tri1
                          1, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(3, 2, 8,  // tri0
                      2, 9, 10, // tri1
                      2, 1, 11, // tri2
                      0, 13, 12 // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7,          // tri count
                          14, 15, 16, // tri0
                          14, 16, 17, // tri1
                          17, 18, 14  // tri2
                          ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      21, 20, 18, // tri1
                      21, 22, 19, // tri2
                      17, 21, 18  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsSPNTrianglesInit_5b(1,          // tri count
                          23, 24, 25, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_lon_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&lon_1_v[322], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&lon_1_v[327], 17, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 4, 5, // tri0
                          0, 7, 6, // tri1
                          3, 9, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 10, // tri0
                      3, 2, 11, // tri1
                      4, 3, 12, // tri2
                      2, 13, 14 // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          15, 16, 17, // tri0
                          18, 19, 20, // tri1
                          19, 21, 20  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_lon_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&lon_1_v[344], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&lon_1_v[350], 22, 6),
    gsSPNTrianglesInit_5b(7,       // tri count
                          4, 0, 6, // tri0
                          1, 7, 0, // tri1
                          1, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(2, 5, 10,  // tri0
                      2, 11, 12, // tri1
                      1, 3, 13,  // tri2
                      0, 15, 14  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7,          // tri count
                          16, 17, 18, // tri0
                          19, 16, 18, // tri1
                          18, 20, 19  // tri2
                          ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      20, 22, 21, // tri1
                      23, 24, 21, // tri2
                      20, 21, 19  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsSPNTrianglesInit_5b(1,          // tri count
                          25, 26, 27, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx base_lon_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&lon_1_v[420], 14, 0),
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
static cKF_Joint_R_c cKF_je_r_lon_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_lon_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_lon_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_lon_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_lon_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_lon_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 75,0,-475 },
    /* joint 11 */ { tail1_lon_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { tail2_lon_model, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_lon_model, 3, cKF_JOINT_FLAG_DISP_OPA, 325,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 425,-450,0 },
    /* joint 15 */ { Larm1_lon_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_lon_model, 0, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 425,450,0 },
    /* joint 18 */ { Rarm1_lon_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_lon_model, 1, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 675,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,600 },
    /* joint 23 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_lon_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1400,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_lon_1 = { 26, 13, cKF_je_r_lon_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_lon_1_c(void) {
    pc_load_asset("assets/npc/mdl/lon_1_v.bin", lon_1_v, 0x1B20, 0x571850, 0, 2);
}
#endif
