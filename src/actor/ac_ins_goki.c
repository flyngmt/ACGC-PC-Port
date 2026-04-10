#include "ac_ins_goki.h"

#include "m_field_info.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "ac_set_ovl_insect.h"

enum {
    aIGK_INIT_TREE,
    aIGK_INIT_CEDAR,

    aIGK_INIT_NUM
};

enum {
    aIGK_ACTION_AVOID,
    aIGK_ACTION_LET_ESCAPE,
    aIGK_ACTION_WAIT_ON_FLOWER,
    aIGK_ACTION_MOVE_ON_FLOWER,
    aIGK_ACTION_WAIT_ON_TREE,
    aIGK_ACTION_MOVE_ON_TREE,
    aIGK_ACTION_WAIT_ON_ITEM,
    aIGK_ACTION_MOVE_ON_ITEM,

    aIGK_ACTION_NUM
};

#define aIGK_PLACE_TREE 4
#define aIGK_PLACE_FLOWER 5
#define aIGK_PLACE_ITEM 6

#define aIGK_BALL_SCARE_DIST (60.0f)
#define aIGK_NET_SCARE_DIST (70.0f)
#define aIGK_SCOOP_SCARE_DIST (30.0f)
#define aIGK_VIB_SCARE_DIST (150.0f)
#define aIGK_MAX_PATIENCE (90.0f) /* Patience threshold for scaring away */

#define aIGK_RANDOM_ANGLE() ((int)((fqrand() - 0.5f) * 2 * (f32)DEG2SHORT_ANGLE2(90.0f)))
#define aIGK_RANDOM_ANGLE2() ((s16)((fqrand() - 0.5f) * (f32)DEG2SHORT_ANGLE2(120.0f)))

#define aIGK_TARGET_ANGLE(insect) ((insect)->s32_work0)
#define aIGK_CHANGE_WAIT_TIMER(insect) ((insect)->s32_work1)
#define aIGK_MOVE_TIMER(insect) ((insect)->s32_work2)
#ifdef TARGET_PC
#define aIGK_GET_ITEM_P(insect) (mFI_GetUnitFG(insect->tools_actor.actor_class.home.position))
#define aIGK_SET_ITEM_P(insect, item_p)
#else
#define aIGK_GET_ITEM_P(insect) ((insect)->s32_work3)
#define aIGK_SET_ITEM_P(insect, item_p) ((insect)->s32_work3 = (int)item_p)
#endif

static void aIGK_actor_move(ACTOR* actorx, GAME* game);
static void aIGK_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game);

extern void aIGK_actor_init(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int act;

    insect->item = ITM_INSECT28;
    actorx->mv_proc = &aIGK_actor_move;
    insect->bg_range = 6.0f;

    switch (actorx->actor_specific) {
        case aSOI_SPAWN_NORMAL: {
            /* Spawn on flower */
            insect->bg_type = 2;
            actorx->world.position.y = 6.0f + mCoBG_GetBgY_OnlyCenter_FromWpos(actorx->world.position, -19.0f);
            xyz_t_move(&actorx->home.position, &actorx->world.position);
            actorx->shape_info.draw_shadow = FALSE;
            insect->flag = aIGK_PLACE_FLOWER;
            actorx->actor_specific = 0;
            act = aIGK_ACTION_WAIT_ON_FLOWER;
            break;
        }
        case aSOI_SPAWN_TREE: {
            /* Spawn insect on tree */
            static f32 init_posY[aIGK_INIT_NUM] = { 35.0f, 30.0f };
            static f32 init_posZ[aIGK_INIT_NUM] = { -2.0f, 8.0f };
            mActor_name_t* fg_p = mFI_GetUnitFG(actorx->world.position);
            int type;

            if (fg_p != NULL && *fg_p == CEDAR_TREE) {
                type = aIGK_INIT_CEDAR;
            } else {
                type = aIGK_INIT_TREE;
            }

            actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, -init_posY[type]);
            actorx->world.position.z += init_posZ[type];
            xyz_t_move(&actorx->home.position, &actorx->world.position);
            actorx->shape_info.draw_shadow = FALSE;
            insect->flag = aIGK_PLACE_TREE;
            actorx->actor_specific = 0;
            actorx->shape_info.rotation.y = DEG2SHORT_ANGLE2(-180.0f);
            actorx->shape_info.rotation.x = DEG2SHORT_ANGLE2(90.0f);
            act = aIGK_ACTION_WAIT_ON_TREE;
            break;
        }
        case aSOI_SPAWN_ITEM: {
            /* Spawn insect on ground item */
            actorx->world.position.y = 5.0f + mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, -2.0f);
            xyz_t_move(&actorx->home.position, &actorx->world.position);
            actorx->shape_info.draw_shadow = FALSE;
            insect->flag = aIGK_PLACE_ITEM;
            actorx->actor_specific = 0;

            aIGK_SET_ITEM_P(insect, mFI_GetUnitFG(actorx->world.position));
            if (aIGK_GET_ITEM_P(insect) == 0) {
                Actor_delete(actorx);
                return;
            }

            actorx->shape_info.rotation.y = DEG2SHORT_ANGLE2(-180.0f);
            actorx->shape_info.rotation.x = DEG2SHORT_ANGLE2(45.0f);
            act = aIGK_ACTION_WAIT_ON_ITEM;
            break;
        }
        default: {
            act = aIGK_ACTION_LET_ESCAPE;
            break;
        }
    }

    aIGK_setupAction(insect, act, game);
}

static void aIGK_anime_proc(aINS_INSECT_ACTOR* insect) {
    insect->_1E0 += 0.5f;
    if (insect->_1E0 >= 2.0f) {
        insect->_1E0 -= 2.0f;
    }
}

static int aIGK_check_tree_shaken(aINS_INSECT_ACTOR* insect) {
    int res = FALSE;

    if (insect->flag == aIGK_PLACE_TREE) {
        if (mPlib_Check_tree_shaken(&insect->tools_actor.actor_class.world.position) == TRUE) {
            res = TRUE;
        } else if (mPlib_Check_VibUnit_OneFrame(&insect->tools_actor.actor_class.world.position) == TRUE &&
                   insect->tools_actor.actor_class.player_distance_xz < aIGK_VIB_SCARE_DIST) {
            res = TRUE;
        }
    }

    return res;
}

static int aIGK_check_ball(aINS_INSECT_ACTOR* insect) {
    f32 dX = Common_Get(ball_pos).x - insect->tools_actor.actor_class.world.position.x;
    f32 dZ = Common_Get(ball_pos).z - insect->tools_actor.actor_class.world.position.z;
    int res = FALSE;

    if ((SQ(dX) + SQ(dZ)) < SQ(aIGK_BALL_SCARE_DIST)) {
        res = TRUE;
    }

    return res;
}

static int aIGK_check_player_net(aINS_INSECT_ACTOR* insect) {
    xyz_t net_pos;
    int res = FALSE;

    if (mPlib_Check_StopNet(&net_pos) == TRUE) {
        uintptr_t label = mPlib_Get_item_net_catch_label();

        if (label != (uintptr_t)insect) {
            f32 dX = net_pos.x - insect->tools_actor.actor_class.world.position.x;
            f32 dZ = net_pos.z - insect->tools_actor.actor_class.world.position.z;

            if ((SQ(dX) + SQ(dZ)) < SQ(aIGK_NET_SCARE_DIST)) {
                res = TRUE;
            }
        }
    }

    return res;
}

static int aIGK_check_player_scoop(aINS_INSECT_ACTOR* insect) {
    xyz_t scoop_pos;
    int res = FALSE;

    if (mPlib_Check_DigScoop(&scoop_pos) == TRUE) {
        f32 dX = scoop_pos.x - insect->tools_actor.actor_class.world.position.x;
        f32 dZ = scoop_pos.z - insect->tools_actor.actor_class.world.position.z;

        if ((SQ(dX) + SQ(dZ)) < SQ(aIGK_SCOOP_SCARE_DIST)) {
            res = TRUE;
        }
    }

    return res;
}

static int aIGK_check_patience(aINS_INSECT_ACTOR* insect) {
    int res = FALSE;

    /* Check that no action which would scare the insect away has occurred */
    if (aIGK_check_tree_shaken(insect) == TRUE) {
        insect->patience = 100.0f;
    } else if (aIGK_check_ball(insect) == TRUE) {
        insect->patience = 100.0f;
    } else if (aIGK_check_player_net(insect) == TRUE) {
        insect->patience = 100.0f;
    } else if (aIGK_check_player_scoop(insect) == TRUE) {
        insect->patience = 100.0f;
    } else if (insect->flag == aIGK_PLACE_ITEM && *(mActor_name_t*)aIGK_GET_ITEM_P(insect) != ITM_KABU_SPOILED) {
        insect->patience = 100.0f;
    }

    if (insect->patience >= aIGK_MAX_PATIENCE) {
        res = TRUE;
    }

    return res;
}

static void aIGK_avoid(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    f32 grav;

    grav = actorx->gravity;
    grav *= 1.1f;
    if (grav > 12.0f) {
        grav = 12.0f;
    }

    actorx->gravity = grav;
    sAdo_OngenPos((uintptr_t)actorx, NA_SE_26, &actorx->world.position);
    aIGK_anime_proc(insect);

    if (insect->bg_type == 0) {
        int h_ut_x;
        int h_ut_z;
        int now_ut_x;
        int now_ut_z;

        mFI_Wpos2UtNum(&h_ut_x, &h_ut_z, actorx->home.position);
        mFI_Wpos2UtNum(&now_ut_x, &now_ut_z, actorx->world.position);

        if (h_ut_x != now_ut_x || h_ut_z != now_ut_z) {
            insect->bg_type = 1;
        }
    }
}

static void aIGK_wait_on_flower(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (aIGK_check_patience(insect) == TRUE) {
        aIGK_setupAction(insect, aIGK_ACTION_AVOID, game);
    } else {
        insect->timer--;

        if (insect->timer <= 0) {
            aIGK_setupAction(insect, aIGK_ACTION_MOVE_ON_FLOWER, game);
        } else {
            chase_angle(&actorx->world.angle.y, aIGK_TARGET_ANGLE(insect), DEG2SHORT_ANGLE2(8.4375f));
            actorx->shape_info.rotation.y = actorx->world.angle.y;
        }
    }
}

static void aIGK_move_on_flower(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (aIGK_check_patience(insect) == TRUE) {
        aIGK_setupAction(insect, aIGK_ACTION_AVOID, game);
    } else {
        aIGK_MOVE_TIMER(insect)--;

        if (aIGK_MOVE_TIMER(insect) <= 0) {
            sAdo_OngenPos((uintptr_t)actorx, NA_SE_GOKI_MOVE, &actorx->world.position);
            insect->timer = (int)(2 * (90.0f + RANDOM_F(90.0f)));
            aIGK_setupAction(insect, aIGK_ACTION_WAIT_ON_FLOWER, game);
        } else {
            int flag = 0;
            f32 dX = actorx->world.position.x - actorx->home.position.x;
            f32 dZ = actorx->world.position.z - actorx->home.position.z;

            if (ABS(dX) >= 15.0f) {
                if (dX < 0.0f) {
                    actorx->world.position.x = actorx->home.position.x - 14.0f;
                    flag = 1;
                } else {
                    actorx->world.position.x = actorx->home.position.x + 14.0f;
                    flag = 2;
                }
            }

            if (ABS(dZ) >= 15.0f) {
                if (dZ < 0.0f) {
                    actorx->world.position.z = actorx->home.position.z - 14.0f;
                    flag |= 4;
                } else {
                    actorx->world.position.z = actorx->home.position.z + 14.0f;
                    flag |= 8;
                }
            }

            if (flag != 0) {
                // clang-format off
                static int ref_angl[16] = {
                    DEG2SHORT_ANGLE2(0.0f), DEG2SHORT_ANGLE2(90.0f), DEG2SHORT_ANGLE2(-90.0f), DEG2SHORT_ANGLE2(0.0f),
                    DEG2SHORT_ANGLE2(0.0f), DEG2SHORT_ANGLE2(45.0f), DEG2SHORT_ANGLE2(-45.0f), DEG2SHORT_ANGLE2(0.0f),
                    DEG2SHORT_ANGLE2(180.0f), DEG2SHORT_ANGLE2(135.0f), DEG2SHORT_ANGLE2(-135.0f), DEG2SHORT_ANGLE2(180.0f),
                    DEG2SHORT_ANGLE2(90.0f), DEG2SHORT_ANGLE2(90.0f), DEG2SHORT_ANGLE2(-90.0f), DEG2SHORT_ANGLE2(0.0f),
                };
                // clang-format on

                aIGK_TARGET_ANGLE(insect) = ref_angl[flag];
                insect->timer = 10;
                aIGK_setupAction(insect, aIGK_ACTION_WAIT_ON_FLOWER, game);
            } else {
                int done = chase_angle(&actorx->world.angle.y, aIGK_TARGET_ANGLE(insect), DEG2SHORT_ANGLE2(8.4375f));

                if (done == TRUE) {
                    aIGK_TARGET_ANGLE(insect) = actorx->world.angle.y + aIGK_RANDOM_ANGLE();
                }

                actorx->shape_info.rotation.y = actorx->world.angle.y;
            }
        }
    }
}

static void aIGK_wait_on_tree(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (aIGK_check_patience(insect) == TRUE) {
        aIGK_setupAction(insect, aIGK_ACTION_AVOID, game);
    } else {
        insect->timer--;
        if (insect->timer <= 0) {
            aIGK_setupAction(insect, insect->action + 1, game);
        }
    }
}

static void aIGK_move_on_tree(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (aIGK_check_patience(insect) == TRUE) {
        aIGK_setupAction(insect, aIGK_ACTION_AVOID, game);
    } else {
        chase_angle(&actorx->shape_info.rotation.y, aIGK_TARGET_ANGLE(insect), 128);
        aIGK_MOVE_TIMER(insect)--;

        if (aIGK_MOVE_TIMER(insect) <= 0) {
            aIGK_CHANGE_WAIT_TIMER(insect)--;
            if (aIGK_CHANGE_WAIT_TIMER(insect) <= 0) {
                aIGK_setupAction(insect, insect->action - 1, game);
            } else {
                aIGK_TARGET_ANGLE(insect) = -aIGK_TARGET_ANGLE(insect);
                aIGK_MOVE_TIMER(insect) = 30;
            }
        }
    }
}

static void aIGK_avoid_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    static f32 base_angl[2] = { DEG2SHORT_ANGLE2(-22.5f), DEG2SHORT_ANGLE2(22.5f) };
    f32 rnd;
    s16 angl;

    insect->tools_actor.actor_class.shape_info.draw_shadow = TRUE;
    insect->tools_actor.actor_class.speed = 4.0f;
    insect->tools_actor.actor_class.max_velocity_y = 12.0f;
    insect->tools_actor.actor_class.gravity = 0.06f;
    insect->tools_actor.actor_class.shape_info.rotation.x = 0;
    insect->tools_actor.actor_class.position_speed.y = 0.0f;
    rnd = fqrand();
    insect->life_time = 0;
    insect->alpha_time = 80;
    angl = (int)(rnd * DEG2SHORT_ANGLE2(90.0f) - (f32)DEG2SHORT_ANGLE2(45.0f) + base_angl[rnd >= 0.5f]);

    insect->tools_actor.actor_class.world.angle.y = angl;
    insect->tools_actor.actor_class.shape_info.rotation.y = angl;
    insect->insect_flags.bit_1 = TRUE;
}

static void aIGK_let_escape_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    PLAYER_ACTOR* player;

    insect->tools_actor.actor_class.shape_info.draw_shadow = TRUE;
    insect->life_time = 0;
    insect->alpha_time = 80;
    insect->tools_actor.actor_class.speed = 4.0f;
    insect->tools_actor.actor_class.max_velocity_y = 12.0f;
    insect->tools_actor.actor_class.gravity = 0.06f;
    insect->tools_actor.actor_class.shape_info.rotation.x = 0;
    insect->tools_actor.actor_class.position_speed.y = 0.0f;

    player = GET_PLAYER_ACTOR_GAME(game);
    if (player != NULL) {
        s16 angl = player->actor_class.shape_info.rotation.y + aIGK_RANDOM_ANGLE2();

        insect->tools_actor.actor_class.world.angle.y = angl;
        insect->tools_actor.actor_class.shape_info.rotation.y = angl;
    }

    insect->insect_flags.bit_1 = TRUE;
    insect->insect_flags.bit_2 = TRUE;
}

static void aIGK_wait_on_flower_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->tools_actor.actor_class.speed = 0.0f;
    insect->speed_step = 0.0f;
    insect->target_speed = 0.0f;
}

static void aIGK_move_on_flower_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    if (aIGK_MOVE_TIMER(insect) == 0) {
        aIGK_MOVE_TIMER(insect) = (int)(2 * (90.0f + RANDOM_F(210.0f)));
    }

    insect->target_speed = 0.4f;
    insect->speed_step = 0.1f;
}

static void aIGK_wait_on_tree_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->timer = (int)(2 * (10.0f + RANDOM_F(10.0f)));
}

static void aIGK_move_on_tree_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    aIGK_TARGET_ANGLE(insect) = DEG2SHORT_ANGLE2(175.78125f);
    aIGK_CHANGE_WAIT_TIMER(insect) = 3 + RANDOM(2);
    aIGK_MOVE_TIMER(insect) = 30;
}

typedef void (*aIGK_INIT_PROC)(aINS_INSECT_ACTOR* insect, GAME* game);

static void aIGK_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game) {
    // clang-format off
    static aIGK_INIT_PROC init_proc[aIGK_ACTION_NUM] = {
        &aIGK_avoid_init,
        &aIGK_let_escape_init,
        &aIGK_wait_on_flower_init,
        &aIGK_move_on_flower_init,
        &aIGK_wait_on_tree_init,
        &aIGK_move_on_tree_init,
        &aIGK_wait_on_tree_init,
        &aIGK_move_on_tree_init,
    };
    // clang-format on

    // clang-format off
    static aINS_ACTION_PROC act_proc[aIGK_ACTION_NUM] = {
        &aIGK_avoid,
        &aIGK_avoid,
        &aIGK_wait_on_flower,
        &aIGK_move_on_flower,
        &aIGK_wait_on_tree,
        &aIGK_move_on_tree,
        &aIGK_wait_on_tree,
        &aIGK_move_on_tree,
    };
    // clang-format on

    insect->action = action;
    insect->action_proc = act_proc[action];
    (*init_proc[action])(insect, game);
}

static void aIGK_actor_move(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    uintptr_t label = mPlib_Get_item_net_catch_label();

    if (label == (uintptr_t)actorx) {
        aIGK_setupAction(insect, aIGK_ACTION_LET_ESCAPE, game);
    } else if (insect->insect_flags.bit_3 == TRUE && insect->insect_flags.bit_2 == FALSE) {
        aIGK_setupAction(insect, aIGK_ACTION_LET_ESCAPE, game);
    } else {
        (*insect->action_proc)(actorx, game);
    }
}
