#include "ac_ins_dango.h"

#include "m_field_info.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "ac_set_ovl_insect.h"

enum {
    aIDG_ACTION_AVOID,
    aIDG_ACTION_LET_ESCAPE,
    aIDG_ACTION_STOP,
    aIDG_ACTION_HIDE,
    aIDG_ACTION_APPEAR,
    aIDG_ACTION_DIVE,
    aIDG_ACTION_DROWN,
    aIDG_ACTION_RETIRE,

    aIDG_ACTION_NUM
};

static void aIDG_actor_move(ACTOR*, GAME*);
static void aIDG_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game);

extern void aIDG_actor_init(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    int bx, bz;
    int action;

    if (insect->tools_actor.actor_class.actor_specific == 0) {
        mFI_BkNum2WposXZ(&insect->f32_work2, &insect->f32_work3, insect->tools_actor.actor_class.block_x,
                         insect->tools_actor.actor_class.block_z);
        insect->f32_work2 += 320.0f;
        insect->f32_work3 += 320.0f;
        mFI_Wpos2UtNum(&bx, &bz, insect->tools_actor.actor_class.world.position);
        action = aIDG_ACTION_HIDE;
        insect->ut_x = bx;
        insect->ut_z = bz;
    } else {
        action = aIDG_ACTION_LET_ESCAPE;
        insect->tools_actor.actor_class.drawn = TRUE;
    }
    insect->insect_flags.bit_4 = FALSE;
    insect->bg_range = 2.0f;

    switch (insect->type) {
        case aINS_INSECT_TYPE_SPIDER:
            break;
        case aINS_INSECT_TYPE_PILL_BUG:
            insect->item = ITM_INSECT36;
            break;
        case aINS_INSECT_TYPE_ANT:
            insect->item = ITM_INSECT38;
            break;
    }
    insect->tools_actor.actor_class.mv_proc = aIDG_actor_move;
    aIDG_setupAction(insect, action, game);
}

static int aIDG_check_strike_stone(aINS_INSECT_ACTOR* insect) {
    int ret;
    int bx, bz;

    ret = FALSE;
    if ((aINS_CLIP->pl_action == aINS_PL_ACT_REFLECT_AXE) || (aINS_CLIP->pl_action == aINS_PL_ACT_REFLECT_SCOOP)) {
        mFI_Wpos2UtNum(&bx, &bz, insect->tools_actor.actor_class.world.position);
        if ((aINS_CLIP->pl_action_ut_x == bx) && (aINS_CLIP->pl_action_ut_z == bz)) {
            ret = TRUE;
        }
    }
    return ret;
}

static int aIDG_check_ball(aINS_INSECT_ACTOR* insect) {
    f32 xDiff;
    f32 zDiff;
    int ret;

    ret = FALSE;

    xDiff = Common_Get(ball_pos).x - insect->tools_actor.actor_class.world.position.x;
    zDiff = Common_Get(ball_pos).z - insect->tools_actor.actor_class.world.position.z;

    if (((xDiff * xDiff) + (zDiff * zDiff)) < 3600.0f) {
        ret = TRUE;
    }

    return ret;
}

static int aIDG_check_player_net(aINS_INSECT_ACTOR* insect) {
    f32 xDiff;
    f32 zDiff;
    int ret;
    xyz_t pos;

    ret = FALSE;
    if (mPlib_Check_StopNet(&pos) == TRUE) {
        xDiff = pos.x - insect->tools_actor.actor_class.world.position.x;
        zDiff = pos.z - insect->tools_actor.actor_class.world.position.z;

        if (((xDiff * xDiff) + (zDiff * zDiff)) < 4900.0f) {
            ret = TRUE;
        }
    }

    return ret;
}

static int aIDG_check_player_scoop(aINS_INSECT_ACTOR* insect) {
    f32 xDiff;
    f32 zDiff;
    int ret;
    xyz_t pos;

    ret = FALSE;
    if (mPlib_Check_DigScoop(&pos) == TRUE) {
        xDiff = pos.x - insect->tools_actor.actor_class.world.position.x;
        zDiff = pos.z - insect->tools_actor.actor_class.world.position.z;

        if (((xDiff * xDiff) + (zDiff * zDiff)) < 4900.0f) {
            ret = TRUE;
        }
    }

    return ret;
}

static int aIDG_check_player_axe(aINS_INSECT_ACTOR* insect) {
    f32 xDiff;
    f32 zDiff;
    int ret;
    xyz_t pos;

    ret = FALSE;
    if (mPlib_Check_HitAxe(&pos) == TRUE) {
        xDiff = pos.x - insect->tools_actor.actor_class.world.position.x;
        zDiff = pos.z - insect->tools_actor.actor_class.world.position.z;

        if (((xDiff * xDiff) + (zDiff * zDiff)) < 4900.0f) {
            ret = TRUE;
        }
    }

    return ret;
}

static int aIDG_check_patience(aINS_INSECT_ACTOR* insect) {
    int ret;

    ret = FALSE;
    if ((insect->ut_x == -1) && (insect->ut_z == -1)) {
        if (aIDG_check_ball(insect) == TRUE) {
            insect->patience = 100.0f;
        } else if (aIDG_check_player_net(insect) == TRUE) {
            insect->patience = 100.0f;
        } else if (aIDG_check_player_scoop(insect) == TRUE) {
            insect->patience = 100.0f;
        } else if (aIDG_check_player_axe(insect) == TRUE) {
            insect->patience = 100.0f;
        }
        if (insect->patience > 90.0f) {
            ret = TRUE;
        }
    }
    return ret;
}

static int aIDG_chk_active_range(aINS_INSECT_ACTOR* insect) {
    f32 z, x;
    int ret;

    ret = TRUE;
    x = insect->f32_work2 - insect->tools_actor.actor_class.world.position.x;
    z = insect->f32_work3 - insect->tools_actor.actor_class.world.position.z;
    if (((x * x) + (z * z)) >= 160000.0f) {
        ret = FALSE;
    }
    return ret;
}

static int aIDG_chk_water_attr(aINS_INSECT_ACTOR* insect, GAME* game) {
    int ret = FALSE;

    if (insect->tools_actor.actor_class.bg_collision_check.result.on_ground) {
        xyz_t pos = insect->tools_actor.actor_class.world.position;
        f32 speed = insect->bg_range + insect->tools_actor.actor_class.speed;
        s16 yAngle = insect->tools_actor.actor_class.world.angle.y;

        pos.x += speed * sin_s(yAngle);
        pos.z += speed * cos_s(yAngle);

        if (mCoBG_CheckWaterAttribute(mCoBG_Wpos2BgAttribute_Original(pos))) {
            aIDG_setupAction(insect, aIDG_ACTION_DIVE, game);
            ret = TRUE;
        }
    }

    return ret;
}

static void aIDG_calc_direction_angl(aINS_INSECT_ACTOR* insect) {
    if (insect->tools_actor.actor_class.bg_collision_check.result.hit_wall & mCoBG_HIT_WALL_FRONT) {
        int wallCount = insect->tools_actor.actor_class.bg_collision_check.result.hit_wall_count & 7;
        if (wallCount != 0) {
            int i;

            for (i = 0; i < wallCount; i++) {
                mCoBG_WallInfo_c* info = &insect->tools_actor.actor_class.bg_collision_check.wall_info[i];
                if (info->type == 0) {
                    insect->tools_actor.actor_class.world.angle.y =
                        insect->tools_actor.actor_class.bg_collision_check.wall_info[i].angleY + 0x4000;
                    break;
                }
            }
        }
    }
    chase_angle(&insect->tools_actor.actor_class.shape_info.rotation.y, insect->tools_actor.actor_class.world.angle.y,
                0x800);
}

static void aIDG_avoid(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    int bx, bz;
    if (aIDG_chk_water_attr(insect, game) == FALSE) {
        if (aIDG_chk_active_range(insect) == FALSE) {
            aIDG_setupAction(insect, aIDG_ACTION_RETIRE, game);
        } else {
            aIDG_calc_direction_angl(insect);
            if (insect->bg_type == 4) {
                mFI_Wpos2UtNum(&bx, &bz, insect->tools_actor.actor_class.world.position);
                if ((insect->ut_x != bx) || ((s16)insect->ut_z != bz)) {
                    insect->ut_x = -1;
                    insect->ut_z = -1;
                    insect->bg_type = 2;
                }
            } else if (aIDG_check_patience(insect) == TRUE) {
                aIDG_setupAction(insect, aIDG_ACTION_STOP, game);
            }
        }
    }
}

static void aIDG_let_escape(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    if (aIDG_chk_water_attr(insect, game) == FALSE) {
        aIDG_calc_direction_angl(insect);
    }
}

static void aIDG_stop(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    if ((aIDG_chk_water_attr(insect, game) == FALSE) && (insect->patience < 50.0f)) {
        aIDG_setupAction(insect, aIDG_ACTION_AVOID, game);
    }
}

static void aIDG_hide(ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*) game;
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;

    if (aIDG_check_strike_stone(insect) == TRUE) {
        aIDG_setupAction(insect, aIDG_ACTION_APPEAR, &play->game);
    }
}

static void aIDG_appear(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    if (insect->tools_actor.actor_class.bg_collision_check.result.on_ground) {
        aIDG_setupAction(insect, aIDG_ACTION_STOP , game);
    }
}

static void aIDG_dive(ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*) game;
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    
    if (actor->world.position.y <=
        mCoBG_GetWaterHeight_File(actor->world.position, "ac_ins_dango.c", 608)) {
        aIDG_setupAction(insect, aIDG_ACTION_DROWN, &play->game);
    }
}

static void aIDG_avoid_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player;
    s16 angle;

    insect->tools_actor.actor_class.speed = 1.5f;
    insect->target_speed = 1.5f;
    insect->speed_step = 0.3f;
    insect->_1E0 = 1.0f;

    player = get_player_actor_withoutCheck(play);
    if (player != NULL) {
        angle = player->actor_class.shape_info.rotation.y + (s16)(21845.0f * (fqrand() - 0.5f));
        insect->tools_actor.actor_class.world.angle.y = angle;
        insect->tools_actor.actor_class.shape_info.rotation.y = angle;
    }
}

static void aIDG_let_escape_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->life_time = 0;
    insect->alpha_time = 80;
    insect->tools_actor.actor_class.shape_info.rotation.x = 0;
    insect->bg_type = 2;
    insect->tools_actor.actor_class.gravity = 2.0f;
    insect->tools_actor.actor_class.max_velocity_y = -20.0f;
    aIDG_avoid_init(insect, game);
    insect->insect_flags.bit_1 = TRUE;
    insect->insect_flags.bit_2 = TRUE;
}

static void aIDG_stop_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->target_speed = 0.0f;
    insect->speed_step = 0.05f;
    insect->_1E0 = 0.0f;
}

static void aIDG_hide_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->bg_type = 4;
    insect->tools_actor.actor_class.gravity = 2.0f;
    insect->tools_actor.actor_class.max_velocity_y = -20.0f;
    insect->tools_actor.actor_class.drawn = FALSE;
}

static void aIDG_appear_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    aIDG_avoid_init(insect, game);
    insect->tools_actor.actor_class.drawn = TRUE;
    insect->_1E0 = 0.0f;
    insect->tools_actor.actor_class.position_speed.y = 12.0f;
}

static void aIDG_dive_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->tools_actor.actor_class.speed = 1.5f;
    insect->speed_step = 0.3f;
    insect->target_speed = 1.5f;
    insect->tools_actor.actor_class.position_speed.y = 8.0f;
    insect->_1E0 = 0.0f;
    insect->insect_flags.bit_1 = TRUE;
}

static void aIDG_drown_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    xyz_t pos = insect->tools_actor.actor_class.world.position;
    f32 height = mCoBG_GetWaterHeight_File(pos, "ac_ins_dango.c", 763);

    pos.y = height;

    eEC_CLIP->effect_make_proc(0x46, pos, 1, insect->tools_actor.actor_class.world.angle.y, game, 0, 4, 0);
    sAdo_OngenTrgStart(0x438, &insect->tools_actor.actor_class.world.position);

    insect->insect_flags.bit_1 = TRUE;
    insect->insect_flags.destruct = TRUE;
    insect->tools_actor.actor_class.shape_info.draw_shadow = FALSE;
}

static void aIDG_retire_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->life_time = 0;
    insect->alpha_time = 0x50;
    insect->tools_actor.actor_class.shape_info.rotation.x = 0;
    insect->bg_type = 2;
    insect->insect_flags.bit_1 = TRUE;
    insect->insect_flags.bit_2 = TRUE;
}

typedef void (*aIBT_INIT_PROC)(aINS_INSECT_ACTOR*, GAME*);

static void aIDG_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game) {
    static aIBT_INIT_PROC init_proc[] = {
        &aIDG_avoid_init, aIDG_let_escape_init, aIDG_stop_init,  aIDG_hide_init,
        aIDG_appear_init, aIDG_dive_init,       aIDG_drown_init, aIDG_retire_init,
    };

    static aINS_ACTION_PROC act_proc[] = {
        aIDG_avoid,
        aIDG_let_escape,
        aIDG_stop,
        aIDG_hide,
        aIDG_appear,
        aIDG_dive,
        (aINS_ACTION_PROC)none_proc1,
        aIDG_let_escape,
    };

    insect->action = action;
    insect->action_proc = act_proc[action];
    (*init_proc[action])(insect, game);
}


static void aIDG_actor_move(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;
 
    uintptr_t label = mPlib_Get_item_net_catch_label();

    if (label == (uintptr_t)actor) {
        insect->alpha0 = 255;
        aIDG_setupAction(insect, aIDG_ACTION_LET_ESCAPE, game);
    } else {
        insect->action_proc(actor,game);
    }
}
