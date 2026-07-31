#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx hip_1_v[0x1C60 / sizeof(Vtx)];
#else
static Vtx hip_1_v[] = {
#include "assets/npc/mdl/hip_1_v.inc"
};
#endif

static Gfx head_hip_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hip_1_v[28], 7, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hip_1_v[35], 18, 7),
    gsSPNTrianglesInit_5b(12,       // tri count
                          1, 7, 8,  // tri0
                          1, 9, 10, // tri1
                          2, 11, 12 // tri2
                          ),
    gsSPNTriangles_5b(2, 13, 14, // tri0
                      3, 4, 15,  // tri1
                      5, 6, 16,  // tri2
                      5, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(4, 19, 20, // tri0
                      1, 3, 21,  // tri1
                      6, 2, 22,  // tri2
                      0, 1, 23   // tri3
                      ),
    gsSPNTriangles_5b(2, 0, 24, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPVertex(&hip_1_v[53], 27, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          1, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 2, // tri0
                      4, 0, 3, // tri1
                      4, 3, 5, // tri2
                      6, 7, 8  // tri3
                      ),
    gsSPNTriangles_5b(6, 8, 9,   // tri0
                      10, 6, 9,  // tri1
                      10, 9, 11, // tri2
                      7, 10, 11  // tri3
                      ),
    gsSPNTriangles_5b(7, 11, 8, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7,          // tri count
                          12, 13, 14, // tri0
                          15, 16, 17, // tri1
                          14, 18, 12  // tri2
                          ),
    gsSPNTriangles_5b(14, 15, 19, // tri0
                      19, 15, 17, // tri1
                      18, 19, 17, // tri2
                      19, 18, 14  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(5,          // tri count
                          20, 21, 22, // tri0
                          22, 23, 24, // tri1
                          24, 25, 20  // tri2
                          ),
    gsSPNTriangles_5b(22, 24, 20, // tri0
                      20, 26, 21, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&hip_1_v[80], 26, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 2, 1  // tri2
                          ),
    gsSPNTriangles_5b(0, 6, 7, // tri0
                      5, 2, 3, // tri1
                      1, 7, 3, // tri2
                      0, 7, 1  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x140, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(20,        // tri count
                          8, 9, 10,  // tri0
                          8, 11, 12, // tri1
                          8, 12, 13  // tri2
                          ),
    gsSPNTriangles_5b(8, 14, 15,  // tri0
                      11, 16, 17, // tri1
                      18, 19, 20, // tri2
                      19, 21, 12  // tri3
                      ),
    gsSPNTriangles_5b(11, 15, 16, // tri0
                      20, 19, 12, // tri1
                      17, 16, 22, // tri2
                      9, 13, 23   // tri3
                      ),
    gsSPNTriangles_5b(12, 11, 17, // tri0
                      12, 17, 20, // tri1
                      17, 22, 24, // tri2
                      24, 18, 20  // tri3
                      ),
    gsSPNTriangles_5b(20, 17, 24, // tri0
                      15, 11, 8,  // tri1
                      13, 12, 21, // tri2
                      21, 25, 13  // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 13, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&hip_1_v[106], 21, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 3,  // tri0
                      11, 12, 9, // tri1
                      0, 11, 13, // tri2
                      3, 5, 14   // tri3
                      ),
    gsSPNTriangles_5b(15, 13, 14, // tri0
                      11, 14, 13, // tri1
                      11, 16, 12, // tri2
                      9, 14, 11   // tri3
                      ),
    gsSPNTriangles_5b(15, 14, 5, // tri0
                      3, 14, 9,  // tri1
                      8, 7, 4,   // tri2
                      3, 17, 8   // tri3
                      ),
    gsSPNTriangles_5b(17, 3, 10, // tri0
                      2, 1, 18,  // tri1
                      19, 6, 8,  // tri2
                      2, 16, 11  // tri3
                      ),
    gsSPNTriangles_5b(20, 16, 2, // tri0
                      2, 18, 20, // tri1
                      8, 17, 19, // tri2
                      2, 11, 0   // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 8, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 60, 252),
    gsSPVertex(&hip_1_v[127], 32, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,   // tri0
                      11, 12, 13, // tri1
                      14, 15, 4,  // tri2
                      16, 4, 3    // tri3
                      ),
    gsSPNTriangles_5b(9, 17, 10,  // tri0
                      18, 12, 11, // tri1
                      19, 20, 21, // tri2
                      20, 19, 22  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 25, // tri0
                      23, 26, 27, // tri1
                      28, 29, 30, // tri2
                      2, 1, 31    // tri3
                      ),
    gsSPVertex(&hip_1_v[159], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          3, 2, 1, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      9, 10, 11, // tri1
                      0, 12, 13, // tri2
                      14, 15, 16 // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      19, 20, 13, // tri1
                      21, 18, 17, // tri2
                      22, 12, 23  // tri3
                      ),
    gsSPNTriangles_5b(13, 22, 24, // tri0
                      16, 19, 25, // tri1
                      16, 15, 19, // tri2
                      5, 14, 18   // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 1,    // tri0
                      15, 26, 27, // tri1
                      27, 20, 15, // tri2
                      18, 28, 5   // tri3
                      ),
    gsSPNTriangles_5b(12, 0, 2,   // tri0
                      19, 15, 20, // tri1
                      1, 27, 26,  // tri2
                      1, 26, 4    // tri3
                      ),
    gsSPNTriangles_5b(2, 29, 12,  // tri0
                      16, 18, 14, // tri1
                      25, 17, 16, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&hip_1_v[189], 25, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x340, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,          // tri count
                          9, 10, 11,  // tri0
                          12, 13, 14, // tri1
                          9, 11, 15   // tri2
                          ),
    gsSPNTriangles_5b(16, 13, 12, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,          // tri count
                          17, 18, 19, // tri0
                          19, 20, 17, // tri1
                          21, 22, 23  // tri2
                          ),
    gsSPNTriangles_5b(24, 21, 23, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x3C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&hip_1_v[214], 18, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(1, 7, 8, // tri0
                      6, 3, 9, // tri1
                      0, 7, 1, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,          // tri count
                          10, 11, 12, // tri0
                          13, 14, 15, // tri1
                          12, 16, 10  // tri2
                          ),
    gsSPNTriangles_5b(15, 17, 13, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx mouth_hip_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hip_1_v[0], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hip_1_v[5], 23, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 5, 6, // tri0
                          4, 8, 7, // tri1
                          0, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 11, // tri0
                      1, 2, 12, // tri1
                      0, 4, 13, // tri2
                      2, 0, 14  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,         // tri count
                          3, 1, 15,  // tri0
                          3, 16, 17, // tri1
                          0, 0, 0    // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,          // tri count
                          18, 19, 20, // tri0
                          21, 22, 23, // tri1
                          18, 23, 22  // tri2
                          ),
    gsSPNTriangles_5b(18, 22, 19, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,          // tri count
                          24, 25, 26, // tri0
                          27, 25, 24, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_hip_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hip_1_v[265], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hip_1_v[270], 13, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 5, // tri0
                          0, 6, 7, // tri1
                          3, 2, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 4, 9,   // tri0
                      1, 10, 11, // tri1
                      2, 12, 13, // tri2
                      2, 0, 14   // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          15, 16, 17, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_hip_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hip_1_v[283], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hip_1_v[287], 11, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 4, 5, // tri0
                          0, 2, 6, // tri1
                          3, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 9,   // tri0
                      3, 1, 10,  // tri1
                      2, 11, 12, // tri2
                      1, 13, 14  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_hip_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hip_1_v[232], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hip_1_v[237], 13, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          1, 0, 5, // tri0
                          0, 6, 7, // tri1
                          2, 3, 8  // tri2
                          ),
    gsSPNTriangles_5b(4, 1, 9,   // tri0
                      1, 10, 11, // tri1
                      2, 12, 13, // tri2
                      0, 2, 14   // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          15, 16, 17, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_hip_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hip_1_v[250], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hip_1_v[254], 11, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 4, 5, // tri0
                          2, 0, 6, // tri1
                          3, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 9,   // tri0
                      1, 3, 10,  // tri1
                      2, 11, 12, // tri2
                      1, 13, 14  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_hip_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hip_1_v[298], 16, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 4,   // tri0
                      3, 0, 2,    // tri1
                      11, 12, 13, // tri2
                      7, 6, 12    // tri3
                      ),
    gsSPNTriangles_5b(13, 9, 11, // tri0
                      7, 12, 11, // tri1
                      4, 10, 5,  // tri2
                      14, 2, 1   // tri3
                      ),
    gsSPNTriangles_5b(0, 3, 5,   // tri0
                      15, 6, 8,  // tri1
                      15, 8, 14, // tri2
                      10, 9, 13  // tri3
                      ),
    gsSPVertex(&hip_1_v[314], 19, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          3, 0, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7,   // tri0
                      4, 7, 8,   // tri1
                      9, 10, 11, // tri2
                      12, 6, 4   // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      13, 15, 16, // tri1
                      13, 17, 18, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_hip_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x4C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hip_1_v[342], 12, 0),
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
    gsSPEndDisplayList(),
};

static Gfx tail2_hip_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x4C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hip_1_v[333], 9, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_hip_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hip_1_v[392], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hip_1_v[397], 16, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 5, 6, // tri0
                          2, 0, 7, // tri1
                          1, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(1, 3, 10, // tri0
                      4, 2, 11, // tri1
                      0, 1, 12, // tri2
                      0, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(2, 15, 16, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          17, 18, 19, // tri0
                          19, 20, 17, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_hip_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hip_1_v[413], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hip_1_v[418], 12, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          3, 5, 6, // tri0
                          3, 2, 7, // tri1
                          2, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(4, 10, 0,  // tri0
                      0, 11, 12, // tri1
                      0, 13, 1,  // tri2
                      2, 1, 14   // tri3
                      ),
    gsSPNTriangles_5b(4, 15, 16, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx lfoot1_hip_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hip_1_v[375], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hip_1_v[380], 12, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          3, 6, 5, // tri0
                          0, 1, 7, // tri1
                          2, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(2, 10, 4,  // tri0
                      4, 11, 12, // tri1
                      1, 4, 13,  // tri2
                      0, 14, 3   // tri3
                      ),
    gsSPNTriangles_5b(0, 15, 16, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_hip_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hip_1_v[354], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&hip_1_v[359], 16, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          4, 5, 6, // tri0
                          3, 7, 8, // tri1
                          4, 3, 9  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 10,  // tri0
                      4, 11, 12, // tri1
                      2, 13, 14, // tri2
                      2, 4, 15   // tri3
                      ),
    gsSPNTriangles_5b(3, 1, 16, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          17, 18, 19, // tri0
                          19, 20, 17, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx base_hip_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&hip_1_v[430], 24, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          1, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(3, 7, 8,   // tri0
                      9, 2, 10,  // tri1
                      9, 10, 11, // tri2
                      11, 10, 12 // tri3
                      ),
    gsSPNTriangles_5b(12, 10, 13, // tri0
                      14, 8, 7,   // tri1
                      8, 14, 15,  // tri2
                      2, 9, 0     // tri3
                      ),
    gsSPNTriangles_5b(8, 15, 16, // tri0
                      4, 6, 5,   // tri1
                      6, 1, 0,   // tri2
                      5, 7, 3    // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      17, 20, 18, // tri1
                      20, 21, 18, // tri2
                      20, 22, 21  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_hip_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_hip_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-600,0 },
    /* joint 3 */ { lfoot1_hip_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_hip_model, 1, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 250,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,600,0 },
    /* joint 7 */ { Rfoot1_hip_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_hip_model, 1, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 250,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,-1300 },
    /* joint 11 */ { tail1_hip_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { tail2_hip_model, 0, cKF_JOINT_FLAG_DISP_OPA, 602,0,0 },
    /* joint 13 */ { chest_hip_model, 3, cKF_JOINT_FLAG_DISP_OPA, 430,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 1100,-1450,0 },
    /* joint 15 */ { Larm1_hip_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_hip_model, 0, cKF_JOINT_FLAG_DISP_OPA, 556,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 1100,1450,1 },
    /* joint 18 */ { Rarm1_hip_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_hip_model, 1, cKF_JOINT_FLAG_DISP_OPA, 549,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 553,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 2020,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 100,0,900 },
    /* joint 23 */ { mouth_hip_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_hip_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1950,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_hip_1 = { 26, 14, cKF_je_r_hip_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_hip_1_c(void) {
    pc_load_asset("assets/npc/mdl/hip_1_v.bin", hip_1_v, 0x1C60, 0x52DC80, 0, 2);
}
#endif
