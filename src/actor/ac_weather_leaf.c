#include "ac_weather_leaf.h"

#include "main.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "m_field_info.h"
#include "m_malloc.h"
#include "m_player_lib.h"
#include "sys_matrix.h"

extern Gfx ef_otiba01_setmode[];

extern Gfx ef_otiba01_00_modelT[];
extern Gfx ef_otiba01_01_modelT[];
extern Gfx ef_otiba01_02_modelT[];

static void aWeatherLeaf_make(ACTOR*, GAME*);
static void aWeatherLeaf_ct(aWeather_Priv*, GAME*);
static void aWeatherLeaf_move(aWeather_Priv*, GAME*);
static void aWeatherLeaf_set(GAME*);
static void aWeatherLeaf_draw(aWeather_Priv*, GAME*);

Gfx* ef_otiba_model_tbl[] = {
    ef_otiba01_00_modelT,
    ef_otiba01_01_modelT,
    ef_otiba01_02_modelT,
};

aWeather_Profile_c iam_weather_leaf = {
    aWeatherLeaf_make, aWeatherLeaf_ct, aWeatherLeaf_move, aWeatherLeaf_set, aWeatherLeaf_draw,
};

static int aWeatherLeaf_DecideMakeLeafCount(ACTOR* actor, GAME* game) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actor;

    if (weather->current_level == 1) {
        return (game->frame_counter & 15) == 0;
    }
    return (game->frame_counter & 7) == 0;
}

static void aWeatherLeaf_make(ACTOR* actor, GAME* game) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;

    aWeather_Priv* priv;
    f32 x, z;
    xyz_t pos = weather->pos;
    f32 y = 230.0f + pos.y;
    int count = Common_Get(clip.weather_clip)->get_priv_num(actor);
    xyz_t base = { 0.0f, 0.0f, 0.0f };
    xyz_t mod_pos;

    if (aWeatherLeaf_DecideMakeLeafCount(actor, game) != 0) {
        base.y = -0.8f + (RANDOM_F(-0.1f));
        if (count != -1) {
            x = -100.0f + (RANDOM_F(200.0f));
            z = -200.0f + (RANDOM_F(380.0f));

            mod_pos = pos;

            mod_pos.x += x;
            mod_pos.z += z;
            mod_pos.y = y;

            priv = Common_Get(clip.weather_clip)->get_priv(4, 280, &mod_pos, &base, actor, count);
            if (priv != NULL) {
                aWeatherLeaf_ct(priv, game);
                priv->work[3] = 0;
                priv->work[4] = 156.5f + (RANDOM_F(260.5));
                priv->currentY = y;
            }
        }
    }
}

static void aWeatherLeaf_ct(aWeather_Priv* priv, GAME*) {
    priv->work[0] = RANDOM_F(3.0f);
    priv->work[1] = RANDOM_F(65535.0f);
    priv->work[2] = RANDOM_F(65535.0f);
}

static int aWeatherLeaf_CheckLeafBorder(aWeather_Priv* priv) {
    WEATHER_ACTOR* weather = (WEATHER_ACTOR*)Common_Get(clip.weather_clip)->actor;
    int ret = 0;
    f32 leafTemp;
    xyz_t pos;

    if (weather != NULL) {
        pos = weather->pos;
        leafTemp = priv->pos.x;

        if (leafTemp < (-100.0f + pos.x)) {
            ret |= 2;
        }
        if (leafTemp > (100.0f + pos.x)) {
            ret |= 8;
        }
        leafTemp = priv->pos.z;

        if (leafTemp > (180.0f + pos.z)) {
            ret |= 4;
        }
        if (leafTemp < (-200.0f + pos.z)) {
            ret |= 1;
        }
    }

    return ret;
}

static void aWeatherLeaf_CheckLeafScroll(aWeather_Priv* priv) {
    int border = aWeatherLeaf_CheckLeafBorder(priv);

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

static void aWeatherLeaf_SetWind2Leaf(aWeather_Priv* priv, GAME* game) {
    const float dt = (float)game->graph->dt_num_60fps_frames;

    priv->pos.x += 0.45f * dt;
}

static void aWeatherLeaf_move(aWeather_Priv* priv, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    const float dt = (float)game->graph->dt_num_60fps_frames;

    priv->pos.x += priv->speed.x * dt;
    priv->pos.y += priv->speed.y * dt;
    priv->pos.z += priv->speed.z * dt;

    priv->work[3] += (float)priv->work[4] * dt;
    aWeatherLeaf_SetWind2Leaf(priv, game);
    aWeatherLeaf_CheckLeafScroll(priv);
    priv->work[1] += 0x8DC * dt;
    priv->work[2] += 0x474 * dt;
}

static void aWeatherLeaf_set(GAME* game) {

    _texture_z_light_fog_prim_xlu(game->graph);

    OPEN_DISP(game->graph);

    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_otiba01_setmode);

    CLOSE_DISP(game->graph);
}

void aWeatherLeaf_draw(aWeather_Priv* priv, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

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

        suMtxMakeSRT(work, 0.005f, 0.005f, 0.005f, priv->work[2], priv->work[1],
                     priv->work[2], pos.x, pos.y, pos.z);

        gSPMatrix(NEXT_POLY_XLU_DISP, work, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_otiba_model_tbl[priv->work[0]]);

        CLOSE_DISP(game->graph);
    }
}
