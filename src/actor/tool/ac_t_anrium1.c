#include "ac_t_anrium1.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"


static void aTA1_actor_ct(ACTOR* actor, GAME*);
static void aTA1_actor_move(ACTOR* actor, GAME*);
static void aTA1_actor_draw(ACTOR* actor, GAME*);
static void aTA1_setupAction(ACTOR*, int);

ACTOR_PROFILE T_Anrium1_Profile = {
    mAc_PROFILE_T_ANRIUM1,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_TOOLS,
    sizeof(ANRIUM1_ACTOR),
    &aTA1_actor_ct,
    NONE_ACTOR_PROC,
    &aTA1_actor_move,
    &aTA1_actor_draw,
    NULL
};

extern Gfx crw_anrium1_body_model[];

static void aTA1_actor_ct(ACTOR* actor, GAME* game){

    aTA1_setupAction(actor,4);
}

static void aTA1_destruct(ACTOR* actor){

    Actor_delete(actor);
}


static void aTA1_setupAction(ACTOR*actor, int action){
    ANRIUM1_ACTOR* anrium = (ANRIUM1_ACTOR*)actor;
    static ANRIUM1_PROC process[] = {
        (ANRIUM1_PROC)none_proc1,(ANRIUM1_PROC)none_proc1,(ANRIUM1_PROC)none_proc1,aTA1_destruct,(ANRIUM1_PROC)none_proc1,NULL
    };

    anrium->proc = process[action];
    anrium->current_id = action;
    anrium->tools_class.work0 = action;

}

static void aTA1_actor_move(ACTOR* actor, GAME* game){
    ANRIUM1_ACTOR* anrium = (ANRIUM1_ACTOR*)actor;

    if(anrium->tools_class.work0 != anrium->current_id){
        aTA1_setupAction(actor, anrium->tools_class.work0);
    }

    anrium->proc(actor);
}

static void aTA1_actor_draw(ACTOR* actor, GAME* game){
    ANRIUM1_ACTOR* anrium = (ANRIUM1_ACTOR*)actor;

    GRAPH* graph;
    Gfx* gfxp;

    if(anrium->tools_class.init_matrix == 1){
        graph = game->graph;
        
        OPEN_DISP(graph);
        
        Matrix_put(&anrium->tools_class.matrix_work);
        Matrix_Position_Zero(&anrium->tools_class.actor_class.world.position);
        
        anrium->tools_class.init_matrix = 0;
    
        _texture_z_light_fog_prim_npc(graph); 

        gfxp = NOW_POLY_OPA_DISP;
        gSPMatrix(gfxp++, _Matrix_to_Mtx_new(graph),G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxp++, crw_anrium1_body_model);
        SET_POLY_OPA_DISP(gfxp);
        
        CLOSE_DISP(graph);
    }

        
}