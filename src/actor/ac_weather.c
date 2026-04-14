#include "ac_weather.h"

#include "ac_weather_fine.h"
#include "ac_weather_rain.h"
#include "ac_weather_snow.h"
#include "ac_weather_sakura.h"
#include "ac_weather_leaf.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "m_field_info.h"
#include "m_malloc.h"
#include "m_player_lib.h"
#include "m_event.h"
#include "libultra/libultra.h"

static void Weather_Actor_ct(ACTOR* actor, GAME* game);
static void Weather_Actor_dt(ACTOR* actor, GAME* game);
static void Weather_Actor_move(ACTOR* actor, GAME* game);
static void Weather_Actor_draw(ACTOR* actor, GAME* game);

static void aWeather_SetNowProfile(ACTOR* actorx, s16 id);
static int aWeather_CountWeatherPrivate(ACTOR* actorx);

static aWeather_Profile_c* profile_tbl[] = {
    &iam_weather_fine, &iam_weather_rain, &iam_weather_snow, &iam_weather_sakura, &iam_weather_leaf,
};

ACTOR_PROFILE Weather_Profile = {
    mAc_PROFILE_WEATHER,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(WEATHER_ACTOR),
    Weather_Actor_ct,
    Weather_Actor_dt,
    Weather_Actor_move,
    Weather_Actor_draw,
    NULL,
};

static void aWeather_SysLevCall_MoveEnd(WEATHER_ACTOR* weather) {

    if (weather->basement_event == 1) {
        weather->stop_sound_effect = 0;
        weather->start_sound_effect = 0;
    } else {
        if (weather->stop_sound_effect != 0) {
            sAdo_SysLevStop(weather->stop_sound_effect);
        }
        if (weather->start_sound_effect != 0) {
            sAdo_SysLevStart(weather->start_sound_effect);
        }
        weather->stop_sound_effect = 0;
        weather->start_sound_effect = 0;
    }
}

static void aWeather_SysLevStart(u8 flag) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)Common_Get(clip.weather_clip)->actor;

    weather->start_sound_effect = flag;
}

static void aWeather_SysLevStop(u8 flag) {
    int stopFlag = flag;
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)Common_Get(clip.weather_clip)->actor;

    if (weather->start_sound_effect == stopFlag) {
        weather->start_sound_effect = 0;
    } else {
        weather->stop_sound_effect = stopFlag;
    }
}

static void aWeather_weatherinfo_CommonSet(s16 type, s16 intensity) {

    if (type >= mEnv_WEATHER_LEAVES) {
        type = 0;
    }

    Common_Set(weather, type);
    Common_Set(weather_intensity, intensity);
}

static void aWeather_RequestChangeWeather(ACTOR* actor, s16 status, s16 level) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actor;
    if (mEnv_ReqeustChangeWeatherEnviroment(weather->current_status, status) != 0) {
        if (status != weather->current_status) {
            weather->next_status = status;
            weather->next_level = level;
            weather->request_change = TRUE;
            weather->current_aim_level = 0;
        } else {
            weather->current_aim_level = level;
        }
    }
}

extern void aWeather_RequestChangeWeatherToIsland() {
    aWeather_RequestChangeWeather(Common_Get(clip.weather_clip)->actor, Common_Get(island_weather),
                                  Common_Get(island_weather_intensity));
}

extern void aWeather_RequestChangeWeatherFromIsland() {
    aWeather_RequestChangeWeather(Common_Get(clip.weather_clip)->actor, mEnv_SAVE_GET_WEATHER_TYPE(Save_Get(weather)),
                                  mEnv_SAVE_GET_WEATHER_INTENSITY(Save_Get(weather)));
}

static int aWeather_GetWeatherPrvNum(ACTOR* actor) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actor;
    aWeather_Priv* priv = weather->priv;
    int i;

    for (i = 0; i < WEATHER_PRV_COUNT; i++) {
        if (priv->use == 0) {
            return i;
        }

        priv++;
    }

    return -1;
}

static void aWeather_AbolishPrivate(ACTOR* actor, int num) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actor;
    aWeather_Priv* priv = weather->priv;

    if (priv != NULL) {
        priv = &priv[num];
        if (priv->use != 0) {
            priv->use = 0;
        }
    }
}

static aWeather_Priv* aWeather_GetWeatherPrv(u8 status, s16 timer, xyz_t* pos, xyz_t* speed, ACTOR* actor, int id) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actor;
    aWeather_Priv* priv = weather->priv;

    if ((id != -1) && (id < WEATHER_PRV_COUNT)) {
        if (priv[id].use == 0) {
            priv[id].use = 1;
            priv[id].status = status;
            priv[id].timer = timer;
            priv[id].id = id;
            if (pos != NULL) {
                priv[id].pos = *pos;
            }
            if (speed != NULL) {
                priv[id].speed = *speed;
            }
            return &priv[id];
        }
        return NULL;
    }
    return NULL;
}

static int aWeather_StopSysLevSE() {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)Common_Get(clip.weather_clip)->actor;
    u8 current = weather->current_sound_effect;

    if (weather->sound_flag == 0) {
        if (((u8)(current - 7) <= 2U) || (u8)(current - 18) <= 1U || current == 20) {
            aWeather_SysLevStop(current);
        }
        weather->sound_flag = 1;
        return 1;
    } else {
        return 0;
    }
}

static int aWeather_StartSysLevSE() {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)Common_Get(clip.weather_clip)->actor;
    u8 current = weather->current_sound_effect;

    if (weather->sound_flag == 1) {
        if (mEnv_SAVE_GET_WEATHER_TYPE(Save_Get(weather)) == 1) {
            switch (mEnv_SAVE_GET_WEATHER_INTENSITY(Save_Get(weather))) {
                case 1:
                    aWeather_SysLevStart(7);
                    weather->current_sound_effect = 7;
                    break;

                case 2:
                    aWeather_SysLevStart(8);
                    weather->current_sound_effect = 8;
                    break;

                case 3:
                    aWeather_SysLevStart(9);
                    weather->current_sound_effect = 9;
                    break;
            }
        }
        weather->sound_flag = 2;
    }
    return 0;
}

static void aWeather_ChangeWeatherInstance(ACTOR* actorx, s16 status, s16 level) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actorx;

    weather->next_status = status;
    weather->next_level = level;
    weather->current_status = status;
    weather->current_level = 0;
    weather->request_change = TRUE;

    if (!aWeather_CountWeatherPrivate(actorx)) {
        weather->current_status = weather->next_status;
        aWeather_SetNowProfile(actorx, weather->current_status);
        aWeather_weatherinfo_CommonSet(weather->current_status, weather->next_level);
        weather->current_level = level;
        weather->current_aim_level = weather->next_level;
        weather->request_change = FALSE;
    }
}

static int aWeather_IsLand_Event_Check() {

    if (((mFI_CheckBeforeScenePerpetual() != 0) || (mFI_GetClimate() == 1)) &&
        (Common_Get(island_weather) != (s16)mEnv_SAVE_GET_WEATHER_TYPE(Save_Get(weather)))) {
        return 1;
    }
    return 0;
}

static int aWeather_Basement_Event_Check(ACTOR* actorx) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actorx;

    if ((weather->basement_event == 1) || (weather->basement_event == 2)) {
        return 1;
    }
    return 0;
}

static void aWeather_ChangeEnvSE(ACTOR* actorx, GAME* game, s16 status, s16 level) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actorx;
    u8 current = weather->current_sound_effect;

    if (weather->sound_flag == 1 || weather->sound_flag == 2)
        return;

    if (((u8)(current - 7) <= 2U) || (u8)(current - 18) <= 1U || current == 20) {
        aWeather_SysLevStop(current);
        weather->current_sound_effect = -1000;
    }

    if (mEv_IsNotTitleDemo()) {
        if (Save_Get(scene_no) == SCENE_START_DEMO || Save_Get(scene_no) == SCENE_START_DEMO2 ||
            Save_Get(scene_no) == SCENE_START_DEMO3) {
            return;
        }
        if ((status == 1) && (weather->current_sound_effect == -1000)) {
            switch (level) {
                case 1:
                    if (mPlib_check_player_open_umbrella(game) != 0) {
                        aWeather_SysLevStart(0x12);
                        weather->current_sound_effect = 0x12;
                        return;
                    }
                    aWeather_SysLevStart(7);
                    weather->current_sound_effect = 7;
                    break;
                case 2:
                    if (mPlib_check_player_open_umbrella(game) != 0) {
                        aWeather_SysLevStart(0x13);
                        weather->current_sound_effect = 0x13;
                        return;
                    }
                    aWeather_SysLevStart(8);
                    weather->current_sound_effect = 8;
                    break;
                case 3:
                    if (mPlib_check_player_open_umbrella(game) != 0) {
                        aWeather_SysLevStart(0x14);
                        weather->current_sound_effect = 0x14;
                        return;
                    }
                    aWeather_SysLevStart(9);
                    weather->current_sound_effect = 9;
                    break;
            }
        }
    }
}

static void aWeather_EndEnvSE(ACTOR* actor) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actor;
    u8 current = weather->current_sound_effect;

    if ((sAdo_GameframeEnd_Check() == 1) ||
        ((sAdo_GameframeEnd_Check() == 2) &&
         ((aWeather_IsLand_Event_Check() != 0) || (aWeather_Basement_Event_Check(actor) != 0)))) {
        if (((u8)(current - 7) <= 2) || ((u8)(current - 0x12) <= 1) || (u8)(current == 0x14)) {
            aWeather_SysLevStop(current);
            weather->current_sound_effect = -1000;
            Common_Set(current_sound_effect, -1000);
        }
    } else if (sAdo_GameframeEnd_Check() == 2) {
        Common_Set(current_sound_effect, weather->current_sound_effect);
    }
    aWeather_SysLevCall_MoveEnd(weather);
}

static void aWeather_SetNowProfile(ACTOR* actorx, s16 id) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actorx;

    if (!mFI_GET_TYPE(mFI_GetFieldId())) {
        weather->current_profile = profile_tbl[id];
    } else {
        weather->current_profile = NULL;
    }
}

static void aWeather_SecureWeatherPrivateWork(ACTOR* actorx) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actorx;
    int i;

    weather->priv = zelda_malloc(sizeof(aWeather_Priv) * WEATHER_PRV_COUNT);
    if (weather->priv != NULL) {
        for (i = 0; i < WEATHER_PRV_COUNT; i++) {
            bzero(&weather->priv[i], sizeof(aWeather_Priv));
        }
    }
}

static void aWeather_SetClip(ACTOR* actorx, int flag) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actorx;
    aWeather_Clip_c* clip;

    if (flag != 0) {
        Common_Set(clip.weather_clip, NULL);
    } else {
        clip = &weather->clip;

        clip->actor = actorx;
        clip->change_weather = aWeather_RequestChangeWeather;
        clip->get_priv_num = aWeather_GetWeatherPrvNum;
        clip->remove_priv = aWeather_AbolishPrivate;
        clip->get_priv = aWeather_GetWeatherPrv;
        clip->stop_sound = aWeather_StopSysLevSE;
        clip->start_sound = aWeather_StartSysLevSE;
        clip->change_weather_instance = aWeather_ChangeWeatherInstance;

        Common_Set(clip.weather_clip, clip);
    }
}

static void aWeather_RenewWindInfo(ACTOR* actorx) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actorx;
    s_xyz pos = Common_Get(wind); // multiply by 1 means inline ?
    f32 speed = Common_Get(wind_speed) * 0.01f;
    f32 factor = 1.0f;

    weather->wind_info.x = pos.x * speed * factor;
    weather->wind_info.y = pos.y * speed * factor;
    weather->wind_info.z = pos.z * speed * factor;
}

static void aWeather_SnowInAdvance(ACTOR* actorx, GAME* game, int moves) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actorx;
    int i;

    for (i = 0; i < moves; i++) {
        Weather_Actor_move(actorx, game);
    }
}

static void Weather_Actor_ct(ACTOR* actor, GAME* game) {
    static s16 DemoWeatherTbl[5][2] = {
        { mEnv_WEATHER_SAKURA, mEnv_WEATHER_INTENSITY_LIGHT },
        { mEnv_WEATHER_RAIN, mEnv_WEATHER_INTENSITY_NORMAL },
        { mEnv_WEATHER_CLEAR, mEnv_WEATHER_INTENSITY_NONE },
        { mEnv_WEATHER_CLEAR, mEnv_WEATHER_INTENSITY_NONE },
        { mEnv_WEATHER_SNOW, mEnv_WEATHER_INTENSITY_LIGHT },
    };
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;

    int cur;
    xyz_t* pos = Camera2_getCenterPos_p();

    aWeather_SetClip(actor, FALSE);

    if (mEv_IsTitleDemo()) {
        cur = mEv_CheckTitleDemo() - mEv_TITLEDEMO_START1;

        weather->current_status = DemoWeatherTbl[cur][0];
        weather->next_status = DemoWeatherTbl[cur][0];
        weather->current_level = DemoWeatherTbl[cur][1];
        weather->current_aim_level = DemoWeatherTbl[cur][1];
    } else if (mFI_GetClimate() == mFI_CLIMATE_ISLAND) {
        weather->current_status = Common_Get(island_weather);
        weather->next_status = Common_Get(island_weather);
        weather->current_level = Common_Get(island_weather_intensity);
        weather->current_aim_level = Common_Get(island_weather_intensity);
    } else {
        weather->current_status = mEnv_SAVE_GET_WEATHER_TYPE(Save_Get(weather));
        weather->next_status = weather->current_status;
        weather->current_level = mEnv_SAVE_GET_WEATHER_INTENSITY(Save_Get(weather));
// Aus version sets the aim level to the current level (from save) rather than from the
// common data struct
#if VERSION >= VER_GAFU01_00
        weather->current_aim_level = weather->current_level;
#else
        weather->current_aim_level = Common_Get(weather_intensity);
#endif
    }

    weather->ptr = NULL;
    weather->priv = NULL;
    weather->request_change = FALSE;

    weather->pos = *pos;

    weather->timer = 0;
    weather->timer2 = 0;
    weather->lightning_timer = 0;
    weather->lightning_timer2 = 30;

    weather->sound_flag = 0;
    aWeather_RenewWindInfo(actor);

    if (!mFI_GET_TYPE(mFI_GetFieldId())) {
        aWeather_SecureWeatherPrivateWork(actor);
    }

    aWeather_SetNowProfile(actor, weather->current_status);

    if ((weather->current_status == mEnv_WEATHER_SNOW) || (weather->current_status == mEnv_WEATHER_SAKURA)) {
        weather->pos.y -= 50.0f;
        aWeather_SnowInAdvance(actor, game, 40);
        weather->pos.y += 50.0f;
    }

    weather->stop_sound_effect = 0;
    weather->start_sound_effect = 0;

    if (mSc_IS_SCENE_BASEMENT(Save_Get(scene_no))) {
        weather->basement_event = 1;
    } else if (mSc_IS_SCENE_BASEMENT(Common_Get(last_scene_no)) && (play->fb_wipe_type == WIPE_TYPE_EVENT)) {
        weather->basement_event = 2;
    } else {
        weather->basement_event = 0;
    }
    if ((play->fb_wipe_type == WIPE_TYPE_EVENT) && (aWeather_IsLand_Event_Check() == 0) &&
        (aWeather_Basement_Event_Check(actor) == 0)) {
        weather->current_sound_effect = Common_Get(current_sound_effect);
    } else {
        weather->current_sound_effect = -1000;
        aWeather_ChangeEnvSE(actor, game, weather->current_status, weather->current_level);
        aWeather_SysLevCall_MoveEnd(weather);
    }
}

static void Weather_Actor_dt(ACTOR* actor, GAME* game) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actor;

    if (weather->priv != NULL) {
        zelda_free(weather->priv);
    }

    aWeather_SetClip(actor, TRUE);
}

static void aWeather_DrawWeatherPrv(ACTOR* actor, GAME* game) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actor;

    aWeather_Priv* priv = weather->priv;
    aWeather_Profile_c* profile;
    int i;

    _texture_z_light_fog_prim_xlu(game->graph);

    if ((weather->current_profile != NULL) && (priv != NULL)) {
        if (weather->current_profile->set != NULL) {
            weather->current_profile->set(game);
        }
        if (weather->current_profile->draw != NULL) {
            for (i = 0; i < WEATHER_PRV_COUNT; i++, priv++) {
                if (priv->use != 0) {
                    weather->current_profile->draw(priv, game);
                }
            }
        }
    }
}

static void Weather_Actor_draw(ACTOR* actor, GAME* game) {
    aWeather_DrawWeatherPrv(actor, game);
}

static void aWeather_MakeWeatherPrv(ACTOR* actor, GAME* game) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actor;

    if (weather->current_level != 0) {
        if (weather->current_profile != NULL) {
            if (weather->current_profile->make != NULL) {
                weather->current_profile->make(actor, game);
            }
        }
    }
}

static void aWeather_MoveWeatherPrv(ACTOR* actorx, GAME* game) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actorx;
    aWeather_Priv* priv;
    int i;

    priv = weather->priv;

    if ((weather->current_profile != NULL) && (priv != NULL) && (weather->current_profile->move != NULL)) {
        for (i = 0; i < WEATHER_PRV_COUNT; i++, priv++) {
            if (priv->use != 0) {
                weather->current_profile->move(priv, game);
                if (priv->timer != WEATHER_PRV_HOLD_TIMER) {
                    priv->timer -= game->graph->dt_num_60fps_frames;
                    if (priv->timer <= 0) {
                        aWeather_AbolishPrivate(actorx, i);
                    }
                }
            }
        }
    }
}

static int aWeather_CountWeatherPrivate(ACTOR* actorx) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actorx;
    aWeather_Priv* priv = weather->priv;
    int count;
    int i;

    count = 0;

    for (i = 0; i < WEATHER_PRV_COUNT; i++) {
        if (priv->use != 0) {
            count++;
        }

        priv++;
    }

    return count;
}

static void aWeather_ChangeWeather(ACTOR* actorx, GAME* game) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actorx;

    if ((weather->request_change == TRUE) && (weather->current_level == 0)) {
        if (mFI_GET_TYPE(mFI_GetFieldId())) {
            weather->current_status = weather->next_status;
            aWeather_weatherinfo_CommonSet(weather->current_status, weather->next_level);
            weather->current_level = 1;
            weather->current_aim_level = weather->next_level;
            aWeather_ChangeEnvSE(actorx, game, weather->current_status, weather->current_level);
            weather->request_change = FALSE;
        } else if (aWeather_CountWeatherPrivate(actorx) == 0) {
            weather->current_status = weather->next_status;
            aWeather_SetNowProfile(actorx, weather->current_status);
            aWeather_weatherinfo_CommonSet(weather->current_status, weather->next_level);
            weather->current_level = 1;
            weather->current_aim_level = weather->next_level;
            aWeather_ChangeEnvSE(actorx, game, weather->current_status, weather->current_level);
            weather->request_change = FALSE;
        }
    }
}

static void aWeather_CheckWeatherTimer(ACTOR* actorx) {
    s_xyz dir;

    mEnv_DecideWindDirect(&dir, 0x3000, 0x3000);
}

static void aWeather_RenewWeatherLevel(ACTOR* actorx, GAME* game) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actorx;
    s16 level;

    if (weather->current_level != weather->current_aim_level) {
        weather->counter += game->graph->dt_num_60fps_frames;
        if (weather->counter >= 180) {
            weather->counter = 0;
            level = weather->current_level;
            if (weather->current_aim_level < level) {
                weather->current_level--;
            } else {
                weather->current_level++;
            }

            aWeather_ChangeEnvSE(actorx, game, weather->current_status, weather->current_level);
        }
    }
}

static void aWeather_ChangeWeatherTime0(ACTOR* actorx) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actorx;
    s16 rndWeather, rndIntensity;
    s16 evWeather, evIntensity;
    s16 save_weather;

    if (mEv_IsNotTitleDemo()) {
        if ((Save_Get(scene_no) == SCENE_START_DEMO) || (Save_Get(scene_no) == SCENE_START_DEMO2) ||
            Save_Get(scene_no) == SCENE_START_DEMO3) {
            return;
        }
        if ((mFI_CheckPlayerBlockInfo() & mRF_BLOCKKIND_OFFING) == 0 && (mTM_check_renew_time(0) != 0)) {
            mEnv_RandomWeather(&rndWeather, &rndIntensity);
            mEv_GetEventWeather(&evWeather, &evIntensity);
            if (evWeather != -1) {
                rndWeather = evWeather;
                rndIntensity = evIntensity;
            }
            if ((mEv_CheckRealArbeit() == TRUE) && (rndWeather == mEnv_WEATHER_RAIN)) {
                rndWeather = mEnv_WEATHER_CLEAR;
                rndIntensity = mEnv_WEATHER_INTENSITY_NONE;
            }
            mTM_off_renew_time(0);

            save_weather = mEnv_SAVE_GET_WEATHER_TYPE(Save_Get(weather));
            if (rndWeather == mEnv_WEATHER_CLEAR || rndWeather == mEnv_WEATHER_SAKURA) {
                if (save_weather == mEnv_WEATHER_SNOW || save_weather == mEnv_WEATHER_RAIN) {
                    mEnv_PreRainNowFine_Init();
                }
            }
            Save_Set(weather, rndIntensity | (rndWeather * 16));

            if (((mEv_CheckTitleDemo() != mEv_TITLEDEMO_STAFFROLL) || (weather->sound_flag != 1)) && (mFI_CheckInIsland() == 0)) {
                aWeather_RequestChangeWeather(actorx, rndWeather, rndIntensity);
            }
            Common_Set(weather_time, Common_Get(time.rtc_time));
        }
    }
}

/** True if unwrapped time crosses a 1000-frame-unit phase threshold this update (t0 -> t0+dt). */
static int aWeather_KaminariCrossedPhase(float t0, float dt, float thresh) {
    const float period = 1000.0f;
    float next;
    float delta = t0 - thresh;

    if (delta < 0.0f) {
        next = thresh;
    } else {
        int n = (int)(delta / period) + 1;

        next = thresh + (float)n * period;
    }
    return (next <= t0 + dt);
}

static void aWeather_MakeKaminari(ACTOR* actorx, GAME* game) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actorx;
    lbRTC_time_c time = Common_Get(time.rtc_time);
    lbRTC_month_t month = time.month;
    float dt;
    float t0;

    if ((weather->basement_event != 1)) {
        if ((Save_Get(scene_no) == SCENE_START_DEMO) || (Save_Get(scene_no) == SCENE_START_DEMO2) ||
            Save_Get(scene_no) == SCENE_START_DEMO3) {
            return;
        }
        if ((month >= lbRTC_JUNE) && (month <= lbRTC_AUGUST) && (weather->current_status == mEnv_WEATHER_RAIN) &&
            (weather->current_level == mEnv_WEATHER_INTENSITY_HEAVY)) {
            dt = (float)game->graph->dt_num_60fps_frames;
            t0 = weather->lightning_timer;
            weather->lightning_timer += dt;

            if (((aWeather_KaminariCrossedPhase(t0, dt, weather->lightning_timer2) ||
                  aWeather_KaminariCrossedPhase(t0, dt, weather->lightning_timer2 + 20.0f)) &&
                 (Common_Get(clip.effect_clip) != NULL) && !mSc_IS_SCENE_BASEMENT(Save_Get(scene_no)) &&
                 Save_Get(scene_no) != SCENE_MUSEUM_ROOM_PAINTING) && Save_Get(scene_no) != SCENE_MUSEUM_ROOM_FOSSIL &&
                 Save_Get(scene_no) != SCENE_MUSEUM_ROOM_FISH) {
                rgba_t kaminari_color = { 70, 70, 160, 255 };
                Common_Get(clip.effect_clip)->regist_effect_light(kaminari_color, 2, 35, FALSE);
            }
            
            if (aWeather_KaminariCrossedPhase(t0, dt, weather->lightning_timer2 + 65.0f)) {
                sAdo_SysTrgStart(0x424);
                weather->lightning_timer2 = (100.0f + (RANDOM_F(500.0f)));
            }
        }
    }
}

static void Weather_Actor_move(ACTOR* actor, GAME* game) {
    xyz_t* pos;
    WEATHER_ACTOR* weather;
    GAME_PLAY* play;
    Camera2* camera;
    CameraLookat* lookat;
    s16 angle;
    s16 umbrella;
    mActor_name_t field_id;
    
    pos = Camera2_getCenterPos_p();
    weather = (WEATHER_ACTOR*)actor;
    play = (GAME_PLAY*)game;
    camera = &play->camera;
    lookat = &camera->lookat;
    angle = search_position_angleY(&lookat->center, &lookat->eye);

    aWeather_MakeKaminari(actor, game);
    aWeather_CheckWeatherTimer(actor);
    aWeather_MakeWeatherPrv(actor, game);
    aWeather_RenewWeatherLevel(actor, game);
    aWeather_MoveWeatherPrv(actor, game);
    aWeather_ChangeWeather(actor, game);

    weather->pos = *pos;

    aWeather_ChangeWeatherTime0(actor);

    if (Common_Get(weather) == mEnv_WEATHER_RAIN) {
        umbrella = mPlib_check_player_open_umbrella(game);
#if VERSION == VER_GAFU01_00
        field_id = mFI_GetFieldId();
        if (mFI_GET_TYPE(field_id) == mFI_FIELDTYPE2_FG && umbrella != weather->umbrella_flag) {
#else
        if (umbrella != weather->umbrella_flag) {
#endif
            aWeather_ChangeEnvSE(actor, game, weather->current_status, weather->current_level);
        }

        weather->umbrella_flag = umbrella;
        weather->current_yAngle = angle;
    }

    if (weather->sound_flag == 2) {
        weather->sound_flag = 0;
    }

    aWeather_EndEnvSE(actor);
}

extern int aWeather_ChangingWeather() {
    if (Common_Get(clip.weather_clip) != NULL) {
        if (Common_Get(clip.weather_clip->actor) != NULL) {
            WEATHER_ACTOR* weather = (WEATHER_ACTOR*)Common_Get(clip).weather_clip->actor;
            return weather->request_change == TRUE;
        }
    }

    return FALSE;
}
