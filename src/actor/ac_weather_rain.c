#include "ac_weather_rain.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "m_field_info.h"
#include "m_malloc.h"
#include "m_player_lib.h"
#include "sys_matrix.h"

extern Gfx ef_ame02_setmode[];

extern Gfx ef_ame02_00_modelT[];
extern Gfx ef_ame02_01_modelT[];
extern Gfx ef_ame02_02_modelT[];
extern Gfx ef_ame02_03_modelT[];
extern Gfx ef_ame02_04_modelT[];

static Gfx* aWeather_rain_picha_disp[] = {
    ef_ame02_00_modelT,
    ef_ame02_01_modelT,
    ef_ame02_02_modelT,
    ef_ame02_03_modelT,
};

static void aWeatherRain_make(ACTOR*, GAME*);
static void aWeatherRain_ct(aWeather_Priv*, GAME*);
static void aWeatherRain_move(aWeather_Priv*, GAME*);
static void aWeatherRain_set(GAME*);
static void aWeatherRain_draw(aWeather_Priv*, GAME*);

aWeather_Profile_c iam_weather_rain = {
    aWeatherRain_make, aWeatherRain_ct, aWeatherRain_move, aWeatherRain_set, aWeatherRain_draw,
};

static int aWeatherRain_DecideMakeRainCount(ACTOR* actor) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actor;

    if (weather->current_level == mEnv_WEATHER_INTENSITY_LIGHT) {
        return 1;
    } else if (weather->current_level == mEnv_WEATHER_INTENSITY_NORMAL) {
        return 2;
    } else {
        return 3;
    }
}

static void aWeatherRain_make(ACTOR* actor, GAME* game) {
    aWeather_Priv* priv;
    xyz_t pos;
    xyz_t pos_mod;
    xyz_t speed;
    int count;
    int i;
    int priv_num;
    GAME_PLAY* play = (GAME_PLAY*)game;
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actor;

    f32 x, y, z;

    count = aWeatherRain_DecideMakeRainCount(actor);
    pos = weather->pos;

    for (i = 0; i < count; i++) {

        priv_num = Common_Get(clip.weather_clip)->get_priv_num(&weather->actor_class);
        if (priv_num != -1) {
            x = -130.0f + (RANDOM_F(260.0f));
            z = -200.0f + (RANDOM_F(360.0f));

            pos_mod = pos;
            speed = ZeroVec;

            speed.y = -9.5f + (RANDOM_F(-2.5f));
            speed.y += -2.0f;

            pos_mod.x += x;
            pos_mod.z += z;

            if (mEv_CheckTitleDemo() == mEv_TITLEDEMO_STAFFROLL) {
                PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);

                pos_mod.y = 70.0f + (120.0f + player->actor_class.world.position.y);
            } else {
                pos_mod.y = 70.0f + (120.0f + mCoBG_GetBgY_OnlyCenter_FromWpos(pos_mod, 0.0f));
            }

            priv = Common_Get(clip.weather_clip)->get_priv(1, 1000, &pos_mod, &speed, actor, priv_num);
            if (priv != NULL) {
                aWeatherRain_ct(priv, game);
                priv->work[0] = 0;
            }
        }
    }
}

static void aWeatherRain_ct(aWeather_Priv*, GAME*) {
}

static void aWeatherRain_MoveRain(aWeather_Priv* priv) {

    priv->pos.x += priv->speed.x;
    priv->pos.y += priv->speed.y;
    priv->pos.z += priv->speed.z;
}

static void aWeatherRain_MakePicha(ACTOR* actor, GAME* game, xyz_t pos) {
    int priv_num = Common_Get(clip.weather_clip)->get_priv_num(actor);
    GAME_PLAY* play = (GAME_PLAY*)game;
    aWeather_Priv* priv;
    f32 y;

    if (priv_num != -1) {
        if (mEv_CheckTitleDemo() == mEv_TITLEDEMO_STAFFROLL) {
            PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);

            y = player->actor_class.world.position.y;
            pos.y = y;
        } else {
            y = mCoBG_GetBgY_OnlyCenter_FromWpos(pos, 0.0f);
            pos.y = y;
        }
        priv = Common_Get(clip.weather_clip)->get_priv(1, 8, &pos, NULL, actor, priv_num);
        if (priv != NULL) {
            aWeatherRain_ct(priv, game);
            priv->work[0] = 1;
        }
    }
}

static void aWeatherRain_set(GAME* game) {

    _texture_z_light_fog_prim_xlu(game->graph);

    OPEN_DISP(game->graph);

    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_ame02_setmode);

    CLOSE_DISP(game->graph);
}

static void aWeatherRain_move(aWeather_Priv* priv, GAME* game) {
    WEATHER_ACTOR* weather;
    float timer = (1000.0f - priv->timer);

    if (priv->work[0] == 0) {
        aWeatherRain_MoveRain(priv);
        if ((timer >= 10) && (Common_Get(clip.weather_clip) != NULL)) {
            weather = (WEATHER_ACTOR*)Common_Get(clip.weather_clip)->actor;
            if (weather != NULL) {
                (Common_Get(clip.weather_clip)->remove_priv(&weather->actor_class, priv->id));
                aWeatherRain_MakePicha(&weather->actor_class, game, priv->pos);
            }
        }
    }
}

void aWeatherRain_draw(aWeather_Priv* priv, GAME* game) {
    static f32 rain_scale[] = {
        0.0003f,
        0.035f,
        0.01f,
    };
    static f32 picha_scale[] = {
        0.0033f,
        0.0033f,
        0.0033f,
    };

    GAME_PLAY* play = (GAME_PLAY*)game;
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)Common_Get(clip.weather_clip)->actor;

    s16 disp;
    xyz_t pos;
    s16 angle;
    GRAPH* graph;
    Mtx* work;

    angle = weather->current_yAngle;
    disp = 8 - priv->timer;
    pos = priv->pos;

    if (priv->work[0] == 1) {
        graph = play->game.graph;

        disp = disp >> 1;

        Matrix_translate(pos.x, pos.y, pos.z, MTX_LOAD);
        Matrix_mult(&play->billboard_matrix, MTX_MULT);
        Matrix_scale(picha_scale[0], picha_scale[1], picha_scale[2], MTX_MULT);

        OPEN_DISP(graph);

        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(play->game.graph),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPDisplayList(NEXT_POLY_XLU_DISP, aWeather_rain_picha_disp[(disp)]);

        CLOSE_DISP(graph);
    } else if (priv->work[0] == 0) {
        work = GRAPH_ALLOC_TYPE(game->graph, Mtx, 1);

        OPEN_DISP(play->game.graph);

        suMtxMakeSRT(work, rain_scale[0], rain_scale[1], rain_scale[2], 0, angle, 0, pos.x, pos.y, pos.z);

        gSPMatrix(NEXT_POLY_XLU_DISP, work, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_ame02_04_modelT);

        CLOSE_DISP(play->game.graph);
    }
}
