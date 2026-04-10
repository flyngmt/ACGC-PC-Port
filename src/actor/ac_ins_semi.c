/**
 * @file ac_ins_semi.c
 * @brief Implements cicada and bee actor behaviors.
 * 
 * This file handles cicadas (semi) and bee actors, including their initialization,
 * movement patterns, and reactions to player actions. These insects typically stay
 * stationary on trees until disturbed, at which point they escape.
 */

#include "ac_ins_semi.h"

#include "m_name_table.h"
#include "m_common_data.h"
#include "m_player_lib.h"

enum {
    aISM_ACT_AVOID,
    aISM_ACT_LET_ESCAPE,
    aISM_ACT_WAIT,

    aISM_ACT_NUM
};

// Cicada variables
#define aISM_CRY_TIMER 60 // Frames between cicada cries
#define aISM_BALL_SCARE_DIST 60.0f // Distance threshold for cicada to be scared by ball
#define aISM_NET_SCARE_DIST 70.0f // Distance threshold for cicada to be scared by net
#define aISM_SCOOP_SCARE_DIST 30.0f // distance threshold for cicada to be scared by scoop
#define aISM_AXE_SCARE_DIST 150.0f // Distance threshold for cicada to be scared by axe

// Cicada-specific work variables
#define aISM_IS_CAUGHT(ins) ((ins)->s32_work0)

static void aISM_actor_move(ACTOR* actorx, GAME* game);

static void aISM_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game);

/**
 * Initializes a cicada or bee actor.
 * Sets up initial position, type-specific properties and starting action.
 *
 * @param actorx Actor to initialize
 * @param game Current game context
 */
extern void aISM_actor_init(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int action;

    actorx->mv_proc = &aISM_actor_move;
    switch (insect->type) {
        case aINS_INSECT_TYPE_ROBUST_CICADA:
            insect->item = ITM_INSECT04;
            break;
        case aINS_INSECT_TYPE_WALKER_CICADA:
            insect->item = ITM_INSECT05;
            break;
        case aINS_INSECT_TYPE_EVENING_CICADA:
            insect->item = ITM_INSECT06;
            break;
        case aINS_INSECT_TYPE_BROWN_CICADA:
            insect->item = ITM_INSECT07;
            break;
        case aINS_INSECT_TYPE_BEE: // why is bee here?
            insect->item = ITM_INSECT08;
            break;
    }

    if (actorx->actor_specific == 0) {
        static f32 init_posY[] = { 35.0f, 30.0f };
        static f32 init_posZ[] = { -2.0f, 8.0f };
        mActor_name_t* fg_p = mFI_GetUnitFG(actorx->world.position);
        int idx;

        // @BUG - devs forgot to check for the item variants of the cedar tree.
        // This causes the 'invisible bug' glitch.
#ifndef BUGFIXES
        if (fg_p != NULL && *fg_p == CEDAR_TREE) {
#else
        if (fg_p != NULL && (*fg_p == CEDAR_TREE || *fg_p == CEDAR_TREE_BELLS || *fg_p == CEDAR_TREE_FTR || *fg_p == CEDAR_TREE_BEES || *fg_p == CEDAR_TREE_LIGHTS)) {
#endif
            idx = 1;
        } else {
            idx = 0;
        }

        actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, -init_posY[idx]);
        actorx->world.position.z += init_posZ[idx];
        xyz_t_move(&actorx->home.position, &actorx->world.position);
        actorx->shape_info.draw_shadow = FALSE;
        actorx->shape_info.rotation.x = DEG2SHORT_ANGLE2(90.0f);
        action = aISM_ACT_WAIT;
    } else {
        // cicada was released
        if (insect->type != aINS_INSECT_TYPE_BEE) {
            sAdo_OngenTrgStart(NA_SE_SEMI_ESCAPE, &actorx->world.position);
        }

        action = aISM_ACT_LET_ESCAPE;
    }

    aISM_setupAction(insect, action, game);
}

/**
 * Processes animation updates for the insect.
 * Updates the animation cycle timer.
 *
 * @param insect Insect actor to animate
 */
static void aISM_anime_proc(aINS_INSECT_ACTOR* insect) {
    insect->_1E0 += 0.5f;
    if (insect->_1E0 >= 2.0f) {
        insect->_1E0 -= 2.0f;
    }
}

/**
 * Checks if a ball is near the insect.
 *
 * @param actorx Actor to check
 * @return TRUE if ball is within range
 */
static int aISM_check_ball(ACTOR* actorx) {
    int ret = FALSE;
    f32 dx = Common_Get(ball_pos).x - actorx->world.position.x;
    f32 dz = Common_Get(ball_pos).z - actorx->world.position.z;

    if (SQ(dx) + SQ(dz) < SQ(aISM_BALL_SCARE_DIST)) {
        ret = TRUE;
    }

    return ret;
}

/**
 * Checks if the player's net is near or hitting the insect.
 *
 * @param actorx Actor to check
 * @return TRUE if net is within range
 */
static int aISM_check_player_net(ACTOR* actorx) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    xyz_t net_pos;
    int ret = FALSE;

    if (mPlib_Check_StopNet(&net_pos) == TRUE) {
        uintptr_t catch_label = mPlib_Get_item_net_catch_label();

        if (catch_label == (uintptr_t)actorx) {
            aISM_IS_CAUGHT(insect) = TRUE;
        } else {
            f32 dx = net_pos.x - actorx->world.position.x;
            f32 dz = net_pos.z - actorx->world.position.z;

            if (SQ(dx) + SQ(dz) < SQ(aISM_NET_SCARE_DIST)) {
                ret = TRUE;
            }
        }
    }

    return ret;
}

/**
 * Checks if the player's scoop is near the insect.
 *
 * @param actorx Actor to check
 * @return TRUE if scoop is within range
 */
static int aISM_check_player_scoop(ACTOR* actorx) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    xyz_t scoop_pos;
    int ret = FALSE;

    if (mPlib_Check_DigScoop(&scoop_pos) == TRUE) {
        f32 dx = scoop_pos.x - actorx->world.position.x;
        f32 dz = scoop_pos.z - actorx->world.position.z;

        if (SQ(dx) + SQ(dz) < SQ(aISM_SCOOP_SCARE_DIST)) {
            ret = TRUE;
        }
    }

    return ret;
}

/**
 * Checks various conditions that affect the insect's patience.
 * Includes tree shaking, vibrations, nearby items, and tools.
 *
 * @param actorx Actor to check
 * @return TRUE if patience threshold exceeded
 */
static int aISM_check_patience(ACTOR* actorx) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int ret = FALSE;

    if (mPlib_Check_tree_shaken(&actorx->world.position) == TRUE) {
        insect->patience = 100.0f;
    } else if (mPlib_Check_VibUnit_OneFrame(&actorx->world.position) == TRUE && actorx->player_distance_xz < aISM_AXE_SCARE_DIST) {
        insect->patience = 100.0f;
    } else if (aISM_check_ball(actorx) == TRUE) {
        insect->patience = 100.0f;
    } else if (aISM_check_player_net(actorx) == TRUE) {
        insect->patience = 100.0f;
    } else if (aISM_check_player_scoop(actorx) == TRUE) {
        insect->patience = 100.0f;
    }

    if (insect->patience > 90.0f) {
        ret = TRUE;
    }

    return ret;
}

/**
 * Avoidance behavior when insect is disturbed.
 * Handles escape movement and sounds.
 *
 * @param actorx Actor performing avoidance
 * @param game Current game context
 */
static void aISM_avoid(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    f32 gravity;

    aISM_anime_proc(insect);
    
    gravity = actorx->gravity;
    gravity *= 1.1f;
    if (gravity > 12.0f) {
        gravity = 12.0f;
    }
    actorx->gravity = gravity;

    if (insect->bg_type == aINS_BG_CHECK_TYPE_NONE) {
        int home_ux;
        int home_uz;
        int cur_ux;
        int cur_uz;

        mFI_Wpos2UtNum(&home_ux, &home_uz, actorx->home.position);
        mFI_Wpos2UtNum(&cur_ux, &cur_uz, actorx->world.position);
        if (home_ux != cur_ux || home_uz != cur_uz) {
            insect->bg_type = aINS_BG_CHECK_TYPE_REG_NO_ATTR;
        }
    }

    if (insect->type == aINS_INSECT_TYPE_BEE) {
        sAdo_OngenPos((uintptr_t)actorx, NA_SE_26, &actorx->world.position);
    }
}

/**
 * Waiting behavior for stationary insect.
 * Handles sound effects and checks for disturbances.
 *
 * @param actorx Actor in waiting state
 * @param game Current game context
 */
static void aISM_wait(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (aISM_check_patience(actorx) == TRUE) {
        if (insect->type != aINS_INSECT_TYPE_BEE) {
            sAdo_OngenTrgStart(NA_SE_SEMI_ESCAPE, &actorx->world.position);
        }

        aISM_setupAction(insect, aISM_ACT_AVOID, game);
    } else {
        if (insect->type != aINS_INSECT_TYPE_BEE && aISM_IS_CAUGHT(insect) == FALSE) {
            if (insect->patience < 50.0f) {
                insect->timer--;
                if (Common_Get(weather) != mEnv_WEATHER_RAIN && insect->timer < 0) {
                    static u8 semi_sound_data[] = { NA_SE_SEMI3_CRY, NA_SE_SEMI2_CRY, NA_SE_SEMI1_CRY, NA_SE_SEMI0_CRY };
                    int semi_idx = insect->type - aINS_INSECT_TYPE_ROBUST_CICADA;

                    insect->timer = 0;
                    sAdo_OngenPos((uintptr_t)actorx, semi_sound_data[semi_idx], &actorx->world.position);
                    actorx->world.position.x = actorx->home.position.x + RANDOM_F(0.4f);
                }
            } else {
                insect->timer = aISM_CRY_TIMER;
            }
        }
    }
}

/**
 * Initializes avoidance behavior parameters.
 *
 * @param insect Insect to initialize
 * @param game Current game context
 */
static void aISM_avoid_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    static f32 base_angl[] = { -DEG2SHORT_ANGLE2(22.5f), DEG2SHORT_ANGLE2(22.5f) };
    f32 rand = fqrand();

    insect->life_time = 0;
    insect->alpha_time = 80;
    insect->tools_actor.actor_class.speed = 4.0f;
    insect->tools_actor.actor_class.max_velocity_y = 12.0f;
    insect->tools_actor.actor_class.gravity = 0.06f;
    insect->tools_actor.actor_class.shape_info.rotation.x = 0;

    if (insect->action == aISM_ACT_AVOID) {
        insect->tools_actor.actor_class.shape_info.rotation.y = (rand * DEG2SHORT_ANGLE2(90.0f) - DEG2SHORT_ANGLE2(45.0f)) + base_angl[rand >= 0.5f];
        insect->tools_actor.actor_class.world.angle.y = insect->tools_actor.actor_class.shape_info.rotation.y;
    } else {
        ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);

        if (playerx != NULL) {
            insect->tools_actor.actor_class.shape_info.rotation.y = insect->tools_actor.actor_class.world.angle.y = playerx->shape_info.rotation.y + (s16)RANDOM_CENTER_F(DEG2SHORT_ANGLE2(120.0f));
        }
    }

    insect->insect_flags.bit_1 = TRUE;
    insect->tools_actor.actor_class.shape_info.draw_shadow = TRUE;
}

/**
 * Initializes escape behavior parameters.
 *
 * @param insect Insect to initialize
 * @param game Current game context
 */
static void aISM_let_escape_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    aISM_avoid_init(insect, game);
    insect->insect_flags.bit_2 = TRUE;
}

/**
 * Initializes waiting behavior parameters.
 *
 * @param insect Insect to initialize
 * @param game Current game context
 */
static void aISM_wait_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->tools_actor.actor_class.shape_info.rotation.y = DEG2SHORT_ANGLE2(180.0f);
}

typedef void (*aISM_INIT_PROC)(aINS_INSECT_ACTOR* insect, GAME* game);

/**
 * Sets up a new action state for the insect.
 *
 * @param insect Insect to update
 * @param action New action to perform
 * @param game Current game context
 */
static void aISM_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game) {
    static aISM_INIT_PROC init_proc[] = {
        aISM_avoid_init,
        aISM_let_escape_init,
        aISM_wait_init,
    };

    static aINS_ACTION_PROC act_proc[] = {
        aISM_avoid,
        aISM_avoid,
        aISM_wait,
    };

    insect->action = action;
    insect->action_proc = act_proc[action];
    init_proc[action](insect, game);
}

/**
 * Main movement update function for cicada/bee actors.
 * Handles state changes and updates current behavior.
 *
 * @param actorx Actor to update
 * @param game Current game context
 */
static void aISM_actor_move(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* ins = (aINS_INSECT_ACTOR*)actorx;
    uintptr_t catch_label = mPlib_Get_item_net_catch_label();

    if (catch_label == (uintptr_t)ins) {
        aISM_setupAction(ins, aISM_ACT_LET_ESCAPE, game);
    } else if (ins->insect_flags.bit_3 == TRUE && ins->insect_flags.bit_2 == FALSE) {
        aISM_setupAction(ins, aISM_ACT_LET_ESCAPE, game);
    } else {
        ins->action_proc(actorx, game);
    }
}
