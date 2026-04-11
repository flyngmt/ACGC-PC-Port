/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef m206h_
#define m206h_

void m206init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m95init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m112init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m112initGet8(uint16_t addr);
void m76initSet8(uint16_t addr);
void m88initSet8(uint16_t addr);
void m95initSet8(uint16_t addr);
void m112initSet8(uint16_t addr);
void m154initSet8(uint16_t addr);
void m206initSet8(uint16_t addr);
void m76initPPUGet8(uint16_t addr);
void m206initPPUGet8(uint16_t addr);
void m206initPPUSet8(uint16_t addr);

#endif
