#ifndef SUB_SYS_H
#define SUB_SYS_H

#include "types.h"
#include "jaudio_NES/audiowork.h"
#include "PR/mbi.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void Nap_AudioPortInit(void);
extern void Nap_SetF32(u32 cmd, f32 param);
extern void Nap_SetS32(u32 cmd, s32 param);
#ifdef TARGET_PC
extern void Nap_SetPtr(u32 cmd, void* ptr);
#endif
extern void Nap_SetS8(u32 cmd, s8 param);
extern void Nap_SetU16(u32 cmd, u16 param);
extern s32 Nap_SendStart(void);
extern void Nap_FlushPort(void);
extern void Nap_Process1Command(AudioPort* port);
extern void Nap_AudioPortProcess(u32 msg);
extern s32 Nap_CheckSpecChange(void);
extern s32 Nap_StartSpecChange(s32 spec_id);
extern s32 Nap_StartReset(void);
extern s8 Nap_ReadSubPort(s32 groupId, s32 subtrackId, s32 portId);
extern s8 Nap_ReadGrpPort(s32 groupId, s32 portId);
extern void Nap_WaitVsync(void);
extern u32 Nap_GetRandom(void);
extern void Nas_InitGAudio(void);
extern s32 CreateAudioTask(Acmd* cmds, s16* pSamples, u32 nSamples, s32 param_4);

#ifdef __cplusplus
}
#endif

#endif
