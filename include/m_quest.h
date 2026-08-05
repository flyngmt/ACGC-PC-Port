#ifndef M_QUEST_H
#define M_QUEST_H

#include "types.h"
#include "libu64/gfxprint.h"
#include "lb_rtc.h"
#include "m_actor_type.h"
#include "m_personal_id.h"
#include "m_npc_personal_id.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mQst_MAX_TIME_LIMIT_DAYS 28
#define mQst_CHECK_NPC_RECEIPIENT 0
#define mQst_CHECK_NPC_SENDER 1

#define mQst_LETTER_RANK_MIN 0
#define mQst_LETTER_RANK_0 mQst_LETTER_RANK_MIN
#define mQst_LETTER_RANK_1 1
#define mQst_LETTER_RANK_2 2
#define mQst_LETTER_RANK_3 3
#define mQst_LETTER_RANK_4 4
#define mQst_LETTER_RANK_5 5
#define mQst_LETTER_RANK_6 6
#define mQst_LETTER_RANK_7 7
#define mQst_LETTER_RANK_8 8
#define mQst_LETTER_RANK_9 9
#define mQst_LETTER_RANK_10 10
#define mQst_LETTER_RANK_11 11
#define mQst_LETTER_RANK_MAX mQst_LETTER_RANK_11 + 1

#define mQst_LETTER_SCORE_BONUS 3   /* Given when the raw score of the letter has passed the threshold */
#define mQst_LETTER_PRESENT_BONUS 6 /* Given when a present is attached */

#define mQst_LETTER_OKAY_LENGTH 17
#define mQst_LETTER_GOOD_LENGTH 49

enum {
    mQst_QUEST_TYPE_DELIVERY, /* Deliver item quest */
    mQst_QUEST_TYPE_ERRAND,   /* Villager 'can I help' quests */
    mQst_QUEST_TYPE_CONTEST,  /* Villager send letter, plant flowers, bring ball, etc */
    mQst_QUEST_TYPE_NONE,

    mQst_QUEST_TYPE_NUM = mQst_QUEST_TYPE_NONE
};

/* sizeof(mQst_base_c) == 0xC */
typedef struct quest_base_s {
    /* 0x00 */ u32 quest_type : 2;         /* type, 0 = delivery, 1 = errand, 2 = contest, 3 = none */
    /* 0x00 */ u32 quest_kind : 6;         /* kind, differs by type */
    /* 0x01 */ u32 time_limit_enabled : 1; /* when set, the time limit will be utilized */
    /* 0x01 */ u32 progress : 4;           /* progress towards quest goal */
    /* 0x01 */ u32 give_reward : 1;        /* player cannot take the item, and will skip quest completion checks */
    /* 0x01 */ u32 unused : 2;

    /* 0x04 */ lbRTC_time_c time_limit;
} mQst_base_c;

/* Contest Quest */

enum {
    mQst_CONTEST_KIND_FRUIT,   /* get fruit for villager */
    mQst_CONTEST_KIND_SOCCER,  /* get ball for villager */
    mQst_CONTEST_KIND_SNOWMAN, /* build snowman for villager */
    mQst_CONTEST_KIND_FLOWER,  /* plant flowers for villager */
    mQst_CONTEST_KIND_FISH,    /* get fish for villager */
    mQst_CONTEST_KIND_INSECT,  /* get insect for villager */
    mQst_CONTEST_KIND_LETTER,  /* send letter to villager */

    mQst_CONTEST_KIND_NUM
};

enum {
    mQst_CONTEST_DATA_NONE,
    mQst_CONTEST_DATA_FLOWER,
    mQst_CONTEST_DATA_LETTER,

    mQst_CONTEST_DATA_NUM
};

/* sizeof(mQst_contest_info_u) == 4 */
typedef union quest_contest_info_s {
    struct {
        /* 0x00 */ u8 flowers_requested; /* number of flowers village requests be planted in acre */
    } flower_data;

    struct {
        /* 0x00 */ u8 score;              /* score rank of letter */
        /* 0x02 */ mActor_name_t present; /* present sent with letter */
    } letter_data;
} mQst_contest_info_u;

/* sizeof(mQst_contest_c) == 0x28 */
typedef struct quest_contest_s {
    /* 0x00 */ mQst_base_c base;             /* quest base struct */
    /* 0x0C */ mActor_name_t requested_item; /* item (if any) requested by the villager */
    /* 0x0E */ PersonalID_c player_id;       /* personal id of the player */
    /* 0x22 */ s8 type;                      /* type of quest, seems to be repeat of data in quest base */
    /* 0x24 */ mQst_contest_info_u info;     /* contest info for flower & letter quests */
} mQst_contest_c;

/* Delivery Quest */

enum {
    mQst_DELIVERY_KIND_NORMAL,  // standard delivery
    mQst_DELIVERY_KIND_FOREIGN, // delivered to a foreign animal
    mQst_DELIVERY_KIND_REMOVE,  // delivered to the animal who last left for another town
    mQst_DELIVERY_KIND_LOST,    // assumed, probably for when a delivery is 'undeliverable'

    mQst_DELIVERY_KIND_NUM
};

/* sizeof(mQst_delivery_c) == 0x28 */
typedef struct quest_delivery_s {
    /* 0x00 */ mQst_base_c base;          /* quest base info */
    /* 0x0C */ AnmPersonalID_c recipient; /* villager who will receive it */
    /* 0x1A */ AnmPersonalID_c sender;    /* villager who sent it */
} mQst_delivery_c;

/* Errand Quest */
#define mQst_ERRAND_FIRST_JOB_ANIMAL_NUM 2
#define mQst_ERRAND_CHAIN_ANIMAL_NUM 3

enum {
    mQst_ERRAND_REQUEST,
    mQst_ERRAND_REQUEST_CONTINUE,
    mQst_ERRAND_REQUEST_FINAL,

    mQst_ERRAND_FIRSTJOB_CHANGE_CLOTH,
    mQst_ERRAND_FIRSTJOB_PLANT_FLOWER,
    mQst_ERRAND_FIRSTJOB_DELIVER_FTR,
    mQst_ERRAND_FIRSTJOB_SEND_LETTER,
    mQst_ERRAND_FIRSTJOB_DELIVER_CARPET,
    mQst_ERRAND_FIRSTJOB_DELIVER_AXE,
    mQst_ERRAND_FIRSTJOB_POST_NOTICE,
    mQst_ERRAND_FIRSTJOB_SEND_LETTER2,
    mQst_ERRAND_FIRSTJOB_DELIVER_AXE2,
    mQst_ERRAND_FIRSTJOB_INTRODUCTIONS,
    mQst_ERRAND_FIRSTJOB_OPEN,
    mQst_ERRAND_FIRSTJOB_START,

    mQst_ERRAND_NUM
};

enum {
    mQst_ERRAND_TYPE_NONE,
    mQst_ERRAND_TYPE_CHAIN,
    mQst_ERRAND_TYPE_FIRST_JOB,

    mQst_ERRAND_TYPE_NUM
};

/* sizeof(mQst_first_job_c) == 0x20 */
typedef struct quest_first_job_s {
    /* 0x00 */ AnmPersonalID_c used_ids[mQst_ERRAND_FIRST_JOB_ANIMAL_NUM]; /* villagers already used for first job quest
                                                                              (furniture, then letter) */
    /* 0x1C */ u8 used_num : 7;                                            /* used count for 'used_ids' */
    /* 0x1C */ u8 wrong_cloth : 1; /* set to TRUE if player changes out of work uniform during chores */
} mQst_firstjob_c;

/* sizeof(mQst_errand_chain_c) == 0x2C */
typedef struct quest_errand_chain_s {
    /* 0x00 */ AnmPersonalID_c used_ids[mQst_ERRAND_CHAIN_ANIMAL_NUM];
    /* 0x2A */ u8 used_num;
} mQst_errand_chain_c;

/* sizeof(mQst_errand_info_u) == 0x2C */
typedef union {
    mQst_errand_chain_c chain;
    mQst_firstjob_c first_job;
} mQst_errand_info_u;

/* sizeof(mQst_errand_c) == 0x58 */
typedef struct quest_errand_s {
    /* 0x00 */ mQst_base_c base;          /* quest base info */
    /* 0x0C */ AnmPersonalID_c recipient; /* villager who will receive it */
    /* 0x1A */ AnmPersonalID_c sender;    /* villager who sent it */
    /* 0x28 */ mActor_name_t item;        /* errand item */
    /* 0x2A */ s8 pockets_idx : 5;        /* index in player pockets where the errand item is */
    /* 0x2A */ s8 errand_type : 3;        /* errand type */
    /* 0x2C */ mQst_errand_info_u info;   /* errand type-specific data */
} mQst_errand_c;

/* 'Not Saved' Quest */
typedef struct not_saved_quest_s {
    int work;
    u8 h;
} mQst_not_saved_c;

extern void mQst_ClearQuestInfo(mQst_base_c* quest);
extern void mQst_ClearDelivery(mQst_delivery_c* delivery, int num);
extern void mQst_ClearErrand(mQst_errand_c* errand, int num);
extern void mQst_ClearContest(mQst_contest_c* contest);
extern void mQst_ClearNotSaveQuest(mQst_not_saved_c* not_saved);
extern void mQst_CopyQuestInfo(mQst_base_c* dst, mQst_base_c* src);
extern void mQst_CopyDelivery(mQst_delivery_c* dst, mQst_delivery_c* src);
extern void mQst_CopyErrand(mQst_errand_c* dst, mQst_errand_c* src);
extern int mQst_CheckFreeQuest(mQst_base_c* quest);
extern int mQst_CheckLimitOver(mQst_base_c* quest);
extern int mQst_GetOccuredDeliveryIdx(int delivery_kind);
extern int mQst_ClearQuestbyPossessionIdx(int idx);
extern int mQst_CheckLimitbyPossessionIdx(int idx);
extern void mQst_ClearGrabItemInfo();
extern void mQst_CheckGrabItem(mActor_name_t item, int pocket_idx);
extern void mQst_CheckPutItem(mActor_name_t item, int pocket_idx);
extern int mQst_CheckNpcExistbyItemIdx(int idx, int sender_or_receipient);
extern int mQst_GetToFromName(u8* to_name, u8* from_name, int idx);
extern int mQst_GetOccuredContestIdx(int kind);
extern int mQst_GetFlowerSeedNum(int block_x, int block_z);
extern int mQst_GetFlowerNum(int block_x, int block_z);
extern int mQst_GetNullNoNum(int block_x, int block_z);
extern void mQst_SetItemNameStr(mActor_name_t item, int string_no);
extern void mQst_SetItemNameFreeStr(mActor_name_t item, int string_no);
extern int mQst_SendRemail(mQst_contest_c* contest, AnmPersonalID_c* sender_id);
extern void mQst_SetReceiveLetter(mQst_contest_c* contest, PersonalID_c* sender_id, u8* body, mActor_name_t present);
extern mQst_errand_c* mQst_GetFirstJobData();
extern int mQst_CheckFirstJobQuestbyItemIdx(int idx);
extern int mQst_CheckFirstJobFin(mQst_errand_c* errand);
extern int mQst_CheckRemoveTarget(mQst_errand_c* errand);
extern void mQst_SetFirstJobStart(mQst_errand_c* errand);
extern void mQst_SetFirstJobChangeCloth(mQst_errand_c* errand, mActor_name_t item);
extern void mQst_SetFirstJobSeed(mQst_errand_c* errand);
extern void mQst_SetFirstJobHello(mQst_errand_c* errand);
extern void mQst_SetFirstJobFurniture(mQst_errand_c* errand, AnmPersonalID_c* pid, mActor_name_t item, int slot);
extern void mQst_SetFirstJobLetter(mQst_errand_c* errand, AnmPersonalID_c* pid);
extern void mQst_SetFirstJobLetter2(mQst_errand_c* errand, AnmPersonalID_c* pid);
extern void mQst_SetFirstJobOpenQuest(mQst_errand_c* errand);
extern void mQst_SetFirstJobCarpet(mQst_errand_c* errand, AnmPersonalID_c* pid, mActor_name_t item, int slot);
extern void mQst_SetFirstJobAxe(mQst_errand_c* errand, AnmPersonalID_c* pid, mActor_name_t item, int slot);
extern void mQst_SetFirstJobAxe2(mQst_errand_c* errand, AnmPersonalID_c* pid, mActor_name_t item, int slot);
extern void mQst_SetFirstJobNotice(mQst_errand_c* errand);
extern int mQst_GetRandom(int max);
extern void mQst_GetGoods_common(mActor_name_t* item, AnmPersonalID_c* pid, int category, mActor_name_t* exist_table,
                                 int exist_num, int list);
extern int mQst_CheckSoccerTarget(ACTOR* actor);
extern void mQst_NextSoccer(ACTOR* actor);
extern void mQst_NextSnowman(xyz_t snowman_pos);
extern void mQst_BackSnowman(xyz_t snowman_pos);
extern void mQst_PrintQuestInfo(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
