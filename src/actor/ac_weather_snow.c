#include "ac_weather_snow.h"

#include "main.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "m_field_info.h"
#include "m_malloc.h"
#include "m_player_lib.h"
#include "sys_matrix.h"

extern Gfx ef_yuki01_setmode[];

extern Gfx ef_yuki01_00_model[];

static void aWeatherSnow_make(ACTOR*, GAME*);
static void aWeatherSnow_ct(aWeather_Priv*, GAME*);
static void aWeatherSnow_move(aWeather_Priv*, GAME*);
static void aWeatherSnow_set(GAME*);
static void aWeatherSnow_draw(aWeather_Priv*, GAME*);

aWeather_Profile_c iam_weather_snow = {
    aWeatherSnow_make, aWeatherSnow_ct, aWeatherSnow_move, aWeatherSnow_set, aWeatherSnow_draw,
};

static int aWeatherSnow_DecideMakeSnowCount(ACTOR* actor, GAME* game) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actor;

    if (weather->current_level == mEnv_WEATHER_INTENSITY_LIGHT) {
        return (game->frame_counter & 7) == 0;
    } else if (weather->current_level == mEnv_WEATHER_INTENSITY_NORMAL) {
        return (game->frame_counter & 3) == 0;
    }
    return (game->frame_counter & 1); // HEAVY
}

static void aWeatherSnow_make(ACTOR* actor, GAME* game) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;

    aWeather_Priv* priv;
    f32 x, z;
    xyz_t pos = weather->pos;
    f32 y = 230.0f + pos.y;
    int count = Common_Get(clip.weather_clip)->get_priv_num(actor);
    xyz_t base = { 0.0f, 0.0f, 0.0f };
    xyz_t mod_pos;

    if (aWeatherSnow_DecideMakeSnowCount(actor, game) != 0) {
        base.y = -0.5f + (RANDOM_F(-2.0f));
        if (count != -1) {
            x = -100.0f + (RANDOM_F(200.0f));
            z = -200.0f + (RANDOM_F(380.0f));

            mod_pos = pos;

            mod_pos.x += x;
            mod_pos.z += z;
            mod_pos.y = y;

            priv = Common_Get(clip.weather_clip)->get_priv(2, 280, &mod_pos, &base, actor, count);
            if (priv != NULL) {
                aWeatherSnow_ct(priv, game);
                priv->work[0] = 0;
                priv->work[1] = 156.5f + (RANDOM_F(260.5));
                priv->currentY = y;
            }
        }
    }
}

static void aWeatherSnow_ct(aWeather_Priv*, GAME*) {
}

static int aWeatherSnow_CheckSnowBorder(aWeather_Priv* priv, GAME_PLAY* play) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)Common_Get(clip.weather_clip)->actor;
    int ret = 0;
    f32 wtemp, ptemp;
    if (weather != NULL) {
        wtemp = weather->pos.x;
        ptemp = priv->pos.x;

        if (ptemp < (-100.0f + wtemp)) {
            ret |= 2;
        }
        if (ptemp > (100.0f + wtemp)) {
            ret |= 8;
        }
        wtemp = weather->pos.z;
        ptemp = priv->pos.z;

        if (ptemp > (180.0f + wtemp)) {
            ret |= 4;
        }
        if (ptemp < (-200.0f + wtemp)) {
            ret |= 1;
        }
    }

    return ret;
}

static void aWeatherSnow_CheckSnowScroll(aWeather_Priv* priv, GAME_PLAY* play) {
    int border = aWeatherSnow_CheckSnowBorder(priv, play);
    PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);

    if (border != 0) {
        if ((border >> 1) & 1) {
            priv->pos.x += 200.0f;
        }
        if ((border >> 3) & 1) {
            priv->pos.x -= 200.0f;
        }
        if ((border >> 2) & 1) {
            priv->pos.z -= 380.0f;
        }
        if (border & 1) {
            priv->pos.z += 380.0f;
        }
    }

    if (Common_Get(clip.weather_clip) != NULL) {
        f32 y;
        WEATHER_ACTOR* weather = (WEATHER_ACTOR*)Common_Get(clip.weather_clip)->actor;

        if (weather != NULL) {
            y = 230.0f + weather->pos.y;
            if (priv->pos.y < (40.0f + player->actor_class.world.position.y)) {
                priv->pos.y = (y + (priv->pos.y - priv->currentY));
                priv->currentY = y;
            }
        }
    }
}

static void aWeatherSnow_SetWind2Snow(aWeather_Priv* priv, GAME* game) {
    if (Common_Get(clip.weather_clip) != NULL) {
        WEATHER_ACTOR* weather = (WEATHER_ACTOR*)Common_Get(clip.weather_clip)->actor;
        if (weather != NULL) {
            const float dt = (float)game->graph->dt_num_60fps_frames;

            priv->pos.x += weather->wind_info.x * dt;
            priv->pos.y += weather->wind_info.y * dt;
            priv->pos.z += weather->wind_info.z * dt;
        }
    }
}

static void aWeatherSnow_move(aWeather_Priv* priv, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    xyz_t_add(&priv->pos, &priv->speed, &priv->pos);
    priv->work[0] += (float)priv->work[1] * game->graph->dt_num_60fps_frames;
    aWeatherSnow_SetWind2Snow(priv, game);
    aWeatherSnow_CheckSnowScroll(priv, play);
}

static void aWeatherSnow_set(GAME* game) {

    _texture_z_light_fog_prim_xlu(game->graph);

    OPEN_DISP(game->graph);

    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_yuki01_setmode);

    CLOSE_DISP(game->graph);
}

void aWeatherSnow_draw(aWeather_Priv* priv, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);

    xyz_t pos;
    xyz_t screen_pos;
    Mtx* work;
    f32 scale;
    f32 min;

    pos.x = priv->pos.x + (6.0f * sin_s(priv->work[0]));
    pos.y = priv->pos.y;
    pos.z = priv->pos.z + (6.0f * cos_s(priv->work[0]));

    Game_play_Projection_Trans(play, &pos, &screen_pos);

    if ((0.0f <= screen_pos.x) && (screen_pos.x < SCREEN_WIDTH_F) && (0.0f <= screen_pos.y) &&
        (screen_pos.y < SCREEN_HEIGHT_F)) {

        work = GRAPH_ALLOC_TYPE(game->graph, Mtx, 1);

        min = pos.y - (40.0f + player->actor_class.world.position.y);

        if (min < 0.0f) {
            min = 0.0f;
        }

        scale = min / 20.0f;

        if (scale > 1.0f) {
            scale = 1.0f;
        }

        OPEN_DISP(game->graph);

        suMtxMakeTS(work, 0.00196f * scale, 0.00196f * scale, 0.00196f * scale, pos.x, pos.y,
                    pos.z);

        gSPMatrix(NEXT_POLY_XLU_DISP, work, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPMatrix(NEXT_POLY_XLU_DISP, play->billboard_mtx_p, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);

        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_yuki01_00_model);

        CLOSE_DISP(game->graph);
    }
}
