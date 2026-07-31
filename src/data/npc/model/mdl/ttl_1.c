#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

#ifdef TARGET_PC
static Vtx ttl_1_v[0x1450 / sizeof(Vtx)];
#else
static Vtx ttl_1_v[] = {
#include "assets/npc/mdl/ttl_1_v.inc"
};
#endif

static Gfx head_ttl_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x140, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&ttl_1_v[26], 23, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 2, // tri1
                          2, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 6, 2, // tri0
                      2, 6, 7, // tri1
                      8, 3, 2, // tri2
                      2, 7, 8  // tri3
                      ),
    gsSPNTriangles_5b(2, 5, 0, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x1C0, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(14,         // tri count
                          9, 10, 11,  // tri0
                          11, 10, 12, // tri1
                          13, 12, 14  // tri2
                          ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      15, 18, 19, // tri1
                      19, 20, 15, // tri2
                      14, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(22, 13, 14, // tri0
                      12, 13, 11, // tri1
                      11, 20, 9,  // tri2
                      17, 16, 22  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 15, // tri0
                      22, 21, 17, // tri1
                      19, 9, 20,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x240, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetTileSize(0, 0, 0, 60, 124),
    gsSPVertex(&ttl_1_v[49], 16, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 6, // tri0
                      1, 0, 11, // tri1
                      11, 7, 1, // tri2
                      12, 5, 4  // tri3
                      ),
    gsSPNTriangles_5b(12, 4, 10, // tri0
                      10, 9, 12, // tri1
                      11, 8, 7,  // tri2
                      2, 13, 0   // tri3
                      ),
    gsSPNTriangles_5b(5, 14, 3, // tri0
                      6, 15, 9, // tri1
                      8, 15, 6, // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&ttl_1_v[65], 17, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,   // tri0
                      8, 10, 11, // tri1
                      8, 11, 9,  // tri2
                      8, 7, 12   // tri3
                      ),
    gsSPNTriangles_5b(4, 13, 3, // tri0
                      4, 3, 5,  // tri1
                      5, 2, 14, // tri2
                      5, 3, 2   // tri3
                      ),
    gsSPNTriangles_5b(0, 10, 1,  // tri0
                      1, 10, 8,  // tri1
                      1, 12, 14, // tri2
                      1, 14, 2   // tri3
                      ),
    gsSPNTriangles_5b(14, 6, 5, // tri0
                      12, 1, 8, // tri1
                      6, 15, 4, // tri2
                      9, 16, 7  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x280, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&ttl_1_v[82], 27, 0),
    gsSPNTrianglesInit_5b(30,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 8,   // tri0
                      9, 1, 0,   // tri1
                      4, 10, 11, // tri2
                      12, 13, 9  // tri3
                      ),
    gsSPNTriangles_5b(6, 14, 15, // tri0
                      16, 17, 3, // tri1
                      14, 6, 8,  // tri2
                      2, 1, 7    // tri3
                      ),
    gsSPNTriangles_5b(18, 12, 19, // tri0
                      18, 19, 20, // tri1
                      18, 15, 14, // tri2
                      2, 21, 22   // tri3
                      ),
    gsSPNTriangles_5b(17, 23, 3, // tri0
                      4, 23, 10, // tri1
                      5, 8, 6,   // tri2
                      11, 21, 5  // tri3
                      ),
    gsSPNTriangles_5b(6, 15, 16,  // tri0
                      24, 25, 26, // tri1
                      21, 2, 5,   // tri2
                      22, 0, 2    // tri3
                      ),
    gsSPNTriangles_5b(14, 12, 18, // tri0
                      8, 13, 14,  // tri1
                      3, 23, 4,   // tri2
                      14, 13, 12  // tri3
                      ),
    gsSPNTriangles_5b(7, 5, 2,  // tri0
                      5, 4, 11, // tri1
                      16, 3, 6, // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x300, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&ttl_1_v[109], 24, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          2, 4, 0  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 1, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x380, G_IM_FMT_CI, 32, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(14,        // tri count
                          6, 7, 8,   // tri0
                          9, 10, 11, // tri1
                          12, 13, 14 // tri2
                          ),
    gsSPNTriangles_5b(12, 15, 13, // tri0
                      9, 16, 8,   // tri1
                      8, 16, 6,   // tri2
                      14, 17, 6   // tri3
                      ),
    gsSPNTriangles_5b(11, 18, 13, // tri0
                      17, 7, 6,   // tri1
                      11, 19, 9,  // tri2
                      11, 10, 18  // tri3
                      ),
    gsSPNTriangles_5b(9, 19, 16,  // tri0
                      6, 12, 14,  // tri1
                      13, 15, 11, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,          // tri count
                          20, 21, 22, // tri0
                          20, 23, 21, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx mouth_ttl_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*13, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&ttl_1_v[0], 5, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*12, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x000, G_IM_FMT_CI, 32, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&ttl_1_v[5], 21, 5),
    gsSPNTrianglesInit_5b(7,       // tri count
                          1, 2, 5, // tri0
                          3, 0, 6, // tri1
                          1, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(4, 1, 9,   // tri0
                      4, 10, 11, // tri1
                      0, 13, 12, // tri2
                      0, 4, 14   // tri3
                      ),
    gsSPNTrianglesInit_5b(1,          // tri count
                          15, 16, 17, // tri0
                          0, 0, 0,    // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x100, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10,         // tri count
                          18, 19, 20, // tri0
                          20, 19, 21, // tri1
                          20, 22, 18  // tri2
                          ),
    gsSPNTriangles_5b(21, 23, 20, // tri0
                      22, 24, 25, // tri1
                      21, 19, 25, // tri2
                      25, 24, 23  // tri3
                      ),
    gsSPNTriangles_5b(25, 19, 18, // tri0
                      18, 22, 25, // tri1
                      25, 23, 21, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx hand_ttl_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x440, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&ttl_1_v[160], 13, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPNTrianglesInit_5b(5,       // tri count
                          4, 5, 6, // tri0
                          7, 8, 9, // tri1
                          7, 9, 10 // tri2
                          ),
    gsSPNTriangles_5b(8, 11, 12, // tri0
                      8, 12, 9,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rarm2_ttl_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*9, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&ttl_1_v[173], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*10, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&ttl_1_v[177], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          1, 2, 4, // tri0
                          2, 0, 5, // tri1
                          0, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(3, 1, 8,   // tri0
                      0, 3, 9,   // tri1
                      0, 10, 11, // tri2
                      1, 12, 13  // tri3
                      ),
    gsSPNTriangles_5b(1, 14, 15, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          16, 17, 18, // tri0
                          19, 18, 17, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rarm1_ttl_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&ttl_1_v[193], 7, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 2, 4, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 2, 5, // tri0
                      5, 1, 6, // tri1
                      1, 0, 6, // tri2
                      2, 3, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Larm2_ttl_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*7, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&ttl_1_v[133], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&ttl_1_v[137], 16, 4),
    gsSPNTrianglesInit_5b(8,       // tri count
                          2, 1, 4, // tri0
                          0, 2, 5, // tri1
                          0, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 3, 8,   // tri0
                      3, 0, 9,   // tri1
                      0, 10, 11, // tri2
                      1, 12, 13  // tri3
                      ),
    gsSPNTriangles_5b(1, 14, 15, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(2,          // tri count
                          16, 17, 18, // tri0
                          17, 16, 19, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Larm1_ttl_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&ttl_1_v[153], 7, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 3  // tri2
                          ),
    gsSPNTriangles_5b(6, 0, 3, // tri0
                      5, 1, 6, // tri1
                      5, 2, 1, // tri2
                      2, 4, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx chest_ttl_model[] = {
    gsSPMatrix(anime_6_model, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&ttl_1_v[200], 8, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*6, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&ttl_1_v[208], 22, 8),
    gsSPNTrianglesInit_5b(7,        // tri count
                          7, 8, 9,  // tri0
                          7, 10, 5, // tri1
                          7, 11, 12 // tri2
                          ),
    gsSPNTriangles_5b(5, 13, 14, // tri0
                      5, 15, 3,  // tri1
                      3, 16, 17, // tri2
                      3, 18, 19  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(7,         // tri count
                          2, 20, 21, // tri0
                          2, 0, 22,  // tri1
                          1, 23, 24  // tri2
                          ),
    gsSPNTriangles_5b(6, 2, 25,  // tri0
                      1, 4, 26,  // tri1
                      0, 27, 28, // tri2
                      1, 29, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x540, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsSPVertex(&ttl_1_v[230], 21, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          2, 1, 3, // tri1
                          3, 1, 4  // tri2
                          ),
    gsSPNTriangles_5b(4, 1, 5, // tri0
                      5, 1, 6, // tri1
                      7, 8, 9, // tri2
                      6, 1, 0  // tri3
                      ),
    gsSPNTriangles_5b(3, 10, 11, // tri0
                      4, 8, 10,  // tri1
                      5, 9, 8,   // tri2
                      6, 12, 9   // tri3
                      ),
    gsSPNTriangles_5b(0, 13, 12,  // tri0
                      2, 11, 13,  // tri1
                      14, 11, 10, // tri2
                      14, 10, 15  // tri3
                      ),
    gsSPNTriangles_5b(11, 2, 3, // tri0
                      10, 3, 4, // tri1
                      8, 4, 5,  // tri2
                      9, 5, 6   // tri3
                      ),
    gsSPNTriangles_5b(12, 6, 0,  // tri0
                      13, 0, 2,  // tri1
                      15, 10, 8, // tri2
                      15, 8, 7   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsSPNTrianglesInit_5b(3,          // tri count
                          16, 17, 18, // tri0
                          19, 16, 18, // tri1
                          18, 17, 20  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx tail1_ttl_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&ttl_1_v[251], 5, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 0, 2  // tri2
                          ),
    gsSPNTriangles_5b(3, 4, 2, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot2_ttl_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&ttl_1_v[286], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&ttl_1_v[290], 19, 4),
    gsSPNTrianglesInit_5b(9,       // tri count
                          2, 4, 5, // tri0
                          2, 6, 7, // tri1
                          0, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(1, 10, 11, // tri0
                      2, 3, 12,  // tri1
                      1, 2, 13,  // tri2
                      0, 1, 14   // tri3
                      ),
    gsSPNTriangles_5b(3, 0, 15,  // tri0
                      0, 16, 17, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          18, 19, 20, // tri0
                          21, 20, 19, // tri1
                          21, 19, 22  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Rfoot1_ttl_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&ttl_1_v[309], 7, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          1, 5, 2  // tri2
                          ),
    gsSPNTriangles_5b(6, 4, 3, // tri0
                      6, 3, 0, // tri1
                      0, 2, 6, // tri2
                      4, 5, 1  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot2_ttl_model[] = {
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&ttl_1_v[256], 4, 0),
    gsSPMatrix(anime_6_model+sizeof(N64Mtx)*2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&ttl_1_v[260], 19, 4),
    gsSPNTrianglesInit_5b(9,       // tri count
                          2, 4, 5, // tri0
                          2, 6, 7, // tri1
                          0, 8, 9  // tri2
                          ),
    gsSPNTriangles_5b(1, 10, 11, // tri0
                      3, 2, 12,  // tri1
                      2, 1, 13,  // tri2
                      1, 0, 14   // tri3
                      ),
    gsSPNTriangles_5b(0, 3, 15,  // tri0
                      0, 16, 17, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(3,          // tri count
                          18, 19, 20, // tri0
                          21, 19, 18, // tri1
                          21, 18, 22  // tri2
                          ),
    gsSPEndDisplayList(),
};

static Gfx Lfoot1_ttl_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x400, G_IM_FMT_CI, 16, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&ttl_1_v[279], 7, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          0, 5, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 6, // tri0
                      2, 4, 6, // tri1
                      6, 0, 2, // tri2
                      1, 5, 3  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx base_ttl_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_4_txt + 0x640, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&ttl_1_v[316], 9, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 3, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      5, 3, 8, // tri1
                      4, 8, 3, // tri2
                      8, 6, 5  // tri3
                      ),
    gsSPNTriangles_5b(3, 5, 1, // tri0
                      7, 1, 5, // tri1
                      1, 7, 2, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

// clang-format off
static cKF_Joint_R_c cKF_je_r_ttl_1_tbl[] = {
    /* joint 0 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,1000,0 },
    /* joint 1 */ { base_ttl_model, 4, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 2 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,-500,-300 },
    /* joint 3 */ { Lfoot1_ttl_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 4 */ { Lfoot2_ttl_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 5 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 6 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,500,-300 },
    /* joint 7 */ { Rfoot1_ttl_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 8 */ { Rfoot2_ttl_model, 1, cKF_JOINT_FLAG_DISP_OPA, 500,0,0 },
    /* joint 9 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 400,0,0 },
    /* joint 10 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, -400,0,-700 },
    /* joint 11 */ { tail1_ttl_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 12 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 650,0,0 },
    /* joint 13 */ { chest_ttl_model, 3, cKF_JOINT_FLAG_DISP_OPA, 403,0,0 },
    /* joint 14 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,-700,200 },
    /* joint 15 */ { Larm1_ttl_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 16 */ { Larm2_ttl_model, 0, cKF_JOINT_FLAG_DISP_OPA, 451,0,0 },
    /* joint 17 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 500,700,200 },
    /* joint 18 */ { Rarm1_ttl_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 19 */ { Rarm2_ttl_model, 1, cKF_JOINT_FLAG_DISP_OPA, 452,0,0 },
    /* joint 20 */ { hand_ttl_model, 0, cKF_JOINT_FLAG_DISP_OPA, 449,0,0 },
    /* joint 21 */ { NULL, 2, cKF_JOINT_FLAG_DISP_OPA, 1000,0,0 },
    /* joint 22 */ { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,2000 },
    /* joint 23 */ { mouth_ttl_model, 0, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 24 */ { head_ttl_model, 1, cKF_JOINT_FLAG_DISP_OPA, 0,0,0 },
    /* joint 25 */ { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, 997,0,1100 },
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_ttl_1 = { 26, 14, cKF_je_r_ttl_1_tbl };

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_data_npc_model_mdl_ttl_1_c(void) {
    pc_load_asset("assets/npc/mdl/ttl_1_v.bin", ttl_1_v, 0x1450, 0x7C8E00, 0, 2);
}
#endif
