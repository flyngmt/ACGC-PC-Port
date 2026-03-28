#include "ac_ins_amenbo.h"

#include "m_field_info.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_player_lib.h"

enum {
    aIAB_ACTION_WAIT,
    aIAB_ACTION_LET_ESCAPE,
    aIAB_ACTION_MOVE,
    aIAB_ACTION_REST,

    aIAB_ACTION_NUM
};

#define aIAB_SCALE(insect) ((insect)->f32_work0)
#define aIAB_SCALE_RATE(insect) ((insect)->f32_work1)
#define aIAB_HIT_WALL(insect) ((insect)->s32_work3)

#define aIAB_RANDOM_ANGLE() ((s16)((fqrand() - 0.5f) * (f32)DEG2SHORT_ANGLE2(120.0f)))

static void aIAB_actor_move(ACTOR* actorx, GAME* game);
static void aIAB_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game);

extern void aIAB_actor_init(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int act;

    if (actorx->actor_specific == 0) {
        actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos(actorx->world.position, -14.0f);
        xyz_t_move(&actorx->home.position, &actorx->world.position);
        insect->bg_type = 2;
        act = aIAB_ACTION_MOVE;
    } else {
        act = aIAB_ACTION_LET_ESCAPE;
    }

    insect->bg_range = mFI_UNIT_BASE_SIZE_F;
    insect->bg_height = -14.0f;
    insect->item = ITM_INSECT34;
    actorx->mv_proc = aIAB_actor_move;
    aIAB_setupAction(insect, act, game);
}

static void aIAB_anime_proc(aINS_INSECT_ACTOR* insect) {
    insect->_1E0 += 0.5f;
    if (insect->_1E0 >= 2.0f) {
        insect->_1E0 -= 2.0f;
    }
}

static void aIAB_BGcheck(aINS_INSECT_ACTOR* insect) {
    if ((insect->tools_actor.actor_class.bg_collision_check.result.hit_wall & mCoBG_HIT_WALL_FRONT) != 0 &&
        aIAB_HIT_WALL(insect) == FALSE) {
        aIAB_HIT_WALL(insect) = TRUE;
    }
}

static void aIAB_make_hamon(ACTOR* actorx, GAME* game) {
    xyz_t ef_pos;
    xyz_t water_flow;
    s16 dir;

    xyz_t_move(&ef_pos, &actorx->world.position);
    ef_pos.y = mCoBG_GetWaterHeight_File(actorx->world.position, __FILE__, 210);
    mCoBG_GetWaterFlow(&water_flow, actorx->bg_collision_check.result.unit_attribute);
    dir = atans_table(water_flow.z, water_flow.x);
    eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, ef_pos, 1, dir, game, EMPTY_NO, 1, 0);
}

static void aIAB_let_escape(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    f32 grav;

    aIAB_anime_proc(insect);
    grav = actorx->gravity;
    grav += grav * 0.1f * 0.5f;
    if (grav > 12.0f) {
        grav = 12.0f;
    }

    actorx->gravity = grav;
    sAdo_OngenPos((uintptr_t)actorx, NA_SE_25, &actorx->world.position);
}

static void aIAB_move(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    f32 scale = aIAB_SCALE(insect);

    chase_f(&aIAB_SCALE_RATE(insect), -0.0021f, 0.00035f);
    scale += aIAB_SCALE_RATE(insect);
    if (scale < 0.0f) {
        scale = 0.0f;
    }

    aIAB_SCALE(insect) = scale;
    actorx->scale.x = 0.01f + scale;
    actorx->scale.y = 0.01f - scale;
    aIAB_BGcheck(insect);

    /* Change to rest action if not moving or if hit a wall */
    if (F32_IS_ZERO(actorx->speed) || aIAB_HIT_WALL(insect) == TRUE) {
        aIAB_setupAction(insect, aIAB_ACTION_REST, game);
    }
}

static void aIAB_rest(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    aIAB_BGcheck(insect);
    insect->timer--;

    /* When timer is 0, move again */
    if (insect->timer <= 0) {
        aIAB_setupAction(insect, aIAB_ACTION_MOVE, game);
    }
}

static void aIAB_let_escape_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player;

    insect->life_time = 0;
    insect->alpha_time = 80;
    insect->tools_actor.actor_class.gravity = 0.06f;
    insect->tools_actor.actor_class.max_velocity_y = 12.0f;
    insect->tools_actor.actor_class.speed = 4.0f;
    insect->tools_actor.actor_class.shape_info.rotation.x = 0;

    player = GET_PLAYER_ACTOR(play);
    if (player != NULL) {
        s16 angleY = player->actor_class.shape_info.rotation.y + aIAB_RANDOM_ANGLE();

        insect->tools_actor.actor_class.world.angle.y = angleY;
        insect->tools_actor.actor_class.shape_info.rotation.y = angleY;
    }

    insect->insect_flags.bit_1 = TRUE;
    insect->insect_flags.bit_2 = TRUE;
}

static void aIAB_move_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;
    s16 angleY = insect->tools_actor.actor_class.world.angle.y;
    s16 newAngle;

    /* Turn around if hit a wall */
    if (aIAB_HIT_WALL(insect) == TRUE) {
        angleY += DEG2SHORT_ANGLE2(180.0f);
    }

    /* Add random angle between -60, 60 */
    newAngle = angleY + aIAB_RANDOM_ANGLE();

    insect->tools_actor.actor_class.world.angle.y = newAngle;
    insect->tools_actor.actor_class.shape_info.rotation.y = newAngle;
    insect->tools_actor.actor_class.gravity = 0.3f;
    insect->tools_actor.actor_class.max_velocity_y = -2.0f;
    insect->target_speed = 0.0f;
    insect->speed_step = 0.05f - RANDOM_F(0.03f);
    insect->tools_actor.actor_class.speed = 2.3f;
    aIAB_SCALE(insect) = 0.0f;
    aIAB_SCALE_RATE(insect) = 0.0021f;
    aIAB_HIT_WALL(insect) = FALSE;
    aIAB_make_hamon(actorx, game);
}

static void aIAB_rest_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->tools_actor.actor_class.speed = 0.0f;
    insect->speed_step = 0.0f;

    if (aIAB_HIT_WALL(insect) == TRUE) {
        insect->timer = 0;
    } else {
        insect->timer = 2.0f * RANDOM_F(30.0f);
    }

    insect->tools_actor.actor_class.scale.y = 0.01f;
}

typedef void (*aIAB_INIT_PROC)(aINS_INSECT_ACTOR*, GAME*);

static void aIAB_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game) {
    static aIAB_INIT_PROC init_proc[] = {
        (aIAB_INIT_PROC)&none_proc1,
        &aIAB_let_escape_init,
        &aIAB_move_init,
        &aIAB_rest_init,
    };

    static aINS_ACTION_PROC act_proc[] = {
        (aINS_ACTION_PROC)&none_proc1,
        &aIAB_let_escape,
        &aIAB_move,
        &aIAB_rest,
    };

    insect->action = action;
    insect->action_proc = act_proc[action];
    (*init_proc[action])(insect, game);
}

static void aIAB_actor_move(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    uintptr_t label = mPlib_Get_item_net_catch_label();

    if (label == (uintptr_t)actorx) {
        insect->alpha0 = 255;
        aIAB_setupAction(insect, aIAB_ACTION_LET_ESCAPE, game);
    } else if (insect->insect_flags.bit_3 == TRUE && insect->insect_flags.bit_2 == FALSE) {
        aIAB_setupAction(insect, aIAB_ACTION_LET_ESCAPE, game);
    } else {
        (*insect->action_proc)(actorx, game);
    }
}
