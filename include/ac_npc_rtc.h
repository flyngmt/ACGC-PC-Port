#ifndef AC_NPC_RTC_H
#define AC_NPC_RTC_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct actor_npc_rtc_s NPC_RTC_ACTOR;

typedef void (*aNRTC_PROC)(NPC_RTC_ACTOR* rtc, GAME_PLAY* play);

struct actor_npc_rtc_s {
    NPC_ACTOR npc_class;
    int talk_idx;
    int unk998;
    aNRTC_PROC talk_proc;
    int talk_flag;
    int unk9A4;
    int think_idx;
    f32 counter;
    f32 fade_timer;
    f32 bgm_timer;
    f32 first_talk_timer;
};

extern ACTOR_PROFILE Npc_Rtc_Profile;

#ifdef __cplusplus
}
#endif

#endif
