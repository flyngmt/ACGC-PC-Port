#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "main.h"

static void eSuisou_Awa_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSuisou_Awa_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSuisou_Awa_mv(eEC_Effect_c* effect, GAME* game);
static void eSuisou_Awa_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_suisou_awa = {
    // clang-format off
    &eSuisou_Awa_init,
    &eSuisou_Awa_ct,
    &eSuisou_Awa_mv,
    &eSuisou_Awa_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eSuisou_Awa_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_SUISOU_AWA, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eSuisou_Awa_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->scale = ZeroVec;
    effect->velocity = ZeroVec;
    effect->velocity.x = RANDOM2_F(0.8f);
    effect->velocity.z = RANDOM2_F(0.8f);
    effect->acceleration = ZeroVec;
    effect->acceleration.y = 0.075f;
    effect->effect_specific[0] = qrand();
    effect->effect_specific[1] = DEG2SHORT_ANGLE2(25.0f);
    effect->effect_specific[2] = qrand();
    effect->effect_specific[3] = DEG2SHORT_ANGLE2(12.5f);
    effect->offset.x = (RANDOM_F(0.75f) + 0.25f) * 0.005f;

    if (effect->offset.x > 0.0025f && effect->arg0 != 4) {
        effect->effect_specific[4] = 1;
    } else {
        effect->effect_specific[4] = 0;
    }

    effect->timer = 80;
}

static xyz_t suisou_pos[5] = {
    {220.0f, 40.0f, 220.0f},
    {420.0f, 40.0f, 220.0f},
    {220.0f, 40.0f, 460.0f},
    {420.0f, 40.0f, 460.0f},
    {320.0f, 40.0f, 20.0f},
};

static void suisou_awa_BGCheck(eEC_Effect_c* effect) {
    xyz_t pos = suisou_pos[effect->arg0];

    if (effect->arg0 == 2) {
        if (effect->position.x > pos.x + 50.0f) {
            effect->position.x = pos.x + 50.0f;
        } else if (effect->position.x < pos.x - 50.0f) {
            effect->position.x = pos.x - 50.0f;
        }

        if (effect->position.z > pos.z + 50.0f) {
            effect->position.z = pos.z + 50.0f;
        } else if (effect->position.z < pos.z - 50.0f) {
            effect->position.z = pos.z - 50.0f;
        }
    }
}

static void eSuisou_Awa_mv(eEC_Effect_c* effect, GAME* game) {
    f32 dt = (f32)game->graph->dt_num_60fps_frames;

    if (effect->position.y >= 115.0f) {
        if (effect->effect_specific[4] == 1) {
            effect->effect_specific[4] = 0;
            eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, effect->position, effect->prio, 0, game, effect->item_name, 6, 0);
        }

        add_calc(&effect->velocity.y, 0.0f, 1.0f - sqrtf(0.5f), 0.5f, 0.05f);
        add_calc(&effect->scale.x, 0.0f, 1.0f - sqrtf(0.5f), 0.001f, 0.00005f);
        effect->scale.y = effect->scale.z = effect->scale.x;
        /* Legacy did extra timer-- here for 2x death drain at surface; mirror via lifetime. */
        effect->lifetime -= dt;
    } else {
        effect->scale.x = eEC_CLIP->calc_adjust_proc((s16)effect->lifetime, 76, 80, effect->offset.x, 0.0f);
        effect->scale.y = effect->scale.z = effect->scale.x;
        effect->velocity.y *= powf(sqrtf(0.84f), dt);
        effect->effect_specific[0] += F32_TO_S16(effect->effect_specific[1] * dt);
        effect->effect_specific[2] += F32_TO_S16(effect->effect_specific[3] * dt);
        if (effect->arg0 == 2) {
            /* Drive sine via lifetime instead of game_frame so high-fps doesn't aliase. */
            f32 t = 80.0f - effect->lifetime;
            effect->acceleration.x = sin_s((s16)(t * DEG2SHORT_ANGLE2(90.0f))) * 0.05f - 0.04f;
        }

        add_calc0(&effect->velocity.x, 0.1f, 0.1f);
        add_calc0(&effect->velocity.z, 0.1f, 0.1f);
        effect->velocity.x += effect->acceleration.x * dt;
        effect->velocity.y += effect->acceleration.y * dt;
        effect->velocity.z += effect->acceleration.z * dt;
        effect->position.x += effect->velocity.x * dt;
        effect->position.y += effect->velocity.y * dt;
        effect->position.z += effect->velocity.z * dt;
        suisou_awa_BGCheck(effect);
        if (effect->position.y >= 115.0f) {
            effect->position.y = 115.0f;
        }
    }
}

extern Gfx ef_museum5_awa1_model[];

static void eSuisou_Awa_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    xyz_t pos;
    xyz_t scale;
    xyz_t screen_pos;
    s16 pos_angle = effect->effect_specific[0];
    s16 scale_angle = effect->effect_specific[2];

    Game_play_Projection_Trans(play, &effect->position, &screen_pos);
    if (0.0f < screen_pos.x && screen_pos.x < SCREEN_WIDTH && 0.0f < screen_pos.y && screen_pos.y < SCREEN_HEIGHT) {
        OPEN_DISP(game->graph);

        pos = effect->position;
        scale = effect->scale;
        
        pos.x += cos_s(pos_angle);
        pos.z += sin_s(pos_angle);
        scale.x = scale.z = scale.z * (sin_s(scale_angle) * 0.1f + 1.0f);
        scale.y = scale.y * (cos_s(scale_angle) * 0.1f + 1.0f);

        eEC_CLIP->auto_matrix_xlu_proc(game, &pos, &scale);
        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_museum5_awa1_model);

        CLOSE_DISP(game->graph);
    }
}
