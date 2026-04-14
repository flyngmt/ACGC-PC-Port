#ifndef AC_WEATHER_H
#define AC_WEATHER_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

#define WEATHER_PRV_COUNT 100
#define WEATHER_PRV_NO_EXIST_ID -1
#define WEATHER_PRV_HOLD_TIMER -100

extern int aWeather_ChangingWeather();
extern void aWeather_RequestChangeWeatherToIsland();
extern void aWeather_RequestChangeWeatherFromIsland();

extern ACTOR_PROFILE Weather_Profile;

typedef struct ac_weather_priv_s {
    xyz_t pos;
    xyz_t speed;
    f32 currentY;
    f32 unk1C;
    float timer;
    s16 work[5];
    u8 use;
    u8 id;
    u8 status;
} aWeather_Priv;

typedef struct weather_actor_s WEATHER_ACTOR;

typedef void (*CHANGE_WEATHER_PROC)(ACTOR* actorx, s16 status, s16 level);
typedef int (*GET_WEATHER_PRV_NUM)(ACTOR* actorx);
typedef void (*REMOVE_WEATHER_PRV)(ACTOR* actorx, int id);
typedef aWeather_Priv* (*GET_WEATHER_PRV)(u8 status, s16 timer, xyz_t* pos, xyz_t* speed, ACTOR* weather, int id);
typedef int (*WEATHER_SOUND_EFFECT)();
typedef void (*CHANGE_WEATER_INSTANCE_PROC)(ACTOR* actorx, s16 status, s16 level);

typedef struct ac_weather_clip_s {
    ACTOR* actor;
    CHANGE_WEATHER_PROC change_weather;
    GET_WEATHER_PRV_NUM get_priv_num;
    REMOVE_WEATHER_PRV remove_priv;
    GET_WEATHER_PRV get_priv;
    WEATHER_SOUND_EFFECT stop_sound;
    WEATHER_SOUND_EFFECT start_sound;
    CHANGE_WEATER_INSTANCE_PROC change_weather_instance;
} aWeather_Clip_c;

typedef void (*MK_WEATHER_PROC)(ACTOR*, GAME*);
typedef void (*CT_WEATHER_PROC)(aWeather_Priv*, GAME*);
typedef void (*MV_WEATHER_PROC)(aWeather_Priv*, GAME*);
typedef void (*MT_WEATHER_PROC)(aWeather_Priv*, GAME*);
typedef void (*ST_WEATHER_PROC)(GAME*);
typedef void (*DW_WEATHER_PROC)(aWeather_Priv*, GAME*);

typedef struct ac_weather_profile_s {
    MK_WEATHER_PROC make;
    CT_WEATHER_PROC constructor;
    MV_WEATHER_PROC move;
    ST_WEATHER_PROC set;
    DW_WEATHER_PROC draw;
} aWeather_Profile_c;

struct weather_actor_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ aWeather_Profile_c* current_profile;
    /* 0x178 */ s16 current_status;
    /* 0x17A */ s16 next_status;
    /* 0x17C */ float counter;
    /* 0x17E */ s16 current_level;
    /* 0x180 */ s16 current_aim_level;
    /* 0x182 */ s16 next_level;
    /* 0x184 */ u8* ptr;
    /* 0x188 */ xyz_t pos;
    /* 0x194 */ aWeather_Priv* priv;
    /* 0x198 */ void* t;
    /* 0x19C */ u8 request_change;
    /* 0x19E */ s16 unk19E;
    /* 0x1A0 */ aWeather_Clip_c clip;
    /* 0x1C0 */ float timer;
    /* 0x1C2 */ float timer2;
    /* 0x1C4 */ xyz_t wind_info;
    /* 0x1D0 */ float lightning_timer;
    /* 0x1D2 */ float lightning_timer2;
    /* 0x1D4 */ s16 current_sound_effect;
    /* 0x1D6 */ s16 umbrella_flag;
    /* 0x1D8 */ s16 current_yAngle;
    /* 0x1DA */ s16 sound_flag;
    /* 0x1DC */ s16 start_sound_effect;
    /* 0x1DE */ s16 stop_sound_effect;
    /* 0x1E0 */ s16 basement_event;
};

#ifdef __cplusplus
}
#endif

#endif
