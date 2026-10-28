#include "m_npc.h"

#include "m_font.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_mail_check.h"
#include "m_mail_check_ovl.h"
#include "m_handbill.h"
#include "m_string.h"
#include "m_shop.h"
#include "m_house.h"
#include "m_event_map_npc.h"
#include "ac_my_room.h"
#include "m_mail_password_check.h"
#include "libultra/libultra.h"
#include "jsyswrap.h"
#include "ac_npc.h"

static int mNpc_CheckIslandAnimalID(AnmPersonalID_c* anm_id);

extern mNpc_Default_Data_c npc_def_list[];
extern s8 npc_grow_list[];
extern mNpc_NpcHouseData_c npc_house_list[];

typedef struct sp_actor_name_data_s {
    mActor_name_t sp_npc_id;
    u16 sex;
    int name_str_no;
    int sound_id;
} mNpc_Sp_Npc_Name_c;

static mNpc_Sp_Npc_Name_c l_sp_actor_name[] = {
    // Tom Nook
    { SP_NPC_SHOP_MASTER, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_SHOP_MASTERSP, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_SHOP_MASTERSP_2, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_SHOP_MASTERSP_3, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_SHOP_MASTERSP_4, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_CONV_MASTER, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_SUPER_MASTER, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_DEPART_MASTER, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_RCN_GUIDE, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_RCN_GUIDE2, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_RCN_GUIDE_1, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_RCN_GUIDE2_1, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_RCN_GUIDE_2, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_RCN_GUIDE2_2, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_RCN_GUIDE_3, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_RCN_GUIDE2_3, mPr_SEX_MALE, 0x205, 2 },
    // Redd
    { SP_NPC_BROKER, mPr_SEX_MALE, 0x206, 2 },
    { SP_NPC_EV_BROKER2, mPr_SEX_MALE, 0x206, 2 },
    { SP_NPC_EV_YOMISE, mPr_SEX_MALE, 0x206, 2 },
    { SP_NPC_EV_YOMISE2, mPr_SEX_MALE, 0x206, 2 },
    // Katrina
    { SP_NPC_GYPSY, mPr_SEX_FEMALE, 0x207, 2 },
    { SP_NPC_EV_MIKO, mPr_SEX_FEMALE, 0x207, 2 },
    // Saharah
    { SP_NPC_CARPETPEDDLER, mPr_SEX_MALE, 0x208, 2 },
    // Wendell
    { SP_NPC_ARTIST, mPr_SEX_MALE, 0x209, 3 },
    // Jingle
    { SP_NPC_SANTA, mPr_SEX_MALE, 0x20A, 2 },
    // Gracie
    { SP_NPC_DESIGNER, mPr_SEX_MALE, 0x20B, 2 },
    // Joan
    { SP_NPC_KABUPEDDLER, mPr_SEX_FEMALE, 0x20C, 8 },
    // Pelly
    { SP_NPC_POST_GIRL, mPr_SEX_FEMALE, 0x20D, 4 },
    // Phyllis
    { SP_NPC_POST_GIRL2, mPr_SEX_FEMALE, 0x20E, 4 },
    // Pete
    { SP_NPC_POST_MAN, mPr_SEX_MALE, 0x20F, 3 },
    // Copper
    { SP_NPC_POLICE, mPr_SEX_MALE, 0x210, 2 },
    // Booker
    { SP_NPC_POLICE2, mPr_SEX_MALE, 0x6D9, 3 },
    // Copper
    { SP_NPC_EV_TAISOU_0, mPr_SEX_MALE, 0x210, 2 },
    // Porter
    { SP_NPC_STATION_MASTER, mPr_SEX_MALE, 0x211, 2 },
    // Jack
    { SP_NPC_HALLOWEEN, mPr_SEX_MALE, 0x212, 3 },
    // Gyroid
    { ACTOR_PROP_HANIWA0, mPr_SEX_OTHER, 0x213, 2 },
    { ACTOR_PROP_HANIWA1, mPr_SEX_OTHER, 0x213, 2 },
    { ACTOR_PROP_HANIWA2, mPr_SEX_OTHER, 0x213, 2 },
    { ACTOR_PROP_HANIWA3, mPr_SEX_OTHER, 0x213, 2 },
    // K.K. Slider
    { SP_NPC_P_SEL, mPr_SEX_OTHER, 0x214, 2 },
    { SP_NPC_TOTAKEKE, mPr_SEX_OTHER, 0x214, 2 },
    { SP_NPC_RTC, mPr_SEX_OTHER, 0x214, 2 },
    // Rover
    { SP_NPC_GUIDE, mPr_SEX_MALE, 0x215, 2 },
    { SP_NPC_GUIDE2, mPr_SEX_MALE, 0x215, 2 },
    // Chip
    { SP_NPC_ANGLER, mPr_SEX_MALE, 0x216, 2 },
    // Timmy
    { SP_NPC_MAMEDANUKI0, mPr_SEX_MALE, 0x217, 2 },
    // Tommy
    { SP_NPC_MAMEDANUKI1, mPr_SEX_MALE, 0x218, 2 },
    // Resetti
    { SP_NPC_MAJIN, mPr_SEX_MALE, 0x4E0, 2 },
    { SP_NPC_MAJIN2, mPr_SEX_MALE, 0x4E0, 2 },
    { SP_NPC_MAJIN3, mPr_SEX_MALE, 0x4E0, 2 },
    { SP_NPC_MAJIN4, mPr_SEX_MALE, 0x4E0, 2 },
    { SP_NPC_MAJIN5, mPr_SEX_MALE, 0x4E0, 2 },
    { SP_NPC_MAJIN_D07C, mPr_SEX_MALE, 0x4E0, 2 },
    { SP_NPC_MAJIN_D07D, mPr_SEX_MALE, 0x4E0, 2 },
    // Don
    { SP_NPC_MAJIN_BROTHER, mPr_SEX_MALE, 0x6D8, 2 },
    // Resetti
    { SP_NPC_MAJIN_D080, mPr_SEX_MALE, 0x4E0, 2 },
    { SP_NPC_EV_MAJIN, mPr_SEX_MALE, 0x4E0, 2 },
    // Gulliver
    { SP_NPC_EV_DOZAEMON, mPr_SEX_MALE, 0x4E1, 2 },
    // Snowman
    { ETC_SNOWMAN_BALL_A, mPr_SEX_MALE, 0x4E2, 2 },
    { ETC_SNOWMAN_BALL_B, mPr_SEX_MALE, 0x4E2, 2 },
    { SNOWMAN0, mPr_SEX_MALE, 0x4E2, 2 },
    { SNOWMAN1, mPr_SEX_MALE, 0x4E2, 2 },
    { SNOWMAN2, mPr_SEX_MALE, 0x4E2, 2 },
    { SNOWMAN3, mPr_SEX_MALE, 0x4E2, 2 },
    { SNOWMAN4, mPr_SEX_MALE, 0x4E2, 2 },
    { SNOWMAN5, mPr_SEX_MALE, 0x4E2, 2 },
    { SNOWMAN6, mPr_SEX_MALE, 0x4E2, 2 },
    { SNOWMAN7, mPr_SEX_MALE, 0x4E2, 2 },
    { SNOWMAN8, mPr_SEX_MALE, 0x4E2, 2 },
    // Tortimer
    { SP_NPC_EV_SONCHO, mPr_SEX_MALE, 0x4E3, 2 },
    { SP_NPC_EV_SONCHO2, mPr_SEX_MALE, 0x4E3, 2 },
    { SP_NPC_SONCHO_D078, mPr_SEX_MALE, 0x4E3, 2 },
    { SP_NPC_SONCHO_D079, mPr_SEX_MALE, 0x4E3, 2 },
    { SP_NPC_SONCHO, mPr_SEX_MALE, 0x4E3, 2 },
    { SP_NPC_EV_SPEECH_SONCHO, mPr_SEX_MALE, 0x4E3, 2 },
    // Blathers
    { SP_NPC_CURATOR, mPr_SEX_MALE, 0x4E4, 2 },
    // Mabel
    { SP_NPC_NEEDLEWORK0, mPr_SEX_FEMALE, 0x4E5, 4 },
    // Sabel
    { SP_NPC_NEEDLEWORK1, mPr_SEX_FEMALE, 0x4E6, 4 },
    // Kapp'n
    { SP_NPC_SENDO, mPr_SEX_MALE, 0x4E7, 2 },
    // Wisp
    { SP_NPC_EV_GHOST, mPr_SEX_MALE, 0x4E8, 2 },
    // Blanca
    { SP_NPC_MASK_CAT, mPr_SEX_MALE, 0x4E9, 4 },
    { SP_NPC_MASK_CAT2, mPr_SEX_MALE, 0x4E9, 4 },
    // Franklin
    { SP_NPC_TURKEY, mPr_SEX_MALE, 0x6DA, 2 },
    // Farley
    { SP_NPC_HEM, mPr_SEX_MALE, 0x6DB, 9 }
};

static u8 l_no_name_npc_name[ANIMAL_NAME_LEN] = { 0xD4, 0x8E, 0xA6, 0x90, 0x85, 0x42 }; // never translated
static u8 l_no_ending_npc_ending[ANIMAL_CATCHPHRASE_LEN] = { 0xD3, 0xAF, 0x9D, 0x20 };  // never translated

static void mNpc_MakeRandTable(int* table, int count, int swap_num) {
    int a;
    int b;
    int i;
    f32 c = count;

    for (i = 0; i < count; i++) {
        table[i] = i;
    }

    while (swap_num--) {
        int temp;

        a = RANDOM_F(c);
        b = RANDOM_F(c);
        temp = table[a];

        table[a] = table[b];
        table[b] = temp;
    }
}

static void mNpc_ClearBufSpace1(u8* buf, int size) {
    mem_clear(buf, size, CHAR_SPACE);
}

extern void mNpc_AddNowNpcMax(u8* npc_max) {
    if (npc_max[0] < ANIMAL_NUM_MAX) {
        npc_max[0]++;
    }
}

extern void mNpc_SubNowNpcMax(u8* npc_max) {
    if (npc_max[0] > ANIMAL_NUM_MIN) {
        npc_max[0]--;
    }
}

extern void mNpc_ClearAnimalPersonalID(AnmPersonalID_c* pid) {
    pid->npc_id = EMPTY_NO;
    pid->name_id = 0xFF;
    pid->land_id = 0xFFFF;
    pid->looks = mNpc_LOOKS_UNSET;
    mNPS_reset_schedule_area(pid);
    mLd_ClearLandName(pid->land_name);
}

extern int mNpc_CheckFreeAnimalPersonalID(AnmPersonalID_c* pid) {
    int res = FALSE;

    if ((pid->npc_id == EMPTY_NO && pid->name_id == 0xFF) || (ITEM_NAME_GET_TYPE(pid->npc_id) != NAME_TYPE_NPC)) {
        res = TRUE;
    }

    return res;
}

extern void mNpc_CopyAnimalPersonalID(AnmPersonalID_c* dst, AnmPersonalID_c* src) {
    if (src != NULL && ITEM_NAME_GET_TYPE(src->npc_id) == NAME_TYPE_NPC) {
        dst->npc_id = src->npc_id;
        dst->name_id = src->name_id;
        dst->land_id = src->land_id;
        dst->looks = src->looks;
        mLd_CopyLandName(dst->land_name, src->land_name);
    }
}

extern int mNpc_CheckCmpAnimalPersonalID(AnmPersonalID_c* pid0, AnmPersonalID_c* pid1) {
    int res = FALSE;

    if ((pid0 != NULL && pid1 != NULL) && (pid0->npc_id == pid1->npc_id) && (pid0->name_id == pid1->name_id) &&
        (pid0->land_id == pid1->land_id) && mLd_CheckCmpLandName(pid0->land_name, pid1->land_name) == TRUE) {
        res = TRUE;
    }

    return res;
}

extern int mNpc_GetAnimalNum() {
    Animal_c* animal = Save_Get(animals);
    int num = 0;
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            num++;
        }

        animal++;
    }

    return num;
}

extern int mNpc_CheckRemoveExp(Animal_c* animal) {
    return (animal->remove_info >> 13) & 0b111;
}

extern int mNpc_GetRemoveTime(Animal_c* animal) {
    return animal->remove_info & 0x1FFF;
}

/* @unused */
extern void mNpc_AddRemoveTime(Animal_c* animal) {
    if ((animal->remove_info & 0x1FFF) < 0x1FFF) {
        animal->remove_info++;
    }
}

/* @unused */
#ifdef MUST_MATCH
extern void mNpc_SetRemoveExp(Animal_c* animal, u16 remove_exp) {
    animal->remove_info = ((((animal->remove_info >> 13) & 0b111) >> 13) | remove_exp)
                          << 13; // what the... "official" impl from DnM
}
#else
extern void mNpc_SetRemoveExp(Animal_c* animal, u16 remove_exp) {
    animal->remove_info |= (remove_exp & 0b111) << 13;
}
#endif

extern void mNpc_SetParentName(Animal_c* animal, PersonalID_c* parent_id) {
    if (parent_id != NULL && mPr_NullCheckPersonalID(parent_id) == FALSE &&
        mPr_NullCheckPlayerName(animal->parent_name) == TRUE) {
        mPr_CopyPlayerName(animal->parent_name, parent_id->player_name);
    }
}

extern void mNpc_SetParentNameAllAnimal() {
    Private_c* priv = Common_Get(now_private);

    if (priv != NULL) {
        PersonalID_c* parent_id = &priv->player_ID;
        Animal_c* animal = Save_Get(animals);
        int i;

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            mNpc_SetParentName(animal, parent_id);
            animal++;
        }
    }
}

extern void mNpc_ClearAnimalMail(Anmplmail_c* mail) {
    mail->font = 0xFF;
    mail->paper_type = 0;
    mail->present = EMPTY_NO;
    mem_clear(mail->body, sizeof(mail->body), CHAR_SPACE);
    mail->date.year = mTM_rtcTime_ymd_clear_code.year;
    mail->date.month = mTM_rtcTime_ymd_clear_code.month;
    mail->date.day = mTM_rtcTime_ymd_clear_code.day;
}

/* @unused */
/*
extern void mNpc_CopyAnimalMail(Anmplmail_c* dst, Anmplmail_c* src) {
  mem_copy((u8*)dst, (u8*)src, sizeof(Anmplmail_c));
}
*/

extern void mNpc_ClearAnimalMemory(Anmmem_c* memory, int num) {
    for (num; num != 0; num--) {
        if (memory != NULL) {
            mPr_ClearPersonalID(&memory->memory_player_id);
            lbRTC_TimeCopy(&memory->last_speak_time, &mTM_rtcTime_clear_code);
            mLd_ClearLandName(memory->memuni.land.name);
            memory->memuni.land.id = 0;
            memory->saved_town_tune = 0;
            memory->friendship = 0;
            memory->letter_info.exists = FALSE;
            memory->letter_info.cond = mNpc_LETTER_RANK_BAD;
            memory->letter_info.send_reply = FALSE;
            memory->letter_info.has_present_cloth = FALSE;
            mNpc_ClearAnimalMail(&memory->letter);
        }

        memory++;
    }
}

/* TODO: this probably implies the union is on the memory itself and not a struct inside it */
extern void mNpc_ClearIslandAnimalMemory(Anmmem_c* memory, int num) {
    for (num; num != 0; num--) {
        if (memory != NULL) {
            mPr_ClearPersonalID(&memory->memory_player_id);
            lbRTC_TimeCopy(&memory->last_speak_time, &mTM_rtcTime_clear_code);
            bzero(&memory->memuni.island, sizeof(memuni_u));
            memory->saved_town_tune = 0;
            memory->friendship = 0;
            memory->letter_info.exists = FALSE;
            memory->letter_info.cond = mNpc_LETTER_RANK_BAD;
            memory->letter_info.send_reply = FALSE;
            memory->letter_info.has_present_cloth = FALSE;
            mNpc_ClearAnimalMail(&memory->letter);
        }

        memory++;
    }
}

/* @unused */
/*
extern void mNpc_CopyAnimalMemory(Anmmem_c* dst, Anmmem_c* src) {
  mem_copy((u8*)dst, (u8*)src, sizeof(Anmmem_c));
}
*/

extern void mNpc_AddFriendship(Anmmem_c* memory, int amount) {
    int friendship;

/* @BUG - devs checked for memory being NULL *after* deferencing it */
#ifdef BUGFIXES
    if (memory == NULL) {
        return;
    }
#endif

    friendship = memory->friendship + amount;

#ifndef BUGFIXES
    if (memory == NULL) {
        return; //???
    }
#endif

    if (friendship > 127) {
        memory->friendship = 127;
    } else if (friendship < 0) {
        memory->friendship = 0;
    } else {
        memory->friendship = friendship;
    }
}

extern int mNpc_CheckFreeAnimalMemory(Anmmem_c* memory) {
    int res = FALSE;

    if (mPr_NullCheckPersonalID(&memory->memory_player_id) == TRUE) {
        res = TRUE;
    }

    return res;
}

extern void mNpc_RenewalAnimalMemory() {
    Private_c* priv;
    Animal_c* animal = Save_Get(animals);
    Anmmem_c* memory;
    int i;
    int j;
    int k;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        memory = animal->memories;

        for (j = 0; j < ANIMAL_MEMORY_NUM; j++) {
            if (mNpc_CheckFreeAnimalMemory(memory) == FALSE &&
                mLd_CheckThisLand(memory->memory_player_id.land_name, memory->memory_player_id.land_id) == TRUE) {
                priv = Save_Get(private_data);

                for (k = 0; k < PLAYER_NUM; k++) {
                    if (mPr_NullCheckPersonalID(&priv->player_ID) == FALSE &&
                        mPr_CheckCmpPersonalID(&priv->player_ID, &memory->memory_player_id) == TRUE) {
                        break;
                    }

                    priv++;
                }

                if (k == PLAYER_NUM) {
                    mNpc_ClearAnimalMemory(memory, 1); // player was deleted so free the memory
                }
            }

            memory++;
        }

        animal++;
    }
}

/* @unused */
/*
extern int mNpc_GetOldAnimalMemoryIdx(Anmmem_c* memory, int num) {
  lbRTC_time_c oldest;
  int res;
  int i;

  lbRTC_TimeCopy(&oldest, &mTM_rtcTime_clear_code);
  res = 0;

  for (i = 0; i < num; i++) {
    if (lbRTC_IsOverTime(&oldest, &memory->last_speak_time) == lbRTC_LESS) {
      res = i;
      lbRTC_TimeCopy(&oldest, &memory->last_speak_time);
    }

    memory++;
  }

  return res;
}
*/

extern int mNpc_GetFreeAnimalMemoryIdx(Anmmem_c* memory, int num) {
    int res = -1;
    int i;

    for (i = 0; i < num; i++) {
        if (mNpc_CheckFreeAnimalMemory(memory) == TRUE) {
            res = i;
            break;
        }

        memory++;
    }

    return res;
}

extern int mNpc_GetOldPlayerAnimalMemoryIdx(Anmmem_c* memory, int num) {
    Private_c* priv;
    int res = -1;
    int i;
    int j;

    for (i = 0; i < num; i++) {
        if (mNpc_CheckFreeAnimalMemory(memory) == FALSE &&
            mLd_CheckThisLand(memory->memory_player_id.land_name, memory->memory_player_id.land_id) == TRUE) {
            priv = Save_Get(private_data);

            for (j = 0; j < PLAYER_NUM; j++) {
                if (mPr_NullCheckPersonalID(&priv->player_ID) == FALSE &&
                    mPr_CheckCmpPersonalID(&priv->player_ID, &memory->memory_player_id) == TRUE) {
                    break;
                }

                priv++;
            }

            /* memory belongs to a player from this town which was deleted */
            if (j == PLAYER_NUM) {
                res = i;
                break;
            }
        }

        memory++;
    }

    return res;
}

extern int mNpc_ForceGetFreeAnimalMemoryIdx(Animal_c* animal, Anmmem_c* memory, int num) {
    Anmmem_c* mem_p = memory;
    Anmmem_c* chosen_mem = NULL;
    int free_idx = mNpc_GetFreeAnimalMemoryIdx(memory, num);
    int i;

    if (free_idx == -1) {
        for (i = 0; i < num; i++) {
            if (mLd_CheckThisLand(memory->memory_player_id.land_name, memory->memory_player_id.land_id) == FALSE) {
                if (chosen_mem != NULL) {
                    if (chosen_mem->letter_info.exists == memory->letter_info.exists) {
                        if (chosen_mem->friendship > memory->friendship) {
                            chosen_mem = memory;
                            free_idx = i;
                        } else if (chosen_mem->friendship == memory->friendship) {
                            if (lbRTC_IsOverTime(&chosen_mem->last_speak_time, &memory->last_speak_time) ==
                                lbRTC_LESS) {
                                chosen_mem = memory;
                                free_idx = i;
                            }
                        }
                    } else if (memory->letter_info.exists == FALSE) {
                        chosen_mem = memory;
                        free_idx = i;
                    }
                } else {
                    chosen_mem = memory;
                    free_idx = i;
                }
            }

            memory++;
        }
    } else {
        chosen_mem = memory + free_idx;
    }

    if (free_idx == -1 || chosen_mem == NULL) {
        free_idx = mNpc_GetOldPlayerAnimalMemoryIdx(mem_p, num);

        if (free_idx == -1) {
            free_idx = 0; // all else failed, so pick the first memory
        }

        chosen_mem = mem_p + free_idx;
    }

    if (chosen_mem != NULL) {
        if (mNpc_CheckIslandAnimalID(&animal->id) == FALSE) {
            mNpc_ClearAnimalMemory(chosen_mem, 1);
        } else {
            mNpc_ClearIslandAnimalMemory(chosen_mem, 1);
        }
    }

    return free_idx;
}

static void mNpc_ResetAnimalRelation(int idx) {
    Animal_c* animal = Save_Get(animals);
    u8* this_relations = animal[idx].animal_relations;
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        this_relations[0] = 128;
        this_relations++;
    }

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (i != idx) {
            animal->animal_relations[idx] = 128;
        }

        animal++;
    }
}

static void mNpc_SetAnimalMemory_NotSetDay(PersonalID_c* pid, AnmPersonalID_c* anm_id, Anmmem_c* memory) {
    if (memory != NULL) {
        if (mNpc_CheckIslandAnimalID(anm_id) == FALSE) {
            mNpc_ClearAnimalMemory(memory, 1);
        } else {
            mNpc_ClearIslandAnimalMemory(memory, 1);
        }

        mPr_CopyPersonalID(&memory->memory_player_id, pid);
        memory->friendship = 1;
    }
}

extern void mNpc_SetAnimalMemory(PersonalID_c* pid, AnmPersonalID_c* anm_id, Anmmem_c* memory) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

    if (memory != NULL) {
        mNpc_SetAnimalMemory_NotSetDay(pid, anm_id, memory);
        lbRTC_TimeCopy(&memory->last_speak_time, rtc_time);
    }
}

extern int mNpc_GetAnimalMemoryIdx(PersonalID_c* pid, Anmmem_c* memory, int num) {
    int res = -1;
    int i;

    for (i = 0; i < num; i++) {
        if (mPr_CheckCmpPersonalID(&memory->memory_player_id, pid) == TRUE) {
            res = i;
            break;
        }

        memory++;
    }

    return res;
}

extern void mNpc_SetAnimalLastTalk(Animal_c* animal) {
    Private_c* priv = Common_Get(now_private);
    Anmmem_c* memory = NULL;

    if (priv != NULL && animal != NULL) {
        int memory_idx = mNpc_GetAnimalMemoryIdx(&priv->player_ID, animal->memories, ANIMAL_MEMORY_NUM);

        if (memory_idx != -1) {
            memory = animal->memories + memory_idx;
        } else {
            memory_idx = mNpc_ForceGetFreeAnimalMemoryIdx(animal, animal->memories, ANIMAL_MEMORY_NUM);

            if (memory_idx != -1) {
                memory = animal->memories + memory_idx;
                mNpc_SetAnimalMemory(&priv->player_ID, &animal->id, memory);
            }
        }

        if (memory != NULL) {
            lbRTC_TimeCopy(&memory->last_speak_time, Common_GetPointer(time.rtc_time));
            mLd_CopyLandName(memory->memuni.land.name, Save_Get(land_info).name);
            memory->memuni.land.id = Save_Get(land_info).id;
            memory->saved_town_tune = Save_Get(melody);
        }
    }
}

extern void mNpc_SetAnimalPersonalID2Memory(AnmPersonalID_c* anm_id) {
    Private_c* priv = Common_Get(now_private);

    if (priv != NULL) {
        int anm_idx = mNpc_SearchAnimalPersonalID(anm_id);

        if (anm_idx != -1) {
            Animal_c* animal = Save_Get(animals) + anm_idx;
            int mem_idx = mNpc_GetAnimalMemoryIdx(&priv->player_ID, animal->memories, ANIMAL_MEMORY_NUM);

            if (mem_idx == -1) {
                int free_idx = mNpc_ForceGetFreeAnimalMemoryIdx(animal, animal->memories, ANIMAL_MEMORY_NUM);

                if (free_idx != -1) {
                    mNpc_SetAnimalMemory_NotSetDay(&priv->player_ID, &animal->id, animal->memories + free_idx);
                }
            }
        }
    }
}

extern int mNpc_GetHighestFriendshipIdx(Anmmem_c* memory, int num) {
    s8 max = 0;
    int res = -1;
    int i;

    for (i = 0; i < num; i++) {
        if (mNpc_CheckFreeAnimalMemory(memory) == FALSE) {
            if (max <= memory->friendship) {
                max = memory->friendship;
                res = i;
            }
        }

        memory++;
    }

    return res;
}

static int mNpc_SelectBestFriend(Anmmem_c** best_friend_mem, Anmmem_c* memory, s8* best_friend_friendship) {
    int res = FALSE;
    Anmmem_c* best_friend;

    if (memory->friendship > best_friend_friendship[0]) {
        best_friend_friendship[0] = memory->friendship;
        best_friend_mem[0] = memory;
        res = TRUE;
    } else if (memory->friendship == best_friend_friendship[0]) {
        best_friend = best_friend_mem[0];

        if (best_friend != NULL) {
            if (best_friend->letter_info.exists == memory->letter_info.exists) {
                if (lbRTC_IsOverTime(&best_friend->last_speak_time, &memory->last_speak_time) == lbRTC_LESS) {
                    best_friend_mem[0] = memory;
                    res = TRUE;
                }
            } else if (memory->letter_info.exists == TRUE) {
                best_friend_mem[0] = memory;
                res = TRUE;
            }
        } else {
            best_friend_mem[0] = memory;
            res = TRUE;
        }
    }

    return res;
}

extern int mNpc_GetAnimalMemoryBestFriend(Anmmem_c* memory, int num) {
    Anmmem_c* memory_p = memory;
    Anmmem_c* best_friend = NULL;
    s8 best_friendship = 0;
    int res = -1;
    int i;

    for (i = 0; i < num; i++) {
        if (mNpc_CheckFreeAnimalMemory(memory) == FALSE &&
            mNpc_SelectBestFriend(&best_friend, memory, &best_friendship) == TRUE) {
            res = i;
        }

        memory++;
    }

    memory = memory_p;
    if (res != -1) {
        memory = &memory[res];

        if (memory->friendship < 80) {
            res = -1; // minimum best friend friendship value failed
        }
    }

    return res;
}

static int mNpc_GetAnimalMemoryFriend_Land_Sex(Anmmem_c* memory, int num, int sex) {
    Anmmem_c* best_friend = NULL;
    s8 best_friendship = 0;
    int priv_idx;
    int res = -1;
    int i;

    for (i = 0; i < num; i++) {
        if (mNpc_CheckFreeAnimalMemory(memory) == FALSE) {
            priv_idx = mPr_GetPrivateIdx(&memory->memory_player_id);

            if (priv_idx != -1 && Save_Get(private_data[priv_idx]).gender == sex &&
                mNpc_SelectBestFriend(&best_friend, memory, &best_friendship) == TRUE) {
                res = i;
            }
        }

        memory++;
    }

    return res;
}

extern int mNpc_GetAnimalMemoryNum(Anmmem_c* memory, int count) {
    int num = 0;
    int i;

    for (i = 0; i < count; i++) {
        if (mNpc_CheckFreeAnimalMemory(memory) == FALSE) {
            num++;
        }

        memory++;
    }

    return num;
}

extern int mNpc_GetAnimalMemoryLetterNum(Anmmem_c* memory, int count) {
    int num = 0;
    int i;

    for (i = 0; i < count; i++) {
        if (mNpc_CheckFreeAnimalMemory(memory) == FALSE && memory->letter_info.exists == TRUE) {
            num++;
        }

        memory++;
    }

    return num;
}

extern int mNpc_GetAnimalMemoryLandKindNum(Anmmem_c* memory, int count) {
    Anmmem_c* memory2;
    Anmlnd_c* land;
    Anmlnd_c* land2;
    u8 bitfield = 0b11111111;
    int num = 0;
    int i;
    int j;

    for (i = 0; i < count; i++) {
        land = &memory->memuni.land;

        if (mNpc_CheckFreeAnimalMemory(memory) == FALSE) {
            if (((bitfield >> i) & 1) == 1) {
                memory2 = memory + 1;
                land2 = &memory2->memuni.land;

                for (j = i + 1; j < count; j++) {
                    if (((bitfield >> j) & 1) == 1) {
                        if (mLd_CheckCmpLand(land->name, land->id, land2->name, land2->id) == TRUE) {
                            bitfield &= ~(1 << j); // duplicate town here, so remove this memory from being checked
                        }
                    }

                    memory2++;
                }
            }

            num++;
        } else {
            bitfield &= ~(1 << i);
        }

        memory++;
    }

    return num;
}

extern void mNpc_ClearAnimalInfo(Animal_c* animal) {
    bzero(animal, sizeof(Animal_c));
    mNpc_ClearAnimalPersonalID(&animal->id);
    mNpc_ClearAnimalMemory(animal->memories, ANIMAL_MEMORY_NUM);
    animal->cloth = EMPTY_NO;
    animal->home_info.type_unused = 0;
    animal->home_info.block_x = 0xFF;
    animal->home_info.block_z = 0xFF;
    animal->home_info.ut_x = 0xFF;
    animal->home_info.ut_z = 0xFF;
    mNpc_ClearBufSpace1(animal->catchphrase, ANIMAL_CATCHPHRASE_LEN);
    mQst_ClearContest(&animal->contest_quest);
    mLd_ClearLandName(animal->anmuni.previous_land_name);
    animal->previous_land_id = 0;
    animal->remove_info = 0;
    animal->is_home = TRUE;
    mPr_ClearPlayerName(animal->parent_name);
}

extern void mNpc_ClearIslandAnimalInfo(Animal_c* animal) {
    bzero(animal, sizeof(Animal_c));
    mNpc_ClearAnimalPersonalID(&animal->id);
    mNpc_ClearIslandAnimalMemory(animal->memories, ANIMAL_MEMORY_NUM);
    animal->cloth = EMPTY_NO;
    animal->home_info.type_unused = 0;
    animal->home_info.block_x = 0xFF;
    animal->home_info.block_z = 0xFF;
    animal->home_info.ut_x = 0xFF;
    animal->home_info.ut_z = 0xFF;
    mNpc_ClearBufSpace1(animal->catchphrase, ANIMAL_CATCHPHRASE_LEN);
    mQst_ClearContest(&animal->contest_quest);
    animal->remove_info = 0;
    animal->is_home = TRUE;
    mPr_ClearPlayerName(animal->parent_name);
}

extern void mNpc_ClearAnyAnimalInfo(Animal_c* animal, int count) {
    int i;

    for (i = 0; i < count; i++) {
        mNpc_ClearAnimalInfo(animal);
        animal++;
    }
}

extern int mNpc_CheckFreeAnimalInfo(Animal_c* animal) {
    int res = FALSE;

    if ((animal->home_info.block_x == 0xFF && animal->home_info.block_z == 0xFF) &&
        ITEM_NAME_GET_TYPE(animal->id.npc_id) != NAME_TYPE_NPC) {
        res = TRUE;
    }

    return res;
}

extern int mNpc_GetFreeAnimalInfo(Animal_c* animal, int count) {
    int res = -1;
    int i;

    for (i = 0; i < count; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == TRUE) {
            res = i;
            break;
        }

        animal++;
    }

    return res;
}

extern int mNpc_UseFreeAnimalInfo(Animal_c* animal, int count) {
    int free_idx = mNpc_GetFreeAnimalInfo(animal, count);

    if (free_idx != -1) {
        mNpc_ClearAnimalInfo(animal + free_idx);
        mNpc_ResetAnimalRelation(free_idx);
    }

    return free_idx;
}

extern void mNpc_CopyAnimalInfo(Animal_c* dst, Animal_c* src) {
    mem_copy((u8*)dst, (u8*)src, sizeof(Animal_c));
}

extern int mNpc_SearchAnimalinfo(Animal_c* animal, mActor_name_t npc_id, int count) {
    int i;

    animal = animal + (count - 1);
    for (i = count - 1; i >= 0; i--) {
        if (animal->id.npc_id == npc_id) {
            return i;
        }

        animal--;
    }

    return -1;
}

extern Animal_c* mNpc_GetAnimalInfoP(mActor_name_t npc_id) {
    Animal_c* animal = NULL;
    int idx = mNpc_SearchAnimalinfo(Save_Get(animals), npc_id, ANIMAL_NUM_MAX);

    if (idx != -1) {
        animal = Save_Get(animals) + idx;
    }

    return animal;
}

extern int mNpc_SearchAnimalPersonalID(AnmPersonalID_c* anm_pid) {
    Animal_c* animal = Save_Get(animals);
    int res = -1;
    int i;

    if (anm_pid != NULL && !mNpc_CheckFreeAnimalPersonalID(anm_pid)) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckCmpAnimalPersonalID(anm_pid, &animal->id) == TRUE) {
                res = i;
                break;
            }

            animal++;
        }
    }

    return res;
}

extern AnmPersonalID_c* mNpc_GetOtherAnimalPersonalIDOtherBlock(AnmPersonalID_c* pids, int count, int bx, int bz,
                                                                int check_flag) {
    Animal_c* animal;
    AnmPersonalID_c* other_id;
    int npc_max;
    int homes_in_block;
    int ids = count;
    u16 bitfield;
    int j;
    int i;

    other_id = NULL;
    npc_max = Save_Get(now_npc_max);
    animal = Save_Get(animals);
    homes_in_block = 0;
    ids = count;
    bitfield = 0xFFFF;

    if (bx == 0xFF || bz == 0xFF) {
        check_flag = FALSE;
    }

    if (pids == NULL && count != 0) {
        count = 0;
    }

    /* clear any uninitialized personal ids */
    for (i = 0; i < count; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(pids + i) == TRUE) {
            ids--;
            bitfield &= ~(1 << i);
        }
    }

    /* clear any npcs who are in the list and live in the acre */
    if (check_flag == TRUE) {
        for (j = 0; j < ANIMAL_NUM_MAX; j++) {
            if (animal->home_info.block_x == bx && animal->home_info.block_z == bz) {
                homes_in_block++;

                for (i = 0; i < count; i++) {
                    if (((bitfield >> i) & 1) == 1 && mNpc_CheckCmpAnimalPersonalID(&animal->id, &pids[i]) == TRUE) {
                        ids--;
                        bitfield &= ~(1 << i);
                        break;
                    }
                }
            }

            animal++;
        }
    }

    if (npc_max > (ids + homes_in_block) && count < ANIMAL_NUM_MAX) {
        int valid;
        int t;

        animal = Save_Get(animals);
        homes_in_block = RANDOM((npc_max - ids) - homes_in_block);

        for (j = 0; j < ANIMAL_NUM_MAX; j++) {
            i = 0;
            valid = TRUE;

            if (!mNpc_CheckFreeAnimalPersonalID(&animal->id)) {
                for (npc_max = 0; npc_max < count; npc_max++) {
                    if (((bitfield >> npc_max) & 1) == 1 &&
                        !mNpc_CheckCmpAnimalPersonalID(&animal->id, &pids[npc_max])) {
                        i++;
                    }
                }

                if (i != ids) {
                    valid = FALSE;
                } else if (check_flag == TRUE && animal->home_info.block_x == bx && animal->home_info.block_z == bz) {
                    if (homes_in_block > 0) {
                        homes_in_block--;
                    }

                    valid = FALSE;
                }

                if (valid == TRUE) {
                    if (homes_in_block == 0) {
                        other_id = &animal->id;
                        break;
                    } else {
                        homes_in_block--;
                    }
                }
            }

            animal++;
        }
    }

    return other_id;
}

extern AnmPersonalID_c* mNpc_GetOtherAnimalPersonalID(AnmPersonalID_c* pids, int count) {
    return mNpc_GetOtherAnimalPersonalIDOtherBlock(pids, count, 0, 0, FALSE);
}

extern void mNpc_SetAnimalThisLand(Animal_c* animal, int count) {
    mLd_land_info_c* land_info = Save_GetPointer(land_info);

    for (count; count != 0; count--) {
        if (!mNpc_CheckFreeAnimalPersonalID(&animal->id)) {
            animal->id.land_id = land_info->id;
            mLd_CopyLandName(animal->id.land_name, land_info->name);
        }

        animal++;
    }
}

extern int mNpc_GetSameLooksNum(u8 looks) {
    Animal_c* animal = Save_Get(animals);
    int i;
    int num = 0;

    if (looks < mNpc_LOOKS_UNSET) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (looks == animal->id.looks) {
                num++;
            }

            animal++;
        }
    }

    return num;
}

extern int mNpc_CheckNpcExistBlock(int idx, int check_bx, int check_bz) {
    int bx;
    int bz;
    int res = FALSE;

    if (idx >= 0 && idx < (ANIMAL_NUM_MAX + 1)) {
        mNpc_NpcList_c* list = Common_GetPointer(npclist[idx]);

        if (mFI_Wpos2BlockNum(&bx, &bz, list->position) == TRUE && bx == check_bx && bz == check_bz) {
            res = TRUE;
        }
    }

    return res;
}

extern void mNpc_Mail2AnimalMail(Anmplmail_c* animal_mail, Mail_c* mail) {
    mem_copy(animal_mail->body, mail->content.body, MAIL_BODY_LEN);
    mem_copy(animal_mail->header, mail->content.header, MAIL_HEADER_LEN);
    mem_copy(animal_mail->footer, mail->content.footer, MAIL_FOOTER_LEN);

    animal_mail->header_back_start = mail->content.header_back_start;
    animal_mail->font = mail->content.font;
    animal_mail->present = mail->present;
    animal_mail->paper_type = mail->content.paper_type;
}

extern void mNpc_AnimalMail2Mail(Mail_c* mail, Anmplmail_c* animal_mail, PersonalID_c* pid, AnmPersonalID_c* anm_id) {
    mem_copy(mail->content.body, animal_mail->body, MAIL_BODY_LEN);
    mem_copy(mail->content.header, animal_mail->header, MAIL_HEADER_LEN);
    mem_copy(mail->content.footer, animal_mail->footer, MAIL_FOOTER_LEN);

    mail->content.header_back_start = animal_mail->header_back_start;
    mail->content.font = animal_mail->font;
    mail->present = animal_mail->present;
    mail->content.paper_type = animal_mail->paper_type;

    if (pid != NULL) {
        mPr_CopyPersonalID(&mail->header.sender.personalID, pid);
        mail->header.sender.type = mMl_NAME_TYPE_PLAYER;
    }

    if (anm_id != NULL) {
        mMl_set_mail_name_npcinfo(&mail->header.recipient, anm_id);
    }
}

static int mNpc_CheckMailChar(u8 c) {
    if ((c == CHAR_EXCLAMATION) || (c == CHAR_QUOTATION) || (c == CHAR_UNDERSCORE) || (c == CHAR_HYPHEN) ||
        (c == CHAR_SYMBOL_ANNOYED) || ((c >= CHAR_PERCENT) && (c <= CHAR_AT_SIGN)) ||
        ((c >= CHAR_CONTROL_CODE) && (c <= CHAR_INTERPUNCT))) {
        return TRUE;
    }

    return FALSE;
}

extern int mNpc_CheckNormalMail_sub(int* char_num, u8* body) {
    u8 last_char = CHAR_SPACE;
    int run_len = 1;
    int consecutive_chars = FALSE;
    int t = 0;
    int i;

    char_num[0] = 0;

    for (i = 0; i < MAIL_BODY_LEN; i++) {
        if (body[0] != CHAR_SPACE) {

            if (last_char == body[0]) {
                run_len++;

                if (run_len >= 3) {
                    if (mNpc_CheckMailChar(body[0]) == TRUE) {
                        if (run_len >= 8) {
                            consecutive_chars = TRUE;
                            break;
                        }
                    } else {
                        consecutive_chars = TRUE;
                        break;
                    }
                }
            } else {
                run_len = 0;
                last_char = body[0];
            }

            char_num[0]++;
        }

        body++;
        t++;
    }

    for (i = t; i < MAIL_BODY_LEN; i++) {
        if (body[0] != CHAR_SPACE) {
            char_num[0]++;
        }

        body++;
    }

    return consecutive_chars;
}

extern u8 mNpc_CheckNormalMail_length(int* len, u8* body) {
    int hit_chars;
    u8 rank = mNpc_LETTER_RANK_NUM;
    int hit_rate = mMC_get_mail_hit_rate(&hit_chars, body, NULL);
    int run_on = mNpc_CheckNormalMail_sub(len, body);

    if (hit_chars < 3) {
        if (len[0] < 5) {
            rank = mNpc_LETTER_RANK_BAD;
        } else if (run_on == TRUE) {
            rank = mNpc_LETTER_RANK_BAD;
        }
    } else if (hit_rate >= 30) {
        rank = mNpc_LETTER_RANK_OK;
    } else if (run_on == TRUE) {
        rank = mNpc_LETTER_RANK_BAD;
    }

    return rank;
}

extern u8 mNpc_CheckNormalMail_nes(u8* body) {
    u8 rank = mNpc_LETTER_RANK_NUM;
    int key_hit = mMck_check_key_hit_nes(body);

    if (key_hit >= 100) {
        rank = mNpc_LETTER_RANK_OK;
    } else if (key_hit < 50) {
        rank = mNpc_LETTER_RANK_BAD;
    }

    return rank;
}

static u8 mNpc_CheckNormalMail(u8* body) {
    return mNpc_CheckNormalMail_nes(body);
}

static int mNpc_SetMailCondThisLand(Anmmem_c* memory, u8* body) {
    u8 letter_rank;

    memory->letter.date.year = Common_Get(time.rtc_time).year;
    memory->letter.date.month = Common_Get(time.rtc_time).month;
    memory->letter.date.day = Common_Get(time.rtc_time).day;

    letter_rank = mNpc_CheckNormalMail(body);

    if (letter_rank < mNpc_LETTER_RANK_NUM) {
        memory->letter_info.cond = letter_rank;
        memory->letter_info.send_reply = TRUE;
    }

    return letter_rank;
}

static int mNpc_SetMailCondOtherLand(Animal_c* animal, u8* body) {
    u8 letter_rank = mNpc_CheckNormalMail(body);

    if (letter_rank < mNpc_LETTER_RANK_NUM) {
        Private_c* priv = Common_Get(now_private);
        Anmremail_c* remail = &priv->remail;

        remail->date.year = Common_Get(time.rtc_time).year;
        remail->date.month = Common_Get(time.rtc_time).month;
        remail->date.day = Common_Get(time.rtc_time).day;
        remail->flags.cond = letter_rank;
        remail->flags.looks = animal->id.looks;

        mNpc_GetNpcWorldNameAnm(remail->name, &animal->id);
        mLd_CopyLandName(remail->land_name, mLd_GetLandName());
    }

    return letter_rank;
}

static int mNpc_SetRemailCond(Animal_c* animal, Anmmem_c* memory, u8* body) {
    if (mLd_PlayerManKindCheck() == FALSE) {
        return mNpc_SetMailCondThisLand(memory, body);
    } else {
        return mNpc_SetMailCondOtherLand(animal, body);
    }
}

static int mNpc_SetPresentCloth(Animal_c* animal, PersonalID_c* player_id, mActor_name_t cloth) {
    Anmmem_c* mem;
    int res = FALSE;

    if (animal != NULL && player_id != NULL && ITEM_NAME_GET_TYPE(cloth) == NAME_TYPE_ITEM1 &&
        ITEM_NAME_GET_CAT(cloth) == ITEM1_CAT_CLOTH && !mNpc_CheckFreeAnimalPersonalID(&animal->id) &&
        !mPr_NullCheckPersonalID(player_id)) {
        int memory_idx = mNpc_GetAnimalMemoryIdx(player_id, animal->memories, ANIMAL_MEMORY_NUM);

        if (memory_idx != -1) {
            Anmmem_c* m = &animal->memories[memory_idx];

            if (m->friendship > 30) {
                Anmmem_c* memory = animal->memories;
                int i;

                for (i = 0; i < ANIMAL_MEMORY_NUM; i++) {
                    if (i == memory_idx) {
                        memory->letter_info.has_present_cloth = TRUE;
                    } else {
                        memory->letter_info.has_present_cloth = FALSE;
                    }

                    memory->letter_info.wearing_present_cloth = FALSE;
                    memory++;
                }

                animal->present_cloth = cloth;
                res = TRUE;
            }
        }
    }

    return res;
}

extern int mNpc_SendMailtoNpc(Mail_c* mail) {
    int res = FALSE;
    Animal_c* animal;
    AnmPersonalID_c anm_id;
    int anm_idx;
    int memory_idx;
    Anmmem_c* memory;
    Anmplmail_c* plmail;
    int letter_rank;
    Animal_c* anm;

    if (mMl_get_npcinfo_from_mail_name(&anm_id, &mail->header.recipient) == TRUE) {
        anm = Save_Get(animals);
        anm_idx = mNpc_SearchAnimalPersonalID(&anm_id);

        if (anm_idx != -1) {
            animal = anm + anm_idx;
            memory_idx = mNpc_GetAnimalMemoryIdx(&mail->header.sender.personalID, animal->memories, ANIMAL_MEMORY_NUM);

            if (memory_idx == -1) {
                memory_idx = mNpc_ForceGetFreeAnimalMemoryIdx(anm, animal->memories, ANIMAL_MEMORY_NUM);

                if (memory_idx >= 0) {
                    mPr_CopyPersonalID(&animal->memories[memory_idx].memory_player_id, &mail->header.sender.personalID);
                }
            } else {
                mNpc_SetPresentCloth(animal, &mail->header.sender.personalID, mail->present);
            }

            memory = animal->memories + memory_idx;
            plmail = &memory->letter;
            memory->letter_info.exists = TRUE;
            mNpc_ClearAnimalMail(plmail);
            mNpc_Mail2AnimalMail(plmail, mail);
            letter_rank = mNpc_SetRemailCond(animal, memory, mail->content.body);

            if (mEv_CheckFirstJob() == TRUE) {
                mQst_errand_c* first_job = mQst_GetFirstJobData();

                if ((first_job->base.quest_kind == mQst_ERRAND_FIRSTJOB_SEND_LETTER ||
                     first_job->base.quest_kind == mQst_ERRAND_FIRSTJOB_SEND_LETTER2) &&
                    first_job->base.progress != 0) {
                    first_job->base.progress = 3;
                    memory->letter_info.send_reply = FALSE;
                }
            } else {
                int friendship = 0;

                if (mLd_PlayerManKindCheck() == FALSE) {
                    int occur_idx = mQst_GetOccuredContestIdx(mQst_CONTEST_KIND_LETTER);
                    if (occur_idx == anm_idx) {
                        mQst_SetReceiveLetter(&animal->contest_quest, &mail->header.sender.personalID,
                                              mail->content.body, mail->present);
                        memory->letter_info.send_reply = FALSE;
                    }
                }

                friendship += 3;

                if (letter_rank == mNpc_LETTER_RANK_BAD) {
                    friendship += -5;
                }

                if (mail->present != EMPTY_NO) {
                    friendship += 3;
                }

                mNpc_AddFriendship(memory, friendship);
            }

            res = TRUE;
        }
    }

    return res;
}

extern void mNpc_ClearRemail(Anmremail_c* remail) {
    remail->date = mTM_rtcTime_ymd_clear_code;
    mPr_ClearPlayerName(remail->name);
    mLd_ClearLandName(remail->land_name);
    remail->flags.cond = mNpc_LETTER_RANK_BAD;
    remail->flags.looks = 0x7F;
}

static void mNpc_GetRemailPresent(mActor_name_t* present) {
    static int category_table[2] = { mSP_KIND_FURNITURE, mSP_KIND_CLOTH };

    mSP_SelectRandomItem_New(NULL, present, 1, NULL, 0, category_table[RANDOM(4) & 1], mSP_LISTTYPE_ABC, FALSE);
}

static int mNpc_GetHandbillz(Mail_c* mail, int super_num, int mail_a_num, int mail_b_num, int mail_c_num, int ps_num) {
    static u8 tmp_super[MAIL_HEADER2_LEN];
    static u8 tmp_ps[MAIL_FOOTER2_LEN];

    mHandbillz_Info_c handbill_info;
    int res;

    handbill_info.super_buf_p = tmp_super;
    handbill_info.super_buf_size = MAIL_HEADER2_LEN;
    handbill_info.mail_buf_p = mail->content.body;
    handbill_info.mail_buf_size = MAIL_BODY_LEN;
    handbill_info.ps_buf_p = tmp_ps;
    handbill_info.ps_buf_size = MAIL_FOOTER2_LEN;
    handbill_info.super_no = super_num;
    handbill_info.maila_no = mail_a_num;
    handbill_info.mailb_no = mail_b_num;
    handbill_info.mailc_no = mail_c_num;
    handbill_info.ps_no = ps_num;

    res = mHandbillz_load(&handbill_info);
    if (res == TRUE) {
        mail->content.header_back_start = handbill_info.header_back_start;
        mem_copy(mail->content.header, tmp_super, MAIL_HEADER_LEN);
        mem_copy(mail->content.footer, tmp_ps, MAIL_FOOTER_LEN);
    }

    return res;
}

static void mNpc_SetRemailFreeString(PersonalID_c* pid, AnmPersonalID_c* anm_id, Anmremail_c* remail) {
    static int base_str_no[11] = {
        0x314, // food
        0x334, // sports
        0x2F4, // hobby games
        0x6A1, // fish
        0x679, // insects
        0x354, // food tastes (sweet, spicy, ...)
        0x374, // feelings
        0x394, // music genres
        0x3D4, // food satisfaction feelings (delicious, stuffed, satisfying, ...)
        0x3F4, // "good" descriptors (brilliant, splendid, ...)
        0x3B4  // "bad" descriptors (unimpressive, awful, ...)
    };

    /* number of string entries per type */
    static f32 rand_max_table[11] = { 32.0f, 32.0f, 32.0f, 40.0f, 40.0f, 32.0f, 32.0f, 32.0f, 32.0f, 32.0f, 32.0f };

    u8 free_str[16];
    AnmPersonalID_c* other_id;
    int i;

    mHandbill_Set_free_str(mHandbill_FREE_STR0, pid->player_name, PLAYER_NAME_LEN);

    if (remail == NULL) {
        mNpc_GetNpcWorldNameAnm(free_str, anm_id);
        mHandbill_Set_free_str(mHandbill_FREE_STR1, free_str, ANIMAL_NAME_LEN);
        other_id = mNpc_GetOtherAnimalPersonalID(anm_id, 1);

        if (other_id != NULL) {
            mNpc_GetNpcWorldNameAnm(free_str, other_id);
            mHandbill_Set_free_str(mHandbill_FREE_STR2, free_str, ANIMAL_NAME_LEN);
        }
    } else {
        mHandbill_Set_free_str(mHandbill_FREE_STR1, remail->name, ANIMAL_NAME_LEN); // foreign npc name
        other_id = mNpc_GetOtherAnimalPersonalID(NULL, 0);
        mNpc_GetNpcWorldNameAnm(free_str, other_id);
        mHandbill_Set_free_str(mHandbill_FREE_STR2, free_str, ANIMAL_NAME_LEN);          // random player town npc name
        mHandbill_Set_free_str(mHandbill_FREE_STR14, remail->land_name, LAND_NAME_SIZE); // foreign town name
        mHandbill_Set_free_str(mHandbill_FREE_STR15, mLd_GetLandName(), LAND_NAME_SIZE); // player town name
    }

    for (i = 0; i < ARRAY_COUNT(base_str_no); i++) {
        int rand = RANDOM_F(rand_max_table[i]);

        mString_Load_StringFromRom(free_str, ARRAY_COUNT(free_str), base_str_no[i] + rand);
        mHandbill_Set_free_str(mHandbill_FREE_STR3 + i, free_str, ARRAY_COUNT(free_str));
    }
}

static void mNpc_GetRemailGoodData(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anm_id, Anmremail_c* remail,
                                   u8 foreign) {
    static int this_start_no[mNpc_LOOKS_NUM] = { 0x020, 0x040, 0x000, 0x060, 0x080, 0x0A0 };

    static int ohter_start_no[mNpc_LOOKS_NUM] = { 0x0E0, 0x100, 0x0C0, 0x120, 0x140, 0x160 };

    static int* start_no_table[2] = { this_start_no, ohter_start_no };

    mActor_name_t present = EMPTY_NO;
    int msg_no;
    int* msg_tbl;
    int looks;
    int give_present;

    if (remail == NULL) {
        looks = anm_id->looks;
    } else {
        looks = remail->flags.looks;
    }

    msg_tbl = start_no_table[foreign];

    give_present = RANDOM(4) & 1;
    if (give_present == 0) {
        mNpc_GetRemailPresent(&present);
    }

    mNpc_SetRemailFreeString(pid, anm_id, remail);
    msg_no = msg_tbl[looks];
    mNpc_GetHandbillz(mail, msg_no + RANDOM(32), msg_no + RANDOM(32), msg_no + RANDOM(16) + give_present * 16,
                      msg_no + RANDOM(32), msg_no + RANDOM(32));
    mail->present = present;
}

static void mNpc_GetRemailWrongData(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anm_id, Anmremail_c* remail,
                                    u8 foreign) {
    static int mail_no[2] = { 0xC5, 0xD8 };
    static u8 tmp_super[MAIL_HEADER2_LEN];
    static u8 tmp_ps[MAIL_FOOTER2_LEN];

    int looks;
    int header_back_start;
    int msg_no;

    if (remail == NULL) {
        looks = anm_id->looks;
    } else {
        looks = remail->flags.looks;
    }

    mNpc_SetRemailFreeString(pid, anm_id, remail);
    msg_no = mail_no[foreign] + looks * 3;
    msg_no += RANDOM(3);
    mHandbill_Load_HandbillFromRom(tmp_super, &header_back_start, tmp_ps, mail->content.body, msg_no);
    mail->content.header_back_start = header_back_start;
    mem_copy(mail->content.header, tmp_super, MAIL_HEADER_LEN);
    mem_copy(mail->content.footer, tmp_ps, MAIL_FOOTER_LEN);
    mail->present = EMPTY_NO;
}

typedef void (*mNPC_GET_REMAIL_PROC)(Mail_c*, PersonalID_c*, AnmPersonalID_c*, Anmremail_c*, u8);

static void mNpc_GetRemailData(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anm_id, Anmremail_c* remail, int cond,
                               u8 foreign) {
    static mNPC_GET_REMAIL_PROC get_remail[mNpc_LETTER_RANK_NUM] = { &mNpc_GetRemailWrongData,
                                                                     &mNpc_GetRemailGoodData };

    mActor_name_t paper;
    int paper_no;

    (*get_remail[cond])(mail, pid, anm_id, remail, foreign);
    mail->content.font = mMl_FONT_RECV;
    mail->content.mail_type = mMl_TYPE_MAIL;
    mPr_CopyPersonalID(&mail->header.recipient.personalID, pid);
    mail->header.recipient.type = mMl_NAME_TYPE_PLAYER;

    if (remail == NULL) {
        mMl_set_mail_name_npcinfo(&mail->header.sender, anm_id);
    } else {
        mPr_CopyPlayerName(mail->header.sender.personalID.player_name, remail->name);
        mLd_CopyLandName(mail->header.sender.personalID.land_name, remail->land_name);
        mail->header.sender.type = mMl_NAME_TYPE_NPC;
    }

    mSP_SelectRandomItem_New(NULL, &paper, 1, NULL, 0, mSP_KIND_PAPER, mSP_LISTTYPE_ABC, FALSE);
    mail->content.paper_type = (paper - ITM_PAPER_START) % PAPER_UNIQUE_NUM;
}

static Mail_c l_npc_mail;

static int mNpc_SendRemailPostOffice(PersonalID_c* pid, AnmPersonalID_c* anm_id, Anmremail_c* remail, int cond,
                                     u8 foreign) {
    Mail_c* mail = &l_npc_mail;
    int res = FALSE;

    if (mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE) {
        mMl_clear_mail(mail);
        mNpc_GetRemailData(mail, pid, anm_id, remail, cond, foreign);
        res = mPO_receipt_proc(mail, mPO_SENDTYPE_MAIL);
    }

    return res;
}

static int mNpc_CheckLetterTime(lbRTC_ymd_c* letter_date, lbRTC_time_c* rtc_time) {
    int res = FALSE;

    if (letter_date->day != 0xFF && (letter_date->year != rtc_time->year || letter_date->month != rtc_time->month ||
                                     letter_date->day != rtc_time->day)) {
        res = TRUE;
    }

    return res;
}

// 25%

extern void mNpc_Remail() {
    Animal_c* animal = Save_Get(animals);
    Anmremail_c* remail;
    Private_c* priv = Common_Get(now_private);
    Anmmem_c* memory;
    lbRTC_time_c* rtc_time;

    rtc_time = Common_GetPointer(time.rtc_time);

    if (mPr_NullCheckPersonalID(&priv->player_ID) == FALSE && mLd_PlayerManKindCheck() == FALSE) {
        int i;

        /* process replies from town villagers first */
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
                int mem_idx = mNpc_GetAnimalMemoryIdx(&priv->player_ID, animal->memories, ANIMAL_MEMORY_NUM);

                if (mem_idx != -1) {
                    memory = animal->memories + mem_idx;

                    if (memory->letter_info.send_reply &&
                        mNpc_CheckLetterTime(&memory->letter.date, rtc_time) == TRUE) {
                        if (mNpc_SendRemailPostOffice(&priv->player_ID, &animal->id, NULL, memory->letter_info.cond,
                                                      FALSE) != TRUE) {
                            break;
                        }

                        memory->letter_info.send_reply = FALSE;
                    }
                }
            }

            animal++;
        }

        /* process info from the last foreign villager (if any) */
        remail = &priv->remail;
        if (remail->flags.looks != 0x7F &&
            mNpc_SendRemailPostOffice(&priv->player_ID, &animal->id, remail, remail->flags.cond, TRUE) == TRUE) {
            mNpc_ClearRemail(remail);
        }
    }
}

extern u8 mNpc_GetPaperType() {
    mActor_name_t paper;

    mSP_SelectRandomItem_New(NULL, &paper, 1, NULL, 0, mSP_KIND_PAPER, mSP_LISTTYPE_ABC, FALSE);
    return (paper - ITM_PAPER_START) % PAPER_UNIQUE_NUM;
}

static void mNpc_LoadMailDataCommon2(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anm_id, mActor_name_t present,
                                     u8 paper_type, int mail_no) {
    u8 super[MAIL_HEADER2_LEN];
    u8 ps[MAIL_FOOTER2_LEN];
    int header_back_start;

    mMl_clear_mail(mail);
    mHandbill_Load_HandbillFromRom2(super, MAIL_HEADER2_LEN, &header_back_start, ps, MAIL_FOOTER2_LEN,
                                    mail->content.body, mail_no);
    mem_copy(mail->content.header, super, MAIL_HEADER_LEN);
    mem_copy(mail->content.footer, ps, MAIL_FOOTER_LEN);
    mail->content.header_back_start = header_back_start;
    mail->content.font = mMl_FONT_RECV;
    mail->content.mail_type = mMl_TYPE_MAIL;
    mPr_CopyPersonalID(&mail->header.recipient.personalID, pid);
    mail->header.recipient.type = mMl_NAME_TYPE_PLAYER;
    mMl_set_mail_name_npcinfo(&mail->header.sender, anm_id);
    mail->present = present;
    mail->content.paper_type = paper_type;
}

static void mNpc_GetEventPresent(mActor_name_t* present, int type) {
    static int priority_table[mNpc_EVENT_MAIL_FRIEND_NUM] = { mSP_LISTTYPE_RARE, mSP_LISTTYPE_UNCOMMON,
                                                              mSP_LISTTYPE_COMMON };

    static int category_table[mNpc_EVENT_MAIL_FRIEND_NUM] = { mSP_KIND_FURNITURE, mSP_KIND_FURNITURE, mSP_KIND_CLOTH };

    mSP_SelectRandomItem_New(NULL, present, 1, NULL, 0, category_table[type], priority_table[type], FALSE);
}

static void mNpc_GetEventMail(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anm_id, int type, int looks) {
    static u8 animal_name[ANIMAL_NAME_LEN];

    mActor_name_t present;

    mHandbill_Set_free_str(mHandbill_FREE_STR0, pid->player_name, PLAYER_NAME_LEN);
    mNpc_GetNpcWorldNameAnm(animal_name, anm_id);
    mHandbill_Set_free_str(mHandbill_FREE_STR6, animal_name, ANIMAL_NAME_LEN);
    mNpc_GetEventPresent(&present, type);
    mNpc_LoadMailDataCommon2(mail, pid, anm_id, present, mNpc_GetPaperType(),
                             0x60 + looks * mNpc_EVENT_MAIL_FRIEND_NUM + type);
}

static int mNpc_SendEventPresentMail(PersonalID_c* pid, int player_no, AnmPersonalID_c* anm_id, int type) {
    Mail_c* mail = &l_npc_mail;
    mHm_hs_c* home;
    int looks = anm_id->looks;
    int res = FALSE;

    home = Save_GetPointer(homes[mHS_get_arrange_idx(player_no)]);

    if (mPr_CheckCmpPersonalID(pid, &home->ownerID) == TRUE) {
        int free_idx;

        mMl_clear_mail(mail);
        free_idx = mMl_chk_mail_free_space(home->mailbox, HOME_MAILBOX_SIZE);

        if (free_idx != -1) {
            mNpc_GetEventMail(mail, pid, anm_id, type, looks);
            mMl_copy_mail(home->mailbox + free_idx, mail);
            res = TRUE;
        } else if (mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE) {
            mNpc_GetEventMail(mail, pid, anm_id, type, looks);
            res = mPO_receipt_proc(mail, mPO_SENDTYPE_MAIL);
        }
    }

    return res;
}

static void mNpc_SendEventPresentMailSex(int* selected, u8* type, Animal_c* animal, int animal_sex) {
    int best_friend_idx = mNpc_GetAnimalMemoryBestFriend(animal->memories, ANIMAL_MEMORY_NUM);
    int other_sex_best_friend_idx =
        mNpc_GetAnimalMemoryFriend_Land_Sex(animal->memories, ANIMAL_MEMORY_NUM, (~animal_sex) & 1);

    if (best_friend_idx != -1 && other_sex_best_friend_idx == best_friend_idx) {
        selected[0] = other_sex_best_friend_idx;
        type[0] = mNpc_EVENT_MAIL_BEST_FRIEND;
    } else if (other_sex_best_friend_idx != -1) {
        selected[0] = other_sex_best_friend_idx;

        if (animal->memories[other_sex_best_friend_idx].friendship >= 80) {
            type[0] = mNpc_EVENT_MAIL_OK_FRIEND;
        } else {
            type[0] = mNpc_EVENT_MAIL_NOT_FRIEND;
        }
    }
}

/* this used to be mNpc_SendEventPresentMail_common in DnM and DnM+ (handled both valentine's day & white day) */

extern int mNpc_SendVtdayMail() {
    u8 types[ANIMAL_NUM_MAX];
    int other_sex_best_friends[ANIMAL_NUM_MAX];
    Animal_c* animal_p;
    int sent;
    u8 player_bitfield;
    int mem_idx;
    PersonalID_c* pid;
    int player_no;
    int i;
    int j;

    animal_p = Save_Get(animals);
    sent = 0;
    player_bitfield = 0b1111;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        other_sex_best_friends[i] = -1;

        if (mNpc_CheckFreeAnimalPersonalID(&animal_p->id) == FALSE) {
            mNpc_SendEventPresentMailSex(&other_sex_best_friends[i], &types[i], animal_p, mNpc_GetAnimalSex(animal_p));
        }

        animal_p++;
    }

    for (i = 0; i < mNpc_EVENT_MAIL_FRIEND_NUM; i++) {
        animal_p = Save_Get(animals);

        for (j = 0; j < ANIMAL_NUM_MAX; j++) {
            if (other_sex_best_friends[j] >= 0 && types[j] == i) {
                pid = &animal_p->memories[other_sex_best_friends[j]].memory_player_id;
                player_no = mPr_GetPrivateIdx(pid);

                if (((player_bitfield >> player_no) & 1) == 1) {
                    if (mNpc_SendEventPresentMail(pid, player_no, &animal_p->id, i) == TRUE) {
                        other_sex_best_friends[j] = -1;
                        sent++;
                    } else {
                        player_bitfield &=
                            ~(1 << player_no); // remove player from bitfield because they can't receive letters
                    }
                }
            }

            if (player_bitfield == 0) {
                return sent; // all players cannot receive any further mail
            }

            animal_p++;
        }
    }

    return sent;
}

static void mNpc_GetBirthdayPresent(mActor_name_t* present) {
    static u8 category_table[5] = { mSP_KIND_FURNITURE, mSP_KIND_FURNITURE, mSP_KIND_CLOTH, mSP_KIND_CLOTH, 0xFF };

    int selected = category_table[RANDOM(ARRAY_COUNT(category_table))];

    if (selected == 0xFF) {
        mSP_RandomUmbSelect(present, 1);
    } else {
        mSP_SelectRandomItem_New(NULL, present, 1, NULL, 0, selected, mSP_LISTTYPE_RARE, FALSE);
    }
}

static void mNpc_GetBirthdayCard(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anm_id) {
    static u8 animal_name[ANIMAL_NAME_LEN];

    u8 item_name[mIN_ITEM_NAME_LEN];
    int mail_no = 0xEA + anm_id->looks * 3 + RANDOM(3);
    mActor_name_t present;

    mHandbill_Set_free_str(mHandbill_FREE_STR0, pid->player_name, PLAYER_NAME_LEN);
    mNpc_GetNpcWorldNameAnm(animal_name, anm_id);
    mHandbill_Set_free_str(mHandbill_FREE_STR1, animal_name, ANIMAL_NAME_LEN);
    mNpc_GetBirthdayPresent(&present);
    mIN_copy_name_str(item_name, present);
    mHandbill_Set_free_str(mHandbill_FREE_STR2, item_name, mIN_ITEM_NAME_LEN);
    mNpc_LoadMailDataCommon2(mail, pid, anm_id, present, mNpc_GetPaperType(), mail_no);
}

static int mNpc_SendBirthdayCard(PersonalID_c* pid, int player_no, AnmPersonalID_c* anm_id) {
    Mail_c* mail = &l_npc_mail;
    mHm_hs_c* home;
    int free_idx;
    int res = FALSE;

    home = Save_GetPointer(homes[mHS_get_arrange_idx(player_no)]);

    if (mPr_NullCheckPersonalID(pid) == FALSE && mPr_CheckCmpPersonalID(pid, &home->ownerID) == TRUE) {
        mMl_clear_mail(mail);
        free_idx = mMl_chk_mail_free_space(home->mailbox, HOME_MAILBOX_SIZE);

        if (free_idx != -1) {
            mNpc_GetBirthdayCard(mail, pid, anm_id);
            mMl_copy_mail(home->mailbox + free_idx, mail);
            res = TRUE;
        } else if (mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE) {
            mNpc_GetBirthdayCard(mail, pid, anm_id);
            res = mPO_receipt_proc(mail, mPO_SENDTYPE_MAIL);
        }
    }

    return res;
}

extern int mNpc_CheckFriendship(PersonalID_c* pid, Animal_c* animal) {
    int best_idx;
    int idx = -1;

    if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
        best_idx = mNpc_GetHighestFriendshipIdx(animal->memories, ANIMAL_MEMORY_NUM);

        if (best_idx != -1 && mPr_CheckCmpPersonalID(pid, &animal->memories[best_idx].memory_player_id) &&
            Common_Get(now_private)->birthday_present_npc != animal->id.npc_id) {
            idx = best_idx;
        }
    }

    return idx;
}

/* @unused */
/*
extern int mNpc_SendEventBirthdayCard(PersonalID_c* pid) {
  return FALSE; // seemingly stubbed
}
*/

extern int mNpc_SendEventBirthdayCard2(PersonalID_c* pid, int player_no) {
    Animal_c* animal = Save_Get(animals);
    int res = FALSE;
    int i;

    if (pid != NULL && mLd_CheckThisLand(pid->land_name, pid->land_id) == TRUE) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFriendship(pid, animal) != -1 && mNpc_SendBirthdayCard(pid, player_no, &animal->id) == TRUE) {
                res = TRUE;
            }

            animal++;
        }

        if (Common_Get(now_private)->celebrated_birthday_year != Common_Get(time.rtc_time).year) {
            Common_Get(now_private)->birthday_present_npc = EMPTY_NO;
            Common_Get(now_private)->celebrated_birthday_year = Common_Get(time.rtc_time).year;
        }
    }

    return res;
}

static void mNpc_GetXmasCardData(Mail_c* mail, PersonalID_c* pid) {
    int header_back_start;

    mHandbill_Load_HandbillFromRom(mail->content.header, &header_back_start, mail->content.footer, mail->content.body,
                                   0xD7);
    mail->content.header_back_start = header_back_start;
    mail->content.font = mMl_FONT_RECV;
    mail->content.mail_type = mMl_TYPE_XMAS;
    mPr_CopyPersonalID(&mail->header.recipient.personalID, pid);
    mail->header.recipient.type = mMl_NAME_TYPE_PLAYER;
    mail->present = FTR_START(FTR_FAMICOM_COMMON01);
    mail->content.paper_type = 22; // festive paper
}

extern int mNpc_SendEventXmasCard(PersonalID_c* pid, int player_no) {
    Mail_c* mail = &l_npc_mail;
    mHm_hs_c* home;
    int res = FALSE;

    if (mPr_NullCheckPersonalID(pid) == FALSE) {
        home = Save_GetPointer(homes[mHS_get_arrange_idx(player_no)]);

        if (mPr_CheckCmpPersonalID(pid, &home->ownerID) == TRUE) {
            int free_space = mMl_chk_mail_free_space(home->mailbox, HOME_MAILBOX_SIZE);

            if (free_space != -1) {
                mMl_clear_mail(mail);
                mNpc_GetXmasCardData(mail, pid);
                mMl_copy_mail(home->mailbox + free_space, mail);
                res = TRUE;
            }
        }
    }

    return res;
}

extern int mNpc_GetPresentClothMemoryIdx(Anmmem_c* memory) {
    int i;
    int res = -1;

    if (memory != NULL) {
        for (i = 0; i < ANIMAL_MEMORY_NUM; i++) {
            if (memory->letter_info.wearing_present_cloth == TRUE) {
                res = i;
                break;
            }

            memory++;
        }
    }

    return res;
}

extern int mNpc_GetPresentClothMemoryIdx_rnd(Anmmem_c* memory) {
    Anmmem_c* mem_p = memory;
    int selected;
    int cloth_mem = 0;
    int res = -1;
    int i;

    if (memory != NULL) {
        for (i = 0; i < ANIMAL_MEMORY_NUM; i++) {
            if (mNpc_CheckFreeAnimalMemory(memory) == FALSE && memory->letter_info.wearing_present_cloth == TRUE) {
                cloth_mem++;
            }

            memory++;
        }

        if (cloth_mem > 0) {
            selected = RANDOM(cloth_mem);
            memory = mem_p;
            for (i = 0; i < ANIMAL_MEMORY_NUM; i++) {
                if (mNpc_CheckFreeAnimalMemory(memory) == FALSE && memory->letter_info.wearing_present_cloth == TRUE) {
                    if (selected <= 0) {
                        res = i;
                        break;
                    } else {
                        selected--;
                    }
                }

                memory++;
            }
        }
    }

    return res;
}

extern int mNpc_CheckTalkPresentCloth(Animal_c* animal) {
    int res = FALSE;

    if (animal != NULL && mNpc_GetPresentClothMemoryIdx(animal->memories) != -1) {
        res = TRUE;
    }

    return res;
}

extern void mNpc_ChangePresentCloth() {
    Animal_c* animal = Save_Get(animals);
    Anmmem_c* memory;
    mActor_name_t present_cloth;
    int i;
    int j;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        present_cloth = animal->present_cloth;

        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE && present_cloth != EMPTY_NO &&
            ITEM_NAME_GET_TYPE(present_cloth) == NAME_TYPE_ITEM1 &&
            ITEM_NAME_GET_CAT(present_cloth) == ITEM1_CAT_CLOTH) {
            memory = animal->memories;

            for (j = 0; j < ANIMAL_MEMORY_NUM; j++) {
                if (mNpc_CheckFreeAnimalMemory(memory) == FALSE && memory->letter_info.has_present_cloth == TRUE) {
                    memory->letter_info.wearing_present_cloth = TRUE;
                    memory->letter_info.has_present_cloth = FALSE;
                    animal->cloth = present_cloth;
                    break;
                }

                memory++;
            }
        }

        animal++;
    }
}

extern u8* mNpc_GetWordEnding(ACTOR* actor) {
    NPC_ACTOR* npc;
    u8* word_ending;

/* @BUG - devs used & instead of && */
#ifndef BUGFIXES
    if (actor != NULL & actor->part == ACTOR_PART_NPC) {
#else
    if (actor != NULL && actor->part == ACTOR_PART_NPC) {
#endif
        npc = (NPC_ACTOR*)actor;

        if (npc->npc_info.animal != NULL) {
            word_ending = npc->npc_info.animal->catchphrase;
        } else {
            word_ending = l_no_ending_npc_ending;
        }
    } else {
        word_ending = l_no_ending_npc_ending;
    }

    return word_ending;
}

extern void mNpc_ResetWordEnding(NPC_ACTOR* nactorx) {
    if (nactorx != NULL && nactorx->actor_class.part == ACTOR_PART_NPC) {
        Animal_c* animal = nactorx->npc_info.animal;

        if (animal != NULL) {
            mString_Load_StringFromRom(animal->catchphrase, ANIMAL_CATCHPHRASE_LEN,
                                       npc_def_list[animal->id.npc_id & 0xFFF].catchphrase_str_idx);
        }
    }
}

extern int mNpc_GetFreeEventNpcIdx() {
    mNpc_EventNpc_c* event_npc = Common_Get(event_npc);
    int i;

    for (i = 0; i < mNpc_EVENT_NPC_NUM; i++) {
        if (event_npc->in_use == FALSE) {
            return i;
        }

        event_npc++;
    }

    return -1;
}

extern int mNpc_RegistEventNpc(mActor_name_t event_id, mActor_name_t texture_id, mActor_name_t npc_id,
                               mActor_name_t cloth_id) {
    int free_idx = mNpc_GetFreeEventNpcIdx();
    int res = FALSE;

    if (free_idx != -1) {
        mNpc_EventNpc_c* event_npc = Common_GetPointer(event_npc[free_idx]);

        if (cloth_id != EMPTY_NO) {
            int valid = (cloth_id == RSV_CLOTH) || (cloth_id >= ITM_CLOTH_START && cloth_id < ITM_CLOTH_END);

            if (valid == FALSE) {
                cloth_id = ITM_CLOTH000;
            }
        }

        event_npc->event_id = event_id;
        event_npc->texture_id = texture_id;
        event_npc->npc_id = npc_id;
        event_npc->cloth_id = cloth_id;
        event_npc->exists = FALSE;
        event_npc->in_use = TRUE;

        res = TRUE;
    }

    return res;
}

extern void mNpc_UnRegistEventNpc(mNpc_EventNpc_c* npc) {
    mNpc_EventNpc_c* event_npc = Common_Get(event_npc);
    int i;

    for (i = 0; i < mNpc_EVENT_NPC_NUM; i++) {
        if (event_npc == npc) {
            bzero(npc, sizeof(mNpc_EventNpc_c));
            break;
        }

        event_npc++;
    }
}

extern void mNpc_ClearEventNpc() {
    bzero(Common_Get(event_npc), mNpc_EVENT_NPC_NUM * sizeof(mNpc_EventNpc_c));
}

extern mNpc_EventNpc_c* mNpc_GetSameEventNpc(mActor_name_t event_id) {
    mNpc_EventNpc_c* event_npc = Common_Get(event_npc);
    int i;

    for (i = 0; i < mNpc_EVENT_NPC_NUM; i++) {
        if (event_npc->event_id == event_id) {
            return event_npc;
        }

        event_npc++;
    }

    return NULL;
}

extern int mNpc_GetFreeMaskNpcIdx() {
    mNpc_MaskNpc_c* mask_npc = Common_Get(mask_npc);
    int i;

    for (i = 0; i < mNpc_MASK_NPC_NUM; i++) {
        if (mask_npc->in_use == FALSE) {
            return i;
        }

        mask_npc++;
    }

    return -1;
}

extern int mNpc_RegistMaskNpc(mActor_name_t mask_id, mActor_name_t npc_id, mActor_name_t cloth_id) {
    int free_idx = mNpc_GetFreeMaskNpcIdx();
    int res = FALSE;

    if (free_idx != -1) {
        mNpc_MaskNpc_c* mask_npc = Common_GetPointer(mask_npc[free_idx]);

        if (cloth_id != EMPTY_NO) {
            int valid = (cloth_id == RSV_CLOTH) || (cloth_id >= ITM_CLOTH_START && cloth_id < ITM_CLOTH_END);

            if (valid == FALSE) {
                cloth_id = ITM_CLOTH000;
            }
        }

        mask_npc->mask_id = mask_id;
        mask_npc->npc_id = npc_id;
        mask_npc->exists = FALSE;
        mask_npc->in_use = TRUE;

        if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
            int animal_idx = mNpc_SearchAnimalinfo(Save_Get(animals), npc_id, ANIMAL_NUM_MAX);

            if (animal_idx != -1) {
                mNpc_CopyAnimalInfo(&mask_npc->animal_data, Save_GetPointer(animals[animal_idx]));
            } else {
                mNpc_ClearAnimalInfo(&mask_npc->animal_data);
                mNpc_SetDefAnimal(&mask_npc->animal_data, npc_id, npc_def_list);
            }

            if (cloth_id == EMPTY_NO) {
                mask_npc->cloth_id = mask_npc->animal_data.cloth;
            } else {
                mask_npc->cloth_id = cloth_id;
            }
        } else {
            mask_npc->cloth_id = cloth_id;
        }

        res = TRUE;
    }

    return res;
}

extern void mNpc_UnRegistMaskNpc(mNpc_MaskNpc_c* npc) {
    mNpc_MaskNpc_c* mask_npc = Common_Get(mask_npc);
    int i;

    for (i = 0; i < mNpc_MASK_NPC_NUM; i++) {
        if (mask_npc == npc) {
            bzero(npc, sizeof(mNpc_MaskNpc_c));
            break;
        }

        mask_npc++;
    }
}

extern void mNpc_ClearMaskNpc() {
    bzero(Common_Get(mask_npc), mNpc_MASK_NPC_NUM * sizeof(mNpc_MaskNpc_c));
}

extern mNpc_MaskNpc_c* mNpc_GetSameMaskNpc(mActor_name_t mask_id) {
    mNpc_MaskNpc_c* mask_npc = Common_Get(mask_npc);
    int i;

    for (i = 0; i < mNpc_MASK_NPC_NUM; i++) {
        if (mask_npc->mask_id == mask_id) {
            return mask_npc;
        }

        mask_npc++;
    }

    return NULL;
}

extern u8 mNpc_GetLooks(mActor_name_t npc_id) {
    u8 looks = mNpc_LOOKS_GIRL;

    if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
        looks = npc_looks_table[npc_id & 0xFFF];
    }

    return looks;
}

static void mNpc_SetDefAnimalInfo(Animal_c* animal, mActor_name_t npc_id, u8 looks, mNpc_Default_Data_c* def_data) {
    mLd_land_info_c* land_info = Save_GetPointer(land_info);

    if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
        animal->id.npc_id = npc_id;
        animal->id.looks = looks;
        animal->cloth = def_data->cloth;
        animal->umbrella_id = def_data->umbrella;
        mString_Load_StringFromRom(animal->catchphrase, ANIMAL_CATCHPHRASE_LEN, def_data->catchphrase_str_idx);
        animal->id.land_id = land_info->id;
        mLd_CopyLandName(animal->id.land_name, land_info->name);
    }
}

extern void mNpc_SetDefAnimalCloth(Animal_c* animal) {
    mActor_name_t npc_id = animal->id.npc_id;

    if (ITEM_NAME_GET_TYPE(npc_id) != NAME_TYPE_NPC) {
        return;
    }

    if ((npc_id & 0xFFF) < 0) {
        return;
    }

    if ((npc_id & 0xFFF) >= NPC_NUM) {
        return;
    }

    animal->cloth = npc_def_list[npc_id & 0xFFF].cloth;
    animal->cloth_original_id = 0xFF;
}

extern void mNpc_SetDefAnimalUmbrella(Animal_c* animal) {
    mActor_name_t npc_id = animal->id.npc_id;

    if (ITEM_NAME_GET_TYPE(npc_id) != NAME_TYPE_NPC) {
        return;
    }

    if ((npc_id & 0xFFF) < 0) {
        return;
    }

    if ((npc_id & 0xFFF) >= NPC_NUM) {
        return;
    }

    animal->umbrella_id = npc_def_list[npc_id & 0xFFF].umbrella;
}

extern void mNpc_SetDefAnimal(Animal_c* animal, mActor_name_t npc_id, mNpc_Default_Data_c* def_data) {
    int idx = npc_id & 0xFFF;

    if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
        mNpc_SetDefAnimalInfo(animal, npc_id, npc_looks_table[idx], &def_data[idx]);
    }
}

static void mNpc_SetHaveAppeared(mActor_name_t npc_id) {
    u8* used_tbl = Save_Get(npc_used_tbl);
    int idx;
    int i;

    if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
        idx = npc_id & 0xFFF;
        i = idx / 8;
        
        if (i < ARRAY_COUNT(Save_Get(npc_used_tbl))) {
            used_tbl += i;
            idx = idx & 7u;
            *used_tbl |= 1 << idx;
        }
    }
}

static int mNpc_GetHaveAppeared_idx(int idx) {
    u8* used_tbl = Save_Get(npc_used_tbl);
    int i = idx / 8;
    int res = TRUE;

    if (i < ARRAY_COUNT(Save_Get(npc_used_tbl))) {
        used_tbl += i;
        res = (*used_tbl >> (idx & 7u)) & 1;
    }

    return res;
}

static int mNpc_GetDefGrowPermission(int idx, s8* grow_list, int count) {
    int res = mNpc_GROW_MOVE_IN;

    if (idx < count) {
        res = grow_list[idx];
    }

    return res;
}

static int mNpc_GetLooks2NotHaveAppearedNum(u8 looks) {
    u8* looks_tbl;
    s8* grow_list = npc_grow_list;
    int num = 0;
    int i;

    if (looks < mNpc_LOOKS_NUM) {
        looks_tbl = npc_looks_table;

        for (i = 0; i < NPC_NUM; i++) {
            if (looks == looks_tbl[0]) {
                int grow_type = mNpc_GetDefGrowPermission(i, grow_list, NPC_NUM);

                if (mNpc_GetHaveAppeared_idx(i) == FALSE &&
                    (grow_type == mNpc_GROW_STARTER || grow_type == mNpc_GROW_MOVE_IN)) {
                    num++;
                }
            }

            looks_tbl++;
        }
    }

    return num;
}

static void mNpc_ResetHaveAppeared_common(u8* npc_used_tbl, Animal_c* animal) {
    int i;

    bzero(npc_used_tbl, sizeof(Save_Get(npc_used_tbl)));
    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            mNpc_SetHaveAppeared(animal->id.npc_id);
        }

        animal++;
    }
}

static void mNpc_ResetHaveAppeared() {
    s8* grow_list = npc_grow_list;
    int i;

    for (i = 0; i < NPC_NUM; i++) {
        u32 grow_perm = mNpc_GetDefGrowPermission(i, grow_list, NPC_NUM);

        if (mNpc_GetHaveAppeared_idx(i) == FALSE && grow_perm <= mNpc_GROW_MOVE_IN) {
            break;
        }
    }

    /* All animals have appeared in town (islanders excluded) */
    if (i == NPC_NUM) {
        mNpc_ResetHaveAppeared_common(Save_Get(npc_used_tbl), Save_Get(animals));
    }
}

static void mNpc_DecideLivingNpcMax(Animal_c* animal, u8 count, int malloc_flag) {
    static int fakeTable[NPC_NUM];

    mNpc_Default_Data_c* def_list;
    s8* grow_list;
    u8 looks_bitfield = 0;
    int i = 0;
    int animal_idx = 0;

    bzero(fakeTable, sizeof(fakeTable));
    mNpc_MakeRandTable(fakeTable, NPC_NUM, NPC_NUM);
    def_list = npc_def_list;
    grow_list = npc_grow_list;

    while (count != 0) {
        if (animal == NULL) {
            break;
        }

        if (animal->id.npc_id == EMPTY_NO) {
            int idx = fakeTable[i];
            mActor_name_t npc_id = NPC_START | idx;
            int grow_perm = mNpc_GetDefGrowPermission(idx, grow_list, NPC_NUM);

            if (grow_perm == mNpc_GROW_STARTER) {
                int looks = npc_looks_table[idx];

                if (((looks_bitfield >> looks) & 1) == 0) {
                    mNpc_SetDefAnimal(animal, npc_id, def_list);
                    looks_bitfield |= (1 << looks);
                    mNpc_SetHaveAppeared(npc_id);
                    mNpc_ResetAnimalRelation(animal_idx);
                    animal++;
                    animal_idx++;
                    count--;
                }
            } else if (grow_perm == -1) {
                mNpc_SetHaveAppeared(npc_id);
            }
        } else {
            animal++;
            ;
            animal_idx++;
            count--;
        }

        i++;
    }
}

extern void mNpc_SetAnimalTitleDemo(mNpc_demo_npc_c* demo_npc, Animal_c* animal, GAME* game) {
    mNpc_Default_Data_c* def_list = npc_def_list;
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
#ifdef TARGET_PC
        /* Keep title-demo animal slots deterministic across repeated demo loops. */
        mNpc_ClearAnimalInfo(animal);

        if (ITEM_NAME_GET_TYPE(demo_npc->npc_name) == NAME_TYPE_NPC) {
#endif
        mNpc_SetDefAnimal(animal, demo_npc->npc_name, def_list);
        animal->home_info.type_unused = 0;
        animal->home_info.block_x = demo_npc->block_x;
        animal->home_info.block_z = demo_npc->block_z;
        animal->home_info.ut_x = demo_npc->ut_x;
        animal->home_info.ut_z = demo_npc->ut_z;
#ifdef TARGET_PC
        }
#endif

        animal++;
        demo_npc++;
    }
}

/* @unused */
extern int mNpc_GetReservedUtNum(int* ut_x, int* ut_z, mActor_name_t* item) {
    f32 reserve_num = 0.0f;
    int rand;
    int res = FALSE;
    int i;

    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if ((*item >= SIGN00 && *item < WISHING_WELL) || *item == DUMMY_RESERVE) {
            reserve_num++;
        }

        item++;
    }

    if (reserve_num > 0.0f) {
        item -= UT_TOTAL_NUM;
        rand = RANDOM(reserve_num);

        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if ((*item >= SIGN00 && *item < WISHING_WELL) || *item == DUMMY_RESERVE) {
                if (rand == 0) {
                    *ut_x = i % UT_Z_NUM;
                    *ut_z = i / UT_X_NUM;
                    res = TRUE;

                    break;
                } else {
                    rand--;
                }
            }

            item++;
        }
    }

    return res;
}

/* @unused */
extern int mNpc_BlockNum2ReservedUtNum(int* ut_x, int* ut_z, int bx, int bz) {
    mActor_name_t* items = mFI_BkNumtoUtFGTop(bx, bz);
    int res = FALSE;

    if (items != NULL) {
        res = mNpc_GetReservedUtNum(ut_x, ut_z, items);
    }

    return res;
}

extern void mNpc_MakeReservedListBeforeFieldct(Anmhome_c* reserved, int reserved_num, u8* reserved_count) {
    mFM_fg_c* fg = Save_GetPointer(fg[0][0]);
    Anmhome_c* reserved_p = reserved;
    mActor_name_t* item;
    u8 num = 0;
    u8 i;
    u8 j;
    u8 k;
    u8 l;

    for (i = 0; i < reserved_num; i++) {
        reserved->block_x = -1;
        reserved->block_z = -1;
        reserved->ut_x = -1;
        reserved->ut_z = -1;
        reserved++;
    }

    reserved = reserved_p;
    for (i = 0; i < FG_BLOCK_Z_NUM; i++) {
        for (j = 0; j < FG_BLOCK_X_NUM; j++) {
            item = &fg->items[0][0];

            for (k = 0; k < UT_Z_NUM; k++) {
                for (l = 0; l < UT_X_NUM; l++) {
                    if (mNT_IS_RESERVE(*item)) {
                        num++;
                        reserved->block_x = j + 1;
                        reserved->block_z = i + 1;
                        reserved->ut_x = l;
                        reserved->ut_z = k;
                        reserved++;
                        if (num >= reserved_num) {
                            *reserved_count = num;
                            return;
                        }
                    }

                    item++;
                }
            }

            fg++;
        }
    }

    *reserved_count = num;
}

extern void mNpc_MakeReservedListAfterFieldct(Anmhome_c* reserved, int reserved_num, u8* reserved_count, u8 bx_max,
                                              u8 bz_max) {
    mFM_block_info_c* block_info = mFI_GetBlockTopP();
    Anmhome_c* reserved_p = reserved;
    mActor_name_t* item;
    u8 num = 0;
    u8 i;
    u8 j;
    u8 k;
    u8 l;

    for (i = 0; i < reserved_num; i++) {
        reserved->block_x = -1;
        reserved->block_z = -1;
        reserved->ut_x = -1;
        reserved->ut_z = -1;
        reserved++;
    }

    reserved = reserved_p;
    for (i = 0; i < bz_max; i++) {
        for (j = 0; j < bx_max; j++) {
            item = block_info->fg_info.items_p;

            for (k = 0; k < UT_Z_NUM; k++) {
                for (l = 0; l < UT_X_NUM; l++) {
                    if (mNT_IS_RESERVE(*item)) {
                        num++;
                        reserved->block_x = j;
                        reserved->block_z = i;
                        reserved->ut_x = l;
                        reserved->ut_z = k;
                        reserved++;
                        if (num >= reserved_num) {
                            *reserved_count = num;
                            return;
                        }
                    }

                    item++;
                }
            }

            block_info++;
        }
    }

    *reserved_count = num;
}

static void mNpc_BuildHouseBeforeFieldct(mActor_name_t npc_id, int bx, int bz, int ut_x, int ut_z) {
    static int ut_d[9][2] = { { 0, 0 }, { -1, 1 },  { 0, 1 },  { 1, 1 }, { -1, 0 },
                              { 1, 0 }, { -1, -1 }, { 0, -1 }, { 1, -1 } };

    static mActor_name_t set_fg[9] = { EMPTY_NO, // npc house id
                                       ACTOR_PROP_VILLAGER_SIGNBOARD,
                                       RSV_NO,
                                       RSV_NO,
                                       RSV_NO,
                                       RSV_NO,
                                       RSV_NO,
                                       RSV_NO,
                                       RSV_NO };

    u16* deposit;
    mFM_fg_c* fg;
    int x;
    int z;
    int i;
    mActor_name_t house = npc_id - 0x10000 + 0x7000; // this shifts it to the house range 0x50XX

    if (bx >= 0 && bx < FG_BLOCK_X_NUM && bz >= 0 && bz < FG_BLOCK_Z_NUM && ut_x > 0 && ut_x < (UT_X_NUM - 1) &&
        ut_z > 0 && ut_z < (UT_Z_NUM - 1)) {
        set_fg[0] = house;
        fg = Save_GetPointer(fg[bz][bx]);

        deposit = mFI_GetDepositP(bx + 1, bz + 1);

        for (i = 0; i < ARRAY_COUNT(set_fg); i++) {
            x = ut_d[i][0] + ut_x;
            z = ut_d[i][1] + ut_z;

            mPB_keep_item(fg->items[z][x]);
            if (deposit != NULL) {
                mFI_BlockDepositOFF(deposit, x, z);
            }

            fg->items[z][x] = set_fg[i];
        }
    }
}

static void mNpc_DestroyHouse(Anmhome_c* home) {
    u8 bx = home->block_x - 1;
    u8 bz = home->block_z - 1;
    u8 ut_x = home->ut_x;
    u8 ut_z = home->ut_z - 1;

    if (bx < FG_BLOCK_X_NUM && bz < FG_BLOCK_Z_NUM && ut_x > 0 && ut_x < (UT_X_NUM - 1) && ut_z > 0 &&
        ut_z < (UT_Z_NUM - 1)) {
        mActor_name_t reserve_no = mFM_GetReseveName(home->block_x, home->block_z);

        Save_Get(fg[bz][bx]).items[ut_z][ut_x] = reserve_no;
        Save_Get(fg[bz][bx]).items[ut_z + 1][ut_x - 1] = EMPTY_NO;
        Save_Get(fg[bz][bx]).items[ut_z + 1][ut_x] = EMPTY_NO;
        Save_Get(fg[bz][bx]).items[ut_z + 1][ut_x + 1] = EMPTY_NO;
        Save_Get(fg[bz][bx]).items[ut_z][ut_x - 1] = EMPTY_NO;
        Save_Get(fg[bz][bx]).items[ut_z][ut_x + 1] = EMPTY_NO;
        Save_Get(fg[bz][bx]).items[ut_z - 1][ut_x - 1] = EMPTY_NO;
        Save_Get(fg[bz][bx]).items[ut_z - 1][ut_x] = EMPTY_NO;
        Save_Get(fg[bz][bx]).items[ut_z - 1][ut_x + 1] = EMPTY_NO;
    }
}

static void mNpc_SetNpcHome(Animal_c* animal, Anmhome_c* reserved, u8 reserved_num) {
    static int fakeTable[60];

    Anmhome_c* home;
    int* fake_table_p = fakeTable;
    int n = 0;
    int i;
    int idx;

    if (reserved_num > ARRAY_COUNT(fakeTable)) {
        reserved_num = ARRAY_COUNT(fakeTable);
    }

    if (reserved_num > 0) {
        bzero(fake_table_p, sizeof(fakeTable));
        mNpc_MakeRandTable(fake_table_p, reserved_num, ARRAY_COUNT(fakeTable) / 2);

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (ITEM_NAME_GET_TYPE(animal->id.npc_id) == NAME_TYPE_NPC && animal->home_info.block_x == 0xFF &&
                animal->home_info.block_z == 0xFF) {
                idx = fake_table_p[n];

                if (idx >= reserved_num) {
                    while ((fake_table_p[n] >= reserved_num) && n < reserved_num) {
                        n++;
                    }

                    if (n >= reserved_num) {
                        return;
                    }

                    idx = fake_table_p[n];
                }

                if (idx < reserved_num) {
                    home = &reserved[idx];

                    animal->home_info.block_x = home->block_x;
                    animal->home_info.block_z = home->block_z;
                    animal->home_info.ut_x = home->ut_x;
                    animal->home_info.ut_z = home->ut_z + 1;
                    mNpc_BuildHouseBeforeFieldct(animal->id.npc_id, animal->home_info.block_x - 1,
                                                 animal->home_info.block_z - 1, animal->home_info.ut_x, home->ut_z);
                }

                n++;
            }

            if (n >= reserved_num) {
                break;
            }

            animal++;
        }
    }
}

extern void mNpc_InitNpcData() {
    static Anmhome_c reserved[60];

    u8 reserved_num = 0;

    mNpc_MakeReservedListBeforeFieldct(reserved, ARRAY_COUNT(reserved), &reserved_num);
    mNpc_SetNpcHome(Save_Get(animals), reserved, reserved_num);
}

extern void mNpc_InitNpcList(mNpc_NpcList_c* npclist, int count) {
    int i;

    if (npclist != NULL) {
        bzero(npclist, count * sizeof(mNpc_NpcList_c));

        for (i = 0; i < count; i++) {
            npclist->name = EMPTY_NO;
            npclist->field_name = RSV_NO;
            mQst_ClearQuestInfo(&npclist->quest_info);
            npclist->house_data.type = 0xFF;
            npclist->house_data.palette = 0xFF;
            npclist->house_data.wall_id = 0xFF;
            npclist->house_data.floor_id = 0xFF;
            npclist->house_data.main_layer_id = 203;

            npclist++;
        }
    }
}

extern void mNpc_SetNpcList(mNpc_NpcList_c* npclist, Animal_c* animal, int count, int malloc_flag) {
    xyz_t pos;
    mActor_name_t npc_id;
    int i;
    mNpc_NpcHouseData_c* house_list = npc_house_list;

    for (i = 0; i < count; i++) {
        npc_id = animal->id.npc_id;

        if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC && animal->home_info.block_x != 0xFF) {
            npclist->name = npc_id;

            npclist->house_position.x = animal->home_info.block_x * mFI_BK_WORLDSIZE_X_F;
            npclist->house_position.z = animal->home_info.block_z * mFI_BK_WORLDSIZE_Z_F;
            mFI_UtNum2PosXZInBk(&pos.x, &pos.z, animal->home_info.ut_x, animal->home_info.ut_z);
            npclist->house_position.x += pos.x;
            npclist->house_position.z += pos.z;
            npclist->house_position.y = 0.0f;

            npclist->position.x = npclist->house_position.x;
            npclist->position.y = npclist->house_position.y;
            npclist->position.z = npclist->house_position.z;

            npclist->appear_flag = TRUE;
            npclist->reward_furniture = EMPTY_NO;

            npclist->house_data.type = house_list[npc_id & 0xFFF].type;
            npclist->house_data.palette = house_list[npc_id & 0xFFF].palette;
            npclist->house_data.wall_id = house_list[npc_id & 0xFFF].wall_id;
            npclist->house_data.floor_id = house_list[npc_id & 0xFFF].floor_id;
            npclist->house_data.main_layer_id = house_list[npc_id & 0xFFF].main_layer_id;
            npclist->house_data.secondary_layer_id = house_list[npc_id & 0xFFF].secondary_layer_id;
        }

        npclist++;
        animal++;
    }
}

extern void mNpc_SetNpcinfo(ACTOR* actor, s8 npc_info_idx) {
    if (actor->part == ACTOR_PART_NPC) {
        NPC_ACTOR* npc = (NPC_ACTOR*)actor;
        mActor_name_t npc_id = actor->npc_id;

        if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_SPNPC) {
            mNpc_EventNpc_c* event_npc = mNpc_GetSameEventNpc(npc_id);

            if (event_npc != NULL) {
                npc_info_idx = mNpc_SearchAnimalinfo(Save_Get(animals), event_npc->npc_id, ANIMAL_NUM_MAX);
            }
        }

        if (npc_info_idx >= 0 && npc_info_idx < ANIMAL_NUM_MAX) {
            npc->npc_info.animal = Save_GetPointer(animals[npc_info_idx]);
            npc->npc_info.list = Common_GetPointer(npclist[npc_info_idx]);
        } else if (npc_info_idx == -ANIMAL_NUM_MAX) {
            npc->npc_info.animal = &Save_Get(island).animal;
            npc->npc_info.list = Common_GetPointer(island_npclist[0]);
        } else {
            mNpc_MaskNpc_c* mask_npc = mNpc_GetSameMaskNpc(npc_id);

            if (mask_npc != NULL) {
                if (ITEM_NAME_GET_TYPE(mask_npc->npc_id) == NAME_TYPE_NPC) {
                    npc->npc_info.animal = &mask_npc->animal_data;
                    npc->npc_info.list = NULL;
                } else {
                    npc->npc_info.animal = NULL;
                    npc->npc_info.list = NULL;
                }
            } else {
                npc->npc_info.animal = NULL;
                npc->npc_info.list = NULL;
            }
        }
    }
}

static void mNpc_AddNpc_inNpcRoom(mFM_move_actor_c* move_actor, int move_actor_idx, u8 bx, u8 bz) {
    u32 owner_id = Common_Get(house_owner_name);
    mActor_name_t id = owner_id;

    if (id != RSV_NO) {
        if (id != EMPTY_NO && mEvNM_CheckJointEvent(owner_id) != TRUE) {
            int idx = mNpc_SearchAnimalinfo(Save_Get(animals), id, ANIMAL_NUM_MAX);

            if (idx != -1) {
                move_actor->name_id = id;
                move_actor->ut_x = 4;
                move_actor->ut_z = 7;
                move_actor->npc_info_idx = idx;
                move_actor->arg = -1;
                mFI_SetMoveActorBitData_ON(move_actor_idx, bx, bz);
            }
        }
    }
}

static void mNpc_AddNpc_inNpcRoomIsland(mFM_move_actor_c* move_actor, int move_actor_idx, u8 bx, u8 bz) {
    move_actor->name_id = Save_Get(island).animal.id.npc_id;
    move_actor->ut_x = 4;
    move_actor->ut_z = 7;
    move_actor->npc_info_idx = -ANIMAL_NUM_MAX;
    move_actor->arg = -1;
    mFI_SetMoveActorBitData_ON(move_actor_idx, bx, bz);
}

static void mNpc_AddNpc_inKamakura(mFM_move_actor_c* move_actor, int move_actor_idx, u8 bx, u8 bz) {
    u8* kamakura_event = (u8*)mEv_get_save_area(mEv_EVENT_KAMAKURA, 15);

    if (kamakura_event != NULL) {
        int idx = *kamakura_event;
        mActor_name_t npc_id = Save_Get(animals[idx]).id.npc_id;

        mEvMN_GetEventNpcName(&npc_id, mEv_EVENT_KAMAKURA, idx, 0);
        move_actor->name_id = npc_id;
        move_actor->ut_x = 4;
        move_actor->ut_z = 7;
        move_actor->npc_info_idx = idx;
        move_actor->arg = -1;
        mFI_SetMoveActorBitData_ON(move_actor_idx, bx, bz);
    }
}

extern void mNpc_AddNpc_inBlock(mFM_move_actor_c* move_actor_list, u8 bx, u8 bz) {
    int scene = Save_Get(scene_no);

    if ((scene == SCENE_NPC_HOUSE || scene == SCENE_KAMAKURA || scene == SCENE_COTTAGE_NPC) &&
        move_actor_list != NULL) {
        mActor_name_t field_id = mFI_GetFieldId(); // unused
        int move_actor_idx = mFI_GetMoveActorListIdx(move_actor_list, mFM_MOVE_ACTOR_NUM, EMPTY_NO);

        if (move_actor_idx != -1 && move_actor_idx < ANIMAL_NUM_MAX) {
            move_actor_list += move_actor_idx;

            switch (scene) {
                case SCENE_NPC_HOUSE:
                    mNpc_AddNpc_inNpcRoom(move_actor_list, move_actor_idx, bx, bz);
                    break;
                case SCENE_COTTAGE_NPC:
                    mNpc_AddNpc_inNpcRoomIsland(move_actor_list, move_actor_idx, bx, bz);
                    break;
                case SCENE_KAMAKURA:
                    mNpc_AddNpc_inKamakura(move_actor_list, move_actor_idx, bx, bz);
                    break;
            }
        }
    }
}

extern void mNpc_RenewalNpcRoom(s16* wall_floor) {
    mActor_name_t field_id = mFI_GetFieldId();
    mActor_name_t owner_id = Common_Get(house_owner_name);
    int island_wall = 0;
    int island_floor = 0;
    u8 wall = 0;
    u8 floor = 0;
    int island_room_ftr_num;

    if (Save_Get(scene_no) == SCENE_COTTAGE_NPC) {
        wall = 8;   // exotic wall
        floor = 32; // bamboo flooring
        island_room_ftr_num = mNpc_GetIslandRoomFtrNum();

        if (island_room_ftr_num >= 2) {
            mNpc_GetIslandWallFloorIdx(&island_wall, &island_floor, Save_Get(island).animal.id.npc_id);
            wall = island_wall;

            if (island_room_ftr_num >= 5) {
                floor = island_floor;
            }
        }
    } else if (mFI_GET_TYPE(field_id) == mFI_FIELD_NPCROOM0 && owner_id != EMPTY_NO && owner_id != RSV_NO) {
        int idx = mNpc_SearchAnimalinfo(Save_Get(animals), owner_id, ANIMAL_NUM_MAX);
        mNpc_NpcList_c* npclist;

        if (idx == -1) {
            idx = 0;
        }

        npclist = Common_GetPointer(npclist[idx]);

        wall = npclist->house_data.wall_id;
        floor = npclist->house_data.floor_id;
    }

    wall_floor[0] = (wall << 8) | floor;
}

extern void mNpc_RenewalSetNpc(ACTOR* actor) {
    NPC_ACTOR* npc = (NPC_ACTOR*)actor;
    Animal_c* animal;

    if (npc->npc_info.list != NULL) {
        mActor_name_t field_id = mFI_GetFieldId();
        mNpc_NpcList_c* npclist = npc->npc_info.list;
        xyz_t* npc_pos = &npclist->position;

        if (mFI_GET_TYPE(field_id) == mFI_FIELD_FG) {
            xyz_t_move(npc_pos, &actor->world.position);
            npclist->appear_flag = TRUE;
            animal = &Save_Get(island).animal;

            if (actor->npc_id == animal->id.npc_id) {
                int bnum = mFI_GetBlockNum(actor->block_x, actor->block_z);
                mFM_move_actor_c* move_actor_list = g_fdinfo->block_info[bnum].fg_info.move_actors;

                if (move_actor_list != NULL) {
                    int move_actor_idx = mFI_GetMoveActorListIdx(move_actor_list, mFM_MOVE_ACTOR_NUM, actor->npc_id);

                    if (move_actor_idx != -1) {
                        int bx;
                        int bz;
                        int ut_x;
                        int ut_z;

                        if (mFI_Wpos2BkandUtNuminBlock(&bx, &bz, &ut_x, &ut_z, npclist->position) == FALSE) {
                            ut_x = animal->home_info.ut_x;
                            ut_z = animal->home_info.ut_z;
                        } else if (mNpc_CheckNpcSet(bx, bz, ut_x, ut_z) == FALSE &&
                                   mNpc_GetMakeUtNuminBlock_area(&ut_x, &ut_z, bx, bz, 0) == FALSE) {
                            ut_x = animal->home_info.ut_x;
                            ut_z = animal->home_info.ut_z;
                        }

                        move_actor_list[move_actor_idx].ut_x = ut_x;
                        move_actor_list[move_actor_idx].ut_z = ut_z;
                    }
                }

                mFI_MyMoveActorBitData_ON(actor);
            }
        }
    } else {
        mFI_MyMoveActorBitData_ON(actor);
    }
}

extern int mNpc_GetFriendAnimalNum(PersonalID_c* pid) {
    Animal_c* animal = Save_Get(animals);
    int num = 0;
    int i;

    if (pid != NULL) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE &&
                mNpc_GetAnimalMemoryIdx(pid, animal->memories, ANIMAL_MEMORY_NUM) != -1) {
                num++;
            }

            animal++;
        }
    }

    return num;
}

extern int mNpc_CheckFriendAllAnimal(PersonalID_c* pid) {
    int now_npc_max = Save_Get(now_npc_max);
    int friend_num = mNpc_GetFriendAnimalNum(pid);

    if (now_npc_max <= friend_num) {
        return TRUE;
    }

    return FALSE;
}

static int mNpc_CheckSelectFurniture(mActor_name_t item) {
    int res = FALSE;

    if (!(item >= FTR_CLOTH_START && item <= FTR_CLOTH_END) &&       // Clothing (furniture)
        !(item >= FTR_UMBRELLA_START && item <= FTR_UMBRELLA_END) && // Umbrellas (furniture)
        !(item >= FTR_INSECT_START && item <= FTR_INSECT_END) &&     // Insects (furniture)
        !(item >= FTR_FISH_START && item <= FTR_FISH_END) &&         // Fish (furniture)
        !(item >= HANIWA_START && item <= HANIWA_END) &&             // Gyroids
        !(item >= FTR_DINO_START && item <= FTR_DINO_END) &&         // Idenitfied fossils
        !(item >= FTR_START(FTR_FAMICOM_COMMON00) && item <= FTR_END(FTR_FAMICOM_COMMON18)) // NES/Famicom games
    ) {
        res = TRUE;
    }

    return res;
}

static mActor_name_t mNpc_DecideNpcFurniture(mFM_fg_data_c** fg_data_table, mNpc_NpcList_c* npclist, int fg_base_id) {
    int data_idx = npclist->house_data.main_layer_id - fg_base_id;
    mActor_name_t* fg_items;
    u8 num = 0;
    int ut_z;
    int ut_x;

    if (data_idx < 0) {
        data_idx = 0;
    }

    fg_items = fg_data_table[data_idx]->items[0];

    for (ut_z = 0; ut_z < 10; ut_z++) {
        for (ut_x = 0; ut_x < 10; ut_x++) {
            if (ITEM_IS_FTR(*fg_items) && mNpc_CheckSelectFurniture(*fg_items) == TRUE) {
                num++;
            }

            fg_items++;
        }

        fg_items += UT_X_NUM - 10;
    }

    if (num != 0) {
        num = RANDOM(num);

        fg_items = fg_data_table[data_idx]->items[0];
        for (ut_z = 0; ut_z < 10; ut_z++) {
            for (ut_x = 0; ut_x < 10; ut_x++) {
                if (ITEM_IS_FTR(*fg_items) && mNpc_CheckSelectFurniture(*fg_items) == TRUE) {
                    if (num <= 0) {
                        return *fg_items;
                    } else {
                        num--;
                    }
                }

                fg_items++;
            }

            fg_items += UT_X_NUM - 10;
        }
    }

    return EMPTY_NO;
}

extern void mNpc_SetNpcFurnitureRandom(mFM_fg_data_c** fg_data_table, int fg_base_id) {
    mNpc_NpcList_c* npclist = Common_Get(npclist);
    Animal_c* animal = Save_Get(animals);
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            npclist->reward_furniture = mNpc_DecideNpcFurniture(fg_data_table, npclist, fg_base_id);
        }

        npclist++;
        animal++;
    }
}

extern mActor_name_t mNpc_GetNpcFurniture(AnmPersonalID_c* anm_id) {
    mActor_name_t furniture = EMPTY_NO;
    int idx = mNpc_SearchAnimalPersonalID(anm_id);

    if (idx != -1) {
        furniture = Common_Get(npclist[idx]).reward_furniture;
    }

    return furniture;
}

static Animal_c l_mnpc_remove_in_animal;

extern void mNpc_ClearInAnimal() {
    mNpc_ClearAnimalInfo(&l_mnpc_remove_in_animal);
}

extern Animal_c* mNpc_GetInAnimalP() {
    return &l_mnpc_remove_in_animal;
}

static void mNpc_RenewRemoveHistory() {
    mTM_set_renew_time(Save_GetPointer(force_remove_date), Common_GetPointer(time.rtc_time));
}

static int mNpc_DecideRemoveAnimalNo_Friend(Animal_c* animal, int ignored_idx, int met_all_flag) {
    int res;
    Private_c* priv_p;
    int n_players;
    int num_possible;
    u16 remove_bitfield;
    int met;
    int selected;
    int i;
    int j;

    res = -1;
    n_players = 0;
    num_possible = 0;
    remove_bitfield = 0;
    priv_p = Save_Get(private_data);

    for (i = 0; i < PLAYER_NUM; i++) {
        if (mPr_NullCheckPersonalID(&priv_p->player_ID) == FALSE) {
            n_players++;
        }

        priv_p++;
    }

    if (n_players > 0) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalInfo(animal) == FALSE && i != ignored_idx) {
                met = 0;
                priv_p = Save_Get(private_data);

                for (j = 0; j < PLAYER_NUM; j++) {
                    if (mPr_NullCheckPersonalID(&priv_p->player_ID) == FALSE) {
                        if (mNpc_GetAnimalMemoryIdx(&priv_p->player_ID, animal->memories, ANIMAL_MEMORY_NUM) == -1) {
                            break;
                        }

                        met++;
                    }

                    priv_p++;
                }

                if (met_all_flag == TRUE) {
                    if (met == n_players) {
                        remove_bitfield |= (1 << i);
                        num_possible++;
                    }
                } else if (met > 0) {
                    remove_bitfield |= (1 << i);
                    num_possible++;
                }
            }

            animal++;
        }
    }

    if (num_possible > 0) {
        selected = RANDOM(num_possible);

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (((remove_bitfield >> i) & 1) == 1) {
                if (selected <= 0) {
                    res = i;
                    break;
                } else {
                    selected--;
                }
            }
        }
    }

    return res;
}

static int mNpc_DecideRemoveAnimalNo(Animal_c* animal, int ignored_idx, int now_npc_max) {
    int i;
    int selected;
    int res = -1;

    if (ignored_idx >= 0 || ignored_idx < ANIMAL_NUM_MAX) {
        now_npc_max--;
    }

    if (now_npc_max > 0 && now_npc_max <= ANIMAL_NUM_MAX) {
        selected = RANDOM(now_npc_max);

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
                if (selected <= 0 && ignored_idx != i) {
                    res = i;
                    break;
                } else {
                    selected--;
                }
            }

            animal++;
        }
    }

    return res;
}

/* 50% */

extern void mNpc_SetRemoveAnimalNo(u8* remove_animal_no, Animal_c* animal, int ignored_idx) {
    u8 now_npc_max = Save_Get(now_npc_max);

    if (now_npc_max > ANIMAL_NUM_MIN && remove_animal_no[0] == 0xFF) {
        /* First, try to pick an animal which all players have met before */
        int remove_no = mNpc_DecideRemoveAnimalNo_Friend(animal, ignored_idx, TRUE);

        if (remove_no == -1) {
            /* Next, try to pick an animal which at least one player has met before */
            remove_no = mNpc_DecideRemoveAnimalNo_Friend(animal, ignored_idx, FALSE);

            if (remove_no == -1) {
                /* Finally, forcefully find an animal to remove */
                remove_no = mNpc_DecideRemoveAnimalNo(animal, ignored_idx, now_npc_max);
            }
        }

        if (remove_no != -1) {
            remove_animal_no[0] = remove_no;
        }
    }
}

static int mNpc_CheckGoodbyAnimalMemoryNum(Animal_c* a0, Animal_c* a1) {
    Anmmem_c* memories0 = a0->memories;
    Anmmem_c* memories1 = a1->memories;
    int res = 0;
    int res0;
    int res1;

    res0 = mNpc_GetAnimalMemoryNum(memories0, ANIMAL_MEMORY_NUM);
    res1 = mNpc_GetAnimalMemoryNum(memories1, ANIMAL_MEMORY_NUM);

    /* Check the total number of memories first */
    if (res1 > res0) {
        res = 1;
    } else if (res1 == res0) {
        /* Next, check the number of memories which have a letter associated with them */
        res0 = mNpc_GetAnimalMemoryLetterNum(memories0, ANIMAL_MEMORY_NUM);
        res1 = mNpc_GetAnimalMemoryLetterNum(memories1, ANIMAL_MEMORY_NUM);

        if (res1 > res0) {
            res = 1;
        } else if (res1 == res0) {
            /* Next, check the number of unique towns each animal's memories contains */
            res0 = mNpc_GetAnimalMemoryLandKindNum(memories0, ANIMAL_MEMORY_NUM);
            res1 = mNpc_GetAnimalMemoryLandKindNum(memories1, ANIMAL_MEMORY_NUM);

            if (res1 > res0) {
                res = 1;
            } else if (res1 == res0) {
                /* Finally, check the total number of animals in town with the same personality and pick the one with
                 * more */
                res0 = mNpc_GetSameLooksNum(a0->id.looks);
                res1 = mNpc_GetSameLooksNum(a1->id.looks);

                if (res1 < res0) {
                    res = 1;
                } else {
                    res = -1;
                }
            }
        }
    }

    return res;
}

extern int mNpc_GetGoodbyAnimalIdx(int ignored_idx) {
    Animal_c* animal;
    Animal_c* other_animal = NULL;
    int res0;
    int res1;
    int selected;
    u16 remove_bitfield;
    int candidate_num;
    int goodby_animal_idx;
    int i;

    animal = Save_Get(animals);
    remove_bitfield = 0;
    candidate_num = 0;
    goodby_animal_idx = -1;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (i != Save_Get(remove_animal_idx) &&
            ((ignored_idx >= 0 && ignored_idx < ANIMAL_NUM_MAX && i != ignored_idx) || ignored_idx == -1) &&
            mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            if (other_animal != NULL) {
                /* Compare remove experience first (unused feature) */
                if (mNpc_CheckRemoveExp(animal) == 0) {
                    if (mNpc_CheckRemoveExp(other_animal) != 0) {
                        candidate_num = 1;
                        remove_bitfield = (1 << i);
                        other_animal = animal;
                        goodby_animal_idx = i;
                    } else {
                        /* Compare total memories in each animal */
                        res1 = mNpc_CheckGoodbyAnimalMemoryNum(animal, other_animal);
                        switch (res1) {
                            case -1:
                                candidate_num++;
                                remove_bitfield |= (1 << i);
                                break;
                            case 1:
                                candidate_num = 1;
                                remove_bitfield = (1 << i);
                                other_animal = animal;
                                goodby_animal_idx = i;
                                break;
                        }
                    }
                } else if (mNpc_CheckRemoveExp(other_animal) != 0) {
                    /* NOTE: this path can never be taken due to remove experiences never being set */
                    /* Compare times removed (unused feature) */
                    res0 = mNpc_GetRemoveTime(animal);
                    res1 = mNpc_GetRemoveTime(other_animal);
                    if (res1 > res0) {
                        candidate_num = 1;
                        remove_bitfield = (1 << i);
                        other_animal = animal;
                        goodby_animal_idx = i;
                    } else if (res1 == res0) {
                        /* Compare total memories in each animal */
                        res1 = mNpc_CheckGoodbyAnimalMemoryNum(animal, other_animal);
                        switch (res1) {
                            case -1:
                                candidate_num++;
                                remove_bitfield |= (1 << i);
                                break;
                            case 1:
                                candidate_num = 1;
                                remove_bitfield = (1 << i);
                                other_animal = animal;
                                goodby_animal_idx = i;
                                break;
                        }
                    }
                }
            } else {
                candidate_num = 1;
                remove_bitfield = (1 << i);
                other_animal = animal;
                goodby_animal_idx = i;
            }
        }

        animal++;
    }

    animal = Save_Get(animals);
    if (candidate_num > 1) {
        selected = RANDOM(candidate_num);

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (((remove_bitfield >> i) & 1) == 1) {
                if (selected == 0) {
                    goodby_animal_idx = i;
                    break;
                } else {
                    selected--;
                }
            }

            animal++;
        }
    }

    return goodby_animal_idx;
}

typedef struct animal_goodbye_mail_s {
    AnmPersonalID_c id;
    u8 deliver_to_bitfield;
} Anm_GoodbyMail_c;

static Anm_GoodbyMail_c l_mnpc_goodby_mail;

static void mNpc_ClearGoodbyMail(Anm_GoodbyMail_c* goodby_mail) {
    mNpc_ClearAnimalPersonalID(&goodby_mail->id);
    goodby_mail->deliver_to_bitfield = 0;
}

extern void mNpc_FirstClearGoodbyMail() {
    mNpc_ClearGoodbyMail(&l_mnpc_goodby_mail);
}

static void mNpc_SetGoodbyAnimalMail(Anm_GoodbyMail_c* goodby_mail, AnmPersonalID_c* anm_id) {
    Private_c* priv = Save_Get(private_data);
    int i;

    if (anm_id != NULL && mNpc_CheckFreeAnimalPersonalID(anm_id) == FALSE) {
        mNpc_ClearGoodbyMail(goodby_mail);
        mNpc_CopyAnimalPersonalID(&goodby_mail->id, anm_id);

        for (i = 0; i < PLAYER_NUM; i++) {
            if (mPr_NullCheckPersonalID(&priv->player_ID) == FALSE) {
                goodby_mail->deliver_to_bitfield |= (1 << i);
            }

            priv++;
        }
    }
}

static int mNpc_SetGoodbyMailData(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anm_id) {
    static u8 animal_name[ANIMAL_NAME_LEN];

    u8 looks = anm_id->looks;
    int mail_no;
    int res = FALSE;

    if (looks < mNpc_LOOKS_NUM) {
        mail_no = 0x20E + looks * 3;
        mail_no += mQst_GetRandom(3);
        mNpc_GetNpcWorldNameAnm(animal_name, anm_id);
        mHandbill_Set_free_str(mHandbill_FREE_STR0, pid->player_name, PLAYER_NAME_LEN);
        mHandbill_Set_free_str(mHandbill_FREE_STR1, animal_name, ANIMAL_NAME_LEN);
        mHandbill_Set_free_str(mHandbill_FREE_STR3, Save_Get(land_info).name, LAND_NAME_SIZE);
        mNpc_LoadMailDataCommon2(mail, pid, anm_id, EMPTY_NO, mNpc_GetPaperType(), mail_no);
        res = TRUE;
    }

    return res;
}

static int mNpc_SendGoodbyAnimalMailOne(Mail_c* mail, PersonalID_c* pid, int player_no, Anm_GoodbyMail_c* goodby_mail) {
    int free_space;
    mHm_hs_c* home;
    int res = FALSE;

    home = Save_GetPointer(homes[mHS_get_arrange_idx(player_no)]);

    if (mPr_NullCheckPersonalID(pid) == FALSE && mPr_CheckCmpPersonalID(pid, &home->ownerID) == TRUE) {
        free_space = mMl_chk_mail_free_space(home->mailbox, HOME_MAILBOX_SIZE);

        if (free_space != -1) {
            if (mNpc_SetGoodbyMailData(mail, pid, &goodby_mail->id) == TRUE) {
                mMl_copy_mail(home->mailbox + free_space, mail);
                res = TRUE;
            }
        } else if (mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE &&
                   mNpc_SetGoodbyMailData(mail, pid, &goodby_mail->id) == TRUE) {
            res = mPO_receipt_proc(mail, mPO_SENDTYPE_MAIL);
        }
    }

    return res;
}

static void mNpc_SendGoodbyAnimalMail(Anm_GoodbyMail_c* goodby_mail) {
    Private_c* priv = Save_Get(private_data);
    int i;

    if (mNpc_CheckFreeAnimalPersonalID(&goodby_mail->id) == FALSE) {
        for (i = 0; i < PLAYER_NUM; i++) {
            if (((goodby_mail->deliver_to_bitfield >> i) & 1) == 1) {
                mMl_clear_mail(&l_npc_mail);

                if (mNpc_SendGoodbyAnimalMailOne(&l_npc_mail, &priv->player_ID, i, goodby_mail) == TRUE) {
                    goodby_mail->deliver_to_bitfield &= ~(1 << i); // player received goodbye letter
                }
            }

            priv++;
        }

        if (goodby_mail->deliver_to_bitfield == 0) {
            mNpc_ClearGoodbyMail(goodby_mail); // all players received goodbye letter
        }
    }
}

extern void mNpc_SendRegisteredGoodbyMail() {
    mNpc_SendGoodbyAnimalMail(&l_mnpc_goodby_mail);
}

extern void mNpc_GetRemoveAnimal(Animal_c* transferring_animal, int moving_out) {
    Private_c* priv = Common_Get(now_private);
    u8* now_npc_max = Save_GetPointer(now_npc_max);
    int new_animal;
    Animal_c* animal2;
    Animal_c* animal = Save_Get(animals);
    int free_animal_idx;
    u8* remove_animal_idx = Save_GetPointer(remove_animal_idx);
    int bruh;
    int i;

    new_animal = TRUE;

    if (mLd_PlayerManKindCheck() == FALSE) {
        if (moving_out == TRUE) {
            if (*remove_animal_idx != 0xFF) {
                animal2 = Save_GetPointer(animals[*remove_animal_idx]);
                animal2->removing = FALSE;
                mNpc_CopyAnimalInfo(transferring_animal, animal2);
                mNpc_DestroyHouse(&animal2->home_info);
                mNpc_ClearAnimalInfo(animal2);
                now_npc_max[0]--;
                *remove_animal_idx = 0xFF;
            }
        }
    } else {
        if (mNpc_CheckFreeAnimalInfo(transferring_animal) == FALSE && transferring_animal->removing == FALSE) {
            mActor_name_t* summercamper_id;

            /* The incoming animal cannot be present in the town already */
            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (transferring_animal->id.npc_id == animal->id.npc_id) {
                    new_animal = FALSE;
                    break;
                }

                animal++;
            }

            /* The last animal who left the town cannot be the next animal to transfer in */
            if (transferring_animal->id.npc_id == Save_Get(last_removed_animal_id).npc_id) {
                new_animal = FALSE;
            }

            /* Ensure that the animal moving in is not the same one that's currently visiting as a summer camper */
            summercamper_id = (mActor_name_t*)mEv_get_save_area(mEv_EVENT_SUMMER_CAMPER, 0);
            if (summercamper_id != NULL) {
                if (ITEM_NAME_GET_TYPE(summercamper_id[0]) == NAME_TYPE_NPC) {
                    mActor_name_t id = transferring_animal->id.npc_id;

                    if (id == summercamper_id[0]) {
                        new_animal = FALSE;
                    }
                }
            }
        } else {
            /* The new animal was unintialized or was scheduled to move out */
            new_animal = FALSE;
        }

        if (new_animal == TRUE) {
            animal = Save_Get(animals);

            /* Try to find an unused slot in the animal data */
            free_animal_idx = mNpc_GetFreeAnimalInfo(Save_Get(animals), ANIMAL_NUM_MAX);

            if (free_animal_idx == -1) {
                /* No slot, so we're going to replace a villager from in town */
                free_animal_idx = mNpc_GetGoodbyAnimalIdx(-1);

                if (free_animal_idx == -1) {
                    /* Final fallback, delete the first villager */
                    free_animal_idx = 0;
                }

                animal += free_animal_idx;
                mNpc_DestroyHouse(&animal->home_info);
                mNpc_SetGoodbyAnimalMail(&l_mnpc_goodby_mail, &animal->id);
                mNpc_SendRegisteredGoodbyMail();
            } else {
                animal += free_animal_idx;
                mNpc_AddNowNpcMax(now_npc_max);
            }

            mNpc_ClearAnimalInfo(animal);
            mNpc_CopyAnimalInfo(animal, transferring_animal);
            animal->home_info.block_x = 0xFF;
            animal->home_info.block_z = 0xFF;
            animal->home_info.ut_x = 0xFF;
            animal->home_info.ut_z = 0xFF;
            mLd_CopyLandName(animal->anmuni.previous_land_name, Common_Get(now_private)->player_ID.land_name);
            animal->previous_land_id = Common_Get(now_private)->player_ID.land_id;
            mQst_ClearContest(&animal->contest_quest);
            mNpc_ClearHPMail(animal->hp_mail, ANIMAL_HP_MAIL_NUM);
            transferring_animal->removing = TRUE;
            priv->animal_memory.npc_id = animal->id.npc_id;
            mLd_CopyLandName(priv->animal_memory.land_name, mLd_GetLandName());
            mNpc_SetHaveAppeared(animal->id.npc_id);
            mNpc_ResetAnimalRelation(free_animal_idx);
            mNpc_RenewRemoveHistory();
        }
    }
}

#ifdef TARGET_PC
extern void mNpc_CopyRemoveAnimal(Animal_c* transferring_animal) {
    u8 remove_idx = Save_Get(remove_animal_idx);

    if (mLd_PlayerManKindCheck() == FALSE && remove_idx < ANIMAL_NUM_MAX &&
        mNpc_CheckFreeAnimalInfo(Save_GetPointer(animals[remove_idx])) == FALSE) {
        mNpc_CopyAnimalInfo(transferring_animal, Save_GetPointer(animals[remove_idx]));
        transferring_animal->removing = FALSE;
    }
}

extern void mNpc_FinishRemoveAnimal(Animal_c* transferring_animal) {
    Animal_c* animal;
    int idx;

    if (mLd_PlayerManKindCheck() == FALSE && mNpc_CheckFreeAnimalInfo(transferring_animal) == FALSE) {
        idx = mNpc_SearchAnimalinfo(Save_Get(animals), transferring_animal->id.npc_id, ANIMAL_NUM_MAX);

        if (idx != -1) {
            if (transferring_animal->removing == TRUE) {
                animal = Save_GetPointer(animals[idx]);
                mNpc_DestroyHouse(&animal->home_info);
                mNpc_ClearAnimalInfo(animal);
                mNpc_SubNowNpcMax(Save_GetPointer(now_npc_max));

                if (Save_Get(remove_animal_idx) == idx) {
                    Save_Set(remove_animal_idx, 0xFF);
                }
            } else {
                mNpc_ClearAnimalInfo(transferring_animal);
            }
        }
    }
}
#endif

static int mNpc_CheckBuildHouse(int bx, int bz, u8 ut_x, u8 ut_z) {
    int res = FALSE;

    if (bx >= 0 && bx < FG_BLOCK_X_NUM && bz >= 0 && bz < FG_BLOCK_Z_NUM && ut_x < UT_X_NUM && ut_z < UT_Z_NUM) {
        mActor_name_t item = Save_Get(fg[bz][bx]).items[ut_z][ut_x];

        if (mNT_IS_RESERVE(item)) {
            res = TRUE;
        }
    }

    return res;
}

extern void mNpc_SetReturnAnimal(Animal_c* return_animal) {
    Anmhome_c* home_info;
    Animal_c* animals = Save_Get(animals);
    Animal_c* found_animal = NULL;
    u8* now_npc_max = Save_GetPointer(now_npc_max);
    Anmret_c* return_animal_p = Save_GetPointer(return_animal);
    int found_animal_idx;
    int ignored_idx = -1;

    if (mLd_PlayerManKindCheck() == FALSE && mNpc_CheckFreeAnimalInfo(return_animal) == FALSE) {
        if (return_animal->removing == FALSE) {
            found_animal_idx = mNpc_SearchAnimalinfo(animals, return_animal->id.npc_id, ANIMAL_NUM_MAX);

            if (found_animal_idx != -1) {
                found_animal = &animals[found_animal_idx];
                mNpc_DestroyHouse(&found_animal->home_info);
                (*now_npc_max)--;

                if (Save_Get(remove_animal_idx) == found_animal_idx) {
                    Save_Set(remove_animal_idx, 0xFF);
                }
            } else if ((*now_npc_max) >= ANIMAL_NUM_MAX) {
                if (Save_Get(scene_no) == SCENE_PLAYERSELECT_2) {
                    /* Don't remove the animal we just saw on the player select screen */
                    ignored_idx = Common_Get(player_select_animal_no);
                }

                found_animal_idx = mNpc_GetGoodbyAnimalIdx(ignored_idx);

                if (found_animal_idx == -1) {
                    found_animal_idx = 0; // fallback
                }

                found_animal = &animals[found_animal_idx];
                mNpc_SetGoodbyAnimalMail(&l_mnpc_goodby_mail, &found_animal->id);
                mNpc_DestroyHouse(&found_animal->home_info);
                (*now_npc_max)--;

                if (Save_Get(remove_animal_idx) == found_animal_idx) {
                    Save_Set(remove_animal_idx, 0xFF);
                }
            } else {
                found_animal_idx = mNpc_GetFreeAnimalInfo(animals, ANIMAL_NUM_MAX);

                if (found_animal_idx != -1) {
                    found_animal = &animals[found_animal_idx];
                }
            }

            if (found_animal != NULL) {
                mNpc_ClearAnimalInfo(found_animal);
                mNpc_CopyAnimalInfo(found_animal, return_animal);
                mNpc_ResetAnimalRelation(found_animal_idx);
                home_info = &found_animal->home_info;

                if (mNpc_CheckBuildHouse(home_info->block_x - 1, home_info->block_z - 1, home_info->ut_x,
                                         home_info->ut_z - 1) == TRUE) {
                    mNpc_BuildHouseBeforeFieldct(found_animal->id.npc_id, home_info->block_x - 1,
                                                 home_info->block_z - 1, home_info->ut_x, home_info->ut_z - 1);
                } else {
                    home_info->block_x = 0xFF;
                    home_info->block_z = 0xFF;
                    home_info->ut_x = 0xFF;
                    home_info->ut_z = 0xFF;
                }

                (*now_npc_max)++;

                if ((*now_npc_max) > ANIMAL_NUM_MAX) {
                    (*now_npc_max) = ANIMAL_NUM_MAX;
                }
            }
        } else {
            return_animal_p->npc_id = return_animal->id.npc_id;
            return_animal_p->talk_bit = 0b000;
            return_animal_p->exist = FALSE;
            lbRTC_TimeCopy(&return_animal_p->renew_time, Common_GetPointer(time.rtc_time));
            mNpc_CopyAnimalPersonalID(Save_GetPointer(last_removed_animal_id), &return_animal->id);
        }

        mNpc_ClearAnimalInfo(return_animal);
    }
}

extern void mNpc_AddActor_inBlock(mFM_move_actor_c* move_actor_list, u8 bx, u8 bz) {
    mNpc_AddNpc_inBlock(move_actor_list, bx, bz);
}

static void mNpc_SetNpcNameID(Animal_c* animal, int num) {
    int i;

    for (i = 0; i < num; i++) {
        if (animal != NULL && ITEM_NAME_GET_TYPE(animal->id.npc_id) == NAME_TYPE_NPC) {
            animal->id.name_id = (u8)animal->id.npc_id;
        }

        animal++;
    }
}

extern void mNpc_LoadNpcNameString(u8* dst, u8 name_id) {
    ATTRIBUTE_ALIGN(32) static u8 dma_area[64];
    u32 addr;
    u32 ofs;
    u32 base_addr;

    mem_clear(dma_area, sizeof(dma_area), CHAR_SPACE);
    addr = JW_GetAramAddress(RESOURCE_NPC_NAME_STR_TABLE);

    if (name_id < 0xFF && dst != NULL && addr != 0) {
        ofs = (name_id)*ANIMAL_NAME_LEN; /* offset into dma table */
        base_addr = ALIGN_PREV(ofs, 32); /* align it to the nearest 32 bytes for DMA */

        _JW_GetResourceAram(base_addr + addr, dma_area, sizeof(dma_area)); // DMA transfer from ARAM
        bcopy(dma_area + (ofs - base_addr), dst, ANIMAL_NAME_LEN);         // perform final copy
    }
}

static u8* mNpc_GetNpcWorldNamePTableNo(mActor_name_t npc_id) {
    static u8 npc_name[ANIMAL_NAME_LEN];

    u8* world_name_p = NULL;

    if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC && (u8)(npc_id & 0xFF) < 0xFF) {
        mNpc_LoadNpcNameString(npc_name, npc_id & 0xFF);
        world_name_p = npc_name;
    }

    return world_name_p;
}

extern void mNpc_GetNpcWorldNameTableNo(u8* dst, mActor_name_t npc_id) {
    u8* world_name_p = mNpc_GetNpcWorldNamePTableNo(npc_id);

    if (world_name_p == NULL) {
        world_name_p = l_no_name_npc_name;
    }

    mPr_CopyPlayerName(dst, world_name_p);
}

typedef struct npc_name_cache_s {
    mActor_name_t npc_id;
    u8 name[ANIMAL_NAME_LEN];
    u8 npc_type; // 0? = Special NPC, 1 = Regular NPC
} mNpc_NameCache_c;

static mNpc_NameCache_c l_npc_name_cache;

extern void mNpc_ClearCacheName() {
    mPr_ClearPlayerName(l_npc_name_cache.name);
    l_npc_name_cache.npc_id = RSV_NO;
    l_npc_name_cache.npc_type = 0;
}

static int mNpc_GetCacheName(u8* dst, mActor_name_t npc_id, u8 npc_type) {
    int res = FALSE;

    if (npc_id == l_npc_name_cache.npc_id && dst != NULL && npc_type == l_npc_name_cache.npc_type) {
        mPr_CopyPlayerName(dst, l_npc_name_cache.name);
        res = TRUE;
    }

    return res;
}

static void mNpc_SetCacheName(u8* name, mActor_name_t npc_id, u8 npc_type) {
    mNpc_NameCache_c* name_cache = &l_npc_name_cache;

    if (name != NULL) {
        mPr_CopyPlayerName(name_cache->name, name);
        name_cache->npc_id = npc_id;
        name_cache->npc_type = npc_type;
    }
}

extern void mNpc_GetNpcWorldNameAnm(u8* dst, AnmPersonalID_c* anm_id) {
    u8 animal_name[ANIMAL_NAME_LEN];
    u8* name = l_no_name_npc_name;

    if (anm_id != NULL) {
        if (anm_id->npc_id != RSV_NO && mNpc_GetCacheName(animal_name, anm_id->npc_id, mNpc_NAME_TYPE_NPC) != FALSE) {
            name = animal_name;
        } else if (ITEM_NAME_GET_TYPE(anm_id->npc_id) == NAME_TYPE_NPC) {
            mNpc_GetNpcWorldNameTableNo(animal_name, anm_id->npc_id);
            name = animal_name;
            mNpc_SetCacheName(name, anm_id->npc_id, mNpc_NAME_TYPE_NPC);
        }
    }

    mPr_CopyPlayerName(dst, name);
}

static u8* mNpc_GetActorWorldNameP(mActor_name_t npc_id) {
    static u8 load_name[ANIMAL_NAME_LEN];

    mNpc_Sp_Npc_Name_c* sp_npc_name = l_sp_actor_name;
    u8* name_p = NULL;
    int i;

    if (npc_id != RSV_NO && mNpc_GetCacheName(load_name, npc_id, mNpc_NAME_TYPE_NPC) != FALSE) {
        name_p = load_name;
    } else if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
        mNpc_GetNpcWorldNameTableNo(load_name, npc_id);
        name_p = load_name;
        mNpc_SetCacheName(load_name, npc_id, mNpc_NAME_TYPE_NPC);
    } else {
        for (i = 0; i < ARRAY_COUNT(l_sp_actor_name); i++) {
            if (npc_id == sp_npc_name->sp_npc_id) {
                mString_Load_StringFromRom(load_name, ANIMAL_NAME_LEN, sp_npc_name->name_str_no);
                name_p = load_name;
                mNpc_SetCacheName(load_name, npc_id, mNpc_NAME_TYPE_NPC);

                break;
            }

            sp_npc_name++;
        }
    }

    return name_p;
}

extern void mNpc_GetActorWorldName(u8* dst, mActor_name_t npc_id) {
    u8* name_p = mNpc_GetActorWorldNameP(npc_id);

    if (name_p == NULL) {
        name_p = l_no_name_npc_name;
    }

    mPr_CopyPlayerName(dst, name_p);
}

extern u8* mNpc_GetNpcWorldNameP(mActor_name_t npc_id) {
    u8* name_p = mNpc_GetNpcWorldNamePTableNo(npc_id);

    if (name_p == NULL) {
        name_p = mNpc_GetActorWorldNameP(npc_id);

        if (name_p == NULL) {
            name_p = l_no_name_npc_name;
        }
    }

    return name_p;
}

extern void mNpc_GetNpcWorldName(u8* dst, ACTOR* actor) {
    u8 npc_name[ANIMAL_NAME_LEN];
    u8* name_p = l_no_name_npc_name;

    if (dst != NULL && actor != NULL) {
        if (actor->part == ACTOR_PART_NPC) {
            NPC_ACTOR* npc = (NPC_ACTOR*)actor;
            Animal_c* animal = npc->npc_info.animal;

            if (animal != NULL) {
                mNpc_GetNpcWorldNameAnm(npc_name, &animal->id);
            } else {
                mActor_name_t npc_id;
                mNpc_EventNpc_c* event_npc;
                mNpc_MaskNpc_c* mask_npc;

                event_npc = mNpc_GetSameEventNpc(actor->npc_id);

                if (event_npc != NULL) {
                    npc_id = event_npc->npc_id;
                } else {
                    mask_npc = mNpc_GetSameMaskNpc(actor->npc_id);

                    if (mask_npc != NULL) {
                        npc_id = mask_npc->npc_id;
                    } else {
                        npc_id = actor->npc_id;
                    }
                }

                if (npc_id == SP_NPC_EV_GHOST) {
                    u8 arg = actor->actor_specific;

                    if (mNpc_GetCacheName(npc_name, npc_id, arg) == FALSE) {
                        if (arg != 1) {
                            /* Load the ?????? name */
                            mString_Load_StringFromRom(npc_name, ANIMAL_NAME_LEN, 0x6D7);
                            mNpc_SetCacheName(npc_name, npc_id, arg);
                        } else {
                            mNpc_GetActorWorldName(npc_name, npc_id);
                        }
                    }
                } else {
                    mNpc_GetActorWorldName(npc_name, npc_id);
                }
            }
        } else {
            mNpc_GetActorWorldName(npc_name, actor->npc_id);
        }

        name_p = npc_name;
    }

    mPr_CopyPlayerName(dst, name_p);
}

extern void mNpc_GetRandomAnimalName(u8* dst) {
    Animal_c* animal = Save_Get(animals);
    Animal_c* animal_p = animal;
    u16 candidate_bitfield = 0;
    int candidate_num = 0;
    int i;

    if (dst != NULL) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalInfo(animal_p) == FALSE) {
                candidate_bitfield |= (1 << i);
                candidate_num++;
            }

            animal_p++;
        }

        if (candidate_num > 0) {
            int selected = RANDOM(candidate_num);

            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (((candidate_bitfield >> i) & 1) == 1) {
                    if (selected == 0) {
                        mNpc_GetNpcWorldNameAnm(dst, &animal->id);
                        break;
                    } else {
                        selected--;
                    }
                }

                animal++;
            }
        }
    }
}

extern void mNpc_GetAnimalPlateName(u8* dst, xyz_t wpos) {
    Animal_c* animal = Save_Get(animals);
    int bx;
    int bz;
    int ut_x;
    int ut_z;

    if (mFI_Wpos2BkandUtNuminBlock(&bx, &bz, &ut_x, &ut_z, wpos) == TRUE) {
        if (mFI_CheckBlockKind_OR(bx, bz, mRF_BLOCKKIND_OCEAN) == TRUE) {
            mNpc_GetNpcWorldNameAnm(dst, &Save_Get(island).animal.id);
        } else {
            int i;

            ut_x++;

            for (i = 0; i < ANIMAL_NUM_MAX; i++) {

                if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
                    Anmhome_c* home = &animal->home_info;

                    if (home->block_x == bx && home->block_z == bz && home->ut_x == ut_x && home->ut_z == ut_z) {
                        mNpc_GetNpcWorldNameAnm(dst, &animal->id);
                        break;
                    }
                }

                animal++;
            }
        }
    }
}

extern int mNpc_GetNpcLooks(ACTOR* actor) {
    int looks = mNpc_LOOKS_BOY;

    if (actor != NULL && actor->part == ACTOR_PART_NPC) {
        NPC_ACTOR* npc = (NPC_ACTOR*)actor;

        if (npc->npc_info.animal != NULL) {
            looks = npc->npc_info.animal->id.looks;
        }
    }

    return looks;
}

static int mNpc_GetActorSex(mActor_name_t npc_id) {
    mNpc_Sp_Npc_Name_c* sp_name_info = l_sp_actor_name;
    int sex = mPr_SEX_MALE;
    int i;

    for (i = 0; i < ARRAY_COUNT(l_sp_actor_name); i++) {
        if (npc_id == sp_name_info->sp_npc_id) {
            sex = sp_name_info->sex;
            break;
        }

        sp_name_info++;
    }

    return sex;
}

extern int mNpc_GetLooks2Sex(int looks) {
    int sex = mPr_SEX_OTHER;

    if (looks == mNpc_LOOKS_GIRL || looks == mNpc_LOOKS_KO_GIRL || looks == mNpc_LOOKS_NANIWA_LADY) {
        sex = mPr_SEX_FEMALE;
    } else if (looks == mNpc_LOOKS_BOY || looks == mNpc_LOOKS_SPORT_MAN || looks == mNpc_LOOKS_GRIM_MAN) {
        sex = mPr_SEX_MALE;
    }

    return sex;
}

extern int mNpc_GetAnimalSex(Animal_c* animal) {
    int sex = mPr_SEX_OTHER;

    if (animal != NULL) {
        sex = mNpc_GetLooks2Sex(animal->id.looks);
    }

    return sex;
}

extern int mNpc_GetNpcSex(ACTOR* actor) {
    if (actor != NULL && actor->part == ACTOR_PART_NPC) {
        NPC_ACTOR* npc = (NPC_ACTOR*)actor;

        return mNpc_GetAnimalSex(npc->npc_info.animal);
    }

    return mNpc_GetActorSex(actor->npc_id);
}

static int mNpc_GetNpcSoundSpecNotAnimal(mActor_name_t npc_id) {
    mNpc_Sp_Npc_Name_c* sp_name_info = l_sp_actor_name;
    int sound_spec = 2;
    int i;

    for (i = 0; i < ARRAY_COUNT(l_sp_actor_name); i++) {
        if (npc_id == sp_name_info->sp_npc_id) {
            sound_spec = sp_name_info->sound_id;
            break;
        }

        sp_name_info++;
    }

    return sound_spec;
}

extern int mNpc_GetNpcSoundSpec(ACTOR* actor) {
    static int spec_table[mNpc_LOOKS_NUM] = { 4, 4, 2, 2, 3, 4 };

    int sound_spec = 2;

    if (actor != NULL) {
        if (actor->part == ACTOR_PART_NPC) {
            NPC_ACTOR* npc = (NPC_ACTOR*)actor;

            if (npc->npc_info.animal != NULL) {
                int looks = npc->npc_info.animal->id.looks;

                if (looks >= mNpc_LOOKS_NUM) {
                    looks = mNpc_LOOKS_BOY;
                }

                sound_spec = spec_table[looks];
            } else {
                sound_spec = mNpc_GetNpcSoundSpecNotAnimal(actor->npc_id);
            }
        } else {
            sound_spec = mNpc_GetNpcSoundSpecNotAnimal(actor->npc_id);
        }
    }

    return sound_spec;
}

static void mNpc_InitRemoveHistory() {
    lbRTC_ymd_c* ymd = Save_GetPointer(force_remove_date);

    ymd->year = 0xFFFF;
    ymd->month = 0xFF;
    ymd->day = 0xFF;
}

extern void mNpc_InitNpcAllInfo(int malloc_flag) {
    Animal_c* animals = Save_Get(animals);

    Save_Set(now_npc_max, mNpc_LOOKS_NUM);
    Save_Set(remove_animal_idx, 0xFF);
    mNpc_InitRemoveHistory();
    mNpc_ClearAnimalPersonalID(Save_GetPointer(last_removed_animal_id));
    mNpc_ClearAnyAnimalInfo(animals, ANIMAL_NUM_MAX);
    mNpc_DecideLivingNpcMax(animals, mNpc_LOOKS_NUM, malloc_flag);
    mNpc_SetNpcNameID(animals, ANIMAL_NUM_MAX);
}

static int mNpc_CheckGrowFieldRank() {
    static int npc_grow_prob[mFAs_FIELDRANK_NUM] = { 40, 50, 60, 70, 80, 90, 100 };

    int rank = mFAs_GetFieldRank();
    int res = FALSE;

    if (rank >= 0 && rank < mFAs_FIELDRANK_NUM) {
        if (RANDOM(100) < npc_grow_prob[rank]) {
            res = TRUE;
        }
    }

    return res;
}

static int mNpc_CheckGrow() {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    lbRTC_time_c* last_grow_time = Save_GetPointer(last_grow_time);
    int res = FALSE;

    if (Save_Get(now_npc_max) < ANIMAL_NUM_MAX) {
        if (lbRTC_IsEqualTime(&mTM_rtcTime_clear_code, last_grow_time, lbRTC_CHECK_ALL) == TRUE) {
            lbRTC_TimeCopy(last_grow_time, rtc_time); // first initialization
        } else if (mNpc_CheckGrowFieldRank() == TRUE) {
            u32 interval;

            if (lbRTC_IsOverTime(last_grow_time, rtc_time) == lbRTC_OVER) {
                interval = lbRTC_IntervalTime(rtc_time, last_grow_time);
            } else {
                interval = lbRTC_IntervalTime(last_grow_time, rtc_time);
            }

            if (interval >= (lbRTC_HOURS_PER_DAY * lbRTC_MINUTES_PER_HOUR) && /* Only one new villager per day */
                mLd_PlayerManKindCheck() == FALSE && /* Player must be from the town being loaded */
                mNpc_CheckFriendAllAnimal(&Common_Get(now_private)->player_ID) ==
                    TRUE /* The player loading must have talked to all current villagers */
            ) {
                res = TRUE;
            }
        }
    }

    return res;
}

static u8 mNpc_GetMinLooks(u8* min_looks_bitfield, int* min_looks_num) {
    int min_looks_animals;
    u8 min_looks;
    u8 i;

    min_looks_bitfield[0] = 0;
    min_looks_num[0] = 0;
    min_looks_animals = ANIMAL_NUM_MAX;
    min_looks = mNpc_LOOKS_UNSET;

    for (i = 0; i < mNpc_LOOKS_NUM; i++) {
        int not_appear_num = mNpc_GetLooks2NotHaveAppearedNum(i);

        if (not_appear_num > 0) {
            int same_looks_num = mNpc_GetSameLooksNum(i);

            if (min_looks_animals > same_looks_num) {
                min_looks_animals = same_looks_num;
                min_looks = i;
                min_looks_bitfield[0] = 0;
                min_looks_bitfield[0] |= (1 << i);
                min_looks_num[0] = 1;
            } else if (min_looks_animals == same_looks_num) {
                min_looks_bitfield[0] |= (1 << i);
                min_looks_num[0]++;
            }
        }
    }

    if (min_looks_bitfield[0] == 0 && min_looks_num[0] == 0) {
        /* All animals have appeared before, so reset the list */
        mNpc_ResetHaveAppeared_common(Save_Get(npc_used_tbl), Save_Get(animals));

        for (i = 0; i < mNpc_LOOKS_NUM; i++) {
            min_looks_bitfield[0] |= (1 << i);
            min_looks_num[0]++;
        }
    }

    if (min_looks_num[0] > 1) {
        min_looks = mNpc_LOOKS_UNSET;
    }

    return min_looks;
}

static int mNpc_GetMinSex() {
    Animal_c* animal = Save_Get(animals);
    int males = 0;
    int females = 0;
    int res;
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            switch (mNpc_GetAnimalSex(animal)) {
                case mPr_SEX_MALE:
                    males++;
                    break;
                case mPr_SEX_FEMALE:
                    females++;
                    break;
            }
        }

        animal++;
    }

    /* TODO: is this bugged? Shouldn't this check be inverted? */
    if (females < males) {
        res = mPr_SEX_MALE;
    } else {
        res = mPr_SEX_FEMALE;
    }

    return res;
}

static int mNpc_GrowLooksNpcIdx(u8 looks) {
    static u8 candidate_table[ALIGN_NEXT(NPC_NUM, 8) / 8];

    u8* looks_table = npc_looks_table;
    s8* grow_list = npc_grow_list;
    int npc_idx;
    int candidates;
    int res;
    int i;
    int j;
    int selected;

    npc_idx = 0;
    candidates = 0;
    res = -1;

    if (looks < mNpc_LOOKS_UNSET) {
        bzero(candidate_table, sizeof(candidate_table));

        for (i = 0; i < ARRAY_COUNT(candidate_table); i++) {
            for (j = 0; j < 8; j++) {
                if (looks == *looks_table) {
                    int grow_perm = mNpc_GetDefGrowPermission(npc_idx, grow_list, NPC_NUM);

                    if ((mNpc_SearchAnimalinfo(Save_Get(animals), npc_idx | NPC_START, ANIMAL_NUM_MAX) == -1) &&
                        (mNpc_GetHaveAppeared_idx(npc_idx) == FALSE) &&
                        (grow_perm == mNpc_GROW_STARTER || grow_perm == mNpc_GROW_MOVE_IN)) {
                        candidates++;
                        candidate_table[i] |= 1 << j;
                    }
                }

                npc_idx++;
                looks_table++;

                if (npc_idx >= NPC_NUM) {
                    break;
                }
            }

            if (npc_idx >= NPC_NUM) {
                break;
            }
        }
    }

    if (candidates > 0) {
        looks_table = npc_looks_table;
        selected = RANDOM(candidates);
        npc_idx = 0;

        for (i = 0; i < ARRAY_COUNT(candidate_table); i++) {
            if (npc_idx >= NPC_NUM) {
                break;
            }

            for (j = 0; j < 8; looks_table++, npc_idx++, j++) {
                if (npc_idx >= NPC_NUM) {
                    break;
                }

                if (((candidate_table[i] >> j) & 1) == 1) {
                    if (selected <= 0) {
                        res = npc_idx;
                        break;
                    } else {
                        selected--;
                    }
                }
            }

            if (res != -1) {
                break;
            }
        }
    }

    return res;
}

static void mNpc_SetAnimalInfoNpcIdx(Animal_c* animal, int idx) {
    if (idx >= 0 && idx < NPC_NUM) {
        mNpc_SetDefAnimalInfo(animal, NPC_START | idx, npc_looks_table[idx], &npc_def_list[idx]);
    }
}

static int mNpc_SetGrowNpc(u8 looks) {
    Animal_c* animal = Save_Get(animals);
    int idx = mNpc_UseFreeAnimalInfo(animal, ANIMAL_NUM_MAX);
    int npc_idx;

    if (idx != -1) {
        animal += idx;
        npc_idx = mNpc_GrowLooksNpcIdx(looks);

        if (npc_idx != -1) {
            mNpc_SetAnimalInfoNpcIdx(animal, npc_idx);
            mNpc_SetHaveAppeared(animal->id.npc_id);
            animal->moved_in = TRUE;
        } else {
            idx = -1;
        }
    }

    return idx;
}

extern void mNpc_Grow() {
    int selected;
    int grow_idx;

    if (mNpc_CheckGrow() == TRUE) {
        lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
        lbRTC_time_c* last_grow_time = Save_GetPointer(last_grow_time);
        u8 min_looks_bitfield;
        int min_looks_num;
        u8 min_looks;
        u8 selected_looks;

        mNpc_ResetHaveAppeared();
        lbRTC_TimeCopy(last_grow_time, rtc_time);

        min_looks = mNpc_GetMinLooks(&min_looks_bitfield, &min_looks_num);
        selected_looks = min_looks;

        /* Multiple personalities are tied for minimum */
        if (min_looks == mNpc_LOOKS_UNSET) {
            int min_sex = mNpc_GetMinSex();
            u8 min_looks_bitfield_save;
            int min_looks_num_save;
            u8 looks;

            if (min_sex != mPr_SEX_OTHER) {
                min_looks_bitfield_save = min_looks_bitfield;
                min_looks_num_save = min_looks_num;

                /* Clear any tied minimum personalities which are of the greater sex */
                for (looks = 0; looks < mNpc_LOOKS_NUM; looks++) {
                    if (((min_looks_bitfield >> looks) & 1) == 1 && mNpc_GetLooks2Sex(looks) != min_sex) {
                        min_looks_bitfield &= ~(1 << looks);
                        min_looks_num--;
                    }
                }

                if (min_looks_num == 0 || min_looks_num == min_looks_num_save) {
                    /* Either all personalities were cleared or none were, so restore the prior state */
                    min_looks_bitfield = min_looks_bitfield_save;
                    min_looks_num = min_looks_num_save;
                }
            }

            selected = RANDOM(min_looks_num);

            for (looks = 0; looks < mNpc_LOOKS_NUM; looks++) {
                if (((min_looks_bitfield >> looks) & 1) == 1) {
                    if (selected <= 0) {
                        selected_looks = looks;
                        break;
                    } else {
                        selected--;
                    }
                }
            }
        }

        grow_idx = mNpc_SetGrowNpc(selected_looks);

        if (grow_idx >= 0 && grow_idx < ANIMAL_NUM_MAX) {
            mNpc_SetNpcNameID(Save_GetPointer(animals[grow_idx]), 1);
            mNpc_AddNowNpcMax(Save_GetPointer(now_npc_max));
            mNpc_RenewRemoveHistory();
        }
    }
}

extern void mNpc_ForceRemove() {
    lbRTC_time_c force_remove_time;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    lbRTC_ymd_c* force_remove_date = Save_GetPointer(force_remove_date);
    Animal_c* animal = Save_Get(animals);
    int interval;
    int animal_num = mNpc_GetAnimalNum();
    int ignored_idx = -1;
    int idx;

    if (animal_num == ANIMAL_NUM_MAX && force_remove_date->year != 0xFFFF && force_remove_date->month != 0xFF &&
        force_remove_date->day != 0xFF) {
        mTM_ymd_2_time(&force_remove_time, force_remove_date);

        if (lbRTC_IsOverTime(&force_remove_time, rtc_time) == lbRTC_OVER) {
            interval = lbRTC_GetIntervalDays(&force_remove_time, rtc_time);
        } else {
            interval = lbRTC_GetIntervalDays(rtc_time, &force_remove_time);
        }

        if (interval >= mNpc_MINIMUM_DAYS_BEFORE_FORCE_REMOVAL) {
            if (Save_Get(scene_no) == SCENE_PLAYERSELECT_2) {
                ignored_idx = Common_Get(player_select_animal_no);
            }

            idx = mNpc_GetGoodbyAnimalIdx(ignored_idx);

            if (idx != -1) {
                animal += idx;

                if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
                    mNpc_DestroyHouse(&animal->home_info);
                    mNpc_SetGoodbyAnimalMail(&l_mnpc_goodby_mail, &animal->id);
                    mNpc_SendRegisteredGoodbyMail();
                    mNpc_ClearAnimalInfo(animal);
                    mNpc_SubNowNpcMax(Save_GetPointer(now_npc_max));
                    mNpc_RenewRemoveHistory();
                }
            }
        }
    }
}

extern int mNpc_DecideMaskNpc_summercamp(mActor_name_t* npc_id) {
    static int looks_table[mNpc_LOOKS_NUM];

    u8 looks;
    int i;
    int res = FALSE;

    if (npc_id != NULL) {
        npc_id[0] = EMPTY_NO;
        mNpc_ResetHaveAppeared();
        mNpc_MakeRandTable(looks_table, mNpc_LOOKS_NUM, NPC_NUM); // why are we swapping this 'NPC_NUM' times???

        for (i = 0; i < mNpc_LOOKS_NUM; i++) {
            looks = looks_table[i];

            if (mNpc_GetLooks2NotHaveAppearedNum(looks) > 0) {
                int idx = mNpc_GrowLooksNpcIdx(looks);

                if (idx != -1) {
                    npc_id[0] = NPC_START | idx;
                    /* This makes summer campers impossible to appear by 'natural growth' in your town
                       unless you've seen every non-islander in your town as a villager or summer camper... */
                    mNpc_SetHaveAppeared(npc_id[0]);
                    res = TRUE;

                    break;
                }
            }
        }
    }

    return res;
}

extern int mNpc_RegistMaskNpc_summercamp(mActor_name_t mask_id, mActor_name_t npc_id, mActor_name_t cloth_id) {
    int free_mask_idx = mNpc_GetFreeMaskNpcIdx();
    int res = FALSE;

    if (free_mask_idx != -1) {
        mNpc_MaskNpc_c* mask_npc = Common_GetPointer(mask_npc[free_mask_idx]);

        if (cloth_id != EMPTY_NO) {
            int valid_cloth = (cloth_id == RSV_CLOTH) || (cloth_id >= ITM_CLOTH_START && cloth_id < ITM_CLOTH_END);

            if (valid_cloth == FALSE) {
                cloth_id = ITM_CLOTH_START;
            }
        }

        if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
            mask_npc->mask_id = mask_id;
            mask_npc->npc_id = npc_id;
            mask_npc->exists = FALSE;
            mask_npc->in_use = TRUE;
            mNpc_ClearAnimalInfo(&mask_npc->animal_data);
            mNpc_SetDefAnimal(&mask_npc->animal_data, npc_id, npc_def_list);

            if (cloth_id == EMPTY_NO) {
                mask_npc->cloth_id = mask_npc->animal_data.cloth;
            } else {
                mask_npc->cloth_id = cloth_id;
            }

            if (Common_Get(npc_is_summercamper) == TRUE) {
                mNpc_ClearAnimalMemory(mask_npc->animal_data.memories, 1);
                mNpc_SetAnimalMemory(&Common_Get(now_private)->player_ID, &mask_npc->animal_data.id,
                                     &mask_npc->animal_data.memories[0]);
            }

            res = TRUE;
        }
    }

    return res;
}

extern int mNpc_CheckNpcSet_fgcol(mActor_name_t fg_item, u32 attribute) {
    int res = FALSE;

    if (mFI_CheckFGNpcOn(fg_item)) {
        res = mCoBG_Attr2CheckPlaceNpc(attribute);
    }

    return res;
}

static int mNpc_CheckNpcSet_fgcol_hard(mActor_name_t fg_item, u32 attribute) {
    int res = FALSE;

    if (mFI_CheckFGNpcOn(fg_item) && (attribute <= mCoBG_ATTRIBUTE_GRASS2 ||
                                      (attribute >= mCoBG_ATTRIBUTE_SOIL0 && attribute <= mCoBG_ATTRIBUTE_SOIL2) ||
                                      attribute == mCoBG_ATTRIBUTE_STONE)) {
        res = TRUE;
    }

    return res;
}

extern int mNpc_CheckNpcSet(int bx, int bz, int ut_x, int ut_z) {
    mCoBG_Collision_u* collision = mFI_GetBkNum2ColTop(bx, bz);
    mActor_name_t* items = mFI_BkNumtoUtFGTop(bx, bz);
    int res = FALSE;

    if (collision != NULL && items != NULL) {
        res = mNpc_CheckNpcSet_fgcol(items[ut_z * UT_X_NUM + ut_x],
                                     collision[ut_z * UT_X_NUM + ut_x].data.unit_attribute);
    }

    return res;
}

extern int mNpc_GetMakeUtNuminBlock_hard_area(int* ut_x, int* ut_z, int bx, int bz, int restrict_area) {
    int now_ut_x;
    int now_ut_z;
    mCoBG_Collision_u* col;
    mActor_name_t* items;
    int min_ut_x;
    int min_ut_z;
    int res;
    u32 center;
    int i;
    int j;

    col = mFI_GetBkNum2ColTop(bx, bz);
    items = mFI_BkNumtoUtFGTop(bx, bz);
    min_ut_x = UT_X_NUM;
    min_ut_z = UT_Z_NUM;
    res = FALSE;

    if (restrict_area < 0 || restrict_area > 9) {
        return FALSE;
    }

    if (items != NULL && col != NULL) {
        for (i = restrict_area; i < UT_Z_NUM - restrict_area; i++) {
            for (j = restrict_area; j < UT_X_NUM - restrict_area; j++) {
                if (mNpc_CheckNpcSet_fgcol_hard(items[i * UT_X_NUM + j], col[i * UT_X_NUM + j].data.unit_attribute) == TRUE) {
                    /* Check that the height of each point on the unit is equal*/
                    if (col[i * UT_X_NUM + j].data.center == col[i * UT_X_NUM + j].data.top_left && col[i * UT_X_NUM + j].data.center == col[i * UT_X_NUM + j].data.bot_left &&
                        col[i * UT_X_NUM + j].data.center == col[i * UT_X_NUM + j].data.bot_right && col[i * UT_X_NUM + j].data.center == col[i * UT_X_NUM + j].data.top_right) {

                        now_ut_x = 8 - j;
                        now_ut_z = 8 - i;

                        now_ut_x = ABS(now_ut_x);
                        now_ut_z = ABS(now_ut_z);

                        if (min_ut_x > now_ut_x && min_ut_z > now_ut_z) {
                            *ut_x = j;
                            *ut_z = i;
                            min_ut_x = now_ut_x;
                            min_ut_z = now_ut_z;
                            res = TRUE;
                        }
                    }
                }
            }
        }
    }

    return res;
}

extern int mNpc_GetMakeUtNuminBlock_area(int* ut_x, int* ut_z, int bx, int bz, int restrict_area) {
    static u16 fg_flag[UT_Z_NUM];

    mCoBG_Collision_u* col_top;
    mActor_name_t* fg_top;
    u16* fg_flag_p = fg_flag;
    int candidates;
    int res;
    int i;
    int j;
    int rand;

    col_top = mFI_GetBkNum2ColTop(bx, bz);
    fg_top = mFI_BkNumtoUtFGTop(bx, bz);
    candidates = 0;
    res = FALSE;

    if (restrict_area < 0 || restrict_area > 9) {
        return FALSE;
    }

    bzero(fg_flag, sizeof(fg_flag));

    if (fg_top != NULL && col_top != NULL) {
        for (i = restrict_area; i < UT_Z_NUM - restrict_area; i++) {
            for (j = restrict_area; j < UT_X_NUM - restrict_area; j++) {
                if (mNpc_CheckNpcSet_fgcol(fg_top[i * UT_X_NUM + j], col_top[i * UT_X_NUM + j].data.unit_attribute) ==
                    TRUE) {
                    *fg_flag_p |= 1 << j;
                    candidates++;
                }
            }

            fg_flag_p++;
        }
    }

    fg_flag_p = fg_flag;
    if (candidates > 0) {
        rand = RANDOM(candidates);

        for (i = restrict_area; i < UT_Z_NUM - restrict_area; i++) {
            for (j = restrict_area; j < UT_X_NUM - restrict_area; j++) {
                if (((*fg_flag_p >> j) & 1) == 1) {
                    if (rand == 0) {
                        *ut_x = j;
                        *ut_z = i;
                        res = TRUE;

                        break;
                    } else {
                        rand--;
                    }
                }
            }

            if (res == TRUE) {
                break;
            }

            fg_flag_p++;
        }
    }

    return res;
}

extern int mNpc_GetMakeUtNuminBlock(int* ut_x, int* ut_z, int bx, int bz) {
    return mNpc_GetMakeUtNuminBlock_area(ut_x, ut_z, bx, bz, 1); // can't spawn in the outer-most square of units
}

static int mNpc_CheckNpcSet_height(int bx, int bz, int ut_x, int ut_z, mActor_name_t item, mCoBG_Collision_u* col) {
    int res = FALSE;

    if (col != NULL && mNpc_CheckNpcSet_fgcol(item, col->data.unit_attribute)) {
        xyz_t wpos;

        mFI_BkandUtNum2Wpos(&wpos, bx, bz, ut_x, ut_z);

        if (mCoBG_ExistHeightGap_KeepAndNow(wpos) == FALSE) {
            res = TRUE;
        }
    }

    return res;
}

extern int mNpc_GetMakeUtNuminBlock33(int* make_ut_x, int* make_ut_z, int ut_x, int ut_z, int bx, int bz) {
    static int ut_xnum_table[9] = { 0, 1, -1, 0, 1, -1, 0, 1, -1 };
    static int ut_znum_table[9] = { 0, 0, 0, 1, 1, 1, -1, -1, -1 };

    mCoBG_Collision_u* col_top;
    mActor_name_t* fg_top;
    int res;
    int x;
    int z;
    int idx;
    int i;

    col_top = mFI_GetBkNum2ColTop(bx, bz);
    fg_top = mFI_BkNumtoUtFGTop(bx, bz);
    res = FALSE;

    if (col_top != NULL && fg_top != NULL) {
        for (i = 0; i < 9; i++) {
            x = ut_x + ut_xnum_table[i];
            z = ut_z + ut_znum_table[i];

            if (x >= 1 && x < (UT_X_NUM - 1) && z >= 1 && z < (UT_Z_NUM - 1)) {
                idx = z * UT_X_NUM + x;

                if (mNpc_CheckNpcSet_height(bx, bz, x, z, fg_top[idx], &col_top[idx]) == TRUE) {
                    make_ut_x[0] = x;
                    make_ut_z[0] = z;
                    res = TRUE;

                    break;
                }
            }
        }
    }

    return res;
}

extern int mNpc_GetMakeUtNuminBlock_hide_hard_area(int* ut_x, int* ut_z, int bx, int bz, int restrict_area) {
    static u16 hide_ut_bit[UT_Z_NUM];

    int now_ut_z;
    int now_ut_x;
    mCoBG_Collision_u* col_top;
    mActor_name_t* fg_top;
    int min_ut_x;
    int min_ut_z;
    int res;
    int i;
    int j;

    col_top = mFI_GetBkNum2ColTop(bx, bz);
    fg_top = mFI_BkNumtoUtFGTop(bx, bz);
    min_ut_x = UT_X_NUM;
    min_ut_z = UT_Z_NUM;
    res = FALSE;

    if (restrict_area < 0 || restrict_area > 9) {
        return FALSE;
    }

    if (fg_top != NULL && col_top != NULL) {
        bzero(hide_ut_bit, sizeof(hide_ut_bit));
        mAGrw_SetHideUtInfo(hide_ut_bit, fg_top);

        for (i = restrict_area; i < UT_Z_NUM - restrict_area; i++) {
            for (j = restrict_area; j < UT_X_NUM - restrict_area; j++) {
                if (mNpc_CheckNpcSet_fgcol_hard(fg_top[i * UT_X_NUM + j], col_top[i * UT_X_NUM + j].data.unit_attribute) == TRUE) {
                    /* Check that the height of each point on the unit is equal*/
                    if (col_top[i * UT_X_NUM + j].data.center == col_top[i * UT_X_NUM + j].data.top_left && col_top[i * UT_X_NUM + j].data.center == col_top[i * UT_X_NUM + j].data.bot_left &&
                        col_top[i * UT_X_NUM + j].data.center == col_top[i * UT_X_NUM + j].data.bot_right && col_top[i * UT_X_NUM + j].data.center == col_top[i * UT_X_NUM + j].data.top_right &&
                        ((hide_ut_bit[i] >> j) & 1) == 1) {

                        now_ut_x = 8 - j;
                        now_ut_z = 8 - i;

                        now_ut_x = ABS(now_ut_x);
                        now_ut_z = ABS(now_ut_z);

                        if (min_ut_x > now_ut_x && min_ut_z > now_ut_z) {
                            *ut_x = j;
                            *ut_z = i;
                            min_ut_x = now_ut_x;
                            min_ut_z = now_ut_z;
                            res = TRUE;
                        }
                    }
                }
            }
        }
    }

    return res;
}

typedef struct npc_temper_s {
    u16 unlock_timer;
    u8 over_impatient_num;
    u8 talk_num_max;
} mNpc_Temper_c;

typedef struct npc_talk_info_s {
    u16 timer;
    u8 talk_num;
    u8 quest_request;
    u16 unlock_timer;
    u16 reset_timer;
} mNpc_Talk_Info_c;

static mNpc_Talk_Info_c l_npc_talk_info[ANIMAL_NUM_MAX + mISL_ISLANDER_NUM];
static mNpc_Temper_c l_npc_temper[mNpc_FEEL_NUM] = {
    { 4000, 12, 15 }, // mNpc_FEEL_NORMAL
    { 3000, 10, 13 }, // mNpc_FEEL_HAPPY
    { 4000, 12, 15 }, // mNpc_FEEL_ANGRY
    { 4000, 10, 13 }, // mNpc_FEEL_SAD
    { 5000, 9, 12 },  // mNpc_FEEL_SLEEPY
    { 5000, 9, 12 }   // mNpc_FEEL_PITFALL
};

extern void mNpc_ClearTalkInfo() {
    mNpc_Talk_Info_c* talk_info_p = l_npc_talk_info;
    int i;

    bzero(talk_info_p, sizeof(l_npc_talk_info));

    for (i = 0; i < ARRAY_COUNT(l_npc_talk_info); i++) {
        talk_info_p->quest_request = TRUE;
        talk_info_p++;
    }
}

static void mNpc_TimerCountDown(mNpc_Talk_Info_c* talk_info, int ticks) {
    if (talk_info->timer > 0) {
        talk_info->timer = ticks >= talk_info->timer ? 0 : talk_info->timer - ticks;
    }
}

static void mNpc_SetUnlockTimer(u16* unlock_timer, u16* reset_timer, int looks) {
    unlock_timer[0] = l_npc_temper[looks].unlock_timer;
    reset_timer[0] = unlock_timer[0];
}

static int mNpc_CountTalkNum(int animal_idx, int looks) {
    int res = FALSE;

    if (animal_idx >= 0 && animal_idx < ARRAY_COUNT(l_npc_talk_info)) {
        mNpc_Talk_Info_c* talk_info = &l_npc_talk_info[animal_idx];

        if (talk_info->talk_num < l_npc_temper[looks].talk_num_max && talk_info->timer > 0) {
            talk_info->talk_num++;
            res = TRUE;
        }
    }

    return res;
}

extern int mNpc_CheckOverImpatient(int animal_idx, int looks) {
    int res = FALSE;

    if (animal_idx >= 0 && animal_idx < ARRAY_COUNT(l_npc_talk_info)) {
        mNpc_Talk_Info_c* talk_info = &l_npc_talk_info[animal_idx];

        if (talk_info->talk_num >= l_npc_temper[looks].over_impatient_num) {
            res = TRUE;
        }
    }

    return res;
}

extern int mNpc_GetOverImpatient(int animal_idx, int looks) {
    int patience = mNpc_PATIENCE_NORMAL;

    if (animal_idx >= 0 && animal_idx < ARRAY_COUNT(l_npc_talk_info)) {
        mNpc_Talk_Info_c* talk_info = &l_npc_talk_info[animal_idx];

        if (talk_info->talk_num >= l_npc_temper[looks].over_impatient_num) {
            if (talk_info->talk_num >= l_npc_temper[looks].talk_num_max) {
                patience = mNpc_PATIENCE_ANNOYED; // refuse to talk
            } else {
                patience = mNpc_PATIENCE_MILDLY_ANNOYED; // dialog shows mild annoyance
            }
        }
    }

    return patience;
}

extern int mNpc_CheckQuestRequest(int animal_idx) {
    int res = FALSE;

    if (animal_idx >= 0 && animal_idx < ARRAY_COUNT(l_npc_talk_info)) {
        mNpc_Talk_Info_c* talk_info = &l_npc_talk_info[animal_idx];

        if (talk_info->quest_request == TRUE) {
            res = TRUE;
        }
    }

    return res;
}

extern void mNpc_SetQuestRequestOFF(int animal_idx, int looks) {
    mNpc_Talk_Info_c* talk_info = &l_npc_talk_info[animal_idx];

    if (animal_idx >= 0 && animal_idx < ARRAY_COUNT(l_npc_talk_info)) {
        if (talk_info->quest_request == TRUE) {
            mNpc_SetUnlockTimer(&talk_info->unlock_timer, &talk_info->reset_timer, looks);
        }

        talk_info->quest_request = FALSE;
    }
}

static void mNpc_UnlockTimerCountDown(mNpc_Talk_Info_c* talk_info, int ticks) {
    if (talk_info != NULL && talk_info->unlock_timer > 0 && talk_info->unlock_timer > (talk_info->reset_timer - 1000)) {
        talk_info->unlock_timer = ticks >= talk_info->unlock_timer ? 0 : talk_info->unlock_timer - ticks;
    }
}

extern void mNpc_TalkInfoMove() {
    mNpc_Talk_Info_c* talk_info_p = l_npc_talk_info;
    static float talk_timer_accum = 0.0f;
    int ticks = graph_dt_60hz_ticks(gamePT, &talk_timer_accum);
    int i;

    if (mFI_CheckPlayerWade(mFI_WADE_START) == TRUE) {
        for (i = 0; i < ARRAY_COUNT(l_npc_talk_info); i++) {
            talk_info_p->reset_timer = talk_info_p->unlock_timer;
            talk_info_p++;
        }
    }

    talk_info_p = l_npc_talk_info;
    for (i = 0; i < ARRAY_COUNT(l_npc_talk_info); i++) {
        mNpc_TimerCountDown(talk_info_p, ticks);
        mNpc_UnlockTimerCountDown(talk_info_p, ticks);

        if (talk_info_p->unlock_timer == 0 && talk_info_p->reset_timer > 0) {
            talk_info_p->talk_num = 0;
            talk_info_p->quest_request = TRUE;
            talk_info_p->reset_timer = 0;
        }

        talk_info_p++;
    }
}

extern void mNpc_TalkEndMove(int animal_idx, int looks) {
    if (animal_idx >= 0 && animal_idx < ARRAY_COUNT(l_npc_talk_info) && looks >= 0 && looks < mNpc_LOOKS_NUM) {
        mNpc_Talk_Info_c* talk_info = &l_npc_talk_info[animal_idx];
        talk_info->timer = 1000;

        if (mNpc_CountTalkNum(animal_idx, looks) == TRUE && mNpc_CheckOverImpatient(animal_idx, looks) == TRUE) {
            mNpc_SetUnlockTimer(&talk_info->unlock_timer, &talk_info->reset_timer, looks);
        }
    }
}

extern int mNpc_GetNpcFloorNo() {
    mActor_name_t field_id = mFI_GetFieldId();
    mActor_name_t owner_name = Common_Get(house_owner_name);
    int floor_no = -1;

    if (mFI_GET_TYPE(field_id) == mFI_FIELD_NPCROOM0) {

        if (owner_name != EMPTY_NO && owner_name != RSV_NO) {
            int idx = mNpc_SearchAnimalinfo(Save_Get(animals), owner_name, ANIMAL_NUM_MAX);

            floor_no = Common_Get(npclist[idx]).house_data.floor_id;
        }
    }

    return floor_no;
}

extern int mNpc_GetNpcWallNo() {
    mActor_name_t field_id = mFI_GetFieldId();
    mActor_name_t owner_name = Common_Get(house_owner_name);
    int wall_no = -1;

    if (mFI_GET_TYPE(field_id) == mFI_FIELD_NPCROOM0) {

        if (owner_name != EMPTY_NO && owner_name != RSV_NO) {
            int idx = mNpc_SearchAnimalinfo(Save_Get(animals), owner_name, ANIMAL_NUM_MAX);

            wall_no = Common_Get(npclist[idx]).house_data.wall_id;
        }
    }

    return wall_no;
}

/* 75% */

extern void mNpc_SetTalkBee() {
    if (Common_Get(player_bee_swell_flag) != TRUE) {
        Animal_c* animal = Save_Get(animals);
        mNpc_NpcList_c* npclist = Common_Get(npclist);
        int i;

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
                npclist->conversation_flags.beesting = TRUE;
            }

            animal++;
            npclist++;
        }

        if (mNpc_CheckFreeAnimalInfo(&Save_Get(island).animal) == FALSE) {
            Common_Get(island_npclist[0]).conversation_flags.beesting = TRUE;
        }
    }
}

extern u8 mNpc_GetFishCompleteTalk(mNpc_NpcList_c* npclist) {
    u8 res = TRUE;

    if (npclist != NULL) {
        res = npclist->conversation_flags.fish_complete;
    }

    return res;
}

extern u8 mNpc_GetInsectCompleteTalk(mNpc_NpcList_c* npclist) {
    u8 res = TRUE;

    if (npclist != NULL) {
        res = npclist->conversation_flags.insect_complete;
    }

    return res;
}

extern void mNpc_SetFishCompleteTalk(mNpc_NpcList_c* npclist) {
    if (npclist != NULL) {
        npclist->conversation_flags.fish_complete = TRUE;
    }
}

extern void mNpc_SetInsectCompleteTalk(mNpc_NpcList_c* npclist) {
    if (npclist != NULL) {
        npclist->conversation_flags.insect_complete = TRUE;
    }
}

extern void mNpc_SetNpcHomeYpos() {
    Animal_c* animal = Save_Get(animals);
    mNpc_NpcList_c* npclist = Common_Get(npclist);
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            npclist->house_position.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(npclist->house_position, 0.0f);
        }

        animal++;
        npclist++;
    }
}

static void mNpc_SetIslandAnimalHouse(Anmhome_c* home) {
    int island_x_blocks[mISL_FG_BLOCK_X_NUM];
    int set = FALSE;
    int bx;
    int ut;

    mFI_GetIslandBlockNumX(island_x_blocks);

    for (bx = 0; bx < mISL_FG_BLOCK_X_NUM; bx++) {
        mActor_name_t* items = &Save_Get(island).fgblock[0][bx].items[0][0];

        if (items != NULL) {
            for (ut = 0; ut < UT_TOTAL_NUM; ut++) {
                if (*items == COTTAGE_NPC) {
                    home->block_x = island_x_blocks[bx];
                    home->block_z = mISL_BLOCK_Z;
                    home->ut_x = ut & 15;
                    home->ut_z = (ut >> 4) + 1;
                    set = TRUE;

                    break;
                }

                items++;
            }

            if (set == TRUE) {
                break;
            }
        }
    }
}

extern void mNpc_DecideIslandNpc(Animal_c* animal) {
    static int cand_table[NPC_ISLANDER_NUM];

    int* cand_p = cand_table;
    int candidates = 0;
    mNpc_Default_Data_c* def_list;
    mActor_name_t npc_id;
    s8* grow_list;
    int i;

    bzero(cand_p, sizeof(cand_table));
    mNpc_ClearIslandAnimalInfo(animal);
    def_list = npc_def_list;
    grow_list = npc_grow_list;

    for (i = 0; i < NPC_NUM; i++) {
        if (*grow_list == mNpc_GROW_ISLANDER) {
            cand_p[0] = i;
            cand_p++;
            candidates++;
        }

        if (candidates >= NPC_ISLANDER_NUM) {
            break;
        }

        grow_list++;
    }

    if (candidates <= 0) {
        candidates = 1;
    }

    npc_id = NPC_START | cand_table[RANDOM(candidates)];
    mNpc_SetDefAnimal(animal, npc_id, def_list);
    mNpc_SetHaveAppeared(npc_id);
    mNpc_SetIslandAnimalHouse(&animal->home_info);
}

static mActor_name_t l_mnpc_get_ftr = EMPTY_NO;
static int l_mnpc_get_letter = FALSE;
static int l_mnpc_chk_ftr_msg = FALSE;

typedef struct island_ftr_s {
    u16 set_ftr_bitfield;
    mActor_name_t trade_list[mNpc_ISLAND_FTR_SAVE_NUM];
    mActor_name_t item_list[mNpc_ISLAND_FTR_NUM];
} mNpc_Island_Ftr_c;

static mNpc_Island_Ftr_c l_mnpc_island_ftr;

static void mNpc_ClearIslandItemList(mActor_name_t* item_list, int count) {
    bzero(item_list, count * sizeof(mActor_name_t));
}

static int mNpc_GetFreeIslandItemListIdx(mActor_name_t* item_list, int count) {
    int idx = -1;
    int i;

    for (i = 0; i < count; i++) {
        if (*item_list == EMPTY_NO) {
            idx = i;
            break;
        }

        item_list++;
    }

    return idx;
}

static int mNpc_SetIslandItemList(mActor_name_t* item_list, int count, mActor_name_t item) {
    int res = FALSE;
    int free_idx = mNpc_GetFreeIslandItemListIdx(item_list, count);

    if (free_idx != -1) {
        item_list[free_idx] = item;
        res = TRUE;
    }

    return res;
}

extern void mNpc_SetIslandRoomFtr(Animal_c* animal) {
    mNpc_Island_Ftr_c* island_ftr_p = &l_mnpc_island_ftr;

    if (animal != NULL) {
        Anmmem_c* memory = animal->memories;
        int i;

        island_ftr_p->set_ftr_bitfield = 0;
        for (i = 0; i < ANIMAL_MEMORY_NUM; i++) {
            if (mNpc_CheckFreeAnimalMemory(memory) == FALSE) {
                island_ftr_p->set_ftr_bitfield |= memory->memuni.island.have_bitfield;
            }

            memory++;
        }

        bcopy(&animal->anmuni.island_ftr, island_ftr_p->trade_list, mNpc_ISLAND_FTR_SAVE_NUM * sizeof(mActor_name_t));
        mNpc_ClearIslandItemList(island_ftr_p->item_list, mNpc_ISLAND_FTR_NUM);
    }
}

static int mNpc_GetIslandFtrIdx(mActor_name_t item) {
    mActor_name_t* island_room = mNpc_GetIslandRoomP(Save_Get(island).animal.id.npc_id);
    int n = 0;
    int idx = -1;
    int i;

    if (island_room != NULL && ITEM_IS_FTR(item)) {
        if (mNpc_CheckFtrIsIslandBestFtr(item) == TRUE) {
            for (i = 0; i < UT_TOTAL_NUM; i++) {
                if (ITEM_IS_FTR(*island_room)) {
                    if (aMR_CorrespondFurniture(item, *island_room) == TRUE) {
                        idx = n;
                        break;
                    }

                    n++;
                } else if (*island_room >= RSV_ISLAND_FTR0 && *island_room <= RSV_ISLAND_FTR15) {
                    n++;
                }

                if (n == mNpc_ISLAND_FTR_NUM) {
                    break;
                }

                island_room++;
            }
        } else {
            int ftr_unit = aMR_GetFurnitureUnit(item);
            u32 ftr_variant0;
            u32 ftr_variant1;
            int j;

            if (ftr_unit == mRmTp_FTRSIZE_1x1) {
                ftr_variant0 = RSV_ISLAND_FTR0;
                ftr_variant1 = RSV_ISLAND_FTR4;
            } else {
                ftr_variant0 = (mActor_name_t)(RSV_ISLAND_FTR0 + (ftr_unit + 1) * mRmTp_DIRECT_NUM);
                ftr_variant1 = EMPTY_NO;
            }

            for (i = 0; i < UT_TOTAL_NUM; i++) {
                if (ITEM_IS_FTR(*island_room)) {
                    n++;
                } else if (*island_room >= RSV_ISLAND_FTR0 && *island_room <= RSV_ISLAND_FTR15) {
                    for (j = 0; j < mRmTp_DIRECT_NUM; j++) {
                        if (*island_room == (mActor_name_t)(ftr_variant0 + j) ||
                            *island_room == (mActor_name_t)(ftr_variant1 + j)) {
                            idx = n;
                            break;
                        }
                    }

                    if (idx != -1) {
                        break;
                    }

                    n++;
                }

                if (n == mNpc_ISLAND_FTR_NUM) {
                    break;
                }

                island_room++;
            }
        }
    }

    return idx;
}

extern void mNpc_SetIslandGetFtr(mActor_name_t ftr) {
    int n;
    mNpc_Island_Ftr_c* island_ftr_p = &l_mnpc_island_ftr;
    mActor_name_t* island_room = mNpc_GetIslandRoomP(Save_Get(island).animal.id.npc_id);
    int set;
    int variant;
    int slot;
    int i;

    n = 0;
    set = FALSE;

    if (ftr != EMPTY_NO && ITEM_IS_FTR(ftr) && island_room != NULL) {
        if (mNpc_CheckFtrIsIslandBestFtr(ftr) == TRUE) {
            int idx = mNpc_GetIslandFtrIdx(ftr);

            if (idx >= 0 && idx < mNpc_ISLAND_FTR_NUM && ((island_ftr_p->set_ftr_bitfield >> idx) & 1) == 0) {
                island_ftr_p->set_ftr_bitfield |= (1 << idx);
                set = TRUE;
            }
        } else {
            int ftr_unit = aMR_GetFurnitureUnit(ftr);
            mActor_name_t ftr_variant0;
            mActor_name_t ftr_variant1;
            int j;

            if (ftr_unit == mRmTp_FTRSIZE_1x1) {
                ftr_variant0 = RSV_ISLAND_FTR0;
                ftr_variant1 = RSV_ISLAND_FTR4;
            } else {
                ftr_variant0 = RSV_ISLAND_FTR0 + (ftr_unit + 1) * 4;
                ftr_variant1 = EMPTY_NO;
            }

            for (i = 0; i < UT_TOTAL_NUM; i++) {
                if (ITEM_IS_FTR(*island_room)) {
                    n++;
                } else if (*island_room >= RSV_ISLAND_FTR0 && *island_room <= RSV_ISLAND_FTR15) {
                    variant = -1;

                    for (j = 0; j < mRmTp_DIRECT_NUM; j++) {
                        if (*island_room == (mActor_name_t)(ftr_variant0 + j)) {
                            variant = 0;
                            break;
                        } else if (*island_room == (mActor_name_t)(ftr_variant1 + j)) {
                            variant = 1;
                            break;
                        }
                    }

                    if (variant != -1 && n >= 0 && n < mNpc_ISLAND_FTR_NUM &&
                        ((island_ftr_p->set_ftr_bitfield >> n) & 1) == 0) {
                        island_ftr_p->set_ftr_bitfield |= (1 << n);

                        if (variant == 0) {
                            slot = (ftr_variant0 - RSV_ISLAND_FTR0) / mNpc_ISLAND_FTR_SAVE_NUM;
                        } else {
                            slot = (ftr_variant1 - RSV_ISLAND_FTR0) / mNpc_ISLAND_FTR_SAVE_NUM;
                        }

                        if (slot < mNpc_ISLAND_FTR_SAVE_NUM) {
                            ftr = aMR_FurnitureFg_to_FurnitureFgWithDirect(ftr, j);
                            island_ftr_p->trade_list[slot] = ftr;
                            set = TRUE;
                        }

                        break;
                    }

                    n++;
                }

                if (n == mNpc_ISLAND_FTR_NUM) {
                    break;
                }

                island_room++;
            }
        }

        if (set == TRUE) {
            mNpc_SetIslandItemList(island_ftr_p->item_list, mNpc_ISLAND_FTR_NUM, ftr);
        }
    }
}

extern void mNpc_SetIslandGetFtrtoRoom() {
    mActor_name_t* item_list = l_mnpc_island_ftr.item_list;
    Animal_c* animal = &Save_Get(island).animal;

    if (Common_Get(now_private) != NULL) {
        Private_c* priv = Common_Get(now_private);
        int i;

        for (i = 0; i < mNpc_ISLAND_FTR_NUM; i++) {
            if (*item_list != EMPTY_NO && ITEM_IS_FTR(*item_list)) {
                mNpc_SetIslandFtr(&priv->player_ID, *item_list);
            }

            item_list++;
        }

        mNpc_RestoreIslandPresentFtr();
        mNpc_ClearIslandPresentFtrInfo();
        mNpc_SetIslandRoomFtr(animal);
    }
}

extern void mNpc_SetIslandGetLetter(int get) {
    l_mnpc_get_letter = get;
}

extern int mNpc_GetIslandGetLetter() {
    return l_mnpc_get_letter;
}

extern void mNpc_SetIslandCheckFtrMsg(int set) {
    l_mnpc_chk_ftr_msg = set;
}

extern int mNpc_GetIslandCheckFtrMsg() {
    return l_mnpc_chk_ftr_msg;
}

typedef struct npc_island_room_data_s {
    mActor_name_t items[UT_Z_NUM][UT_X_NUM];
    int wall_no;
    int floor_no;
    mActor_name_t npc_id;
} mNpc_Island_Npc_Room_Data_c;

static mNpc_Island_Npc_Room_Data_c l_island_npc_room_data[NPC_ISLANDER_NUM];

static mActor_name_t l_island_npc_best_fg_id[NPC_ISLANDER_NUM][2] = {
    { 0x0250, 0x0251 }, { 0x0346, 0x0347 }, { 0x0372, 0x0373 }, { 0x027C, 0x027D }, { 0x02EA, 0x02EB },
    { 0x0326, 0x0327 }, { 0x0270, 0x0271 }, { 0x01C0, 0x01C1 }, { 0x039A, 0x039B }, { 0x02F0, 0x02F1 },
    { 0x02C4, 0x02C5 }, { 0x0224, 0x0225 }, { 0x02D4, 0x02D5 }, { 0x02A4, 0x02A5 }, { 0x038C, 0x038D },
    { 0x01FE, 0x01FF }, { 0x032E, 0x032F }, { 0x01E6, 0x01E7 }
};

extern void mNpc_ClearIslandNpcRoomData() {
    bzero(l_island_npc_room_data, sizeof(l_island_npc_room_data));
}

extern void mNpc_IslandNpcRoomDataSet(mFM_fg_data_c** data_table, int base_idx) {
    mNpc_Island_Npc_Room_Data_c* dst = l_island_npc_room_data;
    s8* grow_list = npc_grow_list;
    mNpc_NpcHouseData_c* house_list = npc_house_list;
    int islander = 0;
    int i;

    for (i = 0; i < NPC_NUM; i++) {
        if (*grow_list == mNpc_GROW_ISLANDER) {
            int idx = l_island_npc_best_fg_id[islander][0] - base_idx;
            mFM_fg_data_c* best_id_p = data_table[idx];

            if (best_id_p != NULL) {
                dst->wall_no = house_list->wall_id;
                dst->floor_no = house_list->floor_id;
                bcopy(data_table[idx]->items, dst->items, sizeof(best_id_p->items));
                dst->npc_id = NPC_START | i;

                islander++;
                dst++;
            }
        }

        if (islander >= NPC_ISLANDER_NUM) {
            break;
        }

        grow_list++;
        house_list++;
    }
}

static mNpc_Island_Npc_Room_Data_c* mNpc_GetIslandRoomInfoP(mActor_name_t npc_id) {
    mNpc_Island_Npc_Room_Data_c* room_p = l_island_npc_room_data;
    mNpc_Island_Npc_Room_Data_c* res = NULL;
    int i;

    for (i = 0; i < NPC_ISLANDER_NUM; i++) {
/* @BUG - devs used & instead of && */
#ifndef BUGFIXES
        if (npc_id != EMPTY_NO & room_p->npc_id == npc_id) {
#else
        if (npc_id != EMPTY_NO && room_p->npc_id == npc_id) {
#endif
            res = room_p;
            break;
        }

        room_p++;
    }

    return res;
}

extern mActor_name_t* mNpc_GetIslandRoomP(mActor_name_t npc_id) {
    mActor_name_t* res = NULL;
    mNpc_Island_Npc_Room_Data_c* room_info = mNpc_GetIslandRoomInfoP(npc_id);

    if (room_info != NULL) {
        res = room_info->items[0];
    }

    return res;
}

extern void mNpc_GetIslandWallFloorIdx(int* wall, int* floor, mActor_name_t npc_id) {
    mNpc_Island_Npc_Room_Data_c* room_info;

    if (wall != NULL && floor != NULL) {
        wall[0] = 8;
        floor[0] = 32;

        room_info = mNpc_GetIslandRoomInfoP(npc_id);

        if (room_info != NULL) {
            wall[0] = room_info->wall_no;
            floor[0] = room_info->floor_no;
        }
    }
}

static mActor_name_t mNpc_getNormalFtr(mActor_name_t rsv_name, Animal_c* animal) {
    mActor_name_t ftr = EMPTY_NO;
    int idx;

    if (rsv_name >= RSV_ISLAND_FTR0 && rsv_name <= RSV_ISLAND_FTR15) {
        int rsv = rsv_name - RSV_ISLAND_FTR0;

        idx = (rsv - (rsv % mNpc_ISLAND_FTR_SAVE_NUM)) / mNpc_ISLAND_FTR_SAVE_NUM;
        if (idx >= mNpc_ISLAND_FTR_SAVE_NUM) {
            idx = 0;
        }

        ftr = animal->anmuni.island_ftr[idx];
    }

    return ftr;
}

static int mNpc_CheckIslandNpcRoomFtrIdx(int ftr_idx) {
    Animal_c* animal = &Save_Get(island).animal;
    Anmmem_c* memory;
    int i;
    int res = -1;

    if (mNpc_CheckFreeAnimalInfo(animal) == FALSE && ftr_idx >= 0 && ftr_idx < mNpc_ISLAND_FTR_NUM) {
        memory = animal->memories;

        for (i = 0; i < ANIMAL_MEMORY_NUM; i++) {
            if (mPr_NullCheckPersonalID(&memory->memory_player_id) == FALSE &&
                ((memory->memuni.island.have_bitfield >> ftr_idx) & 1) == 1) {
                res = i;
                break;
            }

            memory++;
        }
    }

    return res;
}

extern int mNpc_CheckIslandNpcRoomFtrItemNo_keep(mActor_name_t ftr) {
    mActor_name_t* island_room;
    int keep;
    mActor_name_t* trade_list;
    mNpc_Island_Ftr_c* island_ftr_p;
    mActor_name_t rsv_item;
    int n;
    int found;
    int i;
    int j;

    island_ftr_p = &l_mnpc_island_ftr;
    trade_list = l_mnpc_island_ftr.trade_list;
    rsv_item = EMPTY_NO;
    found = FALSE;
    n = 0;
    keep = FALSE;
    island_room = mNpc_GetIslandRoomP(Save_Get(island).animal.id.npc_id);

    if (ITEM_IS_FTR(ftr) && island_room != NULL) {
        if (mNpc_CheckFtrIsIslandBestFtr(ftr) == TRUE) {
            int idx = mNpc_GetIslandFtrIdx(ftr);

/* @BUG & should've been && */
#ifndef BUGFIXES
            if (((idx >= 0) & (idx < mNpc_ISLAND_FTR_NUM)) && ((island_ftr_p->set_ftr_bitfield >> idx) & 1) == 0) {
#else
            if (((idx >= 0) && (idx < mNpc_ISLAND_FTR_NUM)) && ((island_ftr_p->set_ftr_bitfield >> idx) & 1) == 0) {
#endif
                keep = TRUE;
            }
        } else {
            for (i = 0; i < mNpc_ISLAND_FTR_SAVE_NUM; i++) {
                /* Why loop through each direction instead of just masking off the rotation bits */
                for (j = 0; j < mRmTp_DIRECT_NUM; j++) {
                    mActor_name_t dir_item = aMR_FurnitureFg_to_FurnitureFgWithDirect(ftr, j);

                    if (dir_item == trade_list[i]) {
                        found = TRUE;
                        break;
                    }
                }

                if (found == TRUE) {
                    break;
                }
            }

            if (found == FALSE) {
                int ftr_unit = aMR_GetFurnitureUnit(ftr);

                if (ftr_unit == mRmTp_FTRSIZE_1x1) {
                    if (trade_list[0] == EMPTY_NO) {
                        rsv_item = RSV_ISLAND_FTR0;
                    } else if (trade_list[1] == EMPTY_NO) {
                        rsv_item = RSV_ISLAND_FTR4;
                    }
                } else if (ftr_unit != -1) {
                    ftr_unit++;

                    if (trade_list[ftr_unit] == EMPTY_NO) {
                        rsv_item = RSV_ISLAND_FTR0 + ftr_unit * mRmTp_DIRECT_NUM;
                    }
                }

                if (rsv_item != EMPTY_NO) {
                    for (i = 0; i < UT_TOTAL_NUM; i++) {
                        if (*island_room >= RSV_ISLAND_FTR0 && *island_room <= RSV_ISLAND_FTR15) {
                            for (j = 0; j < mRmTp_DIRECT_NUM; j++) {
                                if (*island_room == (mActor_name_t)(rsv_item + j)) {
                                    keep = TRUE;
                                    break;
                                }
                            }
                        }

                        if (keep == TRUE) {
                            break;
                        }

                        island_room++;
                    }
                }
            }
        }
    }

    return keep;
}

extern void mNpc_ChangeIslandRoom(mActor_name_t* items) {
    Animal_c* animal = &Save_Get(island).animal;
    int n = 0;
    int i;

    if (items != NULL) {
        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if (ITEM_IS_FTR(*items)) {
                if (mNpc_CheckIslandNpcRoomFtrIdx(n) == -1) {
                    items[0] = RSV_NO; // cleared because the item hasn't been "obtained" by the islander yet
                }

                n++;
            } else if (*items >= RSV_ISLAND_FTR0 && *items <= RSV_ISLAND_FTR15) {
                if (mNpc_CheckIslandNpcRoomFtrIdx(n) == -1) {
                    items[0] = RSV_NO; // cleared because the item hasn't been "obtained" by the islander yet
                } else {
                    items[0] = mNpc_getNormalFtr(*items, animal); // update with "not best" furniture
                }

                n++;
            }

            if (n >= mNpc_ISLAND_FTR_NUM) {
                break;
            }

            items++;
        }
    }
}

extern int mNpc_CheckFtrIsIslandBestFtr(mActor_name_t ftr) {
    mActor_name_t* island_room;
    int i;
    int res = FALSE;

    island_room = mNpc_GetIslandRoomP(Save_Get(island).animal.id.npc_id);
    if (island_room != NULL && ITEM_IS_FTR(ftr)) {
        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if (aMR_CorrespondFurniture(ftr, *island_room) == TRUE) {
                res = TRUE;
                break;
            }

            island_room++;
        }
    }

    return res;
}

extern int mNpc_CheckFtrIsIslandNormalFtr(mActor_name_t ftr) {
    int res = FALSE;

    if (ITEM_IS_FTR(ftr) && mNpc_CheckFtrIsIslandBestFtr(ftr) == FALSE) {
        res = TRUE;
    }

    return res;
}

// TODO: The deviation here is likely fakematch
#if VERSION != VER_GAFE01_00
extern int mNpc_SetIslandFtr(PersonalID_c* pid, mActor_name_t ftr) {
    int n;
    Anmmem_c* memory;
    mActor_name_t* island_room;
    mActor_name_t rsv_item;
    int variant;
    int set;
    int direct;
    int i;
    int j;
    int slot;
    int mem_idx;

    memory = Save_Get(island).animal.memories;
    island_room = mNpc_GetIslandRoomP(Save_Get(island).animal.id.npc_id);
    n = 0;
    rsv_item = EMPTY_NO;
    set = FALSE;
    slot = 0;
    direct = 0;

    if (ITEM_IS_FTR(ftr) && island_room != NULL && pid != NULL && mPr_NullCheckPersonalID(pid) == FALSE) {
        mem_idx = mNpc_GetAnimalMemoryIdx(pid, memory, ANIMAL_MEMORY_NUM);

        if (mem_idx == -1) {
            memory = &memory[mNpc_ForceGetFreeAnimalMemoryIdx(&Save_Get(island).animal, memory, ANIMAL_MEMORY_NUM)];
            mNpc_SetAnimalMemory(pid, &Save_Get(island).animal.id, memory);
        } else {
            memory = &memory[mem_idx];
        }

        /* Unnecessary NULL check, memory is guaranteed to exist */
        if (memory != NULL) {
            if (mNpc_CheckFtrIsIslandBestFtr(ftr) == TRUE) {
                int idx = mNpc_GetIslandFtrIdx(ftr);

                if (idx != -1 && mNpc_CheckIslandNpcRoomFtrIdx(idx) == -1) {
                    memory->memuni.island.have_bitfield |= (1 << idx);
                    set = TRUE;
                }
            } else {
                mActor_name_t ftr_variant0;
                mActor_name_t ftr_variant1;
                int ftr_unit = aMR_GetFurnitureUnit(ftr);

                if (ftr_unit == mRmTp_FTRSIZE_1x1) {
                    ftr_variant0 = RSV_ISLAND_FTR0;
                    ftr_variant1 = RSV_ISLAND_FTR4;
                } else {
                    ftr_variant0 = RSV_ISLAND_FTR0 + (ftr_unit + 1) * 4;
                    ftr_variant1 = EMPTY_NO;
                }

                for (i = 0; i < UT_TOTAL_NUM; i++) {
                    if (ITEM_IS_FTR(*island_room)) {
                        n++;
                    } else if (*island_room >= RSV_ISLAND_FTR0 && *island_room <= RSV_ISLAND_FTR15) {
                        variant = -1;

                        for (j = 0; j < mRmTp_DIRECT_NUM; j++) {
                            if (*island_room == (mActor_name_t)(ftr_variant0 + j)) {
                                direct = j;
                                variant = 0;
                                break;
                            } else if (*island_room == (mActor_name_t)(ftr_variant1 + j)) {
                                direct = j;
                                variant = 1;
                                break;
                            }
                        }

                        if (variant != -1 && mNpc_CheckIslandNpcRoomFtrIdx(n) == -1) {
                            memory->memuni.island.have_bitfield |= (1 << n);

                            if (variant == 0) {
                                slot = (ftr_variant0 - RSV_ISLAND_FTR0) / mNpc_ISLAND_FTR_SAVE_NUM;
                            } else {
                                slot = (ftr_variant1 - RSV_ISLAND_FTR0) / mNpc_ISLAND_FTR_SAVE_NUM;
                            }

                            if (slot < mNpc_ISLAND_FTR_SAVE_NUM) {
                                Save_Get(island).animal.anmuni.island_ftr[slot] =
                                    aMR_FurnitureFg_to_FurnitureFgWithDirect(ftr, direct);
                                set = TRUE;
                            }

                            break;
                        }

                        n++;
                    }

                    if (n == mNpc_ISLAND_FTR_NUM) {
                        break;
                    }

                    island_room++;
                }
            }
        }
    }

    return set;
}
#else
extern int mNpc_SetIslandFtr(PersonalID_c* pid, mActor_name_t ftr) {
    int n;
    Anmmem_c* memory;
    mActor_name_t* island_room;
    int slot;
    Animal_c* animal;
    mActor_name_t rsv_item;
    int i;
    int j;
    int variant;
    int set;
    int direct;

    memory = Save_Get(island).animal.memories;
    animal = &Save_Get(island).animal;
    island_room = mNpc_GetIslandRoomP(animal->id.npc_id);
    n = 0;
    rsv_item = EMPTY_NO;
    set = FALSE;
    slot = 0;
    direct = 0;

    if (ITEM_IS_FTR(ftr) && island_room != NULL && pid != NULL && mPr_NullCheckPersonalID(pid) == FALSE) {
        int mem_idx = mNpc_GetAnimalMemoryIdx(pid, memory, ANIMAL_MEMORY_NUM);

        if (mem_idx == -1) {
            memory = &memory[mNpc_ForceGetFreeAnimalMemoryIdx(animal, memory, ANIMAL_MEMORY_NUM)];
            mNpc_SetAnimalMemory(pid, &animal->id, memory);
        } else {
            memory = &memory[mem_idx];
        }

        /* Unnecessary NULL check, memory is guaranteed to exist */
        if (memory != NULL) {
            if (mNpc_CheckFtrIsIslandBestFtr(ftr) == TRUE) {
                int idx = mNpc_GetIslandFtrIdx(ftr);

                if (idx != -1 && mNpc_CheckIslandNpcRoomFtrIdx(idx) == -1) {
                    memory->memuni.island.have_bitfield |= (1 << idx);
                    set = TRUE;
                }
            } else {
                mActor_name_t ftr_variant0;
                mActor_name_t ftr_variant1;
                int ftr_unit = aMR_GetFurnitureUnit(ftr);

                if (ftr_unit == mRmTp_FTRSIZE_1x1) {
                    ftr_variant0 = RSV_ISLAND_FTR0;
                    ftr_variant1 = RSV_ISLAND_FTR4;
                } else {
                    ftr_variant0 = RSV_ISLAND_FTR0 + (ftr_unit + 1) * 4;
                    ftr_variant1 = EMPTY_NO;
                }

                for (i = 0; i < UT_TOTAL_NUM; i++) {
                    if (ITEM_IS_FTR(*island_room)) {
                        n++;
                    } else if (*island_room >= RSV_ISLAND_FTR0 && *island_room <= RSV_ISLAND_FTR15) {
                        variant = -1;

                        for (j = 0; j < mRmTp_DIRECT_NUM; j++) {
                            if (*island_room == (mActor_name_t)(ftr_variant0 + j)) {
                                direct = j;
                                variant = 0;
                                break;
                            } else if (*island_room == (mActor_name_t)(ftr_variant1 + j)) {
                                direct = j;
                                variant = 1;
                                break;
                            }
                        }

                        if (variant != -1 && mNpc_CheckIslandNpcRoomFtrIdx(n) == -1) {
                            memory->memuni.island.have_bitfield |= (1 << n);

                            if (variant == 0) {
                                slot = (ftr_variant0 - RSV_ISLAND_FTR0) / mNpc_ISLAND_FTR_SAVE_NUM;
                            } else {
                                slot = (ftr_variant1 - RSV_ISLAND_FTR0) / mNpc_ISLAND_FTR_SAVE_NUM;
                            }

                            if (slot < mNpc_ISLAND_FTR_SAVE_NUM) {
                                Save_Get(island).animal.anmuni.island_ftr[slot] =
                                    aMR_FurnitureFg_to_FurnitureFgWithDirect(ftr, direct);
                                set = TRUE;
                            }

                            break;
                        }

                        n++;
                    }

                    if (n == mNpc_ISLAND_FTR_NUM) {
                        break;
                    }

                    island_room++;
                }
            }
        }
    }

    return set;
}
#endif

extern int mNpc_EraseIslandFtr(mActor_name_t ftr) {
    int n;
    Animal_c* animal;
    mActor_name_t* island_room;
    mActor_name_t* island_ftr;
    mActor_name_t rsv_no;
    int i;
    int j;
    int variant;
    int set;

    animal = &Save_Get(island).animal;
    island_room = mNpc_GetIslandRoomP(animal->id.npc_id);
    island_ftr = Save_Get(island).animal.anmuni.island_ftr;
    rsv_no = EMPTY_NO;
    n = 0;
    set = FALSE;

    if (ITEM_IS_FTR(ftr) && island_room != NULL) {
        if (mNpc_CheckFtrIsIslandBestFtr(ftr) == TRUE) {
            int idx = mNpc_GetIslandFtrIdx(ftr);
            int mem_idx = mNpc_CheckIslandNpcRoomFtrIdx(idx);

            if (idx != -1 && mem_idx != -1) {
                Anmmem_c* memory = &Save_Get(island).animal.memories[mem_idx];
                u16* have_bitfield_p = &memory->memuni.island.have_bitfield;
                u16 have_bitfield = have_bitfield_p[0] & ~(1 << idx);
                have_bitfield_p[0] = have_bitfield;
                set = TRUE;
            }
        } else {
            for (i = 0; i < mNpc_ISLAND_FTR_SAVE_NUM; i++) {
                for (j = 0; j < mRmTp_DIRECT_NUM; j++) {
                    mActor_name_t ftr_rot = aMR_FurnitureFg_to_FurnitureFgWithDirect(ftr, j);

                    if (ftr_rot == island_ftr[i]) {
                        rsv_no = RSV_ISLAND_FTR0 + i * mRmTp_DIRECT_NUM;
                        island_ftr[i] = EMPTY_NO;
                        break;
                    }
                }

                if (rsv_no != EMPTY_NO) {
                    break;
                }
            }

            if (rsv_no != EMPTY_NO) {
                for (i = 0; i < UT_TOTAL_NUM; i++) {
                    if (ITEM_IS_FTR(*island_room)) {
                        n++;
                    } else if (*island_room >= RSV_ISLAND_FTR0 && *island_room <= RSV_ISLAND_FTR15) {
                        variant = -1;

                        for (j = 0; j < mRmTp_DIRECT_NUM; j++) {
                            if (*island_room == (mActor_name_t)(rsv_no + j)) {
                                variant = 1;
                                break;
                            }
                        }

                        if (variant != -1) {
                            int mem_idx = mNpc_CheckIslandNpcRoomFtrIdx(n);

                            if (mem_idx != -1) {
                                Anmmem_c* memory = &Save_Get(island).animal.memories[mem_idx];
                                u16* have_bitfield_p = &memory->memuni.island.have_bitfield;
                                u16 have_bitfield = have_bitfield_p[0] & ~(1 << n);
                                have_bitfield_p[0] = have_bitfield;
                                set = TRUE;

                                break;
                            }
                        }

                        n++;
                    }

                    if (n == mNpc_ISLAND_FTR_NUM) {
                        break;
                    }

                    island_room++;
                }
            }
        }
    }

    return set;
}

extern int mNpc_EraseIslandFtr_keep(mActor_name_t ftr) {
    int n;
    Animal_c* animal;
    mNpc_Island_Ftr_c* island_ftr_p;
    mActor_name_t* island_room;
    mActor_name_t* trade_list;
    int set;
    mActor_name_t rsv_no;
    int i;
    int j;

    animal = &Save_Get(island).animal;
    island_ftr_p = &l_mnpc_island_ftr;
    island_room = mNpc_GetIslandRoomP(animal->id.npc_id);
    trade_list = l_mnpc_island_ftr.trade_list;
    rsv_no = EMPTY_NO;
    n = 0;
    set = FALSE;

    if (ITEM_IS_FTR(ftr) && island_room != NULL) {
        if (mNpc_CheckFtrIsIslandBestFtr(ftr) == TRUE) {
            int idx = mNpc_GetIslandFtrIdx(ftr);

            if (idx >= 0 && idx < mNpc_ISLAND_FTR_NUM && ((island_ftr_p->set_ftr_bitfield >> idx) & 1) == 1) {
                u16* set_ftr_bitfield_p = &island_ftr_p->set_ftr_bitfield;
                u16 set_bitfield = set_ftr_bitfield_p[0] & ~(1 << idx);
                set_ftr_bitfield_p[0] = set_bitfield;
                set = TRUE;
            }
        } else {
            for (i = 0; i < mNpc_ISLAND_FTR_SAVE_NUM; i++) {
                for (j = 0; j < mRmTp_DIRECT_NUM; j++) {
                    mActor_name_t ftr_rot = aMR_FurnitureFg_to_FurnitureFgWithDirect(ftr, j);

                    if (ftr_rot == trade_list[i]) {
                        rsv_no = RSV_ISLAND_FTR0 + i * mRmTp_DIRECT_NUM;
                        trade_list[i] = EMPTY_NO;
                        break;
                    }
                }

                if (rsv_no != EMPTY_NO) {
                    break;
                }
            }

            if (rsv_no != EMPTY_NO) {
                for (i = 0; i < UT_TOTAL_NUM; i++) {
                    if (ITEM_IS_FTR(*island_room)) {
                        n++;
                    } else if (*island_room >= RSV_ISLAND_FTR0 && *island_room <= RSV_ISLAND_FTR15) {
                        int variant = -1;

                        for (j = 0; j < mRmTp_DIRECT_NUM; j++) {
                            if (*island_room == (mActor_name_t)(rsv_no + j)) {
                                variant = 1;
                                break;
                            }
                        }

                        if (variant != -1 && n >= 0 && n < mNpc_ISLAND_FTR_NUM &&
                            ((island_ftr_p->set_ftr_bitfield >> n) & 1) == 1) {
                            u16* set_ftr_bitfield_p = &island_ftr_p->set_ftr_bitfield;
                            u16 set_bitfield = set_ftr_bitfield_p[0] & ~(1 << n);
                            set_ftr_bitfield_p[0] = set_bitfield;
                            set = TRUE;

                            break;
                        }

                        n++;
                    }

                    if (n == mNpc_ISLAND_FTR_NUM) {
                        break;
                    }

                    island_room++;
                }
            }
        }
    }

    return set;
}

typedef struct island_present_ftr_s {
    PersonalID_c pid;
    mActor_name_t present;
} mNpc_IslandPresentFtr_c;

static mNpc_IslandPresentFtr_c l_mnpc_island_present_ftr;

static void mNpc_ClearIslandPresentFtrInfo_common(mNpc_IslandPresentFtr_c* info) {
    mPr_ClearPersonalID(&info->pid);
    info->present = EMPTY_NO;
}

extern void mNpc_ClearIslandPresentFtrInfo() {
    mNpc_ClearIslandPresentFtrInfo_common(&l_mnpc_island_present_ftr);
}

extern void mNpc_SetIslandPresentFtr() {
    Animal_c* animal;
    AnmPersonalID_c* anm_id;
    mNpc_IslandPresentFtr_c* present_ftr_p;
    Anmmem_c* memory;
    int ftr_num;
    mActor_name_t* island_room;
    int selected;
    int n;
    int i;

    ftr_num = 0;
    n = 0;
    animal = &Save_Get(island).animal;
    anm_id = &Save_Get(island).animal.id;
    memory = Save_Get(island).animal.memories;
    present_ftr_p = &l_mnpc_island_present_ftr;

    mNpc_ClearIslandPresentFtrInfo_common(present_ftr_p);

    for (i = 0; i < mNpc_ISLAND_FTR_NUM; i++) {
        if (mNpc_CheckIslandNpcRoomFtrIdx(i) != -1) {
            ftr_num++;
        }
    }

    if (ftr_num > 1) {
        selected = RANDOM(ftr_num);
        island_room = mNpc_GetIslandRoomP(anm_id->npc_id);

        if (island_room != NULL) {
            for (i = 0; i < UT_TOTAL_NUM; i++) {
                if (ITEM_IS_FTR(*island_room)) {
                    if (mNpc_CheckIslandNpcRoomFtrIdx(n) != -1) {
                        if (selected == 0) {
                            int mem_idx;

                            present_ftr_p->present =
                                aMR_FurnitureFg_to_FurnitureFgWithDirect(*island_room, mRmTp_DIRECT_SOUTH);
                            mem_idx = mNpc_CheckIslandNpcRoomFtrIdx(n);

                            if (mem_idx != -1) {
                                memory = &memory[mem_idx];
                                mPr_CopyPersonalID(&present_ftr_p->pid, &memory->memory_player_id);
                            }

                            break;
                        } else {
                            selected--;
                        }
                    }

                    n++;
                } else if (*island_room >= RSV_ISLAND_FTR0 && *island_room <= RSV_ISLAND_FTR15) {
                    if (mNpc_CheckIslandNpcRoomFtrIdx(n) != -1) {
                        if (selected == 0) {
                            int mem_idx;

                            present_ftr_p->present = mNpc_getNormalFtr(*island_room, animal);
                            mem_idx = mNpc_CheckIslandNpcRoomFtrIdx(n);

                            if (mem_idx != -1) {
                                memory = &memory[mem_idx];
                                mPr_CopyPersonalID(&present_ftr_p->pid, &memory->memory_player_id);
                            }

                            break;
                        } else {
                            selected--;
                        }
                    }

                    n++;
                }

                island_room++;
            }
        }
    }

    if (mNpc_CheckIslandPresentFtrIs() == TRUE) {
        mNpc_EraseIslandFtr(mNpc_GetIslandPresentFtr());
    }
}

extern void mNpc_RestoreIslandPresentFtr() {
    PersonalID_c* pid;
    mActor_name_t present;

    if (mNpc_CheckIslandPresentFtrIs() == TRUE) {
        present = mNpc_GetIslandPresentFtr();
        pid = mNpc_GetIslandPresentFtrPersonalID();

        if (present != EMPTY_NO && pid != NULL && mPr_NullCheckPersonalID(pid) == FALSE) {
            mNpc_SetIslandFtr(pid, present);
        }
    }
}

extern int mNpc_GetIslandRoomFtrNum() {
    int num = 0;
    int i;

    for (i = 0; i < mNpc_ISLAND_FTR_NUM; i++) {
        if (mNpc_CheckIslandNpcRoomFtrIdx(i) != -1) {
            num++;
        }
    }

    return num;
}

extern int mNpc_CheckIslandPresentFtrIs() {
    mNpc_IslandPresentFtr_c* present_ftr_p = &l_mnpc_island_present_ftr;
    int res = FALSE;

    if (present_ftr_p->present != EMPTY_NO && mPr_NullCheckPersonalID(&present_ftr_p->pid) == FALSE) {
        res = TRUE;
    }

    return res;
}

extern mActor_name_t mNpc_GetIslandPresentFtr() {
    return l_mnpc_island_present_ftr.present;
}

extern PersonalID_c* mNpc_GetIslandPresentFtrPersonalID() {
    PersonalID_c* pid = NULL;

    if (mNpc_CheckIslandPresentFtrIs() == TRUE) {
        pid = &l_mnpc_island_present_ftr.pid;
    }

    return pid;
}

extern mActor_name_t mNpc_GetRandomBestFtr() {
    Animal_c* animal = &Save_Get(island).animal;
    mActor_name_t* island_room = mNpc_GetIslandRoomP(animal->id.npc_id);
    mNpc_Island_Ftr_c* island_ftr_p = &l_mnpc_island_ftr;
    mActor_name_t* island_room_p = island_room;
    int other_ftr_num = 0;
    int n = 0;
    mActor_name_t best_ftr = EMPTY_NO;
    mActor_name_t present = mNpc_GetIslandPresentFtr();
    int selected;
    int i;

    if (island_room != NULL) {
        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if (ITEM_IS_FTR(*island_room)) {
                if (n >= 0 && n < mNpc_ISLAND_FTR_NUM && ((island_ftr_p->set_ftr_bitfield >> n) & 1) == 0 &&
                    aMR_CorrespondFurniture(present, *island_room) == FALSE) {
                    other_ftr_num++;
                }

                n++;
            } else if (*island_room >= RSV_ISLAND_FTR0 && *island_room <= RSV_ISLAND_FTR15) {
                n++;
            }

            island_room++;
        }

        island_room = island_room_p;
        n = 0;

        if (island_room != NULL && other_ftr_num > 0) {
            selected = RANDOM(other_ftr_num);

            for (i = 0; i < UT_TOTAL_NUM; i++) {
                if (ITEM_IS_FTR(*island_room)) {
                    if (n >= 0 && n < mNpc_ISLAND_FTR_NUM && ((island_ftr_p->set_ftr_bitfield >> n) & 1) == 0 &&
                        aMR_CorrespondFurniture(present, *island_room) == FALSE) {
                        if (selected == 0) {
                            best_ftr = aMR_FurnitureFg_to_FurnitureFgWithDirect(*island_room, mRmTp_DIRECT_SOUTH);
                            break;
                        } else {
                            selected--;
                        }
                    }

                    n++;
                } else if (*island_room >= RSV_ISLAND_FTR0 && *island_room <= RSV_ISLAND_FTR15) {
                    n++;
                }

                island_room++;
            }
        }
    }

    return best_ftr;
}

extern Anmmem_c* mNpc_GetOtherBestFtr(PersonalID_c* pid, mActor_name_t* other_best_ftr, mActor_name_t exist_ftr) {
    Animal_c* animal;
    mActor_name_t* island_room;
    Anmmem_c* memory;
    Anmmem_c* memories;
    mActor_name_t* island_room_p;
    int other_ftr_num;
    int n;
    int mem_idx;
    int i;

    animal = &Save_Get(island).animal;
    memories = Save_Get(island).animal.memories;
    memory = NULL;
    island_room = mNpc_GetIslandRoomP(animal->id.npc_id);
    island_room_p = island_room;
    other_ftr_num = 0;
    n = 0;

    if (island_room != NULL && other_best_ftr != NULL) {
        other_best_ftr[0] = EMPTY_NO;
        mem_idx = mNpc_GetAnimalMemoryIdx(pid, memories, ANIMAL_MEMORY_NUM);

        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if (ITEM_IS_FTR(*island_room)) {
                if (aMR_CorrespondFurniture(*island_room, exist_ftr) == FALSE) {
                    int ftr_idx = mNpc_CheckIslandNpcRoomFtrIdx(n);

                    /* The item must not have been gifted by the current player */
                    if (ftr_idx != -1 && ftr_idx != mem_idx) {
                        other_ftr_num++;
                    }
                }

                n++;
            } else if (*island_room >= RSV_ISLAND_FTR0 && *island_room <= RSV_ISLAND_FTR15) {
                n++;
            }

            island_room++;
        }

        island_room = island_room_p;
        n = 0;

        if (island_room != NULL && other_ftr_num > 0) {
            int selected = RANDOM(other_ftr_num);

            for (i = 0; i < UT_TOTAL_NUM; i++) {
                if (ITEM_IS_FTR(*island_room)) {
                    if (aMR_CorrespondFurniture(*island_room, exist_ftr) == FALSE) {
                        int ftr_idx = mNpc_CheckIslandNpcRoomFtrIdx(n);

                        /* The item must not have been gifted by the current player */
                        if (ftr_idx != -1 && ftr_idx != mem_idx) {
                            if (selected == 0) {
                                other_best_ftr[0] =
                                    aMR_FurnitureFg_to_FurnitureFgWithDirect(*island_room, mRmTp_DIRECT_SOUTH);
                                memory = &memories[ftr_idx]; /* Memory of the other player who gave it */
                                break;
                            } else {
                                selected--;
                            }
                        }
                    }

                    n++;
                } else if (*island_room >= RSV_ISLAND_FTR0 && *island_room <= RSV_ISLAND_FTR15) {
                    n++;
                }

                island_room++;
            }
        }
    }

    return memory;
}

extern mActor_name_t mNpc_GetPlayerBestFtr(PersonalID_c* pid, mActor_name_t exist_ftr) {
    AnmPersonalID_c* anm_id;
    Anmmem_c* memories;
    mActor_name_t* island_room;
    mActor_name_t* island_room_p;
    int mem_idx;
    int other_ftr_num;
    int n;
    int selected;
    int i;
    mActor_name_t best_ftr;

    anm_id = &Save_Get(island).animal.id;
    memories = Save_Get(island).animal.memories;
    island_room = mNpc_GetIslandRoomP(anm_id->npc_id);
    other_ftr_num = 0;
    n = 0;
    best_ftr = EMPTY_NO;
    island_room_p = island_room;

    if (island_room != NULL && pid != NULL) {
        mem_idx = mNpc_GetAnimalMemoryIdx(pid, memories, ANIMAL_MEMORY_NUM);

        if (mem_idx != -1) {
            for (i = 0; i < UT_TOTAL_NUM; i++) {
                if (ITEM_IS_FTR(*island_room)) {
                    if (aMR_CorrespondFurniture(*island_room, exist_ftr) == FALSE) {
                        int ftr_idx = mNpc_CheckIslandNpcRoomFtrIdx(n);

                        /* The item must have been gifted by the current player */
                        if (ftr_idx == mem_idx) {
                            other_ftr_num++;
                        }
                    }

                    n++;
                } else if (*island_room >= RSV_ISLAND_FTR0 && *island_room <= RSV_ISLAND_FTR15) {
                    n++;
                }

                island_room++;
            }

            n = 0;

            if (island_room_p != NULL && other_ftr_num > 0) {
                selected = RANDOM(other_ftr_num);
                island_room = island_room_p;

                for (i = 0; i < UT_TOTAL_NUM; i++) {
                    if (ITEM_IS_FTR(*island_room)) {
                        if (aMR_CorrespondFurniture(*island_room, exist_ftr) == FALSE) {
                            int ftr_idx = mNpc_CheckIslandNpcRoomFtrIdx(n);

                            /* The item must have been gifted by the current player */
                            if (ftr_idx == mem_idx) {
                                if (selected == 0) {
                                    best_ftr =
                                        aMR_FurnitureFg_to_FurnitureFgWithDirect(*island_room, mRmTp_DIRECT_SOUTH);
                                    break;
                                } else {
                                    selected--;
                                }
                            }
                        }

                        n++;
                    } else if (*island_room >= RSV_ISLAND_FTR0 && *island_room <= RSV_ISLAND_FTR15) {
                        n++;
                    }

                    island_room++;
                }
            }
        }
    }

    return best_ftr;
}

extern mActor_name_t mNpc_GetPlayerFtr(PersonalID_c* pid) {
    Animal_c* animal = &Save_Get(island).animal;
    mActor_name_t* island_room = mNpc_GetIslandRoomP(Save_Get(island).animal.id.npc_id);
    mActor_name_t best_ftr = EMPTY_NO;
    mActor_name_t* island_room_p = island_room;
    int other_ftr_num = 0;
    int n = 0;
    int mem_idx = mNpc_GetAnimalMemoryIdx(pid, animal->memories, ANIMAL_MEMORY_NUM);
    int selected;
    int i;

    if (island_room != NULL && mem_idx != -1) {
        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if (ITEM_IS_FTR(*island_room) || (*island_room >= RSV_ISLAND_FTR0 && *island_room <= RSV_ISLAND_FTR15)) {
                int ftr_idx = mNpc_CheckIslandNpcRoomFtrIdx(n);

                /* The item must have been gifted by the current player */
                if (ftr_idx == mem_idx) {
                    other_ftr_num++;
                }

                n++;
            }

            island_room++;
        }

        island_room = island_room_p;
        n = 0;

        if (island_room != NULL && other_ftr_num > 0) {
            selected = RANDOM(other_ftr_num);

            for (i = 0; i < UT_TOTAL_NUM; i++) {
                if (ITEM_IS_FTR(*island_room) ||
                    (*island_room >= RSV_ISLAND_FTR0 && *island_room <= RSV_ISLAND_FTR15)) {
                    int ftr_idx = mNpc_CheckIslandNpcRoomFtrIdx(n);

                    /* The item must have been gifted by the current player */
                    if (ftr_idx == mem_idx) {
                        if (selected == 0) {
                            mActor_name_t ftr = *island_room;

                            if (ftr >= RSV_ISLAND_FTR0 && ftr <= RSV_ISLAND_FTR15) {
                                ftr = mNpc_getNormalFtr(ftr, animal);
                            }

                            best_ftr = aMR_FurnitureFg_to_FurnitureFgWithDirect(ftr, mRmTp_DIRECT_SOUTH);
                            break;
                        } else {
                            selected--;
                        }
                    }

                    n++;
                }

                island_room++;
            }
        }
    }

    return best_ftr;
}

static int mNpc_CheckIslandAnimalTableNo(mActor_name_t npc_id) {
    int res = FALSE;

    if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC && (npc_id & 0xFFF) < NPC_NUM &&
        npc_grow_list[npc_id & 0xFFF] == mNpc_GROW_ISLANDER) {
        res = TRUE;
    }

    return res;
}

static int mNpc_CheckIslandAnimalID(AnmPersonalID_c* anm_id) {
    int res = FALSE;

    if (anm_id != NULL && mNpc_CheckFreeAnimalPersonalID(anm_id) == FALSE) {
        res = mNpc_CheckIslandAnimalTableNo(anm_id->npc_id);
    }

    return res;
}

extern int mNpc_CheckIslandAnimal(Animal_c* animal) {
    int res = FALSE;

    if (animal != NULL) {
        res = mNpc_CheckIslandAnimalID(&animal->id);
    }

    return res;
}

static mActor_name_t l_mnpc_island_md_table[NPC_ISLANDER_NUM] = {
    ITM_MINIDISK16, // K.K. Tango
    ITM_MINIDISK08, // K.K. Aria
    ITM_MINIDISK06, // K.K. Etude
    ITM_MINIDISK33, // K.K. Soul
    ITM_MINIDISK26, // K.K. Rock
    ITM_MINIDISK15, // K.K. Ska
    ITM_MINIDISK07, // K.K. Lullaby
    ITM_MINIDISK05, // K.K. Fusion
    ITM_MINIDISK43, // Comrade K.K.
    ITM_MINIDISK09, // K.K. Samba
    ITM_MINIDISK49, // Cafe K.K.
    ITM_MINIDISK13, // K.K. Mambo
    ITM_MINIDISK01, // K.K. March
    ITM_MINIDISK44, // K.K. Lament
    ITM_MINIDISK40, // K.K. Country
    ITM_MINIDISK10, // K.K. Bossa
    ITM_MINIDISK18, // Aloha K.K.
    ITM_MINIDISK46  // K.K. Dirge
};

extern u32 mNpc_GetMDIdx(mActor_name_t npc_id) {
    mNpc_Island_Npc_Room_Data_c* room_data = l_island_npc_room_data;
    u32 idx = 0;
    int i;

    for (i = 0; i < NPC_ISLANDER_NUM; i++) {
        if (room_data->npc_id == npc_id) {
            idx = (u16)(l_mnpc_island_md_table[i] - ITM_MINIDISK_START);
            // TODO: Bug? missing break here
        }

        room_data++;
    }

    return idx;
}

extern u32 mNpc_GetIslandMDIdx() {
    return mNpc_GetMDIdx(Save_Get(island).animal.id.npc_id);
}

static Mail_c l_npc_hp_mail;

extern void mNpc_ClearHPMail(AnmHPMail_c* hp_mail, int count) {
    bzero(hp_mail, count * sizeof(AnmHPMail_c));
}

extern void mNpc_AllClearHPMailPlayerIdx(int player_no) {
    Animal_c* animal = Save_Get(animals);
    int i;

    if (player_no >= 0 && player_no < PLAYER_NUM) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            mNpc_ClearHPMail(&animal->hp_mail[player_no], 1);
            animal++;
        }
    }
}

extern int mNpc_ReceiveHPMail(Mail_c* mail) {
    static u8 password[mMpswd_PASSWORD_DATA_LEN];

    Animal_c* animal = Save_Get(animals);
    AnmPersonalID_c anm_id;
    int res = FALSE;
    int private_idx = mPr_GetPrivateIdx(&mail->header.sender.personalID);

    if (mail->header.sender.type == mMl_NAME_TYPE_PLAYER && private_idx >= 0 && private_idx < PLAYER_NUM) {
        int is_password = mMpswd_restore_code(mail->content.body, password);

        if (is_password == TRUE && mMl_get_npcinfo_from_mail_name(&anm_id, &mail->header.recipient) == TRUE) {
            int npc_idx = mNpc_SearchAnimalinfo(animal, anm_id.npc_id, ANIMAL_NUM_MAX);

            if (npc_idx != -1) {
                animal = &animal[npc_idx];

                if (animal != NULL) {
/* @BUG - the final byte of the password should not be stored. */
#ifndef BUGFIXES
                    bcopy(password, animal->hp_mail[private_idx].password, mMpswd_PASSWORD_DATA_LEN);
#else
                    bcopy(password, animal->hp_mail[private_idx].password,
                          sizeof(animal->hp_mail[private_idx].password));
#endif
                    lbRTC_TimeCopy(&animal->hp_mail[private_idx].receive_time, Common_GetPointer(time.rtc_time));
                    res = TRUE;
                }
            }
        }
    }

    return res;
}

static int mNpc_SendHPMailNum_famicom(PersonalID_c* pid, AnmPersonalID_c* anm_id, mMpswd_password_c* password) {
    static u8 name_str[mIN_ITEM_NAME_LEN];

    Mail_c* hp_mail = &l_npc_hp_mail;
    int mail_no;
    mActor_name_t present = EMPTY_NO;
    int res = FALSE;

    if (mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE) {
        mMl_clear_mail(hp_mail);

        if (password->hit_rate_index == 1 &&                 // hit rate index must be 1
            mMpswd_password_zuru_check(password) == FALSE && // checksum is valid
            mMpswd_check_present(password) == TRUE &&        // present is valid
            mMpswd_check_name(password) == TRUE              // player & town name match
        ) {
            mail_no = 0x24A + anm_id->looks; // valid password
            present = password->item;
        } else {
            mail_no = 0x250 + anm_id->looks; // invalid password
        }

        mHandbill_Set_free_str(mHandbill_FREE_STR0, pid->player_name, PLAYER_NAME_LEN);
        mNpc_ClearBufSpace1(name_str, ANIMAL_NAME_LEN);
        mNpc_GetNpcWorldNameAnm(name_str, anm_id);
        mHandbill_Set_free_str(mHandbill_FREE_STR1, name_str, ANIMAL_NAME_LEN);
        mHandbill_Set_free_str(mHandbill_FREE_STR2, password->str1, PLAYER_NAME_LEN);
        mHandbill_Set_free_str(mHandbill_FREE_STR3, password->str0, PLAYER_NAME_LEN);

        if (present != EMPTY_NO) {
            mNpc_ClearBufSpace1(name_str, mIN_ITEM_NAME_LEN);
            mIN_copy_name_str(name_str, present);
            mHandbill_Set_free_str(mHandbill_FREE_STR4, name_str, mIN_ITEM_NAME_LEN);
        }

        /* Why is free string 6 the same as free string 1? */
        mNpc_ClearBufSpace1(name_str, ANIMAL_NAME_LEN);
        mNpc_GetNpcWorldNameAnm(name_str, anm_id);
        mHandbill_Set_free_str(mHandbill_FREE_STR6, name_str, ANIMAL_NAME_LEN);

        mNpc_LoadMailDataCommon2(hp_mail, pid, anm_id, present, mNpc_GetPaperType(), mail_no);
        res = mPO_receipt_proc(hp_mail, mPO_SENDTYPE_MAIL);
    }

    return res;
}

static int mNpc_SendHPMailNum_popular(PersonalID_c* pid, AnmPersonalID_c* anm_id, mMpswd_password_c* password) {
    static u8 name_str[mIN_ITEM_NAME_LEN];
    static u8 submenu_name_str[mIN_ITEM_NAME_LEN];

    Mail_c* hp_mail = &l_npc_hp_mail;
    mActor_name_t npc_id;
    int mail_no;
    mActor_name_t present;
    u8 valid;
    u8 special;
    mActor_name_t target_npc_id;
    int npc_idx;
    int looks;
    int res;

    present = EMPTY_NO;
    res = FALSE;
    valid = FALSE;
    special = FALSE;

    if (mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE) {
        mMl_clear_mail(hp_mail);

        if (mMpswd_password_zuru_check(password) == FALSE && // checksum is valid
            mMpswd_check_npc_code(password) == TRUE &&       // valid npc code
            mMpswd_check_present(password) == TRUE &&        // present is valid
            mMpswd_check_name(password) == TRUE              // player & town name match
        ) {
            /* Valid password */
            mNpc_ClearBufSpace1(name_str, ANIMAL_NAME_LEN);
            mNpc_ClearBufSpace1(submenu_name_str, ANIMAL_NAME_LEN);

            if (password->npc_type == mMpswd_NPCTYPE_NORMAL) {
                mActor_name_t npc_id = anm_id->npc_id;

                npc_idx = npc_id & 0xFFF;
                target_npc_id = NPC_START | password->npc_code;
                looks = mNpc_GetLooks(target_npc_id);

                if (npc_idx == password->npc_code) {
                    mail_no = 0x256 + looks;
                } else if (mNpc_CheckIslandAnimalTableNo(target_npc_id) == TRUE) {
                    mail_no = 0x262 + looks;
                } else {
                    looks = mNpc_GetLooks(target_npc_id); // re-calling the function?
                    mail_no = 0x25C + looks;
                }

                mNpc_GetNpcWorldNameTableNo(name_str, NPC_START | password->npc_code);
                mNpc_GetNpcWorldNameTableNo(submenu_name_str, NPC_START | password->npc_code);
                valid = TRUE;
            } else {
                /* Special NPC */
                mail_no = 0x268 + password->npc_code;
                npc_id = mMpswd_get_sp_npc_num(password->npc_code);
                mNpc_GetActorWorldName(name_str, npc_id);
                mNpc_GetActorWorldName(submenu_name_str, npc_id);

                /* Leftover from JP, replace ちん (-san) honorific with spaces */
                if (submenu_name_str[4] == 0x0A && submenu_name_str[5] == 0xC3) {
                    submenu_name_str[4] = CHAR_SPACE;
                    submenu_name_str[5] = CHAR_SPACE;
                }

                valid = TRUE;
                special = TRUE;
            }

            if (password->item != RSV_NO) {
                present = password->item;
            }
        } else {
            /* Invalid password */
            mail_no = 0x288 + anm_id->looks;
        }

        mHandbill_Set_free_str(mHandbill_FREE_STR0, pid->player_name, PLAYER_NAME_LEN);
        mHandbill_Set_free_str(mHandbill_FREE_STR1, name_str, ANIMAL_NAME_LEN);
        mHandbill_Set_free_str(mHandbill_FREE_STR2, password->str1, PLAYER_NAME_LEN);
        mHandbill_Set_free_str(mHandbill_FREE_STR3, password->str0, PLAYER_NAME_LEN);

        if (present != EMPTY_NO) {
            mNpc_ClearBufSpace1(name_str, mIN_ITEM_NAME_LEN);
            mIN_copy_name_str(name_str, present);
            mHandbill_Set_free_str(mHandbill_FREE_STR4, name_str, mIN_ITEM_NAME_LEN);
        }

        /* Why is free string 6 the same as free string 1? */
        mNpc_ClearBufSpace1(name_str, ANIMAL_NAME_LEN);
        mNpc_GetNpcWorldNameAnm(name_str, anm_id);
        mHandbill_Set_free_str(mHandbill_FREE_STR6, name_str, ANIMAL_NAME_LEN);

        mNpc_LoadMailDataCommon2(hp_mail, pid, anm_id, present, mNpc_GetPaperType(), mail_no);

        if (valid == TRUE) {
            // Overwrite the sender name with the name of the password's embedded villager name
            bcopy(submenu_name_str, hp_mail->header.sender.personalID.player_name, PLAYER_NAME_LEN);
            bcopy(pid->player_name, hp_mail->header.recipient.personalID.player_name, PLAYER_NAME_LEN);

            if (special == TRUE) {
                hp_mail->content.mail_type = mMl_TYPE_SPNPC_PASSWORD;
            }
        }

        res = mPO_receipt_proc(hp_mail, mPO_SENDTYPE_MAIL);
    }

    return res;
}

static int mNpc_CheckHit_Rate(u8 hitrate, int n) {
    u8 perfect_bit = 0xFF;
    int res = FALSE;
    int i;

    for (i = 0; i < n; i++) {
        perfect_bit &= ~(1 << i);
    }

    if ((hitrate & perfect_bit) == 0) {
        res = TRUE;
    }

    return res;
}

static int mNpc_GetHit(u8 hitrate) {
    static u8 prob_table[] = { 80, 60, 30, 0, 100 };

    int res = FALSE;

    if (hitrate < ARRAY_COUNT(prob_table)) {
        u8 hit = RANDOM(100);

        if (hit < prob_table[hitrate]) {
            res = TRUE;
        }
    }

    return res;
}

static void mNPC_get_gobi_str_from_name(u8* str, mActor_name_t npc_id) {
    if (str != NULL && ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
        int idx = npc_id & 0xFFF;

/* @BUG - devs used && instead of || */
#ifndef BUGFIXES
        if (idx < 0 && idx >= NPC_NUM) {
#else
        if (idx < 0 || idx >= NPC_NUM) {
#endif
            idx = 0;
        }

        mString_Load_StringFromRom(str, ANIMAL_CATCHPHRASE_LEN, npc_def_list[idx].catchphrase_str_idx);
    }
}

static int mNpc_GetHit_cardE(u8 hitrate) {
    static int prob_table[] = { 80, 60, 40, 20 };

    int res = FALSE;

    if (hitrate < ARRAY_COUNT(prob_table)) {
        u8 hit = RANDOM(100);

        if (hit < prob_table[hitrate]) {
            res = TRUE;
        }
    }

    return res;
}

static int mNpc_SendHPMailNum_cardE(PersonalID_c* pid, AnmPersonalID_c* anm_id, mMpswd_password_c* password) {
    static u8 submenu_name_str[mIN_ITEM_NAME_LEN];
    static u8 name_str[mIN_ITEM_NAME_LEN];
    static u8 gobi_str[ANIMAL_CATCHPHRASE_LEN];

    Mail_c* hp_mail = &l_npc_hp_mail;
    int mail_no;
    mActor_name_t present = EMPTY_NO;
    int res = FALSE;
    u8 valid = FALSE;
    u8 special = FALSE;
    int famicom_hit;

    if (mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE) {
        mMl_clear_mail(hp_mail);

        if (mMpswd_password_zuru_check(password) == FALSE && // checksum is valid
            mMpswd_check_present(password) == TRUE &&        // present is valid
            mMpswd_check_npc_code(password) == TRUE          // valid npc code
        ) {
            /* Valid password */
            famicom_hit = FALSE;
            mNpc_ClearBufSpace1(submenu_name_str, ANIMAL_NAME_LEN);
            mNpc_ClearBufSpace1(name_str, ANIMAL_NAME_LEN);
            mNpc_ClearBufSpace1(gobi_str, ANIMAL_CATCHPHRASE_LEN);

            if (password->npc_type == mMpswd_NPCTYPE_NORMAL) {
                mActor_name_t target_npc_id = NPC_START | password->npc_code;
                int villager_idx = mNpc_SearchAnimalinfo(Save_Get(animals), target_npc_id, ANIMAL_NUM_MAX);
                int islander_idx = mNpc_SearchAnimalinfo(&Save_Get(island).animal, target_npc_id, 1);

                if ((villager_idx != -1 || islander_idx != -1) &&
                    (mNpc_GetAnimalMemoryIdx(&Common_Get(now_private)->player_ID,
                                             Save_Get(animals[villager_idx]).memories, ANIMAL_MEMORY_NUM) != -1 ||
                     mNpc_GetAnimalMemoryIdx(&Common_Get(now_private)->player_ID, Save_Get(island).animal.memories,
                                             ANIMAL_MEMORY_NUM) != -1)) {
                    int looks = mNpc_GetLooks(target_npc_id);

                    if (mNpc_GetHit_cardE(password->hit_rate_index)) {
                        famicom_hit = TRUE;
                        mail_no = mNpc_CheckIslandAnimalTableNo(target_npc_id) == TRUE ? 0x3CA + looks : 0x3C4 + looks;
                        mNpc_GetNpcWorldNameTableNo(name_str, NPC_START | password->npc_code);
                        mNpc_GetNpcWorldNameTableNo(submenu_name_str, NPC_START | password->npc_code);
                        valid = TRUE;
                    }
                }

                if (famicom_hit == FALSE) {
                    mail_no = 0x2B2 + password->npc_code;
                    mNpc_GetNpcWorldNameTableNo(name_str, NPC_START | password->npc_code);
                    mNpc_GetNpcWorldNameTableNo(submenu_name_str, NPC_START | password->npc_code);
                    valid = TRUE;
                }

                mNPC_get_gobi_str_from_name(gobi_str, target_npc_id);
                mHandbill_Set_free_str(mHandbill_FREE_STR5, gobi_str, ANIMAL_CATCHPHRASE_LEN);
            } else {
                /* Special NPC */
                mActor_name_t npc_id;

                mail_no = 0x39E + password->npc_code;
                npc_id = mMpswd_get_sp_npc_num(password->npc_code);
                mNpc_GetActorWorldName(name_str, npc_id);
                mNpc_GetActorWorldName(submenu_name_str, npc_id);

                /* Leftover from JP, replace ちん (-san) honorific with spaces */
                if (submenu_name_str[4] == 0x0A && submenu_name_str[5] == 0xC3) {
                    submenu_name_str[4] = CHAR_SPACE;
                    submenu_name_str[5] = CHAR_SPACE;
                }

                valid = TRUE;
                special = TRUE;
            }

            if (famicom_hit == FALSE && mMpswd_check_present(password) == TRUE) {
                mActor_name_t item = password->item;

                if (item == RSV_NO) {
                    present = EMPTY_NO;
                } else {
                    present = item;
                }
            } else if (famicom_hit == TRUE) {
                int famicom_idx = RANDOM_F(8);

                present = mRmTp_FtrIdx2FtrItemNo(pswd_famicom_list[famicom_idx], mRmTp_DIRECT_SOUTH);
            }
        } else {
            /* Invalid password */
            mail_no = 0x3BE + anm_id->looks;
        }

        mHandbill_Set_free_str(mHandbill_FREE_STR0, pid->player_name, PLAYER_NAME_LEN);
        mHandbill_Set_free_str(mHandbill_FREE_STR1, name_str, ANIMAL_NAME_LEN);
        mHandbill_Set_free_str(mHandbill_FREE_STR2, password->str1, PLAYER_NAME_LEN);
        mHandbill_Set_free_str(mHandbill_FREE_STR3, password->str0, PLAYER_NAME_LEN);

        if (present != EMPTY_NO) {
            mNpc_ClearBufSpace1(name_str, mIN_ITEM_NAME_LEN);
            mIN_copy_name_str(name_str, present);
            mHandbill_Set_free_str(mHandbill_FREE_STR4, name_str, mIN_ITEM_NAME_LEN);
        }

        /* Why is free string 6 the same as free string 1? */
        mNpc_ClearBufSpace1(name_str, ANIMAL_NAME_LEN);
        mNpc_GetNpcWorldNameAnm(name_str, anm_id);
        mHandbill_Set_free_str(mHandbill_FREE_STR6, name_str, ANIMAL_NAME_LEN);

        mNpc_LoadMailDataCommon2(hp_mail, pid, anm_id, present, mNpc_GetPaperType(), mail_no);

        if (valid == TRUE) {
            // Overwrite the sender name with the name of the password's embedded villager name
            bcopy(submenu_name_str, hp_mail->header.sender.personalID.player_name, PLAYER_NAME_LEN);
            bcopy(pid->player_name, hp_mail->header.recipient.personalID.player_name, PLAYER_NAME_LEN);

            if (special == TRUE) {
                hp_mail->content.mail_type = mMl_TYPE_SPNPC_PASSWORD;
            }
        }

        res = mPO_receipt_proc(hp_mail, mPO_SENDTYPE_MAIL);
    }

    return res;
}

static int mNpc_SendHPMailNum_NG(PersonalID_c* pid, AnmPersonalID_c* anm_id) {
    static u8 name_str[mIN_ITEM_NAME_LEN];

    Mail_c* hp_mail = &l_npc_hp_mail;
    int mail_no;
    int res = FALSE;

    if (anm_id != NULL && mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE) {
        mMl_clear_mail(hp_mail);
        mail_no = 0x3BE + anm_id->looks;
        mHandbill_Set_free_str(mHandbill_FREE_STR0, pid->player_name, PLAYER_NAME_LEN);
        mNpc_ClearBufSpace1(name_str, ANIMAL_NAME_LEN);
        mNpc_GetNpcWorldNameAnm(name_str, anm_id);
        mHandbill_Set_free_str(mHandbill_FREE_STR6, name_str, ANIMAL_NAME_LEN);
        mNpc_LoadMailDataCommon2(hp_mail, pid, anm_id, EMPTY_NO, mNpc_GetPaperType(), mail_no);
        res = mPO_receipt_proc(hp_mail, mPO_SENDTYPE_MAIL);
    }

    return res;
}

static int mNpc_SendHPMailNum_cardE_mini_user_password_common(PersonalID_c* pid, AnmPersonalID_c* anm_id) {
    static u8 name_str[ANIMAL_NAME_LEN];

    Mail_c* hp_mail = &l_npc_hp_mail;
    int looks = anm_id->looks;
    int res = FALSE;

    if (mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE && looks < mNpc_LOOKS_NUM) {
        mMl_clear_mail(hp_mail);
        mNpc_ClearBufSpace1(name_str, ANIMAL_NAME_LEN);
        mNpc_GetNpcWorldNameAnm(name_str, anm_id);
        mHandbill_Set_free_str(mHandbill_FREE_STR6, name_str, ANIMAL_NAME_LEN);
        mNpc_LoadMailDataCommon2(hp_mail, pid, anm_id, EMPTY_NO, mNpc_GetPaperType(), 0x3D0 + looks);
        res = mPO_receipt_proc(hp_mail, mPO_SENDTYPE_MAIL);
    }

    return res;
}

static int mNpc_SendHPMailNum_user_password(PersonalID_c* pid, AnmPersonalID_c* anm_id, mMpswd_password_c* password) {
    if (mMpswd_password_zuru_check(password) == FALSE && mMpswd_check_present(password) == TRUE &&
        mMpswd_check_name(password) == TRUE) {
        return mNpc_SendHPMailNum_cardE_mini_user_password_common(pid, anm_id);
    }

    return mNpc_SendHPMailNum_NG(pid, anm_id);
}

static int mNpc_SendHPMailNum_cardE_mini(PersonalID_c* pid, AnmPersonalID_c* anm_id, mMpswd_password_c* password) {
    if (mMpswd_password_zuru_check(password) == FALSE) {
        return mNpc_SendHPMailNum_cardE_mini_user_password_common(pid, anm_id);
    }

    return mNpc_SendHPMailNum_NG(pid, anm_id);
}

static int mNpc_SendHPMailNum_magazine(PersonalID_c* pid, AnmPersonalID_c* anm_id, mMpswd_password_c* password) {
    static u8 name_str[mIN_ITEM_NAME_LEN];

    Mail_c* hp_mail = &l_npc_hp_mail;
    int mail_no;
    mActor_name_t present = EMPTY_NO;
    int res = FALSE;

    if (mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE) {
        mMl_clear_mail(hp_mail);

        if (mNpc_CheckHit_Rate(password->hit_rate_index, 3) == TRUE && // hitrate index is valid
            mMpswd_password_zuru_check(password) == FALSE &&           // checksum is valid
            mMpswd_check_present(password) == TRUE                     // present is valid
        ) {
            /* Valid password */
            if (mNpc_GetHit(password->hit_rate_index) == TRUE) {
                /* Player "won" */
                mail_no = 0x2A0 + anm_id->looks;

                if (password->item != RSV_NO) {
                    present = password->item;
                }
            } else {
                /* Player did not "win" */
                mail_no = 0x2A6 + anm_id->looks;
            }
        } else {
            /* Invalid password */
            mail_no = 0x2AC + anm_id->looks;
        }

        mHandbill_Set_free_str(mHandbill_FREE_STR0, pid->player_name, PLAYER_NAME_LEN);
        mNpc_ClearBufSpace1(name_str, ANIMAL_NAME_LEN);
        mNpc_GetNpcWorldNameAnm(name_str, anm_id);
        mHandbill_Set_free_str(mHandbill_FREE_STR1, name_str, ANIMAL_NAME_LEN);
        mHandbill_Set_free_str(mHandbill_FREE_STR2, password->str1, PLAYER_NAME_LEN);
        mHandbill_Set_free_str(mHandbill_FREE_STR3, password->str0, PLAYER_NAME_LEN);

        if (present != EMPTY_NO) {
            mNpc_ClearBufSpace1(name_str, mIN_ITEM_NAME_LEN);
            mIN_copy_name_str(name_str, present);
            mHandbill_Set_free_str(mHandbill_FREE_STR4, name_str, mIN_ITEM_NAME_LEN);
        }

        /* Why is free string 6 the same as free string 1? */
        mNpc_ClearBufSpace1(name_str, ANIMAL_NAME_LEN);
        mNpc_GetNpcWorldNameAnm(name_str, anm_id);
        mHandbill_Set_free_str(mHandbill_FREE_STR6, name_str, ANIMAL_NAME_LEN);

        mNpc_LoadMailDataCommon2(hp_mail, pid, anm_id, present, mNpc_GetPaperType(), mail_no);
        res = mPO_receipt_proc(hp_mail, mPO_SENDTYPE_MAIL);
    }

    return res;
}

typedef int (*mNpc_HPMAIL_SEND_PROC)(PersonalID_c*, AnmPersonalID_c*, mMpswd_password_c*);

static int mNpc_SendHPMail_analysis(PersonalID_c* pid, AnmPersonalID_c* anm_id, AnmHPMail_c* hp_mail) {
    static mNpc_HPMAIL_SEND_PROC send_proc[mMpswd_CODETYPE_NUM] = {
        &mNpc_SendHPMailNum_famicom,  &mNpc_SendHPMailNum_popular,       &mNpc_SendHPMailNum_cardE,
        &mNpc_SendHPMailNum_magazine, &mNpc_SendHPMailNum_user_password, &mNpc_SendHPMailNum_cardE_mini
    };

    mMpswd_password_c password;

    mMpswd_password(hp_mail->password, &password);

    if (password.type < mMpswd_CODETYPE_NUM) {
        return (*send_proc[password.type])(pid, anm_id, &password);
    }

    return mNpc_SendHPMailNum_NG(pid, anm_id);
}

extern void mNpc_SendHPMail() {
    Private_c* priv = Save_Get(private_data);
    Private_c* priv_p;
    Animal_c* animal = Save_Get(animals);
    AnmHPMail_c* hp_mail;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int i;
    int j;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            hp_mail = animal->hp_mail;
            priv_p = priv;

            for (j = 0; j < ANIMAL_HP_MAIL_NUM; j++) {
                if (hp_mail->receive_time.year != 0 && hp_mail->receive_time.day != 0 &&
                    mPr_NullCheckPersonalID(&priv_p->player_ID) == FALSE) {
                    int days;

                    if (lbRTC_IsOverTime(&hp_mail->receive_time, rtc_time) == lbRTC_OVER) {
                        days = lbRTC_GetIntervalDays(&hp_mail->receive_time, rtc_time);
                    } else {
                        days = lbRTC_GetIntervalDays(rtc_time, &hp_mail->receive_time);
                    }

                    if (days >= 1 && mNpc_SendHPMail_analysis(&priv_p->player_ID, &animal->id, hp_mail) == TRUE) {
                        mNpc_ClearHPMail(hp_mail, 1);
                    }
                }

                priv_p++;
                hp_mail++;
            }
        }

        animal++;
    }
}

extern void mNpc_PrintRemoveInfo(gfxprint_t* gfxprint) {
    Animal_c* remove_anm = NULL;
    Animal_c* in_anm = mNpc_GetInAnimalP();
    u8 remove_idx = Save_Get(remove_animal_idx);

    gfxprint_color(gfxprint, 200, 150, 50, 255);
    gfxprint_locate8x8(gfxprint, 3, 10);

    if (remove_idx < ANIMAL_NUM_MAX) {
        remove_anm = Save_GetPointer(animals[remove_idx]);
    }

    if (remove_anm != NULL) {
        if (in_anm != NULL) {
            gfxprint_printf(gfxprint, "%4x %3d %3d", remove_idx, remove_anm->id.name_id, in_anm->id.name_id);
        } else {
            gfxprint_printf(gfxprint, "%4x %3d ---", remove_idx, remove_anm->id.name_id);
        }
    } else if (in_anm != NULL) {
        gfxprint_printf(gfxprint, "%4x --- %3d", remove_idx, in_anm->id.name_id);
    } else {
        gfxprint_printf(gfxprint, "%4x --- ---", remove_idx);
    }
}

static int l_mnpc_display = 0;

typedef struct npc_add_debug_s {
    int add_switch;
    u16 memory;
    u8 count;
    u8 add_bit;
    u8 edit_bit;
    int mtype;
    int disp_add;
} mNpc_Add_Debug_c;

static mNpc_Add_Debug_c l_mnpc_addd;

/* @unused mNpc_set_switch 1.2.5 size: 0x14 */
/* @unused mNpc_clear_addd 1.2.5 size: 0x44 */
/* @unused mNpc_set_addd 1.2.5 size: 0x0C */

/* @unused @fabricated */
extern void mNpc_set_addd_bit(int bit) {
    l_mnpc_addd.add_bit |= (1 << bit);
}

/* @unused */
extern void mNpc_set_addd_edit_bit(int bit) {
    l_mnpc_addd.edit_bit |= (1 << bit);
}

/* @unused */
extern void mNpc_set_addd_edit_info(int mtype, int disp_add) {
    l_mnpc_addd.mtype = mtype;
    l_mnpc_addd.disp_add = disp_add;
}

/* @unused mNpc_set_addd_memory 1.2.5 size: 0x34 */
/* @unused mNpc_set_addd_count 1.2.5 size: 0x10 */

static void mNpc_PrintFriendship_fdebug_1(gfxprint_t* gfxprint) {
    int add_switch = l_mnpc_addd.add_switch;
    int i;

    gfxprint_color(gfxprint, 250, 100, 170, 255);
    gfxprint_locate8x8(gfxprint, 3, 18);

    if (add_switch == 0) {
        gfxprint_printf(gfxprint, "----------------------- %d", l_mnpc_addd.add_switch);
    } else if (add_switch == 1) {
        gfxprint_printf(gfxprint, "*********************** %d", l_mnpc_addd.add_switch);
    } else if (add_switch == 2) {
        gfxprint_printf(gfxprint, ">>>>>>>>>>>>>>>>>>>>>>> %d", l_mnpc_addd.add_switch);
    } else {
        gfxprint_printf(gfxprint, "%2d    ", l_mnpc_addd.count);
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            gfxprint_printf(gfxprint, "%1d", (l_mnpc_addd.memory >> i) & 1);
        }

        gfxprint_locate8x8(gfxprint, 3, 19);
        gfxprint_printf(gfxprint, "add bit ");
        for (i = 0; i < 8; i++) {
            gfxprint_printf(gfxprint, "%1d", (l_mnpc_addd.add_bit >> i) & 1);
        }

        gfxprint_printf(gfxprint, "  edit bit ");
        for (i = 0; i < 8; i++) {
            gfxprint_printf(gfxprint, "%1d", (l_mnpc_addd.edit_bit >> i) & 1);
        }

        gfxprint_locate8x8(gfxprint, 3, 20);
        gfxprint_printf(gfxprint, "mtype %d  disp_add 0x%x", l_mnpc_addd.mtype, l_mnpc_addd.disp_add);
    }
}

static int l_mnpc_animal_idx = -1;

extern void mNpc_SetTalkAnimalIdx_fdebug(AnmPersonalID_c* anm_id) {
    if (anm_id != NULL) {
        l_mnpc_animal_idx = mNpc_SearchAnimalPersonalID(anm_id);
    }
}

static void mNpc_PrintFriendship_fdebug_0(gfxprint_t* gfxprint) {
    Anmmem_c* memory;
    Private_c* priv;
    int x = 3;
    int y = 19;
    int i;

    if (l_mnpc_animal_idx >= 0 && l_mnpc_animal_idx < ANIMAL_NUM_MAX) {
        memory = Save_Get(animals[l_mnpc_animal_idx]).memories;

        if (memory != NULL) {
            gfxprint_color(gfxprint, 250, 100, 170, 255);
            gfxprint_locate8x8(gfxprint, 3, 18);
            priv = Common_Get(now_private);

            if (priv != NULL) {
                gfxprint_printf(gfxprint, "%4x ", priv->player_ID.player_id);
            } else {
                gfxprint_printf(gfxprint, "**** ");
            }

            gfxprint_color(gfxprint, 50, 150, 50, 255);

            for (i = 0; i < ANIMAL_MEMORY_NUM; i++) {
                if (i == 4) {
                    y++;
                    x = 3;
                }

                gfxprint_locate8x8(gfxprint, x, y);
                if (mNpc_CheckFreeAnimalMemory(memory) == FALSE) {
                    gfxprint_printf(gfxprint, "%4x %3d ", memory->memory_player_id.player_id, memory->friendship);
                } else {
                    gfxprint_printf(gfxprint, "**** *** ");
                }

                memory++;
                x += 9;
            }
        }
    }
}

typedef void (*mNpc_PRINT_FRIENDSHIP_PROC)(gfxprint_t*);

extern void mNpc_PrintFriendship_fdebug(gfxprint_t* gfxprint) {
    static mNpc_PRINT_FRIENDSHIP_PROC print_proc[2] = { &mNpc_PrintFriendship_fdebug_0,
                                                        &mNpc_PrintFriendship_fdebug_1 };

    (*print_proc[l_mnpc_display & 1])(gfxprint);
}
