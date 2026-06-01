#ifndef SYSTEM_H
#define SYSTEM_H

#include "types.h"
#include "libultra/libultra.h"

#define REFRESH_RATE_DEVIATION_NTSC 1.00278f
#define REFRESH_RATE_NTSC 60

typedef enum SET_EXT_POINTER_TYPE {
    EXT_POINTER_TYPE_ADDR,
    EXT_POINTER_TYPE_SIZE,

    EXT_POINTER_TYPE_NUM
} SET_EXT_POINTER_TYPE;

typedef s32 (*Na_DmaProc)(OSPiHandle* handle, OSIoMesg* mb, s32 direction);
typedef void* (*Na_SyncProc)(u8* param0, s32 param1);

#ifdef __cplusplus
extern "C" {
#endif

extern void* Nas_WaveDmaCallBack(uintptr_t device_addr, u32 size, s32 arg2, u8* waveload_idx, s32 medium);
extern void Nas_InitAudio(u64* acmdBuf, s32 acmdBufSize);
extern void Nas_FastCopy(u8* SrcAddr, u8* DestAdd, size_t Length, s32 medium);
extern void Nas_FastDiskCopy(u8* SrcAddr, u8* DestAdd, size_t Length, s32 medium);
extern s32 Nas_StartMySeq(s32 group, s32 seq, s32 arg);
extern s32 Nas_StartSeq_Skip(s32 group, s32 seq, s32 skip_ticks);

extern s32 Nas_LoadVoice(s32 progId, s32 instId, s32 percId);

extern void Nas_PreLoadSeq(s32 seq, s32 flags, s32 param, OSMesgQueue* mq);

extern s32 Nas_PreLoadWave_BG(s32 bankId, s32 param2, s32 param3, OSMesgQueue* mq);
extern s32 Nas_PreLoadBank_BG(s32 bankId, s32 param2, s32 param3, OSMesgQueue* mq);
extern s32 Nas_PreLoadSeq_BG(s32 seqId, s32 param2, s32 param3, OSMesgQueue* mq);

extern void Nas_FlushBank(s32 seqId);
extern u8 Nas_MapHeaderReadByte(s32 byteIndex);

extern void Nas_SetExtPointer(s32 type, s32 idx, s32 set_type, uintptr_t param);

extern void Nas_WaveDmaFrameWork(void);
extern void Nas_BgDmaFrameWork(s32 reset_status);
extern void MK_FrameWork(void);

extern BOOL Nas_CheckIDseq(s32 id);
extern BOOL Nas_CheckIDbank(s32 id);

extern void Nas_WriteIDseq(s32 id, s32 type);
extern void Nas_WriteIDbank(s32 id, s32 type);

extern s32 VoiceLoad(s32 bank_id, u32 inst_id, s8* done_p);
extern s32 SeqLoad(s32 seq_id, u8* ram_addr, s8* done_p);
extern void MK_load(s32 type, s32 id, u8* done_p);

extern void LpsInit(void);
extern void LpsDma(s32 reset_status);

extern s32 Nas_CheckBgWave(s32 reset_status);
extern void Nas_BgCopyMain(s32 reset_status);

extern void EmemReload(void);
extern void Nas_BgCopyInit(void);
extern void MK_Init(void);
extern void Nas_WaveDmaNew(s32 n_channels);

extern Na_SyncProc NA_SYNC_PROC;
extern BOOL AUDIO_SYSTEM_READY;
extern Na_DmaProc NA_DMA_PROC;

#ifdef TARGET_PC
struct envdat_;
void pc_swap_envdat(struct envdat_* env);
void pc_swap_envdat_seq(struct envdat_* env);
void pc_reset_envdat_visited(void);
#endif
extern OSMesgQueue MK_QUEUE;
extern OSMesg MK_QBUF[];
extern u8* MK_RMES[];

#ifdef __cplusplus
}
#endif

#endif
