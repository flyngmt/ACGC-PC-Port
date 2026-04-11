/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef _AUDIO_FDS_H_
#define _AUDIO_FDS_H_

#include "common.h"

void fdsAudioInit();
FIXNES_NOINLINE void fdsAudioCycle();
void fdsAudioClockTimers();
FIXNES_NOINLINE void fdsAudioMasterUpdate();
void fdsAudioSet8(uint16_t addr, uint8_t val);
void fdsAudioSetWave(uint16_t addr, uint8_t val);
uint8_t fdsAudioGetReg90(uint16_t addr);
uint8_t fdsAudioGetReg92(uint16_t addr);
uint8_t fdsAudioGetWave(uint16_t addr);

extern uint8_t fdsOut;

#endif
