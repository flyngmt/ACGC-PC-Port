#include "dolphin/os/OSError.h"
#include "dolphin/os/OSException.h"
#include "dolphin/os/OSInterrupt.h"
#include "dolphin/os/OSTime.h"
#include "dolphin/base/PPCArch.h"
#include "dolphin/hw_regs.h"
// #include "va_args.h"

OSErrorHandler __OSErrorTable[OS_ERROR_MAX];

extern volatile __OSInterrupt __OSLastInterrupt;
extern volatile u32 __OSLastInterruptSrr0;
extern volatile OSTime __OSLastInterruptTime;

__declspec(weak) void OSReport(char* msg, ...) {
    va_list marker;
    va_start(marker, msg);
    vprintf(msg, marker);
    va_end(marker);
}

__declspec(weak) void OSPanic(char* file, int line, char* msg, ...) {
    va_list marker;
    u32 i;
    u32* p;

    OSDisableInterrupts();
    va_start(marker, msg);
    vprintf(msg, marker);
    va_end(marker);
    OSReport(" in \"%s\" on line %d.\n", file, line);

    OSReport("\nAddress:      Back Chain    LR Save\n");
    for (i = 0, p = (u32*)OSGetStackPointer(); p && (u32)p != 0xffffffff && i++ < 16; p = (u32*)*p) {
        OSReport("0x%08x:   0x%08x    0x%08x\n", p, p[0], p[1]);
    }

    PPCHalt();
}

OSErrorHandler OSSetErrorHandler(OSError error, OSErrorHandler handler) {
    OSErrorHandler oldHandler;

    oldHandler = __OSErrorTable[error];
    __OSErrorTable[error] = handler;
    return oldHandler;
}

void __OSUnhandledException(u8 error, OSContext* context, s32 dsisr, s32 dar) {
    if (!(context->srr1 & MSR_RI)) {
        OSReport("Non-recoverable Exception %d", error);
    } else {
        if (__OSErrorTable[error]) {
            OSDisableScheduler();
            __OSErrorTable[error](error, context, dsisr, dar);
            OSEnableScheduler();
            __OSReschedule();
            OSLoadContext(context);
        }
        if (error == __OS_EXCEPTION_DECREMENTER) {
            OSLoadContext(context);
        }
        OSReport("Unhandled Exception %d", error);
    }
    OSReport("\n");
    OSDumpContext(context);
    OSReport("\nDSISR = 0x%08x                   DAR  = 0x%08x\n", dsisr, dar);
    OSReport("TB = 0x%016llx\n", OSGetTime());

    switch (error) {
        case __OS_EXCEPTION_DSI:
            OSReport("\nInstruction at 0x%x (read from SRR0) attempted to access "
                     "invalid address 0x%x (read from DAR)\n",
                     context->srr0, dar);
            break;
        case __OS_EXCEPTION_ISI:
            OSReport("\nAttempted to fetch instruction from invalid address 0x%x "
                     "(read from SRR0)\n",
                     context->srr0);
            break;
        case __OS_EXCEPTION_ALIGNMENT:
            OSReport("\nInstruction at 0x%x (read from SRR0) attempted to access "
                     "unaligned address 0x%x (read from DAR)\n",
                     context->srr0, dar);
            break;
        case __OS_EXCEPTION_PROGRAM:
            OSReport("\nProgram exception : Possible illegal instruction/operation "
                     "at or around 0x%x (read from SRR0)\n",
                     context->srr0, dar);
            break;
        case 15:
            OSReport("\n");
            OSReport("AI DMA Address =   0x%04x%04x\n", __DSPRegs[24], __DSPRegs[25]);
            OSReport("ARAM DMA Address = 0x%04x%04x\n", __DSPRegs[16], __DSPRegs[17]);
            OSReport("DI DMA Address =   0x%08x\n", __DIRegs[5]);
            break;
    }
    OSReport("\nLast interrupt (%d): SRR0 = 0x%08x  TB = 0x%016llx\n", __OSLastInterrupt, __OSLastInterruptSrr0,
             __OSLastInterruptTime);
    PPCHalt();
}
