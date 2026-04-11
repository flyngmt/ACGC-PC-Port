/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef s4_h_
#define s4_h_

void s4init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void s4initGet8(uint16_t addr);
void s4initSet8(uint16_t addr);
void s4initPPUGet8(uint16_t addr);
void s4initPPUSet8(uint16_t addr);

#endif
