#include "gba/gbaPriv.h"
#include <dolphin/os.h>

// local declarations
static BOOL OnReset(BOOL final);

//.data
static OSResetFunctionInfo ResetFunctionInfo = {OnReset, 127, NULL, NULL};

//.bss
static GBASecParam SecParams[4];
GBAControl __GBA[4];

//.sbss
BOOL __GBAReset;

static void ShortCommandProc(s32 chan) {
    GBAControl* gba = &__GBA[chan]; // r31

    if (gba->ret != 0) {
        return;
    }

    if (gba->input[0] != 0 || gba->input[1] != 4) {
        gba->ret = 1;
        return;
    }
    
    *gba->status = gba->input[2] & GBA_JSTAT_MASK;
}

void GBAInit(void) {
    GBAControl* gba; // r31
    s32 chan; // r30

    for (chan = 0; chan < 4; chan++) {
        gba = &__GBA[chan];
        gba->delay = OSMicrosecondsToTicks(60);
        OSInitThreadQueue(&gba->threadQueue);
        gba->param = &SecParams[chan];
        ASSERTLINE(90, (u32) gba->param % 32 == 0);
    }

    OSInitAlarm();
    DSPInit();

    __GBAReset = FALSE;
    OSRegisterResetFunction(&ResetFunctionInfo);
}

s32 GBAGetStatusAsync(s32 chan, u8* status, GBACallback callback) {
    GBAControl* gba = &__GBA[chan]; // r31

    if (gba->callback != NULL) {
        return GBA_BUSY;
    }

    gba->output[0] = 0;
    gba->status = status;
    gba->callback = callback;
    return __GBATransfer(chan, 1, 3, ShortCommandProc);
}

s32 GBAGetStatus(s32 chan, u8* status) {
    GBAControl* gba = &__GBA[chan]; // r1+0x10
    s32 ret; // r31

    ret = GBAGetStatusAsync(chan, status, &__GBASyncCallback);
    if (ret != GBA_READY) {
        return ret;
    }
    return __GBASync(chan);
}

s32 GBAResetAsync(s32 chan, u8* status, GBACallback callback) {
    GBAControl *gba = &__GBA[chan]; // r31

    if (gba->callback != NULL) {
        return GBA_BUSY;
    }

    gba->output[0] = 0xFF;
    gba->status = status;
    gba->callback = callback;
    return __GBATransfer(chan, 1, 3, ShortCommandProc);
}

s32 GBAReset(s32 chan, u8* status) {
    GBAControl* gba = &__GBA[chan]; // r1+0x10
    s32 ret; // r31

    ret = GBAResetAsync(chan, status, (GBACallback)&__GBASyncCallback);
    if (ret != GBA_READY) {
        return ret;
    }
    return __GBASync(chan);
}

static BOOL OnReset(BOOL final) {
    __GBAReset = TRUE;
    return TRUE;
}
