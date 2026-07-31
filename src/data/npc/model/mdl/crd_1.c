#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx crd_1_v[0x1790 / sizeof(Vtx)];
#else
static Vtx crd_1_v[] = {
#include "assets/npc/mdl/crd_1_v.inc"
};
#endif

static Gfx head_crd_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 16, 48, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 188),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&crd_1_v[49], 32, 0),
    gsSPNTrianglesInit_5b(45,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 1  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,   // tri0
                      8, 5, 9,    // tri1
                      11, 12, 13, // tri2
                      6, 14, 7    // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      13, 18, 11, // tri1
                      15, 17, 6,  // tri2
                      7, 2, 1     // tri3
                      ),
    gsSPNTriangles_5b(9, 19, 10, // tri0
                      5, 8, 3,   // tri1
                      2, 20, 0,  // tri2
                      21, 12, 22 // tri3
                      ),
    gsSPNTriangles_5b(12, 11, 22, // tri0
                      8, 12, 21,  // tri1
                      15, 22, 16, // tri2
                      23, 24, 16  // tri3
                      ),
    gsSPNTriangles_5b(11, 25, 23, // tri0
                      1, 0, 3,    // tri1
                      1, 3, 8,    // tri2
                      12, 8, 10   // tri3
                      ),
    gsSPNTriangles_5b(16, 24, 26, // tri0
                      17, 16, 27, // tri1
                      28, 25, 29, // tri2
                      29, 25, 11  // tri3
                      ),
    gsSPNTriangles_5b(28, 26, 24, // tri0
                      23, 25, 28, // tri1
                      6, 1, 15,   // tri2
                      10, 13, 12  // tri3
                      ),
    gsSPNTriangles_5b(7, 14, 30, // tri0
                      5, 4, 31,  // tri1
                      30, 20, 2, // tri2
                      2, 7, 30   // tri3
                      ),
    gsSPNTriangles_5b(31, 19, 9, // tri0
                      9, 5, 31,  // tri1
                      21, 15, 1, // tri2
                      1, 8, 21   // tri3
                      ),
    gsSPNTriangles_5b(22, 15, 21, // tri0
                      28, 24, 23, // tri1
                      16, 22, 23, // tri2
                      23, 22, 11  // tri3
                      ),
    gsSPNTriangles_5b(11, 18, 29, // tri0
                      26, 27, 16, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&crd_1_v[81], 18, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 7,  // tri0
                      5, 4, 1,  // tri1
                      7, 2, 8,  // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 9, // tri0
                      6, 13, 14, // tri1
                      14, 15, 6, // tri2
                      11, 16, 12 // tri3
                      ),
    gsSPNTriangles_5b(5, 1, 0,  // tri0
                      1, 9, 2,  // tri1
                      2, 12, 8, // tri2
                      15, 1, 4  // tri3
                      ),
    gsSPNTriangles_5b(6, 15, 4,   // tri0
                      12, 2, 9,   // tri1
                      14, 17, 15, // tri2
                      15, 9, 1    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&crd_1_v[99], 31, 0),
    gsSPNTrianglesInit_5b(32,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 1, 8,   // tri0
                      9, 10, 11, // tri1
                      12, 13, 2, // tri2
                      3, 2, 6    // tri3
                      ),
    gsSPNTriangles_5b(10, 14, 15, // tri0
                      11, 16, 17, // tri1
                      10, 15, 11, // tri2
                      11, 17, 9   // tri3
                      ),
    gsSPNTriangles_5b(12, 11, 15, // tri0
                      7, 18, 16,  // tri1
                      19, 8, 20,  // tri2
                      20, 8, 1    // tri3
                      ),
    gsSPNTriangles_5b(20, 1, 0, // tri0
                      2, 1, 12, // tri1
                      7, 11, 1, // tri2
                      8, 21, 22 // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 2, // tri0
                      1, 11, 12, // tri1
                      2, 15, 14, // tri2
                      15, 13, 12 // tri3
                      ),
    gsSPNTriangles_5b(8, 16, 18, // tri0
                      8, 18, 7,  // tri1
                      16, 11, 7, // tri2
                      21, 8, 19  // tri3
                      ),
    gsSPNTriangles_5b(6, 2, 4,   // tri0
                      14, 4, 2,  // tri1
                      22, 16, 8, // tri2
                      19, 23, 21 // tri3
                      ),
    gsSPNTriangles_5b(16, 22, 17, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x140, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 60, 60),
    gsSPNTrianglesInit_5b(5,          // tri count
                          24, 25, 26, // tri0
                          26, 25, 27, // tri1
                          25, 28, 29  // tri2
                          ),
    gsSPNTriangles_5b(27, 25, 29, // tri0
                      30, 24, 26, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&crd_1_v[130], 10, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 0, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 4, // tri0
                      5, 4, 3, // tri1
                      7, 8, 9, // tri2
                      6, 9, 4  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 6, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx mouth_crd_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&crd_1_v[0], 7, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&crd_1_v[7], 22, 7),
    gsSPNTrianglesInit_5b(8,        // tri count
                          5, 7, 8,  // tri0
                          6, 5, 9,  // tri1
                          6, 10, 11 // tri2
                          ),
    gsSPNTriangles_5b(4, 12, 13, // tri0
                      0, 6, 14,  // tri1
                      5, 15, 16, // tri2
                      5, 4, 17   // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 18, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x140, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 60, 60),
    gsSPNTrianglesInit_5b(2,         // tri count
                          2, 19, 20, // tri0
                          1, 21, 2,  // tri1
                          0, 0, 0    // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3,          // tri count
                          22, 23, 24, // tri0
                          25, 26, 27, // tri1
                          26, 28, 27  // tri2
                          ),
    gsSPVertex(&crd_1_v[29], 20, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 4  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6,         // tri count
                          7, 8, 9,   // tri0
                          10, 11, 7, // tri1
                          7, 9, 12   // tri2
                          ),
    gsSPNTriangles_5b(8, 13, 9,   // tri0
                      10, 14, 11, // tri1
                      12, 10, 7,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x140, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 60, 60),
    gsSPNTrianglesInit_5b(3,          // tri count
                          15, 16, 17, // tri0
                          16, 18, 17, // tri1
                          18, 19, 17  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_crd_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&crd_1_v[176], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&crd_1_v[181], 16, 5),
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

static Gfx Rarm1_crd_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&crd_1_v[197], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&crd_1_v[201], 11, 4),
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

static Gfx Larm2_crd_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&crd_1_v[140], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&crd_1_v[145], 16, 5),
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

static Gfx Larm1_crd_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&crd_1_v[161], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&crd_1_v[165], 11, 4),
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

static Gfx chest_crd_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&crd_1_v[212], 9, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 252, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&crd_1_v[221], 20, 9),
    gsSPNTrianglesInit_5b(14,        // tri count
                          0, 9, 10,  // tri0
                          8, 11, 12, // tri1
                          1, 0, 13   // tri2
                          ),
    gsSPNTriangles_5b(0, 3, 14, // tri0
                      4, 15, 7, // tri1
                      3, 7, 16, // tri2
                      7, 17, 18 // tri3
                      ),
    gsSPNTriangles_5b(3, 20, 19, // tri0
                      8, 2, 21,  // tri1
                      5, 8, 22,  // tri2
                      5, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(6, 26, 25, // tri0
                      6, 5, 27,  // tri1
                      4, 6, 28,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&crd_1_v[241], 17, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(1, 6, 2,   // tri0
                      7, 8, 9,   // tri1
                      7, 10, 11, // tri2
                      0, 12, 13  // tri3
                      ),
    gsSPNTriangles_5b(5, 14, 10,  // tri0
                      6, 11, 4,   // tri1
                      10, 14, 11, // tri2
                      9, 13, 12   // tri3
                      ),
    gsSPNTriangles_5b(5, 15, 3, // tri0
                      9, 12, 7, // tri1
                      11, 8, 7, // tri2
                      2, 16, 0  // tri3
                      ),
    gsSPNTriangles_5b(13, 1, 0, // tri0
                      4, 14, 5, // tri1
                      1, 9, 6,  // tri2
                      8, 6, 9   // tri3
                      ),
    gsSPNTriangles_5b(8, 11, 6, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_crd_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&crd_1_v[278], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&crd_1_v[282], 12, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          1, 4, 5, // tri0
                          2, 6, 7, // tri1
                          2, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(1, 10, 11, // tri0
                      3, 1, 12,  // tri1
                      1, 0, 13,  // tri2
                      2, 3, 14   // tri3
                      ),
    gsSPNTriangles_5b(0, 2, 15, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail2_crd_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&crd_1_v[258], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&crd_1_v[262], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 4, 5, // tri0
                          0, 6, 7, // tri1
                          3, 0, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 9,   // tri0
                      3, 11, 10, // tri1
                      1, 13, 12, // tri2
                      2, 3, 14   // tri3
                      ),
    gsSPNTriangles_5b(1, 2, 15, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          16, 17, 18, // tri0
                          18, 17, 19, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_crd_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&crd_1_v[325], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&crd_1_v[330], 17, 5),
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

static Gfx Rfoot1_crd_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&crd_1_v[347], 9, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          1, 5, 2  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8, // tri0
                      6, 8, 0, // tri1
                      0, 2, 6, // tri2
                      4, 5, 1  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_crd_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&crd_1_v[294], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&crd_1_v[299], 17, 5),
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

static Gfx Lfoot1_crd_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&crd_1_v[316], 9, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          0, 5, 1  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8, // tri0
                      2, 6, 8, // tri1
                      8, 0, 2, // tri2
                      1, 5, 3  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_crd_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&crd_1_v[356], 21, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          2, 1, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 0, 2, // tri0
                      1, 6, 7, // tri1
                      8, 3, 9, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(10, 9, 11, // tri0
                      12, 5, 7,  // tri1
                      9, 3, 4,   // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 14, // tri0
                      13, 15, 16, // tri1
                      14, 11, 15, // tri2
                      13, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(17, 16, 18, // tri0
                      1, 0, 19,   // tri1
                      1, 19, 6,   // tri2
                      19, 0, 20   // tri3
                      ),
    gsSPNTriangles_5b(6, 19, 13,  // tri0
                      13, 19, 20, // tri1
                      20, 3, 8,   // tri2
                      8, 10, 20   // tri3
                      ),
    gsSPNTriangles_5b(0, 3, 20,   // tri0
                      13, 20, 14, // tri1
                      10, 14, 20, // tri2
                      7, 5, 1     // tri3
                      ),
    gsSPNTriangles_5b(17, 6, 13, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_crd_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_crd_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_crd_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_crd_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_crd_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_crd_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, -300,0,-700 },
    /* joint 11 */ { tail1_crd_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { tail2_crd_model, 0, cKF_JOINT_FLAG_DISP_OPA, 399,0,0 },
    /* joint 13 */ { chest_crd_model, 3, cKF_JOINT_FLAG_DISP_OPA, 325,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 425,-450,0 },
    /* joint 15 */ { Larm1_crd_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_crd_model, 0, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 425,450,0 },
    /* joint 18 */ { Rarm1_crd_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_crd_model, 1, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 675,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 650,0,300 },
    /* joint 23 */ { mouth_crd_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_crd_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1300,0,-100 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_crd_1 = { 26, 14, cKF_je_r_crd_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_crd_1_c(void) {
    pc_load_asset("assets/npc/mdl/crd_1_v.bin", crd_1_v, 0x1790, 0x4A7BA0, 0, 2);
}
#endif
