#ifndef _DOLPHIN_EXI_H_
#define _DOLPHIN_EXI_H_

#include <dolphin/os/OSContext.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    EXI_STATE_DMA_ACCESS = (1 << 0),
    EXI_STATE_IMM_ACCESS = (1 << 1),
    EXI_STATE_SELECTED = (1 << 2),
    EXI_STATE_ATTACHED = (1 << 3),
    EXI_STATE_LOCKED = (1 << 4),
    EXI_STATE_BUSY = EXI_STATE_DMA_ACCESS | EXI_STATE_IMM_ACCESS
} EXIState;

typedef enum {
    EXI_CHAN_0,
    EXI_CHAN_1,
    EXI_CHAN_2,
    EXI_MAX_CHAN
} EXIChannel;

typedef enum {
    EXI_READ,
    EXI_WRITE,
    EXI_TYPE_2,
    EXI_MAX_TYPE
} EXIType;

typedef void (*EXICallback)(s32 chan, OSContext *context);

EXICallback EXISetExiCallback(s32 channel, EXICallback callback);

void EXIInit(void);
BOOL EXILock(s32 channel, u32 device, EXICallback callback);
BOOL EXIUnlock(s32 channel);
BOOL EXISelect(s32 channel, u32 device, u32 frequency);
BOOL EXIDeselect(s32 channel);
BOOL EXIImm(s32 channel, void *buffer, s32 length, u32 type, EXICallback callback);
BOOL EXIImmEx(s32 channel, void *buffer, s32 length, u32 type);
BOOL EXIDma(s32 channel, void *buffer, s32 length, u32 type, EXICallback callback);
BOOL EXISync(s32 channel);
BOOL EXIProbe(s32 channel);
s32 EXIProbeEx(s32 channel);
BOOL EXIAttach(s32 channel, EXICallback callback);
BOOL EXIDetach(s32 channel);
u32 EXIGetState(s32 channel);
s32 EXIGetID(s32 channel, u32 device, u32* id);
void EXIProbeReset(void);

#ifdef __cplusplus
}
#endif

#endif
