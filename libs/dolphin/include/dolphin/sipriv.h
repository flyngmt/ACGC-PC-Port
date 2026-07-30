#ifndef DOLPHIN_SIPRIV
#define DOLPHIN_SIPRIV

#include "types.h"
#include "dolphin/os.h"
#include "dolphin/os/OSTime.h"
#include "dolphin/os/OSInterrupt.h"
#include "dolphin/os/OSSerial.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*SICallback)(s32 chan, u32 sr, OSContext* context);
typedef void (*SITypeAndStatusCallback)(s32 chan, u32 type);

typedef struct SIPacket {
  s32 chan;
  void* output;
  u32 outputBytes;
  void* input;
  u32 inputBytes;
  SICallback callback;
  OSTime fire;
} SIPacket;

void SIInit(void);
u32 SIGetStatus(s32 chan);

BOOL SIBusy(void);
BOOL SIIsChanBusy(s32 chan);

BOOL SITransfer(s32 chan, void* output, u32 outputBytes, void* input, u32 inputBytes,
                SICallback callback, OSTime delay);
u32 SISync(void);

void SISetCommand(s32 chan, u32 command);
u32 SIGetCommand(s32 chan);
void SITransferCommands(void);
u32 SISetXY(u32 x, u32 y);
u32 SIEnablePolling(u32 poll);
u32 SIDisablePolling(u32 poll);
BOOL SIGetResponse(s32 chan, void* data);

BOOL SIRegisterPollingHandler(__OSInterruptHandler handler);
BOOL SIUnregisterPollingHandler(__OSInterruptHandler handler);

u32 SIGetType(s32 chan);
u32 SIGetTypeAsync(s32 chan, SITypeAndStatusCallback callback);
u32 SIDecodeType(u32 type);

#ifdef __cplusplus
}
#endif

#endif
