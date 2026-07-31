#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx bev_1_v[0x1A50 / sizeof(Vtx)];
#else
static Vtx bev_1_v[] = {
#include "assets/npc/mdl/bev_1_v.inc"
};
#endif

static Gfx head_bev_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bev_1_v[0], 29, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          0, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(2, 5, 0, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x040, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(13,        // tri count
                          6, 7, 8,   // tri0
                          9, 10, 11, // tri1
                          12, 13, 14 // tri2
                          ),
    gsSPNTriangles_5b(12, 15, 13, // tri0
                      16, 17, 18, // tri1
                      16, 18, 19, // tri2
                      14, 20, 12  // tri3
                      ),
    gsSPNTriangles_5b(11, 21, 9,  // tri0
                      8, 22, 6,   // tri1
                      23, 24, 25, // tri2
                      26, 27, 23  // tri3
                      ),
    gsSPNTriangles_5b(23, 28, 26, // tri0
                      25, 28, 23, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x080, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&bev_1_v[29], 29, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 4, // tri1
                          0, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(3, 6, 7,   // tri0
                      0, 8, 9,   // tri1
                      10, 11, 3, // tri2
                      2, 11, 10  // tri3
                      ),
    gsSPNTriangles_5b(3, 0, 12, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x0C0, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(13,         // tri count
                          13, 14, 15, // tri0
                          16, 17, 14, // tri1
                          14, 18, 19  // tri2
                          ),
    gsSPNTriangles_5b(14, 19, 16, // tri0
                      14, 17, 20, // tri1
                      20, 15, 14, // tri2
                      21, 22, 16  // tri3
                      ),
    gsSPNTriangles_5b(16, 19, 23, // tri0
                      23, 24, 21, // tri1
                      13, 18, 14, // tri2
                      22, 17, 16  // tri3
                      ),
    gsSPNTriangles_5b(21, 16, 23, // tri0
                      15, 25, 13, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1,          // tri count
                          26, 27, 28, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPVertex(&bev_1_v[58], 30, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,   // tri0
                      11, 12, 13, // tri1
                      14, 15, 16, // tri2
                      8, 17, 18   // tri3
                      ),
    gsSPNTriangles_5b(12, 19, 17, // tri0
                      1, 4, 3,    // tri1
                      20, 21, 22, // tri2
                      23, 2, 1    // tri3
                      ),
    gsSPNTriangles_5b(19, 1, 0,   // tri0
                      24, 2, 21,  // tri1
                      20, 14, 24, // tri2
                      17, 10, 13  // tri3
                      ),
    gsSPNTriangles_5b(17, 0, 18, // tri0
                      18, 0, 24, // tri1
                      0, 17, 19, // tri2
                      2, 24, 0   // tri3
                      ),
    gsSPNTriangles_5b(23, 21, 2, // tri0
                      19, 12, 4, // tri1
                      25, 8, 16, // tri2
                      25, 16, 26 // tri3
                      ),
    gsSPNTriangles_5b(13, 12, 17, // tri0
                      24, 21, 20, // tri1
                      7, 22, 21,  // tri2
                      5, 4, 12    // tri3
                      ),
    gsSPNTriangles_5b(5, 6, 3, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(1,          // tri count
                          27, 28, 29, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPVertex(&bev_1_v[88], 19, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 7,   // tri0
                      8, 9, 6,   // tri1
                      10, 11, 1, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      17, 16, 18, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x200, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&bev_1_v[107], 18, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11, // tri0
                      5, 11, 12, // tri1
                      2, 13, 0,  // tri2
                      11, 14, 9  // tri3
                      ),
    gsSPNTriangles_5b(8, 15, 16, // tri0
                      5, 17, 3,  // tri1
                      15, 8, 2,  // tri2
                      2, 1, 15   // tri3
                      ),
    gsSPNTriangles_5b(12, 17, 5,  // tri0
                      8, 16, 6,   // tri1
                      10, 12, 11, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 60),
    gsSPVertex(&bev_1_v[125], 23, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          3, 1, 4, // tri1
                          5, 1, 3  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      9, 10, 11, // tri1
                      12, 7, 6,  // tri2
                      5, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(2, 1, 5,  // tri0
                      9, 15, 5, // tri1
                      5, 14, 7, // tri2
                      16, 3, 17 // tri3
                      ),
    gsSPNTriangles_5b(17, 9, 16,  // tri0
                      18, 19, 20, // tri1
                      7, 12, 5,   // tri2
                      5, 16, 9    // tri3
                      ),
    gsSPNTriangles_5b(2, 6, 0,   // tri0
                      4, 17, 3,  // tri1
                      17, 4, 10, // tri2
                      21, 14, 13 // tri3
                      ),
    gsSPNTriangles_5b(22, 8, 7,   // tri0
                      15, 13, 5,  // tri1
                      13, 15, 21, // tri2
                      3, 16, 5    // tri3
                      ),
    gsSPNTriangles_5b(8, 0, 6,   // tri0
                      10, 9, 17, // tri1
                      5, 12, 2,  // tri2
                      6, 2, 12   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&bev_1_v[148], 18, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,   // tri0
                      4, 10, 11, // tri1
                      4, 6, 12,  // tri2
                      4, 13, 10  // tri3
                      ),
    gsSPNTriangles_5b(5, 14, 3, // tri0
                      14, 5, 0, // tri1
                      6, 9, 8,  // tri2
                      11, 5, 4  // tri3
                      ),
    gsSPNTriangles_5b(5, 11, 1, // tri0
                      8, 12, 6, // tri1
                      15, 9, 6, // tri2
                      15, 16, 9 // tri3
                      ),
    gsSPNTriangles_5b(1, 0, 5,   // tri0
                      15, 6, 3,  // tri1
                      12, 13, 4, // tri2
                      0, 17, 14  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_bev_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bev_1_v[202], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*11, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bev_1_v[207], 16, 5),
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

static Gfx Rarm1_bev_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bev_1_v[223], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bev_1_v[227], 11, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          1, 4, 5, // tri0
                          2, 6, 7, // tri1
                          0, 2, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 0, 9,   // tri0
                      0, 11, 10, // tri1
                      1, 13, 12, // tri2
                      3, 1, 14   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_bev_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bev_1_v[166], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bev_1_v[171], 16, 5),
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

static Gfx Larm1_bev_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bev_1_v[187], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bev_1_v[191], 11, 4),
    gsSPNTrianglesInit_5b(7,       // tri count
                          3, 4, 5, // tri0
                          1, 6, 7, // tri1
                          1, 0, 8  // tri2
                          ),
    gsSPNTriangles_5b(0, 3, 9,   // tri0
                      0, 11, 10, // tri1
                      3, 13, 12, // tri2
                      3, 2, 14   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_bev_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bev_1_v[238], 11, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bev_1_v[249], 12, 11),
    gsSPNTrianglesInit_5b(8,         // tri count
                          3, 11, 12, // tri0
                          4, 13, 8,  // tri1
                          3, 8, 14   // tri2
                          ),
    gsSPNTriangles_5b(8, 15, 16, // tri0
                      7, 18, 17, // tri1
                      7, 6, 19,  // tri2
                      4, 7, 20   // tri3
                      ),
    gsSPNTriangles_5b(6, 21, 22, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x3C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&bev_1_v[261], 18, 11),
    gsSPNTrianglesInit_5b(9,         // tri count
                          1, 0, 11,  // tri0
                          9, 10, 12, // tri1
                          5, 13, 14  // tri2
                          ),
    gsSPNTriangles_5b(5, 9, 15,  // tri0
                      10, 1, 16, // tri1
                      2, 17, 18, // tri2
                      0, 2, 19   // tri3
                      ),
    gsSPNTriangles_5b(10, 20, 21, // tri0
                      1, 22, 23,  // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x2C0, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,          // tri count
                          24, 25, 26, // tri0
                          27, 28, 24, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPVertex(&bev_1_v[279], 18, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          2, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(2, 7, 0, // tri0
                      5, 1, 0, // tri1
                      0, 3, 5, // tri2
                      1, 8, 2  // tri3
                      ),
    gsSPNTriangles_5b(1, 5, 8, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x3C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8,         // tri count
                          9, 10, 11, // tri0
                          11, 12, 9, // tri1
                          13, 10, 9  // tri2
                          ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      11, 14, 16, // tri1
                      11, 17, 14, // tri2
                      10, 17, 11  // tri3
                      ),
    gsSPNTriangles_5b(16, 12, 11, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail1_bev_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bev_1_v[317], 3, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bev_1_v[320], 11, 3),
    gsSPNTrianglesInit_5b(7,       // tri count
                          1, 3, 4, // tri0
                          1, 0, 5, // tri1
                          2, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(0, 8, 9,   // tri0
                      0, 2, 10,  // tri1
                      1, 11, 12, // tri2
                      2, 1, 13   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx tail2_bev_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*5, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bev_1_v[297], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bev_1_v[301], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          2, 3, 4, // tri0
                          3, 0, 5, // tri1
                          1, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 8, 9,  // tri0
                      2, 10, 1, // tri1
                      1, 11, 0, // tri2
                      3, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(3, 14, 15, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          16, 17, 18, // tri0
                          18, 19, 16, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_bev_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bev_1_v[362], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bev_1_v[367], 17, 5),
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

static Gfx Rfoot1_bev_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bev_1_v[384], 9, 0),
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

static Gfx Lfoot2_bev_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bev_1_v[331], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&bev_1_v[336], 17, 5),
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

static Gfx Lfoot1_bev_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bev_1_v[353], 9, 0),
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

static Gfx base_bev_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x480, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&bev_1_v[393], 28, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 3, 5  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 0,   // tri0
                      9, 10, 11, // tri1
                      9, 12, 6,  // tri2
                      13, 14, 6  // tri3
                      ),
    gsSPNTriangles_5b(15, 13, 12, // tri0
                      9, 16, 12,  // tri1
                      15, 12, 16, // tri2
                      6, 12, 13   // tri3
                      ),
    gsSPNTriangles_5b(6, 10, 9,   // tri0
                      3, 17, 4,   // tri1
                      13, 18, 19, // tri2
                      14, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(15, 18, 13, // tri0
                      14, 13, 19, // tri1
                      21, 16, 22, // tri2
                      1, 23, 2    // tri3
                      ),
    gsSPNTriangles_5b(15, 21, 18, // tri0
                      24, 25, 26, // tri1
                      22, 9, 11,  // tri2
                      11, 10, 27  // tri3
                      ),
    gsSPNTriangles_5b(16, 9, 22, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_bev_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_bev_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-370,0 },
    /* joint 3 */ { Lfoot1_bev_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_bev_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,370,0 },
    /* joint 7 */ { Rfoot1_bev_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_bev_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,-1100 },
    /* joint 11 */ { tail1_bev_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { tail2_bev_model, 0, cKF_JOINT_FLAG_DISP_OPA, 1100,0,0 },
    /* joint 13 */ { chest_bev_model, 3, cKF_JOINT_FLAG_DISP_OPA, 325,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 550,-800,0 },
    /* joint 15 */ { Larm1_bev_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_bev_model, 0, cKF_JOINT_FLAG_DISP_OPA, 401,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 550,800,0 },
    /* joint 18 */ { Rarm1_bev_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_bev_model, 1, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 20 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 399,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 776,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 650,0,300 },
    /* joint 23 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_bev_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 1499,0,0 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_bev_1 = { 26, 13, cKF_je_r_bev_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_bev_1_c(void) {
    pc_load_asset("assets/npc/mdl/bev_1_v.bin", bev_1_v, 0x1A50, 0x3701E0, 0, 2);
}
#endif
