#include "ac_ant.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_rcp.h"
#include "sys_matrix.h"

enum {
    aANT_ACT_WAIT,
    aANT_ACT_CAUGHT,
    aANT_ACT_DISAPPEAR,

    aANT_ACT_NUM
};

static void aANT_actor_ct(ACTOR* actorx, GAME* game);
static void aANT_actor_move(ACTOR* actorx, GAME* game);
static void aANT_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Ant_Profile = {
    mAc_PROFILE_ANT,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_ANT,
    sizeof(ANT_ACTOR),
    &aANT_actor_ct,
    mActor_NONE_PROC1,
    &aANT_actor_move,
    &aANT_actor_draw,
    NULL,
};
// clang-format on

static void aANT_setupAction(ANT_ACTOR* ant, int action);

static void aANT_actor_ct(ACTOR* actorx, GAME* game) {
    ANT_ACTOR* ant = (ANT_ACTOR*)actorx;

    ant->below_fg_p = mFI_GetUnitFG(actorx->world.position);
    actorx->home.position.y = actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos(actorx->world.position, -10.0f);
    actorx->shape_info.rotation.x = DEG2SHORT_ANGLE2(45.0f);
    ant->alpha = 255;
    actorx->mv_proc = &aANT_actor_move;
    aANT_setupAction(ant, aANT_ACT_WAIT);
}

static void aANT_calc_scale(ANT_ACTOR* ant, f32 step, f32 target_scale) {
    f32 scale = ant->actor_class.scale.x;

    chase_f(&scale, target_scale, step * 0.5f);
    ant->actor_class.scale.x = scale;
    ant->actor_class.scale.y = scale;
    ant->actor_class.scale.z = scale;
}

static void aANT_wait(ANT_ACTOR* ant, GAME* game) {
    if (ant->below_fg_p == NULL || (*ant->below_fg_p != ITM_FOOD_CANDY && *ant->below_fg_p != ITM_KABU_SPOILED)) {
        aANT_setupAction(ant, aANT_ACT_DISAPPEAR);
    } else {
        uintptr_t catch_label = mPlib_Get_item_net_catch_label();

        if ((uintptr_t)ant == catch_label) {
            aANT_setupAction(ant, aANT_ACT_CAUGHT);
        } else {
            f32 catch_swing_timer = GET_PLAYER_ACTOR_NOW()->Get_Item_net_catch_swing_timer_proc(GET_PLAYER_ACTOR_NOW_ACTOR(), gamePT);
            xyz_t stop_net_pos;

            if ((catch_swing_timer > 0.0f || mPlib_Check_StopNet(&stop_net_pos)) && ant->actor_class.player_distance_xz < mFI_UNIT_BASE_SIZE_F) {
                GET_PLAYER_ACTOR_NOW()->Set_Item_net_catch_request_force_proc(GET_PLAYER_ACTOR_NOW_ACTOR(), gamePT, (uintptr_t)ant, mPlayer_NET_CATCH_TYPE_ANT);
            } else {
                GET_PLAYER_ACTOR_NOW()->Set_Item_net_catch_request_table_proc(GET_PLAYER_ACTOR_NOW_ACTOR(), gamePT, (uintptr_t)ant, mPlayer_NET_CATCH_TYPE_ANT, &ant->actor_class.world.position, 24.0f);
            }
        }
    }
}

static void aANT_caught(ANT_ACTOR* ant, GAME* game) {
    aINS_Init_c insect_init;

    insect_init.insect_type = aINS_INSECT_TYPE_ANT;
    xyz_t_move(&insect_init.position, &ant->actor_class.world.position);
    insect_init.extra_data = 0;
    insect_init.game = game;

    ant->insect_actor = CLIP(insect_clip)->make_insect_proc(&insect_init, aINS_MAKE_EXIST);
    if (ant->insect_actor != NULL) {
        if (mPlib_Change_item_net_catch_label((uintptr_t)ant->insect_actor, mPlayer_NET_CATCH_TYPE_INSECT)) {
            aANT_setupAction(ant, aANT_ACT_DISAPPEAR);
        }
    } else {
        ant->disappear_counter++;
        if (ant->disappear_counter > 1) {
            aANT_setupAction(ant, aANT_ACT_DISAPPEAR);
        }
    }
}

static void aANT_disappear(ANT_ACTOR* ant, GAME* game) {
    ant->alpha -= 15;
    if (ant->alpha < 0) {
        ant->alpha = 0;
        Actor_delete((ACTOR*)ant);
    } else {
        aANT_calc_scale(ant, 0.1f, 0.01f);
    }
}

static void aANT_caught_init(ANT_ACTOR* ant) {
    ant->disappear_counter = 0;
}

static void aANT_disappear_init(ANT_ACTOR* ant) {
    ant->actor_class.shape_info.rotation.x = 0;
    ant->actor_class.shape_info.rotation.z = 0;
}

typedef void (*aANT_INIT_PROC)(ANT_ACTOR* ant);

static void aANT_setupAction(ANT_ACTOR* ant, int action) {
    static aANT_INIT_PROC init_proc[] = {
        (aANT_INIT_PROC)&none_proc1,
        &aANT_caught_init,
        &aANT_disappear_init,
    };

    static aANT_ACT_PROC act_proc[] = {
        &aANT_wait,
        &aANT_caught,
        &aANT_disappear,
    };

    ant->action = action;
    ant->act_proc = act_proc[action];
    (*init_proc[action])(ant);
}

static void aANT_actor_move(ACTOR* actorx, GAME* game) {
    ANT_ACTOR* ant = (ANT_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if ((actorx->state_bitfield & ACTOR_STATE_NO_CULL) == 0 &&
        (actorx->block_x != play->block_table.block_x || actorx->block_z != play->block_table.block_z)) {
        Actor_delete(actorx);
    } else {
        if (actorx->world.position.x < 0.0f && actorx->world.position.z < 0.0f) {
            return;
        }

        (*ant->act_proc)(ant, game);
        Actor_world_to_eye(actorx, 0.0f);
    }
}

extern EVW_ANIME_DATA act_ant_evw_anime;
extern Gfx act_antT_model[];

static void aANT_actor_draw(ACTOR* actorx, GAME* game) {
    ANT_ACTOR* ant = (ANT_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    GRAPH* graph = game->graph;

    if (actorx->world.position.x < 0.0f || actorx->world.position.z < 0.0f) {
        return;
    }

    _texture_z_light_fog_prim_xlu(graph);
    Setpos_HiliteReflect_xlu_init(&actorx->world.position, play);
    Evw_Anime_Set(play, &act_ant_evw_anime);

    OPEN_POLY_XLU_DISP(graph);

    gSPMatrix(POLY_XLU_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_LOAD | G_MTX_NOPUSH);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 255, 0, 0, 0, ant->alpha);
    gSPDisplayList(POLY_XLU_DISP++, act_antT_model);

    CLOSE_POLY_XLU_DISP(graph);
}
