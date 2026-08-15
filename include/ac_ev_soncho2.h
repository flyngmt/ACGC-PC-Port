#ifndef AC_EV_SONCHO2_H
#define AC_EV_SONCHO2_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Ev_Soncho2_Profile;

typedef struct ac_npc_soncho2 NPC_SONCHO2;

typedef void (*aEV_SONCHO2_PROC)(NPC_SONCHO2* soncho, GAME_PLAY* play);
typedef void (*aEV_SONCHO2_TALK_PROC)(NPC_SONCHO2* soncho, GAME* game);

struct ac_npc_soncho2 {
    NPC_ACTOR npc_class;
    /* 0x994 */ aEV_SONCHO2_PROC _994;
    /* 0x998 */ lbRTC_year_t year;
    /* 0x99a */ lbRTC_month_t month;
    /* 0x99b */ lbRTC_day_t day;
    /* 0x99c */ mActor_name_t item;
    /* 0x99e */ s16 timer;
#ifdef TARGET_PC
    f32 timer_accum;
#endif
    /* 0x9a0 */ s16 center_x;
    /* 0x9a2 */ s16 center_z;
    /* 0x9a4 */ s16 goal_x;
    /* 0x9a6 */ s16 goal_z;
    /* 0x9a8 */ u8 think_idx;
    /* 0x9a9 */ u8 think;
    /* 0x9aa */ u8 _9aa;
    /* 0x9ab */ u8 talk;
    /* 0x9ac */ u8 _9ac;
    /* 0x9ad */ u8 melody_inst;
    /* 0x9ae */ u8 event;
};

struct ev_foot_race_data {
    u8 _0 : 1;
    int flags : 32;
};

typedef struct ev_foot_race_data aES2_FOOT_RACE_DATA;

enum soncho2_talk {
    aES2_TALK_0,
    aES2_TALK_1,
    aES2_TALK_2,
    aES2_TALK_LIGHTHOUSE_QUEST_START_1,
    aES2_TALK_LIGHTHOUSE_QUEST_START_2,
    aES2_TALK_5,
    aES2_TALK_6,
    aES2_TALK_7,
    aES2_TALK_8,
    aES2_TALK_9,
    aES2_TALK_a,
    aES2_TALK_TUG_O_WAR
};

enum soncho2_think {
    aES2_THINK_0,
    aES2_THINK_AEROBICS,
    aES2_THINK_BALL_TOSS,
    aES2_THINK_3,
    aES2_THINK_4,
    aES2_THINK_FOOT_RACE,
    aES2_THINK_LIGHTHOUSE_QUEST_START,
    aES2_THINK_7,
    aES2_THINK_8,
    aES2_THINK_9,
    aES2_THINK_a,
    aES2_THINK_b,
    aES2_THINK_c,
    aES2_THINK_d,
    aES2_THINK_TUG_O_WAR,
};

#ifdef __cplusplus
}
#endif

#endif
