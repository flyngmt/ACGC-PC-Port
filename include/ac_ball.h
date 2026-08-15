#ifndef AC_BALL_H
#define AC_BALL_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aBALL_STATE_DEAD (1 << 0)
#define aBALL_STATE_IN_HOLE (1 << 1)
#define aBALL_STATE_PLAYER_HIT_SCOOP (1 << 2)
#define aBALL_STATE_PLAYER_HIT_AXE (1 << 3)


typedef void (*BALL_PROCESS_PROC)(ACTOR*, GAME*);

typedef struct actor_ball_s {
    ACTOR actor_class;
    ClObjPipe_c ball_pipe;
    u8 pad[0x40]; 
    xyz_t bgpos;
    ACTOR* collider;
    BALL_PROCESS_PROC process_proc;
    int unk1E4;
    f32 ball_y;
    f32 ball_max_speed;
    f32 ball_acceleration;
    f32 ball_speed;
    int type;
    s16 timer;
    s16 unk1FE;
    s_xyz angle;
    s16 unk206;
    s16 state_flags;
    s16 unk20A;
    s16 unk20C;
    f32 grass_effect_accum;
    f32 water_effect_accum;
    u32 water_effect_frame;
    f32 collider_timer_accum;
} BALL_ACTOR;

extern ACTOR_PROFILE Ball_Profile;

#ifdef __cplusplus
}
#endif

#endif
