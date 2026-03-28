#include "ac_ins_batta.h"

#include "m_field_info.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "ac_set_ovl_insect.h"

enum {
    aIBT_ACTION_AVOID,
    aIBT_ACTION_LET_ESCAPE,
    aIBT_ACTION_CHANGE_DIRECTION,
    aIBT_ACTION_WAIT,
    aIBT_ACTION_JUMP,
    aIBT_ACTION_DROWN,

    aIBT_ACTION_NUM
};

static int aIBT_check_live_condition(aINS_INSECT_ACTOR*);
static void aIBT_actor_move(ACTOR*,GAME*);
static void aIBT_actor_first_move(ACTOR*,GAME*);
static void aIBT_setupAction(aINS_INSECT_ACTOR*,int, GAME*);


extern void aIBT_actor_init(ACTOR* actor, GAME* game) {
    PLAYER_ACTOR* player;
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;

    actor->gravity = 0.2f;
    actor->max_velocity_y = -20.0f;

    insect->bg_type = 2;
    switch (insect->type) {
        case aINS_INSECT_TYPE_LONG_LOCUST:
            insect->item = ITM_INSECT13;
            break;
        case aINS_INSECT_TYPE_MIGRATORY_LOCUST:
            insect->item = ITM_INSECT14;
            break;
        case aINS_INSECT_TYPE_CRICKET:
            insect->item = ITM_INSECT15;
            break;
        case aINS_INSECT_TYPE_GRASSHOPPER:
            insect->item = ITM_INSECT16;
            break;
        case aINS_INSECT_TYPE_BELL_CRICKET:
            insect->item = ITM_INSECT17;
            break;
        case aINS_INSECT_TYPE_PINE_CRICKET:
            insect->item = ITM_INSECT18;
            break;
    }
    insect->insect_flags.bit_4 = FALSE;

    if (actor->actor_specific == 0) {
        if (aIBT_check_live_condition(insect) == TRUE) {
            actor->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos(actor->world.position, 0.0f);
            actor->mv_proc = aIBT_actor_first_move;
            mFI_BkNum2WposXZ(&insect->f32_work2, &insect->f32_work3, actor->block_x, actor->block_z);
            insect->f32_work2 += 320.0f;
            insect->f32_work3 += 320.0f;
            aIBT_setupAction(insect, aIBT_ACTION_CHANGE_DIRECTION, game);
        }
    } else {
        GAME_PLAY* play = (GAME_PLAY*)game;
        player = GET_PLAYER_ACTOR(play);
        if (player != NULL) {
            actor->world.position.y = 40.0f + player->actor_class.world.position.y;
        }
        actor->mv_proc = aIBT_actor_move;
        aIBT_setupAction(insect, aIBT_ACTION_LET_ESCAPE, game);
    }
}

static int aIBT_check_live_condition(aINS_INSECT_ACTOR* insect) {
    int cond;

    cond = TRUE;
    if (mCoBG_ExistHeightGap_KeepAndNow(insect->tools_actor.actor_class.world.position) == TRUE) {
        cond = FALSE;
    } else if (Common_Get(weather) == mEnv_WEATHER_RAIN) {
        cond = FALSE;
    } else {
        mActor_name_t* item;
        item = mFI_GetUnitFG(insect->tools_actor.actor_class.world.position);
        if ((item == NULL) || (*item == RSV_NO)) {
            cond = FALSE;
        } else if ((*item >= HOLE_START) && (*item <= HOLE_END)) {
            cond = FALSE;
        } else {
            switch ((*item >> 0xC) & 0xF) {
                case 4:
                    break;
                case 1:
                case 2:
                case 3:
                case 5:
                    cond = FALSE;
                    break;
            }
        }
    }
    if (cond == FALSE) {
        insect->insect_flags.destruct = TRUE;
    }
    return cond;
}

static void aIBT_anime_proc(aINS_INSECT_ACTOR* insect) {
    switch (insect->type) {
        case aINS_INSECT_TYPE_BELL_CRICKET:
            insect->_1E0 += 1.0f;
            break;
        default:
            insect->_1E0 += 0.3f;
            break;
    }

    if (insect->_1E0 >= 2.0f) {
        insect->_1E0 -= 2.0f;
    }
}

static int aIBT_check_ball(aINS_INSECT_ACTOR* insect) {
    f32 x, z;
    int ret = 0;

    x = Common_Get(ball_pos).x - insect->tools_actor.actor_class.world.position.x;
    z = Common_Get(ball_pos).z - insect->tools_actor.actor_class.world.position.z;
    if (((x * x) + (z * z)) < 3600.0f) {
        ret = 1;
    }
    return ret;
}

static void aIBT_set_fly_se(aINS_INSECT_ACTOR* insect) {
    switch (insect->type) {
        case aINS_INSECT_TYPE_LONG_LOCUST:
            sAdo_OngenPos((uintptr_t)insect, 0xA2, &insect->tools_actor.actor_class.world.position);
            break;
        case aINS_INSECT_TYPE_MIGRATORY_LOCUST:
            sAdo_OngenPos((uintptr_t)insect, 0xA3, &insect->tools_actor.actor_class.world.position);
            break;
    }
}

static int aIBT_check_player_net_sub(xyz_t* net_pos, aINS_INSECT_ACTOR* insect) {
    int ret;
    u32 label;

    ret = FALSE;
    if (mPlib_Check_StopNet(net_pos) == TRUE) {
        uintptr_t label = mPlib_Get_item_net_catch_label();
        if (label == (uintptr_t)insect) {
            ret = TRUE;
        }
    }
    return ret;
}

static int aIBT_check_player_net(aINS_INSECT_ACTOR* insect) {
    xyz_t arg;
    int ret;

    ret = FALSE;
    if (insect->s32_work1 == 0) {
        if (aIBT_check_player_net_sub(&arg, insect) == TRUE) {
            ret = TRUE;
            insect->s32_work1 = 1;
        } else {
            aIBT_set_fly_se(insect);
        }
    } else {
        ret = TRUE;
    }
    return ret;
}

static int aIBT_check_player_net2(aINS_INSECT_ACTOR* insect) {
    xyz_t pos;
    f32 x, z;
    int ret;

    ret = FALSE;
    if (mPlib_Check_StopNet(&pos) == TRUE) {
        uintptr_t label = mPlib_Get_item_net_catch_label();
        if (label == (uintptr_t)insect) {
            insect->s32_work1 = 1;
        } else {
            x = pos.x - insect->tools_actor.actor_class.world.position.x;
            z = pos.z - insect->tools_actor.actor_class.world.position.z;
            if (((x * x) + (z * z)) < 4900.0f) {
                ret = TRUE;
            }
        }
    }
    return ret;
}

static int aIBT_check_player_scoop(aINS_INSECT_ACTOR* insect) {
    xyz_t pos;
    f32 x, z;
    int ret;

    ret = FALSE;
    if (mPlib_Check_DigScoop(&pos) == TRUE) {
        x = pos.x - insect->tools_actor.actor_class.world.position.x;
        z = pos.z - insect->tools_actor.actor_class.world.position.z;
        if (((x * x) + (z * z)) < 4900.0f) {
            ret = TRUE;
        }
    }
    return ret;
}

static int aIBT_check_patience(aINS_INSECT_ACTOR* insect, GAME* game) {
    int ret;

    ret = FALSE;

    if (aIBT_check_ball(insect) == TRUE) {
        insect->patience = 100.0f;
    } else if (aIBT_check_player_net2(insect) == TRUE) {
        insect->patience = 100.0f;
    } else if (aIBT_check_player_scoop(insect) == TRUE) {
        insect->patience = 100.0f;
    }
    if (insect->patience >= 90.0f) {
        ret = TRUE;
    }
    return ret;
}

static void aIBT_chk_avoid_jump_angle(ACTOR* actor, s16 chkAngle) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*) actor;
    s16 currentAngle = chkAngle;

    if (insect->tools_actor.actor_class.bg_collision_check.result.hit_wall & mCoBG_HIT_WALL_FRONT) {
        currentAngle = insect->tools_actor.actor_class.world.angle.y;
        currentAngle +=  (((((RANDOM(2)) * 2) - 1) << 0xE));
    }
    insect->tools_actor.actor_class.world.angle.y = currentAngle;
    insect->tools_actor.actor_class.shape_info.rotation.y = currentAngle;
}

static void aIBT_set_avoid_jump_spd(aINS_INSECT_ACTOR* insect) {
    s_xyz angle;
    f32 mod;
    int absRot;

    switch (insect->type) {
        case aINS_INSECT_TYPE_MIGRATORY_LOCUST:
            insect->tools_actor.actor_class.speed = 7.5f;
            insect->tools_actor.actor_class.position_speed.y = 9.0f;
            insect->tools_actor.actor_class.gravity = 0.6f;
            break;
        default:
            mod = 3.0f;
            absRot = ABS(insect->tools_actor.actor_class.shape_info.rotation.y);
            if (absRot > 0x4000) {
                mCoBG_GetBgY_AngleS_FromWpos(&angle, insect->tools_actor.actor_class.world.position, 0.0f);
                if (angle.x > 0) {
                    mod += (3.0f * sin_s(angle.x));
                }
            }
            insect->tools_actor.actor_class.speed = 5.0f;
            insect->tools_actor.actor_class.position_speed.y = mod;
            insect->tools_actor.actor_class.gravity = 0.3f;
            break;
    }
}

static int aIBT_chk_active_range(s16* range, aINS_INSECT_ACTOR* insect) {
    f32 z, x;
    int ret;

    ret = TRUE;
    x = insect->f32_work2 - insect->tools_actor.actor_class.world.position.x;
    z = insect->f32_work3 - insect->tools_actor.actor_class.world.position.z;
    if (((x * x) + (z * z)) >= 57600.0f) {
        if (range != NULL) {
            *range = atans_table(z, x);
        }
        ret = FALSE;
    }
    return ret;
}

static void aIBT_avoid(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;
    
    PLAYER_ACTOR* player;
    f32 timer;
    s16 angle;

    aIBT_anime_proc(insect);
    if (insect->tools_actor.actor_class.bg_collision_check.result.is_in_water) {
        aIBT_setupAction(insect, aIBT_ACTION_DROWN, &play->game);
    } else if ((aIBT_check_player_net(insect) == FALSE) &&
               (insect->tools_actor.actor_class.bg_collision_check.result.on_ground)) {
        if (insect->timer > 0) {
            insect->timer--;
            insect->tools_actor.actor_class.speed = 0.0f;
        } else {
            insect->timer = 8;
            if (insect->patience < 85.0f) {
                timer = 5.0f + (RANDOM_F(10.0f));
                insect->timer = (2.0f * timer);
                aIBT_setupAction(insect, aIBT_ACTION_CHANGE_DIRECTION, &play->game);

            } else {
                if (aIBT_chk_active_range(&angle, insect) == TRUE) {
                    player = GET_PLAYER_ACTOR(play);
                    if (player != NULL) {
                        angle = search_position_angleY(&insect->tools_actor.actor_class.world.position,
                                                       &player->actor_class.world.position) +
                                0x8000;
                    } else {
                        angle = insect->tools_actor.actor_class.shape_info.rotation.y;
                    }
                }
                aIBT_chk_avoid_jump_angle(actor, angle);
                aIBT_set_avoid_jump_spd(insect);
            }
        }
    }
}

static void aIBT_let_escape(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;

    aIBT_anime_proc(insect);
    if (insect->tools_actor.actor_class.bg_collision_check.result.is_in_water) {
        aIBT_setupAction(insect, aIBT_ACTION_DROWN, game);
    } else {
        if (insect->tools_actor.actor_class.bg_collision_check.result.on_ground) {
            if (insect->timer > 0) {
                insect->timer--;
                insect->tools_actor.actor_class.speed = 0.0f;
            } else {
                insect->timer = 8;
                aIBT_chk_avoid_jump_angle(actor, insect->tools_actor.actor_class.world.angle.y);
                aIBT_set_avoid_jump_spd(insect);
            }
        } else {
            aIBT_set_fly_se(insect);
        }
    }
}

static void aIBT_chg_direction(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;

    static f32 range[] = {
        4096.0f,  4096.0f,  8192.0f,  8192.0f,  8192.0f,  12288.0f, 12288.0f, 12288.0f, 12288.0f,
        12288.0f, 16384.0f, 16384.0f, 16384.0f, 16384.0f, 16384.0f, 16384.0f,
    };

    u32 attr;
    xyz_t pos;
    f32 mod;
    s16 angle;
    f32 bgY;
    f32 yDir;
    if (aIBT_chk_active_range(&angle, insect) == FALSE) {
        insect->tools_actor.actor_class.world.angle.y = angle;
        aIBT_setupAction(insect, aIBT_ACTION_WAIT, game);
    } else {
        angle = insect->tools_actor.actor_class.shape_info.rotation.y + 0x8000;
        angle += (s16)(range[insect->s32_work0] * (2.0f * (fqrand() - 0.5f)));
        xyz_t_move(&pos, &insect->tools_actor.actor_class.world.position);
        mod = 53.0f;
        if (insect->type == aINS_INSECT_TYPE_MIGRATORY_LOCUST) {
            mod = 218.0f;
        }
        pos.x += (mod * sin_s(angle));
        pos.z += (mod * cos_s(angle));
        bgY = mCoBG_GetBgY_AngleS_FromWpos(NULL, pos, 0.0f);
        attr = mCoBG_Wpos2Attribute(pos, NULL);
        yDir = insect->tools_actor.actor_class.world.position.y - bgY;
        yDir = (yDir >= 0.0f) ? yDir : -yDir;
        if ((yDir < 40.0f) && (mCoBG_CheckWaterAttribute(attr) == FALSE)) {
            insect->tools_actor.actor_class.world.angle.y = angle;
            aIBT_setupAction(insect, aIBT_ACTION_WAIT, game);
        } else {
            insect->s32_work0 += 1;
            if (insect->s32_work0 > 0xF) {
                aIBT_setupAction(insect, aIBT_ACTION_WAIT, game);
            }
        }
    }
}

static void aIBT_wait(ACTOR* actor, GAME* game) {
    static u8 batta_sound_data[] = {
        159,158,160,157,
    };
    GAME_PLAY* play;
    aINS_INSECT_ACTOR* insect;


    play = (GAME_PLAY*)game;
    insect = (aINS_INSECT_ACTOR*)actor;

    
    if (actor->bg_collision_check.result.is_in_water) {
        aIBT_setupAction(insect, aIBT_ACTION_DROWN, game);

    } else if (aIBT_check_patience(insect,game) == TRUE) {
        aIBT_setupAction(insect, aIBT_ACTION_AVOID, game);
    } else {
        add_calc_short_angle2(&actor->shape_info.rotation.y,
                              actor->world.angle.y, CALC_EASE(0.5f), 0x2000, 0);

        if ((insect->type >= 0xF) || (insect->type < 0xD)) {
            int idx = insect->type - 15;
            if ((actor->bg_collision_check.result.on_ground) &&
                (insect->patience < 20.0f)) {
                if (insect->type == aINS_INSECT_TYPE_BELL_CRICKET) {
                    aIBT_anime_proc(insect);
                }
                if (insect->s32_work1 == 0) {
                    sAdo_OngenPos((uintptr_t)insect, batta_sound_data[idx], &actor->world.position);
                }
            }
        }
        if (insect->timer > 0) {
            insect->timer--;

        } else {
            int action;
            action = aIBT_ACTION_CHANGE_DIRECTION;
            if (aIBT_chk_active_range(NULL, insect) == FALSE) {
                action = aIBT_ACTION_JUMP;
            } else {
                if ((insect->type == aINS_INSECT_TYPE_LONG_LOCUST) || (insect->type == aINS_INSECT_TYPE_MIGRATORY_LOCUST)) {
                    if ((int)(play->game_frame % 200) > 20) {
                        action = aIBT_ACTION_JUMP;
                    }
                } else if ((int)(play->game_frame % 200) < 20) {
                    action = aIBT_ACTION_JUMP;
                }
            }
            aIBT_setupAction(insect, action, game);
        }
    }
}

static void aIBT_jump(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;
    if (insect->tools_actor.actor_class.bg_collision_check.result.on_ground){
        aIBT_setupAction(insect, aIBT_ACTION_CHANGE_DIRECTION, game);
    }
}

static void aIBT_avoid_init(aINS_INSECT_ACTOR* insect, GAME* game) {

    GAME_PLAY* play = (GAME_PLAY*)game;
    
    s16 angle;
    PLAYER_ACTOR* player;
    player = get_player_actor_withoutCheck(play);
    insect->tools_actor.actor_class.gravity = 0.2f;
    insect->timer = 0;
    if (player != NULL) {
        angle = (search_position_angleY(&insect->tools_actor.actor_class.world.position,
                                        &player->actor_class.world.position) -
                 0x8000);
        angle += (s16)(8192.0f * (2.0f * (fqrand() - 0.5f)));
        insect->tools_actor.actor_class.shape_info.rotation.y = angle;
        insect->tools_actor.actor_class.world.angle.y = angle;

    }    
}

static void aIBT_let_escape_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    PLAYER_ACTOR* player;
    s16 chkAngle;
    GAME_PLAY* play = (GAME_PLAY*)game;

    player = get_player_actor_withoutCheck(play);
    insect->life_time = 0;
    insect->alpha_time = 80;
    insect->tools_actor.actor_class.gravity = 0.2f;
    insect->timer = 0;
    insect->tools_actor.actor_class.speed = 5.0f;
    insect->tools_actor.actor_class.position_speed.y = 3.0f;
    
    if (player != NULL) {
        chkAngle = player->actor_class.shape_info.rotation.y + (s16)(21845.0f * (fqrand() - 0.5f));
        insect->tools_actor.actor_class.world.angle.y = chkAngle;
        insect->tools_actor.actor_class.shape_info.rotation.y = chkAngle;
    }
    insect->insect_flags.bit_1 = TRUE;
    insect->insect_flags.bit_2 = TRUE;
}

static void aIBT_chg_direction_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->s32_work0 = 0;
    insect->_1E0 = 0.0f;
    insect->tools_actor.actor_class.speed = 0.0f;
}

static void aIBT_wait_init(aINS_INSECT_ACTOR* insect, GAME* game)  {
    GAME_PLAY* play = (GAME_PLAY*)game;
    
    if (aIBT_chk_active_range(NULL, insect) == FALSE) {
        insect->timer = 60;
    }
    else{
        insect->timer = (2.0f * (120.0f + (play->game_frame % 240)));
    }
}

static void aIBT_jump_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->tools_actor.actor_class.position_speed.y = 4.0f;
    insect->tools_actor.actor_class.speed = 5.5f;
    insect->tools_actor.actor_class.gravity = 0.7f;
}


static void aIBT_drown_init(aINS_INSECT_ACTOR* insect, GAME* game)  {
    xyz_t pos = insect->tools_actor.actor_class.world.position;
    f32 height = mCoBG_GetWaterHeight_File(pos, "ac_ins_batta.c", 995);

    pos.y = height;
    
    eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_MIZU, pos, 1,insect->tools_actor.actor_class.world.angle.y, game, 0, 4, 0);
    sAdo_OngenTrgStart(0x438,&insect->tools_actor.actor_class.world.position);
    
    insect->insect_flags.bit_1 = TRUE;
    insect->insect_flags.destruct = TRUE;
    insect->tools_actor.actor_class.shape_info.draw_shadow = FALSE;
}

typedef void (*aIBT_INIT_PROC)(aINS_INSECT_ACTOR*, GAME*);

static void aIBT_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game) {
    static aIBT_INIT_PROC init_proc[] = {
        &aIBT_avoid_init,
        &aIBT_let_escape_init,
        &aIBT_chg_direction_init,
        &aIBT_wait_init,
        &aIBT_jump_init,
        &aIBT_drown_init,
    };

    static aINS_ACTION_PROC act_proc[] = {
        &aIBT_avoid,
        &aIBT_let_escape,
        &aIBT_chg_direction,
        &aIBT_wait,
        &aIBT_jump,
        (aINS_ACTION_PROC)&none_proc1,
    };

    insect->action = action;
    insect->action_proc = act_proc[action];
    (*init_proc[action])(insect, game);
}

void aIBT_actor_move(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;

    uintptr_t label = mPlib_Get_item_net_catch_label();

    if (label == (uintptr_t)actor) {
        aIBT_setupAction(insect, aIBT_ACTION_LET_ESCAPE, game);
    } else {
        if (insect->insect_flags.bit_3 == TRUE && insect->insect_flags.bit_2 == FALSE) {
            aIBT_setupAction(insect, aIBT_ACTION_LET_ESCAPE, game);
        }
        else
        insect->action_proc(actor,game);
    }
}

static void aIBT_actor_first_move(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    if ((insect->flag < 2) && (aIBT_check_live_condition(insect) == TRUE)) {
        insect->flag++;
        if (insect->flag == 2) {
            insect->tools_actor.actor_class.mv_proc = aIBT_actor_move;
        }
        aIBT_actor_move(actor, game);
    }
}
