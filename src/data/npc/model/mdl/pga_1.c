#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx pga_1_v[0x1A20 / sizeof(Vtx)];
#else
static Vtx pga_1_v[] = {
#include "assets/npc/mdl/pga_1_v.inc"
};
#endif

static Gfx head_pga_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x180, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pga_1_v[40], 30, 0),
    gsSPNTrianglesInit_5b(1,       // tri count
                          0, 1, 2, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(15,       // tri count
                          3, 4, 5,  // tri0
                          6, 7, 8,  // tri1
                          9, 10, 11 // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 9,   // tri0
                      12, 13, 6, // tri1
                      14, 9, 15, // tri2
                      5, 12, 9   // tri3
                      ),
    gsSPNTriangles_5b(13, 12, 5, // tri0
                      16, 7, 6,  // tri1
                      9, 14, 17, // tri2
                      16, 13, 5  // tri3
                      ),
    gsSPNTriangles_5b(6, 9, 12,  // tri0
                      6, 13, 16, // tri1
                      17, 10, 9, // tri2
                      11, 3, 9   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(5,          // tri count
                          18, 19, 20, // tri0
                          18, 20, 21, // tri1
                          22, 23, 19  // tri2
                          ),
    gsSPNTriangles_5b(24, 21, 20, // tri0
                      22, 19, 18, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,          // tri count
                          25, 26, 27, // tri0
                          27, 28, 29, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPVertex(&pga_1_v[70], 12, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1,       // tri count
                          0, 1, 2, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1,       // tri count
                          3, 4, 5, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1,       // tri count
                          6, 7, 8, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1,         // tri count
                          9, 10, 11, // tri0
                          0, 0, 0,   // tri1
                          0, 0, 0    // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pga_1_v[82], 30, 0),
    gsSPNTrianglesInit_5b(48,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(5, 8, 9,   // tri0
                      6, 10, 11, // tri1
                      6, 11, 3,  // tri2
                      6, 9, 10   // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 14, // tri0
                      2, 15, 12,  // tri1
                      12, 16, 17, // tri2
                      11, 10, 18  // tri3
                      ),
    gsSPNTriangles_5b(11, 18, 19, // tri0
                      4, 11, 19,  // tri1
                      4, 15, 2,   // tri2
                      1, 4, 2     // tri3
                      ),
    gsSPNTriangles_5b(13, 20, 14, // tri0
                      5, 21, 22,  // tri1
                      13, 18, 20, // tri2
                      20, 9, 8    // tri3
                      ),
    gsSPNTriangles_5b(12, 15, 13, // tri0
                      13, 15, 19, // tri1
                      19, 18, 13, // tri2
                      23, 16, 14  // tri3
                      ),
    gsSPNTriangles_5b(14, 8, 23, // tri0
                      9, 6, 5,   // tri1
                      8, 5, 22,  // tri2
                      16, 12, 14 // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 26, // tri0
                      17, 2, 12,  // tri1
                      14, 20, 8,  // tri2
                      11, 4, 3    // tri3
                      ),
    gsSPNTriangles_5b(9, 20, 18, // tri0
                      18, 10, 9, // tri1
                      19, 15, 4, // tri2
                      3, 27, 26  // tri3
                      ),
    gsSPNTriangles_5b(24, 7, 6,  // tri0
                      26, 27, 7, // tri1
                      26, 7, 24, // tri2
                      6, 3, 25   // tri3
                      ),
    gsSPNTriangles_5b(25, 24, 6, // tri0
                      3, 26, 25, // tri1
                      7, 21, 5,  // tri2
                      27, 3, 1   // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 29, // tri0
                      29, 21, 7,  // tri1
                      29, 7, 27,  // tri2
                      1, 28, 27   // tri3
                      ),
    gsSPNTriangles_5b(0, 28, 1, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pga_1_v[112], 7, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 2, 4, // tri1
                          1, 5, 2  // tri2
                          ),
    gsSPNTriangles_5b(2, 6, 0, // tri0
                      2, 3, 6, // tri1
                      4, 2, 5, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx mouth_pga_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*14, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pga_1_v[0], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pga_1_v[5], 15, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 5, 6, // tri0
                          4, 8, 7, // tri1
                          2, 4, 9  // tri2
                          ),
    gsSPNTriangles_5b(4, 0, 10,  // tri0
                      2, 11, 12, // tri1
                      0, 13, 14, // tri2
                      2, 15, 16  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,         // tri count
                          1, 3, 17,  // tri0
                          3, 19, 18, // tri1
                          0, 0, 0    // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&pga_1_v[20], 20, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 1  // tri2
                          ),
    gsSPNTriangles_5b(0, 8, 6,   // tri0
                      9, 10, 4,  // tri1
                      11, 10, 9, // tri2
                      12, 8, 10  // tri3
                      ),
    gsSPNTriangles_5b(12, 10, 11, // tri0
                      8, 0, 4,    // tri1
                      4, 10, 8,   // tri2
                      4, 0, 2     // tri3
                      ),
    gsSPNTriangles_5b(4, 2, 5,  // tri0
                      9, 4, 3,  // tri1
                      6, 8, 12, // tri2
                      1, 0, 6   // tri3
                      ),
    gsSPNTriangles_5b(3, 13, 9, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,          // tri count
                          14, 15, 16, // tri0
                          17, 15, 14, // tri1
                          17, 14, 18  // tri2
                          ),
    gsSPNTriangles_5b(14, 16, 19, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_pga_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pga_1_v[192], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pga_1_v[197], 23, 5),
    gsSPNTrianglesInit_5b(9,       // tri count
                          3, 5, 6, // tri0
                          2, 4, 7, // tri1
                          0, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(3, 1, 10,  // tri0
                      3, 11, 12, // tri1
                      0, 2, 13,  // tri2
                      4, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(2, 17, 16, // tri0
                      4, 3, 18,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          19, 20, 21, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(4,          // tri count
                          22, 23, 24, // tri0
                          24, 25, 22, // tri1
                          22, 26, 23  // tri2
                          ),
    gsSPNTriangles_5b(25, 27, 22, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_pga_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pga_1_v[220], 8, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pga_1_v[228], 13, 8),
    gsSPNTrianglesInit_5b(8,         // tri count
                          2, 8, 9,   // tri0
                          0, 10, 11, // tri1
                          3, 0, 12   // tri2
                          ),
    gsSPNTriangles_5b(5, 13, 14, // tri0
                      5, 4, 15,  // tri1
                      1, 6, 16,  // tri2
                      7, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(0, 20, 19, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&pga_1_v[241], 24, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 4, // tri1
                          5, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      4, 1, 0,   // tri1
                      9, 10, 6,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      10, 11, 7,  // tri1
                      16, 17, 14, // tri2
                      8, 18, 6    // tri3
                      ),
    gsSPNTriangles_5b(7, 6, 10,   // tri0
                      19, 20, 21, // tri1
                      13, 12, 22, // tri2
                      23, 19, 21  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_pga_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pga_1_v[119], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pga_1_v[124], 23, 5),
    gsSPNTrianglesInit_5b(9,       // tri count
                          3, 5, 6, // tri0
                          4, 2, 7, // tri1
                          0, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(1, 3, 10,  // tri0
                      3, 11, 12, // tri1
                      2, 0, 13,  // tri2
                      4, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(2, 17, 16, // tri0
                      3, 4, 18,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          19, 20, 21, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(4,          // tri count
                          22, 23, 24, // tri0
                          24, 25, 22, // tri1
                          23, 26, 24  // tri2
                          ),
    gsSPNTriangles_5b(24, 27, 25, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_pga_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pga_1_v[147], 8, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pga_1_v[155], 13, 8),
    gsSPNTrianglesInit_5b(8,         // tri count
                          2, 8, 9,   // tri0
                          0, 10, 11, // tri1
                          0, 3, 12   // tri2
                          ),
    gsSPNTriangles_5b(5, 13, 14, // tri0
                      4, 5, 15,  // tri1
                      6, 1, 16,  // tri2
                      7, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(0, 20, 19, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&pga_1_v[168], 24, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 2, // tri1
                          4, 3, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      2, 1, 3,   // tri1
                      8, 9, 10,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      7, 13, 9,   // tri1
                      16, 17, 14, // tri2
                      8, 18, 6    // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 7,    // tri0
                      19, 20, 21, // tri1
                      22, 12, 11, // tri2
                      19, 21, 23  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_pga_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pga_1_v[265], 32, 0),
    gsSPNTrianglesInit_5b(40,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,   // tri0
                      10, 7, 11, // tri1
                      3, 12, 0,  // tri2
                      13, 14, 5  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      18, 19, 20, // tri1
                      1, 20, 2,   // tri2
                      3, 19, 18   // tri3
                      ),
    gsSPNTriangles_5b(7, 17, 16, // tri0
                      21, 4, 18, // tri1
                      17, 4, 21, // tri2
                      8, 22, 9   // tri3
                      ),
    gsSPNTriangles_5b(21, 15, 17, // tri0
                      18, 20, 21, // tri1
                      3, 18, 23,  // tri2
                      21, 20, 24  // tri3
                      ),
    gsSPNTriangles_5b(21, 24, 15, // tri0
                      8, 15, 22,  // tri1
                      2, 19, 3,   // tri2
                      16, 8, 7    // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 7,   // tri0
                      13, 17, 7,  // tri1
                      23, 25, 26, // tri2
                      27, 6, 5    // tri3
                      ),
    gsSPNTriangles_5b(27, 5, 28, // tri0
                      23, 18, 6, // tri1
                      6, 18, 4,  // tri2
                      4, 17, 5   // tri3
                      ),
    gsSPNTriangles_5b(25, 23, 6,  // tri0
                      5, 17, 13,  // tri1
                      14, 13, 10, // tri2
                      13, 7, 10   // tri3
                      ),
    gsSPNTriangles_5b(26, 3, 23,  // tri0
                      12, 3, 26,  // tri1
                      12, 26, 29, // tri2
                      28, 30, 31  // tri3
                      ),
    gsSPNTriangles_5b(28, 31, 27, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_pga_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pga_1_v[408], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pga_1_v[413], 5, 5),
    gsSPNTrianglesInit_5b(5,       // tri count
                          2, 5, 0, // tri0
                          0, 6, 3, // tri1
                          1, 7, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 8, 1, // tri0
                      4, 3, 9, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot3_pga_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pga_1_v[344], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pga_1_v[347], 18, 3),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 3, 4, // tri0
                          1, 0, 5, // tri1
                          0, 2, 6  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 7,   // tri0
                      2, 8, 9,   // tri1
                      0, 10, 11, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(5,          // tri count
                          12, 13, 14, // tri0
                          12, 14, 15, // tri1
                          16, 17, 18  // tri2
                          ),
    gsSPNTriangles_5b(18, 19, 16, // tri0
                      16, 20, 17, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_pga_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pga_1_v[365], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pga_1_v[369], 14, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 4, 5, // tri0
                          2, 6, 7, // tri1
                          3, 0, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 2, 9,   // tri0
                      2, 10, 11, // tri1
                      2, 3, 12,  // tri2
                      3, 13, 14  // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          15, 16, 17, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_pga_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pga_1_v[383], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          3, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 0, 6, // tri0
                      4, 7, 3, // tri1
                      0, 5, 1, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot3_pga_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pga_1_v[297], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pga_1_v[300], 18, 3),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 3, 4, // tri0
                          0, 1, 5, // tri1
                          2, 0, 6  // tri2
                          ),
    gsSPNTriangles_5b(1, 7, 8,   // tri0
                      1, 2, 9,   // tri1
                      0, 10, 11, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(5,          // tri count
                          12, 13, 14, // tri0
                          12, 14, 15, // tri1
                          16, 17, 18  // tri2
                          ),
    gsSPNTriangles_5b(18, 19, 16, // tri0
                      17, 20, 18, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_pga_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pga_1_v[318], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pga_1_v[322], 14, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 4, 5, // tri0
                          2, 6, 7, // tri1
                          0, 3, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 9,   // tri0
                      2, 10, 11, // tri1
                      3, 2, 12,  // tri2
                      3, 13, 14  // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          15, 16, 17, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_pga_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x600, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pga_1_v[336], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 1, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 3, 6, // tri0
                      0, 7, 4, // tri1
                      2, 6, 3, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_pga_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pga_1_v[391], 17, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 8,   // tri0
                      3, 9, 10,  // tri1
                      7, 6, 11,  // tri2
                      12, 13, 10 // tri3
                      ),
    gsSPNTriangles_5b(6, 14, 13,  // tri0
                      6, 13, 11,  // tri1
                      12, 15, 11, // tri2
                      1, 0, 14    // tri3
                      ),
    gsSPNTriangles_5b(14, 5, 1,   // tri0
                      14, 10, 13, // tri1
                      14, 6, 5,   // tri2
                      0, 10, 14   // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      6, 7, 4,    // tri1
                      11, 15, 7,  // tri2
                      16, 3, 2    // tri3
                      ),
    gsSPNTriangles_5b(10, 0, 3,  // tri0
                      10, 9, 12, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_pga_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_pga_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_pga_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_pga_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { Lfoot3_pga_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_pga_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_pga_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { Rfoot3_pga_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 75,0,-650 },
    /* joint 11 */ { tail1_pga_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_pga_model, 3, cKF_JOINT_FLAG_DISP_OPA, 325,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 1150,-500,0 },
    /* joint 15 */ { Larm1_pga_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_pga_model, 0, cKF_JOINT_FLAG_DISP_OPA, 801,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 1150,500,0 },
    /* joint 18 */ { Rarm1_pga_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_pga_model, 1, cKF_JOINT_FLAG_DISP_OPA, 800,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 801,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 1274,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 1050,0,1350 },
    /* joint 23 */ { mouth_pga_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_pga_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1501,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_pga_1 = { 26, 15, cKF_je_r_pga_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_pga_1_c(void) {
    pc_load_asset("assets/npc/mdl/pga_1_v.bin", pga_1_v, 0x1A20, 0x62EAE0, 0, 2);
}
#endif
