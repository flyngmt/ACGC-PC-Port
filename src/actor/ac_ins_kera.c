/**
 * @file ac_ins_kera.c
 * @brief Mole cricket behavior, including hiding, emerging, and escaping.
 */

#include "ac_ins_kera.h"

#include "m_name_table.h"
#include "m_common_data.h"
#include "m_player_lib.h"

// Actor-specific work variables
#define aIKR_AVOID_TIMER(ins) ((ins)->s32_work0)
#define aIKR_UT_X(ins) ((ins)->s32_work1)
#define aIKR_UT_Z(ins) ((ins)->s32_work2)
#define aIKR_SCALE_TOGGLE(ins) ((ins)->s32_work3)

#define aIKR_DIRT_TIMER(ins) ((ins)->f32_work0)
#define aIKR_BK_CENTER_X(ins) ((ins)->f32_work2)
#define aIKR_BK_CENTER_Z(ins) ((ins)->f32_work3)

enum {
    aIKR_ACT_AVOID,
    aIKR_ACT_LET_ESCAPE,
    aIKR_ACT_HIDE,
    aIKR_ACT_APPEAR,
    aIKR_ACT_DIVE,
    aIKR_ACT_DROWN,
    aIKR_ACT_DUG,

    aIKR_ACT_NUM
};

static void aIKR_actor_move(ACTOR* actorx, GAME* game);
static void aIKR_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game);
static void aIKR_set_avoid_player_angl(ACTOR* actorx, GAME* game);

/**
 * Initializes a mole cricket actor.
 *
 * @param actorx Pointer to the actor to initialize.
 * @param game Pointer to the game context.
 */
extern void aIKR_actor_init(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int action;
    
    insect->bg_range = 5.0f;
    insect->item = ITM_INSECT33;
    actorx->mv_proc = aIKR_actor_move;
    insect->insect_flags.bit_4 = FALSE;

    if (actorx->actor_specific == aINS_INIT_NORMAL) {
        int ux;
        int uz;

        // Get center of the block
        mFI_BkNum2WposXZ(&insect->f32_work2, &insect->f32_work3, actorx->block_x, actorx->block_z);
        insect->f32_work2 += mFI_BK_WORLDSIZE_HALF_X_F;
        insect->f32_work3 += mFI_BK_WORLDSIZE_HALF_Z_F;

        // Get unit
        mFI_Wpos2UtNum(&ux, &uz, actorx->world.position);
        insect->ut_x = ux;
        insect->ut_z = uz;
        action = aIKR_ACT_HIDE;
    } else {
        // aINS_INIT_RELEASE
        aIKR_set_avoid_player_angl(actorx, game);
        actorx->drawn = TRUE;
        action = aIKR_ACT_LET_ESCAPE;
    }

    aIKR_setupAction(insect, action, game);
}

/**
 * Sets the angle of the cricket so it avoids the player's direction.
 *
 * @param actorx Pointer to the mole cricket actor.
 * @param game Pointer to the game context.
 */
static void aIKR_set_avoid_player_angl(ACTOR* actorx, GAME* game) {
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);

    if (playerx != NULL) {
        actorx->shape_info.rotation.y = actorx->world.angle.y = playerx->shape_info.rotation.y + (s16)RANDOM_CENTER_F(DEG2SHORT_ANGLE2(120.0f));
    }
}

/**
 * Calculates scale changes to simulate breathing/movement.
 * Toggles scale growth direction using s32_work3.
 *
 * @param actorx Pointer to the mole cricket actor.
 */
static void aIKR_calc_move_scale(ACTOR* actorx) {
    static f32 target_table[] = { 0.008f, 0.01f };
    static f32 drt_table[] = { -1.0f, 1.0f };
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    f32 target;
    f32 scale;
    f32 drt;

    drt = drt_table[aIKR_SCALE_TOGGLE(insect)];
    scale = actorx->scale.z;
    scale += (drt * 0.002f) * 0.5f;
    target = target_table[aIKR_SCALE_TOGGLE(insect)];
    if (drt * (target - scale) <= 0.0f) {
        aIKR_SCALE_TOGGLE(insect) = (aIKR_SCALE_TOGGLE(insect) ^ 1) & 1;
        scale = target;
    }

    actorx->scale.y = scale;
    actorx->scale.z = scale;
}

/**
 * Checks if the player's shovel or scoop is digging near the cricket.
 *
 * @param actorx Pointer to the mole cricket actor.
 * @return TRUE if scooping in the same tile, FALSE otherwise.
 */
static int aIKR_check_dig_hole_scoop(ACTOR* actorx) {
    int ret = FALSE;

    if (CLIP(insect_clip)->pl_action == aINS_PL_ACT_DIG_SCOOP) {
        int ux;
        int uz;

        mFI_Wpos2UtNum(&ux, &uz, actorx->world.position);
        if (CLIP(insect_clip)->pl_action_ut_x == ux && CLIP(insect_clip)->pl_action_ut_z == uz) {
            ret = TRUE;
        }
    }

    return ret;
}

/**
 * Determines whether the cricket is within its active range from a center point.
 *
 * @param actorx Pointer to the mole cricket actor.
 * @return FALSE if out of range, TRUE otherwise.
 */
static int aIKR_chk_active_range(ACTOR* actorx) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    f32 dx = aIKR_BK_CENTER_X(insect) - actorx->world.position.x;
    f32 dz = aIKR_BK_CENTER_Z(insect) - actorx->world.position.z;
    int ret = TRUE;
    
    if (SQ(dx) + SQ(dz) >= SQ(400.0f)) {
        ret = FALSE;
    }

    return ret;
}

/**
 * Checks for water attributes to see if diving is needed.
 *
 * @param actorx Pointer to the mole cricket actor.
 * @return TRUE if water is directly ahead, FALSE otherwise.
 */
static int aIKR_chk_water_attr(ACTOR* actorx) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int ret = FALSE;

    if (actorx->bg_collision_check.result.on_ground) {
        xyz_t pos = actorx->world.position;
        f32 range = insect->bg_range + actorx->speed;
        s16 angleY = actorx->world.angle.y;

        pos.x += range * sin_s(angleY);
        pos.z += range * cos_s(angleY);
        if (mCoBG_CheckWaterAttribute(mCoBG_Wpos2BgAttribute_Original(pos))) {
            ret = TRUE;
        }
    }

    return ret;
}

/**
 * Reorients the cricket if a wall collision is detected.
 *
 * @param actorx Pointer to the mole cricket actor.
 */
static void aIKR_calc_direction_angl(ACTOR* actorx) {
    s16 step;

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
 * Allows the mole cricket to avoid the player or obstacles.
 * Adjusts speed periodically, checks for water or out-of-range conditions.
 *
 * @param actorx Pointer to the mole cricket actor.
 * @param game Pointer to the current game state.
 */
static void aIKR_avoid(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    
    chase_angle(&actorx->shape_info.rotation.x, 0, 0x1000);
    aIKR_AVOID_TIMER(insect)--;
    if (aIKR_AVOID_TIMER(insect) <= 0) {
        insect->target_speed = (1.1f - RANDOM_F(0.2f)) * 1.5f;
        aIKR_AVOID_TIMER(insect) = 10;
    }

    aIKR_calc_move_scale(actorx);
    if (aIKR_chk_water_attr(actorx) == TRUE) {
        aIKR_setupAction(insect, aIKR_ACT_DIVE, game);
    } else if (aIKR_chk_active_range(actorx) == FALSE) {
        int action;

        if (mCoBG_CheckHole_OrgAttr(mCoBG_Wpos2Attribute(actorx->world.position, NULL)) == TRUE) {
            action = aIKR_ACT_DUG;
        } else {
            action = aIKR_ACT_LET_ESCAPE;
        }

        aIKR_setupAction(insect, action, game);
    } else {
        if (insect->bg_type == aINS_BG_CHECK_TYPE_NO_UNIT_COLUMN_NO_ATTR) {
            int ux;
            int uz;

            mFI_Wpos2UtNum(&ux, &uz, actorx->world.position);
            if (insect->ut_x != ux || insect->ut_z != uz) {
                insect->bg_type = aINS_BG_CHECK_TYPE_REG_NO_ATTR;
            }
        }

        aIKR_calc_direction_angl(actorx);
        sAdo_OngenPos((uintptr_t)actorx, NA_SE_MOLE_CRICKET_OUT, &actorx->world.position);
    }
}

/**
 * Lets the mole cricket escape freely, checking if it should dive.
 *
 * @param actorx Pointer to the mole cricket actor.
 * @param game Pointer to the current game state.
 */
static void aIKR_let_escape(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    aIKR_calc_move_scale(actorx);
    if (aIKR_chk_water_attr(actorx) == TRUE) {
        aIKR_setupAction(insect, aIKR_ACT_DIVE, game);
    } else {
        aIKR_calc_direction_angl(actorx);
        sAdo_OngenPos((uintptr_t)actorx, NA_SE_MOLE_CRICKET_OUT, &actorx->world.position);
    }
}

/**
 * Keeps the mole cricket hidden until has been dug up.
 *
 * @param actorx Pointer to the mole cricket actor.
 * @param game Pointer to the current game state.
 */
static void aIKR_hide(ACTOR* actorx, GAME* game) {
    if (aIKR_check_dig_hole_scoop(actorx) == TRUE) {
        int i;

        aIKR_set_avoid_player_angl(actorx, game);
        aIKR_setupAction((aINS_INSECT_ACTOR*)actorx, aIKR_ACT_APPEAR, game);
        for (i = 3; i < 6; i++) {
            eEC_CLIP->effect_make_proc(eEC_EFFECT_DIG_MUD, actorx->world.position, 2, actorx->shape_info.rotation.y, game, RSV_NO, 0, 0x4000 | i);
        }
    } else {
        sAdo_OngenPos((uintptr_t)actorx, NA_SE_MOLE_CRICKET_HIDE, &actorx->world.position);
    }
}

/**
 * Manages the mole cricket emerging from underground.
 *
 * @param actorx Pointer to the mole cricket actor.
 * @param game Pointer to the current game state.
 */
static void aIKR_appear(ACTOR* actorx, GAME* game) {
    actorx->shape_info.rotation.x = atans_table(actorx->speed, -actorx->position_speed.y);
    if (actorx->bg_collision_check.result.on_ground) {
        aIKR_setupAction((aINS_INSECT_ACTOR*)actorx, aIKR_ACT_AVOID, game);
    }
}

/**
 * Controls the cricket's dive into water and detects submersion depth.
 *
 * @param actorx Pointer to the mole cricket actor.
 * @param game Pointer to the current game state.
 */
static void aIKR_dive(ACTOR* actorx, GAME* game) {
    f32 water_y = mCoBG_GetWaterHeight_File(actorx->world.position, __FILE__, 541);

    actorx->shape_info.rotation.x = atans_table(actorx->speed, -actorx->position_speed.y);
    if (actorx->world.position.y <= water_y) {
        aIKR_setupAction((aINS_INSECT_ACTOR*)actorx, aIKR_ACT_DROWN, game);
    }
}

/**
 * Handles movements after the cricket has dug underground.
 * Continues until it times out or re-emerges.
 *
 * @param actorx Pointer to the mole cricket actor.
 * @param game Pointer to the current game state.
 */
static void aIKR_dug(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    aIKR_calc_move_scale(actorx);
    aIKR_DIRT_TIMER(insect) -= 0.5f;
    if (aIKR_DIRT_TIMER(insect) <= 0.0f) {
        int type = 3.0f + RANDOM_F(3.0f);

        eEC_CLIP->effect_make_proc(eEC_EFFECT_DIG_MUD, actorx->world.position, 2, actorx->shape_info.rotation.y, game, RSV_NO, 0, 0x4000 | type);
        aIKR_DIRT_TIMER(insect) = 6.0f;
    }

    chase_angle(&actorx->shape_info.rotation.x, DEG2SHORT_ANGLE2(157.5f), 0x300);
    sAdo_OngenPos((uintptr_t)actorx, NA_SE_MOLE_CRICKET_OUT, &actorx->world.position);
}

/**
 * Initializes the avoid action, setting initial speed.
 *
 * @param insect Pointer to the insect actor context.
 * @param game Pointer to the game state.
 */
static void aIKR_avoid_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->target_speed = 1.5f;
    insect->speed_step = 0.3f;
    insect->tools_actor.actor_class.shape_info.rotation.x = 0;
}

/**
 * Initializes the escape action, enabling gravity and slowly fading out the insect.
 *
 * @param insect Pointer to the insect actor context.
 * @param game Pointer to the game state.
 */
static void aIKR_let_escape_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->life_time = 0;
    insect->alpha_time = 80;
    insect->tools_actor.actor_class.gravity = 1.0f;
    insect->tools_actor.actor_class.max_velocity_y = -20.0f;
    aIKR_avoid_init(insect, game);
    insect->bg_type = aINS_BG_CHECK_TYPE_REG_NO_ATTR;
    insect->tools_actor.actor_class.shape_info.rotation.x = 0;
    insect->insect_flags.bit_1 = TRUE;
    insect->insect_flags.bit_2 = TRUE;
}

/**
 * Initializes the hidden state, making the actor invisible.
 *
 * @param insect Pointer to the insect actor context.
 * @param game Pointer to the game state.
 */
static void aIKR_hide_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    mFI_Wpos2UtNum(&aIKR_UT_X(insect), &aIKR_UT_Z(insect), insect->tools_actor.actor_class.world.position);
    insect->tools_actor.actor_class.drawn = FALSE;
}

/**
 * Initializes the emerging state with upward speed.
 *
 * @param insect Pointer to the insect actor context.
 * @param game Pointer to the game state.
 */
static void aIKR_appear_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->target_speed = 1.5f;
    insect->speed_step = 0.3f;
    insect->tools_actor.actor_class.speed = 1.5f;
    insect->tools_actor.actor_class.gravity = 1.0f;
    insect->tools_actor.actor_class.max_velocity_y = -20.0f;
    insect->tools_actor.actor_class.position_speed.y = 5.0f;
    insect->tools_actor.actor_class.drawn = TRUE;
    insect->bg_type = aINS_BG_CHECK_TYPE_NO_UNIT_COLUMN_NO_ATTR;
}

/**
 * Initializes the dive into water with vertical speed.
 *
 * @param insect Pointer to the insect actor context.
 * @param game Pointer to the game state.
 */
static void aIKR_dive_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->target_speed = 1.5f;
    insect->speed_step = 0.3f;
    insect->tools_actor.actor_class.speed = insect->target_speed;
    insect->tools_actor.actor_class.position_speed.y = 8.0f;
    insect->insect_flags.bit_1 = TRUE;
}

/**
 * Initializes the drowning state, removing the actor from play.
 *
 * @param insect Pointer to the insect actor context.
 * @param game Pointer to the game state.
 */
static void aIKR_drown_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    xyz_t pos = insect->tools_actor.actor_class.world.position;

    pos.y = mCoBG_GetWaterHeight_File(pos, __FILE__, 712);
    eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_MIZU, pos, 1, insect->tools_actor.actor_class.world.angle.y, game, EMPTY_NO, 4, 0);
    sAdo_OngenTrgStart(NA_SE_438, &insect->tools_actor.actor_class.world.position);
    insect->insect_flags.bit_1 = TRUE;
    insect->insect_flags.destruct = TRUE;
    insect->tools_actor.actor_class.shape_info.draw_shadow = FALSE;
}

/**
 * Initializes the dug state, limiting the insect's movement.
 *
 * @param insect Pointer to the insect actor context.
 * @param game Pointer to the game state.
 */
static void aIKR_dug_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    xyz_t pos = insect->tools_actor.actor_class.world.position;

    insect->life_time = 0;
    insect->alpha_time = 80;
    insect->tools_actor.actor_class.shape_info.rotation.x = 0;
    insect->bg_type = aINS_BG_CHECK_TYPE_NONE;
    insect->tools_actor.actor_class.gravity = 0.01f;
    insect->tools_actor.actor_class.max_velocity_y = -0.2f;
    insect->tools_actor.actor_class.position_speed.y = 0.0f;
    insect->tools_actor.actor_class.speed = 0.0f;
    insect->target_speed = 0.0f;
    insect->speed_step = 0.0f;
    insect->f32_work0 = 1.0f;
    insect->insect_flags.bit_1 = TRUE;
    insect->insect_flags.bit_2 = TRUE;
    insect->tools_actor.actor_class.shape_info.draw_shadow = FALSE;
}

typedef void (*aIKR_INIT_PROC)(aINS_INSECT_ACTOR* insect, GAME* game);

/**
 * Configures the mole cricket's current action and associated init function.
 *
 * @param insect Pointer to the insect actor context.
 * @param action Which action to transition to.
 * @param game Pointer to the game context.
 */
static void aIKR_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game) {
    static aIKR_INIT_PROC init_proc[] = {
        aIKR_avoid_init,
        aIKR_let_escape_init,
        aIKR_hide_init,
        aIKR_appear_init,
        aIKR_dive_init,
        aIKR_drown_init,
        aIKR_dug_init,
    };

    static aINS_ACTION_PROC act_proc[] = {
        aIKR_avoid,
        aIKR_let_escape,
        aIKR_hide,
        aIKR_appear,
        aIKR_dive,
        (aINS_ACTION_PROC)none_proc1,
        aIKR_dug,
    };

    insect->action = action;
    insect->action_proc = act_proc[action];
    (*init_proc[action])(insect, game);
}

/**
 * Movement/update loop for the mole cricket actor.
 *
 * @param actorx Pointer to the mole cricket actor.
 * @param game Pointer to the current game state.
 */
static void aIKR_actor_move(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    uintptr_t catch_label = mPlib_Get_item_net_catch_label();

    if (catch_label == (uintptr_t)actorx) {
        insect->alpha0 = 255;
        aIKR_setupAction(insect, aIKR_ACT_LET_ESCAPE, game);
    } else {
        insect->action_proc(actorx, game);
    }
}
