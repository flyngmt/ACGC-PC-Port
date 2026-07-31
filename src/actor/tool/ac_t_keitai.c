#include "ac_t_keitai.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"
#include "m_common_data.h"

extern cKF_Animation_R_c cKF_ba_r_tol_keitai_1_keitai_on1;
extern cKF_Animation_R_c cKF_ba_r_tol_keitai_1_keitai_off1;
extern cKF_Skeleton_R_c cKF_bs_r_tol_keitai_1;

KEITAI_ACTION_ANIM aTKT_anm_dt[6] = {
    { &cKF_ba_r_tol_keitai_1_keitai_on1, 1.0f, 1.0f },   { &cKF_ba_r_tol_keitai_1_keitai_on1, 1.0f, 68.0f },
    { &cKF_ba_r_tol_keitai_1_keitai_off1, 1.0f, 61.0f }, { &cKF_ba_r_tol_keitai_1_keitai_off1, 1.0f, 61.0f },
    { &cKF_ba_r_tol_keitai_1_keitai_on1, 1.0f, 68.0f },  { NULL, 0.0f, 0.0f },
};

static void aTKT_actor_ct(ACTOR* actor, GAME* game);
static void aTKT_actor_move(ACTOR* actor, GAME* game);
static void aTKT_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE T_Keitai_Profile = {
    mAc_PROFILE_T_KEITAI,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEITAI,
    sizeof(KEITAI_ACTOR),
    &aTKT_actor_ct,
    NONE_ACTOR_PROC,
    &aTKT_actor_move,
    &aTKT_actor_draw,
    NULL,
};

static void aTKT_setupAction(KEITAI_ACTOR* actor, int action);

static void aTKT_actor_ct(ACTOR* actor, GAME* game) {
    KEITAI_ACTOR* keitai = (KEITAI_ACTOR*)actor;
    cKF_SkeletonInfo_R_ct(&keitai->keyframe, &cKF_bs_r_tol_keitai_1, NULL, keitai->work, keitai->morph);
    keitai->bank_ram_start = ((GAME_PLAY*)game)->object_exchange.banks[actor->data_bank_id].ram_start;
    aTKT_setupAction(keitai, aTOL_ACTION_TAKEOUT);
}

static void aTKT_calc_scale(ACTOR* actor, int idx) {
    static f32 start_scale[2] = { 0.0f, 1.0f };
    static f32 end_scale[2] = { 1.0f, 0.0f };
    static f32 start_chno[2] = { 10.0f, 33.0f };
    static f32 end_chno[2] = { 20.0f, 41.0f };

    f32 current_frame;
    f32 starting_chno;
    f32 ending_chno;
    f32 starting_scale;
    f32 ending_scale;
    f32 scale;
    KEITAI_ACTOR* keitai;

    keitai = (KEITAI_ACTOR*)actor;
    current_frame = keitai->keyframe.frame_control.current_frame;
    starting_chno = start_chno[idx];
    ending_chno = end_chno[idx];
    starting_scale = start_scale[idx];
    ending_scale = end_scale[idx];

    if (current_frame < starting_chno) {
        scale = starting_scale;
    } else if (current_frame > ending_chno) {
        scale = ending_scale;
    } else {
        scale = starting_scale +
                ((ending_scale - starting_scale) * ((current_frame - starting_chno) / (ending_chno - starting_chno)));
    }

    actor->scale.x = scale;
    actor->scale.y = scale;
    actor->scale.z = scale;
}

static void aTKT_takeout(ACTOR* actor) {
    aTKT_calc_scale(actor, 0);
}

static void aTKT_putaway(ACTOR* actor) {
    aTKT_calc_scale(actor, 1);
}

static void aTKT_destruct(ACTOR* actor) {
    Actor_delete(actor);
}

static void aTKT_s_takeout(ACTOR* actor) {
    KEITAI_ACTOR* keitai = (KEITAI_ACTOR*)actor;

    actor->scale.x = 1.0f;
    actor->scale.y = 1.0f;
    actor->scale.z = 1.0f;

    keitai->keyframe.frame_control.current_frame = keitai->keyframe.frame_control.end_frame;
}

static void aTKT_setupAction(KEITAI_ACTOR* keitai, int action) {
    static KEITAI_PROC process[] = {
        (KEITAI_PROC)none_proc1, aTKT_takeout, aTKT_putaway, aTKT_destruct, aTKT_s_takeout, NULL,
    };

    KEITAI_ACTION_ANIM* action_anim;
    f32 starting_frame;
    f32 ending_frame;

    keitai->action_proc = process[action];
    keitai->action = action;
    keitai->tools_class.work0 = action;

    action_anim = &aTKT_anm_dt[action];
    starting_frame = action_anim->start_frame;

    cKF_SkeletonInfo_R_init(&keitai->keyframe, keitai->keyframe.skeleton, action_anim->animation, starting_frame,
                            action_anim->end_frame, starting_frame, 0.5f, 0.0f, cKF_FRAMECONTROL_STOP, NULL);
}

static void aTKT_actor_move(ACTOR* actor, GAME* game) {
    KEITAI_ACTOR* keitai = (KEITAI_ACTOR*)actor;
    int action = keitai->tools_class.work0;
    if (action != keitai->action) {
        aTKT_setupAction(keitai, action);
    }

    cKF_SkeletonInfo_R_play(&keitai->keyframe);
    keitai->action_proc(actor);
}

static void aTKT_actor_draw(ACTOR* actor, GAME* game) {
    cKF_SkeletonInfo_R_c* keyf;
    GRAPH* graph;
    N64Mtx* mtx;
    Gfx* gfx;
    KEITAI_ACTOR* keitai;

    keitai = (KEITAI_ACTOR*)actor;
    keyf = &keitai->keyframe;
    graph = game->graph;
    mtx = GRAPH_ALLOC_TYPE(graph, N64Mtx, keyf->skeleton->num_shown_joints);

    if (mtx != NULL) {
        if (keitai->tools_class.init_matrix == TRUE) {
            Matrix_put(&keitai->tools_class.matrix_work);
            Matrix_Position_Zero(&actor->world.position);
            keitai->tools_class.init_matrix = FALSE;
        } else {
            Matrix_translate(actor->world.position.x, actor->world.position.y, actor->world.position.z, MTX_LOAD);
            Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);
        }

        _texture_z_light_fog_prim_npc(graph);

        OPEN_DISP(graph);

        gfx = NOW_POLY_OPA_DISP;
        Matrix_scale(actor->scale.x, actor->scale.y, actor->scale.z, MTX_MULT);
        gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        SET_POLY_OPA_DISP(gfx);

        cKF_Si3_draw_R_SV(game, keyf, mtx, NULL, NULL, NULL);
        CLOSE_DISP(graph);
    }
}
