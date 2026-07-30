#ifndef _DOLPHIN_OSSERIAL_H
#define _DOLPHIN_OSSERIAL_H

#include <dolphin/hw_regs.h>

#define CHAN_NONE -1

#define SI_MAX_CHAN 4

#define SI_MAX_TYPE 4

#define SI_COMCSR_IDX 13
#define SI_STATUS_IDX 14

#define SI_COMCSR_TCINT_MASK       (1 << 31)
#define SI_COMCSR_TCINTMSK_MASK    (1 << 30)
#define SI_COMCSR_COMERR_MASK      (1 << 29)
#define SI_COMCSR_RDSTINT_MASK     (1 << 28)
#define SI_COMCSR_RDSTINTMSK_MASK  (1 << 27)
// 4 bits of padding
#define SI_COMCSR_OUTLNGTH_MASK    (1 << 22) \
                                 | (1 << 21) \
                                 | (1 << 20) \
                                 | (1 << 19) \
                                 | (1 << 18) \
                                 | (1 << 17) \
                                 | (1 << 16)
// 1 bit of padding
#define SI_COMCSR_INLNGTH_MASK     (1 << 14) \
                                 | (1 << 13) \
                                 | (1 << 12) \
                                 | (1 << 11) \
                                 | (1 << 10) \
                                 | (1 << 9)  \
                                 | (1 << 8)
// 5 bits of padding
#define SI_COMCSR_CHANNEL_MASK     (1 << 2) \
                                 | (1 << 1)
#define SI_COMCSR_TSTART_MASK      (1 << 0)

#define ROUND(n, a) (((u32)(n) + (a)-1) & ~((a)-1))

typedef void (*SICallback)(s32, u32, OSContext*);

typedef struct SIControl {
    s32 chan;
    u32 poll;
    u32 inputBytes;
    void* input;
    SICallback callback;
} SIControl;

typedef struct SIPacket {
    s32 chan;
    void* output;
    u32 outputBytes;
    void* input;
    u32 inputBytes;
    SICallback callback;
    OSTime fire;
} SIPacket;

typedef void (*SITypeCallback)(s32, u32);

BOOL SIBusy();
BOOL SIIsChanBusy(s32 chan);
void SIInit();
unsigned long SISync();
u32 SIGetStatus(s32 chan);
void SISetCommand(long chan, unsigned long command);
unsigned long SIGetCommand(long chan);
void SITransferCommands();
unsigned long SISetXY(unsigned long x, unsigned long y);
unsigned long SIEnablePolling(unsigned long poll);
unsigned long SIDisablePolling(unsigned long poll);
BOOL SIGetResponse(s32 chan, void * data);
int SITransfer(long chan, void * output, unsigned long outputBytes, void * input, unsigned long inputBytes, 
                void (* callback)(long, unsigned long, struct OSContext *), long long time);
BOOL SIRegisterPollingHandler(__OSInterruptHandler handler);
BOOL SIUnregisterPollingHandler(__OSInterruptHandler handler);
u32 SIGetType(s32 chan);
u32 SIGetTypeAsync(s32 chan, SITypeCallback callback);
u32 SIProbe(s32 chan);
char* SIGetTypeString(u32 type);

// SISamplingRate.c
void SISetSamplingRate(u32 msec);
void SIRefreshSamplingRate(void);

#if DEBUG
void __SITestSamplingRate(u32 tvmode);
#endif

extern u32 __PADFixBits;

#endif // _DOLPHIN_OSSERIAL_H
