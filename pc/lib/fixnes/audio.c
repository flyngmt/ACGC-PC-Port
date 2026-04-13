/* audio.c — stub for fixNES integration.
 * Audio output is handled by the wrapper (pc_nes_fixnes.c) via AIInitDMA.
 * These stubs satisfy linker references from fixNES core. */

#include "audio.h"

int audioInit() { return 0; }
int audioUpdate() { return 1; } /* always report "processed" so frame loop doesn't stall */
void audioDeinit() { }
void audioSleep() { }
