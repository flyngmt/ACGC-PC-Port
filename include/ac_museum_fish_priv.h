#ifndef AC_MUSEUM_FISH_PRIV_H
#define AC_MUSEUM_FISH_PRIV_H

#include "ac_museum_fish.h"
#include "m_msg.h"
#include "m_common_data.h"
#include "m_lib.h"
#include "sys_matrix.h"
#include "m_player_lib.h"
#include "m_debug_mode.h"
#include "m_rcp.h"
#include "ac_gyoei.h"
#include "sys_math.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    mfish_TANK_0,
    mfish_TANK_1,
    mfish_TANK_2,
    mfish_TANK_3,
    mfish_TANK_4,

    mfish_TANK_NUM
};

// found useful macros
#define MY_MAX(a, b) (((a) >= (b)) ? (a) : (b))
#define MY_CLAMP(v, l, h) MIN(MY_MAX((l), (v)), (h))
#define ARRAY_LEN(a) (sizeof(a) / sizeof(*a))

#define SHORT2DEG_ANGLE2(x) ((x) * (360.0f / 65536.0f))
#define RANDOMF_RANGE(min, max) ((f32)(min) + (f32)RANDOM_F((f32)(max) - (f32)(min)))
#define RANDOM2F_RANGE(min, max) ((f32)(min) + (f32)RANDOM2_F((f32)(max) - (f32)(min)))
#define RANDOM_RANGE(min, max) ((int)(min) + (int)RANDOM((int)(max) - (int)(min)))
#define RANDOM2_RANGE(min, max) ((int)(min) + (int)RANDOM2((int)(max) - (int)(min)))

#define artificial_padding(lastOffset, currentOffset, typeOfLastMember) \
    u8 __##currentOffset##padding[currentOffset - lastOffset - sizeof(typeOfLastMember)]

typedef struct _FISH_PRIVATE_DATA;

typedef void (*PRIV_FISH_CONSTRUCTOR)(struct _FISH_PRIVATE_DATA*, GAME*);
typedef void (*PRIV_FISH_MOVE)(struct _FISH_PRIVATE_DATA*, GAME*);
typedef void (*PRIV_FISH_DRAW)(struct _FISH_PRIVATE_DATA*, GAME*);
typedef void (*PRIV_FISH_PROCESS)(struct _FISH_PRIVATE_DATA*, GAME*);

// struct decls
typedef struct _MUSEUM_FISH_INIT_DATA {
    f32 renderScale;
    f32 ofs_y;
    f32 _08;
    f32 _0C;
    f32 _10;
    f32 _14;
    f32 _18;
    f32 _1C;
    f32 _20;
    f32 ofs_z;
    f32 _28;
    s16 activeFramesMin;
    s16 activeFramesRange;
    s16 _30;
} MUSEUM_FISH_INIT_DATA; // size: 0x34

typedef struct fish_keyframe_s {
    cKF_SkeletonInfo_R_c keyframe; // offset 0, size 0x70
    N64Mtx mtx[2][9];
    s_xyz work[6];
    s_xyz morph[6];
    s_xyz _538;
    // unused 2 byte padding here
    xyz_t _540;
    cKF_Skeleton_R_c* _54C;
    cKF_Animation_R_c* _550[2];
} mfish_keyframe_c; // size 558

typedef struct hasu_s {
    /* 0x000 */ cKF_SkeletonInfo_R_c keyframe; // offset 0, size 0x70
    /* 0x070 */ N64Mtx mtx[2][9];
    /* 0x4F0 */ s_xyz work[9];
    /* 0x526 */ s_xyz morph[9];
    /* 0x55C */ f32 _55C;
    /* 0x560 */ f32 _560;
    /* 0x564 */ f32 _564;
    /* 0x568 */ s16 _568;
    /* 0x56A */ s16 _56A;
    /* 0x56C */ s16 _56C;
    // 2 bytes pad
} mfish_hasu_c;

typedef enum fish_type MUSEUM_FISH_TYPE;
typedef struct _FISH_PRIVATE_DATA MUSEUM_FISH_PRIVATE_DATA;

struct _FISH_PRIVATE_DATA {
    MUSEUM_FISH_INIT_DATA init_data;
    PRIV_FISH_PROCESS currentProcess; // size:4
    mfish_keyframe_c kf;

    mfish_hasu_c* hasu_p; // lilypad
    MUSEUM_FISH_PRIVATE_DATA* _594;
    MUSEUM_FISH_PRIVATE_DATA* _598;

    MUSEUM_FISH_TYPE fish_idx;
    xyz_t position;
    xyz_t _5AC;
    xyz_t objchk_pos;
    artificial_padding(0x5B8, 0x5D0, xyz_t);
    xyz_t _5D0;
    xyz_t _5DC;
    f32 _5E8;
    f32 _5EC;
    f32 _5F0;
    f32 _5F4;
    f32 _5F8;
    f32 _5FC;
    f32 _600;
    f32 _604;
    f32 _608;
    s_xyz _60C;
    s_xyz _612;
    s_xyz _618;
    s16 _61E;
    s16 _620;
    s16 _622;
    s16 _624;
    s16 activityFrameCount;
    s16 savedActivityFrameCount;
    s16 escape_angle;
    s16 _62C;
    s16 _62E_flags;
    s16 tank;
    s16 _632;
    s16 hide_camera_angle;
    s16 _636;
    s16 _638;
    s16 _63A;
    s16 _63C;
    s16 _63E;
    s16 _640;
    s16 _642;
    s16 _644;
    s16 _646;
    f32 hamon_accum;
}; // size 64C

// Holds data for the underwater grass
typedef mfish_keyframe_c MUSEUM_FISH_KUSA_DATA;

typedef struct _FISH_DISPLAY_MSG_INFO {
    s16 fishName;
    s16 fishInfo;
} FISH_DISPLAY_MSG_INFO;

typedef struct _MUSEUM_FISH_ACTOR {
    ACTOR actor; // offset: 0, size: 0x174
    int _174;
    MUSEUM_FISH_PRIVATE_DATA prvFish[aGYO_TYPE_NUM]; // offset: 0x178 size: 0xFB48
    MUSEUM_FISH_KUSA_DATA prvKusa[14];               // offset: 0xFCB8 size: 0x4AD0
    mfish_hasu_c _14788;                           // offset: 0x14788 size: 0x570

    u8 _14cf8[16]; // temp

    xyz_t lightPosition[2];
    int numFishDisplayed;                         // offset: 0x14d20, size: 4
    int fishDisplayMsgIter;                       // offset: 0x14d24, size: 4
    FISH_DISPLAY_MSG_INFO fishDisplayMsgInfo[10]; // offset: 0x14d28, size: 4*10

    s16 _14d50[20];
    s16 _14d78[20];
    artificial_padding(0x14d78, 0x14daa, s16[20]);

    s16 _14daa[5];
    s16 player_area;
    s16 player_area_update_timer;        // offset: 0x14db6, size: 2
    s16 lightID1;      // offset: 0x14db8, size: 2
    s16 lightID2;      // offset: 0x14dba, size: 2
    s16 lightPower[2]; // offset: 0x14dbc, size: 4
    s16 _14dc0;        // offset: 0x14dc0, size: 2
    s16 _14dc2;        // offset: 0x14dc2, size: 2
    s16 _14dc4;        // offset: 0x14dc4, size: 2
    s16 _14dc8;        // offset: 0x14dc8, size: 2
    f32 logic_accum;    // offset: 0x14dcc, size: 4
} MUSEUM_FISH_ACTOR;   // size 14DD0

//  data
extern ACTOR_PROFILE Museum_Fish_Profile;
// technically static, but this helps with vscode includes
#ifdef TARGET_PC
static xyz_t suisou_pos[5];
#else
extern xyz_t suisou_pos[5];
#endif
extern int kusa_group_tbl[14];
extern xyz_t kusa_pos[14];
extern xyz_t hasu_pos;
extern xyz_t suisou_awa_pos[20];
extern s16 suisou_awa_group[20];
extern cKF_Skeleton_R_c* mfish_model_tbl[aGYO_TYPE_NUM];
extern cKF_Animation_R_c* mfish_anime_init_tbl[aGYO_TYPE_NUM];
extern MUSEUM_FISH_INIT_DATA mfish_init_data[aGYO_TYPE_NUM];
extern s16 mfish_group_tbl[aGYO_TYPE_NUM];
extern PRIV_FISH_CONSTRUCTOR mfish_ct[aGYO_TYPE_NUM];
extern PRIV_FISH_MOVE mfish_mv[aGYO_TYPE_NUM];
extern PRIV_FISH_DRAW mfish_dw[aGYO_TYPE_NUM];
extern float kusa_start_frame[14];

// functions

// ac_museum_fish.c_inc
void Museum_Fish_Prv_data_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game, int fishNum, int r6);
void Museum_Fish_Actor_ct(ACTOR* actor, GAME* game);
void Museum_Fish_Actor_dt(ACTOR* actor, GAME* game);
// int Museum_Fish_GetMsgNo(ACTOR* actor);
BOOL Museum_Fish_Check_Talk_Distance(GAME* gamex, int index);
// void Museum_Fish_Set_MsgFishInfo(ACTOR* actor, int param2);
void Museum_Fish_set_talk_info(ACTOR* actor);
// void Museum_Fish_Talk_process(ACTOR* actor, GAME* game);
void Museum_Fish_Actor_move(ACTOR* actor, GAME* game);
void Museum_Fish_Suisou_draw(ACTOR* actor, GAME* game, int r5);
BOOL kusa_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape, u8* joint_flags,
                      void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
void Museum_Fish_Kusa_Draw(ACTOR* actor, GAME* game, int r5);
void Museum_Fish_Actor_draw(ACTOR* actor, GAME* game);
BOOL mfish_cull_check(GAME* game, xyz_t* worldPos, f32 x, f32 y, f32 _y);
void mfish_point_ligh_pos_get(ACTOR* actorx, GAME* game, int r5);
void mfish_point_light_ct(ACTOR* actor, GAME* game);
void mfish_point_light_dt(ACTOR* r30, GAME* r31);
void mfish_point_light_mv(MUSEUM_FISH_ACTOR* actor, GAME* game);
void mfish_normal_light_set(ACTOR* actor, GAME* game);

// ac_museum_fish_base.c_inc
f32 Rnd_EX_f(f32 v1);
f32 Rnd_EX_fx(f32 v1);
void mfish_base_FishMove(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
int mfish_PosWallCheck(MUSEUM_FISH_PRIVATE_DATA* priv, xyz_t* pos);
BOOL mfish_WallCheck(MUSEUM_FISH_PRIVATE_DATA* priv);
s16 mfish_get_hide_camera_angle(MUSEUM_FISH_PRIVATE_DATA* priv);
void mfish_dummy_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_dummy_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_normal_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_normal_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_turn_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_turn_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_peck_process_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_peck_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_ground_peck_process_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_ground_peck_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_base_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_onefish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_onefish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape, u8* joint_flags,
                       void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
void mfish_onefish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_ani_base_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_ani_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_ani_base_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void Museum_Fish_BigFishObjCheck(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void Museum_Fish_ObjBGCheck(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex, f32 f1, f32 f2);
void Museum_Fish_DonkoBGCheck(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void Museum_Fish_objchk_pos_set(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void Museum_Fish_BGCheck(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void Museum_Fish_Kusa_Check(MUSEUM_FISH_ACTOR* actor, GAME* game);
void Museum_Fish_Object_Check(MUSEUM_FISH_ACTOR* actor, GAME* game);
void mfish_body_wind_anime_play(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_get_player_angle(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game, s16* atanx, s16* atany, f32* distance);
BOOL mfish_peck_check(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_peck_wall_check(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_ground_peck_before_check(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_get_player_area(MUSEUM_FISH_ACTOR* actor, GAME* game);
void mfish_get_flow_vec(xyz_t* pos, MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
s16 mfish_get_escape_angle(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_move_smooth(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_hamon_make(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_afish.c_inc
void mfish_afish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_afish_dummy_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_afish_dummy_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_afish_normal_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_afish_normal_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_afish_turn_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_afish_turn_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_afish_base_FishMove(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_afish_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_afish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_afish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_aroana.c_inc
void mfish_aroana_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_aroana_dummy_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_aroana_dummy_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex);
void mfish_aroana_normal_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_aroana_normal_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_aroana_turn_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_aroana_turn_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_aroana_long_move_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_aroana_long_move_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_aroana_base_FishMove(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_aroana_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_aroana_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_aroana_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                              u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
void mfish_aroana_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_koi.c_inc
void mfish_koi_tail_anim_set(MUSEUM_FISH_PRIVATE_DATA* actor, s32 r4);
void mfish_koi_move_smooth(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_dummy_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_koi_dummy_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_normal_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_koi_normal_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_turn_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_koi_turn_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_peck_process_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_peck_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_long_move_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_koi_long_move_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_base_FishMove(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_koi_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                           u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
void mfish_koi_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_kaseki.c_inc
void mfish_kaseki_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kaseki_normal_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex);
void mfish_kaseki_normal(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex);
void mfish_kaseki_move_wall_smooth(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex);
void mfish_kaseki_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_kaseki_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                              u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
void mfish_kaseki_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_bass.c_inc
void mfish_bass_tail_anim_set(MUSEUM_FISH_PRIVATE_DATA* actor, s32 r4);
void mfish_bass_base_FishMove(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_bass_dummy_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_bass_dummy_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_bass_normal_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_bass_normal_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_bass_turn_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_bass_turn_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_bass_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_bass_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_bass_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_seafish.c_inc
void mfish_seafish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_seafish_normal_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_seafish_normal(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_seafish_turn_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_seafish_turn(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_seafish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_seafish_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                               u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
void mfish_seafish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_tai.c_inc
void mfish_tai_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_tai_normal_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_tai_normal(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_tai_turn_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_tai_turn(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_tai_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_tai_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                           u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
void mfish_tai_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_sfish.c_inc
void mfish_small_fish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_sfish_normal_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_sfish_normal(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_sfish_turn_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_sfish_turn(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_small_fish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_sfish_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                             u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
void mfish_small_fish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_gupi.c_inc
void mfish_gupi_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_gupi_normal_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_gupi_normal(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_gupi_turn_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_gupi_turn(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_gupi_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_gupi_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                            u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
void mfish_gupi_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_medaka.c_inc
void mfish_medaka_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_medaka_normal_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_medaka_normal(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_medaka_turn_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_medaka_turn(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_medaka_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_medaka_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                              u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
void mfish_medaka_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_kingyo.c_inc
void mfish_kingyo_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kingyo_normal_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kingyo_normal(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kingyo_turn_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kingyo_turn(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kingyo_peck_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kingyo_peck(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kingyo_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_kingyo_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                              u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
void mfish_kingyo_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_dojou.c_inc
void mfish_dojou_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_dojou_normal_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_dojou_normal(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_dojou_turn_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_dojou_turn(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_dojou_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_dojou_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                             u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
void mfish_dojou_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_donko.c_inc
void mfish_donko_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_donko_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_donko_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                             u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
void mfish_donko_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_big_fish.c_inc
void mfish_big_fish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_big_fish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_bfish_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                             u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
void mfish_big_fish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_ito.c_inc
void mfish_ito_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_ito_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_ito_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                           u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
void mfish_ito_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_unagi.c_inc
void mfish_unagi_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
s16 mfish_unagi_get_next_rail_type(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_unagi_aim_wind_angle_calc(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_unagi_rail_move_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_unagi_rail_move(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_unagi_normal_to_reverse_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_unagi_normal_to_reverse(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_unagi_rail_move_reverse_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_unagi_rail_move_reverse(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_unagi_reverse_to_normal_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_unagi_reverse_to_normal(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_unagi_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_unagi_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                             u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
void mfish_unagi_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_namazu.c_inc
void mfish_namazu_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_namazu_body_wind_anime_play(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_namazu_normal_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_namazu_normal_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_namazu_dummy_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_namazu_dummy_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_namazu_turn_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_namazu_turn_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_namazu_ground_sweep_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_namazu_ground_sweep_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_namazu_base_FishMove(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_namazu_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_namazu_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                              u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
void mfish_namazu_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_zarigani.c_inc
void mfish_zarigani_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_zarigani_normal_process_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_zarigani_normal_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_zarigani_wait_process_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_zarigani_wait_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_zarigani_stand_process_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_zarigani_stand_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_zarigani_jump_process_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_zarigani_jump_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_zarigani_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_zarigani_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
void mfish_zarigani_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_kurage.c_inc
void mfish_kurage_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kurage_normal_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kurage_normal(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kurage_turn_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kurage_turn(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kurage_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kurage_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

// ac_museum_fish_hasu.c_inc
void mfish_hasu_ct(mfish_hasu_c* actor, GAME* game);
void mfish_hasu_mv(mfish_hasu_c* actor, GAME* game);
void mfish_hasu_dw(mfish_hasu_c* actor, GAME* game);
void mfish_kaeru_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex);
void mfish_kaeru_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex);
BOOL hasu_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape, u8* joint_flags,
                      void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
BOOL hasu_after_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape, u8* joint_flags,
                     void* arg, s_xyz* joint_rot, xyz_t* joint_pos);
void mfish_kaeru_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex);

#ifdef __cplusplus
}
#endif

#endif // !AC_MUSEUM_FISH_PRIV_H
