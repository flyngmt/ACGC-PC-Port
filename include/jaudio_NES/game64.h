#ifndef GAME64_H
#define GAME64_H

#include "types.h"
#include "libc/stdarg.h"

#ifdef __cplusplus
extern "C" {
#endif

f32 distance2vol4KITEKI(f32);
f32 distance2vol4MD(f32);

extern void Na_InitAudio(void (*fatal_callback)(), u8* load_addr, size_t load_size, u8* bootsound,
                         size_t bootsound_size, BOOL cut_flag);
extern void Na_GameFrame();
extern void Na_Reset();
extern void Na_SoftReset();
extern void Na_Tenki(u8);
extern void Na_BgmStart(u8);
extern void Na_BgmCrossfadeStart(u8);
extern void Na_BgmStop(u16);
extern void Na_SysTrgStart(u16);
extern void Na_PlyWalkSe(u16 id, u16 angle, f32 distance);
extern void Na_PlyWalkSeRoom(u8 a, u16 angle, f32 distance);
extern void Na_NpcWalkSe(u16 id, u16 angle, f32 distance);
extern void Na_NpcWalkSeRoom(u8 index, u16 angle, f32 distance);
extern void Na_PlayerStatusLevel(u8 playerDash, f32 playerSpeed);
extern void Na_VoiceSe(u8, u8, u8, s16, u8, u8);
extern void Na_MessageStatus(u8 messageStatus);
extern void Na_MessageSpeed(u8 messageSpeed);
extern u8 Na_MessageSpeedGet();
extern void Na_OngenPos(uintptr_t id, u8 index, u16 angle, f32 distance);
extern void Na_OngenTrgStartSpeed(u16 num, u16 angle, f32 distance, f32 speed);
extern void Na_OngenTrgStart(u16 a, u16 angle, f32 distance);
extern void Na_SetOutMode(u8 outMode);
extern void Na_SetVoiceMode(u8);
extern void Na_FloorTrgStart(u8 index, u16 angle, f32 distance);
extern void Na_SysLevStart(u8);
extern void Na_SysLevStop(u8);
extern void Na_Pause(u8 pauseFlag);
extern void Na_RhythmPos(u32 index, u8 unused, u16 angle, f32 distance);
extern void Na_SpecChange(int);
extern void Na_MDPlayerPos(u16 angle, f32 distance, u16 b, u16 c, u32 id);
extern void Na_BGMVolume(f32 volumeScale, u16 b);
extern void Na_RestartPrepare();
extern u8 Na_CheckRestartReady();
extern void Na_Restart();
extern u8 Na_SubGameOK();
extern void Na_KishaStatusTrg(u8);
extern void Na_KishaStatusLevel(f32 speed, uintptr_t ongenNum1, u16 angle1, f32 distance1, uintptr_t ongenNum2, u16 angle2,
                                f32 distance2);
extern void Na_TTKK_ARM(u8);
extern void Na_BgmMuteClear();
extern u8 Na_BgmFadeoutCheck();
extern u8 Na_SeFadeoutCheck();
extern void Na_BgmTrOn(u8 subTrack);
extern void Na_BgmTrOff(u8 subTrack);
extern void Na_SubGameStart();
extern void Na_SubGameEnd();
extern void Na_SceneMode(u8);
extern u8 Na_RoomIncectPos(int insectID, u8 index, u16 angle, f32 distance);
extern void Na_FurnitureInstPos(int id, u16 angle, f32 distance);
extern void Na_TrgSeEcho(u8 echo);
extern void Na_LevSeEcho(u8 echo);
extern void Na_BGMFilter(u8 filterStatus);
extern void Na_RoomType(u8 roomType);
extern u8 Na_CheckNeosBoot();
extern void Na_Museum(u8 museumType);
extern int Na_GetSoundFrameCounter();
extern void Na_kazagurumaLevel(f32 kazagurumaSpeed);

// __declspec(weak) extern int OSAttention(const char* msg, ...) {
//     va_list marker;

//     va_start(marker, msg);

//     return vprintf(msg, marker);
// }

extern u8 sou_now_bgm_handle;
extern u8 sou_chime_status;

#ifdef __cplusplus
}
#endif

#endif
