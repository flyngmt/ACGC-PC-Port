/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef m28_h_
#define m28_h_

void m28init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m28initGet8(uint16_t addr);
void m28initSet8(uint16_t addr);
void m28initPPUGet8(uint16_t addr);
void m28initPPUSet8(uint16_t addr);

#endif
