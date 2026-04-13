/*
 * Copyright (C) 2017 - 2019 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef mmc3_h_
#define mmc3_h_

void mmc3init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m12init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m118init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m119init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void mmc3initGet8(uint16_t addr);
void mmc3initSet8(uint16_t addr);
void m12initSet8(uint16_t addr);
void m118initSet8(uint16_t ori_addr);
void m119initSet8(uint16_t ori_addr);
void m224initSet8(uint16_t ori_addr);
void mmc3initPPUGet8(uint16_t addr);
void mmc3initPPUSet8(uint16_t addr);
void m119initPPUSet8(uint16_t addr);
void mmc3SetChrROMadd(uint32_t val);
uint32_t mmc3GetChrROMadd();

#endif
