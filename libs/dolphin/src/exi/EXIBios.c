#include <string.h>
#include <dolphin.h>
#include <dolphin/os.h>
#include "os/__os.h"

typedef void (*EXICallback)(s32, OSContext*);

typedef struct EXIControl {
    EXICallback exiCallback;
    EXICallback tcCallback;
    EXICallback extCallback;
    volatile u32 state;
    int immLen;
    u8* immBuf;
    u32 dev;
    u32 id;
    s32 idTime;
    int items;
    struct {
        u32 dev;
        EXICallback callback;
    } queue[3];
} EXIControl;

#define MAX_CHAN 3

#define STATE_BUSY 3
#define STATE_SELECTED 4

#define MAX_IMM 4
#define MAX_TYPE 3
#define MAX_DEV 3
#define MAX_FREQ 6

#define EXI_0LENGTH_EXILENGTH_MASK 0x03FFFFE0

#define EXI_READ 0
#define EXI_WRITE 1

static struct EXIControl Ecb[3];

static void SetExiInterruptMask(long chan, struct EXIControl * exi);
static void CompleteTransfer(long chan);
static int __EXIProbe(long chan);
int EXIImm(long chan, void * buf, long len, unsigned long type, EXICallback callback);
int EXIImmEx(long chan, void * buf, long len, unsigned long mode);
int EXIDma(long chan, void * buf, long len, unsigned long type, EXICallback callback);
int EXISync(long chan);
unsigned long EXIClearInterrupts(long chan, int exi, int tc, int ext);
EXICallback EXISetExiCallback(long chan, EXICallback exiCallback);
void EXIProbeReset();
int EXIProbe(long chan);
s32 EXIProbeEx(long chan);
int EXIAttach(long chan, EXICallback extCallback);
int EXIDetach(long chan);
int EXISelect(long chan, unsigned long dev, unsigned long freq);
int EXIDeselect(long chan);
static void EXIIntrruptHandler(signed short interrupt, struct OSContext * context);
static void TCIntrruptHandler(signed short interrupt, struct OSContext * context);
static void EXTIntrruptHandler(signed short interrupt, struct OSContext * context);
void EXIInit();
int EXILock(long chan, unsigned long dev, void (* unlockedCallback)(long, struct OSContext *));
int EXIUnlock(long chan);
unsigned long EXIGetState(long chan);
s32 EXIGetID(long chan, unsigned long dev, unsigned long * id);

static void SetExiInterruptMask(long chan, struct EXIControl * exi) {
    struct EXIControl * exi2 = &Ecb[2];

    switch(chan) {
        case 0:
            if ((exi->exiCallback == 0 && exi2->exiCallback == 0) || exi->state & 0x10) {
                __OSMaskInterrupts(0x410000U);
                return;
            }
            __OSUnmaskInterrupts(0x410000U);
            return;
        case 1:
            if (exi->exiCallback == 0 || exi->state & 0x10) {
                __OSMaskInterrupts(0x80000U);
                return;
            }
            __OSUnmaskInterrupts(0x80000U);
            return;
        case 2:
            if ((__OSGetInterruptHandler(0x19) == 0U) || (exi->state & 0x10)) {
                __OSMaskInterrupts(0x40U);
                return;
            }
            __OSUnmaskInterrupts(0x40U);
            return;
    }
}

static void CompleteTransfer(long chan) {
    struct EXIControl * exi;
    unsigned char * buf;
    unsigned long data;
    int i;
    int len;

    exi = &Ecb[chan];
    ASSERTLINE(301, 0 <= chan && chan < MAX_CHAN);

    if (exi->state & 3) {
        if (exi->state & 2) {
            if ((len = exi->immLen) != 0) {
                buf = exi->immBuf;
                data = __EXIRegs[(chan * 5) + 4];
                for(i = 0; i < len; i++) {
                    *buf++ = data >> ((3 - i) * 8);
                }
            }
        }
        exi->state &= ~3;
    }
}

int EXIImm(long chan, void * buf, long len, unsigned long type, EXICallback callback) {
    struct EXIControl * exi;
    int enabled;
    unsigned long data;
    int i;

    exi = &Ecb[chan];
    ASSERTLINE(339, exi->state & STATE_SELECTED);
    ASSERTLINE(340, 0 <= chan && chan < MAX_CHAN);
    ASSERTLINE(341, 0 < len && len <= MAX_IMM);
    ASSERTLINE(342, type < MAX_TYPE);
    enabled = OSDisableInterrupts();
    if ((exi->state & 3) || !(exi->state & 4)) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    exi->tcCallback = callback;
    if (exi->tcCallback) {
        EXIClearInterrupts(chan, 0, 1, 0);
        __OSUnmaskInterrupts(0x200000U >> (chan * 3));
    }
    exi->state |= 2;
    if (type != 0) {
        data = 0;
        for(i = 0; i < len; i++) {
            data |= ((u8*)buf)[i] << ((3 - i) * 8);
        }
        __EXIRegs[(chan * 5) + 4] = data;
    }
    exi->immBuf = buf;
    exi->immLen = (type != 1) ? len : 0; 
    __EXIRegs[(chan * 5) + 3] = (type << 2) | 1 | ((len - 1) << 4);
    OSRestoreInterrupts(enabled);
    return 1;
}

int EXIImmEx(long chan, void * buf, long len, unsigned long mode) {
    long xLen;

    while(len) {
        xLen = (len < 4) ? len : 4;
        if (EXIImm(chan, buf, xLen, mode, 0) == 0) {
            return 0;
        }
        if (EXISync(chan) == 0) {
            return 0;
        }
        ((u8*)buf) += xLen;
        len -= xLen;
    }
    return 1;
}

int EXIDma(long chan, void * buf, long len, unsigned long type, EXICallback callback) {
    struct EXIControl * exi;
    int enabled;

    exi = &Ecb[chan];

    ASSERTLINE(444, exi->state & STATE_SELECTED);
    ASSERTLINE(445, OFFSET(buf, 32) == 0);
    ASSERTLINE(446, 0 < len && OFFSET(len, 32) == 0);
    ASSERTLINE(448, ((u32) len & ~EXI_0LENGTH_EXILENGTH_MASK) == 0);
    ASSERTLINE(450, type == EXI_READ || type == EXI_WRITE);

    enabled = OSDisableInterrupts();
    if ((exi->state & 3) || !(exi->state & 4)) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    exi->tcCallback = callback;
    if ((u32)exi->tcCallback) {
        EXIClearInterrupts(chan, 0, 1, 0);
        __OSUnmaskInterrupts(0x200000U >> (chan * 3));
    }
    exi->state |= 1;
    __EXIRegs[(chan * 5) + 1] = (u32)buf & 0x03FFFFE0;
    __EXIRegs[(chan * 5) + 2] = len;
    __EXIRegs[(chan * 5) + 3] = (type * 4) | 3;
    OSRestoreInterrupts(enabled);
    return 1;
}

int EXISync(long chan) {
    struct EXIControl * exi;
    int rc;
    int enabled;

    exi = &Ecb[chan];
    rc = 0;
    ASSERTLINE(498, 0 <= chan && chan < MAX_CHAN);
    while ((exi->state & 4)) {
        if (!(__EXIRegs[(chan * 5) + 3] & 1)) {
            enabled = OSDisableInterrupts();
            if (exi->state & 4) {
                CompleteTransfer(chan);
                if (__OSGetDIConfig() != 0xFF || (exi->immLen != 4 || (__EXIRegs[chan * 5] & 0x70) ||
                    (__EXIRegs[(chan * 5) + 4] != 0x01010000 && __EXIRegs[(chan * 5) + 4] != 0x05070000 && __EXIRegs[(chan * 5) + 4] != 0x04220001)) ||
                    __OSDeviceCode == 0x8200) {
                    rc = 1;
                }
            }
            OSRestoreInterrupts(enabled);
            break;
        }
    }
    ASSERTLINE(526, !(exi->state & STATE_BUSY));
    return rc;
}

unsigned long EXIClearInterrupts(long chan, int exi, int tc, int ext) {
    unsigned long cpr;
    unsigned long prev;

    ASSERTLINE(547, 0 <= chan && chan < MAX_CHAN);
    cpr = prev = __EXIRegs[(chan * 5)];
    prev &= 0x7F5;
    if (exi != 0) {
        prev |= 2;
    }
    if (tc != 0) {
        prev |= 8;
    }
    if (ext != 0) {
        prev |= 0x800;
    }
    __EXIRegs[(chan * 5)] = prev;
    return cpr;
}

EXICallback EXISetExiCallback(long chan, EXICallback exiCallback) {
    struct EXIControl * exi;
    EXICallback prev;
    int enabled;

    exi = &Ecb[chan];
    ASSERTLINE(581, 0 <= chan && chan < MAX_CHAN);
    enabled = OSDisableInterrupts();
    prev = exi->exiCallback;
    exi->exiCallback = exiCallback;
    if (chan != 2) {
        SetExiInterruptMask(chan, exi);
    } else {
        SetExiInterruptMask(0, &Ecb[0]);
    }
    OSRestoreInterrupts(enabled);
    return prev;
}

void EXIProbeReset() {
    __gUnknown800030C0[0] = __gUnknown800030C0[1] = 0;
    Ecb[0].idTime = Ecb[1].idTime = 0;
    __EXIProbe(0);
    __EXIProbe(1);
}

static int __EXIProbe(long chan) {
    struct EXIControl * exi;
    int enabled;
    int rc;
    unsigned long cpr;
    long t;

    exi = &Ecb[chan];
    ASSERTLINE(636, 0 <= chan && chan < MAX_CHAN);
    if (chan == 2) {
        return 1;
    }
    rc = 1;
    enabled = OSDisableInterrupts();
    cpr = __EXIRegs[(chan * 5)];
    if (!(exi->state & 8)) {
        if (cpr & 0x800) {
            EXIClearInterrupts(chan, 0, 0, 1);
            __gUnknown800030C0[chan] = exi->idTime = 0;
        }
        if (cpr & 0x1000) {
            t = ((long)(OSTicksToMilliseconds(OSGetTime()) / 100) + 1);

            if (__gUnknown800030C0[chan] == 0) {
                __gUnknown800030C0[chan] = t;
            }
            if (t - (long)__gUnknown800030C0[chan] < 3) {
                rc = 0;
            }
        } else {
            __gUnknown800030C0[chan] = exi->idTime = 0;
            rc = 0;
        }
    } else if(!(cpr & 0x1000) || (cpr & 0x800)) {
        __gUnknown800030C0[chan] = exi->idTime = 0;
        rc = 0;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

int EXIProbe(long chan) {
    EXIControl* exi = &Ecb[chan];
    int rc;
    u32 id;

    
    rc = __EXIProbe(chan);
    if (rc && !exi->idTime) {
        rc = EXIGetID(chan, 0, &id) ? 1 : 0;
    }

    return rc;
}

s32 EXIProbeEx(long chan) {
    if (EXIProbe(chan)) {
        return 1;
    }
    if (__gUnknown800030C0[chan]) {
        return 0;
    }
    return -1;
}

static int __EXIAttach(long chan, EXICallback extCallback) {
    struct EXIControl * exi;
    int enabled;

    exi = &Ecb[chan];
    ASSERTLINE(741, 0 <= chan && chan < 2);
    enabled = OSDisableInterrupts();
    if ((exi->state & 8) || !__EXIProbe(chan)) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    EXIClearInterrupts(chan, 1, 0, 0);
    exi->extCallback = extCallback;
    __OSUnmaskInterrupts(0x100000U >> (chan * 3));
    exi->state |= 8;
    OSRestoreInterrupts(enabled);
    return 1;
}

int EXIAttach(long chan, EXICallback extCallback) {
    struct EXIControl * exi;
    int enabled;
    int rc;

    exi = &Ecb[chan];
    ASSERTLINE(767, 0 <= chan && chan < 2);
    EXIProbe(chan);
    enabled = OSDisableInterrupts();
    if (exi->idTime == 0) {
        OSRestoreInterrupts(enabled);
        return 0;
    }

    rc = __EXIAttach(chan, extCallback);
    OSRestoreInterrupts(enabled);
    return rc;
}

int EXIDetach(long chan) {
    struct EXIControl * exi;
    int enabled;

    exi = &Ecb[chan];
    ASSERTLINE(801, 0 <= chan && chan < 2);
    enabled = OSDisableInterrupts();
    if (!(exi->state & 8)) {
        OSRestoreInterrupts(enabled);
        return 1;
    }
    if ((exi->state & 0x10) && (exi->dev == 0)) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    exi->state &= ~8;
    __OSMaskInterrupts(0x500000U >> (chan * 3));
    OSRestoreInterrupts(enabled);
    return 1;
}

int EXISelect(long chan, unsigned long dev, unsigned long freq) {
    struct EXIControl * exi;
    unsigned long cpr;
    int enabled;

    exi = &Ecb[chan];

    ASSERTLINE(841, 0 <= chan && chan < MAX_CHAN);
    ASSERTLINE(842, chan == 0 && dev < MAX_DEV || dev == 0);
    ASSERTLINE(843, freq < MAX_FREQ);
    ASSERTLINE(844, !(exi->state & STATE_SELECTED));

    enabled = OSDisableInterrupts();
    if ((exi->state & 4) || ((chan != 2) && (((dev == 0) && !(exi->state & 8) && (__EXIProbe(chan) == 0)) || !(exi->state & 0x10) || (exi->dev != dev)))) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    exi->state |= 4;
    cpr = __EXIRegs[(chan * 5)];
    cpr &= 0x405;
    cpr |= (((1 << dev) << 7) | (freq * 0x10));
    __EXIRegs[(chan * 5)] = cpr;
    if (exi->state & 8) {
        switch (chan) {
            case 0:
                __OSMaskInterrupts(0x100000U);
                break;
            case 1:
                __OSMaskInterrupts(0x20000U);
                break;
        }
    }
    OSRestoreInterrupts(enabled);
    return 1;
}

int EXIDeselect(long chan) {
    struct EXIControl * exi;
    unsigned long cpr;
    int enabled;

    exi = &Ecb[chan];
    ASSERTLINE(895, 0 <= chan && chan < MAX_CHAN);
    enabled = OSDisableInterrupts();
    if (!(exi->state & 4)) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    exi->state &= ~4;
    cpr = __EXIRegs[(chan * 5)];
    __EXIRegs[(chan * 5)] = cpr & 0x405;
    if (exi->state & 8) {
        switch (chan) {
            case 0:
                __OSUnmaskInterrupts(0x100000U);
                break;
            case 1:
                __OSUnmaskInterrupts(0x20000U);
                break;
        }
    }
    OSRestoreInterrupts(enabled);
    if ((chan != 2) && (cpr & 0x80)) {
        if (__EXIProbe(chan) != 0) {
            return 1;
        }
        return 0;
    }
    return 1;
}

static void EXIIntrruptHandler(signed short interrupt, struct OSContext * context) {
    long chan;
    struct EXIControl * exi;
    EXICallback callback;

    chan = (interrupt-9)/3;

    ASSERTLINE(946, 0 <= chan && chan < MAX_CHAN);
    exi = &Ecb[chan];
    EXIClearInterrupts(chan, 1, 0, 0);
    callback = exi->exiCallback;
    if (callback) {
        OSContext exceptionContext;

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        callback(chan, context);
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}

static void TCIntrruptHandler(signed short interrupt, struct OSContext * context) {
    long chan;
    struct EXIControl * exi;
    EXICallback callback;

    chan = (interrupt-10)/3;

    ASSERTLINE(982, 0 <= chan && chan < MAX_CHAN);
    exi = &Ecb[chan];
    __OSMaskInterrupts(0x80000000U >> interrupt);
    EXIClearInterrupts(chan, 0, 1, 0);
    callback = exi->tcCallback;
    if (callback) {
        OSContext exceptionContext;

        exi->tcCallback = NULL;
        CompleteTransfer(chan);

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        callback(chan, context);
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}

static void EXTIntrruptHandler(signed short interrupt, struct OSContext * context) {
    long chan;
    struct EXIControl * exi;
    EXICallback callback;

    chan = (interrupt-11)/3;

    ASSERTLINE(1023, 0 <= chan && chan < 2);
    __OSMaskInterrupts(0x500000U >> (chan * 3));
    // __EXIRegs[(chan * 5)] = 0;
    exi = &Ecb[chan];
    callback = exi->extCallback;
    exi->state &= 0xFFFFFFF7;
    if (callback) {
        OSContext exceptionContext;
        
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        exi->extCallback = NULL;
        callback(chan, context);
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}

void EXIInit() {
    __OSMaskInterrupts(0x7F8000U);
    __EXIRegs[0] = 0;
    __EXIRegs[5] = 0;
    __EXIRegs[10] = 0;
    __EXIRegs[0] = 0x2000;
    __OSSetInterruptHandler(9,  EXIIntrruptHandler);
    __OSSetInterruptHandler(10, TCIntrruptHandler);
    __OSSetInterruptHandler(11, EXTIntrruptHandler);
    __OSSetInterruptHandler(12, EXIIntrruptHandler);
    __OSSetInterruptHandler(13, TCIntrruptHandler);
    __OSSetInterruptHandler(14, EXTIntrruptHandler);
    __OSSetInterruptHandler(15, EXIIntrruptHandler);
    __OSSetInterruptHandler(16, TCIntrruptHandler);
    if (OSGetConsoleType() & 0x10000000) {
        EXIProbeReset();
    }
}

int EXILock(long chan, unsigned long dev, void (* unlockedCallback)(long, struct OSContext *)) {
    struct EXIControl * exi;
    int enabled;
    int i;

    exi = &Ecb[chan];
    ASSERTLINE(1112, 0 <= chan && chan < MAX_CHAN);
    ASSERTLINE(1113, chan == 0 && dev < MAX_DEV || dev == 0);
    enabled = OSDisableInterrupts();

    if (exi->state & 0x10) {
        if (unlockedCallback) {
            ASSERTLINE(1119, chan == 0 && exi->items < (MAX_DEV - 1) || exi->items == 0);
            for(i = 0; i < exi->items; i++) {
                if (exi->queue[i].dev == dev) {
                    OSRestoreInterrupts(enabled);
                    return 0;
                }
            }
            exi->queue[exi->items].callback = unlockedCallback;
            exi->queue[exi->items].dev = dev;
            exi->items++;
        }
        OSRestoreInterrupts(enabled);
        return 0;
    }
    ASSERTLINE(1135, exi->items == 0);
    exi->state |= 0x10;
    exi->dev = dev;
    SetExiInterruptMask(chan, exi);
    OSRestoreInterrupts(enabled);
    return 1;
}

int EXIUnlock(long chan) {
    struct EXIControl * exi;
    int enabled;
    EXICallback unlockedCallback;

    exi = &Ecb[chan];
    ASSERTLINE(1159, 0 <= chan && chan < MAX_CHAN);
    enabled = OSDisableInterrupts();
    if (!(exi->state & 0x10)) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    exi->state &= 0xFFFFFFEF;
    SetExiInterruptMask(chan, exi);
    if (exi->items > 0) {
        unlockedCallback = exi->queue[0].callback;
        if (--exi->items > 0) {
            memmove(&exi->queue[0], &exi->queue[1], exi->items * 8);
        }
        unlockedCallback(chan, 0);
    }
    OSRestoreInterrupts(enabled);
    return 1;
}

unsigned long EXIGetState(long chan) {
    struct EXIControl * exi;

    exi = &Ecb[chan];
    ASSERTLINE(1196, 0 <= chan && chan < MAX_CHAN);
    return exi->state;
}

static void UnlockedHandler(s32 chan, OSContext* context) {
    u32 id;

    EXIGetID(chan, 0, &id);
}

s32 EXIGetID(s32 chan, u32 dev, u32* id) {
    EXIControl* exi = &Ecb[chan];
    int err;
    u32 cmd;
    s32 startTime;
    BOOL enabled;

    ASSERTLINE(1233, 0 <= chan && chan < MAX_CHAN);
    if ((chan < 2) && (dev == 0)) {
        if ((__EXIProbe(chan) == 0)) {
            return 0;
        }

        if (exi->idTime == __gUnknown800030C0[chan]) {
            *id = exi->id;
            return exi->idTime;
        }

        if (!__EXIAttach(chan, NULL)) {
            return 0;
        }

        startTime = __gUnknown800030C0[chan];
    }

    err = !EXILock(chan, dev, (chan < 2 && dev == 0) ? &UnlockedHandler : NULL);
    if (err == 0) {
        err = !EXISelect(chan, dev, 0);
        if (err == 0) {
            cmd = 0;
            err |= !EXIImm(chan, &cmd, 2, 1, 0);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, id, 4, 0, 0);
            err |= !EXISync(chan);
            err |= !EXIDeselect(chan);
        }

        EXIUnlock(chan);
    }

    if ((chan < 2) && (dev == 0)) {
        EXIDetach(chan);
        enabled = OSDisableInterrupts();
        err |= __gUnknown800030C0[chan] != startTime;
        
        if (!err) {
            exi->id = *id;
            exi->idTime = startTime;
        }

        OSRestoreInterrupts(enabled);

        if (err) {
            return 0;
        }

        return exi->idTime;
    }

    if (err) {
        return 0;
    }

    return 1;
}

s32 EXIGetType(s32 chan, u32 dev, u32* type) {
    u32 _type;
    s32 probe;

    probe = EXIGetID(chan, dev, &_type);

    if (!probe) {
        return probe;
    }

    switch (_type & ~0xFF) {
        case 0x04020300:
        case 0x04020200:
        case 0x04020100:
        case 0x04060000:
            *type = (_type & ~0xFF);
            return probe;
        default:
            if ((_type & ~0xFFFF) == 0x04220000) {
                *type = 0x04220000;
                return probe;
            } else {
                *type = _type;
                return probe;
            }
    }
}

char* EXIGetTypeString(u32 type) {
    switch (type) {
        case 0x00000004:
            return "Memory Card 59";
        case 0x00000008:
            return "Memory Card 123";
        case 0x00000010:
            return "Memory Card 251";
        case 0x00000020:
            return "Memory Card 507";
        case 0x01010000:
            return "USB Adapter";
        case 0x01020000:
            return "NPDP-GDEV";
        case 0x02020000:
            return "Modem";
        case 0x03010000:
            return "Marlin";
        case 0x04120000:
            return "AD16";
        case 0x04040404:
            return "RS232C";
        case 0x80000004:
        case 0x80000008:
        case 0x80000010:
        case 0x80000020:
            return "Net Card";
        case 0x04020100:
        case 0x04020200:
        case 0x04020300:
        case 0x04220000:
            return "Ether";
        case 0x04060000:
            return "Mic";
        case 0x04130000:
            return "Stream Hanger";
        default:
            return "Unknown";
    }
}
