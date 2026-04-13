/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef p32c8_h_
#define p32c8_h_

void p32c8init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void p32c8RAMinit(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m7_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m36_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m41_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m46_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m132_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m136_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m185_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void m242_init(uint8_t *prgROM, uint32_t prgROMsize, 
			uint8_t *prgRAM, uint32_t prgRAMsize,
			uint8_t *chrROM, uint32_t chrROMsize);
void p32c8RAMinitGet8(uint16_t addr);
void m36_initGet8(uint16_t addr);
void m132_initGet8(uint16_t addr);
void m136_initGet8(uint16_t addr);
void m172_initGet8(uint16_t addr);
void m0_initSet8(uint16_t addr);
void m3_initSet8(uint16_t addr);
void m7_initSet8(uint16_t addr);
void m11_initSet8(uint16_t addr);
void m36_initSet8(uint16_t addr);
void m38_initSet8(uint16_t addr);
void m41_initSet8(uint16_t addr);
void m46_initSet8(uint16_t addr);
void m66_initSet8(uint16_t addr);
void m79_initSet8(uint16_t addr);
void m87_initSet8(uint16_t addr);
void m101_initSet8(uint16_t addr);
void m107_initSet8(uint16_t addr);
void m113_initSet8(uint16_t addr);
void m132_initSet8(uint16_t addr);
void m133_initSet8(uint16_t addr);
void m136_initSet8(uint16_t addr);
void m140_initSet8(uint16_t addr);
void m144_initSet8(uint16_t addr);
void m145_initSet8(uint16_t addr);
void m147_initSet8(uint16_t addr);
void m148_initSet8(uint16_t addr);
void m149_initSet8(uint16_t addr);
void m172_initSet8(uint16_t addr);
void m173_initSet8(uint16_t addr);
void m185_initSet8(uint16_t addr);
void m201_initSet8(uint16_t addr);
void m240_initSet8(uint16_t addr);
void m242_initSet8(uint16_t addr);
void m185_initPPUGet8(uint16_t addr);
void m41_reset();
void m46_reset();
void m242_reset();

#endif
