/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef _AUDIO_VRC7_H_
#define _AUDIO_VRC7_H_

#include "common.h"

void vrc7AudioInit();
FIXNES_NOINLINE void vrc7AudioCycle();
void vrc7AudioSet9010(uint16_t addr, uint8_t val);
void vrc7AudioSet9030(uint16_t addr, uint8_t val);

extern int32_t vrc7Out;

#endif
