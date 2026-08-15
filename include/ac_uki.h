#ifndef AC_UKI_H
#define AC_UKI_H

#include "types.h"
#include "m_actor.h"
#include "libultra/ultratypes.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    aUKI_STATUS_0,
    aUKI_STATUS_CARRY,
    aUKI_STATUS_READY,
    aUKI_STATUS_CAST,
    aUKI_STATUS_FLOAT,
    aUKI_STATUS_VIB,
    aUKI_STATUS_COMEBACK,
    aUKI_STATUS_CATCH,

    aUKI_STATUS_NUM
};

typedef void (*aUKI_SET_VALUE_PROC)(ACTOR* actorx, xyz_t pos, xyz_t pos_speed, int angle_speed_y, int command);
typedef mActor_name_t (*aUKI_GET_FISH_TYPE)(ACTOR* actorx);

/* sizeof(UKI_ACTOR) == 0x2C8 */
typedef struct actor_uki_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ ACTOR* child_actor;
    /* 0x178 */ ClObjPipe_c col_pipe;
    /* 0x194 */ f32 _194;
    /* 0x198 */ MtxF mtxf;
    /* 0x1D8 */ s16 proc;
    /* 0x1DC */ xyz_t parabola_vec[2];
    /* 0x1F4 */ xyz_t parabola_acc[2];
    /* 0x20C */ f32 range;
    /* 0x210 */ aUKI_SET_VALUE_PROC set_value_proc;
    /* 0x214 */ aUKI_GET_FISH_TYPE get_fish_type_proc;
    /* 0x218 */ xyz_t right_hand_pos;
    /* 0x224 */ xyz_t position_speed;
    /* 0x230 */ int angle_speed_y;
    /* 0x234 */ int command;
    /* 0x238 */ int status;
    /* 0x23C */ xyz_t cast_goal_point;
    /* 0x248 */ xyz_t rod_top_position;
    /* 0x254 */ xyz_t left_hand_pos;
    /* 0x260 */ u8 touched_flag;
    /* 0x261 */ u8 hit_water_flag;
    /* 0x262 */ s16 frame_timer;
    /* 0x264 */ s16 cast_timer;
    /* 0x266 */ s16 touch_timer;
    /* 0x268 */ xyz_t uki_pos;
    /* 0x274 */ xyz_t gyo_pos;
    /* 0x280 */ s_xyz uki_angle;
    /* 0x286 */ s16 uki_rot_speed;
    /* 0x288 */ int gyo_command;
    /* 0x28C */ int gyo_status;
    /* 0x290 */ int gyo_type;
    /* 0x294 */ f32 gyo_scale;
    /* 0x298 */ int color[3]; /* rgb */
    /* 0x2A4 */ u8 _2A4[0x10];
    /* 0x2B4 */ u8 coast_flag;
    /* 0x2B5 */ u8 _2B5;
    /* 0x2B8 */ f32 hamon_accum;
    /* 0x2BC */ f32 touch_vib_accum;
    /* 0x2C0 */ f32 logic_accum;
    /* 0x2C4 */ int logic_ticks;
} UKI_ACTOR;

extern ACTOR_PROFILE Uki_Profile;

#ifdef __cplusplus
}
#endif

#endif
