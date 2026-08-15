#ifndef AC_EV_DESIGNER_H
#define AC_EV_DESIGNER_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ev_designer_save_data_s {
    int button_count;
    int result;
} aEv_designer_c;

typedef struct ev_designer_actor_s EV_DESIGNER_ACTOR;

typedef void (*aEDSN_TALK_PROC)(EV_DESIGNER_ACTOR* designer, GAME* game);
typedef void (*aEDSN_THINK_PROC)(EV_DESIGNER_ACTOR* designer, GAME_PLAY* play);

struct ev_designer_actor_s {
    NPC_ACTOR npc_class;
    u8 think_idx;
    u8 next_think_idx;
    u8 talk_idx;
    u8 melody_save;
    aEDSN_THINK_PROC think_proc;
    aEDSN_TALK_PROC talk_proc;
    mActor_name_t present;
    u8 wear_flag;
    u8 complete_flag;
    s16 wash_time;
    u8 camera_flag;
    u8 pl_talk_lock;
    f32 clean_speed;
    aEv_designer_c* tmp_save_p;
    ACTOR* s_car_p;
#ifdef TARGET_PC
    f32 wash_time_accum;
#endif
};

extern ACTOR_PROFILE Ev_Designer_Profile;

#ifdef __cplusplus
}
#endif

#endif
