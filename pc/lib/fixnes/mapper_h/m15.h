/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef m15_h_
#define m15_h_

void m15init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize, 
			uint8_t *chrROM, uint32_t chrROMsize);
void m15initGet8(uint16_t addr);
void m15initSet8(uint16_t addr);
void m15initPPUGet8(uint16_t addr);
void m15initPPUSet8(uint16_t addr);
void m15reset();

#endif
