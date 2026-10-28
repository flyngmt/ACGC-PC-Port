#ifndef M_NPC_H
#define M_NPC_H

#include "types.h"
#include "m_npc_personal_id.h"
#include "libu64/gfxprint.h"
#include "m_actor_type.h"
#include "m_land_h.h"
#include "m_mail.h"
#include "lb_rtc.h"
#include "m_personal_id.h"
#include "m_quest.h"
#include "m_lib.h"
#include "m_private_h.h"
#include "m_field_make.h"
#include "m_name_table.h"
#include "ac_npc_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mNpc_GET_IDX(npc_id) ((npc_id) & 0x0FFF)
#define mNpc_GET_TYPE(npc_id) ((npc_id) & 0xF000)
#define mNpc_IS_SPECIAL(npc_id) (mNpc_GET_TYPE(npc_id) == 0xD000)

#define ANIMAL_NUM_MIN 5
#define ANIMAL_NUM_MAX 15 /* Maximum number of villagers possible in town */
#define ANIMAL_MEMORY_NUM 7
#define ANIMAL_CATCHPHRASE_LEN 10
#define ANIMAL_HP_MAIL_NUM PLAYER_NUM
#define ANIMAL_NAME_LEN PLAYER_NAME_LEN
#define mNpc_MINIMUM_DAYS_BEFORE_FORCE_REMOVAL 10

#define mNpc_ISLAND_FTR_SAVE_NUM 4
#define mNpc_ISLAND_FTR_NUM 16
#define mNpc_EVENT_NPC_NUM 5
#define mNpc_MASK_NPC_NUM 3
#define mNpc_ISLANDER_NO ANIMAL_NUM_MAX

enum {
    mNpc_MOOD_0,
    mNpc_MOOD_1,
    mNpc_MOOD_2,
    mNpc_MOOD_3,
    mNpc_MOOD_4,
    mNpc_MOOD_5,
    mNpc_MOOD_6,
    mNpc_MOOD_7,
    mNpc_MOOD_8,

    mNpc_MOOD_NUM
};

enum {
    mNpc_LETTER_RANK_BAD,
    mNpc_LETTER_RANK_OK,

    mNpc_LETTER_RANK_NUM
};

enum {
    mNpc_EVENT_MAIL_VT_DAY, /* valentine's day */
    mNpc_EVENT_MAIL_WT_DAY, /* white day (JP only) */

    mNpc_EVENT_MAIL_NUM
};

enum {
    mNpc_EVENT_MAIL_BEST_FRIEND,
    mNpc_EVENT_MAIL_OK_FRIEND,
    mNpc_EVENT_MAIL_NOT_FRIEND,

    mNpc_EVENT_MAIL_FRIEND_NUM
};

enum {
    mNpc_GROW_STARTER,
    mNpc_GROW_MOVE_IN,
    mNpc_GROW_ISLANDER,

    mNpc_GROW_NUM
};

enum {
    mNpc_NAME_TYPE_SPNPC,
    mNpc_NAME_TYPE_NPC,

    mNpc_NAME_TYPE_NUM
};

enum {
    mNpc_FEEL_NORMAL,
    mNpc_FEEL_HAPPY,
    mNpc_FEEL_ANGRY,
    mNpc_FEEL_SAD,
    mNpc_FEEL_SLEEPY,
    mNpc_FEEL_PITFALL,

    mNpc_FEEL_NUM,

    mNpc_FEEL_6 = mNpc_FEEL_NUM,
    mNpc_FEEL_UZAI_0,
    mNpc_FEEL_UZAI_1,

    mNpc_FEEL_ALL_NUM
};

enum {
    mNpc_PATIENCE_MILDLY_ANNOYED,
    mNpc_PATIENCE_ANNOYED,
    mNpc_PATIENCE_NORMAL,

    mNpc_PATIENCE_NUM
};

/* sizeof(Anmremail_c) == 0x16 */
typedef struct animal_remail_s {
    lbRTC_ymd_c date;             /* date sent */
    u8 name[ANIMAL_NAME_LEN];     /* villager name */
    u8 land_name[LAND_NAME_SIZE]; /* town name */
    struct {
        u8 cond : 1;  /* was letter good or not */
        u8 looks : 7; /* personality */
    } flags;
} Anmremail_c;

/* sizeof(Anmplmail_c) == 0x104 */
typedef struct animal_player_maiL_s {
    /* 0x000 */ u8 font; /* 'font' to use for letter info */
    /* 0x001 */ u8 paper_type;
    /* 0x002 */ mActor_name_t present;
    /* 0x004 */ u8 header_back_start; /* position for name insertion in header */
    /* 0x005 */ u8 header[MAIL_HEADER_LEN];
    /* 0x01D */ u8 body[MAIL_BODY_LEN];
    /* 0x0DD */ u8 footer[MAIL_FOOTER_LEN];
    /* 0x0FD */ u8 pad0;          /* likely pad */
    /* 0x0FE */ lbRTC_ymd_c date; /* sent date */
} Anmplmail_c;

/* sizeof(Anmhome_c) == 5 */
typedef struct animal_home_s {
    /* 0x00 */ u8 type_unused; /* Likely the house type, but seems to be unused outside of SChk_Anmhome_c_sub */
    /* 0x01 */ u8 block_x;     /* acre x position */
    /* 0x02 */ u8 block_z;     /* acre y position */
    /* 0x03 */ u8 ut_x;        /* unit x position */
    /* 0x04 */ u8 ut_z;        /* unit z position */
} Anmhome_c;

/* sizeof(Anmlet_c) == 1 */
typedef struct animal_letter_info_s {
    u8 exists : 1;                /* letter received by villager and exists */
    u8 cond : 1;                  /* mNpc_LETTER_RANK_* */
    u8 send_reply : 1;            /* set when the villager should reply */
    u8 has_present_cloth : 1;     /* set when the villager's held present shirt is from this letter */
    u8 wearing_present_cloth : 1; /* set when a villager is wearing the shirt sent with the saved letter */
    u8 bit5_7 : 3;                /* seemingly unused */
} Anmlet_c;

/* sizeof(Anmlnd_c) == 0xA */
typedef struct animal_land_mem_s {
    /* 0x00 */ u8 name[LAND_NAME_SIZE];
    /* 0x08 */ u16 id;
} Anmlnd_c;

typedef struct island_animal_best_ftr_s {
    u32 check;
    u16 have_bitfield;
} Anm_bestFtr_c;

/* sizeof(memuni_u) == 0xC */
typedef union {
    Anmlnd_c land;        /* size = 0xA */
    Anm_bestFtr_c island; /* size = 6 */
} memuni_u;

/* sizeof(Anmmem_c) == 0x138 */
typedef struct animal_memory_s {
    /* 0x000 */ PersonalID_c memory_player_id; /* personal id of the player memory belongs to */
    /* 0x014 */ lbRTC_time_c last_speak_time;  /* time the player last spoke to this villager */
    /* 0x01C */ memuni_u memuni;               /* union between town NPC land memory & islander player action memory */
    /* 0x028 */ u64 saved_town_tune;           /* memory origin town tune */
    /* 0x030 */ s8 friendship;                 /* friendship with the player */
    /* 0x031 */ Anmlet_c letter_info;          /* saved letter flags */
    /* 0x032 */ Anmplmail_c letter;            /* saved letter */
} Anmmem_c;

/* sizeof(anmuni) == 8 */
typedef union {
    u8 previous_land_name[LAND_NAME_SIZE];
    mActor_name_t island_ftr[mNpc_ISLAND_FTR_SAVE_NUM];
} anmuni_u;

/* sizeof(AnmHPMail_c) == 0x1C */
typedef struct animal_password_mail_s {
    /* 0x00 */ lbRTC_time_c receive_time;
    /* 0x08 */ u8 password[20]; /* TODO: this should not be a hardcoded length */
} AnmHPMail_c;

/* sizeof(Animal_c) == 0x988 */
typedef struct animal_s {
    /* 0x000 */ AnmPersonalID_c id;                     /* this villager's ID */
    /* 0x010 */ Anmmem_c memories[ANIMAL_MEMORY_NUM];   /* memories of players who've spoken to this villager */
    /* 0x898 */ Anmhome_c home_info;                    /* home position info */
    /* 0x89D */ u8 catchphrase[ANIMAL_CATCHPHRASE_LEN]; /* may be called 'word_ending' */
    /* 0x8A8 */ mQst_contest_c contest_quest;           /* current contest quest information */
    /* 0x8D0 */ u8
        parent_name[PLAYER_NAME_LEN]; /* name of the player who 'spawned' the villager in, unsure why this is tracked */
    /* 0x8D8 */ anmuni_u anmuni;      /* name of the last town the villager lived in or saved island ftr */
    /* 0x8E0 */ u16 previous_land_id; /* id of the previous town the villager lived in */
    /* 0x8E2 */ u8 mood;              /* probably called 'feel' based on code */
    /* 0x8E3 */ u8 mood_time;         /* probably called 'feel_tim' based on code */
    /* 0x8E4 */ mActor_name_t cloth;  /* shirt the villager is wearing */
    /* 0x8E6 */ u16 remove_info;      /* info about villager moving between towns? kinda stubbed */
    /* 0x8E8 */ u8 is_home;           /* TRUE when the villager is home, otherwise FALSE */
    /* 0x8E9 */ u8
        moved_in; /* TRUE when the villager moved in after town creation, FALSE if they started out in town */
    /* 0x8EA */ u8 removing; /* TRUE when the villager is leaving town, FALSE otherwise */
    /* 0x8EB */ u8
        cloth_original_id; /* 0xFF when not wearing an Able Sister's pattern, otherwise 0-3 indicating which pattern */
    /* 0x8EC */ u8 umbrella_id; /* 0xFF when no umbrella, 0-31 when a standard umbrella, 32-35 when using an Able
                                   Sister's pattern */
    /* 0x8ED */ u8 unk_8ED;     /* Exists according to mISL_gc_to_agb_animal, but seems unused in practice */
    /* 0x8EE */ mActor_name_t
        present_cloth; /* The most recently received shirt from a letter which the villager may change into */
    /* 0x8F0 */ u8 animal_relations[ANIMAL_NUM_MAX]; /* relationships between all villagers in town, starts at 128 which
                                                        is neutral */
    /* 0x900 */ AnmHPMail_c hp_mail[ANIMAL_HP_MAIL_NUM]; /* mail password info storage */
    /* 0x000 */ u8 unused[24];                           /* unknown usage/unused */
} Animal_c;

/*
  Struct for keeping track of an event where a villager can briefly return to your town after
  moving away to another town. The time limit seems to be 60 days, and the villager will only
  appear once per player during that time if the player talks to them.
*/

/* sizeof(Anmret_c) == 0xC */
typedef struct animal_return_s {
    /* 0x00 */ mActor_name_t npc_id;    /* id of the villager who left */
    /* 0x02 */ u8 talk_bit;             /* which players have already interacted with this villager */
    /* 0x03 */ u8 exist;                /* if the villager exists */
    /* 0x04 */ lbRTC_time_c renew_time; /* time that this struct was updated */
} Anmret_c;

typedef struct demo_npc_s {
    mActor_name_t npc_name; /* villager id, E0XX */
    u32 block_x, block_z;   /* spawn acre */
    u32 ut_x, ut_z;         /* spawn unit in acre */
} mNpc_demo_npc_c;

typedef struct {
    u8 type;
    u8 palette;
    u8 wall_id;
    u8 floor_id;
    mActor_name_t main_layer_id;
    mActor_name_t secondary_layer_id;
} mNpc_NpcHouseData_c;

typedef struct npc_conversation_s {
    u8 beesting : 1;        // talk to player about their beesting
    u8 fish_complete : 1;   // talk to the player about catching all fish
    u8 insect_complete : 1; // talk to the player about catching all insects
    u8 unk : 5;
} mNpc_NpcConversation_c;

typedef struct npc_list_s {
    mActor_name_t name;
    mActor_name_t field_name;
    xyz_t house_position;
    xyz_t position;
    u8 appear_flag;
    mNpc_NpcConversation_c conversation_flags;
    mQst_base_c quest_info;
    mNpc_NpcHouseData_c house_data;
    mActor_name_t reward_furniture;
} mNpc_NpcList_c;

typedef struct event_npc_s {
    mActor_name_t event_id;   /* event NPC id */
    mActor_name_t texture_id; /* real NPC id which is used for texture data */
    mActor_name_t npc_id;     /* non-texture NPC id used for other NPC data */
    mActor_name_t cloth_id;   /* cloth texture id */
    u8 exists;                /* has the actor been spawned yet? */
    u8 in_use;                /* is this event npc structure being used? */
    u16 _A;                   /* exists based on size of structure, seems unused */
} mNpc_EventNpc_c;

typedef struct mask_npc_s {
    mActor_name_t mask_id;  /* 'mask' actor id */
    mActor_name_t npc_id;   /* NPC actor id whose data will be used */
    mActor_name_t cloth_id; /* cloth actor id */
    u8 exists;              /* has the actor been spawned yet? */
    u8 in_use;              /* is this mask npc structure being used? */
    Animal_c animal_data;   /* animal data is copied if the mask npc is a standard villager NPC */
} mNpc_MaskNpc_c;

typedef struct npc_default_data_s {
    mActor_name_t cloth;
    u16 catchphrase_str_idx;
    s8 umbrella;
} mNpc_Default_Data_c;

extern void mNpc_AddNowNpcMax(u8* npc_max);
extern void mNpc_SubNowNpcMax(u8* npc_max);
extern void mNpc_ClearAnimalPersonalID(AnmPersonalID_c* pid);
extern int mNpc_CheckFreeAnimalPersonalID(AnmPersonalID_c* pid);
extern void mNpc_CopyAnimalPersonalID(AnmPersonalID_c* dst, AnmPersonalID_c* src);
extern int mNpc_CheckCmpAnimalPersonalID(AnmPersonalID_c* pid0, AnmPersonalID_c* pid1);
extern int mNpc_GetAnimalNum();
extern int mNpc_CheckRemoveExp(Animal_c* animal);
extern int mNpc_GetRemoveTime(Animal_c* animal);
extern void mNpc_AddRemoveTime(Animal_c* animal);
extern void mNpc_SetRemoveExp(Animal_c* animal, u16 remove_exp);
extern void mNpc_SetRemoveExp(Animal_c* animal, u16 remove_exp);
extern void mNpc_SetParentName(Animal_c* animal, PersonalID_c* parent_id);
extern void mNpc_SetParentNameAllAnimal();
extern void mNpc_ClearAnimalMail(Anmplmail_c* mail);
extern void mNpc_CopyAnimalMail(Anmplmail_c* dst, Anmplmail_c* src);
extern void mNpc_ClearAnimalMemory(Anmmem_c* memory, int num);
extern void mNpc_ClearIslandAnimalMemory(Anmmem_c* memory, int num);
extern void mNpc_CopyAnimalMemory(Anmmem_c* dst, Anmmem_c* src);
extern void mNpc_AddFriendship(Anmmem_c* memory, int amount);
extern int mNpc_CheckFreeAnimalMemory(Anmmem_c* memory);
extern void mNpc_RenewalAnimalMemory();
extern int mNpc_GetOldAnimalMemoryIdx(Anmmem_c* memory, int num);
extern int mNpc_GetFreeAnimalMemoryIdx(Anmmem_c* memory, int num);
extern int mNpc_GetOldPlayerAnimalMemoryIdx(Anmmem_c* memory, int num);
extern int mNpc_ForceGetFreeAnimalMemoryIdx(Animal_c* animal, Anmmem_c* memory, int num);
extern void mNpc_SetAnimalMemory(PersonalID_c* pid, AnmPersonalID_c* anm_id, Anmmem_c* memory);
extern int mNpc_GetAnimalMemoryIdx(PersonalID_c* pid, Anmmem_c* memory, int num);
extern void mNpc_SetAnimalLastTalk(Animal_c* animal);
extern void mNpc_SetAnimalPersonalID2Memory(AnmPersonalID_c* anm_id);
extern int mNpc_GetHighestFriendshipIdx(Anmmem_c* memory, int num);
extern int mNpc_GetAnimalMemoryBestFriend(Anmmem_c* memory, int num);
extern int mNpc_GetAnimalMemoryNum(Anmmem_c* memory, int count);
extern int mNpc_GetAnimalMemoryLetterNum(Anmmem_c* memory, int count);
extern int mNpc_GetAnimalMemoryLandKindNum(Anmmem_c* memory, int count);
extern void mNpc_ClearAnimalInfo(Animal_c* animal);
extern void mNpc_ClearIslandAnimalInfo(Animal_c* animal);
extern void mNpc_ClearAnyAnimalInfo(Animal_c* animal, int count);
extern int mNpc_CheckFreeAnimalInfo(Animal_c* animal);
extern int mNpc_GetFreeAnimalInfo(Animal_c* animal, int count);
extern int mNpc_UseFreeAnimalInfo(Animal_c* animal, int count);
extern void mNpc_CopyAnimalInfo(Animal_c* dst, Animal_c* src);
extern int mNpc_SearchAnimalinfo(Animal_c* animal, mActor_name_t npc_id, int count);
extern Animal_c* mNpc_GetAnimalInfoP(mActor_name_t npc_id);
extern int mNpc_SearchAnimalPersonalID(AnmPersonalID_c* anm_pid);
extern AnmPersonalID_c* mNpc_GetOtherAnimalPersonalIDOtherBlock(AnmPersonalID_c* exclude_pids, int count, int bx,
                                                                int bz, int check_flag);
extern AnmPersonalID_c* mNpc_GetOtherAnimalPersonalID(AnmPersonalID_c* pids, int count);
extern void mNpc_SetAnimalThisLand(Animal_c* animal, int count);
extern int mNpc_GetSameLooksNum(u8 looks);
extern int mNpc_CheckNpcExistBlock(int idx, int check_bx, int check_bz);
extern void mNpc_Mail2AnimalMail(Anmplmail_c* animal_mail, Mail_c* mail);
extern void mNpc_AnimalMail2Mail(Mail_c* mail, Anmplmail_c* animal_mail, PersonalID_c* pid, AnmPersonalID_c* anm_id);
extern int mNpc_CheckNormalMail_sub(int* char_num, u8* body);
extern u8 mNpc_CheckNormalMail_length(int* len, u8* body);
extern u8 mNpc_CheckNormalMail_nes(u8* body);
extern int mNpc_SendMailtoNpc(Mail_c* mail);
extern void mNpc_ClearRemail(Anmremail_c* remail);
extern void mNpc_Remail();
extern u8 mNpc_GetPaperType();
extern int mNpc_SendVtdayMail();
extern int mNpc_CheckFriendship(PersonalID_c* pid, Animal_c* animal);
extern int mNpc_SendEventBirthdayCard(PersonalID_c* pid);
extern int mNpc_SendEventBirthdayCard2(PersonalID_c* pid, int player_no);
extern int mNpc_SendEventXmasCard(PersonalID_c* pid, int player_no);
extern int mNpc_GetPresentClothMemoryIdx(Anmmem_c* memory);
extern int mNpc_GetPresentClothMemoryIdx_rnd(Anmmem_c* memory);
extern int mNpc_CheckTalkPresentCloth(Animal_c* animal);
extern void mNpc_ChangePresentCloth();
extern u8* mNpc_GetWordEnding(ACTOR* actor);
extern void mNpc_ResetWordEnding(NPC_ACTOR* nactorx);
extern int mNpc_GetFreeEventNpcIdx();
extern int mNpc_RegistEventNpc(mActor_name_t event_id, mActor_name_t texture_id, mActor_name_t npc_id,
                               mActor_name_t cloth_id);
extern void mNpc_UnRegistEventNpc(mNpc_EventNpc_c* npc);
extern void mNpc_ClearEventNpc();
extern mNpc_EventNpc_c* mNpc_GetSameEventNpc(mActor_name_t event_id);
extern int mNpc_GetFreeMaskNpcIdx();
extern int mNpc_RegistMaskNpc(mActor_name_t mask_id, mActor_name_t npc_id, mActor_name_t cloth_id);
extern void mNpc_UnRegistMaskNpc(mNpc_MaskNpc_c* npc);
extern void mNpc_ClearMaskNpc();
extern mNpc_MaskNpc_c* mNpc_GetSameMaskNpc(mActor_name_t mask_id);
extern u8 mNpc_GetLooks(mActor_name_t npc_id);
extern void mNpc_SetDefAnimalCloth(Animal_c* animal);
extern void mNpc_SetDefAnimalUmbrella(Animal_c* animal);
extern void mNpc_SetDefAnimal(Animal_c* animal, mActor_name_t npc_id, mNpc_Default_Data_c* def_data);
extern void mNpc_SetAnimalTitleDemo(mNpc_demo_npc_c* demo_npc, Animal_c* animal, GAME* game);
extern int mNpc_GetReservedUtNum(int* ut_x, int* ut_z, mActor_name_t* item);
extern int mNpc_BlockNum2ReservedUtNum(int* ut_x, int* ut_z, int bx, int bz);
extern void mNpc_MakeReservedListBeforeFieldct(Anmhome_c* reserved, int reserved_num, u8* reserved_count);
extern void mNpc_MakeReservedListAfterFieldct(Anmhome_c* reserved, int reserved_num, u8* reserved_count, u8 bx_max,
                                              u8 bz_max);
extern void mNpc_InitNpcData();
extern void mNpc_InitNpcList(mNpc_NpcList_c* npclist, int count);
extern void mNpc_SetNpcList(mNpc_NpcList_c* npclist, Animal_c* animal, int count, int malloc_flag);
extern void mNpc_SetNpcinfo(ACTOR* actor, s8 npc_info_idx);
extern void mNpc_AddNpc_inBlock(mFM_move_actor_c* move_actor_list, u8 bx, u8 bz);
extern void mNpc_RenewalNpcRoom(s16* wall_floor);
extern void mNpc_RenewalSetNpc(ACTOR* actor);
extern int mNpc_GetFriendAnimalNum(PersonalID_c* pid);
extern int mNpc_CheckFriendAllAnimal(PersonalID_c* pid);
extern void mNpc_SetNpcFurnitureRandom(mFM_fg_data_c** fg_data_table, int fg_base_id);
extern mActor_name_t mNpc_GetNpcFurniture(AnmPersonalID_c* anm_id);
extern void mNpc_ClearInAnimal();
extern Animal_c* mNpc_GetInAnimalP();
extern void mNpc_SetRemoveAnimalNo(u8* remove_animal_no, Animal_c* animal, int ignored_idx);
extern int mNpc_GetGoodbyAnimalIdx(int ignored_idx);
extern void mNpc_FirstClearGoodbyMail();
extern void mNpc_SendRegisteredGoodbyMail();
extern void mNpc_GetRemoveAnimal(Animal_c* transferring_animal, int moving_out);
extern void mNpc_SetReturnAnimal(Animal_c* return_animal);
#ifdef TARGET_PC
extern void mNpc_CopyRemoveAnimal(Animal_c* transferring_animal);
extern void mNpc_FinishRemoveAnimal(Animal_c* transferring_animal);
#endif
extern void mNpc_AddActor_inBlock(mFM_move_actor_c* move_actor_list, u8 bx, u8 bz);
extern void mNpc_LoadNpcNameString(u8* dst, u8 name_id);
extern void mNpc_GetNpcWorldNameTableNo(u8* dst, mActor_name_t npc_id);
extern void mNpc_ClearCacheName();
extern void mNpc_GetNpcWorldNameAnm(u8* dst, AnmPersonalID_c* anm_id);
extern void mNpc_GetActorWorldName(u8* dst, mActor_name_t npc_id);
extern u8* mNpc_GetNpcWorldNameP(mActor_name_t npc_id);
extern void mNpc_GetNpcWorldName(u8* dst, ACTOR* actor);
extern void mNpc_GetRandomAnimalName(u8* dst);
extern void mNpc_GetAnimalPlateName(u8* dst, xyz_t wpos);
extern int mNpc_GetNpcLooks(ACTOR* actor);
extern int mNpc_GetLooks2Sex(int looks);
extern int mNpc_GetAnimalSex(Animal_c* animal);
extern int mNpc_GetNpcSex(ACTOR* actor);
extern int mNpc_GetNpcSoundSpec(ACTOR* actor);
extern void mNpc_InitNpcAllInfo(int malloc_flag);
extern void mNpc_Grow();
extern void mNpc_ForceRemove();
extern int mNpc_DecideMaskNpc_summercamp(mActor_name_t* npc_id);
extern int mNpc_RegistMaskNpc_summercamp(mActor_name_t mask_id, mActor_name_t npc_id, mActor_name_t cloth_id);
extern int mNpc_CheckNpcSet_fgcol(mActor_name_t fg_item, u32 attribute);
extern int mNpc_CheckNpcSet(int bx, int bz, int ut_x, int ut_z);
extern int mNpc_GetMakeUtNuminBlock_hard_area(int* ut_x, int* ut_z, int bx, int bz, int restrict_area);
extern int mNpc_GetMakeUtNuminBlock_area(int* ut_x, int* ut_z, int bx, int bz, int restrict_area);
extern int mNpc_GetMakeUtNuminBlock(int* ut_x, int* ut_z, int bx, int bz);
extern int mNpc_GetMakeUtNuminBlock33(int* make_ut_x, int* make_ut_z, int ut_x, int ut_z, int bx, int bz);
extern int mNpc_GetMakeUtNuminBlock_hide_hard_area(int* ut_x, int* ut_z, int bx, int bz, int restrict_area);
extern void mNpc_ClearTalkInfo();
extern int mNpc_CheckOverImpatient(int animal_idx, int looks);
extern int mNpc_GetOverImpatient(int animal_idx, int looks);
extern int mNpc_CheckQuestRequest(int animal_idx);
extern void mNpc_SetQuestRequestOFF(int animal_idx, int looks);
extern void mNpc_TalkInfoMove();
extern void mNpc_TalkEndMove(int animal_idx, int feel);
extern int mNpc_GetNpcFloorNo();
extern int mNpc_GetNpcWallNo();
extern void mNpc_SetTalkBee();
extern u8 mNpc_GetFishCompleteTalk(mNpc_NpcList_c* npclist);
extern u8 mNpc_GetInsectCompleteTalk(mNpc_NpcList_c* npclist);
extern void mNpc_SetFishCompleteTalk(mNpc_NpcList_c* npclist);
extern void mNpc_SetInsectCompleteTalk(mNpc_NpcList_c* npclist);
extern void mNpc_SetNpcHomeYpos();
extern void mNpc_DecideIslandNpc(Animal_c* animal);
extern void mNpc_SetIslandRoomFtr(Animal_c* animal);
extern void mNpc_SetIslandGetFtr(mActor_name_t ftr);
extern void mNpc_SetIslandGetFtrtoRoom();
extern void mNpc_SetIslandGetLetter(int get);
extern int mNpc_GetIslandGetLetter();
extern void mNpc_SetIslandCheckFtrMsg(int set);
extern int mNpc_GetIslandCheckFtrMsg();
extern void mNpc_ClearIslandNpcRoomData();
extern void mNpc_IslandNpcRoomDataSet(mFM_fg_data_c** data_table, int base_idx);
extern mActor_name_t* mNpc_GetIslandRoomP(mActor_name_t npc_id);
extern void mNpc_GetIslandWallFloorIdx(int* wall, int* floor, mActor_name_t npc_id);
extern int mNpc_CheckIslandNpcRoomFtrItemNo_keep(mActor_name_t ftr);
extern void mNpc_ChangeIslandRoom(mActor_name_t* items);
extern int mNpc_CheckFtrIsIslandBestFtr(mActor_name_t ftr);
extern int mNpc_CheckFtrIsIslandNormalFtr(mActor_name_t ftr);
extern int mNpc_SetIslandFtr(PersonalID_c* pid, mActor_name_t ftr);
extern int mNpc_EraseIslandFtr(mActor_name_t ftr);
extern int mNpc_EraseIslandFtr_keep(mActor_name_t ftr);
extern void mNpc_ClearIslandPresentFtrInfo();
extern void mNpc_SetIslandPresentFtr();
extern void mNpc_RestoreIslandPresentFtr();
extern int mNpc_GetIslandRoomFtrNum();
extern int mNpc_CheckIslandPresentFtrIs();
extern mActor_name_t mNpc_GetIslandPresentFtr();
extern PersonalID_c* mNpc_GetIslandPresentFtrPersonalID();
extern mActor_name_t mNpc_GetRandomBestFtr();
extern Anmmem_c* mNpc_GetOtherBestFtr(PersonalID_c* pid, mActor_name_t* other_best_ftr, mActor_name_t exist_ftr);
extern mActor_name_t mNpc_GetPlayerBestFtr(PersonalID_c* pid, mActor_name_t exist_ftr);
extern mActor_name_t mNpc_GetPlayerFtr(PersonalID_c* pid);
extern int mNpc_CheckIslandAnimal(Animal_c* animal);
extern u32 mNpc_GetMDIdx(mActor_name_t npc_id);
extern u32 mNpc_GetIslandMDIdx();
extern void mNpc_ClearHPMail(AnmHPMail_c* hp_mail, int count);
extern void mNpc_AllClearHPMailPlayerIdx(int player_no);
extern int mNpc_ReceiveHPMail(Mail_c* mail);
extern void mNpc_SendHPMail();
extern void mNpc_PrintRemoveInfo(gfxprint_t* gfxprint);
extern void mNpc_set_addd_bit(int bit);
extern void mNpc_set_addd_edit_bit(int bit);
extern void mNpc_set_addd_edit_info(int mtype, int disp_add);
extern void mNpc_SetTalkAnimalIdx_fdebug(AnmPersonalID_c* anm_id);
extern void mNpc_PrintFriendship_fdebug(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
