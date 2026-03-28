/**
 * @file ac_ins_tentou.c
 * @brief Implements flower-based insect behaviors.
 * 
 * Handles ladybugs, spotted ladybugs, mantises, and snails which are insects
 * found on flowers. These insects will move on flowers and escape when
 * disturbed by the player.
 */

#include "ac_ins_tentou.h"

#include "m_name_table.h"
#include "m_common_data.h"
#include "m_player_lib.h"

enum {
    aITT_ACT_AVOID,
    aITT_ACT_AVOID_MAIMAI,
    aITT_ACT_LET_ESCAPE,
    aITT_ACT_LET_ESCAPE_MAIMAI,
    aITT_ACT_MOVE,
    aITT_ACT_WAIT,

    aITT_ACT_NUM
};

// Flower insect specific variables
#define aITT_BALL_SCARE_DIST 60.0f // Distance threshold to be scared by ball
#define aITT_NET_SCARE_DIST 70.0f // Distance threshold to be scared by net
#define aITT_SCOOP_SCARE_DIST 60.0f // Distance threshold to be scared by scoop

// Actor-specific work variable getters
#define aITT_TARGET_ANGLE(ins) ((ins)->s32_work1)
#define aITT_TURN_DELAY(ins) ((ins)->s32_work2)

static void aITT_actor_move(ACTOR* actorx, GAME* game);
static void aITT_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game);

/**
 * Initializes a flower-based insect actor.
 * Sets initial position and type-specific properties.
 *
 * @param actorx Actor to initialize
 * @param game Current game context
 */
extern void aITT_actor_init(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int action;
    
    actorx->mv_proc = aITT_actor_move;
    insect->bg_type = aINS_BG_CHECK_TYPE_REG_NO_ATTR;

    switch (insect->type) {
        case aINS_INSECT_TYPE_LADYBUG:
            insect->item = ITM_INSECT24;
            break;
        case aINS_INSECT_TYPE_SPOTTED_LADYBUG:
            insect->item = ITM_INSECT25;
            break;
        case aINS_INSECT_TYPE_MANTIS:
            insect->item = ITM_INSECT26;
            break;
        case aINS_INSECT_TYPE_SNAIL:
            insect->item = ITM_INSECT32;
            break;
    }

    if (actorx->actor_specific == aINS_INIT_NORMAL) {
        actorx->world.position.y = 6.0f + mCoBG_GetBgY_OnlyCenter_FromWpos(actorx->world.position, -19.0f);
        actorx->shape_info.draw_shadow = FALSE;
        xyz_t_move(&actorx->home.position, &actorx->world.position);
// Aus stores the spawn unit in work variables
#if VERSION >= VER_GAFU01_00
        mFI_Wpos2UtNum(&insect->s32_work0, &insect->s32_work3, actorx->world.position);
#endif
        action = aITT_ACT_WAIT;
    } else {
        // aINS_INIT_RELEASE
        switch (insect->type) {
            case aINS_INSECT_TYPE_SNAIL:
                actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos(actorx->world.position, 0.0f);
                actorx->home.position.y = actorx->world.position.y;
                action = aITT_ACT_LET_ESCAPE_MAIMAI;
                break;
            default:
                action = aITT_ACT_LET_ESCAPE;
                break;
        }
    }

    aITT_setupAction(insect, action, game);
}

/**
 * Updates the insect's animation cycle.
 *
 * @param insect Insect actor to animate
 */
static void aITT_anime_proc(aINS_INSECT_ACTOR* insect) {
    insect->_1E0 += 0.5f;
    if (insect->_1E0 >= 2.0f) {
        insect->_1E0 -= 2.0f;
    }
}

/**
 * Checks if a ball is near enough to scare the insect.
 *
 * @param actorx Actor to check
 * @return TRUE if ball is within scare range
 */
static int aITT_check_ball(ACTOR* actorx) {
    int ret = FALSE;
    f32 dx = Common_Get(ball_pos).x - actorx->world.position.x;
    f32 dz = Common_Get(ball_pos).z - actorx->world.position.z;

    if (SQ(dx) + SQ(dz) < SQ(aITT_BALL_SCARE_DIST)) {
        ret = TRUE;
    }

    return ret;
}

/**
 * Checks if player's net is near enough to scare the insect.
 *
 * @param actorx Actor to check
 * @return TRUE if net is within scare range
 */
static int aITT_check_player_net(ACTOR* actorx) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    xyz_t net_pos;
    int ret = FALSE;

    if (mPlib_Check_StopNet(&net_pos) == TRUE) {
        uintptr_t catch_label = mPlib_Get_item_net_catch_label();

        if (catch_label != (uintptr_t)actorx) {
            f32 dx = net_pos.x - actorx->world.position.x;
            f32 dz = net_pos.z - actorx->world.position.z;

            if (SQ(dx) + SQ(dz) < SQ(aITT_NET_SCARE_DIST)) {
                ret = TRUE;
            }
        }
    }

    return ret;
}

/**
 * Checks if player's scoop is near enough to scare the insect.
 *
 * @param actorx Actor to check
 * @return TRUE if scoop is within scare range
 */
static int aITT_check_player_scoop(ACTOR* actorx) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    xyz_t scoop_pos;
    int ret = FALSE;

    if (mPlib_Check_DigScoop(&scoop_pos) == TRUE) {
        f32 dx = scoop_pos.x - actorx->world.position.x;
        f32 dz = scoop_pos.z - actorx->world.position.z;

        if (SQ(dx) + SQ(dz) < SQ(aITT_SCOOP_SCARE_DIST)) {
            ret = TRUE;
        }
    }

    return ret;
}

/**
 * Checks if the insect is on a flower.
 *
 * @param actorx Actor to check
 * @return TRUE if on a flower, FALSE otherwise
 */
static int aITT_check_flower(ACTOR* actorx) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    mActor_name_t* fg_p = mFI_GetUnitFG(actorx->world.position);
    int ret = TRUE;

    if (fg_p != NULL && !IS_ITEM_FLOWER(*fg_p)) {
        ret = FALSE;
    }

    return ret;
}

/**
 * Checks various conditions that might scare the insect.
 *
 * @param actorx Actor to check
 * @param game Current game context
 * @return TRUE if insect should be scared
 */
static int aITT_check_patience(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int ret = FALSE;

    switch (insect->type) {
        case aINS_INSECT_TYPE_SNAIL:
            if (aITT_check_flower(actorx) == FALSE) {
                aITT_setupAction(insect, aITT_ACT_AVOID_MAIMAI, game);
                insect->target_speed = 0.1f;
                insect->speed_step = 0.025f;
                ret = TRUE;
            }
            break;
        default:
            if (aITT_check_ball(actorx) == TRUE) {
                insect->patience = 100.0f;
            } else if (aITT_check_player_net(actorx) == TRUE) {
                insect->patience = 100.0f;
            } else if (aITT_check_player_scoop(actorx) == TRUE) {
                insect->patience = 100.0f;
// Aus version checks if the insect is in a unit without a flower
#if VERSION >= VER_GAFU01_00
            } else if (aITT_check_flower(actorx) == FALSE) {
                insect->patience = 100.0f;
#endif
            }

            if (insect->patience > 90.0f) {
                aITT_setupAction(insect, aITT_ACT_AVOID, game);
                ret = TRUE;
            }
            break;
    }

    return ret;
}

/**
 * Calculates new direction angles when colliding with walls.
 *
 * @param actorx Actor to update
 */
static void aITT_calc_direction_angl(ACTOR* actorx) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (actorx->bg_collision_check.result.hit_wall & mCoBG_HIT_WALL_FRONT) {
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

    chase_angle(&actorx->shape_info.rotation.y, actorx->world.angle.y, 0x800);
}

/**
 * Avoid behavior when scared by player.
 */
static void aITT_avoid(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    f32 gravity;
    
    aITT_anime_proc(insect);
    gravity = actorx->gravity;
    gravity *= 1.1f;
    if (gravity > 12.0f) {
        gravity = 12.0f;
    }
    actorx->gravity = gravity;

    switch (insect->type) {
        case aINS_INSECT_TYPE_LADYBUG:
        case aINS_INSECT_TYPE_SPOTTED_LADYBUG:
        case aINS_INSECT_TYPE_MANTIS:
            sAdo_OngenPos((uintptr_t)actorx, NA_SE_26, &actorx->world.position);
            break;
    }
}

/**
 * Special avoid behavior for snails.
 */
static void aITT_avoid_maimai(ACTOR* actorx, GAME* game) {
    aITT_calc_direction_angl(actorx);
}

/**
 * Normal movement behavior between flowers.
 */
static void aITT_move(ACTOR* actorx, GAME* game) {
    static int ref_angl[] = {
        // clang-format off
        DEG2SHORT_ANGLE2(0.0f),
        DEG2SHORT_ANGLE2(90.0f),
        DEG2SHORT_ANGLE2(-90.0f),
        DEG2SHORT_ANGLE2(0.0f),
        DEG2SHORT_ANGLE2(0.0f),
        DEG2SHORT_ANGLE2(45.0f),
        DEG2SHORT_ANGLE2(-45.0f),
        DEG2SHORT_ANGLE2(0.0f),
        DEG2SHORT_ANGLE2(180.0f),
        DEG2SHORT_ANGLE2(135.0f),
        DEG2SHORT_ANGLE2(-135.0f),
        DEG2SHORT_ANGLE2(180.0f),
        DEG2SHORT_ANGLE2(90.0f),
        DEG2SHORT_ANGLE2(90.0f),
        DEG2SHORT_ANGLE2(-90.0f),
        DEG2SHORT_ANGLE2(0.0f),
        // clang-format on
    };

    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (aITT_check_patience(actorx, game) == FALSE) {
        if (insect->timer <= 0) {
            aITT_setupAction(insect, aITT_ACT_WAIT, game);
        } else {
            f32 dx;
            f32 dz;
            int collision;
            s16 step;

            insect->timer--;
            dx = actorx->world.position.x - actorx->home.position.x;
            dz = actorx->world.position.z - actorx->home.position.z;
            collision = 0;
            if (ABS(dx) >= 15.0f) {
                if (dx < 0.0f) {
                    actorx->world.position.x = actorx->home.position.x - 14.0f;
                    collision = 1;
                } else {
                    actorx->world.position.x = actorx->home.position.x + 14.0f;
                    collision = 2;
                }
            }

            if (ABS(dz) >= 15.0f) {
                if (dz < 0.0f) {
                    actorx->world.position.z = actorx->home.position.z - 14.0f;
                    collision |= 4;
                } else {
                    actorx->world.position.z = actorx->home.position.z + 14.0f;
                    collision |= 8;
                }
            }

            actorx->world.position.y = 6.0f + mCoBG_GetBgY_OnlyCenter_FromWpos(actorx->world.position, -19.0f);
            if (collision != 0) {
                aITT_TARGET_ANGLE(insect) = ref_angl[collision];
                aITT_TURN_DELAY(insect) = 10;
                insect->speed_step = 0.0f;
                actorx->speed = 0.0f;
            } else if (actorx->world.angle.y == aITT_TARGET_ANGLE(insect)) {
                aITT_TARGET_ANGLE(insect) = actorx->world.angle.y + (int)(RANDOM_CENTER_F(2.0f) * DEG2SHORT_ANGLE2(90.0f));
            }

            step = 0x600;
            if (insect->type == aINS_INSECT_TYPE_SNAIL) {
                step = 0x180;
            }

            chase_angle(&actorx->world.angle.y, aITT_TARGET_ANGLE(insect), step);
            actorx->shape_info.rotation.y = actorx->world.angle.y;

            if (aITT_TURN_DELAY(insect) == 0) {
                insect->speed_step = 0.1f;
            } else {
                aITT_TURN_DELAY(insect)--;
            }
        }
    }
}

/**
 * Waiting behavior while on flowers.
 */
static void aITT_wait(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (aITT_check_patience(actorx, game) == FALSE) {
        if (insect->timer <= 0) {
            aITT_setupAction(insect, aITT_ACT_MOVE, game);
        } else {
            insect->timer--;
        }
    }
}

/**
 * Initializes avoid state parameters.
 */
static void aITT_avoid_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->life_time = 0;
    insect->alpha_time = 80;
    insect->tools_actor.actor_class.speed = 4.0f;
    insect->tools_actor.actor_class.max_velocity_y = 12.0f;
    insect->tools_actor.actor_class.gravity = 0.06f;
    insect->tools_actor.actor_class.shape_info.rotation.x = 0;

    {
        ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);

        if (playerx != NULL) {
            insect->tools_actor.actor_class.shape_info.rotation.y = insect->tools_actor.actor_class.world.angle.y = playerx->shape_info.rotation.y + (s16)RANDOM_CENTER_F(DEG2SHORT_ANGLE2(120.0f));
        }
    }

    insect->tools_actor.actor_class.shape_info.draw_shadow = TRUE;
    insect->insect_flags.bit_1 = TRUE;
    insect->insect_flags.bit_2 = TRUE;
}

/**
 * Initializes snail-specific avoid parameters.
 */
static void aITT_avoid_maimai_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    aITT_avoid_init(insect, game);
    insect->tools_actor.actor_class.gravity = 2.0f;
    insect->tools_actor.actor_class.max_velocity_y = -20.0f;
    insect->tools_actor.actor_class.speed = 0.2f;
    insect->target_speed = 0.2f;
    insect->speed_step = 0.05f;
    insect->insect_flags.bit_4 = FALSE;
}

/**
 * Initializes movement state parameters.
 */
static void aITT_move_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    insect->timer = ((90 + (int)(play->game_frame % 60)) * 2.0f);
    aITT_TURN_DELAY(insect) = 0;
    insect->target_speed = 0.4f;
    insect->speed_step = 0.1f;

    if (insect->type == aINS_INSECT_TYPE_SNAIL) {
        insect->target_speed *= 0.25f;
        insect->speed_step *= 0.25f;
    }
}

/**
 * Initializes waiting state parameters.
 */
static void aITT_wait_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->timer = (90 + RANDOM_F(90.0f)) * 2.0f;
    insect->tools_actor.actor_class.speed = 0.0f;
    insect->speed_step = 0.0f;
}

typedef void (*aITT_INIT_PROC)(aINS_INSECT_ACTOR* insect, GAME* game);

/**
 * Sets up a new action state for the insect.
 *
 * @param insect Insect to update
 * @param action New action to perform
 * @param game Current game context
 */
static void aITT_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game) {
    static aITT_INIT_PROC init_proc[] = {
        aITT_avoid_init,
        aITT_avoid_maimai_init,
        aITT_avoid_init,
        aITT_avoid_maimai_init,
        aITT_move_init,
        aITT_wait_init,
    };

    static aINS_ACTION_PROC act_proc[] = {
        aITT_avoid,
        aITT_avoid_maimai,
        aITT_avoid,
        aITT_avoid_maimai,
        aITT_move,
        aITT_wait,
    };

    insect->action = action;
    insect->action_proc = act_proc[action];
    (*init_proc[action])(insect, game);
}

/**
 * Main movement update function for flower-based insect actors.
 *
 * @param actorx Actor to update
 * @param game Current game context
 */
static void aITT_actor_move(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    uintptr_t catch_label = mPlib_Get_item_net_catch_label();

    if (catch_label == (uintptr_t)actorx) {
        // @BUG - They forgot to make a separate case for the snail,
        // so it uses the ladybug/spotted ladybug/mantis let escape behavior.
        // This was fixed in the Australian release.
        // Aus version fixes this!
#if !defined(BUGFIXES) && VERSION < VER_GAFU01_00
        aITT_setupAction(insect, aITT_ACT_LET_ESCAPE, game);
#else
        int action;

        switch (insect->type) {
            case aINS_INSECT_TYPE_SNAIL:
                actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos(actorx->world.position, 0.0f);
                actorx->home.position.y = actorx->world.position.y;
                action = aITT_ACT_LET_ESCAPE_MAIMAI;
                break;
            default:
                action = aITT_ACT_LET_ESCAPE;
                break;
        }

        aITT_setupAction(insect, action, game);
#endif
    } else if (insect->insect_flags.bit_3 == TRUE && insect->insect_flags.bit_2 == FALSE) {
        aITT_setupAction(insect, aITT_ACT_LET_ESCAPE, game);
    } else {
        insect->action_proc(actorx, game);
    }
}
