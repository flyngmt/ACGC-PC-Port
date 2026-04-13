/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef m13_h_
#define m13_h_

void m13init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize, 
			uint8_t *chrROM, uint32_t chrROMsize);
void m13initGet8(uint16_t addr);
void m13initSet8(uint16_t addr);
void m13initPPUGet8(uint16_t addr);
void m13initPPUSet8(uint16_t addr);

#endif
