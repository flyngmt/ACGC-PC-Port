#include "ac_t_hat2.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"


static void aTHT2_actor_ct(ACTOR* actor, GAME*);
static void aTHT2_actor_move(ACTOR* actor, GAME*);
static void aTHT2_actor_draw(ACTOR* actor, GAME*);
static void aTHT2_setupAction(ACTOR*, int);

ACTOR_PROFILE T_Hat2_Profile = {
    mAc_PROFILE_T_HAT2,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_TOOLS,
    sizeof(HAT2_ACTOR),
    &aTHT2_actor_ct,
    NONE_ACTOR_PROC,
    &aTHT2_actor_move,
    &aTHT2_actor_draw,
    NULL
};

extern Gfx crw_hat2_body_model[];

static void aTHT2_actor_ct(ACTOR* actor, GAME* game){

    aTHT2_setupAction(actor,4);
}

static void aTHT2_destruct(ACTOR* actor){

    Actor_delete(actor);
}


static void aTHT2_setupAction(ACTOR*actor, int action){
    HAT2_ACTOR* hat = (HAT2_ACTOR*)actor;
    static HAT2_PROC process[] = {
        (HAT2_PROC)none_proc1,(HAT2_PROC)none_proc1,(HAT2_PROC)none_proc1,aTHT2_destruct,(HAT2_PROC)none_proc1,NULL
    };

    hat->proc = process[action];
    hat->current_id = action;
    hat->tools_class.work0 = action;

}

static void aTHT2_actor_move(ACTOR* actor, GAME* game){
    HAT2_ACTOR* hat = (HAT2_ACTOR*)actor;

    if(hat->tools_class.work0 != hat->current_id){
        aTHT2_setupAction(actor, hat->tools_class.work0);
    }

    hat->proc(actor);
}

static void aTHT2_actor_draw(ACTOR* actor, GAME* game){
    HAT2_ACTOR* hat = (HAT2_ACTOR*)actor;

    GRAPH* graph;
    Gfx* gfxp;

    if(hat->tools_class.init_matrix == 1){
        graph = game->graph;
        
        OPEN_DISP(graph);
        
        Matrix_put(&hat->tools_class.matrix_work);
        Matrix_Position_Zero(&hat->tools_class.actor_class.world.position);
        
        hat->tools_class.init_matrix = 0;
    
        _texture_z_light_fog_prim_npc(graph); 

        gfxp = NOW_POLY_OPA_DISP;
        gSPMatrix(gfxp++, _Matrix_to_Mtx_new(graph),G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxp++, crw_hat2_body_model);
        SET_POLY_OPA_DISP(gfxp);
        
        CLOSE_DISP(graph);
    }

        
}