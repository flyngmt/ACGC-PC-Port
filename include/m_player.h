#ifndef M_PLAYER_H
#define M_PLAYER_H

#include "types.h"
#include "m_actor.h"
#include "m_lib.h"
#include "c_keyframe.h"
#include "libultra/ultratypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mPlayer_DEBT0 17400  /* Buy house */
#define mPlayer_DEBT1 148000 /* 1st upgrade main floor */
#define mPlayer_DEBT2 398000 /* 2nd upgrade main floor */
#define mPlayer_DEBT3 49800  /* Basement */
#define mPlayer_DEBT4 798000 /* Upper floor */

/* These are in frames */
#define mPlayer_SUNBURN_TIME_VILLAGE (15 * mTM_SECONDS_IN_MINUTE * FRAMES_PER_SECOND)
#define mPlayer_SUNBURN_TIME_ISLAND (5 * mTM_SECONDS_IN_MINUTE * FRAMES_PER_SECOND)

#define mPlayer_SUNBURN_MAX_RANK 8

#define mPlayer_RADIO_EXERCISE_COMMAND_RING_BUFFER_SIZE 8

typedef struct player_actor_s PLAYER_ACTOR;

#define mPlayer_FORCE_POSITION_ANGLE_NONE 0
// where is (1 << 0) ??
#define mPlayer_FORCE_POSITION_ANGLE_POSX (1 << 1)
#define mPlayer_FORCE_POSITION_ANGLE_POSY (1 << 2)
#define mPlayer_FORCE_POSITION_ANGLE_POSZ (1 << 3)
#define mPlayer_FORCE_POSITION_ANGLE_ROTX (1 << 4)
#define mPlayer_FORCE_POSITION_ANGLE_ROTY (1 << 5)
#define mPlayer_FORCE_POSITION_ANGLE_ROTZ (1 << 6)

#define mPlayer_WALK_FLAG_SET_POS (1 << 1)
#define mPlayer_WALK_FLAG_RESET_MORPH (1 << 2)

#define mPlayer_NET_CATCH_TABLE_COUNT 8

enum {
    mPlayer_JOINT_ROOT,
    mPlayer_JOINT_BASE,
    mPlayer_JOINT_LFOOT_BASE,
    mPlayer_JOINT_LFOOT1,
    mPlayer_JOINT_LFOOT2,
    mPlayer_JOINT_LFOOT3,
    mPlayer_JOINT_RFOOT_BASE,
    mPlayer_JOINT_RFOOT1,
    mPlayer_JOINT_RFOOT2,
    mPlayer_JOINT_RFOOT3,
    mPlayer_JOINT_TAIL_BASE,
    mPlayer_JOINT_TAIL1,
    mPlayer_JOINT_TAIL2,
    mPlayer_JOINT_CHEST,
    mPlayer_JOINT_LARM_BASE,
    mPlayer_JOINT_LARM1,
    mPlayer_JOINT_LARM2,
    mPlayer_JOINT_RARM_BASE,
    mPlayer_JOINT_RARM1,
    mPlayer_JOINT_RARM2,
    mPlayer_JOINT_HAND,
    mPlayer_JOINT_HEAD_BASE,
    mPlayer_JOINT_MOUTH_BASE,
    mPlayer_JOINT_MOUTH,
    mPlayer_JOINT_HEAD,
    mPlayer_JOINT_FEEL,

    mPlayer_JOINT_NUM
};

enum {
    mPlayer_ADDRESSABLE_TRUE,
    mPlayer_ADDRESSABLE_FALSE_MOVEMENT,
    mPlayer_ADDRESSABLE_FALSE_TALKING,
    mPlayer_ADDRESSABLE_FALSE_READY_NET,

    mPlayer_ADDRESSABLE_NUM
};

enum {
    mPlayer_COMPLETE_PAYMENT_TYPE_NONE,
    mPlayer_COMPLETE_PAYMENT_TYPE_ARBEIT,
    mPlayer_COMPLETE_PAYMENT_TYPE_HOUSE,

    mPlayer_COMPLETE_PAYMENT_TYPE_NUM
};

enum {
    mPlayer_BGM_VOLUME_MODE_NORMAL,
    mPlayer_BGM_VOLUME_MODE_COLLECT_INSECTS,
    mPlayer_BGM_VOLUME_MODE_FISHING,

    mPlayer_BGM_VOLUME_MODE_NUM
};

enum {
    mPlayer_INDEX_DMA,
    mPlayer_INDEX_INTRO,
    mPlayer_INDEX_REFUSE,
    mPlayer_INDEX_REFUSE_PICKUP,
    mPlayer_INDEX_RETURN_DEMO,
    mPlayer_INDEX_RETURN_OUTDOOR,
    mPlayer_INDEX_RETURN_OUTDOOR2,
    mPlayer_INDEX_WAIT,
    mPlayer_INDEX_WALK,
    mPlayer_INDEX_RUN,
    mPlayer_INDEX_DASH,
    mPlayer_INDEX_TUMBLE,
    mPlayer_INDEX_TUMBLE_GETUP,
    mPlayer_INDEX_TURN_DASH,
    mPlayer_INDEX_FALL,
    mPlayer_INDEX_WADE,
    mPlayer_INDEX_DOOR,
    mPlayer_INDEX_OUTDOOR,
    mPlayer_INDEX_INVADE,
    mPlayer_INDEX_HOLD,
    mPlayer_INDEX_PUSH,
    mPlayer_INDEX_PULL,
    mPlayer_INDEX_ROTATE_FURNITURE,
    mPlayer_INDEX_OPEN_FURNITURE,
    mPlayer_INDEX_WAIT_OPEN_FURNITURE,
    mPlayer_INDEX_CLOSE_FURNITURE,
    mPlayer_INDEX_LIE_BED,
    mPlayer_INDEX_WAIT_BED,
    mPlayer_INDEX_ROLL_BED,
    mPlayer_INDEX_STANDUP_BED,
    mPlayer_INDEX_PICKUP,
    mPlayer_INDEX_PICKUP_JUMP,
    mPlayer_INDEX_PICKUP_FURNITURE,
    mPlayer_INDEX_PICKUP_EXCHANGE,
    mPlayer_INDEX_SITDOWN,
    mPlayer_INDEX_SITDOWN_WAIT,
    mPlayer_INDEX_STANDUP,
    mPlayer_INDEX_SWING_AXE,
    mPlayer_INDEX_AIR_AXE,
    mPlayer_INDEX_REFLECT_AXE,
    mPlayer_INDEX_BROKEN_AXE,
    mPlayer_INDEX_SLIP_NET,
    mPlayer_INDEX_READY_NET,
    mPlayer_INDEX_READY_WALK_NET,
    mPlayer_INDEX_SWING_NET,
    mPlayer_INDEX_PULL_NET,
    mPlayer_INDEX_STOP_NET,
    mPlayer_INDEX_NOTICE_NET,
    mPlayer_INDEX_PUTAWAY_NET,
    mPlayer_INDEX_READY_ROD,
    mPlayer_INDEX_CAST_ROD,
    mPlayer_INDEX_AIR_ROD,
    mPlayer_INDEX_RELAX_ROD,
    mPlayer_INDEX_COLLECT_ROD,
    mPlayer_INDEX_VIB_ROD,
    mPlayer_INDEX_FLY_ROD,
    mPlayer_INDEX_NOTICE_ROD,
    mPlayer_INDEX_PUTAWAY_ROD,
    mPlayer_INDEX_DIG_SCOOP,
    mPlayer_INDEX_FILL_SCOOP,
    mPlayer_INDEX_REFLECT_SCOOP,
    mPlayer_INDEX_AIR_SCOOP,
    mPlayer_INDEX_GET_SCOOP,
    mPlayer_INDEX_PUTAWAY_SCOOP,
    mPlayer_INDEX_PUTIN_SCOOP,
    mPlayer_INDEX_TALK,
    mPlayer_INDEX_RECIEVE_WAIT,
    mPlayer_INDEX_RECIEVE_STRETCH,
    mPlayer_INDEX_RECIEVE,
    mPlayer_INDEX_RECIEVE_PUTAWAY,
    mPlayer_INDEX_GIVE,
    mPlayer_INDEX_GIVE_WAIT,
    mPlayer_INDEX_TAKEOUT_ITEM,
    mPlayer_INDEX_PUTIN_ITEM,
    mPlayer_INDEX_DEMO_WAIT,
    mPlayer_INDEX_DEMO_WALK,
    mPlayer_INDEX_DEMO_GETON_TRAIN,
    mPlayer_INDEX_DEMO_GETON_TRAIN_WAIT,
    mPlayer_INDEX_DEMO_GETOFF_TRAIN,
    mPlayer_INDEX_DEMO_STANDING_TRAIN,
    mPlayer_INDEX_DEMO_WADE,
    mPlayer_INDEX_HIDE,
    mPlayer_INDEX_GROUNDHOG,
    mPlayer_INDEX_RELEASE_CREATURE,
    mPlayer_INDEX_WASH_CAR,
    mPlayer_INDEX_TIRED,
    mPlayer_INDEX_ROTATE_OCTAGON,
    mPlayer_INDEX_THROW_MONEY,
    mPlayer_INDEX_PRAY,
    mPlayer_INDEX_SHAKE_TREE,
    mPlayer_INDEX_MAIL_JUMP,
    mPlayer_INDEX_MAIL_LAND,
    mPlayer_INDEX_READY_PITFALL,
    mPlayer_INDEX_FALL_PITFALL,
    mPlayer_INDEX_STRUGGLE_PITFALL,
    mPlayer_INDEX_CLIMBUP_PITFALL,
    mPlayer_INDEX_STUNG_BEE,
    mPlayer_INDEX_NOTICE_BEE,
    mPlayer_INDEX_REMOVE_GRASS,
    mPlayer_INDEX_SHOCK,
    mPlayer_INDEX_KNOCK_DOOR,
    mPlayer_INDEX_CHANGE_CLOTH,
    mPlayer_INDEX_PUSH_SNOWBALL,
    mPlayer_INDEX_ROTATE_UMBRELLA,
    mPlayer_INDEX_WADE_SNOWBALL,
    mPlayer_INDEX_COMPLETE_PAYMENT,
    mPlayer_INDEX_FAIL_EMU,
    mPlayer_INDEX_STUNG_MOSQUITO,
    mPlayer_INDEX_NOTICE_MOSQUITO,
    mPlayer_INDEX_SWING_FAN,
    mPlayer_INDEX_SWITCH_ON_LIGHTHOUSE,
    mPlayer_INDEX_RADIO_EXERCISE,
    mPlayer_INDEX_DEMO_GETON_BOAT,
    mPlayer_INDEX_DEMO_GETON_BOAT_SITDOWN,
    mPlayer_INDEX_DEMO_GETON_BOAT_WAIT,
    mPlayer_INDEX_DEMO_GETON_BOAT_WADE,
    mPlayer_INDEX_DEMO_GETOFF_BOAT_STANDUP,
    mPlayer_INDEX_DEMO_GETOFF_BOAT,
    mPlayer_INDEX_DEMO_GET_GOLDEN_ITEM,
    mPlayer_INDEX_DEMO_GET_GOLDEN_ITEM2,
    mPlayer_INDEX_DEMO_GET_GOLDEN_AXE_WAIT,

    mPlayer_INDEX_NUM
};

#define mPlayer_MAIN_INDEX_VALID(idx) ((idx) >= 0 && (idx) < mPlayer_INDEX_NUM)

enum {
    mPlayer_REQUEST_PRIORITY_0,
    mPlayer_REQUEST_PRIORITY_1,
    mPlayer_REQUEST_PRIORITY_2,
    mPlayer_REQUEST_PRIORITY_3,
    mPlayer_REQUEST_PRIORITY_4,
    mPlayer_REQUEST_PRIORITY_5,
    mPlayer_REQUEST_PRIORITY_6,
    mPlayer_REQUEST_PRIORITY_7,
    mPlayer_REQUEST_PRIORITY_8,
    mPlayer_REQUEST_PRIORITY_9,
    mPlayer_REQUEST_PRIORITY_10,
    mPlayer_REQUEST_PRIORITY_11,
    mPlayer_REQUEST_PRIORITY_12,
    mPlayer_REQUEST_PRIORITY_13,
    mPlayer_REQUEST_PRIORITY_14,
    mPlayer_REQUEST_PRIORITY_15,
    mPlayer_REQUEST_PRIORITY_16,
    mPlayer_REQUEST_PRIORITY_17,
    mPlayer_REQUEST_PRIORITY_18,
    mPlayer_REQUEST_PRIORITY_19,
    mPlayer_REQUEST_PRIORITY_20,
    mPlayer_REQUEST_PRIORITY_21,
    mPlayer_REQUEST_PRIORITY_22,
    mPlayer_REQUEST_PRIORITY_23,
    mPlayer_REQUEST_PRIORITY_24,
    mPlayer_REQUEST_PRIORITY_25,
    mPlayer_REQUEST_PRIORITY_26,
    mPlayer_REQUEST_PRIORITY_27,
    mPlayer_REQUEST_PRIORITY_28,
    mPlayer_REQUEST_PRIORITY_29,
    mPlayer_REQUEST_PRIORITY_30,
    mPlayer_REQUEST_PRIORITY_31,
    mPlayer_REQUEST_PRIORITY_32,
    mPlayer_REQUEST_PRIORITY_33,
    mPlayer_REQUEST_PRIORITY_34,
    mPlayer_REQUEST_PRIORITY_35,
    mPlayer_REQUEST_PRIORITY_36,
    mPlayer_REQUEST_PRIORITY_37,
    mPlayer_REQUEST_PRIORITY_38,
    mPlayer_REQUEST_PRIORITY_39,
    mPlayer_REQUEST_PRIORITY_40,
    mPlayer_REQUEST_PRIORITY_41,
    mPlayer_REQUEST_PRIORITY_42,
    mPlayer_REQUEST_PRIORITY_43,
    mPlayer_REQUEST_PRIORITY_44,
    mPlayer_REQUEST_PRIORITY_45,

    mPlayer_REQUEST_PRIORITY_NUM
};

#define mPlayer_REQUEST_PRIORITY_NONE -1

#define mPlayer_REQUEST_PRIORITY_VALID(prio) ((prio) >= 0 && (prio) <= mPlayer_REQUEST_PRIORITY_45)

enum {
    mPlayer_ANIM_WAIT1,
    mPlayer_ANIM_WALK1,
    mPlayer_ANIM_AXE1,
    mPlayer_ANIM_RUN1,
    mPlayer_ANIM_PUSH1,
    mPlayer_ANIM_PULL1,
    mPlayer_ANIM_HOLD_WAIT1,
    mPlayer_ANIM_PICKUP1,
    mPlayer_ANIM_LTURN1,
    mPlayer_ANIM_RTURN1,
    mPlayer_ANIM_GET1,
    mPlayer_ANIM_GET_CHANGE1,
    mPlayer_ANIM_GET_PUTAWAY1,
    mPlayer_ANIM_OPEN1,
    mPlayer_ANIM_PUTAWAY1,
    mPlayer_ANIM_TRANS_WAIT1,
    mPlayer_ANIM_TRANSFER1,
    mPlayer_ANIM_UMB_OPEN1,
    mPlayer_ANIM_UMBRELLA1,
    mPlayer_ANIM_DASH1,
    mPlayer_ANIM_RUN_SLIP1,
    mPlayer_ANIM_GET_PULL1,
    mPlayer_ANIM_GET_M1,
    mPlayer_ANIM_KAMAE_MOVE_M1,
    mPlayer_ANIM_KAMAE_WAIT_M1,
    mPlayer_ANIM_KOKERU_A1,
    mPlayer_ANIM_KOKERU_GETUP_A1,
    mPlayer_ANIM_KOKERU_GETUP_N1,
    mPlayer_ANIM_KOKERU_N1,
    mPlayer_ANIM_NET1,
    mPlayer_ANIM_NET_SWING1,
    mPlayer_ANIM_AXE_SWING1,
    mPlayer_ANIM_KAMAE_SLIP_M1,
    mPlayer_ANIM_KOKERU1,
    mPlayer_ANIM_KOKERU_GETUP1,
    mPlayer_ANIM_SITDOWN1,
    mPlayer_ANIM_SITDOWN_WAIT1,
    mPlayer_ANIM_STANDUP1,
    mPlayer_ANIM_PUTAWAY_M1,
    mPlayer_ANIM_BED_WAIT1,
    mPlayer_ANIM_INBED_L1,
    mPlayer_ANIM_INBED_R1,
    mPlayer_ANIM_INTRAIN1,
    mPlayer_ANIM_KAGU_OPEN_D1,
    mPlayer_ANIM_KAGU_OPEN_H1,
    mPlayer_ANIM_KAGU_OPEN_K1,
    mPlayer_ANIM_NEGAERI_L1,
    mPlayer_ANIM_NEGAERI_R1,
    mPlayer_ANIM_OUTBED_L1,
    mPlayer_ANIM_OUTBED_R1,
    mPlayer_ANIM_OUTTRAIN1,
    mPlayer_ANIM_KAGU_CLOSE_D1,
    mPlayer_ANIM_KAGU_CLOSE_H1,
    mPlayer_ANIM_KAGU_CLOSE_K1,
    mPlayer_ANIM_KAGU_WAIT_D1,
    mPlayer_ANIM_KAGU_WAIT_H1,
    mPlayer_ANIM_KAGU_WAIT_K1,
    mPlayer_ANIM_GO_OUT_O1,
    mPlayer_ANIM_GO_OUT_S1,
    mPlayer_ANIM_INTO_S1,
    mPlayer_ANIM_AXE_HANE1,
    mPlayer_ANIM_AXE_SUKA1,
    mPlayer_ANIM_HOLD_WAIT_H1,
    mPlayer_ANIM_HOLD_WAIT_O1,
    mPlayer_ANIM_GET_T1,
    mPlayer_ANIM_GET_T2,
    mPlayer_ANIM_PUTAWAY_T1,
    mPlayer_ANIM_SAO1,
    mPlayer_ANIM_SAO_SWING1,
    mPlayer_ANIM_TURI_HIKI1,
    mPlayer_ANIM_TURI_WAIT1,
    mPlayer_ANIM_NOT_GET_T1,
    mPlayer_ANIM_MENU_CATCH1,
    mPlayer_ANIM_MENU_CHANGE1,
    mPlayer_ANIM_UMB_CLOSE1,
    mPlayer_ANIM_NOT_SAO_SWING1,
    mPlayer_ANIM_INTRAIN_WAIT1,
    mPlayer_ANIM_CLEAR_TABLE1,
    mPlayer_ANIM_DIG1,
    mPlayer_ANIM_FILL_UP1,
    mPlayer_ANIM_NOT_DIG1,
    mPlayer_ANIM_CLEAR_TABLE_L1,
    mPlayer_ANIM_PICKUP_L1,
    mPlayer_ANIM_SCOOP1,
    mPlayer_ANIM_CONFIRM1,
    mPlayer_ANIM_DIG_SUKA1,
    mPlayer_ANIM_GET_D1,
    mPlayer_ANIM_PUTAWAY_D1,
    mPlayer_ANIM_DIG_KABU1,
    mPlayer_ANIM_FILL_UP_I1,
    mPlayer_ANIM_SEND_MAIL1,
    mPlayer_ANIM_GET_F1,
    mPlayer_ANIM_GET_PULL_F1,
    mPlayer_ANIM_GET_PUTAWAY_F1,
    mPlayer_ANIM_TRANS_WAIT_F1,
    mPlayer_ANIM_TRANSFER_F1,
    mPlayer_ANIM_SHAKE1,
    mPlayer_ANIM_TIRED1,
    mPlayer_ANIM_WASH1,
    mPlayer_ANIM_WASH2,
    mPlayer_ANIM_WASH3,
    mPlayer_ANIM_WASH4,
    mPlayer_ANIM_WASH5,
    mPlayer_ANIM_FUKUBIKI1,
    mPlayer_ANIM_OMAIRI1,
    mPlayer_ANIM_SAISEN1,
    mPlayer_ANIM_RETURN_MAIL1,
    mPlayer_ANIM_RETURN_MAIL2,
    mPlayer_ANIM_RETURN_MAIL3,
    mPlayer_ANIM_EAT1,
    mPlayer_ANIM_GAAAN1,
    mPlayer_ANIM_GAAAN2,
    mPlayer_ANIM_DERU1,
    mPlayer_ANIM_GURATUKU1,
    mPlayer_ANIM_MOGAKU1,
    mPlayer_ANIM_OTIRU1,
    mPlayer_ANIM_ZASSOU1,
    mPlayer_ANIM_KNOCK1,
    mPlayer_ANIM_BIKU1,
    mPlayer_ANIM_HATI1,
    mPlayer_ANIM_HATI2,
    mPlayer_ANIM_HATI3,
    mPlayer_ANIM_PUSH_YUKI1,
    mPlayer_ANIM_DERU2,
    mPlayer_ANIM_OTIRU2,
    mPlayer_ANIM_ITAZURA1,
    mPlayer_ANIM_UMB_ROT1,
    mPlayer_ANIM_PICKUP_WAIT1,
    mPlayer_ANIM_YATTA1,
    mPlayer_ANIM_YATTA2,
    mPlayer_ANIM_YATTA3,
    mPlayer_ANIM_KAZA1,
    mPlayer_ANIM_MOSQUITO1,
    mPlayer_ANIM_MOSQUITO2,
    mPlayer_ANIM_RIDE1,
    mPlayer_ANIM_RIDE2,
    mPlayer_ANIM_RIDEWAIT,
    mPlayer_ANIM_GETOFF1,
    mPlayer_ANIM_GETOFF2,
    mPlayer_ANIM_UTIWA_WAIT1,
    mPlayer_ANIM_UTIWA_D1,
    mPlayer_ANIM_AXE_BREAK1,
    mPlayer_ANIM_AXE_BREAKWAIT1,
    mPlayer_ANIM_LIGHT_ON1,
    mPlayer_ANIM_TAISOU1,
    mPlayer_ANIM_TAISOU2_1,
    mPlayer_ANIM_TAISOU2_2,
    mPlayer_ANIM_TAISOU3,
    mPlayer_ANIM_TAISOU4_1,
    mPlayer_ANIM_TAISOU4_2,
    mPlayer_ANIM_TAISOU5_1,
    mPlayer_ANIM_TAISOU5_2,
    mPlayer_ANIM_TAISOU6_1,
    mPlayer_ANIM_TAISOU6_2,
    mPlayer_ANIM_TAISOU7_1,
    mPlayer_ANIM_TAISOU7_2,
    mPlayer_ANIM_OMAIRI_US1,

    mPlayer_ANIM_NUM
};

enum {
    mPlayer_ITEM_MAIN_NONE,
    mPlayer_ITEM_MAIN_AXE_NORMAL,
    mPlayer_ITEM_MAIN_NET_NORMAL,
    mPlayer_ITEM_MAIN_NET_SWING,
    mPlayer_ITEM_MAIN_NET_STOP,
    mPlayer_ITEM_MAIN_TUMBLE,
    mPlayer_ITEM_MAIN_TUBMLE_GETUP,
    mPlayer_ITEM_MAIN_NET_PULL,
    mPlayer_ITEM_MAIN_NET_PUTAWAY,
    mPlayer_ITEM_MAIN_NET_COMPLETE_COLLECTION,
    mPlayer_ITEM_MAIN_UMBRELLA_NORMAL,
    mPlayer_ITEM_MAIN_ROD_NORMAL,
    mPlayer_ITEM_MAIN_ROD_READY,
    mPlayer_ITEM_MAIN_ROD_CAST,
    mPlayer_ITEM_MAIN_ROD_AIR,
    mPlayer_ITEM_MAIN_ROD_RELAX,
    mPlayer_ITEM_MAIN_ROD_COLLECT,
    mPlayer_ITEM_MAIN_ROD_VIB,
    mPlayer_ITEM_MAIN_ROD_FLY,
    mPlayer_ITEM_MAIN_ROD_PUTAWAY,
    mPlayer_ITEM_MAIN_SCOOP_NORMAL,
    mPlayer_ITEM_MAIN_BALLOON_NORMAL,
    mPlayer_ITEM_MAIN_WINDMILL_NORMAL,
    mPlayer_ITEM_MAIN_FAN_NORMAL,

    mPlayer_ITEM_MAIN_NUM,
};

#define mPlayer_ITEM_MAIN_VALID(main_index) \
    ((main_index) >= (mPlayer_ITEM_MAIN_NONE) && (main_index) < (mPlayer_ITEM_MAIN_NUM))

enum {
    mPlayer_ITEM_KIND_AXE,
    mPlayer_ITEM_KIND_AXE_USE_1,
    mPlayer_ITEM_KIND_AXE_USE_2,
    mPlayer_ITEM_KIND_AXE_USE_3,
    mPlayer_ITEM_KIND_AXE_USE_4,
    mPlayer_ITEM_KIND_AXE_USE_5,
    mPlayer_ITEM_KIND_AXE_USE_6,
    mPlayer_ITEM_KIND_AXE_USE_7,
    mPlayer_ITEM_KIND_GOLD_AXE,

    mPlayer_ITEM_KIND_NET,
    mPlayer_ITEM_KIND_GOLD_NET,

    mPlayer_ITEM_KIND_UMBRELLA00,
    mPlayer_ITEM_KIND_UMBRELLA01,
    mPlayer_ITEM_KIND_UMBRELLA02,
    mPlayer_ITEM_KIND_UMBRELLA03,
    mPlayer_ITEM_KIND_UMBRELLA04,
    mPlayer_ITEM_KIND_UMBRELLA05,
    mPlayer_ITEM_KIND_UMBRELLA06,
    mPlayer_ITEM_KIND_UMBRELLA07,
    mPlayer_ITEM_KIND_UMBRELLA08,
    mPlayer_ITEM_KIND_UMBRELLA09,
    mPlayer_ITEM_KIND_UMBRELLA10,
    mPlayer_ITEM_KIND_UMBRELLA11,
    mPlayer_ITEM_KIND_UMBRELLA12,
    mPlayer_ITEM_KIND_UMBRELLA13,
    mPlayer_ITEM_KIND_UMBRELLA14,
    mPlayer_ITEM_KIND_UMBRELLA15,
    mPlayer_ITEM_KIND_UMBRELLA16,
    mPlayer_ITEM_KIND_UMBRELLA17,
    mPlayer_ITEM_KIND_UMBRELLA18,
    mPlayer_ITEM_KIND_UMBRELLA19,
    mPlayer_ITEM_KIND_UMBRELLA20,
    mPlayer_ITEM_KIND_UMBRELLA21,
    mPlayer_ITEM_KIND_UMBRELLA22,
    mPlayer_ITEM_KIND_UMBRELLA23,
    mPlayer_ITEM_KIND_UMBRELLA24,
    mPlayer_ITEM_KIND_UMBRELLA25,
    mPlayer_ITEM_KIND_UMBRELLA26,
    mPlayer_ITEM_KIND_UMBRELLA27,
    mPlayer_ITEM_KIND_UMBRELLA28,
    mPlayer_ITEM_KIND_UMBRELLA29,
    mPlayer_ITEM_KIND_UMBRELLA30,
    mPlayer_ITEM_KIND_UMBRELLA31,

    mPlayer_ITEM_KIND_ORG_UMBRELLA00,
    mPlayer_ITEM_KIND_ORG_UMBRELLA01,
    mPlayer_ITEM_KIND_ORG_UMBRELLA02,
    mPlayer_ITEM_KIND_ORG_UMBRELLA03,
    mPlayer_ITEM_KIND_ORG_UMBRELLA04,
    mPlayer_ITEM_KIND_ORG_UMBRELLA05,
    mPlayer_ITEM_KIND_ORG_UMBRELLA06,
    mPlayer_ITEM_KIND_ORG_UMBRELLA07,

    mPlayer_ITEM_KIND_ROD,
    mPlayer_ITEM_KIND_GOLD_ROD,

    mPlayer_ITEM_KIND_SHOVEL,
    mPlayer_ITEM_KIND_GOLD_SHOVEL,

    mPlayer_ITEM_KIND_RED_BALLOON,
    mPlayer_ITEM_KIND_YELLOW_BALLOON,
    mPlayer_ITEM_KIND_BLUE_BALLOON,
    mPlayer_ITEM_KIND_GREEN_BALLOON,
    mPlayer_ITEM_KIND_PURPLE_BALLOON,
    mPlayer_ITEM_KIND_BUNNY_P_BALLOON,
    mPlayer_ITEM_KIND_BUNNY_B_BALLOON,
    mPlayer_ITEM_KIND_BUNNY_O_BALLOON,

    mPlayer_ITEM_KIND_YELLOW_PINWHEEL,
    mPlayer_ITEM_KIND_RED_PINWHEEL,
    mPlayer_ITEM_KIND_TIGER_PINWHEEL,
    mPlayer_ITEM_KIND_GREEN_PINWHEEL,
    mPlayer_ITEM_KIND_PINK_PINWHEEL,
    mPlayer_ITEM_KIND_STRIPED_PINWHEEL,
    mPlayer_ITEM_KIND_FLOWER_PINWHEEL,
    mPlayer_ITEM_KIND_FANCY_PINWHEEL,

    mPlayer_ITEM_KIND_BLUEBELL_FAN,
    mPlayer_ITEM_KIND_PLUM_FAN,
    mPlayer_ITEM_KIND_BAMBOO_FAN,
    mPlayer_ITEM_KIND_CLOUD_FAN,
    mPlayer_ITEM_KIND_MAPLE_FAN,
    mPlayer_ITEM_KIND_FAN_FAN,
    mPlayer_ITEM_KIND_FLOWER_FAN,
    mPlayer_ITEM_KIND_LEAF_FAN,

    mPlayer_ITEM_KIND_NUM /* Are there more? */
};

#define mPlayer_ITEM_KIND_NONE -1

#define mPlayer_ITEM_KIND_CHECK(kind, min, max) ((kind) >= (min) && (kind) < ((max) + 1))
#define mPlayer_ITEM_IS_AXE(kind) mPlayer_ITEM_KIND_CHECK(kind, mPlayer_ITEM_KIND_AXE, mPlayer_ITEM_KIND_GOLD_AXE)
#define mPlayer_ITEM_IS_NET(kind) mPlayer_ITEM_KIND_CHECK(kind, mPlayer_ITEM_KIND_NET, mPlayer_ITEM_KIND_GOLD_NET)
#define mPlayer_ITEM_IS_ROD(kind) mPlayer_ITEM_KIND_CHECK(kind, mPlayer_ITEM_KIND_ROD, mPlayer_ITEM_KIND_GOLD_ROD)
#define mPlayer_ITEM_IS_SHOVEL(kind) \
    mPlayer_ITEM_KIND_CHECK(kind, mPlayer_ITEM_KIND_SHOVEL, mPlayer_ITEM_KIND_GOLD_SHOVEL)
#define mPlayer_ITEM_IS_UMBRELLA(kind) \
    mPlayer_ITEM_KIND_CHECK(kind, mPlayer_ITEM_KIND_UMBRELLA00, mPlayer_ITEM_KIND_ORG_UMBRELLA07)
#define mPlayer_ITEM_IS_BALLOON(kind) \
    mPlayer_ITEM_KIND_CHECK(kind, mPlayer_ITEM_KIND_RED_BALLOON, mPlayer_ITEM_KIND_BUNNY_O_BALLOON)
#define mPlayer_ITEM_IS_WINDMILL(kind) \
    mPlayer_ITEM_KIND_CHECK(kind, mPlayer_ITEM_KIND_YELLOW_PINWHEEL, mPlayer_ITEM_KIND_FANCY_PINWHEEL)
#define mPlayer_ITEM_IS_FAN(kind) \
    mPlayer_ITEM_KIND_CHECK(kind, mPlayer_ITEM_KIND_BLUEBELL_FAN, mPlayer_ITEM_KIND_LEAF_FAN)
#define mPlayer_ITEM_IS_NOT_TOOL(kind)                                                                    \
    (mPlayer_ITEM_IS_UMBRELLA(kind) || mPlayer_ITEM_IS_BALLOON(kind) || mPlayer_ITEM_IS_WINDMILL(kind) || \
     mPlayer_ITEM_IS_FAN(kind))

#define mPlayer_ITEM_KIND_VALID(kind) (mPlayer_ITEM_KIND_CHECK(kind, 0, mPlayer_ITEM_KIND_NUM))

enum {
    mPlayer_ITEM_DATA_AXE,      // model
    mPlayer_ITEM_DATA_AXE_B,    // model
    mPlayer_ITEM_DATA_AXE_C,    // model
    mPlayer_ITEM_DATA_GOLD_AXE, // model

    mPlayer_ITEM_DATA_NET,            // skeleton
    mPlayer_ITEM_DATA_GOLD_NET,       // skeleton
    mPlayer_ITEM_DATA_NET_GET_M,      // animation
    mPlayer_ITEM_DATA_NET_SWING,      // animation
    mPlayer_ITEM_DATA_KAMAE_MAIN_M,   // animation
    mPlayer_ITEM_DATA_KOKERU_GETUP_N, // animation
    mPlayer_ITEM_DATA_KOKERU_N,       // animation
    mPlayer_ITEM_DATA_SWING_WAIT,     // animation
    mPlayer_ITEM_DATA_YATTA_M,        // animation

    mPlayer_ITEM_DATA_ROD,           // skeleton
    mPlayer_ITEM_DATA_GOLD_ROD,      // skeleton
    mPlayer_ITEM_DATA_ROD_GET_T,     // animation
    mPlayer_ITEM_DATA_ROD_MOVE,      // animation
    mPlayer_ITEM_DATA_ROD_SINARI,    // animation
    mPlayer_ITEM_DATA_ROD_SWING,     // animation
    mPlayer_ITEM_DATA_ROD_WAIT,      // animation
    mPlayer_ITEM_DATA_ROD_NOT_SWING, // animation

    mPlayer_ITEM_DATA_SHOVEL,      // model
    mPlayer_ITEM_DATA_GOLD_SHOVEL, // model

    mPlayer_ITEM_DATA_BALLOON1,      // skeleton
    mPlayer_ITEM_DATA_BALLOON2,      // skeleton
    mPlayer_ITEM_DATA_BALLOON3,      // skeleton
    mPlayer_ITEM_DATA_BALLOON4,      // skeleton
    mPlayer_ITEM_DATA_BALLOON5,      // skeleton
    mPlayer_ITEM_DATA_BALLOON6,      // skeleton
    mPlayer_ITEM_DATA_BALLOON7,      // skeleton
    mPlayer_ITEM_DATA_BALLOON8,      // skeleton
    mPlayer_ITEM_DATA_BALLOON_WAIT,  // animation
    mPlayer_ITEM_DATA_BALLOON_GYAZA, // animation

    mPlayer_ITEM_DATA_PINWHEEL1,     // skeleton
    mPlayer_ITEM_DATA_PINWHEEL2,     // skeleton
    mPlayer_ITEM_DATA_PINWHEEL3,     // skeleton
    mPlayer_ITEM_DATA_PINWHEEL4,     // skeleton
    mPlayer_ITEM_DATA_PINWHEEL5,     // skeleton
    mPlayer_ITEM_DATA_PINWHEEL6,     // skeleton
    mPlayer_ITEM_DATA_PINWHEEL7,     // skeleton
    mPlayer_ITEM_DATA_PINWHEEL8,     // skeleton
    mPlayer_ITEM_DATA_PINWHEEL_WAIT, // animation

    mPlayer_ITEM_DATA_FAN1, // model
    mPlayer_ITEM_DATA_FAN2, // model
    mPlayer_ITEM_DATA_FAN3, // model
    mPlayer_ITEM_DATA_FAN4, // model
    mPlayer_ITEM_DATA_FAN5, // model
    mPlayer_ITEM_DATA_FAN6, // model
    mPlayer_ITEM_DATA_FAN7, // model
    mPlayer_ITEM_DATA_FAN8, // model

    mPlayer_ITEM_DATA_NUM
};

#define mPlayer_ITEM_DATA_VALID(type) ((type) >= 0 && type < mPlayer_ITEM_DATA_NUM)

enum {
    mPlayer_ITEM_DATA_TYPE_GFX,
    mPlayer_ITEM_DATA_TYPE_SKELETON,
    mPlayer_ITEM_DATA_TYPE_NET_ANIMATION,
    mPlayer_ITEM_DATA_TYPE_ROD_ANIMATION,
    mPlayer_ITEM_DATA_TYPE_BALLOON_ANIMATION,
    mPlayer_ITEM_DATA_TYPE_PINWHEEL_ANIMATION,

    mPlayer_ITEM_DATA_TYPE_NUM
};

enum {
    mPlayer_PART_TABLE_NORMAL,
    mPlayer_PART_TABLE_AXE,
    mPlayer_PART_TABLE_PICK_UP,
    mPlayer_PART_TABLE_NET,
    mPlayer_PART_TABLE_FAN,

    mPlayer_PART_TABLE_NUM
};

enum {
    mPlayer_CREATURE_INSECT,
    mPlayer_CREATURE_GYOEI,
    mPlayer_CREATURE_BALLOON,

    mPlayer_CREATURE_NUM
};

enum {
    mPlayer_BED_ACTION_NONE,
    mPlayer_BED_ACTION_ROLL,
    mPlayer_BED_ACTION_OUT,

    mPlayer_BED_ACTION_NUM
};

enum {
    mPlayer_DRAW_TYPE_NONE,
    mPlayer_DRAW_TYPE_NORMAL,

    mPlayer_DRAW_TYPE_NUM
};

enum {
    mPlayer_SHADOW_TYPE_NORMAL,
    mPlayer_SHADOW_TYPE_WORLD_POS,
    mPlayer_SHADOW_TYPE_ANIME_POS,
    mPlayer_SHADOW_TYPE_NONE,

    mPlayer_SHADOW_TYPE_NUM
};

enum {
    mPlayer_STATUS_FOR_BEE_WAIT,
    mPlayer_STATUS_FOR_BEE_ATTACK,
    mPlayer_STATUS_FOR_BEE_ENTER_BUILDING,

    mPlayer_STATUS_FOR_BEE_NUM
};

enum {
    mPlayer_NET_CATCH_TYPE_INSECT,
    mPlayer_NET_CATCH_TYPE_ANT,

    mPlayer_NET_CATCH_TYPE_NUM
};

enum {
    mPlayer_ABLE_ITEM_CAN_USE_ALL,
    mPlayer_ABLE_ITEM_CAN_USE_UMBRELLA,
    mPlayer_ABLE_ITEM_RESTRICTED,
    mPlayer_ABLE_ITEM_NONE,

    mPlayer_ABLE_ITEM_NUM
};

enum {
    mPlayer_AXE_HIT_NONE,
    mPlayer_AXE_HIT_REFLECT,
    mPlayer_AXE_HIT_TREE,

    mPlayer_AXE_HIT_NUM
};

enum {
    mPlayer_AXE_BREAK_FROM_SWING,
    mPlayer_AXE_BREAK_FROM_REFLECT,

    mPlayer_AXE_BREAK_FROM_NUM
};

enum {
    mPlayer_RADIO_EXERCISE_CMD0,
    mPlayer_RADIO_EXERCISE_CMD1,
    mPlayer_RADIO_EXERCISE_CMD2,
    mPlayer_RADIO_EXERCISE_CMD3,
    mPlayer_RADIO_EXERCISE_CMD4,
    mPlayer_RADIO_EXERCISE_CMD5,
    mPlayer_RADIO_EXERCISE_CMD6,
    mPlayer_RADIO_EXERCISE_CMD7,
    mPlayer_RADIO_EXERCISE_CMD8,
    mPlayer_RADIO_EXERCISE_CMD9,
    mPlayer_RADIO_EXERCISE_CMD10,
    mPlayer_RADIO_EXERCISE_CMD11,
    mPlayer_RADIO_EXERCISE_CMD12,
    mPlayer_RADIO_EXERCISE_CMD13,
    mPlayer_RADIO_EXERCISE_CMD14,
    mPlayer_RADIO_EXERCISE_CMD15,
    mPlayer_RADIO_EXERCISE_CMD16,
    mPlayer_RADIO_EXERCISE_CMD17,

    mPlayer_RADIO_EXERCISE_CMD_NUM
};

enum {
    mPlayer_GOLDEN_ITEM_TYPE_AXE,
    mPlayer_GOLDEN_ITEM_TYPE_NET,
    mPlayer_GOLDEN_ITEM_TYPE_ROD,
    mPlayer_GOLDEN_ITEM_TYPE_SHOVEL,

    mPlayer_GOLDEN_ITEM_TYPE_NUM
};

enum {
    mPlayer_USE_FACE_ROM_TYPE_TEX,
    mPlayer_USE_FACE_ROM_TYPE_PAL,

    mPlayer_USE_FACE_ROM_TYPE_NUM
};

enum {
    mPlayer_EYE_TEX0,
    mPlayer_EYE_TEX1,
    mPlayer_EYE_TEX2,
    mPlayer_EYE_TEX3,
    mPlayer_EYE_TEX4,
    mPlayer_EYE_TEX5,
    mPlayer_EYE_TEX6,
    mPlayer_EYE_TEX7,

    mPlayer_EYE_TEX_NUM
};

enum {
    mPlayer_MOUTH_TEX0,
    mPlayer_MOUTH_TEX1,
    mPlayer_MOUTH_TEX2,
    mPlayer_MOUTH_TEX3,
    mPlayer_MOUTH_TEX4,
    mPlayer_MOUTH_TEX5,

    mPlayer_MOUTH_TEX_NUM
};

#define mPlayer_SETUP_TEXTURE_ANIMATION_NONE (0 << 0)
/* Where is (1 << 0)? */
#define mPlayer_SETUP_TEXTURE_ANIMATION_EYE (1 << 1)
#define mPlayer_SETUP_TEXTURE_ANIMATION_MOUTH (1 << 2)

typedef struct player_request_return_demo_s {
    int prev_main_index;
    f32 time;
} mPlayer_request_return_demo_c;

typedef struct player_request_return_outdoor_s {
    int prev_main_index;
    f32 time;
    f32 _08;
} mPlayer_request_return_outdoor_c;

typedef struct player_request_return_outdoor2_s {
    int prev_main_index;
    f32 time;
    f32 _08;
} mPlayer_request_return_outdoor2_c;

typedef struct player_request_wait_s {
    f32 morph_speed;
    f32 _04;
    int flags;
} mPlayer_request_wait_c;

typedef struct player_request_talk_s {
    ACTOR* talk_actor;
    int turn_flag;
    f32 morph_speed;
    int umbrella_flag;
} mPlayer_request_talk_c;

typedef struct player_request_hold_s {
    int ftr_no;
    s16 angle_y;
    xyz_t player_pos;
    f32 morph_speed;
    int flags;
} mPlayer_request_hold_c;

typedef struct player_request_recieve_wait_s {
    ACTOR* talk_actor;
    int turn_flag;
    int prev_main_index;
    mActor_name_t item;
    int on_surface_flag;
} mPlayer_request_recieve_wait_c;

typedef struct player_request_give_s {
    ACTOR* talk_actor;
    int turn_flag;
    int prev_main_index;
    mActor_name_t item;
    int mode;
    int present_flag;
    int on_surface_flag;
} mPlayer_request_give_c;

typedef struct player_request_sitdown_s {
    s16 angle;
    xyz_t pos;
    int ftrID;
} mPlayer_request_sitdown_c;

typedef struct player_request_close_funriture_s {
    int anim_idx;
} mPlayer_request_close_furniture_c;

typedef struct player_request_lie_bed_s {
    int direction;
    s16 angle;
    xyz_t wpos;
    int flags;
} mPlayer_request_lie_bed_c;

typedef struct player_request_door_s {
    s16 angle_y;
    xyz_t player_pos;
    int type;
    uintptr_t label;
} mPlayer_request_door_c;

typedef struct player_request_outdoor_s {
    int type;
    int is_start_demo;
} mPlayer_request_outdoor_c;

typedef struct player_request_demo_wait_s {
    int umbrella_flag;
    uintptr_t label;
} mPlayer_request_demo_wait_c;

typedef struct player_request_demo_walk_s {
    f32 goal_pos_x;
    f32 goal_pos_z;
    f32 speed;
    int wait_flag;
} mPlayer_request_demo_walk_c;

typedef struct player_request_demo_geton_train_s {
    s16 angle_y;
    xyz_t player_pos;
} mPlayer_request_demo_geton_train_c;

typedef struct player_request_demo_getoff_train_s {
    s16 angle_y;
    xyz_t player_pos;
} mPlayer_request_demo_getoff_train_c;

typedef struct player_request_rotate_octagon_s {
    ACTOR* talk_actor;
    int turn_flag;
    int prev_main_index;
    xyz_t pos;
    s16 angle_y;
} mPlayer_request_rotate_octagon_c;

typedef struct player_request_wash_car_s {
    xyz_t car_pos;
    xyz_t orig_pos;
    s16 orig_angle_y;
    ACTOR* parent_actor;
} mPlayer_request_wash_car_c;

typedef struct player_request_throw_money_s {
    xyz_t pos;
    s16 angle_y;
} mPlayer_request_throw_money_c;

typedef struct player_request_pray_s {
    xyz_t pos;
    s16 angle_y;
} mPlayer_request_pray_c;

typedef struct player_request_mail_jump_s {
    xyz_t pos;
    s16 angle_y;
} mPlayer_request_mail_jump_c;

typedef struct player_request_shock_s {
    f32 start_time;
    s16 target_angle_y;
    u8 bee_chase_bgm_flag;
    int axe_flag;
} mPlayer_request_shock_c;

typedef struct player_request_push_snowball_s {
    uintptr_t label;
    int wade_flag;
} mPlayer_request_push_snowball_c;

typedef struct player_request_stung_mosquito_s {
    uintptr_t label;
} mPlayer_request_stung_mosquito_c;

typedef struct player_request_notice_mosquito_s {
    uintptr_t label;
} mPlayer_request_notice_mosquito_c;

typedef struct player_request_switch_on_lighthouse_s {
    s16 angle_y;
    xyz_t pos;
} mPlayer_request_switch_on_lighthouse_c;

typedef struct player_request_demo_geton_boat_s {
    xyz_t pos;
    s16 angle_y;
} mPlayer_request_demo_geton_boat_c;

typedef struct player_request_demo_getoff_boat_standup_s {
    xyz_t pos;
    s16 angle_y;
} mPlayer_request_demo_getoff_boat_standup_c;

typedef struct player_request_demo_get_golden_item_s {
    int type;
} mPlayer_request_demo_get_golden_item_c;

typedef struct player_request_walk_s {
    xyz_t pos;
    f32 morph_speed;
    int flags;
} mPlayer_request_walk_c;

typedef struct player_request_run_s {
    f32 morph_speed;
    int flags;
} mPlayer_request_run_c;

typedef struct player_request_dash_s {
    f32 morph_speed;
    int flags;
} mPlayer_request_dash_c;

typedef struct player_request_turn_dash_s {
    s16 target_angle_y;
} mPlayer_request_turn_dash_c;

typedef struct player_request_fall_s {
    f32 morph_speed;
    int flags;
} mPlayer_request_fall_c;

typedef struct player_request_wade_s {
    int dir;
} mPlayer_request_wade_c;

typedef struct player_request_wade_snowball_s {
    int dir;
    xyz_t snowball_dist;
    uintptr_t label;
} mPlayer_request_wade_snowball_c;

typedef struct player_request_push_s {
    int ftrNo;
    s16 angle_y;
    xyz_t player_pos;
} mPlayer_request_push_c;

typedef struct player_request_pull_s {
    int ftrNo;
    s16 angle_y;
    xyz_t start_pos;
    xyz_t end_pos;
    xyz_t ofs;
} mPlayer_request_pull_c;

typedef struct player_request_rotate_furniture_s {
    int ftrNo;
    s16 angle_y;
    xyz_t player_pos;
    int rotate_type;
} mPlayer_request_rotate_furniture_c;

typedef struct player_request_open_furniture_s {
    s16 angle_y;
    xyz_t player_pos;
    int anim_idx;
} mPlayer_request_open_furniture_c;

typedef struct player_request_wait_open_furniture_s {
    int anim_idx;
} mPlayer_request_wait_open_furniture_c;

typedef struct player_request_wait_close_furniture_s {
    int anim_idx;
} mPlayer_request_wait_close_furniture_c;

typedef struct player_request_roll_bed_s {
    int move_dir;
} mPlayer_request_roll_bed_c;

typedef struct player_request_standup_bed_s {
    int move_dir;
} mPlayer_request_standup_bed_c;

typedef struct player_request_pickup_s {
    int inv_slot;
    mActor_name_t item;
    xyz_t target_pos;
    xyz_t item_pos;
    int flag;
} mPlayer_request_pickup_c;

typedef struct player_request_pickup_jump_s {
    int inv_slot;
    mActor_name_t item;
    xyz_t item_pos;
    int ftr_flag;
    int knife_and_fork_flag;
} mPlayer_request_pickup_jump_c;

typedef struct player_request_pickup_furniture_s {
    int inv_slot;
    mActor_name_t item;
    xyz_t item_pos;
} mPlayer_request_pickup_furniture_c;

typedef struct player_request_pickup_exchange_s {
    xyz_t target_pos;
    mActor_name_t item;
} mPlayer_request_pickup_exchange_c;

typedef struct player_request_sitdown_wait_s {
    int ftrID;
} mPlayer_request_sitdown_wait_c;

typedef struct player_request_standup_s {
    int ftrID;
} mPlayer_request_standup_c;

typedef struct player_request_swing_axe_s {
    xyz_t goal_pos;
    mActor_name_t hit_item;
    u16 axe_damage_no;
    int hit_ut_x;
    int hit_ut_z;
    int break_flag;
} mPlayer_request_swing_axe_c;

typedef struct player_request_reflect_axe_s {
    xyz_t goal_pos;
    mActor_name_t hit_item;
    u16 axe_damage_no;
    ACTOR* hit_actor;
    int _14;
    int break_flag;
} mPlayer_request_reflect_axe_c;

typedef struct player_request_notice_net_s {
    int already_collected;
} mPlayer_request_notice_net_c;

typedef struct player_request_putaway_net_s {
    int exchange_flag;
} mPlayer_request_putaway_net_c;

typedef struct player_request_cast_rod_s {
    xyz_t bobber_target_pos;
} mPlayer_request_cast_rod_c;

typedef struct player_request_notice_rod_s {
    s16 angle_y;
} mPlayer_request_notice_rod_c;

typedef struct player_request_putaway_rod_s {
    s16 angle_y;
    int exchange_flag;
} mPlayer_request_putaway_rod_c;

typedef struct player_request_dig_scoop_s {
    xyz_t dig_pos;
    mActor_name_t item;
} mPlayer_request_dig_scoop_c;

typedef struct player_request_fill_scoop_s {
    xyz_t dig_pos;
} mPlayer_request_fill_scoop_c;

typedef struct player_request_reflect_scoop_s {
    xyz_t dig_pos;
    mActor_name_t item;
    ACTOR* hit_actor;
} mPlayer_request_reflect_scoop_c;

typedef struct player_request_putin_scoop_s {
    xyz_t dig_pos;
    mActor_name_t item;
    int get_gold_scoop_flag;
} mPlayer_request_putin_scoop_c;

typedef struct player_request_putaway_scoop_s {
    xyz_t dig_pos;
    mActor_name_t item;
    int _10;
} mPlayer_request_putaway_scoop_c;

typedef struct player_request_get_scoop_s {
    xyz_t dig_pos;
    mActor_name_t item;
} mPlayer_request_get_scoop_c;

typedef struct player_request_recieve_stretch_s {
    ACTOR* talk_actor;
    int turn_flag;
    int prev_main_index;
    mActor_name_t item;
    int on_surface_flag;
} mPlayer_request_recieve_stretch_c;

typedef struct player_request_recieve_s {
    ACTOR* talk_actor;
    int turn_flag;
    int prev_main_index;
    mActor_name_t item;
    int on_surface_flag;
} mPlayer_request_recieve_c;

typedef struct player_request_recieve_putaway_s {
    ACTOR* talk_actor;
    int turn_flag;
    int prev_main_index;
    mActor_name_t item;
    int on_surface_flag;
} mPlayer_request_recieve_putaway_c;

typedef struct player_request_give_wait_s {
    ACTOR* talk_actor;
    int turn_flag;
    int prev_main_index;
    mActor_name_t item;
    int on_surface_flag; // TODO: verify this flag is correct
} mPlayer_request_give_wait_c;

typedef struct player_request_demo_wade_s {
    int dir;
} mPlayer_request_demo_wade_c;

typedef struct player_request_release_creature_gyoei_s {
    s16 angle_y;
    s16 _02;
} mPlayer_request_release_creature_gyoei_c;

typedef struct player_request_release_creature_insect_s {
    xyz_t pos;
    int type;
} mPlayer_request_release_creature_insect_c;

typedef struct player_request_release_creature_balloon_s {
    int balloon_type;
} mPlayer_request_release_creature_balloon_c;

typedef union {
    mPlayer_request_release_creature_gyoei_c gyoei;
    mPlayer_request_release_creature_insect_c insect;
    mPlayer_request_release_creature_balloon_c balloon;
} mPlayer_request_release_creature_u;

typedef struct player_request_release_creature_s {
    int type;
    int gold_scoop_flag;
    mPlayer_request_release_creature_u data;
    ACTOR* actor;
} mPlayer_request_release_creature_c;

typedef struct player_request_shake_tree_s {
    xyz_t pos;
    mActor_name_t item;
    int ut_x;
    int ut_z;
} mPlayer_request_shake_tree_c;

typedef struct player_request_ready_pitfall_s {
    xyz_t pos;
} mPlayer_request_ready_pitfall_c;

typedef struct player_request_remove_grass_s {
    xyz_t grass_pos;
    xyz_t target_pos;
} mPlayer_request_remove_grass_c;

typedef struct player_request_change_cloth_s {
    ACTOR* talk_actor;
    int turn_flag;
    int prev_main_index;
    mActor_name_t cloth_item;
    u16 cloth_idx;
    int try_on_flag;
} mPlayer_request_change_cloth_c;

typedef struct player_request_swing_fan_s {
    int start_swing;
} mPlayer_request_swing_fan_c;

typedef struct player_request_radio_exercise_s {
    int cmd;
    f32 speed;
} mPlayer_request_radio_exercise_c;

typedef struct player_request_demo_geton_boat_wade_s {
    int dir;
    f32 border_ofs;
} mPlayer_request_demo_geton_boat_wade_c;

typedef struct player_request_demo_getoff_boat_s {
    xyz_t pos;
    s16 angle_y;
} mPlayer_request_demo_getoff_boat_c;

typedef struct player_request_give_from_submenu_s {
    xyz_t unused; // assumed based on size
    mActor_name_t item;
    int mode_after;   // player mode after the action finishes
    int present_flag; // set if the item is wrapped as presnet
    int counter_flag; // set when the item slides across a counter
} mPlayer_request_give_from_submenu_c;

typedef struct player_request_putin_scoop_from_submenu_s {
    xyz_t wpos;
    mActor_name_t item;
    int got_gold_scoop;
} mPlayer_request_putin_scoop_from_submenu_data_c;

typedef struct {
    int _0;
    ACTOR* speak_actor;
} mPlayer_request_demo_wait_from_submenu_c;

typedef union {
    mPlayer_request_give_from_submenu_c give_from_submenu;
    mPlayer_request_putin_scoop_from_submenu_data_c putin_scoop_from_submenu;
    mPlayer_request_demo_wait_from_submenu_c demo_wait_from_submenu;
    mPlayer_request_return_demo_c return_demo;
    mPlayer_request_wait_c wait;
    mPlayer_request_talk_c talk;
    mPlayer_request_hold_c hold;
    mPlayer_request_recieve_wait_c recieve_wait;
    mPlayer_request_give_c give;
    mPlayer_request_sitdown_c sitdown;
    mPlayer_request_close_furniture_c close_furniture;
    mPlayer_request_lie_bed_c lie_bed;
    mPlayer_request_door_c door;
    mPlayer_request_outdoor_c outdoor;
    mPlayer_request_demo_wait_c demo_wait;
    mPlayer_request_demo_walk_c demo_walk;
    mPlayer_request_demo_geton_train_c demo_geton_train;
    mPlayer_request_demo_getoff_train_c demo_getoff_train;
    mPlayer_request_rotate_octagon_c rotate_octagon;
    mPlayer_request_wash_car_c wash_car;
    mPlayer_request_throw_money_c throw_money;
    mPlayer_request_pray_c pray;
    mPlayer_request_mail_jump_c mail_jump;
    mPlayer_request_shock_c shock;
    mPlayer_request_push_snowball_c push_snowball;
    mPlayer_request_stung_mosquito_c stung_mosquito;
    mPlayer_request_notice_mosquito_c notice_mosquito;
    mPlayer_request_switch_on_lighthouse_c switch_on_lighthouse;
    mPlayer_request_demo_geton_boat_c demo_geton_boat;
    mPlayer_request_demo_getoff_boat_standup_c demo_getoff_boat_standup;
    mPlayer_request_demo_get_golden_item_c demo_get_golden_item;
    mPlayer_request_walk_c walk;
    mPlayer_request_run_c run;
    mPlayer_request_dash_c dash;
    mPlayer_request_turn_dash_c turn_dash;
    mPlayer_request_fall_c fall;
    mPlayer_request_wade_c wade;
    mPlayer_request_wade_snowball_c wade_snowball;
    mPlayer_request_push_c push;
    mPlayer_request_pull_c pull;
    mPlayer_request_rotate_furniture_c rotate_furniture;
    mPlayer_request_open_furniture_c open_furniture;
    mPlayer_request_wait_open_furniture_c wait_open_furniture;
    mPlayer_request_wait_close_furniture_c wait_close_furniture;
    mPlayer_request_roll_bed_c roll_bed;
    mPlayer_request_standup_bed_c standup_bed;
    mPlayer_request_pickup_c pickup;
    mPlayer_request_pickup_jump_c pickup_jump;
    mPlayer_request_pickup_furniture_c pickup_furniture;
    mPlayer_request_pickup_exchange_c pickup_exchange;
    mPlayer_request_sitdown_wait_c sitdown_wait;
    mPlayer_request_standup_c standup;
    mPlayer_request_swing_axe_c swing_axe;
    mPlayer_request_reflect_axe_c reflect_axe;
    mPlayer_request_notice_net_c notice_net;
    mPlayer_request_putaway_net_c putaway_net;
    mPlayer_request_cast_rod_c cast_rod;
    mPlayer_request_notice_rod_c notice_rod;
    mPlayer_request_putaway_rod_c putaway_rod;
    mPlayer_request_dig_scoop_c dig_scoop;
    mPlayer_request_fill_scoop_c fill_scoop;
    mPlayer_request_reflect_scoop_c reflect_scoop;
    mPlayer_request_putin_scoop_c putin_scoop;
    mPlayer_request_putaway_scoop_c putaway_scoop;
    mPlayer_request_get_scoop_c get_scoop;
    mPlayer_request_recieve_stretch_c recieve_stretch;
    mPlayer_request_recieve_c recieve;
    mPlayer_request_recieve_putaway_c recieve_putaway;
    mPlayer_request_give_wait_c give_wait;
    mPlayer_request_demo_wade_c demo_wade;
    mPlayer_request_release_creature_c release_creature;
    mPlayer_request_shake_tree_c shake_tree;
    mPlayer_request_ready_pitfall_c ready_pitfall;
    mPlayer_request_remove_grass_c remove_grass;
    mPlayer_request_change_cloth_c change_cloth;
    mPlayer_request_swing_fan_c swing_fan;
    mPlayer_request_radio_exercise_c radio_exercise;
    mPlayer_request_demo_geton_boat_wade_c demo_geton_boat_wade;
    mPlayer_request_demo_getoff_boat_c demo_getoff_boat;
    u64 align; // TODO: is this necessary? it makes the size correct for this and mPlayer_request_main_data
} mPlayer_request_backup_u;

typedef struct player_request_takeout_item_s {
    mPlayer_request_backup_u request_data;
    int request_main_index;
} mPlayer_request_takeout_item_c;

typedef struct player_request_putin_item_s {
    mPlayer_request_backup_u request_data;
    int request_main_index;
} mPlayer_request_putin_item_c;

typedef struct player_request_knock_door_s {
    mPlayer_request_backup_u request_data;
    int request_main_index;
    xyz_t pos;
    s16 angle_y;
} mPlayer_request_knock_door_c;

typedef union {
    mPlayer_request_give_from_submenu_c give_from_submenu;
    mPlayer_request_putin_scoop_from_submenu_data_c putin_scoop_from_submenu;
    mPlayer_request_demo_wait_from_submenu_c demo_wait_from_submenu;
    mPlayer_request_return_demo_c return_demo;
    mPlayer_request_return_outdoor_c return_outdoor;
    mPlayer_request_return_outdoor2_c return_outdoor2;
    mPlayer_request_wait_c wait;
    mPlayer_request_talk_c talk;
    mPlayer_request_hold_c hold;
    mPlayer_request_recieve_wait_c recieve_wait;
    mPlayer_request_give_c give;
    mPlayer_request_sitdown_c sitdown;
    mPlayer_request_close_furniture_c close_furniture;
    mPlayer_request_lie_bed_c lie_bed;
    mPlayer_request_door_c door;
    mPlayer_request_outdoor_c outdoor;
    mPlayer_request_demo_wait_c demo_wait;
    mPlayer_request_demo_walk_c demo_walk;
    mPlayer_request_demo_geton_train_c demo_geton_train;
    mPlayer_request_demo_getoff_train_c demo_getoff_train;
    mPlayer_request_rotate_octagon_c rotate_octagon;
    mPlayer_request_wash_car_c wash_car;
    mPlayer_request_throw_money_c throw_money;
    mPlayer_request_pray_c pray;
    mPlayer_request_mail_jump_c mail_jump;
    mPlayer_request_shock_c shock;
    mPlayer_request_push_snowball_c push_snowball;
    mPlayer_request_stung_mosquito_c stung_mosquito;
    mPlayer_request_notice_mosquito_c notice_mosquito;
    mPlayer_request_switch_on_lighthouse_c switch_on_lighthouse;
    mPlayer_request_demo_geton_boat_c demo_geton_boat;
    mPlayer_request_demo_getoff_boat_standup_c demo_getoff_boat_standup;
    mPlayer_request_demo_get_golden_item_c demo_get_golden_item;
    mPlayer_request_walk_c walk;
    mPlayer_request_run_c run;
    mPlayer_request_dash_c dash;
    mPlayer_request_turn_dash_c turn_dash;
    mPlayer_request_fall_c fall;
    mPlayer_request_wade_c wade;
    mPlayer_request_wade_snowball_c wade_snowball;
    mPlayer_request_push_c push;
    mPlayer_request_pull_c pull;
    mPlayer_request_rotate_furniture_c rotate_furniture;
    mPlayer_request_open_furniture_c open_furniture;
    mPlayer_request_wait_open_furniture_c wait_open_furniture;
    mPlayer_request_wait_close_furniture_c wait_close_furniture;
    mPlayer_request_roll_bed_c roll_bed;
    mPlayer_request_standup_bed_c standup_bed;
    mPlayer_request_pickup_c pickup;
    mPlayer_request_pickup_jump_c pickup_jump;
    mPlayer_request_pickup_furniture_c pickup_furniture;
    mPlayer_request_pickup_exchange_c pickup_exchange;
    mPlayer_request_sitdown_wait_c sitdown_wait;
    mPlayer_request_standup_c standup;
    mPlayer_request_swing_axe_c swing_axe;
    mPlayer_request_reflect_axe_c reflect_axe;
    mPlayer_request_notice_net_c notice_net;
    mPlayer_request_putaway_net_c putaway_net;
    mPlayer_request_cast_rod_c cast_rod;
    mPlayer_request_notice_rod_c notice_rod;
    mPlayer_request_putaway_rod_c putaway_rod;
    mPlayer_request_dig_scoop_c dig_scoop;
    mPlayer_request_fill_scoop_c fill_scoop;
    mPlayer_request_reflect_scoop_c reflect_scoop;
    mPlayer_request_putin_scoop_c putin_scoop;
    mPlayer_request_putaway_scoop_c putaway_scoop;
    mPlayer_request_get_scoop_c get_scoop;
    mPlayer_request_recieve_stretch_c recieve_stretch;
    mPlayer_request_recieve_c recieve;
    mPlayer_request_recieve_putaway_c recieve_putaway;
    mPlayer_request_give_wait_c give_wait;
    mPlayer_request_demo_wade_c demo_wade;
    mPlayer_request_release_creature_c release_creature;
    mPlayer_request_shake_tree_c shake_tree;
    mPlayer_request_ready_pitfall_c ready_pitfall;
    mPlayer_request_remove_grass_c remove_grass;
    mPlayer_request_change_cloth_c change_cloth;
    mPlayer_request_swing_fan_c swing_fan;
    mPlayer_request_radio_exercise_c radio_exercise;
    mPlayer_request_demo_geton_boat_wade_c demo_geton_boat_wade;
    mPlayer_request_demo_getoff_boat_c demo_getoff_boat;
    mPlayer_request_takeout_item_c takeout_item;
    mPlayer_request_putin_item_c putin_item;
    mPlayer_request_knock_door_c knock_door;
    /* TODO: others? */
    // u8 force_size[72]; // TEMP
} mPlayer_request_main_data;

/* Current main state data structs */

typedef struct player_main_intro_s {
    f32 timer;
} mPlayer_main_intro_c;

typedef struct player_main_return_demo_s {
    f32 timer;
    f32 max_timer;
    int prev_main_index;
} mPlayer_main_return_demo_c;

typedef struct player_main_return_outdoor_s {
    f32 timer;
    f32 max_timer;
    int prev_main_index;
} mPlayer_main_return_outdoor_c;

typedef struct player_main_return_outdoor2_s {
    f32 timer;
    f32 max_timer;
    int prev_main_index;
} mPlayer_main_return_outdoor2_c;

typedef struct player_main_wait_s {
    int radio_exercise_command;
} mPlayer_main_wait_c;

typedef struct player_main_door_s {
    uintptr_t label;
} mPlayer_main_door_c;

typedef struct player_main_outdoor_s {
    int is_demo;
} mPlayer_main_outdoor_c;

typedef struct player_main_hold_s {
    int ftr_no;
    s16 angle_y;
    xyz_t player_pos;
    int flags;
} mPlayer_main_hold_c;

typedef struct player_main_push_s {
    int ftr_no;
} mPlayer_main_push_c;

typedef struct player_main_pull_s {
    int ftr_no;
    xyz_t start_pos;
    xyz_t ofs;
    f32 timer;
} mPlayer_main_pull_c;

typedef struct player_main_rotate_furniture_s {
    int ftr_no;
    xyz_t pos;
    int _10;
    int rotate_type;
} mPlayer_main_rotate_furniture_c;

typedef struct player_main_open_furniture_s {
    s16 angle_y;
    xyz_t player_pos;
    int anim_idx;
} mPlayer_main_open_furniture_c;

typedef struct player_main_lie_bed_s {
    int flags;
} mPlayer_main_lie_bed_c;

typedef struct player_main_wait_bed_s {
    int flags;
} mPlayer_main_wait_bed_c;

typedef struct player_main_sitdown_s {
    int ftrID;
} mPlayer_main_sitdown_c;

typedef struct player_main_sitdown_wait_s {
    int ftrID;
} mPlayer_main_sitdown_wait_c;

typedef struct player_main_wade_s {
    int dir;
    xyz_t start_pos;
    xyz_t end_pos;
    f32 timer;
} mPlayer_main_wade_c;

typedef struct player_main_pickup_s {
    xyz_t target_pos;
    xyz_t item_pos;
    xyz_t item_offset;
    f32 scale;
    f32 timer;
    mActor_name_t item;
    int exchange_flag;
    int signboard_flag;
} mPlayer_main_pickup_c;

typedef struct player_main_pickup_jump_s {
    xyz_t target_pos;
    xyz_t item_pos;
    xyz_t item_offset;
    f32 scale;
    mActor_name_t item;
    int ftr_flag;
    int exchange_flag;
} mPlayer_main_pickup_jump_c;

typedef struct player_main_pickup_furniture_s {
    xyz_t target_pos;
    xyz_t item_pos;
    xyz_t item_offset;
    f32 scale;
    mActor_name_t item;
    int exchange_flag;
} mPlayer_main_pickup_furniture_c;

typedef struct player_main_pickup_exchange_s {
    xyz_t target_pos;
    mActor_name_t item;
    int msg_mode;
    int submenu_flag;
} mPlayer_main_pickup_exchange_c;

typedef struct player_main_axe_common_s {
    /* 0x00 */ xyz_t target_pos;
    /* 0x0C */ mActor_name_t item;
    /* 0x0E */ u16 axe_damage_no;
} mPlayer_main_axe_common_c;

typedef struct player_main_swing_axe_s {
    /* 0x00 */ mPlayer_main_axe_common_c axe_common;
    /* 0x10 */ int tree_ut_x;
    /* 0x14 */ int tree_ut_z;
    /* 0x18 */ int bee_flag;
    /* 0x1C */ s16 bee_angle_y;
    /* 0x20 */ int bee_counter;
} mPlayer_main_swing_axe_c;

typedef struct player_main_reflect_axe_s {
    /* 0x00 */ mPlayer_main_axe_common_c axe_common;
    /* 0x10 */ ACTOR* reflect_actor_p;
} mPlayer_main_reflect_axe_c;

typedef union player_main_axe_u {
    mPlayer_main_swing_axe_c swing_axe;
    mPlayer_main_reflect_axe_c reflect_axe;
} mPlayer_main_axe_u;

typedef struct player_main_broken_axe_s {
    mPlayer_main_axe_u axe;
    int break_type; /* mPlayer_AXE_BREAK_FROM_* */
    f32 _28;
    int _2C;
} mPlayer_main_broken_axe_c;

typedef struct player_main_slip_net_s {
    f32 _00;
} mPlayer_main_slip_net_c;

typedef struct player_main_relax_rod_s {
    int bee_flag;
    int mosquito_flag;
} mPlayer_main_relax_rod_c;

typedef struct player_main_dig_scoop_s {
    xyz_t target_pos;
    mActor_name_t item;
} mPlayer_main_dig_scoop_c;

typedef struct player_main_fill_scoop_s {
    xyz_t target_pos;
} mPlayer_main_fill_scoop_c;

typedef struct player_main_reflect_scoop_s {
    xyz_t target_pos;
    mActor_name_t item;
    ACTOR* reflect_actor_p;
} mPlayer_main_reflect_scoop_c;

typedef struct player_main_get_scoop_s {
    xyz_t target_pos;
    mActor_name_t item;
    f32 scale;
    int success_flag;
    f32 timer;
    int msg_mode;
    int submenu_flag;
} mPlayer_main_get_scoop_c;

typedef struct player_main_putaway_scoop_s {
    xyz_t target_pos;
    mActor_name_t item;
    f32 scale;
    int submenu_flag;
} mPlayer_main_putaway_scoop_c;

typedef struct player_main_putin_scoop_s {
    xyz_t target_pos;
    mActor_name_t item;
    int get_gold_scoop_flag; // TODO: check this
} mPlayer_main_putin_scoop_c;

typedef struct player_main_talk_s {
    ACTOR* talk_actor_p;
    int turn_flag;
    int feel_type;
} mPlayer_main_talk_c;

typedef struct player_main_recieve_wait_s {
    ACTOR* talk_actor_p;
    int turn_flag;
    int ret_main_index;
    mActor_name_t item;
    int surface_flag;
} mPlayer_main_recieve_wait_c;

typedef struct player_main_recieve_stretch_s {
    ACTOR* talk_actor_p;
    int turn_flag;
    int ret_main_index;
    mActor_name_t item;
    int surface_flag;
} mPlayer_main_recieve_stretch_c;

typedef struct player_main_recieve_s {
    ACTOR* talk_actor_p;
    int turn_flag;
    int ret_main_index;
    mActor_name_t item;
    int surface_flag;
} mPlayer_main_recieve_c;

typedef struct player_main_recieve_putaway_s {
    ACTOR* talk_actor_p;
    int turn_flag;
    int ret_main_index;
    int surface_flag;
} mPlayer_main_recieve_putaway_c;

typedef struct player_main_give_s {
    ACTOR* talk_actor_p;
    int turn_flag;
    int ret_main_index;
    mActor_name_t item;
    int surface_flag;
} mPlayer_main_give_c;

typedef struct player_main_give_wait_s {
    ACTOR* talk_actor_p;
    int turn_flag;
    int ret_main_index;
    int surface_flag;
} mPlayer_main_give_wait_c;

typedef struct player_main_takeout_item_s {
    mPlayer_request_takeout_item_c back_request_data;
    f32 timer;
} mPlayer_main_takeout_item_c;

typedef struct player_main_putin_item_s {
    mPlayer_request_putin_item_c back_request_data;
    f32 timer;
} mPlayer_main_putin_item_c;

typedef struct player_main_demo_wait_s {
    int effect_id;
    uintptr_t label;
} mPlayer_main_demo_wait_c;

typedef struct player_main_release_creature_s {
    int type;
    int golden_scoop_flag;
    ACTOR* release_actor_p;
    f32 timer;
    int actor_birth_flag;
} mPlayer_main_release_creature_c;

typedef struct player_main_wash_car_s {
    int anime_idx;
    int change_anime_idx;
    int counter;
    xyz_t ret_pos;
    s16 ret_angle_y;
    ACTOR* control_actor;
    int ret_order;
    int effect_flag;
} mPlayer_main_wash_car_c;

typedef struct player_main_rotate_octagon_s {
    ACTOR* talk_actor_p;
    int turn_flag;
    int return_main_index;
} mPlayer_main_rotate_octagon_c;

typedef struct player_main_swing_net_s {
    f32 swing_timer;
} mPlayer_main_swing_net_c;

typedef struct player_main_pull_net_s {
    f32 timer;
    int already_collected;
} mPlayer_main_pull_net_c;

typedef struct player_main_stop_net_s {
    int _00;
} mPlayer_main_stop_net_c;

typedef struct player_main_notice_net_s {
    int state;
    int not_full_pocket;
    int exchange_flag;
    int already_collected;
    int end_effect_flag;
} mPlayer_main_notice_net_c;

typedef struct player_main_putaway_net_s {
    int exchange_flag;
} mPlayer_main_putaway_net_c;

typedef struct player_main_cast_rod_s {
    xyz_t bobber_target_pos;
} mPlayer_main_cast_rod_c;

typedef struct player_main_notice_rod_s {
    f32 timer;
    int state;
    int not_full_pocket;
    s16 angle_y;
    int exchange_flag;
    int already_collected;
    int end_effect_flag;
} mPlayer_main_notice_rod_c;

typedef struct player_main_putaway_rod_s {
    f32 timer;
    s16 angle_y;
    int exchange_flag;
} mPlayer_main_putaway_rod_c;

typedef struct player_main_demo_wade_s {
    int dir;
    xyz_t start_pos;
    xyz_t end_pos;
    f32 timer;
} mPlayer_main_demo_wade_c;

typedef struct player_main_shake_tree_s {
    xyz_t target_pos;
    mActor_name_t item;
    int tree_ut_x;
    int tree_ut_z;
    int bee_flag;
    s16 bee_angle_y;
    int bee_spawn_timer;
} mPlayer_main_shake_tree_c;

typedef struct player_main_struggle_pitfall_s {
    f32 button_presses;
    f32 target_anim_speed;
} mPlayer_main_struggle_pitfall_c;

typedef struct player_main_stung_bee_s {
    f32 timer;
} mPlayer_main_stung_bee_c;

typedef struct player_main_notice_bee_s {
    f32 timer;
    int msg_mode;
} mPlayer_main_notice_bee_c;

typedef struct player_main_remove_grass_s {
    xyz_t grass_pos;
    xyz_t target_pos;
} mPlayer_main_remove_grass_c;

typedef struct player_main_shock_s {
    f32 start_time;
    s16 target_angle_y;
    f32 timer;
    f32 end_time;
    s8 bee_chase_bgm_flag;
    int axe_flag;
    int bgm_stop_flag;
} mPlayer_main_shock_c;

typedef struct player_main_knock_door_s {
    mPlayer_request_knock_door_c request_data;
} mPlayer_main_knock_door_c;

typedef struct player_main_change_netcloth_s {
    ACTOR* talk_actor;
    int turn_flag;
    int prev_main_index;
    mActor_name_t cloth_item;
    u16 cloth_idx;
} mPlayer_main_change_cloth_c;

typedef struct player_main_push_snowball_s {
    uintptr_t label;
} mPlayer_main_push_snowball_c;

typedef struct player_main_complete_payment_s {
    f32 timer;
    int msg_mode;
} mPlayer_main_complete_payment_c;

typedef struct player_main_fail_emu_s {
    f32 timer;
    int msg_mode;
} mPlayer_main_fail_emu_c;

typedef struct player_main_stung_mosquito_s {
    uintptr_t label;
} mPlayer_main_stung_mosquito_c;

typedef struct player_main_notice_mosquito_s {
    uintptr_t label;
    f32 timer;
    int msg_mode;
} mPlayer_main_notice_mosquito_c;

typedef struct player_main_radio_exercise_s {
    int cmd;
    int _04;
    int _08;
    int _0C;
} mPlayer_main_radio_exercise_c;

typedef struct player_main_wade_snowball_s {
    int dir;
    xyz_t start_pos;
    xyz_t end_pos;
    f32 timer;
    xyz_t snowball_dist;
    uintptr_t snowball_label;
} mPlayer_main_wade_snowball_c;

typedef struct player_main_demo_geton_boat_wade_s {
    int dir;
    xyz_t start_pos;
    xyz_t end_pos;
    f32 timer;
} mPlayer_main_demo_geton_boat_wade_c;

typedef struct player_main_demo_geton_boat_sitdown_s {
    s16 angle_z;
} mPlayer_main_demo_geton_boat_sitdown_c;

typedef struct player_main_demo_getoff_boat_standup_s {
    xyz_t pos;
    s16 angle_y;
    s16 angle_z;
} mPlayer_main_demo_getoff_boat_standup_c;

typedef struct player_main_demo_get_golden_item_s {
    f32 timer;
    int msg_mode;
    int type;
} mPlayer_main_demo_get_golden_item_c;

typedef struct player_main_demo_get_golden_axe_wait_s {
    f32 timer;
} mPlayer_main_demo_get_golden_axe_wait_c;

typedef struct player_main_uki_s {
    xyz_t cast_goal_point;
} mPlayer_main_uki_c;

typedef struct player_main_putaway_uki_s {
    f32 unk0;
} mPlayer_main_putaway_uki_c;

typedef struct player_main_balloon_s {
    int balloon_shape_type;
} mPlayer_main_balloon_c;

typedef struct player_main_turn_dash_s {
    s16 target_angle_y;
} mPlayer_main_turn_dash_c;

typedef struct player_main_fall_s {
    f32 morph_speed;
    int flags;
} mPlayer_main_turn_fall_c;

typedef union {
    mPlayer_main_intro_c intro;
    mPlayer_main_return_demo_c return_demo;
    mPlayer_main_return_outdoor_c return_outdoor;
    mPlayer_main_return_outdoor2_c return_outdoor2;
    mPlayer_main_wait_c wait;
    mPlayer_main_door_c door;
    mPlayer_main_outdoor_c outdoor;
    mPlayer_main_hold_c hold;
    mPlayer_main_push_c push;
    mPlayer_main_pull_c pull;
    mPlayer_main_rotate_furniture_c rotate_furniture;
    mPlayer_main_open_furniture_c open_furniture;
    mPlayer_main_lie_bed_c lie_bed;
    mPlayer_main_wait_bed_c wait_bed;
    mPlayer_main_sitdown_c sitdown;
    mPlayer_main_sitdown_wait_c sitdown_wait;
    mPlayer_main_wade_c wade;
    mPlayer_main_pickup_c pickup;
    mPlayer_main_pickup_jump_c pickup_jump;
    mPlayer_main_pickup_furniture_c pickup_furniture;
    mPlayer_main_pickup_exchange_c pickup_exchange;
    mPlayer_main_swing_axe_c swing_axe;
    mPlayer_main_reflect_axe_c reflect_axe;
    mPlayer_main_broken_axe_c broken_axe;
    mPlayer_main_swing_net_c swing_net;
    mPlayer_main_pull_net_c pull_net;
    mPlayer_main_stop_net_c stop_net;
    mPlayer_main_notice_net_c notice_net;
    mPlayer_main_putaway_net_c putaway_net;
    mPlayer_main_slip_net_c slip_net;
    mPlayer_main_cast_rod_c cast_rod;
    mPlayer_main_relax_rod_c relax_rod;
    mPlayer_main_notice_rod_c notice_rod;
    mPlayer_main_putaway_rod_c putaway_rod;
    mPlayer_main_dig_scoop_c dig_scoop;
    mPlayer_main_fill_scoop_c fill_scoop;
    mPlayer_main_reflect_scoop_c reflect_scoop;
    mPlayer_main_get_scoop_c get_scoop;
    mPlayer_main_putaway_scoop_c putaway_scoop;
    mPlayer_main_putin_scoop_c putin_scoop;
    mPlayer_main_demo_wade_c demo_wade;
    mPlayer_main_talk_c talk;
    mPlayer_main_recieve_wait_c recieve_wait;
    mPlayer_main_recieve_stretch_c recieve_stretch;
    mPlayer_main_recieve_c recieve;
    mPlayer_main_recieve_putaway_c recieve_putaway;
    mPlayer_main_give_c give;
    mPlayer_main_give_wait_c give_wait;
    mPlayer_main_takeout_item_c takeout_item;
    mPlayer_main_putin_item_c putin_item;
    mPlayer_main_demo_wait_c demo_wait;
    mPlayer_main_release_creature_c release_creature;
    mPlayer_main_wash_car_c wash_car;
    mPlayer_main_rotate_octagon_c rotate_octagon;
    mPlayer_main_shake_tree_c shake_tree;
    mPlayer_main_struggle_pitfall_c struggle_pitfall;
    mPlayer_main_stung_bee_c stung_bee;
    mPlayer_main_notice_bee_c notice_bee;
    mPlayer_main_remove_grass_c remove_grass;
    mPlayer_main_shock_c shock;
    mPlayer_main_knock_door_c knock_door;
    mPlayer_main_change_cloth_c change_cloth;
    mPlayer_main_push_snowball_c push_snowball;
    mPlayer_main_complete_payment_c complete_payment;
    mPlayer_main_fail_emu_c fail_emu;
    mPlayer_main_stung_mosquito_c stung_mosquito;
    mPlayer_main_notice_mosquito_c notice_mosquito;
    mPlayer_main_radio_exercise_c radio_exercise;
    mPlayer_main_wade_snowball_c wade_snowball;
    mPlayer_main_demo_geton_boat_wade_c demo_geton_boat_wade;
    mPlayer_main_demo_geton_boat_sitdown_c demo_geton_boat_sitdown;
    mPlayer_main_demo_getoff_boat_standup_c demo_getoff_boat_standup;
    mPlayer_main_demo_get_golden_item_c demo_get_golden_item;
    mPlayer_main_demo_get_golden_axe_wait_c demo_get_golden_axe_wait;
    mPlayer_main_uki_c uki;
    mPlayer_main_putaway_uki_c putaway_uki;
    mPlayer_main_balloon_c balloon;
    mPlayer_main_turn_dash_c turn_dash;
    mPlayer_main_turn_fall_c fall;
    u8 force_size[72]; // TEMP
} mPlayer_main_data;

typedef struct {
    int requested_main_index;
    int requested_index_pending;
    mPlayer_request_main_data request_main_data;
} mPlayer_change_data_from_submenu_c;

typedef struct controller_data_s {
    MCON mcon;
    s8 trigger_btn_a;
    s8 btn_a;
    s8 trigger_btn_b;
    s8 btn_b;
    mActor_name_t equipped_item;
} mPlayer_Controller_Data_c;

typedef struct player_eye_pattern_s {
    s16 pattern;
    s16 timer;
} mPlayer_eye_pattern_c;

/* sizeof(struct player_actor_s) == 0x13A8 */
struct player_actor_s {
    /* 0x0000 */ ACTOR actor_class;
    /* 0x0174 */ cKF_SkeletonInfo_R_c keyframe0;
    /* 0x01E4 */ cKF_SkeletonInfo_R_c keyframe1;
    /* 0x0252 */ s_xyz joint_data[mPlayer_JOINT_NUM + 1];
    /* 0x02F4 */ s_xyz morph_data[mPlayer_JOINT_NUM + 1];
    /* 0x0398 */ Mtx work_mtx[2][13];                /* swapped between frames */
    /* 0x0A18 */ cKF_SkeletonInfo_R_c item_keyframe; /* for item animations */
    /* 0x0A88 */ s_xyz item_joint_data[8];
    /* 0x0AB8 */ s_xyz item_morph_data[8];
    /* 0x0AE8 */ Mtx item_work_mtx[2][4]; /* swapped between frames */
    /* 0x0CE8 */ mPlayer_eye_pattern_c eye_pattern_normal;
    /* 0x0CEC */ int blink_count;
    /* 0x0CF0 */ int eye_tex_idx;
    /* 0x0CF4 */ int mouth_tex_idx;
    /* 0x0CF8 */ int now_main_index;
    /* 0x0CFC */ int prev_main_index;
    /* 0x0D00 */ int changed_main_index;
    /* 0x0D04 */ int now_item_main_index;
    /* 0x0D08 */ int requested_main_index;
    /* 0x0D0C */ int requested_main_index_priority;
    /* 0x0D10 */ int requested_main_index_changed;
    /* 0x0D14 */ int settled_requested_main_index_priority;
    /* 0x0D18 */ mPlayer_main_data main_data;                         // TODO: Union of many types...
    /* 0x0D60 */ mPlayer_request_main_data requested_main_index_data; // Union of many types...
    /* 0x0DA8 */ u8 _0DA8[0x0DB4 - 0x0DA8];                           /* unused */
    /* 0x0DB4 */ int animation0_idx;
    /* 0x0DB8 */ int animation1_idx;
    /* 0x0DBC */ int part_table_idx;
    /* 0x0DC0 */ int _0DC0;
    /* 0x0DC4 */ int item_shape_addr[2];
    /* 0x0DCC */ int item_anim_addr[2];
    /* 0x0DD4 */ int item_shape_segaddr[2];
    /* 0x0DDC */ int item_anim_segaddr[2];
    /* 0x0DE4 */ int item_shape_type[2];
    /* 0x0DEC */ int item_animation_idx[2];
    /* 0x0DF4 */ int item_bank_idx;
    /* 0x0DF8 */ f32 item_scale;
    /* 0x0DFC */ xyz_t shape_angle_delta;
    /* 0x0E08 */ xyz_t world_angle_delta;
    /* 0x0E14 */ s_xyz old_shape_angle;
    /* 0x0E1A */ s_xyz old_world_angle;
    /* 0x0E20 */ xyz_t shadow_pos;
    /* 0x0E2C */ xyz_t axe_pos;
    /* 0x0E38 */ xyz_t net_pos;
    /* 0x0E44 */ xyz_t net_top_col_pos;
    /* 0x0E50 */ xyz_t net_bot_col_pos;
    /* 0x0E5C */ s_xyz net_angle;
    /* 0x0E64 */ ACTOR* umbrella_actor;
    /* 0x0E68 */ int umbrella_state;
    /* 0x0E6C */ s8 unable_hand_item_in_demo;
    /* 0x0E6D */ s8 able_hand_all_item_in_demo;
    /* 0x0E70 */ uintptr_t item_net_catch_label;
    /* 0x0E74 */ s8 item_net_catch_type;
    /* 0x0E75 */ s8 item_net_has_catch;
    /* 0x0E78 */ uintptr_t item_net_catch_label_request_table[mPlayer_NET_CATCH_TABLE_COUNT];
    /* 0x0E98 */ s8 item_net_catch_type_request_table[mPlayer_NET_CATCH_TABLE_COUNT];
    /* 0x0EA0 */ xyz_t item_net_catch_pos_request_table[mPlayer_NET_CATCH_TABLE_COUNT];
    /* 0x0F00 */ f32 item_net_catch_radius_request_table[mPlayer_NET_CATCH_TABLE_COUNT];
    /* 0x0F20 */ int item_net_catch_request_use_count;
    /* 0x0F24 */ uintptr_t item_net_catch_label_request_force;
    /* 0x0F28 */ s8 item_net_catch_type_request_force;
    /* 0x0F2C */ int item_net_catch_insect_idx;
#if VERSION >= VER_GAFU01_00
    /* 0x0F30 */ xyz_t item_net_catch_correct_pos;
    /* 0x0F3C */ int item_net_catch_correct_pos_set;
#endif
    /* 0x0F30 */ ACTOR* fishing_rod_actor_p;
    /* 0x0F34 */ xyz_t item_rod_top_pos;
    /* 0x0F40 */ xyz_t item_rod_virtual_top_pos;
    /* 0x0F4C */ int item_rod_top_pos_set;
    /* 0x0F50 */ s16 item_rod_angle_z;
    /* 0x0F54 */ ClObjTris_c item_axe_tris;
    /* 0x0F68 */ ClObjTrisElem_c item_axe_tris_elem_tbl[1];
    /* 0x0FAC */ ClObjTris_c item_net_tris;
    /* 0x0FC0 */ ClObjTrisElem_c item_net_tris_elem_tbl[1];
    /* 0x1004 */ xyz_t scoop_pos;
    /* 0x1010 */ ClObjPipe_c col_pipe;
    /* 0x102C */ xyz_t head_pos;
    /* 0x1038 */ xyz_t feel_pos;
    /* 0x1044 */ xyz_t right_hand_pos;
    /* 0x1050 */ xyz_t right_hand_move;
    /* 0x105C */ xyz_t left_hand_pos;
    /* 0x1068 */ MtxF right_hand_mtx;
    /* 0x10A8 */ MtxF left_hand_mtx;
    /* 0x10E8 */ xyz_t right_foot_pos;
    /* 0x10F4 */ xyz_t left_foot_pos;
    /* 0x1100 */ s_xyz right_foot_angle;
    /* 0x1106 */ s_xyz left_foot_angle;
    /* 0x110C */ int draw_effect_idx; // subtract 1 for the effect id
    /* 0x1110 */ s8 part_table[mPlayer_JOINT_NUM + 1];
    /* 0x112B */ s8 item_kind;
    /* 0x112C */ int item_matrix_set;
    /* 0x1130 */ xyz_t net_start_pos;
    /* 0x113C */ xyz_t net_end_pos;
    /* 0x1148 */ xyz_t other_item_start_pos;
    /* 0x1154 */ xyz_t other_item_end_pos;
    /* 0x1160 */ f32 other_item_move_dist;
    /* 0x1164 */ s_xyz windmill_param;
    /* 0x116A */ s_xyz windmill_angle;
    /* 0x1170 */ int balloon_start_pos_set_flag;
    /* 0x1174 */ ACTOR* balloon_actor;
    /* 0x1178 */ s16 balloon_lean_angle;
    /* 0x117A */ s_xyz balloon_angle;
    /* 0x1180 */ f32 balloon_add_rot_z;
    /* 0x1184 */ f32 balloon_anim_max_frame;
    /* 0x1188 */ f32 balloon_anim_speed;
    /* 0x118C */ int balloon_stop_movement_flag;
    /* 0x1190 */ s16 ballon_add_rot_x;
    /* 0x1192 */ s16 balloon_add_rot_x_counter;
    /* 0x1194 */ f32 balloon_current_frame;
    /* 0x1198 */ s8 address_able_display;
    /* 0x119A */ s_xyz head_angle;
    /* 0x11A0 */ xyz_t force_position;
    /* 0x11AC */ s_xyz force_angle;
    /* 0x11B2 */ u8 force_position_angle_flag;
    /* 0x11B4 */ f32 shake_tree_timer[3];
    /* 0x11C0 */ int shake_tree_ut_x[3];
    /* 0x11CC */ int shake_tree_ut_z[3];
    /* 0x11D8 */ int shake_tree_little[3];
    /* 0x11E4 */ xyz_t pitfall_pos;
    /* 0x11F0 */ int pitfall_flag;
    /* 0x11F4 */ f32 ripple_timer;
    /* 0x11F8 */ s8 ripple_foot_idx; // == 0: left, != 0: right
    /* 0x11F9 */ s8 bgm_volume_mode;
    /* 0x11FC */ int crash_snowball_for_wade;
    /* 0x1200 */ xyz_t snowball_dist;
    /* 0x120C */ int request_wade_dir;
    /* 0x1210 */ u16 cancel_wade_timer;
    /* 0x1214 */ int excute_cancel_wade;
    /* 0x1218 */ f32 geton_boat_wade_border_start;
    /* 0x121C */ u16 player_frame_counter;
    /* 0x121E */ s8 bee_chase_bgm_flag;
    /* 0x121F */ s8 status_for_bee;
    /* 0x1220 */ uintptr_t able_force_speak_label;
    /* 0x1224 */ int player_sunburn_rankup;
    /* 0x1228 */ int player_sunburn_rankdown;
    /* 0x122C */ s8 radio_exercise_command_ring_buffer[mPlayer_RADIO_EXERCISE_COMMAND_RING_BUFFER_SIZE];
    /* 0x1234 */ s8 radio_exercise_ring_buffer_cmd_timer;
    /* 0x1238 */ int radio_exercise_command_ring_buffer_index;
    /* 0x123C */ int radio_exercise_continue_cmd_idx;
    /* 0x1240 */ f32 radio_exercise_cmd_timer;
    /* 0x1244 */ u32 old_sound_frame_counter;
    /* 0x1248 */ s16 boat_angleZ;
    /* 0x124C */ int change_color_request;
    /* 0x1250 */ int change_color_flag;
    /* 0x1254 */ f32 change_color_timer;
    /* 0x1258 */ int change_color_rgb[3];
    /* 0x1264 */ int change_color_near;
    /* 0x1268 */ int change_color_far;
    /* 0x126C */ int refuse_pickup_knife_fork_flag;
    /* 0x1270 */ int (*request_main_invade_all_proc)(GAME*, int);
    /* 0x1274 */ int (*request_main_refuse_all_proc)(GAME*, int);
    /* 0x1278 */ int (*request_main_return_demo_all_proc)(GAME*, int, f32, int);
    /* 0x127C */ int (*request_main_wait_all_proc)(GAME*, f32, f32, int, int);
    /* 0x1280 */ int (*request_main_talk_all_proc)(GAME*, ACTOR*, int, f32, int, int);
    /* 0x1284 */ int (*request_main_hold_all_proc)(GAME*, int, int, const xyz_t*, f32, int, int);
    /* 0x1288 */ int (*request_main_recieve_wait_all_proc)(GAME*, ACTOR*, int, int, mActor_name_t, int, int);
    /* 0x128C */ int (*request_main_give_all_proc)(GAME*, ACTOR*, int, int, mActor_name_t, int, int, int, int);
    /* 0x1290 */ int (*request_main_sitdown_all_proc)(GAME*, int, const xyz_t*, int, int);
    /* 0x1294 */ int (*request_main_close_furniture_all_proc)(GAME*, int);
    /* 0x1298 */ int (*request_main_lie_bed_all_proc)(GAME*, int, const xyz_t*, int, int, int);
    /* 0x129C */ int (*request_main_hide_all_proc)(GAME*, int);
    /* 0x12A0 */ int (*request_main_groundhog_proc)(GAME*, int);
    /* 0x12A4 */ int (*request_main_door_all_proc)(GAME*, const xyz_t*, s16, int, void*, int);
    /* 0x12A8 */ int (*request_main_outdoor_all_proc)(GAME*, int, int, int);
    /* 0x12AC */ int (*request_main_wash_car_all_proc)(GAME*, const xyz_t*, const xyz_t*, s16, ACTOR*, int);
    /* 0x12B0 */ int (*request_main_rotate_octagon_all_proc)(GAME*, ACTOR*, int, int, const xyz_t*, s16, int);
    /* 0x12B4 */ int (*request_main_throw_money_all_proc)(GAME*, const xyz_t*, s16, int);
    /* 0x12B8 */ int (*request_main_pray_all_proc)(GAME*, const xyz_t*, s16, int);
    /* 0x12BC */ int (*request_main_mail_jump_all_proc)(GAME*, const xyz_t*, s16, int);
    /* 0x12C0 */ int (*request_main_demo_wait_all_proc)(GAME*, int, void*, int);
    /* 0x12C4 */ int (*request_main_demo_walk_all_proc)(GAME*, f32, f32, f32, int, int);
    /* 0x12C8 */ int (*request_main_demo_geton_train_all_proc)(GAME*, const xyz_t*, s16, int);
    /* 0x12CC */ int (*request_main_demo_getoff_train_all_proc)(GAME*, const xyz_t*, s16, int);
    /* 0x12D0 */ int (*request_main_demo_standing_train_all_proc)(GAME*, int);
    /* 0x12D4 */ int (*request_main_stung_bee_all_proc)(GAME*, int);
    /* 0x12D8 */ int (*request_main_shock_all_proc)(GAME*, f32, s16, s8, int, int);
    /* 0x12DC */ int (*request_main_change_cloth_forNPC_proc)(GAME*, mActor_name_t, u16, int);
    /* 0x12E0 */ int (*request_main_push_snowball_all_proc)(GAME*, void*, int, int);
    /* 0x12E4 */ int (*request_main_stung_mosquito_all_proc)(GAME*, void*, int);
    /* 0x12E8 */ int (*request_main_switch_on_lighthouse_all_proc)(GAME*, const xyz_t*, s16, int);
    /* 0x12EC */ int (*request_main_demo_geton_boat_all_proc)(GAME*, const xyz_t*, s16, int);
    /* 0x12F0 */ int (*request_main_demo_getoff_boat_standup_all_proc)(GAME*, const xyz_t*, s16, int);
    /* 0x12F4 */ int (*request_main_demo_get_golden_item2_all_proc)(GAME*, int, int);
    /* 0x12F8 */ int (*request_main_demo_get_golden_axe_wait_all_proc)(GAME*, int);
    /* 0x12FC */ int (*check_request_main_priority_proc)(GAME*, int);
    /* 0x1300 */ void* (*get_door_label_proc)(GAME*);
    /* 0x1304 */ int (*Set_Item_net_catch_request_table_proc)(ACTOR*, GAME*, uintptr_t, s8, const xyz_t*, f32);
    /* 0x1308 */ f32 (*Get_Item_net_catch_swing_timer_proc)(ACTOR*, GAME*);
    /* 0x130C */ int (*Set_Item_net_catch_request_force_proc)(ACTOR*, GAME*, uintptr_t, s8);
    /* 0x1310 */ void (*Set_force_position_angle_proc)(GAME*, const xyz_t*, const s_xyz*, u8);
    /* 0x1314 */ u8 (*Get_force_position_angle_proc)(GAME*, xyz_t*, s_xyz*);
    /* 0x1318 */ int (*Get_WadeEndPos_proc)(GAME*, xyz_t*);
    /* 0x131C */ int (*Check_Label_main_push_snowball_proc)(GAME*, void*);
    /* 0x1320 */ int (*SetParam_for_push_snowball_proc)(GAME*, const xyz_t*, s16, f32);
    /* 0x1324 */ int (*able_submenu_request_main_index_proc)(GAME*);
    /* 0x1328 */ int (*check_able_change_camera_normal_index_proc)(ACTOR*);
    /* 0x132C */ int (*Check_able_force_speak_label_proc)(GAME*, void*);
    /* 0x1330 */ int (*check_cancel_request_change_proc_index_proc)(int);
    /* 0x1334 */ uintptr_t (*Get_item_net_catch_label_proc)(ACTOR*);
    /* 0x1338 */ int (*Change_item_net_catch_label_proc)(ACTOR*, uintptr_t, s8);
    /* 0x133C */ int (*Check_StopNet_proc)(ACTOR*, xyz_t*);
    /* 0x1340 */ int (*Check_HitAxe_proc)(ACTOR*, xyz_t*);
    /* 0x1344 */ int (*Check_VibUnit_OneFrame_proc)(ACTOR*, const xyz_t*);
    /* 0x1348 */ int (*Check_HitScoop_proc)(ACTOR*, xyz_t*);
    /* 0x134C */ int (*Check_DigScoop_proc)(ACTOR*, xyz_t*);
    /* 0x1350 */ int (*check_request_change_item_proc)(GAME*);
    /* 0x1354 */ int (*Check_RotateOctagon_proc)(GAME*);
    /* 0x1358 */ int (*Check_end_stung_bee_proc)(ACTOR*);
    /* 0x135C */ int (*Get_status_for_bee_proc)(ACTOR*);
    /* 0x1360 */ int (*Set_ScrollDemo_forWade_snowball_proc)(ACTOR*, int, const xyz_t*);
    /* 0x1364 */ int (*Check_tree_shaken_proc)(ACTOR*, const xyz_t*);
    /* 0x1368 */ int (*Check_tree_shaken_little_proc)(ACTOR*, const xyz_t*);
    /* 0x136C */ int (*Check_tree_shaken_big_proc)(ACTOR*, const xyz_t*);
    /* 0x1370 */ int (*Check_Label_main_wade_snowball_proc)(GAME*, void*);
    /* 0x1374 */ int (*GetSnowballPos_forWadeSnowball_proc)(ACTOR*, xyz_t*);
    /* 0x1378 */ int (*CheckCondition_forWadeSnowball_proc)(GAME*, const xyz_t*, s16);
    /* 0x137C */ mActor_name_t (*Get_itemNo_forWindow_proc)(ACTOR*);
    /* 0x1380 */ int (*check_cancel_event_without_priority_proc)(GAME*);
    /* 0x1384 */ int (*CheckScene_AbleSubmenu_proc)();
    /* 0x1388 */ int (*Check_stung_mosquito_proc)(GAME*, void*);
    /* 0x138C */ int a_btn_pressed;
    /* 0x1390 */ int a_btn_triggers_submenu;
    /* 0x1394 */ mActor_name_t item_in_front; /* item directly in front of the player */
    /* 0x1398 */ xyz_t forward_ut_pos;        /* wpos of unit in front of player */
    /* 0x13A4 */ s8 update_scene_bg_mode;
};

extern void Player_actor_ct(ACTOR*, GAME*);
extern void Player_actor_dt(ACTOR*, GAME*);
extern void Player_actor_move(ACTOR*, GAME*);
extern void Player_actor_draw(ACTOR*, GAME*);

#ifdef __cplusplus
}
#endif

#endif
