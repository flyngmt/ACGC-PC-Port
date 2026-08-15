#ifndef AC_NPC_STATION_MASTER_H
#define AC_NPC_STATION_MASTER_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    aSTM_THINK_INIT_NONE,
    aSTM_THINK_INIT_GET_OFF_WAIT,
    aSTM_THINK_INIT_INTRO_DEMO_WAIT,
    aSTM_THINK_INIT_INTERRUPT_TURN,
    aSTM_THINK_INIT_INTERRUPT_MOVE,
    aSTM_THINK_INIT_MAKE_TRAIN,
    aSTM_THINK_INIT_MAKE_TRAIN_BF,
    aSTM_THINK_INIT_MOVE_TURN,
    aSTM_THINK_INIT_MOVE,
    aSTM_THINK_INIT_LOOK_P,
    aSTM_THINK_INIT_SEE_OFF,
    aSTM_THINK_INIT_GAME_END,

    aSTM_THINK_INIT_NUM
};

enum {
    aSTM_THINK_PROC_NONE,
    aSTM_THINK_PROC_GET_OFF_WAIT,
    aSTM_THINK_PROC_TURN,
    aSTM_THINK_PROC_LOOK_PLAYER,
    aSTM_THINK_PROC_INTERRUPT_TURN,
    aSTM_THINK_PROC_INTERRUPT_MOVE,
    aSTM_THINK_PROC_MAKE_TRAIN_BF,
    aSTM_THINK_PROC_MAKE_TRAIN,
    aSTM_THINK_PROC_TRAIN_ARRIVE_WAIT,
    aSTM_THINK_PROC_MOVE_TURN_BF,
    aSTM_THINK_PROC_MOVE,
    aSTM_THINK_PROC_IN_TRAIN,
    aSTM_THINK_PROC_IN_TRAIN2,
    aSTM_THINK_PROC_SEE_OFF,
    aSTM_THINK_PROC_TALK_WAIT,

    aSTM_THINK_PROC_NUM
};

enum {
    aSTM_TALK_REQUEST_NONE,
    aSTM_TALK_REQUEST_NORM,
    aSTM_TALK_REQUEST_FORCE,

    aSTM_TALK_REQUEST_NUM,
};

typedef struct npc_station_actor_s NPC_STATION_MASTER_ACTOR;

typedef void (*aSTM_TALK_PROC)(NPC_STATION_MASTER_ACTOR*, GAME_PLAY*);

struct npc_station_actor_s {
    NPC_ACTOR npc_class;
    aSTM_TALK_PROC talk_proc;
    ACTOR* train_actor_p;
    f32 move_ofs_x;
    u8 think_idx;
    u8 next_think_idx;
    u8 talk_idx;
    u8 melody_save;
    u8 think_proc_idx;
    u8 sound;
    u8 happening_sound;
    u8 timer;
    u8 talk_proc_idx;
    u8 station_check_res;
    u8 chan;
    u8 station_err;
#ifdef TARGET_PC
    f32 train_setup_accum;
#endif
};

extern ACTOR_PROFILE Npc_Station_Master_Profile;

#ifdef __cplusplus
}
#endif

#endif
