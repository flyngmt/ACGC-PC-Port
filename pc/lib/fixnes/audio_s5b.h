/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef _AUDIO_s5B_H_
#define _AUDIO_s5B_H_

#include "common.h"

void s5BAudioInit();
void s5BAudioClockTimers();
void s5BAudioSet8_C000(uint16_t addr, uint8_t val);
void s5BAudioSet8_E000(uint16_t addr, uint8_t val);
FIXNES_NOINLINE void s5BAudioCycle();

extern uint16_t s5BOut;

#endif
