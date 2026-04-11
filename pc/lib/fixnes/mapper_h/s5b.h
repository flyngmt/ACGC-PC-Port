/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef s5b_h_
#define s5b_h_

void s5Binit(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void s5BinitGet8(uint16_t addr);
void s5BinitSet8(uint16_t addr);
void s5Bcycle();

#endif
