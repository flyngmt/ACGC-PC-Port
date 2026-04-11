/*
 * Copyright (C) 2019 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef m77_h_
#define m77_h_

void m77init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m77initSet8(uint16_t addr);
void m77initPPUGet8(uint16_t addr);
void m77initPPUSet8(uint16_t addr);

#endif
