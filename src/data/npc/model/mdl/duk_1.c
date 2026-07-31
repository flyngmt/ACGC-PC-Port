#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx duk_1_v[0x1580 / sizeof(Vtx)];
#else
static Vtx duk_1_v[] = {
#include "assets/npc/mdl/duk_1_v.inc"
};
#endif

static Gfx head_duk_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&duk_1_v[26], 19, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 8,  // tri0
                      5, 9, 3,  // tri1
                      6, 4, 10, // tri2
                      4, 3, 10  // tri3
                      ),
    gsSPNTriangles_5b(2, 8, 4,   // tri0
                      2, 4, 6,   // tri1
                      6, 10, 7,  // tri2
                      11, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 10, 3, // tri0
                      10, 12, 7, // tri1
                      7, 12, 13, // tri2
                      7, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(0, 7, 14,   // tri0
                      15, 11, 16, // tri1
                      16, 3, 9,   // tri2
                      16, 11, 3   // tri3
                      ),
    gsSPNTriangles_5b(15, 13, 12, // tri0
                      12, 11, 15, // tri1
                      17, 18, 8,  // tri2
                      2, 1, 17    // tri3
                      ),
    gsSPNTriangles_5b(17, 8, 2, // tri0
                      2, 6, 0,  // tri1
                      8, 18, 5, // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&duk_1_v[45], 13, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          1, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 7, 2, // tri0
                      5, 8, 0, // tri1
                      0, 2, 9, // tri2
                      10, 3, 5 // tri3
                      ),
    gsSPNTriangles_5b(10, 5, 9, // tri0
                      4, 11, 8, // tri1
                      4, 8, 5,  // tri2
                      9, 2, 12  // tri3
                      ),
    gsSPNTriangles_5b(9, 12, 10, // tri0
                      12, 2, 7,  // tri1
                      9, 5, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&duk_1_v[58], 27, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,  // tri0
                      0, 3, 11,  // tri1
                      0, 12, 1,  // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 0, // tri0
                      16, 17, 8, // tri1
                      7, 15, 5,  // tri2
                      6, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 7, // tri0
                      4, 8, 10,  // tri1
                      10, 3, 4,  // tri2
                      16, 8, 4   // tri3
                      ),
    gsSPNTriangles_5b(21, 14, 13, // tri0
                      22, 20, 23, // tri1
                      24, 25, 22, // tri2
                      24, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(2, 4, 0,    // tri0
                      7, 20, 13,  // tri1
                      13, 20, 22, // tri2
                      23, 20, 19  // tri3
                      ),
    gsSPNTriangles_5b(15, 7, 13, // tri0
                      19, 7, 6,  // tri1
                      4, 2, 16,  // tri2
                      19, 18, 26 // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&duk_1_v[85], 16, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10, // tri0
                      0, 2, 4,  // tri1
                      11, 5, 4, // tri2
                      6, 5, 11  // tri3
                      ),
    gsSPNTriangles_5b(10, 7, 6,  // tri0
                      11, 12, 6, // tri1
                      4, 12, 11, // tri2
                      12, 4, 2   // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 8, // tri0
                      7, 14, 5,  // tri1
                      5, 14, 3,  // tri2
                      8, 6, 12   // tri3
                      ),
    gsSPNTriangles_5b(6, 8, 10,  // tri0
                      2, 15, 12, // tri1
                      4, 3, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx mouth_duk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*14, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&duk_1_v[0], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&duk_1_v[4], 22, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 4, // tri0
                          2, 6, 5, // tri1
                          1, 2, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 8, 9,   // tri0
                      0, 11, 10, // tri1
                      3, 0, 12,  // tri2
                      0, 14, 13  // tri3
                      ),
    gsSPNTrianglesInit_5b(10,         // tri count
                          15, 16, 17, // tri0
                          18, 17, 16, // tri1
                          18, 16, 19  // tri2
                          ),
    gsSPNTriangles_5b(20, 21, 22, // tri0
                      20, 22, 23, // tri1
                      16, 15, 24, // tri2
                      24, 19, 16  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 24, // tri0
                      25, 18, 24, // tri1
                      15, 17, 20, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_duk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&duk_1_v[133], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&duk_1_v[137], 15, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 0, 4, // tri0
                          3, 5, 6, // tri1
                          1, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 9, 0,   // tri0
                      3, 10, 11, // tri1
                      2, 3, 12,  // tri2
                      3, 13, 14  // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          15, 16, 17, // tri0
                          18, 15, 17, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_duk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&duk_1_v[152], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&duk_1_v[156], 9, 4),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 4, // tri0
                          2, 0, 5, // tri1
                          0, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 8, 9,   // tri0
                      1, 3, 10,  // tri1
                      3, 11, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_duk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&duk_1_v[101], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&duk_1_v[105], 15, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 3, 4, // tri0
                          3, 5, 6, // tri1
                          0, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 9, 1,   // tri0
                      3, 10, 11, // tri1
                      3, 2, 12,  // tri2
                      3, 13, 14  // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          15, 16, 17, // tri0
                          15, 17, 18, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_duk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&duk_1_v[120], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&duk_1_v[124], 9, 4),
    gsSPNTrianglesInit_5b(6,       // tri count
                          1, 0, 4, // tri0
                          0, 2, 5, // tri1
                          0, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 8, 9,   // tri0
                      3, 1, 10,  // tri1
                      3, 11, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_duk_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&duk_1_v[165], 9, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_3_txt, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 252, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&duk_1_v[174], 20, 9),
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
    gsSPVertex(&duk_1_v[194], 17, 0),
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

static Gfx tail1_duk_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&duk_1_v[211], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&duk_1_v[217], 6, 6),
    gsSPNTrianglesInit_5b(6,       // tri count
                          2, 6, 4, // tri0
                          0, 4, 7, // tri1
                          1, 8, 5  // tri2
                          ),
    gsSPNTriangles_5b(3, 9, 2,  // tri0
                      5, 10, 3, // tri1
                      1, 0, 11, // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot3_duk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&duk_1_v[272], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&duk_1_v[276], 16, 4),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 4, 5, // tri0
                          2, 1, 6, // tri1
                          2, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 3, 9,   // tri0
                      1, 0, 10,  // tri1
                      0, 11, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(5,          // tri count
                          13, 14, 15, // tri0
                          16, 17, 13, // tri1
                          13, 15, 16  // tri2
                          ),
    gsSPNTriangles_5b(18, 17, 16, // tri0
                      18, 16, 19, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_duk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&duk_1_v[292], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&duk_1_v[297], 14, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 5, 6, // tri0
                          2, 3, 7, // tri1
                          3, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 10,  // tri0
                      4, 1, 11,  // tri1
                      2, 12, 13, // tri2
                      4, 14, 15  // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          16, 17, 18, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_duk_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&duk_1_v[311], 10, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 0, 8, // tri0
                      6, 9, 4, // tri1
                      0, 7, 1, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot3_duk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&duk_1_v[223], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&duk_1_v[227], 16, 4),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 4, 5, // tri0
                          1, 6, 7, // tri1
                          1, 2, 8  // tri2
                          ),
    gsSPNTriangles_5b(3, 0, 9,   // tri0
                      0, 1, 10,  // tri1
                      0, 11, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(5,          // tri count
                          13, 14, 15, // tri0
                          15, 16, 17, // tri1
                          17, 13, 15  // tri2
                          ),
    gsSPNTriangles_5b(18, 17, 16, // tri0
                      18, 16, 19, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_duk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&duk_1_v[243], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&duk_1_v[248], 14, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 5, 6, // tri0
                          3, 2, 7, // tri1
                          3, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(2, 0, 10,  // tri0
                      1, 4, 11,  // tri1
                      2, 12, 13, // tri2
                      4, 14, 15  // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          16, 17, 18, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_duk_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&duk_1_v[262], 10, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 3, 8, // tri0
                      6, 9, 4, // tri1
                      2, 8, 3, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_duk_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&duk_1_v[321], 23, 0),
    gsSPNTrianglesInit_5b(30,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          2, 1, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 0, 2, // tri0
                      5, 1, 6, // tri1
                      7, 3, 8, // tri2
                      7, 8, 9  // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 10,  // tri0
                      5, 6, 11,  // tri1
                      12, 5, 11, // tri2
                      8, 3, 4    // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      9, 10, 14,  // tri1
                      13, 15, 16, // tri2
                      14, 10, 15  // tri3
                      ),
    gsSPNTriangles_5b(13, 16, 17, // tri0
                      17, 16, 18, // tri1
                      18, 16, 19, // tri2
                      1, 0, 20    // tri3
                      ),
    gsSPNTriangles_5b(1, 20, 21,  // tri0
                      20, 0, 22,  // tri1
                      21, 20, 13, // tri2
                      13, 20, 22  // tri3
                      ),
    gsSPNTriangles_5b(6, 1, 21,   // tri0
                      21, 13, 17, // tri1
                      22, 3, 7,   // tri2
                      7, 9, 22    // tri3
                      ),
    gsSPNTriangles_5b(0, 3, 22,   // tri0
                      13, 22, 14, // tri1
                      9, 14, 22,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_duk_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_duk_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_duk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_duk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { Lfoot3_duk_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_duk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_duk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { Rfoot3_duk_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 75,0,-650 },
    /* joint 11 */ { tail1_duk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_duk_model, 3, cKF_JOINT_FLAG_DISP_OPA, 325,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,-420,0 },
    /* joint 15 */ { Larm1_duk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_duk_model, 0, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,420,0 },
    /* joint 18 */ { Rarm1_duk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_duk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 675,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 600,0,1150 },
    /* joint 23 */ { mouth_duk_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_duk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1003,0,2 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_duk_1 = { 26, 15, cKF_je_r_duk_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_duk_1_c(void) {
    pc_load_asset("assets/npc/mdl/duk_1_v.bin", duk_1_v, 0x1580, 0x4C6FA0, 0, 2);
}
#endif
