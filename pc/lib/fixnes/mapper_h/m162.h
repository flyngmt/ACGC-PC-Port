/*
 * Copyright (C) 2020 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef m162_h_
#define m162_h_

void m162_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m163_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m162_initGet8(uint16_t addr);
void m163_initGet8(uint16_t addr);
void m164_initGet8(uint16_t addr);
void m162_initSet8(uint16_t addr);
void m163_initSet8(uint16_t addr);
void m164_initSet8(uint16_t addr);
void m162_initPPUGet8(uint16_t addr);
void m162_initPPUSet8(uint16_t addr);
void m162_reset();
void m163_reset();

#endif
