/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef _AUDIO_VRC6_H_
#define _AUDIO_VRC6_H_

#include "common.h"

void vrc6AudioInit();
FIXNES_NOINLINE void vrc6AudioCycle();
void vrc6AudioClockTimers();
void vrc6AudioSet8_9XX0(uint16_t addr, uint8_t val);
void vrc6AudioSet8_9XX1(uint16_t addr, uint8_t val);
void vrc6AudioSet8_9XX2(uint16_t addr, uint8_t val);
void vrc6AudioSet8_9XX3(uint16_t addr, uint8_t val);
void vrc6AudioSet8_AXX0(uint16_t addr, uint8_t val);
void vrc6AudioSet8_AXX1(uint16_t addr, uint8_t val);
void vrc6AudioSet8_AXX2(uint16_t addr, uint8_t val);
void vrc6AudioSet8_BXX0(uint16_t addr, uint8_t val);
void vrc6AudioSet8_BXX1(uint16_t addr, uint8_t val);
void vrc6AudioSet8_BXX2(uint16_t addr, uint8_t val);

extern uint8_t vrc6Out;

#endif
