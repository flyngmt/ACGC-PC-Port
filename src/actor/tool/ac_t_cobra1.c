#include "ac_t_cobra1.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"


static void aTCB1_actor_ct(ACTOR* actor, GAME*);
static void aTCB1_actor_move(ACTOR* actor, GAME*);
static void aTCB1_actor_draw(ACTOR* actor, GAME*);
static void aTCB1_setupAction(ACTOR*, int);

ACTOR_PROFILE T_Cobra1_Profile = {
    mAc_PROFILE_T_COBRA1,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_TOOLS,
    sizeof(COBRA1_ACTOR),
    &aTCB1_actor_ct,
    NONE_ACTOR_PROC,
    &aTCB1_actor_move,
    &aTCB1_actor_draw,
    NULL
};

extern Gfx crw_cobra_model[];

static void aTCB1_actor_ct(ACTOR* actor, GAME* game){

    aTCB1_setupAction(actor,4);
}

static void aTCB1_destruct(ACTOR* actor){

    Actor_delete(actor);
}


static void aTCB1_setupAction(ACTOR*actor, int action){
    COBRA1_ACTOR* cobra = (COBRA1_ACTOR*)actor;
    static COBRA1_PROC process[] = {
        (COBRA1_PROC)none_proc1,(COBRA1_PROC)none_proc1,(COBRA1_PROC)none_proc1,aTCB1_destruct,(COBRA1_PROC)none_proc1,NULL
    };

    cobra->proc = process[action];
    cobra->current_id = action;
    cobra->tools_class.work0 = action;

}

static void aTCB1_actor_move(ACTOR* actor, GAME* game){
    COBRA1_ACTOR* cobra = (COBRA1_ACTOR*)actor;

    if(cobra->tools_class.work0 != cobra->current_id){
        aTCB1_setupAction(actor, cobra->tools_class.work0);
    }

    cobra->proc(actor);
}

static void aTCB1_actor_draw(ACTOR* actor, GAME* game){
    COBRA1_ACTOR* cobra = (COBRA1_ACTOR*)actor;

    GRAPH* graph;
    Gfx* gfxp;

    if(cobra->tools_class.init_matrix == 1){
        graph = game->graph;
        
        OPEN_DISP(graph);
        
        Matrix_put(&cobra->tools_class.matrix_work);
        Matrix_Position_Zero(&cobra->tools_class.actor_class.world.position);
        
        cobra->tools_class.init_matrix = 0;
    
        _texture_z_light_fog_prim_npc(graph); 

        gfxp = NOW_POLY_OPA_DISP;
        gSPMatrix(gfxp++, _Matrix_to_Mtx_new(graph),G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxp++, crw_cobra_model);
        SET_POLY_OPA_DISP(gfxp);
        
        CLOSE_DISP(graph);
    }

        
}