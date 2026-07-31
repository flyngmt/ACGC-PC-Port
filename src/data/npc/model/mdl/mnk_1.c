#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx mnk_1_v[0x1850 / sizeof(Vtx)];
#else
static Vtx mnk_1_v[] = {
#include "assets/npc/mdl/mnk_1_v.inc"
};
#endif

static Gfx head_mnk_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mnk_1_v[0], 15, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          5, 1, 3  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 3,  // tri0
                      8, 0, 9,  // tri1
                      9, 10, 8, // tri2
                      3, 0, 6   // tri3
                      ),
    gsSPNTriangles_5b(8, 7, 6,   // tri0
                      7, 11, 12, // tri1
                      3, 1, 0,   // tri2
                      12, 11, 13 // tri3
                      ),
    gsSPNTriangles_5b(13, 11, 8, // tri0
                      3, 7, 4,   // tri1
                      2, 1, 5,   // tri2
                      12, 4, 7   // tri3
                      ),
    gsSPNTriangles_5b(0, 14, 9, // tri0
                      8, 11, 7, // tri1
                      6, 0, 8,  // tri2
                      8, 10, 13 // tri3
                      ),
    gsSPNTriangles_5b(2, 14, 0, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 250, 255),
    gsSPVertex(&mnk_1_v[15], 28, 0),
    gsSPNTrianglesInit_5b(39,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(6, 0, 9,   // tri0
                      10, 7, 11, // tri1
                      12, 1, 13, // tri2
                      14, 15, 8  // tri3
                      ),
    gsSPNTriangles_5b(0, 16, 13,  // tri0
                      2, 17, 0,   // tri1
                      15, 14, 18, // tri2
                      8, 10, 19   // tri3
                      ),
    gsSPNTriangles_5b(8, 7, 10,  // tri0
                      20, 16, 5, // tri1
                      13, 1, 0,  // tri2
                      15, 21, 8  // tri3
                      ),
    gsSPNTriangles_5b(13, 16, 20, // tri0
                      3, 21, 15,  // tri1
                      6, 5, 16,   // tri2
                      6, 8, 21    // tri3
                      ),
    gsSPNTriangles_5b(10, 22, 23, // tri0
                      24, 25, 17, // tri1
                      16, 0, 6,   // tri2
                      21, 5, 6    // tri3
                      ),
    gsSPNTriangles_5b(5, 21, 3,  // tri0
                      5, 4, 20,  // tri1
                      17, 9, 0,  // tri2
                      26, 17, 25 // tri3
                      ),
    gsSPNTriangles_5b(22, 10, 26, // tri0
                      25, 22, 26, // tri1
                      11, 9, 17,  // tri2
                      6, 9, 27    // tri3
                      ),
    gsSPNTriangles_5b(11, 7, 27,  // tri0
                      11, 26, 10, // tri1
                      17, 26, 11, // tri2
                      27, 9, 11   // tri3
                      ),
    gsSPNTriangles_5b(27, 7, 6,   // tri0
                      24, 17, 2,  // tri1
                      19, 10, 23, // tri2
                      8, 19, 14   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mnk_1_v[43], 25, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          5, 1, 0  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 4, // tri0
                      4, 3, 6, // tri1
                      2, 8, 0, // tri2
                      4, 8, 2  // tri3
                      ),
    gsSPNTriangles_5b(0, 9, 5, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(15,         // tri count
                          10, 11, 12, // tri0
                          13, 14, 15, // tri1
                          16, 13, 15  // tri2
                          ),
    gsSPNTriangles_5b(12, 16, 17, // tri0
                      14, 13, 18, // tri1
                      17, 19, 12, // tri2
                      15, 17, 16  // tri3
                      ),
    gsSPNTriangles_5b(18, 20, 14, // tri0
                      21, 18, 12, // tri1
                      12, 19, 10, // tri2
                      18, 13, 16  // tri3
                      ),
    gsSPNTriangles_5b(18, 16, 12, // tri0
                      22, 20, 18, // tri1
                      23, 24, 22, // tri2
                      18, 23, 22  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&mnk_1_v[68], 26, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 3,  // tri0
                      2, 4, 11,  // tri1
                      5, 9, 3,   // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 12, // tri0
                      14, 16, 15, // tri1
                      8, 17, 6,   // tri2
                      13, 18, 14  // tri3
                      ),
    gsSPNTriangles_5b(6, 19, 7,  // tri0
                      2, 11, 20, // tri1
                      20, 0, 2,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 252, 255, 255),
    gsSPNTrianglesInit_5b(3,          // tri count
                          21, 22, 23, // tri0
                          23, 24, 25, // tri1
                          25, 21, 23  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_mnk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mnk_1_v[134], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mnk_1_v[138], 22, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          2, 3, 4, // tri0
                          0, 2, 5, // tri1
                          0, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 8, 9,   // tri0
                      1, 10, 11, // tri1
                      3, 1, 12,  // tri2
                      1, 0, 13   // tri3
                      ),
    gsSPNTriangles_5b(3, 14, 15, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(9,          // tri count
                          16, 17, 18, // tri0
                          19, 20, 16, // tri1
                          20, 21, 16  // tri2
                          ),
    gsSPNTriangles_5b(17, 16, 21, // tri0
                      16, 18, 19, // tri1
                      21, 19, 18, // tri2
                      21, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 24, // tri0
                      22, 24, 25, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_mnk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mnk_1_v[160], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mnk_1_v[163], 11, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 3, 1, // tri0
                          0, 5, 4, // tri1
                          2, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 8, 9,   // tri0
                      0, 10, 11, // tri1
                      2, 0, 12,  // tri2
                      0, 1, 13   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_mnk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mnk_1_v[94], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mnk_1_v[98], 22, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          3, 2, 4, // tri0
                          2, 0, 5, // tri1
                          0, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 8, 9,   // tri0
                      1, 10, 11, // tri1
                      1, 3, 12,  // tri2
                      0, 1, 13   // tri3
                      ),
    gsSPNTriangles_5b(3, 14, 15, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(9,          // tri count
                          16, 17, 18, // tri0
                          18, 19, 20, // tri1
                          18, 21, 19  // tri2
                          ),
    gsSPNTriangles_5b(21, 18, 17, // tri0
                      20, 16, 18, // tri1
                      17, 16, 20, // tri2
                      17, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 24, // tri0
                      22, 24, 25, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_mnk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mnk_1_v[120], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mnk_1_v[123], 11, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          1, 3, 2, // tri0
                          0, 5, 4, // tri1
                          2, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 8, 9,   // tri0
                      0, 10, 11, // tri1
                      0, 2, 12,  // tri2
                      1, 0, 13   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_mnk_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mnk_1_v[174], 9, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x340, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mnk_1_v[183], 21, 9),
    gsSPNTrianglesInit_5b(13,       // tri count
                          2, 1, 9,  // tri0
                          1, 0, 10, // tri1
                          1, 12, 11 // tri2
                          ),
    gsSPNTriangles_5b(0, 13, 14, // tri0
                      0, 6, 15,  // tri1
                      0, 16, 17, // tri2
                      7, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(4, 20, 21, // tri0
                      3, 22, 23, // tri1
                      4, 3, 24,  // tri2
                      2, 25, 3   // tri3
                      ),
    gsSPNTriangles_5b(8, 27, 26, // tri0
                      4, 28, 29, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&mnk_1_v[204], 22, 9),
    gsSPNTrianglesInit_5b(3,        // tri count
                          5, 9, 7,  // tri0
                          8, 10, 6, // tri1
                          5, 4, 11  // tri2
                          ),
    gsSPNTrianglesInit_5b(16,         // tri count
                          12, 13, 14, // tri0
                          15, 16, 17, // tri1
                          18, 19, 20  // tri2
                          ),
    gsSPNTriangles_5b(18, 20, 17, // tri0
                      21, 22, 23, // tri1
                      19, 18, 24, // tri2
                      17, 16, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 14, // tri0
                      19, 27, 12, // tri1
                      21, 28, 15, // tri2
                      28, 21, 29  // tri3
                      ),
    gsSPNTriangles_5b(30, 14, 13, // tri0
                      30, 25, 14, // tri1
                      21, 23, 29, // tri2
                      24, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(24, 27, 19, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_mnk_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mnk_1_v[258], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mnk_1_v[261], 9, 3),
    gsSPNTrianglesInit_5b(6,       // tri count
                          1, 3, 4, // tri0
                          1, 0, 5, // tri1
                          0, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 8,  // tri0
                      2, 9, 10, // tri1
                      2, 1, 11, // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail2_mnk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mnk_1_v[226], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mnk_1_v[229], 9, 3),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 3, 4, // tri0
                          0, 2, 5, // tri1
                          1, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 8,  // tri0
                      2, 9, 10, // tri1
                      2, 1, 11, // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPVertex(&mnk_1_v[238], 20, 0),
    gsSPNTrianglesInit_5b(31,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 5, 2  // tri2
                          ),
    gsSPNTriangles_5b(2, 5, 6,  // tri0
                      2, 6, 7,  // tri1
                      8, 9, 10, // tri2
                      8, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(11, 10, 12, // tri0
                      11, 12, 13, // tri1
                      13, 12, 14, // tri2
                      13, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(3, 16, 4,   // tri0
                      17, 13, 15, // tri1
                      17, 15, 18, // tri2
                      4, 16, 1    // tri3
                      ),
    gsSPNTriangles_5b(4, 1, 5, // tri0
                      5, 1, 0, // tri1
                      5, 0, 6, // tri2
                      6, 0, 19 // tri3
                      ),
    gsSPNTriangles_5b(6, 19, 10,  // tri0
                      10, 19, 17, // tri1
                      10, 17, 12, // tri2
                      12, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(12, 18, 14, // tri0
                      0, 8, 11,   // tri1
                      0, 11, 19,  // tri2
                      2, 8, 0     // tri3
                      ),
    gsSPNTriangles_5b(19, 11, 13, // tri0
                      19, 13, 17, // tri1
                      16, 3, 2,   // tri2
                      16, 2, 1    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot3_mnk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mnk_1_v[317], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x580, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mnk_1_v[320], 21, 3),
    gsSPNTrianglesInit_5b(9,       // tri count
                          2, 3, 4, // tri0
                          0, 5, 6, // tri1
                          0, 2, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 8, 9,   // tri0
                      2, 1, 10,  // tri1
                      2, 11, 12, // tri2
                      0, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(1, 15, 16, // tri0
                      1, 0, 17,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(4,          // tri count
                          18, 19, 20, // tri0
                          20, 21, 18, // tri1
                          20, 22, 21  // tri2
                          ),
    gsSPNTriangles_5b(18, 23, 19, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_mnk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mnk_1_v[341], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x580, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mnk_1_v[344], 14, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 3, 4, // tri0
                          1, 5, 6, // tri1
                          2, 0, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 1, 8,  // tri0
                      1, 9, 10, // tri1
                      1, 2, 11, // tri2
                      2, 12, 13 // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          14, 15, 16, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_mnk_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x580, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mnk_1_v[358], 6, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          3, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 1, // tri0
                      4, 5, 3, // tri1
                      1, 0, 5, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot3_mnk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mnk_1_v[270], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x580, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mnk_1_v[273], 21, 3),
    gsSPNTrianglesInit_5b(9,       // tri count
                          2, 3, 4, // tri0
                          0, 5, 6, // tri1
                          2, 0, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 2, 8,   // tri0
                      1, 9, 10,  // tri1
                      2, 11, 12, // tri2
                      0, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(1, 15, 16, // tri0
                      0, 1, 17,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(4,          // tri count
                          18, 19, 20, // tri0
                          20, 21, 18, // tri1
                          21, 22, 18  // tri2
                          ),
    gsSPNTriangles_5b(19, 23, 20, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_mnk_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mnk_1_v[294], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x580, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&mnk_1_v[297], 14, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          2, 3, 4, // tri0
                          1, 5, 6, // tri1
                          0, 2, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 8,  // tri0
                      1, 9, 10, // tri1
                      2, 1, 11, // tri2
                      2, 12, 13 // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          14, 15, 16, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_mnk_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x580, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mnk_1_v[311], 6, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 1, 0  // tri2
                          ),
    gsSPNTriangles_5b(2, 4, 5, // tri0
                      0, 5, 4, // tri1
                      5, 3, 2, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_mnk_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x5C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&mnk_1_v[364], 25, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          2, 1, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 0, 2, // tri0
                      6, 5, 1, // tri1
                      3, 7, 8, // tri2
                      8, 7, 9  // tri3
                      ),
    gsSPNTriangles_5b(7, 3, 4,    // tri0
                      10, 11, 12, // tri1
                      8, 9, 11,   // tri2
                      10, 12, 13  // tri3
                      ),
    gsSPNTriangles_5b(11, 9, 12,  // tri0
                      10, 13, 14, // tri1
                      1, 0, 15,   // tri2
                      1, 15, 16   // tri3
                      ),
    gsSPNTriangles_5b(15, 0, 17,  // tri0
                      16, 15, 10, // tri1
                      10, 15, 17, // tri2
                      8, 17, 3    // tri3
                      ),
    gsSPNTriangles_5b(0, 3, 17,   // tri0
                      10, 17, 11, // tri1
                      8, 11, 17,  // tri2
                      1, 16, 6    // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 10, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x340, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3,          // tri count
                          18, 19, 20, // tri0
                          21, 22, 23, // tri1
                          20, 24, 18  // tri2
                          ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_mnk_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_mnk_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-350,0 },
    /* joint 3 */ { Lfoot1_mnk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_mnk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { Lfoot3_mnk_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,350,0 },
    /* joint 7 */ { Rfoot1_mnk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_mnk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { Rfoot3_mnk_model, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 300,0,-950 },
    /* joint 11 */ { tail1_mnk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { tail2_mnk_model, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_mnk_model, 3, cKF_JOINT_FLAG_DISP_OPA, 325,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 750,-550,0 },
    /* joint 15 */ { Larm1_mnk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_mnk_model, 0, cKF_JOINT_FLAG_DISP_OPA, 550,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 750,550,0 },
    /* joint 18 */ { Rarm1_mnk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_mnk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 549,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 551,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 1225,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 600,0,1150 },
    /* joint 23 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_mnk_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1410,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_mnk_1 = { 26, 15, cKF_je_r_mnk_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_mnk_1_c(void) {
    pc_load_asset("assets/npc/mdl/mnk_1_v.bin", mnk_1_v, 0x1850, 0x7DA380, 0, 2);
}
#endif
