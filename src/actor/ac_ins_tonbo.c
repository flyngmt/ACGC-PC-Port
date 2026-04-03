/**
 * @file ac_ins_tonbo.c
 * @brief Implementation of the dragonfly actor.
 *
 * This file contains the functions and logic for initializing, updating, and controlling
 * the behavior of dragonfly (tonbo) actors.
 */

#include "ac_ins_tonbo.h"

#include "m_name_table.h"
#include "m_common_data.h"
#include "m_player_lib.h"

enum {
    aITB_ACT_AVOID,
    aITB_ACT_LET_ESCAPE,
    aITB_ACT_FLY,
    aITB_ACT_ONIYANMA_FLY,
    aITB_ACT_WAIT,
    aITB_ACT_TOUCH_WATER,
    aITB_ACT_TOUCH_WATER_REVERSE,
    aITB_ACT_HOVER_WAIT_ON_WATER,
    aITB_ACT_FLY_ON_NOTICE,
    aITB_ACT_REST_ON_NOTICE,

    aITB_ACT_NUM
};

#define aITB_BG_CHECK_RESULT_NONE 0
#define aITB_BG_CHECK_RESULT_COLLIDE 1
#define aITB_BG_CHECK_RESULT_ESCAPE 2

#define aITB_STOP_TYPE_NONE 0
#define aITB_STOP_TYPE_COLLISION 1
#define aITB_STOP_TYPE_REST 2

// Speed settings
#define aITB_ONIYANMA_FLY_SPEED 4.0f // Banded dragonfly fly speed
#define aITB_DARNER_FLY_SPEED 2.4f // Darner dragonfly fly speed
#define aITB_COMMON_FLY_SPEED 2.0f // Common & red dragonfly fly speed

#define aITB_SPEED_VARIANCE 2.0f // Dragonfly speed variance
#define aITB_AVOID_SPEED 4.0f // Avoid speed

// Range settings
#define aITB_ONIYAMA_MAX_RANGE (12 * mFI_UNIT_BASE_SIZE_F) // Banded dragonfly max range
#define aITB_OTHER_MAX_RANGE (6 * mFI_UNIT_BASE_SIZE_F) // Other dragonfly max range

// Timer settings
#define aITB_DARNER_FLY_TIMER 24 // Darner dragonfly fly timer frames
#define aITB_OTHER_FLY_TIMER 20 // Common & red dragonfly fly timer frames
#define aITB_AVOID_TIMER 20 // Avoid timer frames
#define aITB_TOUCH_WATER_REVERSE_TIMER 6 // Touch water reverse timer frames
#define aITB_HOVER_WAIT_ON_WATER_TIMER 20 // Hover wait on water timer frames
#define aITB_REST_ON_NOTICE_TIMER 200 // Rest on notice timer frames

// Dragonfly-specific work variables
#define aITB_GET_HEIGHT(ins) ((ins)->f32_work0)
#define aITB_SET_HEIGHT(ins, h) ((ins)->f32_work0 = (h))
#define aITB_GET_RESERVE_DUMMY_HEIGHT(ins) ((ins)->f32_work1)
#define aITB_SET_RESERVE_DUMMY_HEIGHT(ins, h) ((ins)->f32_work1 = (h))
#define aITB_GET_BK_CENTER_X(ins) ((ins)->f32_work2)
#define aITB_GET_BK_CENTER_Z(ins) ((ins)->f32_work3)

#define aITB_GET_STOP_STATE(ins) ((ins)->s32_work0)
#define aITB_GET_REST_ANIME_TIMER(ins) ((ins)->s32_work2)

static void aITB_actor_move(ACTOR* actorx, GAME* game);

static void aITB_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game);
static int aITB_check_live_condition(aINS_INSECT_ACTOR* insect);

/**
 * Initializes the dragonfly actor.
 *
 * @param actorx Pointer to the actor to initialize.
 * @param game Pointer to the game context.
 */
extern void aITB_actor_init(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* ins = (aINS_INSECT_ACTOR*)actorx;

    // Set movement procedure and gravity
    actorx->mv_proc = &aITB_actor_move;
    actorx->gravity = 0.1f;
    ins->bg_type = aINS_BG_CHECK_TYPE_REG_ATTR;

    // Assign item type based on insect type
    switch (ins->type) {
        case aINS_INSECT_TYPE_COMMON_DRAGONFLY:
            ins->item = ITM_INSECT09;
            break;
        case aINS_INSECT_TYPE_RED_DRAGONFLY:
            ins->item = ITM_INSECT10;
            break;
        case aINS_INSECT_TYPE_DARNER_DRAGONFLY:
            ins->item = ITM_INSECT11;
            break;
        case aINS_INSECT_TYPE_BANDED_DRAGONFLY:
            ins->item = ITM_INSECT12;
            break;
    }

    ins->insect_flags.bit_4 = FALSE;

    // Check if the dragonfly was released
    if (actorx->actor_specific == 0) {
        // Dragonfly was not released
        if (aITB_check_live_condition(ins) == TRUE) {
            int act;

            // Set initial position and angle
            aITB_SET_HEIGHT(ins, 52.0f + RANDOM_F(10.0f));
            actorx->world.position.y = 20.0f + mCoBG_GetBgY_OnlyCenter_FromWpos(actorx->world.position, 0.0f);
            actorx->world.angle.y = DEG2SHORT_ANGLE3(180.0f) - RANDOM_F(DEG2SHORT_ANGLE3(360.0f));
            actorx->shape_info.rotation.y = actorx->world.angle.y;
            mFI_BkNum2WposXZ(&aITB_GET_BK_CENTER_X(ins), &aITB_GET_BK_CENTER_Z(ins), actorx->block_x, actorx->block_z);
            aITB_GET_BK_CENTER_X(ins) += mFI_BK_WORLDSIZE_HALF_X_F;
            aITB_GET_BK_CENTER_Z(ins) += mFI_BK_WORLDSIZE_HALF_Z_F;

            // Set action based on insect type
            if (ins->type == aINS_INSECT_TYPE_BANDED_DRAGONFLY) {
                act = aITB_ACT_ONIYANMA_FLY;
            } else {
                act = aITB_ACT_FLY;
            }

            aITB_setupAction(ins, act, game);
        }
    } else {
        // Dragonfly was released
        ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);

        if (playerx != NULL) {
            // Set initial rotation based on player's rotation
            actorx->shape_info.rotation.y = actorx->world.angle.y = playerx->shape_info.rotation.y + (s16)RANDOM_CENTER_F(DEG2SHORT_ANGLE2(120.0f));
        }

        aITB_setupAction(ins, aITB_ACT_LET_ESCAPE, game);
    }
}

/**
 * Checks if the dragonfly can live in the current conditions.
 *
 * @param insect Pointer to the insect actor.
 * @return TRUE if the dragonfly can live, FALSE otherwise.
 */
static int aITB_check_live_condition(aINS_INSECT_ACTOR* insect) {
    int ret = TRUE;

    // Check that the dragonfly isn't at exactly ground height
    if (mCoBG_ExistHeightGap_KeepAndNow(insect->tools_actor.actor_class.world.position) == TRUE) {
        ret = FALSE;
    // Check for rain
    } else if (Common_Get(weather) == mEnv_WEATHER_RAIN) {
        ret = FALSE;
    } else {
        // Check for valid unit
        mActor_name_t* fg_p = mFI_GetUnitFG(insect->tools_actor.actor_class.world.position);

        if (fg_p == NULL || *fg_p == RSV_NO || ITEM_NAME_GET_TYPE(*fg_p) == NAME_TYPE_STRUCT) {
            ret = FALSE;
        }
    }

    // Mark for destruction if conditions are not met
    if (ret == FALSE) {
        insect->insect_flags.destruct = TRUE;
    }

    return ret;
}

/**
 * Checks for background collisions and adjusts the dragonfly's angle.
 *
 * @param actorx Pointer to the actor.
 * @param game Pointer to the game context.
 * @return aITB_BG_CHECK_RESULT_COLLIDE if collision detected, aITB_BG_CHECK_RESULT_ESCAPE if collided 4+ times, aITB_BG_CHECK_RESULT_NONE otherwise.
 */
static int aITB_BGcheck(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* ins = (aINS_INSECT_ACTOR*)actorx;
    int ret = aITB_BG_CHECK_RESULT_NONE; // no collision

    // Check for wall or ground collision
    if (((actorx->bg_collision_check.result.hit_wall & mCoBG_HIT_WALL_FRONT) != 0 ||
        (actorx->bg_collision_check.result.hit_attribute_wall & mCoBG_HIT_WALL_FRONT) != 0) ||
        actorx->bg_collision_check.result.on_ground) {
        s16 angle = 0;
        int count = actorx->bg_collision_check.result.hit_wall_count;
        int i;

        if (count != 0) {
            for (i = 0; i < actorx->bg_collision_check.result.hit_wall_count; i++) {
                if (actorx->bg_collision_check.wall_info[i].type == mCoBG_WALL_TYPE0) {
                    angle = actorx->bg_collision_check.wall_info[i].angleY - (DEG2SHORT_ANGLE2(180.0f) + actorx->world.angle.y);
                    break;
                }
            }
        }

        // Adjust angle based on collision
        if ((s16)(actorx->world.angle.y - angle) >= 0) {
            angle += (int)RANDOM_F(DEG2SHORT_ANGLE2(45.0f));
        } else {
            angle -= (int)RANDOM_F(DEG2SHORT_ANGLE2(45.0f));
        }
        actorx->world.angle.y = angle;

        ins->continue_timer++;
        if (ins->continue_timer >= 4) {
            // Dragonfly has collided with wall or ground more than four times,
            // so treat it as trapped and set escape action
            aITB_setupAction(ins, aITB_ACT_LET_ESCAPE, game);
            ret = aITB_BG_CHECK_RESULT_ESCAPE;
        } else {
            // Dragonfly has collided with wall or ground
            ret = aITB_BG_CHECK_RESULT_COLLIDE;
        }
    } else {
        ins->continue_timer = 0;
    }

    return ret;
}

/**
 * Controls the height of the dragonfly.
 *
 * @param actorx Pointer to the actor.
 */
static void aITB_height_ctrl(ACTOR* actorx) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    f32 height = mCoBG_GetBgY_OnlyCenter_FromWpos(insect->tools_actor.actor_class.world.position, 0.0f);

    insect->tools_actor.actor_class.max_velocity_y = (aITB_GET_HEIGHT(insect) + height > insect->tools_actor.actor_class.world.position.y) ? 1.0f : -1.0f;
}

/**
 * Checks if the dragonfly touches water.
 *
 * @param insect Pointer to the insect actor.
 * @param game Pointer to the game context.
 * @return TRUE if the dragonfly touches water, FALSE otherwise.
 */
static int aITB_check_water_touch(aINS_INSECT_ACTOR* insect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    int bx;
    int bz;
    int ret = FALSE;

    if (mFI_Wpos2BlockNum(&bx, &bz, insect->tools_actor.actor_class.world.position) == TRUE) {
        if (bz < FG_BLOCK_Z_NUM && (play->game_frame % 100) < 20) {
            u32 attr = mCoBG_Wpos2Attribute(insect->tools_actor.actor_class.world.position, NULL);

            if (mCoBG_CheckWaterAttribute_OutOfSea(attr) == TRUE) {
                ret = TRUE;
            }
        }
    }

    return ret;
}

/**
 * Controls the flying behavior of the dragonfly.
 *
 * @param insect Pointer to the insect actor.
 * @param game Pointer to the game context.
 */
static void aITB_fly_ctrl(aINS_INSECT_ACTOR* insect, GAME* game) {
    if (insect->tools_actor.actor_class.speed == insect->target_speed) {
        if (insect->timer <= 0) {
            if (F32_IS_ZERO(insect->tools_actor.actor_class.speed)) {
                int action;

                if (insect->type != aINS_INSECT_TYPE_BANDED_DRAGONFLY && aITB_check_water_touch(insect, game) == TRUE) {
                    action = aITB_ACT_TOUCH_WATER;
                    insect->flag = 1;
                } else {
                    action = aITB_ACT_WAIT;
                }

                aITB_setupAction(insect, action, game);
            } else {
                insect->target_speed = 0.0f;
            }
        } else {
            insect->timer--;
        }
    }
}

/**
 * Sets the movement speed of the dragonfly.
 *
 * @param insect Pointer to the insect actor.
 */
static void aITB_move_spd_set(aINS_INSECT_ACTOR* insect) {
    switch (insect->type) {
        case aINS_INSECT_TYPE_BANDED_DRAGONFLY:
            insect->target_speed = aITB_ONIYANMA_FLY_SPEED + RANDOM_F(aITB_SPEED_VARIANCE);
            break;
        case aINS_INSECT_TYPE_DARNER_DRAGONFLY:
            insect->target_speed = aITB_DARNER_FLY_SPEED + RANDOM_F(aITB_SPEED_VARIANCE);
            insect->timer = aITB_DARNER_FLY_TIMER;
            break;
        default:
            insect->target_speed = aITB_COMMON_FLY_SPEED + RANDOM_F(aITB_SPEED_VARIANCE);
            insect->timer = aITB_OTHER_FLY_TIMER;
            break;
    }

    insect->speed_step = 0.2f;
}

/**
 * Processes the animation of the dragonfly.
 *
 * @param insect Pointer to the insect actor.
 */
static void aITB_anime_proc(aINS_INSECT_ACTOR* insect) {
    insect->_1E0 += 0.5f;
    if (insect->_1E0 >= 2.0f) {
        insect->_1E0 -= 2.0f;
    }
}

/**
 * Checks if the dragonfly is near a reserved dummy.
 *
 * @param insect Pointer to the insect actor.
 * @return TRUE if near a reserved dummy, FALSE otherwise.
 */
static int aITB_check_reserve_dummy(aINS_INSECT_ACTOR* insect) {
    int ret = FALSE;

    if (insect->patience < 40.0f) {
        mActor_name_t* fg_p = mFI_GetUnitFG(insect->tools_actor.actor_class.world.position);

        if (fg_p != NULL && *fg_p == DUMMY_RESERVE) {
            aITB_GET_STOP_STATE(insect) = aITB_STOP_TYPE_REST;
            aITB_SET_RESERVE_DUMMY_HEIGHT(insect, mCoBG_Wpos2BgUtCenterHeight_AddColumn(insect->tools_actor.actor_class.world.position));
            ret = TRUE;
        }
    }

    return ret;
}

/**
 * Checks for wall and ground collisions.
 *
 * @param insect Pointer to the insect actor.
 * @return TRUE if collision detected, FALSE otherwise.
 */
static int aITB_check_wall_and_ground(aINS_INSECT_ACTOR* insect) {
    int ret = FALSE;

    if ((insect->tools_actor.actor_class.bg_collision_check.result.hit_wall & mCoBG_HIT_WALL_FRONT) != 0 ||
        (insect->tools_actor.actor_class.bg_collision_check.result.hit_attribute_wall & mCoBG_HIT_WALL_FRONT) != 0 ||
        insect->tools_actor.actor_class.bg_collision_check.result.on_ground) {
        aITB_GET_STOP_STATE(insect) = aITB_STOP_TYPE_COLLISION;
        ret = TRUE;
    }

    return ret;
}

/**
 * Checks if the dragonfly should stop.
 *
 * @param insect Pointer to the insect actor.
 * @return TRUE if the dragonfly should stop, FALSE otherwise.
 */
static int aITB_check_stop(aINS_INSECT_ACTOR* insect) {
    int ret = FALSE;

    aITB_GET_STOP_STATE(insect) = aITB_STOP_TYPE_NONE;
    if (insect->type != aINS_INSECT_TYPE_BANDED_DRAGONFLY) {
        if (aITB_check_reserve_dummy(insect) == TRUE) {
            ret = TRUE;
        } else if (aITB_check_wall_and_ground(insect) == TRUE) {
            ret = TRUE;
        }
    }

    return ret;
}

/**
 * Avoid action for the dragonfly.
 *
 * @param actorx Pointer to the actor.
 * @param game Pointer to the game context.
 */
static void aITB_avoid(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* ins = (aINS_INSECT_ACTOR*)actorx;

    if (ins->type != aINS_INSECT_TYPE_BANDED_DRAGONFLY) {
        aITB_fly_ctrl(ins, game);
    }

    aITB_BGcheck(actorx, game);
    add_calc_short_angle2(&actorx->shape_info.rotation.y, actorx->world.angle.y, 1.0f - sqrtf(0.7f), 2500, 0);
}

/**
 * Let escape action for the dragonfly.
 *
 * @param actorx Pointer to the actor.
 * @param game Pointer to the game context.
 */
static void aITB_let_escape(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* ins = (aINS_INSECT_ACTOR*)actorx;
    f32 gravity = actorx->gravity;
    
    gravity *= 1.1f;
    if (gravity > 12.0f) {
        gravity = 12.0f;
    }
    
    actorx->gravity = gravity;
}

/**
 * Fly action for the dragonfly.
 *
 * @param actorx Pointer to the actor.
 * @param game Pointer to the game context.
 */
static void aITB_fly(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* ins = (aINS_INSECT_ACTOR*)actorx;

    add_calc_short_angle2(&actorx->shape_info.rotation.y, actorx->world.angle.y, 1.0f - sqrtf(0.7f), 2500, 0);
    aITB_height_ctrl(actorx);
    if (aITB_check_stop(ins) == TRUE) {
        int action = aITB_ACT_WAIT;

        if (aITB_GET_STOP_STATE(ins) == aITB_STOP_TYPE_REST) {
            action = aITB_ACT_FLY_ON_NOTICE;
        }

        aITB_setupAction(ins, action, game);
    } else {
        aITB_fly_ctrl(ins, game);
    }
}

/**
 * Oniyanma fly action for the dragonfly.
 *
 * @param actorx Pointer to the actor.
 * @param game Pointer to the game context.
 */
static void aITB_oniyanma_fly(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* ins = (aINS_INSECT_ACTOR*)actorx;
    f32 dx;
    f32 dz;

    add_calc_short_angle2(&actorx->shape_info.rotation.y, actorx->world.angle.y, 1.0f - sqrtf(0.7f), 2500, 0);
    aITB_height_ctrl(actorx);
    aITB_BGcheck(actorx, game);

    dx = aITB_GET_BK_CENTER_X(ins) - actorx->world.position.x;
    dz = aITB_GET_BK_CENTER_Z(ins) - actorx->world.position.z;
    if (SQ(dx) + SQ(dz) >= SQ(aITB_ONIYAMA_MAX_RANGE)) {
        // Banded dragonfly has flown too far from center of acre, so escape
        aITB_setupAction(ins, aITB_ACT_LET_ESCAPE, game);
    }
}

/**
 * Wait action for the dragonfly.
 *
 * @param actorx Pointer to the actor.
 * @param game Pointer to the game context.
 */
static void aITB_wait(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* ins = (aINS_INSECT_ACTOR*)actorx;
    int diff_angle;

    add_calc_short_angle2(&actorx->shape_info.rotation.y, actorx->world.angle.y, 1.0f - sqrtf(0.7f), 2500, 0);
    aITB_height_ctrl(actorx);
    diff_angle = actorx->shape_info.rotation.y - actorx->world.angle.y;
    if (ABS((s16)diff_angle) < DEG2SHORT_ANGLE2(2.8125f)) {
        aITB_GET_STOP_STATE(ins) = aITB_STOP_TYPE_NONE;
        aITB_setupAction(ins, aITB_ACT_FLY, game);
    }
}

/**
 * Touch water action for the dragonfly.
 *
 * @param actorx Pointer to the actor.
 * @param game Pointer to the game context.
 */
static void aITB_touch_water(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* ins = (aINS_INSECT_ACTOR*)actorx;

    add_calc_short_angle2(&actorx->shape_info.rotation.y, actorx->world.angle.y, 1.0f - sqrtf(0.7f), 2500, 0);
    
    if (actorx->bg_collision_check.result.is_in_water) {
        aITB_setupAction(ins, aITB_ACT_TOUCH_WATER_REVERSE, game);
    }
}

/**
 * Touch water reverse action for the dragonfly.
 *
 * @param actorx Pointer to the actor.
 * @param game Pointer to the game context.
 */
static void aITB_touch_water_reverse(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* ins = (aINS_INSECT_ACTOR*)actorx;

    add_calc_short_angle2(&actorx->shape_info.rotation.y, actorx->world.angle.y, 1.0f - sqrtf(0.7f), 2500, 0);
    
    if (ins->timer > 0) {
        ins->timer--;
    }

    if (ins->timer == 0) {
        aITB_setupAction(ins, aITB_ACT_HOVER_WAIT_ON_WATER, game);
    }
}

/**
 * Hover wait on water action for the dragonfly.
 *
 * @param actorx Pointer to the actor.
 * @param game Pointer to the game context.
 */
static void aITB_hover_wait_on_water(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* ins = (aINS_INSECT_ACTOR*)actorx;

    if (ins->timer > 0) {
        ins->timer--;
    }

    if (ins->timer == 0) {
        int action;

        if (ins->flag < 2) {
            ins->flag++;
            action = aITB_ACT_TOUCH_WATER;
        } else {
            action = aITB_ACT_WAIT;
        }

        aITB_setupAction(ins, action, game);
    }
}

/**
 * Fly on notice action for the dragonfly.
 *
 * @param actorx Pointer to the actor.
 * @param game Pointer to the game context.
 */
static void aITB_fly_on_notice(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* ins = (aINS_INSECT_ACTOR*)actorx;

    add_calc_short_angle2(&actorx->shape_info.rotation.y, actorx->world.angle.y, 1.0f - sqrtf(0.7f), 2500, 0);

    if (ins->patience < 90.0f) {
        xyz_t pos_in_unit;

        add_calc(&actorx->world.position.y, aITB_GET_RESERVE_DUMMY_HEIGHT(ins), 1.0f - sqrtf(0.8f), 0.5f, 0.0f);
        mFI_Wpos2UtCenterWpos(&pos_in_unit, actorx->world.position);

        if (SQ(pos_in_unit.x - actorx->world.position.x) + SQ(pos_in_unit.z - actorx->world.position.z) > SQ(5.0f)) {
            actorx->world.angle.y = search_position_angleY(&actorx->world.position, &pos_in_unit);
        } else {
            f32 diff_y = aITB_GET_RESERVE_DUMMY_HEIGHT(ins) - actorx->world.position.y;

            if (SQ(diff_y) < SQ(3.0f)) {
                aITB_setupAction(ins, aITB_ACT_REST_ON_NOTICE, game);
            }
        }
    } else {
        aITB_GET_STOP_STATE(ins) = aITB_STOP_TYPE_NONE;
        ins->patience = 100.0f;
        aITB_setupAction(ins, aITB_ACT_FLY, game);
    }
}

/**
 * Rest on notice action for the dragonfly.
 *
 * @param actorx Pointer to the actor.
 * @param game Pointer to the game context.
 */
static void aITB_rest_on_notice(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* ins = (aINS_INSECT_ACTOR*)actorx;

    if (ins->timer > 0 && ins->patience < 90.0f) {
        add_calc(&actorx->world.position.y, aITB_GET_RESERVE_DUMMY_HEIGHT(ins), 1.0f - sqrtf(0.8f), 0.5f, 0.0f);
        aITB_GET_REST_ANIME_TIMER(ins)++;
        if (aITB_GET_REST_ANIME_TIMER(ins) < 20) {
            aITB_anime_proc(ins);
        }

        if (ins->timer > 0) {
            ins->timer--;
        }
    } else {
        aITB_GET_STOP_STATE(ins) = aITB_STOP_TYPE_NONE;
        ins->patience = 100.0f;
        aITB_setupAction(ins, aITB_ACT_FLY, game);
    }
}

/**
 * Initializes the avoid action for the dragonfly.
 *
 * @param insect Pointer to the insect actor.
 * @param game Pointer to the game context.
 */
static void aITB_avoid_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);

    if (playerx != NULL) {
        insect->tools_actor.actor_class.world.angle.y = search_position_angleY(&playerx->world.position, &insect->tools_actor.actor_class.world.position);
    }

    insect->continue_timer = 0;
    insect->target_speed = aITB_AVOID_SPEED + RANDOM_F(aITB_SPEED_VARIANCE);
    insect->timer = aITB_AVOID_TIMER;
}

/**
 * Initializes the let escape action for the dragonfly.
 *
 * @param insect Pointer to the insect actor.
 * @param game Pointer to the game context.
 */
static void aITB_let_escape_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->life_time = 0;
    insect->alpha_time = 80;
    aITB_SET_HEIGHT(insect, 0.0f);
    insect->tools_actor.actor_class.speed = 4.0f;
    insect->tools_actor.actor_class.max_velocity_y = 12.0f;
    insect->tools_actor.actor_class.gravity = 0.06f;
    insect->tools_actor.actor_class.shape_info.rotation.x = 0;
    insect->tools_actor.actor_class.position_speed.y = 0.0f;
    insect->insect_flags.bit_1 = TRUE;
    insect->insect_flags.bit_2 = TRUE;
}

/**
 * Initializes the fly action for the dragonfly.
 *
 * @param insect Pointer to the insect actor.
 * @param game Pointer to the game context.
 */
static void aITB_fly_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->tools_actor.actor_class.shape_info.rotation.y = insect->tools_actor.actor_class.world.angle.y;
    aITB_move_spd_set(insect);
}

/**
 * Initializes the wait action for the dragonfly.
 *
 * @param insect Pointer to the insect actor.
 * @param game Pointer to the game context.
 */
static void aITB_wait_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    static s16 angl_add[] = {
        DEG2SHORT_ANGLE2(-67.50f),
        DEG2SHORT_ANGLE2(-33.75f),
        DEG2SHORT_ANGLE2( 33.75f),
        DEG2SHORT_ANGLE2( 67.50f),
    };

    int i;
    s16 angle;
    u32 attr;

    if (aITB_GET_STOP_STATE(insect) == aITB_STOP_TYPE_NONE) {
        f32 dx = aITB_GET_BK_CENTER_X(insect) - insect->tools_actor.actor_class.world.position.x;
        f32 dz = aITB_GET_BK_CENTER_Z(insect) - insect->tools_actor.actor_class.world.position.z;

        if (SQ(dx) + SQ(dz) < SQ(aITB_OTHER_MAX_RANGE)) {
            // Fly around randomly
            insect->tools_actor.actor_class.world.angle.y += angl_add[RANDOM(ARRAY_COUNT(angl_add))];
        } else {
            // We're too far from the center of the acre, so turn towards it
            insect->tools_actor.actor_class.world.angle.y = atans_table(dz, dx);
        }
    }

    insect->patience = 0.0f;
    insect->continue_timer = 0;
    aITB_GET_REST_ANIME_TIMER(insect) = 0;
    insect->tools_actor.actor_class.speed = 0.0f;
    insect->speed_step = 0.0f;
    insect->timer = 0;

    angle = insect->tools_actor.actor_class.shape_info.rotation.y;
    insect->tools_actor.actor_class.shape_info.rotation.y = insect->tools_actor.actor_class.world.angle.y;
    mCoBG_BgCheckControll(NULL, (ACTOR*)insect, 12.0f, insect->bg_height, TRUE, mCoBG_REVERSE_TYPE_REVERSE, mCoBG_CHECK_TYPE_NORMAL);
    insect->tools_actor.actor_class.shape_info.rotation.y = angle;

    for (i = 0; i < 4; i++) {
        // Check up to 4 times for wall or ground collision.
        // Each check should handle moving the actor slightly if
        // it is too close to a wall or ground.
        if (aITB_BGcheck((ACTOR*)insect, game) != aITB_BG_CHECK_RESULT_COLLIDE) {
            return;
        }

        insect->tools_actor.actor_class.shape_info.rotation.y = insect->tools_actor.actor_class.world.angle.y;
        mCoBG_BgCheckControll(NULL, (ACTOR*)insect, 12.0f, insect->bg_height, TRUE, mCoBG_REVERSE_TYPE_REVERSE, mCoBG_CHECK_TYPE_NORMAL);
    }
    insect->tools_actor.actor_class.shape_info.rotation.y = angle;    
}

/**
 * Initializes the touch water action for the dragonfly.
 *
 * @param insect Pointer to the insect actor.
 * @param game Pointer to the game context.
 */
static void aITB_touch_water_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    aITB_wait_init(insect, game);
    insect->tools_actor.actor_class.max_velocity_y = -1.0f;
}

/**
 * Initializes the touch water reverse action for the dragonfly.
 *
 * @param insect Pointer to the insect actor.
 * @param game Pointer to the game context.
 */
static void aITB_touch_water_reverse_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, insect->tools_actor.actor_class.world.position, 1, insect->tools_actor.actor_class.world.angle.y, game, EMPTY_NO, 4, 0);
    insect->tools_actor.actor_class.max_velocity_y = 4.0f;
    insect->tools_actor.actor_class.position_speed.y = 4.0f;
    insect->timer = aITB_TOUCH_WATER_REVERSE_TIMER;
}

/**
 * Initializes the hover wait on water action for the dragonfly.
 *
 * @param insect Pointer to the insect actor.
 * @param game Pointer to the game context.
 */
static void aITB_hover_wait_on_water_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->tools_actor.actor_class.max_velocity_y = 0.0f;
    insect->tools_actor.actor_class.position_speed.y = 0.0f;
    insect->timer = aITB_HOVER_WAIT_ON_WATER_TIMER;
}

/**
 * Initializes the fly on notice action for the dragonfly.
 *
 * @param insect Pointer to the insect actor.
 * @param game Pointer to the game context.
 */
static void aITB_fly_on_notice_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->patience = 0.0f;
    insect->continue_timer = 0;
    insect->flag = 0;
    aITB_GET_REST_ANIME_TIMER(insect) = 0;
    insect->tools_actor.actor_class.max_velocity_y = 0.0f;
    insect->tools_actor.actor_class.speed = 1.0f;
    insect->target_speed = 2.0f + RANDOM_F(aITB_SPEED_VARIANCE);
}

/**
 * Initializes the rest on notice action for the dragonfly.
 *
 * @param insect Pointer to the insect actor.
 * @param game Pointer to the game context.
 */
static void aITB_rest_on_notice_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->tools_actor.actor_class.speed = 0.0f;
    insect->speed_step = 0.0f;
    insect->target_speed = 0.0f;
    insect->timer = aITB_REST_ON_NOTICE_TIMER;
}

typedef void (*aITB_INIT_PROC)(aINS_INSECT_ACTOR* insect, GAME* game);

/**
 * Sets up the action for the dragonfly.
 *
 * @param insect Pointer to the insect actor.
 * @param action Action to set up.
 * @param game Pointer to the game context.
 */
static void aITB_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game) {
    static aITB_INIT_PROC init_proc[] = {
        aITB_avoid_init,
        aITB_let_escape_init,
        aITB_fly_init,
        aITB_fly_init,
        aITB_wait_init,
        aITB_touch_water_init,
        aITB_touch_water_reverse_init,
        aITB_hover_wait_on_water_init,
        aITB_fly_on_notice_init,
        aITB_rest_on_notice_init,
    };

    static aINS_ACTION_PROC act_proc[] = {
        aITB_avoid,
        aITB_let_escape,
        aITB_fly,
        aITB_oniyanma_fly,
        aITB_wait,
        aITB_touch_water,
        aITB_touch_water_reverse,
        aITB_hover_wait_on_water,
        aITB_fly_on_notice,
        aITB_rest_on_notice,
    };

    insect->action = action;
    insect->action_proc = act_proc[action];
    init_proc[action](insect, game);
}

/**
 * Dragonfly move proc.
 *
 * @param actorx Pointer to the actor.
 * @param game Pointer to the game context.
 */
static void aITB_actor_move(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* ins = (aINS_INSECT_ACTOR*)actorx;
    uintptr_t catch_label = mPlib_Get_item_net_catch_label();

    if (catch_label == (uintptr_t)ins) {
        ins->alpha0 = 255;
        aITB_setupAction(ins, aITB_ACT_LET_ESCAPE, game);
    } else if (ins->insect_flags.bit_3 == TRUE && ins->insect_flags.bit_2 == FALSE) {
        aITB_setupAction(ins, aITB_ACT_LET_ESCAPE, game);
    } else {
        ins->action_proc(actorx, game);
        if (aITB_GET_STOP_STATE(ins) != aITB_STOP_TYPE_REST) {
            aITB_anime_proc(ins);
        }
    }
}
