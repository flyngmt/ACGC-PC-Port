#include "ef_effect_control.h"
#include "m_common_data.h"
#include "m_malloc.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_debug.h"
#include "m_player_lib.h"

static void eKagu_Happa_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKagu_Happa_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKagu_Happa_mv(eEC_Effect_c* effect, GAME* game);
static void eKagu_Happa_dw(eEC_Effect_c* effect, GAME* game);

#define CALC_EASE(x) (1.0f - sqrtf(1.0f - (x)))
#define EFFECT_LIFETIME 36

eEC_PROFILE_c iam_ef_kagu_happa = {
    // clang-format off
    &eKagu_Happa_init,
    &eKagu_Happa_ct,
    &eKagu_Happa_mv,
    &eKagu_Happa_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eKagu_Happa_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_KAGU_HAPPA, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eKagu_Happa_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR_GAME(game);
    effect->offset = effect->position;
    effect->position = player->actor_class.world.position;
    effect->position.y += 20.f;
    effect->position.x += sin_s(player->actor_class.world.angle.y) * 10.f;
    effect->position.z += cos_s(player->actor_class.world.angle.y) * 10.f;
    effect->acceleration = effect->position;
    effect->scale = ZeroVec;
    effect->timer = EFFECT_LIFETIME;
    effect->effect_specific[0] = 0;
    effect->effect_specific[1] = 0; /* phase flag for one-shot effect spawn at end */
}

static void eKagu_Happa_mv(eEC_Effect_c* effect, GAME* game) {
    f32 dt = (f32)game->graph->dt_num_60fps_frames;
    /* Use lifetime so calc_adjust's "now" matches the original countdown semantics. */
    s16 timer_like = (s16)effect->lifetime;
    f32 t = (f32)EFFECT_LIFETIME - effect->lifetime;

    effect->position.x =
        eEC_CLIP->calc_adjust_proc(timer_like, 8, EFFECT_LIFETIME, effect->offset.x, effect->acceleration.x);
    effect->position.y =
        eEC_CLIP->calc_adjust_proc(timer_like, 8, EFFECT_LIFETIME, effect->offset.y, effect->acceleration.y);
    effect->position.z = eEC_CLIP->calc_adjust_proc(timer_like, 8, 0x1c, effect->offset.z, effect->acceleration.z);
    add_calc(&effect->scale.x, 0.01f, CALC_EASE(0.25f), 0.0015f, 5e-5f);
    effect->scale.y = effect->scale.z = effect->scale.x;
    if (timer_like > 10) {
        effect->position.y += ((timer_like - 14.f) - 4.f) * (-10.f / 98.f) * ((timer_like - 14.f) - 4.f) + 20.f;
        effect->effect_specific[0] += F32_TO_S16(0x924 * dt);
    } else if (effect->effect_specific[1] < 1 && t >= (f32)(EFFECT_LIFETIME - 2)) {
        /* Frame-exact one-shot at original timer==2 (i.e. t == LIFETIME-2). */
        effect->effect_specific[1] = 1;
        effect->position.y += 5.f;
        eEC_CLIP->effect_make_proc(1, effect->position, effect->prio, 0, game, effect->item_name, 0, 3);
    }
}

static void eKagu_Happa_dw(eEC_Effect_c* effect, GAME* game) {
    s16 s = sin_s(effect->effect_specific[0]) * 5120.f;
    GAME_PLAY* play = (GAME_PLAY*)game;
    OPEN_DISP(game->graph);
    _texture_z_light_fog_prim(game->graph);
    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    if (!effect->arg0) {
        Matrix_RotateZ(s, MTX_MULT);
        Matrix_mult(&play->billboard_matrix, MTX_MULT);
    }
    Matrix_scale(effect->scale.x * (GETREG(MYKREG, 0x1b) * 0.01f + 1.f),
                 effect->scale.y * (GETREG(MYKREG, 0x1b) * 0.01f + 1.f),
                 effect->scale.z * (GETREG(MYKREG, 0x1b) * 0.01f + 1.f), MTX_MULT);
    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_OPA_DISP, aMR_IconNo2Gfx1(effect->arg0));
    gSPDisplayList(NEXT_POLY_OPA_DISP, aMR_IconNo2Gfx2(effect->arg0));
    CLOSE_DISP(game->graph);
}
