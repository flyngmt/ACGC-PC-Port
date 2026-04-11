/*
 * Copyright (C) 2019 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef rambo1_h_
#define rambo1_h_

void rambo1init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m158init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void rambo1initSet8(uint16_t addr);
void m158initSet8(uint16_t addr);
void rambo1initPPUGet8(uint16_t addr);
void rambo1initPPUSet8(uint16_t addr);
void rambo1cycle();

#endif
