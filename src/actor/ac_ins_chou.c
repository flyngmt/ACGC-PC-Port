#include "ac_ins_chou.h"

#include "m_field_info.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "ac_set_ovl_insect.h"

enum {
    aICH_ACTION_AVOID,
    aICH_ACTION_LET_ESCAPE,
    aICH_ACTION_FLY,
    aICH_ACTION_LANDING,
    aICH_ACTION_HOVER,
    aICH_ACTION_REST,

    aICH_ACTION_NUM
};

static void aICH_actor_move(ACTOR*, GAME*);
static int aICH_check_live_condition(aINS_INSECT_ACTOR* arg0, mActor_name_t* name);
static void aICH_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game);

extern void aICH_actor_init(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    int action;

    if (actor->actor_specific == 0) {
        mActor_name_t* unit = mFI_GetUnitFG(actor->world.position);
        if (aICH_check_live_condition(insect, unit) == FALSE) {
            insect->insect_flags.destruct = TRUE;
            return;
        }
        actor->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos(actor->world.position, 30.0f);
        xyz_t_move(&actor->home.position, &actor->world.position);
        mFI_Wpos2UtNum_inBlock(&insect->s32_work1, &insect->s32_work2, actor->world.position);
        action = aICH_ACTION_FLY;

    } else {
        action = aICH_ACTION_LET_ESCAPE;
    }
    insect->bg_type = 2;
    switch (insect->type) {
        case aINS_INSECT_TYPE_COMMON_BUTTERFLY:
            insect->item = ITM_INSECT00;
            break;
        case aINS_INSECT_TYPE_YELLOW_BUTTERFLY:
            insect->item = ITM_INSECT01;
            break;
        case aINS_INSECT_TYPE_TIGER_BUTTERFLY:
            insect->item = ITM_INSECT02;
            break;
        case aINS_INSECT_TYPE_PURPLE_BUTTERFLY:
            insect->item = ITM_INSECT03;
            break;
    }
    actor->mv_proc = aICH_actor_move;
    aICH_setupAction(insect, action, game);
}

static int aICH_check_live_condition(aINS_INSECT_ACTOR* insect, mActor_name_t* name) {
    int ret = TRUE;
    if (insect->type != aINS_INSECT_TYPE_PURPLE_BUTTERFLY) {
        if (mCoBG_ExistHeightGap_KeepAndNow(insect->tools_actor.actor_class.world.position) == TRUE) {
            ret = FALSE;
        } else if ((name == NULL) || (*name == RSV_NO)) {
            ret = FALSE;
        } else if (((*name >> 12) & 0xF) == 5) {
            ret = FALSE;
        }
    }
    return ret;
}

static void aICH_anime_proc(aINS_INSECT_ACTOR* insect) {
    insect->_1E0 += 0.2f;
    if (insect->_1E0 >= 2.0f) {
        insect->_1E0 -= 2.0f;
    }
}

static void aICH_jump_ctrl(aINS_INSECT_ACTOR* insect, f32 base) {
    f32 angle;

    angle = mCoBG_GetWaterHeight_File(insect->tools_actor.actor_class.world.position, "ac_ins_chou.c", 265);
    if (angle == -100.0f) {
        angle = mCoBG_GetBgY_AngleS_FromWpos(NULL, insect->tools_actor.actor_class.world.position, 0.0f);
    }
    angle -= base;
    if (insect->tools_actor.actor_class.world.position.y < angle) {
        insect->tools_actor.actor_class.position_speed.y = 2.0f + fqrand();
    }
    chase_f(&insect->tools_actor.actor_class.position_speed.y, insect->tools_actor.actor_class.max_velocity_y,
            0.5f * insect->tools_actor.actor_class.gravity);
}

static int aICH_flower_search_sub(aINS_INSECT_ACTOR* insect, int type) {
    static int add_table[] = {
        -1,
        0,
        1,
    };
    static int add_table2[] = {
        -2,
        0,
        2,
    };

    int bx;
    int bz;

    mActor_name_t* fg;
    int ret;
    xyz_t pos;

    ret = FALSE;
    bx = insect->s32_work1;
    bz = insect->s32_work2;
    fg = mFI_BkNumtoUtFGTop(insect->tools_actor.actor_class.block_x, insect->tools_actor.actor_class.block_z);
    if (type == 2) {
        bx += add_table2[RANDOM(3)];
        bz += add_table2[RANDOM(3)];
    } else {
        bx += add_table[RANDOM(3)];
        bz += add_table[RANDOM(3)];
    }
    if ((bx < 1) || (bx > 14)) {
        bx = insect->s32_work1;
    }
    if ((bz < 1) || (bz > 14)) {
        bz = insect->s32_work2;
    }
    if ((type == 0) || (mFI_CheckFGNpcOn(*(fg + bx + (bz * 16))) == TRUE)) {
        mFI_BkandUtNum2CenterWpos(&pos, insect->tools_actor.actor_class.block_x,
                                  insect->tools_actor.actor_class.block_z, bx, bz);
        if ((mCoBG_GetBgY_OnlyCenter_FromWpos(pos, 0.0f) - insect->tools_actor.actor_class.world.position.y) < 20.0f) {
            insect->s32_work1 = bx;
            ret = TRUE;
            insect->s32_work2 = bz;
            insect->f32_work0 = pos.x;
            insect->f32_work1 = pos.z;
        } else if (type != 2) {
            ret = aICH_flower_search_sub(insect, 2);
        }
    }
    return ret;
}

static void aICH_flower_search(aINS_INSECT_ACTOR* insect) {
    int bx, bz;
    mActor_name_t* unit;

    mFI_Wpos2UtNum(&bx, &bz, insect->tools_actor.actor_class.world.position);
    unit = mFI_UtNum2UtFG(bx, bz);

    if ((!(fqrand() < 0.5f) || (unit == NULL) || (((*unit < FLOWER_PANSIES0))) || (*unit > FLOWER_TULIP2)) &&
        (insect->type != aINS_INSECT_TYPE_PURPLE_BUTTERFLY)) {
        aICH_flower_search_sub(insect, 1);
    }
}

static void aICH_loop_move_ctrl(aINS_INSECT_ACTOR* insect) {
    static f32 ptX_table[] = {10.0f, 10.0f, -10.0f, -10.0f};
    static f32 ptZ_table[] = {10.0f, -10.0f, 10.0f, -10.0f};
    static f32 chkX_table[] = {-1.0f, 1.0f, 1.0f, -1.0f};
    static f32 chkZ_table[] = {-1.0f, 1.0f, -1.0f, 1.0f};

    f32 x;
    f32 z;
    f32 sq;
    s16 angle;
    s16 stepVal;
    int idx = insect->s32_work0;

    x = insect->tools_actor.actor_class.world.position.x - (insect->f32_work0 + ptX_table[idx]);
    z = insect->tools_actor.actor_class.world.position.z - (insect->f32_work1 + ptZ_table[idx]);

    sq = sqrtf((x * x) + (z * z));
    angle = atans_table(-z, -x);

    if (sq < 15.0f) {
        stepVal = 0x800;
    } else {
        stepVal = 0x400;
    }

    chase_angle(&insect->tools_actor.actor_class.shape_info.rotation.y, angle, stepVal);
    insect->tools_actor.actor_class.world.angle.y = insect->tools_actor.actor_class.shape_info.rotation.y;

    if (((x * chkX_table[idx]) < 0.0f) || ((z * chkZ_table[idx]) < 0.0f)) {
        if (insect->s32_work3 == 0) {
            insect->s32_work3 = 1;
            insect->s32_work0 += 1;
            if (insect->s32_work0 > 3) {
                insect->s32_work0 = 0;
                aICH_flower_search(insect);
            }
        }
    } else {
        insect->s32_work3 = 0;
    }
}

static void aICH_avoid_player(aINS_INSECT_ACTOR* insect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    static s16 add_angl[] = {0xF000, 0x1000};
    PLAYER_ACTOR* player;

    player = GET_PLAYER_ACTOR(play);

    if (player != NULL) {
        s16 angle = search_position_angleY(&insect->tools_actor.actor_class.world.position,
                                           &player->actor_class.world.position) + 0x8000;
        angle += add_angl[(play->game.frame_counter >> 5) & 1];
        chase_angle(&insect->tools_actor.actor_class.shape_info.rotation.y, (angle), 0x600);
        insect->tools_actor.actor_class.world.angle.y = insect->tools_actor.actor_class.shape_info.rotation.y;
    }
} 
static void aICH_avoid_move_ctrl(aINS_INSECT_ACTOR* insect, GAME* game) {
    int bx, bz;
    xyz_t pos;
    s16 angle;

    if (mFI_Wpos2UtNum(&bx, &bz, insect->tools_actor.actor_class.world.position) == TRUE) {
        if (((bx & 0xF) >= 1) && ((bx & 0xF) < 0xF)) {
            if (((bz & 0xF) >= 1) && ((bz & 0xF) < 0xF)) {
                aICH_avoid_player(insect, game);
                return;
            }
        }
        mFI_BkandUtNum2Wpos(&pos, insect->tools_actor.actor_class.block_x, insect->tools_actor.actor_class.block_z, 8,
                            8);
        angle = atans_table(pos.z - insect->tools_actor.actor_class.world.position.z,
                            pos.x - insect->tools_actor.actor_class.world.position.x);
        chase_angle(&insect->tools_actor.actor_class.shape_info.rotation.y, angle, 0x600);
        insect->tools_actor.actor_class.world.angle.y = insect->tools_actor.actor_class.shape_info.rotation.y;

    } else {
        aICH_avoid_player(insect, game);
    }
}

static void aICH_rest_check(aINS_INSECT_ACTOR* insect, GAME* game) {
    mActor_name_t* unit;

    if (F32_IS_ZERO(insect->f32_work3)) {
        unit = mFI_GetUnitFG(insect->tools_actor.actor_class.world.position);
        if ((unit != NULL) && (*unit == FLOWER_PANSIES0)) {
            aICH_setupAction(insect, aINS_INSECT_TYPE_PURPLE_BUTTERFLY, game);
        }
    } else {
        insect->f32_work3 -= 0.5f;
        if (insect->f32_work3 < 0.0f) {
            insect->f32_work3 = 0.0f;
        }
    }
}

static void aICH_chou_fuwafuwa(aINS_INSECT_ACTOR* insect) {
    f32 saveSpAng = 10.0f * sin_s(insect->flag);
    f32 curSpAng;

    insect->flag += 0x800;
    curSpAng = 10.0f * sin_s(insect->flag);

    insect->tools_actor.actor_class.position_speed.y = insect->tools_actor.actor_class.gravity + (curSpAng - saveSpAng);
}

static int aICH_check_ball(aINS_INSECT_ACTOR* insect) {
    int ret = FALSE;

    f32 xDiff = Common_Get(ball_pos).x - insect->tools_actor.actor_class.world.position.x;
    f32 zDiff = Common_Get(ball_pos).z - insect->tools_actor.actor_class.world.position.z;

    if (((xDiff * xDiff) + (zDiff * zDiff)) < 3600.0f) {
        ret = TRUE;
    }
    return ret;
}

static int aICH_check_player_net(aINS_INSECT_ACTOR* insect) {
    f32 xDiff;
    f32 zDiff;
    int ret;
    xyz_t pos;

    ret = FALSE;
    if (mPlib_Check_StopNet(&pos) == TRUE) {
        uintptr_t label = mPlib_Get_item_net_catch_label();
        if ((label != (uintptr_t)insect)) {
            xDiff = pos.x - insect->tools_actor.actor_class.world.position.x;
            zDiff = pos.z - insect->tools_actor.actor_class.world.position.z;

            if (((xDiff * xDiff) + (zDiff * zDiff)) < 3600.0f) {
                ret = TRUE;
            }
        }
    }

    return ret;
}

static int aICH_check_player_scoop(aINS_INSECT_ACTOR* insect) {
    f32 xDiff;
    f32 zDiff;
    int ret;
    xyz_t pos;

    ret = FALSE;
    if (mPlib_Check_DigScoop(&pos) == TRUE) {
        xDiff = pos.x - insect->tools_actor.actor_class.world.position.x;
        zDiff = pos.z - insect->tools_actor.actor_class.world.position.z;

        if (((xDiff * xDiff) + (zDiff * zDiff)) < 3600.0f) {
            ret = TRUE;
        }
    }

    return ret;
}

static int aICH_check_patience(aINS_INSECT_ACTOR* insect) {
    int ret;

    ret = FALSE;
    if (aICH_check_ball(insect) == TRUE) {
        insect->patience = 100.0f;
    } else if (aICH_check_player_net(insect) == TRUE) {
        insect->patience = 100.0f;
    } else if (aICH_check_player_scoop(insect) == TRUE) {
        insect->patience = 100.0f;
    }
    if (insect->patience >= 90.0f) {
        ret = TRUE;
    }

    return ret;
}

static void aICH_BGcheck(ACTOR* actor) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    if ((insect->tools_actor.actor_class.bg_collision_check.result.hit_wall & mCoBG_HIT_WALL_FRONT) != 0) {
        if (insect->f32_work2 <= 0.0f) {
            switch (insect->type) {
                case aINS_INSECT_TYPE_TIGER_BUTTERFLY:
                case aINS_INSECT_TYPE_PURPLE_BUTTERFLY:
                    if (aICH_flower_search_sub(insect, 0) == TRUE) {
                        insect->f32_work2 = 10.0f;
                    }
                    break;
                default:
                    if (aICH_flower_search_sub(insect, 1) == TRUE) {
                        insect->f32_work2 = 10.0f;
                    }
                    break;
            }
        }
    }
    insect->f32_work2 -= 1.0f;
    if (insect->f32_work2 < 0.0f) {
        insect->f32_work2 = 0.0f;
    }
}

static void aICH_check_block_edge(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    int bx, bz;

    if (insect->action != aICH_ACTION_LET_ESCAPE) {
        if (mFI_Wpos2UtNum_inBlock(&bx, &bz, actor->world.position) == FALSE) {
            aICH_setupAction(insect, aICH_ACTION_LET_ESCAPE, game);
        } else if ((bx < 1) || (bx > 0xE) || (bz < 1) || (bz > 0xE)) {
            aICH_setupAction(insect, aICH_ACTION_LET_ESCAPE, game);
        }
    }
}

static void aICH_avoid(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    f32 base;

    aICH_anime_proc(insect);
    switch (insect->type) {
        case aINS_INSECT_TYPE_TIGER_BUTTERFLY:
            base = -80.0f;
            break;
        case aINS_INSECT_TYPE_PURPLE_BUTTERFLY:
            base = -100.0f;
            break;
        default:
            base = -60.0f;
            break;
    }
    aICH_jump_ctrl(insect, base);
    aICH_avoid_move_ctrl(insect, game);
    if (insect->patience < 70.0f) {
        mFI_Wpos2UtNum_inBlock(&insect->s32_work1, &insect->s32_work2, actor->world.position);
        aICH_setupAction(insect, aICH_ACTION_FLY, game);
    }
}

static void aICH_let_escape(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;

    aICH_chou_fuwafuwa(insect);
    actor->gravity += 0.1f;
    aICH_anime_proc(insect);
}

static void aICH_fly(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    f32 base;

    aICH_anime_proc(insect);
    aICH_BGcheck(actor);

    switch (insect->type) {
        case aINS_INSECT_TYPE_TIGER_BUTTERFLY:
            base = -40.0f;
            break;
        case aINS_INSECT_TYPE_PURPLE_BUTTERFLY:
            base = -50.0f;
            break;
        default:
            base = -30.0f;
            break;
    }

    aICH_jump_ctrl(insect, base);
    aICH_loop_move_ctrl(insect);

    switch (insect->type) {
        case aINS_INSECT_TYPE_TIGER_BUTTERFLY:
            if (insect->patience > 90.0f) {
                aICH_setupAction(insect, aICH_ACTION_AVOID, game);
                break;
            }
            aICH_rest_check(insect, game);
            break;
        case aINS_INSECT_TYPE_PURPLE_BUTTERFLY:
            if (insect->patience > 90.0f) {
                aICH_setupAction(insect, aICH_ACTION_AVOID, game);
                break;
            }
            break;
        default:
            aICH_rest_check(insect, game);
            break;
    }
}

static void aICH_landing(ACTOR* actor, GAME* game) {
    static xyz_t rest_wait_data[] = {
        {-11.0f, -22.0f, -4.0f},
        {10.0f, -22.0f, -8.0f},
        {2.0f, -24.0f, 14.0f},
    };
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;

    aICH_anime_proc(insect);
    if (aICH_check_patience(insect) == TRUE) {
        int action;
        switch (insect->type) {
            case aINS_INSECT_TYPE_TIGER_BUTTERFLY:
            case aINS_INSECT_TYPE_PURPLE_BUTTERFLY:
                action = aICH_ACTION_AVOID;
                break;
            default:
                action = 2;
                break;
        }
        aICH_setupAction(insect, action, game);
    } else {
        xyz_t pos;
        s16 angle;
        mFI_BkandUtNum2CenterWpos(&pos, actor->block_x, actor->block_z, insect->s32_work1, insect->s32_work2);

        pos.x += rest_wait_data[insect->light_flag].x;
        insect->bg_height = rest_wait_data[insect->light_flag].y;
        pos.z += rest_wait_data[insect->light_flag].z;
        switch (insect->type) {
            case aINS_INSECT_TYPE_COMMON_BUTTERFLY:
            case aINS_INSECT_TYPE_YELLOW_BUTTERFLY:
                insect->bg_height -= 3.0f;
                break;
        }
        angle = search_position_angleY(&actor->world.position, &pos);
        chase_angle(&actor->shape_info.rotation.y, angle, 0x1000);
        actor->world.angle.y = actor->shape_info.rotation.y;
        if (F32_IS_ZERO(insect->target_speed) ||
            ((fabsf(actor->world.position.x - pos.x) < 2.0f) && (fabsf(actor->world.position.z - pos.z) < 2.0f))) {
            aICH_setupAction(insect, aICH_ACTION_HOVER, game);
        }
    }
}

static void aICH_hover(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    int action;

    if (insect->action == aICH_ACTION_HOVER) {
        aICH_anime_proc(insect);
    }
    if (aICH_check_patience(insect) == TRUE) {
        switch (insect->type) {
            case aINS_INSECT_TYPE_TIGER_BUTTERFLY:
            case aINS_INSECT_TYPE_PURPLE_BUTTERFLY:
                action = aICH_ACTION_AVOID;
                break;
            default:
                action = aICH_ACTION_FLY;
                break;
        }
        aICH_setupAction(insect, action, game);
    } else {
        insect->timer--;
        if (insect->timer <= 0) {
            action = aICH_ACTION_REST;
            if (insect->action == aICH_ACTION_REST) {
                action = aICH_ACTION_FLY;
            }
            aICH_setupAction(insect, action, game);
        }
    }
}

static void aICH_avoid_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->bg_height = 0.0f;
    insect->target_speed = 3.0f;
    insect->speed_step = 0.3f;
    insect->tools_actor.actor_class.speed = 2.0f;
}

static void aICH_let_escape_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player;
    
    insect->life_time = 0;
    insect->alpha_time = 0x50;
    insect->tools_actor.actor_class.shape_info.rotation.x = 0;
    insect->bg_height = 0.0f;
    insect->flag = 0;
    
    insect->tools_actor.actor_class.home.position.y = insect->tools_actor.actor_class.world.position.y;
    insect->tools_actor.actor_class.speed = 1.5f;
    player = get_player_actor_withoutCheck(play);
    
    if (player != NULL) {
        s16 angle = player->actor_class.shape_info.rotation.y + (s16)(21845.0f * (fqrand() - 0.5f));
        insect->tools_actor.actor_class.world.angle.y = angle;
        insect->tools_actor.actor_class.shape_info.rotation.y = angle;
    }
    
    insect->insect_flags.bit_1 = TRUE;
    insect->insect_flags.bit_2 = TRUE;
}

static void aICH_fly_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->bg_height = 0.0f;
    insect->tools_actor.actor_class.gravity = 0.3f;
    insect->tools_actor.actor_class.max_velocity_y = -2.0f;
    insect->target_speed = 2.0f;
    insect->speed_step = 0.2f;
    
    insect->s32_work0 = 0;
    insect->s32_work3 = 0;
    
    insect->f32_work0 = insect->tools_actor.actor_class.world.position.x;
    insect->f32_work1 = insect->tools_actor.actor_class.world.position.z;
    insect->f32_work2 = 0.0f;
    insect->f32_work3 = 120.0f;
    
    aICH_flower_search(insect);
}

static void aICH_landing_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    
    insect->light_flag = play->game_frame % 3;
    insect->tools_actor.actor_class.position_speed.y = 0.0f;
}

static void aICH_hover_init(aINS_INSECT_ACTOR* insect, GAME* arg1) {
    insect->target_speed = 0.0f;
    insect->speed_step = 0.0f;
    insect->tools_actor.actor_class.speed = 0.0f;
    insect->timer = 10;
}

static void aICH_rest_init(aINS_INSECT_ACTOR* insect, GAME* arg1) {
    insect->_1E0 = 1.0f;
    insect->timer =  (0.5f * (30.0f + (RANDOM_F(60)))); 
}

typedef void (*aICH_INIT_PROC)(aINS_INSECT_ACTOR*, GAME*);

static void aICH_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game) {
    static aICH_INIT_PROC init_proc[] = {
        &aICH_avoid_init, aICH_let_escape_init, aICH_fly_init,  aICH_landing_init,
        aICH_hover_init, aICH_rest_init,
    };

    static aINS_ACTION_PROC act_proc[] = {
        aICH_avoid,
        aICH_let_escape,
        aICH_fly,
        aICH_landing,
        aICH_hover,
        aICH_hover,
    };

    insect->action = action;
    insect->action_proc = act_proc[action];
    (*init_proc[action])(insect, game);
}

static void aICH_actor_move(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;
 
    uintptr_t label = mPlib_Get_item_net_catch_label();

    if (label == (uintptr_t)actor) {
        insect->alpha0 = 255;
        aICH_anime_proc(insect);
        aICH_setupAction(insect, aICH_ACTION_LET_ESCAPE, game);
    }
    else if((insect->insect_flags.bit_3 == TRUE) && (insect->insect_flags.bit_2 == FALSE)){
        aICH_setupAction(insect, aICH_ACTION_LET_ESCAPE, game);
    } else {
        aICH_check_block_edge(actor, game);
        insect->action_proc(actor,game);
    }
}
