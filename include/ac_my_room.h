#ifndef AC_MY_ROOM_H
#define AC_MY_ROOM_H

#include "types.h"
#include "m_actor.h"
#include "ac_furniture.h"
#include "m_room_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aMR_MAX_UNIT 8
#define aMR_HANIWA_ON_TABLE_NUM 14
#define aMR_GOKI_MAX 3
#define aMR_FIT_FTR_MAX 4
#define aMR_RSV_FTR_NUM 3

#define aMR_NO_FTR_ID 200
#define aMR_NO_FTR_ID2 201

#define aMR_JUDGE_MAX_FTR -1
#define aMR_JUDGE_CANT_PLACE_FTR -2
#define aMR_JUDGE_OTHER_ROOM -3

typedef struct my_room_actor_s MY_ROOM_ACTOR;

enum {
    aMR_CONTACT_LEFT,
    aMR_CONTACT_RIGHT,
    aMR_CONTACT_CENTER,

    aMR_CONTACT_NUM
};

enum {
    aMR_CONTACT_DIR_BACK,
    aMR_CONTACT_DIR_RIGHT,
    aMR_CONTACT_DIR_FRONT,
    aMR_CONTACT_DIR_LEFT,

    aMR_CONTACT_DIR_NUM
};

enum {
    aMR_FRIEND_ALL,
    aMR_FRIEND_ON,
    aMR_FRIEND_OFF,

    aMR_FRIEND_NUM
};

enum {
    aMR_DIRECT_UP,
    aMR_DIRECT_LEFT,
    aMR_DIRECT_DOWN,
    aMR_DIRECT_RIGHT,

    aMR_DIRECT_NUM
};

typedef struct my_room_contact_s {
    int contact_flag;
    int ftrID;
    int direction;
    int contact_side;
    f32 contact_percent;
    f32* normal_p;
    f32 contact_edge_start[2];
    f32 contact_edge_end[2];
    int contact_direction;
} aMR_contact_info_c;

typedef struct my_room_clock_info_s {
    int tick0;     /* set on frame 15 */
    int tick1;     /* set on frame 45 */
    int tick_stop; /* set on frame 0 */
    int frame;     /* 0-119 */
    f32 phase_frame;
} aMR_clock_info_c;

typedef int (*aMR_JUDGE_BREED_NEW_FTR_PROC)(GAME* game, u16 ftr_no, int* ut_x, int* ut_z, u16* rotation,
                                            int* square_offset, int* layer);
typedef mActor_name_t (*aMR_SEARCH_PICKUP_FURNITURE_PROC)(GAME* game);
typedef void (*aMR_FURNITURE2ITEMBAG_PROC)(GAME* game);
typedef int (*aMR_JUDGE_PLAYER_ACTION_PROC)(xyz_t* wpos0, xyz_t* wpos1, int ftr_actor_idx);
typedef void (*aMR_PLAYER_MOVE_FURNITURE_PROC)(int ftr_actor_idx, const xyz_t* wpos);
typedef int (*aMR_FTR_ID_2_WPOS_PROC)(xyz_t* wpos, int ftr_id);
typedef int (*aMR_UNIT_NUM_2_FTR_ITEMNO_FTRID_PROC)(mActor_name_t* ftr_item_no, int* ftr_id, int ut_x, int ut_z,
                                                    int layer);
typedef void (*aMR_FTR_ID_2_EXTINGUISH_FURNITURE_PROC)(int ftr_id);
typedef void (*aMR_REDMA_FTR_BANK_PROC)(void);
typedef int (*aMR_RESERVE_FURNITURE_PROC)(GAME* game, u16 ftr_no, int judge_res, int ut_x, int ut_z, u16 rotation,
                                          int square_offset, int layer);
typedef int (*aMR_COUNT_FRIEND_FURNITURE_PROC)(FTR_ACTOR* ftr_actor, u8 switch_on);
typedef int (*aMR_JUDGE_PLACE_2ND_LAYER_PROC)(int ut_x, int ut_z);
typedef void (*aMR_OPEN_CLOSE_COMMON_MOVE_PROC)(FTR_ACTOR* ftr_actor, ACTOR* actor, GAME* game, f32 start_frame,
                                                f32 end_frame);
typedef int (*aMR_GET_BED_ACTION_PROC)(ACTOR* actorx, int bed_move_dir);
typedef void (*aMR_MINI_DISK_COMMON_MOVE_PROC)(FTR_ACTOR* ftr_actor, ACTOR* my_room_actorx, GAME* game, f32 start_frame,
                                               f32 end_frame);
typedef int (*aMR_SET_LEAF_PROC)(const xyz_t* pos, f32 scale);
typedef int (*aMR_FTR2LEAF_PROC)(void);
typedef void (*aMR_LEAF_START_POS_PROC)(xyz_t* pos);
typedef int (*aMR_PICKUP_FTR_LAYER_PROC)(void);
typedef void (*aMR_LEAF_PICKUPED_PROC)(void);
typedef void (*aMR_FAMICOM_EMU_COMMON_MOVE_PROC)(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, int rom_no,
                                                 int agb_rom_no);
typedef u8* (*aMR_FTR_NO_2_BANK_ADDRESS_PROC)(u16 ftr_no);
typedef void (*aMR_CALL_SIT_DOWN_ONGEN_POS_SE_PROC)(const xyz_t* pos);
typedef void (*aMR_SOUND_MELODY_PROC)(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, int idx);
typedef int (*aMR_CHECK_DANNA_KILL_PROC)(xyz_t* pos);

typedef struct my_room_clip_s {
    ACTOR* my_room_actor_p;
    aMR_JUDGE_BREED_NEW_FTR_PROC judge_breed_new_ftr_proc;
    aMR_SEARCH_PICKUP_FURNITURE_PROC search_pickup_ftr_proc;
    aMR_FURNITURE2ITEMBAG_PROC ftr2itemBag_proc;
    aMR_JUDGE_PLAYER_ACTION_PROC judge_player_action_proc;
    aMR_PLAYER_MOVE_FURNITURE_PROC player_move_ftr_proc;
    aMR_FTR_ID_2_WPOS_PROC ftrId2wpos_proc;
    aMR_UNIT_NUM_2_FTR_ITEMNO_FTRID_PROC unitNum2ftrItemNoftrId_proc;
    aMR_FTR_ID_2_EXTINGUISH_FURNITURE_PROC ftrId2extinguishFtr_proc;
    aMR_REDMA_FTR_BANK_PROC redma_ftr_bank_proc;
    aMR_RESERVE_FURNITURE_PROC reserve_ftr_proc;
    aMR_COUNT_FRIEND_FURNITURE_PROC count_friend_ftr_proc;
    aMR_JUDGE_PLACE_2ND_LAYER_PROC judge_place_2nd_layer_proc;
    aMR_OPEN_CLOSE_COMMON_MOVE_PROC open_close_common_move_proc;
    aMR_GET_BED_ACTION_PROC get_bed_action_proc;
    aMR_MINI_DISK_COMMON_MOVE_PROC mini_disk_common_move_proc;
    aMR_SET_LEAF_PROC set_leaf_proc;
    aMR_FTR2LEAF_PROC ftr2leaf_proc;
    aMR_LEAF_START_POS_PROC leaf_start_pos_proc;
    aMR_PICKUP_FTR_LAYER_PROC pickup_ftr_layer_proc;
    aMR_LEAF_PICKUPED_PROC leaf_pickuped_proc;
    aMR_FAMICOM_EMU_COMMON_MOVE_PROC famicom_emu_common_move_proc;
    aMR_FTR_NO_2_BANK_ADDRESS_PROC ftrNo2bankAddress_proc;
    aMR_CALL_SIT_DOWN_ONGEN_POS_SE_PROC call_sit_down_ongen_pos_se_proc;
    aMR_clock_info_c* clock_info_p; /* used for playing the clock tick? sfx */
    aMR_SOUND_MELODY_PROC sound_melody_proc;
    aMR_CHECK_DANNA_KILL_PROC check_danna_kill_proc;
} aMR_Clip_c;

typedef struct room_leaf_s {
    int exist_flag;
    xyz_t pos;
    f32 scale;
} aMR_leaf_info_c;

typedef struct room_pickup_s {
    int pickup_flag;
    int ftrID;
    xyz_t leaf_pos;
    int picking_up_flag;
    s16 layer;
    s16 dust_effect_timer;
    s16 icon;
} aMR_pickup_info_c;

typedef struct room_rsv_ftr_s {
    u8 exist_flag;
    u16 ftr_name;
    int ofs;
    u16 angle_idx;
    int free_no;
    s16 layer;
    s16 frames;
    s16 initial_frames_num;
#ifdef TARGET_PC
    f32 frame_accum;
#endif
    int ut_x;
    int ut_z;
} aMR_rsv_ftr_c;

typedef struct room_bgm_s {
    int md_no;
    int last_md_no;
    u8 reserve_flag;
    s16 timer;
    FTR_ACTOR* reserved_ftr_actor;
    FTR_ACTOR* active_ftr_actor;
    int active_flag;
} aMR_bgm_info_c;

typedef struct room_info_s {
    int shop_flag;
    int owner_flag;
} aMR_room_info_c;

typedef struct emu_info_s {
    int request_flag;
    int rom_no;
    int agb_rom_no;
    int explaination_given_flag;
    int _10;
    int card_famicom_count;
    int memory_game_select;
    char* famicom_names_p;
    s16 save_msg_timer;
    s16 external_rom;
#ifdef TARGET_PC
    f32 save_msg_timer_accum;
#endif
} aMR_emu_info_c;

typedef void (*aMR_GOKI_CT_PROC)(ACTOR*, GAME*);

typedef struct room_fit_ftr_s {
    int exist_flag;
    xyz_t pos;
    int ftr_ID;
    mActor_name_t item_no;
    s16 angle_y;
    xyz_t ut_pos;
} aMR_fit_ftr_c;

typedef struct room_parent_ftr_s {
    int ftrID;
    s16 angle_y;
    aMR_fit_ftr_c fit_ftr_table[aMR_FIT_FTR_MAX];
} aMR_parent_ftr_c;

struct my_room_actor_s {
    ACTOR actor_class;
    s16 state;
    aMR_contact_info_c contact0;
    aMR_contact_info_c contact1;
    u8 allow_rotation_flag;
    int _1D4;
    cKF_SkeletonInfo_R_c keyframe;
    s_xyz joint[1];
    s_xyz morph[1];
    u8 _254[132];
    s16 move_angle;
    xyz_t nice_pos;
    aMR_Clip_c clip;
    f32 sit_timer;
    f32 bed_timer;
    aMR_leaf_info_c leaf_info;
    aMR_pickup_info_c pickup_info;
    aMR_rsv_ftr_c rsv_ftr[3];
    s16 msg_type;
    s16 requested_msg_type;
    int emu_ftrID;
    int _3F4;
    s16 demo_flag;
    s16 demo_ftrID;
    f32 switch_timer_accum;
    s16 pull_timer;
    s16 push_timer;
    s16 msg_timer;
    s16 head_direction;
    s16 bed_ftr_actor_idx;
    s16 pull_bubu;
    s16 push_bubu;
    s16 keep_push_flag;
    s16 keep_pull_flag;
    xyz_t pull_target_pos0;
    xyz_t pull_target_pos1;
    int haniwa_on_table[aMR_HANIWA_ON_TABLE_NUM];
    aMR_bgm_info_c bgm_info;
    aMR_room_info_c room_info;
    aMR_emu_info_c emu_info;
    aMR_clock_info_c clock_info;
    aMR_GOKI_CT_PROC goki_ct_proc;
    int _4BC[3];
    int weight;
    u8 melody[8];
    int _4D4;
    int _4D8;
    int bank_count0;
    int bank_count1;
    int request_player_surprise;
    s16 player_surprise_angle_y;
    s16 switch_timer;
    s16 force_open_demo_flag;
    f32 pull_timer_accum;
    f32 push_timer_accum;
#ifdef TARGET_PC
    f32 tex_animation_accum;
#endif
    int room_msg_flag;
    int haniwa_step_idx;
    aMR_parent_ftr_c parent_ftr;
    u32 music_box[2];
    int scene;
    int _5A4;
    int throw_item_lock_flag;
    void* bank0_p;
    u32 agb_game_size;
    void* famicom_agb_image_p;
    s16 agb_connect_tries;
    int _5BC;
};

extern ACTOR_PROFILE My_Room_Profile;

extern int aMR_CorrespondFurniture(mActor_name_t ftr0, mActor_name_t ftr1);
extern int aMR_GetFurnitureUnit(mActor_name_t ftr);
extern mActor_name_t aMR_FurnitureFg_to_FurnitureFgWithDirect(mActor_name_t ftr, int direct);
extern void aMR_SameFurnitureSwitchOFF(u16 ftr_name);
extern aMR_contact_info_c* aMR_GetContactInfoLayer1(void);
extern FTR_ACTOR* aMR_GetParentFactor(FTR_ACTOR* ftr_actor, ACTOR* my_room_actorx);
extern s16 aMR_GetParentAngleOffset(FTR_ACTOR* ftr_actor, ACTOR* my_room_actorx);
extern void aMR_SetSurprise(ACTOR* my_room_actor, s16 rot);
extern void aMR_RadioCommonMove(FTR_ACTOR* ftr_actor, ACTOR* my_room_actorx);
extern void aMR_SaveWaltzTempo2(void);
extern u8 aMR_GetAlphaEdge(u16 ftr_name);
extern int aMR_DrawDolphinMode(u16 ftr_name);
extern Gfx* aMR_IconNo2Gfx1(int icon_no);
extern Gfx* aMR_IconNo2Gfx2(int icon_no);
extern int aMR_RadioBgmNow(void);
extern void aMR_ThrowItem_FurnitureLock(void);
extern void aMR_ThrowItem_FurnitureUnlock(void);

#ifdef __cplusplus
}
#endif

#endif
