
#include "ac_weather_sakura.h"

#include "main.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "m_field_info.h"
#include "m_malloc.h"
#include "m_player_lib.h"
#include "sys_matrix.h"

extern Gfx ef_hanabira01_00_setmode[];

extern Gfx ef_hanabira01_00_modelT[];

static void aWeatherSakura_make(ACTOR*, GAME*);
static void aWeatherSakura_ct(aWeather_Priv*, GAME*);
static void aWeatherSakura_move(aWeather_Priv*, GAME*);
static void aWeatherSakura_set(GAME*);
static void aWeatherSakura_draw(aWeather_Priv*, GAME*);

aWeather_Profile_c iam_weather_sakura = {
    aWeatherSakura_make, aWeatherSakura_ct, aWeatherSakura_move, aWeatherSakura_set, aWeatherSakura_draw,
};

static int aWeatherSakura_DecideMakeSakuraCount(ACTOR* actor, GAME* game) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actor;

    if (weather->current_level == 1) {
        return (game->frame_counter & 7) == 0;
    }
    return (game->frame_counter & 3) == 0;
}

static void aWeatherSakura_make(ACTOR* actor, GAME* game) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;

    aWeather_Priv* priv;
    f32 x, z;
    xyz_t pos = weather->pos;
    f32 y = 230.0f + pos.y;
    int count = Common_Get(clip.weather_clip)->get_priv_num(actor);
    xyz_t base = { 0.0f, 0.0f, 0.0f };
    xyz_t mod_pos;

    if (aWeatherSakura_DecideMakeSakuraCount(actor, game) != 0) {
        base.y = -0.8f + (RANDOM_F(-0.1f));
        if (count != -1) {
            x = -100.0f + (RANDOM_F(200.0f));
            z = -200.0f + (RANDOM_F(380.0f));

            mod_pos = pos;

            mod_pos.x += x;
            mod_pos.z += z;
            mod_pos.y = y;

            priv = Common_Get(clip.weather_clip)->get_priv(3, 280, &mod_pos, &base, actor, count);
            if (priv != NULL) {
                aWeatherSakura_ct(priv, game);
                priv->work[3] = 0;
                priv->work[4] = 156.5f + (RANDOM_F(260.5));
                priv->currentY = y;
            }
        }
    }
}

static void aWeatherSakura_ct(aWeather_Priv* priv, GAME*) {
    priv->work[0] = RANDOM_F(65535.0f);
    priv->work[1] = RANDOM_F(65535.0f);
    priv->work[2] = RANDOM_F(65535.0f);
}

static int aWeatherSakura_CheckSakuraBorder(aWeather_Priv* priv) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)Common_Get(clip.weather_clip)->actor;
    int ret = 0;
    f32 sakuraTemp;
    xyz_t pos;

    if (weather != NULL) {
        pos = weather->pos;
        sakuraTemp = priv->pos.x;

        if (sakuraTemp < (-100.0f + pos.x)) {
            ret |= 2;
        }
        if (sakuraTemp > (100.0f + pos.x)) {
            ret |= 8;
        }
        sakuraTemp = priv->pos.z;

        if (sakuraTemp > (180.0f + pos.z)) {
            ret |= 4;
        }
        if (sakuraTemp < (-200.0f + pos.z)) {
            ret |= 1;
        }
    }

    return ret;
}

static void aWeatherSakura_CheckSakuraScroll(aWeather_Priv* priv) {
    int border = aWeatherSakura_CheckSakuraBorder(priv);

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
            if (priv->pos.y < +weather->pos.y) {
                priv->pos.y = (y + (priv->pos.y - priv->currentY));
                priv->currentY = y;
            }
        }
    }
}

static void aWeatherSakura_SetWind2Sakura(aWeather_Priv* priv, GAME* game) {
    const float dt = (float)game->graph->dt_num_60fps_frames;

    priv->pos.x += 0.45f * dt;
}

static void aWeatherSakura_move(aWeather_Priv* priv, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    const float dt = (float)game->graph->dt_num_60fps_frames;

    priv->pos.x += priv->speed.x * dt;
    priv->pos.y += priv->speed.y * dt;
    priv->pos.z += priv->speed.z * dt;

    priv->work[3] += (float)priv->work[4] * dt;
    aWeatherSakura_SetWind2Sakura(priv, game);
    aWeatherSakura_CheckSakuraScroll(priv);
    priv->work[0] += 0x200 * dt;
    priv->work[1] += 0x8DC * dt;
    priv->work[2] += 0x474 * dt;
}

static void aWeatherSakura_set(GAME* game) {

    _texture_z_light_fog_prim_xlu(game->graph);

    OPEN_DISP(game->graph);

    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_hanabira01_00_setmode);

    CLOSE_DISP(game->graph);
}

void aWeatherSakura_draw(aWeather_Priv* priv, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    xyz_t base = { 0.05f, 0.05f, 0.05f };

    Mtx* work;
    f32 scale;
    f32 min;
    xyz_t pos;
    xyz_t screen_pos;

    pos.x = priv->pos.x + (6.0f * sin_s(priv->work[3]));

    pos.z = priv->pos.z + (6.0f * cos_s(priv->work[3]));
    pos.y = priv->pos.y;
    Game_play_Projection_Trans(play, &pos, &screen_pos);

    if ((screen_pos.x >= 0.0f) && (screen_pos.x < SCREEN_WIDTH_F) && (screen_pos.y >= 0.0f) &&
        (screen_pos.y < SCREEN_HEIGHT_F)) {

        work = GRAPH_ALLOC_TYPE(game->graph, Mtx, 1);

        OPEN_DISP(game->graph);

        suMtxMakeSRT(work, base.x, base.y, base.z, priv->work[2], priv->work[1], priv->work[2], pos.x, pos.y, pos.z);

        gSPMatrix(NEXT_POLY_XLU_DISP, work, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_hanabira01_00_modelT);

        CLOSE_DISP(game->graph);
    }
}
