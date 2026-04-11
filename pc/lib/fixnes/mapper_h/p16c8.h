/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef p16c8_h_
#define p16c8_h_

void p16c8init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void p1632c8init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m57_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m58_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m60_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m62_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m97_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m174_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m180_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m200_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m221_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m226_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m230_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m231_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m232_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m235_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m212_initGet8(uint16_t addr);
uint8_t m97_get8(uint16_t addr, uint8_t val);
uint8_t m180_get8(uint16_t addr, uint8_t val);
uint8_t m200_get8(uint16_t addr, uint8_t val);
uint8_t m231_get8(uint16_t addr, uint8_t val);
uint8_t m232_get8(uint16_t addr, uint8_t val);
void m2_initSet8(uint16_t addr);
void m57_initSet8(uint16_t ori_addr);
void m58_initSet8(uint16_t addr);
void m60_initSet8(uint16_t addr);
void m61_initSet8(uint16_t addr);
void m62_initSet8(uint16_t addr);
void m70_initSet8(uint16_t addr);
void m71_initSet8(uint16_t addr);
void m78_initSet8(uint16_t addr);
void m89_initSet8(uint16_t addr);
void m93_initSet8(uint16_t addr);
void m94_initSet8(uint16_t addr);
void m97_initSet8(uint16_t addr);
void m152_initSet8(uint16_t addr);
void m174_initSet8(uint16_t addr);
void m180_initSet8(uint16_t addr);
void m200_initSet8(uint16_t addr);
void m202_initSet8(uint16_t addr);
void m203_initSet8(uint16_t addr);
void m212_initSet8(uint16_t addr);
void m221_initSet8(uint16_t addr);
void m226_initSet8(uint16_t addr);
void m229_initSet8(uint16_t addr);
void m230_initSet8(uint16_t addr);
void m231_initSet8(uint16_t addr);
void m232_initSet8(uint16_t addr);
void m235_initSet8(uint16_t addr);
void m58_reset();
void m60_reset();
void m62_reset();
void m221_reset();
void m226_reset();
void m230_reset();
void m235_reset();

#endif
