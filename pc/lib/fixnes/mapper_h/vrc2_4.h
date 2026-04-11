/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef vrc2_4_h_
#define vrc2_4_h_

void vrc2_4_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void vrc2_4_initGet8(uint16_t addr);
void m21_initSet8(uint16_t ori_addr);
void m22_initSet8(uint16_t ori_addr);
void m23_initSet8(uint16_t ori_addr);
void m25_initSet8(uint16_t ori_addr);

#endif
