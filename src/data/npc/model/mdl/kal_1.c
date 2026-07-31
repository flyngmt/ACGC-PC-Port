#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx kal_1_v[0x1690 / sizeof(Vtx)];
#else
static Vtx kal_1_v[] = {
#include "assets/npc/mdl/kal_1_v.inc"
};
#endif

static Gfx head_kal_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kal_1_v[0], 25, 0),
    gsSPNTrianglesInit_5b(29,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          0, 6, 1  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      6, 10, 1,   // tri1
                      11, 12, 13, // tri2
                      11, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(6, 0, 15, // tri0
                      9, 16, 5, // tri1
                      7, 9, 4,  // tri2
                      17, 7, 4  // tri3
                      ),
    gsSPNTriangles_5b(15, 0, 18, // tri0
                      3, 5, 19,  // tri1
                      15, 20, 6, // tri2
                      5, 4, 9    // tri3
                      ),
    gsSPNTriangles_5b(15, 13, 12, // tri0
                      11, 14, 5,  // tri1
                      19, 5, 14,  // tri2
                      21, 22, 12  // tri3
                      ),
    gsSPNTriangles_5b(23, 15, 18, // tri0
                      13, 15, 23, // tri1
                      23, 19, 14, // tri2
                      23, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(12, 22, 15, // tri0
                      11, 24, 21, // tri1
                      12, 11, 21, // tri2
                      5, 24, 11   // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 17, // tri0
                      2, 18, 0, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kal_1_v[25], 22, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 2, // tri1
                          3, 5, 4  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      2, 4, 9,   // tri1
                      7, 10, 11, // tri2
                      7, 11, 8   // tri3
                      ),
    gsSPNTriangles_5b(0, 8, 1,  // tri0
                      8, 0, 12, // tri1
                      12, 0, 2, // tri2
                      12, 6, 8  // tri3
                      ),
    gsSPNTriangles_5b(1, 3, 2,  // tri0
                      2, 9, 12, // tri1
                      8, 11, 1, // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7,          // tri count
                          13, 14, 15, // tri0
                          16, 17, 18, // tri1
                          17, 16, 19  // tri2
                          ),
    gsSPNTriangles_5b(20, 14, 21, // tri0
                      21, 17, 19, // tri1
                      19, 20, 21, // tri2
                      20, 15, 14  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 32, 40, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kal_1_v[47], 21, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          4, 5, 2  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,  // tri0
                      9, 3, 2,  // tri1
                      0, 3, 10, // tri2
                      0, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(12, 0, 11, // tri0
                      4, 13, 14, // tri1
                      15, 0, 12, // tri2
                      14, 16, 4  // tri3
                      ),
    gsSPNTriangles_5b(9, 5, 17,  // tri0
                      17, 4, 16, // tri1
                      17, 5, 4,  // tri2
                      18, 13, 1  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 3,  // tri0
                      2, 5, 9,   // tri1
                      13, 4, 1,  // tri2
                      19, 13, 18 // tri3
                      ),
    gsSPNTriangles_5b(15, 1, 0,  // tri0
                      1, 15, 18, // tri1
                      6, 19, 18, // tri2
                      18, 15, 6  // tri3
                      ),
    gsSPNTriangles_5b(8, 20, 19, // tri0
                      19, 6, 8,  // tri1
                      2, 1, 4,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&kal_1_v[68], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 9, 2,    // tri0
                      10, 11, 12, // tri1
                      6, 13, 14,  // tri2
                      15, 16, 13  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      19, 20, 17, // tri1
                      21, 19, 12, // tri2
                      3, 5, 22    // tri3
                      ),
    gsSPNTriangles_5b(5, 23, 24,  // tri0
                      13, 25, 15, // tri1
                      26, 27, 22, // tri2
                      0, 28, 29   // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 21, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&kal_1_v[100], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          0, 2, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      10, 11, 12, // tri1
                      13, 14, 15, // tri2
                      6, 16, 15   // tri3
                      ),
    gsSPNTriangles_5b(3, 5, 17,   // tri0
                      17, 18, 19, // tri1
                      7, 20, 21,  // tri2
                      22, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(12, 11, 25, // tri0
                      26, 10, 12, // tri1
                      7, 9, 27,   // tri2
                      22, 24, 12  // tri3
                      ),
    gsSPNTriangles_5b(21, 28, 7,  // tri0
                      17, 19, 29, // tri1
                      7, 28, 30,  // tri2
                      31, 13, 15  // tri3
                      ),
    gsSPVertex(&kal_1_v[132], 9, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_kal_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kal_1_v[177], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kal_1_v[182], 16, 5),
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

static Gfx Rarm1_kal_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kal_1_v[198], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kal_1_v[202], 11, 4),
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

static Gfx Larm2_kal_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kal_1_v[141], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kal_1_v[146], 16, 5),
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

static Gfx Larm1_kal_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kal_1_v[162], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kal_1_v[166], 11, 4),
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

static Gfx chest_kal_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kal_1_v[213], 7, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kal_1_v[220], 20, 7),
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
    gsSPVertex(&kal_1_v[240], 9, 0),
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

static Gfx Rfoot2_kal_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kal_1_v[299], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kal_1_v[304], 17, 5),
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

static Gfx Rfoot1_kal_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kal_1_v[321], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kal_1_v[325], 22, 4),
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
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
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

static Gfx Lfoot2_kal_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kal_1_v[249], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kal_1_v[254], 17, 5),
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

static Gfx Lfoot1_kal_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kal_1_v[271], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&kal_1_v[277], 22, 6),
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
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
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

static Gfx base_kal_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 508, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&kal_1_v[347], 14, 0),
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
static cKF_Joint_R_c cKF_je_r_kal_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_kal_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_kal_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_kal_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_kal_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_kal_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 75,0,-475 },
    /* joint 11 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_kal_model, 3, cKF_JOINT_FLAG_DISP_OPA, 325,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 425,-450,0 },
    /* joint 15 */ { Larm1_kal_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_kal_model, 0, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 425,450,0 },
    /* joint 18 */ { Rarm1_kal_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_kal_model, 1, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 675,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,600 },
    /* joint 23 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_kal_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1500,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_kal_1 = { 26, 11, cKF_je_r_kal_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_kal_1_c(void) {
    pc_load_asset("assets/npc/mdl/kal_1_v.bin", kal_1_v, 0x1690, 0x566100, 0, 2);
}
#endif
