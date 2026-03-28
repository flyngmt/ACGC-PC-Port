#include "ac_ins_ka.h"

#include "m_field_info.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_player_lib.h"

enum {
    aIKA_ACTION_AVOID,
    aIKA_ACTION_LET_ESCAPE,
    aIKA_ACTION_FLY,
    aIKA_ACTION_SEARCH,
    aIKA_ACTION_ATTACK_WAIT,
    aIKA_ACTION_ATTACK,

    aIKA_ACTION_NUM
};

#define aIKA_ATTACK_DIST (mFI_UNIT_BASE_SIZE_F / 2)
#define aIKA_ATTACK_TIME (180)
#define aIKA_IS_DEMO_ACTIVE() (Common_Get(clip).demo_clip != NULL || Common_Get(clip).demo_clip2 != NULL)

#define aIKA_RANDOM_ANGLE() ((s16)((fqrand() - 0.5f) * (f32)DEG2SHORT_ANGLE2(120.0f)))

#define aIKA_ANGLE(insect) ((insect)->s32_work0)
#define aIKA_ATTACK_TIMER(insect) ((insect)->s32_work1)
#define aIKA_TURN_SPEED(insect) ((insect)->f32_work0)
#define aIKA_SPEED(insect) ((insect)->f32_work1)

static void aIKA_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game);
static void aIKA_actor_move(ACTOR* actorx, GAME* game);

extern void aIKA_actor_init(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int act;

    if (actorx->actor_specific == 0) {
        actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos(actorx->world.position, 30.0f);
        act = aIKA_ACTION_FLY;
    } else {
        act = aIKA_ACTION_LET_ESCAPE;
    }

    insect->bg_range = 6.0f;
    insect->bg_height = -14.0f;
    insect->bg_type = 1;
    insect->item = ITM_INSECT39;
    xyz_t_move(&actorx->home.position, &actorx->world.position);
    actorx->mv_proc = &aIKA_actor_move;
    aIKA_setupAction(insect, act, game);
}

static void aIKA_fuwafuwa(aINS_INSECT_ACTOR* insect) {
    s16 angle = aIKA_ANGLE(insect);
    f32 last_spd_angle = aIKA_TURN_SPEED(insect) * sin_s(angle);
    f32 now_spd_angle;

    aIKA_ANGLE(insect) = (s16)(angle + 0x180);
    if ((s16)(angle + 0x180) < 0 && angle >= 0) {
        aIKA_TURN_SPEED(insect) = 10.0f + RANDOM_F(10.0f);
    }

    angle += 0x180;
    now_spd_angle = aIKA_TURN_SPEED(insect) * sin_s(angle);
    chase_f(&aIKA_SPEED(insect), insect->tools_actor.actor_class.max_velocity_y,
            insect->tools_actor.actor_class.gravity * 0.5f);
    insect->tools_actor.actor_class.position_speed.y = aIKA_SPEED(insect) + (now_spd_angle - last_spd_angle);
}

static void aIKA_anime_proc(aINS_INSECT_ACTOR* insect) {
    insect->_1E0 += 0.2f;
    if (insect->_1E0 >= 2.0f) {
        insect->_1E0 -= 2.0f;
    }
}

static void aIKA_BGcheck(aINS_INSECT_ACTOR* insect) {
    if ((insect->tools_actor.actor_class.bg_collision_check.result.hit_wall & mCoBG_HIT_WALL_FRONT) != 0 ||
        (insect->tools_actor.actor_class.bg_collision_check.result.hit_attribute_wall & mCoBG_HIT_WALL_FRONT) != 0 ||
        (insect->tools_actor.actor_class.bg_collision_check.result.on_ground)) {
        s16 new_dir = insect->tools_actor.actor_class.world.angle.y + DEG2SHORT_ANGLE2(180.0f); // turn around
        insect->tools_actor.actor_class.world.angle.y = new_dir;
        insect->tools_actor.actor_class.shape_info.rotation.y = new_dir;
    }
}

static int aIKA_check_condition(aINS_INSECT_ACTOR* insect, GAME_PLAY* play) {
    ACTOR* actorx = (ACTOR*)insect;
    int res = FALSE;

    if (actorx->block_x == play->block_table.block_x && actorx->block_z == play->block_table.block_z) {
        if (ABS(actorx->player_distance_y) < 60.0f) {
            res = TRUE;
        }
    }

    return res;
}

static void aIKA_calc_angle_search_player(ACTOR* actorx, s16 step) {
    s16 angle = actorx->shape_info.rotation.y;

    chase_angle(&angle, actorx->player_angle_y, step);
    actorx->shape_info.rotation.y = angle;
    actorx->world.angle.y = angle;
}

static void aIKA_avoid(ACTOR* actorx, GAME* game) {
    f32 grav = actorx->gravity;

    grav *= 1.1f;
    if (grav > 12.0f) {
        grav = 12.0f;
    }

    actorx->gravity = grav;
}

static void aIKA_fly(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);

    aIKA_BGcheck(insect);

    /* Check that no demo is active */
    if (aIKA_IS_DEMO_ACTIVE()) {
        /* A demo is active (including chores), so despawn mosquito */
        aIKA_setupAction(insect, aIKA_ACTION_AVOID, game);
    } else if (player != NULL && aIKA_check_condition(insect, play) == TRUE) {
        aIKA_setupAction(insect, aIKA_ACTION_SEARCH, game);
    } else {
        s16 angle = actorx->shape_info.rotation.y + 0x80;

        actorx->shape_info.rotation.y = angle;
        actorx->world.angle.y = angle;
    }
}

static void aIKA_search(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    /* Check that no demo is active */
    if (aIKA_IS_DEMO_ACTIVE()) {
        /* A demo is active (including chores), so despawn mosquito */
        aIKA_setupAction(insect, aIKA_ACTION_AVOID, game);
    } else if (aIKA_check_condition(insect, play) == FALSE) {
        aIKA_setupAction(insect, aIKA_ACTION_FLY, game);
    } else if (actorx->player_distance_xz <= aIKA_ATTACK_DIST) {
        aIKA_setupAction(insect, aIKA_ACTION_ATTACK_WAIT, game);
    } else {
        s16 step;

        if (actorx->player_distance_xz <= mFI_UNIT_BASE_SIZE_F) {
            step = 0x100;
        } else {
            step = 0x200;
        }

        aIKA_calc_angle_search_player(actorx, step);
    }
}

static void aIKA_attack_wait(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    /* Check that no demo is active */
    if (aIKA_IS_DEMO_ACTIVE()) {
        /* A demo is active (including chores), so despawn mosquito */
        aIKA_setupAction(insect, aIKA_ACTION_AVOID, game);
    } else if (aIKA_check_condition(insect, play) == FALSE) {
        aIKA_setupAction(insect, aIKA_ACTION_FLY, game);
    } else if (actorx->player_distance_xz > aIKA_ATTACK_DIST) {
        aIKA_setupAction(insect, aIKA_ACTION_SEARCH, game);
    } else {
        aIKA_calc_angle_search_player(actorx, 0x600);
        aIKA_ATTACK_TIMER(insect)++;

        if (aIKA_ATTACK_TIMER(insect) > aIKA_ATTACK_TIME) {
            if (mPlib_Check_stung_mosquito(actorx)) {
                aIKA_setupAction(insect, aIKA_ACTION_ATTACK, game);
            } else {
                mPlib_request_main_stung_mosquito_type1(actorx);
                aIKA_ATTACK_TIMER(insect) = aIKA_ATTACK_TIME;
            }
        }
    }
}

static void aIKA_attack(ACTOR* actorx, GAME* game) {
    if (mPlib_Check_stung_mosquito(actorx) == FALSE) {
        aIKA_setupAction((aINS_INSECT_ACTOR*)actorx, aIKA_ACTION_AVOID, game);
    }
}

static void aIKA_avoid_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player;

    insect->life_time = 0;
    insect->alpha_time = 80;
    actorx->gravity = 0.06f;
    actorx->max_velocity_y = 12.0f;
    actorx->speed = 4.0f;
    actorx->shape_info.rotation.x = 0;
    aIKA_SPEED(insect) = actorx->position_speed.y;

    player = GET_PLAYER_ACTOR(play);
    if (player != NULL) {
        s16 rnd_angle = player->actor_class.shape_info.rotation.y + aIKA_RANDOM_ANGLE();

        actorx->world.angle.y = rnd_angle;
        actorx->shape_info.rotation.y = rnd_angle;
    }

    insect->insect_flags.bit_1 = TRUE;
    insect->insect_flags.bit_2 = TRUE;
}

static void aIKA_fly_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->tools_actor.actor_class.speed = 1.2f;
}

static void aIKA_attack_wait_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    aIKA_ATTACK_TIMER(insect) = 0;
}

static void aIKA_attack_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->tools_actor.actor_class.speed = 0.0f;
    insect->target_speed = 0.0f;
    insect->speed_step = 0.0f;
    insect->tools_actor.actor_class.position_speed.y = 0.0f;
    sAdo_OngenTrgStart(NA_SE_6A, &insect->tools_actor.actor_class.world.position);
}

typedef void (*aIKA_INIT_PROC)(aINS_INSECT_ACTOR*, GAME*);

static void aIKA_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game) {
    // clang-format off
    static aIKA_INIT_PROC init_proc[] = {
        &aIKA_avoid_init,
        &aIKA_avoid_init,
        &aIKA_fly_init,
        (aIKA_INIT_PROC)&none_proc1,
        &aIKA_attack_wait_init,
        &aIKA_attack_init,
    };
    // clang-format on

    // clang-format off
    static aINS_ACTION_PROC act_proc[] = {
        &aIKA_avoid,
        &aIKA_avoid,
        &aIKA_fly,
        &aIKA_search,
        &aIKA_attack_wait,
        &aIKA_attack,
    };
    // clang-format on

    insect->action = action;
    insect->action_proc = act_proc[action];
    (*init_proc[action])(insect, game);
}

static void aIKA_actor_move(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    u32 label;

    if (mPlib_get_player_actor_main_index(game) != mPlayer_INDEX_PUTAWAY_NET && insect->action != aIKA_ACTION_ATTACK) {
        aIKA_anime_proc(insect);
        aIKA_fuwafuwa(insect);
    } else {
        insect->_1E0 = 0;
    }

    label = mPlib_Get_item_net_catch_label();
    if (label == (uintptr_t)actorx) {
        aIKA_setupAction(insect, aIKA_ACTION_LET_ESCAPE, game);
    } else {
        if (insect->action != aIKA_ACTION_ATTACK) {
            sAdo_OngenPos((uintptr_t)actorx, NA_SE_KA_BUZZ, &actorx->world.position);
        }

        if (insect->insect_flags.bit_3 == TRUE && insect->insect_flags.bit_2 == FALSE &&
            insect->action != aIKA_ACTION_LET_ESCAPE) {
            aIKA_setupAction(insect, aIKA_ACTION_LET_ESCAPE, game);
        } else {
            (*insect->action_proc)(actorx, game);
        }
    }
}
