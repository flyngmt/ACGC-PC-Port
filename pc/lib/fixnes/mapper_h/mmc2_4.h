/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef mmc2_4_h_
#define mmc2_4_h_

void mmc2_4init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize, 
			uint8_t *chrROM, uint32_t chrROMsize);

void mmc2initGet8(uint16_t addr);
void mmc4initGet8(uint16_t addr);

void mmc2initSet8(uint16_t addr);
void mmc4initSet8(uint16_t addr);

void mmc2initPPUGet8(uint16_t addr);
void mmc4initPPUGet8(uint16_t addr);

void mmc2_4initPPUSet8(uint16_t addr);

#endif
