#include "m_notice.h"

#include "lb_rtc.h"
#include "lb_reki.h"
#include "m_time.h"
#include "m_event.h"
#include "m_mail.h"
#include "m_font.h"
#include "m_string.h"
#include "m_handbill.h"
#include "m_field_info.h"
#include "m_lib.h"
#include "m_land.h"
#include "m_item_name.h"
#include "m_npc.h"
#include "m_name_table.h"
#include "m_shop.h"
#include "m_fishrecord.h"
#include "m_event.h"
#include "m_common_data.h"

#define lbRTC_TIME_TO_U32(t) ((u32)(((t)->year << 16) + ((t)->month << 8) + (t)->day))

#define mNtc_TO_MONTHDAY(mo, day) ((u16)((((mo) & 0xFF) << 8) | ((day) & 0xFF)))
#define mNtc_GET_MONTH(monthday) (((monthday) >> 8) & 0xFF)
#define mNtc_GET_DAY(monthday) ((monthday) & 0xFF)

#define mNTC_UNUSED_DATE mNtc_TO_MONTHDAY(0xFF, 0xFF)

#define mNtc_FISHING_DAY_YEAR 0xFFFF
#define mNtc_FISHING_DAY_NUM 0xFF

#define mNtc_MIN_DAYS_BETWEEN_TREASURE 3
#define mNtc_TREASURE_CHANCE 0.4f /* 40% chance when possible */

#define mNtc_NWRITE_NUM 5

#define mNtc_DATA_LIST_NUM 43

#define mNtc_UNUSED_MONTH 0xFF
#define mNtc_UNUSED_DAY 0xFF

/* sizeof(mNtc_date_c) == 2 */
typedef struct notice_date_s {
    /* 0x00 */ lbRTC_month_t month;
    /* 0x01 */ lbRTC_day_t day;
} mNtc_date_c;

/* sizeof(mNtc_date_data_c) == 4 */
typedef struct notice_date_data_s {
    /* 0x00 */ u16 id;
    /* 0x02 */ u16 date;
} mNtc_date_data_c;

static mNtc_date_data_c mNtc_auto_nwrite_data[mNtc_DATA_LIST_NUM];

static void mNtc_copy_data_list() {
    static mNtc_date_data_c auto_nwrite_date_data[mNtc_DATA_LIST_NUM] = {
        { 0x00, mNtc_TO_MONTHDAY(lbRTC_JANUARY, 1) },    /* Nook's New Year's post */
        { 0x01, mNtc_TO_MONTHDAY(lbRTC_JANUARY, 15) },   /* Snow weather report */
        { 0x02, mNtc_TO_MONTHDAY(lbRTC_JANUARY, 25) },   /* Groundhog day notice */
        { 0x03, mNtc_TO_MONTHDAY(lbRTC_FEBRUARY, 1) },   /* Valentine's Day notice */
        { 0x04, mNtc_TO_MONTHDAY(lbRTC_FEBRUARY, 15) },  /* Pete's Valentine's Day complaint */
        { 0x05, mNtc_TO_MONTHDAY(lbRTC_MARCH, 15) },     /* Cherry Blossom Festival notice */
        { 0x06, mNtc_TO_MONTHDAY(lbRTC_MARCH, 11) },     /* Spring Sports Fair notice */
        { 0x07, mNtc_TO_MONTHDAY(lbRTC_MARCH, 16) },     /* Spring Sports Fair vernal equinox notice */
        { 0x08, mNtc_TO_MONTHDAY(lbRTC_MARCH, 20) },     /* Spring Sports Fair schedule */
        { 0x09, mNtc_TO_MONTHDAY(lbRTC_APRIL, 3) },      /* Cherry Blossom Festival reminder notice */
        { 0x0A, mNtc_TO_MONTHDAY(lbRTC_APRIL, 21) },     /* Spring weather notice */
        { 0x0B, mNtc_TO_MONTHDAY(lbRTC_MAY, 6) },        /* June weather notice */
        { 0x0C, mNtc_TO_MONTHDAY(lbRTC_MAY, 20) },       /* Summer fishing tourney notice */
        { 0x0D, mNtc_TO_MONTHDAY(lbRTC_JUNE, 8) },       /* Chip's 1st summer fishing tourney post */
        { 0x0E, mNtc_TO_MONTHDAY(lbRTC_JUNE, 23) },      /* Chip's final summer fishing tourney post */
        { 0x0F, mNtc_TO_MONTHDAY(lbRTC_JUNE, 25) },      /* Fireworks Festival notice */
        { 0x10, mNtc_TO_MONTHDAY(lbRTC_JULY, 1) },       /* July weather notice */
        { 0x11, mNtc_TO_MONTHDAY(lbRTC_JULY, 5) },       /* Phyllis? Fireworks Festival complaint */
        { 0x12, mNtc_TO_MONTHDAY(lbRTC_JULY, 15) },      /* Morning aerobics notice */
        { 0x13, mNtc_TO_MONTHDAY(lbRTC_JULY, 25) },      /* Copper morning aerobics post */
        { 0x14, mNtc_TO_MONTHDAY(lbRTC_AUGUST, 1) },     /* Meteor Shower notice */
        { 0x15, mNtc_TO_MONTHDAY(lbRTC_AUGUST, 30) },    /* Copper morning aerobics final day notice */
        { 0x16, mNtc_TO_MONTHDAY(lbRTC_SEPTEMBER, 1) },  /* Moon Viewing notice */
        { 0x17, mNtc_TO_MONTHDAY(lbRTC_SEPTEMBER, 15) }, /* September weather report */
        { 0x18, mNtc_TO_MONTHDAY(lbRTC_SEPTEMBER, 13) }, /* Pete's Fall Sports Fair post */
        { 0x19, mNtc_TO_MONTHDAY(lbRTC_SEPTEMBER, 18) }, /* Fall Sports Fair notice */
        { 0x1A, mNtc_TO_MONTHDAY(lbRTC_SEPTEMBER, 22) }, /* Fall Sports Fair schedule */
        { 0x1B, mNtc_TO_MONTHDAY(lbRTC_OCTOBER, 10) },   /* Mushrooming season notice */
        { 0x1C, mNtc_TO_MONTHDAY(lbRTC_OCTOBER, 16) },   /* Nook's Halloween candy post */
        { 0x1D, mNtc_TO_MONTHDAY(lbRTC_OCTOBER, 20) },   /* Halloween notice */
        { 0x1E, mNtc_TO_MONTHDAY(lbRTC_OCTOBER, 25) },   /* Fall fishing tourney notice */
        { 0x1F, mNtc_TO_MONTHDAY(lbRTC_NOVEMBER, 8) },   /* Chip's 1st fall fishing tourney post */
        { 0x20, mNtc_TO_MONTHDAY(lbRTC_NOVEMBER, 10) },  /* Harvest Festival notice */
        { 0x21, mNtc_TO_MONTHDAY(lbRTC_NOVEMBER, 12) },  /* November weather report */
        { 0x22, mNtc_TO_MONTHDAY(lbRTC_NOVEMBER, 23) },  /* Chip's final fall fishing tourney post */
        { 0x23, mNtc_TO_MONTHDAY(lbRTC_DECEMBER, 9) },   /* Winter storm warning */
        { 0x24, mNtc_TO_MONTHDAY(lbRTC_DECEMBER, 20) },  /* Jingle's holiday notice */
        { 0x25, mNtc_TO_MONTHDAY(lbRTC_DECEMBER, 25) },  /* New Year's Eve countdown notice */
        { 0x26, mNtc_TO_MONTHDAY(lbRTC_DECEMBER, 28) },  /* New Year's Day event notice */
        { 0x27, mNTC_UNUSED_DATE },                      /* Pete check mailbox info? */
        { 0x28, mNTC_UNUSED_DATE },                      /* Anti-litter notice? */
        { 0x29, mNtc_TO_MONTHDAY(lbRTC_MARCH, 31) },     /* Day light savings begin notice */
        { 0x2A, mNtc_TO_MONTHDAY(lbRTC_OCTOBER, 31) }    /* Day light savings end notice */
    };

    mem_copy((u8*)mNtc_auto_nwrite_data, (u8*)auto_nwrite_date_data, mNtc_DATA_LIST_NUM * sizeof(mNtc_date_data_c));
}

static void mNtc_operate_data_list() {
    mNtc_date_data_c* data_p;
    int day;

    /* update Spring Sports Fair dates */
    day = lbRk_VernalEquinoxDay(Common_Get(time.rtc_time.year));
    /* month = march, day = vernal equinox day - 10 */
    data_p = mNtc_auto_nwrite_data + 6;
    data_p->date = day + 0x2F6;
    /* month = march, day = vernal equinox day - 5 */
    data_p = mNtc_auto_nwrite_data + 7;
    data_p->date = day + 0x2FB;
    /* month = march, day = vernal equinox day - 1 */
    data_p = mNtc_auto_nwrite_data + 8;
    data_p->date = day + 0x2FF;

    /* update Fall Sports Fair dates */
    day = lbRk_AutumnalEquinoxDay(Common_Get(time.rtc_time.year));
    /* month = september, day = autumnal equinox day - 10 */
    data_p = mNtc_auto_nwrite_data + 0x18;
    data_p->date = day + 0x8F6;
    /* month = september, day = autumnal equinox day - 5 */
    data_p = mNtc_auto_nwrite_data + 0x19;
    data_p->date = day + 0x8FB;
    /* month = september, day = autumnal equinox day - 1 */
    data_p = mNtc_auto_nwrite_data + 0x1A;
    data_p->date = day + 0x8FF;

    /* update daylight savings time dates */
    mNtc_auto_nwrite_data[0x29].date =
        mEv_weekday2day(lbRTC_MARCH, mEv_WEEKTYPE_LAST, lbRTC_SUNDAY) + 0x300; /* month = march, day = last sunday */
    mNtc_auto_nwrite_data[0x2A].date = mEv_weekday2day(lbRTC_OCTOBER, mEv_WEEKTYPE_LAST, lbRTC_SUNDAY) +
                                       0x9F9; /* month = october, day = second to last sunday */
}

static void mNtc_sort_data_list() {
    mNtc_date_data_c replace_data;
    int replace_idx;
    int i, j;

    /* sort from earliest to latest dates */
    for (i = 0; i < mNtc_DATA_LIST_NUM; i++) {
        replace_data = mNtc_auto_nwrite_data[i];
        replace_idx = i;

        /* search through all entries ahead and find the next closest date */
        for (j = i + 1; j < mNtc_DATA_LIST_NUM; j++) {
            if (mNtc_auto_nwrite_data[j].date < replace_data.date) {
                replace_data = mNtc_auto_nwrite_data[j];
                replace_idx = j;
            }
        }

        /* swap the entries */
        mNtc_auto_nwrite_data[replace_idx] = mNtc_auto_nwrite_data[i];
        mNtc_auto_nwrite_data[i] = replace_data;
    }
}

static void mNtc_make_auto_nwrite_data_list() {
    mNtc_copy_data_list();    /* copy the base list */
    mNtc_operate_data_list(); /* update dynamic dates */
    mNtc_sort_data_list();    /* sort entries by date */
}

static int mNtc_get_auto_nwrite_data_last_idx() {
    int i;
    int res = mNtc_DATA_LIST_NUM - 1;

    for (i = mNtc_DATA_LIST_NUM - 1; i >= 0; i--) {
        if (mNtc_auto_nwrite_data[i].date != 0xFFFF) {
            res = i;
            break;
        }
    }

    return res;
}

static void mNtc_ClearPage(mNtc_board_post_c* page, int count) {
    for (count; count != 0; count--) {
        page->post_time = mTM_rtcTime_clear_code;
        mem_clear(page->message, MAIL_BODY_LEN, CHAR_SPACE);
        page++;
    }
}

extern void mNtc_SetInitData() {
    mNtc_board_post_c* post;
    lbRTC_time_c rtc_time;
    int header_back_pos;
    int handbill_no_tbl[4] = { 0x1E, 0x1F, 0x20, 0x21 };
    u8 header[mHandbill_HEADER_LEN];
    u8 footer[mHandbill_FOOTER_LEN];
    int i;

    post = Save_Get(noticeboard);
    // handbill_no_tbl[0] = 0x1E; /* noticeboard free to use post */
    // handbill_no_tbl[1] = 0x1F; /* Nook's HRA recruitment post */
    // handbill_no_tbl[2] = 0x20; /* HRA points guide post */
    // handbill_no_tbl[3] = 0x21; /* noticeboard usage post */

    rtc_time = Common_Get(time.rtc_time);

    for (i = 0; i < 4; i++) {
        post->post_time = rtc_time;
        mHandbill_Load_HandbillFromRom(header, &header_back_pos, footer, post->message, handbill_no_tbl[i]);
        post++;
    }

    mNtc_ClearPage(post, mNtc_BOARD_POST_COUNT - 4);
}

extern int mNtc_notice_write_num() {
    mNtc_board_post_c* post;
    int i;

    post = Save_Get(noticeboard);
    for (i = 0; i < mNtc_BOARD_POST_COUNT; i++) {
        if (lbRTC_IsEqualTime(&post->post_time, &mTM_rtcTime_clear_code, lbRTC_CHECK_ALL) == TRUE) {
            break;
        }
        post++;
    }

    return i;
}

extern void mNtc_notice_write(mNtc_board_post_c* new_post) {
    int write_num = mNtc_notice_write_num();
    if (write_num == mNtc_BOARD_POST_COUNT) {
        mNtc_board_post_c* post = Save_Get(noticeboard);
        int i;

        /* delete first post and move all others down one */
        for (i = 0; i < mNtc_BOARD_POST_COUNT - 1; i++) {
            mem_copy((u8*)post, (u8*)(post + 1), sizeof(mNtc_board_post_c));
            post++;
        }

        /* copy new post */
        mem_copy((u8*)post, (u8*)new_post, sizeof(mNtc_board_post_c));
    } else {
        /* space available, write to lowest unused slot */
        mem_copy((u8*)(Save_Get(noticeboard) + write_num), (u8*)new_post, sizeof(mNtc_board_post_c));
    }
}

static int mNtc_set_landname_string(u8* buf) {
    mem_copy(buf, Save_Get(land_info.name), LAND_NAME_SIZE);
    return mMl_strlen(Save_Get(land_info.name), LAND_NAME_SIZE, CHAR_SPACE);
}

static void mNtc_set_treasure_string(AnmPersonalID_c* sender_id, mActor_name_t item_no, int block_x, int block_z) {
    static u8 choume_str[BLOCK_X_NUM] = "QABCDEF";

    int land_name_len;
    u8 b_str;
    u8 land_name[LAND_NAME_SIZE];
    u8 anm_name[ANIMAL_NAME_LEN];
    u8 item_name[mIN_ITEM_NAME_LEN];

    mNpc_GetNpcWorldNameAnm(anm_name, sender_id);
    mHandbill_Set_free_str(1, anm_name, ANIMAL_NAME_LEN);
    mIN_copy_name_str(item_name, item_no);
    mHandbill_Set_free_str_art(2, item_name, mIN_ITEM_NAME_LEN, mIN_get_item_article(item_no));

    b_str = choume_str[block_z];
    mHandbill_Set_free_str(3, &b_str, 1); /* z-acre friendly name (A-F) */

    b_str = mFI_COL_TO_CHARSTR(block_x);
    mHandbill_Set_free_str(4, &b_str, 1); /* x-acre friendly name (1-5) */

    land_name_len = mNtc_set_landname_string(land_name);
    mHandbill_Set_free_str(5, land_name, land_name_len);
}

// TODO: deviation implies fakematch
#if VERSION != VER_GAFE01_00
static void mNtc_check_treasure() {
    lbRTC_time_c* treasure_buried_time;
    lbRTC_time_c* treasure_checked_time;
    Animal_c* animal;
    mLd_land_info_c* land_info;
    u32 comp_time_rtc;
    u32 comp_time_buried;
    lbRTC_time_c rtc_time;
    int valid_animal_ids[ANIMAL_NUM_MAX];
    int* valid_id_p;
    Animal_c* selected_animal;
    int valid_animal_num;
    int i;
    u8 header[mHandbill_FOOTER_LEN];
    u8 footer[mHandbill_FOOTER_LEN];
    int mem;
    int interval_days;
    int header_back_pos;
    mNtc_board_post_c post;
    mActor_name_t item;
    int b_x;
    int b_z;
    f32 rng;
    int list_type;

    treasure_buried_time = Save_GetPointer(treasure_buried_time);
    treasure_checked_time = Save_GetPointer(treasure_checked_time);
    animal = Save_Get(animals);
    land_info = Save_GetPointer(land_info);
    valid_animal_num = 0;
    rtc_time = Common_Get(time.rtc_time);

    if (rtc_time.hour >= mTM_FIELD_RENEW_HOUR) {
        comp_time_rtc = lbRTC_TIME_TO_U32(&rtc_time);
        comp_time_buried = lbRTC_TIME_TO_U32(treasure_buried_time);
        if (comp_time_rtc > comp_time_buried) {
            interval_days = lbRTC_GetIntervalDays(treasure_buried_time, &rtc_time);
        } else if (comp_time_rtc < comp_time_buried) {
            interval_days = lbRTC_GetIntervalDays(&rtc_time, treasure_buried_time);
        } else {
            interval_days = 0;
        }

        if (lbRTC_IsEqualTime(treasure_buried_time, &mTM_rtcTime_clear_code, lbRTC_CHECK_ALL) ||
            interval_days >= mNtc_MIN_DAYS_BETWEEN_TREASURE) {
            if (lbRTC_IsEqualTime(treasure_checked_time, &mTM_rtcTime_clear_code, lbRTC_CHECK_ALL) ||
                treasure_checked_time->year != rtc_time.year || treasure_checked_time->month != rtc_time.month ||
                treasure_checked_time->day != rtc_time.day) {
                for (i = 0, valid_id_p = valid_animal_ids; i < ANIMAL_NUM_MAX; i++, animal++) {
                    if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
                        for (mem = 0; mem < ANIMAL_MEMORY_NUM; mem++) {
                            if (animal->memories[mem].memory_player_id.land_id == land_info->id &&
                                mLd_CheckCmpLandName(animal->memories[mem].memory_player_id.land_name,
                                                     land_info->name)) {
                                if (valid_animal_num == ANIMAL_NUM_MAX) {
                                    return;
                                }

                                valid_animal_num++;
                                *valid_id_p++ = i;
                                break;
                            }
                        }
                    }
                }

                if (valid_animal_num != 0 && fqrand() < mNtc_TREASURE_CHANCE) {
                    b_x = 0;
                    b_z = 0;

                    /* 1/3rd chance of pitfall, 2/3rds chance of rare furniture */
                    rng = fqrand();
                    if (rng < (1.0f / 3.0f)) {
                        item = ITM_PITFALL;
                    } else {
                        list_type = rng < (2.0f / 3.0f)
                                        ? mSP_LISTTYPE_LOTTERY
                                        : mSP_LISTTYPE_EVENT; /* 50/50 to roll redd or lottery furniture*/
                        mSP_SelectRandomItem_New(NULL, &item, 1, NULL, 0, mSP_KIND_FURNITURE, list_type, FALSE);
                    }

                    if (mFI_SetTreasure(&b_x, &b_z, item)) {
                        selected_animal =
                            Save_GetPointer(animals[valid_animal_ids[RANDOM(valid_animal_num) % valid_animal_num]]);
                        mNtc_set_treasure_string(&selected_animal->id, item, b_x, b_z);
                        lbRTC_TimeCopy(&post.post_time, &rtc_time);
                        mHandbill_Load_HandbillFromRom(header, &header_back_pos, footer, post.message,
                                                       0x1F0 + selected_animal->id.looks * 3 + (RANDOM(3) % 3));
                        mNtc_notice_write(&post);
                        lbRTC_TimeCopy(treasure_buried_time, &rtc_time);
                    }
                }
            }
        }
    }
}
#else
static void mNtc_check_treasure() {
    lbRTC_time_c* treasure_buried_time;
    lbRTC_time_c* treasure_checked_time;
    Animal_c* animal;
    mLd_land_info_c* land_info;
    u32 comp_time_rtc;
    u32 comp_time_buried;
    lbRTC_time_c rtc_time;
    int valid_animal_ids[ANIMAL_NUM_MAX];
    Animal_c* selected_animal;
    int valid_animal_num;
    int i;
    u8 header[mHandbill_FOOTER_LEN];
    u8 footer[mHandbill_FOOTER_LEN];
    int mem;
    int interval_days;
    int header_back_pos;
    mNtc_board_post_c post;
    mActor_name_t item;
    int b_x;
    int b_z;
    f32 rng;
    int list_type;

    treasure_buried_time = Save_GetPointer(treasure_buried_time);
    treasure_checked_time = Save_GetPointer(treasure_checked_time);
    animal = Save_Get(animals);
    land_info = Save_GetPointer(land_info);
    valid_animal_num = 0;
    rtc_time = Common_Get(time.rtc_time);

    if (rtc_time.hour >= mTM_FIELD_RENEW_HOUR) {
        comp_time_rtc = lbRTC_TIME_TO_U32(&rtc_time);
        comp_time_buried = lbRTC_TIME_TO_U32(treasure_buried_time);
        if (comp_time_rtc > comp_time_buried) {
            interval_days = lbRTC_GetIntervalDays(treasure_buried_time, &rtc_time);
        } else if (comp_time_rtc < comp_time_buried) {
            interval_days = lbRTC_GetIntervalDays(&rtc_time, treasure_buried_time);
        } else {
            interval_days = 0;
        }

        if (lbRTC_IsEqualTime(treasure_buried_time, &mTM_rtcTime_clear_code, lbRTC_CHECK_ALL) ||
            interval_days >= mNtc_MIN_DAYS_BETWEEN_TREASURE) {
            if (lbRTC_IsEqualTime(treasure_checked_time, &mTM_rtcTime_clear_code, lbRTC_CHECK_ALL) ||
                treasure_checked_time->year != rtc_time.year || treasure_checked_time->month != rtc_time.month ||
                treasure_checked_time->day != rtc_time.day) {
                for (i = 0; i < ANIMAL_NUM_MAX; i++, animal++) {
                    if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
                        for (mem = 0; mem < ANIMAL_MEMORY_NUM; mem++) {
                            if (animal->memories[mem].memory_player_id.land_id == land_info->id &&
                                mLd_CheckCmpLandName(animal->memories[mem].memory_player_id.land_name,
                                                     land_info->name)) {
                                if (valid_animal_num == ANIMAL_NUM_MAX) {
                                    return;
                                }

                                valid_animal_ids[valid_animal_num++] = i;
                                break;
                            }
                        }
                    }
                }

                if (valid_animal_num != 0 && fqrand() < mNtc_TREASURE_CHANCE) {
                    b_x = 0;
                    b_z = 0;

                    /* 1/3rd chance of pitfall, 2/3rds chance of rare furniture */
                    rng = fqrand();
                    if (rng < (1.0f / 3.0f)) {
                        item = ITM_PITFALL;
                    } else {
                        list_type = rng < (2.0f / 3.0f)
                                        ? mSP_LISTTYPE_LOTTERY
                                        : mSP_LISTTYPE_EVENT; /* 50/50 to roll redd or lottery furniture*/
                        mSP_SelectRandomItem_New(NULL, &item, 1, NULL, 0, mSP_KIND_FURNITURE, list_type, FALSE);
                    }

                    if (mFI_SetTreasure(&b_x, &b_z, item)) {
                        selected_animal =
                            Save_GetPointer(animals[valid_animal_ids[RANDOM(valid_animal_num) % valid_animal_num]]);
                        mNtc_set_treasure_string(&selected_animal->id, item, b_x, b_z);
                        lbRTC_TimeCopy(&post.post_time, &rtc_time);
                        mHandbill_Load_HandbillFromRom(header, &header_back_pos, footer, post.message,
                                                       0x1F0 + selected_animal->id.looks * 3 + (RANDOM(3) % 3));
                        mNtc_notice_write(&post);
                        lbRTC_TimeCopy(treasure_buried_time, &rtc_time);
                    }
                }
            }
        }
    }
}
#endif

static void mNtc_set_near_old_nwrite_data(lbRTC_time_c* nwrite_time, lbRTC_year_t* nwrite_year, u8* nwrite_num) {
    mNtc_date_data_c* auto_nwrite_p;
    s16 date;
    int last_idx;
    int i;

    date = (nwrite_time->month << 8) + nwrite_time->day;
    last_idx = mNtc_DATA_LIST_NUM - 1;
    auto_nwrite_p = mNtc_auto_nwrite_data + (mNtc_DATA_LIST_NUM - 1);

    for (i = mNtc_DATA_LIST_NUM; i != 0; i--) {
        if (date > auto_nwrite_p->date || (date == auto_nwrite_p->date && nwrite_time->hour >= mTM_FIELD_RENEW_HOUR)) {
            break;
        }

        auto_nwrite_p--;
        last_idx--;
    }

    if (last_idx != -1) {
        *nwrite_year = nwrite_time->year;
        *nwrite_num = last_idx;
    } else {
        *nwrite_year = nwrite_time->year - 1;
        *nwrite_num = mNtc_get_auto_nwrite_data_last_idx();
    }
}

static int mNtc_make_auto_nwrite_day_string(u8* str, int month, int day) {
    int month_len;
    int day_len;
    u8 buf[24];

    month_len = mString_Load_MonthStringFromRom(buf, month);
    mem_copy(str, buf, month_len);
    str[month_len] = CHAR_SPACE;
    day_len = mString_Load_DayStringFromRom(buf, day);
    mem_copy(str + month_len + 1, buf, day_len);
    return month_len + day_len + 1;
}

static void mNtc_set_auto_nwrite_common_string() {
    int land_name_len;
    u8 land_name[LAND_NAME_SIZE];
    u8 shop_name[16];

    land_name_len = mNtc_set_landname_string(land_name);
    mHandbill_Set_free_str(0, land_name, land_name_len);

    mString_Load_StringFromRom(shop_name, 16, 0x558 + mSP_GetShopLevel());
    mHandbill_Set_free_str(1, shop_name, 16);
}

static void mNtc_set_auto_nwrite_fishing_string(const lbRTC_ymd_c* date) {
    u8 month_str[] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    u8 day_str[] = { ' ', ' ', ' ', ' ' };
    u8 size_str[] = { ' ', ' ' };
    PersonalID_c winner_pid;
    u32 size;
    lbRTC_ymd_c win_date = *date;

    mEv_fishRecord_holder(&winner_pid, &size, &win_date);
    mFont_UnintToString(size_str, 2, size, 2, 0, 0, TRUE);
    mString_Load_MonthStringFromRom(month_str, date->month);
    mHandbill_Set_free_str(0, month_str, 9);
    mString_Load_DayStringFromRom(day_str, date->day);
    mHandbill_Set_free_str(1, day_str, 4);
    mHandbill_Set_free_str(2, winner_pid.player_name, PLAYER_NAME_LEN);
    mHandbill_Set_free_str(3, size_str, 2);
}

static void mNtc_set_auto_nwrite_string(lbRTC_year_t year) {
    lbRTC_ymd_c harvest_moon_date;
    int autumnal_equi_day;
    int len;
    u8 buf[28];

    len = 0;
#ifdef TARGET_PC
    if (lbRk_TryHarvestMoonDay(&harvest_moon_date, year)) {
#else
    lbRk_HarvestMoonDay(&harvest_moon_date, year);
    {
#endif
        len = mNtc_make_auto_nwrite_day_string(buf, harvest_moon_date.month, harvest_moon_date.day);
    }
    mHandbill_Set_free_str(2, buf, len);
    autumnal_equi_day = lbRk_AutumnalEquinoxDay(year);
    len = mNtc_make_auto_nwrite_day_string(buf, lbRTC_SEPTEMBER, autumnal_equi_day);
    mHandbill_Set_free_str(4, buf, len);
}

extern void mNtc_auto_nwrite_time_ct() {
    mNtc_make_auto_nwrite_data_list();

    if (lbRTC_IsEqualTime(Save_GetPointer(saved_auto_nwrite_time), &mTM_rtcTime_clear_code, lbRTC_CHECK_ALL) == TRUE) {
        lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
        mNtc_set_near_old_nwrite_data(&rtc_time, Common_GetPointer(auto_nwrite_year),
                                      Common_GetPointer(auto_nwrite_count));
    } else {
        mNtc_set_near_old_nwrite_data(Save_GetPointer(save_check.time), Common_GetPointer(auto_nwrite_year),
                                      Common_GetPointer(auto_nwrite_count));
    }
}

/* TODO: better understand this function & refactor */
static int mNtc_get_fishing_day(lbRTC_ymd_c* ymds, u16* dates, lbRTC_time_c* time, u16* fishing_term_date) {
    int notice_year;
    int notice_hour;
    lbRTC_time_c time_temp;
    lbRTC_ymd_c ymd_buf[5];
    int valid_count = 0;
    int i;

    if (Common_Get(auto_nwrite_set) == FALSE) {
        if (mTM_IsTimeCleared(Save_GetPointer(saved_auto_nwrite_time))) {
            notice_year = time->year;
            notice_hour = time->hour;
        } else {
            notice_year = Save_Get(saved_auto_nwrite_time.year);
            notice_hour = Save_Get(saved_auto_nwrite_time.hour);
        }
    } else {
        notice_year = Common_Get(auto_nwrite_time.year);
        notice_hour = Common_Get(auto_nwrite_time.hour);
    }

    time_temp = *time;
    mEv_fishday(ymd_buf, &time_temp);

    for (i = 0; i < 5; i++) {
        dates[i] = 0;
        ymds[i].year = 0;
        ymds[i].month = 0;
        ymds[i].day = 0;
    }

    for (i = 0; i < 5; i++) {
        lbRTC_ymd_c* ymd = ymd_buf + i;
        u16 month_day = (ymd_buf[i].month << 8) + ymd_buf[i].day;

        if (ymd->year > notice_year ||
            (notice_year == ymd->year &&
             (month_day > *fishing_term_date || (month_day == *fishing_term_date && notice_hour < 18)))) {
            dates[valid_count] = month_day;
            ymds[valid_count] = *ymd;
            valid_count++;
        }
    }

    return valid_count;
}

static void mNtc_set_fishing_term(u16* date, lbRTC_year_t* year) {
    if (Common_Get(auto_nwrite_set) == FALSE) {
        if (mTM_IsTimeCleared(Save_GetPointer(saved_auto_nwrite_time))) {
            *date = (Common_Get(time.rtc_time.month) << 8) + Common_Get(time.rtc_time.day);
            *year = Common_Get(time.rtc_time.year);
        } else {
            *date = (Save_Get(saved_auto_nwrite_time.month) << 8) + Save_Get(saved_auto_nwrite_time.day);
            *year = Save_Get(saved_auto_nwrite_time.year);
        }
    } else {
        *date = (Common_Get(auto_nwrite_time.month) << 8) + Common_Get(auto_nwrite_time.day);
        *year = Common_Get(auto_nwrite_time.year);
    }
}

static void mNtc_decide_nwrite_data(int* write_count, lbRTC_year_t* nwrite_year, u8* nwrite_num,
                                    lbRTC_year_t now_nwrite_year, u8 now_nwrite_num, lbRTC_year_t* out_nwrite_years,
                                    u8* out_nwrite_nums, int* fishing_day, u16 fishing_term_date,
                                    lbRTC_year_t fishing_term_year, const lbRTC_ymd_c* ymds, const u16* month_days) {

    while (*write_count != 0) {
        if (*fishing_day > 0) {
            if ((ymds[*fishing_day - 1].year > fishing_term_year ||
                 (fishing_term_year == ymds[*fishing_day - 1].year &&
                  (month_days[*fishing_day - 1] >= fishing_term_date)))) {
                if (ymds[*fishing_day - 1].year > *nwrite_year ||
                    (*nwrite_year == ymds[*fishing_day - 1].year &&
                     month_days[*fishing_day - 1] >= mNtc_auto_nwrite_data[*nwrite_num].date)) {
                    (*write_count)--;
                    (*fishing_day)--;

                    out_nwrite_years[*write_count] = 0xFFFF;
                    out_nwrite_nums[*write_count] = 0xFFFF;
                    continue;
                }
            }
        }

        if (*nwrite_year > now_nwrite_year || (*nwrite_year == now_nwrite_year && *nwrite_num > now_nwrite_num)) {
            (*write_count)--;

            out_nwrite_years[*write_count] = *nwrite_year;
            out_nwrite_nums[*write_count] = *nwrite_num;

            if (*nwrite_num == 0) {
                *nwrite_num = mNtc_get_auto_nwrite_data_last_idx();
                (*nwrite_year)--;
            } else {
                (*nwrite_num)--;
            }
        } else {
            break;
        }
    }
}

static void mNtc_set_auto_nwrite(int write_count, u8* nwrite_nums, lbRTC_year_t* nwrite_years, int fishing_day,
                                 lbRTC_ymd_c* ymds, const u16* month_days) {
    lbRTC_year_t now_year;
    mNtc_board_post_c post;
    int header_back_pos;
    u8 header[MAIL_FOOTER_LEN];
    u8 footer[MAIL_FOOTER_LEN];
    int year;
    lbRTC_month_t month;
    lbRTC_day_t day;

    post.post_time.sec = 0;
    post.post_time.min = 0;
    post.post_time.hour = 6;

    now_year = 0;

    for (write_count; write_count < 5; write_count++) {
        /* write 'fishing day' info */
        if (nwrite_nums[write_count] == mNtc_FISHING_DAY_NUM && nwrite_years[write_count] == mNtc_FISHING_DAY_YEAR) {
            lbRTC_ymd_c temp;
            lbRTC_ymd_c* post_date = &ymds[fishing_day];
            lbRTC_year_t year = post_date->year;
            u8 month = mNtc_GET_MONTH(month_days[fishing_day]);
            u8 day = mNtc_GET_DAY(month_days[fishing_day]);
            int id = (post_date->day / 7) & 3;

            post.post_time.year = year;
            post.post_time.month = month;
            post.post_time.day = day;
            post.post_time.weekday = lbRTC_Week(year, month, day);

            temp = *post_date;
            mNtc_set_auto_nwrite_fishing_string(&temp);
            now_year = 0;
            mHandbill_Load_HandbillFromRom(header, &header_back_pos, footer, post.message, 0x242 + id);
            mNtc_notice_write(&post);
            fishing_day++;
        } else { /* write standard post */
            mNtc_set_auto_nwrite_common_string();
            /* check if we need to change the year string to a different year */
            if (now_year != nwrite_years[write_count]) {
                mNtc_set_auto_nwrite_string(nwrite_years[write_count]);
                now_year = nwrite_years[write_count];
            }

            year = nwrite_years[write_count];
            month = mNtc_GET_MONTH(mNtc_auto_nwrite_data[nwrite_nums[write_count]].date);
            day = mNtc_GET_DAY(mNtc_auto_nwrite_data[nwrite_nums[write_count]].date);

            post.post_time.year = year;
            post.post_time.month = month;
            post.post_time.day = day;
            post.post_time.weekday = lbRTC_Week(year, month, day);

            mHandbill_Load_HandbillFromRom(header, &header_back_pos, footer, post.message,
                                           0x1A4 + mNtc_auto_nwrite_data[nwrite_nums[write_count]].id);
            mNtc_notice_write(&post);
        }
    }
}

extern void mNtc_set_auto_nwrite_data() {
    u8 nwrite_num;
    u16 fishing_term_date;
    lbRTC_year_t fishing_term_year;
    lbRTC_year_t nwrite_year;
    lbRTC_year_t now_nwrite_year;
    u8 now_nwrite_num;
    lbRTC_time_c rtc_time;
    u8 set_nwrite_nums[5];
    lbRTC_ymd_c nwrite_ymds[mNtc_NWRITE_NUM];
    u16 nwrite_dates[mNtc_NWRITE_NUM];
    lbRTC_year_t set_nwrite_years[mNtc_NWRITE_NUM];
    int write_count;

    if (mEv_CheckTitleDemo() == mEv_TITLEDEMO_NONE && mFI_GET_TYPE(mFI_GetFieldId()) == mFI_TYPE(mFI_FIELDTYPE_FG)) {
        int fishing_day;
        now_nwrite_year = Common_Get(auto_nwrite_year);
        if (now_nwrite_year != 0) {
            write_count = mNtc_NWRITE_NUM;
            fishing_day = 0;
            rtc_time = Common_Get(time.rtc_time);
            now_nwrite_num = Common_Get(auto_nwrite_count);
            mNtc_make_auto_nwrite_data_list();
            mNtc_set_fishing_term(&fishing_term_date, &fishing_term_year);
            fishing_day = mNtc_get_fishing_day(nwrite_ymds, nwrite_dates, &rtc_time, &fishing_term_date);
            mNtc_set_near_old_nwrite_data(&rtc_time, &nwrite_year, &nwrite_num);

            mNtc_decide_nwrite_data(&write_count, &nwrite_year, &nwrite_num, now_nwrite_year, now_nwrite_num,
                                    set_nwrite_years, set_nwrite_nums, &fishing_day, fishing_term_date,
                                    fishing_term_year, nwrite_ymds, nwrite_dates);

            if (write_count != mNtc_NWRITE_NUM) {
                mNtc_set_auto_nwrite(write_count, set_nwrite_nums, set_nwrite_years, fishing_day, nwrite_ymds,
                                     nwrite_dates);
            } else {
                if (Common_Get(buried_treasure_flag) == FALSE) {
                    mNtc_check_treasure();
                }
            }

            mNtc_set_near_old_nwrite_data(&rtc_time, &nwrite_year, &nwrite_num);

            Common_Set(auto_nwrite_year, nwrite_year);
            Common_Set(auto_nwrite_count, nwrite_num);
            Common_Set(auto_nwrite_set, TRUE);
            Common_Set(auto_nwrite_time, Common_Get(time.rtc_time));
            Save_Set(saved_auto_nwrite_time, Common_Get(time.rtc_time));
            mFR_fishmail(); /* send fishing tourney result mail */
            Common_Set(buried_treasure_flag, TRUE);
            lbRTC_TimeCopy(Save_GetPointer(treasure_checked_time), &rtc_time);
        }
    }
}
