#include "ac_t_hat3.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"


static void aTHT3_actor_ct(ACTOR* actor, GAME*);
static void aTHT3_actor_move(ACTOR* actor, GAME*);
static void aTHT3_actor_draw(ACTOR* actor, GAME*);
static void aTHT3_setupAction(ACTOR*, int);

ACTOR_PROFILE T_Hat3_Profile = {
    mAc_PROFILE_T_HAT3,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_TOOLS,
    sizeof(HAT3_ACTOR),
    &aTHT3_actor_ct,
    NONE_ACTOR_PROC,
    &aTHT3_actor_move,
    &aTHT3_actor_draw,
    NULL
};

extern Gfx crw_hat3_body_model[];

static void aTHT3_actor_ct(ACTOR* actor, GAME* game){

    aTHT3_setupAction(actor,4);
}

static void aTHT3_destruct(ACTOR* actor){

    Actor_delete(actor);
}


static void aTHT3_setupAction(ACTOR*actor, int action){
    HAT3_ACTOR* hat = (HAT3_ACTOR*)actor;
    static HAT3_PROC process[] = {
        (HAT3_PROC)none_proc1,(HAT3_PROC)none_proc1,(HAT3_PROC)none_proc1,aTHT3_destruct,(HAT3_PROC)none_proc1,NULL
    };

    hat->proc = process[action];
    hat->current_id = action;
    hat->tools_class.work0 = action;

}

static void aTHT3_actor_move(ACTOR* actor, GAME* game){
    HAT3_ACTOR* hat = (HAT3_ACTOR*)actor;

    if(hat->tools_class.work0 != hat->current_id){
        aTHT3_setupAction(actor, hat->tools_class.work0);
    }

    hat->proc(actor);
}

static void aTHT3_actor_draw(ACTOR* actor, GAME* game){
    HAT3_ACTOR* hat = (HAT3_ACTOR*)actor;

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
        gSPDisplayList(gfxp++, crw_hat3_body_model);
        SET_POLY_OPA_DISP(gfxp);
        
        CLOSE_DISP(graph);
    }

        
}