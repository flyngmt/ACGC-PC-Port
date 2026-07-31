#include "ac_t_bag1.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"


static void aTBG1_actor_ct(ACTOR* actor, GAME*);
static void aTBG1_actor_move(ACTOR* actor, GAME*);
static void aTBG1_actor_draw(ACTOR* actor, GAME*);
static void aTBG1_setupAction(ACTOR*, int);

ACTOR_PROFILE T_Bag1_Profile = {
    mAc_PROFILE_T_BAG1,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_TOOLS,
    sizeof(BAG1_ACTOR),
    &aTBG1_actor_ct,
    NONE_ACTOR_PROC,
    &aTBG1_actor_move,
    &aTBG1_actor_draw,
    NULL
};

extern Gfx crw_bag1_body_model[];

static void aTBG1_actor_ct(ACTOR* actor, GAME* game){

    aTBG1_setupAction(actor,4);
}

static void aTBG1_destruct(ACTOR* actor){

    Actor_delete(actor);
}


static void aTBG1_setupAction(ACTOR*actor, int action){
    BAG1_ACTOR* bag = (BAG1_ACTOR*)actor;
    static BAG1_PROC process[] = {
        (BAG1_PROC)none_proc1,(BAG1_PROC)none_proc1,(BAG1_PROC)none_proc1,aTBG1_destruct,(BAG1_PROC)none_proc1,NULL
    };

    bag->proc = process[action];
    bag->current_id = action;
    bag->tools_class.work0 = action;

}

static void aTBG1_actor_move(ACTOR* actor, GAME* game){
    BAG1_ACTOR* bag = (BAG1_ACTOR*)actor;

    if(bag->tools_class.work0 != bag->current_id){
        aTBG1_setupAction(actor, bag->tools_class.work0);
    }

    bag->proc(actor);
}

static void aTBG1_actor_draw(ACTOR* actor, GAME* game){
    BAG1_ACTOR* bag = (BAG1_ACTOR*)actor;

    GRAPH* graph;
    Gfx* gfxp;

    if(bag->tools_class.init_matrix == 1){
        graph = game->graph;
        
        OPEN_DISP(graph);
        
        Matrix_put(&bag->tools_class.matrix_work);
        Matrix_Position_Zero(&bag->tools_class.actor_class.world.position);
        
        bag->tools_class.init_matrix = 0;
    
        _texture_z_light_fog_prim_npc(graph); 

        gfxp = NOW_POLY_OPA_DISP;
        gSPMatrix(gfxp++, _Matrix_to_Mtx_new(graph),G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxp++, crw_bag1_body_model);
        SET_POLY_OPA_DISP(gfxp);
        
        CLOSE_DISP(graph);
    }

        
}