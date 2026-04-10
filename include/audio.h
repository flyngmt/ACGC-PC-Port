#ifndef AUDIO_H
#define AUDIO_H

#include "types.h"
#include "audio_defs.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(TempoBeat_c) == 2 */
typedef struct audio_tempo_beat_s {
    /* 0x00 */ u8 tempo;
    /* 0x01 */ s8 beat;
} TempoBeat_c;

/* sizeof(StaffRollInfo_c) == 0x18 */
typedef struct audio_staffroll_info_s {
    /* 0x00 */ s16 staffroll_part;
    /* 0x02 */ s16 _01;
    /* 0x08 */ f64 percent;
    /* 0x10 */ s8 mouth_num;
    /* 0x11 */ s8 blink_flag;
    /* 0x12 */ s8 beat;
} StaffRollInfo_c;

typedef struct radio_s {
    /* 0x000 */ s8 measure;
    /* 0x004 */ f32 measure_progress;
    /* 0x008 */ u16 tempo;
} Radio_c;

enum {
    STAFFROLL_PART_START,
    STAFFROLL_PART_INTRO,
    STAFFROLL_PART_MAIN,
    STAFFROLL_PART_FADEOUT,
    STAFFROLL_PART_FINISH,

    STAFFROLL_PART_NUM
};

enum {
    VOICE_STATUS_NORMAL,
    VOICE_STATUS_ANGRY,
    VOICE_STATUS_SAD,
    VOICE_STATUS_FUN,
    VOICE_STATUS_SLEEPY,
    VOICE_STATUS_GLOOMY,

    VOICE_STATUS_NUM
};

extern void sAdo_Calc_MicPosition_forTrig(f32* fcalc, u16* scalc, const xyz_t* pos);
extern void sAdo_Calc_MicPosition_forLevel(f32* fcalc, u16* scalc, const xyz_t* pos);

extern void sAdo_GameFrame();
extern void sAdo_BgmStart(u8 id);
extern void sAdo_BgmStop(u16 id);
extern void sAdo_SysTrgStart(u16 id);

extern void sAdo_PlyWalkSe(u16 walk, const xyz_t* pos);
extern void sAdo_PlyWalkSeRoom(u8 walk, const xyz_t* pos);
extern void sAdo_NpcWalkSe(u16 se_no, const xyz_t* pos);
extern void sAdo_NpcWalkSeRoom(u8 se_no, const xyz_t* pos);

extern void sAdo_PlayerStatusLevel(u8 dash, f32 speed);

/* Not sure about the last param name */
extern void sAdo_VoiceSe(u8 num, u8 num2, u8 num3, s16 character_idx, u8 scale, u8 mode);

extern void sAdo_Inst(u16 num, u8* p);
extern void sAdo_MessageStatus(u8 status);
extern void sAdo_MessageSpeed(u8 speed);
extern u8 sAdo_MessageSpeedGet();

extern void sAdo_SysLevStop(u8 id);
extern void sAdo_SysLevStart(u8 id);

extern void sAdo_OngenPos(uintptr_t p1, u8 p2, const xyz_t* pos);
extern void sAdo_OngenTrgStart(u16 id, const xyz_t* pos);

extern void sAdo_SetOutMode(u8 mode);
extern void sAdo_SetVoiceMode(u8 mode);

extern void sAdo_FloorTrgStart(u8 id, const xyz_t* pos);

extern void sAdo_RhythmStart(u32 id, s8 type, s8 wait);
extern void sAdo_RhythmStop(u32 id);
extern void sAdo_RhythmAllStop();

extern void sAdo_FurnitureInst(u32 id, u8 inst, u8* melody, const xyz_t* pos);
extern void sAdo_Pause(u8 mode);

extern f32 sAdo_GetRhythmAnimCounter(u32 id);
extern s8 sAdo_GetRhythmDelay(u32 id);
extern void sAdo_GetRhythmInfo(TempoBeat_c* rhythm);
extern void sAdo_SetRhythmInfo(TempoBeat_c* rhythm);

extern s8 sAdo_InstCountGet();

extern void sAdo_RhythmPos(u32 id, u8 haniwa_id, const xyz_t* pos);

extern void sAdo_SpecChange(int spec);
extern void sAdo_MDPlayerPos(const xyz_t* pos, u16 s1, u16 s2, u32 p);

extern void sAdo_BGMVolume(f32 f, u16 volume);
extern void sAdo_BgmCrossfadeStart(u8 b);

extern void sAdo_SubGameStart();
extern void sAdo_SubGameEnd();
extern int sAdo_SubGameOK();

extern void sAdo_Tenki(u8 mode);

extern void sAdos_KishaStatusTrg(u8 state);
extern void sAdos_KishaStatusLevel(f32 speed, uintptr_t ongenNum1, f32 distance1, u16 angle1, uintptr_t ongenNum2,
                                   f32 distance2, u16 angle2);

extern int sAdos_GetRadioCounter(Radio_c* radio);
extern void sAdos_GetKappaCounter(void* p);
extern void sAdos_GetStaffRollInfo(StaffRollInfo_c* info);

extern void sAdos_TTKK_ARM(u8 mode);

extern void sAdo_OngenTrgStartSpeed(f32 speed, u16 s1, const xyz_t* pos);

extern void sAdo_TrgSeEcho(u8 b);
extern void sAdo_LevSeEcho(u8 b);

extern u8 sAdo_BgmFadeoutCheck();
extern u8 sAdo_SeFadeoutCheck();

extern void sAdo_RoomType(u8 type);
extern void sAdo_Museum(u8 type);

extern void sAdo_SoftReset();

extern u16 sAdo_Get_WalkLabel(int type);
extern u16 sAdo_Get_KokeruLabel(int type);

extern void sAdo_SceneMode(u8 mode);
extern u8 sAdo_RoomIncectPos(u32 f, u8 u, const xyz_t* pos);

extern void sAdo_FurnitureInstPos(u32 id, const xyz_t* pos);
extern void sAdo_Set_ongenpos_refuse_fg(int state);

extern int sAdo_GameframeEnd_Check();
extern u32 sAdo_GetSoundFrameCounter();

extern int sAdo_CheckOnPlussBridge(const xyz_t* pos, u32 atr);
extern void sAdo_RegistPlussBridge(const xyz_t* pos);
extern void sAdo_DeletePlussBridge();

extern void sAdo_kazagurumaLevel(f32 level);

#ifdef __cplusplus
}
#endif

#endif
