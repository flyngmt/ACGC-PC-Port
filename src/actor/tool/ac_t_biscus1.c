#include "ac_t_biscus1.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"


static void aTB1_actor_ct(ACTOR* actor, GAME*);
static void aTB1_actor_move(ACTOR* actor, GAME*);
static void aTB1_actor_draw(ACTOR* actor, GAME*);
static void aTB1_setupAction(ACTOR*, int);

ACTOR_PROFILE T_Biscus1_Profile = {
    mAc_PROFILE_T_BISCUS1,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_TOOLS,
    sizeof(BISCUS1_ACTOR),
    &aTB1_actor_ct,
    NONE_ACTOR_PROC,
    &aTB1_actor_move,
    &aTB1_actor_draw,
    NULL
};

extern Gfx crw_biscus1_body_model[];

static void aTB1_actor_ct(ACTOR* actor, GAME* game){

    aTB1_setupAction(actor,4);
}

static void aTB1_destruct(ACTOR* actor){

    Actor_delete(actor);
}


static void aTB1_setupAction(ACTOR*actor, int action){
    BISCUS1_ACTOR* biscus = (BISCUS1_ACTOR*)actor;
    static BISCUS1_PROC process[] = {
        (BISCUS1_PROC)none_proc1,(BISCUS1_PROC)none_proc1,(BISCUS1_PROC)none_proc1,aTB1_destruct,(BISCUS1_PROC)none_proc1,NULL
    };

    biscus->proc = process[action];
    biscus->current_id = action;
    biscus->tools_class.work0 = action;

}

static void aTB1_actor_move(ACTOR* actor, GAME* game){
    BISCUS1_ACTOR* biscus = (BISCUS1_ACTOR*)actor;

    if(biscus->tools_class.work0 != biscus->current_id){
        aTB1_setupAction(actor, biscus->tools_class.work0);
    }

    biscus->proc(actor);
}

static void aTB1_actor_draw(ACTOR* actor, GAME* game){
    BISCUS1_ACTOR* biscus = (BISCUS1_ACTOR*)actor;

    GRAPH* graph;
    Gfx* gfxp;

    if(biscus->tools_class.init_matrix == 1){
        graph = game->graph;
        
        OPEN_DISP(graph);
        
        Matrix_put(&biscus->tools_class.matrix_work);
        Matrix_Position_Zero(&biscus->tools_class.actor_class.world.position);
        
        biscus->tools_class.init_matrix = 0;
    
        _texture_z_light_fog_prim_npc(graph); 

        gfxp = NOW_POLY_OPA_DISP;
        gSPMatrix(gfxp++, _Matrix_to_Mtx_new(graph),G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxp++, crw_biscus1_body_model);
        SET_POLY_OPA_DISP(gfxp);
        
        CLOSE_DISP(graph);
    }

        
}