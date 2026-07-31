#include "ac_lighthouse_switch.h"

#include "m_common_data.h"
#include "m_soncho.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "m_debug.h"
#include "m_player_lib.h"

static void Lighthouse_Switch_Actor_ct(ACTOR* actorx, GAME* game);
static void Lighthouse_Switch_Actor_dt(ACTOR* actorx, GAME* game);
static void Lighthouse_Switch_Actor_move(ACTOR* actorx, GAME* game);
static void Lighthouse_Switch_Actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Lighthouse_Switch_Profile = {
    mAc_PROFILE_LIGHTHOUSE_SWITCH,
    ACTOR_PART_BG,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(LIGHTHOUSE_SWITCH_ACTOR),
    Lighthouse_Switch_Actor_ct,
    Lighthouse_Switch_Actor_dt,
    Lighthouse_Switch_Actor_move,
    Lighthouse_Switch_Actor_draw,
    NULL,
};
// clang-format on

static int aLS_CheckLightHousePeriod(void) {
    switch (mSC_LightHouse_get_period(Common_GetPointer(time.rtc_time))) {
        case mSC_LIGHTHOUSE_PERIOD_1:
            return TRUE;
        default:
            return FALSE;
    }
}

static int aLS_NiceSwitchOnTime(void) {
    lbRTC_hour_t hour = Common_Get(time.rtc_time.hour);

    if (hour >= 18 || hour < 5) {
        return TRUE;
    }

    return FALSE;
}

static int aLS_GetNiceStatus(void) {
    if (aLS_NiceSwitchOnTime()) {
        if (aLS_CheckLightHousePeriod() == FALSE) {
            return aLS_NICE_STATUS_SWITCH_ON;
        } else {
            return aLS_NICE_STATUS_LIGHTHOUSE_PERIOD;
        }
    } else {
        return aLS_NICE_STATUS_OFF;
    }
}

static void aLS_RequestPoleToStop(ACTOR* actorx, GAME* game) {
    LIGHTHOUSE_SWITCH_ACTOR* actor = (LIGHTHOUSE_SWITCH_ACTOR*)actorx;

    actor->ls_pole.state = 0;
    actor->ls_pole.keyframe_state = 0;
    mEnv_RequestChangeLightOFF((GAME_PLAY*)game, mEnv_LIGHT_TYPE_TENT, 0.002f);
    sAdo_SysLevStop(0xC9);
    sAdo_SysTrgStart(SE_ECHO(0x79));
}

static void aLS_RequestPoleToMove(ACTOR* actorx, GAME* game) {
    LIGHTHOUSE_SWITCH_ACTOR* actor = (LIGHTHOUSE_SWITCH_ACTOR*)actorx;
    aLS_pole_c* pole = &actor->ls_pole;
    cKF_SkeletonInfo_R_c* kf_p = &pole->keyframe;

    pole->timer = 0.0f;
    pole->state = 1;
    pole->speed = 0.0f;
    sAdo_SysLevStart(0xC9);
    kf_p->frame_control.start_frame = 1.0f;
    kf_p->frame_control.end_frame = 100.0f;
}

extern cKF_Skeleton_R_c cKF_bs_r_obj_toudai_switch;
extern cKF_Animation_R_c cKF_ba_r_obj_toudai_switch;
extern cKF_Animation_R_c cKF_ba_r_obj_toudai_switch_off;

static void aLS_RequestSwitchON(ACTOR* actorx, GAME* game) {
    LIGHTHOUSE_SWITCH_ACTOR* actor = (LIGHTHOUSE_SWITCH_ACTOR*)actorx;
    aLS_switch_c* sw = &actor->ls_switch;
    cKF_SkeletonInfo_R_c* kf_p = &sw->keyframe;

    sw->state = 1;
    cKF_SkeletonInfo_R_init_standard_stop(kf_p, &cKF_ba_r_obj_toudai_switch, NULL);
    kf_p->frame_control.speed = 0.5f;
    cKF_SkeletonInfo_R_play(kf_p);
}

static void aLS_RequestSwitchOFF(ACTOR* actorx, GAME* game) {
    LIGHTHOUSE_SWITCH_ACTOR* actor = (LIGHTHOUSE_SWITCH_ACTOR*)actorx;
    aLS_switch_c* sw = &actor->ls_switch;
    cKF_SkeletonInfo_R_c* kf_p = &sw->keyframe;

    sw->state = 0;
    cKF_SkeletonInfo_R_init_standard_stop(kf_p, &cKF_ba_r_obj_toudai_switch_off, NULL);
    kf_p->frame_control.speed = 0.5f;
    cKF_SkeletonInfo_R_play(kf_p);
}

extern cKF_Skeleton_R_c cKF_bs_r_obj_toudai_pole;
extern cKF_Animation_R_c cKF_ba_r_obj_toudai_pole;

static void aLS_PoleCt(aLS_pole_c* pole, GAME* game, int on) {
    static xyz_t pos = { 0.0f, 0.0f, 0.0f };
    cKF_SkeletonInfo_R_c* kf_p = &pole->keyframe;

    pole->timer = 0.0f;
    pole->pos = pos;
    pole->state = 0;
    pole->speed = 0.0f;
    pole->keyframe_state = 2;
    cKF_SkeletonInfo_R_ct(kf_p, &cKF_bs_r_obj_toudai_pole, &cKF_ba_r_obj_toudai_pole, pole->work, pole->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(kf_p, &cKF_ba_r_obj_toudai_pole, NULL);

    if (on == TRUE) {
        pole->state = 1;
        pole->speed = 0.5f;
        pole->timer = 48.0f;
        sAdo_SysLevStart(0xC9);
    }

    kf_p->frame_control.speed = pole->speed;
    cKF_SkeletonInfo_R_play(kf_p);
}

static void aLS_SwitchCt(aLS_switch_c* sw, GAME* game, int on) {
    static xyz_t pos = { 0.0f, 0.0f, 0.0f };
    cKF_SkeletonInfo_R_c* kf_p = &sw->keyframe;

    sw->pos = pos;
    cKF_SkeletonInfo_R_ct(kf_p, &cKF_bs_r_obj_toudai_switch, &cKF_ba_r_obj_toudai_switch, sw->work, sw->morph);
    if (on == TRUE) {
        sw->state = 1;
        cKF_SkeletonInfo_R_init_standard_stop(kf_p, &cKF_ba_r_obj_toudai_switch_off, NULL);
    } else {
        sw->state = 0;
        cKF_SkeletonInfo_R_init_standard_stop(kf_p, &cKF_ba_r_obj_toudai_switch, NULL);
    }

    kf_p->frame_control.speed = 0.0f;
    cKF_SkeletonInfo_R_play(kf_p);
}

static void Lighthouse_Switch_Actor_ct(ACTOR* actorx, GAME* game) {
    LIGHTHOUSE_SWITCH_ACTOR* actor = (LIGHTHOUSE_SWITCH_ACTOR*)actorx;
    aLS_pole_c* pole = &actor->ls_pole;
    aLS_switch_c* sw = &actor->ls_switch;
    int nice_status = aLS_GetNiceStatus();

    if (nice_status == aLS_NICE_STATUS_SWITCH_ON) {
        aLS_PoleCt(pole, game, TRUE);
        aLS_SwitchCt(sw, game, TRUE);
        mRmTp_IndexLightSwitchON(mRmTp_LIGHT_SWITCH_LIGHTHOUSE);
    } else if (nice_status == aLS_NICE_STATUS_OFF) {
        aLS_PoleCt(pole, game, FALSE);
        aLS_SwitchCt(sw, game, FALSE);
        mRmTp_IndexLightSwitchOFF(mRmTp_LIGHT_SWITCH_LIGHTHOUSE);
    } else if (mRmTp_Index2LightSwitchStatus(mRmTp_LIGHT_SWITCH_LIGHTHOUSE)) {
        aLS_PoleCt(pole, game, TRUE);
        aLS_SwitchCt(sw, game, TRUE);
    } else {
        aLS_PoleCt(pole, game, FALSE);
        aLS_SwitchCt(sw, game, FALSE);
    }
}

static void Lighthouse_Switch_Actor_dt(ACTOR* actorx, GAME* game) {
    LIGHTHOUSE_SWITCH_ACTOR* actor = (LIGHTHOUSE_SWITCH_ACTOR*)actorx;

    if (actor->ls_pole.state == 1) {
        sAdo_SysLevStop(0xC9);
    }
}

static int aLS_PoleDrawBefore(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                              u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    if (joint_idx == 13) {
        *joint_shape = NULL;
    }
    return TRUE;
}

extern Gfx obj_toudai_pole_kage_model[];

static int aLS_PoleDrawAfter(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                              u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    if (joint_idx == 13) {
        OPEN_DISP(game->graph);

        gSPMatrix(NEXT_SHADOW_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_SHADOW_DISP, obj_toudai_pole_kage_model);

        CLOSE_DISP(game->graph);
    }
    return TRUE;
}

static Gfx* aLS_MakePrimcolorDisplayList(u8 r, u8 g, u8 b, u8 a, u8 l, GAME* game) {
    Gfx* gfx = GRAPH_ALLOC_TYPE(game->graph, Gfx, 2);
    Gfx* ret = NULL;

    if (gfx != NULL) {
        ret = gfx;
        gDPSetPrimColor(gfx++, 0, l, r, g, b, a);
        gSPEndDisplayList(gfx++);
    }

    return ret;
}

static Gfx* aLS_MakeRoomPrimcolorDisplayList(GAME* game) {
    u8 r;
    u8 g;
    u8 b;

    mEnv_GetRoomPrimColor(&r, &g, &b, (GAME_PLAY*)game);
    return aLS_MakePrimcolorDisplayList(r, g, b, 255, 128, game);
}

static void aLS_PoleDraw(aLS_pole_c* pole, GAME* game) {
    Gfx* primcolor_gfx = aLS_MakeRoomPrimcolorDisplayList(game);

    if (primcolor_gfx != NULL) {
        N64Mtx* m = pole->mtx[game->frame_counter & 1];

        _texture_z_light_fog_prim(game->graph);
        _texture_z_light_fog_prim_shadow(game->graph);

        OPEN_DISP(game->graph);

        Matrix_translate(pole->pos.x, pole->pos.y, pole->pos.z, MTX_LOAD);
        Matrix_RotateY(0, MTX_MULT);
        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(NEXT_POLY_OPA_DISP, ANIME_1_TXT_SEG, primcolor_gfx);

        CLOSE_DISP(game->graph);

        Setpos_HiliteReflect_init(&pole->pos, (GAME_PLAY*)game);
        cKF_Si3_draw_R_SV(game, &pole->keyframe, m, aLS_PoleDrawBefore, aLS_PoleDrawAfter, pole);
    }
}

static void aLS_SwitchDraw(aLS_switch_c* sw, GAME* game) {
    Gfx* primcolor_gfx = aLS_MakeRoomPrimcolorDisplayList(game);

    if (primcolor_gfx != NULL) {
        N64Mtx* m = sw->mtx[game->frame_counter & 1];

        _texture_z_light_fog_prim(game->graph);

        OPEN_DISP(game->graph);

        Matrix_translate(sw->pos.x, sw->pos.y, sw->pos.z, MTX_LOAD);
        Matrix_RotateY(0, MTX_MULT);
        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(NEXT_POLY_OPA_DISP, ANIME_1_TXT_SEG, primcolor_gfx);

        CLOSE_DISP(game->graph);

        cKF_Si3_draw_R_SV(game, &sw->keyframe, m, NULL, NULL, sw);
    }
}

static void Lighthouse_Switch_Actor_draw(ACTOR* actorx, GAME* game) {
    LIGHTHOUSE_SWITCH_ACTOR* actor = (LIGHTHOUSE_SWITCH_ACTOR*)actorx;

    aLS_PoleDraw(&actor->ls_pole, game);
    aLS_SwitchDraw(&actor->ls_switch, game);
}

static void aLS_GetNowPoleAnimeSpeed(aLS_pole_c* pole, GAME* game, ACTOR* actorx) {
    LIGHTHOUSE_SWITCH_ACTOR* actor = (LIGHTHOUSE_SWITCH_ACTOR*)actorx;
    f32 dt = (f32)game->graph->dt_num_60fps_frames;

    if (pole->state == 0) {
        switch (pole->keyframe_state) {
            case 0:
                pole->speed -= 0.001f * dt;
                if (pole->speed < GETREG(CRV, 83) * 0.01f + 0.1f) {
                    pole->keyframe_state = 1;
                }
                break;
            case 1:
                add_calc(&pole->speed, (GETREG(CRV, 83) * 0.01f + 0.1f) + 0.07f + (GETREG(CRV, 84) * 0.01f), 0.4f, 1.0f, 0.001f);
                if (ABS(pole->speed - ((GETREG(CRV, 83) * 0.01f + 0.1f) + 0.07f + (GETREG(CRV, 84) * 0.01f))) < 0.001f) {
                    pole->keyframe_state = 2;
                    pole->keyframe.frame_control.start_frame = 100.0f;
                    pole->keyframe.frame_control.end_frame = 1.0f;
                    pole->speed = (GETREG(CRV, 83) * 0.01f + 0.1f) * 1.7f;
                    pole->off_timer = 49.0f;
                }
                break;
            default:
                add_calc(&pole->speed, 0.0f, 0.4f, 1.0f, 0.001f);
                if (pole->off_timer > 0.0f) {
                    pole->off_timer -= dt;
                    if (pole->off_timer <= 0.0f) {
                        aLS_RequestSwitchOFF(actorx, game);
                        pole->off_timer = 0.0f;
                    }
                }
                break;
        }
    } else {
        if (pole->timer < 48.0f) {
            f32 prev_timer = pole->timer;
            f32 next_timer = prev_timer + dt;
            int start_frame = prev_timer <= 0.0f;
            int second_kick_frame = prev_timer < 30.0f && next_timer >= 30.0f;

            if (start_frame || second_kick_frame) {
                if (start_frame) {
                    pole->speed = (GETREG(CRV, 80) * 0.01f + 1.0f) * 0.065f;
                } else {
                    pole->speed = (GETREG(CRV, 82) *  0.01f + 0.85f) * 0.065f;
                }
            } else {
                add_calc(&pole->speed, 0.0f, (GETREG(CRV, 81) * 0.001f) + 0.09f, ((GETREG(CRV, 81) * 0.001f) + 0.09f) * 0.065f, 0.00001f);
            }

            pole->timer = MIN(next_timer, 48.0f);
        } else {
            pole->speed += 0.0035f * dt;
        }
    }

    if (pole->speed < 0.0f) {
        pole->speed = 0.0f;
    } else if (pole->speed > 0.5f) {
        pole->speed = 0.5f;
    }
}

static void aLS_PolePlayKeyAnime(aLS_pole_c* pole, GAME* game) {
    cKF_SkeletonInfo_R_c* kf_p = &pole->keyframe;

    kf_p->frame_control.speed = pole->speed;
    if (!F32_IS_ZERO(pole->speed)) {
        cKF_SkeletonInfo_R_play(kf_p);
    }
}

static void aLS_PoleMove(aLS_pole_c* pole, GAME* game, ACTOR* actorx) {
    aLS_GetNowPoleAnimeSpeed(pole, game, actorx);
    aLS_PolePlayKeyAnime(pole, game);
}

static void aLS_SwitchMove(aLS_switch_c* sw, GAME* game, ACTOR* actorx) {
    LIGHTHOUSE_SWITCH_ACTOR* actor = (LIGHTHOUSE_SWITCH_ACTOR*)actorx;
    cKF_SkeletonInfo_R_c* kf_p = &sw->keyframe;

    if (kf_p->frame_control.speed != 0.0f) {
        if (sw->state == 1) {
            int play_se;

            if ((kf_p->frame_control.current_frame - 20.0f) * ((kf_p->frame_control.current_frame - kf_p->frame_control.speed) - 20.0f) <= 0.0f) {
                play_se = TRUE;
            } else {
                play_se = FALSE;
            }

            if (play_se) {
                sAdo_OngenTrgStart(SE_ECHO(NA_SE_78), &sw->pos);
            }
        }

        if (cKF_SkeletonInfo_R_play(kf_p) == cKF_STATE_STOPPED) {
            kf_p->frame_control.speed = 0.0f;
            if (sw->state == 1) {
                aLS_RequestPoleToMove(actorx, game);
                mEnv_RequestChangeLightON((GAME_PLAY*)game, mEnv_LIGHT_TYPE_LIGHTHOUSE, TRUE);
            }
        }
    }
}

static int aLS_CheckPlayerSwitchPositionAngle(xyz_t* position, s16 angle) {
    f32 x = position->x - 180.0f;
    f32 z = position->z - 100.0f;
    u16 uangle = angle;

    if (SQ(x) + SQ(z) < SQ(GETREG(CRV, 86) + 33.5684)) { // @BUG - missing float specifier
        s16 max_angle = DEG2SHORT_ANGLE2(GETREG(CRV, 85) + 45.0f);

        if (uangle > DIFF_USHORT_ANGLE(DEG2SHORT_ANGLE2(135.0f), max_angle) && uangle < DIFF_USHORT_ANGLE(max_angle, DEG2SHORT_ANGLE2(-135.0f))) {
            return TRUE;
        }
    }

    return FALSE;
}

static void aLS_CheckPlayerAction(ACTOR* actorx, GAME* game) {
    static xyz_t nice_pos = { 167.27208f, 40.0f, 112.72792f };
    LIGHTHOUSE_SWITCH_ACTOR* actor = (LIGHTHOUSE_SWITCH_ACTOR*)actorx;
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);

    if (mPlib_check_player_actor_start_switch_on_lighthouse(game) && actor->turning_on == TRUE) {
        actor->turning_on = FALSE;
        if (actor->ls_switch.state == 0) {
            aLS_RequestSwitchON(actorx, game);
            mSC_LightHouse_Switch_On();
        } else {
            aLS_RequestPoleToStop(actorx, game);
        }
    } else if (chkTrigger(BUTTON_A) && aLS_GetNiceStatus() == aLS_NICE_STATUS_LIGHTHOUSE_PERIOD && actor->ls_switch.state == 0 && aLS_CheckPlayerSwitchPositionAngle(&playerx->world.position, playerx->shape_info.rotation.y)) {
        mPlib_request_main_switch_on_lighthouse_type1(game, &nice_pos, DEG2SHORT_ANGLE2(135.0f));
        actor->turning_on = TRUE;
    }
}

static void aLS_AutoSwitch(ACTOR* actorx, GAME* game) {
    LIGHTHOUSE_SWITCH_ACTOR* actor = (LIGHTHOUSE_SWITCH_ACTOR*)actorx;

    switch (aLS_GetNiceStatus()) {
        case aLS_NICE_STATUS_OFF:
            if (actor->ls_switch.state == 1) {
                aLS_RequestPoleToStop(actorx, game);
            }
            break;
        case aLS_NICE_STATUS_SWITCH_ON:
            if (actor->ls_switch.state == 0) {
                aLS_RequestSwitchON(actorx, game);
            }
            break;
    }
}

static void Lighthouse_Switch_Actor_move(ACTOR* actorx, GAME* game) {
    LIGHTHOUSE_SWITCH_ACTOR* actor = (LIGHTHOUSE_SWITCH_ACTOR*)actorx;

    aLS_CheckPlayerAction(actorx, game);
    aLS_AutoSwitch(actorx, game);
    aLS_PoleMove(&actor->ls_pole, game, actorx);
    aLS_SwitchMove(&actor->ls_switch, game, actorx);
}
