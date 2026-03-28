#include "ac_ins_kabuto.h"

#include "ac_set_ovl_insect.h"
#include "m_field_info.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_player_lib.h"

#define aIKB_BALL_SCARE_DIST (60.0f)
#define aIKB_NET_SCARE_DIST (70.0f)
#define aIKB_SCOOP_SCARE_DIST (30.0f)
#define aIKB_VIB_SCARE_DIST (150.0f)
#define aIKB_MAX_PATIENCE (90.0f) /* Patience threshold for scaring away */

#define aIKB_RANDOM_ANGLE() ((s16)((fqrand() - 0.5f) * (f32)DEG2SHORT_ANGLE2(120.0f)))

static void aIKB_actor_move(ACTOR* actorx, GAME* game);
static void aIKB_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game);

enum {
    aIKB_ACTION_AVOID,
    aIKB_ACTION_LET_ESCAPE,
    aIKB_ACTION_WAIT,

    aIKB_ACTION_NUM
};

enum {
    aIKB_INIT_TREE,
    aIKB_INIT_CEDAR,

    aIKB_INIT_NUM
};

#define aIKB_CHASE_ANGLE_TIMER0(insect) ((insect)->s32_work0)
#define aIKB_CHASE_ANGLE_TIMER1(insect) ((insect)->s32_work1)
#define aIKB_CHASE_ANGLE_TIMER2(insect) ((insect)->s32_work2)
#define aIKB_ROT_Y(insect) ((insect)->s32_work3)

extern void aIKB_actor_init(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int act;

    if (actorx->actor_specific == 0) {
        static f32 init_posY[aIKB_INIT_NUM] = { 35.0f, 30.0f };
        static f32 init_posZ[aIKB_INIT_NUM] = { -2.0f, 8.0f };
        mActor_name_t* fg_p = mFI_GetUnitFG(actorx->world.position);
        int init_type;

        // @BUG - devs forgot to check for the item variants of the cedar tree.
        // This causes the 'invisible bug' glitch.
#ifndef BUGFIXES
        if (fg_p != NULL && *fg_p == CEDAR_TREE) {
#else
        if (fg_p != NULL && (*fg_p == CEDAR_TREE || *fg_p == CEDAR_TREE_BELLS || *fg_p == CEDAR_TREE_FTR || *fg_p == CEDAR_TREE_BEES || *fg_p == CEDAR_TREE_LIGHTS)) {
#endif
            init_type = aIKB_INIT_CEDAR;
        } else {
            init_type = aIKB_INIT_TREE;
        }

        actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, -init_posY[init_type]);
        actorx->world.position.z += init_posZ[init_type];
        actorx->shape_info.draw_shadow = FALSE;
        actorx->shape_info.rotation.x = DEG2SHORT_ANGLE2(90.0f);
        aIKB_ROT_Y(insect) = actorx->shape_info.rotation.y;
        act = aIKB_ACTION_WAIT;
    } else {
        act = aIKB_ACTION_LET_ESCAPE;
    }

    switch (insect->type) {
        case aINS_INSECT_TYPE_DRONE_BEETLE:
            insect->item = ITM_INSECT19;
            break;
        case aINS_INSECT_TYPE_DYNASTID_BEETLE:
            insect->item = ITM_INSECT20;
            break;
        case aINS_INSECT_TYPE_FLAT_STAG_BEETLE:
            insect->item = ITM_INSECT21;
            break;
        case aINS_INSECT_TYPE_JEWEL_BEETLE:
            insect->item = ITM_INSECT22;
            break;
        case aINS_INSECT_TYPE_LONGHORN_BEETLE:
            insect->item = ITM_INSECT23;
            break;
        case aINS_INSECT_TYPE_SAW_STAG_BEETLE:
            insect->item = ITM_INSECT29;
            break;
        case aINS_INSECT_TYPE_MOUNTAIN_BEETLE:
            insect->item = ITM_INSECT30;
            break;
        case aINS_INSECT_TYPE_GIANT_BEETLE:
            insect->item = ITM_INSECT31;
            break;
    }

    actorx->mv_proc = &aIKB_actor_move;
    aIKB_setupAction(insect, act, game);
}

static void aIKB_anime_proc(aINS_INSECT_ACTOR* insect) {
    insect->_1E0 += 0.5f;
    if (insect->_1E0 >= 2.0f) {
        insect->_1E0 -= 2.0f;
    }
}

static int aIKB_check_ball(ACTOR* actorx) {
    f32 dX = Common_Get(ball_pos).x - actorx->world.position.x;
    f32 dZ = Common_Get(ball_pos).z - actorx->world.position.z;
    int res = FALSE;

    if ((SQ(dX) + SQ(dZ)) < SQ(aIKB_BALL_SCARE_DIST)) {
        res = TRUE;
    }

    return res;
}

static int aIKB_check_player_net(ACTOR* actorx) {
    xyz_t net_pos;
    int res = FALSE;

    if (mPlib_Check_StopNet(&net_pos) == TRUE) {
        uintptr_t label = mPlib_Get_item_net_catch_label();

        if (label != (uintptr_t)actorx) {
            f32 dX = net_pos.x - actorx->world.position.x;
            f32 dZ = net_pos.z - actorx->world.position.z;

            if ((SQ(dX) + SQ(dZ)) < SQ(aIKB_NET_SCARE_DIST)) {
                res = TRUE;
            }
        }
    }

    return res;
}

static int aIKB_check_player_scoop(ACTOR* actorx) {
    xyz_t scoop_pos;
    int res = FALSE;

    if (mPlib_Check_DigScoop(&scoop_pos) == TRUE) {
        f32 dX = scoop_pos.x - actorx->world.position.x;
        f32 dZ = scoop_pos.z - actorx->world.position.z;

        if ((SQ(dX) + SQ(dZ)) < SQ(aIKB_SCOOP_SCARE_DIST)) {
            res = TRUE;
        }
    }

    return res;
}

static int aIKB_check_patience(aINS_INSECT_ACTOR* insect) {
    int res = FALSE;
    ACTOR* actorx = (ACTOR*)insect;

    /* Check that no action which would scare the insect away has occurred */
    if (mPlib_Check_tree_shaken(&actorx->world.position) == TRUE) {
        insect->patience = 100.0f;
    } else if (mPlib_Check_VibUnit_OneFrame(&actorx->world.position) == TRUE &&
               actorx->player_distance_xz < aIKB_VIB_SCARE_DIST) {
        insect->patience = 100.0f;
    } else if (aIKB_check_ball(actorx) == TRUE) {
        insect->patience = 100.0f;
    } else if (aIKB_check_player_net(actorx) == TRUE) {
        insect->patience = 100.0f;
    } else if (aIKB_check_player_scoop(actorx) == TRUE) {
        insect->patience = 100.0f;
    }

    if (insect->patience > aIKB_MAX_PATIENCE) {
        res = TRUE;
    }

    return res;
}

static void aIKB_avoid(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    f32 grav;

    aIKB_anime_proc(insect);
    grav = actorx->gravity;
    grav *= 1.1f;

    if (grav > 12.0f) {
        grav = 12.0f;
    }

    actorx->gravity = grav;

    sAdo_OngenPos((uintptr_t)actorx, NA_SE_25, &actorx->world.position);

    if (insect->bg_type != 2) {
        int h_ut_x;
        int h_ut_z;
        int now_ut_x;
        int now_ut_z;

        mFI_Wpos2UtNum(&h_ut_x, &h_ut_z, actorx->home.position);
        mFI_Wpos2UtNum(&now_ut_x, &now_ut_z, actorx->world.position);

        if (h_ut_x != now_ut_x || h_ut_z != now_ut_z) {
            insect->bg_type = 2;
        }
    }
}

static void aIKB_wait(ACTOR* actorx, GAME* game) {
    static s16 angle_table[] = { DEG2SHORT_ANGLE2(175.78125f), DEG2SHORT_ANGLE2(-175.78125f) };
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR_GAME(game);

    actorx->player_angle_y = search_position_angleY(&actorx->world.position, &player->actor_class.world.position);
    if (aIKB_check_patience(insect) == TRUE) {
        /* Insect was scared away */
        aIKB_setupAction(insect, aIKB_ACTION_AVOID, game);
    } else if (aIKB_CHASE_ANGLE_TIMER0(insect) == 0) {
        chase_angle(&actorx->shape_info.rotation.y, angle_table[(aIKB_CHASE_ANGLE_TIMER1(insect) & 1)], 128);

        if (aIKB_CHASE_ANGLE_TIMER2(insect) == 0) {
            if (aIKB_CHASE_ANGLE_TIMER1(insect) == 0) {
                aIKB_CHASE_ANGLE_TIMER0(insect) = (int)((10.0f + RANDOM_F(10.0f)) * 2.0f);
                aIKB_CHASE_ANGLE_TIMER1(insect) = 3 + RANDOM(2);
            } else {
                aIKB_CHASE_ANGLE_TIMER1(insect)--;
            }

            aIKB_CHASE_ANGLE_TIMER2(insect) = 30;
        } else {
            aIKB_CHASE_ANGLE_TIMER2(insect)--;
        }
    } else {
        aIKB_CHASE_ANGLE_TIMER0(insect)--;
    }
}

static void aIKB_avoid_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    PLAYER_ACTOR* player;

    insect->life_time = 0;
    insect->alpha_time = 80;
    insect->tools_actor.actor_class.gravity = 0.06f;
    insect->tools_actor.actor_class.max_velocity_y = 12.0f;
    insect->tools_actor.actor_class.speed = 4.0f;
    insect->tools_actor.actor_class.shape_info.rotation.x = 0;

    player = GET_PLAYER_ACTOR_GAME(game);
    if (player != NULL) {
        s16 angle = player->actor_class.shape_info.rotation.y + aIKB_RANDOM_ANGLE();

        insect->tools_actor.actor_class.world.angle.y = angle;
        insect->tools_actor.actor_class.shape_info.rotation.y = angle;
    }

    insect->insect_flags.bit_1 = TRUE;
    insect->insect_flags.bit_2 = TRUE;
    insect->tools_actor.actor_class.shape_info.draw_shadow = TRUE;
}

static void aIKB_wait_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->tools_actor.actor_class.shape_info.rotation.y = DEG2SHORT_ANGLE2(-180.0f);
}

typedef void (*aIKB_INIT_PROC)(aINS_INSECT_ACTOR*, GAME*);

static void aIKB_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game) {
    static aIKB_INIT_PROC init_proc[] = {
        &aIKB_avoid_init,
        &aIKB_avoid_init,
        &aIKB_wait_init,
    };

    static aINS_ACTION_PROC act_proc[] = {
        &aIKB_avoid,
        &aIKB_avoid,
        &aIKB_wait,
    };

    insect->action = action;
    insect->action_proc = act_proc[action];
    (*init_proc[action])(insect, game);
}

static void aIKB_actor_move(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    uintptr_t label = mPlib_Get_item_net_catch_label();

    if (label == (uintptr_t)actorx) {
        aIKB_setupAction(insect, aIKB_ACTION_LET_ESCAPE, game);
    } else if (insect->insect_flags.bit_3 == TRUE && insect->insect_flags.bit_2 == FALSE) {
        aIKB_setupAction(insect, aIKB_ACTION_LET_ESCAPE, game);
    } else {
        (*insect->action_proc)(actorx, game);
    }
}
