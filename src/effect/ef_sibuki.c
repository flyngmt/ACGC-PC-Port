#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_debug.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern Gfx ef_sibuki01_00_modelT[];

extern u8 ef_sibuki01_1_int_i4[];
extern u8 ef_sibuki01_2_int_i4[];
extern u8 ef_sibuki01_3_int_i4[];
extern u8 ef_sibuki01_4_int_i4[];

static void eSibuki_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSibuki_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSibuki_mv(eEC_Effect_c* effect, GAME* game);
static void eSibuki_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_sibuki = {
    // clang-format off
    &eSibuki_init,
    &eSibuki_ct,
    &eSibuki_mv,
    &eSibuki_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static u8* eSibuki_DrawSibukiPtn[] = {
    NULL, NULL, ef_sibuki01_1_int_i4, ef_sibuki01_2_int_i4, ef_sibuki01_3_int_i4, ef_sibuki01_4_int_i4,
};

static void eSibuki_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    pos.y -= 3.0f;
    pos.z += 5.0f;

    eEC_CLIP->make_effect_proc(eEC_EFFECT_SIBUKI, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eSibuki_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    if (effect->arg1 == 0) {
        effect->scale.x = 0.011f;
        effect->scale.y = 0.011f;
        effect->scale.z = 0.011f;
    } else {
        effect->scale.x = 0.011f;
        effect->scale.y = 0.011f;
        effect->scale.z = 0.011f;
    }

    effect->timer = 12;

    effect->effect_specific[0] = 12;
}

static void eSibuki_mv(eEC_Effect_c* effect, GAME* game) {
    return;
}

static void eSibuki_dw(eEC_Effect_c* effect, GAME* game) {
    GRAPH* graph;
    N64Mtx* mtx;
    f32 scale_mult;
    xyz_t pos = effect->position;
    xyz_t scale = effect->scale;
    f32 k = (12.0f - effect->lifetime) * 0.5f;
    s16 idx;
    if (k < 0.0f) k = 0.0f;
    if (k > 5.0f) k = 5.0f;
    idx = (s16)k;

    if (eSibuki_DrawSibukiPtn[idx] != NULL) {
        mtx = (N64Mtx*)GRAPH_ALLOC_TYPE(game->graph, N64Mtx, 1);

        graph = game->graph;
        OPEN_DISP(graph);

        _texture_z_light_fog_prim_xlu(graph);

        scale_mult = GETREG(MYKREG, 27) * 0.01f + 1.0f;
        suMtxMakeSRT(mtx, scale.x * scale_mult, scale.y * scale_mult, scale.z * scale_mult, DEG2SHORT_ANGLE2(-30.0f), 0,
                     0, pos.x, pos.y, pos.z);
        gSPMatrix(NEXT_POLY_XLU_DISP, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if (effect->arg0 == 0) {
            gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 200, 255, 255, 155);
            gDPSetEnvColor(NEXT_POLY_XLU_DISP, 0, 0, 0, 255);
        } else {
            gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 200, 255, 255, 235);
            gDPSetEnvColor(NEXT_POLY_XLU_DISP, 0, 0, 0, 255);
        }
        gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, eSibuki_DrawSibukiPtn[idx]);
        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_sibuki01_00_modelT);

        CLOSE_DISP(graph);
    }
}
