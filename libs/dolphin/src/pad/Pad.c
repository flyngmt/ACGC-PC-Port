#include <dolphin.h>
#include <dolphin/pad.h>
#include <dolphin/si.h>

#include "os/__os.h"

// functions
static void DoReset();
static void PADEnable(s32 chan);
static void PADProbeCallback(s32 chan, u32 error, OSContext *context);
static void PADDisable(s32 chan);
static void UpdateOrigin(s32 chan);
static void PADOriginCallback(s32 chan, u32 error, OSContext *context);
int PADReset(u32 mask);
BOOL PADRecalibrate(u32 mask);
BOOL PADInit();
static void PADReceiveCheckCallback(s32 chan, u32 error);
u32 PADRead(PADStatus* status);
void PADSetSamplingRate(u32 msec);
void __PADTestSamplingRate(u32 tvmode);
void PADControlAllMotors(const u32 *commandArray);
void PADControlMotor(s32 chan, u32 command);
void PADSetSpec(u32 spec);
u32 PADGetSpec();
static void SPEC0_MakeStatus(s32 chan, PADStatus *status, u32 data[2]);
static void SPEC1_MakeStatus(s32 chan, PADStatus *status, u32 data[2]);
static s8 ClampS8(s8 var, s8 org);
static u8 ClampU8(u8 var, u8 org);
static void SPEC2_MakeStatus(s32 chan, PADStatus *status, u32 data[2]);
BOOL PADGetType(s32 chan, u32 * type);
BOOL PADSync(void);
void PADSetAnalogMode(u32 mode);
static BOOL OnReset(BOOL f);
static void PADTypeAndStatusCallback(s32 chan, u32 type);
void __PADDisableXPatch(void);
BOOL __PADDisableRecalibration(BOOL disable);

#define LATENCY 8

#define PAD_ALL                                                                                                        \
    (PAD_BUTTON_LEFT | PAD_BUTTON_RIGHT | PAD_BUTTON_DOWN | PAD_BUTTON_UP | PAD_TRIGGER_Z | PAD_TRIGGER_R              \
     | PAD_TRIGGER_L | PAD_BUTTON_A | PAD_BUTTON_B | PAD_BUTTON_X | PAD_BUTTON_Y | PAD_BUTTON_MENU | 0x2000 | 0x0080)

u16 __OSWirelessPadFixMode : 0x800030E0;


static BOOL Initialized; // size: 0x4, address: 0x0
static u32 EnabledBits; // size: 0x4, address: 0x4
static u32 ResettingBits; // size: 0x4, address: 0x8
static s32 ResettingChan = 0x00000020; // size: 0x4, address: 0x0
static u32 RecalibrateBits; // size: 0x4, address: 0x10
static u32 WaitingBits; // size: 0x4, address: 0x14
static u32 CheckingBits; // size: 0x4, address: 0x18
static u32 PendingBits;
static u32 XPatchBits = PAD_CHAN0_BIT | PAD_CHAN1_BIT | PAD_CHAN2_BIT | PAD_CHAN3_BIT;
static u32 AnalogMode = 0x00000300; // size: 0x4, address: 0x4
static u32 Spec = 0x00000005; // size: 0x4, address: 0x8
static void (* MakeStatus)(long, struct PADStatus *, u32 *) = SPEC2_MakeStatus; // size: 0x4, address: 0xC

static u32 Type[PAD_MAX_CONTROLLERS]; // size: 0x10, address: 0x0
static PADStatus Origin[PAD_MAX_CONTROLLERS]; // size: 0x30, address: 0x10
static u32 CmdTypeAndStatus;
static u32 CmdReadOrigin = 0x41000000;
static u32 CmdCalibrate = 0x42000000;
static u32 CmdProbeDevice[PAD_MAX_CONTROLLERS];

static OSResetFunctionInfo ResetFunctionInfo = {
    OnReset,
    127,
    NULL,
    NULL,
};

static PADSamplingCallback SamplingCallback;

static void PADEnable(s32 chan) {
    u32 cmd;
    u32 chanBit;
    u32 data[2];

    chanBit = 0x80000000 >> chan;
    EnabledBits |= chanBit;
    SIGetResponse(chan, &data);
    // ASSERTLINE(0x1C4, !(Type[chan] & RES_WIRELESS_LITE));
    cmd = (AnalogMode | 0x400000);
    SISetCommand(chan, cmd);
    SIEnablePolling(EnabledBits);
}

static void PADDisable(s32 chan) {
    int enabled;
    u32 chanBit;

    enabled = OSDisableInterrupts();
    chanBit = 0x80000000 >> chan;
    SIDisablePolling(chanBit);
    EnabledBits &= ~chanBit;
    WaitingBits &= ~chanBit;
    CheckingBits &= ~chanBit;
    PendingBits &= ~chanBit;
    OSSetWirelessID(chan, 0);
    OSRestoreInterrupts(enabled);
}

static void DoReset() {
    u32 chanBit;

    ResettingChan = __cntlzw(ResettingBits);
    if (ResettingChan != 32) {
        ASSERTLINE(520, 0 <= ResettingChan && ResettingChan < SI_MAX_CHAN);
        chanBit = (0x80000000 >> ResettingChan);
        ResettingBits &= ~chanBit;
        memset(&Origin[ResettingChan], 0, 0xC);
        SIGetTypeAsync(ResettingChan, &PADTypeAndStatusCallback);
    }
}

static void UpdateOrigin(s32 chan) {
    PADStatus *origin;
    u32 chanBit;

    chanBit = 0x80000000 >> chan;
    origin = &Origin[chan];
    switch (AnalogMode & 0x00000700u)
    {
    case 0x00000000u:
    case 0x00000500u:
    case 0x00000600u:
    case 0x00000700u:
        origin->triggerLeft &= ~15;
        origin->triggerRight &= ~15;
        origin->analogA &= ~15;
        origin->analogB &= ~15;
        break;
    case 0x00000100u:
        origin->substickX &= ~15;
        origin->substickY &= ~15;
        origin->analogA &= ~15;
        origin->analogB &= ~15;
        break;
    case 0x00000200u:
        origin->substickX &= ~15;
        origin->substickY &= ~15;
        origin->triggerLeft &= ~15;
        origin->triggerRight &= ~15;
        break;
    case 0x00000300u: break;
    case 0x00000400u: break;
    }

    origin->stickX -= 128;
    origin->stickY -= 128;
    origin->substickX -= 128;
    origin->substickY -= 128;

    if ((XPatchBits & chanBit) != 0 && origin->stickX > 64 && (SIGetType(chan) & 0xFFFF0000) == SI_GC_CONTROLLER) {
        origin->stickX = 0;
    }
}

static void PADOriginCallback(s32 chan, u32 error, OSContext *context) {
    ASSERTLINE(602, 0 <= ResettingChan && ResettingChan < SI_MAX_CHAN);
    ASSERTLINE(603, chan == ResettingChan);
    if (!(error & (SI_ERROR_UNDER_RUN | SI_ERROR_OVER_RUN | SI_ERROR_NO_RESPONSE | SI_ERROR_COLLISION)))
    {
        UpdateOrigin(ResettingChan);
        PADEnable(ResettingChan);
    }
    DoReset();
}

static void PADOriginUpdateCallback(s32 chan, u32 error, OSContext *context)
{
    ASSERTLINE(632, 0 <= chan && chan < SI_MAX_CHAN);
    if (!(EnabledBits & (PAD_CHAN0_BIT >> chan)))
        return;
    if (!(error & (SI_ERROR_UNDER_RUN | SI_ERROR_OVER_RUN | SI_ERROR_NO_RESPONSE | SI_ERROR_COLLISION)))
        UpdateOrigin(chan);
    if ((error & SI_ERROR_NO_RESPONSE) != 0) {
        PADDisable(chan);
    }
}

static void PADProbeCallback(s32 chan, u32 error, OSContext *context) {
    ASSERTLINE(671, 0 <= ResettingChan && ResettingChan < SI_MAX_CHAN);
    ASSERTLINE(672, chan == ResettingChan);

    ASSERTLINE(674, (Type[chan] & SI_WIRELESS_CONT_MASK) == SI_WIRELESS_CONT && !(Type[chan]  & SI_WIRELESS_LITE));
    if (!(error & (SI_ERROR_UNDER_RUN | SI_ERROR_OVER_RUN | SI_ERROR_NO_RESPONSE | SI_ERROR_COLLISION))) {
        PADEnable(ResettingChan);
        WaitingBits |= PAD_CHAN0_BIT >> ResettingChan;
    }
    
    DoReset();
}

static void PADTypeAndStatusCallback(s32 chan, u32 type) {
    u32 chanBit;
    u32 recalibrate;
    BOOL rc;
    u32 error;

    rc = TRUE;
    ASSERTLINE(707, 0 <= ResettingChan && ResettingChan < SI_MAX_CHAN);
    ASSERTLINE(708, chan == ResettingChan);

    chanBit = (0x80000000 >> ResettingChan);
    error = type & 0xFF;
    ASSERTLINE(717, !(error & SI_ERROR_BUSY));

    recalibrate = RecalibrateBits & chanBit;
    RecalibrateBits &= ~chanBit;

    if ((error & (SI_ERROR_UNDER_RUN | SI_ERROR_OVER_RUN | SI_ERROR_NO_RESPONSE | SI_ERROR_COLLISION))) {
        DoReset();
        return;
    }

    type &= ~0xFF;
    Type[ResettingChan] = type;
    if ((type & SI_TYPE_MASK) != SI_TYPE_GC || (type & SI_GC_STANDARD) == 0) {
        DoReset();
        return;
    }

    if (Spec < 2) {
        PADEnable(ResettingChan);
        DoReset();
        return;
    }

    if (!(type & 0x80000000) || (type & SI_WIRELESS_IR)) {
        if (recalibrate) {
            rc = SITransfer(ResettingChan, &CmdCalibrate, 3, &Origin[ResettingChan], 10, &PADOriginCallback, 0);
        } else {
            rc = SITransfer(ResettingChan, &CmdReadOrigin, 1, &Origin[ResettingChan], 10, &PADOriginCallback, 0);
        }
    } else if ((type & SI_WIRELESS_FIX_ID) && !(type & SI_WIRELESS_CONT_MASK) && !(type & SI_WIRELESS_LITE)) {
        if ((type & SI_WIRELESS_RECEIVED)) {
            rc = SITransfer(ResettingChan, &CmdReadOrigin, 1, &Origin[ResettingChan], 10, &PADOriginCallback, 0);
        } else {
            rc = SITransfer(ResettingChan, &CmdProbeDevice[ResettingChan], 3, &Origin[ResettingChan], 8, &PADProbeCallback, 0);
        }
    }

    if (!rc) {
        PendingBits |= chanBit;
        DoReset();
    }
}

static void PADReceiveCheckCallback(s32 chan, u32 type) {
    u32 error;
    u32 chanBit;

    chanBit = (0x80000000 >> chan);
    if ((EnabledBits & chanBit) != 0) {
        error = type & 0xFF;
        type &= ~0xFF;

        WaitingBits &= ~chanBit;
        CheckingBits &= ~chanBit;

        if (
            !(error & (SI_ERROR_UNDER_RUN | SI_ERROR_OVER_RUN | SI_ERROR_NO_RESPONSE | SI_ERROR_COLLISION)) &&
            (type & SI_GC_WIRELESS) != 0 && (type & SI_WIRELESS_FIX_ID) != 0 &&
            (type & SI_WIRELESS_RECEIVED) != 0 && !(type & SI_WIRELESS_IR) && !(type & SI_WIRELESS_CONT_MASK) && !(type & SI_WIRELESS_LITE)
        ) {
            SITransfer(chan, &CmdReadOrigin, 1, &Origin[chan], 10, &PADOriginUpdateCallback, 0);
        } else {
            PADDisable(chan);
        }
    }
}

BOOL PADReset(u32 mask) {
    BOOL enabled;
    u32 disableBits;

    ASSERTMSGLINE(858, !(mask & 0x0FFFFFFF), "PADReset(): invalid mask");
    enabled = OSDisableInterrupts();
    mask |= PendingBits;
    PendingBits = 0;
    mask = mask & ~(WaitingBits | CheckingBits);
    ResettingBits |= mask;
    disableBits = ResettingBits & EnabledBits;
    EnabledBits &= ~mask;
    if (Spec == 4) {
        RecalibrateBits |= mask;
    }
    SIDisablePolling(disableBits);
    if (ResettingChan == 0x20) {
        DoReset();
    }
    OSRestoreInterrupts(enabled);
    return TRUE;
}

BOOL PADRecalibrate(u32 mask) {
    BOOL enabled;
    u32 disableBits;

    ASSERTMSGLINE(899, !(mask & 0x0FFFFFFF), "PADReset(): invalid mask");
    enabled = OSDisableInterrupts();
    mask |= PendingBits;
    PendingBits = 0;
    mask &= ~(WaitingBits | CheckingBits);
    ResettingBits |= mask;
    disableBits = ResettingBits & EnabledBits;
    EnabledBits &= ~mask;

    if (!(__gUnknown800030E3 & 0x40)) {
        RecalibrateBits |= mask;
    }

    SIDisablePolling(disableBits);
    if (ResettingChan == 0x20) {
        DoReset();
    }
    OSRestoreInterrupts(enabled);
    return TRUE;
}

u32 __PADSpec; // size: 0x4, address: 0x20

BOOL PADInit(void) {
    s32 chan;
    OSTime time;

    if (Initialized) {
        return TRUE;
    }

    if (__PADSpec){
        PADSetSpec(__PADSpec);
    }

    Initialized = TRUE;
    if (__PADFixBits != 0) {
        time = OSGetTime();
        __OSWirelessPadFixMode
            = (u16)((((time)&0xffff) + ((time >> 16) & 0xffff) + ((time >> 32) & 0xffff) + ((time >> 48) & 0xffff))
                    & 0x3fffu);
        RecalibrateBits = PAD_CHAN_ALL_BIT;
    }

    for (chan = 0; chan < SI_MAX_CHAN; chan++) {
        CmdProbeDevice[chan] = 0x4D000000 | (chan << 22) | (__OSWirelessPadFixMode & 0x3FFF) << 8;
    }

    SIRefreshSamplingRate();
    OSRegisterResetFunction(&ResetFunctionInfo);

    return PADReset(PAD_CHAN0_BIT | PAD_CHAN1_BIT | PAD_CHAN2_BIT | PAD_CHAN3_BIT);
}

u32 PADRead(PADStatus* status) {
    BOOL enabled;
    s32 chan;
    u32 data[2];
    u32 chanBit;
    u32 sr;
    int chanShift;
    u32 motor;

    enabled = OSDisableInterrupts();
    motor = 0;

    for(chan = 0; chan < 4; chan++, status++) {
        chanBit = 0x80000000 >> chan;
        chanShift = (3 - chan) * 8;

        if (PendingBits & chanBit) {
            PADReset(0);
            status->err = -2;
            memset(status, 0, 10);
        } else if ((ResettingBits & chanBit) || (ResettingChan == chan)) {
            status->err = -2;
            memset(status, 0, 10);
        } else if (!(EnabledBits & chanBit)) {
            status->err = -1;
            memset(status, 0, 10);
        } else if (SIIsChanBusy(chan)) {
            status->err = -3;
            memset(status, 0, 10);
        } else {
            sr = SIGetStatus(chan);
            if (sr & 8) {
                SIGetResponse(chan, data);

                if (WaitingBits & chanBit) {
                    status->err = 0;
                    memset(status, 0, 10);
                    if (!(CheckingBits & chanBit)) {
                        CheckingBits |= chanBit;
                        SIGetTypeAsync(chan, &PADReceiveCheckCallback);
                    }
                } else {
                    PADDisable(chan);
                    status->err = -1;
                    memset(status, 0, 10);
                }
            } else {
                if (!(SIGetType(chan) & SI_GC_NOMOTOR)) {
                    motor |= chanBit;
                }

                if (!SIGetResponse(chan, &data)) {
                    status->err = -3;
                    memset(status, 0, 10);
                } else if ((data[0] & 0x80000000)) {
                    status->err = -3;
                    memset(status, 0, 10);
                } else {
                    MakeStatus(chan, status, data);

                    if (status->button & 0x2000) {
                        status->err = -3;
                        memset(status, 0, 10);
                        SITransfer(chan, &CmdReadOrigin, 1, &Origin[chan], 10, PADOriginUpdateCallback, 0);
                    } else {
                        status->err = 0;
                        status->button &= 0xFFFFFF7F;
                    }
                }
            }
        }
    }

    OSRestoreInterrupts(enabled);
    return motor;
}

void PADSetSamplingRate(u32 msec) {
    SISetSamplingRate(msec);
}

#if DEBUG
void __PADTestSamplingRate(u32 tvmode) {
    __SITestSamplingRate(tvmode);
}
#endif

void PADControlAllMotors(const u32 *commandArray) {
    BOOL enabled;
    int chan;
    u32 command;
    BOOL commit;
    u32 chanBit;

    enabled = OSDisableInterrupts();
    commit = FALSE;

    for (chan = 0; chan < SI_MAX_CHAN; chan++, commandArray++)
    {
        chanBit = PAD_CHAN0_BIT >> chan;
        if ((EnabledBits & chanBit) && !(SIGetType(chan) & SI_GC_NOMOTOR))
        {
            command = *commandArray;
            ASSERTMSGLINE(1162, !(command & 0xFFFFFFFC), "PADControlAllMotors(): invalid command");
            if (Spec < PAD_SPEC_2 && command == PAD_MOTOR_STOP_HARD)
                command = PAD_MOTOR_STOP;
            SISetCommand(chan, (0x40 << 16) | AnalogMode | (command & (0x00000001 | 0x00000002)));
            commit = TRUE;
        }
    }
    if (commit)
        SITransferCommands();
    OSRestoreInterrupts(enabled);
}

void PADControlMotor(s32 chan, u32 command) {
    BOOL enabled;
    u32 chanBit;

    ASSERTMSGLINE(1197, !(command & 0xFFFFFFFC), "PADControlMotor(): invalid command");

    enabled = OSDisableInterrupts();
    chanBit = PAD_CHAN0_BIT >> chan;
    if ((EnabledBits & chanBit) && !(SIGetType(chan) & SI_GC_NOMOTOR))
    {
        if (Spec < PAD_SPEC_2 && command == PAD_MOTOR_STOP_HARD)
            command = PAD_MOTOR_STOP;
        SISetCommand(chan, (0x40 << 16) | AnalogMode | (command & (0x00000001 | 0x00000002)));
        SITransferCommands();
    }
    OSRestoreInterrupts(enabled);
}

void PADSetSpec(u32 spec) {
    ASSERTLINE(1231, !Initialized);
    __PADSpec = 0;
    switch (spec)
    {
    case PAD_SPEC_0:
        MakeStatus = SPEC0_MakeStatus;
        break;
    case PAD_SPEC_1:
        MakeStatus = SPEC1_MakeStatus;
        break;
    case PAD_SPEC_2:
    case PAD_SPEC_3:
    case PAD_SPEC_4:
    case PAD_SPEC_5:
        MakeStatus = SPEC2_MakeStatus;
        break;
    }
    Spec = spec;
}

u32 PADGetSpec(void) {
    return Spec;
}

static void SPEC0_MakeStatus(s32 chan, PADStatus *status, u32 data[2]) {
    status->button = 0;
    status->button |= ((data[0] >> 16) & 0x0008) ? PAD_BUTTON_A : 0;
    status->button |= ((data[0] >> 16) & 0x0020) ? PAD_BUTTON_B : 0;
    status->button |= ((data[0] >> 16) & 0x0100) ? PAD_BUTTON_X : 0;
    status->button |= ((data[0] >> 16) & 0x0001) ? PAD_BUTTON_Y : 0;
    status->button |= ((data[0] >> 16) & 0x0010) ? PAD_BUTTON_START : 0;
    status->stickX = (s8)(data[1] >> 16);
    status->stickY = (s8)(data[1] >> 24);
    status->substickX = (s8)(data[1]);
    status->substickY = (s8)(data[1] >> 8);
    status->triggerLeft = (u8)(data[0] >> 8);
    status->triggerRight = (u8)data[0];
    status->analogA = 0;
    status->analogB = 0;
    if (170 <= status->triggerLeft)
        status->button |= PAD_TRIGGER_L;
    if (170 <= status->triggerRight)
        status->button |= PAD_TRIGGER_R;
    status->stickX -= 128;
    status->stickY -= 128;
    status->substickX -= 128;
    status->substickY -= 128;
}

static void SPEC1_MakeStatus(s32 chan, PADStatus *status, u32 data[2]) {
    status->button = 0;
    status->button |= ((data[0] >> 16) & 0x0080) ? PAD_BUTTON_A : 0;
    status->button |= ((data[0] >> 16) & 0x0100) ? PAD_BUTTON_B : 0;
    status->button |= ((data[0] >> 16) & 0x0020) ? PAD_BUTTON_X : 0;
    status->button |= ((data[0] >> 16) & 0x0010) ? PAD_BUTTON_Y : 0;
    status->button |= ((data[0] >> 16) & 0x0200) ? PAD_BUTTON_START : 0;

    status->stickX = (s8)(data[1] >> 16);
    status->stickY = (s8)(data[1] >> 24);
    status->substickX = (s8)(data[1]);
    status->substickY = (s8)(data[1] >> 8);

    status->triggerLeft = (u8)(data[0] >> 8);
    status->triggerRight = (u8)data[0];

    status->analogA = 0;
    status->analogB = 0;

    if (170 <= status->triggerLeft)
        status->button |= PAD_TRIGGER_L;
    if (170 <= status->triggerRight)
        status->button |= PAD_TRIGGER_R;

    status->stickX -= 128;
    status->stickY -= 128;
    status->substickX -= 128;
    status->substickY -= 128;
}

static s8 ClampS8(s8 var, s8 org) {
    if (0 < org)
    {
        s8 min = (s8)(-128 + org);
        if (var < min)
            var = min;
    }
    else if (org < 0)
    {
        s8 max = (s8)(127 + org);
        if (max < var)
            var = max;
    }
    return var -= org;
}

static u8 ClampU8(u8 var, u8 org) {
    if (var < org)
        var = org;
    return var -= org;
}

static void SPEC2_MakeStatus(s32 chan, PADStatus *status, u32 data[2]) {
    PADStatus *origin;

    status->button = (u16)((data[0] >> 16) & PAD_ALL);
    status->stickX = (s8)(data[0] >> 8);
    status->stickY = (s8)(data[0]);

    switch (AnalogMode & 0x00000700)
    {
    case 0x00000000:
    case 0x00000500:
    case 0x00000600:
    case 0x00000700:
        status->substickX = (s8)(data[1] >> 24);
        status->substickY = (s8)(data[1] >> 16);
        status->triggerLeft = (u8)(((data[1] >> 12) & 0x0f) << 4);
        status->triggerRight = (u8)(((data[1] >> 8) & 0x0f) << 4);
        status->analogA = (u8)(((data[1] >> 4) & 0x0f) << 4);
        status->analogB = (u8)(((data[1] >> 0) & 0x0f) << 4);
        break;
    case 0x00000100:
        status->substickX = (s8)(((data[1] >> 28) & 0x0f) << 4);
        status->substickY = (s8)(((data[1] >> 24) & 0x0f) << 4);
        status->triggerLeft = (u8)(data[1] >> 16);
        status->triggerRight = (u8)(data[1] >> 8);
        status->analogA = (u8)(((data[1] >> 4) & 0x0f) << 4);
        status->analogB = (u8)(((data[1] >> 0) & 0x0f) << 4);
        break;
    case 0x00000200:
        status->substickX = (s8)(((data[1] >> 28) & 0x0f) << 4);
        status->substickY = (s8)(((data[1] >> 24) & 0x0f) << 4);
        status->triggerLeft = (u8)(((data[1] >> 20) & 0x0f) << 4);
        status->triggerRight = (u8)(((data[1] >> 16) & 0x0f) << 4);
        status->analogA = (u8)(data[1] >> 8);
        status->analogB = (u8)(data[1] >> 0);
        break;
    case 0x00000300:
        status->substickX = (s8)(data[1] >> 24);
        status->substickY = (s8)(data[1] >> 16);
        status->triggerLeft = (u8)(data[1] >> 8);
        status->triggerRight = (u8)(data[1] >> 0);
        status->analogA = 0;
        status->analogB = 0;
        break;
    case 0x00000400:
        status->substickX = (s8)(data[1] >> 24);
        status->substickY = (s8)(data[1] >> 16);
        status->triggerLeft = 0;
        status->triggerRight = 0;
        status->analogA = (u8)(data[1] >> 8);
        status->analogB = (u8)(data[1] >> 0);
        break;
    }

    status->stickX -= 128;
    status->stickY -= 128;
    status->substickX -= 128;
    status->substickY -= 128;

    origin = &Origin[chan];
    status->stickX = ClampS8(status->stickX, origin->stickX);
    status->stickY = ClampS8(status->stickY, origin->stickY);
    status->substickX = ClampS8(status->substickX, origin->substickX);
    status->substickY = ClampS8(status->substickY, origin->substickY);
    status->triggerLeft = ClampU8(status->triggerLeft, origin->triggerLeft);
    status->triggerRight = ClampU8(status->triggerRight, origin->triggerRight);
}

BOOL PADGetType(s32 chan, u32 * type) {
    u32 chanBit;

    *type = SIGetType(chan);
    chanBit = 0x80000000 >> chan;
    if (ResettingBits & chanBit || ResettingChan == chan || !(EnabledBits & chanBit)) {
        return FALSE;
    }
    return TRUE;
}

BOOL PADSync(void) {
    return ResettingBits == 0 && (s32)ResettingChan == 32 && !SIBusy();
}

void PADSetAnalogMode(u32 mode) {
    BOOL enabled;
    u32 mask;

    ASSERTMSGLINE(1547, (mode < 8), "PADSetAnalogMode(): invalid mode");

    enabled = OSDisableInterrupts();
    AnalogMode = mode << 8;
    mask = EnabledBits;

    EnabledBits &= ~mask;
    WaitingBits &= ~mask;
    CheckingBits &= ~mask;

    SIDisablePolling(mask);
    OSRestoreInterrupts(enabled);
}

static BOOL OnReset(BOOL final) {
    BOOL sync;
    static BOOL recalibrated = FALSE;

    if (SamplingCallback) {
        PADSetSamplingCallback(NULL);
    }

    if (!final)
    {
        sync = PADSync();
        if (!recalibrated && sync)
        {
            recalibrated = PADRecalibrate(PAD_CHAN0_BIT | PAD_CHAN1_BIT | PAD_CHAN2_BIT | PAD_CHAN3_BIT);
            return FALSE;
        }
        return sync;
    }
    else
        recalibrated = FALSE;

    return TRUE;
}

void __PADDisableXPatch(void) {
    XPatchBits = 0;
}

static void SamplingHandler(s16 interrupt, OSContext* context) {
    OSContext exceptionContext;

    if (SamplingCallback) {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        (*SamplingCallback)();
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}

PADSamplingCallback PADSetSamplingCallback(PADSamplingCallback callback) {
    PADSamplingCallback prev;

    prev = SamplingCallback;
    SamplingCallback = callback;

    if (callback) {
        SIRegisterPollingHandler(&SamplingHandler);
    } else {
        SIUnregisterPollingHandler(&SamplingHandler);
    }

    return prev;
}

BOOL __PADDisableRecalibration(BOOL disable) {
    BOOL enabled;
    BOOL prev;

    enabled = OSDisableInterrupts();
    prev = (__gUnknown800030E3 & 0x40) ? TRUE : FALSE;
    __gUnknown800030E3 &= 0xBF;

    if (disable) {
        __gUnknown800030E3 |= 0x40;
    }

    OSRestoreInterrupts(enabled);
    return prev;
}
