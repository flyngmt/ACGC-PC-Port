#include "types.h"
#include "c_keyframe.h"
#include "libforest/gbi_extensions.h"

// TODO: assetrip textures & vertices then link

static u8 obj_s_boat_t10_tex_txt[128];
static u8 obj_s_boat_t11_tex_txt[128];
static u8 obj_s_boat_t9_tex_txt[192];
static u8 obj_s_boat_t6_tex_txt[256];
static u8 obj_s_boat_t7_tex_txt[128];
static u8 obj_s_boat_t1_tex_txt[1024];
static u8 obj_s_boat_t3_tex_txt[1024];
static u8 obj_s_boat_t2_tex_txt[128];
static u8 obj_s_boat_t5_tex_txt[128];
static u8 obj_s_boat_t8_tex_txt[128];
static u8 obj_s_boat_t4_tex_txt[128];

static u8 obj_s_boat_water1_pic_i4[512];
static u8 obj_s_boat_water2_pic_i4[256];

static Vtx obj_e_boat_v[156];

static Gfx obj_e_boat_boat1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(obj_s_boat_t6_tex_txt, G_IM_FMT_CI, 16, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&obj_e_boat_v[30], 30, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(obj_s_boat_t7_tex_txt, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(2,         // tri count
                          8, 9, 10,  // tri0
                          8, 10, 11, // tri1
                          0, 0, 0    // tri2
                          ),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,          // tri count
                          12, 13, 14, // tri0
                          12, 14, 15, // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(obj_s_boat_t1_tex_txt, G_IM_FMT_CI, 32, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(5,          // tri count
                          16, 17, 18, // tri0
                          16, 18, 19, // tri1
                          16, 20, 21  // tri2
                          ),
    gsSPNTriangles_5b(16, 21, 17, // tri0
                      20, 22, 21, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(obj_s_boat_t3_tex_txt, G_IM_FMT_CI, 32, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPNTrianglesInit_5b(5,          // tri count
                          23, 24, 25, // tri0
                          23, 25, 26, // tri1
                          23, 27, 24  // tri2
                          ),
    gsSPNTriangles_5b(26, 25, 28, // tri0
                      26, 28, 29, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(obj_s_boat_t2_tex_txt, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&obj_e_boat_v[60], 31, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7,   // tri0
                      8, 9, 10,  // tri1
                      8, 10, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 15, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(obj_s_boat_t5_tex_txt, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,          // tri count
                          16, 17, 18, // tri0
                          16, 18, 19, // tri1
                          20, 21, 22  // tri2
                          ),
    gsSPNTriangles_5b(20, 22, 16, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(obj_s_boat_t8_tex_txt, G_IM_FMT_CI, 16, 16, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,          // tri count
                          23, 24, 25, // tri0
                          23, 25, 26, // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(obj_s_boat_t4_tex_txt, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,          // tri count
                          27, 28, 29, // tri0
                          27, 29, 30, // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(obj_s_boat_t3_tex_txt, G_IM_FMT_CI, 32, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&obj_e_boat_v[91], 7, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 0, // tri0
                      4, 6, 3, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx obj_e_boat_water1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED,
                       COMBINED, 0, TEXEL0, 0),
    gsDPSetPrimColor(0, 255, 190, 210, 255, 230),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(obj_s_boat_water2_pic_i4, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPLoadTextureBlock_4b_Dolphin(obj_s_boat_water1_pic_i4, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 14),
    gsSPDisplayList(anime_2_model),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&obj_e_boat_v[142], 14, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          2, 1, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(2, 7, 8,    // tri0
                      2, 9, 0,    // tri1
                      10, 11, 12, // tri2
                      8, 9, 2     // tri3
                      ),
    gsSPNTriangles_5b(3, 7, 2,   // tri0
                      8, 13, 10, // tri1
                      6, 13, 8,  // tri2
                      8, 12, 9   // tri3
                      ),
    gsSPNTriangles_5b(10, 12, 8, // tri0
                      8, 4, 6,   // tri1
                      7, 4, 8,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx obj_e_boat_water2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED,
                       COMBINED, 0, TEXEL0, 0),
    gsDPSetPrimColor(0, 255, 190, 210, 255, 230),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(obj_s_boat_water2_pic_i4, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPLoadTextureBlock_4b_Dolphin(obj_s_boat_water1_pic_i4, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 14),
    gsSPDisplayList(anime_2_model),
    gsSPMatrix(anime_6_model + sizeof(N64Mtx) * 2, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&obj_e_boat_v[125], 5, 0),
    gsSPMatrix(anime_6_model + sizeof(N64Mtx) * 3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(&obj_e_boat_v[130], 12, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          1, 5, 6, // tri0
                          3, 7, 8, // tri1
                          0, 4, 9  // tri2
                          ),
    gsSPNTriangles_5b(4, 10, 11, // tri0
                      0, 12, 13, // tri1
                      4, 2, 14,  // tri2
                      3, 1, 15   // tri3
                      ),
    gsSPNTriangles_5b(2, 3, 16, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx obj_e_boat_water3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED,
                       COMBINED, 0, TEXEL0, 0),
    gsDPSetPrimColor(0, 255, 190, 210, 255, 230),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(obj_s_boat_water2_pic_i4, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPLoadTextureBlock_4b_Dolphin(obj_s_boat_water1_pic_i4, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 14),
    gsSPDisplayList(anime_2_model),
    gsSPMatrix(anime_6_model + sizeof(N64Mtx) * 3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&obj_e_boat_v[98], 5, 0),
    gsSPMatrix(anime_6_model + sizeof(N64Mtx) * 4, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(&obj_e_boat_v[103], 22, 5),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 5, // tri0
                          0, 6, 7, // tri1
                          1, 2, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 3, 9,   // tri0
                      3, 4, 10,  // tri1
                      4, 11, 12, // tri2
                      3, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(1, 15, 16, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPNTrianglesInit_5b(8,          // tri count
                          17, 18, 19, // tri0
                          20, 21, 22, // tri1
                          19, 23, 24  // tri2
                          ),
    gsSPNTriangles_5b(20, 22, 25, // tri0
                      23, 26, 24, // tri1
                      25, 26, 23, // tri2
                      25, 23, 20  // tri3
                      ),
    gsSPNTriangles_5b(24, 17, 19, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

static Gfx obj_e_boat_oar1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTextureBlock_4b_Dolphin(obj_s_boat_t10_tex_txt, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&obj_e_boat_v[0], 30, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(obj_s_boat_t11_tex_txt, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(6,         // tri count
                          6, 7, 8,   // tri0
                          6, 8, 9,   // tri1
                          10, 11, 12 // tri2
                          ),
    gsSPNTriangles_5b(10, 12, 13, // tri0
                      14, 15, 16, // tri1
                      14, 16, 17, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(obj_s_boat_t9_tex_txt, G_IM_FMT_CI, 48, 8, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(4,          // tri count
                          18, 19, 20, // tri0
                          21, 18, 20, // tri1
                          22, 23, 24  // tri2
                          ),
    gsSPNTriangles_5b(25, 22, 24, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(obj_s_boat_t9_tex_txt, G_IM_FMT_CI, 48, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(2,          // tri count
                          26, 27, 28, // tri0
                          26, 28, 29, // tri1
                          0, 0, 0     // tri2
                          ),
    gsSPEndDisplayList(),
};

extern cKF_Joint_R_c cKF_je_r_obj_e_boat_tbl[] = {
    /* joint 0 */ obj_e_boat_boat1_model,
    2,
    cKF_JOINT_FLAG_DISP_OPA,
    0,
    0,
    0,
    /* joint 1 */ NULL,
    1,
    cKF_JOINT_FLAG_DISP_OPA,
    300,
    2200,
    -4500,
    /* joint 2 */ obj_e_boat_oar1_model,
    0,
    cKF_JOINT_FLAG_DISP_OPA,
    0,
    0,
    0,
    /* joint 3 */ NULL,
    1,
    cKF_JOINT_FLAG_DISP_OPA,
    0,
    0,
    4000,
    /* joint 4 */ obj_e_boat_water1_model,
    1,
    cKF_JOINT_FLAG_DISP_XLU,
    0,
    0,
    0,
    /* joint 5 */ obj_e_boat_water2_model,
    1,
    cKF_JOINT_FLAG_DISP_XLU,
    8400,
    0,
    0,
    /* joint 6 */ obj_e_boat_water3_model,
    0,
    cKF_JOINT_FLAG_DISP_XLU,
    4600,
    0,
    0,
};

extern cKF_Skeleton_R_c cKF_bs_r_obj_e_boat = { 7, // 7 total joints
                                                5, // 5 displayed joints (rendered joints)
                                                cKF_je_r_obj_e_boat_tbl };

static u8 cKF_ckcb_r_obj_e_boat_tbl[] = {
    /* joint 0 */ cKF_ANIMITION_BIT_NONE,
    /* joint 1 */ cKF_ANIMITION_BIT_NONE,
    /* joint 2 */ cKF_ANIMATION_BIT_ROT_X | cKF_ANIMATION_BIT_ROT_Y | cKF_ANIMATION_BIT_ROT_Z,
    /* joint 3 */ cKF_ANIMITION_BIT_NONE,
    /* joint 4 */ cKF_ANIMITION_BIT_NONE,
    /* joint 5 */ cKF_ANIMITION_BIT_NONE,
    /* joint 6 */ cKF_ANIMITION_BIT_NONE
};

static s16 cKF_kn_obj_e_boat_tbl[] = { 8, 5, 9 };

// Fixed position table (used when the joint has no translation)
static s16 cKF_c_obj_e_boat_tbl[] = {
    /* joint 0 */ 0,    0,   0,
    /* joint 1 */ 0,    0,   0,
    /* joint 2 */ 0,    900, 900,
    /* joint 3 */ -450, 900, 450,
    /* joint 4 */ 0,    0,   0,
    /* joint 5 */ 0,    0,   0,
    /* joint 6 */ 0,    0,   0
};

/* frame value slope */
static s16 cKF_ds_obj_e_boat_tbl[] = {
    /* joint 2 X rotational frames */
    1, 904, 648, 13, 1075, 212, 23, 1099, -60, 40, 920, -572, 45, 828, -481, 62, 701, 20, 80, 877, 651, 81, 900, 675,

    /* joint 2 Y rotational frames */
    1, 449, 134, 27, 495, -50, 43, 442, -124, 67, 405, 49, 81, 449, 132,

    /* joint 2 Z rotational frames */
    1, -180, 143, 5, -143, 443, 20, 141, 303, 26, 177, 119, 40, 183, -81, 44, 156, -370, 60, -141, -305, 65, -173, -137,
    81, -180, 83
};

extern cKF_Animation_R_c cKF_ba_r_obj_e_boat = {
    cKF_ckcb_r_obj_e_boat_tbl, cKF_ds_obj_e_boat_tbl, cKF_kn_obj_e_boat_tbl, cKF_c_obj_e_boat_tbl, -1, 81
};
