/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef _audio_mmc5_h_
#define _audio_mmc5_h_

#include "common.h"

void mmc5AudioInit();
FIXNES_NOINLINE void mmc5AudioCycle();
void mmc5AudioClockTimers();
void mmc5AudioSet8(uint16_t addr, uint8_t val);
uint8_t mmc5AudioGet8(uint16_t addr);
FIXNES_NOINLINE void mmc5AudioLenCycle();
void mmc5AudioPCMWrite(uint8_t val);

extern uint8_t mmc5Out;
extern uint8_t mmc5pcm;
extern bool mmc5_dmcreadmode;

#endif
