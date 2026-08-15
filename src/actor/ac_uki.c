#include "ac_uki.h"

#include "m_play.h"
#include "m_name_table.h"
#include "ac_set_ovl_gyoei.h"
#include "m_vibctl.h"
#include "m_common_data.h"
#include "ef_effect_control.h"
#include "m_player_lib.h"
#include "sys_matrix.h"
#include "m_actor_shadow.h"

enum {
    aUKI_PROC_CARRY,
    aUKI_PROC_READY,
    aUKI_PROC_AIR,
    aUKI_PROC_CAST,
    aUKI_PROC_WAIT,
    aUKI_PROC_HIT,
    aUKI_PROC_TOUCH,
    aUKI_PROC_BITE,
    aUKI_PROC_CATCH,
    aUKI_PROC_GET,
    aUKI_PROC_FORCE,

    aUKI_PROC_NUM
};

static void aUKI_actor_ct(ACTOR* actorx, GAME* game);
static void aUKI_actor_dt(ACTOR* actorx, GAME* game);
static void aUKI_actor_move(ACTOR* actorx, GAME* game);
static void aUKI_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Uki_Profile = {
    mAc_PROFILE_UKI,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    ETC_UKI,
    ACTOR_OBJ_BANK_UKI,
    sizeof(UKI_ACTOR),
    &aUKI_actor_ct,
    &aUKI_actor_dt,
    &aUKI_actor_move,
    NULL,
    NULL,
};
// clang-format on

// clang-format off
static ClObjPipeData_c aUKI_CoInfoData = {
    0x3D, 0x20, ClObj_TYPE_PIPE,
    0x01,
    8, 8, 0,  0, 0, 0,
};
// clang-format on

static StatusData_c aUKI_StatusData = { 0, 8, 8, 0, 50 };

#include "../src/actor/ac_gyoei_type.c_inc"

typedef struct uki_vib_s {
    int n_frames;
    int attack_frames;
    int sustain_frames;
    int release_frames;
} aUKI_vib_c;

static void aUKI_set_value(ACTOR* actorx, xyz_t pos, xyz_t pos_speed, int angle_speed_y, int command);
static mActor_name_t aUKI_get_fish_type(ACTOR* actorx);
static void aUKI_set_proc(ACTOR* actorx, GAME* game, int proc, int arg);

static void aUKI_actor_ct(ACTOR* actorx, GAME* game) {
    UKI_ACTOR* uki = (UKI_ACTOR*)actorx;

    Shape_Info_init(actorx, 0.0, &mAc_ActorShadowEllipse, 4.5, 8.5);
    actorx->shape_info.draw_shadow = FALSE;
    ClObjPipe_ct(game, &uki->col_pipe);
    ClObjPipe_set5(game, &uki->col_pipe, actorx, &aUKI_CoInfoData);
    CollisionCheck_Status_set3(&actorx->status_data, &aUKI_StatusData);
    actorx->max_velocity_y = -20.0;
    actorx->gravity = 1.2;
    actorx->speed = 0.0;
    uki->_194 = 0.0;
    Matrix_copy_MtxF(&uki->mtxf, &MtxF_clear);
    actorx->scale.x = 0.01;
    actorx->scale.y = 0.01;
    actorx->scale.z = 0.01;
    actorx->world.position = uki->right_hand_pos;
    uki->set_value_proc = &aUKI_set_value;
    uki->get_fish_type_proc = &aUKI_get_fish_type;
    uki->child_actor = NULL;
    uki->frame_timer = 2;
    uki->cast_timer = 0;
    uki->touch_timer = 0;
    uki->touched_flag = FALSE;
    uki->hit_water_flag = FALSE;
    uki->gyo_type = -1;
    uki->color[0] = 255;
    uki->color[1] = 255;
    uki->color[2] = 255;
    uki->gyo_command = 0;
    uki->gyo_status = 0;
    uki->status = aUKI_STATUS_CARRY;
    uki->proc = aUKI_PROC_CARRY;
    uki->coast_flag = FALSE;
    uki->_2B5 = 0;
    uki->hamon_accum = 0.0f;
    uki->touch_vib_accum = 0.0f;
    uki->logic_accum = 0.0f;
    uki->logic_ticks = 0;
}

static void aUKI_actor_dt(ACTOR* actorx, GAME* game) {
    UKI_ACTOR* uki = (UKI_ACTOR*)actorx;

    ClObjPipe_dt(game, &uki->col_pipe);
}

#include "../src/actor/ac_uki_move.c_inc"
#include "../src/actor/ac_uki_draw.c_inc"
