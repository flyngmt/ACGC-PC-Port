#include "ac_house_goki.h"

#include "m_actor_shadow.h"
#include "m_play.h"
#include "m_player_lib.h"
#include "m_common_data.h"
#include "m_cockroach.h"
#include "sys_matrix.h"
#include "m_rcp.h"

enum {
    aHG_ACT_AWAY,
    aHG_ACT_JUMP_AWAY,
    aHG_ACT_WAIT,
    aHG_ACT_MOVE,
    aHG_ACT_DEAD,
    
    aHG_ACT_NUM
};

static void aHG_actor_ct(ACTOR* actorx, GAME* game);
static void aHG_actor_move(ACTOR* actorx, GAME* game);
static void aHG_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE House_Goki_Profile = {
    mAc_PROFILE_HOUSE_GOKI,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_HOUSE_GOKI,
    sizeof(HOUSE_GOKI_ACTOR),
    &aHG_actor_ct,
    mActor_NONE_PROC1,
    &aHG_actor_move,
    &aHG_actor_draw,
    NULL,
};
// clang-format on

static void aHG_setupAction(HOUSE_GOKI_ACTOR* goki, GAME* game, int action);

static void aHG_actor_ct(ACTOR* actorx, GAME* game) {
    HOUSE_GOKI_ACTOR* goki = (HOUSE_GOKI_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    goki->alpha = 30.0f;
    if (actorx->actor_specific <= 0) {
        actorx->actor_specific = 0;
        goki->alpha = 255.0f;
    }

    actorx->scale.x = 0.01f;
    actorx->scale.y = 0.01f;
    actorx->scale.z = 0.01f;

    Shape_Info_init(actorx, 0.0f, &mAc_ActorShadowCircle, 6.0f, 6.0f);
    xyz_t_move(&actorx->home.position, &actorx->world.position);
    actorx->gravity = -2.0f;
    actorx->shape_info.rotation.y = actorx->player_angle_y + DEG2SHORT_ANGLE2(180.0f);
    actorx->world.angle.y = actorx->shape_info.rotation.y;
    aHG_setupAction(goki, game, aHG_ACT_AWAY);
}

static void aHG_anime_proc(HOUSE_GOKI_ACTOR* goki) {
    goki->anm_no += 0.5f;
    if (goki->anm_no >= 2.0f) {
        goki->anm_no -= 2.0f;
    }
}

static void aHG_calc_timer(HOUSE_GOKI_ACTOR* goki) {
    goki->timer -= 0.5f;
    if (goki->timer < 0.0f) {
        goki->timer = 0.0f;
    }

    goki->timer2 -= 0.5f;
    if (goki->timer2 < 0.0f) {
        goki->timer2 = 0.0f;
    }
}

static s16 aHG_away_bg_hitangle_check_proc(ACTOR* actorx) {
    HOUSE_GOKI_ACTOR* goki = (HOUSE_GOKI_ACTOR*)actorx;
    s16 angle = 777; // 0x309
    s16 wall_angle[2];
    int i;

    goki->timer2 = 0.0f;
    if (actorx->player_distance_xz > 20.0f) {
        wall_angle[0] = 777;
        wall_angle[1] = 777;

        if (actorx->bg_collision_check.result.hit_wall & mCoBG_HIT_WALL_FRONT) {
            wall_angle[0] = DEG2SHORT_ANGLE2(-90.0f);
            wall_angle[1] = DEG2SHORT_ANGLE2(90.0f);
        }

        if ((actorx->bg_collision_check.result.hit_wall & mCoBG_HIT_WALL_RIGHT) || (actorx->bg_collision_check.result.hit_wall & mCoBG_HIT_WALL_LEFT)) {
            if (wall_angle[0] == 777) {
                wall_angle[0] = DEG2SHORT_ANGLE2(180.0f) - actorx->world.angle.y;
                if (wall_angle[0] > 0) {
                    wall_angle[0] = DEG2SHORT_ANGLE2(360.0f) - actorx->world.angle.y;
                }
            } else if (actorx->bg_collision_check.result.hit_wall & mCoBG_HIT_WALL_RIGHT) {
                wall_angle[0] = DEG2SHORT_ANGLE2(90.0f);
            } else {
                wall_angle[0] = DEG2SHORT_ANGLE2(-90.0f);
            }

            angle = wall_angle[0];
        } else {
            i = 0;

            if (wall_angle[0] != 777) {
                // wall_angle[0] -= actorx->player_angle_y;
                angle = ABS((s16)(wall_angle[0] - actorx->player_angle_y));
            }

            if (wall_angle[1] != 777) {
                // wall_angle[1] -= actorx->player_angle_y;


                if (angle < (s16)ABS((s16)(wall_angle[1] - actorx->player_angle_y))) {
                    i = 1;
                }
            }

            angle = wall_angle[i];
        }
    }

    return angle;
}

static void aHG_decide_next_act_idx_wait_move(HOUSE_GOKI_ACTOR* goki, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    int next_act_idx = aHG_ACT_MOVE;

    goki->timer = 5.0f + RANDOM_F(5.0f);
    if (play->game_frame % 100 > 20 || RANDOM_F(1.0f) < 0.5f) {
        next_act_idx = aHG_ACT_WAIT;
    } else if (goki->actor_class.player_distance_xz < 60.0f) {
        next_act_idx = aHG_ACT_WAIT;
    }

    aHG_setupAction(goki, game, next_act_idx);
}

static void aHG_position_move(ACTOR* actorx) {
    s16 angleY = actorx->world.angle.y;

    actorx->position_speed.x = actorx->speed * sin_s(angleY);
    actorx->position_speed.z = actorx->speed * cos_s(angleY);
    actorx->position_speed.y += actorx->gravity;
    Actor_position_move(actorx);
}

static void aHG_BGcheck(ACTOR* actorx) {
    mCoBG_WallCheckOnly(NULL, actorx, 15.0f, 0.0f, 0, 0);
    if (actorx->world.position.y < actorx->home.position.y) {
        actorx->world.position.y = actorx->home.position.y;
    }
}

static int aHG_calc_add_alpha(HOUSE_GOKI_ACTOR* goki) {
    int ret = FALSE;

    goki->alpha += 3.5f;
    if (goki->alpha > 255.0f) {
        goki->alpha = 255.0f;
        ret = TRUE;
    }

    return ret;
}

static int aHG_check_dead(ACTOR* actorx, GAME* game) {
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    int ret = FALSE;

    if (aMR_CLIP != NULL && aMR_CLIP->check_danna_kill_proc(&actorx->world.position)) {
        ret = TRUE;
    }

    if (actorx->bg_collision_check.result.unk_flag2 || actorx->bg_collision_check.result.unk_flag3) {
        ret = TRUE;
    }

    if (playerx != NULL && !F32_IS_ZERO(playerx->speed) && actorx->player_distance_xz < 9.0f && actorx->world.position.y == actorx->home.position.y) {
        ret = TRUE;
    }

    return ret;
}

static int aHG_player_check(ACTOR* actorx, GAME* game) {
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    int ret = FALSE;

    if (playerx != NULL && !F32_IS_ZERO(playerx->speed) && actorx->player_distance_xz < 60.0f) {
        ret = TRUE;
    }

    return ret;
}

static int aHG_check_threshold(ACTOR* actorx) {
    mActor_name_t* fg_p = mFI_GetUnitFG(actorx->world.position);

    if (fg_p != NULL && *fg_p == RSV_DOOR) {
        actorx->shape_info.rotation.y = DEG2SHORT_ANGLE2(180.0f);
        actorx->world.angle.y = DEG2SHORT_ANGLE2(180.0f);
    }

    return FALSE;
}

static void aHG_away(ACTOR* actorx, GAME* game) {
    HOUSE_GOKI_ACTOR* goki = (HOUSE_GOKI_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (goki->timer <= 0.0f && !goki->jump_flag && !aHG_player_check(actorx, game)) {
        goki->timer = 20.0f + RANDOM_F(20.0f);
        aHG_setupAction(goki, game, aHG_ACT_WAIT);
    } else {
        if (aHG_check_threshold(actorx) == TRUE) {
            goki->jump_flag = TRUE;
            goki->timer2 = 4.0f + RANDOM_F(4.0f);
        } else {
            goki->jump_flag = FALSE;

            if (goki->timer2 <= 0.0f) {
                if (actorx->bg_collision_check.result.hit_wall != mCoBG_DIDNT_HIT_WALL) {
                    f32 chance = 0.2f;
                    s16 angle = aHG_away_bg_hitangle_check_proc(actorx);

                    if (angle != 777) {
                        actorx->world.angle.y += angle;
                        actorx->world.angle.y &= 0xC000; // only allow movement on pure X & Z axes: 0, 90, 180, 270
                        actorx->shape_info.rotation.y = actorx->world.angle.y;
                        goki->timer2 = 5.0f + RANDOM_F(5.0f);
                    } else {
                        chance = 0.5f;
                    }

                    if (RANDOM_F(1.0f) < chance) {
                        aHG_setupAction(goki, game, aHG_ACT_JUMP_AWAY);
                    }
                } else {
                    actorx->world.angle.y = actorx->player_angle_y + DEG2SHORT_ANGLE2(180.0f);
                    actorx->shape_info.rotation.y = actorx->world.angle.y;
                }
            }
        }

        sAdo_OngenPos((uintptr_t)goki, NA_SE_GOKI_MOVE, &actorx->world.position);
    }
}

static void aHG_jump_away(ACTOR* actorx, GAME* game) {
    HOUSE_GOKI_ACTOR* goki = (HOUSE_GOKI_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (actorx->world.position.y == actorx->home.position.y) {
        aHG_setupAction(goki, game, aHG_ACT_AWAY);
    } else {
        aHG_anime_proc(goki);
        if (actorx->position_speed.y < 0.0f) {
            actorx->gravity = -7.0f;
        }
        aHG_check_threshold(actorx);
    }
}

static void aHG_wait(ACTOR* actorx, GAME* game) {
    HOUSE_GOKI_ACTOR* goki = (HOUSE_GOKI_ACTOR*)actorx;
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game); // @unused

    if (aHG_player_check(actorx, game) == TRUE) {
        aHG_setupAction(goki, game, aHG_ACT_AWAY);
    } else if (goki->timer <= 0.0f) {
        aHG_decide_next_act_idx_wait_move(goki, game);
    }
}

static void aHG_move(ACTOR* actorx, GAME* game) {
    HOUSE_GOKI_ACTOR* goki = (HOUSE_GOKI_ACTOR*)actorx;

    if (aHG_player_check(actorx, game) == TRUE) {
        aHG_setupAction(goki, game, aHG_ACT_AWAY);
    } else {
        if (mAc_CHK_HIT_WALL(actorx, mCoBG_HIT_WALL_FRONT) ||
            mAc_CHK_HIT_ATR_WALL(actorx, mCoBG_HIT_WALL_FRONT) ||
            mAc_CHK_HIT_WALL(actorx, mCoBG_HIT_WALL_RIGHT) ||
            mAc_CHK_HIT_ATR_WALL(actorx, mCoBG_HIT_WALL_RIGHT) ||
            mAc_CHK_HIT_WALL(actorx, mCoBG_HIT_WALL_LEFT) ||
            mAc_CHK_HIT_ATR_WALL(actorx, mCoBG_HIT_WALL_LEFT)) {
            if (!goki->jump_flag) {
                actorx->shape_info.rotation.y += DEG2SHORT_ANGLE2(180.0f);
                actorx->world.angle.y = actorx->shape_info.rotation.y;
            }

            goki->jump_flag = TRUE;
        } else {
            if (aHG_check_threshold(actorx) == TRUE) {
                goki->timer = 5.0f + RANDOM_F(5.0f);
            }

            goki->jump_flag = FALSE;
        }

        if (goki->timer <= 0.0f) {
            aHG_decide_next_act_idx_wait_move(goki, game);
        } else {
            sAdo_OngenPos((uintptr_t)goki, NA_SE_GOKI_MOVE, &actorx->world.position);
        }
    }
}

static void aHG_dead(ACTOR* actorx, GAME* game) {
    HOUSE_GOKI_ACTOR* goki = (HOUSE_GOKI_ACTOR*)actorx;

    goki->alpha = goki->shadow_alpha;
    if (((int)goki->timer & 2) == 0) {
        goki->alpha = 0.0f;
    }

    goki->shadow_alpha -= 2.5f;
    if (goki->shadow_alpha < 0.0f) {
        goki->shadow_alpha = 0.0f;
    }

    actorx->shape_info.shadow_alpha_change_rate = goki->shadow_alpha * 0.0015f;
    if (goki->timer <= 0.0f) {
        Actor_delete(actorx);
    }
}

static void aHG_away_init(HOUSE_GOKI_ACTOR* goki, GAME* game) {
    goki->timer = 20.0f + RANDOM_F(20.0f);
    goki->timer2 = 0.0f;
    goki->jump_flag = FALSE;
    goki->anm_no = 0.0f;
    goki->actor_class.speed = 8.0f;
}

static void aHG_jump_away_init(HOUSE_GOKI_ACTOR* goki, GAME* game) {
    // @BUG - incorrect usage of random generator again. Devs clearly intended this to be a random
    // binary value (0 or 1), but calling RANDOM(1) will always result in 0 when aliasing to integer.
    // Bug results in the cockroach jump movement always being 22.5 degrees more than
    // the player angle.
#ifndef BUGFIXES
    goki->actor_class.shape_info.rotation.y = goki->actor_class.player_angle_y + (s16)(DEG2SHORT_ANGLE2(22.5f) - ((s16)RANDOM(1) * DEG2SHORT_ANGLE2(45.0f)));
#else
    goki->actor_class.shape_info.rotation.y = goki->actor_class.player_angle_y + (s16)(DEG2SHORT_ANGLE2(22.5f) - ((s16)RANDOM(2) * DEG2SHORT_ANGLE2(45.0f)));
#endif
    goki->actor_class.world.angle.y = goki->actor_class.shape_info.rotation.y;
    goki->actor_class.position_speed.y = 17.0f;
    goki->actor_class.gravity = -2.0f;
    goki->actor_class.speed = 5.0f;
    sAdo_OngenTrgStart(NA_SE_GOKI_JUMP_AWAY, &goki->actor_class.world.position);
}

static void aHG_wait_init(HOUSE_GOKI_ACTOR* goki, GAME* game) {
    goki->actor_class.shape_info.rotation.y = goki->actor_class.player_angle_y + DEG2SHORT_ANGLE2(180.0f);
    goki->actor_class.world.angle.y = goki->actor_class.shape_info.rotation.y;
    goki->actor_class.speed = 0.0f;
    goki->anm_no = 0.0f;
}

static void aHG_move_init(HOUSE_GOKI_ACTOR* goki, GAME* game) {
    xyz_t pos;

    goki->timer = 5.0f + RANDOM_F(5.0f);
    goki->jump_flag = FALSE;
    xyz_t_move(&pos, &goki->actor_class.world.position);
    pos.x += 80.0f - RANDOM_F(160.0f);
    pos.z += 80.0f - RANDOM_F(160.0f);
    goki->actor_class.shape_info.rotation.y = search_position_angleY(&goki->actor_class.world.position, &pos);
    goki->actor_class.world.angle.y = goki->actor_class.shape_info.rotation.y;
    goki->actor_class.speed = 4.0f;
}

static void aHG_dead_init(HOUSE_GOKI_ACTOR* goki, GAME* game) {
    eEC_CLIP->effect_make_proc(eEC_EFFECT_GOKI, goki->actor_class.world.position, 1, 0, game, EMPTY_NO, 0, 0);
    mCkRh_CalcCanLookGokiCount(-1);
    sAdo_OngenTrgStart(NA_SE_GOKI_DEAD, &goki->actor_class.world.position);
    goki->shadow_alpha = 255.0f;
    goki->actor_class.speed = 0.0f;
    goki->timer = 40.0f;
}

typedef void (*aHG_INIT_PROC)(HOUSE_GOKI_ACTOR* goki, GAME* game);

static void aHG_setupAction(HOUSE_GOKI_ACTOR* goki, GAME* game, int act) {
    static aHG_INIT_PROC init_proc[] = {
        &aHG_away_init,
        &aHG_jump_away_init,
        &aHG_wait_init,
        &aHG_move_init,
        &aHG_dead_init,
    };

    static aHG_ACT_PROC act_proc[] = {
        &aHG_away,
        &aHG_jump_away,
        &aHG_wait,
        &aHG_move,
        &aHG_dead,
    };

    goki->action = act;
    goki->act_proc = act_proc[act];
    (*init_proc[act])(goki, game);
}

static void aHG_actor_move(ACTOR* actorx, GAME* game) {
    HOUSE_GOKI_ACTOR* goki = (HOUSE_GOKI_ACTOR*)actorx;

    aHG_position_move(actorx);
    aHG_BGcheck(actorx);
    aHG_calc_timer(goki);

    if (goki->action != aHG_ACT_DEAD && aHG_calc_add_alpha(goki) == TRUE && aHG_check_dead(actorx, game) == TRUE) {
        aHG_setupAction(goki, game, aHG_ACT_DEAD);
    }

    (*goki->act_proc)(actorx, game);
}

extern Gfx act_m_house_goki1T_model[];
extern Gfx act_m_house_goki2T_model[];

static void aHG_actor_draw(ACTOR* actorx, GAME* game) {
    static Gfx* aHG_displayList[] = { act_m_house_goki1T_model, act_m_house_goki2T_model };
    GRAPH* graph = game->graph;
    HOUSE_GOKI_ACTOR* goki = (HOUSE_GOKI_ACTOR*)actorx;

    Matrix_push();
    Matrix_translate(actorx->world.position.x, actorx->world.position.y + 2.0f, actorx->world.position.z, MTX_LOAD);
    Matrix_scale(actorx->scale.x, actorx->scale.y, actorx->scale.z, MTX_MULT);
    Matrix_RotateX(actorx->shape_info.rotation.x, MTX_MULT);
    Matrix_RotateY(actorx->shape_info.rotation.y, MTX_MULT);
    _texture_z_light_fog_prim_xlu(graph);

    OPEN_POLY_XLU_DISP(graph);

    gSPMatrix(POLY_XLU_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_LOAD | G_MTX_NOPUSH);
    gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, (u32)goki->alpha);
    gSPDisplayList(POLY_XLU_DISP++, aHG_displayList[(int)goki->anm_no]);

    CLOSE_POLY_XLU_DISP(graph);

    Matrix_pull();
}
