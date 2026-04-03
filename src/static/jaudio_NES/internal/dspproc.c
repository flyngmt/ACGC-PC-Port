#include "jaudio_NES/dspproc.h"

#ifdef TARGET_PC
/*==========================================================================
 * PC: No hardware DSP — rspsim.c does all audio processing in software.
 * These functions become no-ops or simple state tracking.
 *==========================================================================*/
static u16 DSP_MIXERLEVEL = 0x4000;

extern s32 DSPSendCommands(u32* commands, u32 count) {
    /* No hardware DSP on PC */
    (void)commands; (void)count;
    return 0;
}

extern u32 DSPReleaseHalt(void) {
    /* No hardware DSP — rspsim processes synchronously */
    return 0x88881357;
}

extern void DSPWaitFinish(void) {
    /* No hardware DSP — already done synchronously */
}

extern void DsetupTable(uintptr_t arg0, uintptr_t arg1, uintptr_t arg2, uintptr_t arg3, uintptr_t arg4) {
    /* Channel table setup — no-op on PC, rspsim uses DSPchannel_ structs directly */
    (void)arg0; (void)arg1; (void)arg2; (void)arg3; (void)arg4;
}

extern void DsyncFrame(u32 subframes, uintptr_t dspbuf_start, uintptr_t dspbuf_end) {
    /* On GC this sends commands to DSP to process subframes.
     * On PC, rspsim is called directly from UpdateDSP path.
     * Store buffer pointers for rspsim if needed. */
    (void)subframes; (void)dspbuf_start; (void)dspbuf_end;
}

extern void DwaitFrame(void) {
    /* No-op on PC */
}

extern void DiplSec(uintptr_t arg0) {
    /* IPL security — not needed on PC */
    (void)arg0;
}

extern void DagbSec(uintptr_t arg0) {
    /* AGB security — not needed on PC */
    (void)arg0;
}

#else /* !TARGET_PC — original GC code */

#include "dolphin/dsp.h"

static u16 DSP_MIXERLEVEL = 0x4000;

extern s32 DSPSendCommands(u32* commands, u32 count) {
    if (DSPCheckMailToDSP() != 0) {
        return -1;
    }
    if (DSPCheckMailFromDSP() != 0) {
        return -1;
    }

    int i;

    for (i = 0; i < count; i++) {
        DSPSendMailToDSP(commands[i]);

        while (DSPCheckMailToDSP() != 0);
    }

    return 0;
}

extern u32 DSPReleaseHalt() {
    while (DSPCheckMailToDSP() != 0);
    DSPSendMailToDSP(0);
    if (DSPCheckMailFromDSP() != 0) {
        DSPReadMailFromDSP();
    }

    return 0x88881357;
}

extern void DSPWaitFinish() {
    do {
        while (DSPCheckMailFromDSP() == 0);
    } while ((DSPReadMailFromDSP() + 0x77780000) == 0x1357);
}

extern void DsetupTable(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4) {
    u32 commands[5];

    commands[0] = (arg0 & 0xFFFF) | 0x81000000;
    commands[1] = arg1;
    commands[2] = arg2;
    commands[3] = arg3;
    commands[4] = arg4;

    DSPSendCommands(commands, ARRAY_COUNT(commands));
    DSPWaitFinish();
}

extern void DsyncFrame(u32 subframes, u32 dspbuf_start, u32 dspbuf_end){
    u32 commands[3];

    commands[0] = (subframes << 16 & 0xFF0000) | 0x82000000 | DSP_MIXERLEVEL;
    commands[1] = dspbuf_start;
    commands[2] = dspbuf_end;

    DSPSendCommands(commands, ARRAY_COUNT(commands));
    DSPWaitFinish();
}

extern void DwaitFrame(){
    u32 commands[1];

    commands[0] = 0x80000000;
    DSPSendCommands(commands, ARRAY_COUNT(commands));
    DSPWaitFinish();
}

extern void DiplSec(u32 arg0){
    u32 commands[2];

    commands[0] = 0x8B000008;
    commands[1] = arg0;
    DSPSendCommands(commands, ARRAY_COUNT(commands));
    DSPWaitFinish();
}

extern void DagbSec(u32 arg0){
    u32 commands[2];

    commands[0] = 0x8C000008;
    commands[1] = arg0;
    DSPSendCommands(commands, ARRAY_COUNT(commands));
    DSPWaitFinish();
}

#endif /* TARGET_PC */

