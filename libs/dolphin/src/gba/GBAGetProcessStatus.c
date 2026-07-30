#include "GBA/GBAPriv.h"
#include "dolphin/os/OSInterrupt.h"
#include "dolphin/os/OSTime.h"

s32 GBAGetProcessStatus(s32 chan, u8* percentp) {
    BOOL enabled; // r26
    s32 ret; // r29
    GBAControl* gba = &__GBA[chan]; // r25
    GBABootInfo* bootInfo; // r31
    u8 percent; // r30
    OSTime t; // r27

    bootInfo = &__GBA[chan].bootInfo;
    enabled = OSDisableInterrupts();
    if (bootInfo->callback != NULL) {
        ret = GBA_BUSY;
        percent = (bootInfo->curOffset * 100) / bootInfo->realLength;
        if (bootInfo->begin != 0) {
            t = OSGetTime() - bootInfo->begin;
            if (OSTicksToMilliseconds(t) < 5500) {
                percent = (percent * t) / OSMillisecondsToTicks(5500ll);
            }

            if (percent >= 100) {
                percent = 100;
            }
        }

        if (percentp != NULL) {
            *percentp = percent;
        }
    } else if (gba->callback != NULL) {
        ret = GBA_BUSY;
    } else {
        ret = GBA_READY;
    }

    OSRestoreInterrupts(enabled);
    return ret;
}
