#include "ac_ins_hitodama.h"

#include "m_field_info.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_player_lib.h"

enum {
    aIHD_ACTION_AVOID,
    aIHD_ACTION_LET_ESCAPE,
    aIHD_ACTION_FLY,

    aIHD_ACTION_NUM
};

#define aIHD_RANGE (8 * mFI_UNIT_BASE_SIZE_F)

#define aIHD_MAX_X(insect) ((insect)->f32_work0)
#define aIHD_MAX_Z(insect) ((insect)->f32_work1)

#define aIHD_MOVE_ANGL_ADD(insect) ((insect)->s32_work1)
#define aIHD_MOVE_TIM(insect) ((insect)->s32_work2)
#define aIHD_ANGLE(insect) ((insect)->s32_work3)

#define aIHD_RANDOM_ANGLE() (RANDOM_F(65536))
#define aIHD_ANGLE_F(insect) (sin_s((s16)aIHD_ANGLE(insect)))

static int aIHD_set_move_info(aINS_INSECT_ACTOR* insect, GAME* game);
static void aIHD_unregist_set_block_table(ACTOR* actorx);
static void aIHD_setupAction(aINS_INSECT_ACTOR* insect, int act, GAME* game);
static void aIHD_actor_move(ACTOR* actorx, GAME* game);

extern void aIHD_actor_init(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int act;

    insect->bg_type = 2;
    insect->bg_range = 20.0f;
    actorx->mv_proc = &aIHD_actor_move;
    insect->item = ITM_SPIRIT0;

    if (actorx->actor_specific != 0) {
        act = aIHD_ACTION_AVOID;
    } else {
        u32 attr = mCoBG_Wpos2BgAttribute_Original(actorx->world.position);

        if (mCoBG_CheckWaterAttribute(attr)) {
            actorx->world.position.y =
                mFI_UNIT_BASE_SIZE_F + mCoBG_GetWaterHeight_File(actorx->world.position, __FILE__, 158);
        } else {
            actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos(actorx->world.position, -mFI_UNIT_BASE_SIZE_F);
        }

        actorx->home.position.y = actorx->world.position.y;
        actorx->world.angle.y = aIHD_RANDOM_ANGLE();
        aIHD_MOVE_TIM(insect) = aIHD_set_move_info(insect, game);
        aIHD_ANGLE(insect) = aIHD_RANDOM_ANGLE();
        insect->continue_timer = RANDOM(5);
        mFI_BkNum2WposXZ(&aIHD_MAX_X(insect), &aIHD_MAX_Z(insect), actorx->block_x, actorx->block_z);
        aIHD_MAX_X(insect) += aIHD_RANGE;
        aIHD_MAX_Z(insect) += aIHD_RANGE;
        aIHD_unregist_set_block_table(actorx);
        act = aIHD_ACTION_FLY;
    }

    aIHD_setupAction(insect, act, game);
}

static void aIHD_anime_proc(aINS_INSECT_ACTOR* insect) {
    insect->_1E0 += 0.5f;
    if (insect->_1E0 >= 2.0f) {
        insect->_1E0 -= 2.0f;
    }
}

static void aIHD_unregist_set_block_table(ACTOR* actorx) {
    mEv_gst_common_c* gst_cmn = (mEv_gst_common_c*)mEv_get_common_area(mEv_EVENT_GHOST, 55);

    if (gst_cmn != NULL) {
        u8 bx = actorx->block_x;
        u8 bz = actorx->block_z;
        int i;

        for (i = 0; i < mEv_GHOST_HITODAMA_NUM; i++) {

            if (bx == gst_cmn->hitodama_block_data.block_x[i] && gst_cmn->hitodama_block_data.block_z[i] == bz) {
                gst_cmn->hitodama_block_data.block_x[i] = 0xFF;
                gst_cmn->hitodama_block_data.block_z[i] = 0xFF;
                break;
            }
        }
    }
}

static void aIHD_fuwafuwa(aINS_INSECT_ACTOR* insect, int avoid_flag) {
    f32 last_angle;
    f32 grav;
    int dir;
    f32 now_grav;

    if (avoid_flag == FALSE) {
        dir = 0x100 + RANDOM(0x300);
        grav = 10.0f;
    } else {
        dir = 0x400;
        grav = 13.0f;
    }

    last_angle = aIHD_ANGLE_F(insect) * 10.0f;
    aIHD_ANGLE(insect) += dir;
    now_grav = grav * aIHD_ANGLE_F(insect);
    insect->tools_actor.actor_class.position_speed.y =
        insect->tools_actor.actor_class.gravity + (now_grav - last_angle);
}

static int aIHD_set_move_info(aINS_INSECT_ACTOR* insect, GAME* game) {
    static int angl_add[] = { 40, 56, 80, 104 };
    static int move_tim[] = { 240, 360, 480, 600 };

    int frame = game->frame_counter;
    int angl = angl_add[frame & 3];

    if (aIHD_MOVE_ANGL_ADD(insect) > 0) {
        angl *= -1;
    }

    aIHD_MOVE_ANGL_ADD(insect) = angl;
    return move_tim[(frame >> 2) & 3];
}

static void aIHD_calc_move_drt(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;
    xyz_t target;
    f32 dist_xz;
    s16 angleY;
    int absY;
    int angle2;

    target.x = aIHD_MAX_X(insect);
    target.z = aIHD_MAX_Z(insect);
    dist_xz = search_position_distanceXZ(&actorx->world.position, &target);

    if (dist_xz > (aIHD_RANGE / 2)) {
        angleY = actorx->world.angle.y - search_position_angleY(&target, &actorx->world.position);
        absY = ABS(angleY);

        if (absY < DEG2SHORT_ANGLE2(22.5f)) {
            aIHD_MOVE_TIM(insect) = aIHD_set_move_info(insect, game);
        }
    } else {
        int time = aIHD_MOVE_TIM(insect) - 1;

        if (time < 0) {
            time = aIHD_set_move_info(insect, game);
        }

        aIHD_MOVE_TIM(insect) = time;
    }

    angle2 = actorx->world.angle.y;
    angle2 += (int)aIHD_MOVE_ANGL_ADD(insect);
    actorx->world.angle.y = angle2;
}

static void aIHD_light_proc(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (insect->tools_actor.init_matrix == TRUE || insect->insect_flags.bit_1 == TRUE) {
        if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_PUTAWAY_NET) {
            if ((play->game_frame & 1) == 0 && ((int)insect->_1E0) > 0) {
                insect->_1E0--;
            }
        } else {
            insect->light_step = 0;
        }

        switch (insect->light_flag) {
            case 0: {
                s16 power = 15.0f * fabsf(sin_s(insect->light_counter)) + 25.0f;
                s16 x = actorx->world.position.x;
                s16 y = actorx->world.position.y - 35.0f;
                s16 z = actorx->world.position.z;

                Light_point_ct(&insect->point_light, x, y, z, 120, 255, 180, power);
                insect->light_list = Global_light_list_new(game, &play->global_light, &insect->point_light);
                insect->light_flag++;
                break;
            }
            case 1: {
                insect->timer = 0;
                insect->continue_timer = 0;
                insect->light_flag++;
                break;
            }
            case 2: {
                s16 power = 15.0f * fabsf(sin_s(insect->light_counter)) + 25.0f;
                s16 x = actorx->world.position.x;
                s16 y = actorx->world.position.y - 35.0f;
                s16 z = actorx->world.position.z;

                Light_point_ct(&insect->point_light, x, y, z, 120, 255, 180, power);
                break;
            }
        }

        add_calc_short_angle2(&insect->light_counter, (insect->_1E0 * 0x1555), 1.0f - sqrtf(0.7f), 2500, 0);
    }
}

static void aIHD_avoid(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    aIHD_fuwafuwa(insect, TRUE);
    actorx->gravity += 0.1f;
}

static void aIHD_fly(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    actorx->scale.x = actorx->scale.y = actorx->scale.z = 0.01f;
    insect->target_speed = 0.3f;
    insect->speed_step = 0.1f;
    aIHD_fuwafuwa(insect, FALSE);
    aIHD_calc_move_drt(insect, game);
}

static void aIHD_avoid_init_sub(aINS_INSECT_ACTOR* insect, GAME_PLAY* play) {
    insect->life_time = 0;
    insect->alpha_time = 80;
    insect->tools_actor.actor_class.shape_info.rotation.x = 0;
    insect->tools_actor.actor_class.speed = 1.5f;

    if (insect->insect_flags.bit_1 == FALSE) {
        PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);

        if (player != NULL) {
            insect->tools_actor.actor_class.world.angle.y = player->actor_class.shape_info.rotation.y;
            insect->tools_actor.actor_class.world.angle.y +=
                (s16)(DEG2SHORT_ANGLE2(60.0f) - RANDOM((DEG2SHORT_ANGLE2(120.0f) - 1)));
            insect->tools_actor.actor_class.home.position.y = insect->tools_actor.actor_class.world.position.y;
        }
    }

    insect->insect_flags.bit_1 = TRUE;
    aIHD_ANGLE(insect) = 0;
    insect->tools_actor.actor_class.shape_info.draw_shadow = TRUE;
}

static void aIHD_avoid_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    aIHD_avoid_init_sub(insect, play);
    insect->_1E0 = 0;
    insect->_1E4 = insect->_1E0;
    insect->alpha0 = 255;
}

static void aIHD_let_escape_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    aIHD_avoid_init_sub(insect, play);
    insect->insect_flags.bit_2 = TRUE;
}

static void aIHD_fly_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->flag = FALSE;
    insect->tools_actor.actor_class.world.angle.x = 0;
}

typedef void (*aIHD_INIT_PROC)(aINS_INSECT_ACTOR*, GAME*);

static void aIHD_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game) {
    static aIHD_INIT_PROC init_proc[] = {
        &aIHD_avoid_init,
        &aIHD_let_escape_init,
        &aIHD_fly_init,
    };

    static aINS_ACTION_PROC act_proc[] = {
        &aIHD_avoid,
        &aIHD_avoid,
        &aIHD_fly,
    };

    insect->action = action;
    insect->action_proc = act_proc[action];
    (*init_proc[action])(insect, game);
}

static void aIHD_actor_move(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    u32 label;

    aIHD_light_proc(actorx, game);
    if (mPlib_get_player_actor_main_index(game) != mPlayer_INDEX_PUTAWAY_NET) {
        aIHD_anime_proc(insect);
    }

    label = mPlib_Get_item_net_catch_label();
    if (label == (uintptr_t)actorx) {
        aIHD_setupAction(insect, aIHD_ACTION_LET_ESCAPE, game);
    } else {
        if (mEv_check_status(mEv_EVENT_GHOST, mEv_STATUS_RUN) == FALSE) {
            insect->insect_flags.bit_3 = TRUE;
        }

        if (insect->insect_flags.bit_3 == TRUE && insect->insect_flags.bit_2 == FALSE) {
            aIHD_setupAction(insect, aIHD_ACTION_LET_ESCAPE, game);
        } else {
            (*insect->action_proc)(actorx, game);
        }
    }
}
