/**
 * @file ac_ins_mino.c
 * @brief Implements bagworm and spider behaviors.
 * 
 * This file handles bagworms (minomushi) and spiders, which are insects that hang from trees.
 * They react to tree shaking and player proximity by either falling or escaping.
 */

#include "ac_ins_mino.h"

#include "m_name_table.h"
#include "m_common_data.h"
#include "m_player_lib.h"

// Actor-specific work variable getters
#define aIMN_CURRENT_SHAKE(ins) ((ins)->s32_work0)
#define aIMN_TREE_UNIT_X(ins) ((ins)->s32_work1)
#define aIMN_TREE_UNIT_Z(ins) ((ins)->s32_work2)
#define aIMN_TARGET_SHAKE(ins) ((ins)->s32_work3)

// Float work variables
#define aIMN_ANIM_TIME(ins) ((ins)->f32_work0)
#define aIMN_SHAKE_POS_X(ins) ((ins)->f32_work1)
#define aIMN_SHAKE_POS_Y(ins) ((ins)->f32_work2)
#define aIMN_BASE_POS_Z(ins) ((ins)->f32_work3)

enum {
    aIMN_ACT_AVOID,
    aIMN_ACT_LET_ESCAPE,
    aIMN_ACT_HIDE,
    aIMN_ACT_APPEAR,
    aIMN_ACT_APPEAR_STOP,
    aIMN_ACT_WAIT,
    aIMN_ACT_DISAPPEAR,
    aIMN_ACT_DIVE,
    aIMN_ACT_DROWN,
    aIMN_ACT_FALL,

    aIMN_ACT_NUM
};

static void aIMN_actor_move(ACTOR* actorx, GAME* game);

static void aIMN_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game);
static void aIMN_position_move(ACTOR* actorx);

/**
 * Initializes a bagworm or spider actor.
 * Sets initial position, type, and starting action.
 *
 * @param actorx Actor to initialize
 * @param game Current game context
 */
extern void aIMN_actor_init(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int action;
    
    insect->bg_range = 4.0f;

    switch (insect->type) {
        case aINS_INSECT_TYPE_BAGWORM:
            insect->item = ITM_INSECT35;
            break;
        case aINS_INSECT_TYPE_SPIDER:
            insect->item = ITM_INSECT37;
            break;
    }

    actorx->mv_proc = &aIMN_actor_move;
    insect->insect_flags.bit_4 = FALSE;

    if (actorx->actor_specific == 0) {
        actorx->world.position.y = 5.0f + mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, -60.0f);
        actorx->shape_info.rotation.x = DEG2SHORT_ANGLE2(47.8125f);
        actorx->shape_info.rotation.y = DEG2SHORT_ANGLE2(180.0f);
        actorx->world.angle.x = DEG2SHORT_ANGLE2(47.8125f);
        xyz_t_move(&actorx->home.position, &actorx->world.position);
        mFI_Wpos2UtNum(&aIMN_TREE_UNIT_X(insect), &aIMN_TREE_UNIT_Z(insect), actorx->world.position);
        aIMN_BASE_POS_Z(insect) = -25.0f + actorx->world.position.z;
        insect->move_proc = &aIMN_position_move;
        actorx->shape_info.draw_shadow = FALSE;
        action = aIMN_ACT_HIDE;
    } else {
        actorx->drawn = TRUE;
        action = aIMN_ACT_LET_ESCAPE;
    }

    aIMN_setupAction(insect, action, game);
}

/**
 * Checks if the tree the insect is on is being shaken.
 *
 * @param actorx Actor to check
 * @return TRUE if tree is being shaken
 */
static int aIMN_check_shake_tree(ACTOR* actorx) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int ret = FALSE;

    if (
        // clang-format off
        CLIP(insect_clip)->pl_action == aINS_PL_ACT_SHAKE_TREE &&
        CLIP(insect_clip)->pl_action_ut_x == aIMN_TREE_UNIT_X(insect) &&
        CLIP(insect_clip)->pl_action_ut_z == aIMN_TREE_UNIT_Z(insect)
        // clang-format on
    ) {
        ret = TRUE;
    }

    return ret;
}

/**
 * Updates the insect's position while hanging/moving.
 *
 * @param actorx Actor to update position
 */
static void aIMN_position_move(ACTOR* actorx) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    s16 angleX = actorx->world.angle.x;
    f32 counter = aIMN_ANIM_TIME(insect);

    xyz_t_move(&actorx->last_world_position, &actorx->world.position);
    chase_f(&actorx->speed, insect->target_speed, insect->speed_step * 0.5f);
    counter += actorx->speed * 0.5f;
    aIMN_ANIM_TIME(insect) = counter;
    actorx->world.position.y = actorx->home.position.y + cos_s(angleX) * counter;
    actorx->world.position.z = aIMN_BASE_POS_Z(insect) - sin_s(angleX) * counter;
}

/**
 * Updates the shaking animation angles for the insect.
 *
 * @param actorx Actor to update
 */
static void aIMN_calc_shake_angl(ACTOR* actorx) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    s16 angleY = actorx->shape_info.rotation.y;
    s16 current_shake = aIMN_CURRENT_SHAKE(insect);
    s16 target_shake = aIMN_TARGET_SHAKE(insect);

    if (target_shake * angleY < 0) {
        target_shake = -(target_shake * 0.5f);

        if (ABS(target_shake) < 16) {
            target_shake = 0;
            current_shake = 0;
            angleY = DEG2SHORT_ANGLE2(180.0f);
        }

        aIMN_TARGET_SHAKE(insect) = target_shake;
    }

    chase_angle(&current_shake, target_shake, 16);
    aIMN_CURRENT_SHAKE(insect) = current_shake;
    angleY += (s16)(current_shake * 0.5f);
    actorx->shape_info.rotation.y = angleY;
    actorx->world.position.x = aIMN_SHAKE_POS_X(insect) - 50.0f * sin_s(angleY);
    actorx->world.position.y = aIMN_SHAKE_POS_Y(insect) + 50.0f + 50.0f * cos_s(angleY);
}

/**
 * Updates the twisting animation for the insect.
 *
 * @param actorx Actor to update
 */
static void aIMN_calc_twist_angl(ACTOR* actorx) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    s16 twist_angl = insect->continue_timer;

    twist_angl += 0x100;
    insect->continue_timer = twist_angl;
    actorx->shape_info.rotation.z = (s16)(sin_s(twist_angl) * DEG2SHORT_ANGLE3(22.5f));
}

/**
 * Checks if the tree has been cut down.
 *
 * @param actorx Actor to check
 * @return TRUE if tree is cut
 */
static int aIMN_check_cut_tree(ACTOR* actorx) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int ret = FALSE;
    mActor_name_t* fg_p = mFI_GetUnitFG(actorx->home.position);

    if (fg_p == NULL || IS_ITEM_TREE_STUMP(*fg_p) == TRUE) {
        ret = TRUE;
    }

    return ret;
}

/**
 * Checks if the insect has touched water.
 *
 * @param insect Insect to check
 * @param game Current game context
 * @return TRUE if water was touched
 */
static int aIMN_chk_water_attr(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;
    int ret = FALSE;
    f32 reverse;
    s16 angleY;

    if (actorx->bg_collision_check.result.on_ground) {
        xyz_t pos = actorx->world.position;

        reverse = insect->bg_range + actorx->speed;
        angleY = actorx->world.angle.y;
        pos.x += reverse * sin_s(angleY);
        pos.z += reverse * cos_s(angleY);
        if (mCoBG_CheckWaterAttribute(mCoBG_Wpos2BgAttribute_Original(pos))) {
            aIMN_setupAction(insect, aIMN_ACT_DIVE, game);
            ret = TRUE;
        }
    }

    return ret;
}

/**
 * Calculates direction angles for movement.
 *
 * @param actorx Actor to update
 */
static void aIMN_calc_direction_angl(ACTOR* actorx) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int wall_check;

    switch (insect->type) {
        case aINS_INSECT_TYPE_BAGWORM:
            wall_check = mCoBG_HIT_WALL_FRONT;
            break;
        case aINS_INSECT_TYPE_SPIDER:
            wall_check = mCoBG_HIT_WALL_BACK;
            break;
        default:
            wall_check = mCoBG_HIT_WALL_FRONT;
            break;
    }

    if (actorx->bg_collision_check.result.hit_wall & wall_check) {
        int count = actorx->bg_collision_check.result.hit_wall_count;
        int i;

        if (count != 0) {
            for (i = 0; i < count; i++) {
                if (actorx->bg_collision_check.wall_info[i].type == mCoBG_WALL_TYPE0) {
                    actorx->world.angle.y = DEG2SHORT_ANGLE2(90.0f) + actorx->bg_collision_check.wall_info[i].angleY;
                    break;
                }
            }
        }
    }

    switch (insect->type) {
        case aINS_INSECT_TYPE_BAGWORM:
            chase_angle(&actorx->shape_info.rotation.y, actorx->world.angle.y, 0x800);
            break;
        case aINS_INSECT_TYPE_SPIDER:
            chase_angle(&actorx->shape_info.rotation.y, actorx->world.angle.y + DEG2SHORT_ANGLE2(-180.0f), 0x800);
            break;
    }
}

// Action functions
static void aIMN_let_escape(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (aIMN_chk_water_attr(insect, game) == FALSE) {
        aIMN_calc_direction_angl(actorx);
    }
}

static void aIMN_hide(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (aIMN_check_cut_tree(actorx) == TRUE) {
        aIMN_setupAction(insect, aIMN_ACT_FALL, game);
    } else if (aIMN_check_shake_tree(actorx) == TRUE) {
        aIMN_setupAction(insect, aIMN_ACT_APPEAR, game);
    }
}

static void aIMN_appear(ACTOR* actorx, GAME* game) {
    static f32 move_range_table[] = { -41.0f, -47.0f };
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    f32 move_range = move_range_table[insect->flag];

    if (aIMN_check_cut_tree(actorx) == TRUE) {
        aIMN_setupAction(insect, aIMN_ACT_FALL, game);
    } else {
        if (aIMN_ANIM_TIME(insect) < move_range) {
            if (insect->target_speed < 0.0f && actorx->speed < 0.0f) {
                if (actorx->speed > -2.0f) {
                    aIMN_setupAction(insect, aIMN_ACT_APPEAR_STOP, game);
                } else {
                    insect->target_speed = -actorx->speed * 0.2f;
                    insect->speed_step = 8.0f;
                }
            }
        } else {
            insect->target_speed = -12.0f;
            insect->speed_step = 2.0f;
        }

        aIMN_calc_twist_angl(actorx);
    }
}

static void aIMN_appear_stop(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (aIMN_check_cut_tree(actorx) == TRUE) {
        aIMN_setupAction(insect, aIMN_ACT_FALL, game);
    } else {
        if (F32_IS_ZERO(actorx->speed)) {
            aIMN_setupAction(insect, aIMN_ACT_WAIT, game);
        }

        aIMN_calc_twist_angl(actorx);
    }
}

static void aIMN_wait(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (aIMN_check_cut_tree(actorx) == TRUE) {
        actorx->scale.x = 0.01f;
        actorx->scale.y = 0.01f;
        aIMN_setupAction(insect, aIMN_ACT_FALL, game);
    } else {
        if (aIMN_check_shake_tree(actorx) == TRUE) {
            aIMN_CURRENT_SHAKE(insect) = 0x80;
            aIMN_TARGET_SHAKE(insect) = -0x80;
        }

        insect->timer--;
        if (insect->timer <= 0) {
            if (aIMN_TARGET_SHAKE(insect) == 0) {
                actorx->scale.x = 0.01f;
                actorx->scale.y = 0.01f;
                aIMN_setupAction(insect, aIMN_ACT_DISAPPEAR, game);
            } else {
                insect->timer = 0;
            }
        } else {
            static f32 scaleX_table[] = {
                0.01f,
                0.00875f,
                0.01125f,
                0.00875f,
                0.01125f,
                0.00875f,
                0.01125f,
            };

            static f32 scaleY_table[] = {
                0.01f,
                0.01125f,
                0.00875f,
                0.01125f,
                0.00875f,
                0.01125f,
                0.00875f,
            };

            int idx = actorx->actor_specific;

            if (idx < 7) {
                int res0 = chase_f(&actorx->scale.x, scaleX_table[idx], 0.001125f);
                int res1 = chase_f(&actorx->scale.y, scaleY_table[idx], 0.001125f);

                if ((res0 & res1) == TRUE) {
                    actorx->actor_specific--;
                    if (actorx->actor_specific < 0) {
                        actorx->actor_specific = 0x133 + (s16)(60.0f * RANDOM_F(5.0f));
                    }
                }
            } else {
                actorx->actor_specific--;
            }
        }

        aIMN_calc_shake_angl(actorx);
        aIMN_calc_twist_angl(actorx);
    }
}

static void aIMN_disappear(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (aIMN_check_cut_tree(actorx) == TRUE) {
        aIMN_setupAction(insect, aIMN_ACT_FALL, game);
    } else {
        if (actorx->world.position.y > actorx->home.position.y) {
            aIMN_setupAction(insect, aIMN_ACT_HIDE, game);
        }

        aIMN_calc_twist_angl(actorx);
    }
}

static void aIMN_dive(ACTOR* actorx, GAME* game) {
    f32 water_y = mCoBG_GetWaterHeight_File(actorx->world.position, __FILE__, 685);

    if (actorx->world.position.y <= water_y) {
        aIMN_setupAction((aINS_INSECT_ACTOR*)actorx, aIMN_ACT_DROWN, game);
    }
}

static void aIMN_fall(ACTOR* actorx, GAME* game) {
    f32 bg_y = mCoBG_GetBgY_AngleS_FromWpos(NULL, actorx->world.position, 0.0f);

    if (actorx->world.position.y < bg_y) {
        actorx->world.position.y = bg_y;
        aIMN_setupAction((aINS_INSECT_ACTOR*)actorx, aIMN_ACT_LET_ESCAPE, game);
    }
}

// Action init functions
static void aIMN_let_escape_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* playerx;

    insect->life_time = 0.0f;
    insect->alpha_time = 80;
    insect->bg_type = aINS_BG_CHECK_TYPE_REG_NO_ATTR;
    insect->tools_actor.actor_class.gravity = 2.0f;
    insect->tools_actor.actor_class.max_velocity_y = -20.0f;
    insect->tools_actor.actor_class.shape_info.rotation.x = 0;
    insect->tools_actor.actor_class.shape_info.rotation.z = 0;

    playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    if (playerx != NULL) {
        insect->tools_actor.actor_class.world.angle.y = playerx->shape_info.rotation.y + (s16)RANDOM_CENTER_F(DEG2SHORT_ANGLE2(120.0f));
    }

    switch (insect->type) {
        case aINS_INSECT_TYPE_BAGWORM:
            insect->target_speed = 0.75f;
            insect->speed_step = 0.15f;
            insect->_1E0 = 2.0f;
            insect->tools_actor.actor_class.shape_info.rotation.y = insect->tools_actor.actor_class.world.angle.y;
            break;
        case aINS_INSECT_TYPE_SPIDER:
            insect->target_speed = 1.5f;
            insect->speed_step = 0.3f;
            insect->_1E0 = 0.0f;
            insect->tools_actor.actor_class.shape_info.rotation.y = insect->tools_actor.actor_class.world.angle.y + DEG2SHORT_ANGLE2(-180.0f);
            break;
    }

    insect->insect_flags.bit_1 = TRUE;
    insect->insect_flags.bit_2 = TRUE;
}

static void aIMN_hide_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->tools_actor.actor_class.speed = 0.0f;
    insect->target_speed = 0.0f;
    insect->speed_step = 0.0f;
    insect->tools_actor.actor_class.world.position.y = insect->tools_actor.actor_class.home.position.y;
    insect->_1E0 = 1.0f;
    insect->tools_actor.actor_class.drawn = FALSE;
    insect->insect_flags.bit_1 = TRUE;
}

static void aIMN_appear_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);

    if (playerx != NULL) {
        int flag;
        f32 pos_x;
        f32 pos_z;

        if (playerx->world.position.x < insect->tools_actor.actor_class.home.position.x) {
            pos_x = insect->tools_actor.actor_class.home.position.x + 30.0f;
            pos_z = insect->tools_actor.actor_class.home.position.z + -18.0f;
            aIMN_ANIM_TIME(insect) = 0.0f;
            flag = FALSE;
        } else {
            pos_x = insect->tools_actor.actor_class.home.position.x - 30.0f;
            pos_z = insect->tools_actor.actor_class.home.position.z + -25.0f;
            insect->tools_actor.actor_class.world.position.y = (-47.0f + insect->tools_actor.actor_class.home.position.y) - -41.0f;
            aIMN_ANIM_TIME(insect) = -6.0f;
            flag = TRUE;
        }

        insect->tools_actor.actor_class.world.position.x = pos_x;
        insect->tools_actor.actor_class.world.position.z = pos_z;
        insect->flag = flag;
    }

    aIMN_BASE_POS_Z(insect) = insect->tools_actor.actor_class.world.position.z;
    insect->tools_actor.actor_class.speed = 0.0f;
    insect->target_speed = -20.0f;
    insect->speed_step = 2.0f;
    insect->tools_actor.actor_class.drawn = TRUE;
    insect->insect_flags.bit_1 = FALSE;
}

static void aIMN_appear_stop_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->speed_step = 8.0f;
    insect->target_speed = 0.0f;
}

static void aIMN_wait_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->timer = 1200;
    insect->tools_actor.actor_class.speed = 0.0f;
    insect->target_speed = 0.0f;
    insect->speed_step = 0.0f;
    insect->tools_actor.actor_class.actor_specific = 0x133 + (s16)(60.0f * RANDOM_F(5.0f));
    aIMN_SHAKE_POS_X(insect) = insect->tools_actor.actor_class.world.position.x;
    aIMN_SHAKE_POS_Y(insect) = insect->tools_actor.actor_class.world.position.y;
}

static void aIMN_disappear_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->target_speed = 0.5f;
    insect->speed_step = 0.025f;
    insect->tools_actor.actor_class.shape_info.rotation.z = 0;
}

static void aIMN_dive_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->target_speed = 1.5f;
    insect->speed_step = 0.3;
    insect->tools_actor.actor_class.speed = insect->target_speed;
    insect->tools_actor.actor_class.position_speed.y = 8.0f;

    switch (insect->type) {
        case aINS_INSECT_TYPE_BAGWORM:
            insect->_1E0 = 2.0f;
            break;
        case aINS_INSECT_TYPE_SPIDER:
            insect->_1E0 = 0.0f;
            break;
    }

    insect->insect_flags.bit_1 = TRUE;
}

static void aIMN_drown_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    xyz_t pos = insect->tools_actor.actor_class.world.position;
    
    pos.y = mCoBG_GetWaterHeight_File(pos, __FILE__, 936);
    eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_MIZU, pos, 1, insect->tools_actor.actor_class.world.angle.y, game, EMPTY_NO, 4, 0);
    sAdo_OngenTrgStart(NA_SE_438, &insect->tools_actor.actor_class.world.position);
    insect->insect_flags.bit_1 = TRUE;
    insect->insect_flags.destruct = TRUE;
    insect->tools_actor.actor_class.shape_info.draw_shadow = FALSE;
}

static void aIMN_fall_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->tools_actor.actor_class.gravity = 2.0f;
    insect->tools_actor.actor_class.max_velocity_y = -20.0f;
    insect->tools_actor.actor_class.shape_info.rotation.z = 0;
    insect->move_proc = CLIP(insect_clip)->position_move_proc;
    insect->tools_actor.actor_class.drawn = TRUE;

    switch (insect->type) {
        case aINS_INSECT_TYPE_BAGWORM:
            insect->_1E0 = 2.0f;
            break;
        case aINS_INSECT_TYPE_SPIDER:
            insect->_1E0 = 0.0f;
            break;
    }
}

typedef void (*aIMN_INIT_PROC)(aINS_INSECT_ACTOR* insect, GAME* game);

/**
 * Sets up a new action state for the insect.
 *
 * @param insect Insect to update
 * @param action New action to perform
 * @param game Current game context
 */
static void aIMN_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game) {
    static aIMN_INIT_PROC init_proc[] = {
        (aIMN_INIT_PROC)none_proc1,
        aIMN_let_escape_init,
        aIMN_hide_init,
        aIMN_appear_init,
        aIMN_appear_stop_init,
        aIMN_wait_init,
        aIMN_disappear_init,
        aIMN_dive_init,
        aIMN_drown_init,
        aIMN_fall_init,
    };

    static aINS_ACTION_PROC act_proc[] = {
        (aINS_ACTION_PROC)none_proc1,
        aIMN_let_escape,
        aIMN_hide,
        aIMN_appear,
        aIMN_appear_stop,
        aIMN_wait,
        aIMN_disappear,
        aIMN_dive,
        (aINS_ACTION_PROC)none_proc1,
        aIMN_fall,
    };

    insect->action = action;
    insect->action_proc = act_proc[action];
    init_proc[action](insect, game);
}

/**
 * Main movement update function for bagworm/spider actors.
 * Handles state changes and updates current behavior.
 *
 * @param actorx Actor to update
 * @param game Current game context
 */
static void aIMN_actor_move(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    uintptr_t catch_label = mPlib_Get_item_net_catch_label();

    if (catch_label == (uintptr_t)actorx) {
        insect->alpha0 = 255;
        insect->tools_actor.actor_class.shape_info.rotation.y = DEG2SHORT_ANGLE2(180.0f);
        aIMN_setupAction(insect, aIMN_ACT_LET_ESCAPE, game);
    } else {
        insect->action_proc(actorx, game);
    }
}
