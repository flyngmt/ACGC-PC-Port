#include "ac_t_npc_sao.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_rcp.h"

static void aTNS_setupAction(ACTOR* actorx, u8 action);

ACTOR_PROFILE T_NpcSao_Profile = {
    mAc_PROFILE_T_NPCSAO,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_NPC_SAO,
    sizeof(NPC_SAO_TOOL_ACTOR),
    &aTNS_actor_ct,
    NONE_ACTOR_PROC,
    &aTNS_actor_move,
    &aTNS_actor_draw,
    NULL,
};

extern void aTNS_actor_ct(ACTOR* actorx, GAME* game) {
    ((NPC_SAO_TOOL_ACTOR*)actorx)->rotation_y_accum = 0.0f;
    aTNS_setupAction(actorx, 1);
}

static void aTNS_destruct(NPC_SAO_TOOL_ACTOR* npc_sao) {
    Actor_delete((ACTOR*)npc_sao);
}

static void aTNS_setupAction(ACTOR* actorx, u8 action) {
    NPC_SAO_TOOL_ACTOR* npc_sao = (NPC_SAO_TOOL_ACTOR*)actorx;

    static aTNS_ACTION_PROC process[] = { (aTNS_ACTION_PROC)&none_proc1, (aTNS_ACTION_PROC)&none_proc1,
                                          (aTNS_ACTION_PROC)&none_proc1, &aTNS_destruct,
                                          (aTNS_ACTION_PROC)&none_proc1, NULL };

    npc_sao->action_proc = process[action];
    npc_sao->action = action;
    npc_sao->tool_class.work0 = action;
}

extern void aTNS_actor_move(ACTOR* actorx, GAME* game) {
    NPC_SAO_TOOL_ACTOR* npc_sao = (NPC_SAO_TOOL_ACTOR*)actorx;
    s16 rotation_y;
    ACTOR* parent_actor;
    s16 parent_rotation_y;
    int temp;
    f32 pos_offset;

    if (npc_sao->tool_class.work0 != npc_sao->action) {
        aTNS_setupAction(actorx, npc_sao->tool_class.work0);
    }

    (npc_sao->action_proc)(npc_sao);

    parent_actor = actorx->parent_actor;
    temp = npc_sao->rotation_y;
    parent_rotation_y = parent_actor->shape_info.rotation.y;
#ifdef TARGET_PC
    rotation_y = temp + graph_dt_scaled_step(game, (int)(fqrand() * 6.0f + 2.0f) * 256, &npc_sao->rotation_y_accum);
#else
    rotation_y = temp + ((int)(fqrand() * 6.0f + 2.0f) * 256);
#endif

    npc_sao->pos_x = parent_actor->world.position.x + sin_s(parent_rotation_y) * 100.0f;
    npc_sao->pos_y = parent_actor->world.position.y + -20.0f + sin_s(rotation_y) * 1.5f;
    npc_sao->pos_z = parent_actor->world.position.z + cos_s(parent_rotation_y) * 100.0f;

    npc_sao->rotation_y = rotation_y;
}

extern Gfx tol_npcsao_1_sao_model[];
extern Gfx tol_npcsao_1_uki_model[];

extern void aTNS_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_SAO_TOOL_ACTOR* npc_sao = (NPC_SAO_TOOL_ACTOR*)actorx;
    GRAPH* g = game->graph;
    Gfx* gfx;

    if (npc_sao->tool_class.init_matrix == TRUE) {
        Matrix_put(&npc_sao->tool_class.matrix_work);
        Matrix_Position_Zero(&actorx->world.position);
        npc_sao->tool_class.init_matrix = FALSE;
    } else {
        Matrix_translate(actorx->world.position.x, actorx->world.position.y, actorx->world.position.z, MTX_LOAD);
        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);
    }

    _texture_z_light_fog_prim_npc(g);

    OPEN_DISP(g);
    gfx = NOW_POLY_OPA_DISP;

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(g), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, tol_npcsao_1_sao_model);
    Matrix_translate(npc_sao->pos_x, npc_sao->pos_y, npc_sao->pos_z, MTX_LOAD);
    Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);
    gSPMatrix(gfx++, _Matrix_to_Mtx_new(g), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, tol_npcsao_1_uki_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(g);
}
