#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx pkn_1_v[0x1200 / sizeof(Vtx)];
#else
static Vtx pkn_1_v[] = {
#include "assets/npc/mdl/pkn_1_v.inc"
};
#endif

static Gfx head_pkn_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pkn_1_v[0], 31, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 4, 7, // tri0
                      4, 0, 3, // tri1
                      5, 1, 0, // tri2
                      3, 8, 5  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 32, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(28,         // tri count
                          9, 10, 11,  // tri0
                          12, 11, 13, // tri1
                          11, 10, 14  // tri2
                          ),
    gsSPNTriangles_5b(14, 10, 15, // tri0
                      14, 15, 16, // tri1
                      17, 18, 19, // tri2
                      20, 15, 21  // tri3
                      ),
    gsSPNTriangles_5b(16, 15, 20, // tri0
                      21, 22, 20, // tri1
                      19, 23, 17, // tri2
                      19, 12, 23  // tri3
                      ),
    gsSPNTriangles_5b(23, 12, 13, // tri0
                      24, 12, 19, // tri1
                      10, 21, 15, // tri2
                      24, 10, 9   // tri3
                      ),
    gsSPNTriangles_5b(24, 21, 10, // tri0
                      25, 26, 17, // tri1
                      22, 27, 20, // tri2
                      28, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(17, 23, 25, // tri0
                      13, 25, 23, // tri1
                      20, 29, 16, // tri2
                      21, 24, 30  // tri3
                      ),
    gsSPNTriangles_5b(30, 24, 19, // tri0
                      30, 22, 21, // tri1
                      19, 18, 30, // tri2
                      11, 12, 9   // tri3
                      ),
    gsSPNTriangles_5b(9, 12, 24, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x140, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 252, 255, 255),
    gsSPVertex(&pkn_1_v[31], 26, 0),
    gsSPNTrianglesInit_5b(43,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 4, // tri1
                          0, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(6, 5, 7,  // tri0
                      8, 1, 9,  // tri1
                      10, 3, 0, // tri2
                      2, 1, 8   // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 11,   // tri0
                      12, 13, 14, // tri1
                      11, 3, 10,  // tri2
                      14, 13, 0   // tri3
                      ),
    gsSPNTriangles_5b(0, 13, 15,  // tri0
                      15, 13, 12, // tri1
                      16, 17, 18, // tri2
                      18, 17, 0   // tri3
                      ),
    gsSPNTriangles_5b(9, 1, 0,  // tri0
                      2, 8, 19, // tri1
                      0, 2, 18, // tri2
                      0, 17, 20 // tri3
                      ),
    gsSPNTriangles_5b(20, 17, 16, // tri0
                      7, 5, 21,   // tri1
                      22, 23, 24, // tri2
                      24, 23, 0   // tri3
                      ),
    gsSPNTriangles_5b(21, 5, 0,  // tri0
                      0, 6, 24,  // tri1
                      0, 23, 25, // tri2
                      25, 23, 22 // tri3
                      ),
    gsSPNTriangles_5b(6, 7, 22,  // tri0
                      15, 9, 0,  // tri1
                      0, 25, 14, // tri2
                      0, 20, 10  // tri3
                      ),
    gsSPNTriangles_5b(4, 21, 0,   // tri0
                      8, 9, 15,   // tri1
                      14, 25, 22, // tri2
                      14, 22, 12  // tri3
                      ),
    gsSPNTriangles_5b(7, 21, 4,   // tri0
                      10, 20, 16, // tri1
                      10, 16, 11, // tri2
                      15, 12, 8   // tri3
                      ),
    gsSPNTriangles_5b(22, 24, 6, // tri0
                      4, 11, 7,  // tri1
                      18, 2, 19, // tri2
                      19, 16, 18 // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pkn_1_v[57], 22, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 7, // tri0
                      4, 8, 7, // tri1
                      9, 2, 1, // tri2
                      6, 8, 4  // tri3
                      ),
    gsSPNTriangles_5b(1, 10, 9,  // tri0
                      11, 12, 9, // tri1
                      8, 0, 7,   // tri2
                      11, 9, 10  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 48, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8,          // tri count
                          13, 14, 15, // tri0
                          16, 14, 13, // tri1
                          14, 16, 17  // tri2
                          ),
    gsSPNTriangles_5b(18, 15, 14, // tri0
                      13, 19, 16, // tri1
                      14, 17, 20, // tri2
                      15, 21, 13  // tri3
                      ),
    gsSPNTriangles_5b(20, 18, 14, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_pkn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pkn_1_v[113], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x500, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pkn_1_v[117], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          2, 4, 5, // tri0
                          2, 0, 6, // tri1
                          2, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 9,   // tri0
                      1, 11, 10, // tri1
                      2, 12, 3,  // tri2
                      1, 3, 13   // tri3
                      ),
    gsSPNTriangles_5b(1, 15, 14, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          16, 17, 18, // tri0
                          18, 17, 19, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_pkn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pkn_1_v[133], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x500, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pkn_1_v[136], 11, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 2, 3, // tri0
                          0, 4, 5, // tri1
                          1, 7, 6  // tri2
                          ),
    gsSPNTriangles_5b(2, 8, 9,  // tri0
                      2, 1, 10, // tri1
                      1, 0, 11, // tri2
                      1, 12, 13 // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_pkn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pkn_1_v[79], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x500, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pkn_1_v[83], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          2, 4, 5, // tri0
                          0, 2, 6, // tri1
                          2, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 9,   // tri0
                      1, 11, 10, // tri1
                      3, 12, 2,  // tri2
                      3, 1, 13   // tri3
                      ),
    gsSPNTriangles_5b(1, 15, 14, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          16, 17, 18, // tri0
                          19, 17, 16, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_pkn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pkn_1_v[99], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x500, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pkn_1_v[102], 11, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 0, 3, // tri0
                          0, 4, 5, // tri1
                          1, 7, 6  // tri2
                          ),
    gsSPNTriangles_5b(2, 8, 9,  // tri0
                      1, 2, 10, // tri1
                      0, 1, 11, // tri2
                      1, 12, 13 // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_pkn_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pkn_1_v[147], 6, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pkn_1_v[153], 20, 6),
    gsSPNTrianglesInit_5b(13,      // tri count
                          4, 6, 1, // tri0
                          4, 0, 7, // tri1
                          2, 5, 8  // tri2
                          ),
    gsSPNTriangles_5b(5, 3, 9,   // tri0
                      1, 10, 11, // tri1
                      0, 12, 13, // tri2
                      0, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(3, 1, 16,  // tri0
                      5, 17, 18, // tri1
                      3, 19, 20, // tri2
                      2, 21, 0   // tri3
                      ),
    gsSPNTriangles_5b(1, 23, 22, // tri0
                      2, 24, 25, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&pkn_1_v[173], 7, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          0, 5, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 6, // tri0
                      4, 5, 0, // tri1
                      4, 0, 2, // tri2
                      6, 5, 4  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_pkn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pkn_1_v[228], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pkn_1_v[233], 17, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          1, 5, 6, // tri0
                          2, 3, 7, // tri1
                          1, 2, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 9,   // tri0
                      4, 0, 10,  // tri1
                      0, 12, 11, // tri2
                      2, 14, 13  // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          15, 16, 17, // tri0
                          18, 19, 20, // tri1
                          20, 21, 16  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_pkn_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pkn_1_v[250], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pkn_1_v[254], 22, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 3, 4, // tri0
                          0, 5, 1, // tri1
                          0, 7, 6  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 8,   // tri0
                      2, 9, 10,  // tri1
                      1, 11, 12, // tri2
                      3, 2, 13   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7,          // tri count
                          14, 15, 16, // tri0
                          17, 18, 19, // tri1
                          15, 20, 16  // tri2
                          ),
    gsSPNTriangles_5b(21, 19, 18, // tri0
                      21, 18, 14, // tri1
                      14, 16, 21, // tri2
                      19, 22, 17  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1,          // tri count
                          23, 24, 25, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_pkn_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pkn_1_v[180], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pkn_1_v[185], 17, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          1, 5, 6, // tri0
                          3, 2, 7, // tri1
                          2, 1, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 9,   // tri0
                      0, 4, 10,  // tri1
                      0, 12, 11, // tri2
                      2, 14, 13  // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          15, 16, 17, // tri0
                          18, 19, 20, // tri1
                          16, 21, 18  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_pkn_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pkn_1_v[202], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&pkn_1_v[206], 22, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 0, 4, // tri0
                          1, 5, 0, // tri1
                          0, 7, 6  // tri2
                          ),
    gsSPNTriangles_5b(1, 2, 8,   // tri0
                      2, 9, 10,  // tri1
                      1, 11, 12, // tri2
                      2, 3, 13   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7,          // tri count
                          14, 15, 16, // tri0
                          17, 18, 19, // tri1
                          14, 20, 15  // tri2
                          ),
    gsSPNTriangles_5b(18, 17, 21, // tri0
                      16, 18, 21, // tri1
                      21, 14, 16, // tri2
                      19, 22, 17  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1,          // tri count
                          23, 24, 25, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx base_pkn_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&pkn_1_v[276], 12, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          5, 6, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 8,  // tri0
                      4, 0, 2,  // tri1
                      0, 9, 1,  // tri2
                      7, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(7, 11, 8,  // tri0
                      10, 1, 11, // tri1
                      3, 0, 4,   // tri2
                      9, 11, 1   // tri3
                      ),
    gsSPNTriangles_5b(8, 6, 5, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_pkn_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_pkn_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-250,0 },
    /* joint 3 */ { Lfoot1_pkn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_pkn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,250,0 },
    /* joint 7 */ { Rfoot1_pkn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_pkn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 75,0,-475 },
    /* joint 11 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_pkn_model, 3, cKF_JOINT_FLAG_DISP_OPA, 325,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 425,-450,0 },
    /* joint 15 */ { Larm1_pkn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_pkn_model, 0, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 425,450,0 },
    /* joint 18 */ { Rarm1_pkn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_pkn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 350,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 675,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,600 },
    /* joint 23 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_pkn_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1100,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_pkn_1 = { 26, 11, cKF_je_r_pkn_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_pkn_1_c(void) {
    pc_load_asset("assets/npc/mdl/pkn_1_v.bin", pkn_1_v, 0x1200, 0x5277E0, 0, 2);
}
#endif
