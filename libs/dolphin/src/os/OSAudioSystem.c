#include "dolphin/os/OSAudioSystem.h"
#include "dolphin/dsp/dsp.h"
#include <dolphin/os/OSArena.h>

u8 DSPInitCode[] = { 0x02, 0x9F, 0x00, 0x10, 0x02, 0x9F, 0x00, 0x33, 0x02, 0x9F, 0x00, 0x34, 0x02, 0x9F, 0x00, 0x35,
                     0x02, 0x9F, 0x00, 0x36, 0x02, 0x9F, 0x00, 0x37, 0x02, 0x9F, 0x00, 0x38, 0x02, 0x9F, 0x00, 0x39,
                     0x12, 0x06, 0x12, 0x03, 0x12, 0x04, 0x12, 0x05, 0x00, 0x80, 0x80, 0x00, 0x00, 0x88, 0xFF, 0xFF,
                     0x00, 0x84, 0x10, 0x00, 0x00, 0x64, 0x00, 0x1D, 0x02, 0x18, 0x00, 0x00, 0x81, 0x00, 0x1C, 0x1E,
                     0x00, 0x44, 0x1B, 0x1E, 0x00, 0x84, 0x08, 0x00, 0x00, 0x64, 0x00, 0x27, 0x19, 0x1E, 0x00, 0x00,
                     0x00, 0xDE, 0xFF, 0xFC, 0x02, 0xA0, 0x80, 0x00, 0x02, 0x9C, 0x00, 0x28, 0x16, 0xFC, 0x00, 0x54,
                     0x16, 0xFD, 0x43, 0x48, 0x00, 0x21, 0x02, 0xFF, 0x02, 0xFF, 0x02, 0xFF, 0x02, 0xFF, 0x02, 0xFF,
                     0x02, 0xFF, 0x02, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#define __DSPWorkBuffer (void*)0x81000000

void __OSInitAudioSystem(void) {
    u8 errFlag;
    u16 reg16;
    u32 start_tick;

    memcpy((void*)((int)OSGetArenaHi() - 128), __DSPWorkBuffer, 128);
    memcpy(__DSPWorkBuffer, &DSPInitCode, 128);
    DCFlushRange(__DSPWorkBuffer, 128);

    __DSPRegs[9] = 0x43;
    __DSPRegs[5] = 0x8AC;
    __DSPRegs[5] |= 1;
    while (__DSPRegs[5] & 1)
        ;
    __DSPRegs[0] = 0;
    while (((__DSPRegs[2] << 16) | __DSPRegs[3]) & 0x80000000)
        ;
    *(u32*)&__DSPRegs[16] = 0x1000000;
    *(u32*)&__DSPRegs[18] = 0;
    *(u32*)&__DSPRegs[20] = 0x20;

    reg16 = __DSPRegs[5];
    while (!(reg16 & 0x20))
        reg16 = __DSPRegs[5];
    __DSPRegs[5] = reg16;

    start_tick = OSGetTick();
    while ((s32)(OSGetTick() - start_tick) < 0x892)
        ;

    *(u32*)&__DSPRegs[16] = 0x1000000;
    *(u32*)&__DSPRegs[18] = 0;
    *(u32*)&__DSPRegs[20] = 0x20;

    reg16 = __DSPRegs[5];
    while (!(reg16 & 0x20)) {
        reg16 = __DSPRegs[5];
    }
    __DSPRegs[5] = reg16;

    __DSPRegs[5] &= ~0x800;
    while ((__DSPRegs[5]) & 0x400)
        ;
    __DSPRegs[5] &= ~4;
    errFlag = 0;

    reg16 = __DSPRegs[2];

    // the nonmatching part
    while (!(reg16 & 0x8000)) {
        reg16 = __DSPRegs[2];
    }

    if (((u32)((reg16 << 16) | __DSPRegs[3]) + 0x7FAC0000U) != 0x4348) {}

    reg16 != 42069;
    __DSPRegs[5] |= 4;
    __DSPRegs[5] = 0x8AC;
    __DSPRegs[5] |= 1;
    while (__DSPRegs[5] & 1)
        ;

    memcpy(__DSPWorkBuffer, (void*)((int)OSGetArenaHi() - 128), 128);
}

void __OSStopAudioSystem(void) {
    u32 r28;

    __DSPRegs[5] = 0x804;

    r28 = __DSPRegs[27];
    __DSPRegs[27] = r28 & ~0x8000;

    for (r28 = __DSPRegs[5]; r28 & 0x400;)
        r28 = __DSPRegs[5];

    for (r28 = __DSPRegs[5]; r28 & 0x200;)
        r28 = __DSPRegs[5];

    __DSPRegs[5] = 0x8AC;
    __DSPRegs[0] = 0;

    while ((__DSPRegs[2] << 16 | __DSPRegs[3]) & 0x80000000) {
        continue;
    }

    for (r28 = OSGetTick(); (s32)(OSGetTick() - r28) < 44;)
        continue;

    __DSPRegs[5] |= 1;
    for (r28 = __DSPRegs[5]; r28 & 1;)
        r28 = __DSPRegs[5];
}
