#ifndef _JAUDIO_IPLDEC_H
#define _JAUDIO_IPLDEC_H

#include "types.h"
#include "dolphin/dsp.h"

/////////// JAUDIO IPL DEC DEFINITIONS ///////////
// Global functions (all C++, so no extern C wrap).
#ifdef __cplusplus
extern "C" {
#endif

BOOL DspExtraTaskCheck();
void Jac_DSPcardDecodeAsync(void*, void*, DSPCallback);
void Jac_DSPagbDecodeAsync(void* task, void* cmd, DSPCallback callback);

// IPL Decode specific structs.

#define DSPTARGET_IPL 0
#define DSPTARGET_AGB 1

/**
 * @brief TODO.
 */
typedef struct DSPTask {
	u8 target;            // _00, ipl (gc) or agb (gameboy player)
	uintptr_t cmd;        // _04
	void* task;           // _08
	DSPCallback callback; // _0C
} DSPTask;

//////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif
