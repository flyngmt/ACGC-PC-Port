/*
 * Copyright (C) 2019 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef smb2c_h_
#define smb2c_h_

void m40init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m43init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m50init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);

void m40initGet8(uint16_t addr);
void m43initGet8(uint16_t addr);
void m50initGet8(uint16_t addr);

void m40initSet8(uint16_t addr);
void m43initSet8(uint16_t addr);
void m50initSet8(uint16_t addr);

void smb2c_cycle();
void smb2c_reset();

#endif
