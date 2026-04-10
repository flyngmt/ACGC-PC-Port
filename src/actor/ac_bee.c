#include "ac_bee.h"

#include "m_name_table.h"
#include "libultra/libultra.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "m_player_lib.h"
#include "m_common_data.h"
#include "ac_set_ovl_insect.h"

enum {
    aBEE_ACT_APPEAR,
    aBEE_ACT_FLY,
    aBEE_ACT_CAUGHT,
    aBEE_ACT_ATTACK_WAIT,
    aBEE_ACT_ATTACK,
    aBEE_ACT_DISAPPEAR,

    aBEE_ACT_NUM
};

static void aBEE_actor_ct(ACTOR* actorx, GAME* game);
static void aBEE_actor_move(ACTOR* actorx, GAME* game);
static void aBEE_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Bee_Profile = {
    mAc_PROFILE_BEE,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_BEE,
    sizeof(BEE_ACTOR),
    &aBEE_actor_ct,
    mActor_NONE_PROC1,
    &aBEE_actor_move,
    &aBEE_actor_draw,
    NULL,
};
// clang-format on

static void aBEE_setupAction(BEE_ACTOR* bee, int action, GAME* game);

extern cKF_Skeleton_R_c cKF_bs_r_act_bee;
extern cKF_Animation_R_c cKF_ba_r_act_bee;

static void aBEE_actor_ct(ACTOR* actorx, GAME* game) {
    BEE_ACTOR* bee = (BEE_ACTOR*)actorx;
    cKF_SkeletonInfo_R_c* kf_p = &bee->keyframe;

    cKF_SkeletonInfo_R_ct(kf_p, &cKF_bs_r_act_bee, &cKF_ba_r_act_bee, bee->work, bee->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(kf_p, &cKF_ba_r_act_bee, NULL);
    kf_p->frame_control.current_frame = 90.0f;
    cKF_SkeletonInfo_R_play(kf_p);
    kf_p->frame_control.speed = 0.0f;
    bee->fly_angle[1] = DEG2SHORT_ANGLE2(180.0f);
    bee->start_frame = 90.0f;
    bzero(&actorx->scale, sizeof(actorx->scale));
    actorx->mv_proc = &aBEE_actor_move; // @cleanup - this is unnecessary
    aBEE_setupAction(bee, aBEE_ACT_APPEAR, game);
}

static f32 aBEE_calc_scale_sub(f32* scale_p, f32 target, f32 frac, f32 max_step) {
    return add_calc(scale_p, target, CALC_EASE(frac), max_step * 0.5f, 0.0f);
}

static void aBEE_calc_scale(BEE_ACTOR* bee, f32 frac, f32 max_step) {
    aBEE_calc_scale_sub(&bee->actor_class.scale.x, bee->size.x, frac, max_step);
    aBEE_calc_scale_sub(&bee->actor_class.scale.y, bee->size.y, frac, max_step);
    aBEE_calc_scale_sub(&bee->actor_class.scale.z, bee->size.z, frac, max_step);
}

static void aBEE_anime_proc(BEE_ACTOR* bee) {
    cKF_SkeletonInfo_R_c* kf_p = &bee->keyframe;

    kf_p->frame_control.current_frame = bee->start_frame;
    cKF_SkeletonInfo_R_play(kf_p);
    kf_p->frame_control.speed = 0.0f;
    bee->fly_angle[0] += 500;
    bee->fly_angle[1] -= 500;
}

static void aBEE_fly_move_common(BEE_ACTOR* bee, GAME* game) {
    ACTOR* player = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    f32 speed;
    f32 angle = fabsf(90.0f - bee->start_frame) * 7.5f;
    int speed_angle;
    s16 d_angle;
    s16 abs_speed_angle;
    f32 target_frame;
    f32 diff;

    switch (bee->action) {
        case aBEE_ACT_FLY:
        case aBEE_ACT_CAUGHT:
            bee->base_angle = 1600;
            break;
        default:
            bee->base_angle = 5000;
            break;
    }

    d_angle = bee->base_angle - (s16)angle;
    add_calc_short_angle2(&bee->add_angle, d_angle, CALC_EASE(0.4f), 250, 0);
    add_calc_short_angle2(&bee->actor_class.world.angle.y, bee->actor_class.player_angle_y, CALC_EASE(0.4f), bee->add_angle >> 1, 0);
    bee->actor_class.shape_info.rotation.y = bee->actor_class.world.angle.y;
    speed_angle = (int)(bee->actor_class.world.angle.y - bee->actor_class.player_angle_y);
    abs_speed_angle = ABS((s16)speed_angle);
    if (abs_speed_angle > DEG2SHORT_ANGLE2(-180.0f)) {
        abs_speed_angle = 0;
    }

    bee->speed = 2.9f;
    bee->speed += fabsf((f32)((DEG2SHORT_ANGLE2(180.0f) - abs_speed_angle) / DEG2SHORT_ANGLE2(30.0f)));
    add_calc(&bee->actor_class.speed, bee->speed, CALC_EASE(0.3f), 0.15f, 0.0f);

    bee->bobbing_counter += 0x900;
    if (player != NULL) {
        bee->pos_y = player->world.position.y + 50.0f;
    }
    bee->pos_y += 5.0f * sin_s(bee->bobbing_counter);

    target_frame = 90.0f + (f32)(bee->actor_class.player_angle_y - bee->actor_class.world.angle.y) / 30.0f;
    if (target_frame < 0.0f) {
        target_frame = 0.0f;
    } else if (target_frame > 180.0f) {
        target_frame = 180.0f;
    }
    add_calc(&bee->start_frame, target_frame, CALC_EASE(0.5f), 5.0f, 0.0f);

    diff = fabsf(90.0f - bee->start_frame);
    bee->size.x = (0.75f + diff / 360.0f) * 0.01f;
    bee->size.y = (0.75f + diff / 360.0f) * 0.01f;
    bee->size.z = (1.5f - diff / 180.0f) * 0.01f;
    aBEE_calc_scale(bee, 0.2f, 0.01f);
}

static void aBEE_calc_fly_angle(ACTOR* actorx) {
    add_calc_short_angle2(&actorx->shape_info.rotation.z, 0, CALC_EASE(0.3f), 1000, 0);
    add_calc_short_angle2(&actorx->shape_info.rotation.x, 0, CALC_EASE(0.3f), 1000, 0);
}

static void aBEE_appear(ACTOR* actorx, GAME* game) {
    BEE_ACTOR* bee = (BEE_ACTOR*)actorx;
    ACTOR* player = GET_PLAYER_ACTOR_GAME_ACTOR(game);

    if (player != NULL) {
        bee->pos_y = player->world.position.y + 50.0f;
    }

    actorx->shape_info.rotation.x = DEG2SHORT_ANGLE2(180.0f) - 1;
    actorx->shape_info.rotation.z += DEG2SHORT_ANGLE2(22.5f);
    
    bee->alpha += 3;
    if (bee->alpha >= 255) {
        bee->alpha = 255;
        aBEE_setupAction(bee, aBEE_ACT_FLY, game);
    } else {
        aBEE_calc_scale(bee, 0.1f, 0.005f);
    }
}

static void aBEE_fly(ACTOR* actorx, GAME* game) {
    BEE_ACTOR* bee = (BEE_ACTOR*)actorx;
    xyz_t pos;

    aBEE_calc_fly_angle(actorx);
    if ((uintptr_t)bee == mPlib_Get_item_net_catch_label()) {
        aBEE_setupAction(bee, aBEE_ACT_CAUGHT, game);
    } else if (actorx->shape_info.rotation.x <= DEG2SHORT_ANGLE2(22.5f)) {
        if (mPlib_check_player_actor_main_index_Pitfall(game)) {
            aBEE_setupAction(bee, aBEE_ACT_ATTACK_WAIT, game);
        } else {
            switch (mPlib_Get_status_for_bee()) {
                case mPlayer_STATUS_FOR_BEE_ENTER_BUILDING:
                    aBEE_setupAction(bee, aBEE_ACT_DISAPPEAR, game);
                    return;
                case mPlayer_STATUS_FOR_BEE_ATTACK:
                    if (actorx->player_distance_xz < 30.0f) {
                        mPlib_request_main_stung_bee_type1(game);
                        aBEE_setupAction(bee, aBEE_ACT_ATTACK, game);
                        return;
                    }
                    break;
                default:
                    if (actorx->player_distance_xz < 30.0f) {
                        aBEE_setupAction(bee, aBEE_ACT_ATTACK_WAIT, game);
                        return;
                    }
                    break;
            }

            if (bee->catch_delay_frames > 0) {
                bee->catch_delay_frames--;
            } else {
                f32 swing_timer;

                swing_timer = GET_PLAYER_ACTOR_NOW()->Get_Item_net_catch_swing_timer_proc(GET_PLAYER_ACTOR_NOW_ACTOR(), gamePT);
                if ((swing_timer > 0.0f || mPlib_Check_StopNet(&pos)) && actorx->player_distance_xz < 40.0f) {
                    GET_PLAYER_ACTOR_NOW()->Set_Item_net_catch_request_force_proc(GET_PLAYER_ACTOR_NOW_ACTOR(), gamePT, (uintptr_t)actorx, TRUE);
                } else {
                    GET_PLAYER_ACTOR_NOW()->Set_Item_net_catch_request_table_proc(GET_PLAYER_ACTOR_NOW_ACTOR(), gamePT, (uintptr_t)actorx, TRUE, &actorx->world.position, 24.0f);
                }
            }

            aBEE_fly_move_common(bee, game);
        }
    }
}

static void aBEE_caught(ACTOR* actorx, GAME* game) {
    BEE_ACTOR* bee = (BEE_ACTOR*)actorx;

    if (bee->insect_actor == NULL) {
        aINS_Init_c insect_data;

        insect_data.insect_type = aINS_INSECT_TYPE_BEE;
        xyz_t_move(&insect_data.position, &bee->actor_class.world.position);
        insect_data.extra_data = 0;
        insect_data.game = game;

        bee->insect_actor = CLIP(insect_clip)->make_insect_proc(&insect_data, aINS_MAKE_EXIST);
    }

    if (bee->insect_actor != NULL) {
        if (mPlib_Change_item_net_catch_label((uintptr_t)bee->insect_actor, 0)) {
            aBEE_setupAction(bee, aBEE_ACT_DISAPPEAR, game);
            return;
        }
    } else {
        bee->disappear_timer++;
        if (bee->disappear_timer > 1) {
            aBEE_setupAction(bee, aBEE_ACT_DISAPPEAR, game);
            return;
        }
    }

    aBEE_fly_move_common(bee, game);
}

static void aBEE_attack_wait(ACTOR* actorx, GAME* game) {
    // TODO: this function is suspicious, only matches when accessing actorx.
    // It might be that these all are (BEE_ACTOR*, GAME*) funcs.
    BEE_ACTOR* bee = (BEE_ACTOR*)actorx;

    aBEE_calc_fly_angle(actorx);
    if (actorx->shape_info.rotation.x <= DEG2SHORT_ANGLE2(22.5f)) {
        switch (mPlib_Get_status_for_bee()) {
            case mPlayer_STATUS_FOR_BEE_ENTER_BUILDING:
                aBEE_setupAction((BEE_ACTOR*)actorx, aBEE_ACT_DISAPPEAR, game);
                return;
            case mPlayer_STATUS_FOR_BEE_ATTACK:
                if (actorx->player_distance_xz < 30.0f) {
                    mPlib_request_main_stung_bee_type1(game);
                    aBEE_setupAction((BEE_ACTOR*)actorx, aBEE_ACT_ATTACK, game);
                }
                break;
        }

        aBEE_fly_move_common((BEE_ACTOR*)actorx, game);
    }
}

static void aBEE_attack(ACTOR* actorx, GAME* game) {
    // TODO: this function is suspicious, only matches when accessing actorx.
    // It might be that these all are (BEE_ACTOR*, GAME*) funcs.
    BEE_ACTOR* bee = (BEE_ACTOR*)actorx;

    aBEE_calc_fly_angle(actorx);
    if (actorx->shape_info.rotation.x <= DEG2SHORT_ANGLE2(22.5f)) {
        if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_STUNG_BEE) {
            if (mPlib_Check_end_stung_bee()) {
                aBEE_setupAction((BEE_ACTOR*)actorx, aBEE_ACT_DISAPPEAR, game);
                return;
            }
        } else {
            mPlib_request_main_stung_bee_type1(game);
        }

        aBEE_fly_move_common((BEE_ACTOR*)actorx, game);
    }
}

static void aBEE_disappear(ACTOR* actorx, GAME* game) {
    BEE_ACTOR* bee = (BEE_ACTOR*)actorx;

    bee->size.x = 0.03f;
    bee->size.y = bee->size.z = bee->size.x;
    bee->alpha -= 15;

    if (bee->alpha < 0) {
        bee->alpha = 0;
        Actor_delete(actorx);
    } else {
        aBEE_calc_scale(bee, 0.1f, 0.01f);
    }
}

static void aBEE_appear_init(BEE_ACTOR* bee, GAME* game) {
    static xyz_t Size_data = { 0.01f, 0.01f, 0.01f };

    xyz_t_move(&bee->size, &Size_data);
    Common_Set(player_bee_chase_flag, TRUE);
}

static void aBEE_fly_init(BEE_ACTOR* bee, GAME* game) {
    bee->catch_delay_frames = 60;
}

static void aBEE_caught_init(BEE_ACTOR* bee, GAME* game) {
    bee->disappear_timer = 0;
}

static void aBEE_disappear_init(BEE_ACTOR* bee, GAME* game) {
    bee->actor_class.speed = 9.7f;
    bee->actor_class.shape_info.rotation.x = 0;
    bee->actor_class.shape_info.rotation.z = 0;
}

typedef void (*aBEE_INIT_PROC)(BEE_ACTOR*, GAME*);

static void aBEE_setupAction(BEE_ACTOR* bee, int action, GAME* game) {
    static aBEE_INIT_PROC init_proc[] = {
        &aBEE_appear_init,
        &aBEE_fly_init,
        &aBEE_caught_init,
        (aBEE_INIT_PROC)&none_proc1,
        (aBEE_INIT_PROC)&none_proc1,
        &aBEE_disappear_init,
    };

    static mActor_proc act_proc[] = {
        &aBEE_appear,
        &aBEE_fly,
        &aBEE_caught,
        &aBEE_attack_wait,
        &aBEE_attack,
        &aBEE_disappear,
    };

    bee->action = action;
    bee->action_proc = act_proc[action];
    (*init_proc[action])(bee, game);
}

static void aBEE_actor_move(ACTOR* actorx, GAME* game) {
    BEE_ACTOR* bee = (BEE_ACTOR*)actorx;
    
    sAdo_OngenPos((uintptr_t)actorx, NA_SE_B0, &actorx->world.position);
    if ((actorx->world.position.x < 0.0f && actorx->world.position.z < 0.0f)) {
        // empty block, maybe for debug?
    } else {
        if (bee->action == aBEE_ACT_ATTACK || mFI_GetPlayerWade() == mFI_WADE_NONE) {
            Actor_position_moveF(actorx);
        }

        (*bee->action_proc)(actorx, game);
        aBEE_anime_proc(bee);
        add_calc(&actorx->world.position.y, bee->pos_y, CALC_EASE(0.3f), 1.5f, 0.0f);
    }
}

static void aBEE_actor_draw(ACTOR* actorx, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    GRAPH* graph;
    BEE_ACTOR* bee = (BEE_ACTOR*)actorx;
    int idx;
    Mtx* mtx;
    Gfx* gfx;

    if (actorx->world.position.x < 0.0f || actorx->world.position.z < 0.0f) {
        return;
    }

    graph = game->graph;
    gfx = two_tex_scroll_dolphin(graph, 0, 180.0f * sin_s(bee->fly_angle[0]), 180.0f * cos_s(bee->fly_angle[0]), 32, 32, 1, 180.0f * cos_s(bee->fly_angle[1]), 180.0f * sin_s(bee->fly_angle[1]), 32, 32);
    if (gfx != NULL) {
        idx = game->frame_counter & 1;
        mtx = bee->mtx[idx];

        Matrix_push();
        _texture_z_light_fog_prim_xlu(graph);
        Setpos_HiliteReflect_xlu_init(&actorx->world.position, play);

        OPEN_POLY_XLU_DISP(graph);

        gDPSetPrimColor(POLY_XLU_DISP++, 0, 255, 0, 0, 0, bee->alpha);
        gSPSegment(POLY_XLU_DISP++, ANIME_1_TXT_SEG, gfx);

        CLOSE_POLY_XLU_DISP(graph);

        cKF_Si3_draw_R_SV(game, &bee->keyframe, mtx, NULL, NULL, bee);
        Matrix_pull();
    }
}
