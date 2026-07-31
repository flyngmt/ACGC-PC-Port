#include "ac_t_hasu1.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"


static void aTHS1_actor_ct(ACTOR* actor, GAME*);
static void aTHS1_actor_move(ACTOR* actor, GAME*);
static void aTHS1_actor_draw(ACTOR* actor, GAME*);
static void aTHS1_setupAction(ACTOR*, int);

ACTOR_PROFILE T_Hasu1_Profile = {
    mAc_PROFILE_T_HASU1,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_TOOLS,
    sizeof(HASU1_ACTOR),
    &aTHS1_actor_ct,
    NONE_ACTOR_PROC,
    &aTHS1_actor_move,
    &aTHS1_actor_draw,
    NULL
};

extern Gfx crw_hasu1_body_model[];

static void aTHS1_actor_ct(ACTOR* actor, GAME* game){

    aTHS1_setupAction(actor,4);
}

static void aTHS1_destruct(ACTOR* actor){

    Actor_delete(actor);
}


static void aTHS1_setupAction(ACTOR*actor, int action){
    HASU1_ACTOR* hasu = (HASU1_ACTOR*)actor;
    static HASU1_PROC process[] = {
        (HASU1_PROC)none_proc1,(HASU1_PROC)none_proc1,(HASU1_PROC)none_proc1,aTHS1_destruct,(HASU1_PROC)none_proc1,NULL
    };

    hasu->proc = process[action];
    hasu->current_id = action;
    hasu->tools_class.work0 = action;

}

static void aTHS1_actor_move(ACTOR* actor, GAME* game){
    HASU1_ACTOR* hasu = (HASU1_ACTOR*)actor;

    if(hasu->tools_class.work0 != hasu->current_id){
        aTHS1_setupAction(actor, hasu->tools_class.work0);
    }

    hasu->proc(actor);
}

static void aTHS1_actor_draw(ACTOR* actor, GAME* game){
    HASU1_ACTOR* hasu = (HASU1_ACTOR*)actor;

    GRAPH* graph;
    Gfx* gfxp;

    if(hasu->tools_class.init_matrix == 1){
        graph = game->graph;
        
        OPEN_DISP(graph);
        
        Matrix_put(&hasu->tools_class.matrix_work);
        Matrix_Position_Zero(&hasu->tools_class.actor_class.world.position);
        
        hasu->tools_class.init_matrix = 0;
    
        _texture_z_light_fog_prim_npc(graph); 

        gfxp = NOW_POLY_OPA_DISP;
        gSPMatrix(gfxp++, _Matrix_to_Mtx_new(graph),G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxp++, crw_hasu1_body_model);
        SET_POLY_OPA_DISP(gfxp);
        
        CLOSE_DISP(graph);
    }

        
}