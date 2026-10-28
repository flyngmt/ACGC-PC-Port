#ifndef M_EVENT_H
#define M_EVENT_H

#include "types.h"
#include "libu64/gfxprint.h"
#include "m_personal_id.h"
#include "m_private.h"
#include "m_time.h"
#include "m_olib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mEv_TODAY_EVENT_NUM 16

#define mEv_SCHEDULE_LAST_WEEKDAY_OF_MONTH 6 /* day of last weekday of the month */
#define mEv_SCHEDULE_EVERY_WEEK 7            /* scheduled for the desired day this week (e.g. this saturday) */

/* Month flags */
#define mEv_SCHEDULE_HARVEST_MOON_DATE 0x40 /* Use this year's lunisolar harvest moon date */
#define mEv_SCHEDULE_NOW_MONTH 0x20
#define mEv_SCHEDULE_USE_SAVE_MONTH 0x10

#define mEv_SCHEDULE_SAVE_MONTH(m) (mEv_SCHEDULE_USE_SAVE_MONTH | ((m) & 0xF))
#define mEv_SCHEDULE_LUNAR(m) (mEv_SCHEDULE_HARVEST_MOON_DATE | ((m) & 0xF))

/* Day flags */
#define mEv_SCHEDULE_WEEKLY 0x80   /* Event happens on a given weekday and week of the month */
#define mEv_SCHEDULE_TOWN_DAY 0x40 /* Use save data 'town day' day */
#define mEv_SCHEDULE_DAY_AFTER \
    0x40 /* When used in conjunction with the 'weekly' flag, it schedules on the day after the Nth weekday */
#define mEv_SCHEDULE_LAST_DAY_OF_MONTH 0x20

#define mEv_SCHEDULE_MAKE_WEEKLY_DATA(week, weekday) \
    (mEv_SCHEDULE_WEEKLY | ((((week) & 0b111) << 3) | ((weekday) & 0b111)))
#define mEv_SCHEDULE_1ST_WEEKDAY(weekday) mEv_SCHEDULE_MAKE_WEEKLY_DATA(1, weekday)
#define mEv_SCHEDULE_2ND_WEEKDAY(weekday) mEv_SCHEDULE_MAKE_WEEKLY_DATA(2, weekday)
#define mEv_SCHEDULE_3RD_WEEKDAY(weekday) mEv_SCHEDULE_MAKE_WEEKLY_DATA(3, weekday)
#define mEv_SCHEDULE_4TH_WEEKDAY(weekday) mEv_SCHEDULE_MAKE_WEEKLY_DATA(4, weekday)
#define mEv_SCHEDULE_5TH_WEEKDAY(weekday) mEv_SCHEDULE_MAKE_WEEKLY_DATA(5, weekday)
#define mEv_SCHEDULE_LAST_WEEKDAY(weekday) mEv_SCHEDULE_MAKE_WEEKLY_DATA(mEv_SCHEDULE_LAST_WEEKDAY_OF_MONTH, weekday)
#define mEv_SCHEDULE_EVERY_WEEKDAY(weekday) mEv_SCHEDULE_MAKE_WEEKLY_DATA(mEv_SCHEDULE_EVERY_WEEK, weekday)

/* Hour flags */
#define mEv_SCHEDULE_TODAY 0x80    /* event will be active on the day loaded */
#define mEv_SCHEDULE_MULTIDAY 0x40 /* event scheduled over more than a single day */
#define mEv_SCHEDULE_USE_SAVE_SLOT_VALUE 0x20

#define mEv_SCHEDULE_HOUR_SLOT(h) (mEv_SCHEDULE_USE_SAVE_SLOT_VALUE | (h & 0xF))

#define mEv_TO_DAY(month_day) ((lbRTC_day_t)(month_day))
#define mEv_TO_MONTH(month_day) ((lbRTC_month_t)((month_day) >> 8))

enum {
    mEv_TITLEDEMO_STAFFROLL = -9,
    mEv_TITLEDEMO_LOGO = -1,

    mEv_TITLEDEMO_NONE = 0,
    mEv_TITLEDEMO_START1,
    mEv_TITLEDEMO_START2,
    mEv_TITLEDEMO_START3,
    mEv_TITLEDEMO_START4,
    mEv_TITLEDEMO_START5,

    mEv_TITLEDEMO_NUM
};

typedef union event_monthday_s {
    struct {
#ifdef TARGET_PC
        /* LE: swap so raw/u16 = (month << 8) | day for correct date ordering */
        u8 day;
        u8 month;
#else
        u8 month;
        u8 day;
#endif
    };
    u16 raw;
} mEv_MonthDay_u;

typedef struct event_today_s {
    int type;
    u32 active_hours; /* bitfield (24 bits) */
    mEv_MonthDay_u begin_date;
    mEv_MonthDay_u end_date;
    s16 status;
    u16 pad;
} mEv_event_today_c;

typedef struct event_date_s {
#ifdef TARGET_PC
    /* LE: swap so u16 md = (month << 8) | day for correct date ordering */
    u8 day;
    u8 month;
    u8 hour;
    u8 _2;
#else
    u8 month;
    u8 day;
    u8 _2;
    u8 hour;
#endif
} mEv_schedule_date_c;

typedef union {
    mEv_schedule_date_c d;
    u16 md, _h;
    u32 raw;
} mEv_schedule_date_u;

typedef struct event_schedule_s {
    mEv_schedule_date_u date[2]; /* 0 = begin, 1 = end */
    s16 _8;
    s16 type; /* event type */
} mEv_schedule_c;

#define mEv_EVENT_HOUR_START_EVENT (1 << 28)
#define mEv_EVENT_HOUR_CLEAR_EVENT (1 << 29)
#define mEv_EVENT_HOUR_TOO_SHORT_EVENT (1 << 30)

/**
 * Event type definition
 *  xxxyyyyy yyyyyyyy yyyyyyyy yyyyyyyy
 *
 *  x: event type (e.g. special event, 'first job' (chores) event, holidays, ...) (0-7)
 *  y: sub-type (specific event)
 **/

#define mEv_SUBTYPE_BITS 29
#define mEv_TYPE_BITMASK (0b111 << mEv_SUBTYPE_BITS)
#define mEv_SUBTYPE_BITMASK ((1 << mEv_SUBTYPE_BITS) - 1)

#define mEv_GET_TYPE(event) (((event) & mEv_TYPE_BITMASK) >> mEv_SUBTYPE_BITS)
#define mEv_SET_TYPE(t) (((t) << mEv_SUBTYPE_BITS) & mEv_TYPE_BITMASK)

#define mEv_GET_SUBTYPE(event) ((event) & mEv_SUBTYPE_BITMASK)
#define mEv_SET_SUBTYPE(s) ((s) & mEv_SUBTYPE_BITMASK)

#define mEv_SET(type, subtype) (mEv_SET_TYPE(type) | mEv_SET_TYPE(subtype))

enum event_type {
    mEv_SPNPC_EVENT, /* special NPC events */
    mEv_SAVED_EVENT, /* events saved to data */
    mEv_TYPE2_EVENT, /* unused? */
    mEv_TYPE_RUMOR,
    mEv_TYPE4_EVENT, /* unused? */
    mEv_DAILY_EVENT, /* checked daily always? aSL_ReportShopOpen2Event has event 3 */
    mEv_SPECL_EVENT, /* ??? secondary special npc event data? */

    mEv_EVENT_TYPE_NUM
};

enum events {
    mEv_SPNPC_SHOP = (int)mEv_SET(mEv_SPNPC_EVENT, 0),
    mEv_SPNPC_DESIGNER,
    mEv_SPNPC_BROKER,
    mEv_SPNPC_ARTIST,
    mEv_SPNPC_ARABIAN,
    mEv_SPNPC_GYPSY,
    mEv_SPNPC_END,

    mEv_SAVED_RENEWSHOP = (int)mEv_SET(mEv_SAVED_EVENT, 0), /* renew shop */
    mEv_SAVED_UNK1,                                         /* unused */

    /* intro through chores */
    mEv_SAVED_FIRSTJOB_PLR0,
    mEv_SAVED_FIRSTJOB_PLR1,
    mEv_SAVED_FIRSTJOB_PLR2,
    mEv_SAVED_FIRSTJOB_PLR3,

    /* selecting house */
    mEv_SAVED_FIRSTINTRO_PLR0,
    mEv_SAVED_FIRSTINTRO_PLR1,
    mEv_SAVED_FIRSTINTRO_PLR2,
    mEv_SAVED_FIRSTINTRO_PLR3,

    /* wait for next day to talk about HRA */
    mEv_SAVED_HRAWAIT_PLR0,
    mEv_SAVED_HRAWAIT_PLR1,
    mEv_SAVED_HRAWAIT_PLR2,
    mEv_SAVED_HRAWAIT_PLR3,

    /* Nook will talk about HRA when entering the shop */
    mEv_SAVED_HRATALK_PLR0,
    mEv_SAVED_HRATALK_PLR1,
    mEv_SAVED_HRATALK_PLR2,
    mEv_SAVED_HRATALK_PLR3,

    /* Do a 'favor' for a villager during chores */
    mEv_SAVED_FJOPENQUEST_PLR0,
    mEv_SAVED_FJOPENQUEST_PLR1,
    mEv_SAVED_FJOPENQUEST_PLR2,
    mEv_SAVED_FJOPENQUEST_PLR3,

    /* Player going to another town, set at train station */
    mEv_SAVED_GATEWAY_PLR0,
    mEv_SAVED_GATEWAY_PLR1,
    mEv_SAVED_GATEWAY_PLR2,
    mEv_SAVED_GATEWAY_PLR3,
    mEv_SAVED_GATEWAY_FRGN, /* Foreigner */

    /* Rumors */
    mEv_RUMOR_NEW_YEARS_DAY = (int)mEv_SET(mEv_TYPE_RUMOR, 0),
    mEv_RUMOR_KAMAKURA,
    mEv_RUMOR_VALENTINES_DAY,
    mEv_RUMOR_GROUNDHOG_DAY,
    mEv_RUMOR_CHERRY_BLOSSOM_FESTIVAL,
    mEv_RUMOR_CHERRY_BLOSSOM_FESTIVAL2,
    mEv_RUMOR_SPRING_SPORTS_FAIR,
    mEv_RUMOR_HARVEST_FESTIVAL,
    mEv_RUMOR_KOINOBORI,
    mEv_RUMOR_SUMMER_FISHING_TOURNEY,
    mEv_RUMOR_SUMMER_FISHING_TOURNEY2,
    mEv_RUMOR_MORNING_AEROBICS,
    mEv_RUMOR_MORNING_AEROBICS2,
    mEv_RUMOR_FIREWORKS_SHOW,
    mEv_RUMOR_FIREWORKS_SHOW2, // reminder it happens weekly, unused in AC
    mEv_RUMOR_METEOR_SHOWER,
    mEv_RUMOR_HARVEST_MOON_DAY,
    mEv_RUMOR_FALL_SPORTS_FAIR,
    mEv_RUMOR_MUSHROOM_SEASON,
    mEv_RUMOR_TALK_MUSHROOM_SEASON,
    mEv_RUMOR_HALLOWEEN,
    mEv_RUMOR_FALL_FISHING_TOURNEY,
    mEv_RUMOR_FALL_FISHING_TOURNEY2,
    mEv_RUMOR_TOY_DAY,
    mEv_RUMOR_NEW_YEARS_EVE_COUNTDOWN,

    mEv_DAILY_0 = (int)mEv_SET(mEv_DAILY_EVENT, 0), /* unused */
    mEv_DAILY_1,                                    /* unused */
    mEv_DAILY_2,                                    /* unused */
    mEv_DAILY_OPEN_SHOP,                            /* shop opened */

    mEv_SPECL_DESIGNER_COMPLETE = (int)mEv_SET(mEv_SPECL_EVENT, 0)
};

enum week_type {
    mEv_WEEKTYPE_NONE,
    mEv_WEEKTYPE_1ST,
    mEv_WEEKTYPE_2ND,
    mEv_WEEKTYPE_3RD,
    mEv_WEEKTYPE_4TH,
    mEv_WEEKTYPE_5TH,
    mEv_WEEKTYPE_LAST,
    mEv_WEEKTYPE_SPECIAL
};

enum event_table {
    mEv_EVENT_RUMOR_NEW_YEARS_DAY,
    mEv_EVENT_NEW_YEARS_DAY,
    mEv_EVENT_RUMOR_KAMAKURA,
    mEv_EVENT_KAMAKURA,
    mEv_EVENT_SONCHO_VACATION_JANUARY,
    mEv_EVENT_SONCHO_VACATION_FEBRUARY,
    mEv_EVENT_RUMOR_GROUNDHOG_DAY,
    mEv_EVENT_GROUNDHOG_DAY,
    mEv_EVENT_RUMOR_VALENTINES_DAY,
    mEv_EVENT_VALENTINES_DAY,
    mEv_EVENT_RUMOR_SPRING_SPORTS_FAIR,
    mEv_EVENT_SPRING_EQUINOX,
    mEv_EVENT_SPORTS_FAIR_BALL_TOSS,
    mEv_EVENT_SPORTS_FAIR_AEROBICS,
    mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR,
    mEv_EVENT_SPORTS_FAIR_FOOT_RACE,
    mEv_EVENT_SPORTS_FAIR,
    mEv_EVENT_APRILFOOLS_DAY,
    mEv_EVENT_RUMOR_APRILFOOLS_DAY,
    mEv_EVENT_RUMOR_CHERRY_BLOSSOM_FESTIVAL,
    mEv_EVENT_CHERRY_BLOSSOM_FESTIVAL,
    mEv_EVENT_NATURE_DAY,
    mEv_EVENT_SPRING_CLEANING,
    mEv_EVENT_MOTHERS_DAY,
    mEv_EVENT_SUMMER_CAMPER,
    mEv_EVENT_GRADUATION_DAY,
    mEv_EVENT_FATHERS_DAY,
    mEv_EVENT_RUMOR_FISHING_TOURNEY_1,
    mEv_EVENT_TALK_FISHING_TOURNEY_1, // for dialog?
    mEv_EVENT_FISHING_TOURNEY_1,
    mEv_EVENT_TOWN_DAY,
    mEv_EVENT_RUMOR_FIREWORKS_SHOW,
    mEv_EVENT_FIREWORKS_SHOW,
    mEv_EVENT_RUMOR_MORNING_AEROBICS,
    mEv_EVENT_TALK_MORNING_AEROBICS,
    mEv_EVENT_MORNING_AEROBICS,
    mEv_EVENT_RUMOR_METEOR_SHOWER,
    mEv_EVENT_METEOR_SHOWER,
    mEv_EVENT_FOUNDERS_DAY,
    mEv_EVENT_LABOR_DAY,
    mEv_EVENT_RUMOR_FALL_SPORTS_FAIR,
    mEv_EVENT_AUTUMN_EQUINOX,
    mEv_EVENT_RUMOR_HARVEST_MOON_DAY,
    mEv_EVENT_HARVEST_MOON_FESTIVAL,
    mEv_EVENT_EXPLORERS_DAY,
    mEv_EVENT_RUMOR_MUSHROOM_SEASON,
    mEv_EVENT_TALK_MUSHROOM_SEASON,
    mEv_EVENT_MUSHROOM_SEASON,
    mEv_EVENT_RUMOR_HALLOWEEN,
    mEv_EVENT_HALLOWEEN,
    mEv_EVENT_MAYORS_DAY,
    mEv_EVENT_OFFICERS_DAY,
    mEv_EVENT_RUMOR_FISHING_TOURNEY_2,
    mEv_EVENT_TALK_FISHING_TOURNEY_2,
    mEv_EVENT_FISHING_TOURNEY_2,
    mEv_EVENT_RUMOR_HARVEST_FESTIVAL,
    mEv_EVENT_HARVEST_FESTIVAL,
    mEv_EVENT_SALE_DAY,
    mEv_EVENT_SNOW_DAY,
    mEv_EVENT_TOY_DAY_SONCHO,
    mEv_EVENT_RUMOR_TOY_DAY,
    mEv_EVENT_TOY_DAY_JINGLE,
    mEv_EVENT_SNOWMAN_SEASON,
    mEv_EVENT_RUMOR_NEW_YEARS_EVE_COUNTDOWN,
    mEv_EVENT_NEW_YEARS_EVE_COUNTDOWN,
    mEv_EVENT_CHERRY_BLOSSOM_PETALS,
    mEv_EVENT_TALK_TOY_DAY,

    mEv_EVENT_PLAYER_BIRTHDAY,

    mEv_EVENT_DOZAEMON,
    mEv_EVENT_KABU_PEDDLER,
    mEv_EVENT_LOTTERY,
    mEv_EVENT_KK_SLIDER,

    mEv_EVENT_HANDBILL_BROKER,
    mEv_EVENT_HANDBILL_SHOP_SALE,

    mEv_EVENT_ARTIST,
    mEv_EVENT_BROKER_SALE,
    mEv_EVENT_DESIGNER,
    mEv_EVENT_GYPSY,
    mEv_EVENT_SHOP_SALE,
    mEv_EVENT_CARPET_PEDDLER,

    mEv_EVENT_SONCHO_NEW_YEARS_DAY,
    mEv_EVENT_SONCHO_GROUNDHOG_DAY,
    mEv_EVENT_SONCHO_SPRING_SPORTS_FAIR,
    mEv_EVENT_SONCHO_APRILFOOLS_DAY,
    mEv_EVENT_SONCHO_CHERRY_BLOSSOM_FESTIVAL,
    mEv_EVENT_SONCHO_NATURE_DAY,
    mEv_EVENT_SONCHO_SPRING_CLEANING,
    mEv_EVENT_SONCHO_MOTHERS_DAY,
    mEv_EVENT_SONCHO_GRADUATION_DAY,
    mEv_EVENT_SONCHO_FATHERS_DAY,
    mEv_EVENT_SONCHO_FISHING_TOURNEY_1,
    mEv_EVENT_SONCHO_TOWN_DAY,
    mEv_EVENT_SONCHO_FIREWORKS_SHOW,
    mEv_EVENT_SONCHO_METEOR_SHOWER,
    mEv_EVENT_SONCHO_FOUNDERS_DAY,
    mEv_EVENT_SONCHO_LABOR_DAY,
    mEv_EVENT_SONCHO_FALL_SPORTS_FAIR,
    mEv_EVENT_SONCHO_HARVEST_MOON_FESTIVAL,
    mEv_EVENT_SONCHO_EXPLORERS_DAY,
    mEv_EVENT_SONCHO_HALLOWEEN,
    mEv_EVENT_SONCHO_MAYORS_DAY,
    mEv_EVENT_SONCHO_OFFICERS_DAY,
    mEv_EVENT_SONCHO_FISHING_TOURNEY_2,
    mEv_EVENT_SONCHO_HARVEST_FESTIVAL,
    mEv_EVENT_SONCHO_SALE_DAY,
    mEv_EVENT_SONCHO_SNOW_DAY,
    mEv_EVENT_SONCHO_TOY_DAY,

    mEv_EVENT_TALK_NEW_YEARS_COUNTDOWN,
    mEv_EVENT_HARVEST_FESTIVAL_FRANKLIN,

    mEv_EVENT_WEATHER_CLEAR,
    mEv_EVENT_WEATHER_SNOW,
    mEv_EVENT_WEATHER_SPORTS_FAIR,

    mEv_EVENT_BRIDGE_MAKE,
    mEv_EVENT_SONCHO_BRIDGE_MAKE,

    mEv_EVENT_GHOST,
    mEv_EVENT_MASK_NPC, // "Go Home Npc" & "Blanca" events

    mEv_EVENT_74, // unused?

    mEv_EVENT_KOINOBORI,

    mEv_EVENT_76, // unused?

    mEv_EVENT_NUM
};

enum {
    mEv_SAVE_DATE_TODAY,
    mEv_SAVE_DATE_LAST_PLAY_DATE,
    mEv_SAVE_DATE_BIRTHDAY,
    mEv_SAVE_DATE_SPECIAL0, /* Initialized to rtc month-day in init_special_event */
    mEv_SAVE_DATE_SPECIAL1, /* Initialized to beginning month-day of special event in init_special_event */
    mEv_SAVE_DATE_SPECIAL2, /* Initialized to ending month-day of special event in init_special_event */
    mEv_SAVE_DATE_WEEKLY,
    mEv_SAVE_DATE_SPECIAL3, /* Initialized to opening hours for shop sale in init_special_event */

    mEv_SAVE_DATE_NUM
};

enum {
    mEv_SPECIAL_STATE_UNSCHEDULED,
    mEv_SPECIAL_STATE_SCHEDULED_LATER,
    mEv_SPECIAL_STATE_SCHEDULED_TODAY,
    mEv_SPECIAL_STATE_ACTIVE,

    mEv_SPECIAL_STATE_NUM
};

enum {
    mEv_EVENT_MAIL_VT_DAY, /* Valentine's day */
    mEv_EVENT_MAIL_WT_DAY, /* White day */

    mEv_EVENT_MAIL_NUM
};

#define mEv_STATUS_ACTIVE (1 << 0)    /* event is active */
#define mEv_STATUS_STOP (1 << 1)      /* event is stopped */
#define mEv_STATUS_SHOW (1 << 2)      /* event is shown */
#define mEv_STATUS_PLAYSOUND (1 << 3) /* event should play sound */
#define mEv_STATUS_RUN (1 << 4)       /* event should run */
#define mEv_STATUS_ERROR (1 << 5)     /* event is in error state */
#define mEv_STATUS_TALK (1 << 6)      /* event requires talking to player */
#define mEv_STATUS_EXIST (1 << 7)     /* event is scheduled */

#define mEv_GHOST_HITODAMA_NUM 5
typedef struct ghost_spirit_block_data_s {
    u8 block_x[mEv_GHOST_HITODAMA_NUM];
    u8 block_z[mEv_GHOST_HITODAMA_NUM];
} mEv_gst_hitodama_block_c;

#define mEv_GHOST_FLAG_ACTIVE 0x4000 // TODO: do these live in the ghost actor itself?
#define mEv_GHOST_FLAG_RETURNED_SPIRITS 0x8000

#define mEv_GHOST_COMMON_SPAWNED_SPIRITS 0x8000

typedef struct ghost_common_s {
    mEv_gst_hitodama_block_c hitodama_block_data;
    u16 flags;
    u8 _0C[0x2C - 0x0C];
} mEv_gst_common_c;

typedef struct ghost_event_s {
    u16 okoruhito_str_no;
    u16 flags;
    lbRTC_ymd_c renew_time;
} mEv_gst_c;

#define mEv_DESGINER_NUM 3

typedef struct designer_common_s {
    int button_presses;
    int _04;
} mEv_dsg_common_c;

typedef struct kabu_peddler_event_s {
    PersonalID_c spoken_pids[TOTAL_PLAYER_NUM];
} mEv_kabu_peddler_c;

typedef struct dozaemon_event_s {
    u16 flags;
} mEv_dozaemon_c;

typedef union {
    mEv_kabu_peddler_c kabu_peddler;
    mEv_dozaemon_c dozaemon;
} mEv_weekly_u;

#define mEv_BARGIN_ITEM_NUM 5

typedef struct bargin_event_s {
    lbRTC_time_c start_time;
    lbRTC_time_c end_time;
    mActor_name_t items[mEv_BARGIN_ITEM_NUM];
    int kind;
} mEv_bargin_c;

typedef struct designer_event_s {
    PersonalID_c pids[mEv_DESGINER_NUM];
    int used;
    mActor_name_t gifted_cloths[mEv_DESGINER_NUM];
} mEv_designer_c;

#define mEv_BROKER_ITEM_NUM 3

typedef struct broker_event_s {
    PersonalID_c pid[mEv_BROKER_ITEM_NUM - 1];
    lbRTC_time_c end_time;
    int used;
    mActor_name_t sold_items[mEv_BROKER_ITEM_NUM - 1];
    mActor_name_t items[mEv_BROKER_ITEM_NUM];
} mEv_broker_c;

#define mEv_ARTIST_ENTRY_SAVE_NUM 2

typedef struct artist_event_s {
    PersonalID_c pids[mEv_ARTIST_ENTRY_SAVE_NUM];
    int used;
    mActor_name_t walls[mEv_ARTIST_ENTRY_SAVE_NUM];
} mEv_artist_c;

typedef struct arabian_event_s {
    int used;
    mActor_name_t carpet;
} mEv_arabian_c;

typedef struct gypsy_event_s {
    int _00;
    int block_z;
    int block_x;
    int ut_z;
    int ut_x;
} mEv_gypsy_c;

typedef union {
    mEv_bargin_c bargin;
    mEv_designer_c designer;
    mEv_broker_c broker;
    mEv_artist_c artist;
    mEv_arabian_c arabian;
    mEv_gypsy_c gypsy;
} mEv_special_u;

typedef struct special_event_s {
    lbRTC_time_c scheduled;
    u32 kind;
    mEv_special_u event;
} mEv_special_c;

typedef struct save_event_data_s {
    mEv_special_c special;
    mEv_weekly_u weekly;
    u32 flags;
} mEv_event_save_c;

typedef struct broker_event_common_s {
    PersonalID_c entered_pid;
    int hide_npc;
} mEv_broker_common_c;

typedef struct santa_event_common_s {
    u8 present;
    u8 talk_counter;
    s8 bx;
    s8 bz;
    mActor_name_t last_talk_cloth;
} mEv_santa_event_common_c;

#define mEv_SANTA_CLOTH_NUM_MAX 10 /* How many different shirts can the player trick Jingle with */

typedef struct santa_event_s {
    PersonalID_c pid;
    u8 present_count;
    mActor_name_t cloth[mEv_SANTA_CLOTH_NUM_MAX];
} mEv_santa_event_c;

typedef union {
    mEv_broker_common_c broker;
    mEv_santa_event_common_c santa;
} mEv_event_common_u;

typedef struct event_s {
    u8 day;
    u8 hour;
    u8 _02;
    u8 state;
    u8 month;
    u8 year;
    s16 changed_num;
    int block_z;
    int block_x;
    int unused[5];
} Event_c;

typedef struct event_info_s {
    u8 type;
    u8 id;
    u16 year;
    mEv_MonthDay_u start_date;
    mEv_MonthDay_u end_date;
} mEv_info_c;

typedef struct event_place_data_s {
    BlockOrUnit_c block;
    BlockOrUnit_c unit;
    mActor_name_t actor_name;
    s16 flag;
} mEv_place_data_c;

typedef struct event_place_s {
    mEv_info_c info;
    mEv_place_data_c data;
} mEv_place_c;

typedef struct event_area_s {
    mEv_info_c info;
    int data[11];
} mEv_area_c;

#define mEv_AREA_NUM 5
#define mEv_PLACE_NUM 10

typedef struct event_common_s {
    s16 _00;
    s16 area_use_bitfield;
    mEv_area_c area[mEv_AREA_NUM];
    s16 too_short;
    s16 place_use_bitfield;
    mEv_place_c place[mEv_PLACE_NUM];
    s16 fieldday_event_id;
    s16 fieldday_event_over_status;
    u32 unused[2];
} mEv_common_data_c;

typedef struct event_save_event_info_s {
    u8 type;
    u8 flags;
} mEv_event_save_info_c;

typedef struct event_common_save_data {
    mEv_event_save_info_c special_event;
    mEv_event_save_info_c weekly_event;
    u16 dates[mEv_SAVE_DATE_NUM];
    int area_use_bitfield;
    mEv_area_c area[mEv_AREA_NUM];
    int last_date;
    int delete_event_id;
    u32 valentines_day_date;
    u32 white_day_date; /* unused in AC */
    u16 ghost_day;
    u16 bridge_day; // last date suspension bridge event was active
    union {
        struct {
#ifdef TARGET_PC
            u8 locations_used : 7;
            u8 used_all_locations : 1;
#else
            u8 used_all_locations : 1; // set to true when tortimer has cycled through all possible bridge locations?
            u8 locations_used : 7;     // index of river acre w/ possible bridge location currently at
#endif
        };

        u8 raw;
    } bridge_flags;
    u8 ghost_event_type;   // 0x72 will spawn wisp, 0x77 won't?
    u8 soncho_event_type;  // checked not equal to 0xFF for summer & fall fishing tournies
    u8 dozaemon_completed; // used to signal when you've received an item from gulliver
} mEv_save_common_data_c;

extern void mEv_ClearSpecialEvent(mEv_special_c* special_event);
extern void mEv_ClearEventKabuPeddler(mEv_kabu_peddler_c* kabu_peddler);
extern void mEv_ClearEventSaveInfo(mEv_event_save_c* save_event);
extern void mEv_ClearEventInfo();
extern void mEv_EventON(u32 event_kind);
extern void mEv_EventOFF(u32 event_kind);
extern int mEv_CheckEvent(u32 event_kind);
extern void mEv_ClearPersonalEventFlag(int player_no);
extern void mEv_SetFirstJob();
extern int mEv_CheckRealArbeit();
extern int mEv_CheckArbeit();
extern int mEv_CheckFirstJob();
extern void mEv_UnSetFirstJob();
extern void mEv_SetFirstIntro();
extern int mEv_CheckFirstIntro();
extern void mEv_UnSetFirstIntro();
extern void mEv_SetGateway();
extern int mEv_CheckGateway();
extern void mEv_UnSetGateway();
extern int mEv_CheckTitleDemo();
#define mEv_IsTitleDemo() (mEv_CheckTitleDemo() > mEv_TITLEDEMO_NONE)
#define mEv_IsNotTitleDemo() (!mEv_IsTitleDemo())
extern void mEv_SetTitleDemo(int demo_number);
extern void mEv_RenewalDataEveryDay();
extern void mEv_GetEventWeather(s16* weather, s16* intensity);
extern lbRTC_day_t mEv_get_next_weekday(lbRTC_weekday_t weekday);
extern int mEv_weekday2day(lbRTC_month_t month, int week, int weekday);
extern int mEv_get_end_time(int event_type);
extern u16 mEv_get_bargain_day();
extern u16 mEv_get_special_event_day();
extern u16 mEv_get_special_event_type();
extern int mEv_get_event_place(int event, int* bx, int* bz);
extern int mEv_bridge_time_check();
extern void mEv_init(Event_c* event);
extern void mEv_init_force(Event_c* event);
extern void mEv_2nd_init(Event_c* event);
extern int mEv_PlayerOK();
extern void mEv_run(Event_c* event);
extern void mEv_finish(Event_c* event);
extern int mEv_check_schedule(int event);
extern int mEv_check_run_today(int event);
extern void mEv_set_status(int event, s16 status);
extern void mEv_clear_status(int event, s16 status);
extern int mEv_check_status(int event, s16 status);
extern int mEv_check_status_edge(s16 status);
extern void mEv_set_keep(int event);
extern void mEv_clear_keep(int event);
extern int mEv_check_keep(int event);
extern u8* mEv_reserve_save_area(int type, u8 id);
extern u8* mEv_get_save_area(int type, u8 id);
extern int mEv_clear_save_area(int type, u8 id);
extern u8* mEv_reserve_common_area(int type, u8 id);
extern u8* mEv_get_common_area(int type, u8 id);
extern int mEv_clear_common_area(int type, u8 id);
extern mEv_place_data_c* mEv_reserve_common_place(int type, u8 id);
extern mEv_place_data_c* mEv_get_common_place(int type, u8 id);
extern int mEv_clear_common_place(int type, u8 id);
extern int mEv_use_block_by_other_event(int type, BlockOrUnit_c block);
extern void mEv_erase_FG_all_in_common_place();
extern void mEv_clear_rumor();
extern int mEv_spread_rumor(int type);
extern int mEv_get_rumor();
extern void mEv_actor_dying_message(int type, ACTOR* actor);
extern int mEv_LiveSonchoPresent();
extern int mEv_LivePlayer(u32 player_no);
extern int mEv_ArbeitPlayer_kari(u32 player_no);
extern int mEv_ArbeitPlayer(u32 player_no);
extern void mEv_make_new_special_event();
extern int mEv_GetMonth(Event_c* event);
extern int mEv_GetDay(Event_c* event);
extern int mEv_GetHour(Event_c* event);
extern void mEv_debug_print4f(gfxprint_t* gfxprint);
extern void mEv_sp_debug_print4f(gfxprint_t* gfxprint);
extern int mEv_change(Event_c* event);
extern int mEv_get_special_event_state();
extern int mEv_snowman_born_check();
extern int mEv_someone_died();
extern void mEv_special_event_soldout(int type);
extern void mEv_toland_clear_common();
extern void mGH_animal_return_init();
extern int mGH_check_birth2();
extern int mGH_check_birth();
extern void mGH_check_delete();
extern void mMC_mask_cat_init();
extern int mMC_check_birth();
extern int mMC_check_birth_day();
extern void mMC_check_delete();
extern void mMC_set_time();

#define mEv_IsEventActive(event) mEv_check_status(event, mEv_STATUS_ACTIVE)

#ifdef __cplusplus
}
#endif

#endif
